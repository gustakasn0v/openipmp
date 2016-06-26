/**	\file OMADRMEncManager.cpp

	OMA DRM manager used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OMADRMEncManager.h"
#include "OMADRMEncAgent.h"
#include "CipherFactory.h"
#include "Base64Factory.h"
#include "OMADRMEncCommHandlerFactory.h"
#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!  \brief  Class used for handling globals.
*/
class OMAEncGlobalHandler {
public:
  /*!  \brief  Constructor.

      If fails, throws DRMEncManagerException.
  */
  OMAEncGlobalHandler(): aMutex(ThreadSyncFactory::GetGlobalMutex()), agent(0) {
    if (aMutex == 0) {
      throw DRMEncManagerException();
    }
  }

  /*!  \brief  Destructor.

      If fails, throws DRMEncManagerException.
  */
  ~OMAEncGlobalHandler() {
    if (aMutex != 0) {
      if (aMutex->Lock() == false) {
        throw DRMEncManagerException();
      }
      if (agent != 0) delete agent; agent = 0;
      if (aMutex->Release() == false) {
        throw DRMEncManagerException();
      }
      delete aMutex; aMutex = 0;
    }
  }

  /*!  \brief  Get OMA DRM encoding agent.

      \param  xml         XML document.
      \param  logger      message logger.

      \returns  If successful, OMA DRM encoding agent. If failed, zero pointer.
  */
  OMADRMEncAgent* GetAgent(IXMLElement* xml, DRMLogger& logger) {
    if (aMutex != 0) {
      if (aMutex->Lock() == true) {
        if (agent == 0) {
          try {
            agent = new OMADRMEncAgent(xml, logger);
          }
          catch (DRMEncManagerException) {
            if (agent != 0) delete agent; agent = 0;
          }
        }
        if (aMutex->Release() == false) {
          if (agent != 0) delete agent; agent = 0;
        }
      }
    }
    if (agent == 0) logger.UpdateLog("OMAEncGlobalHandler::GetAgent: cannot create agent...");
    return agent;
  }

private:
  IMutex* aMutex;
  OMADRMEncAgent* agent;
};

static OMAEncGlobalHandler omaEncGlobalHandler;

/*! \brief  OMA DRM manager used in encoding process. Uses OMADRMEncAgent.

    Creates and stores keys (cipher encryptors), adds licenses for protected
    content. Uses OMA DRM encoding agent.
*/
/*! \brief  Constructor.

    See OMADRMEncAgent::OMADRMEncAgent for correct format of XML document.

    \param  xml         XML document.
    \param  logger      message logger.

    If fails, throws DRMEncManagerException.
*/
OMADRMEncManager::OMADRMEncManager(IXMLElement* xml, DRMLogger& logger): comm(OMADRMEncCommHandlerFactory::GetEncCommHandler(logger)), managerLogger(logger), agent(omaEncGlobalHandler.GetAgent(xml, logger)) {
  if (agent == 0) {
    if (comm != 0) delete comm; comm = 0;
    throw DRMEncManagerException();
  }
  if (comm == 0) {
    throw DRMEncManagerException();
  }
  if (comm->Run(agent) == false) {
    if (comm != 0) delete comm; comm = 0;
    throw DRMEncManagerException();
  }
}

OMADRMEncManager::~OMADRMEncManager() {
  if (comm != 0) delete comm; comm = 0;
}

