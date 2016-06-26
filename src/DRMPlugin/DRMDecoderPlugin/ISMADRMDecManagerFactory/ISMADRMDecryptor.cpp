/**	\file ISMADRMDecryptor.cpp

	ISMA DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "ISMADRMDecryptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to ISMA DRM method using AES128ICM
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
bool AES128ICMISMADRMDecryptor::Decrypt(ByteT* secure, UInt32T secureSize,
    ByteT** unsecure, UInt32T* unsecureSize) {
  if (drmInfo.GetSelectiveEnc() == true) {
    ByteT enc = *secure++;
    if ((enc & 0x7f) != 0) {
      //  Wrong data encoding.
      decLogger.UpdateLog("AES128ICMISMADRMDecryptor::Decrypt: wrong data encoding.");
      return false;
    }
    if ((enc & 0x80) == 0) {
      //  Unencrypted sample.
      if ((*unsecure = (ByteT*)malloc(secureSize - 1)) == 0) {
        //  Unable to allocate memory.
        decLogger.UpdateLog("AES128ICMISMADRMDecryptor::Decrypt: memory allocation error.");
        return false;
      }
      memcpy(*unsecure, secure, secureSize - 1);
      return true;
    }
  }
  //  Encrypted sample.
//  int header_length = contentInfo.GetKeyIndLen() + contentInfo.GetIVLen();
  int header_length = 0 + 16;

//  return decryptor->Decrypt(sampleBuffer + header_length, sampleSize -
//    header_length, sampleBuffer + contentInfo.GetKeyIndLen(), header_length -
//    contentInfo.GetKeyIndLen(), decSampleData, decSampleLen);
  return decryptor->Decrypt(secure + header_length, secureSize - header_length,
    secure + 0, header_length - 0, unsecure, unsecureSize);
}

} // namespace DRMPlugin
