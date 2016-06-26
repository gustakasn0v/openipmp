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

#ifndef _Blocking_Socket_H
#define _Blocking_Socket_H

#ifdef WIN32
#	include <winsock.h>
#else
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#	include <errno.h>
#	include <unistd.h>
#endif

#include "squashxml/socket/MessageContainer.h"

/**
 *  A base class for TCP/IP sockets (both client and server).
 *
 */
class BlockingSocket
{
public:

	/**
      * A constructor which takes "host" and "port" as arguments.
	  * @param pHost (character pointer) hostname or IP address to use.
      * @param iPort (unsigned integer) port number to use.
      */
	BlockingSocket(char* pHost, unsigned int iPort);
	virtual ~BlockingSocket();

	/** Returns the hostname (or IP address) of the socket. */
	char* getHost();

	/** Sets the hostname (or IP address) of the socket with the given argument. */
	void setHost(char* pHost);


	/** Returns the port number of the socket. */
	unsigned int getPort();

	/** Sets the port number of the socket. */
	void setPort(unsigned int iPort);


	/** Returns the handle to the socket to be used by low level socket functions.  */
	int getSocketHandle();


	/** Reads and returns the "length" characters from the socket and places it in result. */
	bool read(char* result, int* length);

	/** Writes "length" characters from data to the socket. */
	bool write(char* data, int length);


	/** Reads and returns the next Bean from the socket. */
	bool read(MessageContainer* pMessage);

	/** Writes the Bean to the socket. */
	bool write(MessageContainer* pMessage);


	/** Has the socket been openned? */
	bool isConnected();

protected:
	/** Opens the socket connection. */
	bool open();

	/** Closes the socket connection. */
	void close();

	/** Does the real work for openning the socket. */
	bool createSocketHandle();

	/** Returns the socket structure sockaddr_in which contains socket address information. */
	struct sockaddr_in* getSocketAddress();

	/** Sets the handle to the socket to be used by low level socket functions. */
	void setSocketHandle(int iSocketHandle);

private:

	/** Stores the hostname (or IP address) of the socket. */
	char *m_Host;

	/** Stores the port number of the socket. */
	unsigned int m_Port;

	/** Stores the handle to the socket to be used by low level socket functions. */
	int m_SocketHandle;

	/** Stores the socket address information. */
	struct sockaddr_in m_SocketAddress;


	/** Used to initilize the low level socket library. */
	bool netInit();


	/** Sets the socket structure sockaddr_in which contains socket address information. */
	void setSocketAddress(struct sockaddr_in* pSocketAddress);
};

#endif // Blocking_Socket_H
