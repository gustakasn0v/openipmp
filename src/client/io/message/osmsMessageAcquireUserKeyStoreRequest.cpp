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

#include "io/message/osmsMessageAcquireUserKeyStoreRequest.h"

osmsMessageAcquireUserKeyStoreRequest::osmsMessageAcquireUserKeyStoreRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_ACQUIRE_USER_KEY_STORE_REQUEST, "com.mutable.osms.common.io.message.osmsMessageAcquireUserKeyStoreRequest")
{
	m_UserName = NULL;
	m_Password = NULL;
}

osmsMessageAcquireUserKeyStoreRequest::~osmsMessageAcquireUserKeyStoreRequest()
{
	if (m_UserName != NULL)
		delete[] m_UserName;

	if (m_Password != NULL)
		delete[] m_Password;
}


char* osmsMessageAcquireUserKeyStoreRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageAcquireUserKeyStoreRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<UserName type=\"char[]\"></UserName>" \
			"<Password type=\"char[]\"></Password>" \
		"</com.mutable.osms.common.io.message.osmsMessageAcquireUserKeyStoreRequest>";
}

char* osmsMessageAcquireUserKeyStoreRequest::encode()
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
	pDoc->setString("UserName", getUserName());
	pDoc->setString("Password", getPassword());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageAcquireUserKeyStoreRequest::decode(char* xmlText)
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
	setUserName(pDoc->getString("UserName"));
	setPassword(pDoc->getString("Password"));

	delete pDoc;

	return true;
}




//bean properties
char* osmsMessageAcquireUserKeyStoreRequest::getUserName()
{
	return m_UserName;
}

void osmsMessageAcquireUserKeyStoreRequest::setUserName(char* UserName)
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

char* osmsMessageAcquireUserKeyStoreRequest::getPassword()
{
	return m_Password;
}

void osmsMessageAcquireUserKeyStoreRequest::setPassword(char* Password)
{
	if (m_Password != NULL)
	{
		delete[] m_Password;
		m_Password = NULL;
	}
	if (Password != NULL)
	{
		m_Password = new char[strlen(Password)+1];
		strcpy(m_Password, Password);
	}
}
