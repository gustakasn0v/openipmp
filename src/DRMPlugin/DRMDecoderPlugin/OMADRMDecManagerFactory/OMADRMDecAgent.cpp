/** \file OMADRMDecAgent.cpp

    Agent handling OMA DRM device messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMDecAgent.h"
#include "DRMDecManagerException.h"
#include "ThreadSyncFactory.h"

#include <map>
#include <string>
#include <iostream>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    \param  noncecreator      nonce creator.
    \param  drmtimer          DRM timer.
    \param  hashcalc          hash calculator.
    \param  certverifier      certificate verifier.
    \param  drmdefTimer       DRM (definite time) timer.
    \param  logger            message logger.

    If fails, throws DRMDecManagerException.
*/
OMADRMDecAgent::OMADRMDecAgent(const NZSPtr<OMADRMNonceCreator>& noncecreator,
  const NZSPtr<OMADRMTimer>& drmtimer, const NZSPtr<OMADRMHasher>& hashcalc,
  const NZSPtr<OMACertificateVerifier>& certverifier, const NZSPtr<OMADRMDefTimer>&
  drmdefTimer, DRMLogger& logger): mutex(ThreadSyncFactory::GetMutex(logger)),
  agentRegTracker(new AgentRegProtocolTracker()),
  agentJoinTracker(new AgentJoinDomProtocolTracker()),
  agentLeaveTracker(new AgentLeaveDomProtocolTracker()),
  agentROTracker(new AgentROReqProtocolTracker()),
  noncer(noncecreator), timer(drmtimer), hasher(hashcalc), verifier(certverifier),
  defTimer(drmdefTimer), keyWaiters(), regWaiters(), roWaiters(),
  exitFlag(false), keyExiters(), regExiters(), regRef(), keyRef(), agentLogger(logger) {

  if (mutex == 0) {
    agentLogger.UpdateLog("OMADRMDecAgent::ctor: zero mutex...");
    throw DRMDecManagerException();
  }
}

OMADRMDecAgent::~OMADRMDecAgent() {
  mutex->Lock();
  //  Here we depend on the fact that all communication handlers pointing
  //  on this agent are destroyed, and cannot call this agent's handle routines.
  std::vector<IEvent*> exiters;
  std::map<Base64StringT, IEvent*>::iterator iterk = keyWaiters.begin();
  while (iterk != keyWaiters.end()) {
    exiters.push_back(iterk->second);
    iterk++;
  }
  std::map<NZSPtr<URIValue>, IEvent*>::iterator iterr = regWaiters.begin();
  while (iterr != regWaiters.end()) {
    exiters.push_back(iterr->second);
    iterk++;
  }
  exitFlag = true;
  mutex->Release();
  WaitForEvents(exiters);
  //  This should happen immediately.
  mutex->Lock();
  for (unsigned int i = 0; i < exiters.size(); i++) {
    if (exiters[i] != 0) delete exiters[i];
  }
  mutex->Release();
  delete mutex;
}

/*! \brief  Create device hello message and update protocol tracker.

    Assumes that agent's mutex is obtained in the calling routine.

    \param  tNonce          input, trigger nonce (can be 0).
    \param  url             input, rights issuer URL.

    \returns  Device hello message. If zero, failed.
*/
SPtr<DeviceHelloRequest> OMADRMDecAgent::CreateDeviceHello(const SPtr<ROAPNonce>& tNonce,
    const NZSPtr<URIValue>& url) {
  NZSPtr<AgentDeviceHelloExtensions> ext = new AgentDeviceHelloExtensions(
    GetDeviceCtx()->GetCertCaching());
  NZSPtr<AgentDeviceHelloRequest> deviceHello = new AgentDeviceHelloRequest(
    tNonce, GetDeviceCtx()->GetVersion(), std::vector<NZSPtr<ROAPIdentifier> >(1,
    GetDeviceCtx()->GetID()), GetDeviceCtx()->GetAlgorithms(), ext);
  NZSPtr<DeviceHelloProtocolContext> protCtx =
    new DeviceHelloProtocolContext(GetRegDB(), new TempAgentRIContext(0, 0, 0,
    url, 0, 0, std::vector<NZSPtr<URIValue> >(), 0, std::vector<Base64StringT>(),
    0, 0), deviceHello);
  agentRegTracker->deviceHelloContext = protCtx;
  return (AgentDeviceHelloRequest*)deviceHello;
}

