/** \file AgentROAP.cpp

    OMA DRM agent's ROAP protocols implementation.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "AgentROAP.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Verify chain using provided device context.

    If rights issuer context is != 0, then we first check if its contained
    certificate chain (if contains one) is equal to the one we need to verify.
    If they are equal, returns contained public certificate from rights issuer context.
    If not, or rights issuer context is 0, chain is verified, and if passes,
    new public certificate is returned. If verification fails, returns 0.

    \param  device      input, device context.
    \param  ri          input, rights issuer context.
    \param  verifier    input, certificate verifier.
    \param  chain       input, chain to verify.

    \returns  Public certificate, if verification was successful. If failed, 0.
*/
SPtr<OMAPublicCertificate> VerifyChain(const NZSPtr<AgentDeviceContext>& device,
    const SPtr<AgentRIContext>& ri, const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<ROAPCertificateChain>& chain) {
  if (ri != 0) {
    if (ri->GetCertChain() != 0) {
      //  Compare the chains.
      if ((*(ri->GetCertChain())) == (*chain)) {
        return ri->GetPublicCert();
      }
    }
  }     

  if (device->GetTrustedCerts().size() == 0) {
    return verifier->GetCertificate(chain);
  }
  
  //  Verify chain.
  for (unsigned int i = 0; i < device->GetTrustedCerts().size(); i++) {
    SPtr<OMAPublicCertificate> riCert =
      verifier->VerifyChain(device->GetTrustedCerts()[i], chain);
    if (riCert != 0) {
      return riCert;
    }
  }

  return 0;
}

/*! \brief  Constructor.

    \param  ccaching                  certificate caching.
*/
AgentDeviceHelloExtensions::AgentDeviceHelloExtensions(const NZSPtr<CertCachingExtension>&
  ccaching): DeviceHelloExtensions(ccaching) {
}

bool AgentDeviceHelloExtensions::ProtocolCheck(const NZSPtr<SuccessRIHello>& riHello) const {
  return true;
}

/*! \brief  Constructor.

    Size of device identifiers vector must be >= 1.

    \param  tnonce                  trigger nonce.
    \param  ver                     version.
    \param  idvals                  device identifiers vector.
    \param  algs                    supported algorithms.
    \param  exts                    extensions.

    If fails, throws ROAPException.
*/
AgentDeviceHelloRequest::AgentDeviceHelloRequest(const SPtr<ROAPNonce>& tnonce,
  const NZSPtr<ROAPVersion>& ver,  const std::vector<NZSPtr<ROAPIdentifier> >& idvals,
  const std::vector<NZSPtr<URIValue> >& algs, const SPtr<AgentDeviceHelloExtensions>&
  exts): DeviceHelloRequest(tnonce, ver, idvals, algs, ((exts != 0)?
  new DeviceHelloExtensions(exts->GetCertCaching()): exts)), agentextensions(exts) {
}

bool AgentDeviceHelloRequest::ProtocolCheck(const NZSPtr<SuccessRIHello>& riHello) const {
  if (agentextensions != 0) {
    return agentextensions->ProtocolCheck(riHello);
  }
  return true;
}

/*! \brief  Constructor.

    \param  dbase                       registration database.
    \param  ctx                         temporary rights issuer context.
    \param  hello                       agent's device hello message.
*/
DeviceHelloProtocolContext::DeviceHelloProtocolContext(const NZSPtr<AgentRegDatabase>&
  dbase, const NZSPtr<TempAgentRIContext>& ctx, const NZSPtr<AgentDeviceHelloRequest>&
  hello): regDB(dbase), riCtx(ctx), deviceHello(hello) {
}

/*! \brief  Constructor.

    \param  peerid                  peer key identifier.
    \param  ddetails                device details.
    \param  noocsp                  no OCSP response.
    \param  ocspkeyid               OCSP responder key identifier.

    If fails, throws ROAPException.
*/
AgentRegRequestExtensions::AgentRegRequestExtensions(const SPtr<PeerKeyIdExtension>&
  peerid, const SPtr<DeviceDetailsExtension>& ddetails, const
  SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
  ocspkeyid): RegRequestExtensions(peerid, ddetails, noocsp, ocspkeyid) {
}

bool AgentRegRequestExtensions::ProtocolCheck(const NZSPtr<SuccessRegResponse>& regResponse) const {
  if (peerKeyId == 0) {
    if (regResponse->GetCertChain() == 0) {
      return false;
    }
  }
  if (noOCSP == 0) {
    if (regResponse->GetOCSPResponses().empty() == true) {
      return false;
    }
  }
  return true;
}

/*! \brief  Constructor.

    \param  tnonce                  trigger nonce.
    \param  dnonce                  device nonce.
    \param  dtime                   time.
    \param  cchain                  certificate chain.
    \param  trust                   trusted authorities.
    \param  inf                     server info.
    \param  exts                    extensions.
    \param  sig                     signature.
    \param  sessid                  session identifier.
*/
AgentRegRequest::AgentRegRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPNonce>&
  dnonce, const NZSPtr<DateTime>& dtime, const SPtr<ROAPCertificateChain>& cchain,
  const SPtr<ROAPKeyIdentifiers>& trust, const SPtr<ROAPServerInfo>& inf,
	const SPtr<AgentRegRequestExtensions>& exts, const Base64StringT& sig,
  const NZSPtr<ROAPSessionID>& sessid): RegRequest(tnonce, dnonce, dtime, cchain,
  trust, inf, ((exts != 0)?
  new RegRequestExtensions(exts->GetPeerKeyId(), exts->GetDeviceDetails(),
  exts->GetNoOCSPResponse(), exts->GetOCSPResponderKeyId()): 0), sig, sessid),
  agentextensions(exts) {
}

