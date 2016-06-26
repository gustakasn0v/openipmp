/**
    \defgroup omadrmdecagent OMA DRM decoding agent documentation.
*/
/** \file OMADRMDecAgent.h

    Agent handling OMA DRM device messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMDECAGENT_H)
#define OMADRMDECAGENT_H

#include "IOMADRMDecAgent.h"
#include "IOMADRMDecCommHandler.h"
#include "AgentROAP.h"
#include <string>
#include "DRMLogger.h"

#include "IThreadSync.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Agent handling OMA DRM device messages.

    \ingroup omadrmdecagent
*/
class OMADRMDecAgent: public IOMADRMDecAgent  {
public:
  /*! \brief  Constructor.

      \param  noncecreator      nonce creator.
      \param  drmtimer          DRM timer.
      \param  hashcalc          hash calculator.
      \param  certverifier      certificate verifier.
      \param  drmdefTimer       DRM (definite time) timer.
      \param  logger            message logger.

      If fails, throws DRMDecManagerException.
  */
  OMADRMDecAgent(const NZSPtr<OMADRMNonceCreator>& noncecreator,
    const NZSPtr<OMADRMTimer>& drmtimer, const NZSPtr<OMADRMHasher>& hashcalc,
    const NZSPtr<OMACertificateVerifier>& certverifier,
    const NZSPtr<OMADRMDefTimer>& drmdefTimer, DRMLogger& logger);

  virtual ~OMADRMDecAgent();

  /*! \brief  Handle successful rights issuer hello message.

      \param  response            input, successful rights issuer hello message.

      \returns  Registration request. If zero, failed.
  */
  virtual SPtr<RegRequest> HandleSuccessRIHello(const NZSPtr<SuccessRIHello>& response);

  /*! \brief  Handle unsuccessful rights issuer hello message.

      \param  response            input, unsuccessful rights issuer hello message.
  */
  virtual void HandleUnsuccessRIHello(const NZSPtr<UnsuccessRIHello>& response);

  /*! \brief  Handle successful registration response message.

      \param  response            input, successful registration response message.
  */
  virtual void HandleSuccessRegResponse(const NZSPtr<SuccessRegResponse>& response);

  /*! \brief  Handle unsuccessful registration response message.

      \param  response            input, unsuccessful registration response message.
  */
  virtual void HandleUnsuccessRegResponse(const NZSPtr<UnsuccessRegResponse>& response);

  /*! \brief  Handle successful 2-pass rights objects response message.

      \param  response            input, successful 2-pass rights objects response
                                  message.
  */
  virtual void HandleSuccessROResponse(const NZSPtr<SuccessTwoPassROResponse>& response);

  /*! \brief  Handle unsuccessful 2-pass rights objects response message.

      \param  response            input, unsuccessful 2-pass rights objects response
                                  message.
  */
  virtual void HandleUnsuccessROResponse(const NZSPtr<UnsuccessTwoPassROResponse>& response);

  /*! \brief  Handle 1-pass rights objects response message.

      \param  response          input, 1-pass rights objects response message.
  */
  virtual void HandleROResponse(const NZSPtr<OnePassROResponse>& response);

  /*! \brief  Handle successful join domain response message.

      \param  response          input, successful join domain response message.
  */
  virtual void HandleSuccessJoinResponse(const NZSPtr<SuccessJoinDomainResponse>& response);

  /*! \brief  Handle unsuccessful join domain response message.

      \param  response          input, unsuccessful join domain response message.
  */
  virtual void HandleUnsuccessJoinResponse(const NZSPtr<UnsuccessJoinDomainResponse>& response);

  /*! \brief  Handle successful leave domain response message.

      \param  response          input, successful leave domain response message.
  */
  virtual void HandleSuccessLeaveResponse(const NZSPtr<SuccessLeaveDomainResponse>& response);

  /*! \brief  Handle unsuccessful leave domain response message.

      \param  response          input, unsuccessful leave domain response message.
  */
  virtual void HandleUnsuccessLeaveResponse(const NZSPtr<UnsuccessLeaveDomainResponse>& response);

  /*! \brief  Handle registration trigger.

      \param  trigger           input, registration trigger.

      \returns  Device hello message. If zero, failed.
  */
  virtual SPtr<DeviceHelloRequest> HandleRegTrigger(const NZSPtr<RegRequestTrigger>& trigger);

  /*! \brief  Handle domain rights objects acuisition trigger.

      \param  trigger           input, domain rights objects acuisition trigger.

      \returns  Rights objects acquisition message. If zero, failed.
  */
  virtual SPtr<RORequest> HandleDomainROTrigger(const NZSPtr<DomainROTrigger>& trigger);

  /*! \brief  Handle non-domain rights objects acuisition trigger.

      \param  trigger           input, non-domain rights objects acuisition trigger.

      \returns  Rights objects acquisition message. If zero, failed.
  */
  virtual SPtr<RORequest> HandleNDomainROTrigger(const NZSPtr<NDomainROTrigger>& trigger);

  /*! \brief  Handle join domain trigger.

      \param  trigger           input, join domain trigger.

      \returns  Join domain request message. If zero, failed.
  */
  virtual SPtr<JoinDomainRequest> HandleJoinTrigger(const NZSPtr<JoinDomainTrigger>& trigger);

  /*! \brief  Handle leave domain trigger.

      \param  trigger           input, leave domain trigger.

      \returns  Leave domain request message. If zero, failed.
  */
  virtual SPtr<LeaveDomainRequest> HandleLeaveTrigger(const NZSPtr<LeaveDomainTrigger>& trigger);

  /*! \brief  Get device context.

      \returns  Device context.
  */
  virtual const NZSPtr<AgentDeviceContext>& GetDeviceCtx() = 0;

  /*! \brief  Get registration database.

      \returns  Registration database.
  */
  virtual NZSPtr<AgentRegDatabase> GetRegDB() = 0;

  /*! \brief  Get rights objects database.

      \returns  Rights objects database.
  */
  virtual NZSPtr<AgentRODatabase> GetRODB() = 0;

  /*! \brief  Get content encryption key corresponding to content identifier.

      \param  comm                input, communication handler.
      \param  contentID           input, content identifier.
      \param  url                 input, rights issuer's URL (from DCF).
      \param  key                 output, content encryption key.
      \param  keySize             output, content encryption key size.

      \returns  Boolean indicating success or failure.
  */
  bool GetKey(IOMADRMDecCommHandler* comm, const std::string& contentID,
    const NZSPtr<URIValue>& url, ByteT** key, UInt32T* keySize);

protected:
  /*! \brief  Create device hello message and update protocol tracker.

      Assumes that agent's mutex is obtained in the calling routine.

      \param  tNonce          input, trigger nonce (can be 0).
      \param  url             input, rights issuer URL.

      \returns  Device hello message. If zero, failed.
  */
  SPtr<DeviceHelloRequest> CreateDeviceHello(const SPtr<ROAPNonce>& tNonce,
    const NZSPtr<URIValue>& url);

  IMutex* mutex;
  NZSPtr<AgentRegProtocolTracker> agentRegTracker;
  NZSPtr<AgentJoinDomProtocolTracker> agentJoinTracker;
  NZSPtr<AgentLeaveDomProtocolTracker> agentLeaveTracker;
  NZSPtr<AgentROReqProtocolTracker> agentROTracker;
  NZSPtr<OMADRMNonceCreator> noncer;
  NZSPtr<OMADRMTimer> timer;
  NZSPtr<OMADRMHasher> hasher;
  NZSPtr<OMACertificateVerifier> verifier;
  NZSPtr<OMADRMDefTimer> defTimer;

  bool exitFlag;

  //  Map from content identifier to waiting events (for content encryption
  //  keys).
  std::map<Base64StringT, IEvent*> keyWaiters;
  std::map<Base64StringT, IEvent*> keyExiters;

  //  Map from rights issuers' URLs to registration waiting events.
  std::map<NZSPtr<URIValue>, IEvent*> regWaiters;
  std::map<NZSPtr<URIValue>, IEvent*> regExiters;

  //  Map from rights objects identifier to key waiting events.
  std::map<NZSPtr<IDValue>, std::vector<IEvent*> > roWaiters;

  //  Map counting references for registration events, per URL.
  std::map<NZSPtr<URIValue>, unsigned int> regRef;

  //  Map counting references for key waiting events, per content ID.
  std::map<std::string, unsigned int> keyRef;

  DRMLogger& agentLogger;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMDECAGENT_H)
