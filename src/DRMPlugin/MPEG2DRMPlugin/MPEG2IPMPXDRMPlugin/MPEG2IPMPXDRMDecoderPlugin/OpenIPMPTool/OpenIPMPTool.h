/**	\file OpenIPMPTool.h

	OpenIPMP MPEG2 IPMP tool.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPTOOL_H)
#define OPENIPMPTOOL_H

/* disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

#include "IPMPAgent.h"
#include "MessageRouter.h"
#include "IPMPMessage.h"
#include "IPMPData.h"
#include <string>
#include "DRMLogger.h"
#include "IOpenIPMPDRMDecryptor.h"
#include "IThreadSync.h"

#if defined (WIN32)
#if defined OPENIPMPTOOL_EXPORTS
#define OPENIPMPTOOL_EXPORT __declspec(dllexport)
#else
#define OPENIPMPTOOL_EXPORT __declspec(dllimport)
#endif // OPENIPMPTOOL_EXPORTS
#elif defined (LINUX)
#define OPENIPMPTOOL_EXPORT
#else
#define OPENIPMPTOOL_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Waiting openIPMP user query context.

    User query context waiting user query response.
    If user query message is != 0, it means that at the time of creation
    of user query message, tool was still not authenticated. In this case,
    user query message should be sent immediately after authentication is
    done.
    When user query response is received, handling function should then
    process (if any) waiting user query context.
*/
class UserQueryContext {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  UserQueryContext(): rights(), message() {
  }

  /*! \brief  Constructor.

      \param  rig       rights data.
      \param  mess      user query message.
  */
  UserQueryContext(const ByteSeq& rig, const DecoderUserQueryIPMPData& mess):
    rights(rig), message(mess) {
  }

  /*! \brief  Copy constructor.

      \param  rhs       user query context.
  */
  UserQueryContext(const UserQueryContext& rhs): rights(rhs.rights),
    message(rhs.message) {
  }

  ~UserQueryContext() {
  }

  /*! \brief  Get rights data.

      \returns  Rights data.
  */
  const ByteSeq& GetRights() const {
    return rights;
  }

  /*! \brief  Get query message.

      \returns  Query message.
  */
  const DecoderUserQueryIPMPData& GetMessage() const {
    return message;
  }

private:
  ByteSeq rights;
  DecoderUserQueryIPMPData message;
};

/*! \brief  OpenIPMP tool for protection of MPEG2 data.
*/
class OpenIPMPTool: public IPMPTool {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.

      In case of an error, throws ToolException.
  */
  OPENIPMPTOOL_EXPORT OpenIPMPTool(DRMLogger& logger);

  virtual ~OpenIPMPTool();

  /*! \brief  Process input message and return response in out.

      \warning  This function must be thread safe.
      \warning  Response may be 0, if none was created.

      \param  in          input, input message.
      \param  out         output, response message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ProcessMessage(IPMPMessageFromTool* in, IPMPMessageFromTool** out);

  /*! \brief  IPMP agent identifier.

      Identifier 0 represents IPMP terminal, others represent IPMP descriptor
      identifiers of IPMP tools' logical instances.

      \returns  Identifier.
  */
  virtual const Bit32T& IPMPIdentifier() const;

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
    ByteSeq& resp);

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
    ByteSeq& resp);

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
    SecureContainerIPMPData* data, ByteSeq& resp);

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
    InitAuthenticationIPMPData* data, ByteSeq& resp);

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
    MutualAuthenticationIPMPData* data, ByteSeq& resp);

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
      DecoderUserQueryResponseIPMPData* data, ByteSeq& resp);

  /*! \brief  Process input message and return response in out.

      \warning  This function must be thread safe.
      \warning  Response may be 0, if none was created.

      \param  in          input, input message.
      \param  out         output, response message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ProcessMessage(IPMPMessageFromBitstream* in, IPMPMessageFromTool** out);

  /*! \brief  Process input message and return response in out.

      \warning  This function must be thread safe.
      \warning  Response may be 0, if none was created.

      \param  in          input, input message.
      \param  out         output, response message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool ProcessMessage(IPMPDescriptorFromBitstream* in, IPMPMessageFromTool** out);

  /*! \brief  Process (one) input message and return response.

      \warning  This function must be thread safe.
      \warning  Response may be empty, if none was created.
      \warning  Input message data is modified.

      \param  sender      input, sender's code.
      \param  in          input, input message data.
      \param  out         output, response message data.

      \returns  Boolean indicating success or failure.
  */
  bool ProcessMessage(const Bit32T& sender, ByteSeq& in, ByteSeq& out);

private:
  //! Tool identifier.
  Bit128T toolID;
  //! Instance identifier.
  Bit32T identifier;
  //! Mutex for protecting access to members.
  IMutex* mutex;
  //! Message router.
  MessageRouter* router;
  //! Authenticator (after negotiaion, until authentication is done).
  Authenticator* authenticator;
  //! Symmetric operator (after authentication is done).
  SymmetricOperator* symmetric;
  //! Private authentication context.
  PrivateAuthContext* context;
  //! Crypto provider.
  CryptoProvider* crypto;
  /*! Last posted message data identifier. It is increased for every new
      message that is to be sent. Responses use the request message data
      identifiers, thus they need not change the last message data
      identifier.
  */
  Bit32T lastDataID;
  //! Decryptor used for decrypting MPEG2 stream data.
  IOpenIPMPDRMDecryptor* decryptor;
  //! OpenIPMP user query messages, waiting for user query response.
  std::map<Bit32T, UserQueryContext> queries;

  DRMLogger& toolLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (OPENIPMPTOOL_H)
