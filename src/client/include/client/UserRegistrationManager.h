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

#ifndef UserRegistrationManager_h
#define UserRegistrationManager_h 1

#include "client/ClientManager.h"
#include "tools/MemMan.h"
#include "squashxml/tools/ByteArray.h"

#define ERROR_CREATING_USER			1
#define ERROR_REGISTERING_USER		2
#define ERROR_ACQUIRING_KEY_STORE	3
#define ERROR_UNKNOWN				4

class UserRegistrationManager : public ClientManager
{

  public:     // constructors, destructors, assignment, etc.
  
      // Constructor
      UserRegistrationManager();

      // Copy Constructor
      UserRegistrationManager(UserRegistrationManager* right);

      // Destructor
      ~UserRegistrationManager();

  public:    // attribute accessor methods

      // username
      const char* get_username () const;
      void set_username (char* value);

      // password
      const char* get_password () const;
      void set_password (char* value);

      // passwordConfirm
      const char* get_passwordConfirm () const;
      void set_passwordConfirm (char* value);

      // email address
      const char* get_emailaddr () const;
      void set_emailaddr (char* value);

  public:    // implementation functions

	  // login and acquire P12 file
	  int loginAndAcquireP12(ByteArray** p12fileBuf);

	  // register and acquire P12 file
	  int registerAndAcquireP12(ByteArray** p12fileBuf);

  private:    // Data Members for Class Attributes
   
      char*				m_username;
      char*				m_password;
      char*				m_passwordConfirm;
      char*				m_emailaddr;

};

#endif
