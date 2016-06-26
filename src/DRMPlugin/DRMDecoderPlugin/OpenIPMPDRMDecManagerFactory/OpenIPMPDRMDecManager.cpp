/**	\file OpenIPMPDRMDecManager.cpp

	OpenIPMP DRM manager used in decoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPDRMDecryptor.h"
#include "OpenIPMPDRMDecManager.h"
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
OpenIPMPDRMDecManager::OpenIPMPDRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger):
  manager(new OpenIPMPKeyManager(xmlDoc, logger)), managerLogger(logger) {
}

OpenIPMPDRMDecManager::~OpenIPMPDRMDecManager() {
  if (manager != 0) delete manager; manager = 0;
}

/*! \brief  Create openIPMP DRM decryptor.

    Use information contained in openIPMP DRM information.

    See OpenIPMPKeyManager::CreateAES128CTRDec and
    OpenIPMPKeyManager::CreateBlowfishDec for correct format of the XML
    document.

    \param  info          input, openIPMP DRM information.
    \param  xml           input, XML document.

    \returns  If succeeds, OpenIPMP DRM decryptor pointer. If fails, zero pointer.
*/
IOpenIPMPDRMDecryptor* OpenIPMPDRMDecManager::CreateDecryptor(const OpenIPMPDRMInfo&
    info, IXMLElement* xml) {
  try {
    if (EncMethod(info.GetEncMethod()) == EncMethod(AES128CTR)) {
      return new AES128CTROpenIPMPDRMDecryptor(manager->CreateAES128CTRDec(
        info.GetContentID(), info.GetRightsHost(), xml), info, managerLogger);
    } else if (EncMethod(info.GetEncMethod()) == EncMethod(BLOWFISH)) {
      return new BlowfishOpenIPMPDRMDecryptor(manager->CreateBlowfishDec(
        info.GetContentID(), info.GetRightsHost(), xml), info, managerLogger);
    } else {
      managerLogger.UpdateLog("OpenIPMPDRMDecManager::CreateDecryptor: wrong encryption method...");
      return 0;
    }
  }
  catch (DRMDecryptorException) {
    return 0;
  }
}

} // namespace DRMPlugin
