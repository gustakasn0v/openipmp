/** \file ServerROAP.cpp

    Test server OMA DRM rights issuer messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "ServerROAP.h"
#include "Base64Factory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Verify chain using provided rights issuer context.

    If device context is != 0, then we first check if its contained
    certificate chain (if contains one) is equal to the one we need to verify.
    If they are equal, returns contained public certificate from device context.
    If not, or device context is 0, chain is verified, and if passes,
    new public certificate is returned. If verification fails, returns 0.

    \param  device      input, device context.
    \param  ri          input, rights issuer context.
    \param  verifier    input, certificate verifier.
    \param  chain       input, chain to verify.

    \returns  Public certificate, if verification was successful. If failed, 0.
*/
SPtr<OMAPublicCertificate> VerifyChain(const SPtr<ServerDeviceContext>& device,
    const NZSPtr<ServerRIContext>& ri, const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<ROAPCertificateChain>& chain) {
  if (device != 0) {
    if (device->GetCertChain() != 0) {
      //  Compare the chains.
      if ((*(device->GetCertChain())) == (*chain)) {
        return device->GetPublicCert();
      } else {
        //  Verify chain.
        for (unsigned int i = 0; i < ri->GetTrustedCerts().size(); i++) {
          SPtr<OMAPublicCertificate> devCert =
            verifier->VerifyChain(ri->GetTrustedCerts()[i], chain);
          if (devCert != 0) {
            return devCert;
          }
        }
      }
    } else {
      //  Verify chain.
      for (unsigned int i = 0; i < ri->GetTrustedCerts().size(); i++) {
        SPtr<OMAPublicCertificate> devCert =
          verifier->VerifyChain(ri->GetTrustedCerts()[i], chain);
        if (devCert != 0) {
          return devCert;
        }
      }
    }
  } else {
    //  Verify chain.
    for (unsigned int i = 0; i < ri->GetTrustedCerts().size(); i++) {
      SPtr<OMAPublicCertificate> devCert =
        verifier->VerifyChain(ri->GetTrustedCerts()[i], chain);
      if (devCert != 0) {
        return devCert;
      }
    }
  }

  return 0;
}

/*! \brief  Constructor.

    \param  peerid                peer key identifier.
    \param  ccaching              certificate caching.
    \param  ddetails              device details.

    If fails, throws ROAPException.
*/
ServerRIHelloExtensions::ServerRIHelloExtensions(const SPtr<PeerKeyIdExtension>& peerid,
  const SPtr<CertCachingExtension>& ccaching, const SPtr<DeviceDetailsExtension>&
  ddetails): RIHelloExtensions(peerid, ccaching, ddetails) {
}

/*! \brief  Protocol check.

    \param  request           input, registration request.

    \returns  Boolean indicating success or failure of check.
*/
SPtr<RegResponse> ServerRIHelloExtensions::ProtocolCheck(const NZSPtr<RegRequest>&
    request) const {
  if (peerKeyId == 0) {
    if (request->GetCertChain() == 0) {
      return new UnsuccessRegResponse(new NoCertificateChainROAPStatus(), 0);
    }
  }
  if (details != 0) {
    if (request->GetExtensions()->GetDeviceDetails()->Details() == 0) {
      return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
    }
  }
  return 0;
}

/*! \brief  Constructor.

    \param  ver                   version.
    \param  idval                 rights issuer identifier.
    \param  algs                  selected algorithms.
    \param  nonceval              nonce.
    \param  trust                 trusted authorities.
    \param  inf                   server info.
    \param  exts                  extensions.
    \param  sessid                session identifier.
*/
ServerSuccessRIHello::ServerSuccessRIHello(const NZSPtr<ROAPVersion>& ver,
  const NZSPtr<ROAPIdentifier>& idval, const std::vector<NZSPtr<URIValue> >& algs,
  const NZSPtr<ROAPNonce>& nonceval, const SPtr<ROAPKeyIdentifiers>& trust,
  const SPtr<ROAPServerInfo>& inf, const SPtr<ServerRIHelloExtensions>& exts,
  const NZSPtr<ROAPSessionID>& sessid):
  SuccessRIHello(ver, idval, algs, nonceval, trust, inf,
  (exts != 0)? new RIHelloExtensions(exts->GetPeerKeyID(), exts->GetCertCaching(),
  exts->GetDeviceDetails()): 0, sessid), serverextensions(exts) {
}

/*! \brief  Protocol check.

    \param  request           input, registration request.

    \returns  Boolean indicating success or failure of check.
*/
SPtr<RegResponse> ServerSuccessRIHello::ProtocolCheck(const NZSPtr<RegRequest>&
    request) const {
  SPtr<RegResponse> ret;
  if (serverextensions != 0) {
    if ((ret = serverextensions->ProtocolCheck(request)) != 0) {
      return ret;
    }
  }
  if (info != 0) {
    if (request->GetServerInfo() == 0) {
      return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
    } else {
      if (((*(info)) == (*(request->GetServerInfo()))) == false) {
        return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
      }
    }
  }
  return 0;
}

