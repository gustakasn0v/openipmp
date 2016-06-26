/**	\file IOpenIPMPDRMDecryptor.h

	Interfaces for openIPMP DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOPENIPMPDRMDECRYPTOR_H)
#define IOPENIPMPDRMDECRYPTOR_H

#include "BasicTypes.h"
#include "DRMLogger.h"
#include "IDRMDecryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to openIPMP DRM method.
*/
class IOpenIPMPDRMDecryptor: public IDRMDecryptor {
public:
  virtual ~IOpenIPMPDRMDecryptor() {
  }
};

} // namespace DRMPlugin

#endif // !defined (IOPENIPMPDRMDECRYPTOR_H)
