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

#include "io/message/osmsMessageRegisterUserRequest.h"

osmsMessageRegisterUserRequest::osmsMessageRegisterUserRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_REGISTER_USER_REQUEST, "com.mutable.osms.common.io.message.osmsMessageRegisterUserRequest")
{
	m_UserName = NULL;
	m_EmailAddress = NULL;
	m_Password = NULL;
	m_PasswordConfirm = NULL;
}

osmsMessageRegisterUserRequest::~osmsMessageRegisterUserRequest()
{
	if (m_UserName != NULL)
		delete[] m_UserName;

	if (m_EmailAddress != NULL)
		delete[] m_EmailAddress;

	if (m_Password != NULL)
		delete[] m_Password;

	if (m_PasswordConfirm != NULL)
		delete[] m_PasswordConfirm;
}


char* osmsMessageRegisterUserRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageRegisterUserRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<UserName type=\"char[]\"></UserName>" \
			"<EmailAddress type=\"char[]\"></EmailAddress>" \
			"<Password type=\"char[]\"></Password>" \
			"<PasswordConfirm type=\"char[]\"></PasswordConfirm>" \
		"</com.mutable.osms.common.io.message.osmsMessageRegisterUserRequest>";
}

char* osmsMessageRegisterUserRequest::encode()
{
	XMLDocument* pDoc = new XMLDocument();
	if (pDoc == NULL)
		return NULL;

	if (!pDoc->decode(xmlTemplate(), getName()))
	{
		delete pDoc;
		return NULL;
	}

	pDoc->setInteger("MessageType", getMessageType());
	pDoc->setString("UserName", getUserName());
	pDoc->setString("EmailAddress", getEmailAddress());
	pDoc->setString("Password", getPassword());
	pDoc->setString("PasswordConfirm", getPasswordConfirm());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageRegisterUserRequest::decode(char* xmlText)
{
	XMLDocument* pDoc = new XMLDocument();
	if (pDoc == NULL)
		return false;

	if (!pDoc->decode(xmlText, getName()))
	{
		delete pDoc;
		return false;
	}

	setMessageType(pDoc->getInteger("MessageType"));
	setUserName(pDoc->getString("UserName"));
	setEmailAddress(pDoc->getString("EmailAddress"));
	setPassword(pDoc->getString("Password"));
	setPasswordConfirm(pDoc->getString("PasswordConfirm"));

	delete pDoc;

	return true;
}




//bean properties
char* osmsMessageRegisterUserRequest::getUserName()
{
	return m_UserName;
}

void osmsMessageRegisterUserRequest::setUserName(char* UserName)
{
	if (m_UserName != NULL)
	{
		delete[] m_UserName;
		m_UserName = NULL;
	}
	if (UserName != NULL)
	{
		m_UserName = new char[strlen(UserName)+1];
		strcpy(m_UserName, UserName);
	}
}

char* osmsMessageRegisterUserRequest::getEmailAddress()
{
	return m_EmailAddress;
}

void osmsMessageRegisterUserRequest::setEmailAddress(char* EmailAddress)
{
	if (m_EmailAddress != NULL)
	{
		delete[] m_UserName;
		m_EmailAddress = NULL;
	}
	if (EmailAddress != NULL)
	{
		m_EmailAddress = new char[strlen(EmailAddress)+1];
		strcpy(m_EmailAddress, EmailAddress);
	}
}

char* osmsMessageRegisterUserRequest::getPassword()
{
	return m_Password;
}

void osmsMessageRegisterUserRequest::setPassword(char* Password)
{
	if (m_Password != NULL)
	{
		delete[] m_Password;
		m_Password = NULL;
	}
	if (Password != NULL)
	{
		m_Password = new char[strlen(Password)+1];
		strcpy(m_Password, Password);
	}
}

char* osmsMessageRegisterUserRequest::getPasswordConfirm()
{
	return m_PasswordConfirm;
}

void osmsMessageRegisterUserRequest::setPasswordConfirm(char* PasswordConfirm)
{
	if (m_PasswordConfirm != NULL)
	{
		delete[] m_PasswordConfirm;
		m_PasswordConfirm = NULL;
	}
	if (PasswordConfirm != NULL)
	{
		m_PasswordConfirm = new char[strlen(PasswordConfirm)+1];
		strcpy(m_PasswordConfirm, PasswordConfirm);
	}
}
