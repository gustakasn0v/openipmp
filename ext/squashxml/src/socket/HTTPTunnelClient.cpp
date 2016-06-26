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

#include <iostream>

#include "squashxml/socket/HTTPTunnelClient.h"
#include "squashxml/tools/FileLogger.h"

HTTPTunnelClient::HTTPTunnelClient(char* pHost, unsigned int iPort, char* pUrl, char* pUserAgent)
	: BlockingClientSocket(pHost, iPort)
{
	*session = '\0';

	if (pUrl != NULL)
		strcpy(URL, pUrl);
	else
		strcpy(URL, "/squashxml/servlet/ExampleServletServer");

	if (pUserAgent != NULL)
		strcpy(userAgent, pUserAgent);
	else
		strcpy(userAgent, "SquashXML/1.0 (Cpp;HTTPTunnelClient)");
}

HTTPTunnelClient::~HTTPTunnelClient()
{
}


bool HTTPTunnelClient::write(MessageContainer* pMessage)
{
	if (*session != '\0')
		BlockingClientSocket::open();

	char *dataCopy = pMessage->getMessage();
	if (dataCopy == NULL)
		return false;


	int length = HEADER_SIZE+pMessage->getLength();

	char slen[32];
	sprintf(slen, "%d", length);

	char header[1024];
	strcpy(header, "POST ");
	strcat(header, URL);
	strcat(header, " HTTP/1.0\r\n");
	strcat(header, "Content-Type: text/html\r\n");
	strcat(header, "Content-Length: ");  strcat(header, slen);  strcat(header, "\r\n");
	strcat(header, "User-Agent: ");	strcat(header, userAgent);	strcat(header, "\r\n");
	if (*session != '\0')
	{
		strcat(header, "Cookie: ");  strcat(header, session);  // Already contains \r\n
	}
	strcat(header, "\r\n");	// Terminate headers section
printf("Header = [%s]\n", header);

	// Concat header and content
	int lenhead = strlen(header);
	int newsize = lenhead + length;
	char *cp = new char[newsize+1];
	strcpy(cp, header);
	memcpy(cp+lenhead, dataCopy, length);
	cp[newsize] = '\0';

	// Write out entire message
	bool bDone = BlockingSocket::write(cp, newsize);

	delete[] dataCopy;
	delete[] cp;

	return bDone;
}

bool HTTPTunnelClient::read(MessageContainer* pMessage)
{
	// Strip HTTP header
	//
	char httpHead[1024];
	int hsize = 12;
	if (!BlockingSocket::read(httpHead, &hsize))	// HTTP/1.1 200
		return false;
	httpHead[hsize] = '\0';
	if (strncmp(httpHead, "HTTP", 4) != 0 || strcmp(httpHead+9, "200") != 0)
	{
		return false;
	}
	hsize = 1;
	while (BlockingSocket::read(httpHead, &hsize))
	{
		if (*httpHead == '\r')
		{
			if (!BlockingSocket::read(httpHead, &hsize))
				return false;
			if (*httpHead == '\n')
				break;
			else
				return false;
		}
	}

	// Read headers one line at time.
	char headline[1024];
	char *acp = headline;
	while (BlockingSocket::read(httpHead, &hsize))
	{
		*acp++ = *httpHead;
		if (*httpHead == '\r')
		{
			if (!BlockingSocket::read(httpHead, &hsize))
				return false;
			if (*httpHead != '\n')
				return false;
			*acp++ = *httpHead;
			*acp = '\0';
			printf("Header line = [%s]\n", headline);

			if (strncmp(headline, "Set-Cookie: ", 12) == 0)
				strcpy(session, headline+12);

			acp = headline;

			// End of header sequence "\r\n"
			if (strcmp(headline, "\r\n") == 0)
				break;
		}
	}

	bool bSuccess = BlockingSocket::read(pMessage);

	// Tell the socket it's been closed by HTTP server, but maintain session here
	BlockingSocket::close();

	return bSuccess;
}


void HTTPTunnelClient::close()
{
	*session = '\0';
	BlockingSocket::close();
}

bool HTTPTunnelClient::isConnected()
{
	return (BlockingSocket::isConnected() || *session != '\0');
}