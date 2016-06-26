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

#include "io/message/osmsMessageCreateUserRequest.h"

osmsMessageCreateUserRequest::osmsMessageCreateUserRequest()
	: osmsMessage(osmsMessage::osmsMESSAGE_CREATE_USER_REQUEST, "com.mutable.osms.common.io.message.osmsMessageCreateUserRequest")
{
//	m_FirstName = NULL;
//	m_LastName = NULL;
	m_UserName = NULL;
	m_Password = NULL;
	m_EmailAddress = NULL;
/*
	m_UserType = NULL;
	m_Salutation = NULL;
	m_Suffix = NULL;
	m_SecretQuestion = NULL;
	m_SecretAnswer = NULL;
	m_OrganizationName = NULL;
	m_OrganizationUnit = NULL;
	m_OrganizationPassword = NULL;
	m_MainPhoneCountryCode = NULL;
	m_MainPhoneAreaCode = NULL;
	m_MainPhoneLocalNumb = NULL;
	m_MainPhoneExt = NULL;
	m_AltPhoneCountryCode = NULL;
	m_AltPhoneAreaCode = NULL;
	m_AltPhoneLocalNumb = NULL;
	m_AltPhoneExt = NULL;
	m_FaxPhoneCountryCode = NULL;
	m_FaxPhoneAreaCode = NULL;
	m_FaxPhoneLocalNumb = NULL;
	m_FaxPhoneExt = NULL;
	m_AddressLine1 = NULL;
	m_AddressLine2 = NULL;
	m_AddressLine3 = NULL;
	m_City = NULL;
	m_State = NULL;
	m_ZipCode = NULL;
	m_Country = NULL;
*/
}

osmsMessageCreateUserRequest::~osmsMessageCreateUserRequest()
{
//	if (m_FirstName != NULL)  delete[] m_FirstName;
//	if (m_LastName != NULL)  delete[] m_LastName;
	if (m_UserName != NULL)  delete[] m_UserName;
	if (m_Password != NULL)  delete[] m_Password;
	if (m_EmailAddress != NULL)  delete[] m_EmailAddress;
/*
	if (m_UserType != NULL)  delete[] m_UserType;
	if (m_Salutation != NULL)  delete[] m_Salutation;
	if (m_Suffix != NULL)  delete[] m_Suffix;
	if (m_SecretQuestion != NULL)  delete[] m_SecretQuestion;
	if (m_SecretAnswer != NULL)  delete[] m_SecretAnswer;
	if (m_OrganizationName != NULL)  delete[] m_OrganizationName;
	if (m_OrganizationUnit != NULL)  delete[] m_OrganizationUnit;
	if (m_OrganizationPassword != NULL)  delete[] m_OrganizationPassword;
	if (m_MainPhoneCountryCode != NULL)  delete[] m_MainPhoneCountryCode;
	if (m_MainPhoneAreaCode != NULL)  delete[] m_MainPhoneAreaCode;
	if (m_MainPhoneLocalNumb != NULL)  delete[] m_MainPhoneLocalNumb;
	if (m_MainPhoneExt != NULL)  delete[] m_MainPhoneExt;
	if (m_AltPhoneCountryCode != NULL)  delete[] m_AltPhoneCountryCode;
	if (m_AltPhoneAreaCode != NULL)  delete[] m_AltPhoneAreaCode;
	if (m_AltPhoneLocalNumb != NULL)  delete[] m_AltPhoneLocalNumb;
	if (m_AltPhoneExt != NULL)  delete[] m_AltPhoneExt;
	if (m_FaxPhoneCountryCode != NULL)  delete[] m_FaxPhoneCountryCode;
	if (m_FaxPhoneAreaCode != NULL)  delete[] m_FaxPhoneAreaCode;
	if (m_FaxPhoneLocalNumb != NULL)  delete[] m_FaxPhoneLocalNumb;
	if (m_FaxPhoneExt != NULL)  delete[] m_FaxPhoneExt;
	if (m_AddressLine1 != NULL)  delete[] m_AddressLine1;
	if (m_AddressLine2 != NULL)  delete[] m_AddressLine2;
	if (m_AddressLine3 != NULL)  delete[] m_AddressLine3;
	if (m_City != NULL)  delete[] m_City;
	if (m_State != NULL)  delete[] m_State;
	if (m_ZipCode != NULL)  delete[] m_ZipCode;
	if (m_Country != NULL)  delete[] m_Country;
*/
}


