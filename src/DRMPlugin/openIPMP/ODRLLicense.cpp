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
#include "busobj/ODRLLicense.h"
#include <openssl/evp.h>
#include "crypto/HashContext.h"
#include <time.h>
#include "busobj/Exception.h"
#include "squashxml/tools/FileTool.h"
#include "squashxml/tools/RFC1521Base64.h"
#include "squashxml/tools/FileLogger.h"
#include <string>
#include <cctype>
#include <algorithm>

ODRLLicense::ODRLLicense()
{
	OlMemMan::construct(&m_ODRLStream);
	OlMemMan::construct(&m_Key);
}

ODRLLicense::~ODRLLicense()
{
	OlMemMan::destruct(&m_ODRLStream);
	OlMemMan::destruct(&m_Key);
}

ODRLLicense::ODRLLicense(ODRLLicense& right)
{
		//intiialize the attributes
	OlMemMan::construct(&m_ODRLStream);
	OlMemMan::construct(&m_Key);
	
	//now copy the attributes
	setBytes(right.m_ODRLStream);
	setKey(right.m_Key);
}

//setBytes
void ODRLLicense::setBytes(char* p_Bytes)
{
	OlMemMan::copy(&m_ODRLStream, p_Bytes);
}

//getBytes
char* ODRLLicense::getBytes()
{
	return m_ODRLStream;
}


//TODO:  put in exception handling.. and fix for efficiency
time_t ODRLLicense::parseISO8601DateTime(char* p_ConstraintDateTime)
{
	//check the timeout vals
	struct tm constraintDateTimeStruct;
	char dateTemp[20];
	char timeTemp[20];
	char valTemp[20];
	int year=0, month=0, day=0, hours=0, mins=0, secs=0;
	char *current=NULL, *pdest=NULL;

	pdest = strchr( p_ConstraintDateTime, 'T' );

	if (!pdest) return (time_t)-1;

	int numChars = pdest - p_ConstraintDateTime;

	strncpy(dateTemp, p_ConstraintDateTime, numChars);
	dateTemp[numChars] = 0x00;

	pdest++;  //move past the 'T'
	numChars = strlen(pdest);

	if (numChars == 0) return (time_t)-1;

	strncpy(timeTemp, pdest, numChars);
	timeTemp[numChars] = 0x00;

	//parse year
	current = dateTemp;
	pdest = strchr(current, '-');
	if (!pdest) return (time_t)-1;

	numChars = pdest - current;
	strncpy(valTemp, current, numChars);
	valTemp[numChars] = 0x00;

	year = atoi(valTemp);

	if (year == 0) return (time_t)-1;

	constraintDateTimeStruct.tm_year = year - 1900;

	//parse month
	current = ++pdest;
	//TODO: not found error malformed date
	pdest = strchr(current, '-');
	if (!pdest) return (time_t)-1;

	numChars = pdest - current;
	strncpy(valTemp, current, numChars);
	valTemp[numChars] = 0x00;

	month = atoi(valTemp);

	constraintDateTimeStruct.tm_mon = month - 1;

	//parse day
	current = ++pdest;
	numChars = strlen(current);
	if (numChars == 0) return (time_t)-1;

	strncpy(valTemp, current, numChars);
	valTemp[numChars] = 0x00;

	day = atoi(valTemp);

	constraintDateTimeStruct.tm_mday = day;

	//parse out time

	//parse hours
	current = timeTemp;
	pdest = strchr(current, ':');

	if (!pdest) return (time_t)-1;

	numChars = pdest - current;
	strncpy(valTemp, current, numChars);
	valTemp[numChars] = 0x00;
	
	hours = atoi(valTemp);

	constraintDateTimeStruct.tm_hour = hours;

	//parse mins 
	current = ++pdest;
	pdest = strchr(current, ':');

	if (!pdest) return (time_t)-1;

	numChars = pdest - current;
	strncpy(valTemp, current, numChars);
	valTemp[numChars] = 0x00;

	mins = atoi(valTemp);

	constraintDateTimeStruct.tm_min = mins;

	//parse secs
	current = ++pdest;
	numChars = strlen(current);
	if (numChars==0) return (time_t)-1;

	strncpy(valTemp, current, numChars);
	valTemp[numChars] = 0x00;

	secs = atoi(valTemp);

	constraintDateTimeStruct.tm_sec = secs;

	//Let C runtime figure out the daylight savings
	constraintDateTimeStruct.tm_isdst = -1;
	
	return (mktime(&constraintDateTimeStruct));
}


