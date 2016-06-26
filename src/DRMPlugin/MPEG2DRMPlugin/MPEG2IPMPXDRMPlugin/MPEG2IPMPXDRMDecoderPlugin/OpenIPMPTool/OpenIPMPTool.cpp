/**	\file OpenIPMPTool.cpp

	OpenIPMP MPEG2 IPMP tool.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPTool.h"

#include "IPMPAgent.h"
#include "MessageRouter.h"
#include "IPMPMessage.h"
#include "IPMPData.h"
#include <string>

#include "IPMPDataParser.h"

#include "IOpenIPMPDRMDecryptor.h"
#include "OpenIPMPDRMInfo.h"
#include "OpenIPMPDRMDecManagerFactory.h"
#include "XMLFactory.h"
#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  OpenIPMP tool for protection of MPEG2 data.
*/
/*! \brief  Constructor.

    \param  logger      message logger.

    In case of an error, throws ToolException.
*/
OpenIPMPTool::OpenIPMPTool(DRMLogger& logger): toolID(), identifier(0),
    mutex(0), router(0), authenticator(0), symmetric(0), context(0), crypto(0),
    lastDataID(0), decryptor(0), queries(), toolLogger(logger) {
  mutex = ThreadSyncFactory::GetMutex(toolLogger);
  if (mutex == 0) {
    throw ToolException();
  }
  std::string tool = "openIPMP tool ID";
  ByteT id[16];
  memcpy(id, tool.data(), 16);
  toolID = id;
  router = new MessageRouter(toolLogger);
  context = new KeyPrivateAuthContext(std::vector<AlgorithmDescriptor*>(1,
    new NRegAlgorithmDescriptor(ByteSeq(), ByteSeq("RSA-PKCS1-SHA1"))),
    new TrustSecurityMetadataIPMPData(0, 0), KeyDescriptor(ByteSeq()));
  crypto = new DummyCryptoProvider();
}

OpenIPMPTool::~OpenIPMPTool() {
  if (router != 0) delete router; router = 0;
  if (authenticator != 0) delete authenticator; authenticator = 0;
  if (symmetric != 0) delete symmetric; symmetric = 0;
  if (context != 0) delete context; context = 0;
  if (crypto != 0) delete crypto; crypto = 0;
  if (decryptor != 0) delete decryptor; decryptor = 0;
  if (mutex != 0) delete mutex;
}

