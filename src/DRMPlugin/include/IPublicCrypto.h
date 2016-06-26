/**	\file IPublicCrypto.h

	 Public crypto interfaces.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPUBLICCRYPTO_H)
#define IPUBLICCRYPTO_H

#include "BasicTypes.h"
#include <vector>
#include "Value.h"
#include "UTCTime.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for public crypto error.
*/
class PublicCryptoException {
};

/*! \brief  Hash calculator.
*/
class IHasher {
public:
  virtual ~IHasher() {
  }

  /*! \brief  Calculate hash.

      \param  data          input, data to be hashed.
      \param  hash          output, hash of data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Hash(const ByteSeq& data, ByteSeq& hash) = 0;
};

/*! \brief  Public key primitive.
*/
class IPublicPrimitive {
public:
  virtual ~IPublicPrimitive() {
  }

  /*! \brief  Encode as byte array.

      \param  out         output, encoded data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encode(ByteSeq& out) = 0;
};

/*! \brief  Public key encryptor.
*/
class IPublicEncryptor: public IPublicPrimitive {
public:
  virtual ~IPublicEncryptor() {
  }

  /*! \brief  Encrypt data.

      \param  in          input, data to encrypt.
      \param  out         output, encrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Encrypt(const ByteSeq& in, ByteSeq& out) = 0;
};

/*! \brief  Public key verifier.
*/
class IPublicVerifier: public IPublicPrimitive {
public:
  virtual ~IPublicVerifier() {
  }

  /*! \brief  Get hash calculator.

      \returns  Hash calculator.
  */
  virtual IHasher* GetHasher() = 0;

  /*! \brief  Verify signature.

      \param  in          input, data to verify.
      \param  sig         input, signature data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Verify(const ByteSeq& in, const ByteSeq& sig) = 0;
};

/*! \brief  Public key encryptor and verifier.
*/
class IPublicEncryptorVerifier: public IPublicEncryptor, public IPublicVerifier {
public:
  virtual ~IPublicEncryptorVerifier() {
  }
};

/*! \brief  Public key decryptor.
*/
class IPublicDecryptor: public IPublicEncryptor {
public:
  virtual ~IPublicDecryptor() {
  }

  /*! \brief  Decrypt data.

      \param  in          input, data to decrypt.
      \param  out         output, decrypted data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Decrypt(const ByteSeq& in, ByteSeq& out) = 0;
};

/*! \brief  Public key signer.
*/
class IPublicSigner: public IPublicVerifier {
public:
  virtual ~IPublicSigner() {
  }

  /*! \brief  Create signature.

      \param  in          input, data to sign.
      \param  sig         output, signature data.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Sign(const ByteSeq& in, ByteSeq& sig) = 0;
};

/*! \brief  Public key decryptor and signer.
*/
class IPublicDecryptorSigner: public IPublicEncryptorVerifier, public
  IPublicDecryptor, public IPublicSigner {
public:
  virtual ~IPublicDecryptorSigner() {
  }
};

/*! \brief  Certificate.
*/
class ICertificate: public IPublicPrimitive {
public:
  virtual ~ICertificate() {
  }

  /*! \brief  Get expiration time.

      \returns  Expiration time.
  */
  virtual const TValue<UTCTime>& GetExpirationTime() const = 0;
};

/*! \brief  Certificate with public encryptor.
*/
class IPublicEncryptorCertificate: public ICertificate {
public:
  virtual ~IPublicEncryptorCertificate() {
  }

  /*! \brief  Get public encryptor.

      \returns  Public encryptor.
  */
  virtual IPublicEncryptor* GetPublicEncryptor() = 0;
};

/*! \brief  Certificate with public verifier.
*/
class IPublicVerifierCertificate: public ICertificate {
public:
  virtual ~IPublicVerifierCertificate() {
  }

  /*! \brief  Get public verifier.

      \returns  Public verifier.
  */
  virtual IPublicVerifier* GetPublicVerifier() = 0;
};

/*! \brief  Certificate with public encryptor and verifier.
*/
class IPublicEncryptorVerifierCertificate: public IPublicEncryptorCertificate,
    public IPublicVerifierCertificate {
public:
  virtual ~IPublicEncryptorVerifierCertificate() {
  }

  /*! \brief  Get public encryptor.

      \returns  Public encryptor.
  */
  virtual IPublicEncryptor* GetPublicEncryptor() {
    return GetPublicEncryptorVerifier();
  }

  /*! \brief  Get public verifier.

      \returns  Public verifier.
  */
  virtual IPublicVerifier* GetPublicVerifier() {
    return GetPublicEncryptorVerifier();
  }

  /*! \brief  Get public encryptor and verifier.

      \returns  Public encryptor and verifier.
  */
  virtual IPublicEncryptorVerifier* GetPublicEncryptorVerifier() = 0;
};

/*! \brief  Certificate verifier.

    Verifies certificate chains, gets verified certificates.
*/
class ICertVerifier {
public:
  virtual ~ICertVerifier() {
  }

  /*! \brief  Get public key encryptor certificate.
  
      \param  cert        input, certificate data.

      \returns  Public key encryptor certificate. If zero, failed.
  */
  virtual IPublicEncryptorCertificate* GetEncryptorCertificate(const ByteSeq& cert) = 0;

  /*! \brief  Get public key verifier certificate.
  
      \param  cert        input, certificate data.

      \returns  Public key verifier certificate. If zero, failed.
  */
  virtual IPublicVerifierCertificate* GetVerifierCertificate(const ByteSeq& cert) = 0;

  /*! \brief  Get public key encryptor and verifier certificate.
  
      \param  cert        input, certificate data.

      \returns  Public key encryptor and verifier certificate. If zero, failed.
  */
  virtual IPublicEncryptorVerifierCertificate* GetEncryptorVerifierCertificate(
    const ByteSeq& cert) = 0;

  /*! \brief  Verify certificate chain.
  
      Assume that the chain starts with a certificate issued by root.
      If successful, return encryptor certificate from the last certificate.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, ending with certificate
                          to verify.

      \returns  Verified public key encryptor certificate. If zero, failed.
  */
  virtual IPublicEncryptorCertificate* VerifyChainGetEncryptorCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain) = 0;

  /*! \brief  Verify certificate chain.
  
      Assume that the chain starts with a certificate issued by root.
      If successful, return verifier certificate from the last certificate.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, ending with certificate
                          to verify.

      \returns  Verified public key verifier certificate. If zero, failed.
  */
  virtual IPublicVerifierCertificate* VerifyChainGetVerifierCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain) = 0;

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
    const ByteSeq& root, const std::vector<ByteSeq>& chain) = 0;

  /*! \brief  Verify certificate chain.
  
      Assume that the chain starts with a certificate issued by root.

      \param  root        input, root certificate.
      \param  chain       input, certificate chain, ending with certificate
                          to verify.

      \returns  Boolean indicating success or failure.
  */
  virtual bool VerifyChain(const ByteSeq& root, const std::vector<ByteSeq>& chain) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IPUBLICCRYPTO_H)
