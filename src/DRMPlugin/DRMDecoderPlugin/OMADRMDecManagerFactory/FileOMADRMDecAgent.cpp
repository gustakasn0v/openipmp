/** \file FileOMADRMDecAgent.cpp

    Implementation of agent handling OMA DRM device messages.
    Uses file storage databases.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "FileOMADRMDecAgent.h"
#include "PublicCryptoFactory.h"
#include "OMADRMCommon.h"
#include "DRMDecManagerException.h"
#include "Base64Factory.h"
#include "XMLFactory.h"
#include "ROAPParser.h"

#include <sys/stat.h>
#include <iostream>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Caching agent's rights issuer context factory (parser).
*/
/*! \brief  Create (parse) caching agent's rights issuer context.

    \param  xml       input, XML document.
    \param  logger    input, message logger.

    \returns  New rights issuer context. If fails, throws DRMDecManagerException.
*/
SPtr<CacheAgentRIContext> CacheAgentRIContextFactory::ParseContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("PublicCert") == 0) {
      throw DRMDecManagerException();
    }
    Base64StringT enc(xml->GetChildElement("PublicCert")->GetStrValue());
    ByteSeq data;
    if (Base64Factory::Decode(enc, data) == false) {
      throw DRMDecManagerException();
    }

    std::vector<Base64StringT> ocsps;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("OCSPResponse");
    for (unsigned int i = 0; i < elems.size(); i++) {
      ocsps.push_back(elems[i]->GetStrValue());
    }

    if (xml->GetChildElement("DeviceCertChain") == 0) {
      return new CacheAgentRIContext(
        new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger)),
        ROAPParser::ParseROAPIdentifier(xml->GetChildElement("Identifier"), logger),
        ROAPParser::ParseROAPCertificateChain(xml->GetChildElement("CertChain"), logger),
        ROAPParser::ParseURIValue(xml->GetChildElement("URL"), logger),
        ROAPParser::ParseROAPVersion(xml->GetChildElement("Version"), logger),
        ROAPParser::ParseROAPKeyIdentifiers(xml->GetChildElement("TrustedAuthorities"), logger),
        ParseVector<URIValue, URIValue>(
          xml->GetChildElementsByName("Algorithm"), ROAPParser::ParseURIValue, logger),
        ocsps,
        ROAPParser::ParseDomainNameWhiteListExtension(xml->GetChildElement("WhiteList"), logger),
        ROAPParser::ParseROAPServerInfo(xml->GetChildElement("ServerInfo"), logger));
    } else {
      return new CacheAgentNCacheRIContext(
        new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger)),
        ROAPParser::ParseROAPIdentifier(xml->GetChildElement("Identifier"), logger),
        ROAPParser::ParseROAPCertificateChain(xml->GetChildElement("CertChain"), logger),
        ROAPParser::ParseURIValue(xml->GetChildElement("URL"), logger),
        ROAPParser::ParseROAPVersion(xml->GetChildElement("Version"), logger),
        ROAPParser::ParseROAPKeyIdentifiers(xml->GetChildElement("TrustedAuthorities"), logger),
        ParseVector<URIValue, URIValue>(
          xml->GetChildElementsByName("Algorithm"), ROAPParser::ParseURIValue, logger),
        ocsps,
        ROAPParser::ParseDomainNameWhiteListExtension(xml->GetChildElement("WhiteList"), logger),
        ROAPParser::ParseROAPServerInfo(xml->GetChildElement("ServerInfo"), logger),
        ROAPParser::ParseROAPCertificateChain(xml->GetChildElement("DeviceCertChain"), logger));
    }
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }
  catch (GCException) {
    throw DRMDecManagerException();
  }
  catch (ROAPParserException) {
    throw DRMDecManagerException();
  }
}

