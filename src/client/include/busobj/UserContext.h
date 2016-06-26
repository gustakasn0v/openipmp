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

#ifndef USERCONTEXT_HPP
#define USERCONTEXT_HPP

/**
*	UserContext.h
*
*	Copyright (c) 2001 Mutable, Inc.  All rights reserved.
*/

//openssl stuff
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/opensslv.h>
#include <openssl/pkcs12.h>
#include "tools/OctetString.h"
#include "tools/OlRaw.h"
#include "squashxml/tools/HashMap.h"
#include "busobj/License.h"

//forward ref
class License;

class UserContext 
{

	private:
		char*					m_UserName;
		char*					m_Password;
		bool					m_IsLoggedInLocally;
		bool					m_IsLoggedIntoServer;
		OctetString*			m_PrivateKeyASN1;
		OctetString*			m_UserCertASN1;
		OctetString*			m_PKCS12ASN1;
		RSA*					m_PrivateKey;			//RSA *RSAPrivateKey_dup(RSA *rsa);
		X509*					m_UserCert;				//X509_dup copy function
		STACK_OF(X509)*			m_CaCertChain;			//look at sk_dup in stack.h..will need to copy each cert
		PKCS12*					m_PKCS12Blob;			//ASN1_dup?
		STACK_OF(ASN1_TYPE)*	m_Licenses;			//pop elements and push on new stack?
		int						m_RSAKeySize;			//size of the key used to calculate lengths for encryption ops
		OlRaw*					m_Test;
		HashMap					m_LicenseMap;

	  
	protected:

	public:

	/** 
		Default no-args constructor
	*/
	UserContext();

	UserContext(UserContext &right);

	//## Destructor (generated)
	~UserContext();

	/**
	*	setUserName()
	*
	*	@param char*
	*	@returns void
	*/
	void setUserName(char*);

	/**
	*	getUserName()
	*	DO NOT DELETE!
	*
	*	@param void
	*	*returns char*
	*/
	char* getUserName();

	/**
	*	setPassword()
	*
	*	@param char*
	*	@returns void
	*/
	void setPassword(char*);

	/**
	*	getPassword()
	*	DO NOT DELETE!
	*
	*	@param void
	*	@returns char*
	*/
	char* getPassword();

	/**
	*	setLoggedInLocally()
	*
	*	@param bool
	*	@returns void
	*/
	void setLoggedInLocally(bool);

	/**
	*	isLoggedInLocally()
	*
	*	@param void
	*	@returns bool
	*/
	bool isLoggedInLocally();

	/**
	*	setLoggedIntoServer()
	*
	*	@param bool
	*	@returns void
	*/
	void setLoggedIntoServer(bool);

	/**
	*	isLoggedIntoServer()
	*
	*	@param void
	*	@returns bool
	*/
	bool isLoggedIntoServer();

	/** 
	*	setPrivateKey()
	*
	*	@param RSA*
	*	@returns void
	*/
	void setPrivateKey(RSA*);

	/**
	*	getPrivateKey()
	*
	*	@param void
	*	@returns RSA*
	*/
	RSA* getPrivateKey();

	/** 
	*	setPrivateKeyASN1()
	*
	*	@param unsigned char*
	*	@returns void
	*/
	void setPrivateKeyASN1(OctetString*);

	/**
	*	getPrivateKeyASN1()
	*
	*	@param void
	*	@returns unsigned char* DO NOT DELETE
	*/
	OctetString* getPrivateKeyASN1();

	/**
	*	setUserCert()
	*
	*	@param X509*
	*	@returns void
	*/
	void setUserCert(X509*);

	/**
	*	getUserCert()
	*
	*	@param void
	*	@returns X509*
	*/
	X509* getUserCert();

	/**
	*	setUserCertASN1()
	*
	*	@param OctetString*
	*	@returns void
	*/
	void setUserCertASN1(OctetString*);

	/**
	*	getUserCert()
	*
	*	@param void
	*	@returns OctetString*
	*/
	OctetString* getUserCertASN1();

	/**
	*	setCaCertChain()
	*
	*	@param STACK_OF(X509)*
	*	@returns void
	*/
	void setCaCertChain(STACK_OF(X509)*);

	/**
	*	getCaCertChain()
	*
	*	@param void
	*	@returns STACK_OF(X509)*
	*/
	STACK_OF(X509)* getCaCertChain();

	/**
	*	getRSAKeySize()
	*
	*	@param void
	*	@returns int
	*/
	int getRSAKeySize();

	/**
	*	getLicenses() DEPRECATED
	*
	*	@param STACK_OF(ASN1_TYPE)*
	*	@returns void
	*/
	STACK_OF(ASN1_TYPE)* getLicenses();

	/**
	*	setLicenses() DEPRECATED
	*
	*	@param STACK_OF(ASN1_TYPE)*
	*	@returns void
	*/
	void setLicenses(STACK_OF(ASN1_TYPE)*);

	/** 
	*	removeAllLicenses DEPRECATED
	*
	*	removes all ASN1_TYPE objects from memory and sets the stack to NULL.
	*
	*	@param void
	*	@returns bool
	*/
	bool removeAllLicenses();

	/**
	*	listLicenses() DEPRECATED
	*
	*	prints out the current license list (hopefully, they're all strings)
	*
	*	@param void
	*	@returns void
	*
	*/
	void listLicenses();

	/**
	*	addLicense()  DEPRECATED
	*
	*	@param unsigned char*
	*	@param int length
	*	@returns bool
	*/
	bool addLicense(OctetString*);

	/**
	*	setLicenseMap()
	*	
	*	@param HashMap
	*	@returns void
	*/
	void setLicenseMap(HashMap&);

	/**
	*	getLicenseMap()
	*
	*	@param void
	*	@returns HashMap&
	*/
	HashMap& getLicenseMap();

	/** 
	*	addLicenseToMap()
	*
	*	@param License*
	*	@param char* 
	*	@returns bool
	*/
	bool addLicenseToMap(char*, License*);

	/**
	*	helper function to print out the current user's licenses
	*/
	void printLicenses();

	/**
	*	removeAllLicensesFromMap()
	*
	*	@param void
	*	@returns bool
	*/
	bool removeAllLicensesFromMap();

	/**
	*	removeLicenseFromMap()
	*
	*	@param char* key
	*	@returns bool
	*/
	bool removeLicenseFromMap(char*);

	/**
	*	authorize()
	*
	*	@param char* key
	*	@param char* right
	*	@param OctetString* blobVal
	*	@returns true
	*/
	bool authorize(char*, char*, OctetString*);

	/**
	*/
	void setTest(OlRaw*);

	OlRaw* getTest();


    //## Assignment Operation (generated)
};


#endif
