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

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * @version 1.0
 */

package com.mutable.osms.server.app;

import java.util.Date;
import java.util.Set;
import java.sql.Timestamp;
import java.io.*;
import java.util.*;

import java.security.*;
import java.security.cert.Certificate;
import java.security.interfaces.RSAPublicKey;
import java.security.cert.*;

import com.mutable.osms.common.io.message.*;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.server.db.*;
import com.mutable.io.*;
import com.mutable.io.tools.*;
import com.mutable.osms.server.io.xml.XMLODRLDocument;
import com.mutable.osms.server.io.xml.MPEGRELDocument;
import com.mutable.osms.server.app.ca.*;

/** C. Mollis 9-29-05 Added SPE user auth functions */
import com.sony.spe.cinedrm.webservices.*;

public class osmsRightsManager
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
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger log = null;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsRightsManager(OlLogger logger)
	{
		logDebug("osmsRightsManager","");
		log=logger;
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processRegisterUserRequest(osmsMessageRegisterUserRequest req)
	{
		final String methodName="processRegisterUserRequest";
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
		try
		{
			//----------------
			//validate message
			//----------------
			if(req==null)throw new osmsException(osmsMessageResponseError.UNKNOWN_USER,"req=null");
			if(req.getUserName()==null)throw new osmsException(osmsMessageResponseError.UNKNOWN_USER,"UserName=null");
			if(req.getPassword()==null)throw new osmsException(osmsMessageResponseError.UNKNOWN_USER,"Password=null");
			if(req.getEmailAddress()==null)throw new osmsException(osmsMessageResponseError.UNKNOWN_USER,"EmailAddress=null");

			//----------------
			//get User
			//----------------
			osmsUsers user = db.getUsersByUserName(req.getUserName());
			if(user==null)throw new osmsException(osmsMessageResponseError.UNKNOWN_USER,"User Not found : " +  req.getUserName());

			//------------------
			//call ca issue cert
			//------------------
			IdentityCertIssuanceRequest careq = new IdentityCertIssuanceRequest();
			careq.setEmailAddr(req.getEmailAddress());
			careq.setPassword(req.getPassword());
			careq.setUserName(req.getUserName());
			IdentityCertIssuanceResponse icertrsp = ca.issueIdentityCertificate(careq);

			//----------------
			//validate response
			//----------------
			if(icertrsp==null || icertrsp.getCertificate()==null || icertrsp.getKeyPair()==null || icertrsp.getKeyPair().getPrivate()==null || icertrsp.getUserSecurityStore()==null)
				throw new osmsException(osmsMessageResponseError.SYSTEM_ERROR,"Certificate Response Error: Failed to issue certificate for : " +  req.getUserName());
			if(icertrsp.getCertificate().getPublicKey()==null || ((X509Certificate)icertrsp.getCertificate()).getSerialNumber()==null)
				throw new osmsException(osmsMessageResponseError.SYSTEM_ERROR,"Certificate Error: Failed to issue certificate for : " +  req.getUserName());

			//----------------
			//get algorithm
			//----------------
			osmsAlgorithm osmsAlg = db.getAlgorithmByObjectIdentifier(((X509Certificate)icertrsp.getCertificate()).getSigAlgOID());
			if (osmsAlg==null)throw new osmsException(osmsMessageResponseError.UNKNOWN_ERROR,"could not find ID for AlgOID: " +  ((X509Certificate)icertrsp.getCertificate()).getSigAlgOID());

			//-------------------------
			//Insert Certicate into db
			//-------------------------
			osmsCertificate osmsCert = new osmsCertificate();
			osmsCert.setCertificate(ca.encodeCertificate(icertrsp.getCertificate()));
			osmsCert.setPublicKey(ca.encodePublicKey(icertrsp.getCertificate().getPublicKey()));
			osmsCert.setEncryptedPrivateKey(ca.encryptWithSecretKey(ca.encodePrivateKey( icertrsp.getKeyPair().getPrivate())));
			osmsCert.setCertificateTypeCode("ID");
			osmsCert.setSerialNum(((X509Certificate)icertrsp.getCertificate()).getSerialNumber().toString());
			osmsCert.setVersion(new Integer(((X509Certificate)icertrsp.getCertificate()).getVersion()));
			osmsCert.setAlgorithmId(osmsAlg.getAlgorithmId());
			osmsGlobalObjectManager.getInstance().getDatabase().insertCertificate(osmsCert);

			//------------------------------------------------------------------------------------------------
			//Update user with cert id (and password if password was not established at time user was created)
			//------------------------------------------------------------------------------------------------
			user.setCertificateId(osmsCert.getCertificateId());
			String test = user.getPassword();
			if (user.getPassword()==null) {
				user.setPassword(CryptoTool.base64Encode( CryptoTool.generateMD5Hash(req.getPassword())));
			}
			osmsGlobalObjectManager.getInstance().getDatabase().updateUsers(user);

			//-------------------------
			//Send response
			//-------------------------
			osmsMessageRegisterUserResponse resp = new osmsMessageRegisterUserResponse();
			resp.setUserSecurityStore(CryptoTool.encodeKeyStore(icertrsp.getUserSecurityStore(),req.getPassword()));

			return resp;
		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageRegisterUserResponseError response = new osmsMessageRegisterUserResponseError();
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception e)
		{
			logError(methodName, "",e);
			osmsMessageRegisterUserResponseError response = new osmsMessageRegisterUserResponseError();
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("User Registration Request Failed: Unknown Error");
			return response;
		}
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public byte[] AquireUserKeyStore(osmsUsers loginUser)
	{
		final String methodName="AquireUserKeyStore";
		try
		{
			osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
			CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();

			//Validate parameters
			if(loginUser==null)throw new Exception("User=null");
			if(loginUser.getUserName()==null)throw new Exception("UserName=null");
			if(loginUser.getPassword()==null)throw new Exception("Password=null");

			logDebug(methodName,""+loginUser.getUserName()+" "+loginUser.getPassword());

			//-----------------------------------------------------
			//get the certificate and private Key from the database
			//-----------------------------------------------------
			osmsUsers user = db.getUsersByUserName(loginUser.getUserName());
			if(user==null)throw new Exception("User not found");

			osmsCertificate osmsCert = db.getCertificateByCertificateId(user.getCertificateId());
			if(osmsCert==null || osmsCert.getCertificate()==null|| osmsCert.getEncryptedPrivateKey()==null)throw new Exception("Certificate not found");

			Certificate cert = ca.decodeCertificate(osmsCert.getCertificate());
			PrivateKey privateKey =  ca.decodePrivateKey(ca.decryptWithSecretKey(osmsCert.getEncryptedPrivateKey()));
			if(privateKey==null)throw new Exception("Private key not found");

			//-----------------------------------------------------
			//Rebuild KeyStore
			//-----------------------------------------------------
			KeyStore store =  ca.buildKeyStore(loginUser.getUserName(),  privateKey, cert);
			if(store==null)throw new Exception("Key store not found");

			return CryptoTool.encodeKeyStore(store,loginUser.getPassword());

		}
		catch (Exception ex)
		{
			logError(methodName, "",ex);
		}
		return null;


	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processRightsAuthorizationRequest(osmsMessageRightsAuthorizationRequest message,osmsUsers loginUser)
	{
		final String methodName="processRightsAuthorizationRequest";
		try
		{
			//---------------
			//validate message
			//---------------
			if(message==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message==null");
			logDebug(methodName,new String(message.encode()));
			if(message.getContentId()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message.contentId==null");
			if(message.getUserName()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message.userName==null");
			if(message.getStartDate()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message.startDate==null");
			if(message.getEndDate()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message.endDate==null");
			if(message.getLicenseType()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message.licenseType==null");
			if(!getLicTypes().contains(message.getLicenseType()))throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message.licenseType is " + message.getLicenseType());
			if(message.getLicenseType()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message.licenseType==null");

			if(loginUser==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"loginUser==null");
			if(loginUser.getUserId()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"loginUser.userId==null");

			logDebug(methodName,"contentId="+message.getContentId()+" userId="+message.getUserName()+" ");

			//---------------
			// get item
			//--------------
//			osmsContent item = osmsGlobalObjectManager.getInstance().getDatabase().getContentByContentId(message.getContentId());
			osmsContent item = osmsGlobalObjectManager.getInstance().getDatabase().getContentByPrimaryIdentifierAndIdentifierTypeCode(message.getContentId(),"DOI");
			if(item==null)throw new Exception("Content "+message.getContentId()+"Doesnt Exist!");
			if(item.getRegisteredBy()==null)throw new Exception("Registered By "+message.getContentId()+"Doesnt Exist!");

			//----------------------------------------------------------------------------
			//Validate that loginUser has the rights to issue authorization for this item
			//----------------------------------------------------------------------------
			if(item.getRegisteredBy().intValue()!=loginUser.getUserId().intValue())throw new Exception("User doesn't have the right to issue authorization for this content");

			//-----------------
			// get user from db
			//-----------------
			osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
			osmsUsers assignToUser=db.getUsersByUserName(message.getUserName());
//			if(assignToUser==null)throw new Exception("User "+message.getUserName()+"Doesn't Exist!");
			if(assignToUser==null) logDebug(methodName,"User "+message.getUserName()+"Doesn't Exist; Will need to create");

			//----------------------------------------
			// user does not yet exist, so create one
			//----------------------------------------
			if(assignToUser==null) {
				assignToUser = new osmsUsers();
				assignToUser.setUserName(message.getUserName());
				assignToUser.setOrganizationId(new Integer(1));
				assignToUser.setCertificateId(new Integer(1));
				db.insertUsers(assignToUser);
			}
			
			//-----------------
			// create agreement
			//-----------------
			osmsIpmpAgreement agreement = new osmsIpmpAgreement();
			agreement.setAssignedToUser(assignToUser.getUserId());
			agreement.setRegisteredBy(item.getRegisteredBy());
			agreement.setContentId(item.getContentId());
			agreement.setStartDate(new Timestamp(message.getStartDate().getTime()));
			agreement.setEndDate(new Timestamp(message.getEndDate().getTime()));
			agreement.setLicenseType(message.getLicenseType());
			logDebug(methodName,"startDate="+agreement.getStartDate().toString()+" endDate="+agreement.getEndDate().toString());
			osmsGlobalObjectManager.getInstance().getDatabase().insertIpmpAgreement(agreement);

			//-----------------
			//return response
			//-----------------
			osmsMessageRightsAuthorizationResponse response = new osmsMessageRightsAuthorizationResponse();
			return response;
		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageRightsAuthorizationResponseError response = new osmsMessageRightsAuthorizationResponseError();
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception e)
		{
			logError(methodName, "",e);
			osmsMessageRightsAuthorizationResponseError response = new osmsMessageRightsAuthorizationResponseError();
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("Rights Authorization Failed: "+e.toString());
			return response;
		}
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processRightsAuthorizationArrayRequest(osmsMessageRightsAuthorizationArrayRequest imessage,osmsUsers loginUser)
	{
		// initialization
		final String methodName = "processRightsAuthorizationArrayRequest";
		try {
			String[] grantUsers = imessage.getUserNames();
			
			// loop through all users in the array
			for (int i = 0; i < grantUsers.length; i++)
			{
	
				// grant rights to the user
				osmsMessageRightsAuthorizationRequest smessage = new osmsMessageRightsAuthorizationRequest();
				smessage.setContentId(imessage.getContentId());
				smessage.setUserName(grantUsers[i]);
				smessage.setStartDate(imessage.getStartDate());
				smessage.setEndDate(imessage.getEndDate());
				smessage.setLicenseType(imessage.getLicenseType());
				processRightsAuthorizationRequest(smessage, loginUser);		

			} // for
			//-----------------
			//return response
			//-----------------
			osmsMessageRightsAuthorizationArrayResponse response = new osmsMessageRightsAuthorizationArrayResponse();
			return response;
		} //try
		catch (Exception ex)
		{
			logError(methodName,"",ex);
			osmsMessageRightsAuthorizationArrayResponseError response = new osmsMessageRightsAuthorizationArrayResponseError();
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("Rights Authorization Failed: "+ex.toString());
			return response;
		} // catch
	} // processRightsAuthorizationArrayRequest()
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processLicenseRequest(osmsMessageLicenseRequest message, osmsUsers user)
	{
		final String methodName = "processLicenseRequest";

		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();

		try
		{
			//-------------------------
			//VALIDATE message and user
			//-------------------------
			if(user==null || user.getUserId()==null )throw new Exception("Illegal arguements: user required!");
			if(message==null)throw new Exception("message=null");
			if(message.getContentId()==null)throw new Exception("content identifier required!");
			logDebug(methodName, "for contentID: " + message.getContentId());

			if ( osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration().getSPEAuthUser().equalsIgnoreCase("true") )
			{
				/** C. Mollis 9-29-05  Check SPE Rights */
				AuthenticateLocator authService = new AuthenticateLocator ();
				AuthenticateSoap authCtx = authService.getAuthenticateSoap ();
			
				/** now call auth web service */
				logDebug(methodName, " Attempting to Authenticate user "+ user.getUserName ()
													+ " with password " + user.getClearTextPassword () );
				
				boolean isValid = authCtx.authenicateUser ( 	user.getUserName (), 
																user.getClearTextPassword ()
														);
				
				if ( !isValid )
				{
					throw new osmsException( osmsMessageResponseError.UNKNOWN_USER, "Unable to Authenticate SPE User " + user.getUserName()  );
				}
			}

			
			//------------------------------------------
			//GET AGGREEMENT for user contentIdentifier
			//------------------------------------------
			osmsIpmpAgreement[] agrmnts = db.getIpmpAgreementByAssignedToUserAndDOIIdentifier/*AndPermissionType*/(user.getUserId(),message.getContentId()/*,message.getRightsInfo()*/);
			osmsIpmpAgreement agrmnt=null;
			for (int i = 0; agrmnts!=null && i < agrmnts.length; i++)
			{
				//skip if dates aren't null
				if(agrmnts[i].getStartDate()==null ||agrmnts[i].getEndDate()==null)	continue;

				//check to see if times are valid
				long now  = new Date().getTime();
				long strt = agrmnts[i].getStartDate().getTime();
				long end  = agrmnts[i].getEndDate().getTime();
				if(strt<=now && end>=now)
				{
					agrmnt=agrmnts[i];
				}
			}

			if (agrmnt==null)
			{
				if(agrmnts==null)throw new Exception("No Active Rights!");
				else throw new Exception("Rights Expired!");
			}

			//-------------------------
			//GET DIGITAL_ITEM
			//-------------------------
			osmsDigitalItem digitalItem = db.getDigitalItemByDoiIdentifier(message.getContentId());
			if(digitalItem==null)throw new osmsException(osmsMessageResponseError.DB_ERROR,"Unknown Digital Item!");
			if(digitalItem.getEncryptedKey()==null)throw new osmsException(osmsMessageResponseError.DB_ERROR,"No key for Digital Item!");

			//-------------------------
			//GET LICENSE OR CREATE ONE
			//-------------------------
			osmsIpmpLicense[] licenses = db.getIpmpLicenseByAgreementId/*DigitalItemId*/(agrmnt.getAgreementId()/*digitalItem*/);
			osmsIpmpLicense license=null;
			for (int i = 0; licenses!=null && i < licenses.length; i++)
			{
				if(licenses[i].getDigitalItemId()!=null && licenses[i].getDigitalItemId().intValue()==digitalItem.getDigitalItemId().intValue())
				{
					license = licenses[i];
					break;
				}
			}
			if(license == null)
			{
				//create license
				license = new osmsIpmpLicense();
				license.setAgreementId(agrmnt.getAgreementId());
				license.setDigitalItemId(digitalItem.getDigitalItemId());
				license.setIssuedToUser(user.getUserId());
				license.setLicenseType(agrmnt.getLicenseType());
				db.insertIpmpLicense(license);
			}

			//-------------------------
			//GET CERTIFICATE
			//-------------------------
			osmsCertificate osmsCert = db.getCertificateByCertificateId(user.getCertificateId());
			if(osmsCert==null)throw new Exception("No db Certificate found for this user!");
			if(osmsCert.getCertificate()==null)throw new Exception("No Certificate found for this user!");

			Certificate cert = ca.decodeCertificate(osmsCert.getCertificate());
			if(cert==null)throw new Exception("Failed to decode Certificate!");
			if(cert.getPublicKey()==null)throw new Exception("Failed to get Public Key from Certificate!");

			//-------------------------
			//CONSTRUCT strLicense
			//-------------------------
			String strLicense=null;
			if(license.getLicenseType().equalsIgnoreCase("ODRL"))
			{
				XMLODRLDocument doc = new XMLODRLDocument();
				byte[] encryptedDigitalItemKey = ca.encrypt(ca.decryptWithSecretKey(digitalItem.getEncryptedKey()),cert.getPublicKey());
				if(encryptedDigitalItemKey==null)throw new Exception("Error processing digital item key!");

				doc.build
				(
				license.getLicenseId().toString(),
				message.getContentId(),
				CryptoTool.base64Encode( osmsCert.getCertificate()) ,
				CryptoTool.base64Encode(encryptedDigitalItemKey),
				agrmnt.getStartDate(),
				agrmnt.getEndDate()
				);
				strLicense=doc.encode(false);
			}
			else if(license.getLicenseType().equalsIgnoreCase("MPEGREL"))
			{
				MPEGRELDocument doc = new MPEGRELDocument();
				byte[] encryptedDigitalItemKey = ca.encrypt(ca.decryptWithSecretKey(digitalItem.getEncryptedKey()),cert.getPublicKey());
				if(encryptedDigitalItemKey==null)throw new Exception("Error processing digital item key!");
				RSAPublicKey pubKey=(RSAPublicKey)cert.getPublicKey();
				doc.build
				(
				license.getLicenseId().toString(),
				CryptoTool.base64Encode(pubKey.getModulus().toByteArray()) ,
				CryptoTool.base64Encode(pubKey.getPublicExponent().toByteArray()) ,
				message.getContentId(),
				CryptoTool.base64Encode(osmsCert.getCertificate()) ,
				CryptoTool.base64Encode(encryptedDigitalItemKey),
				agrmnt.getStartDate(),
				agrmnt.getEndDate()
				);
				strLicense=doc.encode(false);
			}
			else
			{
				throw new Exception("Unknow License Type = "+license.getLicenseType());
			}

			//-----------------------------
			//CONSTRUCT AND RETURN RESPONSE
			//-----------------------------
			osmsMessageLicenseResponse rsp = new osmsMessageLicenseResponse();
			rsp.setLicense(strLicense);
			return rsp;

		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageLicenseResponseError response = new osmsMessageLicenseResponseError();
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception ex)
		{
			osmsMessageLicenseResponseError response = new osmsMessageLicenseResponseError();
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("License Request Failed: "+ex.toString());
			logError(methodName, "",ex);
			return response;
		}

	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processQuery(osmsMessageQueryRequest message, osmsUsers loginUser)
	{
		final String methodName="processQuery";
		if(message.getType().equalsIgnoreCase("Users")) return processQueryUsers(message,loginUser);
		if(message.getType().equalsIgnoreCase("Rights")) return processQueryRights(message,loginUser);
		if(message.getType().equalsIgnoreCase("Content")) return processQueryContent(message,loginUser);

		osmsMessageResponseError response = new osmsMessageResponseError(osmsMessage.osmsMESSAGE_QUERY_RESPONSE_ERROR);
		response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
		response.setResponseString("Query Failed: unknown type = "+message.getType());
		return response;
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processQueryUsers(osmsMessageQueryRequest message, osmsUsers loginUser)
	{
		final String methodName="processQueryUsers";
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		try
		{
			if(loginUser.getUserId()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"loginUser.userId==null");
			osmsUsers[] users=db.getUsers();
			osmsMessageQueryResponse retMessage = new osmsMessageQueryResponse();
			String ret="";
			for (int i = 0; users!=null && i < users.length; i++)
			{
//				if(i!=0)ret+="\n";
				ret+=users[i].getUserName();
				ret+="\n";
			}
			retMessage.setHeading("User");
			retMessage.setLength(users==null?0:users.length);
			retMessage.setResults(ret);
			return retMessage;
		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageResponseError response = new osmsMessageResponseError(osmsMessage.osmsMESSAGE_QUERY_RESPONSE_ERROR);
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception ex)
		{
			osmsMessageResponseError response = new osmsMessageResponseError(osmsMessage.osmsMESSAGE_QUERY_RESPONSE_ERROR);
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("Query Users Failed: "+ex.toString());
			logError(methodName, "",ex);
			return response;
		}
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processQueryRights(osmsMessageQueryRequest message, osmsUsers loginUser)
	{
		final String methodName="processQueryRights";
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		try
		{
			if(loginUser.getUserId()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"loginUser.userId==null");


			String ret="";
			osmsMessageQueryResponse retMessage = new osmsMessageQueryResponse();
			osmsIpmpAgreement agreements[]=db.getIpmpAgreementByRegisteredBy(loginUser.getUserId());

			for (int i = 0; agreements!=null && i < agreements.length; i++)
			{
//				if(i!=0)ret+="\n";
				//user,content,AuthDate,StartDate,EndDate,Title
				osmsUsers user=db.getUsersByUserId(agreements[i].getAssignedToUser());
				osmsContent content= db.getContentByContentId(agreements[i].getContentId());
				ret+=
						content.getPrimaryIdentifier()
						+"\t"+content.getPrimaryTitle()
						+"\t"+user.getUserName()
						+"\t"+agreements[i].getStartDate()
						+"\t"+agreements[i].getEndDate()
						+"\t"+agreements[i].getCreatedOn()
						;
				ret+="\n";
			}




			retMessage.setHeading("Content\tTitle\tUser\tStartDate\tEndDate\tAuthDate");
			retMessage.setLength(agreements==null?0:agreements.length);
			retMessage.setResults(ret);
			return retMessage;
		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageResponseError response = new osmsMessageResponseError(osmsMessage.osmsMESSAGE_QUERY_RESPONSE_ERROR);
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception ex)
		{
			osmsMessageResponseError response = new osmsMessageResponseError(osmsMessage.osmsMESSAGE_QUERY_RESPONSE_ERROR);
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("Query Rights Failed: "+ex.toString());
			logError(methodName, "",ex);
			return response;
		}
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage processQueryContent(osmsMessageQueryRequest message, osmsUsers loginUser)
	{
		final String methodName="processQueryRights";
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		try
		{
			if(loginUser.getUserId()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"loginUser.userId==null");
			osmsContent[] contents=db.getContentByRegisteredBy(loginUser.getUserId());
			osmsMessageQueryResponse retMessage = new osmsMessageQueryResponse();
			String ret="";
			for (int i = 0; contents!=null && i < contents.length; i++)
			{
//				if(i!=0)ret+="\n";
				ret+=contents[i].getPrimaryIdentifier()
				+"\t"+contents[i].getPrimaryTitle()
				;
				ret+="\n";
			}
			retMessage.setHeading("Content");
			retMessage.setLength(contents==null?0:contents.length);
			retMessage.setResults(ret);
			return retMessage;
		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageResponseError response = new osmsMessageResponseError(osmsMessage.osmsMESSAGE_QUERY_RESPONSE_ERROR);
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception ex)
		{
			osmsMessageResponseError response = new osmsMessageResponseError(osmsMessage.osmsMESSAGE_QUERY_RESPONSE_ERROR);
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("Query Content Failed: "+ex.toString());
			logError(methodName, "",ex);
			return response;
		}
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static void main(String[] args)
	{
		OlLogger log = new OlLogger();
		try
		{

			log.debug("","START");

			CertificateAuthority ca;
			if(false)
			{
				CAManagerEjbca caManager= new CAManagerEjbca(log);
				caManager.Initialize();

				Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());
				ca = new CertificateAuthority(log);
				ca.Initialize("lib"+File.separator+"mastersecret.ser",caManager);
			}
			else
			{
				osmsRightsManager rm = osmsGlobalObjectManager.getInstance().getRightsManager();
				osmsMessageLicenseRequest req = new osmsMessageLicenseRequest();
				req.setContentId("10.9901/12.i.3");
				req.setRightsInfo("PLAY");
				osmsUsers user = osmsGlobalObjectManager.getInstance().getDatabase().getUsersByUserName("joen");
				rm.processLicenseRequest(req,user);
			}

		}
		catch (Exception ex)
		{
			log.error("","",ex);
		}

	}
	
	public static Set getLicTypes(){
		Set c =  new HashSet();
		c.add("ODRL");
		c.add("MPEGREL");
		return c;
	}
}
