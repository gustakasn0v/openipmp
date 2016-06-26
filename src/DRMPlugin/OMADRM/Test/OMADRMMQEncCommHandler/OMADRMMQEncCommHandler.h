/** \file OMADRMMQEncCommHandler.h

    Message queue implementation of OMA DRM encoding communication handler.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMMQENCCOMMHANDLER_H)
#define OMADRMMQENCCOMMHANDLER_H

#include "OMADRMCommException.h"
#include "IOMADRMEncCommHandler.h"
#include "DRMLogger.h"
#include "OMADRMServer.h"

#include "IThreadSync.h"
#include <queue>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Communication handler parameters passed to the delivering thread.
*/
class OMADRMMQEncCommHandlerParams {
public:
  /*! \brief  Constructor.

      \param  ag          OMA DRM encoding agent.
      \param  mQ          message queue.
      \param  mtex        synchronization mutex.
      \param  dstop       stopping event.
      \param  dexit       exitting event.
      \param  logger      message logger.
      \param  serv        OMA DRM server.
  */
  OMADRMMQEncCommHandlerParams(IOMADRMEncAgent* ag, std::queue<std::string> mQ, IMutex* mtex, IEvent* dstop, IEvent* dexit, DRMLogger& logger, OMADRMServer* serv): agent(ag), messageQ(mQ), mutex(mtex), delivererStop(dstop), delivererExit(dexit), commLogger(logger), server(serv) {
  }
  IOMADRMEncAgent* agent;
  std::queue<std::string> messageQ;
  IMutex* mutex;
  IEvent* delivererStop;
  IEvent* delivererExit;
  DRMLogger& commLogger;
  OMADRMServer* server;
};

/*! \brief  Message queue implementation of OMA DRM encoding communication handler.

    Uses message queue for sending/receiving messages.
*/
class OMADRMMQEncCommHandler: public IOMADRMEncCommHandler {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.

      If fails, throws OMADRMCommException.
  */
  OMADRMMQEncCommHandler(DRMLogger& logger);

  /*! \brief  Destructor.

      If fails, throws OMADRMCommException.
  */
  virtual ~OMADRMMQEncCommHandler();

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
  IThread* deliverer;
  OMADRMMQEncCommHandlerParams params;
  DRMLogger& commLogger;
};

} // namespace DRMPlugin

#endif // !defined (OMADRMMQENCCOMMHANDLER_H)
