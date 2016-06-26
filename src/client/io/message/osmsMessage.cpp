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

#include "io/message/osmsMessage.h"
#include "io/message/osmsMessageCreateUserRequest.h"
#include "io/message/osmsMessageCreateUserResponse.h"
#include "io/message/osmsMessageCreateUserResponseError.h"
#include "io/message/osmsMessageGenericResponseError.h"
#include "io/message/osmsMessageGetContentKeyRequest.h"
#include "io/message/osmsMessageGetContentKeyResponse.h"
#include "io/message/osmsMessageGetContentKeyResponseError.h"
#include "io/message/osmsMessageLicenseRequest.h"
#include "io/message/osmsMessageLicenseResponse.h"
#include "io/message/osmsMessageLicenseResponseError.h"
#include "io/message/osmsMessageLoginRequest.h"
#include "io/message/osmsMessageLoginResponse.h"
#include "io/message/osmsMessageLoginResponseError.h"
#include "io/message/osmsMessageLogout.h"
#include "io/message/osmsMessageLogoutRequest.h"
#include "io/message/osmsMessageLogoutResponse.h"
#include "io/message/osmsMessageLogoutResponseError.h"
#include "io/message/osmsMessageRegisterContentAssignIdentifierRequest.h"
#include "io/message/osmsMessageRegisterContentAssignIdentifierResponse.h"
#include "io/message/osmsMessageRegisterContentAssignIdentifierResponseError.h"
#include "io/message/osmsMessageRegisterContentExistingIdentifierRequest.h"
#include "io/message/osmsMessageRegisterContentExistingIdentifierResponse.h"
#include "io/message/osmsMessageRegisterContentExistingIdentifierResponseError.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceRequest.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceResponse.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceResponseError.h"
#include "io/message/osmsMessageRegisterUserRequest.h"
#include "io/message/osmsMessageRegisterUserResponse.h"
#include "io/message/osmsMessageRegisterUserResponseError.h"
#include "io/message/osmsMessageAcquireUserKeyStoreRequest.h"
#include "io/message/osmsMessageAcquireUserKeyStoreResponse.h"
#include "io/message/osmsMessageAcquireUserKeyStoreResponseError.h"
#include "io/message/osmsMessageUnknownRequestResponseError.h"
#include "io/message/osmsMessageUserLoginRequest.h"
#include "io/message/osmsMessageUserLoginResponse.h"
#include "io/message/osmsMessageUserLoginResponseError.h"
#include "io/message/osmsMessageUserLogoutRequest.h"
#include "io/message/osmsMessageUserLogoutResponse.h"
#include "io/message/osmsMessageUserLogoutResponseError.h"
#include "io/message/osmsMessageRightsAuthorizationRequest.h"
#include "io/message/osmsMessageRightsAuthorizationResponse.h"

#include "io/message/osmsMessageQueryResponse.h"

// pick any non-abstract class that implements the virtual 
static osmsMessageUnknownRequestResponseError sOsmsMessageUnknownRequestResponseError;

osmsMessage::osmsMessage(int messageType, char* name)
	: XMLMessageBean(messageType, name)
{
	static bool bFirstTime = true;
	if (bFirstTime == true)
	{
		bFirstTime = false;
		XMLMessage::registerApplicationMessageBean((XMLMessageBean*)&sOsmsMessageUnknownRequestResponseError);
	}
}

osmsMessage::~osmsMessage()
{
}

