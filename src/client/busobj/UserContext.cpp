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

//UserContext Implementation

#include "busobj/UserContext.h"
#include "tools/MemMan.h"
#include <assert.h>
#include "squashxml/tools/HashMap.h"
#include "busobj/License.h"


UserContext::UserContext()
{
	MemMan::construct(&m_UserName);
	MemMan::construct(&m_Password);
	MemMan::construct(&m_PrivateKeyASN1);
	MemMan::construct(&m_UserCertASN1);
	MemMan::construct(&m_RSAKeySize);
	m_IsLoggedInLocally = false;
	m_IsLoggedIntoServer = false;
	m_PrivateKey = NULL;
	m_UserCert = NULL;
	m_CaCertChain = NULL;
	m_PKCS12Blob = NULL;
	m_Licenses = NULL;
	m_Test = NULL;
}

//copy constructor 
UserContext::UserContext(UserContext &right)
{
	//intiialize the attributes
	MemMan::construct(&m_UserName);
	MemMan::construct(&m_Password);
	MemMan::construct(&m_PrivateKeyASN1);
	MemMan::construct(&m_UserCertASN1);
	MemMan::construct(&m_RSAKeySize);
	m_IsLoggedInLocally = false;
	m_IsLoggedIntoServer = false;
	m_PrivateKey = NULL;
	m_UserCert = NULL;
	m_CaCertChain = NULL;
	m_PKCS12Blob = NULL;
	m_Licenses = NULL;
	m_Test = NULL;

	//now copy the attributes
	setUserName(right.m_UserName);
	setPassword(right.m_Password);
	setPrivateKey(right.m_PrivateKey);
	setUserCert(right.m_UserCert);
	setPrivateKeyASN1(right.m_PrivateKeyASN1);
	setUserCertASN1(right.m_UserCertASN1);
	m_RSAKeySize = right.m_RSAKeySize;
	setLoggedInLocally(right.m_IsLoggedInLocally);
	setLoggedIntoServer(right.m_IsLoggedIntoServer);
	setCaCertChain(right.m_CaCertChain);
	setLicenses(right.m_Licenses);
	setTest(right.m_Test);
	setLicenseMap(right.m_LicenseMap);
}

UserContext::~UserContext()
{
	MemMan::destruct(&m_UserName);
	MemMan::destruct(&m_Password);
	MemMan::destruct(&m_PrivateKeyASN1);
	MemMan::destruct(&m_UserCertASN1);
	MemMan::destruct(&m_RSAKeySize);

	//delete the PrivateKey
	if (m_PrivateKey)
	{
		RSA_free(m_PrivateKey);
	}

	//delete the cert
	if (m_UserCert)
	{
		X509_free(m_UserCert);
	}

	//delete the cert chain
	if (m_CaCertChain)
	{
		//pop each element and delete ..then delete the stack object
		for (int i =0; i < sk_X509_num(m_CaCertChain); i++) 
			X509_free(sk_X509_value(m_CaCertChain, i));

		sk_X509_free(m_CaCertChain);
		m_CaCertChain = NULL;
	}

	//delete the Licenses
	if (m_Licenses)
	{
		for (int i=0; i < sk_ASN1_TYPE_num(m_Licenses); i++)
			ASN1_TYPE_free(sk_ASN1_TYPE_value(m_Licenses, i));

		sk_ASN1_TYPE_free(m_Licenses);
		m_Licenses = NULL;
	}

	//delete the license objects
	if (m_LicenseMap.size() > 0)
	{
			for (License* lic = (License*)m_LicenseMap.first(); lic; lic = (License*)m_LicenseMap.next())
			{
				delete lic;
			}
		m_LicenseMap.clear();  //clear out these pointers too
	}


	if (m_Test)
	{
		delete m_Test; m_Test = NULL;
	}
}

// username property
void UserContext::setUserName(char* p_Name)
{
	MemMan::copy(&m_UserName, p_Name);
}

char* UserContext::getUserName()
{
	return m_UserName;
}

// password property
void UserContext::setPassword(char* p_Password)
{
	MemMan::copy(&m_Password, p_Password);
}

char* UserContext::getPassword()
{
	return m_Password;
}

// isLoggedInLocally property
void UserContext::setLoggedInLocally(bool p_LoggedIn)
{
	m_IsLoggedInLocally = p_LoggedIn;
}

bool UserContext::isLoggedInLocally()
{
	return m_IsLoggedInLocally;
}

