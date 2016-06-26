/**	\file OsmsOpenIPMPMessenger.cpp

	Implementation of openIPMP messenger using osms messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OsmsOpenIPMPMessenger.h"

#include "busobj/Exception.h"
#include "squashxml/tools/ByteArray.h"
#include "squashxml/tools/RFC1521Base64.h"
#include "busobj/KeyTransport.h"
#include "busobj/AuxData.h"
#include "busobj/DOI.h"
#include "busobj/factories/DOI_Factory.h"
#include "busobj/factories/DigitalSignature_Factory.h"
#include "busobj/IPMP_ContentIdentity.h"
#include "busobj/factories/IPMP_ContentId_Factory.h"

#include "OpenIPMP.h"

#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!  \brief  Class used for handling globals.
*/
class OsmsMessengerGlobalHandler {
public:
  /*!  \brief  Constructor.

      If fails, throws OpenIPMPMessengerException.
  */
  OsmsMessengerGlobalHandler(): aMutex(ThreadSyncFactory::GetGlobalMutex()) {
    if (aMutex == 0) {
      throw OpenIPMPMessengerException();
    }
  }

  /*!  \brief  Destructor.
  */
  ~OsmsMessengerGlobalHandler() {
    if (aMutex != 0) delete aMutex; aMutex = 0;
  }

  /*!  \brief  Get messenger mutex.

      \returns  Messenger mutex.
  */
  IMutex* GetMutex() {
    return aMutex;
  }

private:
  IMutex* aMutex;
};

static OsmsMessengerGlobalHandler osmsMessengerGlobalHandler;

/*! \brief  Constructor.

    Use the information provided in the XML document.

    Optional tags in the XML file are:
     - ROOT.P12FilePath
     - ROOT.RandomNumberFilePath.

    If ROOT.P12FilePath tag is not present, p12 path is set to \localsecurity\.
    If ROOT.RandomNumberFilePath tag is not present, random number file path is
    set to .\entropy.dat.
    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <P12FilePath>\localsecurity\</P12FilePath>
     <RandomNumberFilePath>.\entropy.dat</RandomNumberFilePath>
    </ROOT>

    \endverbatim

    \param    xmlDoc          input, XML document.
    \param    logger          input-output, message logger.

    If constructor fails, it throws OpenIPMPMessengerException and logger's
    log contains error description.
*/
OsmsOpenIPMPMessenger::OsmsOpenIPMPMessenger(IXMLElement* xmlDoc, DRMLogger& logger):
    cryptoManager(0), messengerLogger(logger) {
  if (osmsMessengerGlobalHandler.GetMutex() == 0) {
    throw OpenIPMPMessengerException();
  }
  if (osmsMessengerGlobalHandler.GetMutex()->Lock(EVENT_WAIT_TIME) == false) {
    throw OpenIPMPMessengerException();
  }
  cryptoManager = new CryptoManager();
  std::string p12Path = "";
  std::string rnPath = "";
  if (xmlDoc != 0) {
    try {
      p12Path = xmlDoc->GetChildStrValue("P12FilePath");
    }
    catch (XMLException) {
    }
    try {
      rnPath = xmlDoc->GetChildStrValue("RandomNumberFilePath");
    }
    catch (XMLException) {
    }
  }
  if (p12Path != "") {
  	cryptoManager->setP12FilePath((char*)(p12Path.data()));
  } else {
#ifdef WIN32
  	cryptoManager->setP12FilePath("\\localsecurity\\");
#else
	  cryptoManager->setP12FilePath("./");
#endif
  }
  if (rnPath != "") {
  	cryptoManager->setRandomNumberFilePath((char*)(rnPath.data()));
  } else {
#ifdef WIN32
  	cryptoManager->setRandomNumberFilePath(".\\entropy.dat");
#else
	  cryptoManager->setRandomNumberFilePath("./entropy.dat");
#endif
  }
}