bool AgentRegRequest::ProtocolCheck(const NZSPtr<SuccessRegResponse>& regResponse) const {
  if (agentextensions != 0) {
    return agentextensions->ProtocolCheck(regResponse);
  }
  return true;
}

/*! \brief  Constructor.

    \param  exts                temporary registration request extensions.
*/
TempRegRequest::TempRegRequest(const NZSPtr<TempRegRequestExtensions>& exts):
  extensions(exts) {
}

/*! \brief  Constructor.

    \param  dbase                       registration database.
    \param  ctx                         temporary rights issuer context.
    \param  dhello                      agent's device hello message.
    \param  rhello                      rights issuer hello message.
    \param  regreq                      agent's registration request.
*/
AgentRIHelloProtocolContext::AgentRIHelloProtocolContext(const NZSPtr<AgentRegDatabase>&
  dbase, const NZSPtr<TempAgentRIContext>& ctx, const NZSPtr<AgentDeviceHelloRequest>&
  dhello, const NZSPtr<SuccessRIHello>& rhello, const NZSPtr<AgentRegRequest>&
  regreq): regDB(dbase), riCtx(ctx), deviceHello(dhello), riHello(rhello),
  regRequest(regreq) {
}

/*! \brief  Constructor.

    \param  peerid                peer key identifier.
    \param  ccaching              certificate caching.
    \param  ddetails              device details.

    If fails, throws ROAPException.
*/
AgentRIHelloExtensions::AgentRIHelloExtensions(const SPtr<PeerKeyIdExtension>& peerid,
  const SPtr<CertCachingExtension>& ccaching, const SPtr<DeviceDetailsExtension>&
  ddetails): RIHelloExtensions(peerid, ccaching, ddetails) {
}

/*! \brief  Check and update protocol step.

    \param  context           input, protocol context.
    \param  request           input-output, registration request.
    \param  device            input, device context.

    \returns  Boolean indicating success or failure of check.
*/
bool AgentRIHelloExtensions::ProtocolUpdate(const NZSPtr<DeviceHelloProtocolContext>&
    context, const NZSPtr<TempRegRequest>& request, const NZSPtr<AgentDeviceContext>&
    device) const {
  if (context->riCtx == 0) {
    return false;
  }
  context->riCtx->caching = caching;
  if (peerKeyId != 0) {
    if (peerKeyId->GetIdentifier() != 0) {
      if ((*(peerKeyId->GetIdentifier())) != (*(device->GetKeyID()))) {
        //  Check if device CA corresponds to any of the CAs trusted by
        //  rights issuer.
        SPtr<ROAPKeyIdentifiers> riTrusted = context->riCtx->trusted;
        if (riTrusted != 0) {
          const std::vector<NZSPtr<ROAPKeyIdentifier> >& ids = riTrusted->GetIdentifiers();
          if (ids.size() == 0) {
            //  We can send any certificate chain.
            request->certChain = device->GetCertChain();
          } else {
            unsigned int i = 0;
            for (i = 0; i < ids.size(); i++) {
              if ((*(ids[i])) == (*(device->GetCAID()))) {
                //  We have a common root CA.
                request->certChain = device->GetCertChain();
                break;
              }
            }
            //  Check if matched a CA. If not, return false.
            if (i == ids.size()) {
              return false;
            }
          }
        } else {
          //  Rights issuer trusted element is not present. We assume that
          //  this means the same as if rights issuer trusted element was
          //  present, but contained an empty set of trusted authorities.
          //  Thus we can send any certificate chain.
          request->certChain = device->GetCertChain();
        }
      }
    }
    if (context->riCtx->caching == 0) {
      context->riCtx->caching = new CriticalCertCachingExtension();
    }
  } else {
    //  Check if device CA corresponds to any of the CAs trusted by
    //  rights issuer.
    SPtr<ROAPKeyIdentifiers> riTrusted = context->riCtx->trusted;
    if (riTrusted != 0) {
      const std::vector<NZSPtr<ROAPKeyIdentifier> >& ids = riTrusted->GetIdentifiers();
      if (ids.size() == 0) {
        //  We can send any certificate chain.
        request->certChain = device->GetCertChain();
      } else {
        unsigned int i = 0;
        for (i = 0; i < ids.size(); i++) {
          if ((*(ids[i])) == (*(device->GetCAID()))) {
            //  We have a common root CA.
            request->certChain = device->GetCertChain();
            break;
          }
        }
        //  Check if matched a CA. If not, return false.
        if (i == ids.size()) {
          return false;
        }
      }
    } else {
      //  Rights issuer trusted element is not present. We assume that
      //  this means the same as if rights issuer trusted element was
      //  present, but contained an empty set of trusted authorities.
      //  Thus we can send any certificate chain.
      request->certChain = device->GetCertChain();
    }
  }
  if (details != 0) {
    if (details->IsCritical()) {
      request->extensions->deviceDetails =
        new CriticalDeviceDetailsExtension(device->GetDetails());
    } else {
      request->extensions->deviceDetails =
        new DeviceDetailsExtension(device->GetDetails());
    }
  }
  return true;
}

