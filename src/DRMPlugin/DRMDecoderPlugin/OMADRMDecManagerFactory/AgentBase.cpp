/** \file AgentBase.cpp

    OMADRM agent's contexts and tools.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "AgentBase.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Encode as XML string.

    \param  encoded       output, encoded XML string.

    \returns  Boolean indicating success or failure.
*/
bool CacheAgentRIContext::Encode(std::string& encoded) {
  encoded = "<RIContext>";
  Base64StringT tmp;
  if (publicCert->Encode(tmp) == false) {
    return false;
  }
  encoded += "<PublicCert>" + tmp.BString() + "</PublicCert>";
  encoded += riID->XmlEncode("Identifier");
  encoded += chain->XmlEncode("CertChain");
  encoded += url->XmlEncode("URL");
  encoded += version->XmlEncode("Version");
  if (trusted != 0) {
    encoded += trusted->XmlEncode("TrustedAuthorities");
  }
  unsigned int i = 0;
  for (i = 0; i < algorithms.size(); i++) {
    encoded += algorithms[i]->XmlEncode("Algorithm");
  }
  for (i = 0; i < ocsps.size(); i++) {
    encoded += "<OCSPResponse>" + ocsps[i].BString() + "</OCSPResponse>";
  }
  if (whitelist != 0) {
    encoded += whitelist->XmlEncode("WhiteList");
  }
  if (serverInfo != 0) {
    encoded += serverInfo->XmlEncode("ServerInfo");
  }
  if (GetDeviceCertChain() != 0) {
    encoded += GetDeviceCertChain()->XmlEncode("DeviceCertChain");
  }
  encoded += "</RIContext>";

  return true;
}

/*! \brief  Encode as XML string.

    \param  encoded       output, encoded XML string.

    \returns  Boolean indicating success or failure.
*/
bool NCacheAgentRIContext::Encode(std::string& encoded) {
  encoded = "<RIContext>";
  Base64StringT tmp;
  if (publicCert->Encode(tmp) == false) {
    return false;
  }
  encoded += "<PublicCert>" + tmp.BString() + "</PublicCert>";
  encoded += riID->XmlEncode("Identifier");
  encoded += url->XmlEncode("URL");
  encoded += version->XmlEncode("Version");
  if (trusted != 0) {
    encoded += trusted->XmlEncode("TrustedAuthorities");
  }
  unsigned int i = 0;
  for (i = 0; i < algorithms.size(); i++) {
    encoded += algorithms[i]->XmlEncode("Algorithm");
  }
  for (i = 0; i < ocsps.size(); i++) {
    encoded += "<OCSPResponse>" + ocsps[i].BString() + "</OCSPResponse>";
  }
  if (whitelist != 0) {
    encoded += whitelist->XmlEncode("WhiteList");
  }
  if (serverInfo != 0) {
    encoded += serverInfo->XmlEncode("ServerInfo");
  }
  if (GetDeviceCertChain() != 0) {
    encoded += GetDeviceCertChain()->XmlEncode("DeviceCertChain");
  }
  encoded += "</RIContext>";

  return true;
}

/*! \brief  Constructor.
*/
CacheAgentRegDatabase::CacheAgentRegDatabase(): riIDToContext(), domainIDToInfo() {
}

/*! \brief  Constructor.

    \param  ritocontext     rights issuer identifier to context map.
    \param  domaintoinfo    domain identifier to domain info map.
*/
CacheAgentRegDatabase::CacheAgentRegDatabase(
  const std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheAgentRIContext> >& ritocontext,
  const std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> >& domaintoinfo):
  riIDToContext(ritocontext), domainIDToInfo(domaintoinfo) {
}

/*! \brief  Find (if exists) rights issuer context corresponding to URL.

    Used in fetching decryption keys in DCFs.

    \param  riURL           input, rights issuer URL.

    \returns  Rights issuer context. If zero, context was not found.
*/
SPtr<AgentRIContext> CacheAgentRegDatabase::GetRIContext(const NZSPtr<URIValue>&
    riURL) {
  std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheAgentRIContext> >::iterator
    iter = riIDToContext.begin();
  while (iter != riIDToContext.end()) {
    if ((*(iter->second->GetURL())) == (*riURL)) {
      return (CacheAgentRIContext*)(iter->second);
    }
    iter++;
  }
  return 0;
}

