/**	\file IOpenIPMPMessenger.h

	Interfaces for messenger used for communication with openIPMP server.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IOPENIPMPMESSENGER_H)
#define IOPENIPMPMESSENGER_H

#include "BasicTypes.h"
#include "IXMLDocument.h"
#include <string>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Exception used for openIPMP messenger error.
*/
class OpenIPMPMessengerException {
};

/*! \brief Class used by other managers for communication with openIPMP server.
    
    \remark    All functions are thread-safe.
*/
class IOpenIPMPMessenger {
public:
  virtual ~IOpenIPMPMessenger() {
  }

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
    const std::string& contentInfo, std::string& contentID) = 0;

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
    ByteT* key, UInt32T keyLen, std::string& contentID) = 0;

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
    UInt32T* keyLen, const std::string& contentID) = 0;

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
    const int endYear, const int endMonth, const int endDay) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IOPENIPMPMESSENGER_H)
