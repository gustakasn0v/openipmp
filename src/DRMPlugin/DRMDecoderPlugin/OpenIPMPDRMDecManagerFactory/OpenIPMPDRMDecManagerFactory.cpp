/**	\file OpenIPMPDRMDecManagerFactory.cpp

	OpenIPMP DRM decoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPDRMDecManagerFactory.h"
#include "OpenIPMPDRMDecManager.h"
#include "DRMDecManagerException.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OpenIPMP DRM decoding manager creator.
*/
/*! \brief  Create new openIPMP DRM decoding manager.

    See OpenIPMPDRMDecManager::OpenIPMPDRMDecManager for correct format
    of XML document.

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  New openIPMP DRM decoding manager. If fails, 0.
*/
IOpenIPMPDRMDecManager* OpenIPMPDRMDecManagerFactory::GetOpenIPMPDRMDecManager(IXMLElement* xml, DRMLogger& logger) {
  try {
    return new OpenIPMPDRMDecManager(xml, logger);
  }
  catch (DRMDecManagerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("OpenIPMPDRMDecManagerFactory::GetOpenIPMPDRMDecManager: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
