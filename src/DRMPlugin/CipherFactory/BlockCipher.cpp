/**	\file BlockCipher.cpp

	Block cipher encryption and decryption implementations.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "BlockCipher.h"

#if defined (WIN32)
#include <windows.h>
#endif

extern "C" struct cipher_type_t aes_icm;

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
CPPBlowfishEncryptor::CPPBlowfishEncryptor(ByteT* k, UInt32T kSize, DRMLogger& logger):
    key(k), keySize(kSize), iv(0), encData(),
    filter(enc, new CryptoPP::StringSink(encData),
#if defined (WIN32)
    CryptoPP::StreamTransformationFilter::BlockPaddingScheme::DEFAULT_PADDING) {
#elif defined (LINUX)
    CryptoPP::StreamTransformationFilter::DEFAULT_PADDING) {
#else
    CryptoPP::StreamTransformationFilter::DEFAULT_PADDING) {
#endif
  if ((iv = (ByteT*)malloc(keySize)) == NULL) {
    if (key != 0) free(key); key = 0;
    if (iv != 0) free(iv); iv = 0;
    logger.UpdateLog("CPPBlowfishEncryptor::CPPBlowfishEncryptor: memory allocation error.");
    throw CipherException();
  }
  memset(iv, 0, keySize);
}


CPPBlowfishEncryptor::~CPPBlowfishEncryptor() {
  if (key != 0) free(key); key = 0;
  if (iv != 0) free(iv); iv = 0;
}

/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

    \param  in        input, plaintext.
    \param  inSize    input, size of the plaintext.
    \param  out       output, ciphertext.
    \param  outLen    output, size of the ciphertext.

    \return Boolean indicating success or failure.
*/
bool CPPBlowfishEncryptor::Encrypt(ByteT* in, UInt32T inSize, ByteT** out,
    UInt32T* outLen) {
	enc.SetKeyWithIV((unsigned char*)key, keySize, iv);
	encData = "";
	filter.Put((unsigned char*)in, inSize);
	filter.MessageEnd();

  *out = (ByteT*)malloc(encData.size());
  if (*out == NULL) {
    return false;
  }
  memcpy(*out, encData.c_str(), encData.size());
  *outLen = encData.size();
  return true;
}

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  i         initialization vector.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
CPPAES128CBCEncryptor::CPPAES128CBCEncryptor(ByteT* k, UInt32T kSize,
    ByteT* i, DRMLogger& logger): key(k), keySize(kSize), iv(i), enc(), encData(),
    filter(enc, new CryptoPP::StringSink(encData),
#if defined (WIN32)
    CryptoPP::StreamTransformationFilter::BlockPaddingScheme::PKCS_PADDING) {
#elif defined (LINUX)
    CryptoPP::StreamTransformationFilter::PKCS_PADDING) {
#else
    CryptoPP::StreamTransformationFilter::PKCS_PADDING) {
#endif

  if (kSize != 16) {
    if (key != 0) free(key); key = 0;
    if (iv != 0) free(iv); iv = 0;
    logger.UpdateLog("CPPAES128CBCEncryptor::ctor: wrong key size.");
    throw CipherException();
  }
	enc.SetKeyWithIV((unsigned char*)key, keySize, (unsigned char*)iv);
}

CPPAES128CBCEncryptor::~CPPAES128CBCEncryptor() {
  if (key != 0) free(key); key = 0;
  if (iv != 0) free(iv); iv = 0;
}

/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

    \param  in        input, plaintext.
    \param  inSize    input, size of the plaintext.
    \param  out       output, ciphertext.
    \param  outLen    output, size of the ciphertext.

    \return Boolean indicating success or failure.
