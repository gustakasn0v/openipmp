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

#ifndef ContentRegistrationContext_h
#define ContentRegistrationContext_h 1

class ContentRegistrationContext 
{

  public:     // constructors, destructors, assignment, etc.
  
      // Constructor
      ContentRegistrationContext();

      // Copy Constructor
      ContentRegistrationContext(ContentRegistrationContext* right);

      // Destructor
      ~ContentRegistrationContext();

  public:    // attribute accessor methods

      // username
      const char* get_username () const;
      void set_username (char* value);

      // password
      const char* get_password () const;
      void set_password (char* value);

      // ip address
      const char* get_ip () const;
      void set_ip (char* value);

      // port
      const int get_port () const;
      void set_port (int value);

      // xml meta file
      const char* get_xmlmetafile () const;
      void set_xmlmetafile (char* value);

      // use digital signature file
      const char* get_usedsigfile () const;
      void set_usedsigfile (char* value);

      // use key data file
      const char* get_usekeyfile () const;
      void set_usekeyfile (char* value);

      // write key data file
      const char* get_writekeyfile () const;
      void set_writekeyfile (char* value);

      // write master DOI file
      const char* get_writemasterDOIfile () const;
      void set_writemasterDOIfile (char* value);

      // write instance DOI file
      const char* get_writeinstanceDOIfile () const;
      void set_writeinstanceDOIfile (char* value);

      // write digital signature file
      const char* get_writedsigfile () const;
      void set_writedsigfile (char* value);

      // secure flag
      const bool get_secure () const;
      void set_secure (bool value);

  private:    // Data Members for Class Attributes
   
      char*				m_username;
      char*				m_password;
      char*				m_ip;
      int 				m_port;
      char*				m_xmlmetafile;
      char*				m_usedsigfile;
      char*				m_usekeyfile;
      char*				m_writekeyfile;
      char*				m_writemasterDOIfile;
      char*				m_writeinstanceDOIfile;
      char*				m_writedsigfile;
      bool				m_secure;
//      ContentAuthorizationManager*	m_contentAuthMgr;

};

#endif
