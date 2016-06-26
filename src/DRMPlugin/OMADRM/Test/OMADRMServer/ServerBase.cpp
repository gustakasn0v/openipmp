/** \file ServerBase.cpp

    Test server context and tools.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "ServerBase.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

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
ServerRIContext::ServerRIContext(const NZSPtr<OMAPublicCertificate>& cer,
  const NZSPtr<OMAPrivateKey>& pri, const NZSPtr<ROAPIdentifier>& riid,
  const NZSPtr<ROAPCertificateChain>& cchain, const SPtr<ROAPKeyIdentifiers>&
  trust, const std::vector<Base64StringT>& trustcerts, const
  std::vector<NZSPtr<URIValue> >& algs, const SPtr<CertCachingExtension>& ccaching,
  const NZSPtr<ROAPVersion>& ver, const NZSPtr<URIValue>& riurl, const
  std::vector<Base64StringT>& ocspresp, const SPtr<DomainNameWhiteListExtension>&
  wlist, const SPtr<ROAPServerInfo>& sinfo): publicCert(cer), privateKey(pri),
  riID(riid), chain(cchain), trusted(trust), trustedCerts(trustcerts),
  algorithms(algs), caching(ccaching), version(ver), url(riurl), ocsps(ocspresp),
  whitelist(wlist), serverInfo(sinfo) {
}

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
CacheServerDeviceContext::CacheServerDeviceContext(const NZSPtr<OMAPublicCertificate>& cer,
  const NZSPtr<ROAPIdentifier>& id, const NZSPtr<ROAPCertificateChain>& cchain,
  const NZSPtr<URIValue>& devurl, const SPtr<ROAPKeyIdentifiers>& trust,
  const std::vector<NZSPtr<URIValue> >& algs, const SPtr<DeviceDetailsData>& ddetails,
  const NZSPtr<ROAPVersion>& ver): publicCert(cer), deviceID(id), chain(cchain),
  url(devurl), trusted(trust), algorithms(algs), details(ddetails), version(ver) {
}

/*! \brief  Update device context with new information.

    \param  ctx         input, temporary device context.
*/
void CacheServerDeviceContext::UpdateContext(const NZSPtr<TempServerDeviceContext>& ctx) {
  if (ctx->publicCert != 0) {
    publicCert = ctx->publicCert;
  }
  if (ctx->chain != 0) {
    chain = ctx->chain;
  }
  url = ctx->url;
  if (ctx->trusted != 0) {
    trusted = ctx->trusted;
  }
  if (ctx->algorithms.size() != 0) {
    algorithms = ctx->algorithms;
  }
  if (ctx->details != 0) {
    details = ctx->details;
  }
  if (ctx->version != 0) {
    version = ctx->version;
  }
}

/*! \brief  Update device context with new certificate chain and new public certificate.

    \param  cchain            input, certificate chain.
    \param  cer               input, public certificate.
*/
void CacheServerDeviceContext::UpdateContext(const NZSPtr<ROAPCertificateChain>&
    cchain, const NZSPtr<OMAPublicCertificate>& cer) {
  chain = cchain;
  publicCert = cer;
}

/*! \brief  Encode as XML string.

    \param  encoded       output, encoded XML string.

    \returns  Boolean indicating success or failure.
*/
bool CacheServerDeviceContext::Encode(std::string& encoded) {
  encoded = "<DeviceContext>";
  Base64StringT tmp;
  if (publicCert->Encode(tmp) == false) {
    return false;
  }
  encoded += "<PublicCert>" + tmp.BString() + "</PublicCert>";
  encoded += deviceID->XmlEncode("Identifier");
  encoded += chain->XmlEncode("CertChain");
  encoded += url->XmlEncode("URL");
  if (trusted != 0) {
    encoded += trusted->XmlEncode("TrustedAuthorities");
  }
  unsigned int i = 0;
  for (i = 0; i < algorithms.size(); i++) {
    encoded += algorithms[i]->XmlEncode("Algorithm");
  }
  if (details != 0) {
    encoded += "<DeviceDetails>" + details->XmlEncode() + "</DeviceDetails>";
  }
  encoded += version->XmlEncode("Version");
  encoded += "</DeviceContext>";

  return true;
}

