/**	\file IPMPData.cpp

	IPMP data classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "IPMPData.h"

#include "BasicTypes.h"
#include <vector>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!	\brief  Base IPMP data.

    IPMP data base class.
*/
/*! \brief  Get version.

    \returns  Version.
*/
const ByteT& IPMPData::GetVersion() const {
  return version;
}

/*! \brief  Get data identifier.

    Data identifier uniquely identifies the data.

    \returns  Data identifier.
*/
const Bit32T& IPMPData::GetDataID() const {
  return dataID;
}

/*! \brief  Encode as byte array.

    Encode tag, expandable size, version, dataID and class data.

    \param  tag           input, class tag.
    \param  data          input, class data.
    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool IPMPData::MPEG2Encode(const ByteT& tag, const ByteSeq& data, ByteSeq&
    encoded) const {
  if ((data.GetLength() + 5) >= (1 << 28)) {
    return false;
  }
  ByteSeq tmp = ByteSeq(GetVersion()) + ByteSeq(GetDataID()) + data;
  encoded = ByteSeq(tag) + tmp.MPEG2Encode();
  return true;
}

/*!	\brief  Opaque IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool OpaqueIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x01, opaque.MPEG2Encode(), encoded);
}

/*! \brief  Get opaque data.

    \returns  Opaque data.
*/
const ByteSeq& OpaqueIPMPData::GetOpaqueData() const {
  return opaque;
}

/*!	\brief  Audio watermarking init IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool AudioWatermarkingInitIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x02, enc, encoded);
}

/*!	\brief  Video watermarking init IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool VideoWatermarkingInitIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x03, enc, encoded);
}

/*!	\brief  Selective decryption init IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool SelectiveDecryptionInitIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x04, enc, encoded);
}

/*!	\brief  Key IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool KeyIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x05, enc, encoded);
}

/*!	\brief  Send audio watermark IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool SendAudioWatermarkIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x06, enc, encoded);
}

/*!	\brief  Send video watermark IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool SendVideoWatermarkIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x07, enc, encoded);
}

/*!	\brief  Rights IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool RightsIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPData::MPEG2Encode(0x08, rights.MPEG2Encode(), encoded);
}

/*! \brief  Get rights info.

    \returns  Rights info.
*/
const ByteSeq& RightsIPMPData::GetRightsInfo() const {
  return rights;
}

/*!	\brief  Add tool notification listener IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool AddToolNotificationListenerIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x0a, enc, encoded);
}

/*!	\brief  Remove tool notification listener IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool RemoveToolNotificationListenerIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x0b, enc, encoded);
}

/*!	\brief  Tool param capabilities query IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool ToolParamCapabilitiesQueryIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x10, enc, encoded);
}

/*!	\brief  Tool param capabilities response IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool ToolParamCapabilitiesResponseIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x11, enc, encoded);
}

/*!	\brief  Get tools IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool GetToolsIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x12, enc, encoded);
}

/*!	\brief  Get tools response IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool GetToolsResponseIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x13, enc, encoded);
}

/*!	\brief  Connect tool IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool ConnectToolIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x14, enc, encoded);
}

/*!	\brief  Disconnect tool IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool DisconnectToolIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x15, enc, encoded);
}

/*!	\brief  Notify tool event IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool NotifyToolEventIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc;
  return IPMPData::MPEG2Encode(0x16, enc, encoded);
}

/*!	\brief  Can process IPMP data.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool CanProcessIPMPData::MPEG2Encode(ByteSeq& encoded) const {
  ByteSeq enc((ByteT)((canProcess == true)? (0x80): (0x00)));
  return IPMPData::MPEG2Encode(0x17, enc, encoded);
}

/*! \brief  Get can process flag.

    \returns  Can process flag.
*/
const bool CanProcessIPMPData::GetCanProcessFlag() const {
  return canProcess;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
