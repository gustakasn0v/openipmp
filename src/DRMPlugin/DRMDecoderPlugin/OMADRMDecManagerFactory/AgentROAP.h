/** \file AgentROAP.h

    OMA DRM agent's ROAP protocols implementation.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (AGENTROAP_H)
#define AGENTROAP_H

#include "OMADRMCommon.h"
#include "AgentBase.h"
#include <map>

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
  const NZSPtr<ROAPCertificateChain>& chain);

/*! \todo:  None of the device messages has device URL in it. How is the
    rights issuer/server supposed to send its messages to device, since it
    has no information where to send them? Rights issuer messages do have
    URL in it. Is this an inconsistency, bug in specifications, or what?
*/

/*! \brief  Extensions for device hello message (OMA DRM agent).
*/
class AgentDeviceHelloExtensions: public DeviceHelloExtensions {
public:
  /*! \brief  Constructor.

      \param  ccaching                  certificate caching.
  */
  AgentDeviceHelloExtensions(const NZSPtr<CertCachingExtension>& ccaching);

  /*! \brief  Check correctness of rights issuer hello message.

      \param  riHello             input, successful rights issuer hello.

      \returns  Boolean indicating success or failure of check.
  */
  bool ProtocolCheck(const NZSPtr<SuccessRIHello>& riHello) const;
};

/*! \brief  Device hello message (OMA DRM agent).
*/
class AgentDeviceHelloRequest: public DeviceHelloRequest {
public:
  /*! \brief  Constructor.

      Size of device identifiers vector must be >= 1.

      \param  tnonce                  trigger nonce.
      \param  ver                     version.
      \param  idvals                  device identifiers vector.
      \param  algs                    supported algorithms.
      \param  exts                    extensions.

      If fails, throws ROAPException.
  */
	AgentDeviceHelloRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPVersion>&
    ver,  const std::vector<NZSPtr<ROAPIdentifier> >& idvals,	const
    std::vector<NZSPtr<URIValue> >& algs, const SPtr<AgentDeviceHelloExtensions>& exts);

  /*! \brief  Check correctness of rights issuer hello message.

      \param  riHello             input, successful rights issuer hello.

      \returns  Boolean indicating success or failure of check.
  */
  bool ProtocolCheck(const NZSPtr<SuccessRIHello>& riHello) const;

private:
	SPtr<AgentDeviceHelloExtensions> agentextensions;
};

/*! \brief  Registration protocol context after sending device hello message.
*/
class DeviceHelloProtocolContext: public GC {
public:
  /*! \brief  Constructor.

      \param  dbase                       registration database.
      \param  ctx                         temporary rights issuer context.
      \param  hello                       agent's device hello message.
  */
  DeviceHelloProtocolContext(const NZSPtr<AgentRegDatabase>& dbase, const
    NZSPtr<TempAgentRIContext>& ctx, const NZSPtr<AgentDeviceHelloRequest>& hello);

  /*! \brief  Agent's registration database.
  */
  NZSPtr<AgentRegDatabase> regDB;

  /*! \brief  Temporary rights issuer context.
  */
  NZSPtr<TempAgentRIContext> riCtx;

  /*! \brief  Agent's device hello message.
  */
  NZSPtr<AgentDeviceHelloRequest> deviceHello;
};

/*! \brief  Extensions for registration request message (OMA DRM agent).
*/
class AgentRegRequestExtensions: public RegRequestExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid                  peer key identifier.
      \param  ddetails                device details.
      \param  noocsp                  no OCSP response.
      \param  ocspkeyid               OCSP responder key identifier.

      If fails, throws ROAPException.
  */
  AgentRegRequestExtensions(const SPtr<PeerKeyIdExtension>& peerid,
    const SPtr<DeviceDetailsExtension>& ddetails,
    const SPtr<NoOCSPResponseExtension>& noocsp,
    const SPtr<OCSPResponderKeyIdExtension>& ocspkeyid);

  /*! \brief  Check correctness of registration response message.

      \param  resp                    input, successful registration response.

      \returns  Boolean indicating success or failure of check.
  */
  bool ProtocolCheck(const NZSPtr<SuccessRegResponse>& resp) const;
};

