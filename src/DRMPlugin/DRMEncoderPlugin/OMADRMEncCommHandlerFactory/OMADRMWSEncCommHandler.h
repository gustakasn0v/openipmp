/** \file OMADRMWSEncCommHandler.h

    Web service implementation of OMA DRM encoding communication handler.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMWSENCCOMMHANDLER_H)
#define OMADRMWSENCCOMMHANDLER_H

#include "OMADRMCommException.h"
#include "IOMADRMEncCommHandler.h"
#include "DRMLogger.h"

#include "OMADRMWS.hpp"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Web service implementation of OMA DRM encoding communication handler.

    Uses axis for sending/receiving messages.
*/
class OMADRMWSEncCommHandler: public IOMADRMEncCommHandler {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.

      If fails, throws OMADRMCommException.
  */
  OMADRMWSEncCommHandler(DRMLogger& logger);

  /*! \brief  Destructor.

      If fails, throws OMADRMCommException.
  */
  virtual ~OMADRMWSEncCommHandler();

  /*! \brief  Send add content encryption key request.

      \param  request             input, add content encryption key request.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendAddContentKeyRequest(const NZSPtr<AddContentKeyRequest>& request,
    const NZSPtr<URIValue>& url);

  /*! \brief  Send add rights for device for content request.

      \param  request             input, add rights for device for content request.
      \param  url                 input, URL where to send the message.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SendAddDeviceRightsRequest(const NZSPtr<AddDeviceRightsRequest>&
    request, const NZSPtr<URIValue>& url);

  /*! \brief  Set up all neccessary data and start message delivering/receiving.

      \param  omaagent          input, OMA DRM encoding agent.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Run(IOMADRMEncAgent* omaagent);

private:
  IOMADRMEncAgent* agent;
  OMADRMWS* ws;
  DRMLogger& commLogger;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMWSENCCOMMHANDLER_H)
