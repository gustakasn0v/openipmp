/**	\file ICipher.h

	Interfaces for block cipher encryption and decryption.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ICIPHER_H)
#define ICIPHER_H

#include "BasicTypes.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Encryption methods.
*/
enum EncMethod {
  //! No encryption.
  NULLENC   = 0,
  //! AES with 128-bit key in CBC mode encryption.
  AES128CBC = 1,
  //! AES with 128-bit key in CTR mode encryption.
  AES128CTR = 2,
  //! AES with 128-bit key in ICM mode encryption.
  AES128ICM = 3,
  //! Blowfish encryption.
  BLOWFISH  = 4
};

/*! \brief Exception used for cipher error.
*/
class CipherException {
};

/*!	\brief Encrypts data according to blowfish algorithm.
*/
class BlowfishEncryptor {
public:
  virtual ~BlowfishEncryptor() {};

	/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

      \param  in        input, plaintext.
      \param  inSize    input, size of the plaintext.
      \param  out       output, ciphertext.
      \param  outLen    output, size of the ciphertext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Encrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen) = 0;
};

/*!	\brief Encrypts data according to AES algorithm (with 128-bit key).
*/
class AES128Encryptor {
public:
  virtual ~AES128Encryptor() {};

	/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

      \param  in        input, plaintext.
      \param  inSize    input, size of the plaintext.
      \param  out       output, ciphertext.
      \param  outLen    output, size of the ciphertext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Encrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen) = 0;
};

/*!	\brief Encrypts data according to AES algorithm (with 128-bit key) in CBC mode.

    Encrypts data and gets initialization vector that is to be used for
    encrypting next packet.
*/
class AES128CBCEncryptor: public AES128Encryptor {
public:
  virtual ~AES128CBCEncryptor() {};

	/*!	\brief  Get initialization vector that is to be used for next packet encryption.

      \param  par       output, initialization vector.
      \param  parLen    output, size of the initialization vector.

      \return Boolean indicating success or failure. In case of failure,
              logger's log will contain error message.
	*/
	virtual bool NextIV(ByteT** par, UInt32T* parLen) = 0;
};

/*!	\brief Encrypts data according to AES algorithm (with 128-bit key) in CTR mode.

    Encrypts data and gets counter that is to be used for encrypting next packet.
*/
class AES128CTREncryptor: public AES128Encryptor {
public:
  virtual ~AES128CTREncryptor() {};

	/*!	\brief  Get counter that is to be used for next packet encryption.

      \param  par       output, counter.
      \param  parLen    output, size of the counter.

      \return Boolean indicating success or failure.
	*/
	virtual bool NextCtr(ByteT** par, UInt32T* parLen) = 0;
};

/*!	\brief Encrypts data according to AES algorithm (with 128-bit key) in ICM mode.

    Encrypts data and gets byte stream offset that is to be used for encrypting
    next packet.
*/
class AES128ICMEncryptor: public AES128Encryptor {
public:
  virtual ~AES128ICMEncryptor() {};

	/*!	\brief  Get byte stream offset that is to be used for next packet encryption.

      \param  par       output, byte stream offset.
      \param  parLen    output, size of the byte stream offset.

      \return Boolean indicating success or failure.
	*/
	virtual bool NextIV(ByteT** par, UInt32T* parLen) = 0;
};

/*!	\brief Decrypts data according to blowfish algorithm.
*/
class BlowfishDecryptor {
public:
  virtual ~BlowfishDecryptor() {};

	/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

      \param  in        input, ciphertext.
      \param  inSize    input, size of the ciphertext.
      \param  out       output, plaintext.
      \param  outLen    output, size of the plaintext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Decrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen) = 0;
};

/*!	\brief Decrypts data according to AES algorithm (with 128-bit key).

    Decrypts data using initialization vector.
*/
class AES128Decryptor {
public:
  virtual ~AES128Decryptor() {};
};

/*!	\brief Decrypts data according to AES algorithm (with 128-bit key) in CBC mode.

    Decrypts data using initialization vector.
*/
class AES128CBCDecryptor: public AES128Decryptor {
public:
  virtual ~AES128CBCDecryptor() {};

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
    ByteT** out, UInt32T* outLen) = 0;
};

/*!	\brief Decrypts data according to AES algorithm (with 128-bit key) in CTR mode.

    Decrypts data using counter.
*/
class AES128CTRDecryptor: public AES128Decryptor {
public:
  virtual ~AES128CTRDecryptor() {};

	/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

      \param  in        input, ciphertext.
      \param  inSize    input, size of the ciphertext.
      \param  ctr       input, counter.
      \param  ctrSize   input, size of the counter.
      \param  out       output, plaintext.
      \param  outLen    output, size of the plaintext.

      \return Boolean indicating success or failure. In case of failure,
              logger's log will contain error message.
	*/
	virtual bool Decrypt(ByteT* in, UInt32T inSize, ByteT* ctr, UInt32T ctrSize,
    ByteT** out, UInt32T* outLen) = 0;
};

/*!	\brief Decrypts data according to AES algorithm (with 128-bit key) in ICM mode.

    Decrypts data using byte stream offset.
*/
class AES128ICMDecryptor: public AES128Decryptor {
public:
  virtual ~AES128ICMDecryptor() {};

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
    ByteT** out, UInt32T* outLen) = 0;
};

} // namespace DRMPlugin

#endif // !defined (ICIPHER_H)
