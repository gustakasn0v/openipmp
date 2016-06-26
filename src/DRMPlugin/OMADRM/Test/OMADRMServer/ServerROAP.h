/** \file ServerROAP.h

    Test server OMA DRM rights issuer messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (SERVERROAP_H)
#define SERVERROAP_H

#include "OMADRMCommon.h"
#include "ServerBase.h"

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
    const NZSPtr<ROAPCertificateChain>& chain);

/*! \brief  Extensions for rights issuer hello message (OMA DRM server).
*/
class ServerRIHelloExtensions: public RIHelloExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid                peer key identifier.
      \param  ccaching              certificate caching.
      \param  ddetails              device details.

      If fails, throws ROAPException.
  */
  ServerRIHelloExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
    SPtr<CertCachingExtension>& ccaching, const SPtr<DeviceDetailsExtension>&
    ddetails);

  /*! \brief  Protocol check.

      \param  request           input, registration request.

      \returns  Boolean indicating success or failure of check.
  */
  SPtr<RegResponse> ProtocolCheck(const NZSPtr<RegRequest>& request) const;
};

/*! \brief  Successful rights issuer hello message (OMA DRM server).
*/
class ServerSuccessRIHello: public SuccessRIHello {
public:
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
	ServerSuccessRIHello(const NZSPtr<ROAPVersion>& ver, const NZSPtr<ROAPIdentifier>&
    idval, const std::vector<NZSPtr<URIValue> >& algs, const NZSPtr<ROAPNonce>&
    nonceval, const SPtr<ROAPKeyIdentifiers>& trust, const SPtr<ROAPServerInfo>& inf,
    const SPtr<ServerRIHelloExtensions>& exts, const NZSPtr<ROAPSessionID>& sessid);

  /*! \brief  Protocol check.

      \param  request           input, registration request.

      \returns  Boolean indicating success or failure of check.
  */
  SPtr<RegResponse> ProtocolCheck(const NZSPtr<RegRequest>& request) const;

private:
	SPtr<ServerRIHelloExtensions> serverextensions;
};

/*! \brief  Registration protocol context

    Protocol context after receiving and checking device hello message and
    sending rights issuer hello message.
*/
class ServerRIHelloProtocolContext: public GC {
public:
  /*! \brief  Constructor.

      \param  devctx                device context.
      \param  regdb                 registration database.
      \param  dhello                device hello message.
      \param  rhello                rights issuer hello message.
  */
  ServerRIHelloProtocolContext(const NZSPtr<TempServerDeviceContext>& devctx,
    const NZSPtr<ServerRegDatabase>& regdb, const NZSPtr<DeviceHelloRequest>&
    dhello, const NZSPtr<ServerSuccessRIHello>& rhello);

  //! Temporary device context.
  NZSPtr<TempServerDeviceContext> deviceCtx;

  //! Registration database.
  NZSPtr<ServerRegDatabase> regDB;

  //! Device hello message.
  NZSPtr<DeviceHelloRequest> dHello;

  //! Rights issuer hello message.
  NZSPtr<ServerSuccessRIHello> rHello;
};

/*! \brief  Server protocol tracker.

    Contains current running protocol contexts.
*/
class ServerProtocolTracker: public GC {
public:
  //! Trigger nonce to registratio trigger map.
  std::map<NZSPtr<ROAPNonce>, SPtr<RegRequestTrigger> > nonceToRegTrigger;

  //! Trigger nonce to rights objects acquisition trigger map.
  std::map<NZSPtr<ROAPNonce>, SPtr<ROAcquisitionTrigger> > nonceToROTrigger;

  //! Trigger nonce to join domain trigger map.
  std::map<NZSPtr<ROAPNonce>, SPtr<JoinDomainTrigger> > nonceToJoinTrigger;

  //! Trigger nonce to leave domain trigger map.
  std::map<NZSPtr<ROAPNonce>, SPtr<LeaveDomainTrigger> > nonceToLeaveTrigger;

  //! Session identifier to protocol context map.
  std::map<NZSPtr<ROAPSessionID>, SPtr<ServerRIHelloProtocolContext> > idToRIHelloContext;
};