/*! \brief  Constructor.

    \param  devctx                device context.
    \param  regdb                 registration database.
    \param  dhello                device hello message.
    \param  rhello                rights issuer hello message.
*/
ServerRIHelloProtocolContext::ServerRIHelloProtocolContext(const NZSPtr<TempServerDeviceContext>& devctx,
  const NZSPtr<ServerRegDatabase>& regdb, const NZSPtr<DeviceHelloRequest>&
  dhello, const NZSPtr<ServerSuccessRIHello>& rhello): deviceCtx(devctx),
  regDB(regdb), dHello(dhello), rHello(rhello) {
}

/*! \brief  Constructor.

    \param  peerid                  peer key identifier.
    \param  ddetails                device details.
    \param  noocsp                  no OCSP response.
    \param  ocspkeyid               OCSP responder key identifier.

    If fails, throws ROAPException.
*/
ServerRegRequestExtensions::ServerRegRequestExtensions(const SPtr<PeerKeyIdExtension>&
  peerid, const SPtr<DeviceDetailsExtension>& ddetails,
  const SPtr<NoOCSPResponseExtension>& noocsp,
  const SPtr<OCSPResponderKeyIdExtension>& ocspkeyid):
  RegRequestExtensions(peerid, ddetails, noocsp, ocspkeyid) {
}

/*! \brief  Check and update protocol.

    \param  context             input, protocol context.
    \param  resp                input-output, temporary registration response.
    \param  rissuer             input, rights issuer context.

    \returns  Registration response message. If not zero, it means that check
              failed (then it is an unsuccess registration response).
*/
SPtr<RegResponse> ServerRegRequestExtensions::ProtocolUpdate(const
    NZSPtr<ServerRIHelloProtocolContext>& context, NZSPtr<TempRegResponse>& resp,
    const NZSPtr<ServerRIContext>& rissuer) const {
  if (peerKeyId != 0) {
    if (peerKeyId->GetIdentifier() != 0) {
      if ((*(peerKeyId->GetIdentifier())) != (*(rissuer->GetKeyID()))) {
        resp->chain = rissuer->GetCertChain();
      }
    }
  } else {
    resp->chain = rissuer->GetCertChain();
  }
  if (noOCSP == 0) {
    resp->ocsps = rissuer->GetOCSPResponses();
  }
  //  \todo: OCSPResponderKeyIdentifier.
  return 0;
}

/*! \brief  Constructor.

    \param  rhs               registration request.
*/
ServerRegRequest::ServerRegRequest(const NZSPtr<RegRequest>& rhs):
  RegRequest(rhs->GetTriggerNonce(), rhs->GetDeviceNonce(), rhs->GetTime(),
  rhs->GetCertChain(), rhs->GetTrustedAuthorities(), rhs->GetServerInfo(),
  rhs->GetExtensions(), rhs->GetSignature(), rhs->GetSessionID()),
  serverextensions((rhs->GetExtensions() != 0)? new ServerRegRequestExtensions(rhs->GetExtensions()->GetPeerKeyId(),
  rhs->GetExtensions()->GetDeviceDetails(), rhs->GetExtensions()->GetNoOCSPResponse(),
  rhs->GetExtensions()->GetOCSPResponderKeyId()): 0) {
}

