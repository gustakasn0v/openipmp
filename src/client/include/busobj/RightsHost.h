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
#ifndef RightsHost_h
#define RightsHost_h 1

class RightsHost 
{

  public:

      // Constructor
      RightsHost();

      // Copy Constructor
      RightsHost(RightsHost* right);

      // Destructor
      ~RightsHost();

      // Get and Set Operations for Class Attributes
  
      /** RightsHost URL */   
      const char* get_URL () const;
      void set_URL (char* pValue);

      /** RightsHost Port */   
      const int get_Port () const;
      void set_Port (int value);

      // raw XML string
      const char* get_XML_str () const;
      void set_XML_str (char* value);

  protected:
  
  private:

      // Data Members for Class Attributes
      char*	m_URL;
      int	m_Port;

      // raw XML string
	  char* m_XML_str;

};

// Class RightsHost 

#endif