OsmsOpenIPMPMessenger::~OsmsOpenIPMPMessenger() {
  if (osmsMessengerGlobalHandler.GetMutex() == 0) {
    return;
  }
  if (cryptoManager != 0) delete cryptoManager; cryptoManager = 0;
  osmsMessengerGlobalHandler.GetMutex()->Release();
}

/*! \brief  Assign content identifier.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    contentInfo       input, basic content information.
    \param    contentID         output, assigned content identifier.

    \returns  Boolean indicating success or failure.
*/
bool OsmsOpenIPMPMessenger::AssignContentID(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    const std::string& contentInfo, std::string& contentID) {
	osmsMessageRegisterContentAssignIdentifierRequest request;
	request.setMetadataType("DOI");
	request.setMetadataXml((char*)contentInfo.data());

  osmsMessageRegisterContentAssignIdentifierResponse* response = 0;
  if (OsmsAssignContentID(userName, password, hostIP, hostPort, &request, &response) == false) {
    if (response != 0) delete response;
    return false;
  }

	if (strcmp(response->getMetadataType(), "DOI") == 0) {
    contentID = response->getMetadataXml();
    delete response;
    return true;
	} else {
    messengerLogger.UpdateLog("OsmsDRMMessenger::AssignContentID: response contained an unknown metadata type.");
    delete response;
    return false;
	}
}

