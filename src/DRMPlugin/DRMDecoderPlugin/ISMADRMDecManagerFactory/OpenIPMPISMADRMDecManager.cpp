/**	\file OpenIPMPISMADRMDecManager.cpp

	ISMA DRM decoding manager using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "ISMADRMDecryptor.h"
#include "OpenIPMPISMADRMDecManager.h"
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
OpenIPMPISMADRMDecManager::OpenIPMPISMADRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger):
  manager(new OpenIPMPKeyManager(xmlDoc, logger)), managerLogger(logger) {
}

OpenIPMPISMADRMDecManager::~OpenIPMPISMADRMDecManager() {
  if (manager != 0) delete manager; manager = 0;
}

/*! \brief  Create ISMA DRM decryptor.

    Use information contained in ISMA DRM information.

    See OpenIPMPKeyManager::CreateAES128ICMDec for correct format of XML document.

    \param  info          input, ISMA DRM information.
    \param  xml           input, XML document.

    \returns  If succeeds, ISMA DRM decryptor pointer. If fails, zero pointer.
*/
IISMADRMDecryptor* OpenIPMPISMADRMDecManager::CreateDecryptor(const ISMADRMInfo& info,
    IXMLElement* xml) {
  try {
    if (EncMethod(info.GetEncMethod()) == EncMethod(AES128ICM)) {
      return new AES128ICMISMADRMDecryptor(manager->CreateAES128ICMDec(
        info.GetContentID(), info.GetKmsUri(), xml), info, managerLogger);
    } else {
      managerLogger.UpdateLog("OpenIPMPISMADRMDecManager::CreateDecryptor: wrong encryption method...");
      return 0;
    }
  }
  catch (DRMDecryptorException) {
    return 0;
  }
}

} // namespace DRMPlugin
