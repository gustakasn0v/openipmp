/**	\file IPMPControlInfo.h

	IPMP control information classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IPMPCONTROLINFO_H)
#define IPMPCONTROLINFO_H

#include "BasicTypes.h"
#include <vector>
#include <map>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  IPMP control info class.

    Class containing information for initializing IPMP manager.
*/
class IPMPControlInfo {
public:
  virtual ~IPMPControlInfo() {};
  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const = 0;
};

/*! \brief  IPMP rights container.

    Class containing usage rules and states associated with IPMP protected content.
*/
class IPMPRightsContainer: public IPMPControlInfo {
public:
  /*! \brief  Constructor.

      \param  rights      rights data.
  */
  IPMPRightsContainer(const ByteSeq& rights): data(rights) {
  }

  virtual ~IPMPRightsContainer() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get rights data.

      Rights data is a simple byte array.

      \returns  Rights data.
  */
  const ByteSeq& GetRightsData() const;

protected:
  ByteSeq data;
};

/*! \brief  IPMP tool container.

    Class containing a tool needed for consuming the content.
*/
class IPMPToolContainer: public IPMPControlInfo {
public:
  /*! \brief  Constructor.

      \param  toolID      IPMP tool identifier.
      \param  formatID    tool format identifier.
      \param  packageID   tool package identifier.
      \param  body        tool body.
  */
  IPMPToolContainer(const Bit128T& toolID, const Bit32T& formatID, const
    Bit16T& packageID, const ByteSeq& body): ipmpToolID(toolID),
    toolFormatID(formatID), toolPackageID(packageID), toolBody(body) {
  }

  virtual ~IPMPToolContainer() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get IPMP tool identifier.

      \returns  IPMP tool identifier.
  */
  const Bit128T& GetIPMPToolID() const;

  /*! \brief  Get tool format identifier.

      \returns  Tool format identifier.
  */
  const Bit32T& GetToolFormatID() const;

  /*! \brief  Get tool package identifier.

      \returns  Tool package identifier.
  */
  const Bit16T& GetToolPackageID() const;

  /*! \brief  Get tool body data.

      Tool body data is a simple byte array.

      \returns  Tool body data.
  */
  const ByteSeq& GetToolBody() const;

protected:
  Bit128T ipmpToolID;
  Bit32T toolFormatID;
  Bit16T toolPackageID;
  ByteSeq toolBody;
};

/*! \brief  Tool description.

    Description of an IPMP tool contained in a parametric description.
*/
class ToolDescription {
public:
  /*! \brief  Constructor.

      \param  cl        class.
      \param  sub       subclass.
      \param  typData   type data.
      \param  typ       type data value.
      \param  added     additional data.
  */
  ToolDescription(const ByteSeq& cl, const ByteSeq& sub,
    const ByteSeq& typData, const ByteSeq& typ, const ByteSeq& added):
    cclass(cl), subclass(sub), typeData(typData), type(typ), addedData(added) {
  }

  /*! \brief  Copy constructor.

      \param  rhs     tool description.
  */
  ToolDescription(const ToolDescription& rhs): cclass(rhs.cclass),
    subclass(rhs.subclass), typeData(rhs.typeData), type(rhs.type),
    addedData(rhs.addedData){
  }

  ~ToolDescription() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \returns  Encoded byte array.
  */
  ByteSeq MPEG2Encode() const;

  /*! \brief  Get class.

      \returns  Class.
  */
  const ByteSeq& GetClass() const;

  /*! \brief  Get subclass.

      \returns  Subclass.
  */
  const ByteSeq& GetSubclass() const;

  /*! \brief  Get type data.

      \returns  Type data.
  */
  const ByteSeq& GetTypeData() const;

  /*! \brief  Get type data value.

      \returns  Type data value.
  */
  const ByteSeq& GetType() const;

  /*! \brief  Get additional data.

      \returns  Additional data.
  */
  const ByteSeq& GetAddedData() const;

private:
  ByteSeq cclass;
  ByteSeq subclass;
  ByteSeq typeData;
  ByteSeq type;
  ByteSeq addedData;
};

/*! \brief  IPMP parametric description.

    Class containing a parametric description of a tool needed for consuming
    the content.
*/
class IPMPParametricDescription: public IPMPControlInfo {
public:
  /*! \brief  Constructor.

      \param  comment       description comment.
      \param  major         major version.
      \param  minor         minor version.
      \param  descriptions  tool descriptions.
  */
  IPMPParametricDescription(const ByteSeq& comment, const ByteT& major,
    const ByteT& minor, const std::vector<ToolDescription>& descriptions):
    descriptionComment(comment), majorVersion(major), minorVersion(minor),
    toolDescriptions(descriptions) {
  }

  virtual ~IPMPParametricDescription() {
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get description comment.

      Description comment is a simple byte array.

      \returns  Description comment.
  */
  const ByteSeq& GetDescriptionComment() const;

  /*! \brief  Get major version.

      \returns  Major version.
  */
  const ByteT& GetMajorVersion() const;

  /*! \brief  Get minor version.

      \returns  Minor version.
  */
  const ByteT& GetMinorVersion() const;

  /*! \brief  Get tool descriptions contained.

      \returns  Vector of tool descriptions.
  */
  const std::vector<ToolDescription>& GetToolDescriptions() const;

protected:
  ByteSeq descriptionComment;
  ByteT majorVersion;
  ByteT minorVersion;
  std::vector<ToolDescription> toolDescriptions;
};

/*! \brief  IPMP tool information.

    Class containing information about a tool needed for consuming the content.
*/
class IPMPToolInfo: public IPMPControlInfo {
public:
  /*! \brief  Constructor with parametric description.

      \param  tool        tool identifier.
      \param  specific    specific tool identifiers.
      \param  parametric  parametric description.
      \param  urls        tool URLs.
  */
  IPMPToolInfo(const Bit128T& tool, const std::vector<Bit128T>& specific,
    IPMPParametricDescription* parametric, const std::vector<ByteSeq>&
    urls): toolID(tool), specificToolIDs(specific), parametricDescription(parametric),
    toolURLs(urls) {
  }

  virtual ~IPMPToolInfo() {
    if (parametricDescription != 0) delete parametricDescription;
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get tool identifier.

      \returns  Number representing the tool identifier.
  */
  const Bit128T& GetToolID() const;

  /*! \brief  Alternative tool identifiers contained.

      Alternative tool identifiers represent tools that are considered
      equivalent to each other.

      \returns  Vector of tool identifiers.
  */
  const std::vector<Bit128T>& GetSpecificToolIDs() const;

  /*! \brief  Get IPMP parametric description.

      Parametric description describes a tool for consuming the content.
      Terminal will use this description to find an appropriate tool.
      Since this member is optional, return value of 0 indicates that it's
      not present.

      \returns  IPMP parametric description.
  */
  const IPMPParametricDescription* GetIPMPParametricDescription() const;

  /*! \brief  Tool URLs contained.

      \returns  Vector of tool URLs.
  */
  const std::vector<ByteSeq>& GetToolURLs() const;

protected:
  Bit128T toolID;
  std::vector<Bit128T> specificToolIDs;
  IPMPParametricDescription* parametricDescription;
  std::vector<ByteSeq> toolURLs;
};

/*! \brief  IPMP tool list.

    Class containing list of tools needed for consuming the content.
*/
class IPMPToolList: public IPMPControlInfo {
public:
  /*! \brief  Constructor.

      \param  infos     tool infos.
  */
  IPMPToolList(const std::vector<IPMPToolInfo*>& infos): toolInfos(infos) {
  }

  virtual ~IPMPToolList() {
    for (unsigned int i = 0; i < toolInfos.size(); i++) {
      delete toolInfos[i];
    }
    toolInfos.clear();
  }

  /*! \brief  Encode as byte array.

      Encode for purpose of stream encoding, signature verification etc.

      \param  encoded       output, encoded byte array.

      \returns  Boolean indicating success or failure.
  */
  virtual bool MPEG2Encode(ByteSeq& encoded) const;

  /*! \brief  Get IPMP tool informations contained.

      \returns  Vector of IPMP tool informations.
  */
  const std::vector<IPMPToolInfo*>& GetIPMPToolInfos() const;

protected:
  std::vector<IPMPToolInfo*> toolInfos;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined(IPMPCONTROLINFO_H)