/*! \brief  Check and update protocol.

    \param  tracker             input-output, protocol tracker.
    \param  verifier            input, certificate verifier.
    \param  rissuer             input, rights issuer context.

    \returns  Registration response.
*/
NZSPtr<RegResponse> ServerRegRequest::ProtocolUpdate(const NZSPtr<ServerProtocolTracker>&
    tracker, const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<ServerRIContext>& rissuer) const {
  if (tracker->idToRIHelloContext.find(sessionID) == tracker->idToRIHelloContext.end()) {
    return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
  }
  NZSPtr<ServerRIHelloProtocolContext> context = 
    (NZSPtr<ServerRIHelloProtocolContext>)(tracker->idToRIHelloContext[sessionID]);
  SPtr<RegResponse> err;
  if ((err = context->rHello->ProtocolCheck((RegRequest*)this)) != 0) {
    return err;
  }
  NZSPtr<TempRegResponse> tempRR = new TempRegResponse();
  if (serverextensions != 0) {
    if ((err = serverextensions->ProtocolUpdate(context, tempRR, rissuer)) != 0) {
      return err;
    }
  }
  //  Sanity check.
  if (context->deviceCtx->deviceID == 0) {
    //  Error.
    tracker->idToRIHelloContext.erase(sessionID);
    return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
  }
  SPtr<OMAPublicCertificate> devCert;
  SPtr<ServerDeviceContext> ctx =
    context->regDB->GetContext(context->deviceCtx->deviceID);

  if (chain == 0) {
    if (ctx == 0) {
      //  Error.
      tracker->idToRIHelloContext.erase(sessionID);
      return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
    }
    devCert = ctx->GetPublicCert();
  } else {
    //  Device has sent its certificate chain. This could be either because
    //  we don't have its context (and its public key), or because we have
    //  an outdated context, with outdated key (so in peer key ID extension, our
    //  key identifier was not equal to device's own identifier). Another
    //  possibility could be that device doesn't follow the standard protocol,
    //  and in spite of us having its context and indicating it with peer key
    //  ID extension, it sent its certificate chain again.

    if ((devCert = VerifyChain(ctx, rissuer, verifier, chain)) == 0) {
      tracker->idToRIHelloContext.erase(sessionID);
      return new UnsuccessRegResponse(new InvalidCertificateChainROAPStatus(), 0);
    }
    context->deviceCtx->publicCert = devCert;
    context->deviceCtx->chain = chain;
  }
  if (devCert->Verify(signature, context->dHello->XmlEncode() +
      context->rHello->XmlEncode() + XmlEncodeWithoutSignature()) == false) {
    //  Error.
    tracker->idToRIHelloContext.erase(sessionID);
    return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
  }
  context->deviceCtx->trusted = trusted;
  if (serverextensions != 0) {
    if (serverextensions->GetDeviceDetails() != 0) {
      if (serverextensions->GetDeviceDetails()->Details() != 0) {
        context->deviceCtx->details = serverextensions->GetDeviceDetails()->Details();
      }
    }
  }
  //  Temp registration response, for signature.
  SPtr<RegResponseExtensions> exts;
  if (rissuer->GetDomainNameWhiteList() != 0) {
    exts = new RegResponseExtensions(rissuer->GetDomainNameWhiteList());
  }
  NZSPtr<SuccessRegResponse> tempResp = new SuccessRegResponse(rissuer->GetURL(),
    tempRR->chain, tempRR->ocsps, exts, "", sessionID);
  Base64StringT sig;
  if (rissuer->GetPrivateKey()->Sign(XmlEncode() + tempResp->XmlEncodeWithoutSignature(),
      sig) == false) {
    //  Error.
    tracker->idToRIHelloContext.erase(sessionID);
    return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
  }
  NZSPtr<SuccessRegResponse> regResp = new SuccessRegResponse(rissuer->GetURL(),
    tempRR->chain, tempRR->ocsps, exts, sig, sessionID);

  if (context->regDB->AddDevice(context->deviceCtx) == false) {
    //  Error.
    tracker->idToRIHelloContext.erase(sessionID);
    return new UnsuccessRegResponse(new AbortROAPStatus(), 0);
  }
  tracker->idToRIHelloContext.erase(sessionID);
  return (SuccessRegResponse*)regResp;
}

/*! \brief  Constructor.

    \param  ccaching                  certificate caching.
*/
ServerDeviceHelloExtensions::ServerDeviceHelloExtensions(const
  NZSPtr<CertCachingExtension>& ccaching): DeviceHelloExtensions(ccaching) {
}

/*! \brief  Check and update protocol.

    \param  context           input, temporary device context.

    \returns  Rights issuer hello response. If not zero, check failed,
              and response is unsuccessful rights issuer hello response.
*/
SPtr<RIHelloResponse>  ServerDeviceHelloExtensions::ProtocolUpdate(const
    NZSPtr<TempServerDeviceContext>& context) const {
  context->caching = caching;
  return 0;
}

/*! \brief  Constructor.

    \param  rhs             device hello request.
*/
ServerDeviceHelloRequest::ServerDeviceHelloRequest(const NZSPtr<DeviceHelloRequest>&
  rhs): DeviceHelloRequest(rhs->GetTriggerNonce(), rhs->GetVersion(),
  rhs->GetDeviceIDs(), rhs->GetSupportedAlgs(), rhs->GetExtensions()),
  serverextensions((rhs->GetExtensions() != 0)? new ServerDeviceHelloExtensions(rhs->GetExtensions()->GetCertCaching()): 0) {
}