/*! \brief  Register content encryption key with respect to content identifier.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    key               input, encryption key.
    \param    keyLen            input, encryption key length.
    \param    contentID         input-output, content identifier, possibly
                                updated in the process.

    \returns  Boolean indicating success or failure.
*/
bool OsmsOpenIPMPMessenger::RegisterKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    ByteT* key, UInt32T keyLen, std::string& contentID) {
  UserContext userCtx;
  userCtx.setUserName((char*)userName.data());
  userCtx.setPassword((char*)password.data());
	try	{
		cryptoManager->Login(&userCtx);
	}
	catch (Exception& e) {
		messengerLogger.UpdateLog("OsmsDRMMessenger::RegisterKeyForContent: could not login to local security environment.");
		messengerLogger.UpdateLog(e.getErrorMsg());
		return false;
	}
	OctetString encryptedKey;
	encryptedKey.octets = new unsigned char[userCtx.getRSAKeySize() + 11];
	
	// encrypt with RSA key
	encryptedKey.len = RSA_public_encrypt(keyLen, key, encryptedKey.octets,
    userCtx.getPrivateKey(), RSA_PKCS1_PADDING);
	if(encryptedKey.len < 1) {	// -1 should indicate error...
		messengerLogger.UpdateLog("OsmsDRMMessenger::RegisterKeyForContent: error encrypting content key with user's public key.");
		if (encryptedKey.octets != 0) delete encryptedKey.octets;
    return false;
	}

	ByteArray* encryptedKeyBytes = new ByteArray((char*)encryptedKey.octets, encryptedKey.len);
	char* base64enc_encryptedKeyBytes = RFC1521Base64::encode(encryptedKeyBytes);

	ByteArray* certificate_bytes = new ByteArray((char*)userCtx.getUserCertASN1()->octets,
    userCtx.getUserCertASN1()->len);
	char* base64enc_certificate = RFC1521Base64::encode(certificate_bytes);

	KeyTransport keyTransport;
	keyTransport.set_KeyAlgorithm("http://www.w3.org/2001/04/xmlenc#blowfish128-cfb");
	keyTransport.set_TransportAlgorithm("http://www.w3.org/2001/04/xmlenc#rsa-1_5");
	keyTransport.set_EncKeyValue_base64(base64enc_encryptedKeyBytes);
	keyTransport.set_Certificate_base64(base64enc_certificate);

  delete encryptedKey.octets;
	delete encryptedKeyBytes;
  delete[] base64enc_encryptedKeyBytes;
	delete certificate_bytes;
  delete[] base64enc_certificate;

	char* pEncoded_KeyXml = keyTransport.encode();
  AuxData auxDataOut;
  auxDataOut.set_ToolId(OPENIPMP_TOOLID);
  auxDataOut.set_ProtectedFlag(true);
	char* pEncoded_AuxDataXml = auxDataOut.encode();

	osmsMessageRegisterDigitalItemInstanceRequest request;
	request.setMetadataType("DOI");
	request.setMetadataXml((char*)contentID.data());
	request.setKeyXml(pEncoded_KeyXml);
	request.setAuxDataXml(pEncoded_AuxDataXml);
	free(pEncoded_KeyXml);
	free(pEncoded_AuxDataXml);
	osmsMessageRegisterDigitalItemInstanceResponse* response = 0;

  if (OsmsRegisterKeyForContent(userName, password, hostIP, hostPort, &request,
      &response) == false) {
    if (response != 0) delete response;
    return false;
  }

	DOI* pReturnedDOI = 0;
	DigitalSignature* signature = 0;
	if (strcmp(response->getMetadataType(), "DOI") == 0 ) {
		pReturnedDOI = DOI_Factory::CreateInstance(response->getMetadataXml());
		if (pReturnedDOI == 0) {
  		messengerLogger.UpdateLog("OsmsDRMMessenger::RegisterKeyForContent: could not parse DOI.");
      delete response;
			return false;
		}
	  signature = DigitalSignature_Factory::CreateInstance(response->getSignatureXml());
	  if (signature == 0) {
		  messengerLogger.UpdateLog("OsmsDRMMessenger::RegisterKeyForContent: could not parse signature.");
      delete response;
      delete pReturnedDOI;
		  return false;
	  }
  } else {
    messengerLogger.UpdateLog("OsmsDRMMessenger::RegisterKeyForContent: response contained an unknown metadata type.");
    delete response;
		return false;
	}

	if (VerifySignature(response->getMetadataXml(), signature, &userCtx) == false) {
    messengerLogger.UpdateLog("OsmsDRMMessenger::RegisterKeyForContent: signature verification failed.");
    delete response;
    delete pReturnedDOI;
    delete signature;
		return false;
	}

  delete response;

  IPMP_ContentIdentity* pIPMP_ContentId = new IPMP_ContentIdentity(pReturnedDOI, signature);
  const char* encoded = pIPMP_ContentId->encode();
  contentID = encoded;
  delete pReturnedDOI;
  delete signature;
  delete pIPMP_ContentId;
  free((char*)encoded);

  return true;
}