char* osmsMessageCreateUserRequest::xmlTemplate()
{
	return
		"<?xml version=\"1.0\"?>" \
		"<com.mutable.osms.common.io.message.osmsMessageCreateUserRequest>" \
			"<MessageType type=\"int\"></MessageType>" \
			"<UserName type=\"char[]\"></UserName>" \
			"<Password type=\"char[]\"></Password>" \
			"<EmailAddress type=\"char[]\"></EmailAddress>" \
		"</com.mutable.osms.common.io.message.osmsMessageCreateUserRequest>";
}

char* osmsMessageCreateUserRequest::encode()
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
	pDoc->setString("Password", getPassword());
	pDoc->setString("EmailAddress", getEmailAddress());

	char *result = pDoc->encode();

	delete pDoc;

	return result;
}

bool osmsMessageCreateUserRequest::decode(char* xmlText)
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
	setPassword(pDoc->getString("Password"));
	setEmailAddress(pDoc->getString("EmailAddress"));

	delete pDoc;

	return true;
}


//bean properties
char* osmsMessageCreateUserRequest::getFirstName()
{
	return m_FirstName;
}
void osmsMessageCreateUserRequest::setFirstName(char* FirstName)
{
	if (m_FirstName != NULL)
	{
		delete[] m_FirstName;
		m_FirstName = NULL;
	}
	if (FirstName != NULL)
	{
		m_FirstName = new char[strlen(FirstName)+1];
		strcpy(m_FirstName, FirstName);
	}
}

char* osmsMessageCreateUserRequest::getLastName()
{
	return m_LastName;
}
void osmsMessageCreateUserRequest::setLastName(char* LastName)
{
	if (m_LastName != NULL)
	{
		delete[] m_LastName;
		m_LastName = NULL;
	}
	if (LastName != NULL)
	{
		m_LastName = new char[strlen(LastName)+1];
		strcpy(m_LastName, LastName);
	}
}

char* osmsMessageCreateUserRequest::getUserName()
{
	return m_UserName;
}
void osmsMessageCreateUserRequest::setUserName(char* UserName)
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

char* osmsMessageCreateUserRequest::getPassword()
{
	return m_Password;
}
void osmsMessageCreateUserRequest::setPassword(char* Password)
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

char* osmsMessageCreateUserRequest::getEmailAddress()
{
	return m_EmailAddress;
}
void osmsMessageCreateUserRequest::setEmailAddress(char* EmailAddress)
{
	if (m_EmailAddress != NULL)
	{
		delete[] m_EmailAddress;
		m_EmailAddress = NULL;
	}
	if (EmailAddress != NULL)
	{
		m_EmailAddress = new char[strlen(EmailAddress)+1];
		strcpy(m_EmailAddress, EmailAddress);
	}
}

char* osmsMessageCreateUserRequest::getUserType()
{
	return m_UserType;
}
void osmsMessageCreateUserRequest::setUserType(char* UserType)
{
	if (m_UserType != NULL)
	{
		delete[] m_UserType;
		m_UserType = NULL;
	}
	if (UserType != NULL)
	{
		m_UserType = new char[strlen(UserType)+1];
		strcpy(m_UserType, UserType);
	}
}

char* osmsMessageCreateUserRequest::getSalutation()
{
	return m_Salutation;
}
void osmsMessageCreateUserRequest::setSalutation(char* Salutation)
{
	if (m_Salutation != NULL)
	{
		delete[] m_Salutation;
		m_Salutation = NULL;
	}
	if (Salutation != NULL)
	{
		m_Salutation = new char[strlen(Salutation)+1];
		strcpy(m_Salutation, Salutation);
	}
}

char* osmsMessageCreateUserRequest::getSuffix()
{
	return m_Suffix;
}
void osmsMessageCreateUserRequest::setSuffix(char* Suffix)
{
	if (m_Suffix != NULL)
	{
		delete[] m_Suffix;
		m_Suffix = NULL;
	}
	if (Suffix != NULL)
	{
		m_Suffix = new char[strlen(Suffix)+1];
		strcpy(m_Suffix, Suffix);
	}
}

char* osmsMessageCreateUserRequest::getSecretQuestion()
{
	return m_SecretQuestion;
}
void osmsMessageCreateUserRequest::setSecretQuestion(char* SecretQuestion)
{
	if (m_SecretQuestion != NULL)
	{
		delete[] m_SecretQuestion;
		m_SecretQuestion = NULL;
	}
	if (SecretQuestion != NULL)
	{
		m_SecretQuestion = new char[strlen(SecretQuestion)+1];
		strcpy(m_SecretQuestion, SecretQuestion);
	}
}