/*! \brief  Constructor.

    \param  rhs               successful rights issuer hello.
*/
AgentSuccessRIHello::AgentSuccessRIHello(const NZSPtr<SuccessRIHello>& rhs):
  SuccessRIHello(rhs->GetVersion(), rhs->GetRightsIssuerID(), rhs->GetSelectedAlgs(),
  rhs->GetNonce(), rhs->GetTrustedAuthorities(), rhs->GetServerInfo(),
  rhs->GetExtensions(), rhs->GetSessionID()),
  agentextensions(((rhs->GetExtensions() != 0)? new AgentRIHelloExtensions(rhs->GetExtensions()->GetPeerKeyID(),
  rhs->GetExtensions()->GetCertCaching(), rhs->GetExtensions()->GetDeviceDetails()): 0)) {
}

/*! \brief  Check and update protocol.

    \param  tracker             input-output, protocol tracker.
    \param  timer               input, DRM timer.
    \param  noncer              input, DRM noncer.
    \param  device              input, device context.

    \returns  Registration request message. If zero, failed.
*/
SPtr<RegRequest>  AgentSuccessRIHello::ProtocolUpdate(const
    NZSPtr<AgentRegProtocolTracker>& tracker, const NZSPtr<OMADRMDefTimer>& timer,
    const NZSPtr<OMADRMNonceCreator>& noncer, const NZSPtr<AgentDeviceContext>&
    device) const {
  if (tracker->deviceHelloContext == 0) {
    return 0;
  }
  NZSPtr<DeviceHelloProtocolContext> context =
    (NZSPtr<DeviceHelloProtocolContext>)(tracker->deviceHelloContext);
  if (context->deviceHello->ProtocolCheck((SuccessRIHello*)this) == false) {
    tracker->deviceHelloContext = 0;
    return 0;
  }
  NZSPtr<TempRegRequest> tempRR =
    new TempRegRequest(new TempRegRequestExtensions());

  //  This way extensions can add device certificate chain, if needed.
  context->riCtx->trusted = trusted;
  if (agentextensions != 0) {
    if (agentextensions->ProtocolUpdate(context, tempRR, device) == false) {
      tracker->deviceHelloContext = 0;
      return 0;
    }
  }
  context->riCtx->version = version;
  context->riCtx->riID = riID;
  context->riCtx->algorithms = algorithms;
  //  \todo: What to do with nonce?
//  context->riCtx->trusted = trusted;
  context->riCtx->serverInfo = info;

  //  We're done updating context, we're ready to create registration request.
  NZSPtr<ROAPNonce> dNonce = noncer->CreateNonce();
  NZSPtr<DateTime> time = (DateTime*)(timer->GetTime());
  SPtr<PeerKeyIdExtension> peerKeyId;
  SPtr<NoOCSPResponseExtension> noOCSP;
  SPtr<OCSPResponderKeyIdExtension> ocspResp;
  if (context->regDB->GetRIContext(riID) != 0) {
    peerKeyId = context->regDB->GetRIContext(riID)->CreatePeerKeyId(true);
    if (context->regDB->GetRIContext(riID)->GetOCSPResponses().size() != 0) {
      noOCSP = new CriticalNoOCSPResponseExtension();
    }
  }
  /*  Catastrophic: now we have to create just a temporary registration
      request for signature, cause it doesn't make sense to build signature
      data for registration request by ourselves cause signature input has to
      be everything except the signature itself, and it is embedded in the
      registration request message itself.
  */
  SPtr<AgentRegRequestExtensions> exts;
  if ((peerKeyId != 0) || (tempRR->extensions->deviceDetails != 0) || (noOCSP != 0) || (ocspResp != 0)) {
    exts = new AgentRegRequestExtensions(peerKeyId, tempRR->extensions->deviceDetails,
      noOCSP, ocspResp);
  }
  NZSPtr<AgentRegRequest> tempRequest = new AgentRegRequest(0, dNonce,
    time, tempRR->certChain, device->GetTrusted(), info, exts, "", sessionID);
  //  \todo: OCSP responder key identifier.
  Base64StringT signature;
  std::string tosign = context->deviceHello->XmlEncode() + XmlEncode()
      + tempRequest->XmlEncodeWithoutSignature();
  if (device->GetPrivateKey()->Sign(tosign, signature) == false) {
    return 0;
  }
  NZSPtr<AgentRegRequest> regRequest = new AgentRegRequest(0, dNonce,
    time, tempRR->certChain, device->GetTrusted(), info, exts, signature, sessionID);

  NZSPtr<AgentRIHelloProtocolContext> protCtx = new AgentRIHelloProtocolContext(
    context->regDB, context->riCtx, context->deviceHello, (SuccessRIHello*)this,
    regRequest);
  tracker->idToRIHelloContext[sessionID] = protCtx;
  tracker->deviceHelloContext = 0;
  return (AgentRegRequest*)regRequest;
}

/*! \brief  Constructor.

    \param  rhs             successful registration response.
*/
AgentSuccessRegResponse::AgentSuccessRegResponse(const NZSPtr<SuccessRegResponse>& rhs):
  SuccessRegResponse(rhs->GetRightsIssuerURL(), rhs->GetCertChain(),
  rhs->GetOCSPResponses(), rhs->GetExtensions(), rhs->GetSignature(),
  rhs->GetSessionID()) {
}

