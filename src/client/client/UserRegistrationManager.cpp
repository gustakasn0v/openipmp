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

#include "client/UserRegistrationManager.h"

// create user message classes
#include "io/message/osmsMessageCreateUserRequest.h"
#include "io/message/osmsMessageCreateUserResponse.h"
#include "io/message/osmsMessageCreateUserResponseError.h"

// register user message classes
#include "io/message/osmsMessageRegisterUserRequest.h"
#include "io/message/osmsMessageRegisterUserResponse.h"
#include "io/message/osmsMessageRegisterUserResponseError.h"

// register user message classes
#include "io/message/osmsMessageAcquireUserKeyStoreRequest.h"
#include "io/message/osmsMessageAcquireUserKeyStoreResponse.h"
#include "io/message/osmsMessageAcquireUserKeyStoreResponseError.h"

// constructor
UserRegistrationManager::UserRegistrationManager() : ClientManager()
{
    // initialize complex member attributes
    MemMan::construct(&m_username);
    MemMan::construct(&m_password);
    MemMan::construct(&m_passwordConfirm);
    MemMan::construct(&m_emailaddr);
}

// copy constructor
UserRegistrationManager::UserRegistrationManager(UserRegistrationManager* right)
{
    // initialize complex member attributes
    MemMan::construct(&m_username);
    MemMan::construct(&m_password);
    MemMan::construct(&m_passwordConfirm);
    MemMan::construct(&m_emailaddr);

    // initialize complex member attributes
    MemMan::copy(&m_username, (char*) right->get_username());
    MemMan::copy(&m_password, (char*) right->get_password());
    MemMan::copy(&m_passwordConfirm, (char*) right->get_passwordConfirm());
    MemMan::copy(&m_emailaddr, (char*) right->get_emailaddr());
}

// destructor
UserRegistrationManager::~UserRegistrationManager()
{
    // destroy complex member attributes
    MemMan::destruct(&m_username);
    MemMan::destruct(&m_password);
    MemMan::destruct(&m_passwordConfirm);
    MemMan::destruct(&m_emailaddr);
}

// Implementation

// login and acquire P12 file
int UserRegistrationManager::loginAndAcquireP12(ByteArray** p12fileBuf)
{

	// are we already logged in?
    if ( m_SecurityManagerProxy->isConnected() || m_loginState == REMOTE_LOGIN)
		remoteLogout();

	// create and initialize UserContext (NOTE: remoteLogin() needs this)
	UserContext userCtx;
	userCtx.setUserName(m_username);
	userCtx.setPassword(m_password);
	setUserContext(&userCtx);

	// login remotely (NOTE: skip local login, since we don't have a P12 file!)
	if (!remoteLogin()) {
		gLogger->logError("Remote Login Failed.");
		int errcode = osmsMessageGenericResponseError::osmsERROR_UNKNOWN_USER;
		return(errcode);
	}

	// create and populate register user message
	osmsMessageAcquireUserKeyStoreRequest msgAcquireUserKeyStoreRequest;
	msgAcquireUserKeyStoreRequest.setPassword(m_password);
	msgAcquireUserKeyStoreRequest.setUserName(m_username);

	// send message
	m_SecurityManagerProxy->sendRequest(&msgAcquireUserKeyStoreRequest);

	// get response
	osmsMessage* msgResponse = m_SecurityManagerProxy->getResponse();

	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving AcquireUserKeyStoreRequest message. Aborting acquisition procedure, but proceeding otherwise...");
		return(-1);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE:
		{
			osmsMessageAcquireUserKeyStoreResponse* pAcquireUserKeyStoreResponse = (osmsMessageAcquireUserKeyStoreResponse*)msgResponse;
			*p12fileBuf = pAcquireUserKeyStoreResponse->getUserSecurityStore();
			ByteArray* p12fileBufCpy = new ByteArray((char*)(*p12fileBuf)->data(), (*p12fileBuf)->length());
			*p12fileBuf = p12fileBufCpy;
			gLogger->logInfo("Received osmsMESSAGE_REGISTER_USER_RESPONSE.");
			delete msgResponse;
			break;
		}
		case osmsMessage::osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE_ERROR:
		{
			osmsMessageAcquireUserKeyStoreResponseError* pError = (osmsMessageAcquireUserKeyStoreResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_ACQUIRE_USER_KEY_STORE_ERROR. Proceeding...");
			gLogger->logError(pError->getResponseString());
			int errcode = pError->getErrorCode();
			delete msgResponse;
			return(errcode);
		}
		default:
		{
			gLogger->logError("Received unknown response message. Proceeding...");
			delete msgResponse;
			return(osmsMessageGenericResponseError::osmsERROR_UNKNOWN_ERROR);
		}
	} // switch

	return(0);
}