/*! \brief  Non-caching agent's rights issuer context factory (parser).
*/
/*! \brief  Create (parse) non-caching agent's rights issuer context.

    \param  xml       input, XML document.
    \param  logger    input, message logger.

    \returns  New rights issuer context. If fails, throws DRMDecManagerException.
*/
SPtr<NCacheAgentRIContext> NCacheAgentRIContextFactory::ParseContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("PublicCert") == 0) {
      throw DRMDecManagerException();
    }
    Base64StringT enc(xml->GetChildElement("PublicCert")->GetStrValue());
    ByteSeq data;
    if (Base64Factory::Decode(enc, data) == false) {
      throw DRMDecManagerException();
    }

    std::vector<Base64StringT> ocsps;
    std::vector<IXMLElement*> elems = xml->GetChildElementsByName("OCSPResponse");
    for (unsigned int i = 0; i < elems.size(); i++) {
      ocsps.push_back(elems[i]->GetStrValue());
    }

    if (xml->GetChildElement("DeviceCertChain") == 0) {
      return new NCacheAgentRIContext(
        new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger)),
        ROAPParser::ParseROAPIdentifier(xml->GetChildElement("Identifier"), logger),
        ROAPParser::ParseURIValue(xml->GetChildElement("URL"), logger),
        ROAPParser::ParseROAPVersion(xml->GetChildElement("Version"), logger),
        ROAPParser::ParseROAPKeyIdentifiers(xml->GetChildElement("TrustedAuthorities"), logger),
        ParseVector<URIValue, URIValue>(
          xml->GetChildElementsByName("Algorithm"), ROAPParser::ParseURIValue, logger),
        ocsps,
        ROAPParser::ParseDomainNameWhiteListExtension(xml->GetChildElement("WhiteList"), logger),
        ROAPParser::ParseROAPServerInfo(xml->GetChildElement("ServerInfo"), logger));
    } else {
      return new NCacheAgentNCacheRIContext(
        new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger)),
        ROAPParser::ParseROAPIdentifier(xml->GetChildElement("Identifier"), logger),
        ROAPParser::ParseURIValue(xml->GetChildElement("URL"), logger),
        ROAPParser::ParseROAPVersion(xml->GetChildElement("Version"), logger),
        ROAPParser::ParseROAPKeyIdentifiers(xml->GetChildElement("TrustedAuthorities"), logger),
        ParseVector<URIValue, URIValue>(
          xml->GetChildElementsByName("Algorithm"), ROAPParser::ParseURIValue, logger),
        ocsps,
        ROAPParser::ParseDomainNameWhiteListExtension(xml->GetChildElement("WhiteList"), logger),
        ROAPParser::ParseROAPServerInfo(xml->GetChildElement("ServerInfo"), logger),
        ROAPParser::ParseROAPCertificateChain(xml->GetChildElement("DeviceCertChain"), logger));
    }
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }
  catch (GCException) {
    throw DRMDecManagerException();
  }
  catch (ROAPParserException) {
    throw DRMDecManagerException();
  }
}

/*! \brief  Constructor.

    Mandatory tags in the XML file are:
     - ROOT.RegDatabasePath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RegDatabasePath>\p12\cacheagentregdb.xml</RegDatabasePath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    If fails, throws DRMDecManagerException.
*/
FileCacheAgentRegDatabase::FileCacheAgentRegDatabase(IXMLElement* xml, DRMLogger& logger): CacheAgentRegDatabase() {
  IXMLElement* fpath = xml->GetChildElement("RegDatabasePath");
  if (fpath == 0) {
    throw DRMDecManagerException();
  }
  try {
    fName = fpath->GetStrValue();
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  struct stat tstat;
  unsigned int byteslen;

  FILE* dbfile = fopen(fName.data(), "rb");
  if (dbfile == NULL) {
    //  Here we assume that database file has not been created.
    return;
  }
  stat(fName.data(), &tstat);
  byteslen = tstat.st_size;
  char* db = (char*)malloc(byteslen + 1);
  fread(db, byteslen, 1, dbfile);
  db[byteslen] = '\0';
  fclose(dbfile);

  std::string xmls = db;
  free(db);

  IXMLDocument* doc = XMLFactory::DecodeDocument(xmls, logger);
  if (doc == 0) {
    throw DRMDecManagerException();
  }

  IXMLElement* root = doc->GetRootElement();
  if (root == 0) {
    delete doc;
    throw DRMDecManagerException();
  }
  if ((root->GetName() != "Database") || (root->GetChildElement("RIContexts") == 0)
      || (root->GetChildElement("Domains") == 0)) {
    delete doc;
    throw DRMDecManagerException();
  }

  //  Check and parse data.
  IXMLElement* next = root->GetChildElement("RIContexts")->GetFirstChild();
  IXMLElement* sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<ROAPIdentifier> id = ROAPParser::ParseROAPIdentifier(next, logger);
      NZSPtr<CacheAgentRIContext> ctx = CacheAgentRIContextFactory::ParseContext(sib, logger);
      riIDToContext[id] = ctx;
    }
    catch (ROAPParserException) {
      delete doc;
      throw DRMDecManagerException();
    }
    catch (GCException) {
      delete doc;
      throw DRMDecManagerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }
  next = root->GetChildElement("Domains")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<ROAPDomainIdentifier> id = ROAPParser::ParseROAPDomainIdentifier(next, logger);
      NZSPtr<ROAPDomainInfo> info = ROAPParser::ParseROAPDomainInfo(sib, logger);
      domainIDToInfo[id] = info;
    }
    catch (ROAPParserException) {
      delete doc;
      throw DRMDecManagerException();
    }
    catch (GCException) {
      delete doc;
      throw DRMDecManagerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  delete doc;
}