//TODO Exception handling instead of the corny boolean return code
bool ODRLLicense::verifySignature(XMLDocument* p_LicenseDoc, UserContext* p_Principal)
{
	char* origLicenseXML = NULL;
	char* tbsXML = NULL;
	char* sigXML = NULL;
	char* hashBase64 = NULL;
	ByteArray* hashBytes = NULL;
	XMLDocument* pLicenseSigDoc = NULL;
	ByteArray* sigBytes = NULL;
	int outLen=0, saveLen=0;
	HashContext hashCtx;
	bool isError = false;
	int val=0;
	char* tempSigBuffer=NULL;
	char* origLicenseBuffer=NULL;
	char* pdest = NULL;
	int saveLength1=0, saveIndex1=0, lastLength = 0;
	std::string license;
	std::string::size_type pos1=0, pos2=0, finalLength=0;

	/**  Check Signature
	1. clone the license doc
	2. remove the signature section
	3. calculate a hash
	4. base64 decode the signature in the doc 
	5. call signatureVerify, pass in the local certificateChain
	*/

	if ( (p_LicenseDoc == NULL) || (p_Principal == NULL) )
	{
		gLogger->logError("ODRLLicense::verifySignature : p_License or p_Principal is NULL.");
		isError = true;
		goto error;
	}

/*	CJM 10/29/02 origLicenseXML = p_LicenseDoc->encode();
	if (origLicenseXML == NULL)
	{
		isError = true;
		goto error;
	}

	pLicenseSigDoc = new XMLDocument();
	pLicenseSigDoc->decode(origLicenseXML, "o-ex:rights");

	if (pLicenseSigDoc == NULL)
	{
		isError = true;
		goto error;
	}

	if (!pLicenseSigDoc->remove("ds:Signature"))
	{
		isError = true;
		goto error;
	}

	tbsXML = pLicenseSigDoc->encode();

	if (tbsXML == NULL)
	{
		isError = true;
		goto error;
	}
*/

	/** CJM hackfest '02
		Ok.. here's the deal..due to different limitations in both our library and due to the 
		fact that there's differences in how Java (where our licenses are constructed) and C++
		(where the license signatures are checked) manage XML encoding.. we need to implement a 
		hacked up signature checking algorithm..  The following code replaces the code above.
	*/
	license = getBytes();

	std::transform(license.begin(),license.end(), license.begin(),tolower);
	pos1 = license.find ("<ds:signature>",0);

	if (pos1 == std::string::npos)
	{
		gLogger->logError("ODRLLicense::verifySignature : Signature start tag not found in License XML.");
		isError = true;
		goto error;
	}
	pos2 = license.find ("</ds:signature>",0);

	if (pos2 == std::string::npos)
	{
		gLogger->logError("ODRLLicense::verifySignature : Signature end tag not found in License XML.");
		isError = true;
		goto error;
	}
	pos2 += strlen("</ds:Signature>");
	
	//reset it to the original
	license = getBytes();
	license.erase(pos1, (pos2 - pos1));

   
	//TODO: CHECK ALGORITHM defined in the license.. 
	hashCtx.setHashType(EVP_sha1());
	hashCtx.hashInit();
	hashCtx.hashUpdate((unsigned char*)license.c_str(), strlen(license.c_str()));
	hashCtx.hashFinal();

	//read the hash bytes
	hashBase64 = p_LicenseDoc->getString("ds:Signature.ds:SignedInfo.ds:Reference.ds:DigestValue");

	hashBytes = RFC1521Base64::decode(hashBase64);

	if (!hashBytes)
	{
		gLogger->logError("ODRLLicense::verifySignature : Error Decoding DigestValue B64");
		isError = true;
		goto error;
	}


	if ( (val = memcmp(hashBytes->data(), hashCtx.getHashBytes(), hashBytes->length())) != 0)
	{
		gLogger->logError("ODRLLicense::verifySignature : License Hash does not match local hash calculation.");
		isError = true;
		goto error;
	}
	
	//read the signature
	sigXML = p_LicenseDoc->getString("ds:Signature.ds:SignatureValue");

	if (!sigXML)
	{
		gLogger->logError("ODRLLicense::verifySignature : Can't extract SignatureValue from License.");
		isError = true;
		goto error;
	}

	sigBytes = RFC1521Base64::decode(sigXML);
	if (!sigBytes)
	{
		gLogger->logError("ODRLLicense::verifySignature : Error decoding SignatureValue B64.");
		isError = true;
		goto error;
	}
	if (!hashCtx.verifySignature((unsigned char*)sigBytes->data(), sigBytes->length(), p_Principal->getCaCertChain()))
	{
		gLogger->logError("ODRLLicense::verifySignature : License Signature Check Failed.");
		isError = true;
		goto error;
	}

//lamey lame lame
error:
		if (origLicenseXML) delete[] origLicenseXML;
		if (tbsXML) delete[] tbsXML;
		if (sigXML) delete[] sigXML;
		if (pLicenseSigDoc) delete pLicenseSigDoc;
		if (sigBytes)delete sigBytes;
		if (tempSigBuffer) delete[] tempSigBuffer;
		if (hashBytes) delete hashBytes;
    if (hashBase64) delete[] hashBase64;

		if (isError)
			return false;
		
		return true;
}


