/**	\file OMADRMEncManagerFactory.cpp

	OMA DRM encoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OMADRMEncManagerFactory.h"
#include "OMADRMEncManager.h"
#include "OpenIPMPOMADRMEncManager.h"
#include "OMADRMEncAgent.h"
#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Create new OMA DRM encoding manager.

    See OMADRMEncManager::OMADRMEncManager for correct format of XML document.

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  New OMA DRM encoding manager. If fails, 0.
*/
IOMADRMEncManager* OMADRMEncManagerFactory::GetOMADRMEncManager(IXMLElement* xml,
    DRMLogger& logger) {
  try {
//      return new OpenIPMPOMADRMEncManager(xml, logger);
      return new OMADRMEncManager(xml, logger);
  }
  catch (DRMEncManagerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("OMADRMEncManagerFactory::GetOMADRMEncManager: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