/*! \brief  Constructor.

    \param  cer               device public certificate.
    \param  id                device identifier.
    \param  devurl            device URL.
    \param  trust             device trusted authorities.
    \param  algs              device supported algorithms.
    \param  ddetails          device details.
    \param  ver               device version.
*/
NCacheServerDeviceContext::NCacheServerDeviceContext(
  const NZSPtr<OMAPublicCertificate>& cer,const NZSPtr<ROAPIdentifier>& id,
  const NZSPtr<URIValue>& devurl, const SPtr<ROAPKeyIdentifiers>& trust,
  const std::vector<NZSPtr<URIValue> >& algs,
  const SPtr<DeviceDetailsData>& ddetails, const NZSPtr<ROAPVersion>& ver):
  publicCert(cer), deviceID(id), url(devurl), trusted(trust), algorithms(algs),
  details(ddetails), version(ver) {
}

/*! \brief  Update device context with new information.

    \param  ctx         input, temporary device context.
*/
void NCacheServerDeviceContext::UpdateContext(const NZSPtr<TempServerDeviceContext>& ctx) {
  if (ctx->publicCert != 0) {
    publicCert = ctx->publicCert;
  }
  url = ctx->url;
  if (ctx->trusted != 0) {
    trusted = ctx->trusted;
  }
  if (ctx->algorithms.size() != 0) {
    algorithms = ctx->algorithms;
  }
  if (ctx->details != 0) {
    details = ctx->details;
  }
  if (ctx->version != 0) {
    version = ctx->version;
  }
}

/*! \brief  Update device context with new certificate chain and new public certificate.

    \param  cchain            input, certificate chain.
    \param  cer               input, public certificate.
*/
void NCacheServerDeviceContext::UpdateContext(const NZSPtr<ROAPCertificateChain>&
    cchain, const NZSPtr<OMAPublicCertificate>& cer) {
  publicCert = cer;
}

/*! \brief  Encode as XML string.

    \param  encoded       output, encoded XML string.

    \returns  Boolean indicating success or failure.
*/
bool NCacheServerDeviceContext::Encode(std::string& encoded) {
  encoded = "<DeviceContext>";
  Base64StringT tmp;
  if (publicCert->Encode(tmp) == false) {
    return false;
  }
  encoded += "<PublicCert>" + tmp.BString() + "</PublicCert>";
  encoded += deviceID->XmlEncode("Identifier");
  encoded += url->XmlEncode("URL");
  if (trusted != 0) {
    encoded += trusted->XmlEncode("TrustedAuthorities");
  }
  unsigned int i = 0;
  for (i = 0; i < algorithms.size(); i++) {
    encoded += algorithms[i]->XmlEncode("Algorithm");
  }
  if (details != 0) {
    encoded += "<DeviceDetails>" + details->XmlEncode() + "</DeviceDetails>";
  }
  encoded += version->XmlEncode("Version");
  encoded += "</DeviceContext>";

  return true;
}

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
TempServerDeviceContext::TempServerDeviceContext(const SPtr<OMAPublicCertificate>& cer,
  const NZSPtr<ROAPIdentifier>& id, const SPtr<ROAPCertificateChain>& cchain,
  const NZSPtr<URIValue>& devurl, const SPtr<ROAPKeyIdentifiers>& trust,
  const std::vector<NZSPtr<URIValue> >& algs, const SPtr<DeviceDetailsData>& ddetails,
  const SPtr<CertCachingExtension>& ccaching, const SPtr<ROAPVersion>& ver):
  publicCert(cer), deviceID(id), chain(cchain), url(devurl), trusted(trust),
  algorithms(algs), details(ddetails), caching(ccaching), version(ver) {
}

/*! \brief  Constructor.
*/
CacheServerRegDatabase::CacheServerRegDatabase(): deviceIDToContext(),
  domIDToDevIDToInfo() {
}

/*! \brief  Constructor.

    \param  devtoctx          device identifier to device context map.
    \param  domtodevtoinfo    domain identifier to device identifier to
                              domain info map.
*/
CacheServerRegDatabase::CacheServerRegDatabase(
  const std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheServerDeviceContext> >& devtoctx,
  const std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
  SPtr<ROAPDomainInfo> > >& domtodevtoinfo): deviceIDToContext(devtoctx),
  domIDToDevIDToInfo(domtodevtoinfo) {
}

