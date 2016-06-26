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

#include "io/message/osmsMessageLicenseRequest.h"

osmsMessageLicenseRequest::osmsMessageLicenseRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_LICENSE_REQUEST, "com.mutable.osms.common.io.message.osmsMessageLicenseRequest")
{
	m_ContentId = NULL;
	m_RightsInfo = NULL;
}

osmsMessageLicenseRequest::~osmsMessageLicenseRequest()
{
	if (m_ContentId != NULL)
		delete[] m_ContentId;

	if (m_RightsInfo != NULL)
		delete[] m_RightsInfo;
}



char* osmsMessageLicenseRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageLicenseRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<ContentId type=\"char[]\"></ContentId>" \
			"<RightsInfo type=\"char[]\"></RightsInfo>" \
		"</com.mutable.osms.common.io.message.osmsMessageLicenseRequest>";
}

char* osmsMessageLicenseRequest::encode()
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
	pDoc->setString("ContentId", getContentId());
	pDoc->setString("RightsInfo", getRightsInfo());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageLicenseRequest::decode(char* xmlText)
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
  char* tmp = pDoc->getString("ContentId");
	setContentId(tmp);
  delete[] tmp;
  tmp = pDoc->getString("RightsInfo");
	setRightsInfo(tmp);
  delete[] tmp;

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageLicenseRequest::getContentId()
{
	return m_ContentId;
}

void osmsMessageLicenseRequest::setContentId(char* p_ContentId)
{
	if (m_ContentId != NULL)
	{
		delete[] m_ContentId;
		m_ContentId = NULL;
	}
	if (p_ContentId != NULL)
	{
		m_ContentId = new char[strlen(p_ContentId)+1];
		strcpy(m_ContentId, p_ContentId);
	}
}


char* osmsMessageLicenseRequest::getRightsInfo()
{
	return m_RightsInfo;
}

void osmsMessageLicenseRequest::setRightsInfo(char* p_RightsInfo)
{
	if (m_RightsInfo != NULL)
	{
		delete[] m_RightsInfo;
		m_RightsInfo = NULL;
	}
	if (p_RightsInfo != NULL)
	{
		m_RightsInfo = new char[strlen(p_RightsInfo)+1];
		strcpy(m_RightsInfo, p_RightsInfo);
	}
}
