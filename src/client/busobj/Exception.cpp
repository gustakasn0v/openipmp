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

// Exception.cpp: implementation of the Exception class.
//
//////////////////////////////////////////////////////////////////////

#include "busobj/Exception.h"


static Exception::ExceptionStruct m_ExceptionList[] = 
{
	{ Exception::UNKNOWN_ERROR,				"UNKNOWN_ERROR - Unknown Server Error" },
	{ Exception::USER_NOT_FOUND, 			"USER_NOT_FOUND - User Id is unknown" },
	{ Exception::BAD_USER_ID,				"BAD_USER_ID - Bad User Id" },
	{ Exception::ALREADY_LOGGED_IN, 			"ALREADY_LOGGED_IN - User is already logged in to the server" },
	{ Exception::BAD_PASSWORD, 				"BAD_PASSWORD - Invalid password" },
	{ Exception::USER_BLOCKED, 				"USER_BLOCKED - User Blocked - System is unavailable at this time" },
	{ Exception::INCORRECT_ARGUMENTS, 		"INCORRECT_ARGUMENTS - Incorrect arguments supplied to process" },
	{ Exception::SOCKET_CLASS_ERROR,			"SOCKET_CLASS_ERROR - Socket Error" },
	{ Exception::BASE_PATH_TOO_LONG,			"BASE_PATH_TOO_LONG - Base path is too long" },
	{ Exception::BASE_PATH_NOT_SET,			"BASE_PATH_NOT_SET - Base path not set" },
	{ Exception::P12_MISSING_USER_AUTH_DATA,"P12_MISSING_USER_AUTH_DATA - P12 Username and/or Password Not Set." },
	{ Exception::P12_MISSING_BASEPATH,		"P12_MISSING_BASEPATH - P12 Base Path Not Set." },
	{ Exception::P12_ASN1_DECODE_ERROR,		"P12_ASN1_DECODE_ERROR - Error decoding P12 File Structure."},
	{ Exception::P12_TOKEN_PARSE_ERROR,		"P12_TOKEN_PARSE_ERROR - Error Parsing P12 Tokens."},
	{ Exception::P12_LOGIN_AUTO_FAILED,		"P12_LOGIN_AUTO_FAILED - Unable to locally login to PKCS12 File Storage" },
	{ Exception::P12_LOGIN_MANUAL_FAILED,	"P12_LOGIN_MANUAL_FAILED - Please Login with a correct USERNAME and PASSWORD" },
	{ Exception::CERTIFICATE_ENROLL,			"CERTIFICATE_ENROLL - Unable to initiate Certificate Enrollment" },
	{ Exception::CERT_BAD_SERIAL_NUMBER,		"CERT_BAD_SERIAL_NUMBER - FIL_PSE_GetCertSerialNumber error" },
	{ Exception::BAD_OSMS_LOGIN,				"BAD_OSMS_LOGIN - Unable to Log Into OSMS Server.  Check auth parameters" },
	{ Exception::BAD_OSMS_LICENSE_REQUEST,	"BAD_OSMS_LICENSE_REQUEST - Unable to retrieve License.  Check Rights Authorization." },
	{ Exception::MISSING_LICENSE_KEY,		"MISSING_LICENSE_KEY - Required Track Key Not Found in License" },
	{ Exception::LICENSE_NOT_FOUND,			"LICENSE_NOT_FOUND - User not authorized for intent and content." },
	{ Exception::UNEXPECTED_CONDITION,		"UNEXPECTED_CONDITION - Unexpected condition has been encountered.  Check error logs." }
};


const char* Exception::getExceptionMessage(ExceptionType eType)
{
	for (int i = 0; i < sizeof(m_ExceptionList) / sizeof(ExceptionStruct); i++)
		if (m_ExceptionList[i].eType == eType)
			return m_ExceptionList[i].eMsg;

	return "Missing Exception Text";
}


Exception::Exception(ExceptionType eType, const char* classname, const char* filename, int linenum)
{
	m_ErrCode = eType;
	m_ErrMsg  = getExceptionMessage(eType);
	m_ClassName = classname;	
	m_FileName = filename;
	m_LineNum = linenum;
}

