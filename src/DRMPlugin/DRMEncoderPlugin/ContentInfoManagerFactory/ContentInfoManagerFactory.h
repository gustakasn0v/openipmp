/** \file ContentInfoManagerFactory.h

    Content information manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (CONTENTINFOMANAGERFACTORY_H)
#define CONTENTINFOMANAGERFACTORY_H

#include "ContentInfoManager.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined CONTENTINFOMANAGERFACTORY_EXPORTS
#define CONTENTINFOMANAGERFACTORY_EXPORT __declspec(dllexport)
#else
#define CONTENTINFOMANAGERFACTORY_EXPORT __declspec(dllimport)
#endif // CONTENTINFOMANAGERFACTORY_EXPORTS
#elif defined (LINUX)
#define CONTENTINFOMANAGERFACTORY_EXPORT
#else
#define CONTENTINFOMANAGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Content info managers indicators.
*/
enum InfoManagerIndicator {
  //! DOI content info management using openIPMP (OpenIPMPDOIContentInfoManager).
  OPENIPMPDOIINFOMANAGER    = 0,
};

/*! \brief  Content information manager creator.
*/
class ContentInfoManagerFactory {
public:
  /*! \brief  Create new content information manager .

      Flag implies necessary XML document format. See specific content info
      manager documentation for correct format of XML document.

      \param  flag            input, content info manager indicator.
      \param  xml             input, XML document.
      \param  logger          input-output, message logger.

      \returns  New content information manager . If fails, 0.
  */
  static CONTENTINFOMANAGERFACTORY_EXPORT ContentInfoManager* GetContentInfoManager(
    InfoManagerIndicator flag, IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (CONTENTINFOMANAGERFACTORY_H)
