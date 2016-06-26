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

#ifndef DataTypeInt_H
#define DataTypeInt_H

#include <stdlib.h>

class DataTypeInt : public DataTypeCodex
{
public:
	char* getShortName()
	{
		return "int";
	}

	char* encode(void* data)
	{
		if (data == NULL)
			return "";
		static char iStr[64];
		sprintf(iStr, "%d", (int)data);
		return iStr;
	}

	void* decode(char* str)
	{
		static int i;
		if (str != NULL && *str != '\0')
			i = atoi(str);
		else
			i = 0;
		return (void*)i;
	}
};

#endif // DataTypeInt_H
