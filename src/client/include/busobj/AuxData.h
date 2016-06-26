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
#ifndef AuxData_h
#define AuxData_h 1

class AuxData 
{

  public:

      // Constructor
      AuxData();

      // Constructor
      AuxData(AuxData* right);

      // Destructor
      ~AuxData();

      // Get and Set Operations for Class Attributes
  
      /** Protected Flag */   
      const bool get_ProtectedFlag () const;
      void set_ProtectedFlag (bool pValue);

      /** Tool Id */   
      const char* get_ToolId () const;
      void set_ToolId (char* pValue);

      /** RightsHost XML string */   
      const char* get_RightsHost_XML () const;
      void set_RightsHost_XML (char* pValue);

      /** RightsHost URL */   
      const char* get_RightsHost_URL () const;
      void set_RightsHost_URL (char* pValue);

      /** RightsHost Port */   
      const int get_RightsHost_Port () const;
      void set_RightsHost_Port (int value);

      // raw XML string
      const char* get_XML_str () const;
      void set_XML_str (char* value);

// TODO: This should be replaced with proper XML Document creation and encoding
      char* encode();

  protected:
  
  private:

      // Data Members for Class Attributes
      bool	m_ProtectedFlag;
      char*	m_ToolId;
      char*	m_RightsHost_XML;
      char*	m_RightsHost_URL;
      int	m_RightsHost_Port;

      // raw XML string
	  char* m_XML_str;

};

// Class AuxData 

#endif