/*! \brief  Save database for future use.

    Saves database to the same file that it was read from in constructor.

    \returns  Boolean indicating success or failure.
*/
bool FileCacheAgentRegDatabase::SaveDatabase() {
  std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheAgentRIContext> >::iterator
    iterc = riIDToContext.begin();
  std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> >::iterator
    iterd = domainIDToInfo.begin();

  std::string dbstring = "<Database><RIContexts>";
  std::string tmp;
  while (iterc != riIDToContext.end()) {
    dbstring += iterc->first->XmlEncode("RIIdentifier");
    if (iterc->second->Encode(tmp) == false) {
      return false;
    }
    dbstring += tmp;
    iterc++;
  }
  dbstring += "</RIContexts><Domains>";
  while (iterd != domainIDToInfo.end()) {
    dbstring += iterd->first->XmlEncode("DomainIdentifier");
    dbstring += iterd->second->XmlEncode("DomainInfo");
    iterd++;
  }
  dbstring += "</Domains></Database>";

  FILE* dbfile = fopen(fName.data(), "wb");
  if (dbfile == NULL) {
    return false;
  }
  if (fwrite(dbstring.data(), dbstring.size(), 1, dbfile) != 1) {
    return false;
  }
  fclose(dbfile);

  return true;
}

/*! \brief  Constructor.

    Mandatory tags in the XML file are:
     - ROOT.RegDatabasePath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RegDatabasePath>\p12\ncacheagentregdb.xml</RegDatabasePath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    If fails, throws DRMDecManagerException.
*/
FileNCacheAgentRegDatabase::FileNCacheAgentRegDatabase(IXMLElement* xml, DRMLogger& logger):
    NCacheAgentRegDatabase() {
  IXMLElement* fpath = xml->GetChildElement("RegDatabasePath");
  if (fpath == 0) {
    throw DRMDecManagerException();
  }
  try {
    fName = fpath->GetStrValue();
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  struct stat tstat;
  unsigned int byteslen;

  FILE* dbfile = fopen(fName.data(), "rb");
  if (dbfile == NULL) {
    //  Here we assume that database file has not been created.
    return;
  }
  stat(fName.data(), &tstat);
  byteslen = tstat.st_size;
  char* db = (char*)malloc(byteslen + 1);
  fread(db, byteslen, 1, dbfile);
  db[byteslen] = '\0';
  fclose(dbfile);

  std::string xmls = db;
  free(db);

  IXMLDocument* doc = XMLFactory::DecodeDocument(xmls, logger);
  if (doc == 0) {
    throw DRMDecManagerException();
  }

  IXMLElement* root = doc->GetRootElement();
  if (root == 0) {
    delete doc;
    throw DRMDecManagerException();
  }
  if ((root->GetName() != "Database") || (root->GetChildElement("RIContexts") == 0)
      || (root->GetChildElement("Domains") == 0)) {
    delete doc;
    throw DRMDecManagerException();
  }

  //  Check and parse data.
  IXMLElement* next = root->GetChildElement("RIContexts")->GetFirstChild();
  IXMLElement* sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<ROAPIdentifier> id = ROAPParser::ParseROAPIdentifier(next, logger);
      NZSPtr<NCacheAgentRIContext> ctx = NCacheAgentRIContextFactory::ParseContext(sib, logger);
      riIDToContext[id] = ctx;
    }
    catch (ROAPParserException) {
      delete doc;
      throw DRMDecManagerException();
    }
    catch (GCException) {
      delete doc;
      throw DRMDecManagerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }
  next = root->GetChildElement("Domains")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<ROAPDomainIdentifier> id = ROAPParser::ParseROAPDomainIdentifier(next, logger);
      NZSPtr<ROAPDomainInfo> info = ROAPParser::ParseROAPDomainInfo(sib, logger);
      domainIDToInfo[id] = info;
    }
    catch (ROAPParserException) {
      delete doc;
      throw DRMDecManagerException();
    }
    catch (GCException) {
      delete doc;
      throw DRMDecManagerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  delete doc;
}