// isLoggedIntoServer property
void UserContext::setLoggedIntoServer(bool p_LoggedIn)
{
	m_IsLoggedIntoServer = p_LoggedIn;
}

bool UserContext::isLoggedIntoServer()
{
	return m_IsLoggedIntoServer;
}

// privatekey property
void UserContext::setPrivateKey(RSA* p_Key)
{
	//free the current instance and allocate a new one
	if (m_PrivateKey)
	{
		RSA_free(m_PrivateKey);
		m_PrivateKey = NULL;
	}

	if (p_Key)
	{
		m_PrivateKey = RSAPrivateKey_dup(p_Key);
		//set the key size
		m_RSAKeySize = RSA_size(p_Key);
	}
	else
		m_PrivateKey = p_Key;

}

RSA* UserContext::getPrivateKey()
{
	return m_PrivateKey;
}

// certificate property
void UserContext::setUserCert(X509* p_Cert)
{
	if (m_UserCert)
	{
		X509_free(m_UserCert);
		m_UserCert = NULL;
	}

	if (p_Cert)
		m_UserCert = X509_dup(p_Cert);
	else
		m_UserCert = p_Cert;
}

X509* UserContext::getUserCert()
{
	return m_UserCert;
}

//user cert ASN1
void UserContext::setUserCertASN1(OctetString* p_Cert)
{
	MemMan::copy(&m_UserCertASN1, p_Cert);
}

OctetString* UserContext::getUserCertASN1()
{
	return m_UserCertASN1;
}


// private key ASN1
void UserContext::setPrivateKeyASN1(OctetString* p_Key)
{
	MemMan::copy(&m_PrivateKeyASN1, p_Key);
}

OctetString* UserContext::getPrivateKeyASN1()
{
	return m_PrivateKeyASN1;
}

//ca cert chain property
void UserContext::setCaCertChain(STACK_OF(X509)* p_Chain)
{
	if (m_CaCertChain)
		{
			//delete the existing stack, copy the elements to the new stack object
			for (int i =0; i < sk_X509_num(m_CaCertChain); i++) 
				X509_free(sk_X509_value(m_CaCertChain, i));

			sk_X509_free(m_CaCertChain);
			m_CaCertChain = NULL;
		}

	if (p_Chain)
	{
		m_CaCertChain = sk_X509_new_null();
	
		for (int i = 0; i < sk_X509_num(p_Chain); i++) 
			sk_X509_push(m_CaCertChain, X509_dup(sk_X509_value(p_Chain, i)));
	}
	else
		m_CaCertChain = p_Chain;

}

// Licenses property
void UserContext::setLicenses(STACK_OF(ASN1_TYPE)* p_Licenses)
{
	if (m_Licenses)
		{
			//delete the existing stack, copy the elements to the new stack object
			for (int i =0; i < sk_ASN1_TYPE_num(m_Licenses); i++) 
				ASN1_TYPE_free(sk_ASN1_TYPE_value(m_Licenses, i));

			sk_ASN1_TYPE_free(m_Licenses);
			m_Licenses = NULL;
		}

	if (p_Licenses)
	{
		m_Licenses = sk_ASN1_TYPE_new_null();
	
		for (int i = 0; i < sk_ASN1_TYPE_num(p_Licenses); i++) 
		{
			//make a new ASN1_TYPE object
			ASN1_TYPE* thisLicense = ASN1_TYPE_new();
			ASN1_TYPE* toCopy = sk_ASN1_TYPE_value(p_Licenses, i);
			ASN1_TYPE_set_octetstring(thisLicense, (unsigned char*)toCopy->value.octet_string->data, toCopy->value.octet_string->length);
			sk_ASN1_TYPE_push(m_Licenses, thisLicense);
		}
	}
	else
		m_Licenses = p_Licenses;

}

//get Licenses
STACK_OF(ASN1_TYPE)* UserContext::getLicenses()
{
	return m_Licenses;
}


STACK_OF(X509)* UserContext::getCaCertChain()
{
	return m_CaCertChain;
}

//size of the RSA key
int UserContext::getRSAKeySize()
{
	return m_RSAKeySize;
}

//removeAllLicenses
bool UserContext::removeAllLicenses()
{
	//delete the existing stack
	if (m_Licenses)
	{
		for (int i =0; i < sk_ASN1_TYPE_num(m_Licenses); i++) 
			ASN1_TYPE_free(sk_ASN1_TYPE_value(m_Licenses, i));

		sk_ASN1_TYPE_free(m_Licenses);
		m_Licenses = NULL;
	}

	return true;
}

