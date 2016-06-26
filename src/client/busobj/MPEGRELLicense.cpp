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
#include "busobj/MPEGRELLicense.h"
#include <openssl/evp.h>
#include "crypto/HashContext.h"
#include <time.h>
#include "busobj/Exception.h"
#include "squashxml/tools/FileTool.h"
#include "squashxml/tools/RFC1521Base64.h"
#include "squashxml/tools/FileLogger.h"
#include "squashxml/tools/ByteArray.h"
#include "squashxml/xml/XMLDocument.h"
#include <string>
#include <cctype>
#include <algorithm>
#include <time.h>

#ifdef MPEGREL_SUPPORT

#include "stdafx.h"
#include "CGUtil.h"

using namespace MSXML;
#include "RELLicAuthzDriver.h"

#endif


MPEGRELLicense::MPEGRELLicense()
{
	OlMemMan::construct(&m_MPEGRELStream);
	OlMemMan::construct(&m_Key);

	/** initialize the templatestr note: these values will get overwritten */
	m_QueryRELTemplate[0]='\0';
	strcat(m_QueryRELTemplate, "<?xml version=\"1.0\"?>");
	strcat(m_QueryRELTemplate, "<query xmlns=\"http://www.contentguard.com/2002/exampleQueryNS\">");
	strcat(m_QueryRELTemplate, "<goalToCheck>");
	strcat(m_QueryRELTemplate, "<principalToCheck rsaModulus=\"XXXXXXXX\" rsaExponent=\"XX\"/>");
	strcat(m_QueryRELTemplate, "<rightToCheck>");
	strcat(m_QueryRELTemplate, "<mx:play xmlns:mx=\"urn:mpeg:mpeg21:2002:01-REL-NS\"/>");
	strcat(m_QueryRELTemplate, "</rightToCheck>");
	strcat(m_QueryRELTemplate, "<resourceToCheck uri=\"10.9901/12.i.2\"/>");
	strcat(m_QueryRELTemplate, "</goalToCheck>");
	strcat(m_QueryRELTemplate, "<simulationExerciseEnvironment>");
	strcat(m_QueryRELTemplate, "<time>YYYY-MM-DDT00:00:00</time>");
	strcat(m_QueryRELTemplate, "</simulationExerciseEnvironment>");
	strcat(m_QueryRELTemplate, "</query>");
}

MPEGRELLicense::~MPEGRELLicense()
{
	OlMemMan::destruct(&m_MPEGRELStream);
	OlMemMan::destruct(&m_Key);
}

MPEGRELLicense::MPEGRELLicense(MPEGRELLicense& right)
{
		//intiialize the attributes
	OlMemMan::construct(&m_MPEGRELStream);
	OlMemMan::construct(&m_Key);
	
	//now copy the attributes
	setBytes(right.m_MPEGRELStream);
	setKey(right.m_Key);
}

//setBytes
void MPEGRELLicense::setBytes(char* p_Bytes)
{
	OlMemMan::copy(&m_MPEGRELStream, p_Bytes);
}

//getBytes
char* MPEGRELLicense::getBytes()
{
	return m_MPEGRELStream;
}


