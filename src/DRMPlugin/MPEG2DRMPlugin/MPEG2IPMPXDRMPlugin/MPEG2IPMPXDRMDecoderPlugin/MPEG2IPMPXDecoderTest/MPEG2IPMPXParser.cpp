/**   \file MPEG2IPMPXParser.cpp

      \ingroup mpeg2drmplayer

      MPEG2 test parsers with IPMPX signalling.

      The Initial Developer of the Original Code is Mutable, Inc. <br>
      Portions created by Mutable, Inc. are <br>
      Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

      
*/

#include "MPEG2IPMPXParser.h"

#include "IPMPControlInfoPart.h"
#include "IPMPDescriptor.h"
#include "IPMPStreamDataUpdate.h"
#include "SigCertContainer.h"

#include "IPMPToolManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  MPEG2 parser with IPMPX signalling.

    Contains common routines for transport and program stream parsers.
*/
/*! \brief Parse byte array.

    \warning  Input stream is modified in process.

    Calculate array's length and retrieve array data.
    Possibly throws ByteSeqException.

    \returns  Byte array.
*/
ByteSeq MPEG2IPMPXParser::ParseByteSeq(ByteSeq& stream) {
  UInt64T len = stream.GetSizeOfInstance(0);
  return stream.GetBytes((UInt32T)len);
}

/*! \brief Parse IPMP descriptor.

    \warning  Input stream is modified in process.

    Possibly throws ByteSeqException.

    \returns  IPMP descriptor pointer (if 0, failed).
*/
IIPMPDescriptor* MPEG2IPMPXParser::ParseIPMPDescriptor(ByteSeq& stream) {
  ByteT tmp8 = stream.GetByte();
  if (tmp8 != 41) {
    return 0;
  }
//  tmp8 = stream.GetByte();
//  ByteSeq data = stream.GetBytes(tmp8);
  //  Because of a bug in specifiations, we read 16-bit descriptor length.
  Bit16T tmp16 = stream.GetBit16();
  ByteSeq data = stream.GetBytes(tmp16);

  Bit32T descID = data.GetBit32();
  Bit128T toolID = data.GetBit128();
  ByteT point = data.GetByte();
  ByteT code = data.GetByte();
  UInt16T len = data.GetUInt16();
  ByteSeq ipmpData = data.GetBytes(len);

  ISigCertContainer* container = 0;
  if (data.GetByte() & 0x80) {
    //  Signed.
    if ((container = ParseSigCertContainer(data)) == 0) {
      return 0;
    }
  }

  return new IPMPDescriptor(descID, toolID, point, code, ipmpData, container);
}

/*! \brief Parse signature and certificate container.

    \warning  Input stream is modified in process.

    Possibly throws ByteSeqException.

    \returns  Signature and certificate container pointer (if 0, failed).
*/
ISigCertContainer* MPEG2IPMPXParser::ParseSigCertContainer(ByteSeq& stream) {
  std::vector<ICertContainer*> certs;
  ByteSeq signature = ParseByteSeq(stream);
  ByteT tmp8 = stream.GetByte();
  while (tmp8 > 0) {
    ByteT type = stream.GetByte();
    ByteSeq cert = ParseByteSeq(stream);
    certs.push_back(new CertContainer(type, cert));
    tmp8--;
  }
  Bit128T verify = stream.GetBit128();
  return new SigCertContainer(signature, certs, verify);
}

/*! \brief Parse IPMP stream data update.

    \warning  Input stream is modified in process.

    Possibly throws ByteSeqException.

    \returns  IPMP stream data update pointer (if 0, failed).
*/
IIPMPStreamDataUpdate* MPEG2IPMPXParser::ParseIPMPStreamDataUpdate(ByteSeq& stream) {
  Bit32T descID = stream.GetBit32();
  UInt16T len = stream.GetUInt16();
  ByteSeq ipmpData = stream.GetBytes(len);
  return new IPMPStreamDataUpdate(descID, ipmpData);
}

