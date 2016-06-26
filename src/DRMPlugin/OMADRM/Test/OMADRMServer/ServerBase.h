/** \file ServerBase.h

    Test server context and tools.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (SERVERBASE_H)
#define SERVERBASE_H

#include "OMADRMCrypto.h"
#include <map>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Rights issuer context, kept by the server.
*/
class ServerRIContext: public GC {
public:
  /*! \brief  Constructor.

      \param  cer               rights issuer public certificate.
      \param  pri               rights issuer private key.
      \param  riid              rights issuer identifier.
      \param  cchain            rights issuer certificate chain.
      \param  trust             trusted authorities identifiers.
      \param  trustcerts        trusted authorities certificates.
      \param  algs              supported algorithms.
      \param  ccaching          certificate caching.
      \param  ver               version.
      \param  riurl             rights issuer URL.
      \param  ocspresp          OCSP responses.
      \param  wlist             domain name white list.
      \param  sinfo             server info.
  */
  ServerRIContext(const NZSPtr<OMAPublicCertificate>& cer, const NZSPtr<OMAPrivateKey>& pri,
    const NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPCertificateChain>& cchain,
    const SPtr<ROAPKeyIdentifiers>& trust, const std::vector<Base64StringT>& trustcerts,
    const std::vector<NZSPtr<URIValue> >& algs, const SPtr<CertCachingExtension>& ccaching,
    const NZSPtr<ROAPVersion>& ver, const NZSPtr<URIValue>& riurl, const
    std::vector<Base64StringT>& ocspresp, const SPtr<DomainNameWhiteListExtension>&
    wlist, const SPtr<ROAPServerInfo>& sinfo);

  /*! \brief  Get rights issuer public certificate.

      \returns  Rights issuer public certificate.
  */
  const NZSPtr<OMAPublicCertificate>& GetPublicCert() const {
    return publicCert;
  }

  /*! \brief  Get rights issuer private key.

      \returns  Rights issuer private key.
  */
  const NZSPtr<OMAPrivateKey>& GetPrivateKey() const {
    return privateKey;
  }

  /*! \brief  Get rights issuer key identifier.

      \returns  Rights issuer key identifier.
  */
  const NZSPtr<ROAPKeyIdentifier>& GetKeyID() const {
    return riID->GetKeyID();
  }

  /*! \brief  Get rights issuer identifier.

      \returns  Rights issuer identifier.
  */
  const NZSPtr<ROAPIdentifier>& GetID() const {
    return riID;
  }

  /*! \brief  Get rights issuer certificate chain.

      \returns  Rights issuer certificate chain.
  */
  const NZSPtr<ROAPCertificateChain>& GetCertChain() const {
    return chain;
  }

  /*! \brief  Get rights issuer trusted root authorities.
  
      These are used to ensure that device certificate chain roots at
      one of these authorities, otherwise rights issuer will reject device
      requests etc. If trusted authorities is empty, it signals the device
      that it can send any certificate chain.

      \returns Rights issuer trusted root authorities.
  */
  const SPtr<ROAPKeyIdentifiers>& GetTrusted() const {
    return trusted;
  }

  /*! \brief  Get rights issuer trusted root authorities certificates.

      \todo: These should correspond to trusted authorities key identifiers.

      \returns  Rights issuer trusted root authorities certificates.
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

  /*! \brief  Get rights issuer certificate caching capability.
  
      If rights issuer doesn't have certificate caching capability, then
      device has to send complete certificate chain each time.

      \returns  Rights issuer certificate caching capability.
  */
  SPtr<CertCachingExtension> GetCertCaching() const {
    return caching;
  }

  /*! \brief  Get rights issuer version.

      \returns  Rights issuer version.
  */
  const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Get rights issuer URL (where to send requests etc.).

      \returns  Rights issuer URL.
  */
  const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get rights issuer OCSP responses.

      \returns  Rights issuer OCSP responses.
  */
  const std::vector<Base64StringT>& GetOCSPResponses() const {
    return ocsps;
  }

  /*! \brief  Get domain name white list.
  
      Used for retrieving rights objects triggered by silent and preview
      headers in DCF files.

      \returns  Domain name white list.
  */
  const SPtr<DomainNameWhiteListExtension>& GetDomainNameWhiteList() const {
    return whitelist;
  }

  /*! \brief  Get rights issuer server information.

      \returns  Rights issuer server information.
  */
  const SPtr<ROAPServerInfo>& GetServerInfo() const {
    return serverInfo;
  }

private:
  NZSPtr<OMAPublicCertificate> publicCert;
  NZSPtr<OMAPrivateKey> privateKey;
  NZSPtr<ROAPIdentifier> riID;
  NZSPtr<ROAPCertificateChain> chain;
  SPtr<ROAPKeyIdentifiers> trusted;
  std::vector<Base64StringT> trustedCerts;
	std::vector<NZSPtr<URIValue> > algorithms;
  SPtr<CertCachingExtension> caching;
  NZSPtr<ROAPVersion> version;
  NZSPtr<URIValue> url;
  std::vector<Base64StringT> ocsps;
  SPtr<DomainNameWhiteListExtension> whitelist;
  SPtr<ROAPServerInfo> serverInfo;
};

/*! \brief  Temporary device context, used in registration session.
*/
class TempServerDeviceContext: public GC {
public:
  /*! \brief  Constructor.

      \param  cer               device public certificate.
      \param  id                device identifier.
      \param  cchain            device certificate chain.
      \param  devurl            device URL.
      \param  trust             device trusted authorities.
      \param  algs              device supported algorithms.
      \param  ddetails          device details.
      \param  ccaching          device certificate caching.
      \param  ver               device version.
  */
  TempServerDeviceContext(const SPtr<OMAPublicCertificate>& cer, const NZSPtr<ROAPIdentifier>&
    id, const SPtr<ROAPCertificateChain>& cchain, const NZSPtr<URIValue>& devurl,
    const SPtr<ROAPKeyIdentifiers>& trust, const std::vector<NZSPtr<URIValue> >&
    algs, const SPtr<DeviceDetailsData>& ddetails, const SPtr<CertCachingExtension>&
    ccaching, const SPtr<ROAPVersion>& ver);

  //! Device public certificate.
  SPtr<OMAPublicCertificate> publicCert;

  //! Device identifier.
  NZSPtr<ROAPIdentifier> deviceID;

  //! Device certificate chain.
  SPtr<ROAPCertificateChain> chain;

  //! Device URL.
  NZSPtr<URIValue> url;

  //! Device trusted root authorities.
  SPtr<ROAPKeyIdentifiers> trusted;

  //! Device supported algorithms.
	std::vector<NZSPtr<URIValue> > algorithms;

  //! Device details (manufacturer, version, etc.).
  SPtr<DeviceDetailsData> details;

  //! Device certificate caching.
  SPtr<CertCachingExtension> caching;

  //! Device version.
  SPtr<ROAPVersion> version;
};

/*! \brief  Device context, kept by the server.
*/
class ServerDeviceContext: public GC {
public:
  /*! \brief  Update device context with new information.

      \param  ctx         input, temporary device context.
  */
  virtual void UpdateContext(const NZSPtr<TempServerDeviceContext>& ctx) = 0;

  /*! \brief  Update device context with new certificate chain and new public certificate.

      \param  cchain            input, certificate chain.
      \param  cer               input, public certificate.
  */
  virtual void UpdateContext(const NZSPtr<ROAPCertificateChain>& cchain,
    const NZSPtr<OMAPublicCertificate>& cer) = 0;

  /*! \brief  Create peer key identifier, used in protocols.

      \param  crit            input, critical peer key identifier flag.

      \returns  Peer key identifier. If zero, failed.
  */
  NZSPtr<PeerKeyIdExtension> CreatePeerKeyId(bool crit) const {
    if (crit == true) {
      return new CriticalPeerKeyIdExtension(GetKeyID());
    }
    return new PeerKeyIdExtension(GetKeyID());
  }

  /*! \brief  Get device certificate chain (if one is saved).
  
      \returns  Device certificate chain. If none was saved, 0.
  */
  virtual SPtr<ROAPCertificateChain> GetCertChain() const = 0;

  /*! \brief  Get device public certificate.

      \returns  Device public certificate.
  */
  virtual const NZSPtr<OMAPublicCertificate>& GetPublicCert() const = 0;

  /*! \brief  Get device key identifier.

      \returns  Device key identifier.
  */
  const NZSPtr<ROAPKeyIdentifier>& GetKeyID() const {
    return GetID()->GetKeyID();
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  virtual const NZSPtr<ROAPIdentifier>& GetID() const = 0;

  /*! \brief  Get device URL (where to send responses etc.).

      \returns  Device URL.
  */
  virtual const NZSPtr<URIValue>& GetURL() const = 0;

  /*! \brief  Get device trusted root authorities.
  
      Uused to ensure that rights issuer certificate chain roots at one of
      these authorities, otherwise device will reject rights issuer responses etc.
      If trusted authorities is empty, it signals rights issuer that it can
      send any certificate chain.

      \returns  Device trusted root authorities.
  */
  virtual const SPtr<ROAPKeyIdentifiers>& GetTrusted() const = 0;

  /*! \brief  Get supported algorithms.
  
      \todo: Handle different kinds of algorithms.
      Device supported algorithms (hash, mac, key wrap, signature).
      Default algorithms:
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

  /*! \brief  Get device details (manufacturer, version, etc.).

      \returns  Device details.
  */
  virtual const SPtr<DeviceDetailsData>& GetDetails() const = 0;

  /*! \brief  Get device version.

      \returns  Device version.
  */
  virtual const NZSPtr<ROAPVersion>& GetVersion() const = 0;
};

/*! \brief  Device context, kept by the server with caching ability.
*/
class CacheServerDeviceContext: public ServerDeviceContext {
public:
  /*! \brief  Constructor.

      \param  cer                 device public certificate.
      \param  id                  device identifier.
      \param  cchain              device certificate chain.
      \param  devurl              device URL.
      \param  trust               device trusted authorities.
      \param  algs                device supported algorithms.
      \param  ddetails            device details.
      \param  ver                 version.
  */
  CacheServerDeviceContext(const NZSPtr<OMAPublicCertificate>& cer, const
    NZSPtr<ROAPIdentifier>& id, const NZSPtr<ROAPCertificateChain>& cchain,
    const NZSPtr<URIValue>& devurl, const SPtr<ROAPKeyIdentifiers>& trust,
    const std::vector<NZSPtr<URIValue> >& algs, const SPtr<DeviceDetailsData>&
    ddetails, const NZSPtr<ROAPVersion>& ver);

  /*! \brief  Update device context with new information.

      \param  ctx         input, temporary device context.
  */
  virtual void UpdateContext(const NZSPtr<TempServerDeviceContext>& ctx);

  /*! \brief  Update device context with new certificate chain and new public certificate.

      \param  cchain            input, certificate chain.
      \param  cer               input, public certificate.
  */
  virtual void UpdateContext(const NZSPtr<ROAPCertificateChain>& cchain,
    const NZSPtr<OMAPublicCertificate>& cer);

  /*! \brief  Get device certificate chain (if one is saved).
  
      \returns  Device certificate chain. If none was saved, 0.
  */
  virtual SPtr<ROAPCertificateChain> GetCertChain() const {
    return chain;
  }

  /*! \brief  Get device public certificate.

      \returns  Device public certificate.
  */
  virtual const NZSPtr<OMAPublicCertificate>& GetPublicCert() const {
    return publicCert;
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  virtual const NZSPtr<ROAPIdentifier>& GetID() const {
    return deviceID;
  }

  /*! \brief  Get device URL (where to send responses etc.).

      \returns  Device URL.
  */
  virtual const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get device trusted root authorities.
  
      Uused to ensure that rights issuer certificate chain roots at one of
      these authorities, otherwise device will reject rights issuer responses etc.
      If trusted authorities is empty, it signals rights issuer that it can
      send any certificate chain.

      \returns  Device trusted root authorities.
  */
  virtual const SPtr<ROAPKeyIdentifiers>& GetTrusted() const {
    return trusted;
  }

  /*! \brief  Get supported algorithms.
  
      \todo: Handle different kinds of algorithms.
      Device supported algorithms (hash, mac, key wrap, signature).
      Default algorithms:
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

  /*! \brief  Get device details (manufacturer, version, etc.).

      \returns  Device details.
  */
  virtual const SPtr<DeviceDetailsData>& GetDetails() const {
    return details;
  }

  /*! \brief  Get device version.

      \returns  Device version.
  */
  virtual const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Encode as XML string.

      \param  encoded       output, encoded XML string.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(std::string& encoded);

private:
  NZSPtr<OMAPublicCertificate> publicCert;
  NZSPtr<ROAPIdentifier> deviceID;
  NZSPtr<ROAPCertificateChain> chain;
  NZSPtr<URIValue> url;
  SPtr<ROAPKeyIdentifiers> trusted;
	std::vector<NZSPtr<URIValue> > algorithms;
  SPtr<DeviceDetailsData> details;
  NZSPtr<ROAPVersion> version;
};

/*! \brief  Device context, kept by the server without caching capability.
*/
class NCacheServerDeviceContext: public ServerDeviceContext {
public:
  /*! \brief  Constructor.

      \param  cer               device public certificate.
      \param  id                device identifier.
      \param  devurl            device URL.
      \param  trust             device trusted authorities.
      \param  algs              device supported algorithms.
      \param  ddetails          device details.
      \param  ver               device version.
  */
  NCacheServerDeviceContext(const NZSPtr<OMAPublicCertificate>& cer,
    const NZSPtr<ROAPIdentifier>& id, const NZSPtr<URIValue>& devurl,
    const SPtr<ROAPKeyIdentifiers>& trust, const std::vector<NZSPtr<URIValue> >&
    algs, const SPtr<DeviceDetailsData>& ddetails, const NZSPtr<ROAPVersion>& ver);

  /*! \brief  Update device context with new information.

      \param  ctx         input, temporary device context.
  */
  virtual void UpdateContext(const NZSPtr<TempServerDeviceContext>& ctx);

  /*! \brief  Update device context with new certificate chain and new public certificate.

      \param  cchain            input, certificate chain.
      \param  cer               input, public certificate.
  */
  virtual void UpdateContext(const NZSPtr<ROAPCertificateChain>& cchain,
    const NZSPtr<OMAPublicCertificate>& cer);

  /*! \brief  Get device certificate chain (if one is saved).
  
      \returns  Device certificate chain. If none was saved, 0.
  */
  virtual SPtr<ROAPCertificateChain> GetCertChain() const {
    return 0;
  }

  /*! \brief  Get device public certificate.

      \returns  Device public certificate.
  */
  virtual const NZSPtr<OMAPublicCertificate>& GetPublicCert() const {
    return publicCert;
  }

  /*! \brief  Get device identifier.

      \returns  Device identifier.
  */
  virtual const NZSPtr<ROAPIdentifier>& GetID() const {
    return deviceID;
  }

  /*! \brief  Get device URL (where to send responses etc.).

      \returns  Device URL.
  */
  virtual const NZSPtr<URIValue>& GetURL() const {
    return url;
  }

  /*! \brief  Get device trusted root authorities.
  
      Uused to ensure that rights issuer certificate chain roots at one of
      these authorities, otherwise device will reject rights issuer responses etc.
      If trusted authorities is empty, it signals rights issuer that it can
      send any certificate chain.

      \returns  Device trusted root authorities.
  */
  virtual const SPtr<ROAPKeyIdentifiers>& GetTrusted() const {
    return trusted;
  }

  /*! \brief  Get supported algorithms.
  
      \todo: Handle different kinds of algorithms.
      Device supported algorithms (hash, mac, key wrap, signature).
      Default algorithms:
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

  /*! \brief  Get device details (manufacturer, version, etc.).

      \returns  Device details.
  */
  virtual const SPtr<DeviceDetailsData>& GetDetails() const {
    return details;
  }

  /*! \brief  Get device version.

      \returns  Device version.
  */
  virtual const NZSPtr<ROAPVersion>& GetVersion() const {
    return version;
  }

  /*! \brief  Encode as XML string.

      \param  encoded       output, encoded XML string.

      \returns  Boolean indicating success or failure.
  */
  bool Encode(std::string& encoded);

private:
  NZSPtr<OMAPublicCertificate> publicCert;
  NZSPtr<ROAPIdentifier> deviceID;
  NZSPtr<URIValue> url;
  SPtr<ROAPKeyIdentifiers> trusted;
	std::vector<NZSPtr<URIValue> > algorithms;
  SPtr<DeviceDetailsData> details;
  NZSPtr<ROAPVersion> version;
};

/*! \brief  Current server registration database.

    It is the result of initialization and all registration sessions performed.
*/
class ServerRegDatabase: public GC {
public:
  virtual ~ServerRegDatabase() {
  }

  /*! \brief  Find (if exists) device context corresponding to device identifier.

      \param  devID           input, device identifier.

      \returns  Device context. If zero, none was found.
  */
  virtual SPtr<ServerDeviceContext> GetContext(const NZSPtr<ROAPIdentifier>& devID) = 0;

  /*! \brief  Find (if exists) domain info corresponding to domain identifier
              and device identifier.

      Check if device is a member of domain, and if it is, return domain info
      with domain keys encrypted with device's public key.

      \param  devID           input, device identifier.
      \param  domID           input, domain identifier.

      \returns  Domain info. If zero, none was found.
  */
  virtual SPtr<ROAPDomainInfo> GetDomain(const NZSPtr<ROAPIdentifier>& devID,
    const NZSPtr<ROAPDomainIdentifier>& domID) = 0;

  /*! \brief  Add a new device context.

      \param  devCtx            input, temporary device context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddDevice(const NZSPtr<TempServerDeviceContext>& devCtx) = 0;

  /*! \brief  Save database.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase() = 0;
};

/*! \brief  Caching server registration database.
*/
class CacheServerRegDatabase: public ServerRegDatabase {
public:
  /*! \brief  Constructor.
  */
  CacheServerRegDatabase();

  /*! \brief  Constructor.

      \param  devtoctx          device identifier to device context map.
      \param  domtodevtoinfo    domain identifier to device identifier to
                                domain info map.
  */
  CacheServerRegDatabase(
    const std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheServerDeviceContext> >& devtoctx,
    const std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
    SPtr<ROAPDomainInfo> > >& domtodevtoinfo);

  /*! \brief  Find (if exists) device context corresponding to device identifier.

      \param  devID           input, device identifier.

      \returns  Device context. If zero, none was found.
  */
  virtual SPtr<ServerDeviceContext> GetContext(const NZSPtr<ROAPIdentifier>& devID);

  /*! \brief  Find (if exists) domain info corresponding to domain identifier
              and device identifier.

      Check if device is a member of domain, and if it is, return domain info
      with domain keys encrypted with device's public key.

      \param  devID           input, device identifier.
      \param  domID           input, domain identifier.

      \returns  Domain info. If zero, none was found.
  */
  virtual SPtr<ROAPDomainInfo> GetDomain(const NZSPtr<ROAPIdentifier>& devID,
    const NZSPtr<ROAPDomainIdentifier>& domID);

