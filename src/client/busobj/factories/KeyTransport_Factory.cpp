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

#include "busobj/factories/KeyTransport_Factory.h"
#include "squashxml/xml/XMLDocument.h"
#include "squashxml/tools/FileLogger.h"
#include "squashxml/tools/ByteArray.h"
#include "squashxml/tools/RFC1521Base64.h"

KeyTransport_Factory::KeyTransport_Factory()
{
}

KeyTransport_Factory::~KeyTransport_Factory()
{
}

// create KeyTransport instance with hardcoded values
KeyTransport* KeyTransport_Factory::CreateInstanceFromFile (const char* xml_filename)
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

    // instantiate new KeyTransport
    KeyTransport* pKeyTransport = NULL;
	pKeyTransport = CreateInstance(xmlText);

	// free xml memory buffer
    free(xmlText);

	return(pKeyTransport);
}

// create KeyTransport instance with values initialized from parsed XML stream
KeyTransport* KeyTransport_Factory::CreateInstance (const char* xml_stream)
{

	// make sure xml_stream is populated
	if (!xml_stream) {
        gLogger->logError("Aborting attempt to parse NULL xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
	}

    // instantiate new KeyTransport
    KeyTransport* pKeyTransport = new KeyTransport();

	// instantiate XMLDocument
	XMLDocument xdoc;

    // decode xml text buffer into an XMLDocument
    if ( !xdoc.decode(xml_stream, "KeyXml") ) {
        gLogger->logError("Failed attempt parse xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
    }

    // TransportAlgorithm - Required
    char* TransportAlgorithmVal = xdoc.getAttributeValue("ds:KeyInfo.enc:EncryptedKey.enc:EncryptionMethod", "Algorithm");
    if (TransportAlgorithmVal == NULL)
    {
        gLogger->logError("ds:KeyInfo.enc:EncryptedKey.enc:EncryptionMethod value missing or it didn't have an Algorithm attribute!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pKeyTransport->set_TransportAlgorithm(TransportAlgorithmVal);

	delete[] TransportAlgorithmVal;

    // KeyAlgorithm - Required
    char* KeyAlgorithmVal = xdoc.getAttributeValue("KeyAuxData.enc:EncryptionMethod", "Algorithm");
    if (KeyAlgorithmVal == NULL)
    {
        gLogger->logError("KeyAuxData.enc:EncryptionMethod value missing or it didn't have an Algorithm attribute!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pKeyTransport->set_TransportAlgorithm(KeyAlgorithmVal);

	delete[] KeyAlgorithmVal;

    // Certificate - Required
    char* CertificateVal = xdoc.getString("ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.ds:X509Data.ds:X509Certificate");
    if (CertificateVal == NULL)
    {
        gLogger->logError("ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.ds:X509Data.ds:X509Certificate value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pKeyTransport->set_Certificate_base64(CertificateVal);

	// base 64 decode the Certificate
	ByteArray* CertificateBytes = RFC1521Base64::decode(CertificateVal);
	if (!CertificateBytes ) {
		gLogger->logError("Failed attempt to Base 64 decode Certificate");
        return(NULL);	// TODO: this should probably throw an exception
	}
	OctetString CertificateOctets;
	CertificateOctets.len = CertificateBytes->length();
	CertificateOctets.octets = (unsigned char*) CertificateBytes->data();
	pKeyTransport->set_Certificate_octets( &CertificateOctets );

    delete[] CertificateVal;

    // encrypted key - Required
    char* EncKeyValueVal = xdoc.getString("ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.enc:CipherData.enc:CipherValue");
    if (EncKeyValueVal == NULL)
    {
        gLogger->logError("ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.enc:CipherData.enc:CipherValue value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pKeyTransport->set_EncKeyValue_base64(EncKeyValueVal);

	// base 64 decode the encrypted key
	ByteArray* EncKeyValueBytes = RFC1521Base64::decode(EncKeyValueVal);
	if (!EncKeyValueBytes ) {
		gLogger->logError("Failed attempt to Base 64 decode EncKeyValue");
        return(NULL);	// TODO: this should probably throw an exception
	}
	OctetString EncKeyValueOctets;
	EncKeyValueOctets.len = EncKeyValueBytes->length();
	EncKeyValueOctets.octets = (unsigned char*) EncKeyValueBytes->data();
	pKeyTransport->set_EncKeyValue_octets( &EncKeyValueOctets );

    delete[] EncKeyValueVal;

    // set XML string on KeyTransport, free memory
    pKeyTransport->set_XML_str ( (char*) xml_stream);
	    
    // return newly created KeyTransport
    return(pKeyTransport);
 }
