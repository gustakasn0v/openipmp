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
#ifndef _OSMS_Message_H
#define _OSMS_Message_H

#include "squashxml/xml/XMLMessage.h"
#include "squashxml/xml/XMLMessageBean.h"
#include "squashxml/tools/FileLogger.h"
#include "squashxml/tools/HashMap.h"
#include "squashxml/tools/ByteArray.h"

class osmsMessage : public XMLMessageBean
{

public:
    enum Message_Number
    {
		/* These are from Messaging protocol version 0.7.4
		*************************************************************/

		//Login Messages (0-20)
		osmsMESSAGE_USER_LOGIN_REQUEST = 1,
		osmsMESSAGE_USER_LOGIN_RESPONSE = 2,
		osmsMESSAGE_USER_LOGIN_RESPONSE_ERROR = 3,

		osmsMESSAGE_USER_LOGOUT_REQUEST  = 4,
		osmsMESSAGE_USER_LOGOUT_RESPONSE  = 5,
		osmsMESSAGE_USER_LOGOUT_RESPONSE_ERROR  = 6,

		//License Management Messages (201-300)
		osmsMESSAGE_RIGHTS_AUTHORIZATION_REQUEST = 201,
		osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE = 202,
		osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE_ERROR = 203,

		osmsMESSAGE_LICENSE_REQUEST = 204,
		osmsMESSAGE_LICENSE_RESPONSE = 205,
		osmsMESSAGE_LICENSE_RESPONSE_ERROR = 206,

		osmsMESSAGE_QUERY_REQUEST = 207,
		osmsMESSAGE_QUERY_RESPONSE = 208,
		osmsMESSAGE_QUERY_RESPONSE_ERROR = 209,



		//User Management Messages (21-100)
		osmsMESSAGE_CREATE_USER_REQUEST = 21,
		osmsMESSAGE_CREATE_USER_RESPONSE = 22,
		osmsMESSAGE_CREATE_USER_RESPONSE_ERROR = 23,

		osmsMESSAGE_REGISTER_USER_REQUEST = 24,
		osmsMESSAGE_REGISTER_USER_RESPONSE = 25,
		osmsMESSAGE_REGISTER_USER_RESPONSE_ERROR = 26,

		osmsMESSAGE_ACQUIRE_USER_KEY_STORE_REQUEST = 27,
		osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE = 28,
		osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE_ERROR = 29,

		//Content Management Messages (101-200)
		osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_REQUEST = 101,
		osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE = 102,
		osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE_ERROR = 103,

		osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_REQUEST = 104,
		osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE = 105,
		osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE_ERROR = 106,

		osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_REQUEST = 107,
		osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE = 108,
		osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR = 109,

		osmsMESSAGE_GET_CONTENT_KEY_REQUEST = 110,
		osmsMESSAGE_GET_CONTENT_KEY_RESPONSE = 111,
		osmsMESSAGE_GET_CONTENT_KEY_RESPONSE_ERROR = 112,

		//Old Messages
		osmsMESSAGE_UNKNOWN_MESSAGE_ERROR = 998,
		osmsMESSAGE_UNKNOWN_REQUEST_RESPONSE_ERROR = 999

	};

	osmsMessage(int messageType, char* name);
	virtual ~osmsMessage();

	// Derived Classes must implement these methods
	virtual char* encode() = 0;
	virtual bool decode(char* xmlText) = 0;
	virtual char* xmlTemplate() = 0;

	// This method should be implemented here
	virtual XMLMessageBean* getXMLMessageBean(int messageType); 
};

#endif // _OSMS_Message_H