/*! \brief  Create blowfish encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

    \param    contentID       string uniquely identifying the content.
    \param    xmlDoc          XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
BlowfishEncryptor* OMADRMEncManager::CreateBlowfishEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  Base64StringT b64;
  if (Base64Factory::Encode(ByteSeq((ByteT*)contentID.data(), contentID.size()), b64) == false) {
    managerLogger.UpdateLog("OMADRMEncManager::CreateBlowfishEnc: base64 error...");
    return 0;
  }
  contentID = b64.BString();

  ByteT* key;
  UInt32T keySize = 16;

  if (agent->CreateAndStoreKey(comm, contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  return CipherFactory::GetBlowfishEncryptor(key, keySize, managerLogger);
}

/*! \brief  Create AES128CBC encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

    \param    contentID       string uniquely identifying the content.
    \param    xmlDoc          XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128CBCEncryptor* OMADRMEncManager::CreateAES128CBCEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  Base64StringT b64;
  if (Base64Factory::Encode(ByteSeq((ByteT*)contentID.data(), contentID.size()), b64) == false) {
    managerLogger.UpdateLog("OMADRMEncManager::CreateAES128CBCEnc: base64 error...");
    return 0;
  }
  contentID = b64.BString();

  ByteT* key;
  UInt32T keySize = 16;

  if (agent->CreateAndStoreKey(comm, contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  ByteT* i;
  if (CipherFactory::RndGenerate(&i, keySize) == false) {
    if (key) free(key);
    managerLogger.UpdateLog("OMADRMEncManager::CreateAES128CBCEnc: random number generation error...");
    return 0;
  }

  return CipherFactory::GetAES128CBCEncryptor(key, keySize, i, managerLogger);
}

/*! \brief  Create AES128CTR encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

    \param    contentID       string uniquely identifying the content.
    \param    xmlDoc          XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128CTREncryptor* OMADRMEncManager::CreateAES128CTREnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  Base64StringT b64;
  if (Base64Factory::Encode(ByteSeq((ByteT*)contentID.data(), contentID.size()), b64) == false) {
    managerLogger.UpdateLog("OMADRMEncManager::CreateAES128CTREnc: base64 error...");
    return 0;
  }
  contentID = b64.BString();

  ByteT* key;
  UInt32T keySize = 16;

  if (agent->CreateAndStoreKey(comm, contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  ByteT* i;
  if (CipherFactory::RndGenerate(&i, keySize) == false) {
    if (key) free(key);
    managerLogger.UpdateLog("OMADRMEncManager::CreateAES128CTREnc: random number generation error...");
    return 0;
  }

  return CipherFactory::GetAES128CTREncryptor(key, keySize, i, managerLogger);
}

/*! \brief  Create AES128ICM encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

    \param    contentID       string uniquely identifying the content.
    \param    xmlDoc          XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128ICMEncryptor* OMADRMEncManager::CreateAES128ICMEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  Base64StringT b64;
  if (Base64Factory::Encode(ByteSeq((ByteT*)contentID.data(), contentID.size()), b64) == false) {
    managerLogger.UpdateLog("OMADRMEncManager::CreateAES128ICMEnc: base64 error...");
    return 0;
  }
  contentID = b64.BString();

  ByteT* key;
  UInt32T keySize = 16;

  if (agent->CreateAndStoreKey(comm, contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  ByteT* aes_overlay = (ByteT*)malloc(24);
  if (aes_overlay == 0) {
    if (key) free(key);
    managerLogger.UpdateLog("OMADRMEncManager::CreateAES128ICMEnc: memory allocation error...");
    return 0;
  }
  memcpy(aes_overlay, key, keySize);
  if (key) free(key);
  ByteT* tmp;
  if (CipherFactory::RndGenerate(&tmp, 8) == false) {
    if (aes_overlay) free(aes_overlay);
    managerLogger.UpdateLog("OMADRMEncManager::CreateAES128ICMEnc: random generate error...");
    return 0; 
  }
  memcpy(aes_overlay + keySize, tmp, 8);
  free(tmp);

  return CipherFactory::GetAES128ICMEncryptor(aes_overlay, 24, managerLogger);
}

/*! \brief  Add license for content.

    See OMADRMEncAgent::AddLicense for correct format of XML document.

    \param    contentID       string uniquely identifying the content.
    \param    xmlDoc          XML document.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMEncManager::AddLicense(std::string& contentID, IXMLElement* xmlDoc) {
  return agent->AddLicense(comm, contentID, xmlDoc);
}

} // namespace DRMPlugin
