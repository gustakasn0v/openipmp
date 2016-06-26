/**	\file IPMPControlInfo.cpp

	IPMP control information classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "IPMPControlInfo.h"
#include "BasicTypes.h"
#include <vector>
#include <map>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP rights container.

    Class containing usage rules and states associated with IPMP protected content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool IPMPRightsContainer::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x04);
  if (data.GetLength() >= (1 << 16)) {
    return false;
  }
  encoded += ByteSeq((UInt16T)(data.GetLength()));
  encoded += data;
  return true;
}

/*! \brief  Get rights data.

    Rights data is a simple byte array.

    \returns  Rights data.
*/
const ByteSeq& IPMPRightsContainer::GetRightsData() const {
  return data;
}

/*! \brief  IPMP tool container.

    Class containing a tool needed for consuming the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolContainer::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x03);
  ByteSeq data(ipmpToolID);
  data += ByteSeq(toolFormatID);
  data += ByteSeq(toolPackageID);
  if (toolBody.GetLength() >= (1 << 16)) {
    return false;
  }
  data += ByteSeq((UInt16T)(toolBody.GetLength()));
  data += toolBody;
  if (data.GetLength() >= (1 << 16)) {
    return false;
  }
  encoded += ByteSeq((UInt16T)(data.GetLength()));
  encoded += data;
  return true;
}

/*! \brief  Get IPMP tool identifier.

    \returns  IPMP tool identifier.
*/
const Bit128T& IPMPToolContainer::GetIPMPToolID() const {
  return ipmpToolID;
}

/*! \brief  Get tool format identifier.

    \returns  Tool format identifier.
*/
const Bit32T& IPMPToolContainer::GetToolFormatID() const {
  return toolFormatID;
}

/*! \brief  Get tool package identifier.

    \returns  Tool package identifier.
*/
const Bit16T& IPMPToolContainer::GetToolPackageID() const {
  return toolPackageID;
}

/*! \brief  Get tool body data.

    Tool body data is a simple byte array.

    \returns  Tool body data.
*/
const ByteSeq& IPMPToolContainer::GetToolBody() const {
  return toolBody;
}

/*! \brief  Tool description.

    Description of an IPMP tool contained in a parametric description.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \returns  Encoded byte array.
*/
ByteSeq ToolDescription::MPEG2Encode() const {
  return cclass.MPEG2Encode() + subclass.MPEG2Encode() + typeData.MPEG2Encode()
    + type.MPEG2Encode() + addedData.MPEG2Encode();
}

/*! \brief  Get class.

    \returns  Class.
*/
const ByteSeq& ToolDescription::GetClass() const {
  return cclass;
}

/*! \brief  Get subclass.

    \returns  Subclass.
*/
const ByteSeq& ToolDescription::GetSubclass() const {
  return subclass;
}

/*! \brief  Get type data.

    \returns  Type data.
*/
const ByteSeq& ToolDescription::GetTypeData() const {
  return typeData;
}

/*! \brief  Get type data value.

    \returns  Type data value.
*/
const ByteSeq& ToolDescription::GetType() const {
  return type;
}

/*! \brief  Get additional data.

    \returns  Additional data.
*/
const ByteSeq& ToolDescription::GetAddedData() const {
  return addedData;
}

/*! \brief  IPMP parametric description.

    Class containing a parametric description of a tool needed for consuming
    the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool IPMPParametricDescription::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x05);
  ByteSeq data = descriptionComment.MPEG2Encode();
  data += majorVersion;
  data += minorVersion;
  if (toolDescriptions.size() >= (1 << 8)) {
    return false;
  }
  data += (ByteT)(toolDescriptions.size());
  std::vector<ToolDescription>::const_iterator iter = toolDescriptions.begin();
  while (iter != toolDescriptions.end()) {
    data += iter->MPEG2Encode();
    iter++;
  }
  if (data.GetLength() >= (1 << 16)) {
    return false;
  }
  encoded += ByteSeq((UInt16T)(data.GetLength()));
  encoded += data;
  return true;
}

/*! \brief  Get description comment.

    Description comment is a simple byte array.

    \returns  Description comment.
*/
const ByteSeq& IPMPParametricDescription::GetDescriptionComment() const {
  return descriptionComment;
}

