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
#ifndef HASHCONTEXT_HPP
#define HASHCONTEXT_HPP

/**
*	HashContext.h
*
*	Copyright (c) 2001 Mutable, Inc.  All rights reserved.
*/

//openssl stuff
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/opensslv.h>
#include <openssl/rand.h>
#include "busobj/UserContext.h"


class HashContext 
{

	private:
		EVP_MD_CTX m_Ctx;
		const EVP_MD* m_HashType;
		unsigned char m_HashBytes[EVP_MAX_MD_SIZE];
		unsigned int m_HashLength;

	  
	protected:
    // Additional Protected Declarations
      //## begin CryptoManager%3C6C1D9B01BA.protected preserve=yes
      //## end CryptoManager%3C6C1D9B01BA.protected

	public:

	/** 
		Default no-args constructor
	*/
	HashContext();

	HashContext(HashContext &right);

	//## Destructor (generated)
	~HashContext();

	/** 
	*
	*	hashInit()
	*
	*/
	bool hashInit();

	/**
	*	hashUpdate()
	*/
	bool hashUpdate(unsigned char*, int);

	/**
	*	hash()
	*	
	*	@param unsigned char* clearText
	*	@param int clearTextLength
	*	@returns bool
	*/
	bool hashFinal(unsigned char* = NULL, int* = NULL);

	/** 
	*	getHashBytes()
	*	
	*	DO NOT DELETE
	*	@param void
	*	@returns unsigned char*
	*/
	unsigned char* getHashBytes();

	/**
	*	setHashType()
	*
	*	@param EVP_MD* 
	*	@returns void
	*/
	void setHashType(const EVP_MD*);

	/**
	*	getHashType()
	*
	*	DO NOT DELETE
	*	@param void
	*	@returns int
	*/
	const EVP_MD* getHashType();

	/** 
	*	getHashLength
	*
	*	@param void
	*	@returns int
	*/
	unsigned int getHashLength();

	/** 
	*	sign()
	*
	*	call this function to sign the calculated hash with the user's private key.  Note: You cannot call this function until after
	*	the hash value has been calculated.  MUST CALL hashFinal first!
	*
	*	@param unsigned char* buffer to hold signature bytes
	*	@param int*	length (calculated)
	*	@param UserContext*
	*	@returns bool
	*/
	bool signHashBytes(unsigned char*, unsigned int*, RSA*);

	/**
	*	verify()
	*
	*	@param unsigned char* signature to verify with the user's public key
	*	@param length
	*	@param UserContext*
	*	@returns bool
	*/
	bool verifySignature(unsigned char*, unsigned int, X509*);

	/**
	*
	*	verify()  
	*
	*	@param unsigned char*
	*	@param int
	*	@param STACK_OF(X509*) list of certificates to verify signature against
	*	@returns bool
	*/
	bool verifySignature(unsigned char*, unsigned int, STACK_OF(X509)*);

    //## Assignment Operation (generated)
};


#endif
