/**	\file IISMADRMDecManager.h

	ISMA DRM manager used in decoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IISMADRMDECMANAGER_H)
#define IISMADRMDECMANAGER_H

#include "IISMADRMDecryptor.h"
#include "IXMLDocument.h"
#include "ISMADRMInfo.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  ISMA DRM manager used in decoding process.

    Creates ISMA DRM decryptors.
*/
class IISMADRMDecManager {
public:
  virtual ~IISMADRMDecManager() {
  }

  /*! \brief  Create ISMA DRM decryptor.

      Use information contained in ISMA DRM information.

      \param  info          input, ISMA DRM information.
      \param  xml           input, XML document.

      \returns  If succeeds, ISMA DRM decryptor pointer. If fails, zero pointer.
  */
  virtual IISMADRMDecryptor* CreateDecryptor(const ISMADRMInfo& info,
    IXMLElement* xml) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IISMADRMDECMANAGER_H)
