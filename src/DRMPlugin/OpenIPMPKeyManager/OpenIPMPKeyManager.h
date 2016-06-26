/**
    \defgroup openipmpkeymanager OpenIPMP key manager documentation.
*/
/**	\file OpenIPMPKeyManager.h

	Key manager which stores keys using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OPENIPMPKEYMANAGER_H)
#define OPENIPMPKEYMANAGER_H

#include "IOpenIPMPMessenger.h"
#include "ICipher.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Exception used for key manager error.
*/
class KeyManagerException {
};

/*! \brief Uses openIPMP infrastructure to store and fetch content encryption keys.

    \ingroup  openipmpkeymanager
*/
class OpenIPMPKeyManager {
public:
  /*! \brief  Constructor.

      \param    xmlDoc          input, XML document.
      \param    logger          input-output, message logger.

      If fails, throws KeyManagerException and logger's log contains error
      message.
  */
  OpenIPMPKeyManager(IXMLElement* xmlDoc, DRMLogger& logger);

  ~OpenIPMPKeyManager();

  /*! \brief  Create blowfish encryptor.
  
      See CreateAndStoreKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  BlowfishEncryptor* CreateBlowfishEnc(std::string& contentID, IXMLElement* xmlDoc);

  /*! \brief  Create blowfish decryptor corresponding to content ID.

      See FetchKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    rHost           input, rights host URL.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created decryptor. If failed, zero pointer.
  */
  BlowfishDecryptor* CreateBlowfishDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc);

  /*! \brief  Create AES128CBC encryptor.
  
      See CreateAndStoreKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  AES128CBCEncryptor* CreateAES128CBCEnc(std::string& contentID, IXMLElement* xmlDoc);

  /*! \brief  Create AES128CBC decryptor corresponding to content ID.

      See FetchKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    rHost           input, rights host URL.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created decryptor. If failed, zero pointer.
  */
  AES128CBCDecryptor* CreateAES128CBCDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc);

  /*! \brief  Create AES128CTR encryptor.
  
      See CreateAndStoreKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  AES128CTREncryptor* CreateAES128CTREnc(std::string& contentID, IXMLElement* xmlDoc);

  /*! \brief  Create AES128CTR decryptor corresponding to content ID.

      See FetchKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    rHost           input, rights host URL.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created decryptor. If failed, zero pointer.
  */
  AES128CTRDecryptor* CreateAES128CTRDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc);

  /*! \brief  Create AES128ICM encryptor.
  
      See CreateAndStoreKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created encryptor. If failed, zero pointer.
  */
  AES128ICMEncryptor* CreateAES128ICMEnc(std::string& contentID, IXMLElement* xmlDoc);

  /*! \brief  Create AES128ICM decryptor corresponding to content ID.

      See FetchKey for correct format of XML document.

      \param    contentID       input, content identifier.
      \param    rHost           input, rights host URL.
      \param    xmlDoc          input, XML document.

      \returns  If successful, newly created decryptor. If failed, zero pointer.
  */
  AES128ICMDecryptor* CreateAES128ICMDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc);

  /*! \brief  Add license for content.

      Optional tags in the XML file are:
       - ROOT.License

      Mandatory tags in the XML file are:
       - ROOT.UserName
       - ROOT.UserPass
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <License>danijelk;2005-08-31;2006-08-31;ODRL</License>
       <UserName>danijelk</UserName>
       <UserPass>ipmp</UserPass>
       <RightsHostURL>localhost:8080</RightsHostURL>
      </ROOT>

      \endverbatim

      \param    contentID       string uniquely identifying the content.
      \param    xmlDoc          XML document.

      \returns  Boolean indicating success or failure.
  */
  bool AddLicense(std::string& contentID, IXMLElement* xmlDoc);

private:
  /*! \brief  Create content encryption key and store it with respect to content ID.

      Mandatory tags in the XML file are:
       - ROOT.UserName
       - ROOT.UserPass
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <UserName>danijelk</UserName>
       <UserPass>ipmp</UserPass>
       <RightsHostURL>localhost:8080</RightsHostURL>
      </ROOT>

      \endverbatim

      \param    doiStr          input-output, (possibly updated) content identifier.
      \param    xmlDoc          input, XML document.
      \param    key             output, newly created key.
      \param    keySize         input, requested key size.

      \returns  Boolean indicating success or failure.
  */
  bool CreateAndStoreKey(std::string& doiStr, IXMLElement* xmlDoc, ByteT** key,
    UInt32T keySize);

  /*! \brief  Fetch content encryption key with respect to content ID.

      Mandatory tags in the XML file are:
       - ROOT.UserName
       - ROOT.UserPass

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <UserName>danijelk</UserName>
       <UserPass>ipmp</UserPass>
      </ROOT>

      \endverbatim

      \param    doiStr          input, content identifier.
      \param    rHost           input, rights host URL.
      \param    xmlDoc          input, XML document.
      \param    key             output, fetched key.
      \param    keySize         output, fetched key size.

      \returns  Boolean indicating success or failure.
  */
  bool FetchKey(const std::string& doiStr, const std::string& rHost,
    IXMLElement* xmlDoc, ByteT** key, UInt32T* keySize);

  /*! \brief  Parse host IP and port from hostURL.

      \param  hostURL         input, host URL string.
      \param  hostIP          output, host IP address.
      \param  hostPort        output, host port.

      \returns  Boolean indicating success or failure.
  */
  bool ParseHostIPPort(const std::string& hostURL, std::string& hostIP, int* hostPort);

  /*! \brief  Parse user name, start date, end date and license type from
              license string.

      \param  license         input, license string.
      \param  userName        output, user name.
      \param  startYear       output, start year.
      \param  startMonth      output, start month.
      \param  startDay        output, start day.
      \param  endYear         output, end year.
      \param  endMonth        output, end month.
      \param  endDay          output, end day.
      \param  licenseType     output, license type.

      \returns  Boolean indicating success or failure.
  */
  bool ParseLicense(const std::string& license, std::string& userName,
    int* startYear, int* startMonth, int* startDay, int* endYear, int* endMonth,
    int* endDay, std::string& licenseType);

  IOpenIPMPMessenger* messenger;
  UInt32T passphrase;
  DRMLogger& openipmpKeyManagerLogger;
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPKEYMANAGER_H)
