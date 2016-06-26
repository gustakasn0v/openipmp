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

#include "io/message/osmsMessageRegisterUserResponse.h"


osmsMessageRegisterUserResponse::osmsMessageRegisterUserResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_REGISTER_USER_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageRegisterUserResponse")
{
	m_UserName = NULL;
	m_UserSecurityStore = NULL;
}

osmsMessageRegisterUserResponse::~osmsMessageRegisterUserResponse()
{
	if (m_UserName != NULL)
		delete[] m_UserName;

	if (m_UserSecurityStore != NULL)
		delete m_UserSecurityStore;
}


char* osmsMessageRegisterUserResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageRegisterUserResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<UserName type=\"char[]\"></UserName>" \
			"<UserSecurityStore type=\"byte[]\"></UserSecurityStore>" \
		"</com.mutable.osms.common.io.message.osmsMessageRegisterUserResponse>";
}

char* osmsMessageRegisterUserResponse::encode()
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
	pDoc->setBytes("UserSecurityStore", getUserSecurityStore());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageRegisterUserResponse::decode(char* xmlText)
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
	setUserSecurityStore(pDoc->getBytes("UserSecurityStore"));

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageRegisterUserResponse::getUserName()
{
	return m_UserName;
}

void osmsMessageRegisterUserResponse::setUserName(char* UserName)
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

ByteArray* osmsMessageRegisterUserResponse::getUserSecurityStore()
{
	return m_UserSecurityStore;
}

void osmsMessageRegisterUserResponse::setUserSecurityStore(ByteArray* UserSecurityStore)
{
	if (m_UserSecurityStore != NULL)
	{
		delete m_UserSecurityStore;
		m_UserSecurityStore = NULL;
	}
	if (UserSecurityStore != NULL)
	{
		m_UserSecurityStore = new ByteArray((char*)UserSecurityStore->data(), UserSecurityStore->length());
	}
}