*/
bool CPPAES128CBCEncryptor::Encrypt(ByteT* in, UInt32T inSize, ByteT** out,
    UInt32T* outLen) {
	encData = "";
	filter.Put((unsigned char*)in, inSize);
	filter.MessageEnd();
	enc.Resynchronize((unsigned char*)iv);
	enc.GetNextIV((unsigned char*)iv);
	enc.SetKeyWithIV((unsigned char*)key, keySize, (unsigned char*)iv);

  *out = (ByteT*)malloc(encData.size());
  if (*out == NULL) {
    return false;
  }
  memcpy(*out, encData.c_str(), encData.size());
  *outLen = encData.size();
  return true;
}

/*!	\brief  Get initialization vector that is to be used for next packet encryption.

    \param  par       output, initialization vector.
    \param  parLen    output, size of the initialization vector.

    \return Boolean indicating success or failure.
*/
bool CPPAES128CBCEncryptor::NextIV(ByteT** par, UInt32T* parLen) {
  *par = (ByteT*)malloc(keySize);
  if (*par == NULL) {
    return false;
  }
  memcpy(*par, iv, keySize);
  *parLen = keySize;
  return true;
}

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  i         initialization vector.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
CPPAES128CTREncryptor::CPPAES128CTREncryptor(ByteT* k, UInt32T kSize,
    ByteT* i, DRMLogger& logger): key(k), keySize(kSize), iv(i), enc(), encData(),
    filter(enc, new CryptoPP::StringSink(encData),
#if defined (WIN32)
    CryptoPP::StreamTransformationFilter::BlockPaddingScheme::NO_PADDING) {
#elif defined (LINUX)
    CryptoPP::StreamTransformationFilter::NO_PADDING) {
#else
    CryptoPP::StreamTransformationFilter::NO_PADDING) {
#endif

  if (kSize != 16) {
    //! Error.
    if (key != 0) free(key); key = 0;
    if (iv != 0) free(iv); iv = 0;
    logger.UpdateLog("CPPAES128CTREncryptor::ctor: wrong key size.");
    throw CipherException();
  }
	enc.SetKeyWithIV((unsigned char*)key, keySize, (unsigned char*)iv);
}

CPPAES128CTREncryptor::~CPPAES128CTREncryptor() {
  if (key != 0) free(key); key = 0;
  if (iv != 0) free(iv); iv = 0;
}

/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

    \param  in        input, plaintext.
    \param  inSize    input, size of the plaintext.
    \param  out       output, ciphertext.
    \param  outLen    output, size of the ciphertext.

    \return Boolean indicating success or failure.
*/
bool CPPAES128CTREncryptor::Encrypt(ByteT* in, UInt32T inSize, ByteT** out,
    UInt32T* outLen) {
	encData = "";
	filter.Put((unsigned char*)in, inSize);
	filter.MessageEnd();
	enc.Resynchronize((unsigned char*)iv);
	enc.GetNextIV((unsigned char*)iv);
	enc.SetKeyWithIV((unsigned char*)key, keySize, (unsigned char*)iv);

  *out = (ByteT*)malloc(encData.size());
  if (*out == NULL) {
    return false;
  }
  memcpy(*out, encData.c_str(), encData.size());
  *outLen = encData.size();
  return true;
}

/*!	\brief  Get counter that is to be used for next packet encryption.

    \param  par       output, counter.
    \param  parLen    output, size of the counter.

    \return Boolean indicating success or failure.
*/
bool CPPAES128CTREncryptor::NextCtr(ByteT** par, UInt32T* parLen) {
  *par = (ByteT*)malloc(keySize);
  if (*par == NULL) {
    return false;
  }
  memcpy(*par, iv, keySize);
  *parLen = keySize;
  return true;
}

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
SRTPAES128ICMEncryptor::SRTPAES128ICMEncryptor(ByteT* k, UInt32T kSize, DRMLogger& logger):
    aes_overlay(), BSO(0) {
  memset(aes_overlay, 0, 32);
  memcpy(aes_overlay, k, kSize);
  if (k != 0) {
    free(k);
  }
  if (kSize != 24) {
    logger.UpdateLog("SRTPAES128ICMEncryptor::ctor: wrong key size.");
    throw CipherException();
  }
  err_status_t rc = err_status_ok;
  //  Allocate cipher.
  rc = aes_icm.alloc(&cp, 24);
  if (rc != err_status_ok) {
    logger.UpdateLog("SRTPAES128ICMEncryptor::ctor: allocation error.");
    throw CipherException();
  }
  //  Init cipher.
  rc = aes_icm.init((aes_icm_ctx_t*)(cp->state), aes_overlay, direction_encrypt);
  if (rc != err_status_ok) {
    logger.UpdateLog("SRTPAES128ICMEncryptor::ctor: initialization error.");
    throw CipherException();
  }
}