bool MPEGRELLicense::extractEncryptedKey(::XMLDocument* p_License, UserContext* p_Principal, OctetString* p_KeyBlob)
{
	char *encodedKey=NULL, *encodedCert=NULL;
	unsigned char *privateDecryptBuf=NULL, *kbytes=NULL;
	ByteArray *certBuf=NULL, *keyBytes=NULL;
	bool isValidKey=true;
	int val=0;
	//set the defaults for the key
	p_KeyBlob->octets = NULL;
	p_KeyBlob->len = 0;
	int kbyteLen=0;

	//now extract the key and put it into the KeyBlob
	encodedKey = p_License->getString("license.otherInfo.enc:EncryptedData.dsig:KeyInfo.enc:EncryptedKey.enc:CipherData.enc:CipherValue");

	try
	{
		if (encodedKey)
		{
			int outLen=0, saveLen=0;

			//key value found, make sure it's for this user..
			encodedCert = p_License->getString("license.otherInfo.enc:EncryptedData.dsig:KeyInfo.enc:EncryptedKey.dsig:X509Data.dsig:X509Certificate");
			if (!encodedCert) 
			{
				gLogger->logError("MPEGRELLicense::extractEncryptedKey : No matching user X509Certificate tag in License.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}

			certBuf = RFC1521Base64::decode(encodedCert);

			if (!certBuf)
			{
				gLogger->logError("MPEGRELLicense::extractEncryptedKey : Error decoding User Cert B64.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}

			//now compare the memory for the decoded cert and the current user's
			if ( (val = memcmp(p_Principal->getUserCertASN1()->octets, certBuf->data(), certBuf->length())) != 0) 
			{
				gLogger->logError("MPEGRELLicense::extractEncryptedKey : User Cert does not match License X509Certificate.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}

			keyBytes = RFC1521Base64::decode(encodedKey);

			if (!keyBytes)
			{
				gLogger->logError("MPEGRELLicense::extractEncryptedKey : Error decoding encrypted key B64");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}

			privateDecryptBuf = new unsigned char[p_Principal->getRSAKeySize()];
			int bytesDecrypted = RSA_private_decrypt(keyBytes->length(), (unsigned char*)keyBytes->data(), privateDecryptBuf, p_Principal->getPrivateKey(), RSA_PKCS1_PADDING);
			if (bytesDecrypted != -1)
			{
				p_KeyBlob->octets = privateDecryptBuf;
				p_KeyBlob->len = bytesDecrypted;
			}
			else
			{
				gLogger->logError("MPEGRELLicense::extractEncryptedKey : Error decrypting License encryptedKey.");
				if (privateDecryptBuf) delete[] privateDecryptBuf;
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}
		}
		//else OK?  because it's possible to require a license for unencrypted stuff.. although I don't know why in this scenario
	}
	catch (Exception&)
	{
		//TODO:  eventually will rethrow
		isValidKey = false;
	}

	if (keyBytes) delete keyBytes;
	if (encodedKey) delete[] encodedKey;
	if (encodedCert) delete encodedCert;
	if (certBuf) delete certBuf;

	return isValidKey;
}


bool MPEGRELLicense::verifyPermissions(::XMLDocument* p_License, char* p_Permission, char* p_Resource)
{
	bool isValidPermission=true;
	char* pModulus = NULL;
	char* pExponent = NULL;
	char* pDOI = NULL;
	char* pQueryDocBytes = NULL;
    time_t ltime;
    struct tm *today;
	char tmpbuf[128];


	//check to see if they have the appropriate rights
	try
	{

		if (strcmp(p_Permission, "PLAY") != 0) 
		{
			gLogger->logError("MPEGRELLicense::verifyPermissions : Permission Not supported.");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}

		if (p_Resource == NULL) {
			gLogger->logError("MPEGRELLicense::verifyPermissions : Resource cannot be NULL.");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}
		//build the query REL doc...
		//convert the modulus to a byte array
		/** 
		RSA* pKey = p_Principal->getPrivateKey();
		int howLong = BN_num_bytes(pKey->n);
		modulusBytes = new unsigned char[howLong];
		int bytes =  BN_bn2bin(pKey->n, modulusBytes);

		//convert to Base64
		ByteArray modulusByteArray((char*)modulusBytes, bytes);
		modulusBase64 = RFC1521Base64::encode(&modulusByteArray);

		//convert exponent to byte array
		howLong = BN_num_bytes(pKey->e);
		exponentBytes = new unsigned char[howLong];
		bytes = BN_bn2bin(pKey->e, exponentBytes);

		//convert to Base64
		ByteArray exponentByteArray((char*)exponentBytes, bytes);
		exponentBase64 = RFC1521Base64::encode(&exponentByteArray);
		*/

#ifdef MPEGREL_SUPPORT
 
		CRELLicAuthzDriver driver;
		::XMLDocument queryDoc;

		if (!(queryDoc.decode(m_QueryRELTemplate, "query")))
		{
			gLogger->logError("MPEGRELLicense::verifyPermissions : Unable to Decode QueryDoc.");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}

		pModulus = p_License->getString("license.grant.keyHolder.info.dsig:KeyValue.dsig:RSAKeyValue.dsig:Modulus");
		if (!pModulus) {
			gLogger->logError("MPEGRELLicense::verifyPermissions : Unable to obtain RSAmodulus");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}

		pExponent = p_License->getString("license.grant.keyHolder.info.dsig:KeyValue.dsig:RSAKeyValue.dsig:Exponent");
		if (!pExponent) {
			gLogger->logError("MPEGRELLicense::verifyPermissions : Unable to obtain RSAExponent");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}

		DataTypeAttribute modulusAttr("rsaModulus", pModulus);
		DataTypeAttribute exponentAttr("rsaExponent", pExponent);
		DataTypeAttribute doiAttr("uri", p_Resource);

		//joen - TEMPORARY testing for memory issues vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
		if(strcmp(pModulus,modulusAttr.getValue())!=0)
		{
			gLogger->logError("MPEGRELLicense::verifyPermissions : modulusAttr memory corrupt");
			gLogger->logError(modulusAttr.getValue());
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}
		if(strcmp(pExponent,exponentAttr.getValue())!=0)
		{
			gLogger->logError("MPEGRELLicense::verifyPermissions : exponentAttr memory corrupt");
			gLogger->logError(exponentAttr.getValue());
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}
		if(strcmp(p_Resource,doiAttr.getValue())!=0)
		{
			gLogger->logError("MPEGRELLicense::verifyPermissions : doiAttr memory corrupt");
			gLogger->logError(doiAttr.getValue());
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

		DataTypeAttribute *principalAttList[] = { &modulusAttr, &exponentAttr, /*DON'T FORGET*/(DataTypeAttribute*)NULL };
		DataTypeAttribute *doiAttList[] = { &doiAttr, (DataTypeAttribute*)NULL };

		queryDoc.setAttributeList("goalToCheck.principalToCheck", principalAttList);
		queryDoc.setAttributeList("goalToCheck.resourceToCheck", doiAttList);

		time( &ltime );
    
		/* Convert to time structure and adjust for PM if necessary. */
	    today = localtime( &ltime );
	    strftime( tmpbuf, 128, "%Y-%m-%dT%H:%M:%S", today );
		queryDoc.setString("simulationExerciseEnvironment.time", tmpbuf);
		pQueryDocBytes = queryDoc.encode();


		/** Now, call out to ContentGuard driver.. */
		CComBSTR bstrLic(getBytes()), bstrQuery(pQueryDocBytes);

		gLogger->logDebug(getBytes());
		gLogger->logDebug(pQueryDocBytes);
		HRESULT hr = driver.relAuthorizeRight(bstrLic, bstrQuery, false);

		if (hr != S_OK)
		{
			gLogger->logError("MPEGRELLicense::verifyPermissions : RELLicAuthzDriver Failed to Authorize.");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}
#endif

	}
	catch (Exception&)
	{
		isValidPermission = false;
	}
	
	if (pModulus) delete[] pModulus;
	if (pExponent) delete[] pExponent;	
	if (pQueryDocBytes) delete[] pQueryDocBytes;

	return isValidPermission;
}

//License interface implementation
bool MPEGRELLicense::authorize(char* p_Permission, UserContext* p_Principal, char* p_Resource, OctetString* p_KeyBlob)
{ 
	::XMLDocument licenseDoc;
      	bool isValidLicense = true;

	try
	{
#ifndef MPEGREL_SUPPORT
	gLogger->logError("MPEGRELLicense::authorize : MPEGREL NOT SUPPORTED!");
	throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
#endif

		//parse this license
		if (!(licenseDoc.decode(getBytes(), "licenseGroup"))) {
			gLogger->logError("MPEGRELLicense::verifyPermissions : RELLicAuthzDriver returned E_FAIL.");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}

		//MPEG REL Driver combines license and auth checks...
		if (!verifyPermissions(&licenseDoc, p_Permission, p_Resource)) throw EXCEPTION(Exception::UNEXPECTED_CONDITION);

		//extract the key from the license, if one is there
		if (!extractEncryptedKey(&licenseDoc, p_Principal, p_KeyBlob)) throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
	}
	catch (Exception&)
	{
	gLogger->logError("MPEGRELLicense::authorize : Authorization Failed!");
		isValidLicense = false;
	}
		
	return isValidLicense;
}

//License interface implementation
License* MPEGRELLicense::dup()
{
	//implementation to make a copy of myself 
	//initialize the copy constructor with this pointer
	MPEGRELLicense* newLicense = new MPEGRELLicense();

	newLicense->setBytes(this->getBytes());
	newLicense->setKey(this->getKey());

	return newLicense;
}

//License interface implementation
char* MPEGRELLicense::toString()
{
	return getBytes();
}

//License interface implementation
void MPEGRELLicense::setKey(char* p_Key)
{
	OlMemMan::copy(&m_Key, p_Key);
}

//License interface implementation
char* MPEGRELLicense::getKey()
{
	return m_Key;
}