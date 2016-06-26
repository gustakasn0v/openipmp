/**	\file OMADRMDecManagerFactory.cpp

	OMA DRM decoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OMADRMDecManagerFactory.h"
#include "OMADRMDecManager.h"
#include "OMADRMDecCommHandlerFactory.h"
#include "DRMDecManagerException.h"

#include "OpenIPMPOMADRMDecManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Create new OMA DRM decoding manager.

    See FileOMADRMDecManager::FileOMADRMDecManager for correct format of
    XML document.

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  New OMA DRM decoding manager. If fails, 0.
*/
IOMADRMDecManager* OMADRMDecManagerFactory::GetOMADRMDecManager(IXMLElement* xml, DRMLogger& logger) {
  try {
//    return new OpenIPMPOMADRMDecManager(xml, logger);
    return new FileOMADRMDecManager(xml, logger);
  }
  catch (DRMDecManagerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("OMADRMDecManagerFactory::GetOMADRMDecManager: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
