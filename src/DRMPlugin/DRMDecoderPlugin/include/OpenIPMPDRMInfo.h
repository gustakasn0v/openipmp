/**	\file OpenIPMPDRMInfo.h

	OpenIPMP DRM information.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPDRMINFO_H)
#define OPENIPMPDRMINFO_H

#include <string>
#include "DRMInfoException.h"
#include "DRMLogger.h"
#include "ICipher.h"

#include "OpenIPMP.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief OpenIPMP DRM information.

    Contains information that is used for DRM functionality.
*/
class OpenIPMPDRMInfo {
public:
  /*! \brief  Constructor.

      \param    data              input, encoded openIPMP DRM data.
      \param    dataSize          input, length of the encoded openIPMP DRM data.
      \param    logger            input-output, message logger.

      If fails, throws DRMInfoException and logger's log contains error
      description.
  */
  OpenIPMPDRMInfo(ByteT* data, UInt32T dataSize, DRMLogger& logger): encMethod(),
      contentID(), toolID(), rightsHost() {
    if ((data == 0) || (dataSize == 0)) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid openIPMP DRM data.");
      throw DRMInfoException();
    }
    // We try to parse openIPMP specific data.
    encMethod = (*data);
    if ((EncMethod(encMethod) != AES128CTR) && (EncMethod(encMethod) != BLOWFISH)) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid encryption method.");
      throw DRMInfoException();
    }
    std::basic_string<char> ipmpString((char*)(data + 1), (char*)(data + dataSize));
    int index = 0, ret;
    ret = ipmpString.find('\0', index);
    if (ret == -1) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid openIPMP DRM data.");
      throw DRMInfoException();
    }
    toolID = (char*)ipmpString.data();
    if (toolID != OPENIPMP_TOOLID) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid openIPMP tool identifier.");
      throw DRMInfoException();
    }
    index = (ret + 1);
    ret = ipmpString.find('\0', index);
    if (ret == -1) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid openIPMP DRM data.");
      throw DRMInfoException();
    }
    contentID = (char*)(ipmpString.data() + index);
    if (contentID == "") {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid content identifier.");
      throw DRMInfoException();
    }
    index = (ret + 1);
    ret = ipmpString.find('\0', index);
    if (ret == -1) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid openIPMP DRM data.");
      throw DRMInfoException();
    }
    rightsHost = (char*)(ipmpString.data() + index);
  }

  /*! \brief  Constructor.

      \param    eMethod           input, encryption method code.
      \param    conID             input, content identifier.
      \param    tID               input, IPMP tool identifier.
      \param    rHost             input, rights host.
      \param    logger            input-output, message logger.

      If fails, throws DRMInfoException and logger's log contains error
      description.
  */
  OpenIPMPDRMInfo(ByteT eMethod, const std::string& conID, const std::string&
      tID, const std::string& rHost, DRMLogger& logger): encMethod(eMethod),
      contentID(conID), toolID(tID), rightsHost(rHost) {
    if ((EncMethod(encMethod) != AES128CTR) && (EncMethod(encMethod) != BLOWFISH)) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid encryption method.");
      throw DRMInfoException();
    }
    if (contentID == "") {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid content identifier.");
      throw DRMInfoException();
    }
    if (toolID != OPENIPMP_TOOLID) {
      logger.UpdateLog("OpenIPMPDRMInfo::ctor: invalid openIPMP tool identifier.");
      throw DRMInfoException();
    }
  }

  /*! \brief  Copy constructor.
  */
  OpenIPMPDRMInfo(const OpenIPMPDRMInfo& info): encMethod(info.encMethod),
    contentID(info.contentID), toolID(info.toolID), rightsHost(info.rightsHost) {
  }

  /*! \brief  Get encryption method.

      \returns           Code representing encryption method.
  */
  ByteT GetEncMethod() const {
    return encMethod;
  }

  /*! \brief  Get content identifier identifying the content.

      \returns           String representing content identifier.
  */
  const std::string& GetContentID() const {
    return contentID;
  }
/*
  std::string& GetContentID() {
    return contentID;
  }
*/
  /*! \brief  Get tool identifier identifying the openIPMP protection.

      \returns           String representing tool identifier.
  */
  const std::string& GetToolID() const {
    return toolID;
  }

  /*! \brief  Get rights host identifier (URL).

      \returns           String representing rights host.
  */
  const std::string& GetRightsHost() const {
    return rightsHost;
  }
/*
  std::string& GetRightsHost() {
    return rightsHost;
  }
*/
private:
  ByteT encMethod;
  std::string contentID;
  std::string toolID;
  std::string rightsHost;
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPDRMINFO_H)
