/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is OpenIPMP.
 * 
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 * 
 */
// SecurityManagerProxy

#include "io/network/SecurityManagerProxy.h"
#include "squashxml/xml/XMLMessage.h"
#include "squashxml/tools/Logger.h"


// Class SecurityManagerProxy

SecurityManagerProxy::SecurityManagerProxy()
{
	m_SquashXMLServletClient = NULL;
}


bool SecurityManagerProxy::connect(char* ip, int port)
{
	if (m_SquashXMLServletClient != NULL)
	{
		if (isConnected())
			disconnect();			
	}

	m_SquashXMLServletClient = new SquashXMLServletClient(
										ip, 
										port, 
										"/openipmp/servlet/SimpleServletServer",
										"OpenIPMP/1.0 (Mutable, Inc.)"
									);
	if (m_SquashXMLServletClient == NULL)
		return false;

	if (!m_SquashXMLServletClient->connect())
	{
		delete m_SquashXMLServletClient;
		m_SquashXMLServletClient = NULL;

		char message[256];
		sprintf(message, "SecurityManagerProxy::connect() - Could not open socket %s:%d", ip, port);
		gLogger->logError(message);

		return false;
	}
	return true;
}

void SecurityManagerProxy::disconnect()
{
	if (m_SquashXMLServletClient != NULL)
	{
		m_SquashXMLServletClient->disconnect();
		delete m_SquashXMLServletClient;
		m_SquashXMLServletClient = NULL;
	}
}

bool SecurityManagerProxy::isConnected()
{
	if (m_SquashXMLServletClient == NULL)
		return false;
	return m_SquashXMLServletClient->isConnected();
}

SecurityManagerProxy::~SecurityManagerProxy()
{
	disconnect();
}

bool SecurityManagerProxy::sendRequest(osmsMessage* pRequestMessage)
{

	if (!isConnected())
	{
		char message[256];
		sprintf(message, "SecurityManagerProxy::sendRequest() - Socket Not Open.  Could not sendRequest: %d", pRequestMessage->getMessageType());
		gLogger->logError(message);
		return false;
	}

	return m_SquashXMLServletClient->sendRequest(pRequestMessage);
}

osmsMessage* SecurityManagerProxy::getResponse()
{
	if (!isConnected())
	{
		gLogger->logError("SecurityManagerProxy::getResponse() - Socket Not Open.  Could not getResponse");
		return NULL;
	}

	return (osmsMessage*)m_SquashXMLServletClient->getResponse();
}


osmsMessage* SecurityManagerProxy::sendRequestGetResponse(osmsMessage* pRequestMessage)
{
	if (sendRequest(pRequestMessage))
		return getResponse();
	else
		return NULL;
}