/*! \brief  Get content encryption key corresponding to content identifier.

    \param  comm                input, communication handler.
    \param  contentID           input, content identifier.
    \param  url                 input, rights issuer's URL (from DCF).
    \param  key                 output, content encryption key.
    \param  keySize             output, content encryption key size.

    \returns  Boolean indicating success or failure.
*/
bool OMADRMDecAgent::GetKey(IOMADRMDecCommHandler* comm, const std::string& contentID,
    const NZSPtr<URIValue>& url, ByteT** key, UInt32T* keySize) {

  agentLogger.UpdateLog("OMADRMDecAgent::GetKey:...");

  if (mutex->Lock() == false) {
    agentLogger.UpdateLog("OMADRMDecAgent::GetKey: cannot lock mutex...");
    return false;
  }
  if (exitFlag == true) {
    agentLogger.UpdateLog("OMADRMDecAgent::GetKey: exitting...");
    mutex->Release();
    return false;
  }
  *key = 0;
  ByteSeq encKey;

  //  Check if we're registered with rights issuer.
  SPtr<AgentRIContext> riCtx = GetRegDB()->GetRIContext(url);
  if (riCtx != 0) {
    //  Check if context has expired.
    if (riCtx->GetPublicCert()->GetExpirationTime() >=
        (const TValue<UTCTime>&)(FiniteTValue<UTCTime>(defTimer->GetTime()->GetTime()))) {
      SPtr<ROAPProtectedRO> ro = GetRODB()->GetRO(new URIValue(contentID), riCtx);
      if (ro != 0) {
        Base64StringT enc = ((CValueXencCipherData*)(XencCipherData*)(
          ro->GetROPayload()->GetEncKey()->GetCipherData()))->Get();
        if (GetDeviceCtx()->GetPrivateKey()->Decrypt(enc, encKey) == true) {
          NZSPtr<DefDateTime> dtime(defTimer->GetTime());
          NZSPtr<ODDStart> start(new ODDStart(dtime->GetTime()));
          NZSPtr<ODDEnd> end(new ODDEnd(dtime->GetTime()));
          NZSPtr<ODDPlayPermission> permission =
            new ODDPlayPermission(new PlayOEXConstraint(0, 0,
            new StartEndODDDatetimeConstraint(start, end), 0, 0, 0,
            std::vector<NZSPtr<OMADDSystemConstraint> >()));
//          NZSPtr<ODDDisplayPermission> permission =
//            new ODDDisplayPermission(new DisplayOEXConstraint(0, 0,
//            new StartEndODDDatetimeConstraint(start, end), 0, 0, 0,
//            std::vector<NZSPtr<OMADDSystemConstraint> >()));
//          NZSPtr<ODDExecutePermission> permission = new ODDExecutePermission(
//            new ExecuteOEXConstraint(0, 0, new StartEndODDDatetimeConstraint(start, end),
//            0, 0, 0));
//          NZSPtr<ODDPrintPermission> permission = new ODDPrintPermission(
//            new PrintOEXConstraint(0, new StartEndODDDatetimeConstraint(start, end),
//            0, 0, 0));
//          NZSPtr<OMADDExportPermission> permission = new MoveOMADDExportPermission(
//            new MoveExportOEXConstraint(new StartEndODDDatetimeConstraint(start, end),
//            std::vector<NZSPtr<OMADDSystemConstraint> >(1,
//            new OMADDSystemConstraint(new SystemOEXContext(
//            0, std::vector<NZSPtr<SystemODDUID> >())))));

          if (ro->GetROPayload()->GetRights()->GetAgreement()->Allow(permission) == true) {
            *key = (ByteT*)malloc(encKey.GetLength());
            if (*key == 0) {
              //  Internal error.
              agentLogger.UpdateLog("OMADRMDecAgent::GetKey: memory allocation error...");
              mutex->Release();
              return false;
            }
            memcpy(*key, encKey.GetFirst(), encKey.GetLength());
            *keySize = encKey.GetLength();
            if (mutex->Release() == false) {
              agentLogger.UpdateLog("OMADRMDecAgent::GetKey: cannot release mutex...");
              free(*key); *key = 0; *keySize = 0;
              return false;
            }
            agentLogger.UpdateLog("OMADRMDecAgent::GetKey: ok...");
            return true;
          }
        }
      }
    } else {
      //  Context has expired, we have to re-register.
      riCtx = 0;
    }
  }

  bool err = false;

  //  Check if we're registered with rights issuer.
  if (riCtx == 0) {
    //  We're not registered. Set up registration wait event, if not already
    //  set (perhaps from another thread) and enter waiting loop.
    if (regWaiters.find(url) == regWaiters.end()) {
      IEvent* regwaiter = ThreadSyncFactory::GetEvent(agentLogger);
      if (regwaiter == 0) {
        agentLogger.UpdateLog("OMADRMDecAgent::GetKey: cannot create registration waiting event...");
        mutex->Release();
        return false;
      }
      IEvent* regexiter = ThreadSyncFactory::GetEvent(agentLogger);
      if (regexiter == 0) {
        agentLogger.UpdateLog("OMADRMDecAgent::GetKey: cannot create registration exitting event...");
        delete regwaiter;
        mutex->Release();
        return false;
      }
      regWaiters[url] = regwaiter;
      regExiters[url] = regexiter;
      regRef[url] = 1;
      //  Send device hello message.
      SPtr<DeviceHelloRequest> agentDevHello = CreateDeviceHello(0, url);
      mutex->Release();
      if (agentDevHello == 0) {
        agentLogger.UpdateLog("OMADRMDecAgent::GetKey: cannot create device hello...");
        return false;
      }
      comm->SendDeviceHello((NZSPtr<DeviceHelloRequest>)agentDevHello, url);
    } else {
      regRef[url]++;
      mutex->Release();
    }
    err = (!(regWaiters[url]->Wait(EVENT_WAIT_TIME)));
    if (err == true) {
      agentLogger.UpdateLog("OMADRMDecAgent::GetKey: registration event wait timeout...");
    }
    mutex->Lock();
    if (--regRef[url] == 0) {
      //  This is the last thread referencing this URL for registration.
      //  Clean up waiting event. If we're being destroyed, set the exit
      //  event. If not, clean up the exit event, too.
      regRef.erase(url);
      delete regWaiters[url];
      regWaiters.erase(url);
      if (exitFlag == true) {
        regExiters[url]->Set();
        mutex->Release();
        return false;
      } else {
        delete regExiters[url];
        regExiters.erase(url);
      }
    }
    if ((exitFlag == true) || (err == true)) {
      agentLogger.UpdateLog("OMADRMDecAgent::GetKey: registration failed...");
      mutex->Release();
      return false;
    }
  }

  agentLogger.UpdateLog("OMADRMDecAgent::GetKey: registered...");

  //  Now we know we're registered.
  //  Check if key waiting event for this contentID is already set. This is a
  //  hedge for the case of multiple parallel calls to get the key for the same
  //  contentID.
  if (keyWaiters.find(contentID) == keyWaiters.end()) {
    //  Set up key waiting event.
    IEvent* keywaiter = ThreadSyncFactory::GetEvent(agentLogger);
    if (keywaiter == 0) {
      agentLogger.UpdateLog("OMADRMDecAgent::GetKey: cannot create key waiting event...");
      mutex->Release();
      return false;
    }
    IEvent* keyexiter = ThreadSyncFactory::GetEvent(agentLogger);
    if (keyexiter == 0) {
      agentLogger.UpdateLog("OMADRMDecAgent::GetKey: cannot create key exitting event...");
      delete keywaiter;
      mutex->Release();
      return false;
    }
    keyWaiters[contentID] = keywaiter;
    keyExiters[contentID] = keyexiter;
    keyRef[contentID] = 1;
    mutex->Release();
    //  Send initial rights objects request.
    comm->SendInitialRORequest(new InitialRORequest(GetDeviceCtx()->GetID(),
      std::vector<NZSPtr<URIValue> >(1, new URIValue(contentID))), url);
  } else {
    keyRef[contentID]++;
    mutex->Release();
  }

  err = (!(keyWaiters[contentID]->Wait(EVENT_WAIT_TIME)));
  if (err == true) {
    agentLogger.UpdateLog("OMADRMDecAgent::GetKey: key event wait timeout...");
  }
  mutex->Lock();
  if (--keyRef[contentID] == 0) {
    //  This is the last thread referencing key for this content ID.
    //  Clean up waiting event. If we're being destroyed, set the exit
    //  event. If not, clean up the exit event, too.
    keyRef.erase(contentID);
    delete keyWaiters[contentID];
    keyWaiters.erase(contentID);
    if (exitFlag == true) {
      keyExiters[contentID]->Set();
      mutex->Release();
      return false;
    } else {
      delete keyExiters[contentID];
      keyExiters.erase(contentID);
    }
  }
  if ((exitFlag == true) || (err == true)) {
    agentLogger.UpdateLog("OMADRMDecAgent::GetKey: failed...");
    mutex->Release();
    return false;
  }

  riCtx = GetRegDB()->GetRIContext(url);
  SPtr<ROAPProtectedRO> ro = GetRODB()->GetRO(new URIValue(contentID), riCtx);
  if (ro != 0) {
    Base64StringT enc = ((CValueXencCipherData*)(XencCipherData*)(
      ro->GetROPayload()->GetEncKey()->GetCipherData()))->Get();
    if (GetDeviceCtx()->GetPrivateKey()->Decrypt(enc, encKey) == true) {
      //  Check rights.
      NZSPtr<DefDateTime> dtime(defTimer->GetTime());
      NZSPtr<ODDStart> start(new ODDStart(dtime->GetTime()));
      NZSPtr<ODDEnd> end(new ODDEnd(dtime->GetTime()));
      NZSPtr<ODDPlayPermission> permission =
        new ODDPlayPermission(new PlayOEXConstraint(0, 0,
        new StartEndODDDatetimeConstraint(start, end), 0, 0, 0,
        std::vector<NZSPtr<OMADDSystemConstraint> >()));
//      NZSPtr<ODDDisplayPermission> permission =
//        new ODDDisplayPermission(new DisplayOEXConstraint(0, 0,
//        new StartEndODDDatetimeConstraint(start, end), 0, 0, 0,
//        std::vector<NZSPtr<OMADDSystemConstraint> >()));
//      NZSPtr<ODDExecutePermission> permission = new ODDExecutePermission(
//        new ExecuteOEXConstraint(0, 0, new StartEndODDDatetimeConstraint(start, end),
//        0, 0, 0));
//      NZSPtr<ODDPrintPermission> permission = new ODDPrintPermission(
//        new PrintOEXConstraint(0, new StartEndODDDatetimeConstraint(start, end),
//        0, 0, 0));
//      NZSPtr<OMADDExportPermission> permission = new MoveOMADDExportPermission(
//        new MoveExportOEXConstraint(new StartEndODDDatetimeConstraint(start, end),
//        std::vector<NZSPtr<OMADDSystemConstraint> >(1,
//        new OMADDSystemConstraint(new SystemOEXContext(
//        0, std::vector<NZSPtr<SystemODDUID> >())))));

      if (ro->GetROPayload()->GetRights()->GetAgreement()->Allow(permission) == true) {
        *key = (ByteT*)malloc(encKey.GetLength());
        if (*key != 0) {
          memcpy(*key, encKey.GetFirst(), encKey.GetLength());
          *keySize = encKey.GetLength();
        }
      } else {
        agentLogger.UpdateLog("OMADRMDecAgent::GetKey: permission failed...");
      }
    }
  }

  mutex->Release();

  if ((*key) != 0) {
    agentLogger.UpdateLog("OMADRMDecAgent::GetKey: ok...");
  } else {
    agentLogger.UpdateLog("OMADRMDecAgent::GetKey: failed...");
  }

  return ((*key) != 0);
}

