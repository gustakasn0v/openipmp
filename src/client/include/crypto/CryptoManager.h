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
#ifndef CRYPTOMANAGER_HPP
#define CRYPTOMANAGER_HPP

/**
*	CryptoManager.h
*
*	Copyright (c) 2001 Mutable, Inc.  All rights reserved.
*/

//openssl stuff
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pkcs12.h>
#include "crypto/CipherContext.h"
#include "crypto/HashContext.h"
#include "busobj/UserContext.h"
#include "squashxml/xml/XMLDocument.h"

class CryptoManager 
{

	private:
	  //path to the local PKCS#12 path
	  char* m_P12FilePath;
	  char* m_RandomNumberFilePath;

	protected:
    // Additional Protected Declarations
      //## begin CryptoManager%3C6C1D9B01BA.protected preserve=yes
      //## end CryptoManager%3C6C1D9B01BA.protected

	public:

	/** 
		Default no-args constructor
	*/
	CryptoManager();

	CryptoManager(const CryptoManager &right);

	//## Destructor (generated)
	~CryptoManager();

    //## Assignment Operation (generated)
	const CryptoManager & operator=(const CryptoManager &right);

	//## Equality Operations (generated)
	int operator==(const CryptoManager &right) const;

	int operator!=(const CryptoManager &right) const;

	/** 
	*	setP12FilePath()
	*	
	*	@param char* p_Path;
	*	@returns void
	*/
	void setP12FilePath(char*);

	/** 
	*	getP12FilePath()
	*
	*	@param void
	*	@returns char*
	*/
	char* getP12FilePath();

	/** login()
	*
	*	TODO:  implement exception handling
	*	@param char* p_UserName
	*	@returns bool
	*/
	bool Login(UserContext*);

	/** 
	*	dumpEntitlements()
	*
	*	dump current Entitlements list
	*/
	void dumpEntitlements();

	/**
	*	createDummyEntitlements()
	*
	*	@param void
	*	@returns STACK_OF(ASN1_TYPE)*
	*/
	STACK_OF(ASN1_TYPE)* createDummyEntitlements();

	/** 
	*	generateKey()
	*	
	*	@param : char* AlgType
	*	@param : int lengthInBits
	*	@returns: void
	*/
	void generateKey(char*, int);

	/** 
	*	setRandomNumberFilePath
	*
	*	@param char* 
	*/
	void setRandomNumberFilePath(char*);

	/**
	*	init
	*
	*	@param CipherContext*
	*	@param char* key alg
	*	@param int  keylength in bits
	*	@returns bool
	*/
	bool init(CipherContext*, char*, int );

	/** 
	*	init
	*	
	*	@param HashContext*
	*	@param char* alg
	*	@returns bool
	*/
	bool init(HashContext*, char*);

	/**
	*	createP12Instance
	*
	*	I've reimplemented this function to construct the PKCS12 instance with a user rights array.
	*	It's taken from the PKCS12_create() function in the PKCS12 OpenSSL library.
	*
	*	builds an internal PKCS12 structure from supplied user cryptographic credentials.
	*
	*	@param char*
	*	@param EVP_PKEY*
	*	@param X509*
	*	@param STACK_OF(X509)*,
	*	@param int,
	*	@param int
	*	@param int
	*	@param int
	*	@param int
	*	@returns PKCS12*
	*/
	PKCS12* createP12Instance(char *, 
						char *, 
						EVP_PKEY *, 
						X509 *,
						STACK_OF(X509) *,
						STACK_OF(ASN1_TYPE) *,
						int,
						int,
						int,
						int,
						int);
	/**
	*	parseP12Instance
	*
	*	modfied OpenSSL function PKCS12_parse to decrypt and read values from PKCS12 security store.  Modified
	*	to include user rights storage.
	*	
	*	@param PKCS12*
	*	@param const char*
	*	@param X509**
	*	@param STACK_OF(X509)**
	*	@param STACK_OF(ASN1_TYPE)**
	*	@returns bool
	*/
	bool parseP12Instance(PKCS12*, 
							const char *, 
							EVP_PKEY**, 
							X509**,
							STACK_OF(X509)**,
							STACK_OF(ASN1_TYPE)**);

	/**
	*	storeP12Instance
	*
	*	stores the user's cryptographic information to the secure PKCS12 file structure.
	*/
	bool storeP12Instance(UserContext*);

	/**
	*	decodeLicense()
	*
	*	decode the license type and obtain the hash key 
	*
	*	@param XMLDocument*
	*	@param char*
	*	@param char**
	*	@param License**
	*	@returns bool
	*/
	bool decodeLicense(XMLDocument*,
						char*,
						char**,
						License**);


	private:
	/**
	*	randomizeKey()
	*
	*	Gather entropy for the key
	*	
	*	@param: unsigned char* p_Key
	*	@param: int length in bytes
	@	@returns: void
	*/
	bool randomizeKey(unsigned char*, int);

};


#endif
