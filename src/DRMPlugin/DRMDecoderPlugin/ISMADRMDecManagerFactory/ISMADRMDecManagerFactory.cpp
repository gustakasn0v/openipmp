/**	\file ISMADRMDecManagerFactory.cpp

	ISMA DRM decoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "ISMADRMDecManagerFactory.h"
#include "OpenIPMPISMADRMDecManager.h"
#include "DRMDecManagerException.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  ISMA DRM decoding manager creator.
*/
/*! \brief  Create new ISMA DRM decoding manager.

    See OpenIPMPISMADRMDecManager::OpenIPMPISMADRMDecManager for correct format
    of XML document.

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  New ISMA DRM decoding manager. If fails, 0.
*/
IISMADRMDecManager* ISMADRMDecManagerFactory::GetISMADRMDecManager(IXMLElement* xml, DRMLogger& logger) {
  try {
    return new OpenIPMPISMADRMDecManager(xml, logger);
  }
  catch (DRMDecManagerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ISMADRMDecManagerFactory::GetISMADRMDecManager: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
