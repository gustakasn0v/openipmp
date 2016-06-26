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

package com.mutable.osms.server.app.service;

import com.mutable.io.OlLogger;
import com.mutable.osms.common.io.message.osmsMessage;
import com.mutable.osms.common.io.message.osmsMessageLicenseResponse;
import com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest;
import com.mutable.osms.common.io.message.osmsMessageUserLoginRequest;
import com.mutable.osms.common.io.message.osmsMessageUserLoginResponseError;
import com.mutable.osms.server.app.osmsEncoderManager;
import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.app.osmsLoginManager;
import com.mutable.osms.server.app.osmsRightsManager;
import com.mutable.osms.server.bo.osmsUsers;
import com.mutable.osms.server.db.osmsDatabase;
import com.mutable.osms.server.ws.OsmsMessageTranslator;
import com.mutable.osms.server.ws.message.OsmsUserLoginFault;
import com.mutable.osms.server.ws.message.OsmsUserLoginRequest;

import java.util.Date;
import java.text.SimpleDateFormat;

/**
 * OpenIPMP Web Service Interface
 *
 */
public class OpenIPMPWS {
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
	// TODO: What should be license type?
	static private String licType = "MPEGREL";


    /**
     * Login the OSMS server with supplied username/pw credentials
     * @param userName string server login name
     * @param passwd string password 
     * @return error code 0 = good, 1 = not so good
     * @throws Exception 
     */
    public int login(String userName, String passwd) {
    	String methodName = "login";
    	
    	osmsGlobalObjectManager global = osmsGlobalObjectManager.getInstance();
    	osmsLoginManager loginManager = global.getLoginManager();
    	osmsDatabase db = global.getDatabase();

    	osmsMessageUserLoginRequest req = new osmsMessageUserLoginRequest();
    	req.setUserName(userName);
    	req.setPassword(passwd);
    	
    	osmsUsers user = null;
    	try{
    		user = db.getUsersByUserName(userName);
    	}catch(Exception e){
    		logError(methodName, "There is no user with username " + userName + " in the database");
    		return 1;
    	}
    	
    	osmsMessage res = loginManager.processLoginRequest(req, user);
    	
    	if (res.getMessageType().intValue() == osmsMessage.osmsMESSAGE_USER_LOGIN_RESPONSE){
    		return 0;
    	}else{
    		logError(methodName, "Login failed. Error message: " + res.toString());
    		return 1;
    	}
    }

    /**
 	 *	Package secure MP4 content using standard parameters (as opposed to MPEG-REL)
 	 *	@param agentUserName (required) string server login username for the Job Queue monitor agent user
 	 *	@param agentPassword (required) string password for the Job Queue monitor agent user
  	 *	@param sourceFileURL (required) string The URL of the source file being dropped into the Hotfolder
  	 *	@param destinationFileURL (required) string The URL of the destination Hotfolder for the resulting packaged content file
 	 *	@param contentOwnerAppID (required) string A unique identifier for the sending application.
	 *	@param contentOwnerUserID (required) string The CineSuite user ID of the user requesting the job.
 	 *	@param transactionID (optional) string transactionID A string representing the job number local job number.  This string will be returned upon completion (or error) of the DRM job
	 *	@param validityStartDate (conditional) string The first date on which the protected content will be playable. (Note: although listed as conditional, this parameter will be required for the pilot). Date format is yyyy-MM-dd.
	 *	@param validityEndDate (conditional) string The last date on which the protected content will be playable. (Note: although listed as conditional, this parameter will be required for the pilot).  Date format is yyyy-MM-dd.
	 *	@param validityDays (conditional) int The number of days that the protected content will remain playable after the first time the license is acquired. (Note: although listed as conditional, this parameter will not be supported for the pilot, and will produce an error or be ignored).
	 *	@param validityPlaycount (conditional) int The number of times that user can play the protected content under a given license. (Note: although listed as conditional, this parameter will not be supported for the pilot, and will produce an error or be ignored).
	 *	@param grantUsers[] (required) string[] An array of cineVIEW usernames of the users who will be granted entitlements for playing the protected content.
	 *	@returns error code 0 = good, 1 = not so good.
     */
    public int packageSecureContentWithParams (
						String agentUserName,
						String agentPassword,
						String sourceFileURL, 
						String destinationFileURL,
						String contentOwnerAppId,
						String contentOwnerUserId,
						String transactionID,
						String validityStartDate,
						String validityEndDate,
						int validityDays,
						int validityPlaycount,
						String[] grantUsers
					)
	{
    	osmsGlobalObjectManager global = osmsGlobalObjectManager.getInstance();
    	osmsEncoderManager encoder = global.getEncoderManager();
    	osmsRightsManager rights = global.getRightsManager();
    	log = global.getLogger();

    	String methodName = "packageSecureContentWithParamsForSingleUser";
    	
    	logDebug(methodName, "Start encoding...");
    	try {
    		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
    		Date beginDate = dateFormat.parse(validityStartDate);
    		Date endDate = dateFormat.parse(validityEndDate);

			encoder.encode(agentUserName, agentPassword, sourceFileURL, destinationFileURL, licType, beginDate, endDate, grantUsers);
		} catch (Exception e) {
			logError(methodName, "Encoding of input file failed with the exception: ", e);
			return 1;
		}
    	logDebug(methodName, "Input file successfully protected.");
    	
    	return 0;
    }

