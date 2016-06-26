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

#include "squashxml/socket/SquashXMLServletClient.h"
#include "squashxml/xml/XMLMessage.h"
#include "squashxml/tools/Logger.h"


SquashXMLServletClient::SquashXMLServletClient(char* ip, int port, char* pUrl, char* pUserAgent)
	: HTTPTunnelClient(ip, port, pUrl, pUserAgent)

{
}


bool SquashXMLServletClient::connect()
{
	disconnect();	// Just in case. Won't hurt if not connected.

	if (!open())
		return false;

	return true;
}

void SquashXMLServletClient::disconnect()
{
	close();
}

SquashXMLServletClient::~SquashXMLServletClient()
{
	disconnect();
}

bool SquashXMLServletClient::sendRequest(XMLMessageBean* pRequestMessage)
{
	if (!isConnected())
	{
		char message[256];
		sprintf(message, "SocketProxy::sendRequest() - Socket Not Open.  Could not sendRequest.");
		gLogger->logError(message);
		return false;
	}

	XMLMessage xmlMsg;
	xmlMsg.setBean(pRequestMessage);

	return write(&xmlMsg);
}

XMLMessageBean* SquashXMLServletClient::getResponse()
{
	if (!isConnected())
	{
		gLogger->logError("SocketProxy::getResponse() - Socket Not Open.  Could not getResponse");
		return NULL;
	}

	XMLMessage xmlMsg;
	read(&xmlMsg);

	return (XMLMessageBean*)xmlMsg.getBean();
}


XMLMessageBean* SquashXMLServletClient::sendRequestGetResponse(XMLMessageBean* pRequestMessage)
{
	if (sendRequest(pRequestMessage))
		return getResponse();
	else
		return NULL;
}