/*! \brief  Get content encryption key with respect to content identifier.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    key               output, encryption key.
    \param    keyLen            output, encryption key length.
    \param    contentID         input, content identifier.

    \returns  Boolean indicating success or failure.
*/
bool OsmsOpenIPMPMessenger::GetKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    ByteT** key, UInt32T* keyLen, const std::string& contentID) {
  UserContext userCtx;
  userCtx.setUserName((char*)userName.data());
  userCtx.setPassword((char*)password.data());
	try	{
		cryptoManager->Login(&userCtx);
	}
	catch (Exception& e) {
		messengerLogger.UpdateLog("OsmsDRMMessenger::GetKeyForContent: could not login to local security environment.");
		messengerLogger.UpdateLog(e.getErrorMsg());
		return false;
	}

  IPMP_ContentIdentity* pIPMP_ContentId = IPMP_ContentId_Factory::CreateInstance(contentID.data());
  if (pIPMP_ContentId == 0) {
    messengerLogger.UpdateLog("OsmsDRMMessenger::GetKeyForContent: could not create DOI.");
    return false;
  }
	if (pIPMP_ContentId->decode() == false) {
    messengerLogger.UpdateLog("OsmsDRMMessenger::GetKeyForContent: could not decode IPMP content identity.");
    delete pIPMP_ContentId;
    return false;
	}

	if (VerifySignature(pIPMP_ContentId->get_DOI()->get_XML_str(), (DigitalSignature*)
      pIPMP_ContentId->get_DigitalSignature(), &userCtx) == false) {
    messengerLogger.UpdateLog("OsmsDRMMessenger::GetKeyForContent: signature verification error.");
    delete pIPMP_ContentId;
    return false;
	}
	
  OctetString keyBlob;

	if (userCtx.authorize("PLAY", (char*)pIPMP_ContentId->get_ResourceKey(), &keyBlob)
      == false)	{
	  osmsMessageLicenseRequest request;
	  request.setContentId((char*)pIPMP_ContentId->get_ResourceKey());
	  request.setRightsInfo("PLAY");
	  osmsMessageLicenseResponse* response = 0;

    if (OsmsGetKeyForContent(userName, password, hostIP, hostPort, &request, &response) == false) {
      delete pIPMP_ContentId;
      if (response != 0) delete response;
      return false;
    }

		License* newLicense = 0;
		char* dID = 0;
		XMLDocument licenseDoc;
		char* pBuf = response->getLicense();

		if (cryptoManager->decodeLicense(&licenseDoc, pBuf, &dID, &newLicense) == false) {
      messengerLogger.UpdateLog("OsmsDRMMessenger::GetKeyForContent: could not decode license.");
      delete pIPMP_ContentId;
			if (dID != 0) delete dID;
			if (newLicense != 0) delete newLicense;
			return false;
		}

		userCtx.addLicenseToMap(dID, newLicense);
		cryptoManager->storeP12Instance(&userCtx);

		delete dID;
		delete response;

	  if (userCtx.authorize("PLAY", (char*)pIPMP_ContentId->get_ResourceKey(), &keyBlob)
        == false)	{
      delete pIPMP_ContentId;
      return false;
		}
	}

  delete pIPMP_ContentId;

  *key = keyBlob.octets;
  *keyLen = keyBlob.len;

  return true;
}

/*! \brief  Grant license to user for the content identifier.

    \param    userName          input, granter's name.
    \param    password          input, granter's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    contentID         input, content identifier.
    \param    grantee           input, user to which the license is granted.
    \param    licenseType       input, type of the license granted.
    \param    startYear         input, start year for the license.
    \param    startMonth        input, start month for the license.
    \param    startDay          input, start day for the license.
    \param    endYear           input, end year for the license.
    \param    endMonth          input, end month for the license.
    \param    endDay            input, end day for the license.

    \returns  Boolean indicating success or failure.
*/
bool OsmsOpenIPMPMessenger::GrantLicenseForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    const std::string& contentID, const std::string& grantee,
    const std::string& licenseType, const int startYear, const int startMonth,
    const int startDay, const int endYear, const int endMonth, const int endDay) {
  std::string doiID;
  if (GetDOIFromContentID(contentID, doiID) == false) {
		messengerLogger.UpdateLog("OsmsDRMMessenger::GrantLicenseForContent: could not parse DOI from content identifier.");
    return false;
  }

  osmsMessageRightsAuthorizationRequest request;
  request.setContentId((char*)doiID.data());
  request.setUserName((char*)grantee.data());
  Date startDate, endDate;
  startDate.setYear(startYear);
  startDate.setMonth(startMonth);
  startDate.setDay(startDay);
  endDate.setYear(endYear);
  endDate.setMonth(endMonth);
  endDate.setDay(endDay);
  request.setStartDate(&startDate);
  request.setEndDate(&endDate);
  request.setLicenseType((char*)licenseType.data());
  osmsMessageRightsAuthorizationResponse* response = 0;

  if (OsmsGrantLicenseForContent(userName, password, hostIP, hostPort, &request,
      &response) == false) {
    if (response != 0) delete response;
    return false;
  }

  delete response;
  return true;
}