/*! \brief  Find (if exists) rights issuer context corresponding to the identifier.

    \param  riID            input, rights issuer identifier.

    \returns  Rights issuer context. If zero, context was not found.
*/
SPtr<AgentRIContext> CacheAgentRegDatabase::GetRIContext(const
    NZSPtr<ROAPIdentifier>& riID) {
  if (riIDToContext.find(riID) != riIDToContext.end()) {
    return (CacheAgentRIContext*)(riIDToContext[riID]);
  } else {
    return 0;
  }
}

/*! \brief  Find (if exists) domain info (contains a domain key) corresponding
            to the domain identifier.

    \param  domainID        input, domain identifier.

    \returns  Domain info. If zero, info was not found.
*/
SPtr<ROAPDomainInfo> CacheAgentRegDatabase::GetDomainInfo(const
    NZSPtr<ROAPDomainIdentifier>& domainID) {
  if (domainIDToInfo.find(domainID) != domainIDToInfo.end()) {
    return domainIDToInfo[domainID];
  } else {
    return 0;
  }
}

/*! \brief  Add a new rights issuer context.

    \param  riCtx               input, context to be added.
    \param  device              input, device context.

    \returns  Boolean indicating success or failure.
*/
bool CacheAgentRegDatabase::AddRI(const NZSPtr<TempAgentRIContext>& riCtx,
    const NZSPtr<AgentDeviceContext>& device) {
  //  Perform sanity check on temporary ri context.
  if ((riCtx->riID == 0) || (riCtx->url == 0) || (riCtx->version == 0)) {
    return false;
  }
  if (riIDToContext.find(riCtx->riID) != riIDToContext.end()) {
    SPtr<CacheAgentRIContext> origCtx = riIDToContext[riCtx->riID];
    SPtr<ROAPKeyIdentifiers> trusted;
    if (riCtx->trusted != 0) {
      trusted = riCtx->trusted;
    } else {
      trusted = origCtx->GetTrusted();
    }
    std::vector<NZSPtr<URIValue> > supported;
    if (riCtx->algorithms.empty() == false) {
      supported = riCtx->algorithms;
    } else {
      supported = origCtx->GetAlgorithms();
    }
    std::vector<Base64StringT> ocsp;
    if (riCtx->ocsps.empty() == false) {
      ocsp = riCtx->ocsps;
    } else {
      ocsp = origCtx->GetOCSPResponses();
    }
    SPtr<DomainNameWhiteListExtension> dname;
    if (riCtx->whitelist != 0) {
      dname = riCtx->whitelist;
    } else {
      dname = origCtx->GetDomainNameWhiteList();
    }
    SPtr<ROAPServerInfo> sinf;
    if (riCtx->serverInfo != 0) {
      sinf = riCtx->serverInfo;
    } else {
      sinf = origCtx->GetServerInfo();
    }

    NZSPtr<OMAPublicCertificate> pubCert = ((riCtx->publicCert != 0)?
      NZSPtr<OMAPublicCertificate>(riCtx->publicCert): (origCtx->GetPublicCert()));
    NZSPtr<ROAPCertificateChain> chain = ((riCtx->chain != 0)?
      (riCtx->chain): (origCtx->GetCertChain()));
    if ((origCtx->GetDeviceCertChain() == 0) || (riCtx->caching != 0)) {
      NZSPtr<CacheAgentRIContext> newCtx = new CacheAgentRIContext(
        pubCert, riCtx->riID, chain, riCtx->url, riCtx->version, trusted,
        supported, ocsp, dname, sinf);
      riIDToContext[riCtx->riID] = newCtx;
    } else {
      NZSPtr<CacheAgentRIContext> newCtx = new CacheAgentNCacheRIContext(
        pubCert, riCtx->riID, chain, riCtx->url, riCtx->version, trusted,
        supported, ocsp, dname, sinf, device->GetCertChain());
      riIDToContext[riCtx->riID] = newCtx;
    }
  } else {
    //  Perform sanity check on new ri context.
    if ((riCtx->publicCert == 0) || (riCtx->chain == 0)) {
      return false;
    }
    if (riCtx->caching != 0) {
      NZSPtr<CacheAgentRIContext> newCtx = new CacheAgentRIContext(
        riCtx->publicCert, riCtx->riID, riCtx->chain, riCtx->url, riCtx->version,
        riCtx->trusted, riCtx->algorithms, riCtx->ocsps,
        riCtx->whitelist, riCtx->serverInfo);
      riIDToContext[riCtx->riID] = newCtx;
    } else {
      NZSPtr<CacheAgentRIContext> newCtx = new CacheAgentNCacheRIContext(
        riCtx->publicCert, riCtx->riID, riCtx->chain, riCtx->url, riCtx->version,
        riCtx->trusted, riCtx->algorithms, riCtx->ocsps, riCtx->whitelist,
        riCtx->serverInfo, device->GetCertChain());
      riIDToContext[riCtx->riID] = newCtx;
    }
  }
  return true;
}

