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

#include "squashxml/socket/BlockingSocket.h"
#include "squashxml/tools/FileLogger.h"


BlockingSocket::BlockingSocket(char* pHost, unsigned int iPort)
{
	setHost(pHost);
	setPort(iPort);
	setSocketHandle(-1);
}

BlockingSocket::~BlockingSocket()
{
	close();
	if (m_Host != NULL)
		delete[] m_Host;
}

char* BlockingSocket::getHost()
{
	return m_Host;
}

void BlockingSocket::setHost(char* pHost)
{
	if (pHost != NULL)
	{
		m_Host = new char[strlen(pHost)+1];
		strcpy(m_Host, pHost);
	}
	else
		m_Host = pHost;
}


unsigned int BlockingSocket::getPort()
{
	return m_Port;
}

void BlockingSocket::setPort(unsigned int iPort)
{
	m_Port = iPort;
}


struct sockaddr_in* BlockingSocket::getSocketAddress()
{
	return &m_SocketAddress;
}

void BlockingSocket::setSocketAddress(struct sockaddr_in* pSocketAddress)
{
	memcpy(&m_SocketAddress, pSocketAddress, sizeof(struct sockaddr_in));
}


int BlockingSocket::getSocketHandle()
{
	return m_SocketHandle;
}

void BlockingSocket::setSocketHandle(int iSocketHandle)
{
	m_SocketHandle = iSocketHandle;
}

bool BlockingSocket::createSocketHandle()
{
	struct sockaddr_in inaddr;

	char* host = getHost();
	if ((host == NULL) || (*host == '\0'))
		return false;

	memset ((char * ) &inaddr, 0, sizeof inaddr);
	if ((inaddr.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
	{
		struct hostent *hostp;
		if ((hostp = gethostbyname(host)) == NULL)
		{
#ifdef WIN32
			char message[256];
			sprintf(message, "BlockingSocket::createSocketHandle() - gethostbyname(%s) failed:%d", host, WSAGetLastError());
			gLogger->logError(message);
#else
			errno = EINVAL;
#endif
			return false;
		}
		if (hostp->h_addrtype != AF_INET)
		{
#ifdef WIN32
			char message[256];
			sprintf(message, "BlockingSocket::createSocketHandle() - not AF_INET:%d", WSAGetLastError());
			gLogger->logError(message);
#else
			errno = EPROTOTYPE;
#endif
			return false;
		}
		memcpy((char *)&inaddr.sin_addr, (char *)hostp->h_addr, sizeof(inaddr.sin_addr));
	}


	inaddr.sin_family      = AF_INET;

	if (sizeof(inaddr.sin_port) == sizeof(short))
		inaddr.sin_port = htons(getPort());
	else
		inaddr.sin_port = (unsigned short)htonl(getPort());

	unsigned int fd = socket(AF_INET, SOCK_STREAM, 0);
#ifdef WIN32
	if (fd == SOCKET_ERROR)
#else
	if (fd < 0)
#endif
	{
		return false;
	}

	setSocketHandle(fd);
	setSocketAddress(&inaddr);

	return true;
}


bool BlockingSocket::netInit()
{
	static bool bInitialized = false;
	if (bInitialized)
		return true;
	bInitialized = true;

#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD( 2, 0 );

	if (WSAStartup( wVersionRequested, &wsaData))
	{
		char message[256];
		sprintf(message, "BlockingSocket::netInit() - WSAStartup failed %d", WSAGetLastError());
		gLogger->logError(message);
		return false;
	}
#endif

	return true;
}


bool BlockingSocket::open()
{
	if (!netInit())
		return false;

	return true;
}

bool BlockingSocket::read(char* result, int* length)
{
	int total = 0, thisPass;

	if (*length < 0)
		return false;
	else if (*length == 0)
		return true;

	do
	{
		errno = 0;
		if ((thisPass = recv(getSocketHandle(), result+total, *length-total, 0)) <= 0)
		{
#ifdef WIN32
			errno = WSAGetLastError();
#endif
			break;
		}
		total += thisPass;
	} while (thisPass != 0 && total < *length);
	bool bSuccess = (total == *length && errno == 0);
	*length = total;
	return bSuccess;
}

bool BlockingSocket::read(MessageContainer* pMessage)
{
	// Read the header which contains the length and type
	char headerBuf[HEADER_SIZE];
	int size = HEADER_SIZE;
	if (!BlockingSocket::read(headerBuf, &size))
		return false;

	int len = pMessage->decodeLength(headerBuf);

	// Read the data
	char *str = new char[len];
	if (!BlockingSocket::read(str, &len))
		return false;
	ByteArray bytes(str, len);
	pMessage->setPayload(&bytes);
	delete[] str;
	return true;
}

bool BlockingSocket::write(char* data, int length)
{
	if (length < 0)
		return false;
	else if (length == 0)
		return true;

char msg[128];
sprintf(msg, "\tBlockingSocket::write() - Sending the following %d bytes =============================================", length);
gLogger->logDebug(msg);
gLogger->logDebug(data);
	int rv = send(getSocketHandle(), data, length, 0);
gLogger->logDebug("\tBlockingSocket::write() - Sent the data =============================================");
	return (rv == length);
}

bool BlockingSocket::write(MessageContainer* pMessage)
{
	char *dataCopy = pMessage->getMessage();
	if (dataCopy == NULL)
		return false;

	bool bDone = BlockingSocket::write(dataCopy, HEADER_SIZE+pMessage->getLength());
	delete[] dataCopy;
	return bDone;
}


void BlockingSocket::close()
{
	if (getSocketHandle() == -1)
		return;

#ifdef WIN32
	closesocket(getSocketHandle());
#else
	::close(getSocketHandle());
#endif

	setSocketHandle(-1);
}

bool BlockingSocket::isConnected()
{
	return (getSocketHandle() != -1);
}
