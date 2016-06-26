/**	\file OpenIPMPMessengerFactory.h

  OpenIPMP messenger management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "IOpenIPMPMessenger.h"
#include "DRMLogger.h"

#if !defined (OPENIPMPMESSENGERFACTORY_H)
#define OPENIPMPMESSENGERFACTORY_H

#if defined (WIN32)
#if defined OPENIPMPMESSENGERFACTORY_EXPORTS
#define OPENIPMPMESSENGERFACTORY_EXPORT __declspec(dllexport)
#else
#define OPENIPMPMESSENGERFACTORY_EXPORT __declspec(dllimport)
#endif // OPENIPMPMESSENGERFACTORY_EXPORTS
#elif defined (LINUX)
#define OPENIPMPMESSENGERFACTORY_EXPORT
#else
#define OPENIPMPMESSENGERFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  OpenIPMP messenger manager.
*/
class OpenIPMPMessengerFactory {
public:
  /*! \brief  Create messenger using data contained in XML document.
  
      Messenger is newly created and caller must take care of its destruction.
      See specific messenger documentation for the correct format of the
      XML document.

      \param  xmlDoc      input, XML document.
      \param  logger      input-output, message logger.

      \return If successful, pointer to newly created messenger. If failed,
              0, and the logger's log will contain error description.
  */
  static OPENIPMPMESSENGERFACTORY_EXPORT IOpenIPMPMessenger* GetMessenger(
    IXMLElement* xmlDoc, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (OPENIPMPMESSENGERFACTORY_H)