/*! \brief  Handle successful rights issuer hello message.

    \param  response            input, successful rights issuer hello message.

    \returns  Registration request. If zero, failed.
*/
SPtr<RegRequest> OMADRMDecAgent::HandleSuccessRIHello(const NZSPtr<SuccessRIHello>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleSuccessRIHello...");
  NZSPtr<AgentSuccessRIHello> aresponse = new AgentSuccessRIHello(response);
  mutex->Lock();
  SPtr<RegRequest> agentRegRequest = aresponse->ProtocolUpdate(agentRegTracker,
    defTimer, noncer, GetDeviceCtx());
  mutex->Release();
  return agentRegRequest;
}

/*! \brief  Handle unsuccessful rights issuer hello message.

    \param  response            input, unsuccessful rights issuer hello message.
*/
void OMADRMDecAgent::HandleUnsuccessRIHello(const NZSPtr<UnsuccessRIHello>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleUnsuccessRIHello...");
  mutex->Lock();
  agentRegTracker->deviceHelloContext = 0;
  mutex->Release();
}

/*! \brief  Handle successful registration response message.

    \param  response            input, successful registration response message.
*/
void OMADRMDecAgent::HandleSuccessRegResponse(const NZSPtr<SuccessRegResponse>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleSuccessRegResponse...");
  NZSPtr<AgentSuccessRegResponse> aresponse = new AgentSuccessRegResponse(response);
  mutex->Lock();
  aresponse->ProtocolUpdate(agentRegTracker, verifier, GetDeviceCtx());
  //  Inform waiters that registration is done.
  if (regWaiters.find(response->GetRightsIssuerURL()) != regWaiters.end()) {
    regWaiters[response->GetRightsIssuerURL()]->Set();
  }
  mutex->Release();
}