/*! \brief  Registration request message (OMA DRM agent).
*/
class AgentRegRequest: public RegRequest {
public:
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
	AgentRegRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPNonce>& dnonce,
    const NZSPtr<DateTime>& dtime, const SPtr<ROAPCertificateChain>& cchain,
    const SPtr<ROAPKeyIdentifiers>& trust, const SPtr<ROAPServerInfo>& inf,
		const SPtr<AgentRegRequestExtensions>& exts, const Base64StringT& sig,
    const NZSPtr<ROAPSessionID>& sessid);

  /*! \brief  Check correctness of registration response message.

      \param  resp                    input, successful registration response.

      \returns  Boolean indicating success or failure of check.
  */
  bool ProtocolCheck(const NZSPtr<SuccessRegResponse>& resp) const;

private:
	SPtr<AgentRegRequestExtensions> agentextensions;
};

/*! \brief  Temporary registration request extensions.

    Used for building registration request message.
*/
class TempRegRequestExtensions: public GC {
public:
  /*! \brief  Device details.
  */
  SPtr<DeviceDetailsExtension> deviceDetails;
};

/*! \brief  Temporary registration request message.
*/
class TempRegRequest: public GC {
public:
  /*! \brief  Constructor.

      \param  exts                temporary registration request extensions.
  */
  TempRegRequest(const NZSPtr<TempRegRequestExtensions>& exts);

  /*! \brief  Certificate chain.
  */
	SPtr<ROAPCertificateChain> certChain;

  /*! \brief  Temporary registration request extensions.
  */
	NZSPtr<TempRegRequestExtensions> extensions;
};

/*! \brief  Registration protocol context.

    Context after sending device hello message, receiving and checking rights
    issuer hello message and sending registration request message.
*/
class AgentRIHelloProtocolContext: public GC {
public:
  /*! \brief  Constructor.

      \param  dbase                       registration database.
      \param  ctx                         temporary rights issuer context.
      \param  dhello                      agent's device hello message.
      \param  rhello                      rights issuer hello message.
      \param  regreq                      agent's registration request.
  */
  AgentRIHelloProtocolContext(const NZSPtr<AgentRegDatabase>& dbase, const
    NZSPtr<TempAgentRIContext>& ctx, const NZSPtr<AgentDeviceHelloRequest>& dhello,
    const NZSPtr<SuccessRIHello>& rhello, const NZSPtr<AgentRegRequest>& regreq);

  /*! \brief  Agent's registration database.
  */
  NZSPtr<AgentRegDatabase> regDB;

  /*! \brief  Temporary rights issuer context.
  */
  NZSPtr<TempAgentRIContext> riCtx;

  /*! \brief  Agent's device hello message.
  */
  NZSPtr<AgentDeviceHelloRequest> deviceHello;

  /*! \brief  Rights issuer's hello message.
  */
  NZSPtr<SuccessRIHello> riHello;

  /*! \brief  Agent's registration request message.
  */
  NZSPtr<AgentRegRequest> regRequest;
};

/*! \brief  Agent's registration protocol tracker.

    Contains current running registration protocol contexts.
    Rights issuer hello protocol contexts are grouped according to session
    identifiers.
*/
class AgentRegProtocolTracker: public GC {
public:
  /*! \brief  Device hello context.

      If != 0, it means that device hello message was sent, waiting for
      rights issuer hello message.
  */
  SPtr<DeviceHelloProtocolContext> deviceHelloContext;

  /*! \brief  Session identifier to running registration protocol contexts map.
  */
  std::map<NZSPtr<ROAPSessionID>, SPtr<AgentRIHelloProtocolContext> > idToRIHelloContext;
};

