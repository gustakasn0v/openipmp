/**	\file OMADRMDecryptor.cpp

	OMA DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OMADRMDecryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OMA DRM method using AES128CBC
    decryption.
*/
/*! \brief  Decrypt protected data.

    Returns unprotected data in unsecure.

    \param    secure            input, data to be decrypted.
    \param    secureSize        input, size of secure data.
    \param    unsecure          output, unsecure data.
    \param    unsecureSize      output, size of unsecure data.

    \return Boolean indicating success or failure.
*/
bool AES128CBCOMADRMDecryptor::Decrypt(ByteT* secure, UInt32T secureSize,
    ByteT** unsecure, UInt32T* unsecureSize) {
  //  Sanity check.
  if (secureSize < 3) {
    decLogger.UpdateLog("AES128CBCOMADRMDecryptor::Decrypt: invalid input size.");
    return false;
  }
  //  Read AU header.
  //  Selective encryption indicator.
  ByteT selective = *secure++;
  //  Counter length.
  ByteT ctrLen = *secure++;
  //  IV length.
  ByteT ivLen = *secure++;
  if (((selective & 0x7f) != 0) || (ctrLen != 0)) {
    decLogger.UpdateLog("AES128CBCOMADRMDecryptor::Decrypt: invalid input data.");
    return false;
  }
  if (selective == 0) {
    if ((*unsecure = (ByteT*)malloc(secureSize - 3)) == 0) {
      decLogger.UpdateLog("AES128CBCOMADRMDecryptor::Decrypt: memory allocation error.");
      return false;
    }
    memcpy(*unsecure, secure, secureSize - 3);
    *unsecureSize = secureSize - 3;
    return true;
  }
  //  Sanity check.
  if (secureSize < (unsigned int)(ivLen + 3)) {
    decLogger.UpdateLog("AES128CBCOMADRMDecryptor::Decrypt: invalid input size.");
    return false;
  }

  return decryptor->Decrypt(secure + ivLen, secureSize - ivLen - 3, secure, ivLen,
    unsecure, unsecureSize);
}

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OMA DRM method using AES128CTR
    decryption.
*/
/*! \brief  Decrypt protected data.

    Returns unprotected data in unsecure.

    \param    secure            input, data to be decrypted.
    \param    secureSize        input, size of secure data.
    \param    unsecure          output, unsecure data.
    \param    unsecureSize      output, size of unsecure data.

    \return Boolean indicating success or failure.
*/
bool AES128CTROMADRMDecryptor::Decrypt(ByteT* secure, UInt32T secureSize,
    ByteT** unsecure, UInt32T* unsecureSize) {
  //  Sanity check.
  if (secureSize < 3) {
    decLogger.UpdateLog("AES128CTROMADRMDecryptor::Decrypt: invalid input size.");
    return false;
  }
  //  Read AU header.
  //  Selective encryption indicator.
  ByteT selective = *secure++;
  //  Counter length.
  ByteT ctrLen = *secure++;
  //  IV length.
  ByteT ivLen = *secure++;
  if (((selective & 0x7f) != 0) || (ivLen != 0)) {
    decLogger.UpdateLog("AES128CTROMADRMDecryptor::Decrypt: invalid input data.");
    return false;
  }
  if (selective == 0) {
    if ((*unsecure = (ByteT*)malloc(secureSize - 3)) == 0) {
      decLogger.UpdateLog("AES128CTROMADRMDecryptor::Decrypt: memory allocation error.");
      return false;
    }
    memcpy(*unsecure, secure, secureSize - 3);
    *unsecureSize = secureSize - 3;
    return true;
  }
  //  Sanity check.
  if (secureSize < (unsigned int)(ctrLen + 3)) {
    decLogger.UpdateLog("AES128CTROMADRMDecryptor::Decrypt: invalid input size.");
    return false;
  }

  return decryptor->Decrypt(secure + ctrLen, secureSize - ctrLen - 3, secure, ctrLen,
    unsecure, unsecureSize);
}

} // namespace DRMPlugin
