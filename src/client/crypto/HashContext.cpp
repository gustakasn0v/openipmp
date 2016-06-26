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
#include "crypto/HashContext.h"
#include "tools/MemMan.h"
#include "squashxml/tools/FileLogger.h"

#include <iostream>
#include <assert.h>


HashContext::HashContext()
{
	MemMan::construct(&m_HashLength);
}

//copy constructor 
HashContext::HashContext(HashContext &right)
{
	//copy data to the new object
	MemMan::construct(&m_HashLength);
	MemMan::copy(&m_HashLength, right.m_HashLength);

	/** copy the hash data */
	memcpy(&m_Ctx, &right.m_Ctx, sizeof(m_Ctx));
	memcpy(m_HashBytes, right.m_HashBytes, EVP_MAX_MD_SIZE);
	m_HashType = right.m_HashType;

}

HashContext::~HashContext()
{
	MemMan::destruct(&m_HashLength);
}

void HashContext::setHashType(const EVP_MD* p_Type)
{
	//THIS IS STATIC memory.. do not delete
	m_HashType = p_Type;
}

bool HashContext::hashInit()
{
	//TODO set isSetup = true

	//TODO check return code
	EVP_DigestInit(&m_Ctx, m_HashType);

	return true;
}


bool HashContext::hashUpdate(unsigned char* p_Data, int p_Length)
{
	//TODO check isSetupFlag

	EVP_DigestUpdate(&m_Ctx, p_Data, p_Length);

	return true;
}

bool HashContext::hashFinal(unsigned char* p_Hash, int* p_HashLength)
{
	// TODO check isSetupFlag

	EVP_DigestFinal(&m_Ctx, m_HashBytes, &m_HashLength);

	/* if they passed in a buffer, copy the bytes to the buffer and set the length */
	if (p_Hash)
	{
		memcpy(p_Hash, m_HashBytes, m_HashLength);
		*p_HashLength = m_HashLength;
	}

	return true;
}

bool HashContext::signHashBytes(unsigned char* p_Sig, unsigned int* p_SigLen, RSA* p_PrivateKey)
{
	int retCode = RSA_sign(NID_sha1, m_HashBytes, m_HashLength, p_Sig, p_SigLen, p_PrivateKey);

	if (retCode != 0)
	{
		gLogger->logError("HashContext::signHashBytes : Bad return code from RSA_sign.");
		return false;
	}
	else
		return true;
}

//verify signature using one public key
bool HashContext::verifySignature(unsigned char* p_Sig, unsigned int p_SigLen, X509* p_Cert)
{
	//first, get the RSA structure from the user cert 
	EVP_PKEY* pubKey = NULL;

	pubKey = X509_get_pubkey(p_Cert);

	if (!pubKey)
	{
		//TODO throw exception
		gLogger->logError("HashContext::verifySignature : Unable to extract pubkey from Certificate.");
		return false;
	}

	if (!RSA_verify(NID_sha1, m_HashBytes, m_HashLength, p_Sig, p_SigLen, pubKey->pkey.rsa))
	{
		gLogger->logError("HashContext::verifyHashBytes : Bad return code from RSA_verify.");
		EVP_PKEY_free(pubKey);
		return false;
	}
	EVP_PKEY_free(pubKey);
	return true;
}

//test sig verification against a list of public keys
bool HashContext::verifySignature(unsigned char* p_Sig, unsigned int p_SigLen, STACK_OF(X509)* p_CertChain)
{
	bool verified=false;
	/** loop over the list of certificates and see if any verify the signatures */
	//delete the existing stack, copy the elements to the new stack object
	for (int i =0; i < sk_X509_num(p_CertChain); i++) 
	{
		EVP_PKEY* pubKey = X509_get_pubkey(sk_X509_value(p_CertChain, i));
		if (!pubKey) {
			//TODO throw exception
			gLogger->logError("HashContext::verifySignature : Unable to extract pubkey from Certificate.");
			break;
		}

		if (!RSA_verify(NID_sha1, m_HashBytes, m_HashLength, p_Sig, p_SigLen, pubKey->pkey.rsa))
		{
			gLogger->logError("HashContext::verifySignature : Bad return code from RSA_verify.");
			EVP_PKEY_free(pubKey);
		}
		else
		{
			EVP_PKEY_free(pubKey);
			verified = true;
			break;
		}
	}

	return verified;
}


unsigned char* HashContext::getHashBytes()
{
	//DO NOT DELETE THIS POINTER
	return m_HashBytes;
}

unsigned int HashContext::getHashLength()
{
	return m_HashLength;
}