/*! \brief  Save database for future use.

    Saves database to the same file that it was read from in constructor.

    \returns  Boolean indicating success or failure.
*/
bool FileNCacheAgentRegDatabase::SaveDatabase() {
  std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheAgentRIContext> >::iterator
    iterc = riIDToContext.begin();
  std::map<NZSPtr<ROAPDomainIdentifier>, SPtr<ROAPDomainInfo> >::iterator
    iterd = domainIDToInfo.begin();

  std::string dbstring = "<Database><RIContexts>";
  std::string tmp;
  while (iterc != riIDToContext.end()) {
    dbstring += iterc->first->XmlEncode("RIIdentifier");
    if (iterc->second->Encode(tmp) == false) {
      return false;
    }
    dbstring += tmp;
    iterc++;
  }
  dbstring += "</RIContexts><Domains>";
  while (iterd != domainIDToInfo.end()) {
    dbstring += iterd->first->XmlEncode("DomainIdentifier");
    dbstring += iterd->second->XmlEncode("DomainInfo");
    iterd++;
  }
  dbstring += "</Domains></Database>";

  FILE* dbfile = fopen(fName.data(), "wb");
  if (dbfile == NULL) {
    return false;
  }
  if (fwrite(dbstring.data(), dbstring.size(), 1, dbfile) != 1) {
    return false;
  }
  fclose(dbfile);

  return true;
}

/*! \brief  Constructor.

    Mandatory tags in the XML file are:
     - ROOT.RODatabasePath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RODatabasePath>\p12\agentrodb.xml</RODatabasePath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    If fails, throws DRMDecManagerException.
*/
FileAgentRODatabase::FileAgentRODatabase(IXMLElement* xml, DRMLogger& logger) {
  IXMLElement* fpath = xml->GetChildElement("RODatabasePath");
  if (fpath == 0) {
    throw DRMDecManagerException();
  }
  try {
    fName = fpath->GetStrValue();
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  struct stat tstat;
  unsigned int byteslen;

  FILE* dbfile = fopen(fName.data(), "rb");
  if (dbfile == NULL) {
    //  Here we assume that database file has not been created.
    return;
  }
  stat(fName.data(), &tstat);
  byteslen = tstat.st_size;
  char* db = (char*)malloc(byteslen + 1);
  fread(db, byteslen, 1, dbfile);
  db[byteslen] = '\0';
  fclose(dbfile);

  std::string xmls = db;
  free(db);

  IXMLDocument* doc = XMLFactory::DecodeDocument(xmls, logger);
  if (doc == 0) {
    throw DRMDecManagerException();
  }

  IXMLElement* root = doc->GetRootElement();
  if (root == 0) {
    delete doc;
    throw DRMDecManagerException();
  }
  if ((root->GetName() != "Database") || (root->GetChildElement("RightsObjects") == 0)
      || (root->GetChildElement("Domains") == 0)) {
    delete doc;
    throw DRMDecManagerException();
  }

  //  Check and parse data.
  IXMLElement* next = root->GetChildElement("RightsObjects")->GetFirstChild();
  IXMLElement* sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<URIValue> url = ROAPParser::ParseURIValue(next, logger);
      NZSPtr<ROAPProtectedRO> ro = ROAPParser::ParseROAPProtectedRO(sib, logger);
      contentIDToRO[url] = ro;
    }
    catch (ROAPParserException) {
      delete doc;
      throw DRMDecManagerException();
    }
    catch (GCException) {
      delete doc;
      throw DRMDecManagerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }
  next = root->GetChildElement("Domains")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<IDValue> id = ROAPParser::ParseIDValue(next, logger);
      NZSPtr<ROAPDomainIdentifier> dom = ROAPParser::ParseROAPDomainIdentifier(sib, logger);
      roIDToDom[id] = dom;
    }
    catch (ROAPParserException) {
      delete doc;
      throw DRMDecManagerException();
    }
    catch (GCException) {
      delete doc;
      throw DRMDecManagerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  delete doc;
}

/*! \brief  Save database for future use.

    Saves database to the same file that it was read from in constructor.

    \returns  Boolean indicating success or failure.
*/
bool FileAgentRODatabase::SaveDatabase() {
  std::map<NZSPtr<URIValue>, SPtr<ROAPProtectedRO> >::iterator
    iterc = contentIDToRO.begin();
  std::map<NZSPtr<IDValue>, SPtr<ROAPDomainIdentifier> >::iterator
    iterd = roIDToDom.begin();

  std::string dbstring = "<Database><RightsObjects>";
  while (iterc != contentIDToRO.end()) {
    dbstring += iterc->first->XmlEncode("ContentID");
    dbstring += iterc->second->XmlEncode("RO");
    iterc++;
  }
  dbstring += "</RightsObjects><Domains>";
  while (iterd != roIDToDom.end()) {
    dbstring += "<ROIdentifier>" + iterd->first->Get() + "</ROIdentifier>";
    dbstring += iterd->second->XmlEncode("DomainIdentifier");
    iterd++;
  }
  dbstring += "</Domains></Database>";

  FILE* dbfile = fopen(fName.data(), "wb");
  if (dbfile == NULL) {
    return false;
  }
  if (fwrite(dbstring.data(), dbstring.size(), 1, dbfile) != 1) {
    return false;
  }
  fclose(dbfile);

  return true;
}