/*! \brief  Handle unsuccessful registration response message.

    \param  response            input, unsuccessful registration response message.
*/
void OMADRMDecAgent::HandleUnsuccessRegResponse(const NZSPtr<UnsuccessRegResponse>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleUnsuccessRegResponse...");
  mutex->Lock();
  /*  \todo: What if session id is not set, then we have no way to remove aborted
      session from the tracker?
  */
  if (response->GetSessionID() != 0) {
    if (agentRegTracker->idToRIHelloContext.find((NZSPtr<ROAPSessionID>)(
        response->GetSessionID())) != agentRegTracker->idToRIHelloContext.end()) {
      agentRegTracker->idToRIHelloContext.erase(
        (NZSPtr<ROAPSessionID>)(response->GetSessionID()));
    }
  }
  mutex->Release();
}

/*! \brief  Handle successful 2-pass rights objects response message.

    \param  response            input, successful 2-pass rights objects response
                                message.
*/
void OMADRMDecAgent::HandleSuccessROResponse(const NZSPtr<SuccessTwoPassROResponse>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleSuccessROResponse...");
  NZSPtr<AgentSuccessTwoPassROResponse> aresponse = new AgentSuccessTwoPassROResponse(response);
  mutex->Lock();
  aresponse->ProtocolUpdate(agentROTracker, verifier, GetDeviceCtx());

  //  Inform all key waiters about new rights objects.
  const std::vector<NZSPtr<ROAPProtectedRO> >& ros = aresponse->GetProtectedROs();
  for (unsigned int i = 0; i < ros.size(); i++) {
    if (roWaiters.find(ros[i]->GetROPayload()->GetID()) != roWaiters.end()) {
      std::vector<IEvent*> waiters = roWaiters[ros[i]->GetROPayload()->GetID()];
      for (unsigned int j = 0; j < waiters.size(); j++) {
        waiters[j]->Set();
      }
      roWaiters.erase(ros[i]->GetROPayload()->GetID());
    }
  }

  mutex->Release();
}

