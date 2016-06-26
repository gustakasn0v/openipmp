/** \file OMADRMEncCommHandlerFactory.cpp

    OMA DRM encoding communication handler manager.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMEncCommHandlerFactory.h"
#include "OMADRMMQEncCommHandler.h"
#include "OMADRMWSEncCommHandler.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM encoding communication handler manager.
*/
/*! \brief  Create new OMA DRM encoding communication handler.

    \param  logger      input, message logger.

    \returns  New OMA DRM encoding communication handler. If fails, 0.
*/
IOMADRMEncCommHandler* OMADRMEncCommHandlerFactory::GetEncCommHandler(DRMLogger& logger) {
  try {
//    return new OMADRMMQEncCommHandler(logger);
    return new OMADRMWSEncCommHandler(logger);
  }
  catch (OMADRMCommException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("OMADRMEncCommHandlerFactory::GetEncCommHandler: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