/*! \brief  Constructor.

    See FileOMADRMDecAgent::InitDevCtx documentation for XML document format.

    \param  xmlDoc            XML document.
    \param  logger            message logger.

    If fails, throws DRMDecManagerException.
*/
FileOMADRMDecAgent::FileOMADRMDecAgent(IXMLElement* xmlDoc,
  DRMLogger& logger): OMADRMDecAgent(new OMADRMNonceCreator(), new OSTimer(),
  new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger)),
  new OMACertificateVerifier(PublicCryptoFactory::GetCertificateVerifier(logger)),
  new OSDefTimer(), logger), devicectx(InitDevCtx(xmlDoc, defTimer, logger)),
  regDB(((devicectx->GetCertCaching() == 0)?
    (NZSPtr<AgentRegDatabase>(new FileNCacheAgentRegDatabase(xmlDoc, logger))):
    (NZSPtr<AgentRegDatabase>(new FileCacheAgentRegDatabase(xmlDoc, logger))))),
  roDB(new FileAgentRODatabase(xmlDoc, logger)) {
}

FileOMADRMDecAgent::~FileOMADRMDecAgent() {
  regDB->SaveDatabase();
  roDB->SaveDatabase();
}

/*! \brief  Get device context.

    \returns  Device context.
*/
const NZSPtr<AgentDeviceContext>& FileOMADRMDecAgent::GetDeviceCtx() {
  return devicectx;
}

/*! \brief  Get registration database.

    \returns  Registration database.
*/
NZSPtr<AgentRegDatabase> FileOMADRMDecAgent::GetRegDB() {
  return regDB;
}

/*! \brief  Get rights objects database.

    \returns  Rights objects database.
*/
NZSPtr<AgentRODatabase> FileOMADRMDecAgent::GetRODB() {
  return roDB;
}

/*! \brief  Initialize device context.

    Mandatory tags in the XML file are:
     - ROOT.RegDatabasePath
     - ROOT.RODatabasePath
     - ROOT.CertPath
     - ROOT.PrivateKeyPath
     - ROOT.RootCAPath
     - ROOT.Manufacturer
     - ROOT.Model
     - ROOT.Version
     - ROOT.ROAPVersion
     - ROOT.Caching

    Optional tags in the XML file are:
     - ROOT.TrustedCAPath (can be more than one)
     - ROOT.CertificateChainPath (can be more than one)
     - ROOT.SupportedAlgorithm (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RegDatabasePath>\p12\cacheagentregdb.xml</RegDatabasePath>
     <RODatabasePath>\p12\agentrodb.xml</RODatabasePath>
     <CertPath>\p12\deviceCertSigned.der</CertPath>
     <PrivateKeyPath>\p12\deviceKey.der</PrivateKeyPath>
     <RootCAPath>\p12\OMACACert.der</RootCAPath>
     <Manufacturer>manufacturer</Manufacturer>
     <Model>model</Model>
     <Version>1.0</Version>
     <ROAPVersion>1.0</ROAPVersion>
     <Caching>true</Caching>
     <TrustedCAPath>\p12\OMACACert.der</TrustedCAPath>
     <CertificateChainPath>\p12\chainCert.der</CertificateChainPath>
     <SupportedAlgorithm>md5</SupportedAlgorithm>
     <SupportedAlgorithm>md5rsa</SupportedAlgorithm>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  timer       input, DRM timer.
    \param  logger      input, message logger.

    \returns  Device context. If fails, throws DRMDecManagerException.
*/
NZSPtr<AgentDeviceContext> FileOMADRMDecAgent::InitDevCtx(IXMLElement* xml,
    const NZSPtr<OMADRMDefTimer>& timer, DRMLogger& logger) {
  NZSPtr<OMAPublicCertificate> devicePublicCert = InitPublicCert(xml, timer, logger);
  NZSPtr<OMAPrivateKey> devicePrivateKey = InitPrivateKey(xml, logger);
  NZSPtr<ROAPKeyIdentifier> deviceKeyID = InitKeyID(devicePublicCert, logger);
  NZSPtr<ROAPIdentifier> deviceID = InitID(deviceKeyID, logger);
  NZSPtr<ROAPCertificateChain> deviceCertChain = InitCertChain(xml, logger);
  Base64StringT caCert = InitCA(xml, logger);
  NZSPtr<ROAPKeyIdentifier> caID = InitCAID(caCert, logger);
  std::vector<Base64StringT> deviceTrusted = InitCAs(xml, logger);
  NZSPtr<ROAPKeyIdentifiers> deviceTrustedIDs = InitCAIDs(deviceTrusted, logger);
  NZSPtr<DeviceDetailsData> deviceDetailsData = InitDetails(xml, logger);
  NZSPtr<ROAPVersion> deviceVersion = InitVersion(xml, logger);
  SPtr<CertCachingExtension> deviceCertCaching = InitCaching(xml, logger);
  std::vector<NZSPtr<URIValue> > algorithms = InitAlgorithms(xml, logger);

  return new AgentDeviceContext(devicePublicCert, devicePrivateKey,
    deviceID, deviceCertChain, caID, caCert, deviceTrustedIDs, deviceTrusted,
    algorithms, deviceDetailsData, deviceCertCaching, deviceVersion);
}

