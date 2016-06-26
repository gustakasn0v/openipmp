/** \file OMADRMDecCommHandlerFactory.cpp

    OMA DRM decoding communication handler manager.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMDecCommHandlerFactory.h"
#include "OMADRMMQDecCommHandler.h"
#include "OMADRMWSDecCommHandler.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM decoding communication handler manager.
*/
/*! \brief  Create new OMA DRM decoding communication handler.

    \param  logger      input, message logger.

    \returns  New OMA DRM decoding communication handler. If fails, 0.
*/
IOMADRMDecCommHandler* OMADRMDecCommHandlerFactory::GetDecCommHandler(DRMLogger& logger) {
  try {
//    return new OMADRMMQDecCommHandler(logger);
    return new OMADRMWSDecCommHandler(logger);
  }
  catch (OMADRMCommException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("OMADRMDecCommHandlerFactory::GetDecCommHandler: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
