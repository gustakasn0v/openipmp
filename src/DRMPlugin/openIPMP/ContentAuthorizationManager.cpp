/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is OpenIPMP.
 * 
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 * 
 */
#include "client/ContentAuthorizationManager.h"
#include "client/ClientManager.h"
#include "squashxml/tools/Logger.h"
#include "busobj/Exception.h"
#include "busobj/ODRLLicense.h"
#include "squashxml/xml/XMLMessage.h"
#include "busobj/RightsHost.h"

// for base64 encoding / decoding
#include "squashxml/tools/ByteArray.h"
#include "squashxml/tools/RFC1521Base64.h"

// factories (which in turn include business objects)
#include "busobj/factories/DOI_Factory.h"
#include "busobj/factories/AuxData_Factory.h"
#include "busobj/factories/DigitalSignature_Factory.h"
#include "busobj/factories/KeyTransport_Factory.h"
#include "busobj/factories/IPMP_ContentId_Factory.h"
#include "busobj/factories/RightsHost_Factory.h"

//license management
#include "io/message/osmsMessageLicenseRequest.h"
#include "io/message/osmsMessageLicenseResponse.h"
#include "io/message/osmsMessageLicenseResponseError.h"

// content packaging messages
#include "io/message/osmsMessageRegisterContentAssignIdentifierRequest.h"
#include "io/message/osmsMessageRegisterContentAssignIdentifierResponse.h"
#include "io/message/osmsMessageRegisterContentAssignIdentifierResponseError.h"
#include "io/message/osmsMessageRegisterContentExistingIdentifierRequest.h"
#include "io/message/osmsMessageRegisterContentExistingIdentifierResponse.h"
#include "io/message/osmsMessageRegisterContentExistingIdentifierResponseError.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceRequest.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceResponse.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceResponseError.h"
#include "io/message/osmsMessageGetContentKeyRequest.h"
#include "io/message/osmsMessageGetContentKeyResponse.h"
#include "io/message/osmsMessageGetContentKeyResponseError.h"

// for reading/writing key data to/from temporary file
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>

ContentAuthorizationManager::ContentAuthorizationManager() : ClientManager()
{
}

ContentAuthorizationManager::~ContentAuthorizationManager()
{
}

// for media context retrieval (encoding - new mp4 file)
IPMP_MediaContext* ContentAuthorizationManager::constructNewIPMP_MediaContext (ContentRegistrationContext* contentRegCtx)
{

    // initialize pointers to track context and member objects
    IPMP_MediaContext* IPMPmediaCtx = NULL;			// media context to be created
    IPMP_ContentIdentity* pIPMP_ContentId = NULL;	// IPMP_ContentIdentity to be created
    DOI* pDOI_fromFile = NULL;						// local DOI from xmlmetafile; either incomplete (meta data only), or complete (externally generated DOI value)
    DOI* pMasterDOI = NULL;							// master DOI; returned from server if assigned, or from file if using externally generated)
    DOI* pInstanceDOI = NULL;						// instance DOI (returned from server)
    IPMP_MetaData* pMetaData = NULL;				// IPMP_MetaData to be created
    CipherContext* pCipherCtx = NULL;				// CipherContext to be created
	DigitalSignature* pDigitalSignature = NULL;		// DigitalSignature to be created

    // create AuxData object and set tool id
    AuxData* pAuxDataIn = NULL;		// auxillary data object (INCOMING)
    AuxData auxDataOut;				// auxillary data object (OUTGOING)
    auxDataOut.set_ToolId((char*)this->getToolId());		// hardcoded for now; needs to be registered with MPEG (change for each new version of tool?)
    auxDataOut.set_ProtectedFlag( contentRegCtx->get_secure() );

    // if xml file exists, parse it create DOI object, otherwise use hardcoded values
    if ( contentRegCtx->get_xmlmetafile() )
        pDOI_fromFile = DOI_Factory::CreateInstanceFromFile( contentRegCtx->get_xmlmetafile() );
    else
        pDOI_fromFile = DOI_Factory::CreateInstance();
        
    // did we get a DOI?
    if ( !pDOI_fromFile ) {
        gLogger->logError("Error creating input DOI.");
        return(NULL);
    }

    // check status of DOI from file, to determine action to take
    switch ( pDOI_fromFile->get_Status() ) {
        
        case DOI::DOI_NEEDS_MASTER_ASSIGNED:

            // RegisterContentAssignIdentifier
            gLogger->logInfo("Provided DOI status is: DOI_NEEDS_MASTER_ASSIGNED; will perform a RegisterContentAssignIdentifier operation.");
            pMasterDOI = RegisterContentAssignIdentifier(contentRegCtx, pDOI_fromFile);
            if (!pMasterDOI) {
                gLogger->logError("RegisterContentAssignIdentifier failed to return a Master DOI; cannot construct a media context.");
                return(NULL);
            }
            break;
            
        case DOI::DOI_IS_EXTERNALLY_GENERATED:

            // RegisterContentExistingIdentifier
            gLogger->logInfo("Provided DOI status is: DOI_IS_EXTERNALLY_GENERATED; will perform a RegisterContentExistingIdentifier operation.");
            pMasterDOI = RegisterContentExistingIdentifier(pDOI_fromFile);
            if (!pMasterDOI) {
                gLogger->logError("RegisterContentExistingIdentifier failed to return a Master DOI; cannot construct a media context.");
                return(NULL);
            }
            break;
            
        default:
            gLogger->logError("DOI returned an unknown status; cannot continue with construction of media context.");
            return(NULL);
            break;

    } // switch

	// create CipherContext (i.e. the symmetric content key)
	pCipherCtx = createCipherContext(contentRegCtx);	// note: returns NULL if secure / protected flag is set to false
            
	// RegisterDigitalItemInstance
	pInstanceDOI = RegisterDigitalItemInstance(contentRegCtx, pMasterDOI, pCipherCtx, &auxDataOut, &pDigitalSignature, &pAuxDataIn);
	if (!pInstanceDOI || !pDigitalSignature) {
		gLogger->logError("RegisterDigitalItemInstance failed to return an Instance DOI and a DigitalSignature; cannot construct a media context.");
		return(NULL);
	}

    // create IPMP Content Identifier
    pIPMP_ContentId = new IPMP_ContentIdentity (pInstanceDOI, pDigitalSignature);

    // construct an IPMP_MetaData from the instance DOI
    IPMP_MetaData lMetaData;
	if ( !lMetaData.init ( pIPMP_ContentId, pAuxDataIn ) ) {
		gLogger->logError("Unable to initialize the IPMP_MetaData object.");
		return(NULL);
	}
	
	// copy newly created IPMP_MetaData into the IPMP_ContentIdentity object
	pIPMP_ContentId->set_IPMP_MetaData(&lMetaData);

    // construct new media context with IPMP_ContentIdentity and CipherContext
    IPMPmediaCtx = new IPMP_MediaContext(pIPMP_ContentId, pCipherCtx);

	// clean up memory
	if (pAuxDataIn)
		delete pAuxDataIn;
	if (pIPMP_ContentId)
		delete pIPMP_ContentId;
	if (pCipherCtx)
		delete pCipherCtx;

    // return newly created media context
    return(IPMPmediaCtx);

}

