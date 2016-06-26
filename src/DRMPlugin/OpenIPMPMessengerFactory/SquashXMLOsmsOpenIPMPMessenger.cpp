/**	\file SquashXMLOsmsOpenIPMPMessenger.cpp

	Implementation of osms openIPMP messenger using squash XML
  servlet client.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "SquashXMLOsmsOpenIPMPMessenger.h"
/* disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    Use the information provided in the XML document.

    Optional tags in the XML file are:
     - ROOT.P12FilePath
     - ROOT.RandomNumberFilePath.

    If ROOT.P12FilePath tag is not present, p12 path is set to \localsecurity\.
    If ROOT.RandomNumberFilePath tag is not present, random number file path is
    set to .\entropy.dat.
    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <P12FilePath>\localsecurity\</P12FilePath>
     <RandomNumberFilePath>.\entropy.dat</RandomNumberFilePath>
    </ROOT>

    \endverbatim

    \param    xmlDoc          input, XML document.
    \param    logger          input-output, message logger.

    If constructor fails, it throws OpenIPMPMessengerException and logger
    contains error description.
*/
SquashXMLOsmsOpenIPMPMessenger::SquashXMLOsmsOpenIPMPMessenger(IXMLElement* xmlDoc,
  DRMLogger& logger): OsmsOpenIPMPMessenger(xmlDoc, logger) {
}

SquashXMLOsmsOpenIPMPMessenger::~SquashXMLOsmsOpenIPMPMessenger() {
}

/*! \brief  Assign content identifier using osms message.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, content identifier request.
    \param    response          output, content identifier response.

    \returns  Boolean indicating success or failure.
*/
bool SquashXMLOsmsOpenIPMPMessenger::OsmsAssignContentID(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRegisterContentAssignIdentifierRequest* request,
    osmsMessageRegisterContentAssignIdentifierResponse** response) {

	SquashXMLServletClient* client = new SquashXMLServletClient((char*)hostIP.data(),
    hostPort, "/openipmp/servlet/SimpleServletServer",
    "OpenIPMP/1.0 (Mutable, Inc.)");
  if (client == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsAssignContentID: could not create squash XML servlet client.");
		return false;
  }
	if (client->connect() == false)	{
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsAssignContentID: could not connect.");
		return false;
	}

  if (RemoteLogin(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    return false;
  }

  if (client->sendRequest(request) == false) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsAssignContentID: send request error.");
		return false;
  }
	osmsMessage* resp = (osmsMessage*)client->getResponse();
  if (resp == 0) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsAssignContentID: receive response error.");
		return false;
  }

  *response = 0;
	switch (resp->getMessageType()) {
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE: {
      *response = (osmsMessageRegisterContentAssignIdentifierResponse*)resp;
      break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE_ERROR: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsAssignContentID: received response error.");
			delete resp;
      break;
		}
		default: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsAssignContentID: received unknown response.");
			delete resp;
      break;
		}
	}

  if (RemoteLogout(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    if (*response != 0) delete (*response); 
    return false;
  }

  if (*response == 0) {
    client->disconnect();
    delete client;
    return false;
  }

  client->disconnect();
  delete client;
  return true;
}

/*! \brief  Register content encryption key with respect to content identifier
            using osms message.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, register content/key request.
    \param    response          output, register content/key response.

    \returns  Boolean indicating success or failure.
*/
bool SquashXMLOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRegisterDigitalItemInstanceRequest* request,
    osmsMessageRegisterDigitalItemInstanceResponse** response) {

	SquashXMLServletClient* client = new SquashXMLServletClient((char*)hostIP.data(),
    hostPort, "/openipmp/servlet/SimpleServletServer",
    "OpenIPMP/1.0 (Mutable, Inc.)");
  if (client == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: could not create squash XML servlet client.");
		return false;
  }
	if (client->connect() == false)	{
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: could not connect.");
		return false;
	}

  if (RemoteLogin(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    return false;
  }

  if (client->sendRequest(request) == false) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: send request error.");
		return false;
  }
	osmsMessage* resp = (osmsMessage*)client->getResponse();
  if (resp == 0) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: receive response error.");
		return false;
  }

  *response = 0;
	switch (resp->getMessageType()) {
		case osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE: {
      *response = (osmsMessageRegisterDigitalItemInstanceResponse*)resp;
      break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: received response error.");
			delete resp;
      break;
		}
		default: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsRegisterKeyForContent: received unknown response.");
			delete resp;
      break;
		}
	}

  if (RemoteLogout(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    if (*response != 0) delete (*response); 
    return false;
  }

  if (*response == 0) {
    client->disconnect();
    delete client;
    return false;
  }

  client->disconnect();
  delete client;
  return true;
}

