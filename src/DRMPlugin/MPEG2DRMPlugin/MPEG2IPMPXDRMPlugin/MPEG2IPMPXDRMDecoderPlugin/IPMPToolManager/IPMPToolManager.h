/**	\file IPMPToolManager.h

	IPMP tool manager.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPTOOLMANAGER_H)
#define IPMPTOOLMANAGER_H

/* disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

#include "BasicTypes.h"
#include "IIPMPControlInfoPart.h"
#include "IPMPData.h"
#include "IPMPMessage.h"
#include "IPMPAgent.h"
#include "MessageRouter.h"
#include "DRMLogger.h"
#include "IIPMPTerminal.h"

#include "IThreadSync.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP tool context.

    Temporary tool context, before authentication is done.
*/
class IPMPToolContext {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  IPMPToolContext(): toolID(), instanceID(), control() {
  }

  /*! \brief  Constructor.

      \param  tool        tool identifier.
      \param  instance    tool instance identifier (IPMP descriptor identifier
                          that initiated instantiation of a tool).
      \param  point       control point.
      \param  seq         sequence code (where in a sequence of tools residing
                          at a control point should this one be put).
  */
  IPMPToolContext(const Bit128T& tool, const Bit32T& instance, const ByteT& point,
    const ByteT& seq): toolID(tool), instanceID(instance), control(point),
    sequence(seq) {
  }

  /*! \brief  Copy constructor.

      \param  rhs         IPMP tool context.
  */
  IPMPToolContext(const IPMPToolContext& rhs): toolID(rhs.toolID),
    instanceID(rhs.instanceID), control(rhs.control), sequence(rhs.sequence) {
  }

  virtual ~IPMPToolContext() {
  }

  /*! \brief  Get tool identifier.

      \returns  Tool identifier.
  */
  const Bit128T& GetToolIdentifier() const;

  /*! \brief  Get instance identifier.

      \returns  Instance identifier.
  */
  const Bit32T& GetInstanceIdentifier() const;

  /*! \brief  Get control point.

      \returns  Control point.
  */
  const ByteT& GetControlPoint() const;

  /*! \brief  Get sequence code.

      \returns  Sequence code.
  */
  const ByteT& GetSequenceCode() const;

protected:
  Bit128T toolID;
  Bit32T instanceID;
  ByteT control;
  ByteT sequence;
};

/*! \brief  Ready IPMP tool context.

    After a tool is instantiated, this context is used for further
    communication with a tool.
*/
class ReadyIPMPToolContext: public IPMPToolContext {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  ReadyIPMPToolContext(): IPMPToolContext(), oper(0) {
  }

  /*! \brief  Constructor.

      \param  tool        tool identifier.
      \param  instance    tool instance identifier (IPMP descriptor identifier
                          that initiated instantiation of a tool).
      \param  point       control point.
      \param  seq         sequence code (where in a sequence of tools residing
                          at a control point should this one be put).
      \param  op          symmetric operator used for encrypting/decrypting.
  */
  ReadyIPMPToolContext(const Bit128T& tool, const Bit32T& instance,
    const ByteT& point, const ByteT& seq, SymmetricOperator* op):
    IPMPToolContext(tool, instance, point, seq), oper(op) {
  }

  /*! \brief  Copy constructor.

      \param  rhs         ready IPMP tool context.
  */
  ReadyIPMPToolContext(const ReadyIPMPToolContext& rhs):
      IPMPToolContext(rhs.toolID, rhs.instanceID, rhs.control, rhs.sequence),
      oper(0) {
    if (rhs.oper != 0) oper = rhs.oper->Copy();
  }

  virtual ~ReadyIPMPToolContext() {
    if (oper != 0) delete oper; oper = 0;
  }

  /*! \brief  Get symmetric operator.

      \returns  Symmetric operator.
  */
  SymmetricOperator* GetOperator() const;

  /*! \brief  Assignment operator.

      \param  rhs         input, ready IPMP tool context.
  */
  ReadyIPMPToolContext& operator = (const ReadyIPMPToolContext& rhs) {
    toolID = rhs.toolID;
    instanceID = rhs.instanceID;
    control = rhs.control;
    sequence = rhs.sequence;
    if (oper != 0) delete oper;
    oper = rhs.oper->Copy();
    return (*this);
  }

private:
  SymmetricOperator* oper;
};

/*! \brief  Waiting context for processing stream data.

    Context of sent process stream data messages, kept in tool manager.
*/
class DataWaitContext {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  DataWaitContext(): event(0), data(), receiver(0) {
  }

  /*! \brief  Constructor.

      \param  ev        event handler.
      \param  dat       data.
      \param  rec       receiver's identifier.
  */
  DataWaitContext(IEvent* ev, const ByteSeq& dat, const Bit32T& rec):
    event(ev), data(dat), receiver(rec) {
  }

  ~DataWaitContext() {
    if (event != 0) delete event;
  }

  /*! \brief  Get event handler.

      \returns Event handler.
  */
  IEvent* GetEvent() const {
    return event;
  }

  /*! \brief  Get data.

      \returns Data.
  */
  const ByteSeq& GetData() const {
    return data;
  }