/*! \brief  MPEG2 transport stream parser with IPMPX signalling.

    Parses data and calls handling routines.
*/
/*! \brief  Parse transport stream and call tool manager's handling routines.

    \warning  Input stream is modified in process.

    \param  stream        input, transport stream.

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXTStreamParser::ParseStream(ByteSeq& stream) {
  //  Since this is just a test we will assume that first we parse control
  //  info intermediate parts, then control info last part, then IPMP
  // descriptor.
  try {
    //  Parse control info parts.
    bool lastParsed = false;
    while (lastParsed == false) {
      ByteT tableID = stream.GetByte();
      Bit16T tmp16 = stream.GetBit16();
      bool syntax = ((tmp16 & 0x8000) == 0)? (false): (true);
      UInt16T sectionLength = (tmp16 & 0xfff);
      ByteSeq data = stream.GetBytes(sectionLength);
      ByteT tmp8 = data.GetByte();
      Bit5T version = (tmp8 >> 1) & 0x1f;
      bool current = ((tmp8 & 0x1) == 0)? (false): (true);
      ByteT sectionNum = data.GetByte();
      ByteT lastNum = data.GetByte();
      UInt16T totalLen = data.GetUInt16();
      UInt16T thisLen = data.GetUInt16();
      ByteSeq classes = data.GetBytes(thisLen);
      if (sectionNum == lastNum) {
        //  Last section.
        ISigCertContainer* container = 0;
        tmp8 = data.GetByte();
        if (tmp8 & 0x80) {
          //  Signed.
          if ((container = ParseSigCertContainer(data)) == 0) {
            return false;
          }
        }
        UInt32T crc = data.GetUInt32();
        ILastTStreamIPMPControlInfoPart* last =
          new LastTStreamIPMPControlInfoPart(version, current, sectionNum,
          classes, crc, tableID, syntax, totalLen, container);
        lastParsed = true;

        //  Pass control info part to manager.
        if (manager->ProcessLastTStreamIPMPControlInfoPart(last) == false) {
          return false;
        }
      } else {
        UInt32T crc = data.GetUInt32();
        IInterTStreamIPMPControlInfoPart* inter =
          new InterTStreamIPMPControlInfoPart(version, current, sectionNum,
          classes, crc, tableID, syntax, totalLen, lastNum);

        //  Pass control info part to manager.
        if (manager->ProcessInterTStreamIPMPControlInfoPart(inter) == false) {
          return false;
        }
      }
    }

    //  Parse IPMP descriptor.
    IIPMPDescriptor* ipmpDesc = ParseIPMPDescriptor(stream);
    if (ipmpDesc == 0) {
      return false;
    }

    //  Save control point for later reference.
    ByteT control = ipmpDesc->GetControlPoint();

    //  Pass IPMP dscriptor to manager.
    if (manager->ProcessIPMPDescriptor(ipmpDesc) == false) {
      return false;
    }

    //  Read data and pass it to tool manager.
    while (stream.GetLength() > 0) {
      UInt32T length = stream.GetUInt32();
      ByteSeq encrypted = stream.GetBytes(length), plain;
      if (manager->ProcessData(control, encrypted, plain) == false) {
        return false;
      }
    }

    return true;
  }
  catch (ByteSeqException) {
    return false;
  }
}

/*! \brief  MPEG2 program stream parser with IPMPX signalling.

    Parses data and calls handling routines.
*/
/*! \brief  Parse program stream and call tool manager's handling routines.

    \warning  Input stream is modified in process.

    \param  stream        input, transport stream.

    \returns  Boolean indicating success or failure.
*/
bool MPEG2IPMPXPStreamParser::ParseStream(ByteSeq& stream) {
  //  Since this is just a test we will assume that first we parse control
  //  info intermediate parts, then control info last part, then IPMP
  // descriptor.
  try {
    //  Parse control info parts.
    bool lastParsed = false;
    while (lastParsed == false) {
      Bit24T prefix = stream.GetBit24();
      ByteT streamID = stream.GetByte();
      UInt16T packetLength = stream.GetUInt16();
      ByteSeq data = stream.GetBytes(packetLength);
      Bit16T tmp16 = data.GetBit16();
      bool pesFlag = ((tmp16 & 0x1) == 0)? (false): (true);
      ByteT tmp8 = data.GetByte();
      tmp8 = data.GetByte();
      bool pesFlag2 = ((tmp8 & 0x1) == 0)? (false): (true);
      tmp8 = data.GetByte();
      tmp8 = data.GetByte();
      bool extFlag = ((tmp8 & 0x80) == 0)? (false): (true);
      ByteT ext = (tmp8 & 0x7f);
      tmp8 = data.GetByte();
      Bit5T version = (tmp8 >> 3);
      bool next = (((tmp8 >> 2) & 0x1) == 0)? (false): (true);
      ByteT packetNum = data.GetByte();
      ByteT lastNum = data.GetByte();
      UInt16T thisLen = data.GetUInt16();
      ByteSeq classes = data.GetBytes(thisLen);
      if (packetNum == lastNum) {
        //  Last section.
        ISigCertContainer* container = 0;
        tmp8 = data.GetByte();
        if (tmp8 & 0x80) {
          //  Signed.
          if ((container = ParseSigCertContainer(data)) == 0) {
            return false;
          }
        }
        UInt32T crc = data.GetUInt32();
        ILastPStreamIPMPControlInfoPart* last =
          new LastPStreamIPMPControlInfoPart(version, next, packetNum,
          classes, crc, prefix, streamID, pesFlag, pesFlag2, extFlag, ext,
          container);
        lastParsed = true;

        //  Pass control info part to manager.
        if (manager->ProcessLastPStreamIPMPControlInfoPart(last) == false) {
          return false;
        }
      } else {
        UInt32T crc = data.GetUInt32();
        IInterPStreamIPMPControlInfoPart* inter =
          new InterPStreamIPMPControlInfoPart(version, next, packetNum,
          classes, crc, prefix, streamID, pesFlag, pesFlag2, extFlag, ext,
          lastNum);

        //  Pass control info part to manager.
        if (manager->ProcessInterPStreamIPMPControlInfoPart(inter) == false) {
          return false;
        }
      }
    }

    //  Parse IPMP descriptor.
    IIPMPDescriptor* ipmpDesc = ParseIPMPDescriptor(stream);
    if (ipmpDesc == 0) {
      return false;
    }

    //  Save control point for later reference.
    ByteT control = ipmpDesc->GetControlPoint();

    //  Pass IPMP dscriptor to manager.
    if (manager->ProcessIPMPDescriptor(ipmpDesc) == false) {
      return false;
    }

    //  Read data and pass it to tool manager.
    while (stream.GetLength() > 0) {
      UInt32T length = stream.GetUInt32();
      ByteSeq encrypted = stream.GetBytes(length), plain;
      if (manager->ProcessData(control, encrypted, plain) == false) {
        return false;
      }
    }

    return true;
  }
  catch (ByteSeqException) {
    return false;
  }
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
