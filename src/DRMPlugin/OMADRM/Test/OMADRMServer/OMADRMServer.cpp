/** \file OMADRMServer.cpp

    Test server handling all OMA DRM server messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

/*! disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

#include "OMADRMServer.h"
#include "PublicCryptoFactory.h"
#include <sys/stat.h>
#include "Base64Factory.h"
#include "ThreadSyncFactory.h"
#include "XMLFactory.h"
#include "ROAPParser.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Caching server's device context factory (parser).
*/
/*! \brief  Create (parse) caching server's device context.

    \param  xml       input, XML document.
    \param  logger    input, message logger.

    \returns  New device context. If fails, throws OMADRMServerException.
*/
SPtr<CacheServerDeviceContext> CacheServerDeviceContextFactory::ParseContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("PublicCert") == 0) {
      throw OMADRMServerException();
    }
    Base64StringT enc(xml->GetChildElement("PublicCert")->GetStrValue());
    ByteSeq data;
    if (Base64Factory::Decode(enc, data) == false) {
      throw OMADRMServerException();
    }

    return new CacheServerDeviceContext(
      new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger)),
      ROAPParser::ParseROAPIdentifier(xml->GetChildElement("Identifier"), logger),
      ROAPParser::ParseROAPCertificateChain(xml->GetChildElement("CertChain"), logger),
      ROAPParser::ParseURIValue(xml->GetChildElement("URL"), logger),
      ROAPParser::ParseROAPKeyIdentifiers(xml->GetChildElement("TrustedAuthorities"), logger),
      ParseVector<URIValue, URIValue>(
        xml->GetChildElementsByName("Algorithm"), ROAPParser::ParseURIValue, logger),
      ROAPParser::ParseDeviceDetailsData(xml->GetChildElement("DeviceDetails"), logger),
      ROAPParser::ParseROAPVersion(xml->GetChildElement("Version"), logger));
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }
  catch (GCException) {
    throw OMADRMServerException();
  }
  catch (ROAPParserException) {
    throw OMADRMServerException();
  }
}

/*! \brief  Non-caching server's device context factory (parser).
*/
/*! \brief  Create (parse) non-caching server's device context.

    \param  xml       input, XML document.
    \param  logger    input, message logger.

    \returns  New device context. If fails, throws OMADRMServerException.
*/
SPtr<NCacheServerDeviceContext> NCacheServerDeviceContextFactory::ParseContext(IXMLElement* xml, DRMLogger& logger) {
  if (xml == 0) {
    return 0;
  }
  try {
    if (xml->GetChildElement("PublicCert") == 0) {
      throw OMADRMServerException();
    }
    Base64StringT enc(xml->GetChildElement("PublicCert")->GetStrValue());
    ByteSeq data;
    if (Base64Factory::Decode(enc, data) == false) {
      throw OMADRMServerException();
    }

    return new NCacheServerDeviceContext(
      new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger)),
      ROAPParser::ParseROAPIdentifier(xml->GetChildElement("Identifier"), logger),
      ROAPParser::ParseURIValue(xml->GetChildElement("URL"), logger),
      ROAPParser::ParseROAPKeyIdentifiers(xml->GetChildElement("TrustedAuthorities"), logger),
      ParseVector<URIValue, URIValue>(
        xml->GetChildElementsByName("Algorithm"), ROAPParser::ParseURIValue, logger),
      ROAPParser::ParseDeviceDetailsData(xml->GetChildElement("DeviceDetails"), logger),
      ROAPParser::ParseROAPVersion(xml->GetChildElement("Version"), logger));
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }
  catch (GCException) {
    throw OMADRMServerException();
  }
  catch (ROAPParserException) {
    throw OMADRMServerException();
  }
}

/*! \brief  Constructor.

    Mandatory tags in the XML file are:
     - ROOT.RegDatabasePath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RegDatabasePath>\p12\cacheserverregdb.xml</RegDatabasePath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    If fails, throws OMADRMServerException.
*/
FileCacheServerRegDatabase::FileCacheServerRegDatabase(IXMLElement* xml, DRMLogger& logger) {
  IXMLElement* fpath = xml->GetChildElement("RegDatabasePath");
  if (fpath == 0) {
    throw OMADRMServerException();
  }
  try {
    fName = fpath->GetStrValue();
  }
  catch (XMLException) {
    throw OMADRMServerException();
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
    throw OMADRMServerException();
  }

  IXMLElement* root = doc->GetRootElement();
  if (root == 0) {
    delete doc;
    throw OMADRMServerException();
  }
  if ((root->GetName() != "Database") || (root->GetChildElement("DeviceContexts") == 0)
      || (root->GetChildElement("DeviceDomains") == 0)) {
    delete doc;
    throw OMADRMServerException();
  }

  //  Check and parse data.
  IXMLElement* next = root->GetChildElement("DeviceContexts")->GetFirstChild();
  IXMLElement* sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<ROAPIdentifier> id = ROAPParser::ParseROAPIdentifier(next, logger);
      NZSPtr<CacheServerDeviceContext> ctx = CacheServerDeviceContextFactory::ParseContext(sib, logger);
      deviceIDToContext[id] = ctx;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }
  next = root->GetChildElement("DeviceDomains")->GetFirstChild(); // DomainIdentifier
  sib = ((next == 0)? (0): (next->GetFirstSibling())); // DeviceDomains
  while (next != 0) {
    if (sib == 0) {
      delete doc;
      throw OMADRMServerException();
    }
    try {
      NZSPtr<ROAPDomainIdentifier> id = ROAPParser::ParseROAPDomainIdentifier(next, logger);
      IXMLElement* first = sib->GetFirstChild(); // DeviceIdentifier
      IXMLElement* second = ((first == 0)? (0): (first->GetFirstSibling())); // DomainInfo
      std::map<NZSPtr<ROAPIdentifier>, SPtr<ROAPDomainInfo> > tmpmap;
      while (first != 0) {
        NZSPtr<ROAPIdentifier> devid = ROAPParser::ParseROAPIdentifier(first, logger);
        NZSPtr<ROAPDomainInfo> info = ROAPParser::ParseROAPDomainInfo(second, logger);
        tmpmap[devid] = info;
        first = second->GetFirstSibling(); // DeviceIdentifier
        second = ((first == 0)? (0): (first->GetFirstSibling())); // DomainInfo
      }
      domIDToDevIDToInfo[id] = tmpmap;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling(); // DomainIdentifier
    sib = ((next == 0)? (0): (next->GetFirstSibling())); // DeviceDomains
  }

  delete doc;
}

