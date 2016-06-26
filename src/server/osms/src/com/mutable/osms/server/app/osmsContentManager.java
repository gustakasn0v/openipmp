/*
 * LICENSE AND COPYRIGHT INFORMATION:
 *
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
 *
 */


package com.mutable.osms.server.app;

import com.mutable.io.OlLogger;
import com.mutable.io.tools.*;

import com.mutable.osms.server.app.ca.*;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.server.db.*;
import com.mutable.osms.common.io.*;
import com.mutable.osms.common.io.message.*;
import com.mutable.osms.server.io.xml.*;

import java.security.cert.Certificate;
import java.security.PublicKey;
import java.security.PrivateKey;

import java.io.*;

/**
* osmsContentManager is the openIPMP class that coordinates the validation
* and execution of Content and Digital Item registration use cases.  The class
* manages the persistence and retrieval of attributes to and from the database and interfaces
* with the Certificate Authority for cryptographic related operations.  The specific use cases
* managed by this class include:
* <ul>
*   <li>Registering content and assigning a unique identifier
*   <li>Registering content that has been assigned an identifier from an outside system
*   <li>Registering a digital item instance (along with a track key) for distribution
*   <li>Retrieving a key for a previously registered digital item
* </ul>
* <p>
* @version      1.1
* @since      	1.0
*/

