/**	\file BlockCipher.h

	Block cipher encryption and decryption implementations.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (BLOCKCIPHER_H)
#define BLOCKCIPHER_H

#include "ICipher.h"
#include "rijndael.h"
#include "blowfish.h"
#include "modes.h"
#include "mqv.h"
#include "aes_icm.h"
#include "DRMLogger.h"
#include <string>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!	\brief  Blowfish encryptor using Crypto++ library.
*/
class CPPBlowfishEncryptor: public BlowfishEncryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  CPPBlowfishEncryptor(ByteT* k, UInt32T kSize, DRMLogger& logger);

  virtual ~CPPBlowfishEncryptor();

	/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

      \param  in        input, plaintext.
      \param  inSize    input, size of the plaintext.
      \param  out       output, ciphertext.
      \param  outLen    output, size of the ciphertext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Encrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen);

private:
	ByteT* key;
  UInt32T keySize;
	ByteT* iv;
  CryptoPP::CFB_Mode<CryptoPP::Blowfish>::Encryption enc;
	/*  Here we use std::string, because we're not sure how large the buffer
		  needs to be (because of padding).
	*/
	std::string encData;
	CryptoPP::StreamTransformationFilter filter;
};

/*!	\brief  AES128 encryptor in CBC mode using Crypto++ library.
*/
class CPPAES128CBCEncryptor: public AES128CBCEncryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  i         initialization vector.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  CPPAES128CBCEncryptor(ByteT* k, UInt32T kSize, ByteT* i, DRMLogger& logger);

  virtual ~CPPAES128CBCEncryptor();

	/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

      \param  in        input, plaintext.
      \param  inSize    input, size of the plaintext.
      \param  out       output, ciphertext.
      \param  outLen    output, size of the ciphertext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Encrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen);

	/*!	\brief  Get initialization vector that is to be used for next packet encryption.

      \param  par       output, initialization vector.
      \param  parLen    output, size of the initialization vector.

      \return Boolean indicating success or failure.
	*/
	virtual bool NextIV(ByteT** par, UInt32T* parLen);

private:
	ByteT* key;
  UInt32T keySize;
	ByteT* iv;
  CryptoPP::CBC_Mode<CryptoPP::Rijndael>::Encryption enc;
	/*  Here we use std::string, because we're not sure how large the buffer
		  needs to be (because of padding).
	*/
	std::string encData;
	CryptoPP::StreamTransformationFilter filter;
};

/*!	\brief  AES128 encryptor in CTR mode using Crypto++ library.
*/
class CPPAES128CTREncryptor: public AES128CTREncryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  i         initialization vector.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  CPPAES128CTREncryptor(ByteT* k, UInt32T kSize, ByteT* i, DRMLogger& logger);

  virtual ~CPPAES128CTREncryptor();

	/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

      \param  in        input, plaintext.
      \param  inSize    input, size of the plaintext.
      \param  out       output, ciphertext.
      \param  outLen    output, size of the ciphertext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Encrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen);

	/*!	\brief  Get counter that is to be used for next packet encryption.

      \param  par       output, counter.
      \param  parLen    output, size of the counter.

      \return Boolean indicating success or failure.
	*/
	virtual bool NextCtr(ByteT** par, UInt32T* parLen);

private:
	ByteT* key;
  UInt32T keySize;
	ByteT* iv;
	CryptoPP::CTR_Mode<CryptoPP::Rijndael>::Encryption enc;
	/*  Here we use std::string, because we're not sure how large the buffer
		  needs to be (because of padding).
	*/
	std::string encData;
	CryptoPP::StreamTransformationFilter filter;
};

/*!	\brief  AES128 encryptor in ICM mode using SRTP library.
*/
class SRTPAES128ICMEncryptor: public AES128ICMEncryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  SRTPAES128ICMEncryptor(ByteT* k, UInt32T kSize, DRMLogger& logger);

  virtual ~SRTPAES128ICMEncryptor();

	/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

      \param  in        input, plaintext.
      \param  inSize    input, size of the plaintext.
      \param  out       output, ciphertext.
      \param  outLen    output, size of the ciphertext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Encrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen);

	/*!	\brief  Get byte stream offset that is to be used for next packet encryption.

      \param  par       output, byte stream offset.
      \param  parLen    output, size of the byte stream offset.

      \return Boolean indicating success or failure.
	*/
	virtual bool NextIV(ByteT** par, UInt32T* parLen);