/*! \brief  Initialize device public certificate.

    Mandatory tags in the XML file are:
     - ROOT.CertPath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <CertPath>\p12\deviceCertSigned.der</CertPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  timer       input, DRM timer.
    \param  logger      input, message logger.

    \returns  Device public certificate. If fails, throws DRMDecManagerException.
*/
NZSPtr<OMAPublicCertificate> FileOMADRMDecAgent::InitPublicCert(IXMLElement* xml,
    const NZSPtr<OMADRMDefTimer>& timer, DRMLogger& logger) {
  std::string certPath;
  try {
    certPath = xml->GetChildStrValue("CertPath");
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  try {
    NZSPtr<OMAPublicCertificate> ret =
      new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromFile(certPath, logger));
    if (ret->GetExpirationTime() <
        (const TValue<UTCTime>&)FiniteTValue<UTCTime>(timer->GetTime()->GetTime())) {
      throw DRMDecManagerException();
    }
    return ret;
  }
  catch (OMADRMCryptoException) {
    throw DRMDecManagerException();
  }
}

/*! \brief  Initialize device key identifier.

    \param  cer       input, device public certificate.
    \param  logger    input, message logger.

    \returns  Device key identifier. If fails, throws DRMDecManagerException.
*/
NZSPtr<ROAPKeyIdentifier> FileOMADRMDecAgent::InitKeyID(const NZSPtr<OMAPublicCertificate>& cer, DRMLogger& logger) {
  Base64StringT id;
  if (cer->GetKeyIdentifier(new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger)),
      id) == false) {
    throw DRMDecManagerException();
  }
  return new X509SPKIHash(id);
}

/*! \brief  Initialize device identifier.

    \param  keyid       input, device key identifier.

    \returns  Device identifier. If fails, throws DRMDecManagerException.
*/
NZSPtr<ROAPIdentifier> FileOMADRMDecAgent::InitID(const NZSPtr<ROAPKeyIdentifier>& keyid, DRMLogger& logger) {
  return new ROAPIdentifier(keyid);
}

