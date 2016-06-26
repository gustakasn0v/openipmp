/**	\file CryptoContext.h

	Crypto contexts, with the keys, algorithms, etc.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (CRYPTOCONTEXT_H)
#define CRYPTOCONTEXT_H

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

/*! \brief  Public key crypto context.

    Creates public key verifier.
*/
class PublicVerifierContext {
public:
  virtual ~PublicVerifierContext() {
  }

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out) = 0;

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out) = 0;
};

/*! \brief  Public (private) key crypto context.

    Creates public key verifier and signer.
*/
class PublicSignerContext: public PublicVerifierContext {
public:
  virtual ~PublicSignerContext() {
  }

  /*! \brief  Create public key signer.

      \param  crypto        input, crypto provider.
      \param  out           output, public key signer.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicSigner(CryptoProvider* crypto, PublicSigner** out) = 0;
};

/*!	\brief  Certificate container.

    Certificate container consisting of certificate type and certificate data.
*/
class CertificateContainer {
public:
  /*! \brief  Constructor.

      \param  type        certificate type.
      \param  cert        certificate.
  */
  CertificateContainer(const ByteT& type, const ByteSeq& cert): certType(type),
    certificate(cert) {
  }

  /*! \brief  Copy constructor.

      \param  rhs         certificate container.
  */
  CertificateContainer(const CertificateContainer& rhs): certType(rhs.certType),
    certificate(rhs.certificate) {
  }

  ~CertificateContainer() {
  }

  /*! \brief  Get certificate type.

      Certificate type value is assigned by registration authority.

      \returns  Number representing certificate type.
  */
  const ByteT& GetCertType() const {
    return certType;
  }

  /*! \brief  Get certificate.

      \returns  Certificate.
  */
  const ByteSeq& GetCertificate() const {
    return certificate;
  }

private:
  ByteT certType;
  ByteSeq certificate;
};

/*! \brief  Public key crypto context with certificates.

    Creates public key verifier.
*/
class CertPublicVerifierContext: public PublicVerifierContext {
public:
  /*! \brief  Constructor.

      \param  conts         certificate containers.
  */
  CertPublicVerifierContext(const std::vector<ICertContainer*>& conts):
      containers() {
    std::vector<ICertContainer*>::const_iterator iter = conts.begin();
    while (iter != conts.end()) {
      containers.push_back(CertificateContainer((*iter)->GetCertType(),
        (*iter)->GetCertificate()));
      iter++;
    }
  }

  virtual ~CertPublicVerifierContext() {
  }

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

private:
  std::vector<CertificateContainer> containers;
};

/*! \brief  Public (private) key crypto context.

    Creates public key verifier and signer.
*/
class CertPublicSignerContext: public PublicSignerContext {
public:
  /*! \brief  Constructor.

      \param  conts         certificate containers.
  */
  CertPublicSignerContext(const std::vector<ICertContainer*>& conts):
      containers() {
    std::vector<ICertContainer*>::const_iterator iter = conts.begin();
    while (iter != conts.end()) {
      containers.push_back(CertificateContainer((*iter)->GetCertType(),
        (*iter)->GetCertificate()));
      iter++;
    }
  }

  virtual ~CertPublicSignerContext() {
  }

  /*! \brief  Create public key signer.

      \param  crypto        input, crypto provider.
      \param  out           output, public key signer.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicSigner(CryptoProvider* crypto, PublicSigner** out);

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

private:
  std::vector<CertificateContainer> containers;
};

/*!	\brief  Trust security metadata IPMP data.
*/
class TrustSecurityMetadataIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  TrustSecurityMetadataIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  /*! \brief  Copy constructor.
      
      \param  rhs       input, trust security metadata.
  */
  TrustSecurityMetadataIPMPData(const TrustSecurityMetadataIPMPData& rhs):
    IPMPData(rhs.version, rhs.dataID) {
  }

  virtual ~TrustSecurityMetadataIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create a new copy of this metadata.

      \returns  A new copy of this metadata.
  */
  virtual TrustSecurityMetadataIPMPData* Copy() const;
};

/*! \brief  Base authentication descriptor.
*/
class BaseAuthenticationDescriptor {
public:
  virtual ~BaseAuthenticationDescriptor() {};

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const = 0;

protected:
  /*! \brief  Encode as byte array.

      Encode tag, expandable size and class data.

      \param  tag           input, class tag.
      \param  data          input, class data.
      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  bool MPEG2Encode(const ByteT& tag, const ByteSeq& data, ByteSeq& encoded) const;
};

/*! \brief  Key authentication descriptor.
*/
class KeyDescriptor: public BaseAuthenticationDescriptor {
public:
  /*! \brief  Constructor.
      
      \param  body      input, key body.
  */
  KeyDescriptor(const ByteSeq& body): keyBody(body) {
  }

  /*! \brief  Copy constructor.
      
      \param  rhs      input, key descriptor.
  */
  KeyDescriptor(const KeyDescriptor& rhs): keyBody(rhs.keyBody) {
  }

  virtual ~KeyDescriptor() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get key body.

      \returns Key body.
  */
  const ByteSeq& GetKeyBody() const;

private:
  ByteSeq keyBody;
};

/*! \brief  Algorithm authentication descriptor.
*/
class AlgorithmDescriptor: public BaseAuthenticationDescriptor {
public:
  /*! \brief  Constructor.
      
      \param  opaque      input, opaque data.
  */
  AlgorithmDescriptor(const ByteSeq& opaque): opaqueData(opaque) {
  }

  virtual ~AlgorithmDescriptor() {
  }

  /*! \brief  Create a new copy of this algorithm descriptor.

      \return The new copy of this algorithm descriptor.
  */
  virtual AlgorithmDescriptor* Copy() const = 0;

  /*! \brief  Get algorithm identifier.

      \returns  Algorithm identifier.
  */
  virtual ByteSeq GetAlgorithmID() const = 0;

  /*! \brief  Get opaque data.

      \returns Opaque data.
  */
  const ByteSeq& GetOpaqueData() const;

protected:
  ByteSeq opaqueData;
};

/*! \brief  Registered algorithm authentication descriptor.
*/
class RegAlgorithmDescriptor: public AlgorithmDescriptor {
public:
  /*! \brief  Constructor.
      
      \param  opaque      input, opaque data.
      \param  id          input, registered algorithm identifier.
  */
  RegAlgorithmDescriptor(const ByteSeq& opaque, const Bit16T& id):
    AlgorithmDescriptor(opaque), regAlgoID(id) {
  }

  virtual ~RegAlgorithmDescriptor() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create a new copy of this algorithm descriptor.

      \return The new copy of this algorithm descriptor.
  */
  virtual AlgorithmDescriptor* Copy() const;

  /*! \brief  Get algorithm identifier.

      \returns  Algorithm identifier.
  */
  virtual ByteSeq GetAlgorithmID() const;

  /*! \brief  Get registered algorithm identifier.

      \returns Registered algorithm identifier.
  */
  const Bit16T& GetRegAlgoID() const;

private:
  Bit16T regAlgoID;
};

/*! \brief  Non-registered algorithm authentication descriptor.
*/
class NRegAlgorithmDescriptor: public AlgorithmDescriptor {
public:
  /*! \brief  Constructor.
      
      \param  opaque      input, opaque data.
      \param  id          input, non-registered algorithm identifier.
  */
  NRegAlgorithmDescriptor(const ByteSeq& opaque, const ByteSeq& id):
    AlgorithmDescriptor(opaque), specAlgoID(id) {
  }

  virtual ~NRegAlgorithmDescriptor() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create a new copy of this algorithm descriptor.

      \return The new copy of this algorithm descriptor.
  */
  virtual AlgorithmDescriptor* Copy() const;

  /*! \brief  Get algorithm identifier.

      \returns  Algorithm identifier.
  */
  virtual ByteSeq GetAlgorithmID() const;

  /*! \brief  Get special algorithm identifier.

      \returns Special algorithm identifier.
  */
  const ByteSeq& GetSpecAlgoID() const;

private:
  ByteSeq specAlgoID;
};

/*! \brief  Authentication context.

    Used in/for authentication protocol.
*/
class AuthContext {
public:
  virtual ~AuthContext() {
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  virtual const std::vector<AlgorithmDescriptor*>& GetSupportedAlgorithms() const = 0;

  /*! \brief  Get trust and security metadata.

      \returns Trust and security metadata.
  */
  virtual const TrustSecurityMetadataIPMPData* GetTrustData() const = 0;

  /*! \brief  Copy supported algorithms.

      \returns  Copied supported algorithms.
  */
  std::vector<AlgorithmDescriptor*> CopySupportedAlgorithms() const {
    std::vector<AlgorithmDescriptor*> ret;
    for (unsigned int i = 0; i < GetSupportedAlgorithms().size(); i++) {
      ret.push_back(GetSupportedAlgorithms()[i]->Copy());
    }
    return ret;
  }
};

/*! \brief  Authentication context with certificates.

    Used in/for authentication protocol.
*/
class CertAuthContext: public AuthContext {
public:
  virtual ~CertAuthContext() {
  }

  /*! \brief  Get certificate type.

      \returns  Certificate type.
  */
  virtual const ByteT& GetCertType() const = 0;

  /*! \brief  Get certificates.

      \returns  Certificates.
  */
  virtual const std::vector<ByteSeq>& GetCertificates() const = 0;
};

/*! \brief  Authentication context with key.

    Used in/for authentication protocol.
*/
class KeyAuthContext: public AuthContext {
public:
  virtual ~KeyAuthContext() {
  }

  /*! \brief  Get key descriptor.

      \returns  Key descriptor.
  */
  virtual const KeyDescriptor& GetKeyDescriptor() const = 0;
};

/*! \brief  Authentication context with opaque data.

    Used in/for authentication protocol.
*/
class OpaqueAuthContext: public AuthContext {
public:
  virtual ~OpaqueAuthContext() {
  }

  /*! \brief  Get opaque data.

      \returns  Opaque data.
  */
  virtual const ByteSeq& GetOpaque() const = 0;
};

/*! \brief  Public authentication context.

    Used in/for authentication protocol.
*/
class PublicAuthContext: public AuthContext, public PublicVerifierContext {
public:
  virtual ~PublicAuthContext() {
  }

  /*! \brief  Encode as byte array (without algorithms).

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const = 0;

  /*! \brief  Set supported algorithms.

      \param  algs      input, algorithms to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSupportedAlgorithms(const std::vector<AlgorithmDescriptor*>& algs) = 0;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with certificates.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const CertAuthContext* ctx,
    Authenticator** auth) const = 0;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with key.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const KeyAuthContext* ctx,
    Authenticator** auth) const = 0;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with opaque data.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const OpaqueAuthContext* ctx,
    Authenticator** auth) const = 0;
};

/*! \brief  Public authentication context with certificates.

    Used in/for authentication protocol.
*/
class CertPublicAuthContext: public PublicAuthContext, public CertAuthContext {
public:
  /*! \brief  Constructor.

      \param  algs          supported algorithms.
      \param  meta          trust and security metadata (must be != 0).
      \param  type          certificate type.
      \param  certs         certificates.
  */
  CertPublicAuthContext(const std::vector<AlgorithmDescriptor*>& algs,
    TrustSecurityMetadataIPMPData* meta, const ByteT& type,
    const std::vector<ByteSeq>& certs): algorithms(algs), trust(meta),
    certType(type), certificates(certs) {
  }

  virtual ~CertPublicAuthContext() {
    std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
    while (iter != algorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    algorithms.clear();
    if (trust != 0) delete trust; trust = 0;
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  virtual const std::vector<AlgorithmDescriptor*>& GetSupportedAlgorithms() const;

  /*! \brief  Get trust and security metadata.

      \returns Trust and security metadata.
  */
  virtual const TrustSecurityMetadataIPMPData* GetTrustData() const;

  /*! \brief  Encode as byte array (without algorithms).

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Set supported algorithms.

      \param  algs      input, algorithms to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSupportedAlgorithms(const std::vector<AlgorithmDescriptor*>& algs);

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with certificates.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const CertAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with key.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const KeyAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with opaque data.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const OpaqueAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

  /*! \brief  Get certificate type.

      \returns  Certificate type.
  */
  virtual const ByteT& GetCertType() const;

  /*! \brief  Get certificates.

      \returns  Certificates.
  */
  virtual const std::vector<ByteSeq>& GetCertificates() const;

private:
  std::vector<AlgorithmDescriptor*> algorithms;
  TrustSecurityMetadataIPMPData* trust;
  ByteT certType;
  std::vector<ByteSeq> certificates;
};

/*! \brief  Public authentication context with key.

    Used in/for authentication protocol.
*/
class KeyPublicAuthContext: public PublicAuthContext, public KeyAuthContext {
public:
  /*! \brief  Constructor.

      \param  algs          supported algorithms.
      \param  meta          trust and security metadata (must be != 0).
      \param  kDesc         key descriptor.
  */
  KeyPublicAuthContext(const std::vector<AlgorithmDescriptor*>& algs,
    TrustSecurityMetadataIPMPData* meta, const KeyDescriptor& kDesc):
    algorithms(algs), trust(meta), key(kDesc) {
  }

  virtual ~KeyPublicAuthContext() {
    std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
    while (iter != algorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    algorithms.clear();
    if (trust != 0) delete trust; trust = 0;
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  virtual const std::vector<AlgorithmDescriptor*>& GetSupportedAlgorithms() const;

  /*! \brief  Get trust and security metadata.

      \returns Trust and security metadata.
  */
  virtual const TrustSecurityMetadataIPMPData* GetTrustData() const;

  /*! \brief  Encode as byte array (without algorithms).

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Set supported algorithms.

      \param  algs      input, algorithms to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSupportedAlgorithms(const std::vector<AlgorithmDescriptor*>& algs);

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with certificates.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const CertAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with key.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const KeyAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with opaque data.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const OpaqueAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

  /*! \brief  Get key descriptor.

      \returns  Key descriptor.
  */
  virtual const KeyDescriptor& GetKeyDescriptor() const;

private:
  std::vector<AlgorithmDescriptor*> algorithms;
  TrustSecurityMetadataIPMPData* trust;
  KeyDescriptor key;
};

/*! \brief  Public authentication context with opaque data.

    Used in/for authentication protocol.
*/
class OpaquePublicAuthContext: public PublicAuthContext, public OpaqueAuthContext {
public:
  /*! \brief  Constructor.

      \param  algs          supported algorithms.
      \param  meta          trust and security metadata (must be != 0).
      \param  opaq          opaque data.
  */
  OpaquePublicAuthContext(const std::vector<AlgorithmDescriptor*>& algs,
    TrustSecurityMetadataIPMPData* meta, const ByteSeq& opaq):
    algorithms(algs), trust(meta), opaque(opaq) {
  }

  virtual ~OpaquePublicAuthContext() {
    std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
    while (iter != algorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    algorithms.clear();
    if (trust != 0) delete trust; trust = 0;
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  virtual const std::vector<AlgorithmDescriptor*>& GetSupportedAlgorithms() const;

  /*! \brief  Get trust and security metadata.

      \returns Trust and security metadata.
  */
  virtual const TrustSecurityMetadataIPMPData* GetTrustData() const;

  /*! \brief  Encode as byte array (without algorithms).

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Set supported algorithms.

      \param  algs      input, algorithms to be set.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetSupportedAlgorithms(const std::vector<AlgorithmDescriptor*>& algs);

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with certificates.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const CertAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with key.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const KeyAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, authentication context with opaque data.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const OpaqueAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

  /*! \brief  Get opaque data.

      \returns  Opaque data.
  */
  virtual const ByteSeq& GetOpaque() const;

private:
  std::vector<AlgorithmDescriptor*> algorithms;
  TrustSecurityMetadataIPMPData* trust;
  ByteSeq opaque;
};

/*! \brief  Private authentication context.

    Used in/for authentication protocol.
*/
class PrivateAuthContext: public AuthContext, public PublicSignerContext {
public:
  virtual ~PrivateAuthContext() {
  }

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, public authentication context.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const PublicAuthContext* ctx,
    Authenticator** auth) const = 0;

  /*! \brief  Create public authentication context.

      \param  ctx         output, public authentication context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreatePublicContext(PublicAuthContext** ctx) const = 0;
};

/*! \brief  Private authentication context with certificates.

    Used in/for authentication protocol.
*/
class CertPrivateAuthContext: public PrivateAuthContext, public CertAuthContext {
public:
  /*! \brief  Constructor.

      \param  algs          supported algorithms.
      \param  meta          trust and security metadata (must be != 0).
      \param  type          certificate type.
      \param  certs         certificates.
  */
  CertPrivateAuthContext(const std::vector<AlgorithmDescriptor*>& algs,
    TrustSecurityMetadataIPMPData* meta, const ByteT& type,
    const std::vector<ByteSeq>& certs): algorithms(algs), trust(meta),
    certType(type), certificates(certs) {
  }

  virtual ~CertPrivateAuthContext() {
    std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
    while (iter != algorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    algorithms.clear();
    if (trust != 0) delete trust; trust = 0;
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  virtual const std::vector<AlgorithmDescriptor*>& GetSupportedAlgorithms() const;

  /*! \brief  Get trust and security metadata.

      \returns Trust and security metadata.
  */
  virtual const TrustSecurityMetadataIPMPData* GetTrustData() const;

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

  /*! \brief  Create public key signer.

      \param  crypto        input, crypto provider.
      \param  out           output, public key signer.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicSigner(CryptoProvider* crypto, PublicSigner** out);

  /*! \brief  Get certificate type.

      \returns  Certificate type.
  */
  virtual const ByteT& GetCertType() const;

  /*! \brief  Get certificates.

      \returns  Certificates.
  */
  virtual const std::vector<ByteSeq>& GetCertificates() const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, public authentication context.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const PublicAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create public authentication context.

      \param  ctx         output, public authentication context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreatePublicContext(PublicAuthContext** ctx) const;

private:
  std::vector<AlgorithmDescriptor*> algorithms;
  TrustSecurityMetadataIPMPData* trust;
  ByteT certType;
  std::vector<ByteSeq> certificates;
};

/*! \brief  Private authentication context with key.

    Used in/for authentication protocol.
*/
class KeyPrivateAuthContext: public PrivateAuthContext, public KeyAuthContext {
public:
  /*! \brief  Constructor.

      \param  algs          supported algorithms.
      \param  meta          trust and security metadata (must be != 0).
      \param  kDesc         key descriptor.
  */
  KeyPrivateAuthContext(const std::vector<AlgorithmDescriptor*>& algs,
    TrustSecurityMetadataIPMPData* meta, const KeyDescriptor& kDesc):
    algorithms(algs), trust(meta), key(kDesc) {
  }

  virtual ~KeyPrivateAuthContext() {
    std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
    while (iter != algorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    algorithms.clear();
    if (trust != 0) delete trust; trust = 0;
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  virtual const std::vector<AlgorithmDescriptor*>& GetSupportedAlgorithms() const;

  /*! \brief  Get trust and security metadata.

      \returns Trust and security metadata.
  */
  virtual const TrustSecurityMetadataIPMPData* GetTrustData() const;

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

  /*! \brief  Create public key signer.

      \param  crypto        input, crypto provider.
      \param  out           output, public key signer.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicSigner(CryptoProvider* crypto, PublicSigner** out);

  /*! \brief  Get key descriptor.

      \returns  Key descriptor.
  */
  virtual const KeyDescriptor& GetKeyDescriptor() const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, public authentication context.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const PublicAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create public authentication context.

      \param  ctx         output, public authentication context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreatePublicContext(PublicAuthContext** ctx) const;

private:
  std::vector<AlgorithmDescriptor*> algorithms;
  TrustSecurityMetadataIPMPData* trust;
  KeyDescriptor key;
};

/*! \brief  Private authentication context with opaque data.

    Used in/for authentication protocol.
*/
class OpaquePrivateAuthContext: public PrivateAuthContext, public OpaqueAuthContext {
public:
  /*! \brief  Constructor.

      \param  algs          supported algorithms.
      \param  meta          trust and security metadata (must be != 0).
      \param  opaq          opaque data.
  */
  OpaquePrivateAuthContext(const std::vector<AlgorithmDescriptor*>& algs,
    TrustSecurityMetadataIPMPData* meta, const ByteSeq& opaq):
    algorithms(algs), trust(meta), opaque(opaq) {
  }

  virtual ~OpaquePrivateAuthContext() {
    std::vector<AlgorithmDescriptor*>::iterator iter = algorithms.begin();
    while (iter != algorithms.end()) {
      if ((*iter) != 0) delete (*iter);
      iter++;
    }
    algorithms.clear();
    if (trust != 0) delete trust; trust = 0;
  }

  /*! \brief  Get supported algorithms.

      \returns  Supported algorithms.
  */
  virtual const std::vector<AlgorithmDescriptor*>& GetSupportedAlgorithms() const;

  /*! \brief  Get trust and security metadata.

      \returns Trust and security metadata.
  */
  virtual const TrustSecurityMetadataIPMPData* GetTrustData() const;

  /*! \brief  Create hash calculator.

      \param  crypto        input, crypto provider.
      \param  out           output, hash calculator.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreateHashCalculator(CryptoProvider* crypto, HashCalculator** out);

  /*! \brief  Create public key verifier.

      \param  crypto        input, crypto provider.
      \param  out           output, public key verifier.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicVerifier(CryptoProvider* crypto, PublicVerifier** out);

  /*! \brief  Create public key signer.

      \param  crypto        input, crypto provider.
      \param  out           output, public key signer.

      \returns  Boolean indicating succes or failure.
  */
  virtual bool CreatePublicSigner(CryptoProvider* crypto, PublicSigner** out);

  /*! \brief  Get opaque data.

      \returns  Opaque data.
  */
  virtual const ByteSeq& GetOpaque() const;

  /*! \brief  Create authenticator, used in authentication protocol.

      \param  crypto    input, crypto provider.
      \param  ctx       input, public authentication context.
      \param  auth      output, authenticator.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreateAuthenticator(CryptoProvider* crypto, const PublicAuthContext* ctx,
    Authenticator** auth) const;

  /*! \brief  Create public authentication context.

      \param  ctx         output, public authentication context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool CreatePublicContext(PublicAuthContext** ctx) const;

private:
  std::vector<AlgorithmDescriptor*> algorithms;
  TrustSecurityMetadataIPMPData* trust;
  ByteSeq opaque;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (CRYPTOCONTEXT_H)
