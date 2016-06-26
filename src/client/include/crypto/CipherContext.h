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
#ifndef CIPHERCONTEXT_HPP
#define CIPHERCONTEXT_HPP

/**
*	CipherContext.h
*
*	Copyright (c) 2001 Mutable, Inc.  All rights reserved.
*/

//openssl stuff
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/opensslv.h>
#include <openssl/rand.h>
#include "tools/MemMan.h"


class CipherContext 
{

	private:
		EVP_CIPHER_CTX		m_Ctx;
		EVP_CIPHER*			m_Cipher;
		unsigned char*		m_Key;
		unsigned char*		m_Ivec;
		int					m_KeyLength;
		OctetString*		m_KeyObject;
		bool				m_IsSetup;

	  
	protected:
    // Additional Protected Declarations
      //## begin CryptoManager%3C6C1D9B01BA.protected preserve=yes
      //## end CryptoManager%3C6C1D9B01BA.protected

	public:

	/** 
		Default no-args constructor
	*/
	CipherContext();

	CipherContext(CipherContext &right);

	//## Destructor (generated)
	~CipherContext();

	/** 
	*
	*	encryptInit()
	*
	*/
	bool encryptInit();

	/**
	*	encryptUpdate()
	*/
	bool encryptUpdate(unsigned char*, int, unsigned char*, int*);

	/**
	*	encrypt()
	*	
	*	@param unsigned char* clearText
	*	@param int clearTextLength
	*	@param unsigned char* cipherText
	*	@param int cipherTextLength
	*	@returns bool
	*/
	bool encryptFinal(unsigned char*, int*);

	/**
	*	decryptInit()
	*/
	bool decryptInit();

	/**
	*	decryptUpdate();
	*
	*/
	bool decryptFinal(unsigned char*, int*);

	/**
	*	decrypt()
	*
	*	@returns bool
	*/
	bool decryptUpdate(unsigned char*, int, unsigned char*, int*);

	/**
	*	setKeyBytes()  CJM 3/28/02  This function should NOT be used anymore.. it still works
	*					for compatibility but you should use  get/setKey() instead.
	*
	*	@param unsigned char* 
	*	@param int length
	*	@returns void
	*/
	void setKeyBytes(unsigned char*, int);

	/**
	*	setKey()
	*
	*	@param OctetString*
	*	@returns void
	*/
	void setKey(OctetString*);

	/**
	*	getKey()
	*
	*	@param void
	*	@returns OctetString*
	*/
	OctetString* getKey();

	/** 
	*	getKeyBytes() CJM 3/28/02  This function should NOT be used anymore.. it still works
	*					for compatibility but you should use  get/setKey() instead.
	*
	*	@param void
	*	@returns unsigned char*
	*/
	unsigned char* getKeyBytes();

	/**
	*	setKeyLength()
	*
	*	@param int 
	*	@returns void
	*/
	void setKeyLength(int);

	/**
	*	getKeyLength()
	*
	*	@param void
	*	@returns int
	*/
	int getKeyLength();

	/**
	*	setCipher()
	*	@param EVP_CIPHER
	*	@returns void
	*/
	void setCipher(EVP_CIPHER*);

	/**
	*	getCipher()
	*	@param void
	*	@returns EVP_CIPHER*
	*/
	EVP_CIPHER* getCipher();

	/**
	*	setSetup()
	*
	*	@param bool
	*	@returns void
	*/
	void setSetup(bool);

	/**
	*	isSetup()
	*	
	*	@param void
	*	@returns bool
	*/
	bool isSetup();

    //## Assignment Operation (generated)
};


#endif