char* osmsMessageCreateUserRequest::getSecretAnswer()
{
	return m_SecretAnswer;
}
void osmsMessageCreateUserRequest::setSecretAnswer(char* SecretAnswer)
{
	if (m_SecretAnswer != NULL)
	{
		delete[] m_SecretAnswer;
		m_SecretAnswer = NULL;
	}
	if (SecretAnswer != NULL)
	{
		m_SecretAnswer = new char[strlen(SecretAnswer)+1];
		strcpy(m_SecretAnswer, SecretAnswer);
	}
}

char* osmsMessageCreateUserRequest::getOrganizationName()
{
	return m_OrganizationName;
}
void osmsMessageCreateUserRequest::setOrganizationName(char* OrganizationName)
{
	if (m_OrganizationName != NULL)
	{
		delete[] m_OrganizationName;
		m_OrganizationName = NULL;
	}
	if (OrganizationName != NULL)
	{
		m_OrganizationName = new char[strlen(OrganizationName)+1];
		strcpy(m_OrganizationName, OrganizationName);
	}
}

char* osmsMessageCreateUserRequest::getOrganizationUnit()
{
	return m_OrganizationUnit;
}
void osmsMessageCreateUserRequest::setOrganizationUnit(char* OrganizationUnit)
{
	if (m_OrganizationUnit != NULL)
	{
		delete[] m_OrganizationUnit;
		m_OrganizationUnit = NULL;
	}
	if (OrganizationUnit != NULL)
	{
		m_OrganizationUnit = new char[strlen(OrganizationUnit)+1];
		strcpy(m_OrganizationUnit, OrganizationUnit);
	}
}

char* osmsMessageCreateUserRequest::getOrganizationPassword()
{
	return m_OrganizationPassword;
}
void osmsMessageCreateUserRequest::setOrganizationPassword(char* OrganizationPassword)
{
	if (m_OrganizationPassword != NULL)
	{
		delete[] m_OrganizationPassword;
		m_OrganizationPassword = NULL;
	}
	if (OrganizationPassword != NULL)
	{
		m_OrganizationPassword = new char[strlen(OrganizationPassword)+1];
		strcpy(m_OrganizationPassword, OrganizationPassword);
	}
}

char* osmsMessageCreateUserRequest::getMainPhoneCountryCode()
{
	return m_MainPhoneCountryCode;
}
void osmsMessageCreateUserRequest::setMainPhoneCountryCode(char* MainPhoneCountryCode)
{
	if (m_MainPhoneCountryCode != NULL)
	{
		delete[] m_MainPhoneCountryCode;
		m_MainPhoneCountryCode = NULL;
	}
	if (MainPhoneCountryCode != NULL)
	{
		m_MainPhoneCountryCode = new char[strlen(MainPhoneCountryCode)+1];
		strcpy(m_MainPhoneCountryCode, MainPhoneCountryCode);
	}
}

char* osmsMessageCreateUserRequest::getMainPhoneAreaCode()
{
	return m_MainPhoneAreaCode;
}
void osmsMessageCreateUserRequest::setMainPhoneAreaCode(char* MainPhoneAreaCode)
{
	if (m_MainPhoneAreaCode != NULL)
	{
		delete[] m_MainPhoneAreaCode;
		m_MainPhoneAreaCode = NULL;
	}
	if (MainPhoneAreaCode != NULL)
	{
		m_MainPhoneAreaCode = new char[strlen(MainPhoneAreaCode)+1];
		strcpy(m_MainPhoneAreaCode, MainPhoneAreaCode);
	}
}

char* osmsMessageCreateUserRequest::getMainPhoneLocalNumb()
{
	return m_MainPhoneLocalNumb;
}
void osmsMessageCreateUserRequest::setMainPhoneLocalNumb(char* MainPhoneLocalNumb)
{
	if (m_MainPhoneLocalNumb != NULL)
	{
		delete[] m_MainPhoneLocalNumb;
		m_MainPhoneLocalNumb = NULL;
	}
	if (MainPhoneLocalNumb != NULL)
	{
		m_MainPhoneLocalNumb = new char[strlen(MainPhoneLocalNumb)+1];
		strcpy(m_MainPhoneLocalNumb, MainPhoneLocalNumb);
	}
}

char* osmsMessageCreateUserRequest::getMainPhoneExt()
{
	return m_MainPhoneExt;
}
void osmsMessageCreateUserRequest::setMainPhoneExt(char* MainPhoneExt)
{
	if (m_MainPhoneExt != NULL)
	{
		delete[] m_MainPhoneExt;
		m_MainPhoneExt = NULL;
	}
	if (MainPhoneExt != NULL)
	{
		m_MainPhoneExt = new char[strlen(MainPhoneExt)+1];
		strcpy(m_MainPhoneExt, MainPhoneExt);
	}
}

char* osmsMessageCreateUserRequest::getAltPhoneCountryCode()
{
	return m_AltPhoneCountryCode;
}
void osmsMessageCreateUserRequest::setAltPhoneCountryCode(char* AltPhoneCountryCode)
{
	if (m_AltPhoneCountryCode != NULL)
	{
		delete[] m_AltPhoneCountryCode;
		m_AltPhoneCountryCode = NULL;
	}
	if (AltPhoneCountryCode != NULL)
	{
		m_AltPhoneCountryCode = new char[strlen(AltPhoneCountryCode)+1];
		strcpy(m_AltPhoneCountryCode, AltPhoneCountryCode);
	}
}

char* osmsMessageCreateUserRequest::getAltPhoneAreaCode()
{
	return m_AltPhoneAreaCode;
}
void osmsMessageCreateUserRequest::setAltPhoneAreaCode(char* AltPhoneAreaCode)
{
	if (m_AltPhoneAreaCode != NULL)
	{
		delete[] m_AltPhoneAreaCode;
		m_AltPhoneAreaCode = NULL;
	}
	if (AltPhoneAreaCode != NULL)
	{
		m_AltPhoneAreaCode = new char[strlen(AltPhoneAreaCode)+1];
		strcpy(m_AltPhoneAreaCode, AltPhoneAreaCode);
	}
}

char* osmsMessageCreateUserRequest::getAltPhoneLocalNumb()
{
	return m_AltPhoneLocalNumb;
}
void osmsMessageCreateUserRequest::setAltPhoneLocalNumb(char* AltPhoneLocalNumb)
{
	if (m_AltPhoneLocalNumb != NULL)
	{
		delete[] m_AltPhoneLocalNumb;
		m_AltPhoneLocalNumb = NULL;
	}
	if (AltPhoneLocalNumb != NULL)
	{
		m_AltPhoneLocalNumb = new char[strlen(AltPhoneLocalNumb)+1];
		strcpy(m_AltPhoneLocalNumb, AltPhoneLocalNumb);
	}
}

char* osmsMessageCreateUserRequest::getAltPhoneExt()
{
	return m_AltPhoneExt;
}
void osmsMessageCreateUserRequest::setAltPhoneExt(char* AltPhoneExt)
{
	if (m_AltPhoneExt != NULL)
	{
		delete[] m_AltPhoneExt;
		m_AltPhoneExt = NULL;
	}
	if (AltPhoneExt != NULL)
	{
		m_AltPhoneExt = new char[strlen(AltPhoneExt)+1];
		strcpy(m_AltPhoneExt, AltPhoneExt);
	}
}

char* osmsMessageCreateUserRequest::getFaxPhoneCountryCode()
{
	return m_FaxPhoneCountryCode;
}
void osmsMessageCreateUserRequest::setFaxPhoneCountryCode(char* FaxPhoneCountryCode)
{
	if (m_FaxPhoneCountryCode != NULL)
	{
		delete[] m_FaxPhoneCountryCode;
		m_FaxPhoneCountryCode = NULL;
	}
	if (FaxPhoneCountryCode != NULL)
	{
		m_FaxPhoneCountryCode = new char[strlen(FaxPhoneCountryCode)+1];
		strcpy(m_FaxPhoneCountryCode, FaxPhoneCountryCode);
	}
}

char* osmsMessageCreateUserRequest::getFaxPhoneAreaCode()
{
	return m_FaxPhoneAreaCode;
}
void osmsMessageCreateUserRequest::setFaxPhoneAreaCode(char* FaxPhoneAreaCode)
{
	if (m_FaxPhoneAreaCode != NULL)
	{
		delete[] m_FaxPhoneAreaCode;
		m_FaxPhoneAreaCode = NULL;
	}
	if (FaxPhoneAreaCode != NULL)
	{
		m_FaxPhoneAreaCode = new char[strlen(FaxPhoneAreaCode)+1];
		strcpy(m_FaxPhoneAreaCode, FaxPhoneAreaCode);
	}
}

