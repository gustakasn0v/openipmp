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

#ifndef DataTypeBinaryHex_H
#define DataTypeBinaryHex_H

#include "squashxml/tools/ByteArray.h"
#include "squashxml/xml/datatype/DataTypeCodex.h"

#include "squashxml/tools/FileLogger.h"


class DataTypeBinaryHex : public DataTypeCodex
{
public:


	char* getShortName()
	{
		return "base16";
	}


	char* encode(void* data)
	{
		ByteArray* bytes = (ByteArray*)data;
		if (bytes == NULL)
			return "";

		int len = bytes->length();

		char* result = new char[(2*len)+1];
		char* cp = result;
        for (int i = 0; i < len; i++)
        {
            int bi = (int)(bytes->data()[i]);
            if (bi < 0)
                bi += 256;
            int hr = bi % 16;
            char cr;
            if (hr < 10)
              cr = (char)((int)'0' + hr);
            else
              cr = (char)((int)'A' + (hr - 10));
            int hl = (bi - hr) / 16;
            char cl;
            if (hl < 10)
              cl = (char)((int)'0' + hl);
            else
              cl = (char)((int)'A' + (hl - 10));

			*cp++ = cl;
			*cp++ = cr;
        }
		*cp = '\0';


		return result;
	}

	void* decode(char* str)
	{
		if (str == NULL || *str == '\0')
			return NULL;

		int len = strlen(str);
		char *bytes = new char[len/2];

        for (int i = 0; i < len - 1; i += 2)
        {
          char cl = str[i];
          char cr = str[i+1];

          int hl;
          if (cl < 'A')
            hl = (int)cl - (int)'0';
          else
            hl = ((int)cl - (int)'A') + 10;

          int hr;
          if (cr < 'A')
            hr = (int)cr - (int)'0';
          else
            hr = ((int)cr - (int)'A') + 10;

          bytes[i/2] = (char)((hl * 16) + hr);
        }

		ByteArray *pByteArray = new ByteArray(bytes, len/2);
		delete[] bytes;

		return pByteArray;
	}

};


#endif // DataTypeBinaryHex_H
