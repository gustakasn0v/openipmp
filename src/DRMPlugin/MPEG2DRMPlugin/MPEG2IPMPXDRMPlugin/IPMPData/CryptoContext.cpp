/**	\file CryptoContext.cpp

	Crypto contexts, with the keys, algorithms, etc.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "CryptoContext.h"

#include "BasicTypes.h"
#include "CryptoProvider.h"
#include "Authenticator.h"
#include <vector>
#include "ISigCertContainer.h"
#include "IPMPData.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Trust security metadata IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool TrustSecurityMetadataIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x18, enc, encoded);
}

/*! \brief  Create a new copy of this metadata.

    \returns  A new copy of this metadata.
*/
TrustSecurityMetadataIPMPData* TrustSecurityMetadataIPMPData::Copy() const {
  return new TrustSecurityMetadataIPMPData(version, dataID);
}

/*! \brief  Base authentication descriptor.
*/
/*! \brief  Encode as byte array.

    Encode tag, expandable size and class data.

    \param  tag           input, class tag.
    \param  data          input, class data.
    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool BaseAuthenticationDescriptor::MPEG2Encode(const ByteT& tag, const ByteSeq& data,
    ByteSeq& encoded) const {
  if ((data.GetLength() + 1) >= (1 << 28)) {
    return false;
  }
  encoded = ByteSeq(tag) + data.MPEG2Encode();
  return true;
}

/*! \brief  Key authentication descriptor.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool KeyDescriptor::MPEG2Encode(ByteSeq& encoded) const {
  return BaseAuthenticationDescriptor::MPEG2Encode(0x02, keyBody.MPEG2Encode(),
    encoded);
}

/*! \brief  Get key body.

    \returns Key body.
*/
const ByteSeq& KeyDescriptor::GetKeyBody() const {
  return keyBody;
}

/*! \brief  Algorithm authentication descriptor.
*/
/*! \brief  Get opaque data.

    \returns Opaque data.
*/
const ByteSeq& AlgorithmDescriptor::GetOpaqueData() const {
  return opaqueData;
}

/*! \brief  Registered algorithm authentication descriptor.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool RegAlgorithmDescriptor::MPEG2Encode(ByteSeq& encoded) const {
  return BaseAuthenticationDescriptor::MPEG2Encode(0x01, ByteSeq((ByteT)0x80) +
    ByteSeq(regAlgoID) + opaqueData.MPEG2Encode(), encoded);
}

/*! \brief  Create a new copy of this algorithm descriptor.

    \return The new copy of this algorithm descriptor.
*/
AlgorithmDescriptor* RegAlgorithmDescriptor::Copy() const {
  return new RegAlgorithmDescriptor(opaqueData, regAlgoID);
}

/*! \brief  Get algorithm identifier.

    \returns  Algorithm identifier.
*/
ByteSeq RegAlgorithmDescriptor::GetAlgorithmID() const {
  //  Here should be a table lookup to find real identifier from registered code.
  return ByteSeq(regAlgoID);
}

/*! \brief  Get registered algorithm identifier.

    \returns Registered algorithm identifier.
*/
const Bit16T& RegAlgorithmDescriptor::GetRegAlgoID() const {
  return regAlgoID;
}

/*! \brief  Non-registered algorithm authentication descriptor.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool NRegAlgorithmDescriptor::MPEG2Encode(ByteSeq& encoded) const {
  return BaseAuthenticationDescriptor::MPEG2Encode(0x01, ByteSeq((ByteT)0x00) +
    specAlgoID.MPEG2Encode() + opaqueData.MPEG2Encode(), encoded);
}

/*! \brief  Create a new copy of this algorithm descriptor.

    \return The new copy of this algorithm descriptor.
*/
AlgorithmDescriptor* NRegAlgorithmDescriptor::Copy() const {
  return new NRegAlgorithmDescriptor(opaqueData, specAlgoID);
}

/*! \brief  Get algorithm identifier.

    \returns  Algorithm identifier.
*/
ByteSeq NRegAlgorithmDescriptor::GetAlgorithmID() const {
  return specAlgoID;
}