// for media context retrieval (encoding - add track to existing mp4 file)
IPMP_MediaContext* ContentAuthorizationManager::retrieveIPMP_MediaContext (ContentRegistrationContext* contentRegCtx, IPMP_MetaData* pMetaData)
{

	// check protected flag
	if (pMetaData->get_ProtectedContentFlag() ) {
	
		// construct IPMP_ContentIdentity object
		IPMP_ContentIdentity* pIPMP_ContentId = IPMP_ContentId_Factory::CreateInstance( pMetaData->get_ContentId() );
		if (!pIPMP_ContentId) {
			gLogger->logError("Failed attempt to parse ContentId.");
			return(NULL);
		}
			
		// decode the DOI and DigitalSignature
		if (!pIPMP_ContentId->decode() ) {
			gLogger->logError("Failed attempt to decode the DOI and/or DigitalSignature in the IPMP_ContentIdentity.");
			return(NULL);
		}

		// decode and set RightsHost information
/** Don't think this is necessary
		RightsHost* pRightsHost = RightsHost_Factory::CreateInstance( pMetaData->get_RightsHost() );
		if (!pRightsHost) {
			gLogger->logError("Failed attempt to parse RightsHost data.");
			return(NULL);
		}
		set_ip( (char*) pRightsHost->get_URL() );
		set_port( pRightsHost->get_Port() );
**/
		
		// put the MetaData object on the IPMP_ContentIdentity
		pIPMP_ContentId->set_IPMP_MetaData(pMetaData);

		// make sure we are logged in remotely
		// TODO: This needs error checking
		login(LOCAL_LOGIN);
			
		// verify DigitalSignature
		if (!VerifySignature( (DOI*) pIPMP_ContentId->get_DOI(),  (DigitalSignature*) pIPMP_ContentId->get_DigitalSignature() ) ) {
			gLogger->logError("DigitalSignature failed verification.");
			return(NULL);
		}
			
		// get key from server and create CipherContext from it
		CipherContext* pCipherCtx = GetContentKey (contentRegCtx, (char*) pIPMP_ContentId->get_DOI()->get_DOI_idStr() /***, DigitalSignature** pDigitalSignature,***//*** AuxData** ppAuxDataIn***/);
		if (!pCipherCtx) {
			gLogger->logError("GetContentKey failed to return an Cipher Context; cannot reconstruct the media context.");
			return(NULL);
		}

		// construct new media context with IPMP_ContentIdentity and CipherContext
		IPMP_MediaContext* ipmpCtx = new IPMP_MediaContext(pIPMP_ContentId, pCipherCtx);
			
		// return newly created IPMP_MediaContext
		return(ipmpCtx);	
	
	} // if protected
	else { // not protected
		return ( retrieveUnprotectedIPMP_MediaContext (/*** pIntent? ***/) );
	} // not protected

}

