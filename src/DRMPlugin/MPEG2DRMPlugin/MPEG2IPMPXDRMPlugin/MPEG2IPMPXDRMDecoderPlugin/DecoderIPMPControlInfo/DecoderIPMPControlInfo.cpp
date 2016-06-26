/**	\file DecoderIPMPControlInfo.cpp

	IPMP control information classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "DecoderIPMPControlInfo.h"
#include "BasicTypes.h"
#include <vector>
#include <map>
#include "IPMPAgent.h"
#include "OpenIPMPTool.h"

#include <stdio.h>
#include <sys/stat.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Decoder IPMP rights container.

    Class containing usage rules and states associated with IPMP protected content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool DecoderIPMPRightsContainer::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPRightsContainer::MPEG2Encode(encoded);
}

/*! \brief  Create tools, using contained information.

    \warning  Check if there is an existing tool already created in
              the map with the same tool identifier. If there is, do
              not overwrite it, but return error.

    \param  tools       output, IPMP tools (mapped by tool identifiers).

    \returns Boolean indicating success or failure.
*/
bool DecoderIPMPRightsContainer::CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools) {
  return false;
}

/*! \brief  Decoder IPMP tool container.

    Class containing a tool needed for consuming the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool DecoderIPMPToolContainer::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPToolContainer::MPEG2Encode(encoded);
}

/*! \brief  Create tools, using contained information.

    \warning  Check if there is an existing tool already created in
              the map with the same tool identifier. If there is, do
              not overwrite it, but return error.

    \param  tools       output, IPMP tools (mapped by tool identifiers).

    \returns Boolean indicating success or failure.
*/
bool DecoderIPMPToolContainer::CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools) {
  return false;
}

/*! \brief  Decoder IPMP parametric description.

    Class containing a parametric description of a tool needed for consuming
    the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool DecoderIPMPParametricDescription::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPParametricDescription::MPEG2Encode(encoded);
}

/*! \brief  Create tools, using contained information.

    \warning  Check if there is an existing tool already created in
              the map with the same tool identifier. If there is, do
              not overwrite it, but return error.

    \param  tools       output, IPMP tools (mapped by tool identifiers).

    \returns Boolean indicating success or failure.
*/
bool DecoderIPMPParametricDescription::CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools) {
  return false;
}

/*! \brief  Decoder IPMP tool information.

    Class containing information about a tool needed for consuming the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool DecoderIPMPToolInfo::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPToolInfo::MPEG2Encode(encoded);
}

/*! \brief  Create tools, using contained information.

    \warning  Check if there is an existing tool already created in
              the map with the same tool identifier. If there is, do
              not overwrite it, but return error.

    \param  tools       output, IPMP tools (mapped by tool identifiers).

    \returns Boolean indicating success or failure.
*/
bool DecoderIPMPToolInfo::CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools) {
  //  If tool identifier equals openIPMP tool identifier, create it, otherwise
  //  return.
  if (toolID == "openIPMP tool ID") {
    //  Check if there is an existing tool with the same tool identifier.
    //  If there is, do not overwrite it, but return error.
    if (tools.find(toolID) != tools.end()) {
      return false;
    }
    tools[toolID] = new OpenIPMPTool(infoLogger);
    return true;
  }
  return false;
}

/*! \brief  Decoder IPMP tool list.

    Class containing list of tools needed for consuming the content.
*/
/*! \brief  Encode as byte array.

    Encode for purpose of stream encoding, signature verification etc.

    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
bool DecoderIPMPToolList::MPEG2Encode(ByteSeq& encoded) const {
  return IPMPToolList::MPEG2Encode(encoded);
}

/*! \brief  Create tools, using contained information.

    \warning  Check if there is an existing tool already created in
              the map with the same tool identifier. If there is, do
              not overwrite it, but return error.

    \param  tools       output, IPMP tools (mapped by tool identifiers).

    \returns Boolean indicating success or failure.
*/
bool DecoderIPMPToolList::CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools) {
  return false;
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
