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
 * <p>Description:  </p>
 * @version 1.0
 */


package com.mutable.osmsOnline.server.app;

import java.util.*;

import com.mutable.osms.server.app.*;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.server.db.osmsDatabase;
import com.mutable.io.OlLogger;
import com.mutable.osms.common.io.message.*;
import com.mutable.osms.server.app.ca.*;

public class ProcessMessageRegisterUserRequest {

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+" : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger m_logger= osmsGlobalObjectManager.getInstance().getLogger();
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
    public String process(osmsMessageRegisterUserRequest req,osmsUsers a_user)
	{
		String methodName="process";
		logDebug(methodName,req.getUserName()+" "+" "+req.getEmailAddress()+" "+req.getPassword()+" "+req.getPasswordConfirm());

		//VALIDATE PARAMETERS
		if(req.getUserName() == null || req.getUserName().trim().equals(""))
		{
			return "UserName is required!";
		}
		if(req.getEmailAddress() == null || req.getEmailAddress().trim().equals(""))
		{
			return "EmailAddress is required!";
		}
		if(req.getPassword() == null || req.getPassword().trim().equals(""))
		{
			return "Password is required!";
		}
		if(req.getPasswordConfirm() == null || req.getPasswordConfirm().trim().equals(""))
		{
			return "Confirm Password is required!";
		}
		//check to see if the user exists already with a null password
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		osmsUsers testforuser;
		try {
			testforuser = db.getUsersByUserName(req.getUserName());
		}
		catch (Exception e)
		{
			logDebug(methodName, e.getMessage());
			return(e.getMessage());
		}
		if(testforuser!=null)
		{
			if (testforuser.getPassword()==null) {
				logDebug(methodName, "User exists and password is null; will move on to register user and set password.");
			}
			else {
				logDebug(methodName, "User exists and password is not null; this user is already created and registered.");
				return("A user is already regisrered with this username.");
			}
		}
		else
		{
			osmsMessageCreateUserRequest cuReq = new osmsMessageCreateUserRequest();
			//Validate that password and password 2 are the same
			if(!req.getPassword().equals(req.getPasswordConfirm())) return "Password misMatch";
			cuReq.setUserName(req.getUserName());
//			cuReq.setPassword(req.getPassword());
			cuReq.setEmailAddress(req.getEmailAddress());
			osmsMessage rsp = osmsGlobalObjectManager.getInstance().getLoginManager().createUserRequest(cuReq);
			if(rsp==null)return "Encountered Unknown Error!  CreateUserRequest return null.";

			String rspName = rsp.getClass().getName();
//			logDebug(methodName,rspName);
			if(rspName.equals("com.mutable.osms.common.io.message.osmsMessageCreateUserResponseError"))
			{
				logDebug(methodName,((osmsMessageCreateUserResponseError) rsp).getResponseString());
				return ((osmsMessageCreateUserResponseError) rsp).getResponseString();
			}
			if(!rspName.equals("com.mutable.osms.common.io.message.osmsMessageCreateUserResponse"))
			{
				return "Encountered Unknown Error!  ResponseMessage type = "+rspName;
			}
			osmsUsers user = osmsGlobalObjectManager.getInstance().getLoginManager().getUser(req.getUserName());
			user.getUsersBean().copyPropertiesTo(a_user.getUsersBean());
		} // if

		//REGISTER  USER
		{
			osmsMessage resp = osmsGlobalObjectManager.getInstance().getRightsManager().processRegisterUserRequest(req);
			if(resp==null)return "Encountered Unknown Error!";

			String rspName = resp.getClass().getName();
			logDebug(methodName,rspName);
			if(rspName.equals("com.mutable.osms.common.io.message.osmsMessageRegisterUserResponseError"))
			{
				logDebug(methodName,((osmsMessageRegisterUserResponseError) resp).getResponseString());
				return ((osmsMessageRegisterUserResponseError) resp).getResponseString();
			}
			if(!rspName.equals("com.mutable.osms.common.io.message.osmsMessageRegisterUserResponse"))
			{
				return "Encountered Unknown Error!  ResponseMessage type = "+rspName;
			}

			a_user.setUserSecurityStore(((osmsMessageRegisterUserResponse)resp).getUserSecurityStore());
			a_user.isLoggedIn(true);
		}

		return null;
    }
}