/**
    \defgroup omadrmserver Test OMA DRM server documentation.
*/
/** \file OMADRMServer.h

    Test server handling all OMA DRM rights issuer messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMSERVER_H)
#define OMADRMSERVER_H

#include "IXMLDocument.h"
#include "ServerROAP.h"
#include "IThreadSync.h"
#include "DRMLogger.h"
#include <string>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for OMA DRM server exception.
*/
class OMADRMServerException {
};

/*! \brief  Caching server's device context factory (parser).
*/
class CacheServerDeviceContextFactory {
public:
  /*! \brief  Create (parse) caching server's device context.

      \param  xml       input, XML document.
      \param  logger    input, message logger.

      \returns  New device context. If fails, throws OMADRMServerException.
  */
  static SPtr<CacheServerDeviceContext> ParseContext(IXMLElement* xml, DRMLogger& logger);
};

/*! \brief  Non-caching server's device context factory (parser).
*/
class NCacheServerDeviceContextFactory {
public:
  /*! \brief  Create (parse) non-caching server's device context.

      \param  xml       input, XML document.
      \param  logger    input, message logger.

      \returns  New device context. If fails, throws OMADRMServerException.
  */
  static SPtr<NCacheServerDeviceContext> ParseContext(IXMLElement* xml, DRMLogger& logger);
};

/*! \brief  Caching server registration database using file storage.
*/
class FileCacheServerRegDatabase: public CacheServerRegDatabase {
public:
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
  FileCacheServerRegDatabase(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Save database.

      Saves database to the same file that it was read from in constructor.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

private:
  std::string fName;
};

/*! \brief  Non-caching server registration database using file storage.
*/
class FileNCacheServerRegDatabase: public NCacheServerRegDatabase {
public:
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
  FileNCacheServerRegDatabase(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Save database.

      Saves database to the same file that it was read from in constructor.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

private:
  std::string fName;
};

/*! \brief  Current server rights objects database using file storage.

    Contains rights for contents issued for devices.
*/
class FileServerRODatabase: public ServerRODatabase {
public:
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
  FileServerRODatabase(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Save database.

      Saves database to the same file that it was read from in constructor.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

private:
  std::string fName;
};

/*! \brief  Test server handling OMA DRM rights issuer messages.

    Uses file storage databases (see FileCacheServerRegDatabase,
    FileNCacheServerRegDatabase, FileServerRODatabase).

    \ingroup omadrmserver
*/
class OMADRMServer: public GC {
public:
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
  OMADRMServer(IXMLElement* xml, DRMLogger& logger);

  ~OMADRMServer();

  /*! \brief  Handle add content encryption key request.

      \param  request             input, add content encryption key message.

      \returns  Add content encryption key response.
  */
  NZSPtr<AddContentKeyResponse> HandleAddContentKeyRequest(const
    NZSPtr<AddContentKeyRequest>& request);

  /*! \brief  Handle add rights for device for content request.

      \param  request             input, add rights for device for content message.

      \returns  Add rights for device for content response.
  */
  NZSPtr<AddDeviceRightsResponse> HandleAddDeviceRightsRequest(const
    NZSPtr<AddDeviceRightsRequest>& request);

  /*! \brief  Handle initial content rights objects request.

      In a real situation, return object should be either registration trigger
      or rights objects acquisition trigger. Since this is just a test case,
      we restrict return object to rights objects acquisition trigger.

      \param  request         input, initial content rights objects message.

      \returns  Rights objects acquisition trigger. If zero, failed.
  */
  SPtr<ROAcquisitionTrigger> HandleInitialRORequest(const NZSPtr<ServerInitialRORequest>& request);

  /*! \brief  Handle device hello message.

      \param  request             input, device hello message.

      \returns  Rights issuer hello response.
  */
  NZSPtr<RIHelloResponse> HandleDeviceHello(const NZSPtr<ServerDeviceHelloRequest>& request);

  /*! \brief  Handle registration request message.

      \param  request           input, registration request message.

      \returns  Registration response.
  */
  NZSPtr<RegResponse> HandleRegRequest(const NZSPtr<ServerRegRequest>& request);

  /*! \brief  Handle rights objects request message.

      \param  request           input, rights objects request message.

      \returns  2-pass rights objects response.
  */
  NZSPtr<TwoPassROResponse> HandleRORequest(const NZSPtr<ServerRORequest>& request);

  /*! \brief  Handle join domain request message.

      \param  request           input, join domain request message.

      \returns  Join domain response.
  */
  NZSPtr<JoinDomainResponse> HandleJoinRequest(const NZSPtr<ServerJoinDomainRequest>& request);

  /*! \brief  Handle leave domain request message.

      \param  request           input, leave domain request message.

      \returns  Leave domain response.
  */
  NZSPtr<LeaveDomainResponse> HandleLeaveRequest(const NZSPtr<ServerLeaveDomainRequest>& request);

  /*! \brief  Create registration request trigger (with nonce).

      \returns  Registration request trigger. If zero, failed.
  */
  SPtr<RegRequestTrigger> CreateRegTrigger();

  /*! \brief  Create non-domain rights objects acquisition trigger (with nonce).

      \param  deviceID          input, device identifier.
      \param  contentID         input, content identifier.

      \returns  Rights objects acquisition trigger. If zero, failed.
  */
  SPtr<ROAcquisitionTrigger> CreateROTrigger(const NZSPtr<ROAPIdentifier>& deviceID,
    const NZSPtr<URIValue>& contentID);

  /*! \brief  Create domain rights objects acquisition trigger (with nonce).

      \param  domainID          input, domain identifier.
      \param  contentID         input, content identifier.

      \returns  Rights objects acquisition trigger. If zero, failed.
  */
  SPtr<ROAcquisitionTrigger> CreateROTrigger(const NZSPtr<ROAPDomainIdentifier>&
    domainID, const NZSPtr<URIValue>& contentID);

  /*! \brief  Create join domain trigger (with nonce).

      \param  domainID          input, domain identifier.

      \returns  Join domain trigger. If zero, failed.
  */
  SPtr<JoinDomainTrigger> CreateJoinTrigger(const NZSPtr<ROAPDomainIdentifier>& domainID);

  /*! \brief  Create leave domain trigger (with nonce).

      \param  domainID          input, domain identifier.

      \returns  Leave domain trigger. If zero, failed.
  */
  SPtr<LeaveDomainTrigger> CreateLeaveTrigger(const NZSPtr<ROAPDomainIdentifier>& domainID);

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
  NZSPtr<ServerRIContext> InitRICtx(IXMLElement* xml, DRMLogger& logger);

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
  NZSPtr<OMAPublicCertificate> InitPublicCert(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Initialize rights issuer key identifier.

      \param  cer       input, server public certificate.
      \param  logger      input, message logger.

      \returns  Rights issuer key identifier. If fails, throws OMADRMServerException.
  */
  NZSPtr<ROAPKeyIdentifier> InitKeyID(const NZSPtr<OMAPublicCertificate>& cer, DRMLogger& logger);

  /*! \brief  Initialize rights issuer identifier.

      \param  keyid       input, server key identifier.
      \param  logger      input, message logger.

      \returns  Rights issuer identifier. If fails, throws OMADRMServerException.
  */
  NZSPtr<ROAPIdentifier> InitID(const NZSPtr<ROAPKeyIdentifier>& keyid, DRMLogger& logger);

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
  NZSPtr<OMAPrivateKey> InitPrivateKey(IXMLElement* xml, DRMLogger& logger);

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
  NZSPtr<ROAPCertificateChain> InitCertChain(IXMLElement* xml, DRMLogger& logger);

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
  std::vector<Base64StringT> InitCAs(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Initialize rights issuer root CA key identifiers.

      \param  trusted     input, root CA certificates.
      \param  logger      input, message logger.

      \returns Root CA key identifiers. If fails, throws OMADRMServerException.
  */
  NZSPtr<ROAPKeyIdentifiers> InitCAIDs(std::vector<Base64StringT>& trusted, DRMLogger& logger);

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
  std::vector<NZSPtr<URIValue> > InitAlgorithms(IXMLElement* xml, DRMLogger& logger);

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
  SPtr<CertCachingExtension> InitCaching(IXMLElement* xml, DRMLogger& logger);

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
  NZSPtr<ROAPVersion> InitVersion(IXMLElement* xml, DRMLogger& logger);

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
  NZSPtr<URIValue> InitURL(IXMLElement* xml, DRMLogger& logger);

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
  std::vector<Base64StringT> InitOCSPs(IXMLElement* xml, DRMLogger& logger);

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
  SPtr<DomainNameWhiteListExtension> InitDomains(IXMLElement* xml, DRMLogger& logger);

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
  SPtr<ROAPServerInfo> InitInfo(IXMLElement* xml, DRMLogger& logger);

private:
  NZSPtr<ServerRIContext> rissuer;
  IMutex* mutex;
  NZSPtr<ServerRegDatabase> regDB;
  NZSPtr<ServerProtocolTracker> serverRegTracker;
  NZSPtr<ServerRODatabase> roDB;
  NZSPtr<OMADRMNonceCreator> noncer;
  NZSPtr<OMADRMSessionIDCreator> sessioner;
  NZSPtr<OMACertificateVerifier> verifier;
  NZSPtr<OMADRMHasher> hasher;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMSERVER_H)