    /**
 	 *	Package secure MP4 content for a single user, using standard parameters (as opposed to MPEG-REL). This method is mostly for early testing, avoiding the use of arrays.
 	 *	@param agentUserName (required) string server login username for the Job Queue monitor agent user
 	 *	@param agentPassword (required) string password for the Job Queue monitor agent user
  	 *	@param sourceFileURL (required) string The URL of the source file being dropped into the Hotfolder
  	 *	@param destinationFileURL (required) string The URL of the destination Hotfolder for the resulting packaged content file
 	 *	@param contentOwnerAppID (required) string A unique identifier for the sending application.
	 *	@param contentOwnerUserID (required) string The CineSuite user ID of the user requesting the job.
 	 *	@param transactionID (optional) string transactionID A string representing the job number local job number.  This string will be returned upon completion (or error) of the DRM job
	 *	@param validityStartDate (conditional) string The first date on which the protected content will be playable. (Note: although listed as conditional, this parameter will be required for the pilot).
	 *	@param validityEndDate (conditional) string The last date on which the protected content will be playable. (Note: although listed as conditional, this parameter will be required for the pilot).
	 *	@param validityDays (conditional) int The number of days that the protected content will remain playable after the first time the license is acquired. (Note: although listed as conditional, this parameter will not be supported for the pilot, and will produce an error or be ignored).
	 *	@param validityPlaycount (conditional) int The number of times that user can play the protected content under a given license. (Note: although listed as conditional, this parameter will not be supported for the pilot, and will produce an error or be ignored).
	 *	@param grantUser (required) string An array of cineVIEW usernames of the users who will be granted entitlements for playing the protected content.
	 *	@returns error code 0 = good, 1 = not so good.
     */
    public int packageSecureContentWithParamsForSingleUser (
						String agentUserName,
						String agentPassword,
						String sourceFileURL, 
						String destinationFileURL,
						String contentOwnerAppId,
						String contentOwnerUserId,
						String transactionID,
						String validityStartDate,
						String validityEndDate,
						int validityDays,
						int validityPlaycount,
						String grantUser
					)
    {
    	String[] grantUsers = new String[1];
    	grantUsers[0] = grantUser;
    	return packageSecureContentWithParams(agentUserName, agentPassword, sourceFileURL, destinationFileURL, contentOwnerAppId, contentOwnerUserId, transactionID, validityStartDate, validityEndDate, validityDays, validityPlaycount, grantUsers);
    } 

    /**
 	 *	Package secure MP4 content using MPEG-REL notation.
 	 *	@param agentUserName (required) string server login username for the Job Queue monitor agent user
 	 *	@param agentPassword (required) string password for the Job Queue monitor agent user
 	 *	@param contentOwnerAppID (required) string A unique identifier for the sending application.
	 *	@param contentOwnerUserID (required) string The CineSuite user ID of the user requesting the job.
 	 *	@param transactionID (optional) string transactionID A string representing the job number local job number.  This string will be returned upon completion (or error) of the DRM job
	 *	@param mpegREL (required) string This should contain MPEG-REL XML fragment that conforms to the MPEG-REL standard as well as SPE-DRM MPEG-REL extensions. See OpenIPMP documentation for more information.
	 *	@returns error code 0 = good, 1 = not so good.
     */
    public int packageSecureContentWithMPEG_REL (
						String agentUserName,
						String agentPassword,
						String contentOwnerAppId,
						String contentOwnerUserId,
						String transactionID,
						String mpegREL
					 ) { return 0; } 

    /**
     * Let the world know that we are still alive...
     */
    public void ping() { }

    

    /**
     * Logs in the user by its username and password.
     * 
     * @param userName
     * @param password
     * @return
     * @throws OsmsUserLoginFault
     */
	protected static osmsUsers getUser(String userName, String password) throws OsmsUserLoginFault {
		osmsMessageUserLoginRequest req = new osmsMessageUserLoginRequest();
		req.setUserName(userName);
		req.setPassword(password);

		osmsUsers user = osmsGlobalObjectManager.getInstance().getLoginManager().getUser(req.getUserName());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getLoginManager().processLoginRequest(req, user);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageUserLoginResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageUserLoginResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageUserLoginResponse"))
			return user;
		else
			return null;
	}    
}
