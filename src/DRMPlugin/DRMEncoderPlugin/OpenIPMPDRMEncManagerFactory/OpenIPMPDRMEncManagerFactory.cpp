/**	\file OpenIPMPDRMEncManagerFactory.cpp

	OpenIPMP DRM encoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPDRMEncManagerFactory.h"
#include "OpenIPMPDRMEncManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Get new openIPMP DRM encoding manager.

    See OpenIPMPDRMEncManager::OpenIPMPDRMEncManager for correct format
    of XML document.

    \param  xml         input, XML document.
    \param  logger      input-output, message logger.

    \returns New openIPMP DRM encoding manager. If fails, 0.
*/
IOpenIPMPDRMEncManager* OpenIPMPDRMEncManagerFactory::GetOpenIPMPDRMEncManager(
    IXMLElement* xml, DRMLogger& logger) {
  try {
    return new OpenIPMPDRMEncManager(xml, logger);
  }
  catch (DRMEncManagerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("OpenIPMPDRMEncManagerFactory::GetOpenIPMPDRMEncManager: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