/*! \brief  Add a new domain.

    \param  domainID            input, domain identifier.
    \param  info                input, domain info.
*/
void CacheAgentRegDatabase::AddDomain(const NZSPtr<ROAPDomainIdentifier>&
    domainID, const NZSPtr<ROAPDomainInfo>& info) {
  domainIDToInfo[domainID] = info;
}

/*! \brief  Remove domain.

    \param  domainID            input, domain identifier.
*/
void CacheAgentRegDatabase::RemoveDomain(const NZSPtr<ROAPDomainIdentifier>& domainID) {
  domainIDToInfo.erase(domainID);
}

/*! \brief  Save database for future use.

    \returns  Boolean indicating success or failure.
*/
bool CacheAgentRegDatabase::SaveDatabase() {
  return false;
}

/*! \brief  Constructor.
*/
NCacheAgentRegDatabase::NCacheAgentRegDatabase(): riIDToContext(), domainIDToInfo() {
}

/*! \brief  Constructor.

    \param  ritocontext     rights issuer identifier to context map.
    \param  domaintoinfo    domain identifier to domain info map.
    \param  devctx          device context.
*/
NCacheAgentRegDatabase::NCacheAgentRegDatabase(
  const std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheAgentRIContext> >& ritocontext,
  const std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> >& domaintoinfo):
  riIDToContext(ritocontext), domainIDToInfo(domaintoinfo) {
}

/*! \brief  Find (if exists) rights issuer context corresponding to URL.

    Used in fetching decryption keys in DCFs.

    \param  riURL           input, rights issuer URL.

    \returns  Rights issuer context. If zero, context was not found.
*/
SPtr<AgentRIContext> NCacheAgentRegDatabase::GetRIContext(const NZSPtr<URIValue>&
    riURL) {
  std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheAgentRIContext> >::iterator
    iter = riIDToContext.begin();
  while (iter != riIDToContext.end()) {
    if ((*(iter->second->GetURL())) == (*riURL)) {
      return (NCacheAgentRIContext*)(iter->second);
    }
    iter++;
  }
  return 0;
}

/*! \brief  Find (if exists) rights issuer context corresponding to the identifier.

    \param  riID            input, rights issuer identifier.

    \returns  Rights issuer context. If zero, context was not found.
*/
SPtr<AgentRIContext> NCacheAgentRegDatabase::GetRIContext(const
    NZSPtr<ROAPIdentifier>& riID) {
  if (riIDToContext.find(riID) != riIDToContext.end()) {
    return (NCacheAgentRIContext*)(riIDToContext[riID]);
  } else {
    return 0;
  }
}

/*! \brief  Find (if exists) domain info (contains a domain key) corresponding
            to the domain identifier.

    \param  domainID        input, domain identifier.

    \returns  Domain info. If zero, info was not found.
*/
SPtr<ROAPDomainInfo> NCacheAgentRegDatabase::GetDomainInfo(const
    NZSPtr<ROAPDomainIdentifier>& domainID) {
  if (domainIDToInfo.find(domainID) != domainIDToInfo.end()) {
    return domainIDToInfo[domainID];
  } else {
    return 0;
  }
}

