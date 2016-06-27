/**	\file OpenIPMPKeyManager.cpp

	Key manager which stores keys using openIPMP infrastructure.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPKeyManager.h"
#include "CipherFactory.h"
#include "OpenIPMPMessengerFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Uses openIPMP infrastructure to store and fetch content encryption keys.
*/
/*! \brief  Constructor.

    \param    xmlDoc          input, XML document.
    \param    logger          input-output, message logger.

    If fails, throws KeyManagerException and logger's log contains error
    message.
*/
OpenIPMPKeyManager::OpenIPMPKeyManager(IXMLElement* xmlDoc, DRMLogger& logger):
    messenger(OpenIPMPMessengerFactory::GetMessenger(xmlDoc, logger)),
    passphrase(0x11223344), openipmpKeyManagerLogger(logger) {
  if (messenger == 0) {
    throw KeyManagerException();
  }
}

OpenIPMPKeyManager::~OpenIPMPKeyManager() {
  if (messenger != 0) delete messenger; messenger = 0;
}

/*! \brief  Create blowfish encryptor.

    See CreateAndStoreKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
BlowfishEncryptor* OpenIPMPKeyManager::CreateBlowfishEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 16;

  if (CreateAndStoreKey(contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  return CipherFactory::GetBlowfishEncryptor(key, keySize, openipmpKeyManagerLogger);
}

/*! \brief  Create blowfish decryptor corresponding to content ID.

    See FetchKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    rHost           input, rights host URL.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created decryptor. If failed, zero pointer.
*/
BlowfishDecryptor* OpenIPMPKeyManager::CreateBlowfishDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 0;

  if (FetchKey(contentID, rHost, xmlDoc, &key, &keySize) == false) {
    return 0;
  }

  return CipherFactory::GetBlowfishDecryptor(key, keySize, openipmpKeyManagerLogger);
}

/*! \brief  Create AES128CBC encryptor.

    See CreateAndStoreKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128CBCEncryptor* OpenIPMPKeyManager::CreateAES128CBCEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 16;

  if (CreateAndStoreKey(contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  ByteT* i;
  if (CipherFactory::RndGenerate(&i, keySize) == false) {
    if (key) free(key);
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAES128CBCEnc: random generate error...");
    return 0; 
  }

  return CipherFactory::GetAES128CBCEncryptor(key, keySize, i, openipmpKeyManagerLogger);
}

/*! \brief  Create AES128CBC decryptor corresponding to content ID.

    See FetchKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    rHost           input, rights host URL.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created decryptor. If failed, zero pointer.
*/
AES128CBCDecryptor* OpenIPMPKeyManager::CreateAES128CBCDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 0;

  if (FetchKey(contentID, rHost, xmlDoc, &key, &keySize) == false) {
    return 0;
  }

  if (keySize != 16) {
    if (key) free(key);
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAES128CBCDec: wrong key size...");
    return 0;
  }

  return CipherFactory::GetAES128CBCDecryptor(key, keySize, openipmpKeyManagerLogger);
}

/*! \brief  Create AES128CTR encryptor.

    See CreateAndStoreKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128CTREncryptor* OpenIPMPKeyManager::CreateAES128CTREnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 16;

  if (CreateAndStoreKey(contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  ByteT* i;
  if (CipherFactory::RndGenerate(&i, keySize) == false) {
    if (key) free(key);
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAES128CTREnc: random generate error...");
    return 0; 
  }

  return CipherFactory::GetAES128CTREncryptor(key, keySize, i, openipmpKeyManagerLogger);
}

/*! \brief  Create AES128CTR decryptor corresponding to content ID.

    See FetchKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    rHost           input, rights host URL.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created decryptor. If failed, zero pointer.
*/
AES128CTRDecryptor* OpenIPMPKeyManager::CreateAES128CTRDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 0;

  if (FetchKey(contentID, rHost, xmlDoc, &key, &keySize) == false) {
    return 0;
  }

  if (keySize != 16) {
    if (key) free(key);
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAES128CTRDec: wrong key size...");
    return 0;
  }

  return CipherFactory::GetAES128CTRDecryptor(key, keySize, openipmpKeyManagerLogger);
}

/*! \brief  Create AES128ICM encryptor.

    See CreateAndStoreKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created encryptor. If failed, zero pointer.
*/
AES128ICMEncryptor* OpenIPMPKeyManager::CreateAES128ICMEnc(std::string& contentID,
    IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 16;

  if (CreateAndStoreKey(contentID, xmlDoc, &key, keySize) == false) {
    return 0;
  }

  ByteT* aes_overlay = (ByteT*)malloc(24);
  if (aes_overlay == 0) {
    if (key) free(key);
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAES128ICMEnc: memory allocation error...");
    return 0;
  }
  memcpy(aes_overlay, key, keySize);
  if (key) free(key);
  ByteT* tmp;
  if (CipherFactory::RndGenerate(&tmp, 8) == false) {
    if (aes_overlay) free(aes_overlay);
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAES128ICMEnc: random generate error...");
    return 0; 
  }
  memcpy(aes_overlay + keySize, tmp, 8);
  free(tmp);

  return CipherFactory::GetAES128ICMEncryptor(aes_overlay, 24, openipmpKeyManagerLogger);
}

/*! \brief  Create AES128ICM decryptor corresponding to content ID.

    See FetchKey for correct format of XML document.

    \param    contentID       input, content identifier.
    \param    rHost           input, rights host URL.
    \param    xmlDoc          input, XML document.

    \returns  If successful, newly created decryptor. If failed, zero pointer.
*/
AES128ICMDecryptor* OpenIPMPKeyManager::CreateAES128ICMDec(const std::string& contentID,
    const std::string& rHost, IXMLElement* xmlDoc) {
  ByteT* key;
  UInt32T keySize = 0;

  if (FetchKey(contentID, rHost, xmlDoc, &key, &keySize) == false) {
    return 0;
  }

  if (keySize != 16) {
    if (key) free(key);
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAES128ICMDec: wrong key size...");
    return 0;
  }

  return CipherFactory::GetAES128ICMDecryptor(key, keySize, openipmpKeyManagerLogger);
}

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
bool OpenIPMPKeyManager::CreateAndStoreKey(std::string& doiStr, IXMLElement* xmlDoc,
    ByteT** key, UInt32T keySize) {

  openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey:...");

  if (xmlDoc == 0) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey: zero XML file...");
    return false;
  }
  std::string name;
  std::string pass;
  std::string host;
  try {
    name = xmlDoc->GetChildStrValue("UserName");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey: missing user name in XML file...");
    return false;
  }
  try {
    pass = xmlDoc->GetChildStrValue("UserPass");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey: missing user password in XML file...");
    return false;
  }
  try {
    host = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey: missing rights host in XML file...");
    return false;
  }
  std::string hostIP;
  int hostPort;
  if (ParseHostIPPort(host, hostIP, &hostPort) == false) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey: could not parse host IP and port...");
    return false;
  }

  //  Generate random key
  if (CipherFactory::RndGenerate(key, keySize) == false) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey: random generate error...");
    return false; 
  }

  if (messenger->RegisterKeyForContent(name, pass, hostIP, hostPort, *key,
      keySize, doiStr) == false) {
    if (*key) free(*key);
    return false;
  }

  openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::CreateAndStoreKey: ok...");
  
  return true;
}

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
bool OpenIPMPKeyManager::FetchKey(const std::string& doiStr, const std::string& rHost,
    IXMLElement* xmlDoc, ByteT** key, UInt32T* keySize) {

  openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::FetchKey:...");

  if (xmlDoc == 0) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::FetchKey: zero XML file...");
    return false;
  }
  std::string user;
  std::string pass;
  try {
    user = xmlDoc->GetChildStrValue("UserName");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::FetchKey: missing user name in XML file...");
    return false;
  }
  try {
    pass = xmlDoc->GetChildStrValue("UserPass");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::FetchKey: missing user password in XML file...");
    return false;
  }
  std::string hostIP;
  int hostPort;
  if (ParseHostIPPort(rHost, hostIP, &hostPort) == false) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::FetchKey: could not parse host IP and port...");
    return false;
  }

  bool ret = messenger->GetKeyForContent(user, pass, hostIP, hostPort, key, keySize, doiStr);

  if (ret == true) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::FetchKey: ok...");
  } else {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::FetchKey: failed...");
  }

  return ret;
}

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
bool OpenIPMPKeyManager::AddLicense(std::string& contentID, IXMLElement* xmlDoc) {
  if (xmlDoc == 0) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: zero XML file...");
  }
  std::string user;
  std::string pass;
  std::string host;
  try {
    user = xmlDoc->GetChildStrValue("UserName");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: missing user name in XML file...");
    return false;
  }
  try {
    pass = xmlDoc->GetChildStrValue("UserPass");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: missing user password in XML file...");
    return false;
  }
  try {
    host = xmlDoc->GetChildStrValue("RightsHostURL");
  }
  catch (XMLException) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: missing rights host URL in XML file...");
    return false;
  }
  std::string hostIP;
  int hostPort;
  if (ParseHostIPPort(host, hostIP, &hostPort) == false) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: could not parse host IP and port...");
    return false;
  }

  std::vector<IXMLElement*> license = xmlDoc->GetChildElementsByName("License");
  for (unsigned int i = 0; i < license.size(); i++) {
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense:...");
    std::string licenseData;
    try {
      licenseData = license[i]->GetStrValue();
    }
    catch (XMLException) {
      continue;
    }

    std::string grantee, licenseType;
    int startYear, startMonth, startDay, endYear, endMonth, endDay;
    if (ParseLicense(licenseData, grantee, &startYear, &startMonth, &startDay,
        &endYear, &endMonth, &endDay, licenseType) == false) {
      openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: unrecognized license " + licenseData + "...");
      continue;
    }

    if (messenger->GrantLicenseForContent(user, pass, hostIP, hostPort,
        contentID, grantee, licenseType, startYear, startMonth, startDay, endYear,
        endMonth, endDay) == false) {
      openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: failed...");
      return false;
    }
    openipmpKeyManagerLogger.UpdateLog("OpenIPMPKeyManager::AddLicense: ok...");
  }

  return true;
}

