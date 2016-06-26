/**	\file ISMADRMDecManagerFactory.h

	ISMA DRM decoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ISMADRMDECMANAGERFACTORY_H)
#define ISMADRMDECMANAGERFACTORY_H

#include "IISMADRMDecManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined ISMADRMDECMANAGERFACTORY_EXPORTS
#define ISMADRMDECMANAGERFACTORY_EXPORT __declspec(dllexport)
#else
#define ISMADRMDECMANAGERFACTORY_EXPORT __declspec(dllimport)
#endif // ISMADRMDECMANAGERFACTORY_EXPORTS
#elif defined (LINUX)
#define ISMADRMDECMANAGERFACTORY_EXPORT
#else
#define ISMADRMDECMANAGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  ISMA DRM decoding manager creator.
*/
class ISMADRMDecManagerFactory {
public:
  /*! \brief  Create new ISMA DRM decoding manager.

      See OpenIPMPISMADRMDecManager::OpenIPMPISMADRMDecManager for
      correct format of XML document.

      \param  xml         input, XML document.
      \param  logger      input, message logger.

      \returns  New ISMA DRM decoding manager. If fails, 0.
  */
  static ISMADRMDECMANAGERFACTORY_EXPORT IISMADRMDecManager* GetISMADRMDecManager(
    IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (ISMADRMDECMANAGERFACTORY_H)