/*! \brief  Temporary registration response message.
*/
class TempRegResponse: public GC {
public:
  //! Certificate chain.
	SPtr<ROAPCertificateChain> chain;

  //! OCSP responses.
	std::vector<Base64StringT> ocsps;
};

/*! \brief  Extensions for registration request message (OMA DRM server).
*/
class ServerRegRequestExtensions: public RegRequestExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid                  peer key identifier.
      \param  ddetails                device details.
      \param  noocsp                  no OCSP response.
      \param  ocspkeyid               OCSP responder key identifier.

      If fails, throws ROAPException.
  */
  ServerRegRequestExtensions(const SPtr<PeerKeyIdExtension>& peerid,
    const SPtr<DeviceDetailsExtension>& ddetails,
    const SPtr<NoOCSPResponseExtension>& noocsp,
    const SPtr<OCSPResponderKeyIdExtension>& ocspkeyid);

  /*! \brief  Check and update protocol.

      \param  context             input, protocol context.
      \param  resp                input-output, temporary registration response.
      \param  rissuer             input, rights issuer context.

      \returns  Registration response message. If not zero, it means that check
                failed (then it is an unsuccess registration response).
  */
  SPtr<RegResponse> ProtocolUpdate(const NZSPtr<ServerRIHelloProtocolContext>& context,
    NZSPtr<TempRegResponse>& resp, const NZSPtr<ServerRIContext>& rissuer) const;
};

/*! \brief  Registration request message (OMA DRM server).
*/
class ServerRegRequest: public RegRequest {
public:
  /*! \brief  Constructor.

      \param  rhs               registration request.
  */
	ServerRegRequest(const NZSPtr<RegRequest>& rhs);

  /*! \brief  Check and update protocol.

      \param  tracker             input-output, protocol tracker.
      \param  verifier            input, certificate verifier.
      \param  rissuer             input, rights issuer context.

      \returns  Registration response.
  */
  NZSPtr<RegResponse> ProtocolUpdate(const NZSPtr<ServerProtocolTracker>&
    tracker, const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<ServerRIContext>& rissuer) const;

private:
	SPtr<ServerRegRequestExtensions> serverextensions;
};

/*! \brief  Extensions for device hello message (OMA DRM server).
*/
class ServerDeviceHelloExtensions: public DeviceHelloExtensions {
public:
  /*! \brief  Constructor.

      \param  ccaching                  certificate caching.
  */
  ServerDeviceHelloExtensions(const NZSPtr<CertCachingExtension>& ccaching);

  /*! \brief  Check and update protocol.

      \param  context           input, temporary device context.

      \returns  Rights issuer hello response. If not zero, check failed,
                and response is unsuccessful rights issuer hello response.
  */
  SPtr<RIHelloResponse> ProtocolUpdate(const NZSPtr<TempServerDeviceContext>&
    context) const;
};

/*! \brief  Device hello message (OMA DRM server).
*/
class ServerDeviceHelloRequest: public DeviceHelloRequest {
public:
  /*! \brief  Constructor.

      \param  rhs             device hello request.
  */
	ServerDeviceHelloRequest(const NZSPtr<DeviceHelloRequest>& rhs);

  /*! \brief  Check and update protocol.

      \param  tracker               input-output, protocol tracker.
      \param  noncer                input, nonce creator.
      \param  sessioner             input, session identifier creator.
      \param  devURL                input, device URL.
      \param  regDB                 input, registration database.
      \param  rissuer               input, rights issuer context.

      \returns  Rights issuer hello response.
  */
  NZSPtr<RIHelloResponse> ProtocolUpdate(const NZSPtr<ServerProtocolTracker>&
    tracker, const NZSPtr<OMADRMNonceCreator>& noncer,  const
    NZSPtr<OMADRMSessionIDCreator>& sessioner, const NZSPtr<URIValue>& devURL,
    const NZSPtr<ServerRegDatabase>& regDB, const NZSPtr<ServerRIContext>& rissuer) const;

private:
	SPtr<ServerDeviceHelloExtensions> serverextensions;
};

/*! \brief  Temporary rights objects registration response.
*/
class TempROResponse: public GC {
public:
  //! Certificate chain.
	SPtr<ROAPCertificateChain> chain;

  //! OCSP responses.
	std::vector<Base64StringT> ocsps;
};

