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

#include "io/message/osmsMessageUserLogoutResponse.h"


osmsMessageUserLogoutResponse::osmsMessageUserLogoutResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_USER_LOGOUT_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageUserLogoutResponse")
{
	m_ResponseString = NULL;
}

osmsMessageUserLogoutResponse::~osmsMessageUserLogoutResponse()
{
	if (m_ResponseString != NULL)
		delete[] m_ResponseString;
}

char* osmsMessageUserLogoutResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageUserLogoutResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<ResponseString type=\"char[]\"></ResponseString>" \
		"</com.mutable.osms.common.io.message.osmsMessageUserLogoutResponse>";
}

char* osmsMessageUserLogoutResponse::encode()
{
	XMLDocument* pDoc = new XMLDocument();
	if (pDoc == NULL)
		return NULL;

	if (!pDoc->decode(xmlTemplate(), getName()))
	{
		delete pDoc;
		return NULL;
	}

	pDoc->setInteger("MessageType", getMessageType());
	pDoc->setString("ResponseString", getResponseString());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageUserLogoutResponse::decode(char* xmlText)
{
	XMLDocument* pDoc = new XMLDocument();
	if (pDoc == NULL)
		return false;

	if (!pDoc->decode(xmlText, getName()))
	{
		delete pDoc;
		return false;
	}

	setMessageType(pDoc->getInteger("MessageType"));
  char* tmp = pDoc->getString("ResponseString");
	setResponseString(tmp);
  delete[] tmp;

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageUserLogoutResponse::getResponseString()
{
	return m_ResponseString;
}
void osmsMessageUserLogoutResponse::setResponseString(char* ResponseString)
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

