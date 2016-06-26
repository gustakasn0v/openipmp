/**	\file ThreadSyncFactory.cpp

	Thread and synchronization objects management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "ThreadSyncFactory.h"
#include <vector>

#if defined (WIN32)
#include "Win32ThreadSync.h"
#elif defined (LINUX)
#include "PThreadsThreadSync.h"
#else
#pragma "Unrecognized platform. Default thread and synchronization objects will be 0."
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

#if defined (WIN32)

/*! \brief  Get new mutex.

    \param  logger    input, message logger.

    \returns  New mutex. If fails, 0.
*/
IMutex* ThreadSyncFactory::GetMutex(DRMLogger& logger) {
  try {
    return new Win32Mutex(logger);
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ThreadSyncFactory::GetMutex: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new global mutex.

    \returns  New mutex. If fails, 0.
*/
IMutex* ThreadSyncFactory::GetGlobalMutex() {
  try {
    return new Win32GlobalMutex();
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    return 0;
  }
}

/*! \brief  Get new event.

    \param  logger    input, message logger.

    \returns  New event. If fails, 0.
*/
IEvent* ThreadSyncFactory::GetEvent(DRMLogger& logger) {
  try {
    return new Win32Event(logger);
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ThreadSyncFactory::GetEvent: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new thread.

    \param  start     thread start function.
    \param  par       thread function parameters.
    \param  logger    input, message logger.

    \returns  New thread. If fails, 0.
*/
IThread* ThreadSyncFactory::GetThread(void (*start)(void*), void* par, DRMLogger& logger) {
  try {
    return new Win32Thread(start, par, logger);
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ThreadSyncFactory::GetThread: unknown exception...");
    return 0;
  }
}

#elif defined (LINUX)

/*! \brief  Get new mutex.

    \param  logger    input, message logger.

    \returns  New mutex. If fails, 0.
*/
IMutex* ThreadSyncFactory::GetMutex(DRMLogger& logger) {
  try {
    return new PThreadsMutex(logger);
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ThreadSyncFactory::GetMutex: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new global mutex.

    \returns  New mutex. If fails, 0.
*/
IMutex* ThreadSyncFactory::GetGlobalMutex() {
  try {
    return new PThreadsGlobalMutex();
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    return 0;
  }
}

/*! \brief  Get new event.

    \param  logger    input, message logger.

    \returns  New event. If fails, 0.
*/
IEvent* ThreadSyncFactory::GetEvent(DRMLogger& logger) {
  try {
    return new PThreadsEvent(logger);
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ThreadSyncFactory::GetEvent: unknown exception...");
    return 0;
  }
}

/*! \brief  Get new thread.

    \param  start     thread start function.
    \param  par       thread function parameters.
    \param  logger    input, message logger.

    \returns  New thread. If fails, 0.
*/
IThread* ThreadSyncFactory::GetThread(void (*start)(void*), void* par, DRMLogger& logger) {
  try {
    return new PThreadsThread(start, par, logger);
  }
  catch (ThreadSyncException) {
    return 0;
  }
  catch (...) {
    logger.UpdateLog("ThreadSyncFactory::GetThread: unknown exception...");
    return 0;
  }
}

#else

/*! \brief  Get new mutex.

    \param  logger    input, message logger.

    \returns  New mutex. If fails, 0.
*/
IMutex* ThreadSyncFactory::GetMutex(DRMLogger& logger) {
  return 0;
}

/*! \brief  Get new global mutex.

    \returns  New mutex. If fails, 0.
*/
IMutex* ThreadSyncFactory::GetGlobalMutex() {
  return 0;
}

/*! \brief  Get new event.

    \param  logger    input, message logger.

    \returns  New event. If fails, 0.
*/
IEvent* ThreadSyncFactory::GetEvent(DRMLogger& logger) {
  return 0;
}

/*! \brief  Get new thread.

    \param  start     thread start function.
    \param  par       thread function parameters.
    \param  logger    input, message logger.

    \returns  New thread. If fails, 0.
*/
IThread* ThreadSyncFactory::GetThread(void (*start)(void*), void* par, DRMLogger& logger) {
  return 0;
}

#endif

} // namespace DRMPlugin