//listLicenses
void UserContext::listLicenses()
{
		//loop through the Licenses
	printf("Current Licenses for %s \n\n", m_UserName);
	if (m_Licenses)
	{
		if (sk_ASN1_TYPE_num(m_Licenses) > 0)
		{
			char buf[20000];
			for (int i=0; i < sk_ASN1_TYPE_num(m_Licenses); i++)
			{
				//LAME..  puts a cap on the size of an License
				ASN1_TYPE* currentValue = sk_ASN1_TYPE_value(m_Licenses, i);
				int bytes = ASN1_TYPE_get_octetstring(currentValue, (unsigned char*)buf, 20000);  //last param is MAX_LENGTH
				if (bytes != -1)
					buf[bytes] = 0x00;

				printf(" License :  %s\n", buf);
			}
		}
		else
			printf("License List empty.\n");
	}
	else
		printf("License List empty.\n");
}

//addLicense
bool UserContext::addLicense(OctetString* p_Blob)
{
	//check to make sure they've passed in something valid, as best we can
	assert(p_Blob->octets);
	assert(p_Blob->len > 0);

	//TODO check return code here.. malloc error?
	ASN1_TYPE* newLicense = ASN1_TYPE_new();

	//TODO check return code here
	ASN1_TYPE_set_octetstring(newLicense, p_Blob->octets, p_Blob->len);

	//create a new stack of ASN1_TYPEs
	if (!m_Licenses) 
		m_Licenses = sk_ASN1_TYPE_new_null();

	//TODO check return code here
	sk_ASN1_TYPE_push(m_Licenses, newLicense);

	return true;
}


//LicenseMap
void UserContext::setLicenseMap(HashMap& p_Map)
{
	/** first delete what's already there */
	if (m_LicenseMap.size())
	{
		for (License* lic = (License*)m_LicenseMap.first(); lic; lic = (License*)m_LicenseMap.next())
		{
			delete lic;
		}
	}

	m_LicenseMap.clear();  //clear out these pointers too
	
	/** now add the licenses passed in */
	if (p_Map.size())
	{
		for (License* lic = (License*)p_Map.first(); lic; lic = (License*)p_Map.next())
		{
			//dup() is overridden in the derived classes to provide the appropriate type
			License* newLicense = lic->dup();
			m_LicenseMap.put(newLicense->getKey(), newLicense);
		}
	}
}

HashMap& UserContext::getLicenseMap()
{
	return m_LicenseMap;
}


//addLicenseToMap()
bool UserContext::addLicenseToMap(char* p_Key, License* p_License)
{
	p_License->setKey(p_Key);
	m_LicenseMap.put(p_Key, (void*)p_License);

	return true;
}

//printLicenses()
void UserContext::printLicenses()
{
	if (m_LicenseMap.size())
	{
		for (License* lic = (License*)m_LicenseMap.first(); lic; lic = (License*)m_LicenseMap.next())
		{
      std::cout << "License : " << lic->toString() << std::endl;
		}
	}
	else
    std::cout << "No Licenses." << std::endl;
	
}

//removeAllLicensesFromMap
bool UserContext::removeAllLicensesFromMap()
{
	if (m_LicenseMap.size())
	{
		for (License* lic = (License*)m_LicenseMap.first(); lic; lic = (License*)m_LicenseMap.next())
		{
			delete lic;
		}
	}

	m_LicenseMap.clear();  //clear out these pointers too

	return true;
}


//authorize
bool UserContext::authorize(char* p_Right, char* p_ResourceKey, OctetString* p_KeyBlob)
{
	p_KeyBlob->octets = NULL;
	p_KeyBlob->len = 0;

	//lookup license by resourceKey and determine if specific rights are granted
	if (m_LicenseMap.size())
	{
		License* license = (License*)m_LicenseMap.get(p_ResourceKey);

		if (license)
		{
			if (!(license->authorize(p_Right, this, p_ResourceKey, p_KeyBlob)))
			{
				m_LicenseMap.remove(p_ResourceKey);
				delete license;
				return false;
			}
			else
				return true;
		}
		else
			return false;
	}
	else
		return false;
}

//testing new OlMemMan raw functions
void UserContext::setTest(OlRaw* p_Test)
{
	if (m_Test)
	{
		//delete the existing Olraw..
		delete m_Test; m_Test = NULL;
	}
	
	if (p_Test)
	{
		//copy
		m_Test = new OlRaw();
		m_Test->set(p_Test);
	}
	else
		m_Test = p_Test;
}








