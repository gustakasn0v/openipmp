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
#ifndef DigitalSignature_h
#define DigitalSignature_h 1

#include "tools/MemMan.h"

class DigitalSignature 
{

  public:
      // Constructor
      DigitalSignature();

      // Copy Constructor
      DigitalSignature(DigitalSignature* right);

      // Destructor
      ~DigitalSignature();

      // Get and Set Operations for Class Attributes

      // signature value (base64 encoded string)
      const char* get_SignatureValue_base64 () const;
      void set_SignatureValue_base64 (char* value);

      // signature value (binary data buffer)
      const OctetString* get_SignatureValue_octets () const;
      void set_SignatureValue_octets (OctetString* value);

      // X509 Certificate (base64 encoded string)
      const char* get_Certificate_base64 () const;
      void set_Certificate_base64 (char* value);

      // X509 Certificate (binary data buffer)
      const OctetString* get_Certificate_octets () const;
      void set_Certificate_octets (OctetString* value);

      // Digest / Hash value (base64 encoded string)
      const char* get_DigestValue_base64 () const;
      void set_DigestValue_base64 (char* value);

      // Digest / Hash value (binary data buffer)
      const OctetString* get_DigestValue_octets () const;
      void set_DigestValue_octets (OctetString* value);

      // raw XML string
      const char* get_XML_str () const;
      void set_XML_str (char* value);

  private:
  
      // Data Members for Class Attributes

	  // signature value
      char* m_SignatureValue_base64;
      OctetString* m_SignatureValue_octets;

	  // signing entity's certificate
      char* m_Certificate_base64;
      OctetString*  m_Certificate_octets;

	  // signature value
      char* m_DigestValue_base64;
      OctetString* m_DigestValue_octets;

	// TODO: This should also include the following (from the <SignedInfo> element):
	  // char* m_CanonicalizationMethod;
	  // char* m_SignatureMethod;
	  // char* m_DigestMethod;

      // raw XML string
	  char* m_XML_str;

};

#endif
