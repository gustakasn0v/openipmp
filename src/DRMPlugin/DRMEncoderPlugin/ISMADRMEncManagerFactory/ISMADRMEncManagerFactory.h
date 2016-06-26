/**	\file ISMADRMEncManagerFactory.h

	ISMA DRM encoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ISMADRMENCMANAGERFACTORY_H)
#define ISMADRMENCMANAGERFACTORY_H

#include "IISMADRMEncManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined ISMADRMENCMANAGERFACTORY_EXPORTS
#define ISMADRMENCMANAGERFACTORY_EXPORT __declspec(dllexport)
#else
#define ISMADRMENCMANAGERFACTORY_EXPORT __declspec(dllimport)
#endif // ISMADRMENCMANAGERFACTORY_EXPORTS
#elif defined (LINUX)
#define ISMADRMENCMANAGERFACTORY_EXPORT
#else
#define ISMADRMENCMANAGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  	ISMA DRM encoding manager creator.
*/
class ISMADRMEncManagerFactory {
public:
  /*! \brief  Get new ISMA DRM encoding manager.

      See OpenIPMPISMADRMEncManager::OpenIPMPISMADRMEncManager for correct
      format of XML document.

      \param  xml         input, XML document.
      \param  logger      input-output, message logger.

      \returns New ISMA DRM encoding manager. If fails, 0.
  */
  static ISMADRMENCMANAGERFACTORY_EXPORT IISMADRMEncManager* GetISMADRMEncManager(
    IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (ISMADRMENCMANAGERFACTORY_H)
