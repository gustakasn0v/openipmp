/**	\file IDRMEncManager.h

	DRM manager used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IDRMENCMANAGER_H)
#define IDRMENCMANAGER_H

#include "ICipher.h"
#include "IXMLDocument.h"
#include <string>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for DRM encoding manager error.
*/
class DRMEncManagerException {
};

/*! \brief  DRM manager used in encoding process.

    Creates and stores keys (cipher encryptors), adds licenses for protected
    content.
*/
class IDRMEncManager {
public:
  virtual ~IDRMEncManager() {
  }

  /*! \brief  Create blowfish encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See the specific DRM manager documentation for the correct format of the
      XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual BlowfishEncryptor* CreateBlowfishEnc(std::string& contentID,
    IXMLElement* xmlDoc) = 0;

  /*! \brief  Create AES128CBC encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See the specific DRM manager documentation for the correct format of the
      XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128CBCEncryptor* CreateAES128CBCEnc(std::string& contentID,
    IXMLElement* xmlDoc) = 0;

  /*! \brief  Create AES128CTR encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See the specific DRM manager documentation for the correct format of the
      XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128CTREncryptor* CreateAES128CTREnc(std::string& contentID,
    IXMLElement* xmlDoc) = 0;

  /*! \brief  Create AES128ICM encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See the specific DRM manager documentation for the correct format of the
      XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128ICMEncryptor* CreateAES128ICMEnc(std::string& contentID,
    IXMLElement* xmlDoc) = 0;

  /*! \brief  Add license for content.

      Use the information provided in the given XML document.

      See the specific DRM manager documentation for the correct format of the
      XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddLicense(std::string& contentID, IXMLElement* xmlDoc) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IDRMENCMANAGER_H)
