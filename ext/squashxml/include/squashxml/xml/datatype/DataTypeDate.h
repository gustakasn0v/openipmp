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

#ifndef DataTypeDate_H
#define DataTypeDate_H


#include <stdlib.h>
#include <time.h>

#include "squashxml/tools/Date.h"

 //
 // "YYYY-MM-DD HH:MM:SS"
 //

class DataTypeDate : public DataTypeCodex
{
public:
	char* getShortName()
	{
		return "date";
	}

	char* encode(void* data)
	{
		if (data == NULL)
			return "";

		Date *pDate = (Date*)data;
		static char iStr[64];
		int h = pDate->getHours();
		int n = pDate->getMinutes();
		int s = pDate->getSeconds();
		if (!(h == 0 && n == 0 && s == 0))
		{

			sprintf(iStr, "%04d-%02d-%02dT%02d:%02d:%02d",
							pDate->getYear(), pDate->getMonth(), pDate->getDay(), h, n, s);
		}
		else
		{
			sprintf(iStr, "%04d-%02d-%02d",
							pDate->getYear(), pDate->getMonth(), pDate->getDay());
		}
		return iStr;
	}

	void* decode(char* str)
	{
		if (str == NULL || *str == '\0')
			return NULL;

		int m,d,y,h,n,s;
		if (strlen(str) < 10)
			return NULL;

		static Date dt;
		if (strlen(str) >= 19)
		{
			sscanf(str, "%04d-%02d-%02dT%02d:%02d:%02d", &y, &m, &d, &h, &n, &s);

			dt.setMonth(m);
			dt.setDay(d);
			dt.setYear(y);
			dt.setHours(h);
			dt.setMinutes(n);
			dt.setSeconds(s);
		}
		else
		{
			sscanf(str, "%04d-%02d-%02d", &y, &m, &d);

			dt.setMonth(m);
			dt.setDay(d);
			dt.setYear(y);
		}
		return (void*)&dt;
	}
};

#endif // DataTypeDate_H