/*! \brief  Save database.

    Saves database to the same file that it was read from in constructor.

    \returns  Boolean indicating success or failure.
*/
bool FileCacheServerRegDatabase::SaveDatabase() {
  std::map<NZSPtr<ROAPIdentifier>, SPtr<CacheServerDeviceContext> >::iterator
    iterc = deviceIDToContext.begin();
  std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
    SPtr<ROAPDomainInfo> > >::iterator iterd = domIDToDevIDToInfo.begin();

  std::string dbstring = "<Database><DeviceContexts>";
  std::string tmp;
  while (iterc != deviceIDToContext.end()) {
    dbstring += iterc->first->XmlEncode("DeviceIdentifier");
    if (iterc->second->Encode(tmp) == false) {
      return false;
    }
    dbstring += tmp;
    iterc++;
  }
  dbstring += "</DeviceContexts><DeviceDomains>";
  while (iterd != domIDToDevIDToInfo.end()) {
    dbstring += iterd->first->XmlEncode("DomainIdentifier");
    std::map<NZSPtr<ROAPIdentifier>, SPtr<ROAPDomainInfo> >::iterator
      iterdd = iterd->second.begin();
    dbstring += "<DeviceDomains>";
    while (iterdd != iterd->second.end()) {
      dbstring += iterdd->first->XmlEncode("DeviceIdentifier");
      dbstring += iterdd->second->XmlEncode("DomainInfo");
      iterdd++;
    }
    dbstring += "</DeviceDomains>";
    iterd++;
  }
  dbstring += "</DeviceDomains></Database>";

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
     <RegDatabasePath>\p12\ncacheserverregdb.xml</RegDatabasePath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    If fails, throws OMADRMServerException.
*/
FileNCacheServerRegDatabase::FileNCacheServerRegDatabase(IXMLElement* xml, DRMLogger& logger) {
  IXMLElement* fpath = xml->GetChildElement("RegDatabasePath");
  if (fpath == 0) {
    throw OMADRMServerException();
  }
  try {
    fName = fpath->GetStrValue();
  }
  catch (XMLException) {
    throw OMADRMServerException();
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
    throw OMADRMServerException();
  }

  IXMLElement* root = doc->GetRootElement();
  if (root == 0) {
    delete doc;
    throw OMADRMServerException();
  }
  if ((root->GetName() != "Database") || (root->GetChildElement("DeviceContexts") == 0)
      || (root->GetChildElement("DeviceDomains") == 0)) {
    delete doc;
    throw OMADRMServerException();
  }

  //  Check and parse data.
  IXMLElement* next = root->GetChildElement("DeviceContexts")->GetFirstChild();
  IXMLElement* sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<ROAPIdentifier> id = ROAPParser::ParseROAPIdentifier(next, logger);
      NZSPtr<NCacheServerDeviceContext> ctx = NCacheServerDeviceContextFactory::ParseContext(sib, logger);
      deviceIDToContext[id] = ctx;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }
  next = root->GetChildElement("DeviceDomains")->GetFirstChild(); // DomainIdentifier
  sib = ((next == 0)? (0): (next->GetFirstSibling())); // DeviceDomains
  while (next != 0) {
    if (sib == 0) {
      delete doc;
      throw OMADRMServerException();
    }
    try {
      NZSPtr<ROAPDomainIdentifier> id = ROAPParser::ParseROAPDomainIdentifier(next, logger);
      IXMLElement* first = sib->GetFirstChild(); // DeviceIdentifier
      IXMLElement* second = ((first == 0)? (0): (first->GetFirstSibling())); // DomainInfo
      std::map<NZSPtr<ROAPIdentifier>, SPtr<ROAPDomainInfo> > tmpmap;
      while (first != 0) {
        NZSPtr<ROAPIdentifier> devid = ROAPParser::ParseROAPIdentifier(first, logger);
        NZSPtr<ROAPDomainInfo> info = ROAPParser::ParseROAPDomainInfo(second, logger);
        tmpmap[devid] = info;
        first = second->GetFirstSibling(); // DeviceIdentifier
        second = ((first == 0)? (0): (first->GetFirstSibling())); // DomainInfo
      }
      domIDToDevIDToInfo[id] = tmpmap;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling(); // DomainIdentifier
    sib = ((next == 0)? (0): (next->GetFirstSibling())); // DeviceDomains
  }

  delete doc;
}

/*! \brief  Save database.

    Saves database to the same file that it was read from in constructor.

    \returns  Boolean indicating success or failure.
*/
bool FileNCacheServerRegDatabase::SaveDatabase() {
  std::map<NZSPtr<ROAPIdentifier>, SPtr<NCacheServerDeviceContext> >::iterator
    iterc = deviceIDToContext.begin();
  std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<ROAPIdentifier>,
    SPtr<ROAPDomainInfo> > >::iterator iterd = domIDToDevIDToInfo.begin();

  std::string dbstring = "<Database><DeviceContexts>";
  std::string tmp;
  while (iterc != deviceIDToContext.end()) {
    dbstring += iterc->first->XmlEncode("DeviceIdentifier");
    if (iterc->second->Encode(tmp) == false) {
      return false;
    }
    dbstring += tmp;
    iterc++;
  }
  dbstring += "</DeviceContexts><DeviceDomains>";
  while (iterd != domIDToDevIDToInfo.end()) {
    dbstring += iterd->first->XmlEncode("DomainIdentifier");
    std::map<NZSPtr<ROAPIdentifier>, SPtr<ROAPDomainInfo> >::iterator
      iterdd = iterd->second.begin();
    dbstring += "<DeviceDomains>";
    while (iterdd != iterd->second.end()) {
      dbstring += iterdd->first->XmlEncode("DeviceIdentifier");
      dbstring += iterdd->second->XmlEncode("DomainInfo");
      iterdd++;
    }
    dbstring += "</DeviceDomains>";
    iterd++;
  }
  dbstring += "</DeviceDomains></Database>";

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
     <RODatabasePath>\p12\serverrodb.xml</RODatabasePath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    If fails, throws OMADRMServerException.
*/
FileServerRODatabase::FileServerRODatabase(IXMLElement* xml, DRMLogger& logger) {
  IXMLElement* fpath = xml->GetChildElement("RODatabasePath");
  if (fpath == 0) {
    throw OMADRMServerException();
  }
  try {
    fName = fpath->GetStrValue();
  }
  catch (XMLException) {
    throw OMADRMServerException();
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
    throw OMADRMServerException();
  }

  IXMLElement* root = doc->GetRootElement();
  if (root == 0) {
    delete doc;
    throw OMADRMServerException();
  }
  if ((root->GetName() != "Database")
      || (root->GetChildElement("DeviceIDToContentIDToROID") == 0)
      || (root->GetChildElement("ROIDToRO") == 0)
      || (root->GetChildElement("ContentIDToKey") == 0)
      || (root->GetChildElement("DeviceIDToContentIDToRights") == 0)
      || (root->GetChildElement("DomainIDToContentIDToRights") == 0)
      || (root->GetChildElement("ROIDToKeyRights") == 0)) {
    delete doc;
    throw OMADRMServerException();
  }

  IXMLElement* next = root->GetChildElement("DeviceIDToContentIDToROID")->GetFirstChild();
  IXMLElement* sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    if (sib == 0) {
      delete doc;
      throw OMADRMServerException();
    }
    try {
      NZSPtr<ROAPIdentifier> id = ROAPParser::ParseROAPIdentifier(next, logger);
      IXMLElement* first = sib->GetFirstChild();
      IXMLElement* second = ((first == 0)? (0): (first->GetFirstSibling()));
      std::map<NZSPtr<URIValue>, SPtr<IDValue> > tmpmap;
      while (first != 0) {
        NZSPtr<URIValue> url = ROAPParser::ParseURIValue(first, logger);
        NZSPtr<IDValue> iid = ROAPParser::ParseIDValue(second, logger);
        tmpmap[url] = iid;
        first = second->GetFirstSibling();
        second = ((first == 0)? (0): (first->GetFirstSibling()));
      }
      devIDToConIDToROID[id] = tmpmap;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  next = root->GetChildElement("ROIDToRO")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<IDValue> id = ROAPParser::ParseIDValue(next, logger);
      NZSPtr<ROAPProtectedRO> ro = ROAPParser::ParseROAPProtectedRO(sib, logger);
      roIDToRO[id] = ro;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  next = root->GetChildElement("ContentIDToKey")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    try {
      NZSPtr<URIValue> id = ROAPParser::ParseURIValue(next, logger);
      Base64StringT key = sib->GetStrValue();
      contentIDToKey[id] = key;
    }
    catch (XMLException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  next = root->GetChildElement("DeviceIDToContentIDToRights")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    if (sib == 0) {
      delete doc;
      throw OMADRMServerException();
    }
    try {
      NZSPtr<ROAPIdentifier> id = ROAPParser::ParseROAPIdentifier(next, logger);
      IXMLElement* first = sib->GetFirstChild();
      IXMLElement* second = ((first == 0)? (0): (first->GetFirstSibling()));
      std::map<NZSPtr<URIValue>, SPtr<OEXRights> > tmpmap;
      while (first != 0) {
        NZSPtr<URIValue> url = ROAPParser::ParseURIValue(first, logger);
        NZSPtr<OEXRights> rights = ROAPParser::ParseOEXRights(second, logger);
        tmpmap[url] = rights;
        first = second->GetFirstSibling();
        second = ((first == 0)? (0): (first->GetFirstSibling()));
      }
      deviceIDToContentIDToRights[id] = tmpmap;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  next = root->GetChildElement("DomainIDToContentIDToRights")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    if (sib == 0) {
      delete doc;
      throw OMADRMServerException();
    }
    try {
      NZSPtr<ROAPDomainIdentifier> id = ROAPParser::ParseROAPDomainIdentifier(next, logger);
      IXMLElement* first = sib->GetFirstChild();
      IXMLElement* second = ((first == 0)? (0): (first->GetFirstSibling()));
      std::map<NZSPtr<URIValue>, SPtr<OEXRights> > tmpmap;
      while (first != 0) {
        NZSPtr<URIValue> url = ROAPParser::ParseURIValue(first, logger);
        NZSPtr<OEXRights> rights = ROAPParser::ParseOEXRights(second, logger);
        tmpmap[url] = rights;
        first = second->GetFirstSibling();
        second = ((first == 0)? (0): (first->GetFirstSibling()));
      }
      domainIDToContentIDToRights[id] = tmpmap;
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  next = root->GetChildElement("ROIDToKeyRights")->GetFirstChild();
  sib = ((next == 0)? (0): (next->GetFirstSibling()));
  while (next != 0) {
    if (sib == 0) {
      delete doc;
      throw OMADRMServerException();
    }
    try {
      NZSPtr<IDValue> id = ROAPParser::ParseIDValue(next, logger);
      IXMLElement* first = sib->GetFirstChild();
      IXMLElement* second = ((first == 0)? (0): (first->GetFirstSibling()));
      Base64StringT key = first->GetStrValue();
      NZSPtr<OEXRights> rights = ROAPParser::ParseOEXRights(second, logger);
      roIDToKeyRights[id] = std::pair<Base64StringT, SPtr<OEXRights> >(key, rights);
    }
    catch (ROAPParserException) {
      delete doc;
      throw OMADRMServerException();
    }
    catch (GCException) {
      delete doc;
      throw OMADRMServerException();
    }
    next = sib->GetFirstSibling();
    sib = ((next == 0)? (0): (next->GetFirstSibling()));
  }

  delete doc;
}

/*! \brief  Save database.

    Saves database to the same file that it was read from in constructor.

    \returns  Boolean indicating success or failure.
*/
bool FileServerRODatabase::SaveDatabase() {
  std::string dbstring = "<Database>";

  std::map<NZSPtr<ROAPIdentifier>, std::map<NZSPtr<URIValue>, SPtr<IDValue> > >::iterator
    iter1 = devIDToConIDToROID.begin();
  dbstring += "<DeviceIDToContentIDToROID>";
  while (iter1 != devIDToConIDToROID.end()) {
    dbstring += iter1->first->XmlEncode("DeviceIdentifier");
    std::map<NZSPtr<URIValue>, SPtr<IDValue> >::iterator iter2 = iter1->second.begin();
    dbstring += "<ContentIDToROID>";
    while (iter2 != iter1->second.end()) {
      dbstring += iter2->first->XmlEncode("ContentID");
      dbstring += "<ROID>" + iter2->second->Get() + "</ROID>";
      iter2++;
    }
    dbstring += "</ContentIDToROID>";
    iter1++;
  }
  dbstring += "</DeviceIDToContentIDToROID>";

  std::map<NZSPtr<IDValue>, SPtr<ROAPProtectedRO> >::iterator iter2 = roIDToRO.begin();
  dbstring += "<ROIDToRO>";
  while (iter2 != roIDToRO.end()) {
    dbstring += "<ROID>" + iter2->first->Get() + "</ROID>";
    dbstring += iter2->second->XmlEncode("RO");
    iter2++;
  }
  dbstring += "</ROIDToRO>";

  std::map<NZSPtr<URIValue>, Base64StringT>::iterator iter3 = contentIDToKey.begin();
  dbstring += "<ContentIDToKey>";
  while (iter3 != contentIDToKey.end()) {
    dbstring += iter3->first->XmlEncode("ContentID");
    dbstring += "<Key>" + iter3->second.BString() + "</Key>";
    iter3++;
  }
  dbstring += "</ContentIDToKey>";

  std::map<NZSPtr<ROAPIdentifier>, std::map<NZSPtr<URIValue>, SPtr<OEXRights> > >::iterator
    iter4 = deviceIDToContentIDToRights.begin();
  dbstring += "<DeviceIDToContentIDToRights>";
  while (iter4 != deviceIDToContentIDToRights.end()) {
    dbstring += iter4->first->XmlEncode("DeviceIdentifier");
    std::map<NZSPtr<URIValue>, SPtr<OEXRights> >::iterator iter5 = iter4->second.begin();
    dbstring += "<ContentIDToRights>";
    while (iter5 != iter4->second.end()) {
      dbstring += iter5->first->XmlEncode("ContentID");
      dbstring += iter5->second->XmlEncode("Rights");
      iter5++;
    }
    dbstring += "</ContentIDToRights>";
    iter4++;
  }
  dbstring += "</DeviceIDToContentIDToRights>";

  std::map<NZSPtr<ROAPDomainIdentifier>, std::map<NZSPtr<URIValue>, SPtr<OEXRights> > >::iterator
    iter5 = domainIDToContentIDToRights.begin();
  dbstring += "<DomainIDToContentIDToRights>";
  while (iter5 != domainIDToContentIDToRights.end()) {
    dbstring += iter5->first->XmlEncode("DomainIdentifier");
    std::map<NZSPtr<URIValue>, SPtr<OEXRights> >::iterator iter6 = iter5->second.begin();
    dbstring += "<ContentIDToRights>";
    while (iter6 != iter5->second.end()) {
      dbstring += iter6->first->XmlEncode("ContentID");
      dbstring += iter6->second->XmlEncode("Rights");
      iter6++;
    }
    dbstring += "</ContentIDToRights>";
    iter5++;
  }
  dbstring += "</DomainIDToContentIDToRights>";

  std::map<NZSPtr<IDValue>, std::pair<Base64StringT, SPtr<OEXRights> > >::iterator
    iter6 = roIDToKeyRights.begin();
  dbstring += "<ROIDToKeyRights>";
  while (iter6 != roIDToKeyRights.end()) {
    dbstring += "<ROID>" + iter6->first->Get() + "</ROID>";
    std::pair<Base64StringT, SPtr<OEXRights> > ppair = iter6->second;
    dbstring += "<KeyRights>";
    dbstring += "<Key>" + ppair.first.BString() + "</Key>";
    dbstring += ppair.second->XmlEncode("Rights");
    dbstring += "</KeyRights>";
    iter6++;
  }
  dbstring += "</ROIDToKeyRights>";

  dbstring += "</Database>";

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

    For the correct structure of XML document see OMADRMServer::InitRICtx,
    FileCacheServerRegDatabase::FileCacheServerRegDatabase (if XML
    document indicates caching registration database),
    FileNCacheServerRegDatabase::FileNCacheServerRegDatabase (if XML
    document indicates non-caching registration database) and
    FileServerRODatabase::FileServerRODatabase.

    \param  xml       XML document.
    \param  logger    message logger.

    If fails, throws OMADRMServerException.
*/
OMADRMServer::OMADRMServer(IXMLElement* xml, DRMLogger& logger):
  mutex(ThreadSyncFactory::GetMutex(logger)),
  rissuer(InitRICtx(xml, logger)),
  regDB((rissuer->GetCertCaching() == 0)?
    (NZSPtr<ServerRegDatabase>(new FileNCacheServerRegDatabase(xml, logger))):
    (NZSPtr<ServerRegDatabase>(new FileCacheServerRegDatabase(xml, logger)))),
  roDB(new FileServerRODatabase(xml, logger)),
  serverRegTracker(new ServerProtocolTracker()),
  noncer(new OMADRMNonceCreator()),
  sessioner(new DummySessionIDCreator()),
  verifier(new OMACertificateVerifier(PublicCryptoFactory::GetCertificateVerifier(logger))),
  hasher(new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger))) {

  if (mutex == 0) {
    throw OMADRMServerException();
  }
}

OMADRMServer::~OMADRMServer() {
  regDB->SaveDatabase();
  roDB->SaveDatabase();
  if (mutex != 0) delete mutex;
}

/*! \brief  Handle add content encryption key request.

    \param  request             input, add content encryption key message.

    \returns  Add content encryption key response.
*/
NZSPtr<AddContentKeyResponse> OMADRMServer::HandleAddContentKeyRequest(const
    NZSPtr<AddContentKeyRequest>& request) {
  if (mutex->Lock() == false) {
    return new AddContentKeyResponse(false, request->GetNonce());
  }
  roDB->AddContentKey(request->GetContentID(), request->GetKey());
  mutex->Release();
  return new AddContentKeyResponse(true, request->GetNonce());
}

/*! \brief  Handle add rights for device for content request.

    \param  request             input, add rights for device for content message.

    \returns  Add rights for device for content response.
*/
NZSPtr<AddDeviceRightsResponse> OMADRMServer::HandleAddDeviceRightsRequest(const
    NZSPtr<AddDeviceRightsRequest>& request) {
  if (mutex->Lock() == false) {
    return new AddDeviceRightsResponse(false, request->GetNonce());
  }
  roDB->AddRights(request->GetDeviceID(), request->GetContentID(),
    request->GetRights());
  mutex->Release();
  return new AddDeviceRightsResponse(true, request->GetNonce());
}

/*! \brief  Handle initial content rights objects request.

    In a real situation, return object should be either registration trigger
    or rights objects acquisition trigger. Since this is just a test case,
    we restrict return object to rights objects acquisition trigger.

    \param  request         input, initial content rights objects message.

    \returns  Rights objects acquisition trigger. If zero, failed.
*/
SPtr<ROAcquisitionTrigger> OMADRMServer::HandleInitialRORequest(const
    NZSPtr<ServerInitialRORequest>& request) {
  if (mutex->Lock() == false) {
    return 0;
  }
  SPtr<ROAcquisitionTrigger> ret = request->ProtocolUpdate(regDB, roDB, noncer,
    serverRegTracker, rissuer);
  mutex->Release();
  return ret;
}

/*! \brief  Handle device hello message.

    \param  request             input, device hello message.

    \returns  Rights issuer hello response.
*/
NZSPtr<RIHelloResponse> OMADRMServer::HandleDeviceHello(const
    NZSPtr<ServerDeviceHelloRequest>& request) {
  //  \todo:  Currently server operates only as a responder, therefore it
  //          doesn't need a device URL. Perhaps it could change in the future.
  if (mutex->Lock() == false) {
    return new UnsuccessRIHello(new AbortROAPStatus());
  }
  NZSPtr<RIHelloResponse> serverRIHello = request->ProtocolUpdate(serverRegTracker,
    noncer, sessioner, new URIValue("device URL"), regDB, rissuer);
  mutex->Release();
  return serverRIHello;
}

/*! \brief  Handle registration request message.

    \param  request           input, registration request message.

    \returns  Registration response.
*/
NZSPtr<RegResponse> OMADRMServer::HandleRegRequest(const NZSPtr<ServerRegRequest>&
    request) {
  if (mutex->Lock() == false) {
    return new UnsuccessRegResponse(new AbortROAPStatus(), request->GetSessionID());
  }
  NZSPtr<RegResponse> serverRegResp = request->ProtocolUpdate(serverRegTracker,
    verifier, rissuer);
  mutex->Release();
  return serverRegResp;
}

/*! \brief  Handle rights objects request message.

    \param  request           input, rights objects request message.

    \returns  2-pass rights objects response.
*/
NZSPtr<TwoPassROResponse> OMADRMServer::HandleRORequest(const NZSPtr<ServerRORequest>&
    request) {
  if (mutex->Lock() == false) {
    return new UnsuccessTwoPassROResponse(new AbortROAPStatus());
  }
  NZSPtr<TwoPassROResponse> serverROResp = request->ProtocolUpdate(regDB, roDB,
    verifier, serverRegTracker, rissuer);
  mutex->Release();

  return serverROResp;
}

/*! \brief  Handle join domain request message.

    \param  request           input, join domain request message.

    \returns  Join domain response.
*/
NZSPtr<JoinDomainResponse> OMADRMServer::HandleJoinRequest(const NZSPtr<ServerJoinDomainRequest>&
    request) {
  if (mutex->Lock() == false) {
    return new UnsuccessJoinDomainResponse(new AbortROAPStatus());
  }
  NZSPtr<JoinDomainResponse> serverJoinResp = request->ProtocolUpdate(regDB,
    verifier, serverRegTracker, rissuer);
  mutex->Release();

  return serverJoinResp;
}

/*! \brief  Handle leave domain request message.

    \param  request           input, leave domain request message.

    \returns  Leave domain response.
*/
NZSPtr<LeaveDomainResponse> OMADRMServer::HandleLeaveRequest(const NZSPtr<ServerLeaveDomainRequest>&
    request) {
  if (mutex->Lock() == false) {
    return new UnsuccessLeaveDomainResponse(new AbortROAPStatus());
  }
  NZSPtr<LeaveDomainResponse> serverLeaveResp = request->ProtocolUpdate(regDB,
    verifier, serverRegTracker, rissuer);
  mutex->Release();

  return serverLeaveResp;
}

/*! \brief  Create registration request trigger (with nonce).

    \returns  Registration request trigger. If zero, failed.
*/
SPtr<RegRequestTrigger> OMADRMServer::CreateRegTrigger() {
  if (mutex->Lock() == false) {
    return 0;
  }
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  NZSPtr<RegRequestTriggerData> triggerData = new RegRequestTriggerData(
    rissuer->GetID(), nonce, rissuer->GetURL(), new IDValue("trigger ID"));
  //  \todo: Do we want to sign it?
//  Base64StringT signature = regDB->RIContext()->RIPrivateKey()->Sign(
//    triggerData->XmlEncode());
  NZSPtr<RegRequestTrigger> trigger = new RegRequestTrigger(triggerData, 0,
    rissuer->GetVersion(), 0);
  serverRegTracker->nonceToRegTrigger[nonce] = trigger;
  mutex->Release();
  return trigger;
}

/*! \brief  Create non-domain rights objects acquisition trigger (with nonce).

    \param  deviceID          input, device identifier.
    \param  contentID         input, content identifier.

    \returns  Rights objects acquisition trigger. If zero, failed.
*/
SPtr<ROAcquisitionTrigger> OMADRMServer::CreateROTrigger(const NZSPtr<ROAPIdentifier>&
    deviceID, const NZSPtr<URIValue>& contentID) {
  if (mutex->Lock() == false) {
    return 0;
  }
  //  Check if device is registered.
  if (regDB->GetContext(deviceID) == 0) {
    mutex->Release();
    return 0;
  }
  //  Create a new rights objects identifier dependent on deviceID and contentID.
  NZSPtr<IDValue> roID(new IDValue(deviceID->XmlEncode() + contentID->Get()));
  if (roDB->SetROID(roID, deviceID, contentID) == false) {
    //  Error.
    mutex->Release();
    return 0;
  }
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  //  Server creates and sends RO acquisition trigger to the device.
  NZSPtr<NDomainROTriggerData> triggerData = new NDomainROTriggerData(
    rissuer->GetID(), nonce, rissuer->GetURL(),
    std::vector<NZSPtr<ROIDContentID> >(1, new ROIDContentID(roID,
    std::vector<NZSPtr<URIValue> >(1, contentID))), new
    IDValue("trigger id"));
  //  \todo: Do we want to sign it?
//  Base64StringT signature = regDB->RIContext()->RIPrivateKey()->Sign(
//    triggerData->XmlEncode());
  NZSPtr<ROAcquisitionTrigger> trigger = new NDomainROTrigger(triggerData, 0,
    rissuer->GetVersion(), 0);
  serverRegTracker->nonceToROTrigger[nonce] = trigger;
  mutex->Release();
  return trigger;
}

/*! \brief  Create domain rights objects acquisition trigger (with nonce).

    \param  domainID          input, domain identifier.
    \param  contentID         input, content identifier.

    \returns  Rights objects acquisition trigger. If zero, failed.
*/
SPtr<ROAcquisitionTrigger> OMADRMServer::CreateROTrigger(const
    NZSPtr<ROAPDomainIdentifier>& domainID, const NZSPtr<URIValue>& contentID) {
  if (mutex->Lock() == false) {
    return 0;
  }
  //  Create a new rights objects identifier dependent on domainID and contentID.
  NZSPtr<IDValue> roID(new IDValue(domainID->XmlEncode() + contentID->Get()));
  if (roDB->SetROID(roID, domainID, contentID) == false) {
    //  Error.
    mutex->Release();
    return 0;
  }
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  //  Server creates and sends RO acquisition trigger to the device.
  NZSPtr<DomainROTriggerData> triggerData = new DomainROTriggerData(
    rissuer->GetID(), nonce, rissuer->GetURL(), domainID,
    std::vector<NZSPtr<ROIDContentID> >(1, new ROIDContentID(roID,
    std::vector<NZSPtr<URIValue> >(1, contentID))), new
    IDValue("trigger id"));
  //  \todo: Do we want to sign it?
//  Base64StringT signature = regDB->RIContext()->RIPrivateKey()->Sign(
//    triggerData->XmlEncode());
  NZSPtr<ROAcquisitionTrigger> trigger = new DomainROTrigger(triggerData, 0,
    rissuer->GetVersion(), 0);
  serverRegTracker->nonceToROTrigger[nonce] = trigger;
  mutex->Release();
  return trigger;
}

/*! \brief  Create join domain trigger (with nonce).

    \param  domainID          input, domain identifier.

    \returns  Join domain trigger. If zero, failed.
*/
SPtr<JoinDomainTrigger> OMADRMServer::CreateJoinTrigger(const NZSPtr<ROAPDomainIdentifier>&
    domainID) {
  if (mutex->Lock() == false) {
    return 0;
  }
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  NZSPtr<JoinDomainTriggerData> triggerData = new JoinDomainTriggerData(
    rissuer->GetID(), nonce, rissuer->GetURL(), domainID, new IDValue("trigger ID"));
  //  \todo: Do we want to sign it?
//  Base64StringT signature = rissuer->RIPrivateKey()->Sign(triggerData->XmlEncode());
  NZSPtr<JoinDomainTrigger> trigger = new JoinDomainTrigger(triggerData, 0,
    rissuer->GetVersion(), 0);
  serverRegTracker->nonceToJoinTrigger[nonce] = trigger;
  mutex->Release();
  return trigger;
}

/*! \brief  Create leave domain trigger (with nonce).

    \param  domainID          input, domain identifier.

    \returns  Leave domain trigger. If zero, failed.
*/
SPtr<LeaveDomainTrigger> OMADRMServer::CreateLeaveTrigger(const NZSPtr<ROAPDomainIdentifier>&
    domainID) {
  if (mutex->Lock() == false) {
    return 0;
  }
  NZSPtr<ROAPNonce> nonce = noncer->CreateNonce();
  NZSPtr<LeaveDomainTriggerData> triggerData = new LeaveDomainTriggerData(
    rissuer->GetID(), nonce, rissuer->GetURL(), domainID, new IDValue("trigger ID"));
  Base64StringT signature;
  if (rissuer->GetPrivateKey()->Sign(triggerData->XmlEncode(), signature) == false) {
    mutex->Release();
    return 0;
  }
  NZSPtr<LeaveDomainTrigger> trigger = new LeaveDomainTrigger(triggerData,
    new DSSignature(new DSSignedInfo(new DSCanonicalizationMethod(new URIValue("uri")),
    new DSSignatureMethod(0, new URIValue("uri")), std::vector<NZSPtr<DSReference> >(1,
    new DSReference(0, new DSDigestMethod(new URIValue("digest method")),
    new DSDigestValue("digestvalue"), 0, 0, 0)), 0), new DSSignatureValue(
    signature, 0), 0, std::vector<NZSPtr<DSObject> >(), 0), 0, rissuer->GetVersion(),
    0);
  serverRegTracker->nonceToLeaveTrigger[nonce] = trigger;
  mutex->Release();
  return trigger;
}

/*! \brief  Initialize rights issuer context.

    Mandatory tags in the XML file are:
     - ROOT.RegDatabasePath
     - ROOT.RODatabasePath
     - ROOT.CertPath
     - ROOT.PrivateKeyPath
     - ROOT.RootCAPath (can be more than one)
     - ROOT.ROAPVersion
     - ROOT.Caching
     - ROOT.URL

    Optional tags in the XML file are:
     - ROOT.CertificateChainPath (can be more than one)
     - ROOT.SupportedAlgorithm (can be more than one)
     - ROOT.OCSPResponsePath (can be more than one)
     - ROOT.DomainName (can be between 0 and 5)
     - ROOT.Info

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RegDatabasePath>\p12\omaserver\cacheserverregdb.xml</RegDatabasePath>
     <RODatabasePath>\p12\omaserver\serverrodb.xml</RODatabasePath>
     <CertPath>\p12\serverCertSigned.der</CertPath>
     <PrivateKeyPath>\p12\serverKey.der</PrivateKeyPath>
     <RootCAPath>\p12\OMACACert.der</RootCAPath>
     <ROAPVersion>1.0</ROAPVersion>
     <Caching>true</Caching>
     <CertificateChainPath>\p12\chainCert.der</CertificateChainPath>
     <SupportedAlgorithm>md5</SupportedAlgorithm>
     <SupportedAlgorithm>md5rsa</SupportedAlgorithm>
     <URL>http://localhost:8080/</URL>
     <OCSPResponsePath>server_ocsp1.der</OCSPResponsePath>
     <OCSPResponsePath>server_ocsp2.der</OCSPResponsePath>
     <DomainName>domain_name</DomainName>
     <Info>omadrm_server</Info>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Rights issuer context. If fails, throws OMADRMServerException.
*/
NZSPtr<ServerRIContext> OMADRMServer::InitRICtx(IXMLElement* xml, DRMLogger& logger) {
  NZSPtr<OMAPublicCertificate> serverPublicCert = InitPublicCert(xml, logger);
  NZSPtr<OMAPrivateKey> serverPrivateKey = InitPrivateKey(xml, logger);
  NZSPtr<ROAPKeyIdentifier> serverKeyID = InitKeyID(serverPublicCert, logger);
  NZSPtr<ROAPIdentifier> serverID = InitID(serverKeyID, logger);
  NZSPtr<ROAPCertificateChain> serverCertChain = InitCertChain(xml, logger);
  std::vector<Base64StringT> serverTrusted = InitCAs(xml, logger);
  NZSPtr<ROAPKeyIdentifiers> serverTrustedIDs = InitCAIDs(serverTrusted, logger);
  std::vector<NZSPtr<URIValue> > algorithms = InitAlgorithms(xml, logger);
  SPtr<CertCachingExtension> serverCertCaching = InitCaching(xml, logger);
  NZSPtr<ROAPVersion> serverVersion = InitVersion(xml, logger);
  NZSPtr<URIValue> url = InitURL(xml, logger);
  std::vector<Base64StringT> ocsps = InitOCSPs(xml, logger);
  SPtr<DomainNameWhiteListExtension> whitelist = InitDomains(xml, logger);
  SPtr<ROAPServerInfo> serverInfo = InitInfo(xml, logger);

  return new ServerRIContext(serverPublicCert, serverPrivateKey,
    serverID, serverCertChain, serverTrustedIDs, serverTrusted,
    algorithms, serverCertCaching, serverVersion, url, ocsps, whitelist,
    serverInfo);
}

/*! \brief  Initialize rights issuer public certificate.

    Mandatory tags in the XML file are:
     - ROOT.CertPath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <CertPath>\p12\riCertSigned.der</CertPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Rights issuer public certificate. If fails, throws OMADRMServerException.
*/
NZSPtr<OMAPublicCertificate> OMADRMServer::InitPublicCert(IXMLElement* xml, DRMLogger& logger) {
  std::string certPath;
  try {
    certPath = xml->GetChildStrValue("CertPath");
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }

  try {
    return new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromFile(certPath, logger));
  }
  catch (OMADRMCryptoException) {
    throw OMADRMServerException();
  }
}

/*! \brief  Initialize rights issuer key identifier.

    \param  cer       input, server public certificate.
    \param  logger      input, message logger.

    \returns  Rights issuer key identifier. If fails, throws OMADRMServerException.
*/
NZSPtr<ROAPKeyIdentifier> OMADRMServer::InitKeyID(const NZSPtr<OMAPublicCertificate>& cer, DRMLogger& logger) {
  Base64StringT id;
  if (cer->GetKeyIdentifier(new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger)),
      id) == false) {
    throw OMADRMServerException();
  }
  return new X509SPKIHash(id);
}

/*! \brief  Initialize rights issuer identifier.

    \param  keyid       input, server key identifier.
    \param  logger      input, message logger.

    \returns  Rights issuer identifier. If fails, throws OMADRMServerException.
*/
NZSPtr<ROAPIdentifier> OMADRMServer::InitID(const NZSPtr<ROAPKeyIdentifier>& keyid, DRMLogger& logger) {
  return new ROAPIdentifier(keyid);
}

/*! \brief  Initialize rights issuer private key.

    Mandatory tags in the XML file are:
     - ROOT.PrivateKeyPath

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <PrivateKeyPath>\p12\riKey.der</PrivateKeyPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Rights issuer private key. If fails, throws OMADRMServerException.
*/
NZSPtr<OMAPrivateKey> OMADRMServer::InitPrivateKey(IXMLElement* xml, DRMLogger& logger) {
  std::string privatePath;
  try {
    privatePath = xml->GetChildStrValue("PrivateKeyPath");
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }

  try {
    return new OMAPrivateKey(PublicCryptoFactory::ParsePublicDecryptorSignerFromKeyFile(privatePath, logger));
  }
  catch (OMADRMCryptoException) {
    throw OMADRMServerException();
  }
}

/*! \brief  Initialize rights issuer certificate chain.

    Mandatory tags in the XML file are:
     - ROOT.CertPath

    Optional tags in the XML file are:
     - ROOT.CertificateChainPath (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <CertPath>\p12\riCertSigned.der</CertPath>
     <CertificateChainPath>\p12\chainCert.der</CertificateChainPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Rights issuer certificate chain. If fails, throws
              OMADRMServerException.
*/
NZSPtr<ROAPCertificateChain> OMADRMServer::InitCertChain(IXMLElement* xml, DRMLogger& logger) {
  std::string certPath;
  try {
    certPath = xml->GetChildStrValue("CertPath");
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }

  struct stat tstat;

  FILE* certf = fopen(certPath.data(), "rb");
  if (certf == NULL) {
    throw OMADRMServerException();
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
    throw OMADRMServerException();
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
      throw OMADRMServerException();
    }
    certf = fopen(certPath.data(), "rb");
    if (certf == NULL) {
      throw OMADRMServerException();
    }
    stat(certPath.data(), &tstat);
    certbyteslen = tstat.st_size;
    certbytes = (ByteT*)malloc(certbyteslen);
    fread(certbytes, certbyteslen, 1, certf);
    fclose(certf);

    if (Base64Factory::Encode(ByteSeq(certbytes, certbyteslen), b64) == false) {
      free(certbytes);
      throw OMADRMServerException();
    }
    chain[i] = b64;
    free(certbytes);
  }

  return new ROAPCertificateChain(chain);
}

/*! \brief  Initialize rights issuer root CA certificates.

    Mandatory tags in the XML file are:
     - ROOT.RootCAPath (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <RootCAPath>\p12\OMACACert.der</RootCAPath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns Root CA certificates. If fails, throws OMADRMServerException.
*/
std::vector<Base64StringT> OMADRMServer::InitCAs(IXMLElement* xml, DRMLogger& logger) {
  std::vector<IXMLElement*> caPaths = xml->GetChildElementsByName("RootCAPath");
  //  First check mandatory tags.
  if (caPaths.size() == 0) {
    throw OMADRMServerException();
  }

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
      throw OMADRMServerException();
    }
    FILE* certf = fopen(certPath.data(), "rb");
    if (certf == NULL) {
      throw OMADRMServerException();
    }
    stat(certPath.data(), &tstat);
    unsigned int certbyteslen = tstat.st_size;
    ByteT* certbytes = (ByteT*)malloc(certbyteslen);
    fread(certbytes, certbyteslen, 1, certf);
    fclose(certf);

    if (Base64Factory::Encode(ByteSeq(certbytes, certbyteslen), b64) == false) {
      free(certbytes);
      throw OMADRMServerException();
    }
    cas.push_back(b64);
    free(certbytes);
  }

  return cas;
}

