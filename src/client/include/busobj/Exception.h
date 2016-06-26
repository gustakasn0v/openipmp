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

#ifndef __EXCEPTION_HPP
#define __EXCEPTION_HPP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef LINUX
#include <typeinfo>
#endif

#ifdef WIN32
#include <typeinfo.h>
#endif

/**
	<b>Class Exception</b> <br>
	Specifies the base class implementation of an Exception. 
*/



//#define CLASS_NAME(pointer) ((const type_info&)typeid(pointer)).name()
#define CLASS_NAME(pointer) typeid(pointer).name()

#define EXCEPTION(eType) Exception(eType, CLASS_NAME(this), __FILE__, __LINE__)

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
class Exception
{
public:


	enum ExceptionType
	{
		UNKNOWN_ERROR,
		USER_NOT_FOUND,
		BAD_USER_ID,
		ALREADY_LOGGED_IN,
		BAD_PASSWORD,
		USER_BLOCKED,
		INCORRECT_ARGUMENTS,
		SOCKET_CLASS_ERROR,
		BASE_PATH_TOO_LONG,
		BASE_PATH_NOT_SET,
		P12_MISSING_USER_AUTH_DATA,
		P12_MISSING_BASEPATH,
		P12_ASN1_DECODE_ERROR,
		P12_TOKEN_PARSE_ERROR,
		P12_LOGIN_AUTO_FAILED,
		P12_LOGIN_MANUAL_FAILED,
		CERTIFICATE_ENROLL,
		CERT_BAD_SERIAL_NUMBER,
		BAD_OSMS_LOGIN,
		BAD_OSMS_LICENSE_REQUEST,
		MISSING_LICENSE_KEY,
		LICENSE_NOT_FOUND,
		UNEXPECTED_CONDITION
	};

	typedef struct ExceptionStruct {
		ExceptionType eType;
		const char*	eMsg;
	} ExceptionStruct;


	const char* getExceptionMessage(ExceptionType eType);

	Exception(ExceptionType eType, const char* classname, const char* filename, int linenum);


	/**
	*	Get the ErrorCode for this Exception
	*
	*	@returns the ErrorCode of this Exception object
	*/
	inline virtual ExceptionType getErrorCode()
	{
		return m_ErrCode;
	}

	/**
	*	Get the ErrorMsg character array for this Exception..  Developer's should NOT free this pointer.
	*
	*	@returns the ErrorMsg of this Exception object
	*/
	inline virtual const char* getErrorMsg()
	{
		return m_ErrMsg;
	}

	inline virtual const char* getClassName()
	{
		return m_ClassName;
	}

	inline virtual const char* getFileName()
	{
		return m_FileName;
	}

	inline int getLineNum()
	{
		return m_LineNum;
	}


private:
	ExceptionType	m_ErrCode;
	const char*		m_ErrMsg;

	const char*		m_ClassName;
	const char*		m_FileName;
	int				m_LineNum;

};
#endif