/*! \brief  Handle unsuccessful 2-pass rights objects response message.

    \param  response            input, unsuccessful 2-pass rights objects response
                                message.
*/
void OMADRMDecAgent::HandleUnsuccessROResponse(const NZSPtr<UnsuccessTwoPassROResponse>&
  response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleUnsuccessROResponse...");
}

/*! \brief  Handle 1-pass rights objects response message.

    \param  response          input, 1-pass rights objects response message.
*/
void OMADRMDecAgent::HandleROResponse(const NZSPtr<OnePassROResponse>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleROResponse...");
}

/*! \brief  Handle successful join domain response message.

    \param  response          input, successful join domain response message.
*/
void OMADRMDecAgent::HandleSuccessJoinResponse(const NZSPtr<SuccessJoinDomainResponse>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleSuccessJoinResponse...");
  NZSPtr<AgentSuccessJoinDomainResponse> aresponse = new AgentSuccessJoinDomainResponse(response);
  mutex->Lock();
  aresponse->ProtocolUpdate(agentJoinTracker, verifier, GetDeviceCtx());
  mutex->Release();
}

/*! \brief  Handle unsuccessful join domain response message.

    \param  response          input, unsuccessful join domain response message.
*/
void OMADRMDecAgent::HandleUnsuccessJoinResponse(const NZSPtr<UnsuccessJoinDomainResponse>&
  response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleUnsuccessJoinResponse...");
}