/*! \brief  Find (if exists) device context corresponding to device identifier.

    \param  devID           input, device identifier.

    \returns  Device context. If zero, none was found.
*/
SPtr<ServerDeviceContext> CacheServerRegDatabase::GetContext(const NZSPtr<ROAPIdentifier>&
    devID) {
  if (deviceIDToContext.find(devID) != deviceIDToContext.end()) {
    return (ServerDeviceContext*)(deviceIDToContext[devID]);
  } else {
    return 0;
  }
}

/*! \brief  Find (if exists) domain info corresponding to domain identifier
            and device identifier.

    Check if device is a member of domain, and if it is, return domain info
    with domain keys encrypted with device's public key.

    \param  devID           input, device identifier.
    \param  domID           input, domain identifier.

    \returns  Domain info. If zero, none was found.
*/
SPtr<ROAPDomainInfo> CacheServerRegDatabase::GetDomain(const NZSPtr<ROAPIdentifier>&
    devID, const NZSPtr<ROAPDomainIdentifier>& domID) {
  if (domIDToDevIDToInfo.find(domID) == domIDToDevIDToInfo.end()) {
    return 0;
  }
  if (domIDToDevIDToInfo[domID].find(devID) == domIDToDevIDToInfo[domID].end()) {
    return 0;
  }
  return domIDToDevIDToInfo[domID][devID];
}

/*! \brief  Add a new device context.

    \param  devCtx            input, temporary device context.

    \returns  Boolean indicating success or failure.
*/
bool CacheServerRegDatabase::AddDevice(const NZSPtr<TempServerDeviceContext>& devCtx) {
  if (deviceIDToContext.find(devCtx->deviceID) != deviceIDToContext.end()) {
    deviceIDToContext[devCtx->deviceID]->UpdateContext(devCtx);
  } else {
    //  Perform sanity check on new device context.
    if ((devCtx->url == 0) || (devCtx->version == 0) || (devCtx->publicCert == 0) ||
        (devCtx->chain == 0)) {
      return false;
    }

    NZSPtr<CacheServerDeviceContext> newCtx = new CacheServerDeviceContext(
      devCtx->publicCert, devCtx->deviceID, devCtx->chain, devCtx->url,
      devCtx->trusted, devCtx->algorithms, devCtx->details, devCtx->version);
    deviceIDToContext[devCtx->deviceID] = newCtx;
  }
  return true;
}

/*! \brief  Save database.

    \returns  Boolean indicating success or failure.
*/
bool CacheServerRegDatabase::SaveDatabase() {
  return false;
}

/*! \brief  Constructor.
*/
NCacheServerRegDatabase::NCacheServerRegDatabase(): deviceIDToContext(),
  domIDToDevIDToInfo() {
}

/*! \brief  Constructor.

    \param  devtoctx          device identifier to device context map.
    \param  domtodevtoinfo    domain identifier to device identifier to
                              domain info map.
*/
NCacheServerRegDatabase::NCacheServerRegDatabase(
  const std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheServerDeviceContext> >& devtoctx,
  const std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
  SPtr<ROAPDomainInfo> > >& domtodevtoinfo): deviceIDToContext(devtoctx),
  domIDToDevIDToInfo(domtodevtoinfo) {
}

/*! \brief  Find (if exists) device context corresponding to device identifier.

    \param  devID           input, device identifier.

    \returns  Device context. If zero, none was found.
*/
SPtr<ServerDeviceContext> NCacheServerRegDatabase::GetContext(const
    NZSPtr<ROAPIdentifier>& devID) {
  if (deviceIDToContext.find(devID) != deviceIDToContext.end()) {
    return (ServerDeviceContext*)(deviceIDToContext[devID]);
  } else {
    return 0;
  }
}

