/**	\file ISMADRMDecryptor.h

	ISMA DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ISMADRMDECRYPTOR_H)
#define ISMADRMDECRYPTOR_H

#include "ICipher.h"
#include "IISMADRMDecryptor.h"
#include "ISMADRMInfo.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to ISMA DRM method using AES128ICM
    decryption.
*/
class AES128ICMISMADRMDecryptor: public IISMADRMDecryptor {
public:
  /*! \brief  Constructor.

      \param      dec             input, decryptor.
      \param      info            input, content encryption information.
      \param      logger          input-output, message logger.

      If constructor fails, it throws DRMDecryptorException.
  */
  AES128ICMISMADRMDecryptor(AES128ICMDecryptor* dec, const ISMADRMInfo& info,
      DRMLogger& logger): decryptor(dec), drmInfo(info), decLogger(logger) {
    if (decryptor == 0) {
      decLogger.UpdateLog("AES128ICMISMADRMDecryptor::ctor: zero decryptor.");
      throw DRMDecryptorException();
    }
    if ((drmInfo.GetKeyIndicatorLen() != 0) || (drmInfo.GetIVLen() != 16)) {
      if (decryptor != 0) delete decryptor; decryptor = 0;
      decLogger.UpdateLog("AES128ICMISMADRMDecryptor::ctor: error in content info.");
      throw DRMDecryptorException();
    }
  }

  virtual ~AES128ICMISMADRMDecryptor() {
    if (decryptor != 0) delete decryptor; decryptor = 0;
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
    UInt32T* unsecureSize);

private:
  AES128ICMDecryptor* decryptor;
  ISMADRMInfo drmInfo;
  DRMLogger& decLogger;
};

} // namespace DRMPlugin

#endif // !defined (ISMADRMDECRYPTOR_H)
