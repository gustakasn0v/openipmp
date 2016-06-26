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

#ifndef Message_Container_H
#define Message_Container_H

#include "squashxml/tools/ByteArray.h"

#define HEADER_SIZE		8
#define MAX_PACKET_SIZE 4096

class MessageContainer
{
public:
	MessageContainer();
	~MessageContainer();

    char* getMessage();

    ByteArray* getPayload();
    void setPayload(ByteArray* blob);
    bool hasPayload();

    // Length of PayLoad.
    // Don't write a setLength; leave it to JAVA to determine length of char* payload
    // Length is encoded as a string of length HEADER_SIZE with leading 0's
    // (e.g. HEADER_SIZE = 8, payload len of 2048 chars, encode len = 00002048)
    int getLength();
    const char* encodeLength();
    int decodeLength(char* blob);


private:
	ByteArray* payload;
};

#endif // Message_Container_H
