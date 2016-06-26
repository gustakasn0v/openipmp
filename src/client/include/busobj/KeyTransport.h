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
#ifndef KeyTransport_h
#define KeyTransport_h 1

#include "tools/MemMan.h"

class KeyTransport 
{

  public:
      // Constructor
      KeyTransport();

      // Copy Constructor
      KeyTransport(KeyTransport* right);

      // Destructor
      ~KeyTransport();

      // Get and Set Operations for Class Attributes

      // algorithm identifier for the key
      const char* get_KeyAlgorithm () const;
      void set_KeyAlgorithm (char* value);

      // algorithm identifier for the transportation of the key
      const char* get_TransportAlgorithm () const;
      void set_TransportAlgorithm (char* value);

      // X509 Certificate (base64 encoded string)
      const char* get_Certificate_base64 () const;
      void set_Certificate_base64 (char* value);

      // X509 Certificate (binary data buffer)
      const OctetString* get_Certificate_octets () const;
      void set_Certificate_octets (OctetString* value);

      // encrypted key value (base64 encoded string)
      const char* get_EncKeyValue_base64 () const;
      void set_EncKeyValue_base64 (char* value);

      // encrypted key value (binary data buffer)
      const OctetString* get_EncKeyValue_octets () const;
      void set_EncKeyValue_octets (OctetString* value);

      // raw XML string
      const char* get_XML_str () const;
      void set_XML_str (char* value);

      char* encode ();

  private:
  
      // Data Members for Class Attributes

	  // algorithm identifiers
      char* m_KeyAlgorithm;
      char* m_TransportAlgorithm;

	  // encrypting entity's certificate
      char* m_Certificate_base64;
      OctetString*  m_Certificate_octets;

	  // encrypted key value
      char* m_EncKeyValue_base64;
      OctetString* m_EncKeyValue_octets;

      // raw XML string
	  char* m_XML_str;

};

#endif
