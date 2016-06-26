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

#ifndef _HTTP_Tunnel_Client_H
#define _HTTP_Tunnel_Client_H


#include "squashxml/socket/BlockingClientSocket.h"

/**
 *  An HTTP Tunneling client class.
 */
class HTTPTunnelClient: public BlockingClientSocket
{
public:
	/**
      * A constructor which takes "host" and "port" as arguments.
	  * This information is passed to the base class.
	  * @param pHost - hostname or IP address to use.
      * @param iPort - port number to use.
	  * @param pUrl - the url of the servlet (e.g. /servlet/servletname)
	  * @param pUserAgent - used by the server to identify the client.
      */
	HTTPTunnelClient(char* pHost, unsigned int iPort, char* pUrl = NULL, char* pUserAgent = NULL);
	virtual ~HTTPTunnelClient();

	/** Add HTTP header here */
	bool write(MessageContainer* pMessage);

	/** Strip HTTP header here */
	bool read(MessageContainer* pMessage);

	/** Closes the socket connection. */
	void close();

	/** connected or we have a session with the server  */
	bool isConnected();

private:
	char session[256];
	char URL[1024];
	char userAgent[1024];
};

#endif	// _HTTP_Tunnel_Client_H