public class osmsContentManager
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(log!=null)log.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(log!=null)log.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(log!=null)log.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(log!=null)log.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(log!=null)log.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
    * Class constructor which creates a new osmsContentManager object.  The constructor sets the objects private members, log and configuration.
    */
    public osmsContentManager()
	{
		log=osmsGlobalObjectManager.getInstance().getLogger();
		m_Config = osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
    * The OlLogger object used for logging purposes.
    */
	OlLogger log = null;

	/**
    * The configuration object used to get server configuration options.
    */
	osmsServerConfiguration m_Config = null;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* Returns the DOI Master Identifier Prefix.
	*
	* @return   the prefix for the doi master identifier.
	*/
	private String assignDoiMasterIdentifierPrefix()
	{
		return osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration().getDoiMasterPrefix();
	}

	/**
	* Returns the DOI Instance Identifier Prefix.
	*
	* @return   the prefix for the doi instance identifier.
	*/
	private String assignDoiInstanceIdentifierPrefix()
	{
		return osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration().getDoiInstancePrefix();
	}

	/**
	* Validates the attributes of a content business object in the context of a register content assign identifier request.
	*
	* @param    content     a content business object representing the content to be registered
	* @return   null if business object is valid or an osmsMessageRegisterContentAssignIdentifierResponseError object
	* indicating the reason the business object failed validation
	*/
	private osmsMessageRegisterContentAssignIdentifierResponseError validateContentForAssignIdentifierRequest(osmsContent content)
	{
		osmsMessageResponseError err;

		if(content.getIdentifierTypeCode()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier Type could not be determined"));

		if(content.getPrimaryArtist()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Artist could not be determined"));

		if(content.getPrimaryTitle()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title could not be determined"));

		osmsDoi doi = content.getDoi();
		if(doi==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "DOI could not be determined"));

		if(doi.getStructuralType()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Structural Type could not be determined"));

		if(doi.getPrimaryAgentName()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Agent could not be determined"));

		if(doi.getPrimaryAgentType()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Agent Type could not be determined"));

		if(doi.getPrimaryAgentRole()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Agent Role could not be determined"));

		if(doi.getPrimaryTitleText()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title could not be determined"));

		if(doi.getPrimaryTitleLanguage()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title Language could not be determined"));

		//If we got this far, the content object is valid so return null
		return null;
	}

	/**
	* Validates the attributes of a content business object in the context of a register content existing identifier request.
	*
	* @param    content     a content business object representing the content to be registered
	* @return   null if business object is valid or an osmsMessageRegisterContentExistingIdentifierResponseError object
	* indicating the reason the business object failed validation
	*/
	private osmsMessageRegisterContentExistingIdentifierResponseError validateContentForExistingIdentifierRequest(osmsContent content)
	{
		if(content.getPrimaryIdentifier()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier must be supplied"));

		if(content.getIdentifierTypeCode()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier Type could not be determined"));

		if(content.getPrimaryArtist()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Artist could not be determined"));

		if(content.getPrimaryTitle()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title could not be determined"));

		osmsDoi doi = content.getDoi();
		if(doi==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "DOI could not be determined"));

		if(doi.getDoiIdentifier()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier (DOI) must be supplied"));

		if(doi.getStructuralType()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Structural Type could not be determined"));

		if(doi.getPrimaryAgentName()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Agent could not be determined"));

		if(doi.getPrimaryAgentType()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Agent Type could not be determined"));

		if(doi.getPrimaryAgentRole()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Agent Role could not be determined"));

		if(doi.getPrimaryTitleText()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title could not be determined"));

		if(doi.getPrimaryTitleLanguage()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title Language could not be determined"));

		//If we got this far, the content object is valid so return null
		return null;
	}

	/**
	* Validates the attributes of a digital item business object in the context of a register digital item instance request.
	*
	* @param    dItem   a ditial item instance business object representing the digital item to be registered
	* @return   null if business object is valid or an osmsMessageRegisterDigitalItemInstanceResponseError object
	* indicating the reason the business object failed validation
	*/
	private osmsMessageRegisterDigitalItemInstanceResponseError validateDigitalItemForDigitalItemInstanceRequest(osmsDigitalItem dItem)
	{
		if(dItem==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier (1) must be supplied"));

		osmsDoi doi = dItem.getDoi();
		if(doi==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier (2) must be supplied"));

		if(doi.getMasterDoi()==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier (3) must be supplied"));

		if(doi.getMasterDoi().getDoiIdentifier()==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Identifier (4) must be supplied"));

		if(doi.getPrimaryTitleText()==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title could not be determined"));

		if(doi.getPrimaryTitleLanguage()==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Title Language could not be determined"));

		if(doi.getStructuralType()==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Structural Type could not be determined"));

		if(doi.getDoiAgents()==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Primary Agents could not be determined"));

		//If we got this far, the digital item is valid so return null
		return null;
	}
	/**
	* Manages the processing of a Register Content Existing DOI request:
	* <ul>
	*   <li> Validates the required elements of the message
	*   <li> Manages the decoding of the xml message attributes into Content and DOI related business objects
	*   <li> Validates the attributes of the business objects
	*   <li> Validates that the DOI is not already registered
	*   <li> Persists content and related objects to the database
	*   <li> Constructs, populates and returns the appropriate response message
	* </ul>
	* <p>
	*
	* @param    request     a content registration existing identifier request message object
	* @param    user        the user object for the user making the request
	* @return   an osmsMessage object indicating the status of the processing:
	* <ul>
	*   <li> Success - osmsMessageRegisterContentExistingIdentifierResponse
	*   <li> Failure - osmsMessageRegisterContentExistingIdentifierResponseError
	* </ul>
	*/
	private osmsMessage processRegisterContentExistingDoiRequest(osmsMessageRegisterContentExistingIdentifierRequest request, osmsUsers user)
	{
		String methodName = "processRegisterContentExistingDoiRequest";
		logDebug(methodName, "Beginning processing of existing DOI for user: "+" "+user.getUserId()+" "+user.getUserName());

		//Parse DOI Xml and convert to Content business object
		XMLDOIDocument xmlDOI = new XMLDOIDocument(request.getMetadataXml());
		osmsContent content = xmlDOI.convertRegisterContentRequestToBusinessObject();
		if(content==null || content.getDoi()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.DOI_PARSING_ERROR, "DOI Metadata could not be parsed"));

		//Set user on content
		content.setRegisteredByUser(user);

		//Validate Content Request Business Object
		osmsMessageRegisterContentExistingIdentifierResponse response = new osmsMessageRegisterContentExistingIdentifierResponse();
		osmsMessageResponseError error = validateContentForExistingIdentifierRequest(content);
		if(error!=null)
			return error;

		//Existing Identifier, save to the database and construct/return response message
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		try
		{
			//Make sure DOI does not already exist in DB
			osmsDoi doi = null;
			doi = db.getDoiByDoiIdentifier(content.getDoi().getDoiIdentifier());
			if(doi!=null)
				return(new osmsMessageRegisterContentExistingIdentifierResponseError
						(osmsMessageResponseError.DOI_ALREADY_REGISTERED, "DOI: " + content.getDoi().getDoiIdentifier() + " is already registered with the system"));

			//Create empty contentDoi business object (DB layer will populate with proper ids)
			osmsContentDoi contentDoi = new osmsContentDoi();
			content.setContentDoi(contentDoi);

			//Get encoded DOI XML and set on DOI object for persistence
			String contentXml = xmlDOI.encode();
		    if(contentXml==null)
				return(new osmsMessageRegisterContentExistingIdentifierResponseError
					    (osmsMessageResponseError.SYSTEM_ERROR, "Could not encode Content Existing DOI document on request"));

			//Make sure encoded document does not exceed maximum db column size (4000 bytes in Oracle)
			if(contentXml.length()>4000)
			{
				contentXml = null;  //To avoid sql error on insert
				logInfo(methodName, "XML for: "+content.getPrimaryIdentifier()+" exceeded allowed length and could not be saved to the database");
			}
			content.getDoi().setXmlString(contentXml);

		    //Save to DB
			db.insertContentDoiFull(content);

			//Construct and return response message
			response.setResponseString("OK");
		}
		catch(Exception e)
		{
			logError(methodName, "Encountered exception: "+e.toString());
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.SYSTEM_ERROR, "Encountered fatal error processing Register Content Existing DOI request"));
		}
		return response;
	}
	/**
	* Manages the processing of a Register Content Existing GRID request:
	* <ul>
	*   <li> Validates the required elements of the message
	*   <li> Manages the decoding of the xml message attributes into Content and GRID related business objects
	*   <li> Validates the attributes of the business objects
	*   <li> Validates that the GRID is not already registered
	*   <li> Persists content and related objects to the database
	*   <li> Constructs, populates and returns the appropriate response message
	* </ul>
	* <p>
	*
	* @param    request     a content registration existing identifier request message object
	* @param    user        the user object for the user making the request
	* @return   an osmsMessage object indicating the status of the processing:
	* <ul>
	*   <li> Success - osmsMessageRegisterContentExistingIdentifierResponse
	*   <li> Failure - osmsMessageRegisterContentExistingIdentifierResponseError
	* </ul>
	*/
	private osmsMessage processRegisterContentExistingGridRequest(osmsMessageRegisterContentExistingIdentifierRequest request, osmsUsers user)
	{
		String methodName = "processRegisterContentExistingGridRequest";
		logDebug(methodName, "Beginning processing of existing GRID for user: "+" "+user.getUserId()+" "+user.getUserName());

		//Parse GRID Xml and convert to Content business object
		XMLGRIDDocument xmlGRID = new XMLGRIDDocument(request.getMetadataXml());
		osmsContent content = xmlGRID.convertRegisterContentRequestToBusinessObject();
		if(content==null || content.getGrid()==null)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.GRID_PARSING_ERROR, "GRID Metadata could not be parsed"));

		//Set user on content
		content.setRegisteredByUser(user);

		//Validate Content Request Business Object
		osmsMessageRegisterContentExistingIdentifierResponse response = new osmsMessageRegisterContentExistingIdentifierResponse();
		osmsMessageResponseError error = validateContentForExistingIdentifierRequest(content);
		if(error!=null)
			return error;

		//Existing Identifier, save to the database and construct/return response message
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		try
		{
			//Make sure GRID does not already exist in DB
			osmsGrid grid = null;
			grid = db.getGridByGrid(content.getGrid().getGrid());
			if(grid!=null)
				return(new osmsMessageRegisterContentExistingIdentifierResponseError
						(osmsMessageResponseError.GRID_ALREADY_REGISTERED, "GRID: " + content.getGrid().getGrid() + " is already registered with the system"));

			//Create empty contentGrid business object (DB layer will populate with proper ids)
			osmsContentGrid contentGrid = new osmsContentGrid();
			content.setContentGrid(contentGrid);

			//Get encoded DOI XML and set on GRID object for persistence
			String contentXml = xmlGRID.encode();
		    if(contentXml==null)
				return(new osmsMessageRegisterContentExistingIdentifierResponseError
					    (osmsMessageResponseError.SYSTEM_ERROR, "Could not encode Content Existing GRID document on request"));

			//Make sure encoded document does not exceed maximum db column size (4000 bytes in Oracle)
			if(contentXml.length()>4000)
			{
				contentXml = null;  //To avoid sql error on insert
				logInfo(methodName, "XML for: "+content.getPrimaryIdentifier()+" exceeded allowed length and could not be saved to the database");
			}
			content.getGrid().setXmlString(contentXml);

		    //Save to DB
			db.insertContentGridFull(content);

			//Construct and return response message
			response.setResponseString("OK");
		}
		catch(Exception e)
		{
			logError(methodName, "Encountered exception: "+e.toString());
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.SYSTEM_ERROR, "Encountered fatal error processing Register Content Existing GRID request"));
		}
		return response;
	}
	/**
	* Updates a doi business object with the Assertor Authority values (based on the server's constants) and with
	* the Assertor Registrant values if they weren't supplied (based on the user's information).
	*
	* @param    doi     a doi business object
	* @param    user    the user object for the user making the request
	*/
	private void buildAssertor(osmsDoi doi, osmsUsers user)
	{
		doi.setAssertAuthName(m_Config.getDoiAssertorAuthName());
		doi.setAssertAuthType(m_Config.getDoiAssertorAuthType());

		//If Assertor Registrant info was not provide
		if(!StringTool.isStringValid(doi.getAssertRegName()))
		{
			doi.setAssertRegType(m_Config.getDoiRegPersonType());
			if(user.getFirstName()!=null && user.getLastName()!=null)
				doi.setAssertRegName(user.getFirstName() + " " + user.getLastName());
			else
				doi.setAssertRegName(user.getUserName());
		}
		//Set Assertor Registrant Identifier Info
		doi.setAssertIdentifierType("PUBKEY");
		doi.setAssertIdentifier("UNKNOWN"); //Default if Public Key is not available
		if(user!=null && user.getOsmsCertificate()!=null && user.getOsmsCertificate().getPublicKey()!=null)
		{
			String pubKey = CryptoTool.base64Encode(user.getOsmsCertificate().getPublicKey());
			if(StringTool.isStringValid(pubKey))
			    //doi.setAssertIdentifier(pubKey)
				;
		}
	}

	/**
	* Decodes a Public Key from a byte[] and encrypts a series of bytes with
	* the decode Public key.  Returns the encrypted bytes as a base64 encoded string.
	*
	* @param    bytesToEncrypt  the bytes to be encrypted
	* @param    publicKey  the asn1 encoded public key bytes
	* @return   the encrypted bytes as a base64 encoded string (NOTE: returns null if an error is encountered during processing)
	*/
	private String encryptWithPublicKeyBytesAndBase64Encode(byte[] bytesToEncrypt, PublicKey publicKey)
	{
		String methodName = "encryptWithPublicKeyBytesAndBase64Encode";
		if(bytesToEncrypt==null)
		{
			logError(methodName,"Bytes null on encrypt with Public Key request");
			return null;
		}
		if(publicKey==null)
		{
			logError(methodName,"Public Key null on encrypt with Public Key request");
			return null;
		}

		//Decode Public Key from byte[]
		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();

		//Attempt to encrypt bytes with Public Key
		byte[] encryptedBytes = null;
		try
		{
		    encryptedBytes = ca.encrypt(bytesToEncrypt,publicKey);
		}
		catch (Exception e)
		{
			logError(methodName,"Exception encountered trying to encrypt with Public Key: " + e.toString());
			return null;
		}
		if(encryptedBytes==null)
		{
			logError(methodName,"Encryption with Public Key failed");
			return null;
		}
		return(CryptoTool.base64Encode(encryptedBytes));
	}

	/**
	* Decrypts a series of bytes with the server's secret key and returns the decrypted bytes.
	*
	* @param    bytesToDecrypt  the bytes to be decrypted
	* @return   the decrypted bytes as a byte[] (NOTE: returns null if an error is encountered during processing)
	*/
	private byte[] decryptWithSecretKey(byte[] bytesToDecrypt)
	{
		String methodName = "decryptWithSecretKey";
		if(bytesToDecrypt==null)
		{
			logError(methodName,"Bytes null on decrypt request");
			return null;
		}

		//Attempt to decrypt bytes
		byte[] decryptedBytes = null;
		try
		{
		    decryptedBytes = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority().decryptWithSecretKey(bytesToDecrypt);
		}
		catch (Exception e)
		{
			logError(methodName,"Exception encountered trying to decrypt string: " + e.toString());
			return null;
		}

		if(decryptedBytes==null)
		{
			logError(methodName,"Decryption of key failed");
			return null;
		}

		return decryptedBytes;
	}

	/**
	* Decrypts a series of bytes with the server's secret key and returns the decrypted bytes as a base64 encoded string.
	*
	* @param    bytesToDecrypt  the bytes to be decrypted
	* @return   the decrypted bytes as a base64 Encoded String (NOTE: returns null if an error is encountered during processing)
	*/
	private String decryptWithSecretKeyAndBase64Encode(byte[] bytesToDecrypt)
	{
		String methodName = "decryptWithSecretKeyAndBase64Encode";
		if(bytesToDecrypt==null)
		{
			logError(methodName,"Bytes null on decrypt request");
			return null;
		}

		//Attempt to decrypt bytes
		byte[] decryptedBytes = this.decryptWithSecretKey(bytesToDecrypt);

		if(decryptedBytes==null)
			return null;
		else
			return(CryptoTool.base64Encode(decryptedBytes));
	}

	/**
	* Encrypts a base64 encoded string with the server's secret key.
	*
	* @param    stringToEncrypt  the base64 Encoded String to be encrypted
	* @return   the encrypted bytes as a byte[] (NOTE: returns null if an error is encountered during processing)
	*/
	private byte[] base64DecodeAndEncryptWithSecretKey(String stringToEncrypt)
	{
		String methodName = "base64DecodeAndEncryptWithSecretKey";
		if(stringToEncrypt==null)
		{
			logError(methodName,"String was null on encrypt request");
			return null;
		}

		//Base64 decode
		byte[] bytes = null;
		try
		{
			bytes = CryptoTool.base64Decode(stringToEncrypt);
			if(bytes==null || bytes.length==0)
			{
				logError(methodName,"Base64 Decoding failed during encrypt request");
				return null;
			}
		}
		catch (Exception e)
		{
			logError(methodName,"Exception encountered trying to base64 Decode: " + e.toString());
			return null;
		}

		byte[] encryptedBytes = null;
		try
		{
		    encryptedBytes = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority().encryptWithSecretKey(bytes);
		}
		catch (Exception e)
		{
			logError(methodName,"Exception encountered trying to encrypt string: " + e.toString());
			return null;
		}

		if(encryptedBytes==null)
		{
			logError(methodName,"String encryption failed");
			return null;
		}
		return encryptedBytes;
	}

	/**
	* Generates a signature for a series of bytes and returns the values resulting from the signing operations
	* in the form of an osmsDigitalSignature object.
	*
	* @param    bytesToSign  the bytes that are to be signed
	* @return   an osmsDigitalSignature object
	* @throws Exception
	*/
	private osmsDigitalSignature generateSignature(byte[] bytesToSign) throws Exception
	{
		String methodName = "generateSignature";

		//Create new osmsDigitalSignature object
		osmsDigitalSignature sig = new osmsDigitalSignature();
		sig.setBytesToSign(bytesToSign);

		//Hash the bytes of the xml doi and set the resulting hash on the digital sig bo
		byte[] digest = CryptoTool.generateSHA1Hash(sig.getBytesToSign());
		if(digest==null)
			throw new Exception("Error generating hash of DOI");

		String digestB64E = CryptoTool.base64Encode(digest);
		sig.setDigestValue(digestB64E);

		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
		if(ca==null)
		{
		    logError(methodName,"Certificate Authority was not available");
			return null;
		}

		//Have the ca sign the original bytes, Base64 encode the signed digest and set result on the digital sig bo
		byte[] signedDigest = ca.generateSignedSHA1Digest(sig.getBytesToSign());
		String signedDigestB64E = CryptoTool.base64Encode(signedDigest);
		sig.setSignatureValue(signedDigestB64E);

		//Retrieve ca certificate, base64 encode and set on digital sig bo
		byte[] caCert = ca.encodeCertificate(ca.getCaCertificate());
		String caCertB64E = CryptoTool.base64Encode(caCert);
		sig.setSignerCertificate(caCertB64E);

		return sig;
	}

	/**
	* Prepares an encrypted track key for Database storage (base64 decodes encrypted key, decrypts key, encrypts with server's private key).
	* Decrypted track Key bytes are set on osmsEncryptedKey object passed into method.
	*
	* @param    encKey      the encrypted key object
	* @param    osmsCert    the osms certificate of the recipient
	* @returns  a boolean indicating if the key was successfully set on the osmsEncryptedKey object and prepared for db storage.
	*/
	private boolean prepareTrackKeyForDbStorage(osmsEncryptedKey encKey, osmsCertificate osmsCert)
	{
		String methodName = "prepareTrackKeyForDbStorage";

		//Validate parameters
		if(encKey==null || encKey.getEncryptedKey()==null)
		{
			logError(methodName,"Encrypted Key object was null");
			return false;
		}
		if(osmsCert==null || osmsCert.getCertificate()==null)
		{
		    logError(methodName,"Certificate was null");
			return false;
		}
		if(osmsCert.getEncryptedPrivateKey()==null)
		{
		    logError(methodName,"User's Private Key from DB was null");
			return false;
		}

		//TODO: Validate certificates from db and message match

		//Decode encrypted key
		byte[] encryptedKeyBytes = null;
		try
		{
			encryptedKeyBytes = CryptoTool.base64Decode(encKey.getEncryptedKey());
			if(encryptedKeyBytes==null)
			{
				logError(methodName,"Error decoding encrypted key");
				return false;
			}
		}
		catch (Exception e)
		{
		    logError(methodName,"Exception encountered decoding encrypted key: " + e.toString());
			return false;
		}

		//Get reference to CA
		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
		if(ca==null)
		{
		    logError(methodName,"Certificate Authority was not available");
			return false;
		}

		//Decrypt user's Private Key
		byte[] privateKeyBytes = null;
		try
		{
			privateKeyBytes = ca.decryptWithSecretKey(osmsCert.getEncryptedPrivateKey());
			if(privateKeyBytes==null)
			{
				logError(methodName,"Error decrypting user's Private Key");
				return false;
			}
		}
		catch (Exception e)
		{
		    logError(methodName,"Exception encountered decrypting user's Private Key: " + e.toString());
			return false;
		}

		//Decode decrypted private key bytes into Private Key
		PrivateKey privateKey = null;
		try
		{
			privateKey=ca.decodePrivateKey(privateKeyBytes);
			if(privateKey==null)
			{
				logError(methodName,"Error decoding user's Private Key");
				return false;
			}
		}
		catch (Exception e)
		{
		    logError(methodName,"Exception encountered decoding user's Private Key: " + e.toString());
			return false;
		}

		//Decrypt track key from encrypted key object with user's private key
		byte[] decryptedKeyBytes = null;
		try
		{
			decryptedKeyBytes=ca.decrypt(encryptedKeyBytes,privateKey);
			if(decryptedKeyBytes==null)
			{
				logError(methodName,"Error decrypting Track Key with user's Private Key");
				return false;
			}
		}
		catch (Exception e)
		{
		    logError(methodName,"Exception encountered decrypting Track Key with user's Private Key: " + e.toString());
			return false;
		}

		//Encrypt key with server's secret key
		byte[] protectedKeyBytes = null;
		try
		{
			protectedKeyBytes=ca.encryptWithSecretKey(decryptedKeyBytes);
			if(protectedKeyBytes==null)
			{
				logError(methodName,"Error encrypting Track Key with server's secret key");
				return false;
			}
		}
		catch (Exception e)
		{
		    logError(methodName,"Exception encountered encrypting Track Key with server's secret key: " + e.toString());
			return false;
		}

		//Set on Encrypted Key object and return
		encKey.setProtectedKey(protectedKeyBytes);
		return true;
	}

	/**
	* Prepares an encrypted track key for transport (decrypts key, encrypts with user's public key, etc...) and returns an osmsEncryptedKey object.
	*
	* @param    keyBytes  the encrypted key bytes that are to be prepared for transport
	* @param    osmsCert  the osms certificate of the recipient
	* @return   an osmsEncryptedKey object
	*/
	private osmsEncryptedKey prepareTrackKeyForTransport(byte[] keyBytes, osmsCertificate osmsCert)
	{
		String methodName = "prepareTrackKeyForTransport";

		//Validate parameters
		if(keyBytes==null)
		{
			logError(methodName,"Key was null");
			return null;
		}
		if(osmsCert==null || osmsCert.getCertificate()==null)
		{
		    logError(methodName,"Certificate was null");
			return null;
		}
		if(osmsCert.getPublicKey()==null)
		{
			logError(methodName,"Public Key was null");
			return null;
		}

		//Get User's Certificate and Public Key from osmsCertificate
		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
		if(ca==null)
		{
		    logError(methodName,"Certificate Authority was not available");
			return null;
		}

		//Decode certificate bytes into a Certificate object...this must be a java.security.cert.Certificate
		Certificate cert = null;
		try
		{
		    cert = ca.decodeCertificate(osmsCert.getCertificate());
			if(cert==null)
			{
				logError(methodName,"Certificate could not be decoded");
				return null;
			}
		}
		catch (Exception e)
		{
		    logError(methodName,"Exception encountered decoding Certificate: " + e.toString());
			return null;
		}

		//Be careful..."cert" must be a java.security.cert.Certificate
		byte[] signerCert = null;
		try
		{
			signerCert = ca.encodeCertificate(cert);
			if(signerCert==null)
			{
				logError(methodName,"Certificate could not be encoded");
				return null;
			}
		}
		catch (Exception e)
		{
		    logError(methodName,"Exception encountered encoding Certificate: " + e.toString());
			return null;
		}

		//Decrypt track key
		byte[] decryptedKeyBytes = decryptWithSecretKey(keyBytes);
		if(decryptedKeyBytes==null)
		{
			logError(methodName,"Error decrypting bytes with secret key");
		    return null;
		}

		//Encrypt track key
		String encryptedKey = this.encryptWithPublicKeyBytesAndBase64Encode(decryptedKeyBytes,cert.getPublicKey());
		if(encryptedKey==null)
		{
			logError(methodName,"Error encrypting key bytes with public key");
		    return null;
		}

		logDebug(methodName, "Base64 Encoded key after decryption, re-encryption is: " + encryptedKey);

		//Prepare encrypted key object
		osmsEncryptedKey encKey = new osmsEncryptedKey();
		encKey.setEncryptedKey(encryptedKey);
		encKey.setSignerCertificate(CryptoTool.base64Encode(signerCert));
		encKey.setSignerOsmsCertificate(osmsCert);
		return encKey;
	}

	/**
	* Validates that a base64Encoded Certificate bytes match the Certificate bytes from an osmsCertificate.
	*
	* @param    base64EncodedCert   the base64 encoded Certificate as a String
	* @param    osmsCert            the osms certificate business object to compare
	* @return   a boolean indicating if the Certificates match (true: certificates match, false: certificates do NOT match)
	*/
	private boolean validateCertificates(String base64EncodedCert, osmsCertificate osmsCert)
	{
		String methodName = "validateCertificates";

		try
		{
			//Validate parameters
			if(base64EncodedCert==null)
			{
				logError(methodName,"Base 64 Encoded Certificate was null");
				return false;
			}
			if(osmsCert==null || osmsCert.getCertificate()==null)
			{
				logError(methodName,"Certificate was null");
				return false;
			}

			//Get reference to CA
			CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
			if(ca==null)
			{
				logError(methodName,"Certificate Authority was not available");
				return false;
			}

			//convert parameter 1 into a byte[]
			byte[] encodedCert=CryptoTool.base64Decode(base64EncodedCert);
			if(encodedCert==null)
			{
				logError(methodName,"Base 64 Certificate could not be decoded");
				return false;
			}

			//convert parameter 2 into a byte[]
			byte[] userCert = osmsCert.getCertificate();
			if(userCert==null)
			{
				logError(methodName,"Certificate was not found");
				return false;
			}

			//compare parameter 1 & 2
			if(encodedCert.length!=userCert.length)
			{
				logError(methodName,"Certificates do NOT match... lengths are unequal");
				return false;
			}

			for (int i = 0; i < encodedCert.length; i++)
			{
				if(encodedCert[i]!=userCert[i])
				{
					logError(methodName,"Certificates do NOT match... ");
					return false;
				}
			}
			return true;
		}
		catch (Exception ex)
		{
			logError(methodName,"",ex);
			return false;
		}
	}

	/**
	* Determines if a ca signed digest checks out against a series of bytes
	* (i.e., the bytes where used to generate the original signed digest).
	*
	* @param    bytesToVerify   the bytes to verify the signature against
	* (i.e., the bytes that were used as input into the original signature operation)
	* @param    signature       the signature bytes
	* @return   true if the signature is valid for the bytesToVerify and false if it is not valid
	* @throws Exception
	*/
	private boolean verifySignature(byte[] bytesToVerify, byte[] signature) throws Exception
	{
		String methodName = "verifySignature";

		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
		boolean isGoodSignature = ca.verifyBytesAndSignedSHA1Digest(bytesToVerify, signature);
		logDebug(methodName, "Signature "+((isGoodSignature)?"IS AUTHENTIC":"DOES NOT MATCH"));

		return isGoodSignature;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* Manages the processing of a Register Content Assign Identifier request:
	* <ul>
	*   <li> Validates the required elements of the message
	*   <li> Manages the decoding of the xml message attributes into a content business object
	*   <li> Validates the attributes of the business object
	*   <li> Assigns a new DOI and persists content and doi related objects to the database
	*   <li> Constructs, populates and returns the appropriate response message
	* </ul>
	* <p>
	*
	* @param    request     a content registration request message object
	* @param    user        the user object for the user making the request
	* @return   an osmsMessage object indicating the status of the processing:
	* <ul>
	*   <li> Success - osmsMessageRegisterContentAssignIdentifierResponse
	*   <li> Failure - osmsMessageRegisterContentAssignIdentifierResponseError
	* </ul>
	*/
	public osmsMessage processRegisterContentAssignIdentifierRequest(osmsMessageRegisterContentAssignIdentifierRequest request, osmsUsers user)
	{
		String methodName = "processRegisterContentAssignIdentifierRequest";
		logDebug(methodName, "Beginning processing of assign identifier for user: "+" "+user.getUserId()+" "+user.getUserName());
		osmsMessageRegisterContentAssignIdentifierResponseError err=null;

		if(!StringTool.isStringValid(request.getMetadataType()))
			return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Metadata Type must be supplied"));

		if(!StringTool.isStringValid(request.getMetadataXml()))
			return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Metadata XML must be supplied"));

		if(!request.getMetadataType().equalsIgnoreCase(m_Config.getDoiCode()))
			return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.UNSUPPORTED_CONTENT_METADATA_SCHEME, "Unsupported Metadata scheme, must use DOI scheme"));

		if(user==null || user.getUserId().intValue()==0)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.UNKNOWN_USER, "User must be logged in to make request"));

		//Parse DOI Xml and convert to Content business object
		XMLDOIDocument xmlDOI = new XMLDOIDocument(request.getMetadataXml());
		System.out.println(request.getMetadataXml());
		osmsContent content = xmlDOI.convertRegisterContentRequestToBusinessObject();
		if(content==null || content.getDoi()==null)
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.DOI_PARSING_ERROR, "DOI Metadata could not be parsed"));

		//Set user on content
		content.setRegisteredByUser(user);

		//Build Assertor
		//Get User Certificate...for Assertor information
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		if(user.getOsmsCertificate()==null && user.getCertificateId()!=null && user.getCertificateId().intValue()!=0)
		{
			try
			{
				user.setOsmsCertificate(db.getCertificateByCertificateId(user.getCertificateId()));
			}
			catch(Exception e)
			{
				logError(methodName, "Encountered exception attempting to build Assertor: "+e.toString());
				return(new osmsMessageRegisterContentAssignIdentifierResponseError
						(osmsMessageResponseError.SYSTEM_ERROR, "Encountered fatal error processing Register Content Assign Identifier request"));
			}
		}
		buildAssertor(content.getDoi(),user);

		//Validate Content Request Business Object
		osmsMessageRegisterContentAssignIdentifierResponse response = new osmsMessageRegisterContentAssignIdentifierResponse();
		osmsMessageRegisterContentAssignIdentifierResponseError error = validateContentForAssignIdentifierRequest(content);
		if(error!=null)
			return error;

		//Assign Identifier, save to the database and construct/return response message
		try
		{
			Integer seq = db.assignDoiIdentifierSequenceByType(m_Config.getDoiMasterSuffixTable());
			if(seq.intValue()==0)
				return(new osmsMessageRegisterContentAssignIdentifierResponseError
					    (osmsMessageResponseError.DB_ERROR, "Failed to assign DOI Identifier"));

			content.setPrimaryIdentifier(this.assignDoiMasterIdentifierPrefix()+seq.intValue());
			content.getDoi().setDoiIdentifier(content.getPrimaryIdentifier());

			//Generate response DOI XML and set on DOI object for persistence
			String contentXml = xmlDOI.encodeRegisterContentResponse(content);
		    if(contentXml==null)
				return(new osmsMessageRegisterContentAssignIdentifierResponseError
					    (osmsMessageResponseError.SYSTEM_ERROR, "Could not encode Content Assign Identifier document"));

			//Make sure encoded document does not exceed maximum db column size (4000 bytes in Oracle)
			if(contentXml.length()>4000)
			{
				contentXml = null;  //To avoid sql error on insert
				logInfo(methodName, "XML for: "+content.getPrimaryIdentifier()+" exceeded allowed length and could not be saved to the database");
			}
			content.getDoi().setXmlString(contentXml);

		    //Save to DB
			db.insertContentDoiFull(content);

			//Construct and return response message
			response.setMetadataType(m_Config.getDoiCode());
			response.setMetadataXml(xmlDOI.encode());
		}
		catch(Exception e)
		{
			logError(methodName, "",e);
		    return(new osmsMessageRegisterContentAssignIdentifierResponseError
				    (osmsMessageResponseError.SYSTEM_ERROR, "Encountered fatal error processing Register Content Assign Identifier request"));
		}
		return response;
	}

	/**
	* Manages the processing of a Register Content Existing Identifier request:
	* <ul>
	*   <li> Validates the required elements of the message
	*   <li> Manages the decoding of the xml message attributes into the appropriate content business objects
	*   <li> Validates the attributes of the business objects
	*   <li> Validates that the DOI or GRID is not already registered
	*   <li> Persists content and related objects to the database
	*   <li> Constructs, populates and returns the appropriate response message
	* </ul>
	* <p>
	*
	* @param    request     a content registration existing identifier request message object
	* @param    user        the user object for the user making the request
	* @return   an osmsMessage object indicating the status of the processing:
	* <ul>
	*   <li> Success - osmsMessageRegisterContentExistingIdentifierResponse
	*   <li> Failure - osmsMessageRegisterContentExistingIdentifierResponseError
	* </ul>
	*/
	public osmsMessage processRegisterContentExistingIdentifierRequest(osmsMessageRegisterContentExistingIdentifierRequest request, osmsUsers user)
	{
		String methodName = "processRegisterContentExistingIdentifierRequest";
		logDebug(methodName, "Beginning processing of existing identifier for user: "+" "+user.getUserId()+" "+user.getUserName());

		if(!StringTool.isStringValid(request.getMetadataType()))
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Metadata Type must be supplied"));

		if(!StringTool.isStringValid(request.getMetadataXml()))
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Metadata XML must be supplied"));

		if(!request.getMetadataType().equalsIgnoreCase(m_Config.getDoiCode()) || !request.getMetadataType().equalsIgnoreCase(m_Config.getGridCode()))
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.UNSUPPORTED_CONTENT_METADATA_SCHEME, "Unsupported Metadata scheme, must use DOI or GRID scheme"));

		if(user==null || user.getUserId().intValue()==0)
		    return(new osmsMessageRegisterContentExistingIdentifierResponseError
				    (osmsMessageResponseError.UNKNOWN_USER, "User must be logged in to make request"));


		//Determine if we're dealing with a DOI or a GRID and call appropriate method to process
		if(request.getMetadataType().equalsIgnoreCase(m_Config.getDoiCode()))
		    return processRegisterContentExistingDoiRequest(request,user);
		else
		    return processRegisterContentExistingGridRequest(request,user);
	}

	/**
	* Manages the processing of a Register Digital Item Instance request:
	* <ul>
	*   <li> Validates the required elements of the message
	*   <li> Manages the decoding of the xml message attributes into a content business object
	*   <li> Validates the attributes of the business object
	*   <li> Validates that the Master DOI is registered as Content with the system
	*   <li> Encrypts the Digital Item key accompanying the request and prepares for db storage
	*   <li> Assigns a new DOI and persists digital item and doi related objects to the database
	*   <li> Constructs, populates and returns the appropriate response message
	* </ul>
	* <p>
	*
	* @param    request     a digital item instance request message object
	* @param    user        the user object for the user making the request
	* @return   an osmsMessage object indicating the status of the processing:
	* <ul>
	*   <li> Success - osmsMessageRegisterDigitalItemInstanceResponse
	*   <li> Failure - osmsMessageRegisterDigitalItemInstanceResponseError
	* </ul>
	*/
	public osmsMessage processRegisterDigitalItemInstanceRequest(osmsMessageRegisterDigitalItemInstanceRequest request, osmsUsers user)
	{
		String methodName = "processRegisterDigitalItemInstanceRequest";
		logDebug(methodName, "Beginning processing of registering digital item instance for user: "+" "+user.getUserId()+" "+user.getUserName());

		if(!StringTool.isStringValid(request.getMetadataType()))
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Metadata Type must be supplied"));

		if(!StringTool.isStringValid(request.getMetadataXml()))
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Metadata XML must be supplied"));

		if(!StringTool.isStringValid(request.getAuxDataXml()))
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Auxillary Data XML must be supplied"));

		if(!request.getMetadataType().equalsIgnoreCase(m_Config.getDoiCode()))
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.UNSUPPORTED_CONTENT_METADATA_SCHEME, "Unsupported Metadata scheme, must use DOI scheme"));

		if(user==null || user.getUserId().intValue()==0)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.UNKNOWN_USER, "User must be logged in to make request"));

		//Parse DOI Xml and convert to Content business object
		XMLDOIDocument xmlDOI = new XMLDOIDocument(request.getMetadataXml());
		osmsDigitalItem dItem = xmlDOI.convertRegisterDigitalItemRequestToBusinessObject();

		if(dItem == null || dItem.getDoi()==null || dItem.getDoi().getMasterDoi()==null)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.DOI_PARSING_ERROR, "DOI Metadata could not be parsed"));

		//Parse Auxillary Xml and convert to AuxData business object
		XMLAuxDataDocument xmlAuxData = new XMLAuxDataDocument(request.getAuxDataXml());
		osmsAuxData aux = xmlAuxData.convertAuxDataToBusinessObject();

		//Validate Aux Data
		if(aux == null || aux.getToolIdentifier()==null || aux.getToolIdentifier().intValue()==0)
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.DOI_PARSING_ERROR, "Auxillary Data could not be parsed"));

		//Validate Key Data if conent is protected
		if(aux.isProtected() && !StringTool.isStringValid(request.getKeyXml()))
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Key XML must be supplied when content is to be protected"));

		//Set Auxillary Data on digital item
		dItem.setToolIdentifier(aux.getToolIdentifier());
		dItem.setRightsHostUrl(m_Config.getRightsHostUrl());
		dItem.setRightsHostPort(m_Config.getRightsHostPort());
		dItem.setIsProtectedFlag(aux.isProtected()?"Y":"N");

		//Build Aux Data for response
		aux.setRightsHostUrl(m_Config.getRightsHostUrl());
		aux.setRightsHostPort(m_Config.getRightsHostPort());

		//Set user on digital item
		dItem.setRegisteredByUser(user);

		//Build Assertor
		//Get User Certificate
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		if(user.getOsmsCertificate()==null && user.getCertificateId()!=null && user.getCertificateId().intValue()!=0)
		{
			try
			{
				user.setOsmsCertificate(db.getCertificateByCertificateId(user.getCertificateId()));
			}
			catch(Exception e)
			{
				logError(methodName, "Encountered exception attempting to build Assertor: "+e.toString());
				return(new osmsMessageRegisterContentAssignIdentifierResponseError
						(osmsMessageResponseError.SYSTEM_ERROR, "Encountered fatal error processing Register Content Assign Identifier request"));
			}
		}
		buildAssertor(dItem.getDoi(),user);

		//Validate Digital Item Request Business Object
		osmsMessageRegisterDigitalItemInstanceResponse response = new osmsMessageRegisterDigitalItemInstanceResponse();
		osmsMessageRegisterDigitalItemInstanceResponseError error = validateDigitalItemForDigitalItemInstanceRequest(dItem);

		if(error!=null)
			return error;

		//Assign Identifier, save to the database and construct/return response message
		try
		{
			//Process Key and set on Digital Item
			byte[] encryptedKey = null;
			Integer encryptionKeyId = new Integer(0);
		    Integer encryptionKeySize = new Integer(0);

			if(aux.isProtected())
			{
				logDebug(methodName, "Key on request is: "+request.getKeyXml());

				//Check user's certificate...required when content is protected
				if(user.getOsmsCertificate()==null)
					return(new osmsMessageRegisterDigitalItemInstanceResponseError
							(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered retrieving user's Certificate"));

				//Create Key Transport document object from KeyXml on request
				XMLEncryptedKeyDocument keyDoc = new XMLEncryptedKeyDocument(request.getKeyXml());
				if(keyDoc==null)
					return(new osmsMessageRegisterDigitalItemInstanceResponseError
							(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered retrieving Encrypted Key"));

				//Convert Key Transport document object into business object
				osmsEncryptedKey encKey = keyDoc.convertEncryptedKeyXmlToBusinessObject();
				if(encKey==null)
					return(new osmsMessageRegisterDigitalItemInstanceResponseError
							(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered decoding key transport xml for track key"));

				//Validate that osmsCertificate of registering user match Certificate on request
				if(encKey.getSignerCertificate()==null)
					return(new osmsMessageRegisterDigitalItemInstanceResponseError
							(osmsMessageResponseError.SYSTEM_ERROR, "Signer Certifcate must be supplied"));

				if(!validateCertificates(encKey.getSignerCertificate(),user.getOsmsCertificate()))
					return(new osmsMessageRegisterDigitalItemInstanceResponseError
							(osmsMessageResponseError.SYSTEM_ERROR, "Certificate of Registering User and Certificate from request do not match"));

				//Prepare Key for storage
				if(!prepareTrackKeyForDbStorage(encKey,user.getOsmsCertificate()))
					return(new osmsMessageRegisterDigitalItemInstanceResponseError
							(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered preparing track key for db storage"));

				//Make sure key was set properly
				if(encKey.getProtectedKey()==null)
					return(new osmsMessageRegisterDigitalItemInstanceResponseError
							(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered preparing track key for db storage!"));

				encryptedKey = encKey.getProtectedKey();
				encryptionKeyId = new Integer(1); //TODO: Need a better way of referencing master secret key
				encryptionKeySize = osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration().getSymmetricKeySize();
			}

			dItem.setEncryptedKey(encryptedKey);
			dItem.setEncryptionKeyId(encryptionKeyId);
		    dItem.setKeyLength(encryptionKeySize);

			//Make sure Master DOI exists in DB and is registered as a Master DOI (i.e., Content)
			osmsDoi masterDoi = null;
			masterDoi = db.getDoiByDoiIdentifier(dItem.getDoi().getMasterDoi().getDoiIdentifier());
			if(masterDoi==null)
				return(new osmsMessageRegisterDigitalItemInstanceResponseError
				        (osmsMessageResponseError.DOI_NOT_FOUND, "Master DOI must be previously registered with the system: "+dItem.getDoi().getMasterDoi().getDoiIdentifier()));

			dItem.getDoi().setMasterDoi(masterDoi);

			//Make sure Master DOI is registered as Content
			String doiIdentifier = masterDoi.getDoiIdentifier();
			osmsContent content = db.getContentByPrimaryIdentifierAndIdentifierTypeCode(doiIdentifier, m_Config.getDoiCode());
			if(content==null)
				return(new osmsMessageRegisterDigitalItemInstanceResponseError
				        (osmsMessageResponseError.DOI_NOT_REGISTERED_AS_CONTENT, "Master DOI must be previously registered as Content with the system: "+dItem.getDoi().getMasterDoi().getDoiIdentifier()));

			if(content.getRegisteredBy()==null || content.getRegisteredBy().intValue()!=user.getUserId().intValue())
				return(new osmsMessageRegisterDigitalItemInstanceResponseError
						(osmsMessageResponseError.NOT_AUTHORIZED, "Master DOI was registered by a different user"));

			dItem.setContent(content);

			Integer seq = db.assignDoiIdentifierSequenceByType(m_Config.getDoiInstanceSuffixTable());
			if(seq.intValue()==0)
				return(new osmsMessageRegisterDigitalItemInstanceResponseError
						(osmsMessageResponseError.DB_ERROR, "Failed to assign DOI Instance Identifier"));

			dItem.getDoi().setDoiIdentifier(this.assignDoiInstanceIdentifierPrefix()+seq.intValue());

			//Generate response DOI XML and set on DOI object for persistence
			String itemXml = xmlDOI.encodeRegisterDigitalItemResponse(dItem);
		    if(itemXml==null)
				return(new osmsMessageRegisterDigitalItemInstanceResponseError
					    (osmsMessageResponseError.SYSTEM_ERROR, "Could not encode Digital Item Instance document"));

			//Make sure encoded document does not exceed maximum db column size (4000 bytes in Oracle)
			if(itemXml.length()>4000)
			{
				itemXml = null;  //To avoid sql error on insert
				logInfo(methodName, "XML for: "+dItem.getDoi().getDoiIdentifier()+" exceeded allowed length and could not be saved to the database");
			}
			//Set response DOI XML on DOI object for persistence
			dItem.getDoi().setXmlString(itemXml);

			//Process signature for DOI
		    String xmlDoiString = xmlDOI.encode(false);
			osmsDigitalSignature sig = generateSignature(xmlDoiString.getBytes());
		    if(sig==null)
				return(new osmsMessageRegisterDigitalItemInstanceResponseError
						(osmsMessageResponseError.DB_ERROR, "Error encountered signing DOI, signature was null"));

			//Build XMLDigitalSignatureDocument (from template) and populate with data from signature object
			XMLDigitalSignatureDocument xmlSigDoc = new XMLDigitalSignatureDocument(m_Config.getOpenIpmpTemplateSignatureXml());
			String xmlSigString = xmlSigDoc.encodeDigitalSignatureResponse(sig);
		    if(xmlSigString==null)
				return(new osmsMessageRegisterDigitalItemInstanceResponseError
						(osmsMessageResponseError.DB_ERROR, "Error encountered signing DOI, encode could not generate signature xml"));

			//Set relevant doi attributes for db persistence

		    //Save to DB
			db.insertDigitalItemFull(dItem);

			//Construct and return response message
			response.setMetadataType(m_Config.getDoiCode());
			response.setMetadataXml(xmlDoiString);
			response.setAuxDataXml(xmlAuxData.encodeAuxDataResponse(aux));
			response.setSignatureXml(xmlSigString);
		}
		catch(Exception e)
		{
			logError(methodName, "Encountered exception: "+e.toString());
		    return(new osmsMessageRegisterDigitalItemInstanceResponseError
				    (osmsMessageResponseError.SYSTEM_ERROR, "Encountered fatal error processing Digital Signature request"));
		}
		return response;
	}

	/**
	* Manages the processing of a Get Content Key request:
	* <ul>
	*   <li> Validates the required elements of the message
	*   <li> Validates that the DOI is registered as a Digital Item with the system
	*   <li> Validates that the user requesting the key is the registered user and that the content was protected
	*   <li> Retrieves the key from the db, decrypts and base64 encodes it for return
	*   <li> Constructs, populates and returns the appropriate response message
	* </ul>
	* <p>
	*
	* @param    request     a get content key request message object
	* @param    user        the user object for the user making the request
	* @return   an osmsMessage object indicating the status of the processing:
	* <ul>
	*   <li> Success - osmsMessageGetContentKeyResponse
	*   <li> Failure - osmsMessageGetContentKeyResponseError
	* </ul>
	*/
	public osmsMessage processGetContentKeyRequest(osmsMessageGetContentKeyRequest request, osmsUsers user)
	{
		String methodName = "processGetContentKeyRequest";
		logDebug(methodName, "Beginning processing of retrieving content key for user: "+" "+user.getUserId()+" "+user.getUserName());
		logDebug(methodName, "Digital Item Instance Id is: "+request.getDigitalItemInstanceId()!=null?request.getDigitalItemInstanceId():null);

		if(!StringTool.isStringValid(request.getMetadataType()))
		    return(new osmsMessageGetContentKeyResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "Metadata Type must be supplied"));

		if(!StringTool.isStringValid(request.getDigitalItemInstanceId()))
		    return(new osmsMessageGetContentKeyResponseError
				    (osmsMessageResponseError.INCOMPLETE_REQUEST, "DOI Instance Identifier must be supplied"));

		if(!request.getMetadataType().equalsIgnoreCase(m_Config.getDoiCode()))
		    return(new osmsMessageGetContentKeyResponseError
				    (osmsMessageResponseError.UNSUPPORTED_CONTENT_METADATA_SCHEME, "Unsupported Metadata scheme, must use DOI scheme"));

		if(user==null || user.getUserId().intValue()==0)
		    return(new osmsMessageGetContentKeyResponseError
				    (osmsMessageResponseError.UNKNOWN_USER, "User must be logged in to make request"));

		//Create response message
		osmsMessageGetContentKeyResponse response = new osmsMessageGetContentKeyResponse();

		//Retrieve Digital Item and validate that the user requesting the key registered the digital item in the first place
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		try
		{
			osmsDigitalItem dItem = null;
			dItem = db.getDigitalItemByDoiIdentifier(request.getDigitalItemInstanceId());
			if(dItem==null)
				return(new osmsMessageGetContentKeyResponseError
				        (osmsMessageResponseError.DOI_NOT_FOUND, "Instance DOI is not registered with the system: "+request.getDigitalItemInstanceId()));

			if(user.getUserId().intValue()!=dItem.getRegisteredBy().intValue())
				return(new osmsMessageGetContentKeyResponseError
						(osmsMessageResponseError.NOT_AUTHORIZED, "Instance DOI was registered by a different user"));

		    //Assume content is protected if flag was not set during registration
			if(dItem.getIsProtectedFlag()==null)
				dItem.setIsProtectedFlag("Y");

			if(dItem.getIsProtectedFlag().equalsIgnoreCase("Y") && dItem.getEncryptedKey()==null)
				return(new osmsMessageGetContentKeyResponseError
						(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered retrieving content key for protected content"));

			//Build Aux Data for response
			osmsAuxData aux = new osmsAuxData();
			aux.setRightsHostUrl(m_Config.getRightsHostUrl());
			aux.setRightsHostPort(m_Config.getRightsHostPort());
			aux.setToolIdentifier(dItem.getToolIdentifier());
			aux.setIsProtected(dItem.getIsProtectedFlag().equalsIgnoreCase("N")?false:true);

			XMLAuxDataDocument auxDoc = new XMLAuxDataDocument(m_Config.getOpenIpmpTemplateAuxDataXml());
			auxDoc.isFromTemplate(true);
			response.setAuxDataXml(auxDoc.encodeAuxDataResponse(aux));

			//Content was registered without protection
			if(!dItem.getIsProtectedFlag().equalsIgnoreCase("Y"))
			{
				response.setKeyXml(null);
				return response;
			}

		    //Get the user's certificate
			osmsCertificate cert = db.getCertificateByCertificateId(user.getCertificateId());
			if(cert==null)
				return(new osmsMessageGetContentKeyResponseError
						(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered retrieving user's Certificate"));

			//Prepare track key for transport
			osmsEncryptedKey encKey = this.prepareTrackKeyForTransport(dItem.getEncryptedKey(),cert);
			if(encKey==null)
				return(new osmsMessageGetContentKeyResponseError
						(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered preparing track key for transport"));

			//Create new Encrypted Key Transport document for Encrypted Key
			XMLEncryptedKeyDocument keyDoc = new XMLEncryptedKeyDocument(m_Config.getOpenIpmpTemplateEncryptedKeyXml());
			if(keyDoc==null)
				return(new osmsMessageGetContentKeyResponseError
						(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered retrieving Encrypted Key Template"));

			//Encode Encrypted Key Transport Xml
			String keyXml = keyDoc.encodeEncryptedKeyResponse(encKey);
			if(keyXml==null)
				return(new osmsMessageGetContentKeyResponseError
						(osmsMessageResponseError.SYSTEM_ERROR, "Error encountered encoding Encrypted Key Xml"));

			//Populate Encrypted Key Transport Xml on response message object
			response.setKeyXml(keyXml);
		}
		catch(Exception e)
		{
			logError(methodName, "Encountered exception: "+e.toString());
		    return(new osmsMessageGetContentKeyResponseError
				    (osmsMessageResponseError.SYSTEM_ERROR, "Encountered fatal error processing Get Content Key request"));
		}
		return response;
	}
	public static void main(String[] args)
	{
		osmsGlobalObjectManager gom = osmsGlobalObjectManager.getInstance();
		try
		{

			//load request
			osmsMessageRegisterContentAssignIdentifierRequest request= new osmsMessageRegisterContentAssignIdentifierRequest();
			request.setMessageType(new Integer(104));
			request.setMetadataType("DOI");
			request.setMetadataXml(
//					"<MetadataXml type=\"char[]\">"+
					"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"+
					"<doi:KernelMetadata xmlns:doi=\"http://www.doi.org/\">"+
					"<DOI>TBD</DOI>"+
					"<Identifiers>"+
					"   <Identifier>"+
					"      <IdentifierType>ISWC</IdentifierType>"+
					"      <IdentifierValue>T-034.524.680</IdentifierValue>"+
					"   </Identifier>"+
					"</Identifiers>"+
					"<Titles><Title>"+
					"   <TitleValue>just a friend</TitleValue>"+
					"   <Language>en</Language>"+
					"</Title></Titles>"+
					"<StructuralType>visual</StructuralType>"+
					"<Modes>"+
					"   <Mode>visual</Mode>"+
					"</Modes>"+
					"<PrimaryAgents>"+
					"   <Agent sequence=\"1\"><Name>"+
					"      <NameType>Person</NameType>"+
					"      <NameValue>mario</NameValue>"+
					"   </Name><Roles>"+
					"<Role>Artist</Role>"+
					"   </Roles></Agent>"+
					"   <Agent sequence=\"2\"><Name>"+
					"      <NameType>Person</NameType>"+
					"      <NameValue>Freddy</NameValue>"+
					"   </Name><Roles>"+
					"      <Role>Directory</Role>"+
					"   </Roles></Agent>"+
					"</PrimaryAgents>"+
					"<Assertor>"+
					"   <Registrant>"+
					"      <Name>"+
					"         <NameType>Person</NameType>"+
					"         <NameValue>Persons Name Here</NameValue>"+
					"      </Name>"+
					"      <Identifier>"+
					"         <IdentifierType>PublisherCode</IdentifierType>"+
					"         <IdentifierValue>9901</IdentifierValue>"+
					"      </Identifier>"+
					"   </Registrant>"+
					"   <Authority>"+
					"      <Name>"+
					"         <NameType>Organization</NameType>"+
					"         <NameValue>Mutable</NameValue>"+
					"      </Name>"+
					"   </Authority>"+
					"</Assertor>"+
					"</doi:KernelMetadata>"+
//					""+
//					"</MetadataXml>"+
					""
			);

			//load user
			osmsUsers user = gom.getDatabase().getUsersByUserId(new Integer(2));

			osmsMessage response = gom.getContentManager().processRegisterContentAssignIdentifierRequest(request,user);
			gom.getLogger().debug("",new  String(response.encode()));

		}
		catch (Exception ex)
		{
			gom.getLogger().error("","",ex);
		}

	}

}