/*! \brief  Process input message and return response in out.

    \warning  This function must be thread safe.
    \warning  Response may be 0, if none was created.

    \param  in          input, input message.
    \param  out         output, response message.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPTool::ProcessMessage(IPMPMessageFromTool* in, IPMPMessageFromTool** out) {
  //  First check if the sender is the terminal and that we are instantiated.
  if ((in->GetSender() != 0) || (identifier == 0)) {
    delete in;
    return false;
  }

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
const Bit32T& OpenIPMPTool::IPMPIdentifier() const {
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
bool OpenIPMPTool::HandleOpaqueIPMPData(const Bit32T& sender, OpaqueIPMPData* data,
    ByteSeq& resp) {
  //  First check if the sender is the terminal and that we are instantiated.
  if ((sender != 0) || (identifier == 0) || (decryptor == 0)) {
    delete data;
    return false;
  }

  //  Here we assume that opaque data is a stream data process request.
  //  Process data.
  DRMLogger logger;
  ByteT* outb = 0;
  UInt32T outl = 0;
  if (decryptor->Decrypt((ByteT*)(data->GetOpaqueData().GetFirst()),
      data->GetOpaqueData().GetLength(), &outb, &outl) == false) {
    delete data;
    return false;
  }
  ByteSeq out(outb, outl);
  if (outb != 0) {
    free(outb);
  }
  OpaqueIPMPData opaque(data->GetVersion(), data->GetDataID(), out);
  delete data;

  return opaque.MPEG2Encode(resp);
}

/*! \brief  Handle rights IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, rights IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPTool::HandleRightsIPMPData(const Bit32T& sender, RightsIPMPData* data,
    ByteSeq& resp) {
  //  First check if the sender is the terminal and that we are instantiated.
  if ((sender != 0) || (identifier == 0)) {
    delete data;
    return false;
  }

  //  If we are authenticated with the tool manager, then we immediately send
  //  a user query message. If not, it means that we are still in process
  //  of authentication, thus we save a pending user query message, which
  //  should be sent after authentication is done.
  std::vector<QTArray> qtext;
  qtext.push_back(QTArray(Bit16T(), Bit16T(), false,
    ByteSeq(std::string("Please enter openIPMP server username: "))));
  qtext.push_back(QTArray(Bit16T(), Bit16T(), false,
    ByteSeq(std::string("Please enter openIPMP server password: "))));
  qtext.push_back(QTArray(Bit16T(), Bit16T(), false,
    ByteSeq(std::string("Please enter openIPMP XML configuration file name: "))));
  UserQueryText text(Bit24T(), 0, std::vector<DTArray>(1, DTArray(Bit16T(),
    ByteSeq(std::string("Instantiating openIPMP tool...\n")))), qtext,
    std::vector<OptionArray>(), 0);

  DecoderUserQueryIPMPData query(0, lastDataID++, false, true, true, false,
    false, std::vector<UserQueryText>(1, text));
  queries[query.GetDataID()] = UserQueryContext(data->GetRightsInfo(), query);
  delete data;
  if (symmetric != 0) {
    //  Authentication is done.
    if (query.MPEG2Encode(resp) == false) {
      //  Should we remove the waiting user query context?
      return false;
    }
  }
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
bool OpenIPMPTool::HandleSecureContainerIPMPData(const Bit32T& sender,
    SecureContainerIPMPData* data, ByteSeq& resp) {
  //  First check if the sender is the terminal and that we are instantiated.
  if ((sender != 0) || (identifier == 0)) {
    delete data;
    return false;
  }

  //  Check if we have a symmetric operator set.
  ByteSeq unsecure;
  if (data->CheckDecrypt(symmetric, unsecure) == false) {
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
    if (symmetric->EncryptAuthenticate(resp, mac, encrypted) == false) {
      //  Cleanup response and return error.
      resp = ByteSeq();
      return false;
    }
    //  Create new secure container, and put response in it.
    MACEncSecureContainerIPMPData secure(0, data->GetDataID(), encrypted, mac, toolLogger);
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
bool OpenIPMPTool::HandleInitAuthenticationIPMPData(const Bit32T& sender,
    InitAuthenticationIPMPData* data, ByteSeq& resp) {
  //  First check if the sender is the terminal and that we are instantiated.
  if ((sender != 0) || (identifier == 0)) {
    delete data;
    return false;
  }

  ByteT authType = data->GetAuthType();
  Bit32T dataID = data->GetDataID();

  //  We don't need it anymore.
  delete data;

  //  Decide what to do based on authentication type.
  if (authType == 0x01) {
    //  No authentication required. Do we want to allow this?
    if (symmetric != 0) {
      //  We had previous context set. An error?
      delete symmetric; symmetric = 0;
    }
    return crypto->CreateSymmetricOperator(&symmetric);
  } else if (authType == 0x02) {
    //  No ID verify. Do secure channel. What exactly does this mean?
    //  Create mutual authentication message.
    MutualAuthenticationIPMPData message(0, dataID, false,
      context->CopySupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
    //  Do we want to authenticate the message?
    if (true) {
      // authenticate
      if (message.Authenticate(crypto, context) == false) {
        return false;
      }
    }
    return message.MPEG2Encode(resp);
  } else if (authType == 0x03) {
    //  Do ID verify. No secure channel. What exactly does this mean?
    //  Create mutual authentication message.
    MutualAuthenticationIPMPData message(0, dataID, false,
      context->CopySupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
    //  Do we want to authenticate the message?
    if (true) {
      // authenticate
      if (message.Authenticate(crypto, context) == false) {
        return false;
      }
    }
    return message.MPEG2Encode(resp);
  } else if (authType == 0x04) {
    //  Do ID verify. Do secure channel. What exactly does this mean?
    //  Create mutual authentication message.
    MutualAuthenticationIPMPData message(0, dataID, false,
      context->CopySupportedAlgorithms(), std::vector<AlgorithmDescriptor*>(), 0);
    //  Do we want to authenticate the message?
    if (true) {
      // authenticate
      if (message.Authenticate(crypto, context) == false) {
        return false;
      }
    }
    return message.MPEG2Encode(resp);
  } else {
    return false;
  }
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
bool OpenIPMPTool::HandleMutualAuthenticationIPMPData(const Bit32T& sender,
    MutualAuthenticationIPMPData* data, ByteSeq& resp) {
  //  First check if the sender is the terminal and that we are instantiated.
  if ((sender != 0) || (identifier == 0)) {
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

  //  This message is either a negotiation response or an authentication
  //  step response. We check if we have an authenticator set. If it is set,
  //  then it is handled as an authentication step response.
  //  If it is not set, then it is handled as an negotiation response.
  if (authenticator == 0) {
    //  Negotiation step.
    if (data->GetFailedNegotiation() == true) {
      delete data;
      return true;
    }
    if (data->GetSuccessNegotiation() == true) {
      AuthCodes* codes = data->GetAuthenticationCodes();
      if (codes == 0) {
        //  We cannot create authenticator without authentication context.
        //  Should we create a failed negotiation message and send it?
        delete data;
        return false;
      }
      PublicAuthContext* pubCtx = codes->GetAuthContext();
      std::vector<AlgorithmDescriptor*> algs;
      std::vector<AlgorithmDescriptor*>::const_iterator i1 =
        data->GetAgreedAlgorithms().begin();
      while (i1 != data->GetAgreedAlgorithms().end()) {
        algs.push_back((*i1)->Copy());
        i1++;
      }
      pubCtx->SetSupportedAlgorithms(algs);
      if (context->CreateAuthenticator(crypto, pubCtx, &authenticator) == false) {
        delete data;
        return false;
      }
      delete data;
      //  Perform authenication step and send a mutual authentication message.
      //  If we had previous symmetric operator, we delete it. This means that
      //  this is another authentication.
      if (symmetric != 0) delete symmetric; symmetric = 0;
      ByteSeq authData;
      if (authenticator->AuthenticationStep(crypto, ByteSeq(), authData,
          &symmetric) == false) {
        delete authenticator; authenticator = 0;
        return false;
      }
      //  There are 2 possibilities: either only a single step is needed for
      //  authentication, in which case symmetric operator and authentication data
      //  are created, or more steps are needed, in which case only authentication
      //  data is created.
      //  First check that we have authentication data.
      if (authData.GetLength() == 0) {
        //  Error.
        delete authenticator; authenticator = 0;
        if (symmetric != 0) delete symmetric; symmetric = 0;
        return false;
      }

      //  Clean up response.
      resp = ByteSeq();
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
          delete authenticator; authenticator = 0;
          if (symmetric != 0) delete symmetric; symmetric = 0;
          return false;
        }
      }

      //  We have created a mutual authentication message. If the symmetric
      //  operator was created, we don't need authenticator anymore. Otherwise
      //  we keep it for further authentication.
      if (symmetric != 0) {
        //  Successful authentication.
        delete authenticator; authenticator = 0;
        /*  Check if we have pending user queries. If we do, send them. If not,
            then return can process message.
        */
        if (queries.size() > 0) {
          std::map<Bit32T, UserQueryContext>::iterator iter = queries.begin();
          while (iter != queries.end()) {
            ByteSeq tmp;
            if (iter->second.GetMessage().MPEG2Encode(tmp) == false) {
              //  Error. Should we delete symmetric?
//              delete symmetric; symmetric = 0;
              return false;
            }
            resp += tmp;
            iter++;
          }
        } else {
          CanProcessIPMPData canProcess(0, dataID, true);
          ByteSeq canProcessEncoded;
          if (canProcess.MPEG2Encode(canProcessEncoded) == false) {
            //  Error. Should we delete symmetric?
//            delete symmetric; symmetric = 0;
            return false;
          }
          resp += canProcessEncoded;
        }
      }
      return true;
    }
    //  If we got here, none of the above checks applied, so this is an error.
    delete data;
    return false;
  } else { // authenticator != 0
    //  Authentication step.
    if (data->GetAuthenticationData() == 0) {
      //  Error.
      delete data;
      delete authenticator; authenticator = 0;
      return false;
    }

    ByteSeq authData;
    if (authenticator->AuthenticationStep(crypto, *(data->GetAuthenticationData()),
        authData, &symmetric) == true) {
      //  Clean up response.
      resp = ByteSeq();
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
            delete authenticator; authenticator = 0;
            if (symmetric != 0) delete symmetric; symmetric = 0;
            return false;
          }
        }
      }
      if (symmetric != 0) {
        //  Successful authentication.
        delete authenticator; authenticator = 0;
        /*  Check if we have pending user queries. If we do, send them. If not,
            then return can process message.
        */
        if (queries.size() > 0) {
          std::map<Bit32T, UserQueryContext>::iterator iter = queries.begin();
          while (iter != queries.end()) {
            ByteSeq tmp;
            if (iter->second.GetMessage().MPEG2Encode(tmp) == false) {
              //  Error. Should we delete symmetric?
//              delete symmetric; symmetric = 0;
              return false;
            }
            resp += tmp;
            iter++;
          }
        } else {
          CanProcessIPMPData canProcess(0, dataID, true);
          ByteSeq canProcessEncoded;
          if (canProcess.MPEG2Encode(canProcessEncoded) == false) {
            //  Error. Should we delete symmetric?
//            delete symmetric; symmetric = 0;
            return false;
          }
          resp += canProcessEncoded;
        }
      }
      //  Perhaps one more check should be applied: if symmetric == 0, then
      //  authData must not be empty. Otherwise it's an authenticator bug.
      return true;
    } else {
      //  Authentication failed.
      delete data;
      delete authenticator;
      return false;
    }
  }
}

