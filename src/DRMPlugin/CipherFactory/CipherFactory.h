/**	\file CipherFactory.h

	Cipher management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (CIPHERFACTORY_H)
#define CIPHERFACTORY_H

#include "ICipher.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!	\brief Cipher manager.
*/
class CipherFactory {
public:
  /*! \brief  Random generate bytes using passphrase.

      Memory is allocated by the function.

      \param  passphrase        input, passphrase used for random generation.
      \param  k                 output, random bytes.
      \param  klen              input, requested number of bytes.

      \returns  Boolean indicating success or failure.
  */
  static bool RndGenerate(UInt32T passphrase, ByteT** k, UInt32T klen);

  /*! \brief  Random generate bytes.

      Memory is allocated by the function.

      \param  k                 output, random bytes.
      \param  klen              input, requested number of bytes.

      \returns  Boolean indicating success or failure.
  */
  static bool RndGenerate(ByteT** k, UInt32T klen);

  /*! \brief  Get new blowfish encryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  logger            input-output, message logger.

      \returns  New blowfish encryptor. If fails, 0.
  */
  static BlowfishEncryptor* GetBlowfishEncryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger);

  /*! \brief  Get new AES128CBC encryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  iv                input, initialization vector.
      \param  logger            input-output, message logger.

      \returns  New AES128CBC encryptor. If fails, 0.
  */
  static AES128CBCEncryptor* GetAES128CBCEncryptor(ByteT* k, UInt32T kSize,
    ByteT* iv, DRMLogger& logger);

  /*! \brief  Get new AES128CTR encryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  iv                input, initialization vector.
      \param  logger            input-output, message logger.

      \returns  New AES128CTR encryptor. If fails, 0.
  */
  static AES128CTREncryptor* GetAES128CTREncryptor(ByteT* k, UInt32T kSize,
    ByteT* iv, DRMLogger& logger);

  /*! \brief  Get new AES128ICM encryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  logger            input-output, message logger.

      \returns  New AES128ICM encryptor. If fails, 0.
  */
  static AES128ICMEncryptor* GetAES128ICMEncryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger);

  /*! \brief  Get new blowfish decryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  logger            input-output, message logger.

      \returns  New blowfish encryptor. If fails, 0.
  */
  static BlowfishDecryptor* GetBlowfishDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger);

  /*! \brief  Get new AES128CBC decryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  logger            input-output, message logger.

      \returns  New AES128CBC decryptor. If fails, 0.
  */
  static AES128CBCDecryptor* GetAES128CBCDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger);

  /*! \brief  Get new AES128CTR decryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  logger            input-output, message logger.

      \returns  New AES128CTR decryptor. If fails, 0.
  */
  static AES128CTRDecryptor* GetAES128CTRDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger);

  /*! \brief  Get new AES128ICM decryptor.

      \param  k                 input, key.
      \param  kSize             input, key size.
      \param  logger            input-output, message logger.

      \returns  New AES128ICM decryptor. If fails, 0.
  */
  static AES128ICMDecryptor* GetAES128ICMDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined(CIPHERFACTORY_H)