/*! \brief  Check and update protocol.

    \param  tracker               input-output, protocol tracker.
    \param  verifier              input, certificate verifier.
    \param  device                input, device context.
  
    \returns  Boolean indicating success or failure.
*/
bool AgentSuccessRegResponse::ProtocolUpdate(const NZSPtr<AgentRegProtocolTracker>&
    tracker, const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<AgentDeviceContext>& device) const {
  if (tracker->idToRIHelloContext.find(sessionID) == tracker->idToRIHelloContext.end()) {
    return false;
  }
  SPtr<AgentRIHelloProtocolContext> context = tracker->idToRIHelloContext[sessionID];
  if (context->regRequest->ProtocolCheck((SuccessRegResponse*)this) == false) {
    tracker->idToRIHelloContext.erase(sessionID);
    return false;
  }
  //  Sanity check.
  if (context->riCtx->riID == 0) {
    tracker->idToRIHelloContext.erase(sessionID);
    return false;
  }
  /*  We need to verify the signature, therefore we need to locate rights
      issuer's public key. It will either be derived from certificate chain in
      this message, or from registration database, if we already have rights
      issuer's certificate chain, and have indicated it in the registration
      request by putting a peer key identifier extension to it.
  */
  SPtr<OMAPublicCertificate> riCert;
  SPtr<AgentRIContext> ctx = 
    context->regDB->GetRIContext(context->riCtx->riID);

  if (chain == 0) {
    if (ctx == 0) {
      tracker->idToRIHelloContext.erase(sessionID);
      return false;
    }
    riCert = ctx->GetPublicCert();
  } else {
    //  Rights issuer has sent its certificate chain. This could be either because
    //  we don't have its context (and its public key), or because we have
    //  an outdated context, with outdated key (so in peer key ID extension, our
    //  key identifier was not equal to rights issuer's own identifier). Another
    //  possibility could be that rights issuer doesn't follow the standard protocol,
    //  and in spite of us having its context and indicating it with peer key
    //  ID extension, it sent its certificate chain again.
    if ((riCert = VerifyChain(device, ctx, verifier, chain)) == 0) {
      tracker->idToRIHelloContext.erase(sessionID);
      return false;
    }
    context->riCtx->publicCert = riCert;
    context->riCtx->chain = chain;
  }

  //  riCert is now != 0.
  std::string toverify = context->regRequest->XmlEncode() +
      XmlEncodeWithoutSignature();
  if (riCert->Verify(signature, toverify) == false) {
    tracker->idToRIHelloContext.erase(sessionID);
    return false;
  }
  context->riCtx->url = riURL;
  context->riCtx->ocsps = ocsps;
  context->riCtx->whitelist = ((extensions != 0)? extensions->GetDomainNameWhiteList(): 0);

  /*  Save temporary rights issuer context to registration database.
      If entry for rights issuer id already exists, then merge data.
  */
  if (context->regDB->AddRI(context->riCtx, device) == false) {
    //  Error!
    tracker->idToRIHelloContext.erase(sessionID);
    return false;
  }
  tracker->idToRIHelloContext.erase(sessionID);
  return true;
}

/*! \brief  Constructor.

    \param  peerid                peer key identifier.
    \param  noocsp                no OCSP response.
    \param  ocspresp              OCSP responder key identifier.
    \param  transid               transaction identifier.

    If fails, throws ROAPException.
*/
AgentROReqExtensions::AgentROReqExtensions(const SPtr<PeerKeyIdExtension>& peerid,
  const SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
  ocspresp, const SPtr<TransactionIdExtension>& transid):
  RORequestExtensions(peerid, noocsp, ocspresp, transid) {
}

/*! \brief  Protocol check.

    \param  resp                  input, successful RO response.

    \returns  Boolean indicating success or failure.
*/
bool AgentROReqExtensions::ProtocolCheck(const NZSPtr<SuccessTwoPassROResponse>& roResponse) const {
  if (peerKeyId == 0) {
    if (roResponse->GetCertChain() == 0) {
      return false;
    }
  }
  if (noOCSP == 0) {
    if (roResponse->GetOCSPResponses().empty() == true) {
      return false;
    }
  }
  return true;
}

/*! \brief  Constructor.

    Size of RO infos vector must be >= 1.

    \param  tnonce                  trigger nonce.
    \param  devid                   device identifier.
    \param  domid                   domain identifier.
    \param  riid                    rights issuer identifier.
    \param  dnonce                  device nonce.
    \param  dtime                   time.
    \param  inf                     RO infos vector.
    \param  cchain                  certificate chain.
    \param  exts                    extensions.
    \param  sig                     signature.

    If fails, throws ROAPException.
*/
AgentRORequest::AgentRORequest(const SPtr<ROAPNonce>& tnonce, const
  NZSPtr<ROAPIdentifier>& devid, const SPtr<ROAPDomainIdentifier>& domid,
  const NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPNonce>& dnonce,
  const NZSPtr<DefDateTime>& dtime, const NZSPtr<ROInfo>& inf,
  const SPtr<ROAPCertificateChain>& cchain, const SPtr<AgentROReqExtensions>& exts,
  const Base64StringT& sig): RORequest(tnonce, devid, domid, riid, dnonce, dtime,
  inf, cchain, ((exts != 0)? new RORequestExtensions(exts->GetPeerKeyID(), exts->GetNoOCSPResponse(),
  exts->GetOCSPResponderKeyID(), exts->GetTransactionID()): 0), sig),
  agentextensions(exts) {
}