/*! \brief  Get special algorithm identifier.

    \returns Special algorithm identifier.
*/
const ByteSeq& NRegAlgorithmDescriptor::GetSpecAlgoID() const {
  return specAlgoID;
}

/*! \brief  Public key crypto context with certificates.

    Creates public key verifier.
*/
/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool CertPublicVerifierContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool CertPublicVerifierContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  /*! \todo Take the key out of the certificates and pass it to the crypto
            provider.
  */
  return crypto->CreatePublicVerifier(ByteSeq(), ByteSeq(), out);
}

/*! \brief  Public (private) key crypto context.

    Creates public key verifier and signer.
*/
/*! \brief  Create public key signer.

    \param  crypto        input, crypto provider.
    \param  out           output, public key signer.

    \returns  Boolean indicating succes or failure.
*/
bool CertPublicSignerContext::CreatePublicSigner(CryptoProvider* crypto,
    PublicSigner** out) {
  /*! \todo Take the key out of the certificates and pass it to the crypto
            provider.
  */
  return crypto->CreatePublicSigner(ByteSeq(), ByteSeq(), out);
}

/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool CertPublicSignerContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool CertPublicSignerContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  /*! \todo Take the key out of the certificates and pass it to the crypto
            provider.
  */
  return crypto->CreatePublicVerifier(ByteSeq(), ByteSeq(), out);
}

/*! \brief  Private authentication context with certificates.

    Used in/for authentication protocol.
*/
/*! \brief  Get supported algorithms.

    \returns  Supported algorithms.
*/
const std::vector<AlgorithmDescriptor*>& CertPrivateAuthContext::GetSupportedAlgorithms() const {
  return algorithms;
}

/*! \brief  Get trust and security metadata.

    \returns Trust and security metadata.
*/
const TrustSecurityMetadataIPMPData* CertPrivateAuthContext::GetTrustData() const {
  return trust;
}

/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool CertPrivateAuthContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool CertPrivateAuthContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  /*! \todo Take the key out of the certificates and pass it to the crypto
            provider.
  */
  return crypto->CreatePublicVerifier(ByteSeq(), ByteSeq(), out);
}

/*! \brief  Create public key signer.

    \param  crypto        input, crypto provider.
    \param  out           output, public key signer.

    \returns  Boolean indicating succes or failure.
*/
bool CertPrivateAuthContext::CreatePublicSigner(CryptoProvider* crypto,
    PublicSigner** out) {
  /*! \todo Take the key out of the certificates and pass it to the crypto
            provider.
  */
  return crypto->CreatePublicSigner(ByteSeq(), ByteSeq(), out);
}

/*! \brief  Get certificate type.

    \returns  Certificate type.
*/
const ByteT& CertPrivateAuthContext::GetCertType() const {
  return certType;
}

/*! \brief  Get certificates.

    \returns  Certificates.
*/
const std::vector<ByteSeq>& CertPrivateAuthContext::GetCertificates() const {
  return certificates;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, public authentication context.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool CertPrivateAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const PublicAuthContext* ctx, Authenticator** auth) const {
  return ctx->CreateAuthenticator(crypto, (CertAuthContext*)this, auth);
}

/*! \brief  Create public authentication context.

    \param  ctx         output, public authentication context.

    \returns  Boolean indicating success or failure.
*/
bool CertPrivateAuthContext::CreatePublicContext(PublicAuthContext** ctx) const {
  std::vector<AlgorithmDescriptor*> algs;
  std::vector<AlgorithmDescriptor*>::const_iterator iter = algorithms.begin();
  while (iter != algorithms.end()) {
    algs.push_back((*iter)->Copy());
    iter++;
  }
  TrustSecurityMetadataIPMPData* meta = 0;
  if (trust != 0) meta = trust->Copy();
  *ctx = new CertPublicAuthContext(algs, meta, certType, certificates);

  return true;
}

