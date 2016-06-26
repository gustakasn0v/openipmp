/**	\file OpenIPMPDRMDecManager.h

	OpenIPMP DRM manager used in decoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPDRMDECMANAGER_H)
#define OPENIPMPDRMDECMANAGER_H

#include "IOpenIPMPDRMDecryptor.h"
#include "IOpenIPMPDRMDecManager.h"
#include "OpenIPMPKeyManager.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OpenIPMP DRM manager used in decoding process.

    Creates OpenIPMP DRM decryptors. Uses existing openIPMP infrastructure.
*/
class OpenIPMPDRMDecManager: public IOpenIPMPDRMDecManager {
public:
  /*! \brief  Constructor.

      See OpenIPMPKeyManager::OpenIPMPKeyManager for correct format
      of XML document.

      \param    xmlDoc          input, XML document.
      \param    logger          input-output, message logger.

      If fails, throws DRMDecManagerException and logger's log contains
      error message.
  */
  OpenIPMPDRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger);

  virtual ~OpenIPMPDRMDecManager();

  /*! \brief  Create openIPMP DRM decryptor.

      Use information contained in openIPMP DRM information.

      See OpenIPMPKeyManager::CreateAES128CTRDec and
      OpenIPMPKeyManager::CreateBlowfishDec for correct format of the XML
      document.

      \param  info          input, openIPMP DRM information.
      \param  xml           input, XML document.

      \returns  If succeeds, OpenIPMP DRM decryptor pointer. If fails, zero pointer.
  */
  virtual IOpenIPMPDRMDecryptor* CreateDecryptor(const OpenIPMPDRMInfo& info,
    IXMLElement* xml);

private:
  OpenIPMPKeyManager* manager;
  DRMLogger& managerLogger;
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPDRMDECMANAGER_H)
