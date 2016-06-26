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

#include "io/message/osmsMessageQueryResponse.h"


osmsMessageQueryResponse::osmsMessageQueryResponse()
	: osmsMessage(osmsMessage::osmsMESSAGE_QUERY_RESPONSE, "com.mutable.osms.common.io.message.osmsMessageQueryResponse")
{
	m_Results = NULL;
	m_Heading = NULL;
	m_Length=0;
}

osmsMessageQueryResponse::~osmsMessageQueryResponse()
{
	if (m_Results != NULL)
		delete[] m_Results;
	if (m_Results != NULL)
		delete[] m_Heading;
}

char* osmsMessageQueryResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageQueryResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<Results type=\"char[]\"></Results>" \
			"<Heading type=\"char[]\"></Heading>" \
			"<Length type=\"int\"></Length>" \
		"</com.mutable.osms.common.io.message.osmsMessageQueryResponse>";
}

char* osmsMessageQueryResponse::encode()
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
	pDoc->setString("Results", getResults());
	pDoc->setString("Heading", getHeading());
	pDoc->setInteger("Length", getLength());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageQueryResponse::decode(char* xmlText)
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
	setResults(pDoc->getString("Results"));
	setHeading(pDoc->getString("Heading"));
	setLength(pDoc->getInteger("Length"));

	delete pDoc;

	return true;
}



//bean properties
char* osmsMessageQueryResponse::getResults()
{
	return m_Results;
}
void osmsMessageQueryResponse::setResults(char* Results)
{
	if (m_Results != NULL)
	{
		delete[] m_Results;
		m_Results = NULL;
	}
	if (Results != NULL)
	{
		m_Results = new char[strlen(Results)+1];
		strcpy(m_Results, Results);
	}
}

char* osmsMessageQueryResponse::getHeading()
{
	return m_Heading;
}
void osmsMessageQueryResponse::setHeading(char* Heading)
{
	if (m_Heading != NULL)
	{
		delete[] m_Heading;
		m_Heading = NULL;
	}
	if (Heading != NULL)
	{
		m_Heading = new char[strlen(Heading)+1];
		strcpy(m_Heading, Heading);
	}
}
int osmsMessageQueryResponse::getLength()
{
	return m_Length;
}
void osmsMessageQueryResponse::setLength(int Length)
{
	m_Length=Length;
}