/*! \brief  Handle successful leave domain response message.

    \param  response          input, successful leave domain response message.
*/
void OMADRMDecAgent::HandleSuccessLeaveResponse(const NZSPtr<SuccessLeaveDomainResponse>& response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleSuccessLeaveResponse...");
  NZSPtr<AgentSuccessLeaveDomainResponse> aresponse = new AgentSuccessLeaveDomainResponse(response);
  mutex->Lock();
  aresponse->ProtocolUpdate(agentLeaveTracker);
  mutex->Release();
}

/*! \brief  Handle unsuccessful leave domain response message.

    \param  response          input, unsuccessful leave domain response message.
*/
void OMADRMDecAgent::HandleUnsuccessLeaveResponse(const NZSPtr<UnsuccessLeaveDomainResponse>&
  response) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleUnsuccessLeaveResponse...");
}

/*! \brief  Handle registration trigger.

    \param  trigger           input, registration trigger.

    \returns  Device hello message. If zero, failed.
*/
SPtr<DeviceHelloRequest> OMADRMDecAgent::HandleRegTrigger(const NZSPtr<RegRequestTrigger>&
    trigger) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleRegTrigger...");
  mutex->Lock();
  SPtr<DeviceHelloRequest> dHello = CreateDeviceHello(trigger->GetData()->GetNonce(),
    trigger->GetData()->GetURL());
  mutex->Release();
  return dHello;
}

/*! \brief  Handle domain rights objects acuisition trigger.

    \param  trigger           input, domain rights objects acuisition trigger.

    \returns  Rights objects acquisition message. If zero, failed.
*/
SPtr<RORequest> OMADRMDecAgent::HandleDomainROTrigger(const NZSPtr<DomainROTrigger>& trigger) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleDomainROTrigger...");
  NZSPtr<AgentROReqHandler> agentROReqH = new AgentROReqHandler(new
    DomainROTriggerHandler(trigger));

  mutex->Lock();
  SPtr<RORequest> agentROReq = agentROReqH->CreateRORequest(GetRegDB(), GetRODB(),
    agentROTracker, defTimer, noncer, GetDeviceCtx());

  //  Set up all key waiting events to rights objects identifier dependency.
  const std::vector<NZSPtr<ROIDContentID> >& ids =
    trigger->GetTriggerData()->GetROIDContentIDs();
  for (unsigned int i = 0; i < ids.size(); i++) {
    std::vector<IEvent*> waiters;
    for (unsigned int j = 0; j < ids[i]->GetContentIDs().size(); j++) {
      if (keyWaiters.find(ids[i]->GetContentIDs()[j]->Get()) != keyWaiters.end()) {
        waiters.push_back(keyWaiters[ids[i]->GetContentIDs()[j]->Get()]);
      }
    }
    for (unsigned int k = 0; k < waiters.size(); k++) {
      roWaiters[ids[i]->GetROID()].push_back(waiters[k]);
    }
  }

  mutex->Release();
  return agentROReq;
}

/*! \brief  Handle non-domain rights objects acuisition trigger.

    \param  trigger           input, non-domain rights objects acuisition trigger.

    \returns  Rights objects acquisition message. If zero, failed.
*/
SPtr<RORequest> OMADRMDecAgent::HandleNDomainROTrigger(const NZSPtr<NDomainROTrigger>& trigger) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleNDomainROTrigger...");
  NZSPtr<AgentROReqHandler> agentROReqH = new AgentROReqHandler(new
    NDomainROTriggerHandler(trigger));

  mutex->Lock();
  SPtr<RORequest> agentROReq = agentROReqH->CreateRORequest(GetRegDB(), GetRODB(),
    agentROTracker, defTimer, noncer, GetDeviceCtx());

  //  Set up all key waiting events to rights objects identifier dependency.
  const std::vector<NZSPtr<ROIDContentID> >& ids =
    trigger->GetTriggerData()->GetROIDContentIDs();
  for (unsigned int i = 0; i < ids.size(); i++) {
    std::vector<IEvent*> waiters;
    for (unsigned int j = 0; j < ids[i]->GetContentIDs().size(); j++) {
      if (keyWaiters.find(ids[i]->GetContentIDs()[j]->Get()) != keyWaiters.end()) {
        waiters.push_back(keyWaiters[ids[i]->GetContentIDs()[j]->Get()]);
      }
    }
    for (unsigned int k = 0; k < waiters.size(); k++) {
      roWaiters[ids[i]->GetROID()].push_back(waiters[k]);
    }
  }

  mutex->Release();
  return agentROReq;
}

