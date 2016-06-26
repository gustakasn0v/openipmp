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

#include "io/message/osmsMessageGetContentKeyResponse.h"

osmsMessageGetContentKeyResponse::osmsMessageGetContentKeyResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_GET_CONTENT_KEY_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageGetContentKeyResponse")
{
	m_KeyXml = NULL;
	m_AuxDataXml = NULL;
}

osmsMessageGetContentKeyResponse::~osmsMessageGetContentKeyResponse()
{
	if (m_KeyXml != NULL)
		delete[] m_KeyXml;

	if (m_AuxDataXml != NULL)
		delete[] m_AuxDataXml;
}



char* osmsMessageGetContentKeyResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageGetContentKeyResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<KeyXml type=\"char[]\"></KeyXml>" \
			"<AuxDataXml type=\"char[]\"></AuxDataXml>" \
		"</com.mutable.osms.common.io.message.osmsMessageGetContentKeyResponse>";
}

char* osmsMessageGetContentKeyResponse::encode()
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
	pDoc->setString("KeyXml", getKeyXml());
	pDoc->setString("AuxDataXml", getAuxDataXml());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageGetContentKeyResponse::decode(char* xmlText)
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
	setKeyXml(pDoc->getString("KeyXml"));
	setAuxDataXml(pDoc->getString("AuxDataXml"));

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageGetContentKeyResponse::getKeyXml()
{
	return m_KeyXml;
}

void osmsMessageGetContentKeyResponse::setKeyXml(char* KeyXml)
{
	if (m_KeyXml != NULL)
	{
		delete[] m_KeyXml;
		m_KeyXml = NULL;
	}
	if (KeyXml != NULL)
	{
		m_KeyXml = new char[strlen(KeyXml)+1];
		strcpy(m_KeyXml, KeyXml);
	}
}

char* osmsMessageGetContentKeyResponse::getAuxDataXml()
{
	return m_AuxDataXml;
}

void osmsMessageGetContentKeyResponse::setAuxDataXml(char* AuxDataXml)
{
	if (m_AuxDataXml != NULL)
	{
		delete[] m_AuxDataXml;
		m_AuxDataXml = NULL;
	}
	if (AuxDataXml != NULL)
	{
		m_AuxDataXml = new char[strlen(AuxDataXml)+1];
		strcpy(m_AuxDataXml, AuxDataXml);
	}
}