/*! \brief  Check and update protocol.

    \param  tracker               input-output, protocol tracker.
    \param  noncer                input, nonce creator.
    \param  sessioner             input, session identifier creator.
    \param  devURL                input, device URL.
    \param  regDB                 input, registration database.
    \param  rissuer               input, rights issuer context.

    \returns  Rights issuer hello response.
*/
NZSPtr<RIHelloResponse> ServerDeviceHelloRequest::ProtocolUpdate(const
    NZSPtr<ServerProtocolTracker>& tracker, const NZSPtr<OMADRMNonceCreator>& noncer,
    const NZSPtr<OMADRMSessionIDCreator>& sessioner, const NZSPtr<URIValue>& devURL,
    const NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<ServerRIContext>& rissuer) const {
  /*  \todo: Do we have to do something about the trigger?
  */
  if (nonce != 0) {
    if (tracker->nonceToRegTrigger.find((NZSPtr<ROAPNonce>)nonce) ==
        tracker->nonceToRegTrigger.end()) {
      return new UnsuccessRIHello(new AbortROAPStatus());
    } else {
      tracker->nonceToRegTrigger.erase((NZSPtr<ROAPNonce>)nonce);
    }
  }
  NZSPtr<TempServerDeviceContext> devCtx = new TempServerDeviceContext(0,
    deviceIDs[0], 0, devURL, 0, std::vector<NZSPtr<URIValue> >(), 0, 0, 0);
  if (serverextensions != 0) {
    SPtr<RIHelloResponse> err = serverextensions->ProtocolUpdate(devCtx);
    if (err != 0) {
      return (NZSPtr<RIHelloResponse>)err;
    }
  }
  devCtx->version = version;
  devCtx->deviceID = deviceIDs[0];
  devCtx->algorithms = algorithms;

  SPtr<ROAPSessionID> prev;
  if (tracker->idToRIHelloContext.empty() == false) {
    prev = (--(tracker->idToRIHelloContext.end()))->first;
//    prev = tracker->idToRIHelloContext.Last();
  }
  NZSPtr<ROAPSessionID> sessID = sessioner->CreateSessionID(prev);
  NZSPtr<ROAPVersion> version = rissuer->GetVersion();
  NZSPtr<ROAPIdentifier> riID = rissuer->GetID();
  std::vector<NZSPtr<URIValue> > algorithms = rissuer->GetAlgorithms();
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  SPtr<ROAPKeyIdentifiers> trusted = rissuer->GetTrusted();
  SPtr<ROAPServerInfo> sInfo = rissuer->GetServerInfo();
  SPtr<PeerKeyIdExtension> peerKeyId;
  SPtr<CertCachingExtension> caching = rissuer->GetCertCaching();
  SPtr<DeviceDetailsExtension> details;
  if (regDB->GetContext(deviceIDs[0]) != 0) {
    peerKeyId = regDB->GetContext(deviceIDs[0])->CreatePeerKeyId(true);
    if (regDB->GetContext(deviceIDs[0])->GetDetails() == 0) {
      details = new CriticalDeviceDetailsExtension(0);
    }
  } else {
    details = new CriticalDeviceDetailsExtension(0);
  }
  SPtr<ServerRIHelloExtensions> exts;
  if ((peerKeyId != 0) || (caching != 0) || (details != 0)) {
    exts = new ServerRIHelloExtensions(peerKeyId, caching, details);
  }
  NZSPtr<ServerSuccessRIHello> riHello = new ServerSuccessRIHello(version,
    riID, algorithms, nonce, trusted, sInfo, exts, sessID);
  NZSPtr<ServerRIHelloProtocolContext> protCtx =
    new ServerRIHelloProtocolContext(devCtx, regDB, (DeviceHelloRequest*)this,
    riHello);
  tracker->idToRIHelloContext[sessID] = protCtx;

  return (ServerSuccessRIHello*)riHello;
}

/*! \brief  Constructor.

    \param  peerid                peer key identifier.
    \param  noocsp                no OCSP response.
    \param  ocspresp              OCSP responder key identifier.
    \param  transid               transaction identifier.

    If fails, throws ROAPException.
*/
ServerROReqExtensions::ServerROReqExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
  SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
  ocspresp, const SPtr<TransactionIdExtension>& transid):
  RORequestExtensions(peerid, noocsp, ocspresp, transid) {
}

/*! \brief  Check and update protocol.

    \param  regDB             input, registration database.
    \param  roDB              input, right objects database.
    \param  response          input-output, temporary rights objects response.
    \param  rissuer           input, rights issuer context.

    \returns  2-pass rights objects response. If not zero, check failed,
              and response is an unsuccessful 2-pass rights objects response.
*/
SPtr<TwoPassROResponse> ServerROReqExtensions::ProtocolUpdate(const
    NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<ServerRODatabase>& roDB,
    const NZSPtr<TempROResponse>& response, const NZSPtr<ServerRIContext>& rissuer) const {
  if (peerKeyId == 0) {
    response->chain = rissuer->GetCertChain();
  } else {
    if ((*(peerKeyId->GetIdentifier())) != (*(rissuer->GetKeyID()))) {
      response->chain = rissuer->GetCertChain();
    }
  }
  if (noOCSP == 0) {
    response->ocsps = rissuer->GetOCSPResponses();
  }
  return 0;
}

/*! \brief  Constructor.

    Size of rights objects infos vector must be >= 1.

    \param  rhs           rights objects request.

    If fails, throws ROAPException.
*/
ServerRORequest::ServerRORequest(const NZSPtr<RORequest>& rhs):
  RORequest(rhs->GetTriggerNonce(), rhs->GetDeviceID(), rhs->GetDomainID(),
  rhs->GetRightsIssuerID(), rhs->GetDeviceNonce(), rhs->GetTime(), rhs->GetInfo(),
  rhs->GetCertChain(), rhs->GetExtensions(), rhs->GetSignature()),
  serverextensions((rhs->GetExtensions() != 0)? new ServerROReqExtensions(rhs->GetExtensions()->GetPeerKeyID(),
  rhs->GetExtensions()->GetNoOCSPResponse(), rhs->GetExtensions()->GetOCSPResponderKeyID(),
  rhs->GetExtensions()->GetTransactionID()): 0) {
}