/*! \brief  Extensions for rights issuer hello message (OMA DRM agent).
*/
class AgentRIHelloExtensions: public RIHelloExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid                peer key identifier.
      \param  ccaching              certificate caching.
      \param  ddetails              device details.

      If fails, throws ROAPException.
  */
  AgentRIHelloExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
    SPtr<CertCachingExtension>& ccaching, const SPtr<DeviceDetailsExtension>&
    ddetails);

  /*! \brief  Check and update protocol step.

      \param  context           input, protocol context.
      \param  request           input-output, registration request.
      \param  device            input, device context.

      \returns  Boolean indicating success or failure of check.
  */
  bool ProtocolUpdate(const NZSPtr<DeviceHelloProtocolContext>& context, const
    NZSPtr<TempRegRequest>& request, const NZSPtr<AgentDeviceContext>& device) const;
};

/*! \brief  Successful rights issuer hello message (OMA DRM agent).
*/
class AgentSuccessRIHello: public SuccessRIHello {
public:
  /*! \brief  Constructor.

      \param  rhs               successful rights issuer hello.
  */
	AgentSuccessRIHello(const NZSPtr<SuccessRIHello>& rhs);

  /*! \brief  Check and update protocol.

      \param  tracker             input-output, protocol tracker.
      \param  timer               input, DRM timer.
      \param  noncer              input, DRM noncer.
      \param  device              input, device context.

      \returns  Registration request message. If zero, failed.
  */
  SPtr<RegRequest> ProtocolUpdate(const NZSPtr<AgentRegProtocolTracker>& tracker,
    const NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>& noncer,
    const NZSPtr<AgentDeviceContext>& device) const;

private:
	SPtr<AgentRIHelloExtensions> agentextensions;
};

/*! \brief  Successful registration response message (OMA DRM agent).
*/
class AgentSuccessRegResponse: public SuccessRegResponse {
public:
  /*! \brief  Constructor.

      \param  rhs             successful registration response.
  */
	AgentSuccessRegResponse(const NZSPtr<SuccessRegResponse>& rhs);

  /*! \brief  Check and update protocol.

      \param  tracker               input-output, protocol tracker.
      \param  verifier              input, certificate verifier.
      \param  device                input, device context.
      
      \returns  Boolean indicating success or failure.
  */
  bool ProtocolUpdate(const NZSPtr<AgentRegProtocolTracker>& tracker,
    const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<AgentDeviceContext>& device) const;
};

/*! \brief  Extensions for rights object request message (OMA DRM agent).
*/
class AgentROReqExtensions: public RORequestExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid                peer key identifier.
      \param  noocsp                no OCSP response.
      \param  ocspresp              OCSP responder key identifier.
      \param  transid               transaction identifier.

      If fails, throws ROAPException.
  */
  AgentROReqExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
    SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
    ocspresp, const SPtr<TransactionIdExtension>& transid);

  /*! \brief  Protocol check.

      \param  resp                  input, successful RO response.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolCheck(const NZSPtr<SuccessTwoPassROResponse>& resp) const;
};

/*! \brief  Rights object request (OMA DRM agent).
*/
class AgentRORequest: public RORequest {
public:
  /*! \brief  Constructor.

      \param  tnonce                  trigger nonce.
      \param  devid                   device identifier.
      \param  domid                   domain identifier.
      \param  riid                    rights issuer identifier.
      \param  dnonce                  device nonce.
      \param  dtime                   time.
      \param  inf                     RO info.
      \param  cchain                  certificate chain.
      \param  exts                    extensions.
      \param  sig                     signature.
  */
	AgentRORequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPIdentifier>& devid,
    const SPtr<ROAPDomainIdentifier>& domid, const NZSPtr<ROAPIdentifier>& riid,
    const NZSPtr<ROAPNonce>& dnonce, const NZSPtr<DefDateTime>& dtime,
    const NZSPtr<ROInfo>& inf, const SPtr<ROAPCertificateChain>& cchain,
    const SPtr<AgentROReqExtensions>& exts, const Base64StringT& sig);

  /*! \brief  Protocol check.

      \param  resp                  input, successful RO response.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolCheck(const NZSPtr<SuccessTwoPassROResponse>& resp) const;

private:
	SPtr<AgentROReqExtensions> agentextensions;
};

/*! \brief  Rights objects trigger handler.
*/
class ROTriggerHandler: public GC {
public:
  /*! \brief  Get trigger.

      \returns  Trigger.
  */
  virtual NZSPtr<ROAcquisitionTrigger> GetTrigger() const = 0;