/*! \brief  Parse host IP and port from hostURL.

    \param  hostURL         input, host URL string.
    \param  hostIP          output, host IP address.
    \param  hostPort        output, host port.

    \returns  Boolean indicating success or failure.
*/
bool OpenIPMPKeyManager::ParseHostIPPort(const std::string& hostURL,
    std::string& hostIP, int* hostPort) {
  char* colon = const_cast<char*>(strchr(hostURL.data(), ':'));
  if (colon == NULL) {
    return false;
  }
  hostIP = std::string(hostURL.begin(), std::string::const_iterator(colon));
  *hostPort = atoi(++colon);
  return true;
}

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
bool OpenIPMPKeyManager::ParseLicense(const std::string& license, std::string& userName,
    int* startYear, int* startMonth, int* startDay, int* endYear, int* endMonth,
    int* endDay, std::string& licenseType) {
  char *semi1, *semi2;
  char *hyphen1, *hyphen2;

  semi1 = const_cast<char*>(strchr(license.data(), ';'));
  if (semi1 == NULL) {
    return false;
  }
  userName = std::string(license.begin(), std::string::const_iterator(semi1));

  semi2 = strchr(++semi1, ';');
  if (semi2 == NULL) {
    return false;
  }
  std::string startDate = std::string(std::string::iterator(semi1), std::string::iterator(semi2));
  hyphen1 = const_cast<char*>(strchr(startDate.data(), '-'));
  if (hyphen1 == NULL) {
    return false;
  }
  std::string tmp = std::string(startDate.begin(), std::string::iterator(hyphen1));
  *startYear = atoi(tmp.data());
  hyphen2 = strchr(++hyphen1, '-');
  if (hyphen2 == NULL) {
    return false;
  }
  tmp = std::string(std::string::iterator(hyphen1), std::string::iterator(hyphen2));
  *startMonth = atoi(tmp.data());
  *startDay = atoi(++hyphen2);

  semi1 = strchr(++semi2, ';');
  if (semi1 == NULL) {
    return false;
  }
  std::string endDate = std::string(std::string::iterator(semi2), std::string::iterator(semi1));
  hyphen1 = const_cast<char*>(strchr(endDate.data(), '-'));
  if (hyphen1 == NULL) {
    return false;
  }
  tmp = std::string(endDate.begin(), std::string::iterator(hyphen1));
  *endYear = atoi(tmp.data());
  hyphen2 = strchr(++hyphen1, '-');
  if (hyphen2 == NULL) {
    return false;
  }
  tmp = std::string(std::string::iterator(hyphen1), std::string::iterator(hyphen2));
  *endMonth = atoi(tmp.data());
  *endDay = atoi(++hyphen2);

  licenseType = std::string(std::string::const_iterator(++semi1), license.end());
  return true;
}

} // namespace DRMPlugin