/*! \brief  Protocol check.

    \param  regDB               input, registration database.
    \param  roDB                input, rights objects database.
    \param  verifier            input, certificate verifier.
    \param  tracker             input-output, protocol tracker.
    \param  rissuer           input, rights issuer context.

    \returns  2-pass rights objects response.
*/
NZSPtr<TwoPassROResponse> ServerRORequest::ProtocolUpdate(const
    NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<ServerRODatabase>& roDB,
    const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<ServerProtocolTracker>& tracker, const
    NZSPtr<ServerRIContext>& rissuer) const {
  /*  \todo: Do we have to do something about the trigger?
  */
  if (tNonce != 0) {
    if (tracker->nonceToROTrigger.find((NZSPtr<ROAPNonce>)tNonce) ==
        tracker->nonceToROTrigger.end()) {
      return new UnsuccessTwoPassROResponse(new AbortROAPStatus());
    } else {
      tracker->nonceToROTrigger.erase((NZSPtr<ROAPNonce>)tNonce);
    }
  }
  NZSPtr<TempROResponse> tempResp = new TempROResponse();
  SPtr<TwoPassROResponse> err;
  if (serverextensions != 0) {
    if ((err = serverextensions->ProtocolUpdate(regDB, roDB, tempResp, rissuer)) != 0) {
      return (NZSPtr<TwoPassROResponse>)err;
    }
  }
  /*  Check if we have device context. If we do, read the public key, if it
      exists, if not check the certificate chain and take it from there. If
      we cannot get the device's public key, return error.
  */
  SPtr<OMAPublicCertificate> devCert;
  if (regDB->GetContext(deviceID) == 0) {
    return new UnsuccessTwoPassROResponse(new NotRegisteredROAPStatus());
  }
  if (chain != 0) {
    if ((devCert = VerifyChain(regDB->GetContext(deviceID), rissuer, verifier,
        chain)) == 0) {
      return new UnsuccessTwoPassROResponse(new InvalidCertificateChainROAPStatus());
    }
    regDB->GetContext(deviceID)->UpdateContext(chain, devCert);
  } else {
    devCert = regDB->GetContext(deviceID)->GetPublicCert();
  }
  //  Now we know that devCert != 0.
  //  Basic task is to build protected rights objects.
  std::vector<NZSPtr<ROAPProtectedRO> > protRO;

  //  Build up device protected rights objects.
  for (unsigned int i = 0; i < info->GetDatas().size(); i++) {
    Base64StringT enckey;
    SPtr<OEXRights> rights;
    if (roDB->GetRO(info->GetDatas()[i]->GetROID(), enckey, rights) == true) {
      Base64StringT eenckey;
      if (devCert->Encrypt(enckey, eenckey) == false) {
        return new UnsuccessTwoPassROResponse(new AbortROAPStatus());
      }
      NZSPtr<XencEncryptedKey> key = new XencEncryptedKey(0, 0,
        new CValueXencCipherData(eenckey), 0, 0, 0, 0, 0, 0, 0, 0);

      NZSPtr<ROAPROPayload> payload = new DeviceROAPROPayload(
        rissuer->GetID(), NZSPtr<OEXRights>(rights), 0, 0,
        key, rissuer->GetVersion(), info->GetDatas()[i]->GetROID(), 0, 0);

      Base64StringT signature;
      if (rissuer->GetPrivateKey()->Sign(payload->XmlEncode(), signature) == false) {
        return new UnsuccessTwoPassROResponse(new AbortROAPStatus());
      }
      NZSPtr<ROAPProtectedRO> ro = new ROAPProtectedRO(payload,
        new DSSignature(new DSSignedInfo(new DSCanonicalizationMethod(
        new URIValue("uri")), new DSSignatureMethod(0, new URIValue("uri")),
        std::vector<NZSPtr<DSReference> >(1, new DSReference(0,
        new DSDigestMethod(new URIValue("digest method")), new DSDigestValue(
        "digestvalue"), 0, 0, 0)), 0),
        new DSSignatureValue(signature, 0), 0, std::vector<NZSPtr<DSObject> >(), 0));

      protRO.push_back(ro);
    } else {
      //  This is an either an internal error (server sent wrong roID to the
      //  agent), or the agent requested wrong roID.
      return new UnsuccessTwoPassROResponse(new AbortROAPStatus());
    }
  }

  //  TODO: Build up domain protected rights objects for domains that device
  //  is member of.

  NZSPtr<SuccessTwoPassROResponse> resp =
    new SuccessTwoPassROResponse(deviceID, rissuer->GetID(),
    dNonce, protRO, tempResp->chain, tempResp->ocsps, 0, "");
  Base64StringT signature;
  if (rissuer->GetPrivateKey()->Sign(resp->XmlEncodeWithoutSignature(), signature)
      == false) {
    return 0;
  }
  return new SuccessTwoPassROResponse(deviceID, rissuer->GetID(),
    dNonce, protRO, tempResp->chain, tempResp->ocsps, 0, signature);
}

