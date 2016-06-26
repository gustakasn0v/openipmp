/**	\file OpenSSLPublicCrypto.h

	OpenSSL public crypto implementations.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENSSLPUBLICCRYPTO_H)
#define OPENSSLPUBLICCRYPTO_H

#include "IPublicCrypto.h"
#include "DRMLogger.h"
#include "openssl/x509.h"
#include "openssl/engine.h"
#include "openssl/evp.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Parse X509 certificate from input data.

    \param  data        input, data.
    \param  datalen     input, data length.

    \returns  New X509 structure. If fails, 0.
*/
X509* ParseX509CertFromData(ByteT* data, unsigned int datalen);

/*! \brief  Parse X509 certificate from a file.

    \param  fname       input, file name.

    \returns  New X509 structure. If fails, 0.
*/
X509* ParseX509CertFromFile(const std::string& fname);

/*! \brief  MD5 hash calculator.
*/
class MD5OpenSSLHasher: public IHasher {
public:
  virtual ~MD5OpenSSLHasher() {
  }

  /*! \brief  Calculate hash.

      \param  data          input, data to be hashed.
      \param  hash          output, hash of data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Hash(const ByteSeq& data, ByteSeq& hash);
};

/*! \brief  SHA1 hash calculator.
*/
class SHA1OpenSSLHasher: public IHasher {
public:
  virtual ~SHA1OpenSSLHasher() {
  }

  /*! \brief  Calculate hash.

      \param  data          input, data to be hashed.
      \param  hash          output, hash of data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Hash(const ByteSeq& data, ByteSeq& hash);
};

/*! \brief  RSAMD5 public key encryptor and verifier.
*/
class RSAMD5OpenSSLPublicEncryptorVerifier: public IPublicEncryptorVerifier {
public:
  /*! \brief  Constructor.

      \param  key       public key.

      If fails, throws PublicCryptoException.
  */
  RSAMD5OpenSSLPublicEncryptorVerifier(EVP_PKEY* key);

  virtual ~RSAMD5OpenSSLPublicEncryptorVerifier();

  /*! \brief  Encode as byte array.

      \param  out         output, encoded data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encode(ByteSeq& out);

  /*! \brief  Encrypt data.

      \param  in          input, data to encrypt.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out);

  /*! \brief  Get hash calculator.

      \returns  Hash calculator.
  */
  virtual IHasher* GetHasher();

  /*! \brief  Verify signature.

      \param  in          input, data to verify.
      \param  sig         input, signature data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Verify(const ByteSeq& in, const ByteSeq& sig);

private:
  EVP_PKEY* pkey;
  MD5OpenSSLHasher* hasher;
};

/*! \brief  RSAMD5 public key decryptor and signer.
*/
class RSAMD5OpenSSLPublicDecryptorSigner: public IPublicDecryptorSigner {
public:
  /*! \brief  Constructor.

      \param  key       public key.

      If fails, throws PublicCryptoException.
  */
  RSAMD5OpenSSLPublicDecryptorSigner(EVP_PKEY* key);

  virtual ~RSAMD5OpenSSLPublicDecryptorSigner();

  /*! \brief  Encode as byte array.

      \param  out         output, encoded data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encode(ByteSeq& out);

  /*! \brief  Encrypt data.

      \param  in          input, data to encrypt.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out);

  /*! \brief  Decrypt data.

      \param  in          input, data to decrypt.
      \param  out         output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Decrypt(const ByteSeq& in, ByteSeq& out);

  /*! \brief  Get hash calculator.

      \returns  Hash calculator.
  */
  virtual IHasher* GetHasher();

  /*! \brief  Verify signature.

      \param  in          input, data to verify.
      \param  sig         input, signature data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Verify(const ByteSeq& in, const ByteSeq& sig);

  /*! \brief  Create signature.

      \param  in          input, data to sign.
      \param  sig         output, signature data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Sign(const ByteSeq& in, ByteSeq& sig);

private:
  EVP_PKEY* pkey;
  MD5OpenSSLHasher* hasher;
};

/*! \brief  Certificate verifier.

    Verifies certificate chains, gets verified certificates.
*/
class OpenSSLCertVerifier: public ICertVerifier {
public:
  /*!	\brief  Constructor.

      	\param		logger		message logger.
  */
  OpenSSLCertVerifier(DRMLogger& logger);

  virtual ~OpenSSLCertVerifier() {
  }

  /*! \brief  Get public key encryptor certificate.
  
      \param  cert        input, certificate data.

      \returns  Public key encryptor certificate. If zero, failed.
  */
  virtual IPublicEncryptorCertificate* GetEncryptorCertificate(const ByteSeq& cert);

  /*! \brief  Get public key verifier certificate.
  
      \param  cert        input, certificate data.

      \returns  Public key verifier certificate. If zero, failed.
  */
  virtual IPublicVerifierCertificate* GetVerifierCertificate(const ByteSeq& cert);

  /*! \brief  Get public key encryptor and verifier certificate.
  
      \param  cert        input, certificate data.

      \returns  Public key encryptor and verifier certificate. If zero, failed.
  */
  virtual IPublicEncryptorVerifierCertificate* GetEncryptorVerifierCertificate(
    const ByteSeq& cert);

  /*! \brief  Verify certificate chain.
  
      Assume that the chain starts with a certificate issued by root.
      If successful, return encryptor certificate from the last certificate.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, ending with certificate
                          to verify.

      \returns  Verified public key encryptor certificate. If zero, failed.
  */
  virtual IPublicEncryptorCertificate* VerifyChainGetEncryptorCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain);

  /*! \brief  Verify certificate chain.
  
      Assume that the chain starts with a certificate issued by root.
      If successful, return verifier certificate from the last certificate.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, ending with certificate
                          to verify.

      \returns  Verified public key verifier certificate. If zero, failed.
  */
  virtual IPublicVerifierCertificate* VerifyChainGetVerifierCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain);

  /*! \brief  Verify certificate chain.
  
      Assume that the chain starts with a certificate issued by root.
      If successful, return encryptor and verifier certificate from the
      last certificate.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, ending with certificate
                          to verify.

      \returns  Verified public key encryptor and verifier certificate. If zero, failed.
  */
  virtual IPublicEncryptorVerifierCertificate* VerifyChainGetEncryptorVerifierCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain);

  /*! \brief  Verify certificate chain.
  
      Assume that the chain starts with a certificate issued by root.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, ending with certificate
                          to verify.

      \returns  Boolean indicating success or failure.
  */
  virtual bool VerifyChain(const ByteSeq& root, const std::vector<ByteSeq>& chain);

private:
  DRMLogger& verifierLogger;
};

/*! \brief  X509 certificate with public encryptor and verifier.
*/
class X509OpenSSLPublicEncryptorVerifierCertificate: public IPublicEncryptorVerifierCertificate {
public:
  /*! \brief  Constructor.

      \param  pk          public key.
      \param  cert        X509 certificate.

      If fails, throws PublicCryptoException.
  */
  X509OpenSSLPublicEncryptorVerifierCertificate(EVP_PKEY* pk, X509* cert);

  virtual ~X509OpenSSLPublicEncryptorVerifierCertificate();

  /*! \brief  Encode as byte array.

      \param  out         output, encoded data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encode(ByteSeq& out);

  /*! \brief  Get expiration time.

      \returns  Expiration time.
  */
  virtual const TValue<UTCTime>& GetExpirationTime() const;

  /*! \brief  Get public encryptor and verifier.

      \returns  Public encryptor and verifier.
  */
  virtual IPublicEncryptorVerifier* GetPublicEncryptorVerifier();

private:
  IPublicEncryptorVerifier* encver;
  FiniteTValue<UTCTime> expiration;
  X509* certificate;
};

} // namespace DRMPlugin

#endif // !defined (OPENSSLPUBLICCRYPTO_H)
