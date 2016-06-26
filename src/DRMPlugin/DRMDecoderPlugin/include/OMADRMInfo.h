/**	\file OMADRMInfo.h

	OMA DRM information.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OMADRMINFO_H)
#define OMADRMINFO_H

#include <string>
#include "BasicTypes.h"
#include "DRMInfoException.h"
#include "DRMLogger.h"
#include "ICipher.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief OMA DRM information.

    Contains information that is used for DRM functionality.
*/
class OMADRMInfo {
public:
  /*! \brief  Constructor.

      \param    eMethod           input, encryption method code.
      \param    ePadding          input, encryption padding code.
      \param    pTLen             input, plaintext length.
      \param    conID             input, content identifier.
      \param    s_version         input, OMA scheme version.
      \param    url               input, rights issuer's URL.
      \param    headers           input, encoded OMA headers.
      \param    headersLen        input, length of the encoded OMA headers.
      \param    logger            input-output, message logger.

      If fails, throws DRMInfoException and logger's log contains error
      description.
  */
  OMADRMInfo(ByteT eMethod, ByteT ePadding, UInt64T pTLen, const std::string& conID,
      UInt16T s_version, const std::string& url, ByteT* headers, UInt16T headersLen,
      DRMLogger& logger): encMethod(eMethod), encPadding(ePadding), pTextLen(pTLen),
      contentID(conID), schemeVersion(s_version), riURL(url), silentHdr(),
      previewHdr(), contentURL(), contentVer(), contentLoc() {
    if (contentID == "") {
      logger.UpdateLog("OMADRMInfo::ctor: invalid content identifier.");
      throw DRMInfoException();
    }
    if (EncMethod(encMethod) == NULLENC) {
      if (encPadding != 0) {
        logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method/padding.");
        throw DRMInfoException();
      }
    } else if (EncMethod(encMethod) == AES128CBC) {
      if (encPadding != 1) {
        logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method/padding.");
        throw DRMInfoException();
      }
    } else if (EncMethod(encMethod) == AES128CTR) {
      if (encPadding != 0) {
        logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method/padding.");
        throw DRMInfoException();
      }
    } else {
      logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method.");
      throw DRMInfoException();
    }
    if (schemeVersion != 0x0200) {
      logger.UpdateLog("OMADRMInfo::ctor: unsupported version.");
      throw DRMInfoException();
    }

    if ((headers != 0) && (headersLen != 0)) {
      std::basic_string<char> tHdr((char*)headers, (char*)(headers + headersLen));
      int index = 0, ret;
      while (index < headersLen) {
        ret = tHdr.find('\0', index);
        if (ret == -1) {
          logger.UpdateLog("OMADRMInfo::ctor: invalid data while parsing OMA textual headers.");
          throw DRMInfoException();
          break;
        }
        std::string sub = (char*)(tHdr.data() + index);
        index = (ret + 1);
        ret = sub.find_first_of(':', 0);
        if (ret == -1) {
          logger.UpdateLog("OMADRMInfo::ctor: invalid data while parsing OMA textual headers.");
          throw DRMInfoException();
          break;
        }
        std::string htype(sub.begin(), sub.begin() + ret);
	      if (htype == "Silent") {
          silentHdr = sub;
	      } else if (htype == "Preview") {
          previewHdr = sub;
	      } else if (htype == "ContentURL") {
          contentURL = sub;
	      } else if (htype == "ContentVersion") {
          contentVer = sub;
	      } else if (htype == "Content-Location") {
          contentLoc = sub;
        } else {
          // Custom header. Ignore.
        }
      }
    }
  }

  /*! \brief  Constructor.

      \param    eMethod           input, encryption method code.
      \param    ePadding          input, encryption padding code.
      \param    pTLen             input, plaintext length.
      \param    conID             input, content identifier.
      \param    s_version         input, OMA scheme version.
      \param    url               input, rights issuer's URL.
      \param    silent            input, silent header.
      \param    preview           input, preview header.
      \param    conURL            input, content URL header.
      \param    conVer            input, content version header.
      \param    conLoc            input, content location header.
      \param    logger            input-output, message logger.

      If fails, throws DRMInfoException and logger's log contains error
      description.
  */
  OMADRMInfo(ByteT eMethod, ByteT ePadding, UInt64T pTLen, const std::string& conID,
      UInt16T s_version, const std::string& url, const std::string& silent,
      const std::string& preview, const std::string& conURL, const std::string&
      conVer, const std::string& conLoc, DRMLogger& logger): encMethod(eMethod),
      encPadding(ePadding), pTextLen(pTLen), contentID(conID), schemeVersion(s_version),
      riURL(url), silentHdr(silent), previewHdr(preview), contentURL(conURL),
      contentVer(conVer), contentLoc(conLoc) {
    if (contentID == "") {
      logger.UpdateLog("OMADRMInfo::ctor: invalid content identifier.");
      throw DRMInfoException();
    }
    if (EncMethod(encMethod) == NULLENC) {
      if (encPadding != 0) {
        logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method/padding.");
        throw DRMInfoException();
      }
    } else if (EncMethod(encMethod) == AES128CBC) {
      if (encPadding != 1) {
        logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method/padding.");
        throw DRMInfoException();
      }
    } else if (EncMethod(encMethod) == AES128CTR) {
      if (encPadding != 0) {
        logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method/padding.");
        throw DRMInfoException();
      }
    } else {
      logger.UpdateLog("OMADRMInfo::ctor: invalid encryption method.");
      throw DRMInfoException();
    }
    if (schemeVersion != 0x0200) {
      logger.UpdateLog("OMADRMInfo::ctor: unsupported version.");
      throw DRMInfoException();
    }
  }

  /*! \brief  Copy constructor.
  */
  OMADRMInfo(const OMADRMInfo& info): encMethod(info.encMethod),
    encPadding(info.encPadding), pTextLen(info.pTextLen), contentID(info.contentID),
    schemeVersion(info.schemeVersion), riURL(info.riURL), silentHdr(info.silentHdr),
    previewHdr(info.previewHdr), contentURL(info.contentURL),
    contentVer(info.contentVer), contentLoc(info.contentLoc) {
  }

  /*! \brief  Get encryption method.

      \returns           Code representing encryption method.
  */
  ByteT GetEncMethod() const {
    return encMethod;
  }

  /*! \brief  Get encryption padding.

      \returns           Code representing encryption padding.
  */
  ByteT GetEncPadding() const {
    return encPadding;
  }

  /*! \brief  Get plaintext length.

      \returns           Plaintext length.
  */
  UInt64T GetPlaintextLen() const {
    return pTextLen;
  }

  /*! \brief  Get content identifier identifying the DRM.

      \returns           String representing content identifier.
  */
  const std::string& GetContentID() const {
    return contentID;
  }

  /*! \brief  Get scheme version of the OMA DRM scheme.

      \returns           Integer representing version of the OMA DRM scheme.
  */
  UInt16T GetSchemeVersion() const {
    return schemeVersion;
  }

  /*! \brief  Get URL of the rights issuer.
  
      Rights issuer is in charge of the rights management for the DRM
      identified with DRM ID.

      \returns          String representing URL of the rights issuer.
  */
  const std::string& GetRightsIssuerURL() const {
    return riURL;
  }

  /*! \brief  Get silent textual header.
  
      Silent header indicates that the content rights objects can be
      retrieved silently (without user interaction) from rights issuer.

      Format for the silent text header is:
        - "Silent" ":" <silent-method> ";" <silent-rights-URL>
        - <silent-method> = "on-demand" || "in-advance"
        - <silent-rights-URL> = URL string.

      If silent method is on-demand, then rights objects can be acquired
      from silent-rights-URL when user decides to play the content. If silent
      method is in-advance then rights objects can be acquired from
      silent-rights-URL at the earliest occasion.

      \retval     ""    if doesn't have silent text header.
      \retval   != ""   if has silent text header.
  */
  const std::string& GetSilentTextHeader() const {
    return silentHdr;
  }

  /*! \brief  Get preview textual header.
  
      Preview header indicates that the content can be previewed.

      Format for the preview text header is:
        - "Preview" ":" [("instant" ";" preview-element-URI) ||
            ("preview-rights" ";" preview-rights-URL)]
        - preview-element-URI = URI string
        - preview-rights-URL = URL string.

      \retval     ""    if doesn't have preview text header.
      \retval   != ""   if has preview text header.
  */
  const std::string& GetPreviewTextHeader() const {
    return previewHdr;
  }

  /*! \brief  Get content URL textual header.
  
      Content URL header indicates where the content can be downloaded.

      Format for the content URL text header is:
        - "ContentURL" ":" URL string.

      \retval     ""    if doesn't have content URL text header.
      \retval   != ""   if has content URL text header.
  */
  const std::string& GetContentURLTextHeader() const {
    return contentURL;
  }

  /*! \brief  Get content version.
  
      Content version header indicates version of the content.

      Format for the content version text header is:
        - "ContentVersion" ":" <original-content-identifier> ":" <version-identifier>
        - <original-content-identifier> = string
        - <version-identifier> = string representing integer in range 0..65535.

      \retval     ""    if doesn't have content version text header.
      \retval   != ""   if has content version text header.
  */
  const std::string& GetContentVersionTextHeader() const {
    return contentVer;
  }

  /*! \brief  Get content location textual header.

      Format for the content location text header is:
        - "Content-Location" ":" URI string.

      \retval     ""    if doesn't have content location text header.
      \retval   != ""   if has content location text header.
  */
  const std::string& GetContentLocationTextHeader() const {
    return contentLoc;
  }

private:
  ByteT encMethod;
  ByteT encPadding;
  UInt64T pTextLen;
  std::string contentID;
  UInt16T schemeVersion;
  std::string riURL;
  std::string silentHdr;
  std::string previewHdr;
  std::string contentURL;
  std::string contentVer;
  std::string contentLoc;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMINFO_H)