/*! \brief  Extensions for rights object request message (OMA DRM server).
*/
class ServerROReqExtensions: public RORequestExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid                peer key identifier.
      \param  noocsp                no OCSP response.
      \param  ocspresp              OCSP responder key identifier.
      \param  transid               transaction identifier.

      If fails, throws ROAPException.
  */
  ServerROReqExtensions(const SPtr<PeerKeyIdExtension>& peerid, const
    SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
    ocspresp, const SPtr<TransactionIdExtension>& transid);

  /*! \brief  Check and update protocol.

      \param  regDB             input, registration database.
      \param  roDB              input, right objects database.
      \param  response          input-output, temporary rights objects response.
      \param  rissuer           input, rights issuer context.

      \returns  2-pass rights objects response. If not zero, check failed,
                and response is an unsuccessful 2-pass rights objects response.
  */
  SPtr<TwoPassROResponse> ProtocolUpdate(const NZSPtr<ServerRegDatabase>&
    regDB, const NZSPtr<ServerRODatabase>& roDB, const NZSPtr<TempROResponse>&
    response, const NZSPtr<ServerRIContext>& rissuer) const;
};

/*! \brief  Rights object request (OMA DRM server).
*/
class ServerRORequest: public RORequest {
public:
  /*! \brief  Constructor.

      \param  rhs           rights objects request.
  */
	ServerRORequest(const NZSPtr<RORequest>& rhs);

  /*! \brief  Protocol check.

      \param  regDB               input, registration database.
      \param  roDB                input, rights objects database.
      \param  verifier            input, certificate verifier.
      \param  tracker             input-output, protocol tracker.
      \param  rissuer             input, rights issuer context.

      \returns  2-pass rights objects response.
  */
  NZSPtr<TwoPassROResponse> ProtocolUpdate(const NZSPtr<ServerRegDatabase>& regDB,
    const NZSPtr<ServerRODatabase>& roDB, const NZSPtr<OMACertificateVerifier>&
    verifier, const NZSPtr<ServerProtocolTracker>& tracker,
    const NZSPtr<ServerRIContext>& rissuer) const;

private:
	SPtr<ServerROReqExtensions> serverextensions;
};

/*! \brief  Server's one pass rights objects response handler.

    If there are no errors, returns one pass rights objects response.
*/
class ServerOnePassROResponseHandler: public GC {
public:
  /*! \brief  Check and update protocol.

      \param  regDB             input, registration database.
      \param  roDB              input, rights objects database.
      \param  devID             input, device identifier.
      \param  roID              input, rights objects identifier.
      \param  rissuer           input, rights issuer context.

      \returns  1-pass rights objects response. If zero, failed.
  */
  SPtr<OnePassROResponse> ProtocolUpdate(const NZSPtr<ServerRegDatabase>& regDB,
    const NZSPtr<ServerRODatabase>& roDB, const NZSPtr<ROAPIdentifier>& devID,
    const std::vector<NZSPtr<IDValue> >& roID, const NZSPtr<ServerRIContext>& rissuer) const;
};

/*! \brief  Temporary join domain response.
*/
class TempJoinDomainResponse: public GC {
public:
  //! Certificate chain
	SPtr<ROAPCertificateChain> chain;

  //! OCSP responses.
  std::vector<Base64StringT> ocsps;
};

/*! \brief  Extensions for join domain request message (OMA DRM server).
*/
class ServerJoinDomainReqExt: public JoinDomainReqExtensions {
public:
  /*! \brief  Constructor.

      \param  peerid              peer key identifier.
      \param  noocsp              no OCSP response.
      \param  ocspresp            OCSP responder key identifier.
      \param  hchain              hash chain support.

      If fails, throws ROAPException.
  */
  ServerJoinDomainReqExt(const SPtr<PeerKeyIdExtension>& peerid, const
    SPtr<NoOCSPResponseExtension>& noocsp, const SPtr<OCSPResponderKeyIdExtension>&
    ocspresp, const SPtr<HashChainSupportExtension>& hchain);

