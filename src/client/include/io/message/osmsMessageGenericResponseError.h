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
#ifndef OSMS_Message_Generic_Response_Error_H
#define OSMS_Message_Generic_Response_Error_H

#include "osmsMessage.h"

class osmsMessageGenericResponseError : public osmsMessage
{
public:
	enum ErrorCode	{
		osmsERROR_UNKNOWN_ERROR							= 1,
		osmsERROR_UNKNOWN_REQUEST						= 2,
		osmsERROR_UNKNOWN_USER							= 3,
		osmsERROR_UNKNOWN_AGENT							= 4,
		osmsERROR_UNKNOWN_RESOURCE						= 5,
		osmsERROR_UNKNOWN_RIGHT							= 6,
		osmsERROR_UNKNOWN_ACTION						= 7,
		osmsERROR_ALREADY_LOGGED_IN						= 8,
		osmsERROR_NOT_LOGGED_IN							= 9,
		osmsERROR_NOT_AUTHORIZED						= 10,
		osmsERROR_BAD_PASSWORD							= 11,
		osmsERROR_BAD_SIGNATURE							= 12,
		osmsERROR_INCOMPLETE_REQUEST					= 13,
		osmsERROR_CA_ERROR								= 14,
		osmsERROR_DB_ERROR								= 15,
		osmsERROR_SYSTEM_ERROR							= 16,
		osmsERROR_UNSUPPORTED_CONTENT_METADATA_SCHEME	= 17,
		osmsERROR_DOI_PARSING_ERROR						= 18,
		osmsERROR_DOI_NOT_FOUND							= 19,
		osmsERROR_DOI_ALREADY_REGISTERED				= 20,
		osmsERROR_DOI_NOT_REGISTERED_AS_CONTENT			= 21,
		osmsERROR_DOI_NOT_PROTECTED						= 22,
		osmsERROR_GRID_PARSING_ERROR					= 23,
		osmsERROR_GRID_NOT_FOUND						= 24,
		osmsERROR_GRID_ALREADY_REGISTERED				= 25,
		osmsERROR_GRID_NOT_REGISTERED_AS_CONTENT		= 26,
		osmsERROR_GRID_NOT_PROTECTED					= 27,
		osmsERROR_USER_ALREADY_EXISTS					= 28
	};

	osmsMessageGenericResponseError(int messageType, char* name);
	virtual ~osmsMessageGenericResponseError();

	//bean properties
	int getErrorCode();
	void setErrorCode(int ErrorCode);

	char* getResponseString();
	void setResponseString(char* ResponseString);

private:
	int m_ErrorCode;
	char* m_ResponseString;
};

#endif // OSMS_Message_Generic_Response_Error_H
