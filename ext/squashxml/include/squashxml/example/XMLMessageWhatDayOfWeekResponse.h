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

#ifndef XMLMessageWhatDayOfWeekResponse_H
#define XMLMessageWhatDayOfWeekResponse_H

#include "squashxml/xml/XMLMessageBean.h"
#include "squashxml/example/XMLMessageExampleBase.h"

class XMLMessageWhatDayOfWeekResponse : public XMLMessageExampleBase
{

public:
	XMLMessageWhatDayOfWeekResponse();
	virtual ~XMLMessageWhatDayOfWeekResponse();

	virtual char* encode();
	virtual bool decode(char* xmlText);
	virtual char* xmlTemplate();

	//bean properties
	char* getDayOfWeekDateInQuestion();
	void setDayOfWeekDateInQuestion(char* dayOfWeekDateInQuestion);


private:
	char* m_DayOfWeekDateInQuestion;
};

#endif // XMLMessageWhatDayOfWeekResponse