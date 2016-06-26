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
#ifndef IPMP_ContentIdentity_h
#define IPMP_ContentIdentity_h 1

#include "busobj/ContentIdentity.h"
#include "busobj/DigitalSignature.h"
#include "crypto/HashContext.h"
#include "busobj/DOI.h"

// forward declaration to avoid circular reference
#include "busobj/IPMP_MetaData.h"
class IPMP_MetaData;

class IPMP_ContentIdentity : public ContentIdentity
{

  public:
      // Constructors
      IPMP_ContentIdentity();
      IPMP_ContentIdentity(IPMP_MetaData* pMetaData, DOI* pDOI, DigitalSignature* pDigitalSignature);
      IPMP_ContentIdentity(IPMP_MetaData* pMetaData, DOI* pDOI);
      IPMP_ContentIdentity(DOI* pDOI, DigitalSignature* pDigitalSignature);

      // Copy Constructor
      IPMP_ContentIdentity(IPMP_ContentIdentity* right);

      // Destructor
      ~IPMP_ContentIdentity();

      // Get and Set Operations for Class Attributes (implementation of virtual functions)

      // title
      const char* get_Title () const;
      void set_Title (char* value);

      // artist
      const char* get_Artist () const;
      void set_Artist (char* value);

      // rights host
      const char* get_RightsHost () const;
      void set_RightsHost (char* value);

      // protected flag
      const bool get_ProtectedFlag () const;
      void set_ProtectedFlag (bool value);

      // ResourceKey facade
      const char* get_ResourceKey () const;

      // Get and Set Operations for Class Attributes (subclass specific)

      const IPMP_MetaData* get_IPMP_MetaData () const;
      void set_IPMP_MetaData (IPMP_MetaData* value);

      const DOI* get_DOI () const;
      void set_DOI (DOI* value);

      // full IPMP_ContentId XML string
      const char* get_XML_str () const;
      void set_XML_str (char* value);

      // DOI xml string
      const char* get_DOI_XML_str () const;
      void set_DOI_XML_str (char* value);

      // DigitalSignature xml string
      const char* get_DigitalSignature_XML_str () const;
      void set_DigitalSignature_XML_str (char* value);

      // encode to xml
      const char* encode ();

      // decode DOI and DigitalSignature XML strings into their respective objects
      bool decode ();

  private:
  
      // Data Members for Class Attributes
      IPMP_MetaData*	m_IPMP_MetaData;
      DOI*		m_DOI;

      // xml strings
      char*	m_XML_str;
      char*	m_DOI_XML_str;
      char*	m_DigitalSignature_XML_str;

};

// Class IPMP_ContentIdentity 

#endif