/*! \brief  Initialize rights issuer root CA key identifiers.

    \param  trusted     input, root CA certificates.
    \param  logger      input, message logger.

    \returns Root CA key identifiers. If fails, throws OMADRMServerException.
*/
NZSPtr<ROAPKeyIdentifiers> OMADRMServer::InitCAIDs(std::vector<Base64StringT>& trusted, DRMLogger& logger) {
  std::vector<NZSPtr<ROAPKeyIdentifier> > ret;
  for (unsigned int i = 0; i < trusted.size(); i++) {
    //  Decode from base64.
    ByteSeq data;
    if (Base64Factory::Decode(trusted[i], data) == false) {
      throw OMADRMServerException();
    }
    //  Create key identifier.
    SPtr<OMAPublicCertificate> cer;
    try {
      cer = new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromData((ByteT*)data.GetFirst(), (unsigned int)data.GetLength(), logger));
    }
    catch (OMADRMCryptoException) {
      throw OMADRMServerException();
    }
    Base64StringT id;
    if (cer->GetKeyIdentifier(new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger)),
        id) == false) {
      throw OMADRMServerException();
    }
    ret.push_back(new X509SPKIHash(id));
  }
  return new ROAPKeyIdentifiers(ret);
}

/*! \brief  Initialize rights issuer supported algorithms.

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

    \returns  Rights issuer supported algorithms. If fails, throws
              OMADRMServerException.
*/
std::vector<NZSPtr<URIValue> > OMADRMServer::InitAlgorithms(IXMLElement* xml, DRMLogger& logger) {
  std::vector<IXMLElement*> algs = xml->GetChildElementsByName("SupportedAlgorithm");
  std::vector<NZSPtr<URIValue> > ret;
  unsigned int i = 0;

  for (i = 0; i < algs.size(); i++) {
    //  Check getting value in a node without children!
    std::string alg;
    try {
      alg = algs[i]->GetStrValue();
    }
    catch (XMLException) {
      throw OMADRMServerException();
    }
    ret.push_back(new URIValue(alg));
  }

  return ret;
}

