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

#include "busobj/XRMLLicense.h"
#include "tools/OlMemMan.h"
#include <openssl/evp.h>

#include "squashxml/xml/XMLDocument.h"


XRMLLicense::XRMLLicense()
{
	OlMemMan::construct(&m_XRMLStream);
	OlMemMan::construct(&m_Key);
}

XRMLLicense::~XRMLLicense()
{
	OlMemMan::destruct(&m_XRMLStream);
	OlMemMan::destruct(&m_Key);
}

XRMLLicense::XRMLLicense(XRMLLicense& right)
{
		//intiialize the attributes
	OlMemMan::construct(&m_XRMLStream);
	OlMemMan::construct(&m_Key);
	
	//now copy the attributes
	setBytes(right.m_XRMLStream);
	setKey(right.m_Key);
}

//setBytes
void XRMLLicense::setBytes(char* p_Bytes)
{
	OlMemMan::copy(&m_XRMLStream, p_Bytes);
}

//getBytes
char* XRMLLicense::getBytes()
{
	return m_XRMLStream;
}


//License interface implementation
bool XRMLLicense::authorize(char* p_Right, UserContext* p_Principal, char* p_Resource, OctetString* p_KeyBlob)
{
	//implement a VERY basic authorization algorithm.. XRML2.0 has documented
	//the auth algorithm for the core components.. needs to be implemented

		// Create and Parse the XMLDocument
	XMLDocument* pLicenseDoc = new XMLDocument();
	if (pLicenseDoc == NULL)
	{
    std::cout << "XRMLLicense::authorize - could not create XMLDocument" << std::endl;
		return false;
	}

	//parse the XML license
	pLicenseDoc->decode(getBytes(), "com.mutable.osms.common.io.message.osmsMessageLicenseResponse");

	// check the user's identity here..
	//char* pubKey = pLicenseDoc->getString("grant.keyHolder.info.dsig:KeyValue.dsig:RSAKeyValue.dsig:Modulus");

	//verify the DCD content ID stuff here...

	//check to see if they have the appropriate rights
	if (strcmp(p_Right, "PLAY") == 0)
	{
		//check play rights
		char* right = pLicenseDoc->getString("RightsInfo");
	if (right)
	{
			//now extract the key and put it into the KeyBlob
			char* encodedKey = pLicenseDoc->getString("TrackKey");

			if (encodedKey)
			{
				//key value found, it's at least as big as the B64-encoded key
				unsigned char* keyBytes = (unsigned char*)malloc(sizeof(unsigned char)*strlen(encodedKey));
				int outLen=0, saveLen=0;
				EVP_ENCODE_CTX dCtx;
				EVP_DecodeInit(&dCtx);
	
				EVP_DecodeUpdate(&dCtx, keyBytes, &outLen, (unsigned char*)encodedKey, strlen((const char*)encodedKey));
				saveLen = outLen;
				EVP_DecodeFinal(&dCtx, keyBytes, &outLen);
				saveLen = saveLen + outLen;

				p_KeyBlob->octets = keyBytes;
				p_KeyBlob->len = saveLen;

			}
			else
			{
				//no key set defaults..
				p_KeyBlob->octets = NULL;
				p_KeyBlob->len = 0;
			}
			delete pLicenseDoc;
			delete right;
			return true;
	}
	else
	{
			delete pLicenseDoc;
			delete right;
			return false;
	}

	}
	if (strcmp(p_Right, "READ") == 0)
	{
		//check read 
		return true;
	}

	return false;
}

//License interface implementation
License* XRMLLicense::dup()
{
	//implementation to make a copy of myself 
	//initialize the copy constructor with this pointer
	XRMLLicense* newLicense = new XRMLLicense();

	newLicense->setBytes(this->getBytes());
	newLicense->setKey(this->getKey());

	return newLicense;
}

//License interface implementation
char* XRMLLicense::toString()
{
	return getBytes();
}

//License interface implementation
void XRMLLicense::setKey(char* p_Key)
{
	OlMemMan::copy(&m_Key, p_Key);
}

//License interface implementation
char* XRMLLicense::getKey()
{
	return m_Key;
}




