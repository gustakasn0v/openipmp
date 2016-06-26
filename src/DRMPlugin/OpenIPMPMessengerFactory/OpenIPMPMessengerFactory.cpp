/**	\file OpenIPMPMessengerFactory.cpp

  OpenIPMP messenger management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenIPMPMessengerFactory.h"
#include "SquashXMLOsmsOpenIPMPMessenger.h"
#include "WSOsmsOpenIPMPMessenger.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Create messenger using data contained in XML document.

    Messenger is newly created and caller must take care of its destruction.
    See specific messenger documentation for the correct format of the
    XML document.

    \param  xmlDoc      input, XML document.
    \param  logger      input-output, message logger.

    \return If successful, pointer to newly created messenger. If failed,
            0, and the logger's log will contain error description.
*/
IOpenIPMPMessenger* OpenIPMPMessengerFactory::GetMessenger(IXMLElement* xmlDoc,
    DRMLogger& logger) {
  try {
//    return new SquashXMLOsmsOpenIPMPMessenger(xmlDoc, logger);
    return new WSOsmsOpenIPMPMessenger(xmlDoc, logger);
  }
  catch (OpenIPMPMessengerException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("OpenIPMPMessengerFactory::GetMessenger: unknown exception...");
    return 0;
  }
}

} // namespace DRMPlugin