  /*! \brief  Update rights objects database.

      \param  roDB            input-output, rights objects database.

      \returns  Boolean indicating success or failure.
  */
  virtual bool UpdateRODB(const NZSPtr<AgentRODatabase>& roDB) const = 0;
};

/*! \brief  Domain rights objects trigger handler.
*/
class DomainROTriggerHandler: public ROTriggerHandler {
public:
  /*! \brief  Constructor.

      \param  trig              trigger.
  */
  DomainROTriggerHandler(const NZSPtr<DomainROTrigger>& trig);

  /*! \brief  Get trigger.

      \returns  Trigger.
  */
  virtual NZSPtr<ROAcquisitionTrigger> GetTrigger() const {
    return (ROAcquisitionTrigger*)trigger;
  }

  /*! \brief  Update rights objects database.

      \param  roDB            input-output, rights objects database.

      \returns  Boolean indicating success or failure.
  */
  virtual bool UpdateRODB(const NZSPtr<AgentRODatabase>& roDB) const;

private:
  NZSPtr<DomainROTrigger> trigger;
};

/*! \brief  Non-domain rights objects trigger handler.
*/
class NDomainROTriggerHandler: public ROTriggerHandler {
public:
  /*! \brief  Constructor.

      \param  trig              trigger.
  */
  NDomainROTriggerHandler(const NZSPtr<NDomainROTrigger>& trig);

  /*! \brief  Get trigger.

      \returns  Trigger.
  */
  virtual NZSPtr<ROAcquisitionTrigger> GetTrigger() const {
    return (ROAcquisitionTrigger*)trigger;
  }

  /*! \brief  Update rights objects database.

      \param  roDB            input-output, rights objects database.

      \returns  Boolean indicating success or failure.
  */
  virtual bool UpdateRODB(const NZSPtr<AgentRODatabase>& roDB) const;

private:
  NZSPtr<NDomainROTrigger> trigger;
};

/*! \brief  Rights objects protocol context after sending rights object
            request message.
*/
class ROReqProtocolContext: public GC {
public:
  /*! \brief  Constructor.

      \param  regdbase              registration database.
      \param  rodbase               rights objects database.
      \param  req                   rights objects request.
      \param  hand                  trigger handler.
  */
  ROReqProtocolContext(const NZSPtr<AgentRegDatabase>& regdbase, const
    NZSPtr<AgentRODatabase>& rodbase, const NZSPtr<AgentRORequest>& req,
    const NZSPtr<ROTriggerHandler>& hand);

  /*! \brief  Registration database.
  */
  NZSPtr<AgentRegDatabase> regDB;

  /*! \brief  Rights objects database.
  */
  NZSPtr<AgentRODatabase> roDB;

  /*! \brief  Rights objects request.
  */
  NZSPtr<AgentRORequest> request;

  /*! \brief  Trigger handler.
  */
  NZSPtr<ROTriggerHandler> handler;
};

/*! \brief  Rights objects protocol tracker.

    Contains current running rights objects protocols, grouped by device nonces.
*/
class AgentROReqProtocolTracker: public GC {
public:
  /*! \brief  Nonce to rights objects protocol context map.
  */
  std::map<NZSPtr<ROAPNonce>, SPtr<ROReqProtocolContext> > nonceToCtx;
};

