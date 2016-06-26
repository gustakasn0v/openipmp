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

#include "squashxml/xml/XMLMessage.h"
#include "squashxml/example/XMLMessageExampleBase.h"
#include "squashxml/example/XMLMessageGenericError.h"
#include "squashxml/example/XMLMessageWhatDayOfWeek.h"
#include "squashxml/example/XMLMessageWhatDayOfWeekResponse.h"


static XMLMessageGenericError sXMLMessageGenericError;

XMLMessageExampleBase::XMLMessageExampleBase(int messageType, const char* name)
	: XMLMessageBean(messageType, name)
{
	static bool bFirstTime = true;
	if (bFirstTime == true)
	{
		bFirstTime = false;
		XMLMessage::registerApplicationMessageBean((XMLMessageBean*)&sXMLMessageGenericError);
	}
}

XMLMessageExampleBase::~XMLMessageExampleBase()
{
}


XMLMessageBean* XMLMessageExampleBase::getXMLMessageBean(int messageType)
{
	XMLMessageBean* resultBean = (XMLMessageBean*)NULL;

	switch (messageType)
	{
		case XMLMessageExampleBase::GENERIC_ERROR:
		{
			resultBean = new XMLMessageGenericError();
			break;
		}
		case XMLMessageExampleBase::WHAT_DAY_OF_WEEK:
		{
			resultBean = new XMLMessageWhatDayOfWeek();
			break;
		}
		case XMLMessageExampleBase::WHAT_DAY_OF_WEEK_RESPONSE:
		{
			resultBean = new XMLMessageWhatDayOfWeekResponse();
			break;
		}

		default:
		{
			break;
		}
	}

	return resultBean;
}
