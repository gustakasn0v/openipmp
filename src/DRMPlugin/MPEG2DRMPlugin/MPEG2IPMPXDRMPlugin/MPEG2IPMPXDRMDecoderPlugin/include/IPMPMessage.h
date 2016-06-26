/**	\file IPMPMessage.h

	IPMP messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPMESSAGE_H)
#define IPMPMESSAGE_H

#include "BasicTypes.h"
#include <vector>
#include "IIPMPStreamDataUpdate.h"
#include "IIPMPDescriptor.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP tool message.

    Base for all messages used between IPMP tools and IPMP terminal
*/
class IPMPToolMessage {
public:
  /*! \brief  Constructor.

      \param  ver       message version.
      \param  send      sender's identifier.
      \param  receive   receiver's identifier.
  */
  IPMPToolMessage(const ByteT& ver, const Bit32T& send, const Bit32T& receive):
    version(ver), sender(send), receiver(receive) {
  }

  virtual ~IPMPToolMessage() {
  }

  /*! \brief  Get version.

      \returns Version.
  */
  const ByteT& GetVersion() const {
    return version;
  }

  /*! \brief  Get sender.

      \returns Sender.
  */
  const Bit32T& GetSender() const {
    return sender;
  }

  /*! \brief  Get receiver.

      \returns Receiver.
  */
  const Bit32T& GetReceiver() const {
    return receiver;
  }

protected:
  ByteT version;
  Bit32T sender;
  Bit32T receiver;
};

/*! \brief  IPMP message from bitstream (IPMP stream).
*/
class IPMPMessageFromBitstream: public IPMPToolMessage {
public:
  /*! \brief  Constructor.

      \param  ver       message version.
      \param  send      sender's identifier.
      \param  receive   receiver's identifier.
      \param  upd       update messages.
  */
  IPMPMessageFromBitstream(const ByteT& ver, const Bit32T& send, const Bit32T&
    receive, const std::vector<IIPMPStreamDataUpdate*>& upd): IPMPToolMessage(ver,
    send, receive), updates(upd) {
  }

  virtual ~IPMPMessageFromBitstream() {
    std::vector<IIPMPStreamDataUpdate*>::iterator iter = updates.begin();
    while (iter != updates.end()) {
      delete (*iter);
      iter++;
    }
    updates.clear();
  }

  /*! \brief  Get IPMP stream data updates.

      \returns IPMP stream data updates.
  */
  const std::vector<IIPMPStreamDataUpdate*>& GetIPMPStreamDataUpdates() const {
    return updates;
  }

private:
  std::vector<IIPMPStreamDataUpdate*> updates;
};

/*! \brief  IPMP descriptor from bitstream.
*/
class IPMPDescriptorFromBitstream: public IPMPToolMessage {
public:
  /*! \brief  Constructor.

      \param  ver       message version.
      \param  send      sender's identifier.
      \param  receive   receiver's identifier.
      \param  desc      IPMP descriptor (must be != 0).
  */
  IPMPDescriptorFromBitstream(const ByteT& ver, const Bit32T& send, const Bit32T&
    receive, IIPMPDescriptor* desc): IPMPToolMessage(ver, send, receive),
    descriptor(desc) {
  }

  virtual ~IPMPDescriptorFromBitstream() {
    if (descriptor != 0) delete descriptor;
  }

  /*! \brief  Get IPMP descriptor.

      \returns IPMP descriptor.
  */
  const IIPMPDescriptor* GetIPMPDescriptor() const {
    return descriptor;
  }

private:
  IIPMPDescriptor* descriptor;
};

/*! \brief  IPMP message from tool (or terminal).
*/
class IPMPMessageFromTool: public IPMPToolMessage {
public:
  /*! \brief  Constructor.

      \param  ver       message version.
      \param  send      sender's identifier.
      \param  receive   receiver's identifier.
      \param  mess      IPMP messages.
  */
  IPMPMessageFromTool(const ByteT& ver, const Bit32T& send, const Bit32T&
    receive, const ByteSeq& mess): IPMPToolMessage(ver, send, receive),
    messages(mess) {
  }

  virtual ~IPMPMessageFromTool() {
  }

  /*! \brief  Get messages.

      Messages contained are encoded IPMPData.

      \returns messages.
  */
  const ByteSeq& GetMessages() const {
    return messages;
  }

private:
  ByteSeq messages;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (IPMPMESSAGE_H)
