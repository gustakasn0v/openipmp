/**	\file IOMADRMEncManager.h

	OMA DRM manager used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOMADRMENCMANAGER_H)
#define IOMADRMENCMANAGER_H

#include "IDRMEncManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM manager used in encoding process.

    Creates and stores keys (cipher encryptors), adds licenses for protected
    content, handles OMA DRM messages.
*/
class IOMADRMEncManager: public IDRMEncManager {
public:
  virtual ~IOMADRMEncManager() {
  }
};

} // namespace DRMPlugin

#endif // !defined (IOMADRMENCMANAGER_H)
