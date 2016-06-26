/**	\file OpenIPMPDRMDecManagerFactory.h

	OpenIPMP DRM decoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPDRMDECMANAGERFACTORY_H)
#define OPENIPMPDRMDECMANAGERFACTORY_H

#include "IOpenIPMPDRMDecManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OPENIPMPDRMDECMANAGERFACTORY_EXPORTS
#define OPENIPMPDRMDECMANAGERFACTORY_EXPORT __declspec(dllexport)
#else
#define OPENIPMPDRMDECMANAGERFACTORY_EXPORT __declspec(dllimport)
#endif // OPENIPMPDRMDECMANAGERFACTORY_EXPORTS
#elif defined (LINUX)
#define OPENIPMPDRMDECMANAGERFACTORY_EXPORT
#else
#define OPENIPMPDRMDECMANAGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OpenIPMP DRM decoding manager creator.
*/
class OpenIPMPDRMDecManagerFactory {
public:
  /*! \brief  Create new OpenIPMP DRM decoding manager.

      See OpenIPMPDRMDecManager::OpenIPMPDRMDecManager for correct format
      of XML document.

      \param  xml         input, XML document.
      \param  logger      input, message logger.

      \returns  New openIPMP DRM decoding manager. If fails, 0.
  */
  static OPENIPMPDRMDECMANAGERFACTORY_EXPORT IOpenIPMPDRMDecManager* GetOpenIPMPDRMDecManager(
    IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPDRMDECMANAGERFACTORY_H)
