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
 * @author: Ayman Gebrail
 * @version 1.0
 */

import java.io.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

import squashxml.xml.*;
import squashxml.socket.*;

import com.mutable.osms.common.io.message.*;

import com.mutable.osms.server.bo.*;
import com.mutable.osms.server.app.*;
import com.mutable.io.OlLogger;

public class SimpleServletServer extends SquashXMLServletServer
{
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
	// PROPERTIES
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger m_logger= osmsGlobalObjectManager.getInstance().getLogger();
	private osmsGlobalObjectManager gObjectManager = null;
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


	public SimpleServletServer()
	{
		gObjectManager = osmsGlobalObjectManager.getInstance();
	}

	//
	// osms application specific messages (i.e. osmsMessage's).
	//
	public XMLMessageBean processRequestMessage(HttpServletRequest request, XMLMessageBean inMessage)
	{
		String methodName = "processRequestMessage";

		/** Insanity checks
		 *
		 */
		logDebug(methodName,"Checking for errors.");
		if (gObjectManager == null)
		{
			osmsMessageUnknownRequestResponseError errMessage = new osmsMessageUnknownRequestResponseError();
			errMessage.setErrorCode(new Integer(osmsMessageResponseError.SYSTEM_ERROR));
			errMessage.setResponseString("SYSTEM ERROR: Global Object Manager not set.");
			return errMessage;
		}
		if (inMessage == null)
		{
			osmsMessageUnknownRequestResponseError errMessage = new osmsMessageUnknownRequestResponseError();
			errMessage.setErrorCode(new Integer(osmsMessageResponseError.INCOMPLETE_REQUEST));
			errMessage.setResponseString("ERROR: Input could not be converted into a request object.");
			return errMessage;
		}

		/** Session Management
		 *
		 */
		osmsUsers user = null;
		osmsMessage outMessage;
		if (hasSession(request) && (user = (osmsUsers)getSessionObject(request)) != null)
		{
			logDebug(methodName,"Found existing user using sessions");
		}
		else
		{
			if (inMessage.getMessageType().intValue() == osmsMessage.osmsMESSAGE_USER_LOGIN_REQUEST)
			{
				osmsMessageUserLoginRequest loginMessage  = (osmsMessageUserLoginRequest)inMessage;
				logDebug(methodName,loginMessage.getUserName());
				user = gObjectManager.getLoginManager().getUser(loginMessage.getUserName());

				if (user == null)
				{
					osmsMessageUserLoginResponseError errLogin = new osmsMessageUserLoginResponseError();
					errLogin.setErrorCode(new Integer(osmsMessageResponseError.UNKNOWN_USER));
					errLogin.setResponseString("ERROR: Unknown user.");
					return errLogin;
				}

				/** C. Mollis set clear text password for SPE */
				user.setClearTextPassword( loginMessage.getPassword() );
				logDebug(methodName,"Got new user");
				startSession(request, user);
			}
			else if (inMessage.getMessageType().intValue() == osmsMessage.osmsMESSAGE_CREATE_USER_REQUEST) {

				logDebug(methodName,"Got Create User Request");
				osmsMessageCreateUserRequest createUserMessage  = (osmsMessageCreateUserRequest)inMessage;
				outMessage = gObjectManager.getLoginManager().createUserRequest(createUserMessage);
				logDebug(methodName,"Processed Create User Request");
				if (outMessage.getMessageType().intValue() == osmsMessage.osmsMESSAGE_CREATE_USER_RESPONSE) {
					logDebug(methodName,"Create User Request successful");
					user = gObjectManager.getLoginManager().getUser(createUserMessage.getUserName());
					if (user == null)
					{
						logDebug(methodName,"Create User Request successful, but can't find the newly created user.");
						osmsMessageCreateUserResponseError errLogin = new osmsMessageCreateUserResponseError();
						errLogin.setErrorCode(new Integer(osmsMessageCreateUserResponseError.UNKNOWN_USER));
						errLogin.setResponseString("ERROR: Create User Request successful, but can't find the newly created user.");
						return errLogin;
					}
					logDebug(methodName,"Got newly created user");
					startSession(request, user);
					return outMessage;
				}
				return outMessage;
			}
			else
			{
				osmsMessageUnknownRequestResponseError errMessage = new osmsMessageUnknownRequestResponseError();
				errMessage.setErrorCode(new Integer(osmsMessageResponseError.NOT_AUTHORIZED));
				errMessage.setResponseString("ERROR: Must login in first; no session.");
				return errMessage;
			}
		}

		/** Message Processing
		 *
		 */
		switch (inMessage.getMessageType().intValue())
		{
			case osmsMessage.osmsMESSAGE_USER_LOGOUT_REQUEST:
			{
				logDebug(methodName,"Got Logout Request");
				outMessage = gObjectManager.getLoginManager().processLogoutRequest((osmsMessageUserLogoutRequest)inMessage, user);
				if(outMessage.getMessageType().intValue()==osmsMessage.osmsMESSAGE_USER_LOGOUT_RESPONSE)
				{
					stopSession(request);
				}
				break;
			}
			case osmsMessage.osmsMESSAGE_USER_LOGIN_REQUEST:
			{
				logDebug(methodName,"Got Login Request");
				outMessage = gObjectManager.getLoginManager().processLoginRequest((osmsMessageUserLoginRequest)inMessage, user);
				break;
			}
			/*
			case osmsMessage.osmsMESSAGE_CREATE_USER_REQUEST:
			{
				logDebug(methodName,"Got Create User Request");
				outMessage = gObjectManager.getLoginManager().createUserRequest((osmsMessageCreateUserRequest)inMessage);
				logDebug(methodName,"Processed Create User Request");
				break;
			}
			*/
			case osmsMessage.osmsMESSAGE_REGISTER_USER_REQUEST:
			{
				logDebug(methodName,"Got Register User Request");
				outMessage = gObjectManager.getRightsManager().processRegisterUserRequest((osmsMessageRegisterUserRequest)inMessage);
				logDebug(methodName,"Processed Register User Request");
				stopSession(request);
				break;
			}
			case osmsMessage.osmsMESSAGE_ACQUIRE_USER_KEY_STORE_REQUEST:
			{
				logDebug(methodName,"Got Acquire User Key Store Request");
				byte[] ba = gObjectManager.getRightsManager().AquireUserKeyStore(user);
				if(ba==null) {
					osmsMessageAcquireUserKeyStoreResponseError errMsg = new osmsMessageAcquireUserKeyStoreResponseError();
					errMsg.setErrorCode(new Integer(osmsMessageAcquireUserKeyStoreResponseError.UNKNOWN_ERROR));
					errMsg.setResponseString("ERROR: Unable to create user key store.");
					return errMsg;
				}
				user.setUserSecurityStore(ba);
				osmsMessageAcquireUserKeyStoreResponse retMessage = new osmsMessageAcquireUserKeyStoreResponse();
				retMessage.setUserName(user.getUserName());
				retMessage.setUserSecurityStore(ba);
				logDebug(methodName,"Processed Acquire User Key Store Request");
				return(retMessage);
			}
			case osmsMessage.osmsMESSAGE_LICENSE_REQUEST:
			{
				logDebug(methodName,"Got License Request");
				outMessage = gObjectManager.getRightsManager().processLicenseRequest((osmsMessageLicenseRequest)inMessage, user);
				break;
			}
			case osmsMessage.osmsMESSAGE_RIGHTS_AUTHORIZATION_REQUEST:
			{
				logDebug(methodName,"Got Rights Auth Request");
				outMessage = gObjectManager.getRightsManager().processRightsAuthorizationRequest((osmsMessageRightsAuthorizationRequest)inMessage,user);
				break;
			}
			case osmsMessage.osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_REQUEST:
			{
				logDebug(methodName,"Got Register Content Assign Identifier Request");
				outMessage = gObjectManager.getContentManager().processRegisterContentAssignIdentifierRequest((osmsMessageRegisterContentAssignIdentifierRequest)inMessage,user);
				break;
			}
			case osmsMessage.osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_REQUEST:
			{
				logDebug(methodName,"Got Register Content Existing Identifier Request");
				outMessage = gObjectManager.getContentManager().processRegisterContentExistingIdentifierRequest((osmsMessageRegisterContentExistingIdentifierRequest)inMessage,user);
				break;
			}
			case osmsMessage.osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_REQUEST:
			{
				logDebug(methodName,"Got Register Digital Item Instance Request");
				outMessage = gObjectManager.getContentManager().processRegisterDigitalItemInstanceRequest((osmsMessageRegisterDigitalItemInstanceRequest)inMessage,user);
				break;
			}
			case osmsMessage.osmsMESSAGE_GET_CONTENT_KEY_REQUEST:
			{
				logDebug(methodName,"Got Content Key Request");
				outMessage = gObjectManager.getContentManager().processGetContentKeyRequest((osmsMessageGetContentKeyRequest)inMessage,user);
				break;
			}
			case osmsMessage.osmsMESSAGE_QUERY_REQUEST:
			{
				outMessage = gObjectManager.getRightsManager().processQuery((osmsMessageQueryRequest)inMessage,user);
				break;
			}
			default:
			{
				logDebug(methodName,"Got Unknown Request");
				osmsMessageUnknownRequestResponseError resMessage = new osmsMessageUnknownRequestResponseError();
				outMessage = resMessage;
				break;
			}
		}

		if (outMessage == null)
		{
			osmsMessageUnknownRequestResponseError errMessage = new osmsMessageUnknownRequestResponseError();
			errMessage.setErrorCode(new Integer(osmsMessageResponseError.SYSTEM_ERROR));
			errMessage.setResponseString("Could not encode response object.");
			return errMessage;
		}
		return outMessage;
	}
}