/*! \brief  Handle user query response IPMP data.

    \param  sender  input, sender's code.
    \param  data    input, user query response IPMP data.
    \param  resp    output, response message data.

    \warning  Response can be empty, depending on whether any response to this
              message is needed and whether an error occured during the
              processing.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPTool::HandleUserQueryResponseIPMPData(const Bit32T& sender,
    DecoderUserQueryResponseIPMPData* data, ByteSeq& resp) {
  //  First check if the sender is the terminal and that we are instantiated.
  if ((sender != 0) || (identifier == 0)) {
    delete data;
    return false;
  }

  //  First check if we have a waiting user query context.
  if (queries.find(data->GetDataID()) == queries.end()) {
    delete data;
    return false;
  }

  //  Take the rights data out.
  ByteSeq rights = queries[data->GetDataID()].GetRights();

  //  We don't need the waiting context anymore, so we remove it.
  queries.erase(data->GetDataID());
  /*  Now we assume (since it is the only user query we send) that this is
      a response to an openIPMP user query (username, password, XML file name),
      thus we take these parameters out of the response.
  */
  if (data->GetResponses().size() < 3) {
    //  Insufficient number of responses.
    delete data;
    return false;
  }
  std::string user = (std::string)(data->GetResponses()[0].GetPrompt());
  std::string pass = (std::string)(data->GetResponses()[1].GetPrompt());
  std::string xml = (std::string)(data->GetResponses()[2].GetPrompt());

  delete data;

  if ((user == "") || (pass == "") || (xml == "")) {
    return false;
  }

  IXMLDocument* doc = XMLFactory::DecodeDocumentFromFile(xml, toolLogger);
  if (doc == 0) {
    return false;
  }
  IXMLElement* xmlDoc = doc->GetRootElement();
  if (xmlDoc == 0) {
    delete doc;
    return false;
  }
  IXMLElement* elem = xmlDoc->AddChildElement("UserName");
  if (elem == 0) {
    delete doc;
    return false;
  }

  if (elem->SetStrValue(user) == false) {
    delete doc;
    return false;
  }

  elem = xmlDoc->AddChildElement("UserPass");
  if (elem == 0) {
    delete doc;
    return false;
  }

  if (elem->SetStrValue(pass) == false) {
    delete doc;
    return false;
  }

  //  Create decryptor.
  if (decryptor != 0) delete decryptor; decryptor = 0;
  IOpenIPMPDRMDecManager* drmManager =
    OpenIPMPDRMDecManagerFactory::GetOpenIPMPDRMDecManager(xmlDoc, toolLogger);
  if (drmManager == 0) {
    delete doc;
    return false;
  }

  try {
    //  Parse encryption method, content identifier and rights host address.
    OpenIPMPDRMInfo info((ByteT*)(rights.GetFirst()), rights.GetLength(), toolLogger);

    decryptor = drmManager->CreateDecryptor(info, xmlDoc);
    if (decryptor == 0) {
      delete drmManager;
      delete doc;
      return false;
    }
  }
  catch (...) {
    delete drmManager;
    delete doc;
    if (decryptor != 0) delete decryptor; decryptor = 0;
    return false;
  }

  delete drmManager;
  delete doc;

  /*  After setting everything up, send can process message to the terminal.
      This could happen multiple times, but it shouldn't be an error on
      terminal's side.
  */
  CanProcessIPMPData canProcess(0, lastDataID++, true);
  return canProcess.MPEG2Encode(resp);
}

/*! \brief  Process input message and return response in out.

    \warning  This function must be thread safe.
    \warning  Response may be 0, if none was created.

    \param  in          input, input message.
    \param  out         output, response message.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPTool::ProcessMessage(IPMPMessageFromBitstream* in, IPMPMessageFromTool** out) {
  //  Here we should process IPMP stream data update. Todo.
  delete in;
  return true;
}

/*! \brief  Process input message and return response in out.

    \warning  This function must be thread safe.
    \warning  Response may be 0, if none was created.

    \param  in          input, input message.
    \param  out         output, response message.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPTool::ProcessMessage(IPMPDescriptorFromBitstream* in, IPMPMessageFromTool** out) {
  //  First check if the sender is the terminal.
  if (in->GetSender() != 0) {
    delete in;
    return false;
  }

  //  First check if the IPMP descriptor contained is really intended for this
  //  tool (by inspecting tool identifier).
  if (in->GetIPMPDescriptor() == 0) {
    delete in;
    return false;
  }
  if (in->GetIPMPDescriptor()->GetIPMPToolID() != toolID) {
    delete in;
    return false;
  }

  //  If IPMP descriptor has signature container, check signature.
  if (in->GetIPMPDescriptor()->GetSigCertContainer() != 0) {
    //  Do we want to check the signature.
    if (true) {
      ByteSeq ipmpDescEncoded;
      if (in->GetIPMPDescriptor()->MPEG2Encode(ipmpDescEncoded) == false) {
        delete in;
        return false;
      }

      CertPublicVerifierContext verifierCtx(in->GetIPMPDescriptor()->GetSigCertContainer()->GetCertContainers());
      HashCalculator* hasher;
      ByteSeq hash;
      if (verifierCtx.CreateHashCalculator(crypto, &hasher) == false) {
        delete in;
        return false;
      }
      ByteSeq hashed;
      if (hasher->HashData(ipmpDescEncoded, hashed) == false) {
        delete hasher;
        delete in;
        return false;
      }
      delete hasher;

      PublicVerifier* verifier;
      if (verifierCtx.CreatePublicVerifier(crypto, &verifier) == false) {
        delete in;
        return false;
      }
      if (verifier->VerifySignature(in->GetIPMPDescriptor()->GetSigCertContainer()->GetSignature(), hashed)
          == false) {
        delete verifier;
        delete in;
        return false;
      }
      delete verifier;
    }
  }

  //  Get mutex.
  if (mutex->Lock() == false) {
    delete in;
    return false;
  }

  //  Set up instance based on informations contained in IPMP descriptor.
  identifier = in->GetIPMPDescriptor()->GetIPMPDescriptorID();

  //  We simulate message from tool, to be able to process IPMP data with
  //  ProcessMessage().
  IPMPMessageFromTool* resp = 0;
  IPMPMessageFromTool* message = new IPMPMessageFromTool(in->GetVersion(),
    in->GetSender(), in->GetReceiver(), in->GetIPMPDescriptor()->GetIPMPData());

  mutex->Release();

  if (ProcessMessage(message, &resp) == false) {
    //  Some error happened.
    delete in;
    return false;
  }

  //  We shouldn't have received any response, cause we're still not
  //  authenticated and communication with the terminal is not possible.
  //  This means that IPMP descriptor contained some strange IPMP data,
  //  which cannot be processed at this point.
  if (resp != 0) {
    delete resp;
    delete in;
    return false;
  }

  //  Finally we're done.
  delete in;

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
bool OpenIPMPTool::ProcessMessage(const Bit32T& sender, ByteSeq& in, ByteSeq& out) {
  //  Create IPMP data parser, and give the contained messages to it. It will
  //  parse them, and call our handling routines.
  IPMPDataParser parser(toolLogger);
  //  Response created by one of the handling functions.
  return parser.ParseMessage(sender, in, this, out);
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