/*! \brief  Protocol check.

    \param  resp                  input, successful RO response.

    \returns  Boolean indicating success or failure.
*/
bool AgentRORequest::ProtocolCheck(const NZSPtr<SuccessTwoPassROResponse>& resp) const {
  if (agentextensions != 0) {
    if (agentextensions->ProtocolCheck(resp) == false) {
      return false;
    }
  }
  return ((*dNonce) == (*(resp->GetNonce())));
}

/*! \brief  Constructor.

    \param  trig              trigger.
*/
DomainROTriggerHandler::DomainROTriggerHandler(const NZSPtr<DomainROTrigger>& trig):
  trigger(trig) {
}

/*! \brief  Update rights objects database.

    \param  roDB            input-output, rights objects database.

    \returns  Boolean indicating success or failure.
*/
bool DomainROTriggerHandler::UpdateRODB(const NZSPtr<AgentRODatabase>& roDB) const {
  for (unsigned int i = 0; i < trigger->GetTriggerData()->GetROIDContentIDs().size(); i++) {
    roDB->AddRODomainID(trigger->GetTriggerData()->GetROIDContentIDs()[i]->GetROID(),
      (NZSPtr<ROAPDomainIdentifier>)(trigger->GetTriggerData()->GetDomainID()));
  }
  return true;
}

/*! \brief  Constructor.

    \param  trig              trigger.
*/
NDomainROTriggerHandler::NDomainROTriggerHandler(const NZSPtr<NDomainROTrigger>& trig):
  trigger(trig) {
}

/*! \brief  Update rights objects database.

    \param  roDB            input-output, rights objects database.

    \returns  Boolean indicating success or failure.
*/
bool NDomainROTriggerHandler::UpdateRODB(const NZSPtr<AgentRODatabase>& roDB) const {
  return true;
}

/*! \brief  Constructor.

    \param  regdbase              registration database.
    \param  rodbase               rights objects database.
    \param  req                   rights objects request.
    \param  hand                  trigger handler.
*/
ROReqProtocolContext::ROReqProtocolContext(const NZSPtr<AgentRegDatabase>& regdbase,
  const NZSPtr<AgentRODatabase>& rodbase, const NZSPtr<AgentRORequest>& req,
  const NZSPtr<ROTriggerHandler>& hand): regDB(regdbase), roDB(rodbase),
  request(req), handler(hand) {
}

/*! \brief  Constructor.

    \param  hand          trigger handler.
*/
AgentROReqHandler::AgentROReqHandler(const NZSPtr<ROTriggerHandler>& hand):
  handler(hand) {
}

/*! \brief  Create rights objects request.

    \param  regDB                   input, registration database.
    \param  roDB                    input, rights objects database.
    \param  tracker                 input, protocol tracker.
    \param  timer                   input, DRM timer.
    \param  noncer                  input, DRM nonce creator.
    \param  device                  input, device context.

    \returns  Rights objects request. If zero, failed.
*/
SPtr<RORequest> AgentROReqHandler::CreateRORequest(const NZSPtr<AgentRegDatabase>&
    regDB, const NZSPtr<AgentRODatabase>& roDB, const NZSPtr<AgentROReqProtocolTracker>&
    tracker, const NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>&
    noncer, const NZSPtr<AgentDeviceContext>& device) const {
  NZSPtr<ROAPIdentifier> devID = device->GetID();
  NZSPtr<ROAPIdentifier> riID =
    handler->GetTrigger()->GetTriggerData()->GetRightsIssuerID();
  if (regDB->GetRIContext(riID) == false) {
    return 0;
  }
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  NZSPtr<DefDateTime> time = timer->GetTime();
  SPtr<ROAPCertificateChain> chain = regDB->GetRIContext(riID)->GetDeviceCertChain();
  SPtr<PeerKeyIdExtension> peerKeyId =
    regDB->GetRIContext(riID)->CreatePeerKeyId(true);
  SPtr<NoOCSPResponseExtension> noOCSP;
  if (regDB->GetRIContext(riID)->GetOCSPResponses().empty() == true) {
    noOCSP = new CriticalNoOCSPResponseExtension();
  }
  //  \todo: OCSPResponderKeyIdentifier extension.
  SPtr<OCSPResponderKeyIdExtension> ocspResp;
  //  \todo: Transaction identifier extension.
  SPtr<TransactionIdExtension> trans;
  const std::vector<NZSPtr<ROIDContentID> >& roID =
    handler->GetTrigger()->GetTriggerData()->GetROIDContentIDs();
  std::vector<NZSPtr<ROInfoData> > roInfoDatas;
  for (unsigned int i = 0; i < roID.size(); i++) {
    roInfoDatas.push_back(new ROInfoData(roID[i]->GetROID(), 0));
  }
  NZSPtr<ROInfo> roInfo(new ROInfo(roInfoDatas));
  NZSPtr<AgentRORequest> tempReq = new AgentRORequest(handler->GetTrigger()->
    GetTriggerData()->GetNonce(), devID, handler->GetTrigger()->GetTriggerData()->GetDomainID(),
    riID, nonce, time, roInfo, chain, new AgentROReqExtensions(peerKeyId, noOCSP,
    ocspResp, trans), "");
  std::string toSign = tempReq->XmlEncodeWithoutSignature();
  Base64StringT signature;
  if (device->GetPrivateKey()->Sign(toSign, signature) == false) {
    return 0;
  }
  NZSPtr<AgentRORequest> roReq = new AgentRORequest(handler->GetTrigger()->
    GetTriggerData()->GetNonce(), devID, handler->GetTrigger()->GetTriggerData()->GetDomainID(),
    riID, nonce, time, roInfo, chain, new AgentROReqExtensions(peerKeyId, noOCSP,
    ocspResp, trans), signature);
  NZSPtr<ROReqProtocolContext> ctx = new ROReqProtocolContext(regDB, roDB,
    roReq, handler);
  tracker->nonceToCtx[nonce] = ctx;
  return (AgentRORequest*)roReq;
}

