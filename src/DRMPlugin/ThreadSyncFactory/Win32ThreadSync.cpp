/**	\file Win32ThreadSync.cpp

  Thread and synchronization objects implementations on win32 platform.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "Win32ThreadSync.h"

#if defined (WIN32)

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Mutex implementation on win32 platform.
*/
/*! \brief  Constructor.

    Creates win32 mutex without security attributes, without initial
    ownership and without name.

    If fails, throws ThreadSyncException.
*/
Win32GlobalMutex::Win32GlobalMutex(): mutex(CreateMutex(NULL, FALSE, NULL)) {
  if (mutex == NULL) {
    throw ThreadSyncException();
  }
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
Win32GlobalMutex::~Win32GlobalMutex() {
  if (CloseHandle(mutex) == false) {
    throw ThreadSyncException();
  }
}

/*! \brief  Obtain mutex lock. Waits for finite time.

    \param  timeout     input, wait timeout.

    \returns  Boolean indicating success or failure.
*/
bool Win32GlobalMutex::Lock(unsigned int timeout) {
  DWORD wait = WaitForSingleObject(mutex, timeout);
  switch (wait) {
  case WAIT_OBJECT_0:
    return true;
  default:
    return false;
  }
}

/*! \brief  Obtain mutex lock. Waits infinitely.

    \returns  Boolean indicating success or failure.
*/
bool Win32GlobalMutex::Lock() {
  DWORD wait = WaitForSingleObject(mutex, INFINITE);
  switch (wait) {
  case WAIT_OBJECT_0:
    return true;
  default:
    return false;
  }
}

/*! \brief  Release mutex lock.

    \returns  Boolean indicating success or failure.
*/
bool Win32GlobalMutex::Release() {
  if (ReleaseMutex(mutex) == 0) {
    return false;
  }
  return true;
}

/*! \brief  Mutex implementation on win32 platform.
*/
/*! \brief  Constructor.

    Creates win32 mutex without security attributes, without initial
    ownership and without name.

    \param  logger      message logger.

    If fails, throws ThreadSyncException.
*/
Win32Mutex::Win32Mutex(DRMLogger& logger): mutex(CreateMutex(NULL, FALSE, NULL)),     mutexLogger(logger) {
  if (mutex == NULL) {
    mutexLogger.UpdateLog("Win32Mutex::ctor: cannot create...");
    throw ThreadSyncException();
  }
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
Win32Mutex::~Win32Mutex() {
  if (CloseHandle(mutex) == false) {
    mutexLogger.UpdateLog("Win32Mutex::dtor: cannot close handle...");
    throw ThreadSyncException();
  }
}

/*! \brief  Obtain mutex lock. Waits for finite time.

    \param  timeout     input, wait timeout.

    \returns  Boolean indicating success or failure.
*/
bool Win32Mutex::Lock(unsigned int timeout) {
  DWORD wait = WaitForSingleObject(mutex, timeout);
  switch (wait) {
  case WAIT_OBJECT_0:
    return true;
  default:
//    mutexLogger.UpdateLog("Win32Mutex::Lock: cannot lock...");
    return false;
  }
}

/*! \brief  Obtain mutex lock. Waits infinitely.

    \returns  Boolean indicating success or failure.
*/
bool Win32Mutex::Lock() {
  DWORD wait = WaitForSingleObject(mutex, INFINITE);
  switch (wait) {
  case WAIT_OBJECT_0:
    return true;
  default:
    mutexLogger.UpdateLog("Win32Mutex::Lock: cannot lock...");
    return false;
  }
}

/*! \brief  Release mutex lock.

    \returns  Boolean indicating success or failure.
*/
bool Win32Mutex::Release() {
  if (ReleaseMutex(mutex) == 0) {
//    mutexLogger.UpdateLog("Win32Mutex::Release: cannot release...");
    return false;
  }
  return true;
}

/*! \brief  Event implementation on win32 platform.

    Event is manually resetable.
*/
/*! \brief  Constructor.

    Creates win32 event without security attributes, manually resetable,
    initially unsignaled and without name.

    \param  logger      message logger.

    If fails, throws ThreadSyncException.
*/
Win32Event::Win32Event(DRMLogger& logger): event(CreateEvent(NULL, true, false, NULL)),
    eventLogger(logger) {
  if (event == NULL) {
    eventLogger.UpdateLog("Win32Event::ctor: cannot create...");
    throw ThreadSyncException();
  }
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
Win32Event::~Win32Event() {
  if (CloseHandle(event) == false) {
    eventLogger.UpdateLog("Win32Event::dtor: cannot close handle...");
    throw ThreadSyncException();
  }
}

/*! \brief  Wait till event becomes signaled. Waits for finite time.

    \param  timeout     input, wait timeout.

    \returns  Boolean indicating success or failure.
*/
bool Win32Event::Wait(unsigned int timeout) {
  DWORD wait = WaitForSingleObject(event, timeout);
  switch (wait) {
  case WAIT_OBJECT_0:
    return true;
  default:
//    eventLogger.UpdateLog("Win32Event::Wait: wait failed...");
    return false;
  }
}

/*! \brief  Wait till event becomes signaled. Waits infinitely.

    \returns  Boolean indicating success or failure.
*/
bool Win32Event::Wait() {
  DWORD wait = WaitForSingleObject(event, INFINITE);
  switch (wait) {
  case WAIT_OBJECT_0:
    return true;
  default:
    eventLogger.UpdateLog("Win32Event::Wait: wait failed...");
    return false;
  }
}

/*! \brief  Set event to signaled.

    \returns  Boolean indicating success or failure.
*/
bool Win32Event::Set() {
  if (SetEvent(event) == 0) {
//    eventLogger.UpdateLog("Win32Event::Set: cannot set event...");
    return false;
  }
  return true;
}

/*! \brief  Set event to unsignaled.

    \returns  Boolean indicating success or failure.
*/
bool Win32Event::Unset() {
  if (ResetEvent(event) == 0) {
//    eventLogger.UpdateLog("Win32Event::Unset: cannot unset event...");
    return false;
  }
  return true;
}

/*! \brief  Thread interface.

    Threads are run when they are created.
*/
/*! \brief  Constructor.

    Creates win32 thread without security attributes, with default stack size
    and immediately runs it.

    \param  start     thread start function.
    \param  par       thread function parameters.
    \param  logger    message logger.

    If fails, throws ThreadSyncException.
*/
Win32Thread::Win32Thread(void (*start)(void*), void* par, DRMLogger& logger): thread(NULL) {
  DWORD idThread;
  thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)start, par, 0, &idThread);
  if (thread == NULL) {
    logger.UpdateLog("Win32Thread::ctor: cannot create thread...");
    throw ThreadSyncException();
  }
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
Win32Thread::~Win32Thread() {
  if (CloseHandle(thread) == false) {
    throw ThreadSyncException();
  }
}

} // namespace DRMPlugin

#endif // defined (WIN32)
