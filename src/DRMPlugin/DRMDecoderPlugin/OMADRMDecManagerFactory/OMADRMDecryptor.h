/**	\file OMADRMDecryptor.h

	OMA DRM decryptor.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OMADRMDECRYPTOR_H)
#define OMADRMDECRYPTOR_H

#include "ICipher.h"
#include "IOMADRMDecryptor.h"
#include "OMADRMInfo.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OMA DRM method using AES128CBC
    decryption.
*/
class AES128CBCOMADRMDecryptor: public IOMADRMDecryptor {
public:
  /*! \brief  Constructor.

      \param      dec             input, decryptor.
      \param      info            input, content encryption information.
      \param      logger          input-output, message logger.

      If constructor fails, it throws DRMDecryptorException.
  */
  AES128CBCOMADRMDecryptor(AES128CBCDecryptor* dec, const OMADRMInfo& info,
      DRMLogger& logger): decryptor(dec), drmInfo(info), pTextLen(0), decLogger(logger) {
    if (decryptor == 0) {
      decLogger.UpdateLog("AES128CBCOMADRMDecryptor::ctor: zero decryptor.");
      throw DRMDecryptorException();
    }
  }

  virtual ~AES128CBCOMADRMDecryptor() {
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
  AES128CBCDecryptor* decryptor;
  OMADRMInfo drmInfo;
  UInt64T pTextLen;
  DRMLogger& decLogger;
};

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OMA DRM method using AES128CTR
    decryption.
*/
class AES128CTROMADRMDecryptor: public IOMADRMDecryptor {
public:
  /*! \brief  Constructor.

      \param      dec             input, decryptor.
      \param      info            input, content encryption information.
      \param      logger          input-output, message logger.

      If constructor fails, it throws DRMDecryptorException.
  */
  AES128CTROMADRMDecryptor(AES128CTRDecryptor* dec, const OMADRMInfo& info,
      DRMLogger& logger): decryptor(dec), drmInfo(info), pTextLen(0), decLogger(logger) {
    if (decryptor == 0) {
      decLogger.UpdateLog("AES128CTROMADRMDecryptor::ctor: zero decryptor.");
      throw DRMDecryptorException();
    }
  }

  virtual ~AES128CTROMADRMDecryptor() {
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
  AES128CTRDecryptor* decryptor;
  OMADRMInfo drmInfo;
  UInt64T pTextLen;
  DRMLogger& decLogger;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMDECRYPTOR_H)
