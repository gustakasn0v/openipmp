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

#ifndef Date_H
#define Date_H


#include <stdlib.h>
#include <time.h>

class Date
{
public:

	Date()
	{
		m_year = 1970;
		m_mon = 1;
		m_day = 1;
		m_hour = 0;
		m_min = 0;
		m_sec = 0;
	}

	void now()  //  ???
	{
		time_t ltime;
		time(&ltime);
		struct tm *today = localtime(&ltime);

		setYear(today->tm_year + 1900);
		setMonth(today->tm_mon + 1);
		setDay(today->tm_mday);
		setHours(today->tm_hour);
		setMinutes(today->tm_min);
		setSeconds(today->tm_sec);
	}

	Date(Date* pSrcDate)
	{
		if (pSrcDate != NULL)
		{
			setYear(pSrcDate->getYear());
			setMonth(pSrcDate->getMonth());
			setDay(pSrcDate->getDay());
			setHours(pSrcDate->getHours());
			setMinutes(pSrcDate->getMinutes());
			setSeconds(pSrcDate->getSeconds());
		}
	}

	int getYear()			{ return m_year; }
	void setYear(int y)		{ m_year = y; }

	int getMonth()			{ return m_mon; }
	void setMonth(int m)	{ m_mon = m; }

	int getDay()			{ return m_day; }
	void setDay(int d)		{ m_day = d; }

	int getHours()			{ return m_hour; }
	void setHours(int h)	{ m_hour = h; }

	int getMinutes()		{ return m_min; }
	void setMinutes(int m)	{ m_min = m; }

	int getSeconds()		{ return m_sec; }
	void setSeconds(int s)  { m_sec = s; }

private:
	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
};

#endif // Date_H