SRTPAES128ICMEncryptor::~SRTPAES128ICMEncryptor() {
  aes_icm.dealloc(cp);
}

/*!	\brief  Encrypts plaintext from in and returns ciphertext in out.

    \param  in        input, plaintext.
    \param  inSize    input, size of the plaintext.
    \param  out       output, ciphertext.
    \param  outLen    output, size of the ciphertext.

    \return Boolean indicating success or failure.
*/
bool SRTPAES128ICMEncryptor::Encrypt(ByteT* in, UInt32T inSize, ByteT** out,
    UInt32T* outLen) {
  err_status_t rc = err_status_ok;

  *outLen = inSize;
  *out = (ByteT *)malloc(*outLen);
  if (*out == NULL) {
    return false;
  }
  memcpy(*out, in, *outLen);

  // length will not be updated in calling function (obviously) awv.
//  rc = aes_icm_encrypt(cp->state, *out, outLen);
  rc = aes_icm.encrypt(cp->state, *out, (unsigned int*)outLen);
  if (rc != err_status_ok) {
    free(*out);
    return false;
  }

  BSO += inSize;

  return true;
}

/*!	\brief  Get byte stream offset that is to be used for next packet encryption.

    \param  par       output, byte stream offset.
    \param  parLen    output, size of the byte stream offset.

    \return Boolean indicating success or failure.
*/
bool SRTPAES128ICMEncryptor::NextIV(ByteT** par, UInt32T* parLen) {
  *par = (ByteT*)malloc(16);
  if (*par == NULL) {
    return false;
  }
  //  Copy salt.
  memset(*par, 0, 16);
  memcpy(*par, aes_overlay + 16, 8);
  *((UInt32T*)(*par + 12)) = htonl(BSO);
  *parLen = 16;
  return true;
}

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
CPPBlowfishDecryptor::CPPBlowfishDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger):
    key(k), keySize(kSize), iv(0), dec(), decData(),
    filter(dec, new CryptoPP::StringSink(decData),
#if defined (WIN32)
    CryptoPP::StreamTransformationFilter::BlockPaddingScheme::DEFAULT_PADDING) {
#elif defined (LINUX)
    CryptoPP::StreamTransformationFilter::DEFAULT_PADDING) {
#else
    CryptoPP::StreamTransformationFilter::DEFAULT_PADDING) {
#endif

  if ((iv = (ByteT*)malloc(keySize)) == NULL) {
    if (key != 0) free(key); key = 0;
    if (iv != 0) free(iv); iv = 0;
    logger.UpdateLog("CPPBlowfishDecryptor::CPPBlowfishDecryptor: memory allocation error.");
    throw CipherException();
  }
  memset(iv, 0, keySize);
}

CPPBlowfishDecryptor::~CPPBlowfishDecryptor() {
  if (key != 0) free(key); key = 0;
  if (iv != 0) free(iv); iv = 0;
}

/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

    \param  in        input, ciphertext.
    \param  inSize    input, size of the ciphertext.
    \param  out       output, plaintext.
    \param  outLen    output, size of the plaintext.

    \return Boolean indicating success or failure.
