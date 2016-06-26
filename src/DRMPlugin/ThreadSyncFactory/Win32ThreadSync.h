/**	\file Win32ThreadSync.h

  Thread and synchronization objects implementations on win32 platform.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (WIN32THREADSYNC_H)
#define WIN32THREADSYNC_H

#include "IThreadSync.h"
#include "DRMLogger.h"

#if defined (WIN32)

#include <windows.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Mutex implementation on win32 platform.
*/
class Win32GlobalMutex: public IMutex {
public:
  /*! \brief  Constructor.

      Creates win32 mutex without security attributes, without initial
      ownership and without name.

      If fails, throws ThreadSyncException.
  */
  Win32GlobalMutex();

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~Win32GlobalMutex();

  /*! \brief  Obtain mutex lock. Waits for finite time.

      \param  timeout     input, wait timeout.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Lock(unsigned int timeout);

  /*! \brief  Obtain mutex lock. Waits infinitely.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Lock();

  /*! \brief  Release mutex lock.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Release();

private:
  HANDLE mutex;
};

/*! \brief  Mutex implementation on win32 platform.
*/
class Win32Mutex: public IMutex {
public:
  /*! \brief  Constructor.

      Creates win32 mutex without security attributes, without initial
      ownership and without name.

      \param  logger      message logger.

      If fails, throws ThreadSyncException.
  */
  Win32Mutex(DRMLogger& logger);

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~Win32Mutex();

  /*! \brief  Obtain mutex lock. Waits for finite time.

      \param  timeout     input, wait timeout.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Lock(unsigned int timeout);

  /*! \brief  Obtain mutex lock. Waits infinitely.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Lock();

  /*! \brief  Release mutex lock.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Release();

private:
  DRMLogger& mutexLogger;
  HANDLE mutex;
};

/*! \brief  Event implementation on win32 platform.

    Event is manually resetable.
*/
class Win32Event: public IEvent {
public:
  /*! \brief  Constructor.

      Creates win32 event without security attributes, manually resetable,
      initially unsignaled and without name.

      \param  logger      message logger.

      If fails, throws ThreadSyncException.
  */
  Win32Event(DRMLogger& logger);

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~Win32Event();

  /*! \brief  Wait till event becomes signaled. Waits for finite time.

      \param  timeout     input, wait timeout.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Wait(unsigned int timeout);

  /*! \brief  Wait till event becomes signaled. Waits infinitely.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Wait();

  /*! \brief  Set event to signaled.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Set();

  /*! \brief  Set event to unsignaled.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Unset();

private:
  DRMLogger& eventLogger;
  HANDLE event;
};

/*! \brief  Thread interface.

    Threads are run when they are created.
*/
class Win32Thread: public IThread {
public:
  /*! \brief  Constructor.

      Creates win32 thread without security attributes, with default stack size
      and immediately runs it.

      \param  start     thread start function.
      \param  par       thread function parameters.
      \param  logger      message logger.

      If fails, throws ThreadSyncException.
  */
  Win32Thread(void (*start)(void*), void* par, DRMLogger& logger);

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~Win32Thread();

private:
  HANDLE thread;
};

} // namespace DRMPlugin

#endif // defined (WIN32)

#endif // !defined (WIN32THREADSYNC_H)
