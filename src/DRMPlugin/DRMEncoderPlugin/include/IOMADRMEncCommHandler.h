/** \file IOMADRMEncCommHandler.h

    OMA DRM communication handler, used for sending OMA DRM encoding messages.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (IOMADRMENCCOMMHANDLER_H)
#define IOMADRMENCCOMMHANDLER_H

#include "IOMADRMEncAgent.h"
#include "ROAPMessages.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OMA DRM encoding communication handler.

    Used for OMA DRM encoding messages sending.
*/
class IOMADRMEncCommHandler {
public:
  virtual ~IOMADRMEncCommHandler () {
  }

  /*! \brief  Send add content encryption key request.

      \param  request             input, add content encryption key request.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendAddContentKeyRequest(const NZSPtr<AddContentKeyRequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Send add rights for device for content request.

      \param  request             input, add rights for device for content request.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendAddDeviceRightsRequest(const NZSPtr<AddDeviceRightsRequest>& request,
    const NZSPtr<URIValue>& url) = 0;

  /*! \brief  Set up all neccessary data and start message delivering/receiving.

      \param  omaagent          input, OMA DRM encoding agent.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Run(IOMADRMEncAgent* omaagent) = 0;
};

} // namespace DRMPlugin

#endif // !defined (IOMADRMENCCOMMHANDLER_H)