/*! \brief  Private authentication context with key.

    Used in/for authentication protocol.
*/
/*! \brief  Get supported algorithms.

    \returns  Supported algorithms.
*/
const std::vector<AlgorithmDescriptor*>& KeyPrivateAuthContext::GetSupportedAlgorithms() const {
  return algorithms;
}

/*! \brief  Get trust and security metadata.

    \returns Trust and security metadata.
*/
const TrustSecurityMetadataIPMPData* KeyPrivateAuthContext::GetTrustData() const {
  return trust;
}

/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool KeyPrivateAuthContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool KeyPrivateAuthContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  return crypto->CreatePublicVerifier(ByteSeq(), key.GetKeyBody(), out);
}

/*! \brief  Create public key signer.

    \param  crypto        input, crypto provider.
    \param  out           output, public key signer.

    \returns  Boolean indicating succes or failure.
*/
bool KeyPrivateAuthContext::CreatePublicSigner(CryptoProvider* crypto,
    PublicSigner** out) {
  return crypto->CreatePublicSigner(ByteSeq(), key.GetKeyBody(), out);
}

/*! \brief  Get key descriptor.

    \returns  Key descriptor.
*/
const KeyDescriptor& KeyPrivateAuthContext::GetKeyDescriptor() const {
  return key;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, public authentication context.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool KeyPrivateAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const PublicAuthContext* ctx, Authenticator** auth) const {
  return ctx->CreateAuthenticator(crypto, (KeyAuthContext*)this, auth);
}

/*! \brief  Create public authentication context.

    \param  ctx         output, public authentication context.

    \returns  Boolean indicating success or failure.
*/
bool KeyPrivateAuthContext::CreatePublicContext(PublicAuthContext** ctx) const {
  std::vector<AlgorithmDescriptor*> algs;
  std::vector<AlgorithmDescriptor*>::const_iterator iter = algorithms.begin();
  while (iter != algorithms.end()) {
    algs.push_back((*iter)->Copy());
    iter++;
  }
  TrustSecurityMetadataIPMPData* meta = 0;
  if (trust != 0) meta = trust->Copy();
  *ctx = new KeyPublicAuthContext(algs, meta, key);

  return true;
}

/*! \brief  Private authentication context with opaque data.

    Used in/for authentication protocol.
*/
/*! \brief  Get supported algorithms.

    \returns  Supported algorithms.
*/
const std::vector<AlgorithmDescriptor*>& OpaquePrivateAuthContext::GetSupportedAlgorithms() const {
  return algorithms;
}

/*! \brief  Get trust and security metadata.

    \returns Trust and security metadata.
*/
const TrustSecurityMetadataIPMPData* OpaquePrivateAuthContext::GetTrustData() const {
  return trust;
}

/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool OpaquePrivateAuthContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool OpaquePrivateAuthContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  return crypto->CreatePublicVerifier(ByteSeq(), opaque, out);
}

/*! \brief  Create public key signer.

    \param  crypto        input, crypto provider.
    \param  out           output, public key signer.

    \returns  Boolean indicating succes or failure.
*/
bool OpaquePrivateAuthContext::CreatePublicSigner(CryptoProvider* crypto,
    PublicSigner** out) {
  return crypto->CreatePublicSigner(ByteSeq(), opaque, out);
}

/*! \brief  Get opaque data.

    \returns  Opaque data.
*/
const ByteSeq& OpaquePrivateAuthContext::GetOpaque() const {
  return opaque;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, public authentication context.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool OpaquePrivateAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const PublicAuthContext* ctx, Authenticator** auth) const {
  return ctx->CreateAuthenticator(crypto, (OpaqueAuthContext*)this, auth);
}

/*! \brief  Create public authentication context.

    \param  ctx         output, public authentication context.

    \returns  Boolean indicating success or failure.
*/
bool OpaquePrivateAuthContext::CreatePublicContext(PublicAuthContext** ctx) const {
  std::vector<AlgorithmDescriptor*> algs;
  std::vector<AlgorithmDescriptor*>::const_iterator iter = algorithms.begin();
  while (iter != algorithms.end()) {
    algs.push_back((*iter)->Copy());
    iter++;
  }
  TrustSecurityMetadataIPMPData* meta = 0;
  if (trust != 0) meta = trust->Copy();
  *ctx = new OpaquePublicAuthContext(algs, meta, opaque);

  return true;
}

