/**	\file IOpenIPMPDRMEncManager.h

	OpenIPMP DRM manager used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOPENIPMPDRMENCMANAGER_H)
#define IOPENIPMPDRMENCMANAGER_H

#include "IDRMEncManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OpenIPMP DRM manager used in encoding process.

    Creates and stores keys (cipher encryptors), adds licenses for protected
    content.
*/
class IOpenIPMPDRMEncManager: public IDRMEncManager {
public:
  virtual ~IOpenIPMPDRMEncManager() {
  }
};

} // namespace DRMPlugin

#endif // !defined (IOPENIPMPDRMENCMANAGER_H)
