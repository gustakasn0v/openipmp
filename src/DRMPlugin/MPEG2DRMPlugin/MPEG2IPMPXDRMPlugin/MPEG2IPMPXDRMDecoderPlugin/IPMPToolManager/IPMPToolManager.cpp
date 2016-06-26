/**	\file IPMPToolManager.cpp

	IPMP tool manager.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "IPMPToolManager.h"

#include "BasicTypes.h"
#include "IIPMPControlInfoPart.h"
#include "IPMPData.h"
#include "IPMPMessage.h"
#include "IPMPAgent.h"
#include "MessageRouter.h"
#include "IPMPDataParser.h"
#include "IPMPControlInfoParser.h"
#include "DecoderIPMPUserQuery.h"
#include "ThreadSyncFactory.h"
#include <algorithm>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP tool context.

    Temporary tool context, before authentication is done.
*/
/*! \brief  Get tool identifier.

    \returns  Tool identifier.
*/
const Bit128T& IPMPToolContext::GetToolIdentifier() const {
  return toolID;
}

/*! \brief  Get instance identifier.

    \returns  Instance identifier.
*/
const Bit32T& IPMPToolContext::GetInstanceIdentifier() const {
  return instanceID;
}

/*! \brief  Get control point.

    \returns  Control point.
*/
const ByteT& IPMPToolContext::GetControlPoint() const {
  return control;
}

/*! \brief  Get sequence code.

    \returns  Sequence code.
*/
const ByteT& IPMPToolContext::GetSequenceCode() const {
  return sequence;
}

/*! \brief  Ready IPMP tool context.

    After a tool is instantiated, this context is used for further
    communication with a tool.
*/
/*! \brief  Get symmetric operator.

    \returns  Symmetric operator.
*/
SymmetricOperator* ReadyIPMPToolContext::GetOperator() const {
  return oper;
}

/*! \brief  Greater than operator on ready IPMP tool contexts (sequence codes).

    Used to sort contexts contained in a vector of ready contexts.

    \returns  Boolean indicating if lhs is greater than rhs, depending on
              the relation between the sequence codes.
*/
bool GreaterSeqCode(const ReadyIPMPToolContext& lhs, const ReadyIPMPToolContext& rhs) {
  return (lhs.GetSequenceCode() > rhs.GetSequenceCode());
}

/*! \brief  Equal operator on ready IPMP tool contexts (sequence codes).

    Used to find contexts contained in a vector of ready contexts.
*/
class EqualSeqCode {
public:
  /*! \brief  Equal operator on ready IPMP tool contexts (sequence codes).

      Used to find contexts contained in a vector of ready contexts.

      \returns  Boolean indicating if saved sequence code is equal to rhs's
                sequence code.
  */
  static bool Oper(const ReadyIPMPToolContext& rhs) {
    return (seqCode == rhs.GetSequenceCode());
  }

  //! \brief  Saved sequence code.
  static ByteT seqCode;
};

ByteT EqualSeqCode::seqCode = 0;

/*! \brief  Equal operator on ready IPMP tool contexts (instance identifiers).

    Used to find contexts contained in a vector of ready contexts.
*/
class EqualID {
public:
  /*! \brief  Equal operator on ready IPMP tool contexts (instance identifiers).

      Used to find contexts contained in a vector of ready contexts.

      \returns  Boolean indicating if saved instance identifier is equal to rhs's
                instance identifier.
  */
  static bool Oper(const ReadyIPMPToolContext& rhs) {
    return (instanceID == rhs.GetInstanceIdentifier());
  }

  //! \brief  Saved instance identifier.
  static Bit32T instanceID;
};

Bit32T EqualID::instanceID = 0;

/*! \brief  Less than operator on pair (part number, data).

    Used to sort control info parts in control info vector.

    \returns  Boolean indicating if lhs is less than rhs, depending on
              the relation between the part numbers.
*/
bool LessPartNumber(const std::pair<ByteT, ByteSeq>& lhs,
    const std::pair<ByteT, ByteSeq>& rhs) {
  return (lhs.first < rhs.first);
}

/*! \brief  IPMP tool manager.

    IPMP tool manager within a terminal.
*/
/*! \brief  Constructor.

    \param  term        IPMP terminal, used for communication with user
                        (must be != 0).
    \param  logger      message logger.

    In case of an error, throws IPMPToolManagerException.
*/     
IPMPToolManager::IPMPToolManager(IIPMPTerminal* term, DRMLogger& logger): identifier(0), mutex(0),
    created(), instantiated(), authenticated(), ready(), router(0), crypto(0),
    context(0), lastDataID(0), stop(false), dataWait(), authWait(), updateWait(),
    dataExit(), authExit(), updateExit(), controlInfoParts(), terminal(term), managerLogger(logger) {
  mutex = ThreadSyncFactory::GetMutex(managerLogger);
  if (mutex == 0) {
    throw IPMPToolManagerException();
  }
  if (terminal == 0) {
    delete mutex;
    throw IPMPToolManagerException();
  }
  crypto = new DummyCryptoProvider();
  context = new KeyPrivateAuthContext(std::vector<AlgorithmDescriptor*>(1,
    new NRegAlgorithmDescriptor(ByteSeq(), ByteSeq("RSA-PKCS1-SHA1"))),
    new TrustSecurityMetadataIPMPData(0, 0), KeyDescriptor(ByteSeq()));
  router = new MessageRouter(managerLogger);
  router->SetTerminal(this);
}

