/** \file OMADRMEncCommHandlerFactory.h

    OMA DRM encoding communication handler manager.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMENCCOMMHANDLERFACTORY_H)
#define OMADRMENCCOMMHANDLERFACTORY_H

#include "IOMADRMEncCommHandler.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OMADRMENCCOMMHANDLERFACTORY_EXPORTS
#define OMADRMENCCOMMHANDLERFACTORY_EXPORT __declspec(dllexport)
#else
#define OMADRMENCCOMMHANDLERFACTORY_EXPORT __declspec(dllimport)
#endif // OMADRMENCCOMMHANDLERFACTORY_EXPORTS
#elif defined (LINUX)
#define OMADRMENCCOMMHANDLERFACTORY_EXPORT
#else
#define OMADRMENCCOMMHANDLERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM encoding communication handler manager.
*/
class OMADRMEncCommHandlerFactory {
public:
  /*! \brief  Create new OMA DRM encoding communication handler.

      \param  logger      input, message logger.

      \returns  New OMA DRM encoding communication handler. If fails, 0.
  */
  static OMADRMENCCOMMHANDLERFACTORY_EXPORT IOMADRMEncCommHandler* GetEncCommHandler(DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (OMADRMENCCOMMHANDLERFACTORY_H)