/*! \brief  Get major version.

    \returns  Major version.
*/
const ByteT& IPMPParametricDescription::GetMajorVersion() const {
  return majorVersion;
}

/*! \brief  Get minor version.

    \returns  Minor version.
*/
const ByteT& IPMPParametricDescription::GetMinorVersion() const {
  return minorVersion;
}

/*! \brief  Get tool descriptions contained.

    \returns  Vector of tool descriptions.
*/
const std::vector<ToolDescription>& IPMPParametricDescription::GetToolDescriptions() const {
  return toolDescriptions;
}

/*! \brief  IPMP tool information.

    Class containing information about a tool needed for consuming the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolInfo::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x02);
  ByteSeq data(toolID);
  data += (ByteT)(((specificToolIDs.size() == 0)? (0): (0x80)) |
    ((parametricDescription == 0)? (0): (0x40)) | 0x3f);
  if (specificToolIDs.size() > 0) {
    if (specificToolIDs.size() >= (1 << 8)) {
      return false;
    }
    data += (ByteT)(specificToolIDs.size());
    std::vector<Bit128T>::const_iterator iter = specificToolIDs.begin();
    while (iter != specificToolIDs.end()) {
      data += ByteSeq(*iter);
      iter++;
    }
  }
  if (parametricDescription != 0) {
    ByteSeq tmp;
    if (parametricDescription->MPEG2Encode(tmp) == false) {
      return false;
    }
    data += tmp;
  }
  if (toolURLs.size() >= (1 << 8)) {
    return false;
  }
  data += (ByteT)(toolURLs.size());
  std::vector<ByteSeq>::const_iterator iter = toolURLs.begin();
  while (iter != toolURLs.end()) {
    data += iter->MPEG2Encode();
    iter++;
  }
  if (data.GetLength() >= (1 << 16)) {
    return false;
  }
  encoded += ByteSeq((UInt16T)(data.GetLength()));
  encoded += data;
  return true;
}

/*! \brief  Get tool identifier.

    \returns  Number representing the tool identifier.
*/
const Bit128T& IPMPToolInfo::GetToolID() const {
  return toolID;
}

/*! \brief  Alternative tool identifiers contained.

    Alternative tool identifiers represent tools that are considered
    equivalent to each other.

    \returns  Vector of tool identifiers.
*/
const std::vector<Bit128T>& IPMPToolInfo::GetSpecificToolIDs() const {
  return specificToolIDs;
}

/*! \brief  Get IPMP parametric description.

    Parametric description describes a tool for consuming the content.
    Terminal will use this description to find an appropriate tool.
    Since this member is optional, return value of 0 indicates that it's
    not present.

    \returns  IPMP parametric description.
*/
const IPMPParametricDescription* IPMPToolInfo::GetIPMPParametricDescription() const {
  return parametricDescription;
}

/*! \brief  Tool URLs contained.

    \returns  Vector of tool URLs.
*/
const std::vector<ByteSeq>& IPMPToolInfo::GetToolURLs() const {
  return toolURLs;
}

/*! \brief  IPMP tool list.

    Class containing list of tools needed for consuming the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool IPMPToolList::MPEG2Encode(ByteSeq& encoded) const {
  encoded = ByteSeq((ByteT)0x01);
  ByteSeq infos;
  if (toolInfos.size() >= (1 << 8)) {
    return false;
  }
  std::vector<IPMPToolInfo*>::const_iterator iter = toolInfos.begin();
  while (iter != toolInfos.end()) {
    ByteSeq tmp;
    if ((*iter)->MPEG2Encode(tmp) == false) {
      return false;
    }
    infos += tmp;
    iter++;
  }
  //  Inconstistency in the documentation: is this 8-bit or 16-bit field?
  if ((infos.GetLength() + 1) >= (1 << 16)) {
    return false;
  }
  encoded += ByteSeq((UInt16T)(infos.GetLength() + 1));
  encoded += (ByteT)(toolInfos.size());
  encoded += infos;
  return true;
}

/*! \brief  Get IPMP tool informations contained.

    \returns  Vector of IPMP tool informations.
*/
const std::vector<IPMPToolInfo*>& IPMPToolList::GetIPMPToolInfos() const {
  return toolInfos;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
