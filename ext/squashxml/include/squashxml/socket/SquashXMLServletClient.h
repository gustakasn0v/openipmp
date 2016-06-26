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

#ifndef SquashXMLServletClient_H
#define SquashXMLServletClient_H

/**
 *	This class allows HTTPTunnelClient (which works with the generic
 *  MessageContainer class) to work with XMLMessageBean class.
 */

#include "squashxml/socket/HTTPTunnelClient.h"
#include "squashxml/xml/XMLMessageBean.h"

class SquashXMLServletClient : public HTTPTunnelClient
{
public:
	SquashXMLServletClient(char* ip, int port, char* pUrl = NULL, char* pUserAgent = NULL);
	virtual ~SquashXMLServletClient();

	bool connect();
	void disconnect();

	// Message Methods
	bool sendRequest(XMLMessageBean* pRequestMessage);
	XMLMessageBean* getResponse();

	XMLMessageBean* sendRequestGetResponse(XMLMessageBean* pRequestMessage);
};

#endif // SquashXMLServletClient_H
