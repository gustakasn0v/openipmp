/**	\file OpenIPMPOMADRMDecManager.h

	OMA DRM decoding manager using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPOMADRMDECMANAGER_H)
#define OPENIPMPOMADRMDECMANAGER_H

#include "IOMADRMDecryptor.h"
#include "IOMADRMDecManager.h"
#include "OpenIPMPKeyManager.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM decoding manager using openIPMP infrastructure.
*/
class OpenIPMPOMADRMDecManager: public IOMADRMDecManager {
public:
  /*! \brief  Constructor.

      See OpenIPMPKeyManager::OpenIPMPKeyManager for correct format
      of XML document.

      \param    xmlDoc          input, XML document.
      \param    logger          input-output, message logger.

      If fails, throws DRMDecManagerException and logger's log contains
      error message.
  */
  OpenIPMPOMADRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger);

  virtual ~OpenIPMPOMADRMDecManager();

  /*! \brief  Create OMA DRM decryptor.

      Use information contained in OMA DRM information.

      See OpenIPMPKeyManager::CreateAES128CBCDec and
      OpenIPMPKeyManager::CreateAES128CTRDec for correct format of XML document.

      \param  info          input, OMA DRM information.
      \param  xml           input, XML document.

      \returns  If succeeds, OMA DRM decryptor pointer. If fails, zero pointer.
  */
  virtual IOMADRMDecryptor* CreateDecryptor(const OMADRMInfo& info, IXMLElement* xml);

private:
  OpenIPMPKeyManager* manager;
  DRMLogger& managerLogger;
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPOMADRMDECMANAGER_H)
