/** \file AgentBase.h

    OMADRM agent's contexts and tools.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (AGENTBASE_H)
#define AGENTBASE_H

#include "OMADRMCrypto.h"
#include <map>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \todo: There is an inconsistency in the DRM documentation related to
    supported algorithms. In the text it is indicated that device and rights
    issuer must support algorithms for each kind of operation (hash, mac,
    signature, key wrap etc.) but for example in the rights issuer hello
    message, there is no way (syntax doesn't define it) to distinguish between
    different kinds of algorithms, because they are all defined as simple
    URI values.
*/

/*! \brief  Device context, kept by the agent.
*/
class AgentDeviceContext: public GC {
public:
  /*! \brief  Constructor.

      \param  cer               device public certificate.
      \param  pri               device private key.
      \param  devid             device identifier.
      \param  cchain            device certificate chain.
      \param  ca                CA identifier.
      \param  cacer             CA certificate.
      \param  trust             trusted authorities identifiers.
      \param  trustcerts        trusted authorities certificates.
      \param  algs              supported algorithms.
      \param  devdetails        device details data.
      \param  ccaching          certificate caching.
      \param  ver               version.
  */
  AgentDeviceContext(const NZSPtr<OMAPublicCertificate>& cer,
    const NZSPtr<OMAPrivateKey>& pri, const NZSPtr<ROAPIdentifier>& devid,
    const NZSPtr<ROAPCertificateChain>& cchain, const NZSPtr<ROAPKeyIdentifier>& ca,
    const Base64StringT& cacer, const SPtr<ROAPKeyIdentifiers>& trust,
    const std::vector<Base64StringT>& trustcerts,
    const std::vector<NZSPtr<URIValue> >& algs, const NZSPtr<DeviceDetailsData>& devdetails,
    const SPtr<CertCachingExtension>& ccaching, const NZSPtr<ROAPVersion>& ver):
    publicCert(cer), privateKey(pri), deviceID(devid), chain(cchain), caID(ca),
    caCert(cacer), trusted(trust), trustedCerts(trustcerts), algorithms(algs),
    details(devdetails), caching(ccaching), version(ver) {
  }

  /*! \brief  Get device public certificate.

      \returns  Device public certificate.
  */
  const NZSPtr<OMAPublicCertificate>& GetPublicCert() const {
    return publicCert;
  }

  /*! \brief  Get device private key.

      \returns  Device private key.
  */
  const NZSPtr<OMAPrivateKey>& GetPrivateKey() const {
    return privateKey;
  }

  /*! \brief  Get device key identifier.

      \returns  Device key identifier.
  */
  const NZSPtr<ROAPKeyIdentifier>& GetKeyID() const {
    return deviceID->GetKeyID();
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetID() const {
    return deviceID;
  }

  /*! \brief  Get device certificate chain.

      \returns  Device certificate chain.
  */
  const NZSPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get device CA key identifier.
  
      \returns Device CA key identifier.
  */
  const NZSPtr<ROAPKeyIdentifier>& GetCAID() const {
    return caID;
  }

  /*! \brief  Get device CA certificate.

      \todo: This must correspond to CA key identifier.

      \returns  Device CA certificate.
  */
  const Base64StringT& GetCACert() const {
    return caCert;
  }

  /*! \brief  Get device trusted root authorities.
  
      These are used to ensure that rights issuer's certificate chain roots at
      one of these authorities, otherwise device will reject rights issuer's
      responses etc. If trusted authorities is empty, it signals rights issuer
      that it can send any certificate chain.

      \returns Device trusted root authorities.
  */
  const SPtr<ROAPKeyIdentifiers>& GetTrusted() const {
    return trusted;
  }

  /*! \brief  Get device trusted root authorities certificates.

      \todo: These should correspond to trusted authorities key identifiers.

      \returns  Device trusted root authorities certificates.
  */
  const std::vector<Base64StringT>& GetTrustedCerts() const {
    return trustedCerts;
  }

  /*! \brief  Get supported algorithms.
  
      \todo: Handle different kinds of algorithms.

      Default algorithms (hash, mac, key wrap, signature):
      Hash algorithms:
      SHA-1: http://www.w3.org/2000/09/xmldsig#sha1.
      MAC algorithms:
      HMAC-SHA-1: http://www.w3.org/2000/09/xmldsig#hmac-sha1.
      Signature algorithms:
      RSA-PSS-Default: http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsa-pss-default.
      Key transport algorithms:
      RSAES-KEM-KDF2-KW-AES128:
      http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsaes-kem-kdf2-kw-aes128.
      Key wrapping algorithms:
      AES-WRAP: http://www.w3.org/2001/04/xmlenc#kw-aes128.

      \returns  Supported algorithms.
  */
  const std::vector<NZSPtr<URIValue> >& GetAlgorithms() const {
    return algorithms;
  }

  /*! \brief  Get device details data (manufacturer, version, etc.).

      \returns  Device details data.
  */
  const NZSPtr<DeviceDetailsData>& GetDetails() const {
    return details;
  }

  /*! \brief  Get device's ability to store information on whether rights issuer
              has saved device certificate chain or not.
  
      \todo:  Documentation says that certificate caching extension on the device
              side does not mean certificate caching ability, but ability to store
              information on whether rights issuer has saved device certificate
              data or not. Since this is a trivial ability to implement (we just
              save a pointer to device certificate chain in the rights issuer context),
              we shall by default assume that this is true, so the certificate
              caching extension in device context will be set (non-zero).

      \returns  Device's ability to store information on whether rights issuer
                has saved device certificate chain or not.
  */
  SPtr<CertCachingExtension> GetCertCaching() const {
//    return caching;
    return new CertCachingExtension();
  }

  /*! \brief  Get device version.

      \returns  Device version.
  */
  const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

private:
  NZSPtr<OMAPublicCertificate> publicCert;
  NZSPtr<OMAPrivateKey> privateKey;
  NZSPtr<ROAPIdentifier> deviceID;
  NZSPtr<ROAPCertificateChain> chain;
  NZSPtr<ROAPKeyIdentifier> caID;
  Base64StringT caCert;
  SPtr<ROAPKeyIdentifiers> trusted;
  std::vector<Base64StringT> trustedCerts;
	std::vector<NZSPtr<URIValue> > algorithms;
  NZSPtr<DeviceDetailsData> details;
  SPtr<CertCachingExtension> caching;
  NZSPtr<ROAPVersion> version;
};

/*! \brief  Temporary rights issuer context, used in registration protocol.
*/
class TempAgentRIContext: public GC {
public:
  /*! \brief  Constructor.

      \param  cer               rights issuer public certificate.
      \param  id                rights issuer identifier.
      \param  cchain            rights issuer certificate chain.
      \param  riurl             rights issuer URL.
      \param  ver               rights issuer version.
      \param  trust             rights issuer trusted authorities.
      \param  algs              rights issuer supported algorithms.
      \param  ccaching          certificate caching.
      \param  ocspresp          rights issuer OCSP responses.
      \param  wlist             domain name white list.
      \param  serverinf         server info.
  */
  TempAgentRIContext(const SPtr<OMAPublicCertificate>& cer, const SPtr<ROAPIdentifier>& id,
    const SPtr<ROAPCertificateChain>& cchain, const NZSPtr<URIValue>& riurl,
    const SPtr<ROAPVersion>& ver, const SPtr<ROAPKeyIdentifiers>& trust,
    const std::vector<NZSPtr<URIValue> >& algs, const SPtr<CertCachingExtension>&
    ccaching, const std::vector<Base64StringT>& ocspresp, const
    SPtr<DomainNameWhiteListExtension>& wlist, const SPtr<ROAPServerInfo>&
    serverinf): publicCert(cer), riID(id), chain(cchain), url(riurl), version(ver),
    trusted(trust), algorithms(algs), caching(ccaching), ocsps(ocspresp),
    whitelist(wlist), serverInfo(serverinf) {
  }

  //! Rights issuer public certificate.
  SPtr<OMAPublicCertificate> publicCert;

  //! Rights issuer identifier.
  SPtr<ROAPIdentifier> riID;

  //! Rights issuer certificate chain.
  SPtr<ROAPCertificateChain> chain;

  //! Rights issuer URL (where to send requests etc.).
  NZSPtr<URIValue> url;

  //! Rights issuer selected version.
  SPtr<ROAPVersion> version;

  //! Rights issuer trusted root authorities.
  SPtr<ROAPKeyIdentifiers> trusted;

  //! Supported algorithms.
	std::vector<NZSPtr<URIValue> > algorithms;

  //! Certificate caching capability.
  SPtr<CertCachingExtension> caching;

  //! Rights issuer OCSP responses.
  std::vector<Base64StringT> ocsps;

  //! Domain name white list.
  SPtr<DomainNameWhiteListExtension> whitelist;

  //! Rights issuer server information.
  SPtr<ROAPServerInfo> serverInfo;
};

/*! \brief  Rights issuer context, kept by the agent.
*/
class AgentRIContext: public GC {
public:
  /*! \brief  Update right issuer context with new informations.

      \param  ctx         input, temporary rights issuer context.
  */
  virtual void UpdateContext(const NZSPtr<TempAgentRIContext>& ctx) = 0;

  /*! \brief  Update right issuer context.

      Update with new certificate chain and new public certificate.
  
      \param  cchain              input, rights issuer certificate chain.
      \param  cer                 input, rights issuer public key.
  */
  virtual void UpdateContext(const NZSPtr<ROAPCertificateChain>& cchain,
    const NZSPtr<OMAPublicCertificate>& cer) = 0;

  /*! \brief  Create peer key identifier, used in protocols.

      \param  crit          input, whether extension has to be critical or not.

      \returns  Peer key identifier extension.
  */
  NZSPtr<PeerKeyIdExtension> CreatePeerKeyId(bool crit) const {
    if (crit) {
      return new CriticalPeerKeyIdExtension(GetKeyID());
    }
    return new PeerKeyIdExtension(GetKeyID());
  }

  /*! \brief  Get rights issuer public certificate.

      \returns  Rights issuer public certificate.
  */
  virtual const NZSPtr<OMAPublicCertificate>& GetPublicCert() const = 0;

  /*! \brief  Get rights issuer key identifier.

      \returns  Rights issuer key identifier.
  */
  const NZSPtr<ROAPKeyIdentifier>& GetKeyID() const {
    return GetID()->GetKeyID();
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  virtual const NZSPtr<ROAPIdentifier>& GetID() const = 0;

  /*! \brief  Get rights issuer URL (where to send requests etc.).

      \returns  Rights issuer URL.
  */
  virtual const NZSPtr<URIValue>& GetURL() const = 0;

  /*! \brief  Get rights issuer version.

      \returns  Rights issuer version.
  */
  virtual const NZSPtr<ROAPVersion>& GetVersion() const = 0;

  /*! \brief  Get rights issuer trusted root authorities.

      \returns  Rights issuer trusted root authorities.
  */
  virtual const SPtr<ROAPKeyIdentifiers>& GetTrusted() const = 0;

  /*! \brief  Get supported algorithms.
  
      \todo: Handle different kinds of algorithms.

      Default algorithms (hash, mac, key wrap, signature):
      Hash algorithms:
      SHA-1: http://www.w3.org/2000/09/xmldsig#sha1.
      MAC algorithms:
      HMAC-SHA-1: http://www.w3.org/2000/09/xmldsig#hmac-sha1.
      Signature algorithms:
      RSA-PSS-Default: http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsa-pss-default.
      Key transport algorithms:
      RSAES-KEM-KDF2-KW-AES128:
      http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsaes-kem-kdf2-kw-aes128.
      Key wrapping algorithms:
      AES-WRAP: http://www.w3.org/2001/04/xmlenc#kw-aes128.

      \returns  Supported algorithms.
  */
  virtual const std::vector<NZSPtr<URIValue> >& GetAlgorithms() const = 0;

  /*! \brief  Get device certificate chain.
  
      Depends on rights issuer's caching capability: if it has caching capability,
      this will be 0 (no need to send certificate chain again), if it doesn't have
      caching capability, this will be != 0, device certificate chain.

      \returns  Device certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetDeviceCertChain() const = 0;

  /*! \brief  Get rights issuer OCSP responses.

      \returns  Rights issuer OCSP responses.
  */
  virtual const std::vector<Base64StringT>& GetOCSPResponses() const = 0;

  /*! \brief  Get domain name white list.
  
      Used for retrieving rights objects triggered by silent and preview
      headers in DCF files.

      \returns  Domain name white list.
  */
  virtual const SPtr<DomainNameWhiteListExtension>& GetDomainNameWhiteList() const = 0;

  /*! \brief  Get rights issuer server information.

      \returns  Rights issuer server information.
  */
  virtual const SPtr<ROAPServerInfo>& GetServerInfo() const = 0;

  /*! \brief  Get rights issuer certificate chain (for key verification).

      \returns  Rights issuer certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetCertChain() const = 0;
};

/*! \brief  Rights issuer context, kept by the agent with caching capability.

    Default assumption is that rights issuer has certificate caching capability.
*/
class CacheAgentRIContext: public AgentRIContext {
public:
  /*! \brief  Constructor.

      \param  cer                 rights issuer public certificate.
      \param  id                  rights issuer identifier.
      \param  cchain              rights issuer certificate chain.
      \param  riurl               rights issuer URL.
      \param  ver                 rights issuer version.
      \param  trust               rights issuer trusted authorities.
      \param  algs                rights issuer supported algorithms.
      \param  ocspresp            rights issuer OCSP responses.
      \param  wlist               domain name white list.
      \param  serverinf           server info.
  */
  CacheAgentRIContext(const NZSPtr<OMAPublicCertificate>& cer,
    const NZSPtr<ROAPIdentifier>& id, const NZSPtr<ROAPCertificateChain>& cchain,
    const NZSPtr<URIValue>& riurl, const NZSPtr<ROAPVersion>& ver,
    const SPtr<ROAPKeyIdentifiers>& trust, const std::vector<NZSPtr<URIValue> >& algs,
    const std::vector<Base64StringT>& ocspresp,
    const SPtr<DomainNameWhiteListExtension>& wlist,
    const SPtr<ROAPServerInfo>& serverinf): publicCert(cer), riID(id),
    chain(cchain), url(riurl), version(ver), trusted(trust), algorithms(algs),
    ocsps(ocspresp), whitelist(wlist), serverInfo(serverinf) {
  }

  /*! \brief  Update right issuer context with new informations.

      \param  ctx         input, temporary rights issuer context.
  */
  virtual void UpdateContext(const NZSPtr<TempAgentRIContext>& ctx) {
    if (ctx->publicCert != 0) {
      publicCert = ctx->publicCert;
    }
    if (ctx->riID != 0) {
      riID = ctx->riID;
    }
    if (ctx->chain != 0) {
      chain = ctx->chain;
    }
    url = ctx->url;
    if (ctx->version != 0) {
      version = ctx->version;
    }
    if (ctx->trusted != 0) {
      trusted = ctx->trusted;
    }
    if (ctx->algorithms.size() != 0) {
      algorithms = ctx->algorithms;
    }
    if (ctx->ocsps.size() != 0) {
      ocsps = ctx->ocsps;
    }
    if (ctx->whitelist != 0) {
      whitelist = ctx->whitelist;
    }
    if (ctx->serverInfo != 0) {
      serverInfo = ctx->serverInfo;
    }
  }

  /*! \brief  Update right issuer context.

      Update with new certificate chain and new public certificate.
  
      \param  cchain              input, rights issuer certificate chain.
      \param  cer                 input, rights issuer public certificate.
  */
  virtual void UpdateContext(const NZSPtr<ROAPCertificateChain>& cchain,
      const NZSPtr<OMAPublicCertificate>& cer) {
    chain = cchain;
    publicCert = cer;
  }

  /*! \brief  Get rights issuer public certificate.

      \returns  Rights issuer public certificate.
  */
  virtual const NZSPtr<OMAPublicCertificate>& GetPublicCert() const {
    return publicCert;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  virtual const NZSPtr<ROAPIdentifier>& GetID() const {
    return riID;
  }

  /*! \brief  Get rights issuer URL (where to send requests etc.).

      \returns  Rights issuer URL.
  */
  virtual const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get rights issuer version.

      \returns  Rights issuer version.
  */
  virtual const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Get rights issuer trusted root authorities.

      \returns  Rights issuer trusted root authorities.
  */
  virtual const SPtr<ROAPKeyIdentifiers>& GetTrusted() const {
    return trusted;
  }

  /*! \brief  Get supported algorithms.
  
      \todo: Handle different kinds of algorithms.

      Default algorithms (hash, mac, key wrap, signature):
      Hash algorithms:
      SHA-1: http://www.w3.org/2000/09/xmldsig#sha1.
      MAC algorithms:
      HMAC-SHA-1: http://www.w3.org/2000/09/xmldsig#hmac-sha1.
      Signature algorithms:
      RSA-PSS-Default: http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsa-pss-default.
      Key transport algorithms:
      RSAES-KEM-KDF2-KW-AES128:
      http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsaes-kem-kdf2-kw-aes128.
      Key wrapping algorithms:
      AES-WRAP: http://www.w3.org/2001/04/xmlenc#kw-aes128.

      \returns  Supported algorithms.
  */
  virtual const std::vector<NZSPtr<URIValue> >& GetAlgorithms() const {
    return algorithms;
  }

  /*! \brief  Get device certificate chain.
  
      Depends on rights issuer's caching capability: if it has caching capability,
      this will be 0 (no need to send certificate chain again), if it doesn't have
      caching capability, this will be != 0, device certificate chain.

      Deafult is rights issuer with certificate caching capability.

      \returns  Device certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetDeviceCertChain() const {
    return 0;
  }

  /*! \brief  Get rights issuer OCSP responses.

      \returns  Rights issuer OCSP responses.
  */
  virtual const std::vector<Base64StringT>& GetOCSPResponses() const {
    return ocsps;
  }

  /*! \brief  Get domain name white list.
  
      Used for retrieving rights objects triggered by silent and preview
      headers in DCF files.

      \returns  Domain name white list.
  */
  virtual const SPtr<DomainNameWhiteListExtension>& GetDomainNameWhiteList() const {
    return whitelist;
  }

  /*! \brief  Get rights issuer server information.

      \returns  Rights issuer server information.
  */
  virtual const SPtr<ROAPServerInfo>& GetServerInfo() const {
    return serverInfo;
  }

  /*! \brief  Get rights issuer certificate chain (for key verification).

      \returns  Rights issuer certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetCertChain() const {
    return chain;
  }

  /*! \brief  Encode as XML string.

      \param  encoded       output, encoded XML string.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(std::string& encoded);

protected:
  NZSPtr<OMAPublicCertificate> publicCert;
  NZSPtr<ROAPIdentifier> riID;
  NZSPtr<ROAPCertificateChain> chain;
  NZSPtr<URIValue> url;
  NZSPtr<ROAPVersion> version;
  SPtr<ROAPKeyIdentifiers> trusted;
	std::vector<NZSPtr<URIValue> > algorithms;
  std::vector<Base64StringT> ocsps;
  SPtr<DomainNameWhiteListExtension> whitelist;
  SPtr<ROAPServerInfo> serverInfo;
};

/*! \brief  Rights issuer without caching capability context, kept by the agent
            with caching capability.
*/
class CacheAgentNCacheRIContext: public CacheAgentRIContext {
public:
  /*! \brief  Constructor.

      \param  cer                 rights issuer public certificate.
      \param  id                  rights issuer identifier.
      \param  cchain              rights issuer certificate chain.
      \param  riurl               rights issuer URL.
      \param  ver                 rights issuer version.
      \param  trust               rights issuer trusted authorities.
      \param  algs                rights issuer supported algorithms.
      \param  ocspresp            rights issuer OCSP responses.
      \param  wlist               domain name white list.
      \param  serverinf           server info.
      \param  devchain            device certificate chain.
  */
  CacheAgentNCacheRIContext(const NZSPtr<OMAPublicCertificate>& cer, const
    NZSPtr<ROAPIdentifier>& id, const NZSPtr<ROAPCertificateChain>& cchain,
    const NZSPtr<URIValue>& riurl, const NZSPtr<ROAPVersion>& ver, const
    SPtr<ROAPKeyIdentifiers>& trust, const std::vector<NZSPtr<URIValue> >& algs,
    const std::vector<Base64StringT>& ocspresp, const SPtr<DomainNameWhiteListExtension>&
    wlist, const SPtr<ROAPServerInfo>& serverinf, const NZSPtr<ROAPCertificateChain>&
    devchain): CacheAgentRIContext(cer, id, cchain, riurl, ver, trust, algs,
    ocspresp, wlist, serverinf), deviceChain(devchain) {
  }

  /*! \brief  Get device certificate chain.
  
      Depends on rights issuer's caching capability: if it has caching capability,
      this will be 0 (no need to send certificate chain again), if it doesn't have
      caching capability, this will be != 0, device certificate chain.

      \returns  Device certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetDeviceCertChain() const {
    return deviceChain;
  }

private:
  NZSPtr<ROAPCertificateChain> deviceChain;
};

/*! \brief  Rights issuer context, kept by the agent without caching capability.

    Default assumption is that rights issuer has certificate caching capability.
*/
class NCacheAgentRIContext: public AgentRIContext {
public:
  /*! \brief  Constructor.

      \param  cer                 rights issuer public certificate.
      \param  id                  rights issuer identifier.
      \param  riurl               rights issuer URL.
      \param  ver                 rights issuer version.
      \param  trust               rights issuer trusted authorities.
      \param  algs                rights issuer supported algorithms.
      \param  ocspresp            rights issuer OCSP responses.
      \param  wlist               domain name white list.
      \param  serverinf           server info.
  */
  NCacheAgentRIContext(const NZSPtr<OMAPublicCertificate>& cer,
    const NZSPtr<ROAPIdentifier>& id, const NZSPtr<URIValue>& riurl,
    const NZSPtr<ROAPVersion>& ver, const SPtr<ROAPKeyIdentifiers>& trust,
    const std::vector<NZSPtr<URIValue> >& algs, const std::vector<Base64StringT>&
    ocspresp, const SPtr<DomainNameWhiteListExtension>& wlist, const
    SPtr<ROAPServerInfo>& serverinf): publicCert(cer), riID(id), url(riurl), version(ver),
    trusted(trust), algorithms(algs), ocsps(ocspresp), whitelist(wlist),
    serverInfo(serverinf) {
  }

  /*! \brief  Update right issuer context with new informations.

      \param  ctx         input, temporary rights issuer context.
  */
  virtual void UpdateContext(const NZSPtr<TempAgentRIContext>& ctx) {
    if (ctx->publicCert != 0) {
      publicCert = ctx->publicCert;
    }
    if (ctx->riID != 0) {
      riID = ctx->riID;
    }
    url = ctx->url;
    if (ctx->version != 0) {
      version = ctx->version;
    }
    if (ctx->trusted != 0) {
      trusted = ctx->trusted;
    }
    if (ctx->algorithms.size() != 0) {
      algorithms = ctx->algorithms;
    }
    if (ctx->ocsps.size() != 0) {
      ocsps = ctx->ocsps;
    }
    if (ctx->whitelist != 0) {
      whitelist = ctx->whitelist;
    }
    if (ctx->serverInfo != 0) {
      serverInfo = ctx->serverInfo;
    }
  }

  /*! \brief  Update right issuer context.

      Update with new certificate chain and new public certificate.
  
      \param  cchain              input, rights issuer certificate chain.
      \param  cer                 input, rights issuer public certificate.
  */
  virtual void UpdateContext(const NZSPtr<ROAPCertificateChain>& cchain,
      const NZSPtr<OMAPublicCertificate>& cer) {
    publicCert = cer;
  }

  /*! \brief  Get rights issuer public certificate.

      \returns  Rights issuer public certificate.
  */
  virtual const NZSPtr<OMAPublicCertificate>& GetPublicCert() const {
    return publicCert;
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  virtual const NZSPtr<ROAPIdentifier>& GetID() const {
    return riID;
  }

  /*! \brief  Get rights issuer URL (where to send requests etc.).

      \returns  Rights issuer URL.
  */
  virtual const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get rights issuer version.

      \returns  Rights issuer version.
  */
  virtual const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Get rights issuer trusted root authorities.

      \returns  Rights issuer trusted root authorities.
  */
  virtual const SPtr<ROAPKeyIdentifiers>& GetTrusted() const {
    return trusted;
  }

  /*! \brief  Get supported algorithms.
  
      \todo: Handle different kinds of algorithms.

      Default algorithms (hash, mac, key wrap, signature):
      Hash algorithms:
      SHA-1: http://www.w3.org/2000/09/xmldsig#sha1.
      MAC algorithms:
      HMAC-SHA-1: http://www.w3.org/2000/09/xmldsig#hmac-sha1.
      Signature algorithms:
      RSA-PSS-Default: http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsa-pss-default.
      Key transport algorithms:
      RSAES-KEM-KDF2-KW-AES128:
      http://www.rsasecurity.com/rsalabs/pkcs/schemas/pkcs-1#rsaes-kem-kdf2-kw-aes128.
      Key wrapping algorithms:
      AES-WRAP: http://www.w3.org/2001/04/xmlenc#kw-aes128.

      \returns  Supported algorithms.
  */
  virtual const std::vector<NZSPtr<URIValue> >& GetAlgorithms() const {
    return algorithms;
  }

  /*! \brief  Get device certificate chain.
  
      Depends on rights issuer's caching capability: if it has caching capability,
      this will be 0 (no need to send certificate chain again), if it doesn't have
      caching capability, this will be != 0, device certificate chain.

      Deafult is rights issuer with certificate caching capability.

      \returns  Device certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetDeviceCertChain() const {
    return 0;
  }

  /*! \brief  Get rights issuer OCSP responses.

      \returns  Rights issuer OCSP responses.
  */
  virtual const std::vector<Base64StringT>& GetOCSPResponses() const {
    return ocsps;
  }

  /*! \brief  Get domain name white list.
  
      Used for retrieving rights objects triggered by silent and preview
      headers in DCF files.

      \returns  Domain name white list.
  */
  virtual const SPtr<DomainNameWhiteListExtension>& GetDomainNameWhiteList() const {
    return whitelist;
  }

  /*! \brief  Get rights issuer server information.

      \returns  Rights issuer server information.
  */
  virtual const SPtr<ROAPServerInfo>& GetServerInfo() const {
    return serverInfo;
  }

  /*! \brief  Get rights issuer certificate chain (for key verification).

      \returns  Rights issuer certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetCertChain() const {
    return 0;
  }

  /*! \brief  Encode as XML string.

      \param  encoded       output, encoded XML string.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(std::string& encoded);

protected:
  NZSPtr<OMAPublicCertificate> publicCert;
  NZSPtr<ROAPIdentifier> riID;
  NZSPtr<URIValue> url;
  NZSPtr<ROAPVersion> version;
  SPtr<ROAPKeyIdentifiers> trusted;
	std::vector<NZSPtr<URIValue> > algorithms;
  std::vector<Base64StringT> ocsps;
  SPtr<DomainNameWhiteListExtension> whitelist;
  SPtr<ROAPServerInfo> serverInfo;
};

/*! \brief  Rights issuer without certificate caching capability context, kept
            by the agent without caching capability.
*/
class NCacheAgentNCacheRIContext: public NCacheAgentRIContext {
public:
  /*! \brief  Constructor.

      \param  cer                 rights issuer public certificate.
      \param  id                  rights issuer identifier.
      \param  riurl               rights issuer URL.
      \param  ver                 rights issuer version.
      \param  trust               rights issuer trusted authorities.
      \param  algs                rights issuer supported algorithms.
      \param  ocspresp            rights issuer OCSP responses.
      \param  wlist               domain name white list.
      \param  serverinf           server info.
      \param  devchain            device certificate chain.
  */
  NCacheAgentNCacheRIContext(const NZSPtr<OMAPublicCertificate>& cer,
    const NZSPtr<ROAPIdentifier>& id, const NZSPtr<URIValue>& riurl,
    const NZSPtr<ROAPVersion>& ver, const SPtr<ROAPKeyIdentifiers>& trust,
    const std::vector<NZSPtr<URIValue> >& algs,
    const std::vector<Base64StringT>& ocspresp,
    const SPtr<DomainNameWhiteListExtension>& wlist,
    const SPtr<ROAPServerInfo>& serverinf,
    const NZSPtr<ROAPCertificateChain>& devchain):
    NCacheAgentRIContext(cer, id, riurl, ver, trust, algs, ocspresp, wlist,
    serverinf), deviceChain(devchain) {
  }

  /*! \brief  Get device certificate chain.
  
      Depends on rights issuer's caching capability: if it has caching capability,
      this will be 0 (no need to send certificate chain again), if it doesn't have
      caching capability, this will be != 0, device certificate chain.

      Deafult is rights issuer with certificate caching capability.

      \returns  Device certificate chain.
  */
  virtual SPtr<ROAPCertificateChain> GetDeviceCertChain() const {
    return deviceChain;
  }

private:
  NZSPtr<ROAPCertificateChain> deviceChain;
};

/*! \brief  Current agent registration database.

    It is the result of initialization and all registration sessions performed.
*/
class AgentRegDatabase: public GC {
public:
  virtual ~AgentRegDatabase() {
  }

  /*! \brief  Find (if exists) rights issuer context corresponding to URL.
  
      Used in fetching decryption keys in DCFs.

      \param  riURL           input, rights issuer URL.

      \returns  Rights issuer context. If zero, context was not found.
  */
  virtual SPtr<AgentRIContext> GetRIContext(const NZSPtr<URIValue>& riURL) = 0;

  /*! \brief  Find (if exists) rights issuer context corresponding to the identifier.

      \param  riID            input, rights issuer identifier.

      \returns  Rights issuer context. If zero, context was not found.
  */
  virtual SPtr<AgentRIContext> GetRIContext(const NZSPtr<ROAPIdentifier>& riID) = 0;

  /*! \brief  Find (if exists) domain info (contains a domain key) corresponding
              to the domain identifier.

      \param  domainID        input, domain identifier.

      \returns  Domain info. If zero, info was not found.
  */
  virtual SPtr<ROAPDomainInfo> GetDomainInfo(const NZSPtr<ROAPDomainIdentifier>&
    domainID) = 0;

  /*! \brief  Add a new rights issuer context.

      \param  riCtx               input, context to be added.
      \param  device              input, device context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddRI(const NZSPtr<TempAgentRIContext>& riCtx, const
    NZSPtr<AgentDeviceContext>& device) = 0;

  /*! \brief  Add a new domain.

      \param  domainID            input, domain identifier.
      \param  info                input, domain info.
  */
  virtual void AddDomain(const NZSPtr<ROAPDomainIdentifier>& domainID,
    const NZSPtr<ROAPDomainInfo>& info) = 0;

  /*! \brief  Remove domain.

      \param  domainID            input, domain identifier.
  */
  virtual void RemoveDomain(const NZSPtr<ROAPDomainIdentifier>& domainID) = 0;

  /*! \brief  Save database for future use.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase() = 0;
};

/*! \brief  Caching agent registration database.
*/
class CacheAgentRegDatabase: public AgentRegDatabase {
public:
  /*! \brief  Constructor.
  */
  CacheAgentRegDatabase();

  /*! \brief  Constructor.

      \param  ritocontext     rights issuer identifier to context map.
      \param  domaintoinfo    domain identifier to domain info map.
  */
  CacheAgentRegDatabase(
    const std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheAgentRIContext> >& ritocontext,
    const std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> >& domaintoinfo);

  /*! \brief  Find (if exists) rights issuer context corresponding to URL.
  
      Used in fetching decryption keys in DCFs.

      \param  riURL           input, rights issuer URL.

      \returns  Rights issuer context. If zero, context was not found.
  */
  virtual SPtr<AgentRIContext> GetRIContext(const NZSPtr<URIValue>& riURL);

  /*! \brief  Find (if exists) rights issuer context corresponding to the identifier.

      \param  riID            input, rights issuer identifier.

      \returns  Rights issuer context. If zero, context was not found.
  */
  virtual SPtr<AgentRIContext> GetRIContext(const NZSPtr<ROAPIdentifier>& riID);

  /*! \brief  Find (if exists) domain info (contains a domain key) corresponding
              to the domain identifier.

      \param  domainID        input, domain identifier.

      \returns  Domain info. If zero, info was not found.
  */
  virtual SPtr<ROAPDomainInfo> GetDomainInfo(const NZSPtr<ROAPDomainIdentifier>&
    domainID);

  /*! \brief  Add a new rights issuer context.

      \param  riCtx               input, context to be added.
      \param  device              input, device context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddRI(const NZSPtr<TempAgentRIContext>& riCtx,
    const NZSPtr<AgentDeviceContext>& device);

  /*! \brief  Add a new domain.

      \param  domainID            input, domain identifier.
      \param  info                input, domain info.
  */
  virtual void AddDomain(const NZSPtr<ROAPDomainIdentifier>& domainID,
    const NZSPtr<ROAPDomainInfo>& info);

  /*! \brief  Remove domain.

      \param  domainID            input, domain identifier.
  */
  virtual void RemoveDomain(const NZSPtr<ROAPDomainIdentifier>& domainID);

  /*! \brief  Save database for future use.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

protected:
  std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheAgentRIContext> > riIDToContext;
  std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> > domainIDToInfo;
};

/*! \brief  Non-caching agent registration database.
*/
class NCacheAgentRegDatabase: public AgentRegDatabase {
public:
  /*! \brief  Constructor.
  */
  NCacheAgentRegDatabase();

  /*! \brief  Constructor.

      \param  ritocontext     rights issuer identifier to context map.
      \param  domaintoinfo    domain identifier to domain info map.
  */
  NCacheAgentRegDatabase(
    const std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheAgentRIContext> >& ritocontext,
    const std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> >& domaintoinfo);

  /*! \brief  Find (if exists) rights issuer context corresponding to URL.
  
      Used in fetching decryption keys in DCFs.

      \param  riURL           input, rights issuer URL.

      \returns  Rights issuer context. If zero, context was not found.
  */
  virtual SPtr<AgentRIContext> GetRIContext(const NZSPtr<URIValue>& riURL);

  /*! \brief  Find (if exists) rights issuer context corresponding to the identifier.

      \param  riID            input, rights issuer identifier.

      \returns  Rights issuer context. If zero, context was not found.
  */
  virtual SPtr<AgentRIContext> GetRIContext(const NZSPtr<ROAPIdentifier>& riID);

  /*! \brief  Find (if exists) domain info (contains a domain key) corresponding
              to the domain identifier.

      \param  domainID        input, domain identifier.

      \returns  Domain info. If zero, info was not found.
  */
  virtual SPtr<ROAPDomainInfo> GetDomainInfo(const NZSPtr<ROAPDomainIdentifier>&
    domainID);

  /*! \brief  Add a new rights issuer context.

      \param  riCtx               input, context to be added.
      \param  device              input, device context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddRI(const NZSPtr<TempAgentRIContext>& riCtx,
    const NZSPtr<AgentDeviceContext>& device);

  /*! \brief  Add a new domain.

      \param  domainID            input, domain identifier.
      \param  info                input, domain info.
  */
  virtual void AddDomain(const NZSPtr<ROAPDomainIdentifier>& domainID,
    const NZSPtr<ROAPDomainInfo>& info);

  /*! \brief  Remove domain.

      \param  domainID            input, domain identifier.
  */
  virtual void RemoveDomain(const NZSPtr<ROAPDomainIdentifier>& domainID);

  /*! \brief  Save database for future use.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

protected:
  std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheAgentRIContext> > riIDToContext;
  std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> > domainIDToInfo;
};

/*! \brief  Current agent rights objects database.

    It is the result of all rights objects acquisition sessions performed.
*/
class AgentRODatabase: public GC {
public:
  /*! \brief  Constructor.
  */
  AgentRODatabase();

  /*! \brief  Constructor.

      \param  contenttoro     content identifier to protected rights objects map.
      \param  rotodom         rights objects identifier to domain identifier map.
  */
  AgentRODatabase(const std::map<NZSPtr<URIValue>, SPtr<ROAPProtectedRO> >&
    contenttoro, const std::map<NZSPtr<IDValue>, SPtr<ROAPDomainIdentifier> >&
    rotodom);

  virtual ~AgentRODatabase() {
    SaveDatabase();
  }

  /*! \brief  Get (if exist) protected rights object corresponding to content
              identifier.

      Protected rights objects have content encryption key encrypted with
      device's public key.
      If finds protected rights objects, checks payload signature. If signature
      verification fails, returns 0.

      \param  contentID               input, content identifier.
      \param  ri                      input, rights issuer context.

      \returns  Protected rights object. If zero, none was found, or payload
                signature verification failed.
  */
  SPtr<ROAPProtectedRO> GetRO(const NZSPtr<URIValue>& contentID,
    const NZSPtr<AgentRIContext>& ri);

  /*! \brief  Get (if exist) domain identifier corresponding to rights
              objects identifier.

      \param  roID                    input, rights objects identifier.

      \returns  Domain identifier. If zero, none was found.
  */
  SPtr<ROAPDomainIdentifier> GetDomainID(const NZSPtr<IDValue>& roID);

  /*! \brief  Add a (content identifier, protected rights objects) pair.

      \param  contentID             input, content identifier.
      \param  protRO                input, protected rights objects.
  */
  void AddRO(const NZSPtr<URIValue>& contentID, const NZSPtr<ROAPProtectedRO>& protRO);

  /*! \brief  Add a (rights objects identifier, domain identifier) pair.

      \param  roID                  input, rights objects identifier.
      \param  domainID              input, domain identifier.
  */
  void AddRODomainID(const NZSPtr<IDValue>& roID, const NZSPtr<ROAPDomainIdentifier>&
    domainID);

  /*! \brief  Save database for future use.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

protected:
  /*! \brief  Map from content ID to protected rights objects.
  
      Contains all data gathered so far about rights for contents. Protected
      rights objects contain content encryption keys encrypted with device's
      public key.
  */
  std::map<NZSPtr<URIValue>, SPtr<ROAPProtectedRO> > contentIDToRO;

  /*! \brief  Map from rights objects ID to domain ID.
  
      Contains rights objects ids that correspond to domains. Protected rights
      objects corresponding to these rights objects ids contain content encryption
      keys encrypted with domain's public key. This map should be combined with
      GetDomainInfo() from registration database to get domain key and decrypt
      content encryption key.
  */
  std::map<NZSPtr<IDValue>, SPtr<ROAPDomainIdentifier> > roIDToDom;
};

} // namespace DRMPlugin

#endif // !defined (AGENTBASE_H)
