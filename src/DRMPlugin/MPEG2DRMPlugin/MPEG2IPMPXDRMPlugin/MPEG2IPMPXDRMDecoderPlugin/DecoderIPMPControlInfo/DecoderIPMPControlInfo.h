/**	\file DecoderIPMPControlInfo.h

	IPMP control information classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (DECODERIPMPCONTROLINFO_H)
#define DECODERIPMPCONTROLINFO_H

#include "BasicTypes.h"
#include <vector>
#include <map>
#include "IPMPAgent.h"
#include "IPMPControlInfo.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Decoder IPMP control info class.

    Class containing information for initializing IPMP manager.
*/
class DecoderIPMPControlInfo: public IPMPControlInfo {
public:
  virtual ~DecoderIPMPControlInfo() {
  }

  /*! \brief  Create tools, using contained information.

      \warning  Check if there is an existing tool already created in
                the map with the same tool identifier. If there is, do
                not overwrite it, but return error.

      \param  tools       output, IPMP tools (mapped by tool identifiers).

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools) = 0;
};

/*! \brief  Decoder IPMP rights container.

    Class containing usage rules and states associated with IPMP protected content.
*/
class DecoderIPMPRightsContainer: public DecoderIPMPControlInfo,
    public IPMPRightsContainer {
public:
  /*! \brief  Constructor.

      \param  rights      rights data.
      \param  logger      message logger.
  */
  DecoderIPMPRightsContainer(const ByteSeq& rights, DRMLogger& logger): IPMPRightsContainer(rights), infoLogger(logger) {
  }

  virtual ~DecoderIPMPRightsContainer() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create tools, using contained information.

      \warning  Check if there is an existing tool already created in
                the map with the same tool identifier. If there is, do
                not overwrite it, but return error.

      \param  tools       output, IPMP tools (mapped by tool identifiers).

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools);

private:
  DRMLogger& infoLogger;
};

/*! \brief  Decoder IPMP tool container.

    Class containing a tool needed for consuming the content.
*/
class DecoderIPMPToolContainer: public DecoderIPMPControlInfo, public IPMPToolContainer {
public:
  /*! \brief  Constructor.

      \param  toolID      IPMP tool identifier.
      \param  formatID    tool format identifier.
      \param  packageID   tool package identifier.
      \param  body        tool body.
      \param  logger      message logger.
  */
  DecoderIPMPToolContainer(const Bit128T& toolID, const Bit32T& formatID, const
    Bit16T& packageID, const ByteSeq& body, DRMLogger& logger): IPMPToolContainer(toolID, formatID, packageID, body), infoLogger(logger) {
  }

  virtual ~DecoderIPMPToolContainer() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create tools, using contained information.

      \warning  Check if there is an existing tool already created in
                the map with the same tool identifier. If there is, do
                not overwrite it, but return error.

      \param  tools       output, IPMP tools (mapped by tool identifiers).

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools);

private:
  DRMLogger& infoLogger;
};

/*! \brief  Decoder IPMP parametric description.

    Class containing a parametric description of a tool needed for consuming
    the content.
*/
class DecoderIPMPParametricDescription: public DecoderIPMPControlInfo,
    public IPMPParametricDescription {
public:
  /*! \brief  Constructor.

      \param  comment       description comment.
      \param  major         major version.
      \param  minor         minor version.
      \param  descriptions  tool descriptions.
      \param  logger        message logger.
  */
  DecoderIPMPParametricDescription(const ByteSeq& comment, const ByteT& major,
    const ByteT& minor, const std::vector<ToolDescription>& descriptions, DRMLogger& logger): IPMPParametricDescription(comment, major, minor, descriptions), infoLogger(logger) {
  }

  virtual ~DecoderIPMPParametricDescription() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create tools, using contained information.

      \warning  Check if there is an existing tool already created in
                the map with the same tool identifier. If there is, do
                not overwrite it, but return error.

      \param  tools       output, IPMP tools (mapped by tool identifiers).

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools);

private:
  DRMLogger& infoLogger;
};

/*! \brief  Decoder IPMP tool information.

    Class containing information about a tool needed for consuming the content.
*/
class DecoderIPMPToolInfo: public DecoderIPMPControlInfo, public IPMPToolInfo {
public:
  /*! \brief  Constructor with parametric description.

      \param  tool        tool identifier.
      \param  specific    specific tool identifiers.
      \param  parametric  parametric description.
      \param  urls        tool URLs.
      \param  logger      message logger.
  */
  DecoderIPMPToolInfo(const Bit128T& tool, const std::vector<Bit128T>& specific,
    IPMPParametricDescription* parametric, const std::vector<ByteSeq>&
    urls, DRMLogger& logger): IPMPToolInfo(tool, specific, parametric, urls), infoLogger(logger) {
  }

  virtual ~DecoderIPMPToolInfo() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create tools, using contained information.

      \warning  Check if there is an existing tool already created in
                the map with the same tool identifier. If there is, do
                not overwrite it, but return error.

      \param  tools       output, IPMP tools (mapped by tool identifiers).

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools);

private:
  DRMLogger& infoLogger;
};

/*! \brief  Decoder IPMP tool list.

    Class containing list of tools needed for consuming the content.
*/
class DecoderIPMPToolList: public DecoderIPMPControlInfo, public IPMPToolList {
public:
  /*! \brief  Constructor.

      \param  infos     tool infos.
      \param  logger    message logger.
  */
  DecoderIPMPToolList(const std::vector<DecoderIPMPToolInfo*>& infos, DRMLogger& logger):
      IPMPToolList(std::vector<IPMPToolInfo*>()), decoderInfos(infos), infoLogger(logger) {
    for (unsigned int i = 0; i < decoderInfos.size(); i++) {
      toolInfos.push_back(decoderInfos[i]);
    }
  }

  virtual ~DecoderIPMPToolList() {
    //  IPMPToolList will do the cleanup.
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Create tools, using contained information.

      \warning  Check if there is an existing tool already created in
                the map with the same tool identifier. If there is, do
                not overwrite it, but return error.

      \param  tools       output, IPMP tools (mapped by tool identifiers).

      \returns Boolean indicating success or failure.
  */
  virtual bool CreateIPMPTools(std::map<Bit128T, IPMPTool*>& tools);

private:
  const std::vector<DecoderIPMPToolInfo*>& decoderInfos;
  DRMLogger& infoLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(DECODERIPMPCONTROLINFO_H)