/*! \brief  Add a new rights issuer context.

    \param  riCtx               input, context to be added.
    \param  device              input, device context.

    \returns  Boolean indicating success or failure.
*/
bool NCacheAgentRegDatabase::AddRI(const NZSPtr<TempAgentRIContext>& riCtx,
    const NZSPtr<AgentDeviceContext>& device) {
  //  Perform sanity check on temporary ri context.
  if ((riCtx->riID == 0) || (riCtx->url == 0) || (riCtx->version == 0)) {
    return false;
  }
  if (riIDToContext.find((NZSPtr<ROAPIdentifier>)(riCtx->riID)) != riIDToContext.end()) {
    SPtr<NCacheAgentRIContext> origCtx =
      riIDToContext[(NZSPtr<ROAPIdentifier>)(riCtx->riID)];
    SPtr<ROAPKeyIdentifiers> trusted;
    if (riCtx->trusted != 0) {
      trusted = riCtx->trusted;
    } else {
      trusted = origCtx->GetTrusted();
    }
    std::vector<NZSPtr<URIValue> > supported;
    if (riCtx->algorithms.empty() == false) {
      supported = riCtx->algorithms;
    } else {
      supported = origCtx->GetAlgorithms();
    }
    std::vector<Base64StringT> ocsp;
    if (riCtx->ocsps.empty() == false) {
      ocsp = riCtx->ocsps;
    } else {
      ocsp = origCtx->GetOCSPResponses();
    }
    SPtr<DomainNameWhiteListExtension> dname;
    if (riCtx->whitelist != 0) {
      dname = riCtx->whitelist;
    } else {
      dname = origCtx->GetDomainNameWhiteList();
    }
    SPtr<ROAPServerInfo> sinf;
    if (riCtx->serverInfo != 0) {
      sinf = riCtx->serverInfo;
    } else {
      sinf = origCtx->GetServerInfo();
    }

    if ((origCtx->GetDeviceCertChain() == 0) || (riCtx->caching != 0)) {
      NZSPtr<NCacheAgentRIContext> newCtx = new NCacheAgentRIContext(
        origCtx->GetPublicCert(),
        (NZSPtr<ROAPIdentifier>)(riCtx->riID), (NZSPtr<URIValue>)(riCtx->url),
        (NZSPtr<ROAPVersion>)(riCtx->version), trusted, supported,
        ocsp, dname, sinf);
      riIDToContext[(NZSPtr<ROAPIdentifier>)(riCtx->riID)] = newCtx;
    } else {
      NZSPtr<NCacheAgentRIContext> newCtx = new NCacheAgentNCacheRIContext(
        origCtx->GetPublicCert(),
        (NZSPtr<ROAPIdentifier>)(riCtx->riID), (NZSPtr<URIValue>)(riCtx->url),
        (NZSPtr<ROAPVersion>)(riCtx->version), trusted, supported, ocsp, dname,
        sinf, device->GetCertChain());
      riIDToContext[(NZSPtr<ROAPIdentifier>)(riCtx->riID)] = newCtx;
    }
  } else {
    //  Perform sanity check on new ri context.
    if ((riCtx->publicCert == 0) || (riCtx->chain == 0)) {
      return false;
    }
    if (riCtx->caching != 0) {
      NZSPtr<NCacheAgentRIContext> newCtx = new NCacheAgentRIContext(
        riCtx->publicCert,
        (NZSPtr<ROAPIdentifier>)(riCtx->riID), (NZSPtr<URIValue>)(riCtx->url),
        (NZSPtr<ROAPVersion>)(riCtx->version), riCtx->trusted,
        riCtx->algorithms, riCtx->ocsps, riCtx->whitelist,
        riCtx->serverInfo);
      riIDToContext[(NZSPtr<ROAPIdentifier>)(riCtx->riID)] = newCtx;
    } else {
      NZSPtr<NCacheAgentRIContext> newCtx = new NCacheAgentNCacheRIContext(
        riCtx->publicCert,
        (NZSPtr<ROAPIdentifier>)(riCtx->riID), (NZSPtr<URIValue>)(riCtx->url),
        (NZSPtr<ROAPVersion>)(riCtx->version), riCtx->trusted,
        riCtx->algorithms, riCtx->ocsps, riCtx->whitelist, riCtx->serverInfo,
        device->GetCertChain());
      riIDToContext[(NZSPtr<ROAPIdentifier>)(riCtx->riID)] = newCtx;
    }
  }
  return true;
}

