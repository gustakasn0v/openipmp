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

#include "squashxml/example/XMLMessageWhatDayOfWeek.h"


XMLMessageWhatDayOfWeek::XMLMessageWhatDayOfWeek()
	: XMLMessageExampleBase(XMLMessageExampleBase.WHAT_DAY_OF_WEEK, "squashxml.example.XMLMessageWhatDayOfWeek")
{
	m_DateInQuestion = NULL;
}

XMLMessageWhatDayOfWeek::~XMLMessageWhatDayOfWeek()
{
	if (m_DateInQuestion != NULL)
		delete m_DateInQuestion;
}


char* XMLMessageWhatDayOfWeek::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<squashxml.example.XMLMessageWhatDayOfWeek>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<DateInQuestion type=\"date\"></DateInQuestion>"\
		"</squashxml.example.XMLMessageWhatDayOfWeek>";
}

char* XMLMessageWhatDayOfWeek::encode()
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
	pDoc->setDate("DateInQuestion", getDateInQuestion());

	char *result = pDoc->encode();

	delete pDoc;
	return result;
}

bool XMLMessageWhatDayOfWeek::decode(char* xmlText)
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
	setDateInQuestion(pDoc->getDate("DateInQuestion"));

	delete pDoc;
	return true;
}



//bean properties
Date* XMLMessageWhatDayOfWeek::getDateInQuestion()
{
	return m_DateInQuestion;
}
void XMLMessageWhatDayOfWeek::setDateInQuestion(Date* DateInQuestion)
{
	if (m_DateInQuestion != NULL)
	{
		delete m_DateInQuestion;
		m_DateInQuestion = NULL;
	}
	if (DateInQuestion != NULL)
	{
		m_DateInQuestion = new Date(DateInQuestion);
	}
}