*/
bool CPPBlowfishDecryptor::Decrypt(ByteT* in, UInt32T inSize, ByteT** out,
    UInt32T* outLen) {
	dec.SetKeyWithIV((unsigned char*)key, keySize, iv);
	decData = "";
	filter.Put((unsigned char*)in, inSize);
	filter.MessageEnd();

  *out = (ByteT*)malloc(decData.size() + 3);
  if (*out == NULL) {
    return false;
  }
  memcpy(*out, decData.c_str(), decData.size());
  *outLen = decData.size();
  return true;
}

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
CPPAES128CBCDecryptor::CPPAES128CBCDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger):
  	key(k), keySize(kSize), dec(), decData(), filter(dec, new CryptoPP::StringSink(decData),
#if defined (WIN32)
	  CryptoPP::StreamTransformationFilter::BlockPaddingScheme::PKCS_PADDING) {
#elif defined (LINUX)
	  CryptoPP::StreamTransformationFilter::PKCS_PADDING) {
#else
	  CryptoPP::StreamTransformationFilter::PKCS_PADDING) {
#endif

  if (kSize != 16) {
    if (key != 0) free(key); key = 0;
    logger.UpdateLog("CPPAES128CBCDecryptor::ctor: wrong key size.");
    throw CipherException();
  }
}

CPPAES128CBCDecryptor::~CPPAES128CBCDecryptor() {
  if (key != 0) free(key); key = 0;
}

/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

    \param  in        input, ciphertext.
    \param  inSize    input, size of the ciphertext.
    \param  iv        input, initialization vector.
    \param  ivSize    input, size of the initialization vector.
    \param  out       output, plaintext.
    \param  outLen    output, size of the plaintext.

    \return Boolean indicating success or failure.
*/
bool CPPAES128CBCDecryptor::Decrypt(ByteT* in, UInt32T inSize, ByteT* iv,
    UInt32T ivSize, ByteT** out, UInt32T* outLen) {
	decData = "";
  if (ivSize != keySize) {
    return false;
  }
	dec.SetKeyWithIV((unsigned char*)key, keySize, (unsigned char*)iv);
	filter.Put((unsigned char*)in, inSize);
	filter.MessageEnd();

  *out = (ByteT*)malloc(decData.size() + 3);
  if (*out == NULL) {
    return false;
  }
  memcpy(*out, decData.c_str(), decData.size());
  *outLen = decData.size();
  return true;
}

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
CPPAES128CTRDecryptor::CPPAES128CTRDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger):
  	key(k), keySize(kSize), dec(), decData(), filter(dec, new CryptoPP::StringSink(decData),
#if defined (WIN32)
	  CryptoPP::StreamTransformationFilter::BlockPaddingScheme::NO_PADDING) {
#elif defined (LINUX)
	  CryptoPP::StreamTransformationFilter::NO_PADDING) {
#else
	  CryptoPP::StreamTransformationFilter::NO_PADDING) {
#endif

  if (kSize != 16) {
    if (key != 0) free(key); key = 0;
    logger.UpdateLog("CPPAES128CTRDecryptor::ctor: wrong key size.");
    throw CipherException();
  }
}

CPPAES128CTRDecryptor::~CPPAES128CTRDecryptor() {
  if (key != 0) free(key); key = 0;
}

/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

    \param  in        input, ciphertext.
    \param  inSize    input, size of the ciphertext.
    \param  ctr       input, counter.
    \param  ctrSize   input, size of the counter.
    \param  out       output, plaintext.
    \param  outLen    output, size of the plaintext.

    \return Boolean indicating success or failure.
*/
bool CPPAES128CTRDecryptor::Decrypt(ByteT* in, UInt32T inSize, ByteT* ctr,
    UInt32T ctrSize, ByteT** out, UInt32T* outLen) {
	decData = "";
  if (ctrSize != keySize) {
    return false;
  }
	dec.SetKeyWithIV((unsigned char*)key, keySize, (unsigned char*)ctr);
	filter.Put((unsigned char*)in, inSize);
	filter.MessageEnd();

  *out = (ByteT*)malloc(decData.size() + 3);
  if (*out == NULL) {
    return false;
  }
  memcpy(*out, decData.c_str(), decData.size());
  *outLen = decData.size();
  return true;
}

