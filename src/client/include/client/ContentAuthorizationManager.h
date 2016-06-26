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
#ifndef ContentAuthorizationManager_h
#define ContentAuthorizationManager_h 1

#include "client/ClientManager.h"
#include "client/ContentRegistrationContext.h"
#include "busobj/IPMP_MediaContext.h"
#include "busobj/AuxData.h"
#include "busobj/DOI.h"
#include "busobj/IPMP_ContentIdentity.h"
#include "busobj/IPMP_MetaData.h"
#include "crypto/CipherContext.h"

// define cipher and hash algorithms and key sizes
#define	ALG_HASH		"SHA1"
#define	ALG_CIPHER		"BF-CFB"
#define	CIPHER_KEYSIZE	128

/** CJM 4/9/03  KMS ToolID */
#define OPENIPMP_TOOLID "440e5752-d874-499f-b7a5-3e8ddf4ebcaf"

// error messages
#define ERR_INVALID_LOGIN_TYPE	-1

class ContentAuthorizationManager : public ClientManager
{

  public: // methods
  
    // *** Constructor ***
      ContentAuthorizationManager();

    // *** Destructor ***
      ~ContentAuthorizationManager();

    // *** Accessor Methods ***

	  /** CJM 4/9/03  */
	  const char* getToolId() { return OPENIPMP_TOOLID; }

    // *** Implementation Methods ***
	
      // for media context retrieval (encoding - new mp4 file)
      IPMP_MediaContext* constructNewIPMP_MediaContext (ContentRegistrationContext* contentRegCtx);
	  
      // for media context retrieval (encoding - add track to existing mp4 file)
      IPMP_MediaContext* retrieveIPMP_MediaContext (ContentRegistrationContext* contentRegCtx, IPMP_MetaData* pMetaData);

      // for media context retrieval (playback)
      IPMP_MediaContext* retrieveIPMP_MediaContext (bool retcode, IPMP_MetaData* pMetaData, char* pIntent);

      // for unprotected media context retrieval
      IPMP_MediaContext* retrieveUnprotectedIPMP_MediaContext (/*** char* pIntent? ***/);

  private: // internal methods

      // content registration operations
      DOI* RegisterContentAssignIdentifier (ContentRegistrationContext* contentRegCtx, DOI* pSendDOI);
      DOI* RegisterContentExistingIdentifier (DOI* pSendDOI);
      DOI* RegisterDigitalItemInstance (ContentRegistrationContext* contentRegCtx, DOI* pSendDOI, CipherContext* pCipherCtx, AuxData* pAuxDataOut, DigitalSignature** pDigitalSignature, AuxData** ppAuxDataIn);
      CipherContext* GetContentKey (ContentRegistrationContext* contentRegCtx, char* pDOI_idStr /***, DigitalSignature** pDigitalSignature ***//***, AuxData** ppAuxDataIn***/);

      // retrieve license from server and store...
      bool retrieveRemoteLicense(char* p_Intent, char* p_ContentId);
	  
      // for media context retrieval (playback) with license from local store or server delivery
      IPMP_MediaContext* retrieveIPMP_MediaContext (IPMP_ContentIdentity* pContentId, char* pIntent);
      
      // create cipher context
	  CipherContext* createCipherContext (ContentRegistrationContext* contentRegCtx, unsigned char* pKeyBuffer, int keyBufferLength);
      CipherContext* createCipherContext (ContentRegistrationContext* contentRegCtx);

      bool VerifySignature (DOI* pDOI, DigitalSignature* pDigitalSignature);

};

// Class ContentAuthorizationManager 

#endif