/*! \brief  Check and update protocol.

    \param  regDB             input, registration database.
    \param  roDB              input, rights objects database.
    \param  devID             input, device identifier.
    \param  roID              input, rights objects identifier.
    \param  rissuer           input, rights issuer context.

    \returns  1-pass rights objects response. If zero, failed.
*/
SPtr<OnePassROResponse> ServerOnePassROResponseHandler::ProtocolUpdate(const
    NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<ServerRODatabase>& roDB,
    const NZSPtr<ROAPIdentifier>& devID, const std::vector<NZSPtr<IDValue> >&
    roID, const NZSPtr<ServerRIContext>& rissuer) const {
  /*  Check if we have device context. If we do, read the public key, if it
      exists, if not check the certificate chain and take it from there. If
      we cannot get the device's public key, return error.
  */
  SPtr<OMAPublicCertificate> devCert;
  if (regDB->GetContext(devID) == false) {
    return 0;
  }
  if (regDB->GetContext(devID)->GetPublicCert() == 0) {
    return 0;
  } else {
    devCert = regDB->GetContext(devID)->GetPublicCert();
  }
  //  Now we know that devCert != 0.
  //  Basic task is to build protected rights objects.
//  if (roDB->dIDroIDRO.Has(devID) == false) {
//    return 0;
//  }
  std::vector<NZSPtr<ROAPProtectedRO> > protRO;
  for (unsigned int i = 0; i < roID.size(); i++) {
    if (roDB->GetRO(roID[i]) != 0) {
      protRO.push_back((NZSPtr<ROAPProtectedRO>)(roDB->GetRO(roID[i])));
    } else {
      return 0;
    }
  }
  //  Since the device is registered, it has our context saved. So the only case
  //  when we could send the certificate chain is if we know it's updated from
  //  the registration session with the device.
//  SPtr<ROAPCertificateChain> cChain = regDB->GetContext(devID)->GetRICertChain();
  SPtr<ROAPCertificateChain> cChain;
  NZSPtr<OnePassROResponse> resp = new OnePassROResponse(
    new SuccessROAPStatus(), devID, rissuer->GetID(), protRO, cChain,
    rissuer->GetOCSPResponses(), 0, "");
  Base64StringT signature;
  if (rissuer->GetPrivateKey()->Sign(resp->XmlEncodeWithoutSignature(), signature)
      == false) {
    return 0;
  }
  return new OnePassROResponse(new SuccessROAPStatus(), devID, rissuer->GetID(),
    protRO, cChain, rissuer->GetOCSPResponses(), 0, signature);
}

/*! \brief  Constructor.

    \param  peerid              peer key identifier.
    \param  noocsp              no OCSP response.
    \param  ocspresp            OCSP responder key identifier.
    \param  hchain              hash chain support.

    If fails, throws ROAPException.
*/
ServerJoinDomainReqExt::ServerJoinDomainReqExt(const SPtr<PeerKeyIdExtension>& peerid, const
  SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
  ocspresp, const SPtr<HashChainSupportExtension>& hchain):
  JoinDomainReqExtensions(peerid, noocsp, ocspresp, hchain) {
}

/*! \brief  Check and update protocol.

    \param  regDB             input, registration database.
    \param  response          input-output, temporary join domain response.
    \param  rissuer           input, rights issuer context.

    \returns  Join domain response. If not zero, check failed, and response
              is an unsuccessful join domain response.
*/
SPtr<JoinDomainResponse> ServerJoinDomainReqExt::ProtocolUpdate(const
    NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<TempJoinDomainResponse>& response,
    const NZSPtr<ServerRIContext>& rissuer)
    const {
  if (peerKeyId != 0) {
    if ((*(peerKeyId->GetIdentifier())) != (*(rissuer->GetKeyID()))) {
      response->chain = rissuer->GetCertChain();
    }
  } else {
    response->chain = rissuer->GetCertChain();
  }
  if (noOCSP == 0) {
    response->ocsps = rissuer->GetOCSPResponses();
  }
  return 0;
}

