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
#include "client/ClientManager.h"
#include "squashxml/tools/Logger.h"
#include "busobj/UserContext.h"
#include "busobj/Exception.h"
#include "squashxml/xml/XMLMessage.h"

// message base class and other generic messaging classes
#include "io/message/osmsMessage.h"
#include "io/message/osmsMessageUnknownRequestResponseError.h"
#include "io/message/osmsMessageUserLogoutRequest.h"

// login message classes
#include "io/message/osmsMessageUserLoginRequest.h"
#include "io/message/osmsMessageUserLoginResponse.h"
#include "io/message/osmsMessageUserLoginResponseError.h"

//logout messages
#include "io/message/osmsMessageUserLogoutRequest.h"
#include "io/message/osmsMessageUserLogoutResponse.h"
#include "io/message/osmsMessageUserLogoutResponseError.h"

ClientManager::ClientManager()
{
	MemMan::construct(&m_ip);
        m_port = NULL;
        m_SecurityManagerProxy = NULL;
        m_CryptoManager = NULL;
}

bool ClientManager::init()
{

        // initialize login and connection states
        m_loginState = NO_LOGIN;
		m_UserContext = NULL;

// TODO: These objects should probably be constructed outside of the ClientManager..

		// create Security Manager Proxy
        m_SecurityManagerProxy = new SecurityManagerProxy();

        // create Crypto Manager (and initialize key attributes)
        m_CryptoManager = new CryptoManager();

#ifdef WIN32
	m_CryptoManager->setP12FilePath("\\localsecurity\\");
	m_CryptoManager->setRandomNumberFilePath(".\\entropy.dat");
#else
	m_CryptoManager->setP12FilePath("./");
	m_CryptoManager->setRandomNumberFilePath("./entropy.dat");
#endif

	return true;
}

ClientManager::~ClientManager()
{

    // logout if necessary
    if (m_loginState == REMOTE_LOGIN)
    {
        // create and populate login request message
        osmsMessageUserLogoutRequest msgLogout;

        // send message
        m_SecurityManagerProxy->sendRequest(&msgLogout);
    }

    // if connected, disconnect and destory Security Manager Proxy
    if (m_SecurityManagerProxy) {
        if (m_SecurityManagerProxy->isConnected())
            m_SecurityManagerProxy->disconnect();
        delete m_SecurityManagerProxy;
    }

    // destroy Crypto Manager
    if (m_CryptoManager)
        delete m_CryptoManager;

    // destroy User Context
    if (m_UserContext)
        delete m_UserContext;

    // destroy complex member variables
    MemMan::destruct(&m_ip);

}

void ClientManager::login (int loginType)
{

// TODO: This should trigger user interface to popup a dialog box requesting username and password

	// if already in desired state (or better), return
	if (m_loginState==loginType || m_loginState>loginType )
		return;

	// need to increase login state
	else {

		// do we need to login locally?
		if (m_loginState != LOCAL_LOGIN)
			if (localLogin())
				++m_loginState;
			else
				return;

		// can we return now?
		if (m_loginState==loginType)
			return;

		// login remotely
		if (remoteLogin())
			++m_loginState;

	} // else

} // login

bool ClientManager::localLogin ()
{
	try
	{
		m_CryptoManager->Login(m_UserContext);
	}
	catch (Exception& e)
	{
		gLogger->logError("Failed attempt to login to local security environment.");
		gLogger->logError(e.getErrorMsg());
		return(false);
	}
	
	gLogger->logInfo("Logged in to local security environment.");

	return(true);
}