// for media context retrieval (playback)
IPMP_MediaContext* ContentAuthorizationManager::retrieveIPMP_MediaContext (bool retCode, IPMP_MetaData* pMetaData, char* pIntent)
{

	if (retCode)	// if IPI Data set exists
					//   Note: this is the return code from either MP4GetODStreamIPMPInfo()
					//         or MP4ParseIPMPInfoFromSdpIod()
	{
		// check protected flag
		if (pMetaData->get_ProtectedContentFlag() )
		{

		    // make sure we are logged in locally
			// TODO: This needs error checking
			//CJM login(LOCAL_LOGIN);

// TODO: This should just use the login() function that is commented out above ...

			/** CJM fixes local login bug */
			if (localLogin())
				m_loginState = LOCAL_LOGIN;
			else
			{
				gLogger->logError("ContentAuthorizationManager::retrieveIPMP_MediaContext : Unable to login locally to P12 file...");
				throw EXCEPTION(Exception::P12_LOGIN_MANUAL_FAILED);
			}

			// construct IPMP_ContentIdentity object
			IPMP_ContentIdentity* pIPMP_ContentId = IPMP_ContentId_Factory::CreateInstance( pMetaData->get_ContentId() );
			if (!pIPMP_ContentId) {
				gLogger->logError("Failed attempt to parse ContentId.");
				return(NULL);
			}
			
			// decode the DOI and DigitalSignature
			if (!pIPMP_ContentId->decode() ) {
				gLogger->logError("Failed attempt to decode the DOI and/or DigitalSignature in the IPMP_ContentIdentity.");
				return(NULL);
			}

			// decode and set RightsHost information
			RightsHost* pRightsHost = RightsHost_Factory::CreateInstance( pMetaData->get_RightsHost() );
			if (!pRightsHost) {
				gLogger->logError("Failed attempt to parse RightsHost data.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}
			set_ip( (char*) pRightsHost->get_URL() );
			set_port( pRightsHost->get_Port() );
		
			// put the MetaData object on the IPMP_ContentIdentity
			pIPMP_ContentId->set_IPMP_MetaData(pMetaData);
			
			// verify DigitalSignature
			// TODO: Should this move to the private retrieveIPMP_MediaContext? Don't think it matters ...
			if (!VerifySignature( (DOI*) pIPMP_ContentId->get_DOI(),  (DigitalSignature*) pIPMP_ContentId->get_DigitalSignature() ) ) {
				gLogger->logError("DigitalSignature failed verification.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}
			
			IPMP_MediaContext* ipmpCtx;			  
			try
			{
				// retrieve track context (private overloaded function for retieving from local store / server delivery
				ipmpCtx = retrieveIPMP_MediaContext(pIPMP_ContentId, pIntent);
			}
			catch(Exception& e)
			{
				gLogger->logError( e.getErrorMsg() );
				throw;
			}
			
			return(ipmpCtx);
			
		} // if protected
		else {
			return ( retrieveUnprotectedIPMP_MediaContext ( /*** pIntent? ***/) );
		}
	} // if IPI Data set exists
	else {
		return ( retrieveUnprotectedIPMP_MediaContext (/*** pIntent? ***/) );
	}

}

// for media context retrieval (playback) with license from local store or server delivery
IPMP_MediaContext* ContentAuthorizationManager::retrieveIPMP_MediaContext (IPMP_ContentIdentity* pContentId, char* pIntent)
{

    // init
    IPMP_MediaContext* IPMPmediaCtx = NULL;
    CipherContext* pCipherCtx = new CipherContext();
    OctetString keyBlob;

// TODO: This should use the login() function ....

	if (m_loginState == NO_LOGIN)
	{
		if (localLogin())
			m_loginState = LOCAL_LOGIN;
		else

		{
			gLogger->logError("Unable to login locally to P12 file...");
			// delete any alloc'd mem and throw exception
			delete pCipherCtx;
			throw EXCEPTION(Exception::P12_LOGIN_MANUAL_FAILED);
		}
	}

// TODO: This should be reworked (simplified) by using the sendMessage() function.

	if (m_loginState == LOCAL_LOGIN)
	{
		// now check the local storage for this user's license

		if (!m_UserContext->authorize(pIntent, (char*) pContentId->get_ResourceKey(), &keyBlob))
		{
			// login to the server and request a license
			if (!remoteLogin())
			{
				gLogger->logError("Unable to login to server...make sure server's running");

				/** CJM disconnect here... */
				if (m_SecurityManagerProxy->isConnected())
					m_SecurityManagerProxy->disconnect();

				delete pCipherCtx;
				throw EXCEPTION(Exception::BAD_OSMS_LOGIN);
			}
			else
			{
				// request license for contentID
				if (!retrieveRemoteLicense(pIntent, (char*) pContentId->get_ResourceKey()))
				{
					remoteLogout();
					gLogger->logError("Unable to retrieve and store License from OSMS.");

					/** CJM disconnect here... */
					if (m_SecurityManagerProxy->isConnected())
						m_SecurityManagerProxy->disconnect();

					delete pCipherCtx;
					throw EXCEPTION(Exception::BAD_OSMS_LICENSE_REQUEST);
				}
				else
				{
					// recheck their authorization...
					if (!m_UserContext->authorize(pIntent, (char*) pContentId->get_ResourceKey(), &keyBlob))
					{
						remoteLogout();
						// throw exception... really can't continue
							if (m_SecurityManagerProxy->isConnected())
								m_SecurityManagerProxy->disconnect();
							gLogger->logError("Unable to obtain license for intent and contentID");

							delete pCipherCtx;
							throw EXCEPTION(Exception::LICENSE_NOT_FOUND);
					}
					else
					{
						remoteLogout();
				
						/** CJM disconnect here... */
						if (m_SecurityManagerProxy->isConnected())
							m_SecurityManagerProxy->disconnect();
					}

				}
			
			}
		}
		
	}	// if m_loginState = LOCAL_LOGIN

	// if here, got a key so set up a IPMP_MediaContext
	if (keyBlob.len)
	{
		// CJM hack..should read the Cipher type ("BF-CFB") from the license 
		pCipherCtx->setCipher((struct evp_cipher_st*)EVP_get_cipherbyname("BF-CFB"));
		pCipherCtx->setKey(&keyBlob);

		// free up the key buf
		free(keyBlob.octets);
		keyBlob.len = 0;

		// TODO: This will not work for block cipher mode, but should be okay for stream cipher
		pCipherCtx->decryptInit();
		gLogger->logInfo("Initialized Cipher Context with license key.");
	}
	else
	{
		//HAVE play rights, but no key..  possible, but would need to reference the encrypted attribute located in the IPIDataset
		delete pCipherCtx;
		throw EXCEPTION(Exception::MISSING_LICENSE_KEY);
	}

    // construct new media context with IPMP_ContentIdentity and CipherContext
	IPMPmediaCtx = new IPMP_MediaContext(pContentId, pCipherCtx);
	gLogger->logInfo("Media Context created.");

	// clean up memory
	if (pCipherCtx)
		delete pCipherCtx;

    // return newly created IPMP_MediaContext
    return(IPMPmediaCtx);
        
}

// This function is intented for use when no IPI dataset (and therefore no Content Id) is present in
// the IOD. It returns a dummy IPMP_MediaContext that has the ProtectedFlag set to false, and will 
// therefore result in NULL decryption.
IPMP_MediaContext* ContentAuthorizationManager::retrieveUnprotectedIPMP_MediaContext ( /*** char* pIntent ***/ )
{

    // construct empty IPMP_MediaContext
    IPMP_MediaContext* IPMPmediaCtx = new IPMP_MediaContext();

    // construct empty IPMP_ContentIdentity
    IPMP_ContentIdentity lIPMP_ContentId;

    // construct empty IPMP_MetaData and attach to IPMP_ContentIdentity
    IPMP_MetaData lIPMP_MetaData;
	lIPMP_ContentId.set_IPMP_MetaData ( &lIPMP_MetaData );

    // construct empty DOI and attach to IPMP_ContentIdentity
    DOI lDOI;
	lIPMP_ContentId.set_DOI ( &lDOI );

    // copy IPMP_ContentIdentity into media context
	IPMPmediaCtx->set_IPMP_ContentIdentity ( &lIPMP_ContentId );

    // set ProtectedFlag
    IPMPmediaCtx->set_ProtectedFlag(false);

    // return newly created IPMP_MediaContext
    return(IPMPmediaCtx);

}

bool ContentAuthorizationManager::retrieveRemoteLicense(char* p_Intent, char* p_ResourceKey)
{
		// do we have a host ip address and port?
	if (!m_ip || !m_port) {
		gLogger->logError("Failed attempt to login remotely: host ip address and/or port missing. Proceeding...");
		return(false);
	}

	// create socket connection if one does not already exist
	if (!m_SecurityManagerProxy->isConnected())
		if (!m_SecurityManagerProxy->connect(m_ip, m_port) || !m_SecurityManagerProxy->isConnected()) {
			gLogger->logError("Failed attempt to create socket connection. Aborting login procedure, but proceeding otherwise...");
			return(false);
		}

	// create and populate login request message
	osmsMessageLicenseRequest msgLicenseRequest;
	msgLicenseRequest.setContentId(p_ResourceKey);
	msgLicenseRequest.setRightsInfo(p_Intent);

	// send message
	m_SecurityManagerProxy->sendRequest(&msgLicenseRequest);

	osmsMessage* msgResponse = m_SecurityManagerProxy->getResponse();

	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving LicenseRequest message. Aborting License procedure...");
		return(false);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_LICENSE_RESPONSE:
		{
			osmsMessageLicenseResponse* pLicenseResponse = (osmsMessageLicenseResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_LICENSE_RESPONSE.");
			
			gLogger->logInfo("Adding license to local store..");

			License* newLicense = NULL;
			char* dID = NULL;
			XMLDocument licenseDoc;
			char* pBuf = pLicenseResponse->getLicense();

			/** CJM 4/14/03 try to decode the MPEGREL or ODLRL license */
			if (!m_CryptoManager->decodeLicense(&licenseDoc, pBuf, &dID, &newLicense)) {
				gLogger->logError("Unable to decode license from OSMSLicenseResponse Message");
				if (newLicense) delete newLicense;
				return false;
			}

			//add the license to the user's internal map and then save it to disk
			m_UserContext->addLicenseToMap(dID, newLicense);
			m_CryptoManager->storeP12Instance(m_UserContext);

			delete dID;
			delete msgResponse;
			return(true);
		}
		case osmsMessage::osmsMESSAGE_LICENSE_RESPONSE_ERROR:
		{
			osmsMessageLicenseResponseError* pError = (osmsMessageLicenseResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_LICENSE_RESPONSE_ERROR.");
			gLogger->logError(pError->getResponseString());
			delete msgResponse;
			return(false);
		}
		default:
		{
			gLogger->logError("Received unknown response message. Proceeding...");
			delete msgResponse;
			return(false);
		}
	} // switch

}

DOI* ContentAuthorizationManager::RegisterContentAssignIdentifier (ContentRegistrationContext* contentRegCtx, DOI* pSendDOI)
{

    // make sure we are logged in remotely
	// TODO: This needs error checking
	login(REMOTE_LOGIN);

	// create and populate RegisterContentAssignIdentifier request message
	osmsMessageRegisterContentAssignIdentifierRequest msgRequest;
	msgRequest.setMetadataType("DOI");		// TODO: This should come from the DOI class itself
	msgRequest.setMetadataXml( (char*) pSendDOI->get_XML_str() );

	// send request / receive response
	osmsMessage* msgResponse = sendMessage(&msgRequest);
	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving RegisterContentAssignIdentifier message.");
		return(false);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE:
		{
			osmsMessageRegisterContentAssignIdentifierResponse* pRegisterContentAssignIdentifierResponse = (osmsMessageRegisterContentAssignIdentifierResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE.");

			DOI* pReturnedDOI = NULL;

			// DOI-Kernel
			if ( strcmp(pRegisterContentAssignIdentifierResponse->getMetadataType(), "DOI") == 0 ) {
                        
				// construct DOI object from response
				pReturnedDOI = DOI_Factory::CreateInstance( pRegisterContentAssignIdentifierResponse->getMetadataXml() );
                                
				// write DOI xml stream to file
				if ( contentRegCtx->get_writemasterDOIfile() ) {
					FILE* fp;
					fp = fopen(contentRegCtx->get_writemasterDOIfile(), "wb");
					fwrite(pReturnedDOI->get_XML_str(), strlen( pReturnedDOI->get_XML_str() ), 1, fp);
					fclose(fp);
				}
			} // DOI-Kernel
                        
			// unknown meta data type
			else {
				gLogger->logError("RegisterContentAssignIdentifierResponse contained an unknown MetadataType.");
			}

			delete msgResponse;
			return(pReturnedDOI);
		}
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE_ERROR:
		{
			osmsMessageRegisterContentAssignIdentifierResponseError* pError = (osmsMessageRegisterContentAssignIdentifierResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE_ERROR.");
			gLogger->logError(pError->getResponseString());
			delete msgResponse;
			return(NULL);
		}
		default:
		{
			gLogger->logError("Received unknown response message.");
			delete msgResponse;
			return(NULL);
		}
	} // switch
}

DOI* ContentAuthorizationManager::RegisterContentExistingIdentifier (DOI* pSendDOI)
{
    // make sure we are logged in remotely
	// TODO: This needs error checking
	login(REMOTE_LOGIN);

	// create and populate RegisterContentExistingIdentifier request message
	osmsMessageRegisterContentExistingIdentifierRequest msgRequest;
	msgRequest.setMetadataType("DOI");		// TODO: This should come from the DOI class itself
	msgRequest.setMetadataXml( (char*) pSendDOI->get_XML_str() );

	// send request / receive response
	osmsMessage* msgResponse = sendMessage(&msgRequest);
	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving RegisterContentExistingIdentifier message.");
		return(false);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE:
		{
			osmsMessageRegisterContentExistingIdentifierResponse* pRegisterContentAssignIdentifierResponse = (osmsMessageRegisterContentExistingIdentifierResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE.");
			delete msgResponse;
			// return the same DOI that was sent ...
			return(pSendDOI);
		}
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE_ERROR:
		{
			osmsMessageRegisterContentExistingIdentifierResponseError* pError = (osmsMessageRegisterContentExistingIdentifierResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE_ERROR.");
			gLogger->logError(pError->getResponseString());
			delete msgResponse;
			return(NULL);
		}
		default:
		{
			gLogger->logError("Received unknown response message.");
			delete msgResponse;
			return(NULL);
		}
	} // switch
}

DOI* ContentAuthorizationManager::RegisterDigitalItemInstance (ContentRegistrationContext* contentRegCtx, DOI* pSendDOI, CipherContext* pCipherCtx, AuxData* pAuxDataOut, DigitalSignature** pDigitalSignature, AuxData** ppAuxDataIn)
{

    // make sure we are logged in remotely
	// TODO: This needs error checking
	login(REMOTE_LOGIN);

    // do we have a key to send?
	KeyTransport keyTransport;
	if ( contentRegCtx->get_secure() )  {

		// allocate buffer for encrypted key = RSA Key size + 11 bytes (depending on the padding mode)
		OctetString encrytedKey;
		encrytedKey.octets = new unsigned char[m_UserContext->getRSAKeySize()+11];
		
		// encrypt with RSA key
		encrytedKey.len = RSA_public_encrypt((pCipherCtx->getKeyLength() / 8), pCipherCtx->getKeyBytes(), encrytedKey.octets, m_UserContext->getPrivateKey(), RSA_PKCS1_PADDING);
		if(encrytedKey.len < 1) {	// -1 should indicate error...
			gLogger->logError("Error encrypting content key with user's public key.");
			return(false);
		}

		// base 64 encode the key
		// TODO: Move this to the set_octets() function on the KeyTransport object
		char* base64enc_encryptedKeyBytes = NULL;
		ByteArray* encryptedKeyBytes = new ByteArray((char*) encrytedKey.octets, encrytedKey.len);
		base64enc_encryptedKeyBytes = RFC1521Base64::encode( encryptedKeyBytes );

		// base 64 encode the certificate
		char* base64enc_certificate = NULL;
		ByteArray* certificate_bytes = new ByteArray((char*) m_UserContext->getUserCertASN1()->octets, m_UserContext->getUserCertASN1()->len);
		base64enc_certificate = RFC1521Base64::encode( certificate_bytes );

		// build up the key transport object
		keyTransport.set_KeyAlgorithm("http://www.w3.org/2001/04/xmlenc#blowfish128-cfb");	// TODO: this should be defined elsewhere
		keyTransport.set_TransportAlgorithm("http://www.w3.org/2001/04/xmlenc#rsa-1_5");	// TODO: this should be defined elsewhere
		keyTransport.set_EncKeyValue_base64( base64enc_encryptedKeyBytes );
		keyTransport.set_Certificate_base64( base64enc_certificate );

        // clean up memory
    		delete encrytedKey.octets;
		delete encryptedKeyBytes;
		delete certificate_bytes;
        delete[] base64enc_encryptedKeyBytes;
        delete[] base64enc_certificate;

	}
	else {
	
		// build up empty key transport object
		keyTransport.set_KeyAlgorithm("Not Protected");
		keyTransport.set_TransportAlgorithm("Not Protected");
		keyTransport.set_EncKeyValue_base64("Not Protected");
		keyTransport.set_Certificate_base64("Not Protected");
	}

	// encode KeyXml and AuxDataXml (these return dynamically allocated memory)
	char* pEncoded_KeyXml = keyTransport.encode();
	char* pEncoded_AuxDataXml = pAuxDataOut->encode();

	// create and populate RegisterContentExistingIdentifier request message
	osmsMessageRegisterDigitalItemInstanceRequest msgRequest;
	msgRequest.setMetadataType("DOI");		// TODO: This should come from the DOI class itself
	msgRequest.setMetadataXml( (char*) pSendDOI->get_XML_str() );
	msgRequest.setKeyXml( pEncoded_KeyXml );
	msgRequest.setAuxDataXml( pEncoded_AuxDataXml );

	// send request / receive response
	osmsMessage* msgResponse = sendMessage(&msgRequest);
	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving RegisterDigitalItemInstance message.");
		return(false);
	}

	// clean up memory
	free(pEncoded_KeyXml);
	free(pEncoded_AuxDataXml);

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE:
		{
			osmsMessageRegisterDigitalItemInstanceResponse* pRegisterDigitalItemInstanceResponse = (osmsMessageRegisterDigitalItemInstanceResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE.");

			DOI* pReturnedDOI = NULL;

			// DOI-Kernel
			if ( strcmp(pRegisterDigitalItemInstanceResponse->getMetadataType(), "DOI") == 0 ) {

				// construct DOI object from response
				pReturnedDOI = DOI_Factory::CreateInstance( pRegisterDigitalItemInstanceResponse->getMetadataXml() );

				// check for errors
				if (!pReturnedDOI) {
					gLogger->logError("Unable to parse Instance DOI.");
					return(NULL);
				}
                                
				// write DOI xml stream to file
				if ( contentRegCtx->get_writeinstanceDOIfile() ) {
					FILE* fp;
					fp = fopen(contentRegCtx->get_writeinstanceDOIfile(), "wb");
					fwrite(pReturnedDOI->get_XML_str(), strlen( pReturnedDOI->get_XML_str() ), 1, fp);
					fclose(fp);
				}
			}
			// unknown meta data type
			else {
				gLogger->logError("RegisterDigitalItemInstanceResponse contained an unknown MetadataType.");
			}

			// set rights host on aux data object
			*ppAuxDataIn = AuxData_Factory::CreateInstance( pRegisterDigitalItemInstanceResponse->getAuxDataXml() );

			// check for errors
			if (!(*ppAuxDataIn)) {
				gLogger->logError("Unable to parse AuxData.");
				return(NULL);
			}

			/** 
				CJM 4/9/03 to handle new GUID ToolID value
				the server should be updated to handle a string TOOLID value 
				instead of an integer.
			*/
			(*ppAuxDataIn)->set_ToolId((char*)this->getToolId());

			// construct DigitalSignature object from response
			*pDigitalSignature = DigitalSignature_Factory::CreateInstance( pRegisterDigitalItemInstanceResponse->getSignatureXml() );

			// check for errors
			if (!(*pDigitalSignature)) {
				gLogger->logError("Unable to parse DigitalSignature.");
				return(NULL);
			}

			// write DigitalSignature xml stream to file
			if ( contentRegCtx->get_writedsigfile() ) {
				FILE* fp;
				fp = fopen(contentRegCtx->get_writedsigfile(), "wb");
				fwrite( (*pDigitalSignature)->get_XML_str(), strlen( (*pDigitalSignature)->get_XML_str() ), 1, fp);
				fclose(fp);
			}

			// verify signature
			if ( !VerifySignature(pReturnedDOI, (*pDigitalSignature)) ) {
				gLogger->logError("DigitalSignature verification failed.");
				return(NULL);
			}

			delete msgResponse;
			return(pReturnedDOI);
		}
		case osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR:
		{
			osmsMessageRegisterDigitalItemInstanceResponseError* pError = (osmsMessageRegisterDigitalItemInstanceResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR.");
			gLogger->logError(pError->getResponseString());
			delete msgResponse;
			return(NULL);
		}
		default:
		{
			gLogger->logError("Received unknown response message.");
			delete msgResponse;
			return(NULL);
		}
	} // switch
}

CipherContext* ContentAuthorizationManager::GetContentKey (ContentRegistrationContext* contentRegCtx, char* pDOI_idStr /***, DigitalSignature** pDigitalSignature ***//***,  AuxData** ppAuxDataIn ***/)
{
    // make sure we are logged in remotely
	// TODO: This needs error checking
	login(REMOTE_LOGIN);

	// create and populate RegisterContentExistingIdentifier request message
	osmsMessageGetContentKeyRequest msgRequest;
	msgRequest.setMetadataType("DOI");		// TODO: This should come from the DOI class itself
	msgRequest.setDigitalItemInstanceId( pDOI_idStr );

	// send request / receive response
	osmsMessage* msgResponse = sendMessage(&msgRequest);
	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving GetContentKey message.");
		return(false);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_GET_CONTENT_KEY_RESPONSE:
		{
			osmsMessageGetContentKeyResponse* pGetContentKeyResponse = (osmsMessageGetContentKeyResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_GET_CONTENT_KEY_RESPONSE.");

			KeyTransport* pKeyTransport = KeyTransport_Factory::CreateInstance ( pGetContentKeyResponse->getKeyXml() );

			// decrypt the delivered content key with user's private key
			unsigned char* decryptedKeyBuffer = new unsigned char[m_UserContext->getRSAKeySize()];
			int decryptedKeyLength = RSA_private_decrypt(pKeyTransport->get_EncKeyValue_octets()->len, pKeyTransport->get_EncKeyValue_octets()->octets, decryptedKeyBuffer, m_UserContext->getPrivateKey(), RSA_PKCS1_PADDING);

			// instantiate and initialize CipherContext
			CipherContext* pCipherCtx = createCipherContext (contentRegCtx, decryptedKeyBuffer, decryptedKeyLength );

			// get AuxData
			// TODO: This is a hack; need a AuxData_Factory that derives from XMLDocument
//			pAuxData->set_RightsHost_XML( pGetContentKeyResponse->getAuxDataXml() );

/***** No longer necessary
			*ppAuxDataIn = AuxData_Factory::CreateInstance ( pGetContentKeyResponse->getAuxDataXml() );

			// check for errors
			if (!(*ppAuxDataIn)) {
				gLogger->logError("Unable to parse AuxData.");
				return(NULL);
			}
 *****/
                        
			// delete base 64 decode buffer and response message
// KLUDGE: Not sure why this wasn't ok; pointer problem? Should be malloc'd in base64_decode()
//			free(base64dec_buffer);
//			delete base64dec;

			// clean up memory
			delete msgResponse;
			delete[] decryptedKeyBuffer;
                        
			return(pCipherCtx);
		}
		case osmsMessage::osmsMESSAGE_GET_CONTENT_KEY_RESPONSE_ERROR:
		{
			osmsMessageGetContentKeyResponseError* pError = (osmsMessageGetContentKeyResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_GET_CONTENT_KEY_RESPONSE_ERROR.");
			gLogger->logError(pError->getResponseString());
			delete msgResponse;
			return(NULL);
		}
		default:
		{
			gLogger->logError("Received unknown response message.");
			delete msgResponse;
			return(NULL);
		}
	} // switch
}

CipherContext* ContentAuthorizationManager::createCipherContext (ContentRegistrationContext* contentRegCtx, unsigned char* pKeyBuffer, int keyBufferLength)
{
	// create and initialize Cipher Context
	CipherContext* pCipherCtx = new CipherContext();
	if ( m_CryptoManager->init(pCipherCtx, ALG_CIPHER, CIPHER_KEYSIZE) )
		gLogger->logInfo("Initialized Cipher Context.");
	else
		gLogger->logError("Failed attempt to initialize Cipher Context. Proceeding...");

        pCipherCtx->setCipher((struct evp_cipher_st*)EVP_get_cipherbyname("BF-CFB"));
    // TODO: Change this to use OctetString and setKey(); these functions have been
    //       deprecated, but should still work ...
        pCipherCtx->setKeyBytes(pKeyBuffer, keyBufferLength);
        pCipherCtx->setKeyLength(keyBufferLength * 8);
        gLogger->logInfo("Initialized Cipher Context with key from buffer.");

	// Writing the key data to a file (for debugging purposes)
	if (contentRegCtx->get_writekeyfile()) {
            FILE* fp;
            fp = fopen(contentRegCtx->get_writekeyfile(), "wb");
    // TODO: Was getKeyBytes deprecated? It still works, but might want to change this
            fwrite(pCipherCtx->getKeyBytes(), (pCipherCtx->getKeyLength() / 8), 1, fp);
            fclose(fp);
	} // if (contentRegCtx->get_writekeyfile()) 

        return(pCipherCtx);
}

CipherContext* ContentAuthorizationManager::createCipherContext (ContentRegistrationContext* contentRegCtx)
{

    if ( contentRegCtx->get_secure() )  {

	// create and initialize Cipher Context
	CipherContext* pCipherCtx = new CipherContext();
	if ( m_CryptoManager->init(pCipherCtx, ALG_CIPHER, CIPHER_KEYSIZE) )
		gLogger->logInfo("Initialized Cipher Context.");
	else
		gLogger->logError("Failed attempt to initialize Cipher Context. Proceeding...");

        // Reading key data from a file (for debugging purposes)
        if ( contentRegCtx->get_usekeyfile() ) {
            FILE* fp;
            struct stat tstat;
            stat(contentRegCtx->get_usekeyfile(), &tstat);
            fp = fopen(contentRegCtx->get_usekeyfile(), "rb");
            if (!fp) {
                gLogger->logError("Failed attempt to open debug key data file.");
                return(NULL);
            }
            unsigned char* keybuf = (unsigned char*) malloc(tstat.st_size+1);
            fread(keybuf, tstat.st_size, 1, fp);
            fclose(fp);
            
            pCipherCtx->setCipher((struct evp_cipher_st*)EVP_get_cipherbyname("BF-CFB"));
    // TODO: Change this to use OctetString and setKey(); these functions have been
    //       deprecated, but should still work ...
            pCipherCtx->setKeyBytes(keybuf, tstat.st_size);
            pCipherCtx->setKeyLength(tstat.st_size * 8);
            gLogger->logInfo("Initialized Cipher Context with key from file.");
            delete keybuf;
            
        } // if (contentRegCtx->get_usekeyfile())
        
        else // if (contentRegCtx->get_writekeyfile())
            gLogger->logInfo("Using a newly generated track key. (Key file was null).");

	// Writing the key data to a temporary file (for debugging purposes)
	if (contentRegCtx->get_writekeyfile()) {
            FILE* fp;
            fp = fopen(contentRegCtx->get_writekeyfile(), "wb");
    // TODO: Was getKeyBytes deprecated? It still works, but might want to change this
            fwrite(pCipherCtx->getKeyBytes(), (pCipherCtx->getKeyLength() / 8), 1, fp);
            fclose(fp);
	} // if (contentRegCtx->get_writekeyfile()) 

        return(pCipherCtx);
    } // // if (secure)
    
    else // if (secure)
        return(NULL);

}

// Verify DOI Signature
bool ContentAuthorizationManager::VerifySignature (DOI* pDOI, DigitalSignature* pDigitalSignature)
{

	// get hash of DOI xml
	HashContext hashDOI;
	// TODO: This should set the hash type using pDigitalSignature->get_DigestMethod() when that functionality becomes available
	m_CryptoManager->init(&hashDOI, "SHA1");
	hashDOI.hashUpdate((unsigned char*)pDOI->get_XML_str(), strlen(pDOI->get_XML_str()) );
	hashDOI.hashFinal();

	return(hashDOI.verifySignature(
		(pDigitalSignature->get_SignatureValue_octets())->octets,
		(pDigitalSignature->get_SignatureValue_octets())->len,
		m_UserContext->getCaCertChain()
	));
}
