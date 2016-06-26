/**	\file IPMPData.h

	IPMP data classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPDATA_H)
#define IPMPDATA_H

#include "BasicTypes.h"
#include <vector>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Exception used for IPMP data error.
*/
class IPMPDataException {
};

/*!	\brief  Base IPMP data.

    IPMP data base class.
*/
class IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  IPMPData(const ByteT& ver, const Bit32T& id): version(ver), dataID(id) {
  }

  virtual ~IPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const = 0;

  /*! \brief  Get version.

      \returns  Version.
  */
  const ByteT& GetVersion() const;

  /*! \brief  Get data identifier.

      Data identifier uniquely identifies the data.

      \returns  Data identifier.
  */
  const Bit32T& GetDataID() const;

protected:
  /*! \brief  Encode as byte array.

      Encode tag, expandable size, version, dataID and class data.

      \param  tag           input, class tag.
      \param  data          input, class data.
      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  bool MPEG2Encode(const ByteT& tag, const ByteSeq& data, ByteSeq& encoded) const;

  ByteT version;
  Bit32T dataID;
};

/*!	\brief  Opaque IPMP data.
*/
class OpaqueIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  data      input, opaque data.
  */
  OpaqueIPMPData(const ByteT& ver, const Bit32T& id, const ByteSeq& data):
    IPMPData(ver, id), opaque(data) {
  }

  virtual ~OpaqueIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get opaque data.

      \returns  Opaque data.
  */
  const ByteSeq& GetOpaqueData() const;

private:
  ByteSeq opaque;
};

/*!	\brief  Audio watermarking init IPMP data.
*/
class AudioWatermarkingInitIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  AudioWatermarkingInitIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~AudioWatermarkingInitIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Video watermarking init IPMP data.
*/
class VideoWatermarkingInitIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  VideoWatermarkingInitIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~VideoWatermarkingInitIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Selective decryption init IPMP data.
*/
class SelectiveDecryptionInitIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  SelectiveDecryptionInitIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~SelectiveDecryptionInitIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Key IPMP data.
*/
class KeyIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  KeyIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~KeyIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Send audio watermark IPMP data.
*/
class SendAudioWatermarkIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  SendAudioWatermarkIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~SendAudioWatermarkIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Send video watermark IPMP data.
*/
class SendVideoWatermarkIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  SendVideoWatermarkIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~SendVideoWatermarkIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Rights IPMP data.
*/
class RightsIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  right     input, rights data.
  */
  RightsIPMPData(const ByteT& ver, const Bit32T& id, const ByteSeq& right):
    IPMPData(ver, id), rights(right) {
  }

  virtual ~RightsIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get rights info.

      \returns  Rights info.
  */
  const ByteSeq& GetRightsInfo() const;

private:
  ByteSeq rights;
};

/*!	\brief  Add tool notification listener IPMP data.
*/
class AddToolNotificationListenerIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  AddToolNotificationListenerIPMPData(const ByteT& ver, const Bit32T& id):
    IPMPData(ver, id) {
  }

  virtual ~AddToolNotificationListenerIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Remove tool notification listener IPMP data.
*/
class RemoveToolNotificationListenerIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  RemoveToolNotificationListenerIPMPData(const ByteT& ver, const Bit32T& id):
    IPMPData(ver, id) {
  }

  virtual ~RemoveToolNotificationListenerIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Tool param capabilities query IPMP data.
*/
class ToolParamCapabilitiesQueryIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  ToolParamCapabilitiesQueryIPMPData(const ByteT& ver, const Bit32T& id):
    IPMPData(ver, id) {
  }

  virtual ~ToolParamCapabilitiesQueryIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Tool param capabilities response IPMP data.
*/
class ToolParamCapabilitiesResponseIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  ToolParamCapabilitiesResponseIPMPData(const ByteT& ver, const Bit32T& id):
    IPMPData(ver, id) {
  }

  virtual ~ToolParamCapabilitiesResponseIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Get tools IPMP data.
*/
class GetToolsIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  GetToolsIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~GetToolsIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Get tools response IPMP data.
*/
class GetToolsResponseIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  GetToolsResponseIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~GetToolsResponseIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Connect tool IPMP data.
*/
class ConnectToolIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  ConnectToolIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~ConnectToolIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Disconnect tool IPMP data.
*/
class DisconnectToolIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  DisconnectToolIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~DisconnectToolIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Notify tool event IPMP data.
*/
class NotifyToolEventIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
  */
  NotifyToolEventIPMPData(const ByteT& ver, const Bit32T& id): IPMPData(ver, id) {
  }

  virtual ~NotifyToolEventIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;
};

/*!	\brief  Can process IPMP data.
*/
class CanProcessIPMPData: public IPMPData {
public:
  /*! \brief  Constructor.
      
      \param  ver       input, version.
      \param  id        input, data identifier.
      \param  process   input, can process flag.
  */
  CanProcessIPMPData(const ByteT& ver, const Bit32T& id, const bool& process):
   IPMPData(ver, id), canProcess(process) {
  }

  virtual ~CanProcessIPMPData() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get can process flag.

      \returns  Can process flag.
  */
  const bool GetCanProcessFlag() const;

private:
  bool canProcess;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IPMPDATA_H)
