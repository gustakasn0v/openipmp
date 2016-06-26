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

#include "io/message/osmsMessageQueryRequest.h"


osmsMessageQueryRequest::osmsMessageQueryRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_QUERY_REQUEST, "com.mutable.osms.common.io.message.osmsMessageQueryRequest")
{
	m_Type = NULL;
}

osmsMessageQueryRequest::~osmsMessageQueryRequest()
{
	if (m_Type != NULL)
		delete[] m_Type;
}

char* osmsMessageQueryRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageQueryRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<Type type=\"char[]\"></Type>" \
		"</com.mutable.osms.common.io.message.osmsMessageQueryRequest>";
}

char* osmsMessageQueryRequest::encode()
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
	pDoc->setString("Type", getType());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageQueryRequest::decode(char* xmlText)
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
	setType(pDoc->getString("Type"));

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageQueryRequest::getType()
{
	return m_Type;
}
void osmsMessageQueryRequest::setType(char* Type)
{
	if (m_Type != NULL)
	{
		delete[] m_Type;
		m_Type = NULL;
	}
	if (Type != NULL)
	{
		m_Type = new char[strlen(Type)+1];
		strcpy(m_Type, Type);
	}
}