/*! \brief  Constructor.

    \param  rhs                 join domain request.
*/
ServerJoinDomainRequest::ServerJoinDomainRequest(const NZSPtr<JoinDomainRequest>& rhs):
  JoinDomainRequest(rhs->GetTriggerNonce(), rhs->GetDeviceID(),
  rhs->GetRightsIssuerID(), rhs->GetDeviceNonce(), rhs->GetTime(),
  rhs->GetDomainID(), rhs->GetCertChain(), rhs->GetExtensions(), rhs->GetSignature()),
  serverextensions((rhs->GetExtensions() != 0)? new ServerJoinDomainReqExt(rhs->GetExtensions()->GetPeerKeyId(),
  rhs->GetExtensions()->GetNoOCSPResponse(), rhs->GetExtensions()->GetOCSPResponderKeyId(),
  rhs->GetExtensions()->GetHashChainSupport()): 0) {
}

/*! \brief  Check and update protocol

    \param  regDB             input, registration database.
    \param  verifier          input, certificate verifier.
    \param  tracker           input-output, protocol tracker.
    \param  rissuer           input, rights issuer context.

    \returns  Join domain response.
*/
NZSPtr<JoinDomainResponse> ServerJoinDomainRequest::ProtocolUpdate(const
    NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<OMACertificateVerifier>&
    verifier, const NZSPtr<ServerProtocolTracker>& tracker,
    const NZSPtr<ServerRIContext>& rissuer) const {
  /*  \todo: Do we have to do something about the trigger?
  */
  if (tNonce != 0) {
    if (tracker->nonceToJoinTrigger.find((NZSPtr<ROAPNonce>)tNonce) ==
        tracker->nonceToJoinTrigger.end()) {
      return new UnsuccessJoinDomainResponse(new AbortROAPStatus());
    } else {
      tracker->nonceToJoinTrigger.erase((NZSPtr<ROAPNonce>)tNonce);
    }
  }
  NZSPtr<TempJoinDomainResponse> tempResp = new TempJoinDomainResponse();
  SPtr<JoinDomainResponse> err;
  if (serverextensions != 0) {
    if ((err = serverextensions->ProtocolUpdate(regDB, tempResp, rissuer)) != 0) {
      return (NZSPtr<JoinDomainResponse>)err;
    }
  }
  if ((*riID) != (*(rissuer->GetID()))) {
    return new UnsuccessJoinDomainResponse(new AbortROAPStatus());
  }
  SPtr<OMAPublicCertificate> devCert;
  if (regDB->GetContext(deviceID) == 0) {
    return new UnsuccessJoinDomainResponse(new AbortROAPStatus());
  }
  if (chain != 0) {
    if ((devCert = VerifyChain(regDB->GetContext(deviceID), rissuer, verifier,
        chain)) == 0) {
      return new UnsuccessJoinDomainResponse(new InvalidCertificateChainROAPStatus());
    }
    regDB->GetContext(deviceID)->UpdateContext(chain, devCert);
  } else {
    devCert = regDB->GetContext(deviceID)->GetPublicCert();
  }
  if (devCert->Verify(signature, XmlEncodeWithoutSignature()) == false) {
    return new UnsuccessJoinDomainResponse(new SignatureErrorROAPStatus());
  }
  /*  \todo: If device key was changed due to new certificate chain, then domain
      info must be reencrypted.
  */
  SPtr<ROAPDomainInfo> domInfo;
  if ((domInfo = regDB->GetDomain(deviceID, domainID)) == 0) {
    return new UnsuccessJoinDomainResponse(new InvalidDomainROAPStatus());
  }
  NZSPtr<SuccessJoinDomainResponse> tempR =
    new SuccessJoinDomainResponse(deviceID, rissuer->GetID(),
    dNonce, (NZSPtr<ROAPDomainInfo>)domInfo, tempResp->chain, tempResp->ocsps,
    0, "");
  Base64StringT signature;
  if (rissuer->GetPrivateKey()->Sign(tempR->XmlEncodeWithoutSignature(), signature)
      == false) {
    return new UnsuccessJoinDomainResponse(new AbortROAPStatus());
  }

  return new SuccessJoinDomainResponse(deviceID, rissuer->GetID(),
    dNonce, (NZSPtr<ROAPDomainInfo>)domInfo, tempResp->chain, tempResp->ocsps,
    0, signature);
}

/*! \brief  Constructor.

    \param  rhs                 leave domain request.
*/
ServerLeaveDomainRequest::ServerLeaveDomainRequest(const NZSPtr<LeaveDomainRequest>&
  rhs): LeaveDomainRequest(rhs->GetTriggerNonce(), rhs->GetDeviceID(),
  rhs->GetRightsIssuerID(), rhs->GetDeviceNonce(), rhs->GetTime(), rhs->GetDomainID(),
  rhs->GetCertChain(), rhs->GetExtensions(), rhs->GetSignature()) {
}