/*! \brief  Rights objects request message handler.

    \todo:  What about time, that is what if device doesn't support DRM time?
            The we cannot create definite time...
*/
class AgentROReqHandler: public GC {
public:
  /*! \brief  Constructor.

      \param  hand          trigger handler.
  */
  AgentROReqHandler(const NZSPtr<ROTriggerHandler>& hand);

  /*! \brief  Create rights objects request.

      \param  regDB                   input, registration database.
      \param  roDB                    input, rights objects database.
      \param  tracker                 input, protocol tracker.
      \param  timer                   input, DRM timer.
      \param  noncer                  input, DRM nonce creator.
      \param  device                  input, device context.

      \returns  Rights objects request. If zero, failed.
  */
  SPtr<RORequest> CreateRORequest(const NZSPtr<AgentRegDatabase>& regDB,
    const NZSPtr<AgentRODatabase>& roDB, const NZSPtr<AgentROReqProtocolTracker>&
    tracker, const NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>&
    noncer, const NZSPtr<AgentDeviceContext>& device) const;

private:
  NZSPtr<ROTriggerHandler> handler;
};

/*! \brief  Successful 2-Pass rights object response (OMA DRM agent).
*/
class AgentSuccessTwoPassROResponse: public SuccessTwoPassROResponse {
public:
  /*! \brief  Constructor.

      Size of protected rights objects vector must be >= 1.

      \param  rhs           successful 2-pass rights objects response.

      If fails, throws ROAPException.
  */
	AgentSuccessTwoPassROResponse(const NZSPtr<SuccessTwoPassROResponse>& rhs);

  /*! \brief  Check and update protocol.

      \param  tracker                 input-output, protocol tracker.
      \param  verifier                input, certificate verifier.
      \param  device                  input, device context.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolUpdate(const NZSPtr<AgentROReqProtocolTracker>& tracker,
    const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<AgentDeviceContext>& device) const;
};

/*! \brief  1-Pass rights object response (OMA DRM agent).
*/
class AgentOnePassROResponse: public OnePassROResponse {
public:
  /*! \brief  Constructor.

      Size of protected rights objects vector must be >= 1.

      \param  rhs               one pass rights objects response.

      If fails, throws ROAPException.
  */
	AgentOnePassROResponse(const NZSPtr<OnePassROResponse>& rhs);

  /*! \brief  Check and update protocol.

      \param  regDB                   input, registration database.
      \param  roDB                    input, rights objects database.
      \param  verifier                input, certificate verifier.
      \param  hasher                  input, hash calculator.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolUpdate(const NZSPtr<AgentRegDatabase>& regDB,
    const NZSPtr<AgentRODatabase>& roDB, const NZSPtr<OMACertificateVerifier>&
    verifier, const NZSPtr<OMADRMHasher>& hasher) const;
};

/*! \brief  Extensions for join domain request message (OMA DRM agent).
*/
class AgentJoinDomainReqExt: public JoinDomainReqExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid              peer key identifier.
      \param  noocsp              no OCSP response.
      \param  ocspresp            OCSP responder key identifier.
      \param  hchain              hash chain support.

      If fails, throws ROAPException.
  */
  AgentJoinDomainReqExt(const SPtr<PeerKeyIdExtension>& peerid, const
    SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
    ocspresp, const SPtr<HashChainSupportExtension>& hchain);

  /*! \brief  Protocol check.

      \param  response              input, join domain response.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolCheck(const NZSPtr<SuccessJoinDomainResponse>& response) const;
};

/*! \brief  Join domain request (OMA DRM agent).
*/
class AgentJoinDomainRequest: public JoinDomainRequest {
public:
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
	AgentJoinDomainRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPIdentifier>&
    devid, const NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPNonce>& dnonce,
    const NZSPtr<DateTime>& dtime, const NZSPtr<ROAPDomainIdentifier>& domid,
		const SPtr<ROAPCertificateChain>& cchain,	const SPtr<AgentJoinDomainReqExt>&
    exts, const Base64StringT& sig);

