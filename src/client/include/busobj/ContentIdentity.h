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
#ifndef ContentIdentity_h
#define ContentIdentity_h 1

#include "busobj/DigitalSignature.h"
#include "crypto/HashContext.h"
#include "busobj/DOI.h"

class ContentIdentity 
{

  public:
      // Constructor
      ContentIdentity();

      // Copy Constructor
      ContentIdentity(const ContentIdentity &right);

      // Destructor
      virtual ~ContentIdentity() = 0;

      // Get and Set Operations for Class Attributes (pure virtual functions)

      // title
      virtual const char* get_Title () const = 0;
      virtual void set_Title (char* value) = 0;

      // artist
      virtual const char* get_Artist () const = 0;
      virtual void set_Artist (char* value) = 0;

      // rights host
      virtual const char* get_RightsHost () const = 0;
      virtual void set_RightsHost (char* value) = 0;

      // protected flag (facade?)
      virtual const bool get_ProtectedFlag () const = 0;
      virtual void set_ProtectedFlag (bool value) = 0;

      // Get and Set Operations for Class Attributes (regular implementations)

      // isSetup flag
      const bool isSetup ();

      // ResourceKey facade
      virtual const char* get_ResourceKey () const = 0;

      // digital signature
      const DigitalSignature* get_DigitalSignature () const;
      void set_DigitalSignature (DigitalSignature* value);

  protected:
  
      // Data Members for Class Attributes
      DigitalSignature*	m_DigitalSignature;
      bool		m_isSetupFlag;

};

// Class ContentIdentity 

#endif
