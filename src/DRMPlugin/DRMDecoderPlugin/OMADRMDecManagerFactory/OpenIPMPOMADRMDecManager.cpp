/**	\file OpenIPMPOMADRMDecManager.cpp

	OMA DRM decoding manager using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OMADRMDecryptor.h"
#include "OpenIPMPOMADRMDecManager.h"
#include "DRMDecManagerException.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    See OpenIPMPKeyManager::OpenIPMPKeyManager for correct format
    of XML document.

    \param    xmlDoc          input, XML document.
    \param    logger          input-output, message logger.

    If fails, throws DRMDecManagerException and logger's log contains
    error message.
*/
OpenIPMPOMADRMDecManager::OpenIPMPOMADRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger):
  manager(new OpenIPMPKeyManager(xmlDoc, logger)), managerLogger(logger) {
}

OpenIPMPOMADRMDecManager::~OpenIPMPOMADRMDecManager() {
  if (manager != 0) delete manager; manager = 0;
}

/*! \brief  Create OMA DRM decryptor.

    Use information contained in OMA DRM information.

    See OpenIPMPKeyManager::CreateAES128CBCDec and
    OpenIPMPKeyManager::CreateAES128CTRDec for correct format of XML document.

    \param  info          input, OMA DRM information.
    \param  xml           input, XML document.

    \returns  If succeeds, OMA DRM decryptor pointer. If fails, zero pointer.
*/
IOMADRMDecryptor* OpenIPMPOMADRMDecManager::CreateDecryptor(const OMADRMInfo& info,
    IXMLElement* xml) {
  try {
    if (EncMethod(info.GetEncMethod()) == EncMethod(AES128CBC)) {
      return new AES128CBCOMADRMDecryptor(manager->CreateAES128CBCDec(
        info.GetContentID(), info.GetRightsIssuerURL(), xml), info, managerLogger);
    } else if (EncMethod(info.GetEncMethod()) == EncMethod(AES128CTR)) {
      return new AES128CTROMADRMDecryptor(manager->CreateAES128CTRDec(
        info.GetContentID(), info.GetRightsIssuerURL(), xml), info, managerLogger);
    } else {
      managerLogger.UpdateLog("OpenIPMPOMADRMDecManager::CreateDecryptor: wrong encryption method...");
      return 0;
    }
  }
  catch (DRMDecryptorException) {
    return 0;
  }
}

} // namespace DRMPlugin
