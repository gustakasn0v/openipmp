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

#ifndef ByteArray_H
#define ByteArray_H


#ifdef STLCLASSSES

#ifdef WIN32
#pragma warning(disable:4786)
#endif
// # include <memory>

#else

#include <memory.h>

#endif

class ByteArray
{
public:
	ByteArray(char* bs, int len)
	{
		nBytes = len;
		if (nBytes > 0)
		{
			bytes = new char[nBytes+1];
			memcpy(bytes, bs, nBytes);
			bytes[nBytes] = '\0';
		}
	}

	~ByteArray()
	{
		if (nBytes > 0)
			delete[] bytes;
	}

	int length()
	{
		return nBytes;
	}

	const char* data()
	{
		return (const char*)bytes;
	}

private:
	char* bytes;
	int nBytes;
};

#endif // ByteArray_H