/*! \brief  Initialize device private key.

    Mandatory tags in the XML file are:
     - ROOT.PrivateKeyPath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <PrivateKeyPath>\p12\deviceKey.der</PrivateKeyPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Device private key. If fails, throws DRMDecManagerException.
*/
NZSPtr<OMAPrivateKey> FileOMADRMDecAgent::InitPrivateKey(IXMLElement* xml, DRMLogger& logger) {
  std::string privatePath;
  try {
    privatePath = xml->GetChildStrValue("PrivateKeyPath");
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  try {
    return new OMAPrivateKey(PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyFile(privatePath, logger));
  }
  catch (OMADRMCryptoException) {
    throw DRMDecManagerException();
  }
}

/*! \brief  Initialize device certificate chain.

    Mandatory tags in the XML file are:
     - ROOT.CertPath

    Optional tags in the XML file are:
     - ROOT.CertificateChainPath (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <CertPath>\p12\deviceCertSigned.der</CertPath>
     <CertificateChainPath>\p12\chainCert.der</CertificateChainPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Device certificate chain. If fails, throws DRMDecManagerException.
*/
NZSPtr<ROAPCertificateChain> FileOMADRMDecAgent::InitCertChain(IXMLElement* xml, DRMLogger& logger) {
  std::string certPath;
  try {
    certPath = xml->GetChildStrValue("CertPath");
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  struct stat tstat;

  FILE* certf = fopen(certPath.data(), "rb");
  if (certf == NULL) {
    throw DRMDecManagerException();
  }
  stat(certPath.data(), &tstat);
  unsigned int certbyteslen = tstat.st_size;
  ByteT* certbytes = (ByteT*)malloc(certbyteslen);
  fread(certbytes, certbyteslen, 1, certf);
  fclose(certf);

  std::vector<IXMLElement*> chainPaths = xml->GetChildElementsByName("CertificateChainPath");

  std::vector<Base64StringT> chain(chainPaths.size() + 1, "");
  Base64StringT b64;
  if (Base64Factory::Encode(ByteSeq(certbytes, certbyteslen), b64) == false) {
    free(certbytes);
    throw DRMDecManagerException();
  }
  chain[chainPaths.size()] = b64;
  free(certbytes);

  unsigned int i = 0;
  for (i = 0; i < chainPaths.size(); i++) {
    std::string certPath;
    try {
      certPath = chainPaths[i]->GetStrValue();
    }
    catch (XMLException) {
      throw DRMDecManagerException();
    }
    certf = fopen(certPath.data(), "rb");
    if (certf == NULL) {
      throw DRMDecManagerException();
    }
    stat(certPath.data(), &tstat);
    certbyteslen = tstat.st_size;
    certbytes = (ByteT*)malloc(certbyteslen);
    fread(certbytes, certbyteslen, 1, certf);
    fclose(certf);

    if (Base64Factory::Encode(ByteSeq(certbytes, certbyteslen), b64) == false) {
      free(certbytes);
      throw DRMDecManagerException();
    }
    chain[i] = b64;
    free(certbytes);
  }

  return new ROAPCertificateChain(chain);
}

/*! \brief  Initialize device root CA certificate.

    Mandatory tags in the XML file are:
     - ROOT.RootCAPath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RootCAPath>\p12\OMACACert.der</RootCAPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns Root CA certificate. If fails, throws DRMDecManagerException.
*/
Base64StringT FileOMADRMDecAgent::InitCA(IXMLElement* xml, DRMLogger& logger) {
  std::string certPath;
  try {
    certPath = xml->GetChildStrValue("RootCAPath");
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  struct stat tstat;
  Base64StringT ca;
  FILE* certf = fopen(certPath.data(), "rb");
  if (certf == NULL) {
    throw DRMDecManagerException();
  }
  stat(certPath.data(), &tstat);
  unsigned int certbyteslen = tstat.st_size;
  ByteT* certbytes = (ByteT*)malloc(certbyteslen);
  fread(certbytes, certbyteslen, 1, certf);
  fclose(certf);

  if (Base64Factory::Encode(ByteSeq(certbytes, certbyteslen), ca) == false) {
    free(certbytes);
    throw DRMDecManagerException();
  }
  free(certbytes);

  return ca;
}

/*! \brief  Initialize device root CA key identifier.

    \param  ca          input, root CA certificate.
    \param  logger      input, message logger.

    \returns Root CA key identifier. If fails, throws DRMDecManagerException.
*/
NZSPtr<ROAPKeyIdentifier> FileOMADRMDecAgent::InitCAID(const Base64StringT& ca, DRMLogger& logger) {
  //  Decode from base64.
  ByteSeq data;
  if (Base64Factory::Decode(ca, data) == false) {
    throw DRMDecManagerException();
  }
  //  Create key identifier.
  SPtr<OMAPublicCertificate> cer;
  try {
    cer = new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger));
  }
  catch (OMADRMCryptoException) {
    throw DRMDecManagerException();
  }
  Base64StringT id;
  if (cer->GetKeyIdentifier(new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger)),
      id) == false) {
    throw DRMDecManagerException();
  }
  return new X509SPKIHash(id);
}

/*! \brief  Initialize device trusted CA certificates.

    Optional tags in the XML file are:
     - ROOT.TrustedCAPath (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <TrustedCAPath>\p12\OMACACert.der</TrustedCAPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns Trusted CA certificates. If fails, throws DRMDecManagerException.
*/
std::vector<Base64StringT> FileOMADRMDecAgent::InitCAs(IXMLElement* xml, DRMLogger& logger) {
  std::vector<IXMLElement*> caPaths = xml->GetChildElementsByName("TrustedCAPath");

  struct stat tstat;
  std::vector<Base64StringT> cas;
  Base64StringT b64;
  unsigned int i = 0;
  for (i = 0; i < caPaths.size(); i++) {
    std::string certPath;
    try {
      certPath = caPaths[i]->GetStrValue();
    }
    catch (XMLException) {
      throw DRMDecManagerException();
    }
    FILE* certf = fopen(certPath.data(), "rb");
    if (certf == NULL) {
      throw DRMDecManagerException();
    }
    stat(certPath.data(), &tstat);
    unsigned int certbyteslen = tstat.st_size;
    ByteT* certbytes = (ByteT*)malloc(certbyteslen);
    fread(certbytes, certbyteslen, 1, certf);
    fclose(certf);

    if (Base64Factory::Encode(ByteSeq(certbytes, certbyteslen), b64) == false) {
      free(certbytes);
      throw DRMDecManagerException();
    }
    cas.push_back(b64);
    free(certbytes);
  }

  return cas;
}

/*! \brief  Initialize device trusted CA key identifiers.

    \param  trusted     input, trusted CA certificates.
    \param  logger      input, message logger.

    \returns Trusted CA key identifiers. If fails, throws DRMDecManagerException.
*/
NZSPtr<ROAPKeyIdentifiers> FileOMADRMDecAgent::InitCAIDs(std::vector<Base64StringT>& trusted, DRMLogger& logger) {
  std::vector<NZSPtr<ROAPKeyIdentifier> > ret;
  for (unsigned int i = 0; i < trusted.size(); i++) {
    //  Decode from base64.
    ByteSeq data;
    if (Base64Factory::Decode(trusted[i], data) == false) {
      throw DRMDecManagerException();
    }
    //  Create key identifier.
    SPtr<OMAPublicCertificate> cer;
    try {
      cer = new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger));
    }
    catch (OMADRMCryptoException) {
      throw DRMDecManagerException();
    }
    Base64StringT id;
    if (cer->GetKeyIdentifier(new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger)),
        id) == false) {
      throw DRMDecManagerException();
    }
    ret.push_back(new X509SPKIHash(id));
  }
  return new ROAPKeyIdentifiers(ret);
}

/*! \brief  Initialize device details.

    Mandatory tags in the XML file are:
     - ROOT.Manufacturer
     - ROOT.Model
     - ROOT.Version

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <Manufacturer>manufacturer</Manufacturer>
     <Model>model</Model>
     <Version>1.0</Version>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Device details. If fails, throws DRMDecManagerException.
*/
NZSPtr<DeviceDetailsData> FileOMADRMDecAgent::InitDetails(IXMLElement* xml, DRMLogger& logger) {
  std::string manufacturer;
  std::string model;
  std::string version;
  try {
    manufacturer = xml->GetChildStrValue("Manufacturer");
    model = xml->GetChildStrValue("Model");
    version = xml->GetChildStrValue("Version");
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  return new DeviceDetailsData(manufacturer, model, version);
}

/*! \brief  Initialize device ROAP version.

    Mandatory tags in the XML file are:
     - ROOT.ROAPVersion

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <ROAPVersion>1.0</ROAPVersion>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Device ROAP version. If fails, throws DRMDecManagerException.
*/
NZSPtr<ROAPVersion> FileOMADRMDecAgent::InitVersion(IXMLElement* xml, DRMLogger& logger) {
  std::string roapversion;
  try {
    roapversion = xml->GetChildStrValue("ROAPVersion");
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }

  return new ROAPVersion(roapversion);
}

/*! \brief  Initialize device caching.

    Mandatory tags in the XML file are:
     - ROOT.Caching

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <Caching>false</Caching>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Device caching. If fails, throws DRMDecManagerException.
*/
SPtr<CertCachingExtension> FileOMADRMDecAgent::InitCaching(IXMLElement* xml, DRMLogger& logger) {
  std::string caching;
  try {
    caching = xml->GetChildStrValue("Caching");
  }
  catch (XMLException) {
    throw DRMDecManagerException();
  }
  SPtr<CertCachingExtension> ret;
  if (caching == "true") {
    //  Do we want to make it critical?
    ret = new CertCachingExtension();
  }

  return ret;
}

/*! \brief  Initialize device supported algorithms.

    Optional tags in the XML file are:
     - ROOT.SupportedAlgorithm (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <SupportedAlgorithm>md5</SupportedAlgorithm>
     <SupportedAlgorithm>md5rsa</SupportedAlgorithm>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Device supported algorithms. If fails, throws DRMDecManagerException.
*/
std::vector<NZSPtr<URIValue> > FileOMADRMDecAgent::InitAlgorithms(IXMLElement* xml, DRMLogger& logger) {
  std::vector<IXMLElement*> algs = xml->GetChildElementsByName("SupportedAlgorithm");
  std::vector<NZSPtr<URIValue> > ret;
  unsigned int i = 0;

  for (i = 0; i < algs.size(); i++) {
    std::string alg;
    try {
      alg = algs[i]->GetStrValue();
    }
    catch (XMLException) {
      throw DRMDecManagerException();
    }
    ret.push_back(new URIValue(alg));
  }

  return ret;
}

} // namespace DRMPlugin
