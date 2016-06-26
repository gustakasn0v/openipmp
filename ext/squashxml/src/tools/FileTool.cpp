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

#include "squashxml/tools/FileTool.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#	include <io.h>
#	define open		_open
#	define close	_close
#	define read		_read
#	define write	_write
#	define stat		_stat
#	define fstat	_fstat
#	define O_RDONLY _O_RDONLY
#	define O_BINARY _O_BINARY
#	define O_CREAT	_O_CREAT
#	define O_WRONLY _O_WRONLY
#	define S_IREAD	_S_IREAD
#	define S_IWRITE _S_IWRITE
#else
#	define O_BINARY 0	// no support for O_BINARY in Linux
#	include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>

ByteArray* FileTool::readFile(const char* filename)
{

	int fd = open(filename, O_RDONLY | O_BINARY );
	if (fd == -1)
		return NULL;
	struct stat fileStat;
	fstat(fd, &fileStat);

	ByteArray* bytes = NULL;
	if (fileStat.st_size > 0)
	{
		char* strBuffer = new char[fileStat.st_size];
		int n = read(fd, strBuffer, fileStat.st_size);
		bytes = new ByteArray(strBuffer, n);
		delete[] strBuffer;
	}

	close(fd);
	return bytes;
}

bool FileTool::writeFile(const char* filename, ByteArray* bytes)
{
	int fd = open(filename, (O_CREAT | O_WRONLY | O_BINARY ), (S_IREAD | S_IWRITE));
	if (fd == -1)
		return false;

	if (bytes != NULL)
		write(fd, bytes->data(), bytes->length());	// TODO: Make sure all were written

	close(fd);
	return true;
}