/*! \brief  Constructor.

    \param  rhs           successful 2-pass rights objects response.
*/
AgentSuccessTwoPassROResponse::AgentSuccessTwoPassROResponse(const
  NZSPtr<SuccessTwoPassROResponse>& rhs):SuccessTwoPassROResponse(rhs->GetDeviceID(),
  rhs->GetRightsIssuerID(), rhs->GetNonce(), rhs->GetProtectedROs(),
  rhs->GetCertChain(), rhs->GetOCSPResponses(), rhs->GetExtensions(),
  rhs->GetSignature()) {
}

/*! \brief  Check and update protocol.

    \param  tracker                 input-output, protocol tracker.
    \param  verifier                input, certificate verifier.
    \param  device                  input, device context.

    \returns  Boolean indicating success or failure.
*/
bool AgentSuccessTwoPassROResponse::ProtocolUpdate(const NZSPtr<AgentROReqProtocolTracker>&
    tracker, const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<AgentDeviceContext>& device) const {
  unsigned int i = 0;
  SPtr<ROReqProtocolContext> reqCtx;
  if (tracker->nonceToCtx.find(nonce) == tracker->nonceToCtx.end()) {
    return false;
  }
  reqCtx = tracker->nonceToCtx[nonce];
  if (reqCtx->request->ProtocolCheck((SuccessTwoPassROResponse*)this) == false) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }
  //  \todo: Transaction identifier extension check.
  if ((*(reqCtx->request->GetDeviceID())) != (*deviceID)) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }
  if ((*(reqCtx->request->GetRightsIssuerID())) != (*riID)) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }
  SPtr<OMAPublicCertificate> riCert;
  /*  Here we know that registration request made a check whether certificate
      chain needs to be sent or not. If it was not sent, it means that we
      have correct context saved. Even if it was sent, we know that we have
      context, which perhaps needs updating.
  */
  if (chain != 0) {
    if ((riCert = VerifyChain(device, reqCtx->regDB->GetRIContext(riID), verifier,
        chain)) == 0) {
      tracker->nonceToCtx.erase(nonce);
      return false;
    }
    reqCtx->regDB->GetRIContext(riID)->UpdateContext(chain, riCert);
  } else {
    riCert = reqCtx->regDB->GetRIContext(riID)->GetPublicCert();
  }
  if (ocsps.empty() == false) {
    /*  Perhaps we should check again if we have rights issuer context in the
        database.
    */
    //  \todo: add update routine for ocsp response.
//    reqCtx->regDB->GetRIContext(riID)->OCSPResponse() = ocspResponse;
  }
  //  Here we know that riCert != 0.
  std::string toSign = XmlEncodeWithoutSignature();
  if (riCert->Verify(signature, toSign) == false) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }

  //  OK, now we can process the protected rights objects.
  for (i = 0; i < reqCtx->request->GetInfo()->GetDatas().size(); i++) {
    NZSPtr<IDValue> roid = reqCtx->request->GetInfo()->GetDatas()[i]->GetROID();
    for (unsigned int j = 0; j < ros.size(); j++) {
      if ((*(ros[i]->GetROPayload()->GetID())) == (*roid)) {
        //  OK, we've found the requsted rights object.
        NZSPtr<ROAcquisitionTrigger> trigger = reqCtx->handler->GetTrigger();
        for (unsigned int k = 0; k < trigger->GetTriggerData()->GetROIDContentIDs().size(); k++) {
          if ((*(trigger->GetTriggerData()->GetROIDContentIDs()[k]->GetROID())) == (*roid)) {
            for (unsigned int l = 0; l < trigger->GetTriggerData()->GetROIDContentIDs()[k]->GetContentIDs().size(); l++) {
              //  Check the payload signature.
              //   What to do if signature fails? Currently we just ignore the RO.
              toSign = ros[i]->GetROPayload()->XmlEncode("ro");
              if (riCert->Verify(ros[i]->GetSignature()->GetValue()->Get(), toSign) == true) {
                reqCtx->roDB->AddRO(trigger->GetTriggerData()->GetROIDContentIDs()[k]->GetContentIDs()[l],
                  ros[i]);
              }
            }
            break;
          }
        }
        break;
      }
    }
  }
  if (reqCtx->handler->UpdateRODB(reqCtx->roDB) == false) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }

  tracker->nonceToCtx.erase(nonce);
  return true;
}

/*! \brief  Constructor.

    \param  rhs               one pass rights objects response.
*/
AgentOnePassROResponse::AgentOnePassROResponse(const NZSPtr<OnePassROResponse>& rhs):
  OnePassROResponse(rhs->GetStatus(), rhs->GetDeviceID(), rhs->GetRightsIssuerID(),
  rhs->GetProtectedROs(), rhs->GetCertChain(), rhs->GetOCSPResponses(),
  rhs->GetExtensions(), rhs->GetSignature()) {
}

