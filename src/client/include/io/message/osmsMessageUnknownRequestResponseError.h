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
#ifndef OSMS_Message_Unknown_Request_Response_Error_H
#define OSMS_Message_Unknown_Request_Response_Error_H

#include "osmsMessageGenericResponseError.h"

class osmsMessageUnknownRequestResponseError : public osmsMessageGenericResponseError
{
public:
	osmsMessageUnknownRequestResponseError();

	virtual char* encode();
	virtual bool decode(char* xmlText);
	virtual char* xmlTemplate();
};

#endif // OSMS_Message_Unknown_Request_Response_Error_H
