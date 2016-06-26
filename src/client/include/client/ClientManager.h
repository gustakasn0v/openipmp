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
#ifndef ClientManager_h
#define ClientManager_h 1

#include "io/network/SecurityManagerProxy.h"
#include "crypto/CryptoManager.h"
#include "busobj/UserContext.h"

// login types and states (successive state values must increment)
#define NO_LOGIN	0
#define LOCAL_LOGIN	1
#define REMOTE_LOGIN	2

class ClientManager 
{

  public: // methods
  
    // *** Constructor ***
      ClientManager();

    // *** Destructor ***
      virtual ~ClientManager();

    // *** Accessor Methods ***

      // ip address
      virtual const char* get_ip () const;
      virtual void set_ip (char* value);

      // port
      virtual const int get_port () const;
      virtual void set_port (int value);

	  // UserContext 
	  virtual void setUserContext(UserContext*);
	  virtual const UserContext* getUserContext();

  	  /** initialization... */
  	  virtual bool init();

	  /** P12 FilePath attribute */
	  virtual void setP12FilePath(char* p_Path);

  protected: // internal methods

      void login (int loginType);
      bool localLogin ();
      bool remoteLogin ();
	  bool remoteLogout();

      // SecurityManagerProxy
      const SecurityManagerProxy* get_SecurityManagerProxy () const;
      void set_SecurityManagerProxy (SecurityManagerProxy* value);

      // helper method for message request / response (including connect / login checks)
      osmsMessage* sendMessage (osmsMessage* msg);
 
      // CryptoManager
      const CryptoManager* get_CryptoManager () const;
      void set_CryptoManager (CryptoManager* value);

  protected: // member variables
  
      // Data Members for Class Attributes
      char*					m_ip;
      int 					m_port;
      SecurityManagerProxy*	m_SecurityManagerProxy;
      CryptoManager*		m_CryptoManager;
      UserContext*			m_UserContext;

      // For maintaining login state
      int			m_loginState;
      
};

// Class ClientManager 

#endif