/*! \brief  Constructor.

    \param  k         key.
    \param  kSize     key size.
    \param  logger    message logger.

    If fails, throws CipherException.
*/
SRTPAES128ICMDecryptor::SRTPAES128ICMDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger):
    aes_overlay() {
  memset(aes_overlay, 0, 32);
  memcpy(aes_overlay, k, kSize);
  if (k != 0) {
    free(k);
  }
  if (kSize != 16) {
    logger.UpdateLog("SRTPAES128ICMDecryptor::ctor: wrong key size.");
    throw CipherException();
  }
  err_status_t rc = err_status_ok;
  //  Allocate cipher.
  rc = aes_icm.alloc(&cp, 24);
  if (rc != err_status_ok) {
    //! Error.
    logger.UpdateLog("SRTPAES128ICMDecryptor::ctor: initialization error.");
    throw CipherException();
  }
  //  Init cipher.
//  rc = aes_icm_context_init((aes_icm_ctx_t*)(cp->state), aes_overlay);
  rc = aes_icm.init((aes_icm_ctx_t*)(cp->state), aes_overlay, direction_decrypt);
  if (rc != err_status_ok) {
    aes_icm.dealloc(cp);
    logger.UpdateLog("SRTPAES128ICMDecryptor::ctor: initialization error.");
    throw CipherException();
  }
}

SRTPAES128ICMDecryptor::~SRTPAES128ICMDecryptor() {
  aes_icm.dealloc(cp);
}

/*!	\brief  Decrypts ciphertext from in and returns plaintext in out.

    \param  in        input, ciphertext.
    \param  inSize    input, size of the ciphertext.
    \param  iv        input, byte stream offset.
    \param  ivSize    input, size of the byte stream offset.
    \param  out       output, plaintext.
    \param  outLen    output, size of the plaintext.

    \return Boolean indicating success or failure.
*/
bool SRTPAES128ICMDecryptor::Decrypt(ByteT* in, UInt32T inSize, ByteT* iv,
    UInt32T ivSize, ByteT** out, UInt32T* outLen) {
  if (ivSize != 16) {
    return false;
  }
  ByteT counter[16];
  memset(counter, 0, 16);
  memcpy(counter, iv, 8);
  UInt32T BSO = ntohl(*((UInt32T*)(iv + 12)));
  UInt32T ctr = BSO/16;
  UInt32T rem = BSO%16;
  *((UInt32T *)(&counter[12])) = htonl(ctr);

  err_status_t rc;
  rc = aes_icm.set_iv((cipher_t*)(cp->state), counter);
  if (rc != err_status_ok) {
    return false;
  }
  
  // calculate counter from BSO
  if (rem) {
    // a non-zero remainder means that the key corresponding to 
    // counter has only decrypted a number of bytes equal
    // to remainder in the preceding data. therefore that key must 
    // be used to decrypt the first (16 - remainder) bytes of this data.
    // so we need to first set the previous key and do a fake decrypt to
    // get everything set up properly for this decrypt.

    // this is the fake decrypt of remainder bytes.
    ByteT fakedata[16];
    rc = aes_icm.encrypt((aes_icm_ctx_t*)(cp->state), fakedata, (unsigned int*)(&rem));
    if (rc != err_status_ok) {
      return false;
    }
  }

  *outLen = inSize;
  *out = (ByteT *)malloc(*outLen + 3);
  if (*out == NULL) {
    return false; 
  }
  memcpy(*out, in, *outLen);
  
  // length will not be updated in calling function (obviously) awv.
  rc = aes_icm.encrypt((aes_icm_ctx_t*)(cp->state), *out, (unsigned int*)outLen);
  if (rc != err_status_ok) {
    if (*out) free(*out);
    *outLen = 0;
    return false;
  }

  return true;
}

} // namespace DRMPlugin