/*! \brief  Handle join domain trigger.

    \param  trigger           input, join domain trigger.

    \returns  Join domain request message. If zero, failed.
*/
SPtr<JoinDomainRequest> OMADRMDecAgent::HandleJoinTrigger(const NZSPtr<JoinDomainTrigger>&
    trigger) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleJoinTrigger...");
  mutex->Lock();
  SPtr<AgentRIContext> riCtx;
  if ((riCtx = GetRegDB()->GetRIContext(trigger->GetTriggerData()->GetRightsIssuerID())) == 0) {
    mutex->Release();
    return 0;
  }
  SPtr<PeerKeyIdExtension> peerKeyId = riCtx->CreatePeerKeyId(true);
  SPtr<NoOCSPResponseExtension> noOCSP;
  if (GetRegDB()->GetRIContext(trigger->GetTriggerData()->GetRightsIssuerID())->GetOCSPResponses().empty() == true) {
    noOCSP = new CriticalNoOCSPResponseExtension();
  }
  //  \todo: OCSPResponderKeyIdentifier extension.
  SPtr<OCSPResponderKeyIdExtension> ocspResp;
  //  \todo: HashChainSupport extension.
  SPtr<HashChainSupportExtension> hashChain;
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  NZSPtr<DateTime> time = (DateTime*)(defTimer->GetTime());
  NZSPtr<AgentJoinDomainRequest> tempReq = new AgentJoinDomainRequest(
    trigger->GetTriggerData()->GetNonce(), GetDeviceCtx()->GetID(),
    trigger->GetTriggerData()->GetRightsIssuerID(), nonce, time,
    trigger->GetTriggerData()->GetDomainID(), riCtx->GetDeviceCertChain(),
    new AgentJoinDomainReqExt(peerKeyId, noOCSP, ocspResp, hashChain), "");
  Base64StringT signature;
  if (GetDeviceCtx()->GetPrivateKey()->Sign(tempReq->XmlEncodeWithoutSignature(),
      signature) == false) {
    mutex->Release();
    return 0;
  }
  NZSPtr<AgentJoinDomainRequest> joinReq = new AgentJoinDomainRequest(
    trigger->GetTriggerData()->GetNonce(), GetDeviceCtx()->GetID(),
    trigger->GetTriggerData()->GetRightsIssuerID(), nonce, time,
    trigger->GetTriggerData()->GetDomainID(), riCtx->GetDeviceCertChain(),
    new AgentJoinDomainReqExt(peerKeyId, noOCSP, ocspResp, hashChain),
    signature);
  NZSPtr<JoinDomainProtocolContext> protCtx = new JoinDomainProtocolContext(
    GetRegDB(), joinReq);
  agentJoinTracker->nonceToCtx[nonce] = protCtx;

  mutex->Release();
  return (AgentJoinDomainRequest*)joinReq;
}

/*! \brief  Handle leave domain trigger.

    \param  trigger           input, leave domain trigger.

    \returns  Leave domain request message. If zero, failed.
*/
SPtr<LeaveDomainRequest> OMADRMDecAgent::HandleLeaveTrigger(const NZSPtr<LeaveDomainTrigger>&
    trigger) {
  agentLogger.UpdateLog("OMADRMDecAgent::HandleLeaveTrigger...");
  NZSPtr<TriggerAgentLeaveDomainReqHandler> handler =
    new TriggerAgentLeaveDomainReqHandler(trigger);
  SPtr<LeaveDomainRequest> request;
  mutex->Lock();
  request = handler->CreateRequest(GetRegDB(), agentLeaveTracker, defTimer, noncer);
  mutex->Release();
  return request;
}

} // namespace DRMPlugin