char* osmsMessageCreateUserRequest::getFaxPhoneLocalNumb()
{
	return m_FaxPhoneLocalNumb;
}
void osmsMessageCreateUserRequest::setFaxPhoneLocalNumb(char* FaxPhoneLocalNumb)
{
	if (m_FaxPhoneLocalNumb != NULL)
	{
		delete[] m_FaxPhoneLocalNumb;
		m_FaxPhoneLocalNumb = NULL;
	}
	if (FaxPhoneLocalNumb != NULL)
	{
		m_FaxPhoneLocalNumb = new char[strlen(FaxPhoneLocalNumb)+1];
		strcpy(m_FaxPhoneLocalNumb, FaxPhoneLocalNumb);
	}
}

char* osmsMessageCreateUserRequest::getFaxPhoneExt()
{
	return m_FaxPhoneExt;
}
void osmsMessageCreateUserRequest::setFaxPhoneExt(char* FaxPhoneExt)
{
	if (m_FaxPhoneExt != NULL)
	{
		delete[] m_FaxPhoneExt;
		m_FaxPhoneExt = NULL;
	}
	if (FaxPhoneExt != NULL)
	{
		m_FaxPhoneExt = new char[strlen(FaxPhoneExt)+1];
		strcpy(m_FaxPhoneExt, FaxPhoneExt);
	}
}

char* osmsMessageCreateUserRequest::getAddressLine1()
{
	return m_AddressLine1;
}
void osmsMessageCreateUserRequest::setAddressLine1(char* AddressLine1)
{
	if (m_AddressLine1 != NULL)
	{
		delete[] m_AddressLine1;
		m_AddressLine1 = NULL;
	}
	if (AddressLine1 != NULL)
	{
		m_AddressLine1 = new char[strlen(AddressLine1)+1];
		strcpy(m_AddressLine1, AddressLine1);
	}
}

char* osmsMessageCreateUserRequest::getAddressLine2()
{
	return m_AddressLine2;
}
void osmsMessageCreateUserRequest::setAddressLine2(char* AddressLine2)
{
	if (m_AddressLine2 != NULL)
	{
		delete[] m_AddressLine2;
		m_AddressLine2 = NULL;
	}
	if (AddressLine2 != NULL)
	{
		m_AddressLine2 = new char[strlen(AddressLine2)+1];
		strcpy(m_AddressLine2, AddressLine2);
	}
}

char* osmsMessageCreateUserRequest::getAddressLine3()
{
	return m_AddressLine3;
}
void osmsMessageCreateUserRequest::setAddressLine3(char* AddressLine3)
{
	if (m_AddressLine3 != NULL)
	{
		delete[] m_AddressLine3;
		m_AddressLine3 = NULL;
	}
	if (AddressLine3 != NULL)
	{
		m_AddressLine3 = new char[strlen(AddressLine3)+1];
		strcpy(m_AddressLine3, AddressLine3);
	}
}

char* osmsMessageCreateUserRequest::getCity()
{
	return m_City;
}
void osmsMessageCreateUserRequest::setCity(char* City)
{
	if (m_City != NULL)
	{
		delete[] m_City;
		m_City = NULL;
	}
	if (City != NULL)
	{
		m_City = new char[strlen(City)+1];
		strcpy(m_City, City);
	}
}

char* osmsMessageCreateUserRequest::getState()
{
	return m_State;
}
void osmsMessageCreateUserRequest::setState(char* State)
{
	if (m_State != NULL)
	{
		delete[] m_State;
		m_State = NULL;
	}
	if (State != NULL)
	{
		m_State = new char[strlen(State)+1];
		strcpy(m_State, State);
	}
}

char* osmsMessageCreateUserRequest::getZipCode()
{
	return m_ZipCode;
}
void osmsMessageCreateUserRequest::setZipCode(char* ZipCode)
{
	if (m_ZipCode != NULL)
	{
		delete[] m_ZipCode;
		m_ZipCode = NULL;
	}
	if (ZipCode != NULL)
	{
		m_ZipCode = new char[strlen(ZipCode)+1];
		strcpy(m_ZipCode, ZipCode);
	}
}

char* osmsMessageCreateUserRequest::getCountry()
{
	return m_Country;
}
void osmsMessageCreateUserRequest::setCountry(char* Country)
{
	if (m_Country != NULL)
	{
		delete[] m_Country;
		m_Country = NULL;
	}
	if (Country != NULL)
	{
		m_Country = new char[strlen(Country)+1];
		strcpy(m_Country, Country);
	}
}

