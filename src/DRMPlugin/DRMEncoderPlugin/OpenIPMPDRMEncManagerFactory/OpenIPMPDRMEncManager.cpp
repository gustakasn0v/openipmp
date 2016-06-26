/**	\file OpenIPMPDRMEncManager.cpp

	OpenIPMP DRM encoding manager.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "IXMLDocument.h"
#include "DRMLogger.h"
#include <string>
#include "IDRMEncManager.h"
#include "IOpenIPMPDRMEncManager.h"
#include "OpenIPMPKeyManager.h"
#include "OpenIPMPDRMEncManager.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Constructor.

    See OpenIPMPKeyManager::OpenIPMPKeyManager for correct format
    of XML document.

    \param  xml         XML document.
    \param  logger      message logger.
*/
OpenIPMPDRMEncManager::OpenIPMPDRMEncManager(IXMLElement* xml, DRMLogger& logger):
  manager(new OpenIPMPKeyManager(xml, logger)), managerLogger(logger) {
}

OpenIPMPDRMEncManager::~OpenIPMPDRMEncManager() {
  if (manager != 0) delete manager; manager = 0;
}

/*! \brief  Create blowfish encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OpenIPMPKeyManager::CreateBlowfishEnc for correct format
    of XML document.

    \param    contentID       input-output, string uniquely identifying the content.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
BlowfishEncryptor* OpenIPMPDRMEncManager::CreateBlowfishEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  return manager->CreateBlowfishEnc(contentID, xmlDoc);
}

/*! \brief  Create AES128CBC encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OpenIPMPKeyManager::CreateAES128CBCEnc for correct format
    of XML document.

    \param    contentID       input-output, string uniquely identifying the content.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128CBCEncryptor* OpenIPMPDRMEncManager::CreateAES128CBCEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  return manager->CreateAES128CBCEnc(contentID, xmlDoc);
}

/*! \brief  Create AES128CTR encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OpenIPMPKeyManager::CreateAES128CTREnc for correct format
    of XML document.

    \param    contentID       input-output, string uniquely identifying the content.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128CTREncryptor* OpenIPMPDRMEncManager::CreateAES128CTREnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  return manager->CreateAES128CTREnc(contentID, xmlDoc);
}

/*! \brief  Create AES128ICM encryptor.

    Save (a newly created key) with respect to content ID.
    Use the information provided in the given XML document.

    See OpenIPMPKeyManager::CreateAES128ICMEnc for correct format
    of XML document.

    \param    contentID       input-output, string uniquely identifying the content.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128ICMEncryptor* OpenIPMPDRMEncManager::CreateAES128ICMEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  return manager->CreateAES128ICMEnc(contentID, xmlDoc);
}

/*! \brief  Add license for content.

    See OpenIPMPKeyManager::AddLicense for correct format of XML document.

    \param    contentID       input-output, string uniquely identifying the content.
    \param    xmlDoc          input, XML document.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPDRMEncManager::AddLicense(std::string& contentID, IXMLElement* xmlDoc) {
  return manager->AddLicense(contentID, xmlDoc);
}

} // namespace DRMPlugin