  /*! \brief  Protocol check

      \param  response              input, join domain response.

      \returns  Boolean indicating success or failure of check.
  */
  bool ProtocolCheck(const NZSPtr<SuccessJoinDomainResponse>& response) const;

private:
	SPtr<AgentJoinDomainReqExt> agentextensions;
};

/*! \brief  Join domain protocol context after sending join domain request message.
*/
class JoinDomainProtocolContext: public GC {
public:
  /*! \brief  Constructor.

      \param  regdbase              registration database.
      \param  req                   join domain request.
  */
  JoinDomainProtocolContext(const NZSPtr<AgentRegDatabase>& regdbase,
    const NZSPtr<AgentJoinDomainRequest>& req);

  /*! \brief  Registration database.
  */
  NZSPtr<AgentRegDatabase> regDB;

  /*! \brief  Join domain request.
  */
  NZSPtr<AgentJoinDomainRequest> request;
};

/*! \brief  Join domain protocol tracker.

    Contains current running join domain sessions, grouped by device nonces.
*/
class AgentJoinDomProtocolTracker: public GC {
public:
  /*! \brief  Nonce to join domain protocol context map.
  */
  std::map<NZSPtr<ROAPNonce>, SPtr<JoinDomainProtocolContext> > nonceToCtx;
};

/*! \brief  Successful join domain response (OMA DRM agent).
*/
class AgentSuccessJoinDomainResponse: public SuccessJoinDomainResponse {
public:
  /*! \brief  Constructor.

      \param  rhs                 successful join domain response.
  */
	AgentSuccessJoinDomainResponse(const NZSPtr<SuccessJoinDomainResponse>& rhs);

  /*! \brief  Check and update protocol.

      \param  tracker             input-output, protocol tracker.
      \param  verifier            input, certificate verifier.
      \param  device              input, device context.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolUpdate(const NZSPtr<AgentJoinDomProtocolTracker>& tracker,
    const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<AgentDeviceContext>& device) const;
};

/*! \brief  Leave domain request (OMA DRM agent).
*/
class AgentLeaveDomainRequest: public LeaveDomainRequest {
public:
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
	AgentLeaveDomainRequest(const SPtr<ROAPNonce>& tnonce, const NZSPtr<ROAPIdentifier>&
    devid, const NZSPtr<ROAPIdentifier>& riid, const NZSPtr<ROAPNonce>& dnonce,
    const NZSPtr<DateTime>& dtime, const NZSPtr<ROAPDomainIdentifier>& domid,
		const SPtr<ROAPCertificateChain>& cchain,	const SPtr<LeaveDomainReqExtensions>&
    exts, const Base64StringT& sig);

  /*! \brief  Protocol check.

      \param  response                input, leave domain response.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolCheck(const NZSPtr<SuccessLeaveDomainResponse>& response) const;
};

/*! \brief  Leave domain protocol context after sending leave domain request message.
*/
class LeaveDomainProtocolContext: public GC {
public:
  /*! \brief  Constructor.

      \param  regdbase                  registration database.
      \param  req                       leave domain request.
  */
  LeaveDomainProtocolContext(const NZSPtr<AgentRegDatabase>& regdbase,
    const NZSPtr<AgentLeaveDomainRequest>& req);

  /*! \brief  Registration database.
  */
  NZSPtr<AgentRegDatabase> regDB;

