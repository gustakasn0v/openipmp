/**	\file IOMADRMDecryptor.h

	Interfaces for OMA DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOMADRMDECRYPTOR_H)
#define IOMADRMDECRYPTOR_H

#include "BasicTypes.h"
#include "DRMLogger.h"
#include "IDRMDecryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OMA DRM method.
*/
class IOMADRMDecryptor: public IDRMDecryptor {
public:
  virtual ~IOMADRMDecryptor() {
  }
};

} // namespace DRMPlugin

#endif // !defined (IOMADRMDECRYPTOR_H)