/*! \brief  Public authentication context with certificates.

    Used in/for authentication protocol.
*/
/*! \brief  Get supported algorithms.

    \returns  Supported algorithms.
*/
const std::vector<AlgorithmDescriptor*>& CertPublicAuthContext::GetSupportedAlgorithms() const {
  return algorithms;
}

/*! \brief  Get trust and security metadata.

    \returns Trust and security metadata.
*/
const TrustSecurityMetadataIPMPData* CertPublicAuthContext::GetTrustData() const {
  return trust;
}

/*! \brief  Encode as byte array (without algorithms).

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool CertPublicAuthContext::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x01);
  if (certificates.size() >= (1 << 8)) {
    return false;
  }
  encoded += (ByteT)(certificates.size());
  encoded += certType;
  std::vector<ByteSeq>::const_iterator iter = certificates.begin();
  while (iter != certificates.end()) {
    encoded += iter->MPEG2Encode();
    iter++;
  }
  ByteSeq tmp;
  if (trust->MPEG2Encode(tmp) == false) {
    return false;
  }
  encoded += tmp;
  return true;
}

/*! \brief  Set supported algorithms.

    \param  algs      input, algorithms to be set.

    \returns  Boolean indicating success or failure.
*/
bool CertPublicAuthContext::SetSupportedAlgorithms(const std::vector<AlgorithmDescriptor*>&
    algs) {
  std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
  while (iter != algorithms.end()) {
    if ((*iter) != 0) delete (*iter);
    iter++;
  }
  algorithms.clear();
  algorithms = algs;
  return true;
}

/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool CertPublicAuthContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool CertPublicAuthContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  /*! \todo Take the key out of the certificates and pass it to the crypto
            provider.
  */
  return crypto->CreatePublicVerifier(ByteSeq(), ByteSeq(), out);
}

/*! \brief  Get certificate type.

    \returns  Certificate type.
*/
const ByteT& CertPublicAuthContext::GetCertType() const {
  return certType;
}

/*! \brief  Get certificates.

    \returns  Certificates.
*/
const std::vector<ByteSeq>& CertPublicAuthContext::GetCertificates() const {
  return certificates;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with certificates.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool CertPublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const CertAuthContext* ctx, Authenticator** auth) const {
  //  Create authenticator.
  *auth = new DiffieHellmanAuthenticator(ctx->GetCertificates(), certificates);
  return true;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with key.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool CertPublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const KeyAuthContext* ctx, Authenticator** auth) const {
  return false;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with opaque data.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool CertPublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const OpaqueAuthContext* ctx, Authenticator** auth) const {
  return false;
}

/*! \brief  Public authentication context with key.

    Used in/for authentication protocol.
*/
/*! \brief  Get supported algorithms.

    \returns  Supported algorithms.
*/
const std::vector<AlgorithmDescriptor*>& KeyPublicAuthContext::GetSupportedAlgorithms() const {
  return algorithms;
}

/*! \brief  Get trust and security metadata.

    \returns Trust and security metadata.
*/
const TrustSecurityMetadataIPMPData* KeyPublicAuthContext::GetTrustData() const {
  return trust;
}

/*! \brief  Encode as byte array (without algorithms).

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool KeyPublicAuthContext::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x02);
  ByteSeq tmp;
  if (key.MPEG2Encode(tmp) == false) {
    return false;
  }
  encoded += tmp;
  if (trust->MPEG2Encode(tmp) == false) {
    return false;
  }
  encoded += tmp;
  return true;
}

/*! \brief  Set supported algorithms.

    \param  algs      input, algorithms to be set.

    \returns  Boolean indicating success or failure.
*/
bool KeyPublicAuthContext::SetSupportedAlgorithms(const std::vector<AlgorithmDescriptor*>&
    algs) {
  std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
  while (iter != algorithms.end()) {
    if ((*iter) != 0) delete (*iter);
    iter++;
  }
  algorithms.clear();
  algorithms = algs;
  return true;
}

