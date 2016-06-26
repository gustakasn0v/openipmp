/** \file OMADRMDecManager.cpp

    Manager providing OMA DRM decryptors.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMDecManager.h"
#include "FileOMADRMDecAgent.h"
#include "DRMDecManagerException.h"
#include "CipherFactory.h"
#include "OMADRMDecryptor.h"
#include "OMADRMDecCommHandlerFactory.h"
#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!  \brief  Class used for handling globals.
*/
class OMADecGlobalHandler {
public:
  /*!  \brief  Constructor.

      If fails, throws DRMDecManagerException.
  */
  OMADecGlobalHandler(): aMutex(ThreadSyncFactory::GetGlobalMutex()), agent(0) {
    if (aMutex == 0) {
      throw DRMDecManagerException();
    }
  }

  /*!  \brief  Destructor.

      If fails, throws DRMDecManagerException.
  */
  ~OMADecGlobalHandler() {
    if (aMutex != 0) {
      if (aMutex->Lock() == false) {
        throw DRMDecManagerException();
      }
      if (agent != 0) delete agent; agent = 0;
      if (aMutex->Release() == false) {
        throw DRMDecManagerException();
      }
      delete aMutex; aMutex = 0;
    }
  }

  /*!  \brief  Get OMA DRM decoding agent.

      \param  xml         XML document.
      \param  logger      message logger.

      \returns  If successful, OMA DRM decoding agent. If failed, zero pointer.
  */
  OMADRMDecAgent* GetAgent(IXMLElement* xml, DRMLogger& logger) {
    if (aMutex != 0) {
      if (aMutex->Lock() == true) {
        if (agent == 0) {
          try {
            agent = new FileOMADRMDecAgent(xml, logger);
          }
          catch (DRMDecManagerException) {
            if (agent != 0) delete agent; agent = 0;
          }
        }
        if (aMutex->Release() == false) {
          if (agent != 0) delete agent; agent = 0;
        }
      }
    }
    if (agent == 0) logger.UpdateLog("OMADecGlobalHandler::GetAgent: cannot create agent...");
    return agent;
  }

private:
  IMutex* aMutex;
  OMADRMDecAgent* agent;
};

static OMADecGlobalHandler omaDecGlobalHandler;

/*! \brief  Manager providing OMA DRM decryptors. Uses FileOMADRMDecAgent.
*/
/*! \brief  Constructor.

    See FileOMADRMDecAgent::FileOMADRMDecAgent documentation
    for XML document format.

    \param  xmlDoc            XML document.
    \param  logger            message logger.

    If fails, throws DRMDecManagerException.
*/
FileOMADRMDecManager::FileOMADRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger): comm(OMADRMDecCommHandlerFactory::GetDecCommHandler(logger)), managerLogger(logger), agent(omaDecGlobalHandler.GetAgent(xmlDoc, logger)) {
  if (agent == 0) {
    if (comm != 0) delete comm; comm = 0;
    throw DRMDecManagerException();
  }
  if (comm == 0) {
    throw DRMDecManagerException();
  }
  if (comm->Run((IOMADRMDecAgent*)agent) == false) {
    if (comm != 0) delete comm; comm = 0;
    throw DRMDecManagerException();
  }
}

FileOMADRMDecManager::~FileOMADRMDecManager() {
  if (comm != 0) delete comm; comm = 0;
}

/*! \brief  Create OMA DRM decryptor.

    Use information contained in OMA DRM information.

    \param  info          input, OMA DRM information.
    \param  xml           input, XML document.

    \returns  If succeeds, OMA DRM decryptor pointer. If fails, zero pointer.
*/
IOMADRMDecryptor* FileOMADRMDecManager::CreateDecryptor(const OMADRMInfo& info,
    IXMLElement* xml) {
  std::string contentID = info.GetContentID();
  NZSPtr<URIValue> url = new URIValue(info.GetRightsIssuerURL());
  ByteT* key;
  UInt32T keySize;
  try {
    if (EncMethod(info.GetEncMethod()) == EncMethod(AES128CBC)) {
      if (agent->GetKey(comm, contentID, url, &key, &keySize) == false) {
        return 0;
      }
      return new AES128CBCOMADRMDecryptor(CipherFactory::GetAES128CBCDecryptor(key,
        keySize, managerLogger), info, managerLogger);
    } else if (EncMethod(info.GetEncMethod()) == EncMethod(AES128CTR)) {
      if (agent->GetKey(comm, contentID, url, &key, &keySize) == false) {
        return 0;
      }
      return new AES128CTROMADRMDecryptor(CipherFactory::GetAES128CTRDecryptor(key,
        keySize, managerLogger), info, managerLogger);
    } else {
      managerLogger.UpdateLog("FileOMADRMDecManager::CreateDecryptor: wrong encryption method...");
      return 0;
    }
  }
  catch (DRMDecryptorException) {
    return 0;
  }
}

} // namespace DRMPlugin
