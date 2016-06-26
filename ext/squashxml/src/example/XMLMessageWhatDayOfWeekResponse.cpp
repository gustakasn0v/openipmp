/* ***** BEGIN LICENSE BLOCK *****
 *	The contents of this file are subject to the Mozilla Public License
 *	Version 1.1 (the "License"); you may not use this file except in
 *	compliance with the License. You may obtain a copy of the License at
 *	http://www.mozilla.org/MPL/
 *
 *	Software distributed under the License is distributed on an "AS IS"
 *	basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *	License for the specific language governing rights and limitations
 *	under the License.
 *
 *	The Original Code is SquashXML.
 *
 *	The Initial Developer of the Original Code is Ayman A. Gebrail.
 *	Portions created by Ayman A. Gebrail are
 *	Copyright (C) 2002 Ayman A. Gebrail. All Rights Reserved.
 *
 *  Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

#include "squashxml/example/XMLMessageWhatDayOfWeekResponse.h"


XMLMessageWhatDayOfWeekResponse::XMLMessageWhatDayOfWeekResponse()
	: XMLMessageExampleBase(XMLMessageExampleBase.WHAT_DAY_OF_WEEK_RESPONSE, "squashxml.example.XMLMessageWhatDayOfWeekResponse")
{
	m_DayOfWeekDateInQuestion = NULL;
}

XMLMessageWhatDayOfWeekResponse::~XMLMessageWhatDayOfWeekResponse()
{
	if (m_DayOfWeekDateInQuestion != NULL)
		delete[] m_DayOfWeekDateInQuestion;
}


char* XMLMessageWhatDayOfWeekResponse::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<squashxml.message.XMLMessageWhatDayOfWeekResponse>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<DayOfWeekDateInQuestion type=\"char[]\"></DayOfWeekDateInQuestion>" \
		"</squashxml.message.XMLMessageWhatDayOfWeekResponse>";
}

char* XMLMessageWhatDayOfWeekResponse::encode()
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
	pDoc->setString("DayOfWeekDateInQuestion", getDayOfWeekDateInQuestion());

	char *result = pDoc->encode();

	delete pDoc;
	return result;
}

bool XMLMessageWhatDayOfWeekResponse::decode(char* xmlText)
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
	setDayOfWeekDateInQuestion(pDoc->getString("DayOfWeekDateInQuestion"));

	delete pDoc;
	return true;
}



//bean properties
char* XMLMessageWhatDayOfWeekResponse::getDayOfWeekDateInQuestion()
{
	return m_DayOfWeekDateInQuestion;
}
void XMLMessageWhatDayOfWeekResponse::setDayOfWeekDateInQuestion(char* dayOfWeekDateInQuestion)
{
	if (m_DayOfWeekDateInQuestion != NULL)
	{
		delete[] m_DayOfWeekDateInQuestion;
		m_DayOfWeekDateInQuestion = NULL;
	}
	if (dayOfWeekDateInQuestion != NULL)
	{
		m_DayOfWeekDateInQuestion = new char[strlen(dayOfWeekDateInQuestion)+1];
		strcpy(m_DayOfWeekDateInQuestion, dayOfWeekDateInQuestion);
	}
}

