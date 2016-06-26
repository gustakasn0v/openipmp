/**	\file ISMADRMInfo.h

	ISMA DRM information.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ISMADRMINFO_H)
#define ISMADRMINFO_H

#include <string>
#include "BasicTypes.h"
#include "DRMInfoException.h"
#include "DRMLogger.h"
#include "ICipher.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief ISMA DRM information.

    Contains information that is used for DRM functionality.
*/
class ISMADRMInfo {
public:
  /*! \brief  Constructor.

      \param    data              input, encoded content identifier.
      \param    dataSize          input, length of the encoded content identifier.
      \param    s_version         input, ISMA scheme version.
      \param    k_uri             input, key management system URI.
      \param    selective         input, selective encryption indicator.
      \param    key_ind_len       input, length of the key indicator.
      \param    iv_len            input, length of the initialization vector.
      \param    logger            input-output, message logger.

      If fails, throws DRMInfoException and logger's log contains error
      description.
  */
  ISMADRMInfo(ByteT* data, UInt32T dataSize, UInt16T s_version,
      const std::string& k_uri, bool selective, ByteT key_ind_len, ByteT iv_len,
      DRMLogger& logger): contentID(), schemeVersion(s_version), kmsURI(k_uri),
      selectiveEnc(selective), keyIndicatorLen(key_ind_len), ivLen(iv_len) {
    //! We expect (null-terminated) content identifier in data.
    if ((data == 0) || (dataSize == 0)) {
      logger.UpdateLog("ISMADRMInfo::ctor: invalid data for content identifier.");
      throw DRMInfoException();
    }
    // We must have a null terminated string.
    if (data[dataSize - 1] != '\0') {
      logger.UpdateLog("ISMADRMInfo::ctor: invalid data for content identifier.");
      throw DRMInfoException();
    }
    contentID = (const char*)data;
    if (contentID == "") {
      logger.UpdateLog("ISMADRMInfo::ctor: invalid content identifier.");
      throw DRMInfoException();
    }
  }

  /*! \brief  Constructor.

      \param    conID             input, content identifier.
      \param    s_version         input, ISMA scheme version.
      \param    k_uri             input, key management system URI.
      \param    selective         input, selective encryption indicator.
      \param    key_ind_len       input, length of the key indicator.
      \param    iv_len            input, length of the initialization vector.
      \param    logger            input-output, message logger.

      If fails, throws DRMInfoException and logger's log contains error
      description.
  */
  ISMADRMInfo(const std::string& conID, UInt16T s_version,
      const std::string& k_uri, bool selective, ByteT key_ind_len, ByteT iv_len,
      DRMLogger& logger): contentID(conID), schemeVersion(s_version), kmsURI(k_uri),
      selectiveEnc(selective), keyIndicatorLen(key_ind_len), ivLen(iv_len) {
    if (contentID == "") {
      logger.UpdateLog("ISMADRMInfo::ctor: invalid content identifier.");
      throw DRMInfoException();
    }
  }

  /*! \brief  Copy constructor.
  */
  ISMADRMInfo(const ISMADRMInfo& info): contentID(info.contentID),
    schemeVersion(info.schemeVersion), kmsURI(info.kmsURI),
    selectiveEnc(info.selectiveEnc), keyIndicatorLen(info.keyIndicatorLen),
    ivLen(info.ivLen) {
  }

  /*! \brief  Get content identifier identifying the content.

      \returns           String representing content identifier.
  */
  const std::string& GetContentID() const {
    return contentID;
  }

  /*! \brief  Get scheme version of the ISMA DRM scheme.

      \returns           Integer representing version of the ISMA DRM scheme.
  */
  UInt16T GetSchemeVersion() const {
    return schemeVersion;
  }

  /*! \brief  Get URI of the key management system.

      \returns           URI of the key management system.
  */
  const std::string& GetKmsUri() const {
    return kmsURI;
  }

  /*! \brief  Get selective encryption indicator.

      \returns           Selective encryption indicator.
  */
  bool GetSelectiveEnc() const {
    return selectiveEnc;
  }

  /*! \brief  Get key indicator length.

      \returns           Key indicator length.
  */
  ByteT GetKeyIndicatorLen() const {
    return keyIndicatorLen;
  }

  /*! \brief  Get IV length.

      \returns           IV length.
  */
  ByteT GetIVLen() const {
    return ivLen;
  }

  /*! \brief  Get encryption method.

      \returns           Code representing the encryption method.
  */
  ByteT GetEncMethod() const {
    return (ByteT)AES128ICM;
  }

private:
  std::string contentID;
  UInt16T schemeVersion;
  std::string kmsURI;
  bool selectiveEnc;
  ByteT keyIndicatorLen;
  ByteT ivLen;
};

} // namespace DRMPlugin

#endif // !defined (ISMADRMINFO_H)