  /*! \brief  Check and update protocol.

      \param  regDB             input, registration database.
      \param  response          input-output, temporary join domain response.
      \param  rissuer           input, rights issuer context.

      \returns  Join domain response. If not zero, check failed, and response
                is an unsuccessful join domain response.
  */
  SPtr<JoinDomainResponse> ProtocolUpdate(const NZSPtr<ServerRegDatabase>& regDB,
    const NZSPtr<TempJoinDomainResponse>& response, const NZSPtr<ServerRIContext>&
    rissuer) const;
};

/*! \brief  Join domain request (OMA DRM server).
*/
class ServerJoinDomainRequest: public JoinDomainRequest {
public:
  /*! \brief  Constructor.

      \param  rhs                 join domain request.
  */
	ServerJoinDomainRequest(const NZSPtr<JoinDomainRequest>& rhs);

  /*! \brief  Check and update protocol

      \param  regDB             input, registration database.
      \param  verifier          input, certificate verifier.
      \param  tracker           input-output, protocol tracker.
      \param  rissuer           input, rights issuer context.

      \returns  Join domain response.
  */
  NZSPtr<JoinDomainResponse> ProtocolUpdate(const NZSPtr<ServerRegDatabase>& regDB,
    const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<ServerProtocolTracker>& tracker,
    const NZSPtr<ServerRIContext>& rissuer) const;

protected:
	SPtr<ServerJoinDomainReqExt> serverextensions;
};

/*! \brief  Temporary leave domain response.
*/
class TempLeaveDomainResponse: public GC {
};

/*! \brief  Leave domain request (OMA DRM server).
*/
class ServerLeaveDomainRequest: public LeaveDomainRequest {
public:
  /*! \brief  Constructor.

      \param  rhs                 leave domain request.
  */
	ServerLeaveDomainRequest(const NZSPtr<LeaveDomainRequest>& rhs);

  /*! \brief  Check and update protocol.

      \param  regDB           input, registration database.
      \param  verifier        input, certificate verifier.
      \param  tracker         input-output, protocol tracker.
      \param  rissuer         input, rights issuer context.

      \returns  Leave domain response.
  */
  NZSPtr<LeaveDomainResponse> ProtocolUpdate(const NZSPtr<ServerRegDatabase>& regDB,
    const NZSPtr<OMACertificateVerifier>& verifier,
    const NZSPtr<ServerProtocolTracker>& tracker,
    const NZSPtr<ServerRIContext>& rissuer) const;
};

/*! \brief  Initial content rights objects request message (server side).

    This is not OMA DRM message, and it is used to initiate content rights
    objects acquisition protocol. Response to this message must be a trigger,
    either a registration trigger, if device is not yet registered, or a rights
    objects acquisition trigger, if device is registered and corresponding
    rights objects exist. For the test case, we assume that the device is not
    registered, thus initial rights objects request returns a registration
    trigger.
*/
class ServerInitialRORequest: public InitialRORequest {
public:
  /*! \brief  Constructor.

      Size of content identifiers vector must be >= 1.

      \param  rhs               initial rights objects request.

      If fails, throws ROAPException.
  */
  ServerInitialRORequest(const NZSPtr<InitialRORequest>& rhs);

  /*! \brief  Constructor.

      Size of content identifiers vector must be >= 1.

      \param  devid               device identifier.
      \param  idvals              content identifiers vector.

      If fails, throws ROAPException.
  */
  ServerInitialRORequest(const NZSPtr<ROAPIdentifier>& devid,
    const std::vector<NZSPtr<URIValue> >& idvals);

  /*! \brief  Create a rights objects acquisition trigger as a response to
              initial rights objects request.

      \param  regDB               input, registration database.
      \param  roDB                input, rights database.
      \param  noncer              input, nonce creator.
      \param  tracker             input-output, protocol tracker.
      \param  rissuer             input, rights issuer context.

      \returns  Rights objects acquisition trigger. If zero, failed.
  */
  SPtr<ROAcquisitionTrigger> ProtocolUpdate(const NZSPtr<ServerRegDatabase>& regDB,
    const NZSPtr<ServerRODatabase>& roDB, const NZSPtr<OMADRMNonceCreator>& noncer,
    const NZSPtr<ServerProtocolTracker>& tracker, const NZSPtr<ServerRIContext>& rissuer);
};

} // namespace DRMPlugin

#endif // !defined(SERVERROAP_H)
