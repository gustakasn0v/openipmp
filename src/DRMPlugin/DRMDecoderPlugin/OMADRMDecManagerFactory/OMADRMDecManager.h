/** \file OMADRMDecManager.h

    Manager providing OMA DRM decryptors.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMDECMANAGER_H)
#define OMADRMDECMANAGER_H

#include "IOMADRMDecryptor.h"
#include "IOMADRMDecManager.h"
#include "IOMADRMDecCommHandler.h"
#include "OMADRMDecAgent.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Manager providing OMA DRM decryptors. Uses FileOMADRMDecAgent.
*/
class FileOMADRMDecManager: public IOMADRMDecManager  {
public:
  /*! \brief  Constructor.

      See FileOMADRMDecAgent::FileOMADRMDecAgent documentation
      for XML document format.

      \param  xmlDoc            XML document.
      \param  logger            message logger.

      If fails, throws DRMDecManagerException.
  */
  FileOMADRMDecManager(IXMLElement* xmlDoc, DRMLogger& logger);

  virtual ~FileOMADRMDecManager();

  /*! \brief  Create OMA DRM decryptor.

      Use information contained in OMA DRM information.

      \param  info          input, OMA DRM information.
      \param  xml           input, XML document.

      \returns  If succeeds, OMA DRM decryptor pointer. If fails, zero pointer.
  */
  virtual IOMADRMDecryptor* CreateDecryptor(const OMADRMInfo& info, IXMLElement* xml);

private:
  IOMADRMDecCommHandler* comm;
  DRMLogger& managerLogger;
  OMADRMDecAgent* agent;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMDECMANAGER_H)
