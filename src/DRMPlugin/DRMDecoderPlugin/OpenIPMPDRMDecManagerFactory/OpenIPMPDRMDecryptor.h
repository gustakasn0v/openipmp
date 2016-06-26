/**	\file OpenIPMPDRMDecryptor.h

	OpenIPMP DRM decryptor plugin.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPDRMDECRYPTOR_H)
#define OPENIPMPDRMDECRYPTOR_H

#include "ICipher.h"
#include "IOpenIPMPDRMDecryptor.h"
#include "OpenIPMPDRMInfo.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OpenIPMP DRM method using
    AES128CTR decryption.
*/
class AES128CTROpenIPMPDRMDecryptor: public IOpenIPMPDRMDecryptor {
public:
  /*! \brief  Constructor.

      \param      dec             input, decryptor.
      \param      info            input, content encryption information.
      \param      logger          input-output, message logger.

      If constructor fails, it throws DRMDecryptorException.
  */
  AES128CTROpenIPMPDRMDecryptor(AES128CTRDecryptor* dec, const OpenIPMPDRMInfo& info,
      DRMLogger& logger): decryptor(dec), drmInfo(info), decLogger(logger) {
    if (decryptor == 0) {
      decLogger.UpdateLog("AES128CTROpenIPMPDRMDecryptor::ctor: zero decryptor.");
      throw DRMDecryptorException();
    }
  }

  virtual ~AES128CTROpenIPMPDRMDecryptor() {
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
  OpenIPMPDRMInfo drmInfo;
  DRMLogger& decLogger;
};

/*! \brief Decrypts protected data.

    Protected data is decrypted according to OpenIPMP DRM method using
    blowfish decryption.
*/
class BlowfishOpenIPMPDRMDecryptor: public IOpenIPMPDRMDecryptor {
public:
  /*! \brief  Constructor.

      \param      dec             input, decryptor.
      \param      info            input, content encryption information.
      \param      logger          input-output, message logger.

      If constructor fails, it throws DRMDecryptorException.
  */
  BlowfishOpenIPMPDRMDecryptor(BlowfishDecryptor* dec, const OpenIPMPDRMInfo& info,
      DRMLogger& logger): decryptor(dec), drmInfo(info), decLogger(logger) {
    if (decryptor == 0) {
      decLogger.UpdateLog("BlowfishOpenIPMPDRMDecryptor::ctor: zero decryptor.");
      throw DRMDecryptorException();
    }
  }

  virtual ~BlowfishOpenIPMPDRMDecryptor() {
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
  BlowfishDecryptor* decryptor;
  OpenIPMPDRMInfo drmInfo;
  DRMLogger& decLogger;
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPDRMDECRYPTOR_H)
