/** \file OMADRMWSDecCommHandler.h

    Web service implementation of OMA DRM decoding communication handler.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMWSDECCOMMHANDLER_H)
#define OMADRMWSDECCOMMHANDLER_H

#include "OMADRMCommException.h"
#include "IOMADRMDecCommHandler.h"
#include "DRMLogger.h"
#include "OMADRMWS.hpp"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Web service implementation of OMA DRM decoding communication handler.

    Uses axis for sending/receiving messages.
*/
class OMADRMWSDecCommHandler: public IOMADRMDecCommHandler {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.

      If fails, throws OMADRMCommException.
  */
  OMADRMWSDecCommHandler(DRMLogger& logger);

  /*! \brief  Destructor.

      If fails, throws OMADRMCommException.
  */
  virtual ~OMADRMWSDecCommHandler();

  /*! \brief  Send initial content rights objects request.

      \param  request             input, content rights objects request.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendInitialRORequest(const NZSPtr<InitialRORequest>& request,
    const NZSPtr<URIValue>& url);

  /*! \brief  Send device hello message to the server.

      \param  request             input, device hello message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendDeviceHello(const NZSPtr<DeviceHelloRequest>& request,
    const NZSPtr<URIValue>& url);

  /*! \brief  Send registration request message to the server.

      \param  request             input, registration request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendRegRequest(const NZSPtr<RegRequest>& request,
    const NZSPtr<URIValue>& url);

  /*! \brief  Send rights objects request message to the server.

      \param  request             input, rights objects request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendRORequest(const NZSPtr<RORequest>& request,
    const NZSPtr<URIValue>& url);

  /*! \brief  Send join domain request message to the server.

      \param  request             input, join domain request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendJoinDomainRequest(const NZSPtr<JoinDomainRequest>& request,
    const NZSPtr<URIValue>& url);

  /*! \brief  Send leave domain request message to the server.

      \param  request             input, leave domain request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendLeaveDomainRequest(const NZSPtr<LeaveDomainRequest>& request,
    const NZSPtr<URIValue>& url);
  
  /*! \brief  Set up all neccessary data and start message delivering/receiving.

      \param  omaagent          input, OMA DRM agent.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Run(IOMADRMDecAgent* omaagent);

private:
  IOMADRMDecAgent* agent;
  OMADRMWS* ws;
  DRMLogger& commLogger;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMWSDECCOMMHANDLER_H)
