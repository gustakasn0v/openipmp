/**	\file IOpenIPMPDRMDecManager.h

	OpenIPMP DRM manager used in decoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOPENIPMPDRMDECMANAGER_H)
#define IOPENIPMPDRMDECMANAGER_H

#include "IOpenIPMPDRMDecryptor.h"
#include "IXMLDocument.h"
#include "OpenIPMPDRMInfo.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OpenIPMP DRM manager used in decoding process.

    Creates openIPMP DRM decryptors.
*/
class IOpenIPMPDRMDecManager {
public:
  virtual ~IOpenIPMPDRMDecManager() {
  }

  /*! \brief  Create openIPMP DRM decryptor.

      Use information contained in openIPMP DRM information.

      \param  info          input, openIPMP DRM information.
      \param  xml           input, XML document.

      \returns  If succeeds, openIPMP DRM decryptor pointer. If fails,
                zero pointer.
  */
  virtual IOpenIPMPDRMDecryptor* CreateDecryptor(const OpenIPMPDRMInfo& info,
    IXMLElement* xml) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IOPENIPMPDRMDECMANAGER_H)
