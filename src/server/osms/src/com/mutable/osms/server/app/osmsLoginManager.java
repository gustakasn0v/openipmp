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

//import java.nio.ByteBuffer;

import com.mutable.osms.common.io.message.*;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.server.db.*;
import com.mutable.io.*;
import com.mutable.io.tools.CryptoTool;

import java.util.Date;


/**
 * -> How do we handle Manager invoke shutdown of the session/connection?
 *    I think this is an example of why we need to make the managers more
 *    business oriented and let the custom dispatcher handle this work.
 *
 */



/**
 * <p>Title: </p>
 * <p>Description: </p>
 * @version 1.0
 */
public class osmsLoginManager
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
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	OlLogger log = null;
	public osmsLoginManager()
	{
		log=osmsGlobalObjectManager.getInstance().getLogger();
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsMessage createUserRequest(osmsMessageCreateUserRequest message)
	{
		String methodName = "createUserRequest";
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();

		try
		{
			//validate message
			if(message==null)	throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message==null");
			if(message.getUserName()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"userName==null");
//			if(message.getPassword()==null)	throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"password==null");

			osmsUsers user = new osmsUsers();
			user.setUserName(message.getUserName());
			if (message.getPassword()!=null)
				user.setPassword(CryptoTool.base64Encode( CryptoTool.generateMD5Hash(message.getPassword())));
			user.setEmailAddress(message.getEmailAddress());
			user.setOrganizationId(new Integer(1));
			user.setCertificateId(new Integer(1));
			if(db.getUsersByUserName(message.getUserName())!=null)
			{
				osmsMessageCreateUserResponseError ret=new osmsMessageCreateUserResponseError();
				ret.setResponseString("User Already Exists!");
				ret.setErrorCode(new Integer(osmsMessageResponseError.USER_ALREADY_EXISTS));
				return ret;
			}
			db.insertUsers(user);
			return new osmsMessageCreateUserResponse();

		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageCreateUserResponseError response = new osmsMessageCreateUserResponseError();
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception ex)
		{
			logError(methodName,"",ex);
			osmsMessageCreateUserResponseError ret=new osmsMessageCreateUserResponseError();
			ret.setResponseString(ex.toString());
			return ret;
		}
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public osmsUsers getUser(String userName)
	{
		String methodName="getUser";
		try
		{
			osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
			return db.getUsersByUserName(userName);
		}
		catch(Exception e)
		{
			logError(methodName, "",e);
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
	public osmsMessage processLoginRequest(osmsMessageUserLoginRequest message, osmsUsers user)
	{
		String methodName = "processLoginRequest";
		logDebug(methodName, "for user: " + message.getUserName());
		try
		{

			//validate message
			if(message==null)	throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message==null");
			if(message.getUserName()==null)throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"userName==null");
			if(message.getPassword()==null)	throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"password==null");

			if (user!=null)
			{

				if(user.isLoggedIn())
				{
					osmsMessageUserLoginResponseError err = new osmsMessageUserLoginResponseError();
					err.setErrorCode(new Integer(osmsMessageResponseError.ALREADY_LOGGED_IN));
					err.setResponseString("Login failed because user is already logged into the server");
					return err;
				}

				String hashedPassword = CryptoTool.base64Encode( CryptoTool.generateMD5Hash(message.getPassword()));
				logDebug(methodName, " user:" + user.getUserName() + " pwd: " + user.getPassword() + " db pwd: " + hashedPassword);
				if (user.getPassword().compareTo(hashedPassword)==0)
				{
					//Try to generate a login record for this user
					user.login();
					user.setPassword(message.getPassword());
					osmsMessageUserLoginResponse response = new osmsMessageUserLoginResponse();
					//TODO: I think we want to change the response to include any revokes that needs to be delivered
					//: maybe it should be a differ message because this message isnt only used by the player
					response.setResponseString("OK");
					return response;
				}
				else
				{
					throw new osmsException (osmsMessageResponseError.BAD_PASSWORD, "Login Failed: Passwords do not match: ");
				}
			}
			else
			{
				//TODO: set message error code
				throw new osmsException(osmsMessageResponseError.UNKNOWN_USER, "Login Failed: User not found in database");
			}
		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageUserLoginResponseError response = new osmsMessageUserLoginResponseError();
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception e)
		{
			logError(methodName, e.toString());
			osmsMessageUserLoginResponseError response = new osmsMessageUserLoginResponseError();
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("Login Failed: Unknown Error");
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
	public osmsMessage processLogoutRequest(osmsMessageUserLogoutRequest message, osmsUsers user)
	{
		String methodName = "processLogoutRequest";
		logDebug(methodName, "for user: " + (user!=null?user.getUserName():"user is null"));

		try
		{
			//validate message
			if(message==null)	throw new osmsException(osmsMessageResponseError.INCOMPLETE_REQUEST,"message==null");

			if ((user==null) || (!user.isLoggedIn()))
			{
				osmsMessageUserLogoutResponseError err = new osmsMessageUserLogoutResponseError();
				err.setErrorCode(new Integer(osmsMessageResponseError.NOT_LOGGED_IN));
				err.setResponseString("Logout failed because user is not logged into the server");
				return err;
			}

			user.logout();
			osmsMessageUserLogoutResponse response = new osmsMessageUserLogoutResponse();
			response.setResponseString("OK");
			return response;
		}
		catch (osmsException oe)
		{
			logError(methodName, oe.getErrorCode()+": "+oe.getMessage());
			osmsMessageUserLogoutResponseError response = new osmsMessageUserLogoutResponseError();
			response.setErrorCode(new Integer(oe.getErrorCode()));
			response.setResponseString(oe.getMessage());
			return response;
		}
		catch (Exception e)
		{
			logError(methodName, e.toString());
			osmsMessageUserLogoutResponseError response = new osmsMessageUserLogoutResponseError();
			response.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_ERROR));
			response.setResponseString("Logout Failed: Unknown Error");
			return response;
		}
	}
}
