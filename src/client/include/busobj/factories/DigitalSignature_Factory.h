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
#ifndef DigitalSignature_Factory_h
#define DigitalSignature_Factory_h 1

#include "busobj/DigitalSignature.h"

class DigitalSignature_Factory
{

  public:

      // Constructor
      DigitalSignature_Factory();

      // Destructor
      ~DigitalSignature_Factory();

      // create instance functions
      
      // create DigitalSignature instance with values initialized from parsed XML stream
      static DigitalSignature* CreateInstance (const char* xml_stream);

      // create DigitalSignature instance with values initialized from parsed XML file
      static DigitalSignature* CreateInstanceFromFile (const char* xml_filename);


  private:

};

// Class DigitalSignature_Factory

#endif
