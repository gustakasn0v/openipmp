/**	\file IPMPAgent.h

	IPMP agent. Entity participating in IPMP communication.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPAGENT_H)
#define IPMPAGENT_H

#include "BasicTypes.h"
#include <vector>
#include <string>
#include "IPMPData.h"
#include "SecureContainerData.h"
#include "AuthenticationData.h"
#include "DecoderIPMPUserQuery.h"
#include "IPMPMessage.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP agent.

    Agent that participates in communication via IPMP messages. Eg. IPMP
    tool manager (terminal), IPMP tool.
*/
class IPMPAgent {
public:
  virtual ~IPMPAgent() {
  }

  /*! \brief  Process input message and return response in out.

      \warning  This function must be thread safe.
      \warning  Response may be 0, if none was created.

      \param  in          input, input message.
      \param  out         output, response message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ProcessMessage(IPMPMessageFromTool* in, IPMPMessageFromTool** out) = 0;

  /*! \brief  IPMP agent identifier.

      Identifier 0 represents IPMP terminal, others represent IPMP descriptor
      identifiers of IPMP tools' logical instances.

      \returns  Identifier.
  */
  virtual const Bit32T& IPMPIdentifier() const = 0;

  /*! \brief  Handle opaque IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, opaque IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleOpaqueIPMPData(const Bit32T& sender, OpaqueIPMPData* data,
      ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle audio watermarking init IPMP data

      \param  sender  input, sender's code.
      \param  data    input, audio watermarking init IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleAudioWatermarkingInitIPMPData(const Bit32T& sender,
      AudioWatermarkingInitIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle video watermarking init IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, video watermarking init IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleVideoWatermarkingInitIPMPData(const Bit32T& sender,
      VideoWatermarkingInitIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle selective decryption init IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, selective decryption init IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleSelectiveDecryptionInitIPMPData(const Bit32T& sender,
      SelectiveDecryptionInitIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle key IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, key IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleKeyIPMPData(const Bit32T& sender, KeyIPMPData* data,
      ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle send audio watermark IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, send audio watermark IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleSendAudioWatermarkIPMPData(const Bit32T& sender,
      SendAudioWatermarkIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle send video watermark IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, send video watermark IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleSendVideoWatermarkIPMPData(const Bit32T& sender,
      SendVideoWatermarkIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
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
  virtual bool HandleRightsIPMPData(const Bit32T& sender, RightsIPMPData* data,
      ByteSeq& resp) {
    delete data;
    return false;
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
  virtual bool HandleSecureContainerIPMPData(const Bit32T& sender,
      SecureContainerIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle add tool notification listener IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, add tool notification listener IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleAddToolNotificationListenerIPMPData(const Bit32T& sender,
      AddToolNotificationListenerIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle remove tool notification listener IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, remove tool notification listener IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleRemoveToolNotificationListenerIPMPData(const Bit32T& sender,
      RemoveToolNotificationListenerIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
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
  virtual bool HandleInitAuthenticationIPMPData(const Bit32T& sender,
      InitAuthenticationIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
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
  virtual bool HandleMutualAuthenticationIPMPData(const Bit32T& sender,
      MutualAuthenticationIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
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
  virtual bool HandleUserQueryIPMPData(const Bit32T& sender, DecoderUserQueryIPMPData*
      data, ByteSeq& resp) {
    delete data;
    return false;
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
  virtual bool HandleUserQueryResponseIPMPData(const Bit32T& sender,
      DecoderUserQueryResponseIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle tool param capabilities query IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, tool param capabilities query IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleToolParamCapabilitiesQueryIPMPData(const Bit32T& sender,
      ToolParamCapabilitiesQueryIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle tool param capabilities response IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, tool param capabilities response IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleToolParamCapabilitiesResponseIPMPData(const Bit32T& sender,
      ToolParamCapabilitiesResponseIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle get tools IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, get tools IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleGetToolsIPMPData(const Bit32T& sender, GetToolsIPMPData* data,
      ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle get tools response IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, get tools response IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleGetToolsResponseIPMPData(const Bit32T& sender,
      GetToolsResponseIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle connect tool IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, connect tool IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleConnectToolIPMPData(const Bit32T& sender, ConnectToolIPMPData* data,
      ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle disconnect tool IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, disconnect tool IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleDisconnectToolIPMPData(const Bit32T& sender,
      DisconnectToolIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle notify tool event IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, notify tool event IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleNotifyToolEventIPMPData(const Bit32T& sender,
      NotifyToolEventIPMPData* data, ByteSeq& resp) {
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
  virtual bool HandleCanProcessIPMPData(const Bit32T& sender, CanProcessIPMPData* data,
      ByteSeq& resp) {
    delete data;
    return false;
  }

  /*! \brief  Handle trust security metadata IPMP data.

      \param  sender  input, sender's code.
      \param  data    input, trust security metadata IPMP data.
      \param  resp    output, response message data.

      \warning  Response can be empty, depending on whether any response to this
                message is needed and whether an error occured during the
                processing.

      \returns  Boolean indicating success or failure.
  */
  virtual bool HandleTrustSecurityMetadataIPMPData(const Bit32T& sender,
      TrustSecurityMetadataIPMPData* data, ByteSeq& resp) {
    delete data;
    return false;
  }
};

/*! \brief  Tool exception.
*/
class ToolException {
};

/*! \brief  IPMP tool.

    Tool that provides IPMP protection.
*/
class IPMPTool: public IPMPAgent {
public:
  virtual ~IPMPTool() {}

  /*! \brief  Process input message and return response in out.

      \warning  This function must be thread safe.
      \warning  Response may be 0, if none was created.

      \param  in          input, input message.
      \param  out         output, response message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ProcessMessage(IPMPMessageFromTool* in, IPMPMessageFromTool** out) = 0;

  /*! \brief  Process input message and return response in out.

      \warning  This function must be thread safe.
      \warning  Response may be 0, if none was created.

      \param  in          input, input message.
      \param  out         output, response message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ProcessMessage(IPMPMessageFromBitstream* in, IPMPMessageFromTool** out) = 0;

  /*! \brief  Process input message and return response in out.

      \warning  This function must be thread safe.
      \warning  Response may be 0, if none was created.

      \param  in          input, input message.
      \param  out         output, response message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ProcessMessage(IPMPDescriptorFromBitstream* in, IPMPMessageFromTool** out) = 0;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IPMPAGENT_H)
