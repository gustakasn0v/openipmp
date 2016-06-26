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
 * @author Ayman Gebrail
 * @version 1.0
 */

package com.mutable.osms.common.io.message;

import squashxml.xml.*;

public class osmsMessage extends XMLMessageBean
{
	//Login Messages (0-20)
	public final static int osmsMESSAGE_USER_LOGIN_REQUEST = 1;
	public final static int osmsMESSAGE_USER_LOGIN_RESPONSE = 2;
	public final static int osmsMESSAGE_USER_LOGIN_RESPONSE_ERROR = 3;

	public final static int osmsMESSAGE_USER_LOGOUT_REQUEST  = 4;
	public final static int osmsMESSAGE_USER_LOGOUT_RESPONSE  = 5;
	public final static int osmsMESSAGE_USER_LOGOUT_RESPONSE_ERROR  = 6;

	//User Management Messages (21-100)
	public final static int osmsMESSAGE_CREATE_USER_REQUEST = 21;
	public final static int osmsMESSAGE_CREATE_USER_RESPONSE = 22;
	public final static int osmsMESSAGE_CREATE_USER_RESPONSE_ERROR = 23;

	public final static int osmsMESSAGE_REGISTER_USER_REQUEST = 24;
	public final static int osmsMESSAGE_REGISTER_USER_RESPONSE = 25;
	public final static int osmsMESSAGE_REGISTER_USER_RESPONSE_ERROR = 26;

	public final static int osmsMESSAGE_ACQUIRE_USER_KEY_STORE_REQUEST = 27;
	public final static int osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE = 28;
	public final static int osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE_ERROR = 29;

	//Content Management Messages (101-200)
	public final static int osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_REQUEST = 101;
	public final static int osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE = 102;
	public final static int osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE_ERROR = 103;

	public final static int osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_REQUEST = 104;
	public final static int osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE = 105;
	public final static int osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE_ERROR = 106;

	public final static int osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_REQUEST = 107;
	public final static int osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE = 108;
	public final static int osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR = 109;

	public final static int osmsMESSAGE_GET_CONTENT_KEY_REQUEST = 110;
	public final static int osmsMESSAGE_GET_CONTENT_KEY_RESPONSE = 111;
	public final static int osmsMESSAGE_GET_CONTENT_KEY_RESPONSE_ERROR = 112;

	//License Management Messages (201-300)
	public final static int osmsMESSAGE_RIGHTS_AUTHORIZATION_REQUEST = 201;
	public final static int osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE = 202;
	public final static int osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE_ERROR = 203;

	public final static int osmsMESSAGE_LICENSE_REQUEST = 204;
	public final static int osmsMESSAGE_LICENSE_RESPONSE = 205;
	public final static int osmsMESSAGE_LICENSE_RESPONSE_ERROR = 206;
	public final static int osmsMESSAGE_QUERY_REQUEST = 207;
	public final static int osmsMESSAGE_QUERY_RESPONSE = 208;
	public final static int osmsMESSAGE_QUERY_RESPONSE_ERROR = 209;

	public final static int osmsMESSAGE_RIGHTS_AUTHORIZATION_ARRAY_REQUEST = 210;
	public final static int osmsMESSAGE_RIGHTS_AUTHORIZATION_ARRAY_RESPONSE = 211;
	public final static int osmsMESSAGE_RIGHTS_AUTHORIZATION_ARRAY_RESPONSE_ERROR = 212;

	//Miscellaneous Messages (901-999)
	public final static int osmsMESSAGE_UNKNOWN_MESSAGE_ERROR = 998;
	public final static int osmsMESSAGE_UNKNOWN_REQUEST_RESPONSE_ERROR = 999;

	public osmsMessage(int messageType)
	{
		super(messageType);
	}
}