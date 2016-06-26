/**	\file PThreadsThreadSync.h

  Thread and synchronization objects implementations using pthreads.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (PTHREADSTHREADSYNC_H)
#define PTHREADSTHREADSYNC_H

#include "IThreadSync.h"
#include "DRMLogger.h"

#if defined (PTHREADS)

#include <pthread.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Mutex implementation using pthreads.
*/
class PThreadsGlobalMutex: public IMutex {
public:
  /*! \brief  Constructor.

      Creates mutex without security attributes, without initial
      ownership and without name.

      If fails, throws ThreadSyncException.
  */
  PThreadsGlobalMutex();

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~PThreadsGlobalMutex();

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
  pthread_mutex_t id;
};

/*! \brief  Mutex implementation using pthreads.
*/
class PThreadsMutex: public IMutex {
public:
  /*! \brief  Constructor.

      Creates mutex without security attributes, without initial
      ownership and without name.

      \param  logger      message logger.

      If fails, throws ThreadSyncException.
  */
  PThreadsMutex(DRMLogger& logger);

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~PThreadsMutex();

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
  pthread_mutex_t id;
};

/*! \brief  Event implementation using pthreads.

    Event is manually resetable.
*/
class PThreadsEvent: public IEvent {
public:
  /*! \brief  Constructor.

      Creates event without security attributes, manually resetable,
      initially unsignaled and without name.

      \param  logger      message logger.

      If fails, throws ThreadSyncException.
  */
  PThreadsEvent(DRMLogger& logger);

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~PThreadsEvent();

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
  pthread_mutex_t mtex;
  pthread_cond_t cond;
  bool signaled;
};

/*! \brief  Thread implementation using pthreads.

    Threads are run when they are created.
*/
class PThreadsThread: public IThread {
public:
  /*! \brief  Constructor.

      Creates thread without security attributes, with default stack size
      and immediately runs it.

      \param  start     thread start function.
      \param  par       thread function parameters.
      \param  logger      message logger.

      If fails, throws ThreadSyncException.
  */
  PThreadsThread(void (*start)(void*), void* par, DRMLogger& logger);

  /*! \brief  Destructor.

      If fails throws ThreadSyncException.
  */
  virtual ~PThreadsThread();

private:
  pthread_t handle;
};

} // namespace DRMPlugin

#endif // defined (PTHREADS)

#endif // !defined (PTHREADSTHREADSYNC_H)