XMLMessageBean* osmsMessage::getXMLMessageBean(int messageType) 
{
	XMLMessageBean* resultBean = (XMLMessageBean*)NULL;
	switch (messageType)
	{
		/* These are from Messaging protocol version 0.7.4
		*************************************************************/

		//Login Messages (0-20)
		case osmsMessage::osmsMESSAGE_USER_LOGIN_REQUEST:
		{
			resultBean = new osmsMessageUserLoginRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_USER_LOGIN_RESPONSE:
		{
			resultBean = new osmsMessageUserLoginResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_USER_LOGIN_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageUserLoginResponseError();
			break;
		}

		case osmsMessage::osmsMESSAGE_USER_LOGOUT_REQUEST :
		{
			resultBean = new osmsMessageUserLogoutRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_USER_LOGOUT_RESPONSE :
		{
			resultBean = new osmsMessageUserLogoutResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_USER_LOGOUT_RESPONSE_ERROR :
		{
			resultBean = new osmsMessageUserLogoutResponseError();
			break;
		}

		//License Management Messages (201-300)
		case osmsMessage::osmsMESSAGE_RIGHTS_AUTHORIZATION_REQUEST:
		{
			resultBean = new osmsMessageRightsAuthorizationRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE:
		{
			resultBean = new osmsMessageRightsAuthorizationResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE_ERROR:
		{
			// No objects ???
			return resultBean;	// NULL
		}
		case osmsMessage::osmsMESSAGE_LICENSE_REQUEST:
		{
			resultBean = new osmsMessageLicenseRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_LICENSE_RESPONSE:
		{
			resultBean = new osmsMessageLicenseResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_LICENSE_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageLicenseResponseError();
			break;
		}


		//User Management Messages (21-100)
		case osmsMessage::osmsMESSAGE_CREATE_USER_REQUEST:
		{
			resultBean = new osmsMessageCreateUserRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_CREATE_USER_RESPONSE:
		{
			resultBean = new osmsMessageCreateUserResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_CREATE_USER_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageCreateUserResponseError();
			break;
		}

		case osmsMessage::osmsMESSAGE_REGISTER_USER_REQUEST:
		{
			resultBean = new osmsMessageRegisterUserRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_USER_RESPONSE:
		{
			resultBean = new osmsMessageRegisterUserResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_USER_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageRegisterUserResponseError();
			break;
		}

		case osmsMessage::osmsMESSAGE_ACQUIRE_USER_KEY_STORE_REQUEST:
		{
			resultBean = new osmsMessageAcquireUserKeyStoreRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE:
		{
			resultBean = new osmsMessageAcquireUserKeyStoreResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageAcquireUserKeyStoreResponseError();
			break;
		}

		//Content Management Messages (101-200)
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_REQUEST:
		{
			resultBean = new osmsMessageRegisterContentExistingIdentifierRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE:
		{
			resultBean = new osmsMessageRegisterContentExistingIdentifierResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageRegisterContentExistingIdentifierResponseError();
			break;
		}

		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_REQUEST:
		{
			resultBean = new osmsMessageRegisterContentAssignIdentifierRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE:
		{
			resultBean = new osmsMessageRegisterContentAssignIdentifierResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageRegisterContentAssignIdentifierResponseError();
			break;
		}

		case osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_REQUEST:
		{
			resultBean = new osmsMessageRegisterDigitalItemInstanceRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE:
		{
			resultBean = new osmsMessageRegisterDigitalItemInstanceResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageRegisterDigitalItemInstanceResponseError();
			break;
		}

		case osmsMessage::osmsMESSAGE_GET_CONTENT_KEY_REQUEST:
		{
			resultBean = new osmsMessageGetContentKeyRequest();
			break;
		}
		case osmsMessage::osmsMESSAGE_GET_CONTENT_KEY_RESPONSE:
		{
			resultBean = new osmsMessageGetContentKeyResponse();
			break;
		}
		case osmsMessage::osmsMESSAGE_GET_CONTENT_KEY_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageGetContentKeyResponseError();
			break;
		}

		case osmsMessage::osmsMESSAGE_UNKNOWN_REQUEST_RESPONSE_ERROR:
		{
			resultBean = new osmsMessageUnknownRequestResponseError();
			break;
		}
		case osmsMessage::osmsMESSAGE_QUERY_RESPONSE:
		{
			resultBean = new osmsMessageQueryResponse();
			break;
		}

		default:
		{
			break;
		}
	}

	return resultBean;
}
