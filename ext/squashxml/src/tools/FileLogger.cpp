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

#include "squashxml/tools/FileLogger.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#	include <io.h>
#	define open		_open
#	define close	_close
#	define O_CREAT	_O_CREAT
#	define O_APPEND	_O_APPEND
#	define O_WRONLY _O_WRONLY
#	define S_IREAD	_S_IREAD
#	define S_IWRITE _S_IWRITE
#else
#	include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "squashxml/tools/FileTool.h"


/** CJM 9/5/05  cheap hack to fix log write issues... we need to
	move away from this global instance of gLogger
*/
#ifdef MACOSX
FileLogger glogFile("/Library/Logs/DRMManager.log");
#else
FileLogger glogFile("default.log");
#endif
FileLogger* gLogger = &glogFile;

FileLogger::FileLogger(const char* filename)
	: Logger()
{
	fd = open(filename, (O_CREAT | O_APPEND | O_WRONLY), (S_IREAD | S_IWRITE));
	if (fd == -1)
		printf("ERROR: Failed to open log file!\n");
}

FileLogger::~FileLogger()
{
	if (fd != -1)
		close(fd);
}

bool FileLogger::write(const char* str)
{
	if (str == NULL || fd == -1)
		return false;

#ifdef WIN32
#	define write	_write
#endif

	if (::write(fd, str, strlen(str)) == -1)
		return false;

	if (::write(fd, "\r\n", 2) == -1)
		return false;

#ifdef WIN32
#	ifdef write
#	undef write
#	endif
#endif

	return true;
}

