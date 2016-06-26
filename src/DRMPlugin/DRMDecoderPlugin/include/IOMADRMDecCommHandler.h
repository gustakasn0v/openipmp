/** \file IOMADRMDecCommHandler.h

    OMA DRM communication handler, used for sending OMA DRM decoding messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (IOMADRMDECCOMMHANDLER_H)
#define IOMADRMDECCOMMHANDLER_H

#include "IOMADRMDecAgent.h"
#include "ROAPMessages.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM decoding communication handler.

    Used for OMA DRM decoding messages sending.
*/
class IOMADRMDecCommHandler {
public:
  virtual ~IOMADRMDecCommHandler () {
  }

  /*! \brief  Send initial content rights objects request.

      \param  request             input, content rights objects request.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendInitialRORequest(const NZSPtr<InitialRORequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Send device hello message to the server.

      \param  request             input, device hello message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendDeviceHello(const NZSPtr<DeviceHelloRequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Send registration request message to the server.

      \param  request             input, registration request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendRegRequest(const NZSPtr<RegRequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Send rights objects request message to the server.

      \param  request             input, rights objects request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendRORequest(const NZSPtr<RORequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Send join domain request message to the server.

      \param  request             input, join domain request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendJoinDomainRequest(const NZSPtr<JoinDomainRequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Send leave domain request message to the server.

      \param  request             input, leave domain request message.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendLeaveDomainRequest(const NZSPtr<LeaveDomainRequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Set up all neccessary data and start message delivering/receiving.

      \param  omaagent          input, OMA DRM agent.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Run(IOMADRMDecAgent* omaagent) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IOMADRMDECCOMMHANDLER_H)