/*! \brief  Find (if exists) domain info corresponding to domain identifier
            and device identifier.

    Check if device is a member of domain, and if it is, return domain info
    with domain keys encrypted with device's public key.

    \param  devID           input, device identifier.
    \param  domID           input, domain identifier.

    \returns  Domain info. If zero, none was found.
*/
SPtr<ROAPDomainInfo> NCacheServerRegDatabase::GetDomain(const NZSPtr<ROAPIdentifier>&
    devID, const NZSPtr<ROAPDomainIdentifier>& domID) {
  if (domIDToDevIDToInfo.find(domID) == domIDToDevIDToInfo.end()) {
    return 0;
  }
  if (domIDToDevIDToInfo[domID].find(devID) == domIDToDevIDToInfo[domID].end()) {
    return 0;
  }
  return domIDToDevIDToInfo[domID][devID];
}

/*! \brief  Add a new device context.

    \param  devCtx            input, temporary device context.

    \returns  Boolean indicating success or failure.
*/
bool NCacheServerRegDatabase::AddDevice(const NZSPtr<TempServerDeviceContext>& devCtx) {
  if (deviceIDToContext.find(devCtx->deviceID) != deviceIDToContext.end()) {
    deviceIDToContext[devCtx->deviceID]->UpdateContext(devCtx);
  } else {
    //  Perform sanity check on new device context.
    if ((devCtx->url == 0) || (devCtx->version == 0) || (devCtx->publicCert == 0) ||
        (devCtx->chain == 0)) {
      return false;
    }

    NZSPtr<NCacheServerDeviceContext> newCtx = new NCacheServerDeviceContext(
      devCtx->publicCert, devCtx->deviceID, devCtx->url, devCtx->trusted,
      devCtx->algorithms, devCtx->details, devCtx->version);
    deviceIDToContext[devCtx->deviceID] = newCtx;
  }
  return true;
}

/*! \brief  Save database.

    \returns  Boolean indicating success or failure.
*/
bool NCacheServerRegDatabase::SaveDatabase() {
  return false;
}

/*! \brief  Constructor.
*/
ServerRODatabase::ServerRODatabase(): devIDToConIDToROID(), roIDToRO(), contentIDToKey(),
  deviceIDToContentIDToRights(), domainIDToContentIDToRights(),
  roIDToKeyRights() {
}

/*! \brief  Update rights objects database.

    Add a new devID->conID->roID map, and new roID->ro map.

    \param  devID           input, device identifier.
    \param  conID           input, content identifier.
    \param  roID            input, rights objects identifier.
    \param  ro              input, rights objects.

    \returns  Boolean indicating success or failure.
*/
bool ServerRODatabase::AddRO(const NZSPtr<ROAPIdentifier>& devID,
    const NZSPtr<URIValue>& conID, const NZSPtr<IDValue>& roID, const
    NZSPtr<ROAPProtectedRO>& ro) {
  devIDToConIDToROID[devID][conID] = roID;
  roIDToRO[roID] = ro;
  return true;
}

/*! \brief  Get rights objects identifier applicable to the content for the device.

    Used to build ro acquisition triggers.

    \param  devID           input, device identifier.
    \param  conID           input, content identifier.

    \returns  Rights objects identifier. If zero, none was found.
*/
SPtr<IDValue> ServerRODatabase::GetROID(const NZSPtr<ROAPIdentifier>&
    devID, const NZSPtr<URIValue>& conID) {
  if (devIDToConIDToROID.find(devID) == devIDToConIDToROID.end()) {
    return 0;
  }
  if (devIDToConIDToROID[devID].find(conID) == devIDToConIDToROID[devID].end()) {
    return 0;
  }
  return devIDToConIDToROID[devID][conID];
}

/*! \brief  Get protected rights objects corresponding to rights objects identifier.

    \todo:  Do we want to allow any device to ask for any rights objects,
            even if they are encrypted?

    \param  roID            input, rights objects identifier.

    \returns  Protected rights objects. If zero, none was found.
*/
SPtr<ROAPProtectedRO> ServerRODatabase::GetRO(const NZSPtr<IDValue>& roID) {
  if (roIDToRO.find(roID) == roIDToRO.end()) {
    return 0;
  }
  return roIDToRO[roID];
}

/*! \brief  Add content encryption key.

    \param  contentID         input, content identifier.
    \param  enckey            input, encryption key.
*/
void ServerRODatabase::AddContentKey(const NZSPtr<URIValue>& contentID, const
    Base64StringT& enckey) {
  contentIDToKey[contentID] = enckey;
}

/*! \brief  Add rights for device for content.

    \param  deviceID          input, device identifier.
    \param  contentID         input, content identifier.
    \param  rights            input, rights.
*/
void ServerRODatabase::AddRights(const NZSPtr<ROAPIdentifier>& deviceID, const
    NZSPtr<URIValue>& contentID, const NZSPtr<OEXRights>& rights) {
  deviceIDToContentIDToRights[deviceID][contentID] = rights;
}

/*! \brief  Add rights for domain for content.

    \param  domainID          input, domain identifier.
    \param  contentID         input, content identifier.
    \param  rights            input, rights.
*/
void ServerRODatabase::AddRights(const NZSPtr<ROAPDomainIdentifier>& domainID,
    const NZSPtr<URIValue>& contentID, const NZSPtr<OEXRights>& rights) {
  domainIDToContentIDToRights[domainID][contentID] = rights;
}

/*! \brief  Set rights objects identifer for device and content.

    \param  roID              input, rights objects identifier.
    \param  deviceID          input, device identifier.
    \param  contentID         input, content identifier.

    \returns  Boolean indicating success or not. If fails, it means that
              either content is not registered as protected, or device does
              not have rights for the content.
*/
bool ServerRODatabase::SetROID(const NZSPtr<IDValue>& roID, const NZSPtr<ROAPIdentifier>&
    deviceID, const NZSPtr<URIValue>& contentID) {
  if (contentIDToKey.find(contentID) == contentIDToKey.end()) {
    return false;
  }
  if (deviceIDToContentIDToRights.find(deviceID) == deviceIDToContentIDToRights.end()) {
    return false;
  }
  if (deviceIDToContentIDToRights[deviceID].find(contentID) == 
      deviceIDToContentIDToRights[deviceID].end()) {
    return false;
  }
  roIDToKeyRights[roID] = std::pair<Base64StringT, SPtr<OEXRights> >(
    contentIDToKey[contentID], deviceIDToContentIDToRights[deviceID][contentID]);
  return true;
}

/*! \brief  Set rights objects identifer for domain and content.

    \param  roID              input, rights objects identifier.
    \param  domainID          input, domain identifier.
    \param  contentID         input, content identifier.

    \returns  Boolean indicating success or not. If fails, it means that
              either content is not registered as protected, or domain does
              not have rights for the content.
*/
bool ServerRODatabase::SetROID(const NZSPtr<IDValue>& roID, const NZSPtr<ROAPDomainIdentifier>&
    domainID, const NZSPtr<URIValue>& contentID) {
  if (contentIDToKey.find(contentID) == contentIDToKey.end()) {
    return false;
  }
  if (domainIDToContentIDToRights.find(domainID) == domainIDToContentIDToRights.end()) {
    return false;
  }
  if (domainIDToContentIDToRights[domainID].find(contentID) == 
      domainIDToContentIDToRights[domainID].end()) {
    return false;
  }
  roIDToKeyRights[roID] = std::pair<Base64StringT, SPtr<OEXRights> >(
    contentIDToKey[contentID], domainIDToContentIDToRights[domainID][contentID]);
  return true;
}

/*! \brief  Get encryption key and rights corresponding to rights objects identifer.

    \param  roID              input, rights objects identifier.
    \param  enckey            output, encryption key.
    \param  rights            output, rights.

    \returns  Boolean indicating if key and rights exist or not.
*/
bool ServerRODatabase::GetRO(const NZSPtr<IDValue>& roID, Base64StringT& enckey,
    SPtr<OEXRights>& rights) {
  if (roIDToKeyRights.find(roID) == roIDToKeyRights.end()) {
    return false;
  }
  enckey = roIDToKeyRights[roID].first;
  rights = roIDToKeyRights[roID].second;
  return true;
}

/*! \brief  Save database.

    \returns  Boolean indicating success or failure.
*/
bool ServerRODatabase::SaveDatabase() {
  return false;
}

} // namespace DRMPlugin
