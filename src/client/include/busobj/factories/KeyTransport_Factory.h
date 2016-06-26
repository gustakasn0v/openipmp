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
#ifndef KeyTransport_Factory_h
#define KeyTransport_Factory_h 1

#include "busobj/KeyTransport.h"

class KeyTransport_Factory
{

  public:

      // Constructor
      KeyTransport_Factory();

      // Destructor
      ~KeyTransport_Factory();

      // create instance functions
      
      // create KeyTransport instance with values initialized from parsed XML stream
      static KeyTransport* CreateInstance (const char* xml_stream);

      // create KeyTransport instance with values initialized from parsed XML file
      static KeyTransport* CreateInstanceFromFile (const char* xml_filename);


  private:

};

// Class KeyTransport_Factory

#endif
