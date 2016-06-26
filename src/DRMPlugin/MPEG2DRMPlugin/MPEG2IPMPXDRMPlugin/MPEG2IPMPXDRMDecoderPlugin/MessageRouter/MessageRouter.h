/**	\file MessageRouter.h

	IPMP message router.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (MESSAGEROUTER_H)
#define MESSAGEROUTER_H

/* disabled warning
	  'identifier' : identifier was truncated to 'number' characters in
	  the debug information
*/
#pragma warning(disable: 4786)

#include "BasicTypes.h"
#include <map>
#include <string>
#include "IPMPAgent.h"
#include "IPMPMessage.h"
#include "DRMLogger.h"
#include <queue>
#include "IThreadSync.h"

#if defined (WIN32)
#if defined MESSAGEROUTER_EXPORTS
#define MESSAGEROUTER_EXPORT __declspec(dllexport)
#else
#define MESSAGEROUTER_EXPORT __declspec(dllimport)
#endif // MESSAGEROUTER_EXPORTS
#elif defined (LINUX)
#define MESSAGEROUTER_EXPORT
#else
#define MESSAGEROUTER_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*! \brief  Message router exception.
*/
class MessageRouterException {
};

/*! \brief  Message router.

    Manages message communication between IPMP agents.
*/
class MessageRouter {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.

      In case of an error, throws MessageRouterException.
  */
  MESSAGEROUTER_EXPORT MessageRouter(DRMLogger& logger);

  /*! \brief  Destructor.

      Decrease number of references to deliverer and if it drops to 0, stop
      thread and clean up everything.

      In case of an error, throws MessageRouterException.
  */
  MESSAGEROUTER_EXPORT ~MessageRouter();

  /*! \brief  Set IPMP terminal.

      \warning  This function must be thread safe.

      \param  term       input, terminal.

      \returns  Boolean indicating succes or failure.
  */
  bool MESSAGEROUTER_EXPORT SetTerminal(IPMPAgent* term);

  /*! \brief  Add IPMP tool to list of tools.

      \warning  This function must be thread safe.

      \param  instanceID  input, instance identifier of the tool being added.
      \param  tool        input, tool to be added.

      \returns  Boolean indicating succes or failure.
  */
  bool MESSAGEROUTER_EXPORT AddTool(const Bit32T& instanceID, IPMPTool* tool);

  /*! \brief  Add IPMP tool to list of tools.

      \warning  This function must be thread safe.
      \warning  Identifier must be != 0.

      \param  id       input, identifier of the tool to be added.

      \returns  Boolean indicating succes or failure.
  */
  bool MESSAGEROUTER_EXPORT RemoveTool(const Bit32T& id);

  /*! \brief  Send message.

      \warning  This function must be thread safe.

      \param  in          input, input message.

      \returns  Boolean indicating success or failure.
  */
  bool MESSAGEROUTER_EXPORT SendMessage(IPMPMessageFromTool* in);

  /*! \brief  Send message to an IPMP tool.

      \warning  This function must be thread safe.

      \param  in          input, input message.

      \returns  Boolean indicating success or failure.
  */
  bool MESSAGEROUTER_EXPORT SendToolMessage(IPMPMessageFromBitstream* in);

  /*! \brief  Send message to an IPMP tool.

      \warning  This function must be thread safe.

      \param  in          input, input message.

      \returns  Boolean indicating success or failure.
  */
  bool MESSAGEROUTER_EXPORT SendToolMessage(IPMPDescriptorFromBitstream* in);

private:
  /*! \brief  Delivering thread function.
  */
  static void DelivererThread(void* lpParam);

  //! IPMP terminal (tool manager).
  static IPMPAgent* terminal;

  //! Map from identifier to tools.
  static std::map<Bit32T, IPMPTool*> tools;

  //! Message queue (IPMPMessageFromTool).
  static std::queue<IPMPMessageFromTool*> messages;

  //! Delivering thread handle.
  static IThread* deliverer;

  /*! Delivering thread stop event. Set by destructor to indicate to delivering
      thread to stop.
  */
  static IEvent* delivererStop;

  /*! Delivering thread exit event. Set by delivering thread when exiting to
      indicate to the destructor that it is exiting.
  */
  static IEvent* delivererExit;

  //! Reference count. When drops to 0, delivering thread is stopped.
  static unsigned int delivererRef;

  DRMLogger& routerLogger;
};

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin

#endif // !defined (MESSAGEROUTER_H)
