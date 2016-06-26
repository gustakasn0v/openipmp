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
#ifndef OSMS_Message_Create_User_Request_H
#define OSMS_Message_Create_User_Request_H


#include "osmsMessage.h"

class osmsMessageCreateUserRequest : public osmsMessage
{
public:
	osmsMessageCreateUserRequest();
	virtual ~osmsMessageCreateUserRequest();

	virtual char* encode();
	virtual bool decode(char* xmlText);
	virtual char* xmlTemplate();

	//bean properties
	char* getFirstName();
	void setFirstName(char* FirstName);

	char* getLastName();
	void setLastName(char* LastName);

	char* getUserName();
	void setUserName(char* UserName);

	char* getPassword();
	void setPassword(char* Password);

	char* getEmailAddress();
	void setEmailAddress(char* EmailAddress);

	char* getUserType();
	void setUserType(char* UserType);

	char* getSalutation();
	void setSalutation(char* Salutation);

	char* getSuffix();
	void setSuffix(char* Suffix);

	char* getSecretQuestion();
	void setSecretQuestion(char* SecretQuestion);

	char* getSecretAnswer();
	void setSecretAnswer(char* SecretAnswer);

	char* getOrganizationName();
	void setOrganizationName(char* OrganizationName);

	char* getOrganizationUnit();
	void setOrganizationUnit(char* OrganizationUnit);

	char* getOrganizationPassword();
	void setOrganizationPassword(char* OrganizationPassword);

	char* getMainPhoneCountryCode();
	void setMainPhoneCountryCode(char* MainPhoneCountryCode);

	char* getMainPhoneAreaCode();
	void setMainPhoneAreaCode(char* MainPhoneAreaCode);

	char* getMainPhoneLocalNumb();
	void setMainPhoneLocalNumb(char* MainPhoneLocalNumb);

	char* getMainPhoneExt();
	void setMainPhoneExt(char* MainPhoneExt);

	char* getAltPhoneCountryCode();
	void setAltPhoneCountryCode(char* AltPhoneCountryCode);

	char* getAltPhoneAreaCode();
	void setAltPhoneAreaCode(char* AltPhoneAreaCode);

	char* getAltPhoneLocalNumb();
	void setAltPhoneLocalNumb(char* AltPhoneLocalNumb);

	char* getAltPhoneExt();
	void setAltPhoneExt(char* AltPhoneExt);

	char* getFaxPhoneCountryCode();
	void setFaxPhoneCountryCode(char* FaxPhoneCountryCode);

	char* getFaxPhoneAreaCode();
	void setFaxPhoneAreaCode(char* FaxPhoneAreaCode);

	char* getFaxPhoneLocalNumb();
	void setFaxPhoneLocalNumb(char* FaxPhoneLocalNumb);

	char* getFaxPhoneExt();
	void setFaxPhoneExt(char* FaxPhoneExt);

	char* getAddressLine1();
	void setAddressLine1(char* AddressLine1);

	char* getAddressLine2();
	void setAddressLine2(char* AddressLine2);

	char* getAddressLine3();
	void setAddressLine3(char* AddressLine3);

	char* getCity();
	void setCity(char* City);

	char* getState();
	void setState(char* State);

	char* getZipCode();
	void setZipCode(char* ZipCode);

	char* getCountry();
	void setCountry(char* Country);

private:
	char* m_FirstName;
	char* m_LastName;
	char* m_UserName;
	char* m_Password;
	char* m_EmailAddress;
	char* m_UserType;
	char* m_Salutation;
	char* m_Suffix;
	char* m_SecretQuestion;
	char* m_SecretAnswer;
	char* m_OrganizationName;
	char* m_OrganizationUnit;
	char* m_OrganizationPassword;
	char* m_MainPhoneCountryCode;
	char* m_MainPhoneAreaCode;
	char* m_MainPhoneLocalNumb;
	char* m_MainPhoneExt;
	char* m_AltPhoneCountryCode;
	char* m_AltPhoneAreaCode;
	char* m_AltPhoneLocalNumb;
	char* m_AltPhoneExt;
	char* m_FaxPhoneCountryCode;
	char* m_FaxPhoneAreaCode;
	char* m_FaxPhoneLocalNumb;
	char* m_FaxPhoneExt;
	char* m_AddressLine1;
	char* m_AddressLine2;
	char* m_AddressLine3;
	char* m_City;
	char* m_State;
	char* m_ZipCode;
	char* m_Country;
};

#endif // OSMS_Message_Create_User_Request_H