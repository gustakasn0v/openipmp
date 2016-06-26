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
#ifndef DOI_Factory_h
#define DOI_Factory_h 1

#include "busobj/DOI.h"

class DOI_Factory
{

  public:

      // Constructor
      DOI_Factory();

      // Destructor
      ~DOI_Factory();

      // create instance functions
      
      // create DOI instance with hardcoded values
      static DOI* CreateInstance ();

      // create DOI instance with values initialized from parsed XML stream
      static DOI* CreateInstance (const char* xml_stream);

      // create DOI instance with values initialized from parsed XML file
      static DOI* CreateInstanceFromFile (const char* xml_filename);


  private:

};

// Class DOI_Factory

#endif
