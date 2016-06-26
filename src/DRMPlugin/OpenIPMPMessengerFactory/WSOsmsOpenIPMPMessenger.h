/**	\file WSOsmsOpenIPMPMessenger.h

	Implementation of osms openIPMP messenger using web service.<br>

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

*/

#pragma warning(disable: 4786)

#include "OsmsOpenIPMPMessenger.h"
#include "OsmsWebService.hpp"

#if !defined (WSOSMSOPENIPMPMESSENGER_H)
#define WSOSMSOPENIPMPMESSENGER_H

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Sends osms messages using web service.

    \remark    All functions are thread-safe.
*/
class WSOsmsOpenIPMPMessenger : public OsmsOpenIPMPMessenger {
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

      If constructor fails, it throws OpenIPMPMessengerException and logger
      contains error description.
  */
	WSOsmsOpenIPMPMessenger(IXMLElement* xmlDoc, DRMLogger& logger);

	virtual ~WSOsmsOpenIPMPMessenger();

protected:
  /*! \brief  Assign content identifier using osms message via web service.

	    \param	userName		  input, user's name.
	    \param	password		  input, user's password.
	    \param	hostIP			  input, host's IP address.
	    \param	hostPort		  input, host's port.
	    \param	request 		  input, content identifier request.
	    \param	response		  output, content identifier response.

	    \returns	Boolean indicating success or failure.
  */
  virtual bool OsmsAssignContentID(const std::string& userName,
    const std::string& password, const std::string& hostIP, const int hostPort,
    osmsMessageRegisterContentAssignIdentifierRequest* request,
    osmsMessageRegisterContentAssignIdentifierResponse** response);

  /*! \brief  Register content encryption key with respect to content identifier
              using osms message via web service.

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
    osmsMessageRegisterDigitalItemInstanceResponse** response);

  /*! \brief  Get content encryption key with respect to content identifier
              using osms message via web service.

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
    osmsMessageLicenseRequest* request, osmsMessageLicenseResponse** response);

  /*! \brief  Grant license to user for the content identifier using 
              osms message via web service.

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
    osmsMessageRightsAuthorizationResponse** response);

private:
	void SetServiceEndpoint(const std::string& hostIP, const int hostPort);
	bool SetSoapHeaders(const std::string& userName, const std::string& password);
	bool CleanSoapHeaders();

	OsmsWebService* ws;
};

} // namespace DRMPlugin

#endif // !defined (WSOSMSOPENIPMPMESSENGER_H)
