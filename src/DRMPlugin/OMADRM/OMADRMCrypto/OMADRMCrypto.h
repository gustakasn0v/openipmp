/** \file OMADRMCrypto.h

    OMA DRM crypto implementations.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMCRYPTO_H)
#define OMADRMCRYPTO_H

#include "ROAPMessages.h"
#include "IPublicCrypto.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for OMA DRM crypto error.
*/
class OMADRMCryptoException {
};

/*! \brief  Hash calculator.
*/
class OMADRMHasher: public GC {
public:
  /*! \brief  Constructor.

      \param  hsher     hasher.

      If fails, throws OMADRMCryptoException.
  */
  OMADRMHasher(IHasher* hsher);

  ~OMADRMHasher();

  /*! \brief  Calculate hash.

      \param  data          input, data to be hashed.
      \param  hash          output, hash of data.

      \returns  Boolean indicating success or failure.
  */
  bool Hash(const ByteSeq& data, ByteSeq& hash);

  /*! \brief  Calculate hash.

      \param  data          input, data to be hashed.
      \param  hash          output, hash of data.

      \returns  Boolean indicating success or failure.
  */
  bool Hash(const ByteSeq& data, Base64StringT& hash);

private:
  IHasher* hasher;
};

/*! \brief  Public certificate. Verifies signatures and encrypts data.

    Uses IPublicEncryptorVerifierCertificate.
*/
class OMAPublicCertificate: public GC {
public:
  /*! \brief  Constructor.

      \param  cert      encryptor and verifier certificate.

      If fails, throws OMADRMCryptoException.
  */
  OMAPublicCertificate(IPublicEncryptorVerifierCertificate* cert);

  ~OMAPublicCertificate();

  /*! \brief  Verify signature.

      \param  sigValue        input, signature value.
      \param  data            input, signed data.

      \returns  Boolean indicating success or failure.
  */
  bool Verify(const Base64StringT& sigValue, const ByteSeq& data);

  /*! \brief  Encrypt data.

      \param  data            input, data to encrypt.
      \param  enc             output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  bool Encrypt(const ByteSeq& data, Base64StringT& enc);

  /*! \brief  Encrypt data.

      \param  data            input, data to encrypt.
      \param  enc             output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  bool Encrypt(const Base64StringT& data, Base64StringT& enc);

  /*! \brief  Get key identifier.

      \param  hsher         input, hash calculator.
      \param  id            output, key identifier string.

      \returns  Boolean indicating success or failure.
  */
  bool GetKeyIdentifier(const NZSPtr<OMADRMHasher>& hsher, Base64StringT& id);

  /*! \brief  Encode as base64 string.

      \param  encoded       output, encoded base64 string.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(Base64StringT& encoded);

  /*! \brief  Get expiration time.

      \returns  Expiration time.
  */
  const TValue<UTCTime>& GetExpirationTime() const;

private:
  IPublicEncryptorVerifierCertificate* certificate;
};

/*! \brief  Private key. Signs and decrypts data.
*/
class OMAPrivateKey: public GC {
public:
  /*! \brief  Constructor.

      \param  key     decryptor and signer.

      If fails, throws OMADRMCryptoException.
  */
  OMAPrivateKey(IPublicDecryptorSigner* key);

  ~OMAPrivateKey();

  /*! \brief  Sign data.

      \param  data            input, data to be signed.
      \param  sig             output, signature data.

      \returns  Boolean indicating success or failure.
  */
  bool Sign(const ByteSeq& data, Base64StringT& sig);

  /*! \brief  Decrypt data.

      \param  data            input, data to decrypt.
      \param  dec             output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  bool Decrypt(const Base64StringT& data, ByteSeq& dec);

  /*! \brief  Encode as base64 string.

      \param  encoded       output, encoded base64 string.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(Base64StringT& encoded);

private:
  IPublicDecryptorSigner* pkey;
};

/*! \brief  Certificate verifier. Verifies certificate chains, gets verified certificates.
*/
class OMACertificateVerifier: public GC {
public:
  /*! \brief  Constructor.

      \param  ver     certificate verifier.

      If fails, throws OMADRMCryptoException.
  */
  OMACertificateVerifier(ICertVerifier* ver);

  ~OMACertificateVerifier();

  /*! \brief  Get certificate from chain, without verification.
  
      \warning  OMA DRM specifies reverse order of the certificates in a chain.
                Thus, first certificate is the one to get.

      \param  chain       input, certificate chain.

      \returns  Certificate. If zero, failed.
  */
  SPtr<OMAPublicCertificate> GetCertificate(const NZSPtr<ROAPCertificateChain>& chain);

  /*! \brief  Verify certificate chain.
  
      \warning  OMA DRM specifies reverse order of the certificates in a chain.
                Thus, first certificate is the one to verify, and every other is
                certified by the following one. Last certificate is certified
                by the root.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, starting with the
                          certificate to verify.

      \returns  Verified certificate. If zero, failed.
  */
  SPtr<OMAPublicCertificate> VerifyChain(const Base64StringT& root,
    const NZSPtr<ROAPCertificateChain>& chain);

private:
  ICertVerifier* verifier;
};

/*! \brief  Nonce creator.
*/
class OMADRMNonceCreator: public GC {
public:
  virtual ~OMADRMNonceCreator() {
  }

  /*! \brief  Create a nonce.

      \returns  Nonce.
  */
  virtual NZSPtr<ROAPNonce> CreateNonce();
};

} // namespace DRMPlugin

#endif // !defined (OMADRMCRYPTO_H)
