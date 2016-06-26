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

#include "io/message/osmsMessageRegisterContentAssignIdentifierResponse.h"

osmsMessageRegisterContentAssignIdentifierResponse::osmsMessageRegisterContentAssignIdentifierResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageRegisterContentAssignIdentifierResponse")
{
	m_MetadataType = NULL;
	m_MetadataXml = NULL;
}

osmsMessageRegisterContentAssignIdentifierResponse::~osmsMessageRegisterContentAssignIdentifierResponse()
{
	if (m_MetadataType != NULL)
		delete[] m_MetadataType;

	if (m_MetadataXml != NULL)
		delete[] m_MetadataXml;
}


char* osmsMessageRegisterContentAssignIdentifierResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageRegisterContentAssignIdentifierResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<MetadataType type=\"char[]\"></MetadataType>" \
			"<MetadataXml type=\"char[]\"></MetadataXml>" \
		"</com.mutable.osms.common.io.message.osmsMessageRegisterContentAssignIdentifierResponse>";
}

char* osmsMessageRegisterContentAssignIdentifierResponse::encode()
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
	pDoc->setString("MetadataXml", getMetadataXml());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageRegisterContentAssignIdentifierResponse::decode(char* xmlText)
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
	setMetadataType(pDoc->getString("MetadataType"));
	setMetadataXml(pDoc->getString("MetadataXml"));

	delete pDoc;

	return true;
}




//bean properties
char* osmsMessageRegisterContentAssignIdentifierResponse::getMetadataType()
{
	return m_MetadataType;
}

void osmsMessageRegisterContentAssignIdentifierResponse::setMetadataType(char* MetadataType)
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


char* osmsMessageRegisterContentAssignIdentifierResponse::getMetadataXml()
{
	return m_MetadataXml;
}

void osmsMessageRegisterContentAssignIdentifierResponse::setMetadataXml(char* MetadataXml)
{
	if (m_MetadataXml != NULL)
	{
		delete[] m_MetadataXml;
		m_MetadataXml = NULL;
	}
	if (MetadataXml != NULL)
	{
		m_MetadataXml = new char[strlen(MetadataXml)+1];
		strcpy(m_MetadataXml, MetadataXml);
	}
}
