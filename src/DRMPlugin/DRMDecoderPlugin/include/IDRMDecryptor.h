/**	\file IDRMDecryptor.h

	Interfaces for DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IDRMDECRYPTOR_H)
#define IDRMDECRYPTOR_H

#include "BasicTypes.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Exception used for DRM decryptor error.
*/
class DRMDecryptorException {
};

/*! \brief Decrypts protected data.

    Protected data is decrypted according to specific DRM method.
*/
class IDRMDecryptor {
public:
  virtual ~IDRMDecryptor() {
  }

  /*! \brief  Decrypt protected data.
  
      Returns unprotected data in unsecure.

      \param    secure            input, data to be decrypted.
      \param    secureSize        input, size of secure data.
      \param    unsecure          output, unsecure data.
      \param    unsecureSize      output, size of unsecure data.

      \return Boolean indicating success or failure.
  */
  virtual bool Decrypt(ByteT* secure, UInt32T secureSize, ByteT** unsecure,
    UInt32T* unsecureSize) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IDRMDECRYPTOR_H)