  /*! \brief  Set data.

      \param  d     input, data to be set.
  */
  void SetData(const ByteSeq& d) {
    data = d;
  }

  /*! \brief  Get receiver's identifier.

      \returns Receiver's identifier.
  */
  const Bit32T& GetReceiver() const {
    return receiver;
  }

private:
  IEvent* event;
  ByteSeq data;
  Bit32T receiver;
};

/*! \brief  Waiting context for authentication.

    Context kept in tool manager until authentication is done (successfuly or not).
*/
class AuthWaitContext {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  AuthWaitContext(): event(0), success(false), receiver(0), authenticator(0) {
  }

  /*! \brief  Constructor.

      \param  ev        event handler.
      \param  succ      success indicator.
      \param  rec       receiver's identifier.
      \param  auth      authenticator.
  */
  AuthWaitContext(IEvent* ev, const bool& succ, const Bit32T& rec,
    Authenticator* auth): event(ev), success(succ), receiver(rec),
    authenticator(auth) {
  }

  ~AuthWaitContext() {
    if (event != 0) delete event;
    if (authenticator != 0) delete authenticator; authenticator = 0;
  }

  /*! \brief  Get event handler.

      \returns Event handler.
  */
  IEvent* GetEvent() const {
    return event;
  }

  /*! \brief  Get success indicator.

      \returns Success indicator.
  */
  const bool& GetSuccess() const {
    return success;
  }

  /*! \brief  Set success indicator.

      \param  succ      input, success indicator to be set.
  */
  void SetSuccess(const bool& succ) {
    success = succ;
  }

  /*! \brief  Get receiver's identifier.

      \returns Receiver's identifier.
  */
  const Bit32T& GetReceiver() const {
    return receiver;
  }

  /*! \brief  Get authenticator.

      \returns Authenticator.
  */
  Authenticator* GetAuthenticator() {
    return authenticator;
  }

  /*! \brief  Set authenticator.

      \param  auth    input, authenticator to be set.
  */
  void SetAuthenticator(Authenticator* auth) {
    if (authenticator != 0) delete authenticator;
    authenticator = auth;
  }

private:
  IEvent* event;
  bool success;
  Bit32T receiver;
  Authenticator* authenticator;
};

/*! \brief  Waiting context for IPMP stream data update.

    Context kept in tool manager until IPMP stream data update is done
    (successfuly or not).
*/
class UpdateWaitContext {
public:
  /*! \brief  Dummy constructor. SHOULD NOT BE USED.
  
      Needed cause std::map needs default constructor.
  */
  UpdateWaitContext(): event(0), success(false), receiver(0) {
  }

  /*! \brief  Constructor.

      \param  ev        event handler.
      \param  succ      success indicator.
      \param  rec       receiver's identifier.
  */
  UpdateWaitContext(IEvent* ev, const bool& succ, const Bit32T& rec):
    event(ev), success(succ), receiver(rec) {
  }

  ~UpdateWaitContext() {
    if (event != 0) delete event;
  }

  /*! \brief  Get event handler.

      \returns Event handler.
  */
  IEvent* GetEvent() const {
    return event;
  }

  /*! \brief  Get success indicator.

      \returns Success indicator.
  */
  const bool& GetSuccess() const {
    return success;
  }

  /*! \brief  Set success indicator.

      \param  succ      input, success indicator to be set.
  */
  void SetSuccess(const bool& succ) {
    success = succ;
  }

  /*! \brief  Get receiver's identifier.

      \returns Receiver's identifier.
  */
  const Bit32T& GetReceiver() const {
    return receiver;
  }

private:
  IEvent* event;
  bool success;
  Bit32T receiver;
};

/*! \brief  IPMP tool manager exception.
*/
class IPMPToolManagerException {
};

/*! \brief  IPMP tool manager.

    IPMP tool manager within a terminal.
*/
class IPMPToolManager: public IPMPAgent {
public:
  /*! \brief  Constructor.

      \param  term        IPMP terminal, used for communication with user
                          (must be != 0).
      \param  logger      message logger.

      In case of an error, throws IPMPToolManagerException.
  */     
  IPMPToolManager(IIPMPTerminal* term, DRMLogger& logger);

  /*! \brief  Destructor.

      In case of an error, throws IPMPToolManagerException.
  */     
  virtual ~IPMPToolManager();

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
    ByteSeq& resp);

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
    data, ByteSeq& resp);

  /*! \brief  Process last IPMP control info part (transport stream).

      \param  in          input, last IPMP control info part (transport stream).

      \returns  Boolean indicating success or failure.
  */
  bool ProcessLastTStreamIPMPControlInfoPart(ILastTStreamIPMPControlInfoPart* in);

  /*! \brief  Process intermediate IPMP control info part (transport stream).

      \param  in          input, intermediate IPMP control info part (transport stream).

      \returns  Boolean indicating success or failure.
  */
  bool ProcessInterTStreamIPMPControlInfoPart(IInterTStreamIPMPControlInfoPart* in);

  /*! \brief  Process last IPMP control info part (program stream).

      \param  in          input, last IPMP control info part (program stream).

      \returns  Boolean indicating success or failure.
  */
  bool ProcessLastPStreamIPMPControlInfoPart(ILastPStreamIPMPControlInfoPart* in);

  /*! \brief  Process intermediate IPMP control info part (program stream).

      \param  in          input, intermediate IPMP control info part (program stream).

      \returns  Boolean indicating success or failure.
  */
  bool ProcessInterPStreamIPMPControlInfoPart(IInterPStreamIPMPControlInfoPart* in);

  /*! \brief  Process IPMP descriptor.

      \warning  This function must be thread safe.

      \param  in          input, IPMP descriptor.

      \returns  Boolean indicating success or failure.
  */
  bool ProcessIPMPDescriptor(IIPMPDescriptor* in);

  /*! \brief  Process IPMP stream data update.

      \warning  This function must be thread safe.

      \param  in          input, IPMP stream data update.

      \returns  Boolean indicating success or failure.
  */
  bool ProcessIPMPStreamDataUpdate(IIPMPStreamDataUpdate* in);

  /*! \brief  Process stream data.

      \param  cPoint      input, control point code.
      \param  in          input, data to be processed.
      \param  out         output, processed data.

      \returns  Boolean indicating success or failure.
  */
  bool ProcessData(const ByteT& cPoint, const ByteSeq& in, ByteSeq& out);

protected:
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
  /*! \brief  Check if tool is created.

      \param  id        input, tool identifier.

      \returns  Boolean indicating whether tool is created.
  */
  bool IsCreated(const Bit128T& id);

  /*! \brief  Check if tool is instantiated.

      \param  id        input, tool's instance identifier.

      \returns  Boolean indicating whether tool is instantiated.
  */
  bool IsInstantiated(const Bit32T& id);

  /*! \brief  Check if tool is authenticated.

      \param  id        input, tool's instance identifier.

      \returns  Boolean indicating whether tool is authenticated.
  */
  bool IsAuthenticated(const Bit32T& id);

  /*! \brief  Check if tool is authenticated and ready for processing.

      \param  id        input, tool's instance identifier.

      \returns  Boolean indicating whether tool is authenticated and
                ready for processing.
  */
  bool IsReady(const Bit32T& id);

  //! Tool manager's identifier (0).
  Bit32T identifier;
  //! Mutex for protecting access to members.
  IMutex* mutex;
  /*! Created tools.
      Map is from tool identifier to tool pointer.
  */
  std::map<Bit128T, IPMPTool*> created;
  /*! Instantiated tools.
      Map is from instance identifier to tool context.
  */
  std::map<Bit32T, IPMPToolContext> instantiated;
  /*! Instantiated and authenticated tools.
      Map is from instance identifier to tool context.
  */
  std::map<Bit32T, ReadyIPMPToolContext> authenticated;
  /*! Instantiated and authenticated tools, ready for processing
      (can process message has been received).
      Map is from control point to tool contexts of all tools residing at
      that control point (sorted by sequence codes).
  */
  std::map<ByteT, std::vector<ReadyIPMPToolContext> > ready;
  //! Message router.
  MessageRouter* router;
  //! Crypto provider.
  CryptoProvider* crypto;
  //! Tool manager's crypto context.
  PrivateAuthContext* context;
  /*! Last posted message data identifier. It is increased for every new
      message that is to be sent. Responses use the request message data
      identifiers, thus they need not change the last message data
      identifier.
  */
  Bit32T lastDataID;
  //! Stop indicator for all waiters.
  bool stop;
  /*! Waiting events for stream data process messages.
      Map is from data identifier of a message to waiting context.
      When ProcessData() is called, a message exchange follows, which is not
      under control of ProcessData(). That is why it has to wait until message
      exchange results in delivery of required data, upon which the event
      is signaled.
  */
  std::map<Bit32T, DataWaitContext*> dataWait;
  std::map<Bit32T, IEvent*> dataExit;
  /*! Waiting events for authentication messages.
      Map is from data identifier of a message to waiting context.
      When ProcessIPMPDescriptor() is called, a message exchange follows, which
      is not under control of ProcessIPMPDescriptor(). That is why it has to
      wait until message exchange results in successful (or unsuccessful)
      authentication, upon which the event is signaled.
  */
  std::map<Bit32T, AuthWaitContext*> authWait;
  std::map<Bit32T, IEvent*> authExit;
  /*! Waiting events for IPMP stream data update messages.
      Map is from data identifier of a message to waiting context.
      When ProcessIPMPStreamDataUpdate() is called, a message exchange follows,
      which is not under control of ProcessIPMPStreamDataUpdate(). That is why
      it has to wait until message exchange results in successful (or unsuccessful)
      update, upon which the event is signaled.
  */
  std::map<Bit32T, UpdateWaitContext*> updateWait;
  std::map<Bit32T, IEvent*> updateExit;
  /*! Control info data in process of assembling.
      Vector contains pairs of (control info part number, data).
  */
  std::vector<std::pair<ByteT, ByteSeq> > controlInfoParts;
  //! IPMP terminal, used for communication with user.
  IIPMPTerminal* terminal;

  DRMLogger& managerLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IPMPTOOLMANAGER_H)