/*! \brief  Check and update protocol.

    \param  regDB           input, registration database.
    \param  verifier        input, certificate verifier.
    \param  tracker         input-output, protocol tracker.
    \param  rissuer         input, rights issuer context.

    \returns  Leave domain response.
*/
NZSPtr<LeaveDomainResponse> ServerLeaveDomainRequest::ProtocolUpdate(const
    NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<OMACertificateVerifier>&
    verifier, const NZSPtr<ServerProtocolTracker>& tracker,
    const NZSPtr<ServerRIContext>& rissuer) const {
  /*  \todo: Do we have to do something about the trigger?
  */
  if (tNonce != 0) {
    if (tracker->nonceToLeaveTrigger.find((NZSPtr<ROAPNonce>)tNonce) ==
        tracker->nonceToLeaveTrigger.end()) {
      return new UnsuccessLeaveDomainResponse(new AbortROAPStatus());
    } else {
      tracker->nonceToLeaveTrigger.erase((NZSPtr<ROAPNonce>)tNonce);
    }
  }
  NZSPtr<TempLeaveDomainResponse> tempResp = new TempLeaveDomainResponse();
  if ((*riID) != (*(rissuer->GetID()))) {
    return new UnsuccessLeaveDomainResponse(new AbortROAPStatus());
  }
  SPtr<OMAPublicCertificate> devCert;
  if (regDB->GetContext(deviceID) == 0) {
    return new UnsuccessLeaveDomainResponse(new AbortROAPStatus());
  }
  if (chain != 0) {
    if ((devCert = VerifyChain(regDB->GetContext(deviceID), rissuer, verifier,
        chain)) == 0) {
      return new UnsuccessLeaveDomainResponse(new InvalidCertificateChainROAPStatus());
    }
    regDB->GetContext(deviceID)->UpdateContext(chain, devCert);
  } else {
    devCert = regDB->GetContext(deviceID)->GetPublicCert();
  }
  if (devCert->Verify(signature, XmlEncodeWithoutSignature()) == false) {
    return new UnsuccessLeaveDomainResponse(new SignatureErrorROAPStatus());
  }
  return new SuccessLeaveDomainResponse(dNonce, domainID, 0);
}

/*! \brief  Constructor.

    Size of content identifiers vector must be >= 1.

    \param  rhs               initial rights objects request.

    If fails, throws ROAPException.
*/
ServerInitialRORequest::ServerInitialRORequest(const NZSPtr<InitialRORequest>& rhs):
  InitialRORequest(rhs) {
}

/*! \brief  Constructor.

    Size of content identifiers vector must be >= 1.

    \param  devid               device identifier.
    \param  idvals              content identifiers vector.
    \param  urival              device URL.

    If fails, throws ROAPException.
*/
ServerInitialRORequest::ServerInitialRORequest(const NZSPtr<ROAPIdentifier>& devid,
  const std::vector<NZSPtr<URIValue> >& idvals): InitialRORequest(devid, idvals) {
}

/*! \brief  Create a rights objects acquisition trigger as a response to
            initial rights objects request.

    \param  regDB               input, registration database.
    \param  roDB                input, rights database.
    \param  noncer              input, nonce creator.
    \param  tracker             input-output, protocol tracker.
    \param  rissuer             input, rights issuer context.

    \returns  Rights objects acquisition trigger. If zero, failed.
*/
SPtr<ROAcquisitionTrigger> ServerInitialRORequest::ProtocolUpdate(const NZSPtr<ServerRegDatabase>&
    regDB, const NZSPtr<ServerRODatabase>& roDB, const NZSPtr<OMADRMNonceCreator>&
    noncer, const NZSPtr<ServerProtocolTracker>& tracker, const NZSPtr<ServerRIContext>&
    rissuer) {
  //  Check if device is registered.
  if (regDB->GetContext(deviceID) == 0) {
    return 0;
  }
  std::vector<NZSPtr<ROIDContentID> > roidcids;
  for (unsigned int i = 0; i < contentIDs.size(); i++) {
    //  Create a new rights objects identifier dependent on deviceID and contentID.
    std::string enc = deviceID->XmlEncode() + contentIDs[i]->XmlEncode();
    Base64StringT b64;
    if (Base64Factory::Encode(ByteSeq((ByteT*)enc.data(), enc.size()), b64) == false) {
      return 0;
    }
    NZSPtr<IDValue> roid(new IDValue(b64.BString()));
    if (roDB->SetROID(roid, deviceID, contentIDs[i]) == false) {
      //  Error.
      return 0;
    }
    roidcids.push_back(new ROIDContentID(roid, std::vector<NZSPtr<URIValue> >(
      1, contentIDs[i])));
  }

  NZSPtr<NDomainROTriggerData> triggerdata = new NDomainROTriggerData(
    rissuer->GetID(), noncer->CreateNonce(), rissuer->GetURL(), roidcids,
    /* What should this be? */ new IDValue("aa"));

  SPtr<ROAcquisitionTrigger> trigger = new NDomainROTrigger(triggerdata, 0,
    rissuer->GetVersion(), 0);
  if (triggerdata->GetNonce() != 0) {
    tracker->nonceToROTrigger[(NZSPtr<ROAPNonce>)(triggerdata->GetNonce())] = trigger;
  }

  return trigger;
}

} // namespace DRMPlugin
