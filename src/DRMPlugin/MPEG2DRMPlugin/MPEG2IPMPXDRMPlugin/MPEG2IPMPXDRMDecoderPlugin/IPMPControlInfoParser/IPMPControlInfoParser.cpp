/**	\file IPMPControlInfoParser.cpp

	IPMP control information classes parser.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "IPMPControlInfoParser.h"

#include "BasicTypes.h"
#include <string>
#include "IPMPControlInfo.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Parser of IPMP control information classes.

    Used for parsing IPMP control information classes and returning parsed
    classes to callers.
*/
/*! \brief  Parse IPMP control information class.

    \warning  Encoded data is modified during parsing.

    \param  encoded   input, encoded data.
    \param  control   output, parsed IPMP control information class.

    \returns  Boolean indicating success or failure.
*/
bool IPMPControlInfoParser::ParseIPMPControlInfo(ByteSeq& encoded,
    DecoderIPMPControlInfo** control) {
  try {
    switch (encoded.GetByte()) {
    case 0x01:
      //  IPMP tool list.
      *control = ParseIPMPToolList(encoded);
      return true;
    case 0x02:
      //  IPMP tool info.
      *control = ParseIPMPToolInfo(encoded);
      return true;
    case 0x03:
      //  IPMP tool container.
      *control = ParseIPMPToolContainer(encoded);
      return true;
    case 0x04:
      //  IPMP rights container.
      *control = ParseIPMPRightsContainer(encoded);
      return true;
    case 0x05:
      //  IPMP parametric description.
      *control = ParseIPMPParametricDescription(encoded);
      return true;
    default:
      return false;
    }
  }
  catch (ByteSeqException) {
    return false;
  }
  catch (IPMPControlInfoParserException) {
    return false;
  }
}

/*! \brief  Parse IPMP rights container.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPControlInfoParserException.

    \param  encoded   input, encoded message.

    \returns  IPMP rights container.
*/
DecoderIPMPRightsContainer* IPMPControlInfoParser::ParseIPMPRightsContainer(ByteSeq&
    encoded) {
  UInt16T length = encoded.GetUInt16();
  ByteSeq data = encoded.GetBytes(length);
  ByteSeq rights = data.GetBytes((UInt32T)(data.GetSizeOfInstance(0)));
  return new DecoderIPMPRightsContainer(rights, parserLogger);
}

/*! \brief  Parse IPMP tool container.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPControlInfoParserException.

    \param  encoded   input, encoded message.

    \returns  IPMP tool container.
*/
DecoderIPMPToolContainer* IPMPControlInfoParser::ParseIPMPToolContainer(ByteSeq&
    encoded) {
  UInt16T length = encoded.GetUInt16();
  ByteSeq data = encoded.GetBytes(length);
  Bit128T toolID = data.GetBit128();
  Bit32T formatID = data.GetBit32();
  Bit16T packageID = data.GetBit16();
  UInt16T size = data.GetUInt16();
  ByteSeq body = data.GetBytes((UInt32T)size);
  return new DecoderIPMPToolContainer(toolID, formatID, packageID, body, parserLogger);
}

/*! \brief  Parse IPMP parametric description.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPControlInfoParserException.

    \param  encoded   input, encoded message.

    \returns  IPMP parametric description.
*/
DecoderIPMPParametricDescription* IPMPControlInfoParser::ParseIPMPParametricDescription(
    ByteSeq& encoded) {
  UInt16T length = encoded.GetUInt16();
  ByteSeq data = encoded.GetBytes(length);
  ByteSeq comment = data.GetBytes((UInt32T)(data.GetSizeOfInstance(0)));
  ByteT major = data.GetByte();
  ByteT minor = data.GetByte();
  ByteT nDesc = data.GetByte();
  std::vector<ToolDescription> descriptions;
  while (nDesc > 0) {
    descriptions.push_back(ParseToolDescription(data));
    nDesc--;
  }
  return new DecoderIPMPParametricDescription(comment, major, minor, descriptions, parserLogger);
}

/*! \brief  Parse IPMP tool description.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPControlInfoParserException.

    \param  encoded   input, encoded message.

    \returns  IPMP tool description.
*/
ToolDescription IPMPControlInfoParser::ParseToolDescription(ByteSeq& encoded) {
  ByteSeq cclass = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  ByteSeq subclass = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  ByteSeq typeData = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  ByteSeq type = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  ByteSeq addedData = encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0)));
  return ToolDescription(cclass, subclass, typeData, type, addedData);
}

/*! \brief  Parse IPMP tool info.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPControlInfoParserException.

    \param  encoded   input, encoded message.

    \returns  IPMP tool info.
*/
DecoderIPMPToolInfo* IPMPControlInfoParser::ParseIPMPToolInfo(ByteSeq& encoded) {
  UInt16T length = encoded.GetUInt16();
  ByteSeq data = encoded.GetBytes(length);
  Bit128T toolID = data.GetBit128();
  ByteT tmp = data.GetByte();
  bool isAltGroup = ((tmp & 0x80) == 0)? (false): (true);
  bool isParametric = ((tmp & 0x40) == 0)? (false): (true);
  if ((tmp & 0x3f) != 0x3f) {
    throw IPMPControlInfoParserException();
  }
  std::vector<Bit128T> specific;
  if (isAltGroup) {
    tmp = data.GetByte();
    while (tmp > 0) {
      specific.push_back(data.GetBit128());
      tmp--;
    }
  }
  IPMPParametricDescription* parametric = 0;
  if (isParametric) {
    if (data.GetByte() != 0x05) {
      throw IPMPControlInfoParserException();
    }
    parametric = ParseIPMPParametricDescription(data);
  }
  std::vector<ByteSeq> urls;
  tmp = data.GetByte();
  while (tmp > 0) {
    urls.push_back(encoded.GetBytes((UInt32T)(encoded.GetSizeOfInstance(0))));
    tmp--;
  }
  return new DecoderIPMPToolInfo(toolID, specific, parametric, urls, parserLogger);
}

/*! \brief  Parse IPMP tool list.

    \warning  Encoded data is modified during parsing.
    \warning  In case of an error, throws either ByteSeqException or
              IPMPControlInfoParserException.

    \param  encoded     input, encoded data.

    \returns  IPMP tool list.
*/
DecoderIPMPToolList* IPMPControlInfoParser::ParseIPMPToolList(ByteSeq& encoded) {
  UInt16T length = encoded.GetUInt16();
  ByteSeq data = encoded.GetBytes(length);
  ByteT nTools = data.GetByte();
  std::vector<DecoderIPMPToolInfo*> infos;
  while (nTools > 0) {
    if (data.GetByte() != 0x02) {
      throw IPMPControlInfoParserException();
    }
    infos.push_back(ParseIPMPToolInfo(data));
    nTools--;
  }
  return new DecoderIPMPToolList(infos, parserLogger);
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