bool ODRLLicense::verifyPermissions(XMLDocument* p_License, char* p_Permission)
{
	XMLDocument* permission=NULL;
	char* startDateTime=NULL;
	char* endDateTime=NULL;
	time_t now;
	bool isValidPermission=true;

	//check to see if they have the appropriate rights
	if (strcmp(p_Permission, "PLAY") == 0)
	{
		//check play rights
		permission = p_License->getSubDoc("o-ex:agreement.o-ex:permission.o-dd:play");
		if (!permission) 
		{
			gLogger->logError("ODRLLicense::verifyPermissions : No matching PLAY tag in License.");
			isValidPermission = false;
			goto error;
		}

		//check the timeout vals
		startDateTime = p_License->getString("o-ex:agreement.o-ex:permission.o-dd:play.o-ex:constraint.o-dd:datetime.o-dd:start");
		if (!startDateTime)
		{
			gLogger->logError("ODRLLicense::verifyPermissions : No matching STARTIME tag in License.");
			isValidPermission = false;
			goto error;
		}

		endDateTime = p_License->getString("o-ex:agreement.o-ex:permission.o-dd:play.o-ex:constraint.o-dd:datetime.o-dd:end");
		if (!endDateTime)
		{
			gLogger->logError("ODRLLicense::verifyPermissions : No matching ENDTIME tag in License.");
			isValidPermission = false;
			goto error;
		}

		time_t startDate = parseISO8601DateTime(startDateTime);	
		time_t endDate = parseISO8601DateTime(endDateTime);

		time(&now);

		if ( (now < startDate) || (now > endDate) )
		{
			gLogger->logError("ODRLLicense::verifyPermissions : Time constraint check failed.");
			isValidPermission = false;
			goto error;
		}

	}
	else
		isValidPermission=false;


error:	
		if (permission) delete permission;
		if (startDateTime) delete[] startDateTime;
		if (endDateTime) delete[] endDateTime;

		return isValidPermission;
}

bool ODRLLicense::extractEncryptedKey(XMLDocument* p_License, UserContext* p_Principal, OctetString* p_KeyBlob)
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
	encodedKey = p_License->getString("o-ex:agreement.o-ex:asset.ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.enc:CipherData.enc:CipherValue");

	try
	{
		if (encodedKey)
		{
			int outLen=0, saveLen=0;

			//key value found, make sure it's for this user..
			encodedCert = p_License->getString("o-ex:agreement.o-ex:asset.ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.ds:X509Data.ds:X509Certificate");
			if (!encodedCert) 
			{
				gLogger->logError("ODRLLicense::extractEncryptedKey : No matching user X509Certificate tag in License.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}

			certBuf = RFC1521Base64::decode(encodedCert);

			if (!certBuf)
			{
				gLogger->logError("ODRLLicense::extractEncryptedKey : Error decoding User Cert B64.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}

			//now compare the memory for the decoded cert and the current user's
			if ( (val = memcmp(p_Principal->getUserCertASN1()->octets, certBuf->data(), certBuf->length())) != 0) 
			{
				gLogger->logError("ODRLLicense::extractEncryptedKey : User Cert does not match License X509Certificate.");
				throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
			}

			keyBytes = RFC1521Base64::decode(encodedKey);

			if (!keyBytes)
			{
				gLogger->logError("ODRLLicense::extractEncryptedKey : Error decoding encrypted key B64");
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
				gLogger->logError("ODRLLicense::extractEncryptedKey : Error decrypting License encryptedKey.");
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

//License interface implementation
bool ODRLLicense::authorize(char* p_Permission, UserContext* p_Principal, char* p_Resource, OctetString* p_KeyBlob)
{
	XMLDocument* pLicenseDoc = NULL;
	bool isValidLicense = true;

	try
	{
		// Create and Parse the XMLDocument
		pLicenseDoc = new XMLDocument();

		if (pLicenseDoc == NULL) 
		{
			gLogger->logError("ODRLLicense::authorize : Unable to alloc mem for XMLDocument.");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}

		//parse the XML license
		bool goodDocument = pLicenseDoc->decode(getBytes(), "o-ex:rights");

		if (!goodDocument) 
		{
			gLogger->logError("ODRLLicense::authorize : Error parsing License XML.");
			throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		}

		//verify the signature
		if (!verifySignature(pLicenseDoc, p_Principal)) throw EXCEPTION(Exception::UNEXPECTED_CONDITION);

		//verify the permissions
		if (!verifyPermissions(pLicenseDoc, p_Permission)) throw EXCEPTION(Exception::UNEXPECTED_CONDITION);

		//extract the key from the license, if one is there
		if (!extractEncryptedKey(pLicenseDoc, p_Principal, p_KeyBlob)) throw EXCEPTION(Exception::UNEXPECTED_CONDITION);
		
	}
	catch (Exception&)
	{
		//TODO:  eventually will rethrow
		isValidLicense = false;
	}

	if (pLicenseDoc) delete pLicenseDoc;
		
	return isValidLicense;
}

//License interface implementation
License* ODRLLicense::dup()
{
	//implementation to make a copy of myself 
	//initialize the copy constructor with this pointer
	ODRLLicense* newLicense = new ODRLLicense();

	newLicense->setBytes(this->getBytes());
	newLicense->setKey(this->getKey());

	return newLicense;
}

//License interface implementation
char* ODRLLicense::toString()
{
	return getBytes();
}

//License interface implementation
void ODRLLicense::setKey(char* p_Key)
{
	OlMemMan::copy(&m_Key, p_Key);
}

//License interface implementation
char* ODRLLicense::getKey()
{
	return m_Key;
}




