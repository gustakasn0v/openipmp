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

#include "squashxml/example/XMLMessageGenericError.h"

XMLMessageGenericError::XMLMessageGenericError()
	: XMLMessageExampleBase(XMLMessageExampleBase.GENERIC_ERROR, "squashxml.example.XMLMessageGenericError")
{
	m_ErrorString = NULL;
}

XMLMessageGenericError::~XMLMessageGenericError()
{
	if (m_ErrorString != NULL)
		delete[] m_ErrorString;
}

char* XMLMessageGenericError::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<squashxml.example.XMLMessageGenericError>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<ErrorString type=\"char[]\"></ErrorString>" \
		"</squashxml.example.XMLMessageGenericError>";
}

char* XMLMessageGenericError::encode()
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
	pDoc->setString("ErrorString", getErrorString());

	char *result = pDoc->encode();

	delete pDoc;
	return result;
}

bool XMLMessageGenericError::decode(char* xmlText)
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
	setErrorString(pDoc->getString("ErrorString"));

	delete pDoc;
	return true;
}



//bean properties
char* XMLMessageGenericError::getErrorString()
{
	return m_ErrorString;
}

void XMLMessageGenericError::setErrorString(char* errorString)
{
	if (m_ErrorString != NULL)
	{
		delete[] m_ErrorString;
		m_ErrorString = NULL;
	}
	if (errorString != NULL)
	{
		m_ErrorString = new char[strlen(errorString)+1];
		strcpy(m_ErrorString, errorString);
	}
}
