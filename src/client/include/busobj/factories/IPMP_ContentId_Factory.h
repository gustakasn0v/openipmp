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
#ifndef IPMP_ContentId_Factory_h
#define IPMP_ContentId_Factory_h 1

#include "busobj/IPMP_ContentIdentity.h"

class IPMP_ContentId_Factory
{

  public:

      // Constructor
      IPMP_ContentId_Factory();

      // Destructor
      ~IPMP_ContentId_Factory();

      // create instance functions
      
      // create IPMP_ContentId instance with values initialized from parsed XML stream
      static IPMP_ContentIdentity* CreateInstance (const char* xml_stream);

      // create IPMP_ContentId instance with values initialized from parsed XML file
      static IPMP_ContentIdentity* CreateInstanceFromFile (const char* xml_filename);

  private:

};

// Class IPMP_ContentId_Factory

#endif
