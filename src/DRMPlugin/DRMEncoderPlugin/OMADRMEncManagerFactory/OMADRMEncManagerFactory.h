/**	\file OMADRMEncManagerFactory.h

	OMA DRM encoding manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OMADRMENCMANAGERFACTORY_H)
#define OMADRMENCMANAGERFACTORY_H

#include "IOMADRMEncManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined OMADRMENCMANAGERFACTORY_EXPORTS
#define OMADRMENCMANAGERFACTORY_EXPORT __declspec(dllexport)
#else
#define OMADRMENCMANAGERFACTORY_EXPORT __declspec(dllimport)
#endif // OMADRMENCMANAGERFACTORY_EXPORTS
#elif defined (LINUX)
#define OMADRMENCMANAGERFACTORY_EXPORT
#else
#define OMADRMENCMANAGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM encoding manager creator.
*/
class OMADRMEncManagerFactory {
public:
  /*! \brief  Create new OMA DRM encoding manager.

      See OMADRMEncManager::OMADRMEncManager for correct format of XML document.

      \param  xml         input, XML document.
      \param  logger      input, message logger.

      \returns  New OMA DRM encoding manager. If fails, 0.
  */
  static OMADRMENCMANAGERFACTORY_EXPORT IOMADRMEncManager* GetOMADRMEncManager(
    IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (OMADRMENCMANAGERFACTORY_H)