private:
  //  16 bytes for the key, 8 bytes for the salt, 8 bytes for the counter.
  ByteT aes_overlay[32];
  cipher_t *cp;
  UInt32T BSO;
};

/*!	\brief Blowfish decryptor using Crypto++ library.
*/
class CPPBlowfishDecryptor: public BlowfishDecryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  CPPBlowfishDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger);

  virtual ~CPPBlowfishDecryptor();

	/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

      \param  in        input, ciphertext.
      \param  inSize    input, size of the ciphertext.
      \param  out       output, plaintext.
      \param  outLen    output, size of the plaintext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Decrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen);

private:
	ByteT* key;
  UInt32T keySize;
	ByteT* iv;
	CryptoPP::CFB_Mode<CryptoPP::Blowfish>::Decryption dec;
	/*  Here we use std::string, because we're not sure how large the buffer
		  needs to be (because of padding).
	*/
	std::string decData;
	CryptoPP::StreamTransformationFilter filter;
};

/*!	\brief  AES128 decryptor in CBC mode using Crypto++ library.
*/
class CPPAES128CBCDecryptor: public AES128CBCDecryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  CPPAES128CBCDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger);

  virtual ~CPPAES128CBCDecryptor();

	/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

      \param  in        input, ciphertext.
      \param  inSize    input, size of the ciphertext.
      \param  iv        input, initialization vector.
      \param  ivSize    input, size of the initialization vector.
      \param  out       output, plaintext.
      \param  outLen    output, size of the plaintext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Decrypt(ByteT* in, UInt32T inSize, ByteT* iv, UInt32T ivSize,
    ByteT** out, UInt32T* outLen);

private:
	ByteT* key;
  UInt32T keySize;
	CryptoPP::CBC_Mode<CryptoPP::Rijndael>::Decryption dec;
	/*  Here we use std::string, because we're not sure how large the buffer
		  needs to be (because of padding).
	*/
	std::string decData;
	CryptoPP::StreamTransformationFilter filter;
};

/*!	\brief  AES128 decryptor in CTR mode using Crypto++ library.
*/
class CPPAES128CTRDecryptor: public AES128CTRDecryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  CPPAES128CTRDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger);

  virtual ~CPPAES128CTRDecryptor();

	/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

      \param  in        input, ciphertext.
      \param  inSize    input, size of the ciphertext.
      \param  ctr       input, counter.
      \param  ctrSize   input, size of the counter.
      \param  out       output, plaintext.
      \param  outLen    output, size of the plaintext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Decrypt(ByteT* in, UInt32T inSize, ByteT* ctr, UInt32T ctrSize,
    ByteT** out, UInt32T* outLen);

private:
	ByteT* key;
  UInt32T keySize;
	CryptoPP::CTR_Mode<CryptoPP::Rijndael>::Decryption dec;
	/*  Here we use std::string, because we're not sure how large the buffer
		  needs to be (because of padding).
	*/
	std::string decData;
	CryptoPP::StreamTransformationFilter filter;
};

/*!	\brief  AES128 decryptor in ICM mode using SRTP library.
*/
class SRTPAES128ICMDecryptor: public AES128ICMDecryptor {
public:
  /*! \brief  Constructor.

      \param  k         key.
      \param  kSize     key size.
      \param  logger    message logger.

      If fails, throws CipherException.
  */
  SRTPAES128ICMDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger);

  virtual ~SRTPAES128ICMDecryptor();

	/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

      \param  in        input, ciphertext.
      \param  inSize    input, size of the ciphertext.
      \param  iv        input, byte stream offset.
      \param  ivSize    input, size of the byte stream offset.
      \param  out       output, plaintext.
      \param  outLen    output, size of the plaintext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Decrypt(ByteT* in, UInt32T inSize, ByteT* iv, UInt32T ivSize,
    ByteT** out, UInt32T* outLen);

private:
  //  16 bytes for the key, 8 bytes for the salt, 8 bytes for the counter.
  ByteT aes_overlay[32];
  cipher_t *cp;
};

} // namespace DRMPlugin

#endif // !defined (BLOCKCIPHER_H)
