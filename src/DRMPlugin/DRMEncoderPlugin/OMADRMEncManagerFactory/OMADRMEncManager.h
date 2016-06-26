/**	\file OMADRMEncManager.h

	OMA DRM manager used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OMADRMENCMANAGER_H)
#define OMADRMENCMANAGER_H

#include "IOMADRMEncCommHandler.h"
#include "IOMADRMEncManager.h"
#include "DRMLogger.h"
#include "OMADRMEncAgent.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM manager used in encoding process. Uses OMADRMEncAgent.

    Creates and stores keys (cipher encryptors), adds licenses for protected
    content. Uses OMA DRM encoding agent.
*/
class OMADRMEncManager: public IOMADRMEncManager {
public:
  /*! \brief  Constructor.

      See OMADRMEncAgent::OMADRMEncAgent for correct format of XML document.

      \param  xml         XML document.
      \param  logger      message logger.

      If fails, throws DRMEncManagerException.
  */
  OMADRMEncManager(IXMLElement* xml, DRMLogger& logger);

  virtual ~OMADRMEncManager();

  /*! \brief  Create blowfish encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

      \param    contentID       string uniquely identifying the content.
      \param    xmlDoc          XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual BlowfishEncryptor* CreateBlowfishEnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Create AES128CBC encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

      \param    contentID       string uniquely identifying the content.
      \param    xmlDoc          XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128CBCEncryptor* CreateAES128CBCEnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Create AES128CTR encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

      \param    contentID       string uniquely identifying the content.
      \param    xmlDoc          XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128CTREncryptor* CreateAES128CTREnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Create AES128ICM encryptor.
  
      Save (a newly created key) with respect to content ID.
      Use the information provided in the given XML document.

      See OMADRMEncAgent::CreateAndStoreKey for correct format of XML document.

      \param    contentID       string uniquely identifying the content.
      \param    xmlDoc          XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  virtual AES128ICMEncryptor* CreateAES128ICMEnc(std::string& contentID,
    IXMLElement* xmlDoc);

  /*! \brief  Add license for content.

      See OMADRMEncAgent::AddLicense for correct format of XML document.

      \param    contentID       string uniquely identifying the content.
      \param    xmlDoc          XML document.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AddLicense(std::string& contentID, IXMLElement* xmlDoc);

private:
  IOMADRMEncCommHandler* comm;
  DRMLogger& managerLogger;
  // Global agent, not destroyed by the manager.
  OMADRMEncAgent* agent;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMENCMANAGER_H)
