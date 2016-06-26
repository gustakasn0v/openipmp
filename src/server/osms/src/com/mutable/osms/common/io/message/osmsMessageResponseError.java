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


package com.mutable.osms.common.io.message;

/**
 * <p>Title: osmsMessageResponseError</p>
 * <p>Description: </p>
 * @version 1.0
 */

public class osmsMessageResponseError extends osmsMessage
{
	public static final int UNKNOWN_ERROR    = 1;
	public static final int UNKNOWN_REQUEST  = 2;
	public static final int UNKNOWN_USER     = 3;
	public static final int UNKNOWN_AGENT    = 4;
	public static final int UNKNOWN_RESOURCE = 5;
	public static final int UNKNOWN_RIGHT    = 6;
	public static final int UNKNOWN_ACTION   = 7;
	public static final int ALREADY_LOGGED_IN = 8;
	public static final int NOT_LOGGED_IN    = 9;
	public static final int NOT_AUTHORIZED   = 10;
	public static final int BAD_PASSWORD     = 11;
	public static final int BAD_SIGNATURE    = 12;
	public static final int INCOMPLETE_REQUEST  = 13;
	public static final int CA_ERROR         = 14;
	public static final int DB_ERROR         = 15;
	public static final int SYSTEM_ERROR     = 16;
	public static final int UNSUPPORTED_CONTENT_METADATA_SCHEME = 17;
	public static final int DOI_PARSING_ERROR = 18;
	public static final int DOI_NOT_FOUND = 19;
	public static final int DOI_ALREADY_REGISTERED = 20;
	public static final int DOI_NOT_REGISTERED_AS_CONTENT = 21;
	public static final int DOI_NOT_PROTECTED = 22;
	public static final int GRID_PARSING_ERROR = 23;
	public static final int GRID_NOT_FOUND = 24;
	public static final int GRID_ALREADY_REGISTERED = 25;
	public static final int GRID_NOT_REGISTERED_AS_CONTENT = 26;
	public static final int GRID_NOT_PROTECTED = 27;
	public static final int USER_ALREADY_EXISTS = 28;

	//bean properties

	private Integer m_ErrorCode=null;
	public Integer getErrorCode(){return m_ErrorCode;}
	public void setErrorCode(Integer ErrorCode){m_ErrorCode = new Integer(ErrorCode.intValue());}

	private String m_ResponseString=null;
	public String getResponseString(){return m_ResponseString;}
	public void setResponseString(String ResponseString){m_ResponseString=ResponseString;}

	public osmsMessageResponseError(int messageType)
	{
		super(messageType);
	}

	public osmsMessageResponseError(int messageType, int errCode, String errMsg)
	{
		super(messageType);
		setErrorCode(new Integer(errCode));
		setResponseString(errMsg);
	}
}