/*! \brief  Verify signature on data.

    \param    data              input, signed data.
    \param    signature         input, signature.
    \param    userCtx           input, user context.

    \returns  Boolean indicating whether signature is valid or not.
*/
bool OsmsOpenIPMPMessenger::VerifySignature(const std::string& data, DigitalSignature*
    signature, UserContext* userCtx) {
	HashContext hashData;
	cryptoManager->init(&hashData, "SHA1");
	hashData.hashUpdate((unsigned char*)data.data(), data.size());
	hashData.hashFinal();

	return (hashData.verifySignature(signature->get_SignatureValue_octets()->octets,
    signature->get_SignatureValue_octets()->len, userCtx->getCaCertChain()));
}

/*! \brief  Get simple DOI identifier from full DOI content ID string.

    \param  contentID       input, full DOI contentID string.
    \param  doi             output, simple DOI identifier.

    \returns  Boolean indicating success or failure.
*/
bool OsmsOpenIPMPMessenger::GetDOIFromContentID(const std::string& contentID,
    std::string& doiID) {
  XMLDocument pIPMP_ContentId;
  if (pIPMP_ContentId.decode(contentID.data(), "IPMP_ContentIdentity") == false) {
    return false;
  }
  HashMap* identifier = pIPMP_ContentId.getDocList("Identifier");
  if (identifier == 0) {
    return false;
  }
  if (identifier->size() == 0) {
    identifier->clear();
    delete identifier;
    return false;
  }
  XMLDocument* node = (XMLDocument*)identifier->first();
  if (node == 0) {
    for (int j = 1; j < identifier->size(); j++) {
      node = (XMLDocument*)identifier->next();
      if (node != 0) delete node;
    }
    identifier->clear();
    delete identifier;
    return false;
  }
  char* identifierType = node->getString("IdentifierType");
  char* identifierValue = node->getString("IdentifierValue");
  if ((identifierType == 0) || (identifierValue == 0)) {
    delete node;
    for (int j = 1; j < identifier->size(); j++) {
      node = (XMLDocument*)identifier->next();
      if (node != 0) delete node;
    }
    identifier->clear();
    delete identifier;
    return false;
  }
  if (strcmp(identifierType, "DOI") == 0) {
    doiID = identifierValue;
    delete[] identifierType;
    delete[] identifierValue;
    delete node;
    for (int j = 1; j < identifier->size(); j++) {
      node = (XMLDocument*)identifier->next();
      if (node != 0) delete node;
    }
    identifier->clear();
    delete identifier;
    return true;
  }
  delete[] identifierType;
  delete[] identifierValue;
  delete node;

  for (int i = 1; i < identifier->size(); i++) {
    node = (XMLDocument*)identifier->next();
    if (node == 0) {
      for (int j = (i + 1); j < identifier->size(); j++) {
        node = (XMLDocument*)identifier->next();
        if (node != 0) delete node;
      }
      identifier->clear();
      delete identifier;
      return false;
    }
    char* identifierType = node->getString("IdentifierType");
    char* identifierValue = node->getString("IdentifierValue");
    if ((identifierType == 0) || (identifierValue == 0)) {
      delete node;
      for (int j = (i + 1); j < identifier->size(); j++) {
        node = (XMLDocument*)identifier->next();
        if (node != 0) delete node;
      }
      identifier->clear();
      delete identifier;
      return false;
    }
    if (strcmp(identifierType, "DOI") == 0) {
      doiID = identifierValue;
      delete[] identifierType;
      delete[] identifierValue;
      delete node;
      for (int j = (i + 1); j < identifier->size(); j++) {
        node = (XMLDocument*)identifier->next();
        if (node != 0) delete node;
      }
      identifier->clear();
      delete identifier;
      return true;
    }
    delete[] identifierType;
    delete[] identifierValue;
    delete node;
  }
  identifier->clear();
  delete identifier;
  return false;
}

} // namespace DRMPlugin