bool ClientManager::remoteLogin ()
{

	// do we have a host ip address and port?
	if (!m_ip || !m_port) {
		gLogger->logError("Failed attempt to login remotely: host ip address and/or port missing. Proceeding...");
		return(false);
	}

	// create socket connection if one does not already exist
	if (!m_SecurityManagerProxy->isConnected())

		if (!m_SecurityManagerProxy->connect(m_ip, m_port) || !m_SecurityManagerProxy->isConnected()) {
			gLogger->logError("Failed attempt to create socket connection. Aborting login procedure, but proceeding otherwise...");
			return(false);
		}

	// create and populate login request message
	osmsMessageUserLoginRequest msgLoginRequest;
	msgLoginRequest.setUserName(m_UserContext->getUserName());
	msgLoginRequest.setPassword(m_UserContext->getPassword());

	// send message
	m_SecurityManagerProxy->sendRequest(&msgLoginRequest);

	// get response
	osmsMessage* msgResponse = m_SecurityManagerProxy->getResponse();

	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving LoginRequest message. Aborting login procedure, but proceeding otherwise...");
		return(false);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_USER_LOGIN_RESPONSE:
		{
			osmsMessageUserLoginResponse* pLoginResponse = (osmsMessageUserLoginResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_USER_LOGIN_RESPONSE.");
			delete msgResponse;
			return(true);
		}
		case osmsMessage::osmsMESSAGE_USER_LOGIN_RESPONSE_ERROR:
		{
			osmsMessageUserLoginResponseError* pError = (osmsMessageUserLoginResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_USER_LOGIN_RESPONSE_ERROR. Proceeding...");
			gLogger->logError(pError->getResponseString());
			delete msgResponse;
			return(false);
		}
		default:
		{
			gLogger->logError("Received unknown response message. Proceeding...");
			delete msgResponse;
			return(false);
		}
	} // switch

} // remoteLogin


// set p12 File Path
void ClientManager::setP12FilePath(char* p_Path)
{
	if (m_CryptoManager)
	{
		m_CryptoManager->setP12FilePath(p_Path);
	}
}

// ip address
const char* ClientManager::get_ip () const
{ return m_ip; }
void ClientManager::set_ip (char* value)
{ MemMan::copy(&m_ip, value); }

// UserContext
void ClientManager::setUserContext(UserContext* p_Ctx)
{
	if (m_UserContext)
	{
		delete m_UserContext;
		m_UserContext = NULL;
	}
	
	if (p_Ctx != NULL)
	{
		// copy the one sent in
		m_UserContext = new UserContext(*p_Ctx);
	}
}

const UserContext* ClientManager::getUserContext()
{ return m_UserContext; }

// port
const int ClientManager::get_port () const
{ return m_port; }
void ClientManager::set_port (int value)
{ m_port = value; }

// SecurityManager
const SecurityManagerProxy* ClientManager::get_SecurityManagerProxy () const
{ return m_SecurityManagerProxy; }
void ClientManager::set_SecurityManagerProxy (SecurityManagerProxy* value)
{ m_SecurityManagerProxy = value; }

// helper method for message request / response (including connect / disconnect for HTTP based)
osmsMessage* ClientManager::sendMessage (osmsMessage* msg)
{

    // do we have a SecurityManagerProxy?
    if (!m_SecurityManagerProxy) {
// TODO: This could just create it !?!?!?!?
        gLogger->logError("SecurityManagerProxy is NULL.");
//        throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
        return(NULL);
    }

    // do we have a host ip address and port?
    if (!m_ip || !m_port) {
        gLogger->logError("Disregarding attempt to connect: host ip address and/or port missing.");
//        throw EXCEPTION(Exception::BAD_HOST_PARAMS);
        return(NULL);
    }

    // is this a login message?
    if ( msg->getMessageType() != osmsMessage::osmsMESSAGE_USER_LOGIN_REQUEST)
    {
    
        // not a login message - so make sure we are connected and logged in
        if ( !m_SecurityManagerProxy->isConnected() || m_loginState != REMOTE_LOGIN) {
            gLogger->logError("Socket connection and/or session was unexpectedly lost. Attempting reconnect (and login again)...");
            login(REMOTE_LOGIN);
            
            // check again
            if ( !m_SecurityManagerProxy->isConnected() || m_loginState != REMOTE_LOGIN) {
                gLogger->logError("... still can't connect and/or login. Aborting ...");
                return(NULL);
            } // check again
        }  // if logged in and connected

/**** Below is the old check, replaced by above *******
        // not a login message - so make sure we are already logged in?
        if (m_loginState != REMOTE_LOGIN) {
// TODO: This could just call remoteLogin() !?!?!?!?
            gLogger->logError("Disregarding attempt to send message: not yet logged in.");
//            throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
            return(NULL);
        }
****************/
        
    } // is a login message ?
    else {
    
        // need to be connect - check if we are, if not: connect
        if (m_SecurityManagerProxy->isConnected()) {
            if (!m_SecurityManagerProxy->connect(m_ip, m_port) ) {
                gLogger->logError("Failed attempt to create socket connection.");
//            	throw EXCEPTION(Exception::SOCKET_CONNECT_ERROR);
                m_SecurityManagerProxy->disconnect();
                return(NULL);
            } // connect
        } // if not connected
        
    }

/**** Below assumes that connections are dropped following each request / response pair *******
    // create socket connection if one does not already exist
    if (m_SecurityManagerProxy->isConnected()) {
        gLogger->logWarning("Unexpected condition: Already connected; proceeding ...");
    }
    else {
        if (!m_SecurityManagerProxy->connect(m_ip, m_port) ) {
            gLogger->logError("Failed attempt to create socket connection.");
//            throw EXCEPTION(Exception::SOCKET_CONNECT_ERROR);
            m_SecurityManagerProxy->disconnect();
            return(NULL);
        }
    }
****************/

    // send message
    if (!m_SecurityManagerProxy->sendRequest(msg) ) {
        gLogger->logError("Failure sending request message.");
//        throw EXCEPTION(Exception::MESSAGE_SEND_ERROR);
        m_SecurityManagerProxy->disconnect();
        return(NULL);
    }

    // get response
    osmsMessage* msgResponse = m_SecurityManagerProxy->getResponse();
    if (msgResponse == NULL) {
        gLogger->logError("Failure receiving response message.");
//        throw EXCEPTION(Exception::MESSAGE_RESPONSE_ERROR);
        m_SecurityManagerProxy->disconnect();
        return(NULL);
    }

/**** Below assumes that connections are dropped following each request / response pair *******
    // disconnect
//    m_SecurityManagerProxy->disconnect();
****************/

    // return response message
    return(msgResponse);
    
}


//remoteLogout
bool ClientManager::remoteLogout ()
{

	// do we have a host ip address and port?
	if (!m_ip || !m_port) {
		gLogger->logError("Failed attempt to login remotely: host ip address and/or port missing. Proceeding...");
		return(false);
	}

	// create socket connection if one does not already exist
	if (!m_SecurityManagerProxy->isConnected())

		if (!m_SecurityManagerProxy->connect(m_ip, m_port) || !m_SecurityManagerProxy->isConnected()) {
			gLogger->logError("Failed attempt to create socket connection. Aborting login procedure, but proceeding otherwise...");
			return(false);
		}

	// create and populate login request message
	osmsMessageUserLogoutRequest msgLogoutRequest;

	// send message
	m_SecurityManagerProxy->sendRequest(&msgLogoutRequest);

	// get response
	osmsMessage* msgResponse = m_SecurityManagerProxy->getResponse();
	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving LoginRequest message. Aborting login procedure, but proceeding otherwise...");
		return(false);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_USER_LOGOUT_RESPONSE:
		{
			osmsMessageUserLogoutResponse* pLogoutResponse = (osmsMessageUserLogoutResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_LOGOUT_RESPONSE.");
			delete msgResponse;
			return(true);
		}
		case osmsMessage::osmsMESSAGE_USER_LOGOUT_RESPONSE_ERROR:
		{
			osmsMessageUserLogoutResponseError* pError = (osmsMessageUserLogoutResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_LOGOUT_RESPONSE_ERROR. Proceeding...");
			gLogger->logError(pError->getResponseString());
			delete msgResponse;
			return(false);
		}
		default:
		{
			gLogger->logError("Received unknown response message. Proceeding...");
			delete msgResponse;
			return(false);
		}
	} // switch

} // remoteLogin

// CryptoManager
const CryptoManager* ClientManager::get_CryptoManager () const
{ return m_CryptoManager; }
// TODO: This needs a copy constructor (it should resemble the logic used above for the User Context)
void ClientManager::set_CryptoManager (CryptoManager* value)
{ m_CryptoManager = value; }
