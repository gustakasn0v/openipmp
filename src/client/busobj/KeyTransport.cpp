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
#include "busobj/KeyTransport.h"

#include <string>

using namespace std;

// Class KeyTransport

KeyTransport::KeyTransport()
{
	// initialize (construct) complex member variables
	MemMan::construct(&m_KeyAlgorithm);
	MemMan::construct(&m_TransportAlgorithm);
	MemMan::construct(&m_Certificate_base64);
	MemMan::construct(&m_Certificate_octets);
	MemMan::construct(&m_EncKeyValue_base64);
	MemMan::construct(&m_EncKeyValue_octets);
	MemMan::construct(&m_XML_str);
}

KeyTransport::KeyTransport(KeyTransport* right)
{
	// initialize (construct) complex member variables
	MemMan::construct(&m_KeyAlgorithm);
	MemMan::construct(&m_TransportAlgorithm);
	MemMan::construct(&m_Certificate_base64);
	MemMan::construct(&m_Certificate_octets);
	MemMan::construct(&m_EncKeyValue_base64);
	MemMan::construct(&m_EncKeyValue_octets);
	MemMan::construct(&m_XML_str);

	// copy complex member variables from input object
	MemMan::copy(&m_KeyAlgorithm, (char*) right->get_KeyAlgorithm());
	MemMan::copy(&m_TransportAlgorithm, (char*) right->get_TransportAlgorithm());
	MemMan::copy(&m_Certificate_base64, (char*) right->get_Certificate_base64());
	MemMan::copy(&m_Certificate_octets, (OctetString*) right->get_Certificate_octets());
	MemMan::copy(&m_EncKeyValue_base64, (char*) right->get_EncKeyValue_base64());
	MemMan::copy(&m_EncKeyValue_octets, (OctetString*) right->get_EncKeyValue_octets());
	MemMan::copy(&m_XML_str, (char*) right->get_XML_str());
}

KeyTransport::~KeyTransport()
{
	// free memory: (destruct) complex member variables
	MemMan::destruct(&m_KeyAlgorithm);
	MemMan::destruct(&m_TransportAlgorithm);
	MemMan::destruct(&m_Certificate_base64);
	MemMan::destruct(&m_Certificate_octets);
	MemMan::destruct(&m_EncKeyValue_base64);
	MemMan::destruct(&m_EncKeyValue_octets);
	MemMan::destruct(&m_XML_str);
}

// Get and Set Operations for Class Attributes

// algorithm identifier for the key
const char* KeyTransport::get_KeyAlgorithm () const
{ return m_KeyAlgorithm; }
void KeyTransport::set_KeyAlgorithm (char* value)
{ MemMan::copy(&m_KeyAlgorithm, value); }

// algorithm identifier for the transportation of the key
const char* KeyTransport::get_TransportAlgorithm () const
{ return m_TransportAlgorithm; }
void KeyTransport::set_TransportAlgorithm (char* value)
{ MemMan::copy(&m_TransportAlgorithm, value); }

// X509 certificate (base64 encoded string)
const char* KeyTransport::get_Certificate_base64 () const
{ return m_Certificate_base64; }
void KeyTransport::set_Certificate_base64 (char* value)
{ MemMan::copy(&m_Certificate_base64, value); }

// X509 certificate (binary data buffer)
const OctetString* KeyTransport::get_Certificate_octets () const
{ return m_Certificate_octets; }
void KeyTransport::set_Certificate_octets (OctetString* value)
{ MemMan::copy(&m_Certificate_octets, value); }

// encrypted key value (base64 encoded string)
const char* KeyTransport::get_EncKeyValue_base64 () const
{ return m_EncKeyValue_base64; }
void KeyTransport::set_EncKeyValue_base64 (char* value)
{ MemMan::copy(&m_EncKeyValue_base64, value); }

// encrypted key value (binary data buffer)
const OctetString* KeyTransport::get_EncKeyValue_octets () const
{ return m_EncKeyValue_octets; }
void KeyTransport::set_EncKeyValue_octets (OctetString* value)
{ MemMan::copy(&m_EncKeyValue_octets, value); }

// raw XML string
const char* KeyTransport::get_XML_str () const
{ return m_XML_str; }
void KeyTransport::set_XML_str (char* value)
{ MemMan::copy(&m_XML_str, value); }

// TODO: This should be replaced with proper XML Document creation and encoding
char* KeyTransport::encode()
{
	string result = "";

    // start building xml string
    result += "<KeyXml xmlns:enc=\"http://www.w3.org/2000/10/xmlenc\" xmlns:ds=\"http://www.w3.org/2000/09/xmldsig\">\n";

		// key info
		result += "\t<ds:KeyInfo>\n";

			result += "\t\t<enc:EncryptedKey>\n";

				// algorithm identifier for the key
				result += "\t\t\t<enc:EncryptionMethod Algorithm=\"";
				result += get_TransportAlgorithm();
				result += "\"/>\n";

				result += "\t\t\t<ds:KeyInfo>\n";

					result += "\t\t\t\t<ds:X509Data>\n";

						// certificate
						result += "\t\t\t\t\t<ds:X509Certificate>";
						result += get_Certificate_base64();
						result += "</ds:X509Certificate>\n";

					result += "\t\t\t\t</ds:X509Data>\n";

					result += "\t\t\t\t<enc:CipherData>\n";

						// cipher value (encrypted key value)
						result += "\t\t\t\t\t<enc:CipherValue>";
						result += get_EncKeyValue_base64();
						result += "</enc:CipherValue>\n";

					result += "\t\t\t\t</enc:CipherData>\n";

				result += "\t\t\t</ds:KeyInfo>\n";

			result += "\t\t</enc:EncryptedKey>\n";

		result += "\t</ds:KeyInfo>\n";

		// key aux data
		result += "\t<KeyAuxData>\n";

			// algorithm identifier for the key
			result += "\t\t<enc:EncryptionMethod Algorithm=\"";
			result += get_KeyAlgorithm();
			result += "\"/>\n";

		result += "\t</KeyAuxData>\n";

	result += "</KeyXml>\n";

	// allocate space on heap for string and return it
	return( strdup( (char*)result.c_str() ) );
}
