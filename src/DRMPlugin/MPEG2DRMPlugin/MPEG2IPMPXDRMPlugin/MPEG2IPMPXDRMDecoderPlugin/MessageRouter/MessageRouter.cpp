/**	\file MessageRouter.cpp

	IPMP message router.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "MessageRouter.h"

#include "BasicTypes.h"
#include <map>
#include <string>
#include "IPMPAgent.h"
#include "IPMPMessage.h"

#include "ThreadSyncFactory.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

//! MPEG2IPMPXDRMPlugin namespace. All MPEG2 IPMPX DRM plugin code resides in it.
namespace MPEG2IPMPXDRMPlugin {

/*!  \brief  Class used for handling globals.
*/
class MessageRouterGlobalHandler {
public:
  /*!  \brief  Constructor.

      If fails, throws MessageRouterException.
  */
  MessageRouterGlobalHandler(): aMutex(ThreadSyncFactory::GetGlobalMutex()) {
    if (aMutex == 0) {
      throw MessageRouterException();
    }
  }

  /*!  \brief  Destructor.
  */
  ~MessageRouterGlobalHandler() {
    if (aMutex != 0) delete aMutex; aMutex = 0;
  }

  /*!  \brief  Get message router mutex.

      \returns  Message router mutex.
  */
  IMutex* GetMutex() {
    return aMutex;
  }

private:
  IMutex* aMutex;
};

static MessageRouterGlobalHandler messageRouterGlobalHandler;

/*! \brief  Delivering thread function.
*/
void MessageRouter::DelivererThread(void* lpParam) {
  IPMPMessageFromTool* in = 0;
  IPMPMessageFromTool* out = 0;

  while (true) {
    if (delivererStop->Wait(100) == true) {
      //  Stop thread.
      if (delivererExit->Set() == false) {
        //  Error. What to do?
      }
      //  Exit.
      return;
//      ExitThread(0);
    }

    //  Get mutex.
    if (messageRouterGlobalHandler.GetMutex()->Lock(1000) == true) {
      //  Do the work.
      in = out = 0;
      if (messages.empty() == false) {
        in = messages.front();

        if (in->GetReceiver() == 0) {
          if (terminal == 0) {
            //  We have a message for the terminal, which is not yet set.
            //  This should not have happened.
            //  We do nothing, just continue.
          } else {
            messages.pop();
            //  Pass the message to terminal and retrieve response (if any).
            if (terminal->ProcessMessage(in, &out) == false) {
              //  Error. What to do?
            }
            //  If response was created, put it to message queue.
            if (out != 0) {
              messages.push(out);
            }
          }
        } else {
          if (tools.find(in->GetReceiver()) == tools.end()) {
            //  We have a message for a tool, which is not yet set.
            //  We do nothing, just continue.
          } else {
            messages.pop();
            //  Pass the message to terminal and retrieve response (if any).
            if (tools[in->GetReceiver()]->ProcessMessage(in, &out)
                == false) {
              //  Error. What to do?
            }
            //  If response was created, put it to message queue.
            if (out != 0) {
              messages.push(out);
            }
          }
        }
      }
      messageRouterGlobalHandler.GetMutex()->Release();
    }
  }
}

//! IPMP terminal (tool manager).
IPMPAgent* MessageRouter::terminal = 0;

//! Map from identifier to tools.
std::map<Bit32T, IPMPTool*> MessageRouter::tools;

//! Message queue (IPMPMessageFromTool).
std::queue<IPMPMessageFromTool*> MessageRouter::messages;

//! Delivering thread handle.
IThread* MessageRouter::deliverer = 0;

/*! Delivering thread stop event. Set by destructor to indicate to delivering
    thread to stop.
*/
IEvent* MessageRouter::delivererStop = 0;

/*! Delivering thread exit event. Set by delivering thread when exiting to
    indicate to the destructor that it is exiting.
*/
IEvent* MessageRouter::delivererExit = 0;

//! Reference count. When drops to 0, delivering thread is stopped.
unsigned int MessageRouter::delivererRef = 0;

/*! \brief  Message router.

    Manages message communication between IPMP agents.
*/
/*! \brief  Constructor.

    \param  logger      message logger.

    In case of an error, throws MessageRouterException.
*/
MessageRouter::MessageRouter(DRMLogger& logger): routerLogger(logger) {
  //  Check if neccessary synchronization members are set.
  if (messageRouterGlobalHandler.GetMutex() == 0) {
    //  Error.
    throw MessageRouterException();
  }

  if (messageRouterGlobalHandler.GetMutex()->Lock() == false) {
    throw MessageRouterException();
  }

  //  Got mutex, create delivering thread, if not already created.
  if (deliverer == 0) {
    if ((delivererStop = ThreadSyncFactory::GetEvent(routerLogger)) == 0) {
      //  Error.
      messageRouterGlobalHandler.GetMutex()->Release();
      throw MessageRouterException();
    }
    if ((delivererExit = ThreadSyncFactory::GetEvent(routerLogger)) == 0) {
      //  Error.
      delete delivererStop;
      messageRouterGlobalHandler.GetMutex()->Release();
      throw MessageRouterException();
    }
    if ((deliverer = ThreadSyncFactory::GetThread(DelivererThread, 0, routerLogger)) == 0) {
      //  Error.
      delete delivererStop;
      delete delivererExit;
      messageRouterGlobalHandler.GetMutex()->Release();
      throw MessageRouterException();
    }
  }

  delivererRef++;
  messageRouterGlobalHandler.GetMutex()->Release();
}

/*! \brief  Destructor.

    Decrease number of references to deliverer and if it drops to 0, stop
    thread and clean up everything.

    In case of an error, throws MessageRouterException.
*/
MessageRouter::~MessageRouter() {
  //  Check if neccessary synchronization members are set.
  if ((messageRouterGlobalHandler.GetMutex() == 0) || (delivererStop == 0) ||
      (delivererExit == 0) || (deliverer == 0)) {
    //  This should not have happened.
    throw MessageRouterException();
  }

  if (messageRouterGlobalHandler.GetMutex()->Lock() == false) {
    throw MessageRouterException();
  }

  std::map<Bit32T, IPMPTool*>::iterator iter;

  /*  Got mutex, stop delivering thread and clean up everything,
      if delivererRef == 0.
  */
  if (--delivererRef <= 0) {
    //  Stop delivering thread and clean up everything.
    //  Tell deliverer to stop.
    if (delivererStop->Set() == false) {
      //  Error.
      messageRouterGlobalHandler.GetMutex()->Release();
      throw MessageRouterException();
    }
    //  Wait till deliverer exits.
    if (delivererExit->Wait() == false) {
      messageRouterGlobalHandler.GetMutex()->Release();
      throw MessageRouterException();
    }
    //  Deliverer has exited, now clean up everything.
    /*  CHECK: If tool pointers are saved in the terminal, we shouldn't
        delete them here!
    */
    /*
    iter = tools.begin();
    while (iter != tools.end()) {
      delete iter->second;
      iter++;
    }
    */
    terminal = 0;
    tools.clear();
    while (messages.empty() == false) {
      delete messages.front();
      messages.pop();
    }
    delete deliverer; deliverer = 0;
    delete delivererStop; delivererStop = 0;
    delete delivererExit; delivererExit = 0;
  }

  messageRouterGlobalHandler.GetMutex()->Release();
}

/*! \brief  Set IPMP terminal.

    \warning  This function must be thread safe.

    \param  term       input, terminal.

    \returns  Boolean indicating succes or failure.
*/
bool MessageRouter::SetTerminal(IPMPAgent* term) {
  if (messageRouterGlobalHandler.GetMutex()->Lock() == true) {
    //  Got mutex, set terminal.
    //  What to do if terminal is already set? Error?
    if (terminal == 0) {
      terminal = term;
    }
    messageRouterGlobalHandler.GetMutex()->Release();
    return true;
  } else {
    messageRouterGlobalHandler.GetMutex()->Release();
    return false;
  }
}

