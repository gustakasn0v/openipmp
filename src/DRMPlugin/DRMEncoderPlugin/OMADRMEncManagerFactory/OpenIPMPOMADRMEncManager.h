/**	\file OpenIPMPOMADRMEncManager.h

	OMA DRM encoding manager using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPOMADRMENCMANAGER_H)
#define OPENIPMPOMADRMENCMANAGER_H

#include "IXMLDocument.h"
#include "DRMLogger.h"
#include <string>
#include "IDRMEncManager.h"
#include "IOMADRMEncManager.h"
#include "OpenIPMPKeyManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM encoding manager using openIPMP infrastructure.

    Creates and stores keys (cipher encryptors), adds licenses for protected
    content.
*/
class OpenIPMPOMADRMEncManager: public IOMADRMEncManager {
public:
  /*! \brief  Constructor.

      See OpenIPMPKeyManager::OpenIPMPKeyManager for correct format of
      XML document.

      \param  xml         XML document.
      \param  logger      message logger.
  */
  OpenIPMPOMADRMEncManager(IXMLElement* xml, DRMLogger& logger);

  virtual ~OpenIPMPOMADRMEncManager();

  /*! \brief  Create blowfish encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OpenIPMPKeyManager::CreateBlowfishEnc for correct format
      of XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual BlowfishEncryptor* CreateBlowfishEnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Create AES128CBC encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OpenIPMPKeyManager::CreateAES128CBCEnc for correct format
      of XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128CBCEncryptor* CreateAES128CBCEnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Create AES128CTR encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OpenIPMPKeyManager::CreateAES128CTREnc for correct format
      of XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128CTREncryptor* CreateAES128CTREnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Create AES128ICM encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OpenIPMPKeyManager::CreateAES128ICMEnc for correct format
      of XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128ICMEncryptor* CreateAES128ICMEnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Add license for content.

      See OpenIPMPKeyManager::AddLicense for correct format of XML document.

      \param    contentID       input-output, string uniquely identifying the content.
      \param    xmlDoc          input, XML document.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddLicense(std::string& contentID, IXMLElement* xmlDoc);

private:
  OpenIPMPKeyManager* manager;
  DRMLogger& managerLogger;
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPOMADRMENCMANAGER_H)
