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

#include "io/message/osmsMessageAcquireUserKeyStoreResponse.h"


osmsMessageAcquireUserKeyStoreResponse::osmsMessageAcquireUserKeyStoreResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageAcquireUserKeyStoreResponse")
{
	m_UserName = NULL;
	m_UserSecurityStore = NULL;
}

osmsMessageAcquireUserKeyStoreResponse::~osmsMessageAcquireUserKeyStoreResponse()
{
	if (m_UserName != NULL)
		delete[] m_UserName;

	if (m_UserSecurityStore != NULL)
		delete m_UserSecurityStore;
}


char* osmsMessageAcquireUserKeyStoreResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageAcquireUserKeyStoreResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<UserName type=\"char[]\"></UserName>" \
			"<UserSecurityStore type=\"byte[]\"></UserSecurityStore>" \
		"</com.mutable.osms.common.io.message.osmsMessageAcquireUserKeyStoreResponse>";
}

char* osmsMessageAcquireUserKeyStoreResponse::encode()
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

bool osmsMessageAcquireUserKeyStoreResponse::decode(char* xmlText)
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
    char* tmp = pDoc->getString("UserName");
    setUserName(tmp);
    delete[] tmp;
        
	ByteArray* bytes = pDoc->getBytes("UserSecurityStore");
	setUserSecurityStore(bytes);

	/*** CJM 11-11-05 changed delete[] to delete */
	delete bytes;

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageAcquireUserKeyStoreResponse::getUserName()
{
	return m_UserName;
}

void osmsMessageAcquireUserKeyStoreResponse::setUserName(char* UserName)
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

ByteArray* osmsMessageAcquireUserKeyStoreResponse::getUserSecurityStore()
{
	return m_UserSecurityStore;
}

void osmsMessageAcquireUserKeyStoreResponse::setUserSecurityStore(ByteArray* UserSecurityStore)
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

