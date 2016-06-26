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
#include "squashxml/socket/BlockingClientSocket.h"
#include "squashxml/tools/FileLogger.h"

BlockingClientSocket::BlockingClientSocket(char* pHost, unsigned int iPort)
	: BlockingSocket(pHost, iPort)
{
}

BlockingClientSocket::~BlockingClientSocket()
{
}


bool BlockingClientSocket::open()
{
	if (getSocketHandle() != -1)
		return true;

	if (!BlockingSocket::open())
		return false;

	if (!connectTo())
		return false;

	return true;
}

bool BlockingClientSocket::connectTo()
{

	if (!createSocketHandle())
		return false;

	int fd = getSocketHandle();
	struct sockaddr_in* pInaddr = getSocketAddress();

	int r;
#ifdef WIN32
	while (connect(fd, (struct sockaddr *)pInaddr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		r = WSAGetLastError();
		if (r == WSAEINPROGRESS)
			break;

		if (r != WSAEINTR)

#else
	while (connect(fd, (struct sockaddr *)pInaddr, sizeof(struct sockaddr_in)) == -1) {
		if (r == EINPROGRESS)
			break;

		if (r != EINTR)
#endif

		{
			char message[256];
			sprintf(message, "BlockingClientSocket::connectTo() - connect failed %d", r);
			gLogger->logError(message);

			BlockingSocket::close();
			return false;
		}
	}

	/* wait for connection to complete */
	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET(fd, &wfds);

	return true;
}
