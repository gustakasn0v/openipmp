/**	\file IOMADRMDecManager.h

	OMA DRM manager used in decoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOMADRMDECMANAGER_H)
#define IOMADRMDECMANAGER_H

#include "IOMADRMDecryptor.h"
#include "IXMLDocument.h"
#include "OMADRMInfo.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM manager used in decoding process.

    Creates OMA DRM decryptors.
*/
class IOMADRMDecManager {
public:
  virtual ~IOMADRMDecManager() {
  }

  /*! \brief  Create OMA DRM decryptor.

      Use information contained in OMA DRM information.

      \param  info          input, OMA DRM information.
      \param  xml           input, XML document.

      \returns  If succeeds, OMA DRM decryptor pointer. If fails, zero pointer.
  */
  virtual IOMADRMDecryptor* CreateDecryptor(const OMADRMInfo& info,
    IXMLElement* xml) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IOMADRMDECMANAGER_H)