/*! \brief  Add a new domain.

    \param  domainID            input, domain identifier.
    \param  info                input, domain info.
*/
void NCacheAgentRegDatabase::AddDomain(const NZSPtr<ROAPDomainIdentifier>&
    domainID, const NZSPtr<ROAPDomainInfo>& info) {
  domainIDToInfo[domainID] = info;
}

/*! \brief  Remove domain.

    \param  domainID            input, domain identifier.
*/
void NCacheAgentRegDatabase::RemoveDomain(const NZSPtr<ROAPDomainIdentifier>& domainID) {
  domainIDToInfo.erase(domainID);
}

/*! \brief  Save database for future use.

    \returns  Boolean indicating success or failure.
*/
bool NCacheAgentRegDatabase::SaveDatabase() {
  return false;
}

/*! \brief  Constructor.
*/
AgentRODatabase::AgentRODatabase(): contentIDToRO(), roIDToDom() {
}

/*! \brief  Constructor.

    \param  contenttoro     content identifier to protected rights objects map.
    \param  rotodom         rights objects identifier to domain identifier map.
*/
AgentRODatabase::AgentRODatabase(const std::map<NZSPtr<URIValue>, SPtr<ROAPProtectedRO> >&
  contenttoro, const std::map<NZSPtr<IDValue>, SPtr<ROAPDomainIdentifier> >&
  rotodom): contentIDToRO(contenttoro), roIDToDom(rotodom) {
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
SPtr<ROAPProtectedRO> AgentRODatabase::GetRO(const NZSPtr<URIValue>& contentID,
    const NZSPtr<AgentRIContext>& ri) {
  if (contentIDToRO.find(contentID) != contentIDToRO.end()) {
    SPtr<ROAPProtectedRO> ro = contentIDToRO[contentID];
    if (ri->GetPublicCert()->Verify(ro->GetSignature()->GetValue()->Get(),
        ro->GetROPayload()->XmlEncode("ro")) == true) {
      return ro;
    }
  }
  return 0;
}

/*! \brief  Get (if exist) domain identifier corresponding to rights
            objects identifier.

    \param  roID                    input, rights objects identifier.

    \returns  Domain identifier. If zero, none was found.
*/
SPtr<ROAPDomainIdentifier> AgentRODatabase::GetDomainID(const NZSPtr<IDValue>& roID) {
  if (roIDToDom.find(roID) != roIDToDom.end()) {
    return roIDToDom[roID];
  } else {
    return 0;
  }
}

/*! \brief  Add a (content identifier, protected rights objects) pair.

    \param  contentID             input, content identifier.
    \param  protRO                input, protected rights objects.
*/
void AgentRODatabase::AddRO(const NZSPtr<URIValue>& contentID, const
    NZSPtr<ROAPProtectedRO>& protRO) {
  contentIDToRO[contentID] = protRO;
}

/*! \brief  Add a (rights objects identifier, domain identifier) pair.

    \param  roID                  input, rights objects identifier.
    \param  domainID              input, domain identifier.
*/
void AgentRODatabase::AddRODomainID(const NZSPtr<IDValue>& roID, const
    NZSPtr<ROAPDomainIdentifier>& domainID) {
  roIDToDom[roID] = domainID;
}

/*! \brief  Save database for future use.

    \returns  Boolean indicating success or failure.
*/
bool AgentRODatabase::SaveDatabase() {
  return false;
}

} // namespace DRMPlugin
