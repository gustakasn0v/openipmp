/**	\file IISMADRMDecryptor.h

	Interfaces for ISMA DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IISMADRMDECRYPTOR_H)
#define IISMADRMDECRYPTOR_H

#include "BasicTypes.h"
#include "DRMLogger.h"
#include "IDRMDecryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to ISMA DRM method.
*/
class IISMADRMDecryptor: public IDRMDecryptor {
public:
  virtual ~IISMADRMDecryptor() {
  }
};

} // namespace DRMPlugin

#endif // !defined (IISMADRMDECRYPTOR_H)