// register and acquire P12 file
int UserRegistrationManager::registerAndAcquireP12(ByteArray** p12fileBuf)
{

	// do we have a host ip address and port?
	if (!m_ip || !m_port) {
		gLogger->logError("Failure: IP and port not initialized.");
		return(-1);
	}

	// create socket connection if one does not already exist
	if (!m_SecurityManagerProxy->isConnected())

		if (!m_SecurityManagerProxy->connect(m_ip, m_port) || !m_SecurityManagerProxy->isConnected()) {
			gLogger->logError("Unable to connect to the server.");
			return(-1);
		}

	// create and populate create user message
	osmsMessageCreateUserRequest msgCreateUserRequest;
	msgCreateUserRequest.setEmailAddress(m_emailaddr);
	msgCreateUserRequest.setUserName(m_username);

	// send message
	m_SecurityManagerProxy->sendRequest(&msgCreateUserRequest);

	// get response
	osmsMessage* msgResponse = m_SecurityManagerProxy->getResponse();

	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving CreateUser message. Aborting login procedure, but proceeding otherwise...");
		return(-1);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_CREATE_USER_RESPONSE:
		{
			osmsMessageCreateUserResponse* pCreateUserResponse = (osmsMessageCreateUserResponse*)msgResponse;
			gLogger->logInfo("Received osmsMESSAGE_CREATE_USER_RESPONSE.");
			delete msgResponse;
			break;
		}
		case osmsMessage::osmsMESSAGE_CREATE_USER_RESPONSE_ERROR:
		{
			osmsMessageCreateUserResponseError* pError = (osmsMessageCreateUserResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_CREATE_USER_RESPONSE_ERROR. Proceeding...");
			gLogger->logError(pError->getResponseString());
			int errcode = pError->getErrorCode();
			delete msgResponse;
			return(errcode);
		}
		default:
		{
			gLogger->logError("Received unknown response message. Proceeding...");
			delete msgResponse;
			return(osmsMessageGenericResponseError::osmsERROR_UNKNOWN_ERROR);
		}
	} // switch

	
	// create and populate register user message
	osmsMessageRegisterUserRequest msgRegisterUserRequest;
	msgRegisterUserRequest.setPassword(m_password);
	msgRegisterUserRequest.setPasswordConfirm(m_passwordConfirm);
	msgRegisterUserRequest.setUserName(m_username);
	msgRegisterUserRequest.setEmailAddress(m_emailaddr);

	// send message
	m_SecurityManagerProxy->sendRequest(&msgRegisterUserRequest);

	// get response
	msgResponse = m_SecurityManagerProxy->getResponse();

	if (msgResponse == NULL) {
		gLogger->logError("Failure sending/receiving RegisterUser message. Aborting login procedure, but proceeding otherwise...");
		return(-1);
	}

	switch (msgResponse->getMessageType())
	{
		case osmsMessage::osmsMESSAGE_REGISTER_USER_RESPONSE:
		{
			osmsMessageRegisterUserResponse* pRegisterUserResponse = (osmsMessageRegisterUserResponse*)msgResponse;
			*p12fileBuf = pRegisterUserResponse->getUserSecurityStore();
			ByteArray* p12fileBufCpy = new ByteArray((char*)(*p12fileBuf)->data(), (*p12fileBuf)->length());
			*p12fileBuf = p12fileBufCpy;
			gLogger->logInfo("Received osmsMESSAGE_REGISTER_USER_RESPONSE.");
			delete msgResponse;
			break;
		}
		case osmsMessage::osmsMESSAGE_REGISTER_USER_RESPONSE_ERROR:
		{
			osmsMessageRegisterUserResponseError* pError = (osmsMessageRegisterUserResponseError*)msgResponse;
			gLogger->logError("Received osmsMESSAGE_REGISTER_USER_RESPONSE_ERROR. Proceeding...");
			gLogger->logError(pError->getResponseString());
			int errcode = pError->getErrorCode();
			delete msgResponse;
			return(errcode);
		}
		default:
		{
			gLogger->logError("Received unknown response message. Proceeding...");
			delete msgResponse;
			return(osmsMessageGenericResponseError::osmsERROR_UNKNOWN_ERROR);
		}
	} // switch

	m_SecurityManagerProxy->disconnect();
	return(0);
}

// Get and Set Operations for Class Attributes

// username
const char* UserRegistrationManager::get_username () const
{ return m_username; }
void UserRegistrationManager::set_username (char* value)
{ MemMan::copy(&m_username, value); }

// password
const char* UserRegistrationManager::get_password () const
{ return m_password; }
void UserRegistrationManager::set_password (char* value)
{ MemMan::copy(&m_password, value); }

// passwordConfirm
const char* UserRegistrationManager::get_passwordConfirm () const
{ return m_passwordConfirm; }
void UserRegistrationManager::set_passwordConfirm (char* value)
{ MemMan::copy(&m_passwordConfirm, value); }

// email address
const char* UserRegistrationManager::get_emailaddr () const
{ return m_emailaddr; }
void UserRegistrationManager::set_emailaddr (char* value)
{ MemMan::copy(&m_emailaddr, value); }
