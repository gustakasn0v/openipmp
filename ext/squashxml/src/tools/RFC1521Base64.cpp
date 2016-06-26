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

#include <string.h>
#include "squashxml/tools/RFC1521Base64.h"
#include "squashxml/tools/FileLogger.h"

static char alphabet[] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 	//  0 -  7
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 	//  8 - 15
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 	// 16 - 23
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 	// 24 - 31
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 	// 32 - 39
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 	// 40 - 47
	'w', 'x', 'y', 'z', '0', '1', '2', '3', 	// 48 - 55
	'4', '5', '6', '7', '8', '9', '+', '/'		// 56 - 63
};
static char reverseAlphabet[] =
{
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	//   0 -   7
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	//   8 -  15
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	//  16 -  23
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	//  24 -  31
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	//  32 -  39
	-1,  -1,  -1,  62,  -1,  -1,  -1,  63,  	//  40 -  47
	52,  53,  54,  55,  56,  57,  58,  59,  	//  48 -  55
	60,  61,  -1,  -1,  -1,  -1,  -1,  -1,  	//  56 -  63
	-1,   0,   1,   2,   3,   4,   5,   6,  	//  64 -  71
	 7,   8,   9,  10,  11,  12,  13,  14,  	//  72 -  79
	15,  16,  17,  18,  19,  20,  21,  22,  	//  80 -  87
	23,  24,  25,  -1,  -1,  -1,  -1,  -1,  	//  88 -  95
	-1,  26,  27,  28,  29,  30,  31,  32,  	//  96 - 103
	33,  34,  35,  36,  37,  38,  39,  40,  	// 104 - 111
	41,  42,  43,  44,  45,  46,  47,  48,  	// 112 - 119
	49,  50,  51,  -1,  -1,  -1,  -1,  -1,  	// 120 - 127
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 128 - 135
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 136 - 143
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 144 - 151
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 152 - 159
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 160 - 167
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 168 - 175
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 176 - 183
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 184 - 191
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 192 - 199
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 200 - 207
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 208 - 215
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 216 - 223
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 224 - 231
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 232 - 239
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  	// 240 - 247
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1		// 248 - 255
};

static char padChar = '=';
static char carrReturn = '\r';	// 0D
static char lineFeed = '\n';	// 0A
static int maxline = 76;

static int bits11111100 = 252, bits11110000 = 240, bits11000000 = 192;
static int bits00000011 = 3  , bits00001111 = 15 , bits00111111 = 63;


char* RFC1521Base64::encode(ByteArray* bytes)
{
	if (bytes == NULL)
		return "";

	int len = bytes->length();
	int newlen = ((((len - (len % 3)) / 3) + 1) * 4);
	int linebr = 2 * ((newlen - (newlen % maxline)) / maxline);
	newlen += linebr + 1;
	char* result = new char[newlen];
	char* cp = result;

	int count = 0;

	for (int i = 0; i < len; i += 3)
	{
		int i1 = -1, i2 = -1, i3 = -1;
		int b1, b2, b3, b4;
		i1 = (int)(bytes->data()[i]);
		b1 = (i1 & bits11111100) >> 2;
		*cp++ = alphabet[b1];

		if (i + 1 < len)
		{
			i2 = (int)(bytes->data()[i+1]);
			b2 = ((i1 & bits00000011) << 4) | ((i2 & bits11110000) >> 4);
			*cp++ = alphabet[b2];

			if (i + 2 < len)
			{
				i3 = (int)(bytes->data()[i+2]);
				b3 = ((i2 & bits00001111) << 2) | ((i3 & bits11000000) >> 6);
				*cp++ = alphabet[b3];
				b4 = i3 & bits00111111;
				*cp++ = alphabet[b4];

				count += 4;
				if (count == maxline)
				{
					*cp++ = carrReturn;
					*cp++ = lineFeed;
					count = 0;
				}
			}
			else
			{
				b3 = (i2 & bits00001111) << 2;
				*cp++ = alphabet[b3];
				*cp++ = padChar;
			}
		}
		else
		{
			b2 = (i1 & bits00000011) << 4;
			*cp++ = alphabet[b2];
			*cp++ = padChar;
			*cp++ = padChar;
		}

	}
	*cp = '\0';

	return result;
}


ByteArray* RFC1521Base64::decode(char* str)
{
	if (str == NULL || *str == '\0')
		return NULL;

	int len = strlen(str); // maybe more than needed if \r\n exist

	int newlen = (int)(len / 4) * 3;
	char* bytes = new char[newlen];
	int bidx = 0;

	int i = 0, bs[4];
        while (i < len)
        {
		int nbs = 0;
		for (int b = 0; b < 4 && i < len; b++)
		{
			while (i < len && (str[i] == carrReturn || str[i] == lineFeed))
				i++;

			if (i < len && str[i] == padChar)
				break;

			if (i < len)
			{
				if ((bs[b] = reverseAlphabet[str[i++]]) == -1)
				{
					i--;

					char errStr[256];
					sprintf(errStr, "ERROR: At position %d, char=[%c] (int=[%d]) is outside of the base64 alpahbet!", i, str[i], str[i]);
					gLogger->logError(errStr);
					delete[] bytes;
					return NULL;
				}
				nbs++;
			}
		}

		switch (nbs)
		{
			case 4:
			{
				bytes[bidx++] = (bs[0] << 2) | ((bs[1] & bits11110000) >> 4);
				bytes[bidx++] = ((bs[1] & bits00001111) << 4) | ((bs[2] & bits11111100) >> 2);
				bytes[bidx++] = ((bs[2] & bits00000011) << 6) | (bs[3]);
				break;
			}
			case 3:
			{
				bytes[bidx++] = (bs[0] << 2) | ((bs[1] & bits11110000) >> 4);
				bytes[bidx++] = ((bs[1] & bits00001111) << 4) | ((bs[2] & bits11111100) >> 2);
				break;
			}
			case 2:
			{
				bytes[bidx++] = (bs[0] << 2) | ((bs[1] & bits11110000) >> 4);
				break;
			}
			default:
			{
				// problems
				break;
			}
		}

		if (i < len && str[i] == padChar)
			break;
        }

	if (bidx == 0)
		return NULL;

	ByteArray *pByteArray = new ByteArray(bytes, bidx);
	delete[] bytes;
	return pByteArray;

}