/*! \brief  Get content encryption key with respect to content identifier
            using osms message.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, get key request.
    \param    response          output, get key response.

    \returns  Boolean indicating success or failure.
*/
bool SquashXMLOsmsOpenIPMPMessenger::OsmsGetKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageLicenseRequest* request, osmsMessageLicenseResponse** response) {

	SquashXMLServletClient* client = new SquashXMLServletClient((char*)hostIP.data(),
    hostPort, "/openipmp/servlet/SimpleServletServer",
    "OpenIPMP/1.0 (Mutable, Inc.)");
  if (client == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGetKeyForContent: could not create squash XML servlet client.");
		return false;
  }
	if (client->connect() == false)	{
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGetKeyForContent: could not connect.");
		return false;
	}

  if (RemoteLogin(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    return false;
  }

  if (client->sendRequest(request) == false) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGetKeyForContent: send request error.");
		return false;
  }
	osmsMessage* resp = (osmsMessage*)client->getResponse();
  if (resp == 0) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGetKeyForContent: receive response error.");
		return false;
  }

  *response = 0;
	switch (resp->getMessageType()) {
		case osmsMessage::osmsMESSAGE_LICENSE_RESPONSE: {
      *response = (osmsMessageLicenseResponse*)resp;
      break;
		}
		case osmsMessage::osmsMESSAGE_LICENSE_RESPONSE_ERROR: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGetKeyForContent: received response error.");
			delete resp;
      break;
		}
		default: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGetKeyForContent: received unknown response.");
			delete resp;
      break;
		}
	}

  if (RemoteLogout(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    if (*response != 0) delete (*response); 
    return false;
  }

  if (*response == 0) {
    client->disconnect();
    delete client;
    return false;
  }

  client->disconnect();
  delete client;
  return true;
}

/*! \brief  Grant license to user for the content identifier.

    \param    userName          input, granter's name.
    \param    password          input, granter's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    request           input, grant license request.
    \param    response          output, grant license response.

    \returns  Boolean indicating success or failure.
*/
bool SquashXMLOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRightsAuthorizationRequest* request,
    osmsMessageRightsAuthorizationResponse** response) {

	SquashXMLServletClient* client = new SquashXMLServletClient((char*)hostIP.data(),
    hostPort, "/openipmp/servlet/SimpleServletServer",
    "OpenIPMP/1.0 (Mutable, Inc.)");
  if (client == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: could not create squash XML servlet client.");
		return false;
  }
	if (client->connect() == false)	{
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: could not connect.");
		return false;
	}

  if (RemoteLogin(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    return false;
  }

  if (client->sendRequest(request) == false) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: send request error.");
		return false;
  }
	osmsMessage* resp = (osmsMessage*)client->getResponse();
  if (resp == 0) {
    client->disconnect();
    delete client;
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: receive response error.");
		return false;
  }

  *response = 0;
	switch (resp->getMessageType()) {
		case osmsMessage::osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE: {
      *response = (osmsMessageRightsAuthorizationResponse*)resp;
      break;
		}
		case osmsMessage::osmsMESSAGE_RIGHTS_AUTHORIZATION_RESPONSE_ERROR: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: received response error.");
			delete resp;
      break;
		}
		default: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::OsmsGrantLicenseForContent: received unknown response.");
			delete resp;
      break;
		}
	}

  if (RemoteLogout(userName, password, hostIP, hostPort, client) == false) {
    client->disconnect();
    delete client;
    if (*response != 0) delete (*response); 
    return false;
  }

  if (*response == 0) {
    client->disconnect();
    delete client;
    return false;
  }

  client->disconnect();
  delete client;
  return true;
}

/*! \brief  Login to remote host.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    client            input, client used for communication.

    \returns  Boolean indicating success or failure.
*/
bool SquashXMLOsmsOpenIPMPMessenger::RemoteLogin(const std::string& userName,
    const std::string& password,  const std::string& hostIP, const int hostPort, SquashXMLServletClient* client) {

	osmsMessageUserLoginRequest request;
	request.setUserName((char*)userName.data());
	request.setPassword((char*)password.data());

  if (client == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogin: zero client.");
    return false;
  }
	if (client->isConnected() == false)	{
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogin: not connected.");
		return false;
	}

  if (client->sendRequest(&request) == false) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogin: send login request error.");
		return false;
  }
	osmsMessage* resp = (osmsMessage*)client->getResponse();
  if (resp == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogin: receive login response error.");
		return false;
  }
	switch (resp->getMessageType()) {
		case osmsMessage::osmsMESSAGE_USER_LOGIN_RESPONSE: {
			delete resp;
      return true;
		}
		case osmsMessage::osmsMESSAGE_USER_LOGIN_RESPONSE_ERROR: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogin: received login response error.");
			delete resp;
			return false;
		}
		default: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogin: received unknown response.");
			delete resp;
			return false;
		}
	}
}

/*! \brief  Logout from remote host.

    \param    userName          input, user's name.
    \param    password          input, user's password.
    \param    hostIP            input, host's IP address.
    \param    hostPort          input, host's port.
    \param    client            input, client used for communication.

    \returns  Boolean indicating success or failure.
*/
bool SquashXMLOsmsOpenIPMPMessenger::RemoteLogout(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    SquashXMLServletClient* client) {

	osmsMessageUserLogoutRequest request;

  if (client == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogout: zero client.");
    return false;
  }
	if (client->isConnected() == false)	{
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogout: not connected.");
		return false;
	}

  if (client->sendRequest(&request) == false) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogout: send logout request error.");
		return false;
  }
	osmsMessage* resp = (osmsMessage*)client->getResponse();
  if (resp == 0) {
    messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogout: receive logout response error.");
		return false;
  }
	switch (resp->getMessageType()) {
		case osmsMessage::osmsMESSAGE_USER_LOGOUT_RESPONSE: {
			delete resp;
      return true;
		}
		case osmsMessage::osmsMESSAGE_USER_LOGOUT_RESPONSE_ERROR: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogout: received logout response error.");
			delete resp;
			return false;
		}
		default: {
      messengerLogger.UpdateLog("SquashXMLOsmsOpenIPMPMessenger::RemoteLogout: received unknown response.");
			delete resp;
			return false;
		}
	}
}

} // namespace DRMPlugin
