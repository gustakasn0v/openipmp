/** \file OMADRMDecCommHandlerFactory.h

    OMA DRM decoding communication handler manager.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMDECCOMMHANDLERFACTORY_H)
#define OMADRMDECCOMMHANDLERFACTORY_H

#include "IOMADRMDecCommHandler.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OMADRMDECCOMMHANDLERFACTORY_EXPORTS
#define OMADRMDECCOMMHANDLERFACTORY_EXPORT __declspec(dllexport)
#else
#define OMADRMDECCOMMHANDLERFACTORY_EXPORT __declspec(dllimport)
#endif // OMADRMDECCOMMHANDLERFACTORY_EXPORTS
#elif defined (LINUX)
#define OMADRMDECCOMMHANDLERFACTORY_EXPORT
#else
#define OMADRMDECCOMMHANDLERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM decoding communication handler manager.
*/
class OMADRMDecCommHandlerFactory {
public:
  /*! \brief  Create new OMA DRM decoding communication handler.

      \param  logger      input, message logger.

      \returns  New OMA DRM decoding communication handler. If fails, 0.
  */
  static OMADRMDECCOMMHANDLERFACTORY_EXPORT IOMADRMDecCommHandler* GetDecCommHandler(DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (OMADRMDECCOMMHANDLERFACTORY_H)
