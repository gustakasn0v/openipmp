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

#include "io/message/osmsMessageGenericResponseError.h"


osmsMessageGenericResponseError::osmsMessageGenericResponseError(int messageType, char* name)
	: osmsMessage(messageType, name)
{
	m_ResponseString = NULL;
}

osmsMessageGenericResponseError::~osmsMessageGenericResponseError()
{
	if (m_ResponseString != NULL)
		delete[] m_ResponseString;
}

 
//bean properties
int osmsMessageGenericResponseError::getErrorCode()					
{ 
	return m_ErrorCode; 
}

void osmsMessageGenericResponseError::setErrorCode(int pi)
{ 
	m_ErrorCode = pi; 
}

	
char* osmsMessageGenericResponseError::getResponseString()
{
	return m_ResponseString;
}

void osmsMessageGenericResponseError::setResponseString(char* ResponseString)
{
	if (m_ResponseString != NULL)
	{
		delete[] m_ResponseString;
		m_ResponseString = NULL;
	}
	if (ResponseString != NULL)
	{
		m_ResponseString = new char[strlen(ResponseString)+1];
		strcpy(m_ResponseString, ResponseString);
	}
}