  /*! \brief  Leave domain request.
  */
  NZSPtr<AgentLeaveDomainRequest> request;
};

/*! \brief  Leave domain protocol tracker.

    Contains current running leave domain sessions, grouped by device nonces.
*/
class AgentLeaveDomProtocolTracker: public GC {
public:
  /*! \brief  Nonce to leave domain protocol context map.
  */
  std::map<NZSPtr<ROAPNonce>, SPtr<LeaveDomainProtocolContext> > nonceToCtx;
};

/*! \brief  Leave domain request message handler.

    Creates leave domain request message, creates leave domain protocol context,
    and puts it to protocol tracker.
*/
class AgentLeaveDomainReqHandler: public GC {
public:
  /*! \brief  Create leave domain request.

      \param  regDB               input, registration database.
      \param  tracker             input-output, protocol tracker.
      \param  timer               input, DRM timer.
      \param  noncer              input, nonce creator.

      \returns  Leave domain request message. If zero, failed.
  */
  virtual SPtr<LeaveDomainRequest> CreateRequest(const NZSPtr<AgentRegDatabase>&
    regDB, const NZSPtr<AgentLeaveDomProtocolTracker>& tracker, const
    NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>& noncer) const = 0;
};

/*! \brief  Triggered leave domain request message handler.
*/
class TriggerAgentLeaveDomainReqHandler: public AgentLeaveDomainReqHandler {
public:
  /*! \brief  Constructor.

      \param  trig              trigger.
  */
  TriggerAgentLeaveDomainReqHandler(const NZSPtr<LeaveDomainTrigger>& trig);

  /*! \brief  Create leave domain request.

      \param  regDB               input, registration database.
      \param  tracker             input-output, protocol tracker.
      \param  timer               input, DRM timer.
      \param  noncer              input, nonce creator.

      \returns  Leave domain request message. If zero, failed.
  */
  virtual SPtr<LeaveDomainRequest> CreateRequest(const NZSPtr<AgentRegDatabase>&
    regDB, const NZSPtr<AgentLeaveDomProtocolTracker>& tracker, const
    NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>& noncer) const;

private:
  NZSPtr<LeaveDomainTrigger> trigger;
};

/*! \brief  Non-triggered join domain request message handler.
*/
class NTriggerAgentLeaveDomainReqHandler: public AgentLeaveDomainReqHandler {
public:
  /*! \brief  Constructor.

      \param  riid                rights issuer identifier.
      \param  domid               domain identifier.
  */
  NTriggerAgentLeaveDomainReqHandler(const NZSPtr<ROAPIdentifier>& riid,
    const NZSPtr<ROAPDomainIdentifier>& domid);

  /*! \brief  Create leave domain request.

      \param  regDB               input, registration database.
      \param  tracker             input-output, protocol tracker.
      \param  timer               input, DRM timer.
      \param  noncer              input, nonce creator.

      \returns  Leave domain request message. If zero, failed.
  */
  virtual SPtr<LeaveDomainRequest> CreateRequest(const NZSPtr<AgentRegDatabase>&
    regDB, const NZSPtr<AgentLeaveDomProtocolTracker>& tracker, const
    NZSPtr<OMADRMDefTimer>& timer, const NZSPtr<OMADRMNonceCreator>& noncer) const;

private:
  NZSPtr<ROAPIdentifier> riID;
  NZSPtr<ROAPDomainIdentifier> domainID;
};

/*! \brief  Successful leave domain response (OMA DRM agent).
*/
class AgentSuccessLeaveDomainResponse: public SuccessLeaveDomainResponse {
public:
  /*! \brief  Constructor.

      \param  rhs                successful leave domain response.
  */
	AgentSuccessLeaveDomainResponse(const NZSPtr<SuccessLeaveDomainResponse>& rhs);

  /*! \brief  Check and update protocol.

      \param  tracker             input-output, protocol tracker.

      \returns  Boolean indicating success or failure.
  */
  bool ProtocolUpdate(const NZSPtr<AgentLeaveDomProtocolTracker>& tracker) const;
};

} // namespace DRMPlugin

#endif // !defined (AGENTROAP_H)
