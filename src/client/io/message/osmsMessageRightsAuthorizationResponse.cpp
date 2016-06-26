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

#include "io/message/osmsMessageRightsAuthorizationResponse.h"

osmsMessageRightsAuthorizationResponse::osmsMessageRightsAuthorizationResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationResponse")
{
	m_TransactionId = NULL;
}

osmsMessageRightsAuthorizationResponse::~osmsMessageRightsAuthorizationResponse()
{
	if (m_TransactionId != NULL)
		delete[] m_TransactionId;

}


char* osmsMessageRightsAuthorizationResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<TransactionId type=\"char[]\"></TransactionId>" \
		"</com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationResponse>";
}

char* osmsMessageRightsAuthorizationResponse::encode()
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
	pDoc->setString("TransactionId", getTransactionId());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageRightsAuthorizationResponse::decode(char* xmlText)
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
	setTransactionId(pDoc->getString("TransactionId"));

	delete pDoc;

	return true;
}




//bean properties
char* osmsMessageRightsAuthorizationResponse::getTransactionId()
{
	return m_TransactionId;
}

void osmsMessageRightsAuthorizationResponse::setTransactionId(char* TransactionId)
{
	if (m_TransactionId != NULL)
	{
		delete[] m_TransactionId;
		m_TransactionId = NULL;
	}
	if (TransactionId != NULL)
	{
		m_TransactionId = new char[strlen(TransactionId)+1];
		strcpy(m_TransactionId, TransactionId);
	}
}


