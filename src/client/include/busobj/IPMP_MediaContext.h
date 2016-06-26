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
#ifndef IPMP_MediaContext_h
#define IPMP_MediaContext_h 1

#include "busobj/IPMP_MetaData.h"
#include "busobj/IPMP_ContentIdentity.h"
#include "crypto/CipherContext.h"

//#ifndef __OPENIPMPSINGLETHREADED
// #include "SDL.h"
//#endif

class IPMP_MediaContext
{

  public:
      // Constructors
      IPMP_MediaContext();
      IPMP_MediaContext(IPMP_ContentIdentity* pIPMP_ContentId, CipherContext* pCipherCtx);

      // Copy Constructor
      IPMP_MediaContext(IPMP_MediaContext* right);

      // Destructor
      ~IPMP_MediaContext();

      // Get and Set Operations for Class Attributes

      // IPMP_ContentIdentity
      const IPMP_ContentIdentity* get_IPMP_ContentIdentity () const;
      void set_IPMP_ContentIdentity (IPMP_ContentIdentity* value);

      // CipherContext
      const CipherContext* get_CipherContext () const;
      void set_CipherContext (CipherContext* value);

      // encrypt
      bool ProtectMediaSample(unsigned char* buffer, int length);
      bool ProtectMediaSample(unsigned char* in_buffer, int in_length, unsigned char* out_buffer, int out_length);

      // decrypt
      bool UnlockMediaSample(unsigned char* buffer, int length);
      bool UnlockMediaSample(unsigned char* in_buffer, int in_length, unsigned char* out_buffer, int out_length);

      // protected flag
      const bool get_ProtectedFlag () const;
      void set_ProtectedFlag (bool value);

//#ifndef __OPENIPMPSINGLETHREADED
//	  static SDL_mutex* m_DecryptMutex;
//#endif

	  static bool createMutex();

  private:
  
      // Data Members for Class Attributes
      IPMP_ContentIdentity*	m_IPMP_ContentIdentity;
      CipherContext*		m_CipherCtx;

};

#endif
