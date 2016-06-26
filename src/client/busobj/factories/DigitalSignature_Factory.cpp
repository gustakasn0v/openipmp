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
#include <stdio.h>
#include <sys/stat.h>

#include "busobj/factories/DigitalSignature_Factory.h"
#include "squashxml/xml/XMLDocument.h"
#include "squashxml/tools/FileLogger.h"
#include "squashxml/tools/ByteArray.h"
#include "squashxml/tools/RFC1521Base64.h"

DigitalSignature_Factory::DigitalSignature_Factory()
{
}

DigitalSignature_Factory::~DigitalSignature_Factory()
{
}

// create DigitalSignature instance with hardcoded values
DigitalSignature* DigitalSignature_Factory::CreateInstanceFromFile (const char* xml_filename)
{

    // read from xml file into a memory buffer
    FILE* fp;
    struct stat tstat;
    stat(xml_filename, &tstat);
    fp = fopen(xml_filename, "rb");
    if (!fp) {
        gLogger->logError("Failed attempt to open xml file. Returning...");
        return(NULL);	// TODO: this should probably throw an exception
    }
    char* xmlText = (char*) malloc(tstat.st_size+1);
    fread(xmlText, tstat.st_size, 1, fp);
	xmlText[tstat.st_size]=0x00;
    fclose(fp);

    // instantiate new DigitalSignature
    DigitalSignature* pDigitalSignature = NULL;
	pDigitalSignature = CreateInstance(xmlText);

	// free xml memory buffer
    free(xmlText);

	return(pDigitalSignature);
}

// create DigitalSignature instance with values initialized from parsed XML stream
DigitalSignature* DigitalSignature_Factory::CreateInstance (const char* xml_stream)
{

	// make sure xml_stream is populated
	if (!xml_stream) {
        gLogger->logError("Aborting attempt to parse NULL xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
	}

    // instantiate new DigitalSignature
    DigitalSignature* pDigitalSignature = new DigitalSignature();

	// instantiate XMLDocument
	XMLDocument xdoc;

    // decode xml text buffer into an XMLDocument
    if ( !xdoc.decode(xml_stream, "Signature") ) {
        gLogger->logError("Failed attempt parse xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
    }

    // SignatureValue - Required
    char* SignatureValueVal = xdoc.getString("SignatureValue");
    if (SignatureValueVal == NULL)
    {
        gLogger->logError("SignatureValue value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDigitalSignature->set_SignatureValue_base64(SignatureValueVal);

	// base 64 decode the SignatureValue
	ByteArray* SignatureValueBytes = RFC1521Base64::decode(SignatureValueVal);
	if (!SignatureValueBytes ) {
		gLogger->logError("Failed attempt to Base 64 decode SignatureValue - AYMAN");
        return(NULL);	// TODO: this should probably throw an exception
	}
	OctetString SignatureValueOctets;
	SignatureValueOctets.len = SignatureValueBytes->length();
	SignatureValueOctets.octets = (unsigned char*) SignatureValueBytes->data();
	pDigitalSignature->set_SignatureValue_octets( &SignatureValueOctets );

	delete[] SignatureValueVal;

    // Certificate - Required
    char* CertificateVal = xdoc.getString("KeyInfo.X509Data.X509Certificate");
    if (CertificateVal == NULL)
    {
        gLogger->logError("KeyInfo.X509Data.X509Certificate value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDigitalSignature->set_Certificate_base64(CertificateVal);

	// base 64 decode the Certificate AYMAN
	ByteArray* CertificateBytes = RFC1521Base64::decode(CertificateVal);
	if (!CertificateBytes ) {
		gLogger->logError("Failed attempt to Base 64 decode Certificate");
        return(NULL);	// TODO: this should probably throw an exception
	}
	OctetString CertificateOctets;
	CertificateOctets.len = CertificateBytes->length();
	CertificateOctets.octets = (unsigned char*) CertificateBytes->data();
	pDigitalSignature->set_Certificate_octets( &CertificateOctets );

    delete[] CertificateVal;

    // DigestValue - Required
    char* DigestValueVal = xdoc.getString("SignedInfo.Reference.DigestValue");
    if (DigestValueVal == NULL)
    {
        gLogger->logError("SignedInfo.Reference.DigestValue value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDigitalSignature->set_DigestValue_base64(DigestValueVal);

	// base 64 decode the DigestValue AYMAN
	ByteArray* DigestValueBytes = RFC1521Base64::decode(DigestValueVal);
	if (!DigestValueBytes ) {
		gLogger->logError("Failed attempt to Base 64 decode DigestValue");
        return(NULL);	// TODO: this should probably throw an exception
	}
	OctetString DigestValueOctets;
	DigestValueOctets.len = DigestValueBytes->length();
	DigestValueOctets.octets = (unsigned char*) DigestValueBytes->data();
	pDigitalSignature->set_DigestValue_octets( &DigestValueOctets );

    delete[] DigestValueVal;

    // set XML string on DigitalSignature, free memory
    pDigitalSignature->set_XML_str ( (char*) xml_stream);
	    
    // return newly created DigitalSignature
    return(pDigitalSignature);
 }
