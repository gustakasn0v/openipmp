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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "squashxml/socket/MessageContainer.h"

#ifdef WIN32
#	define snprintf _snprintf
#endif


MessageContainer::MessageContainer()
{
	payload = NULL;
}

MessageContainer::~MessageContainer()
{
	if (payload != NULL)
		delete payload;
}

char* MessageContainer::getMessage()
{
	if (!this->hasPayload())
		return NULL;

	const char* header = encodeLength();
	int payloadLen = payload->length();
	char* message = new char[HEADER_SIZE + payloadLen + 1];
	memcpy(message, header, HEADER_SIZE);
	memcpy(message+HEADER_SIZE, payload->data(), payloadLen);
	message[HEADER_SIZE + payloadLen] = '\0';

	return message;
}

ByteArray* MessageContainer::getPayload()
{
	return payload;
}

void MessageContainer::setPayload(ByteArray* blob)
{
	if (payload != NULL)
	{
		delete payload;
		payload = NULL;
	}

	if (blob == NULL)
		return;

	payload = new ByteArray((char*)blob->data(), blob->length());
}

bool MessageContainer::hasPayload()
{
  if (payload == NULL)
	return false;
  else
	return true;
}

// Length of PayLoad.
// Don't write a setLength; set in setPayload
int MessageContainer::getLength()
{
	if (payload == NULL)
		return 0;
	else
		return payload->length();
}

// Length is encoded as a string of length HEADER_SIZE with leading 0's
// (e.g. HEADER_SIZE = 8, payload len of 2048 chars, encode len = 00002048
const char* MessageContainer::encodeLength()
{
  static char lenstr[HEADER_SIZE+1];
  static char lenfmt[HEADER_SIZE+5];
  sprintf(lenfmt, "%%0%dd", HEADER_SIZE);

  snprintf(lenstr, HEADER_SIZE+1, lenfmt, payload->length());

  return lenstr;
}

int MessageContainer::decodeLength(char* blob)
{
  if (blob == NULL)
	  return 0;
  static char lenstr[HEADER_SIZE+1];
  strncpy(lenstr, blob, HEADER_SIZE);
  return atoi(lenstr);
}
