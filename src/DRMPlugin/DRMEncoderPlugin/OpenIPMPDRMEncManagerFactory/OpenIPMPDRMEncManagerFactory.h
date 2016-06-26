/**	\file OpenIPMPDRMEncManagerFactory.h

	OpenIPMP DRM encoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPDRMENCMANAGERFACTORY_H)
#define OPENIPMPDRMENCMANAGERFACTORY_H

#include "IOpenIPMPDRMEncManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OPENIPMPDRMENCMANAGERFACTORY_EXPORTS
#define OPENIPMPDRMENCMANAGERFACTORY_EXPORT __declspec(dllexport)
#else
#define OPENIPMPDRMENCMANAGERFACTORY_EXPORT __declspec(dllimport)
#endif // OPENIPMPDRMENCMANAGERFACTORY_EXPORTS
#elif defined (LINUX)
#define OPENIPMPDRMENCMANAGERFACTORY_EXPORT
#else
#define OPENIPMPDRMENCMANAGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OpenIPMP DRM encoding manager creator.
*/
class OpenIPMPDRMEncManagerFactory {
public:
  /*! \brief  Get new openIPMP DRM encoding manager.

      See OpenIPMPDRMEncManager::OpenIPMPDRMEncManager for correct format
      of XML document.

      \param  xml         input, XML document.
      \param  logger      input-output, message logger.

      \returns New openIPMP DRM encoding manager. If fails, 0.
  */
  static OPENIPMPDRMENCMANAGERFACTORY_EXPORT IOpenIPMPDRMEncManager*
    GetOpenIPMPDRMEncManager(IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPDRMENCMANAGERFACTORY_H)
