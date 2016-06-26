/** \file FileOMADRMDecAgent.h

    Implementation of agent handling OMA DRM device messages.
    Uses file storage databases.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (FILEOMADRMDECAGENT_H)
#define FILEOMADRMDECAGENT_H

#include "OMADRMDecAgent.h"
#include "IXMLDocument.h"
#include "DRMLogger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Caching agent's rights issuer context factory (parser).
*/
class CacheAgentRIContextFactory {
public:
  /*! \brief  Create (parse) caching agent's rights issuer context.

      \param  xml       input, XML document.
      \param  logger    input, message logger.

      \returns  New rights issuer context. If fails, throws DRMDecManagerException.
  */
  static SPtr<CacheAgentRIContext> ParseContext(IXMLElement* xml, DRMLogger& logger);
};

/*! \brief  Non-caching agent's rights issuer context factory (parser).
*/
class NCacheAgentRIContextFactory {
public:
  /*! \brief  Create (parse) non-caching agent's rights issuer context.

      \param  xml       input, XML document.
      \param  logger    input, message logger.

      \returns  New rights issuer context. If fails, throws DRMDecManagerException.
  */
  static SPtr<NCacheAgentRIContext> ParseContext(IXMLElement* xml, DRMLogger& logger);
};

/*! \brief  Caching agent registration database using file storage.
*/
class FileCacheAgentRegDatabase: public CacheAgentRegDatabase {
public:
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
  FileCacheAgentRegDatabase(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Save database for future use.

      Saves database to the same file that it was read from in constructor.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

private:
  std::string fName;
};

/*! \brief  Non-caching agent registration database using file storage.
*/
class FileNCacheAgentRegDatabase: public NCacheAgentRegDatabase {
public:
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
  FileNCacheAgentRegDatabase(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Save database for future use.

      Saves database to the same file that it was read from in constructor.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

private:
  std::string fName;
};

/*! \brief  Current agent rights objects database using file storage.

    It is the result of all rights objects acquisition sessions performed.
*/
class FileAgentRODatabase: public AgentRODatabase {
public:
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
  FileAgentRODatabase(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Save database for future use.

      Saves database to the same file that it was read from in constructor.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SaveDatabase();

private:
  std::string fName;
};

/*! \brief  Implementation of agent handling OMA DRM device messages.

    Uses file storage databases (see FileCacheAgentRegDatabase,
    FileNCacheAgentRegDatabase, FileAgentRODatabase).

    \ingroup omadrmdecagent
*/
class FileOMADRMDecAgent: public OMADRMDecAgent {
public:
  /*! \brief  Constructor.

      See FileOMADRMDecAgent::InitDevCtx documentation for XML document format.

      \param  xmlDoc            XML document.
      \param  logger            message logger.

      If fails, throws DRMDecManagerException.
  */
  FileOMADRMDecAgent(IXMLElement* xmlDoc, DRMLogger& logger);

  virtual ~FileOMADRMDecAgent();

  /*! \brief  Get device context.

      \returns  Device context.
  */
  virtual const NZSPtr<AgentDeviceContext>& GetDeviceCtx();

  /*! \brief  Get registration database.

      \returns  Registration database.
  */
  virtual NZSPtr<AgentRegDatabase> GetRegDB();

  /*! \brief  Get rights objects database.

      \returns  Rights objects database.
  */
  virtual NZSPtr<AgentRODatabase> GetRODB();

  NZSPtr<AgentDeviceContext> devicectx;
  NZSPtr<AgentRegDatabase> regDB;
  NZSPtr<AgentRODatabase> roDB;

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
  NZSPtr<AgentDeviceContext> InitDevCtx(IXMLElement* xml,
    const NZSPtr<OMADRMDefTimer>& timer, DRMLogger& logger);

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
  NZSPtr<OMAPublicCertificate> InitPublicCert(IXMLElement* xml,
    const NZSPtr<OMADRMDefTimer>& timer, DRMLogger& logger);

  /*! \brief  Initialize device key identifier.

      \param  cer       input, device public certificate.
      \param  logger    input, message logger.

      \returns  Device key identifier. If fails, throws DRMDecManagerException.
  */
  NZSPtr<ROAPKeyIdentifier> InitKeyID(const NZSPtr<OMAPublicCertificate>& cer, DRMLogger& logger);

  /*! \brief  Initialize device identifier.

      \param  keyid       input, device key identifier.
      \param  logger      input, message logger.

      \returns  Device identifier. If fails, throws DRMDecManagerException.
  */
  NZSPtr<ROAPIdentifier> InitID(const NZSPtr<ROAPKeyIdentifier>& keyid, DRMLogger& logger);

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
  NZSPtr<OMAPrivateKey> InitPrivateKey(IXMLElement* xml, DRMLogger& logger);

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
  NZSPtr<ROAPCertificateChain> InitCertChain(IXMLElement* xml, DRMLogger& logger);

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
  Base64StringT InitCA(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Initialize device root CA key identifier.

      \param  ca          input, root CA certificate.
      \param  logger      input, message logger.

      \returns Root CA key identifier. If fails, throws DRMDecManagerException.
  */
  NZSPtr<ROAPKeyIdentifier> InitCAID(const Base64StringT& ca, DRMLogger& logger);

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
  std::vector<Base64StringT> InitCAs(IXMLElement* xml, DRMLogger& logger);

  /*! \brief  Initialize device trusted CA key identifiers.

      \param  trusted     input, trusted CA certificates.
      \param  logger      input, message logger.

      \returns Root CA key identifiers. If fails, throws DRMDecManagerException.
  */
  NZSPtr<ROAPKeyIdentifiers> InitCAIDs(std::vector<Base64StringT>& trusted, DRMLogger& logger);

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
  NZSPtr<DeviceDetailsData> InitDetails(IXMLElement* xml, DRMLogger& logger);

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
  NZSPtr<ROAPVersion> InitVersion(IXMLElement* xml, DRMLogger& logger);

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
  SPtr<CertCachingExtension> InitCaching(IXMLElement* xml, DRMLogger& logger);

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
  std::vector<NZSPtr<URIValue> > InitAlgorithms(IXMLElement* xml, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (FILEOMADRMDECAGENT_H)