/*! \brief  Check and update protocol.

    \param  regDB                   input, registration database.
    \param  roDB                    input, rights objects database.
    \param  verifier                input, certificate verifier.
    \param  hasher                  input, hash calculator.

    \returns  Boolean indicating success or failure.
*/
bool AgentOnePassROResponse::ProtocolUpdate(const NZSPtr<AgentRegDatabase>& regDB,
    const NZSPtr<AgentRODatabase>& roDB, const NZSPtr<OMACertificateVerifier>&
    verifier, const NZSPtr<OMADRMHasher>& hasher) const {
  return true;
}

/*! \brief  Constructor.

    \param  peerid              peer key identifier.
    \param  noocsp              no OCSP response.
    \param  ocspresp            OCSP responder key identifier.
    \param  hchain              hash chain support.
*/
AgentJoinDomainReqExt::AgentJoinDomainReqExt(const SPtr<PeerKeyIdExtension>& peerid,
  const SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
  ocspresp, const SPtr<HashChainSupportExtension>& hchain):
  JoinDomainReqExtensions(peerid, noocsp, ocspresp, hchain) {
}

/*! \brief  Protocol check.

    \param  response              input, join domain response.

    \returns  Boolean indicating success or failure.
*/
bool AgentJoinDomainReqExt::ProtocolCheck(const NZSPtr<SuccessJoinDomainResponse>&
    joinResponse) const {
  if (peerKeyId == 0) {
    if (joinResponse->GetCertChain() == 0) {
      return false;
    }
  }
  if (noOCSP == 0) {
    if (joinResponse->GetOCSPResponses().empty() == true) {
      return false;
    }
  }
  //! \todo: OCSP responder key identifier.
  return true;
}

/*! \brief  Constructor.

    \param  tnonce              trigger nonce.
    \param  devid               device identifier.
    \param  riid                rights issuer identifier.
    \param  dnonce              device nonce.
    \param  dtime               time.
    \param  domid               domain identifier.
    \param  cchain              certificate chain.
    \param  exts                extensions.
    \param  sig                 signature.
*/
AgentJoinDomainRequest::AgentJoinDomainRequest(const SPtr<ROAPNonce>& tnonce,
  const NZSPtr<ROAPIdentifier>& devid, const NZSPtr<ROAPIdentifier>& riid,
  const NZSPtr<ROAPNonce>& dnonce, const NZSPtr<DateTime>& dtime, const
  NZSPtr<ROAPDomainIdentifier>& domid, const SPtr<ROAPCertificateChain>& cchain,
  const SPtr<AgentJoinDomainReqExt>& exts, const Base64StringT& sig):
  JoinDomainRequest(tnonce, devid, riid, dnonce, dtime, domid, cchain,
  (exts != 0)? new JoinDomainReqExtensions(exts->GetPeerKeyId(), exts->GetNoOCSPResponse(),
  exts->GetOCSPResponderKeyId(), exts->GetHashChainSupport()): 0, sig),
  agentextensions(exts) {
}

/*! \brief  Protocol check

    \param  response              input, join domain response.

    \returns  Boolean indicating success or failure of check.
*/
bool AgentJoinDomainRequest::ProtocolCheck(const NZSPtr<SuccessJoinDomainResponse>&
    response) const {
  if (agentextensions != 0) {
    if (agentextensions->ProtocolCheck(response) == false) {
      return false;
    }
  }
  if ((*deviceID) != (*(response->GetDeviceID()))) {
    return false;
  }
  if ((*riID) != (*(response->GetRightsIssuerID()))) {
    return false;
  }
  if ((*dNonce) != (*(response->GetNonce()))) {
    return false;
  }
  return true;
}

/*! \brief  Constructor.

    \param  regdbase              registration database.
    \param  req                   join domain request.
*/
JoinDomainProtocolContext::JoinDomainProtocolContext(const NZSPtr<AgentRegDatabase>&
  regdbase, const NZSPtr<AgentJoinDomainRequest>& req): regDB(regdbase), request(req) {
}

/*! \brief  Constructor.

    \param  rhs                 successful join domain response.
*/
AgentSuccessJoinDomainResponse::AgentSuccessJoinDomainResponse(const
  NZSPtr<SuccessJoinDomainResponse>& rhs):
  SuccessJoinDomainResponse(rhs->GetDeviceID(), rhs->GetRightsIssuerID(),
  rhs->GetNonce(), rhs->GetDomainInfo(), rhs->GetCertChain(),
  rhs->GetOCSPResponses(), rhs->GetExtensions(), rhs->GetSignature()) {
}

/*! \brief  Check and update protocol.

    \param  tracker             input-output, protocol tracker.
    \param  verifier            input, certificate verifier.
    \param  device              input, device context.

    \returns  Boolean indicating success or failure.
*/
bool AgentSuccessJoinDomainResponse::ProtocolUpdate(const NZSPtr<AgentJoinDomProtocolTracker>& tracker,
    const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<AgentDeviceContext>& device) const {
  if (tracker->nonceToCtx.find(nonce) == tracker->nonceToCtx.end()) {
    return false;
  }
  SPtr<JoinDomainProtocolContext> context = tracker->nonceToCtx[nonce];
  if (context->request->ProtocolCheck((SuccessJoinDomainResponse*)this) == false) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }
  SPtr<OMAPublicCertificate> riCert;
  //  \todo:  In JoinDomainRequest creation we must check if rights issuer's
  //          context exists.
  if (chain != 0) {
    if ((riCert = VerifyChain(device, context->regDB->GetRIContext(riID), verifier,
        chain)) == 0) {
      tracker->nonceToCtx.erase(nonce);
      return false;
    }
    context->regDB->GetRIContext(riID)->UpdateContext(chain, riCert);
  } else {
    riCert = context->regDB->GetRIContext(riID)->GetPublicCert();
  }
  if (ocsps.empty() == false) {
    /*  Perhaps we should check again if we have rights issuer context in the
        database.
    */
    //  \todo: add update routine for ocsp response.
//    reqCtx->regDB->GetRIContext(riID)->OCSPResponse() = ocspResponse;
  }
  //  Here we know that riCert != 0.
  if (riCert->Verify(signature, XmlEncodeWithoutSignature()) == false) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }
  context->regDB->AddDomain(context->request->GetDomainID(), info);
  
  tracker->nonceToCtx.erase(nonce);
  return true;
}