  /*! \brief  Add a new device context.

      \param  devCtx            input, temporary device context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddDevice(const NZSPtr<TempServerDeviceContext>& devCtx);

  /*! \brief  Save database.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

protected:
  std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheServerDeviceContext> > deviceIDToContext;
  std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
    SPtr<ROAPDomainInfo> > > domIDToDevIDToInfo;
};

/*! \brief  Non-caching server registration database.
*/
class NCacheServerRegDatabase: public ServerRegDatabase {
public:
  /*! \brief  Constructor.
  */
  NCacheServerRegDatabase();

  /*! \brief  Constructor.

      \param  devtoctx          device identifier to device context map.
      \param  domtodevtoinfo    domain identifier to device identifier to
                                domain info map.
  */
  NCacheServerRegDatabase(
    const std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheServerDeviceContext> >& devtoctx,
    const std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
    SPtr<ROAPDomainInfo> > >& domtodevtoinfo);

  /*! \brief  Find (if exists) device context corresponding to device identifier.

      \param  devID           input, device identifier.

      \returns  Device context. If zero, none was found.
  */
  virtual SPtr<ServerDeviceContext> GetContext(const NZSPtr<ROAPIdentifier>& devID);

  /*! \brief  Find (if exists) domain info corresponding to domain identifier
              and device identifier.

      Check if device is a member of domain, and if it is, return domain info
      with domain keys encrypted with device's public key.

      \param  devID           input, device identifier.
      \param  domID           input, domain identifier.

      \returns  Domain info. If zero, none was found.
  */
  virtual SPtr<ROAPDomainInfo> GetDomain(const NZSPtr<ROAPIdentifier>& devID,
    const NZSPtr<ROAPDomainIdentifier>& domID);

  /*! \brief  Add a new device context.

      \param  devCtx            input, temporary device context.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddDevice(const NZSPtr<TempServerDeviceContext>& devCtx);

  /*! \brief  Save database.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

protected:
  std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheServerDeviceContext> > deviceIDToContext;
  std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
    SPtr<ROAPDomainInfo> > > domIDToDevIDToInfo;
};

/*! \brief  Current server rights objects database.

    Contains rights for contents issued for devices.
*/
class ServerRODatabase: public GC {
public:
  /*! \brief  Constructor.
  */
  ServerRODatabase();

  virtual ~ServerRODatabase() {
  }

  /*! \brief  Constructor.

      \param  devtocontoro      device identifier to content identifier to
                                rights objects identifier map.
      \param  roidro            rights objects identifier to rights objects map.
  */
/*
  ServerRODatabase(const std::map<NZSPtr<ROAPIdentifier>, std::map<NZSPtr<URIValue>,
    SPtr<IDValue> > >& devtocontoro, const std::map<NZSPtr<IDValue>,
    SPtr<ROAPProtectedRO> >& c): devIDToConIDToROID(devtocontoro),
    roIDToRO(roIDToRO), contentIDToKey(), deviceIDToContentIDToRights(),
    domainIDToContentIDToRights(), roIDToKeyRights() {
  }
*/
  /*! \brief  Update rights objects database.
  
      Add a new devID->conID->roID map, and new roID->ro map.

      \param  devID           input, device identifier.
      \param  conID           input, content identifier.
      \param  roID            input, rights objects identifier.
      \param  ro              input, rights objects.

      \returns  Boolean indicating success or failure.
  */
  bool AddRO(const NZSPtr<ROAPIdentifier>& devID, const NZSPtr<URIValue>& conID,
    const NZSPtr<IDValue>& roID, const NZSPtr<ROAPProtectedRO>& ro);

  /*! \brief  Get rights objects identifier applicable to the content for the device.
  
      Used to build ro acquisition triggers.

      \param  devID           input, device identifier.
      \param  conID           input, content identifier.

      \returns  Rights objects identifier. If zero, none was found.
  */
  SPtr<IDValue> GetROID(const NZSPtr<ROAPIdentifier>& devID, const NZSPtr<URIValue>&
    conID);

  /*! \brief  Get protected rights objects corresponding to rights objects identifier.

      \todo:  Do we want to allow any device to ask for any rights objects,
              even if they are encrypted?

      \param  roID            input, rights objects identifier.

      \returns  Protected rights objects. If zero, none was found.
  */
  SPtr<ROAPProtectedRO> GetRO(const NZSPtr<IDValue>& roID);

  /*! \brief  Add content encryption key.

      \param  contentID         input, content identifier.
      \param  enckey            input, encryption key.
  */
  void AddContentKey(const NZSPtr<URIValue>& contentID, const Base64StringT& enckey);

  /*! \brief  Add rights for device for content.

      \param  deviceID          input, device identifier.
      \param  contentID         input, content identifier.
      \param  rights            input, rights.
  */
  void AddRights(const NZSPtr<ROAPIdentifier>& deviceID, const NZSPtr<URIValue>&
    contentID, const NZSPtr<OEXRights>& rights);

  /*! \brief  Add rights for domain for content.

      \param  domainID          input, domain identifier.
      \param  contentID         input, content identifier.
      \param  rights            input, rights.
  */
  void AddRights(const NZSPtr<ROAPDomainIdentifier>& domainID, const NZSPtr<URIValue>&
    contentID, const NZSPtr<OEXRights>& rights);

  /*! \brief  Set rights objects identifer for device and content.

      \param  roID              input, rights objects identifier.
      \param  deviceID          input, device identifier.
      \param  contentID         input, content identifier.

      \returns  Boolean indicating success or not. If fails, it means that
                either content is not registered as protected, or device does
                not have rights for the content.
  */
  bool SetROID(const NZSPtr<IDValue>& roID, const NZSPtr<ROAPIdentifier>& deviceID,
    const NZSPtr<URIValue>& contentID);

  /*! \brief  Set rights objects identifer for domain and content.

      \param  roID              input, rights objects identifier.
      \param  domainID          input, domain identifier.
      \param  contentID         input, content identifier.

      \returns  Boolean indicating success or not. If fails, it means that
                either content is not registered as protected, or domain does
                not have rights for the content.
  */
  bool SetROID(const NZSPtr<IDValue>& roID, const NZSPtr<ROAPDomainIdentifier>&
    domainID, const NZSPtr<URIValue>& contentID);

  /*! \brief  Get encryption key and rights corresponding to rights objects identifer.

      \param  roID              input, rights objects identifier.
      \param  enckey            output, encryption key.
      \param  rights            output, rights.

      \returns  Boolean indicating if key and rights exist or not.
  */
  bool GetRO(const NZSPtr<IDValue>& roID, Base64StringT& enckey, SPtr<OEXRights>& rights);

  /*! \brief  Save database.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

protected:
  std::map<NZSPtr<ROAPIdentifier>, std::map<NZSPtr<URIValue>, SPtr<IDValue> > > devIDToConIDToROID;
  std::map<NZSPtr<IDValue>, SPtr<ROAPProtectedRO> > roIDToRO;

  std::map<NZSPtr<URIValue>, Base64StringT> contentIDToKey;
  std::map<NZSPtr<ROAPIdentifier>, std::map<NZSPtr<URIValue>, SPtr<OEXRights> > >
    deviceIDToContentIDToRights;
  std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<URIValue>, SPtr<OEXRights> > >
    domainIDToContentIDToRights;
  std::map<NZSPtr<IDValue>, std::pair<Base64StringT, SPtr<OEXRights> > >
    roIDToKeyRights;
};

} // namespace DRMPlugin

#endif // !defined (SERVERBASE_H)
