/**	\file OMADRMDecManagerFactory.h

	OMA DRM decoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OMADRMDECMANAGERFACTORY_H)
#define OMADRMDECMANAGERFACTORY_H

#include "IOMADRMDecManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OMADRMDECMANAGERFACTORY_EXPORTS
#define OMADRMDECMANAGERFACTORY_EXPORT __declspec(dllexport)
#else
#define OMADRMDECMANAGERFACTORY_EXPORT __declspec(dllimport)
#endif // OMADRMDECMANAGERFACTORY_EXPORTS
#elif defined (LINUX)
#define OMADRMDECMANAGERFACTORY_EXPORT
#else
#define OMADRMDECMANAGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM decoding manager creator.
*/
class OMADRMDecManagerFactory {
public:
  /*! \brief  Create new OMA DRM decoding manager.

      See FileOMADRMDecManager::FileOMADRMDecManager for correct format of
      XML document.

      \param  xml         input, XML document.
      \param  logger      input, message logger.

      \returns  New OMA DRM decoding manager. If fails, 0.
  */
  static OMADRMDECMANAGERFACTORY_EXPORT IOMADRMDecManager* GetOMADRMDecManager(
    IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (OMADRMDECMANAGERFACTORY_H)