/*! \brief  Add IPMP tool to list of tools.

    \warning  This function must be thread safe.

    \param  instanceID  input, instance identifier of the tool being added.
    \param  tool        input, tool to be added.

    \returns  Boolean indicating succes or failure.
*/
bool MessageRouter::AddTool(const Bit32T& instanceID, IPMPTool* tool) {
  if (tool == 0) {
    return false;
  }

  if (messageRouterGlobalHandler.GetMutex()->Lock() == true) {
    //  Got mutex, add tool.
    tools[instanceID] = tool;
    messageRouterGlobalHandler.GetMutex()->Release();
    return true;
  } else {
    return false;
  }
}

/*! \brief  Add IPMP tool to list of tools.

    \warning  This function must be thread safe.
    \warning  Identifier must be != 0.

    \param  id       input, identifier of the tool to be added.

    \returns  Boolean indicating succes or failure.
*/
bool MessageRouter::RemoveTool(const Bit32T& id) {
  if (id == 0) {
    return false;
  }

  if (messageRouterGlobalHandler.GetMutex()->Lock() == true) {
    //  Got mutex, remove tool.
    tools.erase(id);
    messageRouterGlobalHandler.GetMutex()->Release();
    return true;
  } else {
    return false;
  }
}

/*! \brief  Send message.

    \warning  This function must be thread safe.

    \param  in          input, input message.

    \returns  Boolean indicating success or failure.
*/
bool MessageRouter::SendMessage(IPMPMessageFromTool* in) {
  if (messageRouterGlobalHandler.GetMutex()->Lock() == true) {
    //  Got mutex, put message to message queue.
    messages.push(in);
    messageRouterGlobalHandler.GetMutex()->Release();
    return true;
  } else {
    return false;
  }
}

/*! \brief  Send message to an IPMP tool.

    \warning  This function must be thread safe.

    \param  in          input, input message.

    \returns  Boolean indicating success or failure.
*/
bool MessageRouter::SendToolMessage(IPMPMessageFromBitstream* in) {
  if (messageRouterGlobalHandler.GetMutex()->Lock() == true) {
    IPMPMessageFromTool* out = 0;
    //  Got mutex.
    //  Find receiver. If exists, call ProcessMessage() on the receiver and
    //  put response to message queue. If doesn't exist return false.
    if (tools.find(in->GetReceiver()) == tools.end()) {
      delete in;
      messageRouterGlobalHandler.GetMutex()->Release();
      return false; 
    }
    if (tools[in->GetReceiver()]->ProcessMessage(in, &out) == false) {
      //  Error.
      messageRouterGlobalHandler.GetMutex()->Release();
      return false;
    }
    if (out != 0) {
      messages.push(out);
    }
    messageRouterGlobalHandler.GetMutex()->Release();
    return true;
  } else {
    delete in;
    return false;
  }
}

/*! \brief  Send message to an IPMP tool.

    \warning  This function must be thread safe.

    \param  in          input, input message.

    \returns  Boolean indicating success or failure.
*/
bool MessageRouter::SendToolMessage(IPMPDescriptorFromBitstream* in) {
  if (messageRouterGlobalHandler.GetMutex()->Lock() == true) {
    IPMPMessageFromTool* out = 0;
    //  Got mutex.
    //  Find receiver. If exists, call ProcessMessage() on the receiver and
    //  put response to message queue. If doesn't exist return false.
    if (tools.find(in->GetReceiver()) == tools.end()) {
      delete in;
      messageRouterGlobalHandler.GetMutex()->Release();
      return false; 
    }
    if (tools[in->GetReceiver()]->ProcessMessage(in, &out) == false) {
      //  Error.
      messageRouterGlobalHandler.GetMutex()->Release();
      return false;
    }
    if (out != 0) {
      messages.push(out);
    }
    messageRouterGlobalHandler.GetMutex()->Release();
    return true;
  } else {
    delete in;
    return false;
  }
}

} // namespace MPEG2IPMPXDRMPlugin

} // namespace DRMPlugin
