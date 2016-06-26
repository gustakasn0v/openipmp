/**
    \defgroup omadrmencagent OMA DRM encoding agent documentation.
*/
/**	\file OMADRMEncAgent.h

	OMA DRM agent and manager used in encoding process.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OMADRMENCAGENT_H)
#define OMADRMENCAGENT_H

#include "IXMLDocument.h"
#include "DRMLogger.h"
#include <string>
#include <map>
#include "IOMADRMEncAgent.h"
#include "IOMADRMEncCommHandler.h"
#include "ROAPMessages.h"
#include "OMADRMCrypto.h"
#include "IThreadSync.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM agent and manager used in encoding process.

    Creates and stores keys (cipher encryptors), adds licenses for protected
    content. Uses communication handler for OMA DRM communication.

    \ingroup omadrmencagent
*/
class OMADRMEncAgent: public IOMADRMEncAgent {
public:
  /*! \brief  Constructor.

      \param  xml         XML document.
      \param  logger      message logger.

      If fails, throws DRMEncManagerException.
  */
  OMADRMEncAgent(IXMLElement* xml, DRMLogger& logger);

  virtual ~OMADRMEncAgent();

  /*! \brief  Add license for content.

      Use the information provided in the given XML document.

      Optional tags in the XML file are:
       - ROOT.License

      Mandatory tags in the XML file are:
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <License>dG2IhDioBnMdX1faxsuX0MCCmaQ=;2006-01-02T00:00:00Z;2006-12-31T00:00:00Z</License>
       <RightsHostURL>localhost:8080</RightsHostURL>
      </ROOT>

      \endverbatim

      \param    comm            input, communication handler.
      \param    contentID       string uniquely identifying the content.
      \param    xmlDoc          XML document.

      \returns  Boolean indicating success or failure.
  */
  bool AddLicense(IOMADRMEncCommHandler* comm, std::string& contentID, IXMLElement* xmlDoc);

  /*! \brief  Handle add content encryption key response.

      \param  response          input, add content encryption key response.
  */
  virtual void HandleAddContentKeyResponse(const NZSPtr<AddContentKeyResponse>& response);

  /*! \brief  Handle add rights for device for content response.

      \param  response          input, add rights for device for content response.
  */
  virtual void HandleAddDeviceRightsResponse(const NZSPtr<AddDeviceRightsResponse>& response);

  /*! \brief  Create content encryption key and store it with respect to content ID.

      Mandatory tags in the XML file are:
       - ROOT.RightsHostURL

      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <RightsHostURL>localhost:8080</RightsHostURL>
      </ROOT>

      \endverbatim

      \param    comm            input, communication handler.
      \param    contentID       input-output, (possibly updated) content identifier.
      \param    xmlDoc          input, XML document.
      \param    key             output, newly created key.
      \param    keySize         input, requested key size.

      \returns  Boolean indicating success or failure.
  */
  bool CreateAndStoreKey(IOMADRMEncCommHandler* comm, std::string& contentID,
    IXMLElement* xmlDoc, ByteT** key, UInt32T keySize);

protected:
  /*! \brief  Encode encryption key as a base64 string.

      \param  key         input, encryption key.
      \param  len         input, encryption key length.
      \param  enc         output, base64 encoded encryption key.

      \returns  Boolean indicating success or failure.
  */
  bool EncodeKey(const ByteT* key, const UInt32T len, Base64StringT& enc);

  /*! \brief  Parse license.

      \param  license         input, license string.
      \param  deviceID        output, device identifier.
      \param  oddStart        output, start date.
      \param  oddEnd          output, end date.

      \returns  Boolean indicating success or failure.
  */
  bool ParseLicense(const std::string& license, std::string& deviceID,
    SPtr<ODDStart>& oddStart, SPtr<ODDEnd>& oddEnd);

  bool exitFlag;

  IMutex* mutex;
  std::map<NZSPtr<ROAPNonce>, IEvent*> nonceToWait;
  NZSPtr<OMADRMNonceCreator> noncer;
  std::map<NZSPtr<ROAPNonce>, IEvent*> nonceToExit;
  DRMLogger& agentLogger;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMENCAGENT_H)
