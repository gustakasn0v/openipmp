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

package com.mutable.osms.server.ws;

import com.mutable.osms.server.ws.message.*;
import com.mutable.osms.common.io.message.*;
import com.mutable.osms.server.app.*;
import com.mutable.osms.server.bo.*;
import org.apache.axis.*;
import org.apache.axis.message.*;

/**
 * class OsmsWebService
 * -> authorization is managed by using SOAP headers
 * -> userLogin() and userLogout() are actually not neccessary 
 *    but are provided if there will be ambition for caching 
 *    user objects (osmsUsers) in the future   
 */

public class OsmsWebService {
	
	// "manual" user login 
	public OsmsUserLoginResponse userLogin(OsmsUserLoginRequest msg) throws OsmsUserLoginFault {
		osmsMessageUserLoginRequest req = OsmsMessageTranslator.convert(msg);

		osmsUsers user = osmsGlobalObjectManager.getInstance().getLoginManager().getUser(req.getUserName());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getLoginManager().processLoginRequest(req, user);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageUserLoginResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageUserLoginResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageUserLoginResponse"))
			return OsmsMessageTranslator.convert((osmsMessageUserLoginResponse)rsp);
		else
			return null;
	}
	
	// obtains a user defined by userName/password given in SOAP headers
	protected osmsUsers getUser(MessageContext context) throws OsmsUserLoginFault {
		Message message = context.getRequestMessage();
		SOAPEnvelope envelope = null;
		SOAPHeaderElement element = null;
		String userName = null, password = null;
		try {
			envelope = message.getSOAPEnvelope();
			element = envelope.getHeaderByName("http://ws.server.osms.mutable.com", "userName");
			userName = (String) element.getValueAsType(Constants.XSD_STRING);
			element = envelope.getHeaderByName("http://ws.server.osms.mutable.com", "password");
			password = (String) element.getValueAsType(Constants.XSD_STRING);
		}
		catch (Exception e) {
		}
		return getUser(userName, password);
	}
	
	// obtains a user defined by userName/password strings
	protected osmsUsers getUser(String userName, String password) throws OsmsUserLoginFault {
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

	// "manual" user logout
	public OsmsUserLogoutResponse userLogout(OsmsUserLogoutRequest msg) throws OsmsUserLoginFault, OsmsUserLogoutFault {
		osmsMessageUserLogoutRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getLoginManager().processLogoutRequest(req, user);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageUserLogoutResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageUserLogoutResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageUserLogoutResponse"))
			return OsmsMessageTranslator.convert((osmsMessageUserLogoutResponse)rsp);
		else
			return null;
	}
	
	public OsmsCreateUserResponse createUser(OsmsCreateUserRequest msg) throws OsmsCreateUserFault {
		osmsMessageCreateUserRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers NOT required [?]
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getLoginManager().createUserRequest(req);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageCreateUserResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageCreateUserResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageCreateUserResponse"))
			return OsmsMessageTranslator.convert((osmsMessageCreateUserResponse)rsp);
		else
			return null;
	}
	
	public OsmsGetContentKeyResponse getContentKey(OsmsGetContentKeyRequest msg) throws OsmsUserLoginFault, OsmsGetContentKeyFault {
		osmsMessageGetContentKeyRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getContentManager().processGetContentKeyRequest(req, user);

		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageGetContentKeyResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageGetContentKeyResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageGetContentKeyResponse"))
			return OsmsMessageTranslator.convert((osmsMessageGetContentKeyResponse)rsp);
		else
			return null;		
	}

	public OsmsLicenseResponse license(OsmsLicenseRequest msg) throws OsmsUserLoginFault, OsmsLicenseFault {
		osmsMessageLicenseRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getRightsManager().processLicenseRequest(req, user);

		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageLicenseResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageLicenseResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageLicenseResponse"))
			return OsmsMessageTranslator.convert((osmsMessageLicenseResponse)rsp);
		else
			return null;		
	}
	
	public OsmsQueryResponse query(OsmsQueryRequest msg) throws OsmsUserLoginFault, OsmsQueryFault {
		osmsMessageQueryRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getRightsManager().processQuery(req, user);

		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageResponseError")) // note the type is osmsMessageResponseError, not osmsMessageQueryResponseError
			throw OsmsMessageTranslator.convert((osmsMessageResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageQueryResponse"))
			return OsmsMessageTranslator.convert((osmsMessageQueryResponse)rsp);
		else
			return null;		
	}

	public OsmsRegisterContentAssignIdentifierResponse registerContentAssignIdentifier(OsmsRegisterContentAssignIdentifierRequest msg) throws OsmsUserLoginFault, OsmsRegisterContentAssignIdentifierFault {
		osmsMessageRegisterContentAssignIdentifierRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getContentManager().processRegisterContentAssignIdentifierRequest(req, user);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterContentAssignIdentifierResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageRegisterContentAssignIdentifierResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterContentAssignIdentifierResponse"))
			return OsmsMessageTranslator.convert((osmsMessageRegisterContentAssignIdentifierResponse)rsp);
		else
			return null;		
	}

	public OsmsRegisterContentExistingIdentifierResponse registerContentExistingIdentifier(OsmsRegisterContentExistingIdentifierRequest msg) throws OsmsUserLoginFault, OsmsRegisterContentExistingIdentifierFault {
		osmsMessageRegisterContentExistingIdentifierRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getContentManager().processRegisterContentExistingIdentifierRequest(req, user);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterContentExistingIdentifierResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageRegisterContentExistingIdentifierResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterContentExistingIdentifierResponse"))
			return OsmsMessageTranslator.convert((osmsMessageRegisterContentExistingIdentifierResponse)rsp);
		else
			return null;		
	}

	public OsmsRegisterDigitalItemInstanceResponse registerDigitalItemInstance(OsmsRegisterDigitalItemInstanceRequest msg) throws OsmsUserLoginFault, OsmsRegisterDigitalItemInstanceFault {
		osmsMessageRegisterDigitalItemInstanceRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getContentManager().processRegisterDigitalItemInstanceRequest(req, user);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterDigitalItemInstanceResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageRegisterDigitalItemInstanceResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterDigitalItemInstanceResponse"))
			return OsmsMessageTranslator.convert((osmsMessageRegisterDigitalItemInstanceResponse)rsp);
		else
			return null;		
	}
	
	public OsmsRegisterUserResponse registerUser(OsmsRegisterUserRequest msg) throws OsmsRegisterUserFault {
		osmsMessageRegisterUserRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers NOT required [?]
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getRightsManager().processRegisterUserRequest(req);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterUserResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageRegisterUserResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRegisterUserResponse"))
			return OsmsMessageTranslator.convert((osmsMessageRegisterUserResponse)rsp);
		else
			return null;		
	}

	public OsmsRightsAuthorizationResponse rightsAuthorization(OsmsRightsAuthorizationRequest msg) throws OsmsUserLoginFault, OsmsRightsAuthorizationFault {
		osmsMessageRightsAuthorizationRequest req = OsmsMessageTranslator.convert(msg);
		
		// user authentication through SOAP headers required
		osmsUsers user = getUser(MessageContext.getCurrentContext());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getRightsManager().processRightsAuthorizationRequest(req, user);
		
		if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationResponseError"))
			throw OsmsMessageTranslator.convert((osmsMessageRightsAuthorizationResponseError)rsp);
		else if (rsp.getClass().getName().equals("com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationResponse"))
			return OsmsMessageTranslator.convert((osmsMessageRightsAuthorizationResponse)rsp);
		else
			return null;		
	}
}