/*! \brief  Initialize server caching.

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

    \returns  Server caching. If fails, throws OMADRMServerException.
*/
SPtr<CertCachingExtension> OMADRMServer::InitCaching(IXMLElement* xml, DRMLogger& logger) {
  std::string caching;
  try {
    caching = xml->GetChildStrValue("Caching");
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }
  SPtr<CertCachingExtension> ret;
  if (caching == "true") {
    //  Do we want to make it critical?
    ret = new CertCachingExtension();
  }

  return ret;
}

/*! \brief  Initialize rights issuer ROAP version.

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

    \returns  Rights issuer ROAP version. If fails, throws OMADRMServerException.
*/
NZSPtr<ROAPVersion> OMADRMServer::InitVersion(IXMLElement* xml, DRMLogger& logger) {
  std::string roapversion;
  try {
    roapversion = xml->GetChildStrValue("ROAPVersion");
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }

  return new ROAPVersion(roapversion);
}

/*! \brief  Initialize rights issuer URL.

    Mandatory tags in the XML file are:
     - ROOT.URL

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <URL>http://localhost:8080/</URL>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Rights issuer URL. If fails, throws OMADRMServerException.
*/
NZSPtr<URIValue> OMADRMServer::InitURL(IXMLElement* xml, DRMLogger& logger) {
  std::string url;
  try {
    url = xml->GetChildStrValue("URL");
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }

  return new URIValue(url);
}

