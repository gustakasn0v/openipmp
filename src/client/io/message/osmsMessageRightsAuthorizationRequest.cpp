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

#include "io/message/osmsMessageRightsAuthorizationRequest.h"


osmsMessageRightsAuthorizationRequest::osmsMessageRightsAuthorizationRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_RIGHTS_AUTHORIZATION_REQUEST, "com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest")
{
	m_ContentId=NULL;
	m_UserName=NULL;
	m_StartDate=NULL;
	m_EndDate=NULL;
	m_LicenseType=NULL;
}

osmsMessageRightsAuthorizationRequest::~osmsMessageRightsAuthorizationRequest()
{
	if (m_ContentId != NULL)
		delete[] m_ContentId;

	if (m_UserName != NULL)
		delete[] m_UserName;

	if (m_StartDate != NULL)
		delete m_StartDate;

	if (m_EndDate != NULL)
		delete m_EndDate;

	if (m_LicenseType != NULL)
		delete m_LicenseType;
}


char* osmsMessageRightsAuthorizationRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<ContentId type=\"char[]\"></ContentId>" \
			"<UserName type=\"char[]\"></UserName>" \
			"<StartDate type=\"date\"></StartDate>" \
			"<EndDate type=\"date\"></EndDate>" \
			"<LicenseType type=\"char[]\"></LicenseType>" \
		"</com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationRequest>";
}

char* osmsMessageRightsAuthorizationRequest::encode()
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
	pDoc->setString("UserName", getUserName());
	pDoc->setDate("StartDate", getStartDate());
	pDoc->setDate("EndDate", getEndDate());
	pDoc->setString("LicenseType", getLicenseType());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageRightsAuthorizationRequest::decode(char* xmlText)
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
	setContentId(pDoc->getString("ContentId"));
	setUserName(pDoc->getString("UserName"));
	setStartDate(pDoc->getDate("StartDate"));
	setEndDate(pDoc->getDate("EndDate"));
	setLicenseType(pDoc->getString("LicenseType"));

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageRightsAuthorizationRequest::getContentId()
{
	return m_ContentId;
}

void osmsMessageRightsAuthorizationRequest::setContentId(char* ContentId)
{
	if (m_ContentId != NULL)
	{
		delete[] m_ContentId;
		m_UserName = NULL;
	}
	if (ContentId != NULL)
	{
		m_ContentId = new char[strlen(ContentId)+1];
		strcpy(m_ContentId, ContentId);
	}
}




char* osmsMessageRightsAuthorizationRequest::getUserName()
{
	return m_UserName;
}

void osmsMessageRightsAuthorizationRequest::setUserName(char* UserName)
{
	if (m_UserName != NULL)
	{
		delete[] m_UserName;
		m_UserName = NULL;
	}
	if (UserName != NULL)
	{
		m_UserName = new char[strlen(UserName)+1];
		strcpy(m_UserName, UserName);
	}
}


Date* osmsMessageRightsAuthorizationRequest::getStartDate()
{
	return m_StartDate;
}

void osmsMessageRightsAuthorizationRequest::setStartDate(Date* StartDate)
{
	if (m_StartDate != NULL)
	{
		delete m_StartDate;
		m_StartDate = NULL;
	}
	if (StartDate != NULL)
	{
		m_StartDate = new Date(StartDate);
		
	}
}

Date* osmsMessageRightsAuthorizationRequest::getEndDate()
{
	return m_EndDate;
}

void osmsMessageRightsAuthorizationRequest::setEndDate(Date* EndDate)
{
	if (m_EndDate != NULL)
	{
		delete m_EndDate;
		m_EndDate = NULL;
	}
	if (EndDate != NULL)
	{
		m_EndDate = new Date(EndDate);
		
	}
}

char* osmsMessageRightsAuthorizationRequest::getLicenseType()
{
	return m_LicenseType;
}

void osmsMessageRightsAuthorizationRequest::setLicenseType(char* LicenseType)
{
	if (m_LicenseType != NULL)
	{
		delete[] m_LicenseType;
		m_LicenseType = NULL;
	}
	if (LicenseType != NULL)
	{
		m_LicenseType = new char[strlen(LicenseType)+1];
		strcpy(m_LicenseType, LicenseType);
	}
}