/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool KeyPublicAuthContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool KeyPublicAuthContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  return crypto->CreatePublicVerifier(ByteSeq(), key.GetKeyBody(), out);
}

/*! \brief  Get key descriptor.

    \returns  Key descriptor.
*/
const KeyDescriptor& KeyPublicAuthContext::GetKeyDescriptor() const {
  return key;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with certificates.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool KeyPublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const CertAuthContext* ctx, Authenticator** auth) const {
  return false;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with key.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool KeyPublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const KeyAuthContext* ctx, Authenticator** auth) const {
  //  Create authenticator.
  *auth = new RSANeedhamSchroederAuthenticator(ctx->GetKeyDescriptor().GetKeyBody(),
    key.GetKeyBody());
  return true;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with opaque data.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool KeyPublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const OpaqueAuthContext* ctx, Authenticator** auth) const {
  return false;
}

/*! \brief  Public authentication context with opaque data.

    Used in/for authentication protocol.
*/
/*! \brief  Get supported algorithms.

    \returns  Supported algorithms.
*/
const std::vector<AlgorithmDescriptor*>& OpaquePublicAuthContext::GetSupportedAlgorithms() const {
  return algorithms;
}

/*! \brief  Get trust and security metadata.

    \returns Trust and security metadata.
*/
const TrustSecurityMetadataIPMPData* OpaquePublicAuthContext::GetTrustData() const {
  return trust;
}

/*! \brief  Encode as byte array (without algorithms).

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool OpaquePublicAuthContext::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x02);
  encoded += opaque.MPEG2Encode();
  ByteSeq tmp;
  if (trust->MPEG2Encode(tmp) == false) {
    return false;
  }
  encoded += tmp;
  return true;
}

/*! \brief  Set supported algorithms.

    \param  algs      input, algorithms to be set.

    \returns  Boolean indicating success or failure.
*/
bool OpaquePublicAuthContext::SetSupportedAlgorithms(const std::vector<AlgorithmDescriptor*>&
    algs) {
  std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
  while (iter != algorithms.end()) {
    if ((*iter) != 0) delete (*iter);
    iter++;
  }
  algorithms.clear();
  algorithms = algs;
  return true;
}

/*! \brief  Create hash calculator.

    \param  crypto        input, crypto provider.
    \param  out           output, hash calculator.

    \returns  Boolean indicating succes or failure.
*/
bool OpaquePublicAuthContext::CreateHashCalculator(CryptoProvider* crypto,
    HashCalculator** out) {
  //! \todo Take the hash algorithm out and pass it to crypto provider.
  return crypto->CreateHashCalculator(ByteSeq(), out);
}

/*! \brief  Create public key verifier.

    \param  crypto        input, crypto provider.
    \param  out           output, public key verifier.

    \returns  Boolean indicating succes or failure.
*/
bool OpaquePublicAuthContext::CreatePublicVerifier(CryptoProvider* crypto,
    PublicVerifier** out) {
  return crypto->CreatePublicVerifier(ByteSeq(), opaque, out);
}

/*! \brief  Get opaque data.

    \returns  Opaque data.
*/
const ByteSeq& OpaquePublicAuthContext::GetOpaque() const {
  return opaque;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with certificates.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool OpaquePublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const CertAuthContext* ctx, Authenticator** auth) const {
  return false;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with key.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool OpaquePublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const KeyAuthContext* ctx, Authenticator** auth) const {
  return false;
}

/*! \brief  Create authenticator, used in authentication protocol.

    \param  crypto    input, crypto provider.
    \param  ctx       input, authentication context with opaque data.
    \param  auth      output, authenticator.

    \returns  Boolean indicating success or failure.
*/
bool OpaquePublicAuthContext::CreateAuthenticator(CryptoProvider* crypto,
    const OpaqueAuthContext* ctx, Authenticator** auth) const {
  //  Create authenticator.
  //  Should be true, but for now we have no idea what to do with it.
  return false;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