/*! \brief  Initialize rights issuer OCSP responses.

    Optional tags in the XML file are:
     - ROOT.OCSPResponsePath (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <OCSPResponsePath>server_ocsp1.der</OCSPResponsePath>
     <OCSPResponsePath>server_ocsp2.der</OCSPResponsePath>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Rights issuer OCSP responses. If fails, throws OMADRMServerException.
*/
std::vector<Base64StringT> OMADRMServer::InitOCSPs(IXMLElement* xml, DRMLogger& logger) {
  std::vector<IXMLElement*> ocsps = xml->GetChildElementsByName("OCSPResponsePath");
  std::vector<Base64StringT> ret;
  unsigned int i = 0;

  for (i = 0; i < ocsps.size(); i++) {
    std::string ocsp;
    try {
      ocsp = ocsps[i]->GetStrValue();
    }
    catch (XMLException) {
      throw OMADRMServerException();
    }
    struct stat tstat;
    FILE* ocspf = fopen(ocsp.data(), "rb");
    if (ocspf == NULL) {
      throw OMADRMServerException();
    }
    stat(ocsp.data(), &tstat);
    unsigned int ocspbyteslen = tstat.st_size;
    ByteT* ocspbytes = (ByteT*)malloc(ocspbyteslen);
    fread(ocspbytes, ocspbyteslen, 1, ocspf);
    fclose(ocspf);
    //  \todo: Should we encode it here or read base64 data from XML file?
    Base64StringT ocspstr;
    if (Base64Factory::Encode(ByteSeq(ocspbytes, ocspbyteslen), ocspstr) == false) {
      free(ocspbytes);
      throw OMADRMServerException();
    }
    free(ocspbytes);
    ret.push_back(ocspstr);
  }

  return ret;
}

