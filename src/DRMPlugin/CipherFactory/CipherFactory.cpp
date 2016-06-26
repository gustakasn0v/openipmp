/**	\file CipherFactory.cpp

	Cipher management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "CipherFactory.h"
#include "BlockCipher.h"
#include "rng.h"
#include "osrng.h"
//#include <openssl/rand.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!	\brief Cipher manager.
*/
/*! \brief  Random generate bytes using passphrase.

    Memory is allocated by the function.

    \param  passphrase        input, passphrase used for random generation.
    \param  k                 output, random bytes.
    \param  klen              input, requested number of bytes.

    \returns  Boolean indicating success or failure.
*/
bool CipherFactory::RndGenerate(UInt32T passphrase, ByteT** k, UInt32T klen) {
  if ((*k = (ByteT*)malloc(klen)) == NULL) {
    return false;
  }
	CryptoPP::LC_RNG rng(passphrase);
	rng.GenerateBlock(*k, klen);
  return true;
}

/*! \brief  Random generate bytes.

    Memory is allocated by the function.

    \param  k                 output, random bytes.
    \param  klen              input, requested number of bytes.

    \returns  Boolean indicating success or failure.
*/
bool CipherFactory::RndGenerate(ByteT** k, UInt32T klen) {
  if ((*k = (ByteT*)malloc(klen)) == NULL) {
    return false;
  }
#ifdef JOJO
	//  Generate random key
	char buffer[200];
	const char* filename = RAND_file_name(buffer, sizeof(buffer));
	/** load the random number file */
  int bytes = RAND_load_file(buffer, -1);
	/** get the key */
	if (!RAND_bytes(*k, klen)) {
    free(*k);
		RAND_cleanup();
		return false; 
	}
	RAND_cleanup();
  return true;
#endif
  static CryptoPP::AutoSeededX917RNG<CryptoPP::Rijndael> rng;
  rng.Reseed();
	rng.GenerateBlock(*k, klen);
  return true;
}

/*! \brief  Get new blowfish encryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  logger            input-output, message logger.

    \returns  New blowfish encryptor. If fails, 0.
*/
BlowfishEncryptor* CipherFactory::GetBlowfishEncryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger) {
  try {
//    return new OpenSSLBlowfishEncryptor(k, kSize, logger);
    return new CPPBlowfishEncryptor(k, kSize, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetBlowfishEncryptor: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new AES128CBC encryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  iv                input, initialization vector.
    \param  logger            input-output, message logger.

    \returns  New AES128CBC encryptor. If fails, 0.
*/
AES128CBCEncryptor* CipherFactory::GetAES128CBCEncryptor(ByteT* k, UInt32T kSize,
    ByteT* iv, DRMLogger& logger) {
  try {
    return new CPPAES128CBCEncryptor(k, kSize, iv, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetAES128CBCEncryptor: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new AES128CTR encryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  iv                input, initialization vector.
    \param  logger            input-output, message logger.

    \returns  New AES128CTR encryptor. If fails, 0.
*/
AES128CTREncryptor* CipherFactory::GetAES128CTREncryptor(ByteT* k, UInt32T kSize,
    ByteT* iv, DRMLogger& logger) {
  try {
    return new CPPAES128CTREncryptor(k, kSize, iv, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetAES128CTREncryptor: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new AES128ICM encryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  logger            input-output, message logger.

    \returns  New AES128ICM encryptor. If fails, 0.
*/
AES128ICMEncryptor* CipherFactory::GetAES128ICMEncryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger) {
  try {
    return new SRTPAES128ICMEncryptor(k, kSize, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetAES128ICMEncryptor: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new blowfish decryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  logger            input-output, message logger.

    \returns  New blowfish encryptor. If fails, 0.
*/
BlowfishDecryptor* CipherFactory::GetBlowfishDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger) {
  try {
//    return new OpenSSLBlowfishDecryptor(k, kSize, logger);
    return new CPPBlowfishDecryptor(k, kSize, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetBlowfishDecryptor: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new AES128CBC decryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  logger            input-output, message logger.

    \returns  New AES128CBC decryptor. If fails, 0.
*/
AES128CBCDecryptor* CipherFactory::GetAES128CBCDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger) {
  try {
    return new CPPAES128CBCDecryptor(k, kSize, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetAES128CBCDecryptor: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new AES128CTR decryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  logger            input-output, message logger.

    \returns  New AES128CTR decryptor. If fails, 0.
*/
AES128CTRDecryptor* CipherFactory::GetAES128CTRDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger) {
  try {
    return new CPPAES128CTRDecryptor(k, kSize, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetAES128CTRDecryptor: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new AES128ICM decryptor.

    \param  k                 input, key.
    \param  kSize             input, key size.
    \param  logger            input-output, message logger.

    \returns  New AES128ICM decryptor. If fails, 0.
*/
AES128ICMDecryptor* CipherFactory::GetAES128ICMDecryptor(ByteT* k, UInt32T kSize,
    DRMLogger& logger) {
  try {
    return new SRTPAES128ICMDecryptor(k, kSize, logger);
  }
  catch (CipherException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("CipherFactory::GetAES128ICMDecryptor: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
