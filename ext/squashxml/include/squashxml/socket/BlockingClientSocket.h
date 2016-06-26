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

#ifndef _Blocking_Client_Socket_H
#define _Blocking_Client_Socket_H

#include "squashxml/socket/BlockingSocket.h"

/**
 *  A TCP/IP client socket class.
 */
class BlockingClientSocket : public BlockingSocket
{
public:
	/**
      * A constructor which takes "host" and "port" as arguments.
	  * This information is passed to the "SSLSocket" base class.
	  * @param pHost (character pointer) hostname or IP address to use.
      * @param iPort (unsigned integer) port number to use.
      */
	BlockingClientSocket(char* pHost, unsigned int iPort);
	virtual ~BlockingClientSocket();

	/** Opens the client socket connection. */
	bool open();

private:
	/** Connects to a server socket.  Called by open(). */
	bool connectTo();
};

#endif	// _Blocking_Client_Socket_H