/*! \brief  Destructor.

    In case of an error, throws IPMPToolManagerException.
*/     
IPMPToolManager::~IPMPToolManager() {
  if (mutex->Lock() == false) {
    throw IPMPToolManagerException();
  }
  //  Delete all tools, to prevent them from sending any new messages.
  std::map<Bit128T, IPMPTool*>::iterator iter = created.begin();
  while (iter != created.end()) {
    if (iter->second != 0) delete iter->second;
    iter++;
  }
  created.clear();

  /*  Delete router, to prevent it from sending any new messages. This
      should fully remove the message router thread and all data.
  */
  if (router != 0) delete router; router = 0;

  if (context != 0) delete context; context = 0;
  if (crypto != 0) delete crypto; crypto = 0;

  if (terminal != 0) delete terminal; terminal = 0;

  // A list of waited events, to ensure proper stop.
  std::vector<IEvent*> waiters;
  //  Set stop indicator, for all waiters.
  stop = true;
  std::map<Bit32T, DataWaitContext*>::iterator dIter = dataWait.begin();
  while (dIter != dataWait.end()) {
    if (dIter->second->GetEvent()->Set() == false) {
      //  Error.
      mutex->Release();
      throw IPMPToolManagerException();
    }
    waiters.push_back(dataExit[dIter->first]);
    dIter++;
  }
  std::map<Bit32T, AuthWaitContext*>::iterator aIter = authWait.begin();
  while (aIter != authWait.end()) {
    if (aIter->second->GetEvent()->Set() == false) {
      //  Error.
      mutex->Release();
      throw IPMPToolManagerException();
    }
    waiters.push_back(authExit[aIter->first]);
    aIter++;
  }
  std::map<Bit32T, UpdateWaitContext*>::iterator uIter = updateWait.begin();
  while (uIter != updateWait.end()) {
    if (uIter->second->GetEvent()->Set() == false) {
      //  Error.
      mutex->Release();
      throw IPMPToolManagerException();
    }
    waiters.push_back(updateExit[uIter->first]);
    uIter++;
  }
  //  Wait for all waiters to stop.
  mutex->Release();
  if (WaitForEvents(waiters) == false) {
    throw IPMPToolManagerException();
  }

  //  This should happen immediately.
  mutex->Lock();
  for (unsigned int i = 0; i < waiters.size(); i++) {
    if (waiters[i] != 0) delete waiters[i];
  }
  mutex->Release();
  delete mutex;
}

/*! \brief  Process input message and return response in out.

    \warning  This function must be thread safe.
    \warning  Response may be 0, if none was created.

    \param  in          input, input message.
    \param  out         output, response message.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessMessage(IPMPMessageFromTool* in,
    IPMPMessageFromTool** out) {
  //  First check if the message properly routed.
  if (in->GetReceiver() != identifier) {
    delete in;
    return false;
  }

  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  ByteSeq data(in->GetMessages());
  ByteSeq response;
  while (data.GetLength() > 0) {
    //  Response created by one of the handling functions.
    ByteSeq tmp;
    if (ProcessMessage(in->GetSender(), data, tmp) == false) {
      delete in;
      mutex->Release();
      return false;
    }
    response += tmp;
  }
  if (response.GetLength() > 0) {
    *out = new IPMPMessageFromTool(in->GetVersion(), in->GetReceiver(),
      in->GetSender(), response);
  }
  delete in;
  mutex->Release();

  return true;
}

/*! \brief  IPMP agent identifier.

    Identifier 0 represents IPMP terminal, others represent IPMP descriptor
    identifiers of IPMP tools' logical instances.

    \returns  Identifier.
*/
const Bit32T& IPMPToolManager::IPMPIdentifier() const {
  return identifier;
}

/*! \brief  Handle opaque IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, opaque IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::HandleOpaqueIPMPData(const Bit32T& sender, OpaqueIPMPData* data,
    ByteSeq& resp) {
  //  First check if the sender is authenticated.
  if (IsAuthenticated(sender) == false) {
    delete data;
    return false;
  }
  //  Here we assume that opaque data is sent as a response to stream data
  //  processing message, therefore we first check if we've sent a stream data
  //  processing message with this data identifier, and if everything checks out
  //  we save return opaque data.
  if (dataWait.find(data->GetDataID()) == dataWait.end()) {
    //  We did not send a message with this data identifier. Error.
    delete data;
    return false;
  }
  if (dataWait[data->GetDataID()]->GetReceiver() != sender) {
    //  We've sent a message with this data identifier, but to another
    //  recipient. Error.
    delete data;
    return false;
  }
  //  Save opaque data for waiter.
  dataWait[data->GetDataID()]->SetData(data->GetOpaqueData());

  //  Signal waiter that data has been processed.
  if (dataWait[data->GetDataID()]->GetEvent()->Set() == false) {
    //  Error that we cannot handle.
    delete data;
    return false;
  }

  //  Delete the message.
  delete data;

  return true;
}

/*! \brief  Handle secure container IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, secure container IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::HandleSecureContainerIPMPData(const Bit32T& sender,
    SecureContainerIPMPData* data, ByteSeq& resp) {
  //  First check if the sender is authenticated.
  if (IsAuthenticated(sender) == false) {
    delete data;
    return false;
  }
  //  Here we assume that authenticatedCtx and authenticated are properly
  //  setup.
  ByteSeq unsecure;
  if (data->CheckDecrypt(authenticated[sender].GetOperator(), unsecure) == false) {
    delete data;
    return false;
  }
  //  Delete the message.
  delete data;
  //  Now we forward the message for further processing.
  if (ProcessMessage(sender, unsecure, resp) == false) {
    return false;
  }
  //  If there is a response, create a new container and return it.
  if (resp.GetLength() > 0) {
    //  Do we want to encrypt, authenticate,...?
    ByteSeq encrypted, mac, encoded;
    if (authenticated[sender].GetOperator()->EncryptAuthenticate(resp, mac,
        encrypted) == false) {
      //  Cleanup response and return error.
      resp = ByteSeq();
      return false;
    }
    //  Create new secure container, and put response in it.
    MACEncSecureContainerIPMPData secure(0, lastDataID++, encrypted, mac, managerLogger);
    if (secure.MPEG2Encode(encoded) == false) {
      //  Cleanup response and return error.
      resp = ByteSeq();
      return false;
    }
    resp = encoded;
  }
  return true;
}

/*! \brief  Handle init authentication IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, init authentication IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::HandleInitAuthenticationIPMPData(const Bit32T& sender,
    InitAuthenticationIPMPData* data, ByteSeq& resp) {
  //  Since we send an init authentication message immediately after 
  //  receiving IPMP descriptor with which tool should be instantiated,
  //  we ignore init authentication messages.
  delete data;
  return false;
/*
  //  First check if the sender is instantiated.
  if (IsInstantiated(sender) == false) {
    delete data;
    return false;
  }
  
  bool retValue = true;

  //  Decide what to do based on authentication type.
  if (data->GetAuthType() == 0x01) {
    delete data;
    //  No authentication required. Do we want to allow this?
    //  Create new ready context and save it as authenticated.
    SymmetricOperator* oper;
    if (crypto->CreateSymmetricOperator(&oper) == false) {
      return false;
    }
    ReadyIPMPToolContext ctx(instantiated[sender].GetToolIdentifier(),
      instantiated[sender].GetInstanceIdentifier(),
      instantiated[sender].GetControlPoint(), instantiated[sender].GetSequenceCode(),
      oper);
    authenticated[ctx.GetInstanceIdentifier()] = ctx;
    return true;
  } else if (data->GetAuthType() == 0x02) {
    delete data;
    //  No ID verify. Do secure channel. What exactly does this mean?
    //  Create mutual authentication message.
    //  Do we want to authenticate the message?
    if (true) {
      // authenticate
      MutualAuthenticationIPMPData tmp(0, lastDataID++, false,
        context->GetSupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
      MutualAuthenticationIPMPData* message = 0;
      if (AuthenticateMessage(&tmp, &message) == false) {
        return false;
      }
      retValue = message->MPEG2Encode(resp);
      delete message;
      return retValue;
    } else {
      // do not authenticate
      MutualAuthenticationIPMPData message(0, lastDataID++, false,
        context->GetSupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
      return message.MPEG2Encode(resp);
    }
  } else if (data->GetAuthType() == 0x03) {
    delete data;
    //  Do ID verify. No secure channel. What exactly does this mean?
    //  Create mutual authentication message.
    //  Do we want to authenticate the message?
    if (true) {
      // authenticate
      MutualAuthenticationIPMPData tmp(0, lastDataID++, false,
        context->GetSupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
      MutualAuthenticationIPMPData* message = 0;
      if (AuthenticateMessage(&tmp, &message) == false) {
        return false;
      }
      retValue = message->MPEG2Encode(resp);
      delete message;
      return retValue;
    } else {
      // do not authenticate
      MutualAuthenticationIPMPData message(0, lastDataID++, false,
        context->GetSupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
      return message.MPEG2Encode(resp);
    }
  } else if (data->GetAuthType() == 0x04) {
    delete data;
    //  Do ID verify. Do secure channel. What exactly does this mean?
    //  Create mutual authentication message.
    //  Do we want to authenticate the message?
    if (true) {
      // authenticate
      MutualAuthenticationIPMPData tmp(0, lastDataID++, false,
        context->GetSupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
      MutualAuthenticationIPMPData* message = 0;
      if (AuthenticateMessage(&tmp, &message) == false) {
        return false;
      }
      retValue = message->MPEG2Encode(resp);
      delete message;
      return retValue;
    } else {
      // do not authenticate
      MutualAuthenticationIPMPData message(0, lastDataID++, false,
        context->GetSupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
      return message.MPEG2Encode(resp);
    }
  } else {
    delete data;
    return false;
  }
*/
}

