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
#include "busobj/DigitalSignature.h"

// Class DigitalSignature 

DigitalSignature::DigitalSignature()
{
	// initialize (construct) complex member variables
	MemMan::construct(&m_SignatureValue_base64);
	MemMan::construct(&m_SignatureValue_octets);
	MemMan::construct(&m_Certificate_base64);
	MemMan::construct(&m_Certificate_octets);
	MemMan::construct(&m_DigestValue_base64);
	MemMan::construct(&m_DigestValue_octets);
	MemMan::construct(&m_XML_str);
}

DigitalSignature::DigitalSignature(DigitalSignature* right)
{
	// initialize (construct) complex member variables
	MemMan::construct(&m_SignatureValue_base64);
	MemMan::construct(&m_SignatureValue_octets);
	MemMan::construct(&m_Certificate_base64);
	MemMan::construct(&m_Certificate_octets);
	MemMan::construct(&m_DigestValue_base64);
	MemMan::construct(&m_DigestValue_octets);
	MemMan::construct(&m_XML_str);

	// copy complex member variables from input object
	MemMan::copy(&m_SignatureValue_base64, (char*) right->get_SignatureValue_base64());
	MemMan::copy(&m_SignatureValue_octets, (OctetString*) right->get_SignatureValue_octets());
	MemMan::copy(&m_Certificate_base64, (char*) right->get_Certificate_base64());
	MemMan::copy(&m_Certificate_octets, (OctetString*) right->get_Certificate_octets());
	MemMan::copy(&m_DigestValue_base64, (char*) right->get_DigestValue_base64());
	MemMan::copy(&m_DigestValue_octets, (OctetString*) right->get_DigestValue_octets());
	MemMan::copy(&m_XML_str, (char*) right->get_XML_str());
}

DigitalSignature::~DigitalSignature()
{
	// free memory: (destruct) complex member variables
	MemMan::destruct(&m_SignatureValue_base64);
	MemMan::destruct(&m_SignatureValue_octets);
	MemMan::destruct(&m_Certificate_base64);
	MemMan::destruct(&m_Certificate_octets);
	MemMan::destruct(&m_DigestValue_base64);
	MemMan::destruct(&m_DigestValue_octets);
	MemMan::destruct(&m_XML_str);
}

// Get and Set Operations for Class Attributes

// signature value (base64 encoded string)
const char* DigitalSignature::get_SignatureValue_base64 () const
{ return m_SignatureValue_base64; }
void DigitalSignature::set_SignatureValue_base64 (char* value)
{ MemMan::copy(&m_SignatureValue_base64, value); }

// signature value (binary data buffer)
const OctetString* DigitalSignature::get_SignatureValue_octets () const
{ return m_SignatureValue_octets; }
void DigitalSignature::set_SignatureValue_octets (OctetString* value)
{ MemMan::copy(&m_SignatureValue_octets, value); }

// X509 certificate (base64 encoded string)
const char* DigitalSignature::get_Certificate_base64 () const
{ return m_Certificate_base64; }
void DigitalSignature::set_Certificate_base64 (char* value)
{ MemMan::copy(&m_Certificate_base64, value); }

// X509 certificate (binary data buffer)
const OctetString* DigitalSignature::get_Certificate_octets () const
{ return m_Certificate_octets; }
void DigitalSignature::set_Certificate_octets (OctetString* value)
{ MemMan::copy(&m_Certificate_octets, value); }

// Digest / Hash value (base64 encoded string)
const char* DigitalSignature::get_DigestValue_base64 () const
{ return m_DigestValue_base64; }
void DigitalSignature::set_DigestValue_base64 (char* value)
{ MemMan::copy(&m_DigestValue_base64, value); }

// Digest / Hash value (binary data buffer)
const OctetString* DigitalSignature::get_DigestValue_octets () const
{ return m_DigestValue_octets; }
void DigitalSignature::set_DigestValue_octets (OctetString* value)
{ MemMan::copy(&m_DigestValue_octets, value); }

// raw XML string
const char* DigitalSignature::get_XML_str () const
{ return m_XML_str; }
void DigitalSignature::set_XML_str (char* value)
{ MemMan::copy(&m_XML_str, value); }
