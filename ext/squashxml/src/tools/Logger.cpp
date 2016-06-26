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

#include "squashxml/tools/Logger.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#	include <io.h>
#else
#	include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>

Logger::Logger()
{

}

Logger::~Logger()
{

}

bool Logger::logInfo(const char* str)
{
	sprintf(m_TempStr, "<<INFO >> %s - %s", getDateTime(), str);
	return write(m_TempStr);
}

bool Logger::logDebug(const char* str)
{
	sprintf(m_TempStr, "<<DEBUG>> %s - %s", getDateTime(), str);
	return write(m_TempStr);
}

bool Logger::logWarning(const char* str)
{
	sprintf(m_TempStr, "<<WARN >> %s - %s", getDateTime(), str);
	return write(m_TempStr);
}

bool Logger::logError(const char* str)
{
	sprintf(m_TempStr, "<<ERROR>> %s - %s", getDateTime(), str);
	return write(m_TempStr);
}

char* Logger::getDateTime()
{
	static char sDateTime[64];

	time_t ltime;
    time(&ltime);
	struct tm *today = localtime(&ltime);
	sprintf(sDateTime, "%4d-%02d-%02d %02d:%02d:%02d", today->tm_year+1900, today->tm_mon+1, today->tm_mday, today->tm_hour, today->tm_min, today->tm_sec);
	return sDateTime;
}

