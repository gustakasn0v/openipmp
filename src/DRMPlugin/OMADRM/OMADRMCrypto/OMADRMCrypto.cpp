/** \file OMADRMCrypto.cpp

    OMA DRM crypto implementations.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMCrypto.h"
#include "Base64Factory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    \param  hsher     hasher.

    If fails, throws OMADRMCryptoException.
*/
OMADRMHasher::OMADRMHasher(IHasher* hsher): hasher(hsher) {
  if (hasher == 0) {
    throw OMADRMCryptoException();
  }
}

OMADRMHasher::~OMADRMHasher() {
  if (hasher != 0) delete hasher; hasher = 0;
}

/*! \brief  Calculate hash.

    \param  data          input, data to be hashed.
    \param  hash          output, hash of data.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMHasher::Hash(const ByteSeq& data, ByteSeq& hash) {
  return hasher->Hash(data, hash);
}

/*! \brief  Calculate hash.

    \param  data          input, data to be hashed.
    \param  hash          output, hash of data.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMHasher::Hash(const ByteSeq& data, Base64StringT& hash) {
  ByteSeq hhash;
  if (Hash(data, hhash) == false) {
    return false;
  }
  return Base64Factory::Encode(hhash, hash);
}

/*! \brief  Constructor.

    \param  cert      encryptor and verifier certificate.

    If fails, throws OMADRMCryptoException.
*/
OMAPublicCertificate::OMAPublicCertificate(IPublicEncryptorVerifierCertificate* cert): certificate(cert) {
  if (certificate == 0) {
    throw OMADRMCryptoException();
  }
}

OMAPublicCertificate::~OMAPublicCertificate() {
  if (certificate != 0) delete certificate; certificate = 0;
}

/*! \brief  Verify signature.

    \param  sigValue        input, signature value.
    \param  data            input, signed data.

    \returns  Boolean indicating success or failure.
*/
bool OMAPublicCertificate::Verify(const Base64StringT& sigValue, const ByteSeq& data) {
  ByteSeq sig;
  if (Base64Factory::Decode(sigValue, sig) == false) {
    return false;
  }
  return certificate->GetPublicEncryptorVerifier()->Verify(data, sig);
}

/*! \brief  Encrypt data.

    \param  data            input, data to encrypt.
    \param  enc             output, encrypted data.

    \returns  Boolean indicating success or failure.
*/
bool OMAPublicCertificate::Encrypt(const ByteSeq& data, Base64StringT& enc) {
  ByteSeq encc;
  if (certificate->GetPublicEncryptorVerifier()->Encrypt(data, encc) == false) {
    return false;
  }
  return Base64Factory::Encode(encc, enc);
}

/*! \brief  Encrypt data.

    \param  data            input, data to encrypt.
    \param  enc             output, encrypted data.

    \returns  Boolean indicating success or failure.
*/
bool OMAPublicCertificate::Encrypt(const Base64StringT& data, Base64StringT& enc) {
  ByteSeq dta;
  if (Base64Factory::Decode(data, dta) == false) {
    return false;
  }
  return Encrypt(dta, enc);
}

/*! \brief  Get key identifier.

    \param  hsher         input, hash calculator.
    \param  id            output, key identifier string.

    \returns  Boolean indicating success or failure.
*/
bool OMAPublicCertificate::GetKeyIdentifier(const NZSPtr<OMADRMHasher>& hsher,
    Base64StringT& id) {
  ByteSeq enc;
  if (((IPublicEncryptor*)certificate->GetPublicEncryptorVerifier())->Encode(enc) == false) {
    return false;
  }
  return hsher->Hash(enc, id);
}

/*! \brief  Encode as base64 string.

    \param  encoded       output, encoded base64 string.

    \returns  Boolean indicating success or failure.
*/
bool OMAPublicCertificate::Encode(Base64StringT& encoded) {
  ByteSeq der;
  if (((IPublicEncryptorCertificate*)certificate)->Encode(der) == false) {
    return false;
  }
  return Base64Factory::Encode(der, encoded);
}

/*! \brief  Get expiration time.

    \returns  Expiration time.
*/
const TValue<UTCTime>& OMAPublicCertificate::GetExpirationTime() const {
  return ((IPublicEncryptorCertificate*)certificate)->GetExpirationTime();
}

/*! \brief  Constructor.

    \param  key     decryptor and signer.

    If fails, throws OMADRMCryptoException.
*/
OMAPrivateKey::OMAPrivateKey(IPublicDecryptorSigner* key): pkey(key) {
  if (pkey == 0) {
    throw OMADRMCryptoException();
  }
}

OMAPrivateKey::~OMAPrivateKey() {
  if (pkey != 0) delete pkey; pkey = 0;
}

/*! \brief  Sign data.

    \param  data            input, data to be signed.
    \param  sig             output, signature data.

    \returns  Boolean indicating success or failure.
*/
bool OMAPrivateKey::Sign(const ByteSeq& data, Base64StringT& sig) {
  ByteSeq ssig;
  if (pkey->Sign(data, ssig) == false) {
    return false;
  }
  return Base64Factory::Encode(ssig, sig);
}

/*! \brief  Decrypt data.

    \param  data            input, data to decrypt.
    \param  dec             output, decrypted data.

    \returns  Boolean indicating success or failure.
*/
bool OMAPrivateKey::Decrypt(const Base64StringT& data, ByteSeq& dec) {
  ByteSeq dta;
  if (Base64Factory::Decode(data, dta) == false) {
    return false;
  }
  return pkey->Decrypt(dta, dec);
}

/*! \brief  Encode as base64 string.

    \param  encoded       output, encoded base64 string.

    \returns  Boolean indicating success or failure.
*/
bool OMAPrivateKey::Encode(Base64StringT& encoded) {
  ByteSeq enc;
  if (((IPublicDecryptor*)pkey)->Encode(enc) == false) {
    return false;
  }
  return Base64Factory::Encode(enc, encoded);
}

/*! \brief  Constructor.

    \param  ver     certificate verifier.

    If fails, throws OMADRMCryptoException.
*/
OMACertificateVerifier::OMACertificateVerifier(ICertVerifier* ver): verifier(ver) {
  if (verifier == 0) {
    throw OMADRMCryptoException();
  }
}

OMACertificateVerifier::~OMACertificateVerifier() {
  if (verifier != 0) delete verifier; verifier = 0;
}

/*! \brief  Get certificate from chain, without verification.

    \warning  OMA DRM specifies reverse order of the certificates in a chain.
              Thus, first certificate is the one to get.

    \param  chain       input, certificate chain.

    \returns  Certificate. If zero, failed.
*/
SPtr<OMAPublicCertificate> OMACertificateVerifier::GetCertificate(const NZSPtr<ROAPCertificateChain>& chain) {
  const std::vector<Base64StringT>& certs = chain->GetCertificates();
  if (certs.size() == 0) {
    return 0;
  }
  //  Decode from base64.
  ByteSeq data;
  if (Base64Factory::Decode(certs[0], data) == false) {
    return 0;
  }
  try {
    return new OMAPublicCertificate(verifier->GetEncryptorVerifierCertificate(data));
  }
  catch (OMADRMCryptoException) {
    return 0;
  }
}

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
SPtr<OMAPublicCertificate> OMACertificateVerifier::VerifyChain(const Base64StringT& root,
    const NZSPtr<ROAPCertificateChain>& chain) {
  //  Decode from base64.
  ByteSeq cert;
  if (Base64Factory::Decode(root, cert) == false) {
    return 0;
  }
  std::vector<ByteSeq> cchain;
  int i = (chain->GetCertificates().size() - 1);
  for (; i >= 0; i--) {
    ByteSeq ccert;
    Base64StringT b64 = chain->GetCertificates()[i];
    if (Base64Factory::Decode(b64, ccert) == false) {
      return 0;
    }
    cchain.push_back(ccert);
  }
  try {
    return new OMAPublicCertificate(verifier->VerifyChainGetEncryptorVerifierCertificate(cert, cchain));
  }
  catch (OMADRMCryptoException) {
    return 0;
  }
}

static std::string nonce = "nonce of length >= 14";

/*! \brief  Create a nonce.

    \returns  Nonce.
*/
NZSPtr<ROAPNonce> OMADRMNonceCreator::CreateNonce() {
  nonce = nonce + "a";
  Base64StringT tmp;
  Base64Factory::Encode(ByteSeq((ByteT*)nonce.data(), nonce.size()), tmp);
  return new ROAPNonce(tmp);
}

} // namespace DRMPlugin
