/** \file ContentInfoManagerFactory.cpp

    Content information manager creator.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "ContentInfoManagerFactory.h"
#include "OpenIPMPDOIContentInfoManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Create new content information manager .

    Flag implies necessary XML document format. See specific content info
    manager documentation for correct format of XML document.

    \param  flag            input, content info manager indicator.
    \param  xml             input, XML document.
    \param  logger          input-output, message logger.

    \returns  New content information manager . If fails, 0.
*/
ContentInfoManager* ContentInfoManagerFactory::GetContentInfoManager(
    InfoManagerIndicator flag, IXMLElement* xml, DRMLogger& logger) {
  try {
    if (flag == OPENIPMPDOIINFOMANAGER) {
      return new OpenIPMPDOIContentInfoManager(xml, logger);
    } else {
      logger.UpdateLog("ContentInfoManagerFactory::GetContentInfoManager: unknown indicator...");
      return 0;
    }
  }
  catch (ContentInfoManagerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ContentInfoManagerFactory::GetContentInfoManager: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