/*! \brief  Handle mutual authentication IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, mutual authentication IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::HandleMutualAuthenticationIPMPData(const Bit32T& sender,
    MutualAuthenticationIPMPData* data, ByteSeq& resp) {
  //  First check if the sender is instantiated.
  if (IsInstantiated(sender) == false) {
    delete data;
    return false;
  }
  
  Bit32T dataID = data->GetDataID();
  bool retValue = true;

  //  Do we want to check authentication codes?
  if (true) {
    if (data->GetAuthenticationCodes() != 0) {
      if (data->CheckAuthentication(crypto) == false) {
        delete data;
        return false;
      }
    }
  }

  //  Check if this a response to previous authentication message.
  if (authWait.find(dataID) != authWait.end()) {
    //  Since we send init authentication message, this message is either
    //  a negotiation response or an authentication step response. We
    //  check if we have an authenticator set for this data identifier.
    //  If it is set, then it is handled as an authentication step response.
    //  If it is not set, then it is handled as an negotiation response.
    if (authWait[dataID]->GetAuthenticator() == 0) {
      //  Negotiation step.
      if (data->GetFailedNegotiation() == true) {
        //  Strange, but who knows.
        delete data;
        authWait[dataID]->SetSuccess(false);
        authWait[dataID]->GetEvent()->Set();
        return true;
      }
      if (data->GetRequestNegotiation() == true) {
        //  Create an intersection of supported algorithms and send either
        //  success negotiation or failed negotiation message.
        std::vector<AlgorithmDescriptor*> intersect;
        std::vector<AlgorithmDescriptor*>::const_iterator i1 =
          context->GetSupportedAlgorithms().begin();
        std::vector<AlgorithmDescriptor*>::const_iterator i2 =
          data->GetCandidateAlgorithms().begin();
        while (i1 != context->GetSupportedAlgorithms().end()) {
          while (i2 != data->GetCandidateAlgorithms().end()) {
            if ((*i1)->GetAlgorithmID() == (*i2)->GetAlgorithmID()) {
              intersect.push_back((*i1)->Copy());
            }
            i2++;
          }
          i1++;
        }
        if (intersect.size() == 0) {
          //  Failed negotiation.
          delete data;
          MutualAuthenticationIPMPData message(0, dataID, true,
            std::vector<AlgorithmDescriptor*>(), std::vector<AlgorithmDescriptor*>(),
            0);
          //  Do we want to authenticate the message?
          if (true) {
            // authenticate
            if (message.Authenticate(crypto, context) != false) {
              message.MPEG2Encode(resp);
            }
          }
          authWait[dataID]->SetSuccess(false);
          authWait[dataID]->GetEvent()->Set();
          return false;
        } else {
          //  Successful negotiation.
          AuthCodes* codes = data->GetAuthenticationCodes();
          if ((retValue = (codes != 0)) != false) {
            PublicAuthContext* pubCtx = codes->GetAuthContext();
            std::vector<AlgorithmDescriptor*> algs;
            std::vector<AlgorithmDescriptor*>::const_iterator i1 = intersect.begin();
            while (i1 != intersect.end()) {
              algs.push_back((*i1)->Copy());
              i1++;
            }
            pubCtx->SetSupportedAlgorithms(algs);
            Authenticator* authenticator;
            if ((retValue = context->CreateAuthenticator(crypto, pubCtx, &authenticator))
                != false) {
              authWait[dataID]->SetAuthenticator(authenticator);
            }
          }
          delete data;
          if (retValue == false) {
            authWait[dataID]->SetSuccess(false);
            authWait[dataID]->GetEvent()->Set();
            return false;
          }

          MutualAuthenticationIPMPData message(0, dataID, false,
            std::vector<AlgorithmDescriptor*>(), intersect, 0);
          //  Do we want to authenticate the message?
          if (true) {
            // authenticate
            if ((retValue = message.Authenticate(crypto, context)) != false) {
              retValue = message.MPEG2Encode(resp);
            }
            if (retValue == false) {
              //  Error. Remove authenticator.
              authWait[dataID]->SetAuthenticator(0);
              authWait[dataID]->SetSuccess(false);
              authWait[dataID]->GetEvent()->Set();
              return false;
            }
          }
          return true;
        }
      }
      //  If we got here, none of the above checks applied, so this is an error.
      authWait[dataID]->SetSuccess(false);
      authWait[dataID]->GetEvent()->Set();
      return false;
    } else {
      //  Authentication step.
      if (data->GetAuthenticationData() != 0) {
        SymmetricOperator* symm = 0;
        ByteSeq authData;
        if ((retValue = authWait[dataID]->GetAuthenticator()->AuthenticationStep(
            crypto, *(data->GetAuthenticationData()), authData, &symm)) == true) {
          delete data;
          if (authData.GetLength() != 0) {
            MutualAuthenticationIPMPData message(0, dataID, false,
              std::vector<AlgorithmDescriptor*>(), std::vector<AlgorithmDescriptor*>(),
              authData, 0);
            //  Do we want to authenticate the message?
            if (true) {
              // authenticate
              if ((retValue = message.Authenticate(crypto, context)) != false) {
                retValue = message.MPEG2Encode(resp);
              }
              if (retValue == false) {
                authWait[dataID]->SetAuthenticator(0);
                authWait[dataID]->SetSuccess(false);
                authWait[dataID]->GetEvent()->Set();
                if (symm != 0) delete symm; symm = 0;
                return false;
              }
            }
          }
          if (symm != 0) {
            //  Successful authentication.
            ReadyIPMPToolContext ctx(instantiated[sender].GetToolIdentifier(),
              instantiated[sender].GetInstanceIdentifier(),
              instantiated[sender].GetControlPoint(),
              instantiated[sender].GetSequenceCode(), symm);
            authenticated[ctx.GetInstanceIdentifier()] = ctx;
          }
          //  Perhaps one more check should be applied: if symm == 0, then
          //  authData must not be empty. Otherwise it's an authenticator bug.
          return true;
        }
      }
      delete data;
      authWait[dataID]->SetAuthenticator(0);
      authWait[dataID]->SetSuccess(false);
      authWait[dataID]->GetEvent()->Set();
      return false;
    }
  }
  //  We don't have a waiting context, so we refuse the message.
  delete data;
  return false;
}

/*! \brief  Handle can process IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, can process IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::HandleCanProcessIPMPData(const Bit32T& sender,
    CanProcessIPMPData* data, ByteSeq& resp) {
  //  First check that the sender is authenticated.
  if (IsAuthenticated(sender) == true) {
    //  Now check if sender is ready for processing.
    if (data->GetCanProcessFlag() == true) {
      //  Check if there is a waiting context for this sender. If not,
      //  it's an internal error, cause the sender should not have been
      //  authenticated without an existing waiting context (see mutual
      //  authentication message process function).
      std::map<Bit32T, AuthWaitContext*>::iterator waiters = authWait.begin();
      while (waiters != authWait.end()) {
        if (waiters->second->GetReceiver() == sender) {
          break;
        }
        waiters++;
      }
      if (waiters == authWait.end()) {
        //  Internal error.
        delete data;
        return false;
      }

      //  We have to check if an existing tool on the same control point has
      //  the same sequence code. If it does, then it is an error.
      std::vector<ReadyIPMPToolContext>& contexts =
        ready[authenticated[sender].GetControlPoint()];
      EqualSeqCode::seqCode = authenticated[sender].GetSequenceCode();
      if (std::find_if(contexts.begin(), contexts.end(), EqualSeqCode::Oper) !=
          contexts.end()) {
        delete data;
        return false;
      }
      contexts.push_back(authenticated[sender]);
      //  Sort ready tools by sequence code.
      std::sort(contexts.begin(), contexts.end(), GreaterSeqCode);
      delete data;
      //  Signal waiters.
      waiters->second->SetSuccess(true);
      waiters->second->GetEvent()->Set();
      return true;
    } else {
      //  The sender indicated that it cannot process. We remove it's context
      //  from ready, if it exists.
      std::vector<ReadyIPMPToolContext>& contexts =
        ready[authenticated[sender].GetControlPoint()];
      EqualID::instanceID = authenticated[sender].GetInstanceIdentifier();
      std::vector<ReadyIPMPToolContext>::iterator iter = 
        std::find_if(contexts.begin(), contexts.end(), EqualID::Oper);
      if (iter != contexts.end()) {
        //  It exists. Remove it.
        contexts.erase(iter);
        //  Re-sort the ready contexts.
        std::sort(contexts.begin(), contexts.end(), GreaterSeqCode);
      }
      delete data;
      return true;
    }
  } else {
    //  The sender is not authenticated.
    delete data;
    return false;
  }
}

/*! \brief  Handle user query IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, user query IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::HandleUserQueryIPMPData(const Bit32T& sender,
    DecoderUserQueryIPMPData* data, ByteSeq& resp) {
  UserQueryResponseIPMPData* response = 0;
  if (data->Query(terminal, &response) == false) {
    delete data;
    return false;
  }
  delete data;
  if (response != 0) {
    if (response->MPEG2Encode(resp) == false) {
      delete response;
      return false;
    }
    delete response;
  }

  return true;
}

/*! \brief  Process last IPMP control info part (transport stream).

    \param  in          input, last IPMP control info part (transport stream).

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessLastTStreamIPMPControlInfoPart(
    ILastTStreamIPMPControlInfoPart* in) {
  if (in == 0) {
    return false;
  }
  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  //  Check CRC32 code.
  ByteSeq encoded;
  if (in->MPEG2Encode(encoded) == false) {
    delete in;
    mutex->Release();
    return false;
  }
  CRC32Calculator crcCalc;
  if (crcCalc.GetCRC(encoded.GetFirst(), encoded.GetLength()) != in->GetCRC32Code()) {
    controlInfoParts.clear();
    delete in;
    mutex->Release();
    return false;
  }

  //  Now take control infos out, save them to controlInfoParts and return.
  controlInfoParts.push_back(std::pair<ByteT, ByteSeq>(in->GetPartNumber(),
    in->GetIPMPControlInfos()));

  bool retValue = true;

  //  If last part has signature container, check signature.
  if (in->GetSigCertContainer() != 0) {
    //  Do we want to check the signature.
    if (true) {
      CertPublicVerifierContext verifierCtx(in->GetSigCertContainer()->GetCertContainers());
      HashCalculator* hasher;
      ByteSeq hash;
      if ((retValue = verifierCtx.CreateHashCalculator(crypto, &hasher)) != false) {
        if ((retValue = hasher->HashInit()) != false) {
          for (unsigned int i = 0; i < controlInfoParts.size(); i++) {
            if ((retValue = hasher->HashUpdate(controlInfoParts[i].second)) == false) {
              break;
            }
          }
          if (retValue != false) {
            retValue = retValue && hasher->HashFinish(hash);
          }
          delete hasher;
          if (retValue != false) {
            PublicVerifier* verifier;
            if ((retValue = verifierCtx.CreatePublicVerifier(crypto, &verifier)) != false) {
              retValue = verifier->VerifySignature(
                in->GetSigCertContainer()->GetSignature(), hash);
            }
          }
        } else {
          delete hasher;
        }
      }
    }
  }

  delete in;

  if (retValue == false) {
    controlInfoParts.clear();
    mutex->Release();
    return retValue;
  }

  //  Sort the vector by part numbers.
  std::sort(controlInfoParts.begin(), controlInfoParts.end(), LessPartNumber);
  //  Assemble control info classes data.
  ByteSeq controlInfos;
  for (unsigned int j = 0; j < controlInfoParts.size(); j++) {
    controlInfos += controlInfoParts[j].second;
  }
  controlInfoParts.clear();

  //  Create a control info parser, and parse control infos. Create tools.
  IPMPControlInfoParser parser(managerLogger);
  while (controlInfos.GetLength() > 0) {
    DecoderIPMPControlInfo* control;
    if (parser.ParseIPMPControlInfo(controlInfos, &control) == false) {
      mutex->Release();
      return false;
    }
    //  Control information classes must take care of possible overwriting
    //  of already created tools.
    if (control->CreateIPMPTools(created) == false) {
      delete control;
      mutex->Release();
      return false;
    }
    delete control;
  }

  mutex->Release();

  return retValue;
}

/*! \brief  Process intermediate IPMP control info part (transport stream).

    \param  in          input, intermediate IPMP control info part (transport stream).

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessInterTStreamIPMPControlInfoPart(
    IInterTStreamIPMPControlInfoPart* in) {
  if (in == 0) {
    return false;
  }
  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  //  Check CRC32 code.
  ByteSeq encoded;
  if (in->MPEG2Encode(encoded) == false) {
    delete in;
    mutex->Release();
    return false;
  }
  CRC32Calculator crcCalc;
  if (crcCalc.GetCRC(encoded.GetFirst(), encoded.GetLength()) != in->GetCRC32Code()) {
    controlInfoParts.clear();
    delete in;
    mutex->Release();
    return false;
  }

  //  Now take control infos out, save them to controlInfoParts and return.
  controlInfoParts.push_back(std::pair<ByteT, ByteSeq>(in->GetPartNumber(),
    in->GetIPMPControlInfos()));

  delete in;
  mutex->Release();
  return true;
}

/*! \brief  Process last IPMP control info part (program stream).

    \param  in          input, last IPMP control info part (program stream).

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessLastPStreamIPMPControlInfoPart(
    ILastPStreamIPMPControlInfoPart* in) {
  if (in == 0) {
    return false;
  }
  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  //  Check CRC32 code.
  ByteSeq encoded;
  if (in->MPEG2Encode(encoded) == false) {
    delete in;
    mutex->Release();
    return false;
  }
  CRC32Calculator crcCalc;
  if (crcCalc.GetCRC(encoded.GetFirst(), encoded.GetLength()) != in->GetCRC32Code()) {
    controlInfoParts.clear();
    delete in;
    mutex->Release();
    return false;
  }

  //  Now take control infos out, save them to controlInfoParts and return.
  controlInfoParts.push_back(std::pair<ByteT, ByteSeq>(in->GetPartNumber(),
    in->GetIPMPControlInfos()));

  bool retValue = true;

  //  If last part has signature container, check signature.
  if (in->GetSigCertContainer() != 0) {
    //  Do we want to check the signature.
    if (true) {
      CertPublicVerifierContext verifierCtx(in->GetSigCertContainer()->GetCertContainers());
      HashCalculator* hasher;
      ByteSeq hash;
      if ((retValue = verifierCtx.CreateHashCalculator(crypto, &hasher)) != false) {
        if ((retValue = hasher->HashInit()) != false) {
          for (unsigned int i = 0; i < controlInfoParts.size(); i++) {
            if ((retValue = hasher->HashUpdate(controlInfoParts[i].second)) == false) {
              break;
            }
          }
          if (retValue != false) {
            retValue = retValue && hasher->HashFinish(hash);
          }
          delete hasher;
          if (retValue != false) {
            PublicVerifier* verifier;
            if ((retValue = verifierCtx.CreatePublicVerifier(crypto, &verifier)) != false) {
              retValue = verifier->VerifySignature(
                in->GetSigCertContainer()->GetSignature(), hash);
            }
          }
        } else {
          delete hasher;
        }
      }
    }
  }

  delete in;

  if (retValue == false) {
    controlInfoParts.clear();
    mutex->Release();
    return retValue;
  }

  //  Sort the vector by part numbers.
  std::sort(controlInfoParts.begin(), controlInfoParts.end(), LessPartNumber);
  //  Assemble control info classes data.
  ByteSeq controlInfos;
  for (unsigned int j = 0; j < controlInfoParts.size(); j++) {
    controlInfos += controlInfoParts[j].second;
  }
  controlInfoParts.clear();

  //  Create a control info parser, and parse control infos. Create tools.
  IPMPControlInfoParser parser(managerLogger);
  while (controlInfos.GetLength() > 0) {
    DecoderIPMPControlInfo* control;
    if (parser.ParseIPMPControlInfo(controlInfos, &control) == false) {
      mutex->Release();
      return false;
    }
    //  Control information classes must take care of possible overwriting
    //  of already created tools.
    if (control->CreateIPMPTools(created) == false) {
      delete control;
      mutex->Release();
      return false;
    }
    delete control;
  }

  mutex->Release();

  return retValue;
}

/*! \brief  Process intermediate IPMP control info part (program stream).

    \param  in          input, intermediate IPMP control info part (program stream).

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessInterPStreamIPMPControlInfoPart(
    IInterPStreamIPMPControlInfoPart* in) {
  if (in == 0) {
    return false;
  }
  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  //  Check CRC32 code.
  ByteSeq encoded;
  if (in->MPEG2Encode(encoded) == false) {
    delete in;
    mutex->Release();
    return false;
  }
  CRC32Calculator crcCalc;
  if (crcCalc.GetCRC(encoded.GetFirst(), encoded.GetLength()) != in->GetCRC32Code()) {
    controlInfoParts.clear();
    delete in;
    mutex->Release();
    return false;
  }

  //  Now take control infos out, save them to controlInfoParts and return.
  controlInfoParts.push_back(std::pair<ByteT, ByteSeq>(in->GetPartNumber(),
    in->GetIPMPControlInfos()));

  delete in;
  mutex->Release();
  return true;
}

/*! \brief  Process IPMP descriptor.

    \warning  This function must be thread safe.

    \param  in          input, IPMP descriptor.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessIPMPDescriptor(IIPMPDescriptor* in) {
  //  Check if we received a correct descriptor.
  if (in == 0) {
    return false;
  }

  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  //  Check if a tool is created.
  if (IsCreated(in->GetIPMPToolID()) == false) {
    delete in;
    mutex->Release();
    return false;
  }

  //  Save receiver.
  Bit128T toolID = in->GetIPMPToolID();
  Bit32T instanceID = in->GetIPMPDescriptorID();
  ByteT control = in->GetControlPoint();
  ByteT sequence = in->GetSequenceCode();

  //  Inform message router that we have a new tool.
  if (router->AddTool(instanceID, created[toolID]) == false) {
    mutex->Release();
    return false;
  }

  //  Send IPMP descriptor to the tool.
  if (router->SendToolMessage(new IPMPDescriptorFromBitstream(0, identifier,
      instanceID, in)) == false) {
    mutex->Release();
    return false;
  }

  //  Save a context to instantiated.
  IPMPToolContext instance(toolID, instanceID, control, sequence);
  instantiated[instanceID] = instance;

  //  Create a new init authentication message and send it to the tool.
  //  What kind of authentication shall we require?
  InitAuthenticationIPMPData init(0, lastDataID++, instanceID, 0x04);
  ByteSeq encoded;
  if (init.MPEG2Encode(encoded) == false) {
    mutex->Release();
    return false;
  }
  if (router->SendMessage(new IPMPMessageFromTool(0, identifier, instanceID,
      encoded)) == false) {
    mutex->Release();
    return false;
  }

  //  Save a context to authWait.
  IEvent* waitEvent = ThreadSyncFactory::GetEvent(managerLogger);
  IEvent* exitEvent = ThreadSyncFactory::GetEvent(managerLogger);
  if ((waitEvent == 0) || (exitEvent == 0)) {
    if (waitEvent != 0) delete waitEvent;
    if (exitEvent != 0) delete exitEvent;
    mutex->Release();
    return false;
  }
  authWait[init.GetDataID()] = new AuthWaitContext(waitEvent, false, instanceID, 0);
  authExit[init.GetDataID()] = exitEvent;

  mutex->Release();

  //  Enter waiting loop for the successful or failed authentication.
  bool succ = waitEvent->Wait(EVENT_WAIT_TIME);

  //  Authentication event is signaled. Wait for mutex.
  if (mutex->Lock() == false) {
    return false;
  }

  //  Now we have control. This is a result of either successful authentication
  //  or a destructor.
  delete authWait[init.GetDataID()];
  authWait.erase(init.GetDataID());
  if (stop == true) {
    exitEvent->Set();
  } else {
    delete authExit[init.GetDataID()];
    authExit.erase(init.GetDataID());
  }

  mutex->Release();

  return (succ && (!stop));
}

/*! \brief  Process IPMP stream data update.

    \warning  This function must be thread safe.

    \param  in          input, IPMP stream data update.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessIPMPStreamDataUpdate(IIPMPStreamDataUpdate* in) {
  //  Check if we received a correct update.
  if (in == 0) {
    return false;
  }

  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  //  Check if the receiver is ready.
  if (IsReady(in->GetIPMPDescriptorID()) == false) {
    delete in;
    mutex->Release();
    return false;
  }

  //  Send IPMP update to the tool.
  if (router->SendToolMessage(new IPMPMessageFromBitstream(0, identifier,
      in->GetIPMPDescriptorID(), std::vector<IIPMPStreamDataUpdate*>(1, in))) == false) {
    mutex->Release();
    return false;
  }

  //  Do we have to wait for something here? Some indication that update
  //  was successful?
  mutex->Release();
  return true;
}

/*! \brief  Process stream data.

    \param  cPoint      input, control point code.
    \param  in          input, data to be processed.
    \param  out         output, processed data.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessData(const ByteT& cPoint, const ByteSeq& in, ByteSeq& out) {
  //  Get mutex.
  if (mutex->Lock() == false) {
    return false;
  }

  //  Check if we have any tools residing on the control point cPoint.
  if (ready.find(cPoint) == ready.end()) {
    mutex->Release();
    return false;
  }
  if (ready[cPoint].size() == 0) {
    //  This should not have happened. It's some bug in the internal handling
    //  of ready map.
    mutex->Release();
    return false;
  }

  //  For all tools that reside on the control point cPoint, encrypt in,
  //  create and send them opaque IPMP data message containing encrypted in,
  //  create a waiting context for response, and waiting is done, continue.
  ByteSeq dataInProcess = in;
  for (unsigned int i = 0; i < ready[cPoint].size(); i++) {
    ReadyIPMPToolContext& ctx = ready[cPoint][i];
    if (ctx.GetOperator() == 0) {
      //  This should not have happened. Internal error.
      mutex->Release();
      return false;
    }
    //  First create opaque data message, which will be sent to the tool.
    //  We create new data identifier for this message.
    OpaqueIPMPData opaque(0, lastDataID++, dataInProcess);
    ByteSeq encoded;
    if (opaque.MPEG2Encode(encoded) == false) {
      mutex->Release();
      return false;
    }
    //  How do we want to encrypt, authenticate, etc.?
    ByteSeq encrypted, mac;
    if (ctx.GetOperator()->EncryptAuthenticate(encoded, mac, encrypted) == false) {
      mutex->Release();
      return false;
    }
    MACEncSecureContainerIPMPData secure(0, lastDataID++, encrypted, mac, managerLogger);
    if (secure.MPEG2Encode(encoded) == false) {
      mutex->Release();
      return false;
    }
    if (router->SendMessage(new IPMPMessageFromTool(0, identifier,
        ctx.GetInstanceIdentifier(), encoded)) == false) {
      mutex->Release();
      return false;
    }

    //  Now create a waiting context, release mutex and wait.
    IEvent* waitEvent = ThreadSyncFactory::GetEvent(managerLogger);
    IEvent* exitEvent = ThreadSyncFactory::GetEvent(managerLogger);
    if ((waitEvent == 0) || (exitEvent == 0)) {
      if (waitEvent != 0) delete waitEvent;
      if (exitEvent != 0) delete exitEvent;
      mutex->Release();
      return false;
    }

    dataWait[opaque.GetDataID()] =
      new DataWaitContext(waitEvent, ByteSeq(), ctx.GetInstanceIdentifier());
    dataExit[opaque.GetDataID()] = exitEvent;

    mutex->Release();

    //  Enter waiting loop for the successful or failed processing.
    bool succ = waitEvent->Wait(EVENT_WAIT_TIME);

    //  Data processing event is signaled. Wait for mutex.
    if (mutex->Lock() == false) {
      return false;
    }

    ByteSeq dd(dataWait[opaque.GetDataID()]->GetData());
    delete dataWait[opaque.GetDataID()];
    dataWait.erase(opaque.GetDataID());
    //  Now we have control. This is a result of either successful data processing
    //  or the destructor.
    //  Check if we're supposed to stop.
    if (stop == true) {
      exitEvent->Set();
      mutex->Release();
      return false;
    } else {
      delete dataExit[opaque.GetDataID()];
      dataExit.erase(opaque.GetDataID());
    }
    if (succ == false) {
      mutex->Release();
      return false;
    }

    //  Take the data out and decrypt it.
    if (ctx.GetOperator()->Decrypt(dd, dataInProcess) == false) {
      mutex->Release();
      return false;
    }
  }

  //  Now we have the control of the mutex and processed data in dataInProcess.
  out = dataInProcess;

  mutex->Release();

  return true;
}

/*! \brief  Process (one) input message and return response.

    \warning  This function must be thread safe.
    \warning  Response may be empty, if none was created.
    \warning  Input message data is modified.

    \param  sender      input, sender's code.
    \param  in          input, input message data.
    \param  out         output, response message data.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolManager::ProcessMessage(const Bit32T& sender, ByteSeq& in,
    ByteSeq& out) {
  //  Create IPMP data parser, and give the contained messages to it. It will
  //  parse them, and call our handling routines.
  IPMPDataParser parser(managerLogger);
  //  Response created by one of the handling functions.
  return parser.ParseMessage(sender, in, this, out);
}

/*! \brief  Check if tool is created.

    \param  id        input, tool identifier.

    \returns  Boolean indicating whether tool is created.
*/
bool IPMPToolManager::IsCreated(const Bit128T& id) {
  return (created.find(id) != created.end());
}

/*! \brief  Check if tool is instantiated.

    \param  id        input, tool's instance identifier.

    \returns  Boolean indicating whether tool is instantiated.
*/
bool IPMPToolManager::IsInstantiated(const Bit32T& id) {
  return (instantiated.find(id) != instantiated.end());
}

/*! \brief  Check if tool is authenticated.

    \param  id        input, tool's instance identifier.

    \returns  Boolean indicating whether tool is authenticated.
*/
bool IPMPToolManager::IsAuthenticated(const Bit32T& id) {
  return (authenticated.find(id) != authenticated.end());
}

/*! \brief  Check if tool is authenticated and ready for processing.

    \param  id        input, tool's instance identifier.

    \returns  Boolean indicating whether tool is authenticated and
              ready for processing.
*/
bool IPMPToolManager::IsReady(const Bit32T& id) {
  if (IsAuthenticated(id) == false) {
    return false;
  }
  if (ready.find(authenticated[id].GetControlPoint()) == ready.end()) {
    return false;
  }
  std::vector<ReadyIPMPToolContext>::const_iterator iter =
    ready[authenticated[id].GetControlPoint()].begin();
  while (iter != ready[authenticated[id].GetControlPoint()].end()) {
    if (iter->GetInstanceIdentifier() == id) {
      return true;
    }
    iter++;
  }
  return false;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
