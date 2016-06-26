/**	\file ISMADRMEncManagerFactory.cpp

	ISMA DRM encoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "ISMADRMEncManagerFactory.h"
#include "OpenIPMPISMADRMEncManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Get new ISMA DRM encoding manager.

    See OpenIPMPISMADRMEncManager::OpenIPMPISMADRMEncManager for correct
    format of XML document.

    \param  xml         input, XML document.
    \param  logger      input-output, message logger.

    \returns New ISMA DRM encoding manager. If fails, 0.
*/
IISMADRMEncManager* ISMADRMEncManagerFactory::GetISMADRMEncManager(IXMLElement* xml,
    DRMLogger& logger) {
  try {
    return new OpenIPMPISMADRMEncManager(xml, logger);
  }
  catch (DRMEncManagerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ISMADRMEncManagerFactory::GetISMADRMEncManager: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
