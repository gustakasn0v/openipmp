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

#include "io/message/osmsMessageLicenseResponse.h"

osmsMessageLicenseResponse::osmsMessageLicenseResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_LICENSE_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageLicenseResponse")
{
	m_License = NULL;
}

osmsMessageLicenseResponse::~osmsMessageLicenseResponse()
{
	if (m_License != NULL)
		delete[] m_License;
}


char* osmsMessageLicenseResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageLicenseResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<License type=\"char[]\"></License>" \
		"</com.mutable.osms.common.io.message.osmsMessageLicenseResponse>";
}

char* osmsMessageLicenseResponse::encode()
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
	pDoc->setString("License", getLicense());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageLicenseResponse::decode(char* xmlText)
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
  char* tmp = pDoc->getString("License");
	setLicense(tmp);
  delete[] tmp;

	delete pDoc;

	return true;
}


//bean properties
char* osmsMessageLicenseResponse::getLicense()
{
	return m_License;
}

void osmsMessageLicenseResponse::setLicense(char* p_License)
{
	if (m_License != NULL)
	{
		delete[] m_License;
		m_License = NULL;
	}
	if (p_License != NULL)
	{
		m_License = new char[strlen(p_License)+1];
		strcpy(m_License, p_License);
	}
}


