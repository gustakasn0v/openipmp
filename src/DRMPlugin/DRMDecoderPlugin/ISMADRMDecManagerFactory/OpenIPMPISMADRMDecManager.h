/**	\file OpenIPMPISMADRMDecManager.h

	ISMA DRM decoding manager using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPISMADRMDECMANAGER_H)
#define OPENIPMPISMADRMDECMANAGER_H

#include "IISMADRMDecryptor.h"
#include "IISMADRMDecManager.h"
#include "OpenIPMPKeyManager.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  ISMA DRM decoding manager using openIPMP infrastructure.
*/
class OpenIPMPISMADRMDecManager: public IISMADRMDecManager {
public:
  /*! \brief  Constructor.

      See OpenIPMPKeyManager::OpenIPMPKeyManager for correct format
      of XML document.

      \param    xmlDoc          input, XML document.
      \param    logger          input-output, message logger.

      If fails, throws DRMDecManagerException and logger's log contains
      error message.
  */
  OpenIPMPISMADRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger);

  virtual ~OpenIPMPISMADRMDecManager();

  /*! \brief  Create ISMA DRM decryptor.

      Use information contained in ISMA DRM information.

      See OpenIPMPKeyManager::CreateAES128ICMDec for correct format of XML document.

      \param  info          input, ISMA DRM information.
      \param  xml           input, XML document.

      \returns  If succeeds, ISMA DRM decryptor pointer. If fails, zero pointer.
  */
  virtual IISMADRMDecryptor* CreateDecryptor(const ISMADRMInfo& info,
    IXMLElement* xml);

private:
  OpenIPMPKeyManager* manager;
  DRMLogger& managerLogger;
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPISMADRMDECMANAGER_H)
