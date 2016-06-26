/**	\file PublicCryptoFactory.cpp

	Public crypto management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "PublicCryptoFactory.h"

#include "OpenSSLPublicCrypto.h"
#include <openssl/evp.h>

//	Need this cause wincrypt.h defines X509_NAME and it produces a
//	conflict with openSSL definition.
#if defined X509_NAME
#undef X509_NAME
#endif // X509_NAME

#include <openssl/pem.h>
#include <openssl/pkcs12.h>

#include <openssl/engine.h>
#include <iostream>
#include <sys/stat.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!  \brief  Class used for handling globals.
*/
class PublicCryptoGlobalHandler {
public:
  /*!  \brief  Constructor.
  */
  PublicCryptoGlobalHandler() {
  }

  /*!  \brief  Destructor.
  */
  ~PublicCryptoGlobalHandler() {
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
  }
};

static PublicCryptoGlobalHandler publicCryptoGlobalHandler;

/*! \brief  Get new MD5 hasher.

    \param  logger	input, message logger.

    \returns  New MD5 hasher. If fails, 0.
*/
IHasher* PublicCryptoFactory::GetMD5Hasher(DRMLogger& logger) {
  return new MD5OpenSSLHasher();
}

/*! \brief  Get new SHA1 hasher.

    \param  logger	input, message logger.

    \returns  New SHA1 hasher. If fails, 0.
*/
IHasher* PublicCryptoFactory::GetSHA1Hasher(DRMLogger& logger) {
  return new SHA1OpenSSLHasher();
}

/*! \brief  Parse public key decryptor from key data.

    \param  data        input, data.
    \param  datalen     input, data length.
    \param  logger	input, message logger.

    \returns  New public key decryptor. If fails, 0.
*/
IPublicDecryptor* PublicCryptoFactory::ParsePublicDecryptorFromKeyData(
    ByteT* data, unsigned int datalen, DRMLogger& logger) {
  return ParsePublicDecryptorSignerFromKeyData(data, datalen, logger);
}

/*! \brief  Parse public key signer from key data.

    \param  data        input, data.
    \param  datalen     input, data length.
    \param  logger	input, message logger.

    \returns  New public key signer. If fails, 0.
*/
IPublicSigner* PublicCryptoFactory::ParsePublicSignerFromKeyData(
    ByteT* data, unsigned int datalen, DRMLogger& logger) {
  return ParsePublicDecryptorSignerFromKeyData(data, datalen, logger);
}

/*! \brief  Parse public key decryptor and signer from key data.

    \param  data        input, data.
    \param  datalen     input, data length.
    \param  logger	input, message logger.

    \returns  New public key decryptor and signer. If fails, 0.
*/
IPublicDecryptorSigner* PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyData(
    ByteT* data, unsigned int datalen, DRMLogger& logger) {
#define USE_PKCS8_PRIVATE_KEY
#if defined (USE_PKCS8_PRIVATE_KEY)
  BIO* bp = BIO_new_mem_buf((void*)data, (int)datalen);
  if (bp == 0) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyData: error creating memory buffer...");
    return 0;
  }
  OpenSSL_add_all_algorithms();

	EVP_PKEY* key;
  PKCS8_PRIV_KEY_INFO* p8inf = d2i_PKCS8_PRIV_KEY_INFO_bio(bp, NULL);
  BIO_free(bp);
  if (p8inf == 0) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyData: error getting key...");
    return 0;
  }
  key = EVP_PKCS82PKEY(p8inf);
  PKCS8_PRIV_KEY_INFO_free(p8inf);

//  EVP_PKEY* key = PEM_read_bio_PrivateKey/*d2i_PKCS8PrivateKey_bio*/(bp, NULL, /*pem_password_cb *cb*/NULL, /*void *u*/NULL);
//  ERR_load_ERR_strings();
//  unsigned long lerr = ERR_peek_last_error();
//  const char* lerr_string = ERR_reason_error_string(lerr);
#else
  EVP_PKEY* key = d2i_AutoPrivateKey(NULL, &data, datalen);
#endif // USE_PKCS8_PRIVATE_KEY
  if (key == 0) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyData: error parsing key...");
    return 0;
  }
  if (key->pkey.rsa == 0) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyData: error in key...");
    EVP_PKEY_free(key);
    return 0;
  }

  try {
    return new RSAMD5OpenSSLPublicDecryptorSigner(key);
  }
  catch (PublicCryptoException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyData: unknown exception...");
    return 0;
  }
}

/*! \brief  Parse public key decryptor from a key file.

    \param  fname       input, file name.
    \param  logger	input, message logger.

    \returns  New public key decryptor. If fails, 0.
*/
IPublicDecryptor* PublicCryptoFactory::ParsePublicDecryptorFromKeyFile(
    const std::string& fname, DRMLogger& logger) {
  return ParsePublicDecryptorSignerFromKeyFile(fname, logger);
}

/*! \brief  Parse public key decryptor and signer from a key file.

    \param  fname       input, file name.
    \param  logger	input, message logger.

    \returns  New public key signer. If fails, 0.
*/
IPublicSigner* PublicCryptoFactory::ParsePublicSignerFromKeyFile(
    const std::string& fname, DRMLogger& logger) {
  return ParsePublicDecryptorSignerFromKeyFile(fname, logger);
}

/*! \brief  Parse public key decryptor and signer from a key file.

    \param  fname       input, file name.
    \param  logger	input, message logger.

    \returns  New public key decryptor and signer. If fails, 0.
*/
IPublicDecryptorSigner* PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyFile(
    const std::string& fname, DRMLogger& logger) {
  FILE* fp = fopen(fname.data(), "rb");
  if (fp == NULL) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyFile: cannot open " + fname + "...");
    return 0;
  }
  struct stat tstat;
  stat(fname.data(), &tstat);
  unsigned int byteslen = tstat.st_size;
  ByteT* bytes = (ByteT*)malloc(byteslen);
  fread(bytes, byteslen, 1, fp);
  fclose(fp);
  IPublicDecryptorSigner* ret = ParsePublicDecryptorSignerFromKeyData(bytes, byteslen, logger);
  free(bytes);
  return ret;
}

/*! \brief  Get new certificate verifier.

    \param  logger	input, message logger.

    \returns  New certificate verifier. If fails, 0.
*/
ICertVerifier* PublicCryptoFactory::GetCertificateVerifier(DRMLogger& logger) {
  return new OpenSSLCertVerifier(logger);
}

/*! \brief  Parse public key encryptor certificate from certificate data.

    \param  data        input, data.
    \param  datalen     input, data length.
    \param  logger	input, message logger.

    \returns  New public key encryptor certificate. If fails, 0.
*/
IPublicEncryptorCertificate* PublicCryptoFactory::ParsePublicEncryptorCertificateFromData(ByteT* data, unsigned int datalen, DRMLogger& logger) {
  return ParsePublicEncryptorVerifierCertificateFromData(data, datalen, logger);
}

/*! \brief  Parse public key encryptor certificate from a certificate file.

    \param  fname       input, file name.
    \param  logger	input, message logger.

    \returns  New public key encryptor certificate. If fails, 0.
*/
IPublicEncryptorCertificate* PublicCryptoFactory::ParsePublicEncryptorCertificateFromFile(const std::string& fname, DRMLogger& logger) {
  return ParsePublicEncryptorVerifierCertificateFromFile(fname, logger);
}

/*! \brief  Parse public key verifier certificate from certificate data.

    \param  data        input, data.
    \param  datalen     input, data length.
    \param  logger	input, message logger.

    \returns  New public key verifier certificate. If fails, 0.
*/
IPublicVerifierCertificate* PublicCryptoFactory::ParsePublicVerifierCertificateFromData(ByteT* data, unsigned int datalen, DRMLogger& logger) {
  return ParsePublicEncryptorVerifierCertificateFromData(data, datalen, logger);
}

/*! \brief  Parse public key verifier certificate from a certificate file.

    \param  fname       input, file name.
    \param  logger	input, message logger.

    \returns  New public key verifier certificate. If fails, 0.
*/
IPublicVerifierCertificate* PublicCryptoFactory::ParsePublicVerifierCertificateFromFile(const std::string& fname, DRMLogger& logger) {
  return ParsePublicEncryptorVerifierCertificateFromFile(fname, logger);
}

/*! \brief  Parse public key encryptor and verifier certificate from certificate data.

    \param  data        input, data.
    \param  datalen     input, data length.
    \param  logger	input, message logger.

    \returns  New public key encryptor and verifier certificate. If fails, 0.
*/
IPublicEncryptorVerifierCertificate* PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData(ByteT* data, unsigned int datalen, DRMLogger& logger) {
  X509* cert = ParseX509CertFromData(data, datalen);
  if (cert == 0) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData: cannot parse certificate...");
    return 0;
  }
  ByteT* kdata = cert->cert_info->key->public_key->data;
  EVP_PKEY* pubkey = d2i_PublicKey(EVP_PKEY_RSA, NULL, &kdata,
    cert->cert_info->key->public_key->length);
  if (pubkey == 0) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData: cannot parse public key...");
    X509_free(cert);
    return 0;
  }
  if (pubkey->pkey.rsa == 0) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData: public key error...");
    EVP_PKEY_free(pubkey);
    X509_free(cert);
    return 0;
  }

  try {
    return new X509OpenSSLPublicEncryptorVerifierCertificate(pubkey, cert);
  }
  catch(PublicCryptoException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData: unknown exception...");
    return 0;
  }
}

/*! \brief  Parse public key encryptor and verifier certificate from a certificate file.

    \param  fname       input, file name.
    \param  logger	input, message logger.

    \returns  New public key encryptor and verifier certificate. If fails, 0.
*/
IPublicEncryptorVerifierCertificate* PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromFile(const std::string& fname, DRMLogger& logger) {
  FILE* fp = fopen(fname.data(), "rb");
  if (fp == NULL) {
    logger.UpdateLog("PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromFile: cannot open " + fname + "...");
    return 0;
  }
  struct stat tstat;
  stat(fname.data(), &tstat);
  unsigned int byteslen = tstat.st_size;
  ByteT* bytes = (ByteT*)malloc(byteslen);
  fread(bytes, byteslen, 1, fp);
  fclose(fp);
  IPublicEncryptorVerifierCertificate* ret =
    ParsePublicEncryptorVerifierCertificateFromData(bytes, byteslen, logger);
  free(bytes);
  return ret;
}

} // namespace DRMPlugin
