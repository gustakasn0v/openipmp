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

#ifdef WIN32
#	include <io.h>
#else
#	include <unistd.h>
#endif
#include <ctype.h>
#include <stdio.h>

#include "squashxml/xml/XMLMessage.h"
#include "squashxml/example/XMLMessageGenericError.h"


static XMLMessageBean *m_ApplicationBean = NULL;

XMLMessage::XMLMessage()
	: MessageContainer()
{
}

XMLMessageBean* XMLMessage::getBean()
{
	XMLMessageBean* resultBean = (XMLMessageBean*)NULL;

	if (!hasPayload())
		return resultBean;	// NULL


	char *data = (char*)getPayload()->data();
	if (data == NULL)
		return resultBean;	// NULL


	//
	// Hugh hack to get message number quickly.
	//
		const char *messagePrefix = "<MessageType type=\"int\">", *messageSuffix = "</MessageType>";
		char *messnumBegin = NULL, *messnumEnd = NULL;
		if ((messnumBegin = strstr(data, messagePrefix)) == NULL)
			return resultBean;	// NULL
		if ((messnumEnd = strstr(messnumBegin, messageSuffix)) == NULL)
			return resultBean;	// NULL

		// Should be replaced with a call to xml.datatype.DataTypeInt::decode()
		messnumBegin += strlen(messagePrefix);
		char *cp = messnumBegin;
		while (cp != messnumEnd)
		{
			if (!isdigit(*cp))	// Check for junk
				return resultBean;	// NULL
			cp++;
		}
		int numLen = messnumEnd - messnumBegin;
		char *strNum = new char[numLen+1];
/** CJM 09-09-05..  fix for memory instability  */
		memset( strNum, 0x00, numLen+1 );
		strncpy(strNum, messnumBegin, numLen);
	int mNum = atoi(strNum);
		delete[] strNum;

	if (m_ApplicationBean != NULL)
		resultBean = m_ApplicationBean->getXMLMessageBean(mNum);

	if (resultBean != NULL)
		resultBean->decode(data);

	return resultBean;
}

void XMLMessage::setBean(XMLMessageBean* bean)
{
	char *xmlText = bean->encode();
 	if (xmlText != NULL)
	{
		ByteArray bytes(xmlText, strlen(xmlText));
		setPayload(&bytes);
		free(xmlText);
	}
	else
		setPayload(NULL);
}



void XMLMessage::registerApplicationMessageBean(XMLMessageBean* applicationBean)
{
	m_ApplicationBean = applicationBean;
}
