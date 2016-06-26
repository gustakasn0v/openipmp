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

#include "io/message/osmsMessageGetContentKeyRequest.h"

osmsMessageGetContentKeyRequest::osmsMessageGetContentKeyRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_GET_CONTENT_KEY_REQUEST, "com.mutable.osms.common.io.message.osmsMessageGetContentKeyRequest")
{
	m_MetadataType = NULL;
	m_DigitalItemInstanceId = NULL;
}

osmsMessageGetContentKeyRequest::~osmsMessageGetContentKeyRequest()
{
	if (m_MetadataType != NULL)
		delete[] m_MetadataType;

	if (m_DigitalItemInstanceId != NULL)
		delete[] m_DigitalItemInstanceId;
}



char* osmsMessageGetContentKeyRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageGetContentKeyRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<MetadataType type=\"char[]\"></MetadataType>" \
			"<DigitalItemInstanceId type=\"char[]\"></DigitalItemInstanceId>" \
		"</com.mutable.osms.common.io.message.osmsMessageGetContentKeyRequest>";
}

char* osmsMessageGetContentKeyRequest::encode()
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
	pDoc->setString("MetadataType", getMetadataType());
	pDoc->setString("DigitalItemInstanceId", getDigitalItemInstanceId());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageGetContentKeyRequest::decode(char* xmlText)
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
  char* tmp = pDoc->getString("MetadataType");
	setMetadataType(tmp);
  delete[] tmp;
  tmp = pDoc->getString("DigitalItemInstanceId");
	setDigitalItemInstanceId(tmp);
  delete[] tmp;

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageGetContentKeyRequest::getMetadataType()
{
	return m_MetadataType;
}

void osmsMessageGetContentKeyRequest::setMetadataType(char* MetadataType)
{
	if (m_MetadataType != NULL)
	{
		delete[] m_MetadataType;
		m_MetadataType = NULL;
	}
	if (MetadataType != NULL)
	{
		m_MetadataType = new char[strlen(MetadataType)+1];
		strcpy(m_MetadataType, MetadataType);
	}
}


char* osmsMessageGetContentKeyRequest::getDigitalItemInstanceId()
{
	return m_DigitalItemInstanceId;
}

void osmsMessageGetContentKeyRequest::setDigitalItemInstanceId(char* DigitalItemInstanceId)
{
	if (m_DigitalItemInstanceId != NULL)
	{
		delete[] m_DigitalItemInstanceId;
		m_DigitalItemInstanceId = NULL;
	}
	if (DigitalItemInstanceId != NULL)
	{
		m_DigitalItemInstanceId = new char[strlen(DigitalItemInstanceId)+1];
		strcpy(m_DigitalItemInstanceId, DigitalItemInstanceId);
	}
}
