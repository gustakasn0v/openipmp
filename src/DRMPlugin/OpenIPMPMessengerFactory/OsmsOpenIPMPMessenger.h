/**	\file OsmsOpenIPMPMessenger.h

	Implementation of openIPMP messenger using osms messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (OSMSOPENIPMPMESSENGER_H)
#define OSMSOPENIPMPMESSENGER_H

#include "IOpenIPMPMessenger.h"
#include "DRMLogger.h"

#include "io/message/osmsMessageUserLoginRequest.h"
#include "io/message/osmsMessageUserLoginResponse.h"
#include "io/message/osmsMessageUserLogoutRequest.h"
#include "io/message/osmsMessageUserLogoutResponse.h"
#include "io/message/osmsMessageRegisterContentAssignIdentifierRequest.h"
#include "io/message/osmsMessageRegisterContentAssignIdentifierResponse.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceRequest.h"
#include "io/message/osmsMessageRegisterDigitalItemInstanceResponse.h"
#include "io/message/osmsMessageLicenseRequest.h"
#include "io/message/osmsMessageLicenseResponse.h"
#include "io/message/osmsMessageRightsAuthorizationRequest.h"
#include "io/message/osmsMessageRightsAuthorizationResponse.h"
#include "IXMLDocument.h"
#include "crypto/CryptoManager.h"
#include "busobj/DigitalSignature.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Uses osms messages to implement communication with openIPMP server.

    \remark    All functions are thread-safe.
*/
class OsmsOpenIPMPMessenger: public IOpenIPMPMessenger {
public:
  /*! \brief  Constructor.
  
      Use the information provided in the XML document.

      Optional tags in the XML file are:
       - ROOT.P12FilePath
       - ROOT.RandomNumberFilePath.

      If ROOT.P12FilePath tag is not present, p12 path is set to \localsecurity\.
      If ROOT.RandomNumberFilePath tag is not present, random number file path is
      set to .\entropy.dat.
      Here follows an example of a correctly formatted XML document.

      \verbatim

      <ROOT>
       <P12FilePath>\localsecurity\</P12FilePath>
       <RandomNumberFilePath>.\entropy.dat</RandomNumberFilePath>
      </ROOT>

      \endverbatim

      \param    xmlDoc          input, XML document.
      \param    logger          input-output, message logger.

      If constructor fails, it throws OpenIPMPMessengerException and logger's
      log contains error description.
  */
  OsmsOpenIPMPMessenger(IXMLElement* xmlDoc, DRMLogger& logger);

  virtual ~OsmsOpenIPMPMessenger();

  /*! \brief  Assign content identifier.

      \param    userName          input, user's name.
      \param    password          input, user's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    contentInfo       input, basic content information.
      \param    contentID         output, assigned content identifier.

      \returns  Boolean indicating success or failure.
  */
  virtual bool AssignContentID(const std::string& userName, const std::string&
    password, const std::string& hostIP, const int hostPort,
    const std::string& contentInfo, std::string& contentID);

  /*! \brief  Register content encryption key with respect to content identifier.

      \param    userName          input, user's name.
      \param    password          input, user's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    key               input, encryption key.
      \param    keyLen            input, encryption key length.
      \param    contentID         input-output, content identifier, possibly
                                  updated in the process.

      \returns  Boolean indicating success or failure.
  */
  virtual bool RegisterKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    ByteT* key, UInt32T keyLen, std::string& contentID);

  /*! \brief  Get content encryption key with respect to content identifier.

      \param    userName          input, user's name.
      \param    password          input, user's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    key               output, encryption key.
      \param    keyLen            output, encryption key length.
      \param    contentID         input, content identifier.

      \returns  Boolean indicating success or failure.
  */
  virtual bool GetKeyForContent(const std::string& userName, const std::string&
    password, const std::string& hostIP, const int hostPort, ByteT** key,
    UInt32T* keyLen, const std::string& contentID);

  /*! \brief  Grant license to user for the content identifier.

      \param    userName          input, granter's name.
      \param    password          input, granter's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    contentID         input, content identifier.
      \param    grantee           input, user to which the license is granted.
      \param    licenseType       input, type of the license granted.
      \param    startYear         input, start year for the license.
      \param    startMonth        input, start month for the license.
      \param    startDay          input, start day for the license.
      \param    endYear           input, end year for the license.
      \param    endMonth          input, end month for the license.
      \param    endDay            input, end day for the license.

      \returns  Boolean indicating success or failure.
  */
  virtual bool GrantLicenseForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    const std::string& contentID, const std::string& grantee, const std::string&
    licenseType, const int startYear, const int startMonth, const int startDay,
    const int endYear, const int endMonth, const int endDay);

protected:
  /*! \brief  Verify signature on data.

      \param    data              input, signed data.
      \param    signature         input, signature.
      \param    userCtx           input, user context.

      \returns  Boolean indicating whether signature is valid or not.
  */
  bool VerifySignature(const std::string& data, DigitalSignature* signature,
    UserContext* userCtx);

  /*! \brief  Assign content identifier using osms message.

      \param    userName          input, user's name.
      \param    password          input, user's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    request           input, content identifier request.
      \param    response          output, content identifier response.

      \returns  Boolean indicating success or failure.
  */
  virtual bool OsmsAssignContentID(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRegisterContentAssignIdentifierRequest* request,
    osmsMessageRegisterContentAssignIdentifierResponse** response) = 0;

  /*! \brief  Register content encryption key with respect to content identifier
              using osms message.

      \param    userName          input, user's name.
      \param    password          input, user's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    request           input, register content/key request.
      \param    response          output, register content/key response.

      \returns  Boolean indicating success or failure.
  */
  virtual bool OsmsRegisterKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRegisterDigitalItemInstanceRequest* request,
    osmsMessageRegisterDigitalItemInstanceResponse** response) = 0;

  /*! \brief  Get content encryption key with respect to content identifier using
              osms message.

      \param    userName          input, user's name.
      \param    password          input, user's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    request           input, get key request.
      \param    response          output, get key response.

      \returns  Boolean indicating success or failure.
  */
  virtual bool OsmsGetKeyForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageLicenseRequest* request, osmsMessageLicenseResponse** response) = 0;

  /*! \brief  Grant license to user for the content identifier.

      \param    userName          input, granter's name.
      \param    password          input, granter's password.
      \param    hostIP            input, host's IP address.
      \param    hostPort          input, host's port.
      \param    request           input, grant license request.
      \param    response          output, grant license response.

      \returns  Boolean indicating success or failure.
  */
  virtual bool OsmsGrantLicenseForContent(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRightsAuthorizationRequest* request,
    osmsMessageRightsAuthorizationResponse** response) = 0;

protected:
  DRMLogger& messengerLogger;

private:
  /*! \brief  Get simple DOI identifier from full DOI content ID string.

      \param  contentID       input, full DOI contentID string.
      \param  doi             output, simple DOI identifier.

      \returns  Boolean indicating success or failure.
  */
  bool GetDOIFromContentID(const std::string& contentID, std::string& doi);

  CryptoManager* cryptoManager;
};

} // namespace DRMPlugin

#endif // !defined (OSMSOPENIPMPMESSENGER_H)