/*! \brief  Constructor.

    \param  tnonce              trigger nonce.
    \param  devid               device identifier.
    \param  riid                rights issuer identifier.
    \param  dnonce              device nonce.
    \param  dtime               time.
    \param  domid               domain identifier.
    \param  cchain              certificate chain.
    \param  exts                extensions.
    \param  sig                 signature.
*/
AgentLeaveDomainRequest::AgentLeaveDomainRequest(const SPtr<ROAPNonce>& tnonce,
  const NZSPtr<ROAPIdentifier>& devid, const NZSPtr<ROAPIdentifier>& riid,
  const NZSPtr<ROAPNonce>& dnonce, const NZSPtr<DateTime>& dtime, const
  NZSPtr<ROAPDomainIdentifier>& domid, const SPtr<ROAPCertificateChain>& cchain,
  const SPtr<LeaveDomainReqExtensions>& exts, const Base64StringT& sig):
  LeaveDomainRequest(tnonce, devid, riid, dnonce, dtime, domid, cchain, exts, sig) {
}

/*! \brief  Protocol check.

    \param  response                input, leave domain response.

    \returns  Boolean indicating success or failure.
*/
bool AgentLeaveDomainRequest::ProtocolCheck(const NZSPtr<SuccessLeaveDomainResponse>& response) const {
  return ((*(response->GetNonce())) == (*dNonce));
}

/*! \brief  Constructor.

    \param  regdbase                  registration database.
    \param  req                       leave domain request.
*/
LeaveDomainProtocolContext::LeaveDomainProtocolContext(const NZSPtr<AgentRegDatabase>& regdbase,
  const NZSPtr<AgentLeaveDomainRequest>& req): regDB(regdbase), request(req) {
}

/*! \brief  Constructor.

    \param  trig              trigger.
*/
TriggerAgentLeaveDomainReqHandler::TriggerAgentLeaveDomainReqHandler(const
  NZSPtr<LeaveDomainTrigger>& trig): trigger(trig) {
}

/*! \brief  Create leave domain request.

    \param  regDB               input, registration database.
    \param  tracker             input-output, protocol tracker.
    \param  timer               input, DRM timer.
    \param  noncer              input, nonce creator.

    \returns  Leave domain request message. If zero, failed.
*/
SPtr<LeaveDomainRequest> TriggerAgentLeaveDomainReqHandler::CreateRequest(const
    NZSPtr<AgentRegDatabase>& regDB, const NZSPtr<AgentLeaveDomProtocolTracker>&
    tracker, const NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>&
    noncer) const {
  return 0;
}

/*! \brief  Constructor.

    \param  riid                rights issuer identifier.
    \param  domid               domain identifier.
*/
NTriggerAgentLeaveDomainReqHandler::NTriggerAgentLeaveDomainReqHandler(const
  NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPDomainIdentifier>& domid):
  riID(riid), domainID(domid) {
}

/*! \brief  Create leave domain request.

    \param  regDB               input, registration database.
    \param  tracker             input-output, protocol tracker.
    \param  timer               input, DRM timer.
    \param  noncer              input, nonce creator.

    \returns  Leave domain request message. If zero, failed.
*/
SPtr<LeaveDomainRequest> NTriggerAgentLeaveDomainReqHandler::CreateRequest(const
    NZSPtr<AgentRegDatabase>& regDB, const NZSPtr<AgentLeaveDomProtocolTracker>&
    tracker, const NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>&
    noncer) const {
  return 0;
}

/*! \brief  Constructor.

    \param  rhs                successful leave domain response.
*/
AgentSuccessLeaveDomainResponse::AgentSuccessLeaveDomainResponse(const
  NZSPtr<SuccessLeaveDomainResponse>& rhs):
  SuccessLeaveDomainResponse(rhs->GetNonce(), rhs->GetDomainID(), 0) {
}

/*! \brief  Check and update protocol.

    \param  tracker             input-output, protocol tracker.

    \returns  Boolean indicating success or failure.
*/
bool AgentSuccessLeaveDomainResponse::ProtocolUpdate(const
    NZSPtr<AgentLeaveDomProtocolTracker>& tracker) const {
  if (tracker->nonceToCtx.find(nonce) == tracker->nonceToCtx.end()) {
    return false;
  }
  SPtr<LeaveDomainProtocolContext> context = tracker->nonceToCtx[nonce];
  if (context->request->ProtocolCheck((SuccessLeaveDomainResponse*)this) == false) {
    tracker->nonceToCtx.erase(nonce);
    return false;
  }
  context->regDB->RemoveDomain(context->request->GetDomainID());
  
  tracker->nonceToCtx.erase(nonce);
  return true;
}

} // namespace DRMPlugin
