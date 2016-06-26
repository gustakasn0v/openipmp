/**	\file OpenIPMPDRMDecryptor.cpp

	OpenIPMP DRM decryptor plugin.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPDRMDecryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OpenIPMP DRM method using
    AES128CTR decryption.
*/
/*! \brief  Decrypt protected data.

    Returns unprotected data in unsecure.

    \param    secure            input, data to be decrypted.
    \param    secureSize        input, size of secure data.
    \param    unsecure          output, unsecure data.
    \param    unsecureSize      output, size of unsecure data.

    \return Boolean indicating success or failure.
*/
bool AES128CTROpenIPMPDRMDecryptor::Decrypt(ByteT* secure, UInt32T secureSize,
    ByteT** unsecure, UInt32T* unsecureSize) {
  //  Sanity check.
  if (secureSize < 1) {
    decLogger.UpdateLog("AES128CTROpenIPMPDRMDecryptor::Decrypt: invalid input size.");
    return false;
  }
  //  Read AU header.
  //  Counter length.
  ByteT ctrLen = *secure++;
  //  Sanity check.
  if (secureSize < (unsigned int)(ctrLen + 1)) {
    decLogger.UpdateLog("AES128CTROpenIPMPDRMDecryptor::Decrypt: invalid input size.");
    return false;
  }

  return decryptor->Decrypt(secure + ctrLen, secureSize - ctrLen - 1, secure, ctrLen,
    unsecure, unsecureSize);
}

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OpenIPMP DRM method using
    blowfish decryption.
*/
/*! \brief  Decrypt protected data.

    Returns unprotected data in unsecure.

    \param    secure            input, data to be decrypted.
    \param    secureSize        input, size of secure data.
    \param    unsecure          output, unsecure data.
    \param    unsecureSize      output, size of unsecure data.

    \return Boolean indicating success or failure.
*/
bool BlowfishOpenIPMPDRMDecryptor::Decrypt(ByteT* secure, UInt32T secureSize,
    ByteT** unsecure, UInt32T* unsecureSize) {
  return decryptor->Decrypt(secure, secureSize, unsecure, unsecureSize);
}

} // namespace DRMPlugin
