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
#include "crypto/CipherContext.h"
#include "tools/MemMan.h"
#include <iostream>
#include <assert.h>
#include "squashxml/tools/FileLogger.h"


CipherContext::CipherContext()
{
	m_Cipher = NULL;
	MemMan::construct(&m_Key);
	MemMan::construct(&m_Ivec);
	MemMan::construct(&m_KeyLength);
	MemMan::construct(&m_KeyObject);
	m_IsSetup = false;
//TODO:  remove if retest ok	EVP_CIPHER_CTX_init(&m_Ctx);
}

CipherContext::~CipherContext()
{
//TODO: remove if retest ok	EVP_CIPHER_CTX_cleanup(&m_Ctx);
	MemMan::destruct(&m_Key);
	MemMan::destruct(&m_Ivec);
	MemMan::destruct(&m_KeyLength);
	MemMan::destruct(&m_KeyObject);
	m_IsSetup = false;
}

CipherContext::CipherContext(CipherContext &right)
{
	m_Cipher = NULL;
	MemMan::construct(&m_Key);
	MemMan::construct(&m_Ivec);
	MemMan::construct(&m_KeyLength);
	MemMan::construct(&m_KeyObject);
//TODO: remove if retest ok	EVP_CIPHER_CTX_init(&m_Ctx);
	m_IsSetup = false;

	//copy the data 
//TODO: remove if retest ok	memcpy(&m_Ctx, &right.m_Ctx, sizeof(right.m_Ctx));
	m_Cipher = right.m_Cipher;
	m_IsSetup = right.m_IsSetup;
	MemMan::copy(&m_KeyObject, right.m_KeyObject);
	MemMan::copy(&m_KeyLength, right.m_KeyLength);
	MemMan::copy(&m_Key, right.m_Key, EVP_MAX_KEY_LENGTH);

}


//KeyLength
void CipherContext::setKeyLength(int p_KeyLengthInBits)
{
	MemMan::copy(&m_KeyLength, p_KeyLengthInBits);
}

int CipherContext::getKeyLength()
{
	return m_KeyLength;
}

//KeyBytes
void CipherContext::setKeyBytes(unsigned char* p_Key, int p_Length)
{
	MemMan::copy(&m_Key, p_Key, p_Length);
}

unsigned char* CipherContext::getKeyBytes()
{
	return m_Key;
}

//Key
void CipherContext::setKey(OctetString* p_Key)
{
	MemMan::copy(&m_KeyObject, p_Key);
	//set the key length
	setKeyLength(m_KeyObject->len * 8);

	//CJM hack?
	setKeyBytes(m_KeyObject->octets, m_KeyObject->len);
}

OctetString* CipherContext::getKey()
{
	return m_KeyObject;
}

/** THIS MEMORY IS STATIC.. does not need to be copied */
void CipherContext::setCipher(EVP_CIPHER* p_Cipher)
{
	m_Cipher = p_Cipher;
}

EVP_CIPHER* CipherContext::getCipher()
{
	return m_Cipher;
}

bool CipherContext::encryptInit()
{
	/** initialize the encryption context */

	/** CJM 8-17-05 moving CTX_init here to fix problem with copy constructor */
	EVP_CIPHER_CTX_init(&m_Ctx);
	EVP_EncryptInit(&m_Ctx, m_Cipher, m_Key, m_Ivec);

	m_IsSetup = true;

	return m_IsSetup;
}

bool CipherContext::encryptFinal(unsigned char* p_CipherText, int* p_CipherTextLen)
{
	if (m_IsSetup)
	{
		EVP_EncryptFinal(&m_Ctx, p_CipherText, p_CipherTextLen);
	/** CJM 08-17-05 moving cleanup here to fix problem with copy constructor */
		EVP_CIPHER_CTX_cleanup(&m_Ctx);
	}
	else
	{
		gLogger->logError("CipherContext::encryptFinal : CipherContext not setup.");
		return false;
	}

	return true;
}


/** do encryption */
bool CipherContext::encryptUpdate(unsigned char* p_ClearText, int p_ClearTextLen, unsigned char* p_CipherText, int* p_CipherTextLen)
{
	if (m_IsSetup)
		EVP_EncryptUpdate(&m_Ctx, p_CipherText, p_CipherTextLen, p_ClearText, p_ClearTextLen);
	else
	{
		gLogger->logError("CipherContext::encryptUpdate : CipherContext not setup.");
		return false;
	}

	return true;
}

bool CipherContext::decryptInit()
{
	/** CJM 8-17-05 moving CTX_init here to fix problem with copy constructor */
	EVP_CIPHER_CTX_init(&m_Ctx);
	EVP_DecryptInit(&m_Ctx, m_Cipher, m_Key, m_Ivec);
	m_IsSetup = true;
	return m_IsSetup;

}

bool CipherContext::decryptFinal(unsigned char* p_ClearText, int* p_ClearTextLen)
{
	if (m_IsSetup) 
	{
		EVP_DecryptFinal(&m_Ctx, p_ClearText, p_ClearTextLen);
	/** CJM 8-17-05 moving cleanup here to fix problem with copy constructor */
		EVP_CIPHER_CTX_cleanup(&m_Ctx);
	}
	else
		gLogger->logError("CipherContext::decryptFinal : CipherContext not setup.");

	return m_IsSetup;
}

/** do decryption */
bool CipherContext::decryptUpdate(unsigned char* p_CipherText, int p_CipherTextLen, unsigned char* p_ClearText, int* p_ClearTextLen)
{
	//TODO check return codes
	//TODO check isSetup

	if (m_IsSetup)
		EVP_DecryptUpdate(&m_Ctx, p_ClearText, p_ClearTextLen, p_CipherText, p_CipherTextLen);
	else
		gLogger->logError("CipherContext::decryptUpdate : CipherContext not setup.");
	return true;
}

//isSetup
void CipherContext::setSetup(bool p_Setup)
{
	m_IsSetup = p_Setup;
}

bool CipherContext::isSetup()
{
	return m_IsSetup;

}