/*! \brief  Initialize rights issuer domain name whitelist.

    Optional tags in the XML file are:
     - ROOT.DomainName (can be more than one)

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <DomainName>domain_name</DomainName>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Rights issuer domain name whitelist. If fails, throws
              OMADRMServerException.
*/
SPtr<DomainNameWhiteListExtension> OMADRMServer::InitDomains(IXMLElement* xml, DRMLogger& logger) {
  std::vector<IXMLElement*> domains = xml->GetChildElementsByName("DomainName");
  std::vector<std::string> ret;
  unsigned int i = 0;

  for (i = 0; i < domains.size(); i++) {
    std::string domain;
    try {
      domain = domains[i]->GetStrValue();
    }
    catch (XMLException) {
      throw OMADRMServerException();
    }
    ret.push_back(domain);
  }

  if (ret.size() > 0) {
    return new DomainNameWhiteListExtension(ret);
  } else {
    return 0;
  }
}

/*! \brief  Initialize server info.

    Optional tags in the XML file are:
     - ROOT.Info

    Here follows an example of a correctly formatted XML document.

    \verbatim

    <ROOT>
     <Info>omadrm_server</Info>
    </ROOT>

    \endverbatim

    \param  xml         input, XML document.
    \param  logger      input, message logger.

    \returns  Server info. If fails, throws OMADRMServerException.
*/
SPtr<ROAPServerInfo> OMADRMServer::InitInfo(IXMLElement* xml, DRMLogger& logger) {
  if (xml->GetChildElement("Info") == 0) {
    return 0;
  }
  std::string info;
  try {
    info = xml->GetChildStrValue("Info");
  }
  catch (XMLException) {
    throw OMADRMServerException();
  }

  //  \todo: Should we encode it here or read base64 data from XML file?
  Base64StringT serverInfo;
  if (Base64Factory::Encode(ByteSeq((ByteT*)info.data(), info.size()), serverInfo) == false) {
    return 0;
  }

  return new ROAPServerInfo(serverInfo);
}

} // namespace DRMPlugin
