/**	\file PThreadsThreadSync.cpp

  Thread and synchronization objects implementations using pthreads.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "PThreadsThreadSync.h"

#if defined (PTHREADS)

#include <sys/time.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Mutex implementation using pthreads.
*/
/*! \brief  Constructor.

    Creates mutex without security attributes, without initial
    ownership and without name.

    If fails, throws ThreadSyncException.
*/
PThreadsGlobalMutex::PThreadsGlobalMutex(): id() {
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	if (pthread_mutex_init(&id, &attr) != 0) {
    throw ThreadSyncException();
	}
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
PThreadsGlobalMutex::~PThreadsGlobalMutex() {
  if (pthread_mutex_destroy(&id) < 0) {
    throw ThreadSyncException();
  }
}

/*! \brief  Obtain mutex lock. Waits for finite time.

    \param  timeout     input, wait timeout.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsGlobalMutex::Lock(unsigned int timeout) {
  //  TODO: see how to set timeout.
  return Lock();
}

/*! \brief  Obtain mutex lock. Waits infinitely.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsGlobalMutex::Lock() {
  if (pthread_mutex_lock(&id) < 0) {
    return false;
  }
  return true;
}

/*! \brief  Release mutex lock.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsGlobalMutex::Release() {
  if (pthread_mutex_unlock(&id) < 0) {
    return false;
  }
  return true;
}

/*! \brief  Mutex implementation using pthreads.
*/
/*! \brief  Constructor.

    Creates mutex without security attributes, without initial
    ownership and without name.

    \param  logger      message logger.

    If fails, throws ThreadSyncException.
*/
PThreadsMutex::PThreadsMutex(DRMLogger& logger): id(), mutexLogger(logger) {
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	if (pthread_mutex_init(&id, &attr) != 0) {
    mutexLogger.UpdateLog("PThreadsMutex::ctor: cannot initialize...");
    throw ThreadSyncException();
	}
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
PThreadsMutex::~PThreadsMutex() {
  if (pthread_mutex_destroy(&id) < 0) {
    mutexLogger.UpdateLog("PThreadsMutex::dtor: cannot destroy mutex...");
    throw ThreadSyncException();
  }
}

/*! \brief  Obtain mutex lock. Waits for finite time.

    \param  timeout     input, wait timeout.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsMutex::Lock(unsigned int timeout) {
  //  TODO: see how to set timeout.
  return Lock();
}

/*! \brief  Obtain mutex lock. Waits infinitely.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsMutex::Lock() {
  if (pthread_mutex_lock(&id) < 0) {
//    mutexLogger.UpdateLog("PThreadsMutex::Lock: cannot lock...");
    return false;
  }
  return true;
}

/*! \brief  Release mutex lock.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsMutex::Release() {
  if (pthread_mutex_unlock(&id) < 0) {
    mutexLogger.UpdateLog("PThreadsMutex::Release: cannot release...");
    return false;
  }
  return true;
}

/*! \brief  Event implementation using pthreads.

    Event is manually resetable.
*/
/*! \brief  Constructor.

    Creates event without security attributes, manually resetable,
    initially unsignaled and without name.

    \param  logger      message logger.

    If fails, throws ThreadSyncException.
*/
PThreadsEvent::PThreadsEvent(DRMLogger& logger): mtex(), cond(), signaled(false), eventLogger(logger) {
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  if (pthread_mutex_init(&mtex, &attr) != 0) {
    eventLogger.UpdateLog("PThreadsEvent::ctor: cannot initialize...");
    throw ThreadSyncException();
  }
  pthread_condattr_t cattr;
  pthread_condattr_init(&cattr);
  if (pthread_cond_init(&cond, &cattr) != 0) {
    eventLogger.UpdateLog("PThreadsEvent::ctor: cannot initialize...");
    throw ThreadSyncException();
  }
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
PThreadsEvent::~PThreadsEvent() {
  if (pthread_mutex_destroy(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::ctor: cannot destroy mutex...");
    throw ThreadSyncException();
  }
  if (pthread_cond_destroy(&cond) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::ctor: cannot destroy condition variable...");
    throw ThreadSyncException();
  }
}

/*! \brief  Wait till event becomes signaled. Waits for finite time.

    \param  timeout     input, wait timeout.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsEvent::Wait(unsigned int timeout) {
  if (pthread_mutex_lock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Wait: cannot lock mutex...");
    return false;
  }
  if (signaled == true) {
    return (pthread_mutex_unlock(&mtex) >= 0);
  }
  struct timeval now;
  struct timezone zone;
  struct timespec tout;
  gettimeofday(&now, &zone);
  tout.tv_sec = now.tv_sec + (timeout/1000);
  tout.tv_nsec = (now.tv_usec + (timeout%1000)*1000)*1000;
  if (pthread_cond_timedwait(&cond, &mtex, &tout) != 0) {
//    eventLogger.UpdateLog("PThreadsEvent::Wait: wait failed...");
    pthread_mutex_unlock(&mtex);
    return false;
  }
  if (pthread_mutex_unlock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Wait: cannot unlock mutex...");
    return false;
  }
  return true;
}

/*! \brief  Wait till event becomes signaled. Waits infinitely.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsEvent::Wait() {
  if (pthread_mutex_lock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Wait: cannot lock mutex...");
    return false;
  }
  if (signaled == true) {
    return (pthread_mutex_unlock(&mtex) >= 0);
  }
  if (pthread_cond_wait(&cond, &mtex) != 0) {
//    eventLogger.UpdateLog("PThreadsEvent::Wait: wait failed...");
    pthread_mutex_unlock(&mtex);
    return false;
  }
  if (pthread_mutex_unlock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Wait: cannot unlock mutex...");
    return false;
  }
  return true;
}

/*! \brief  Set event to signaled.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsEvent::Set() {
  if (pthread_mutex_lock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Set: cannot lock mutex...");
    return false;
  }
  signaled = true;
  if (pthread_mutex_unlock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Set: cannot unlock mutex...");
    return false;
  }
  if (pthread_cond_broadcast(&cond) != 0) {
    eventLogger.UpdateLog("PThreadsEvent::Set: broadcast failed...");
    return false;
  }
  return true;
}

/*! \brief  Set event to unsignaled.

    \returns  Boolean indicating success or failure.
*/
bool PThreadsEvent::Unset() {
  if (pthread_mutex_lock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Unset: cannot lock mutex...");
    return false;
  }
  signaled = false;
  if (pthread_mutex_unlock(&mtex) < 0) {
    eventLogger.UpdateLog("PThreadsEvent::Unset: cannot unlock mutex...");
    return false;
  }
  return true;
}

//  Patch for pthreads. Start routine must return void*, instead of void.
struct PThreadParams {
  void (*start)(void*);
  void* par;
};

static void* PThreadRun(void* par) {
  PThreadParams* str = (PThreadParams*)par;
  void (*tstart)(void*) = str->start;
  void* tpar = str->par;
  tstart(tpar);
  delete str;
  pthread_exit(0);
  return 0;
}

/*! \brief  Thread implementation using pthreads.

    Threads are run when they are created.
*/
/*! \brief  Constructor.

    Creates thread without security attributes, with default stack size
    and immediately runs it.

    \param  start     thread start function.
    \param  par       thread function parameters.
    \param  logger    message logger.

    If fails, throws ThreadSyncException.
*/
PThreadsThread::PThreadsThread(void (*start)(void*), void* par, DRMLogger& logger): handle() {
  pthread_attr_t type;
  if (pthread_attr_init(&type) != 0) {
    logger.UpdateLog("PThreadsThread::ctor: cannot initialize...");
    throw ThreadSyncException();
  }
  PThreadParams* pars = new PThreadParams();
  pars->start = start;
  pars->par = par;
  if (pthread_create(&handle, &type, PThreadRun, pars) != 0) {
    logger.UpdateLog("PThreadsThread::ctor: cannot create thread...");
    delete pars;
    throw ThreadSyncException();
  }
}

/*! \brief  Destructor.

    If fails throws ThreadSyncException.
*/
PThreadsThread::~PThreadsThread() {
}

} // namespace DRMPlugin

#endif // defined (PTHREADS)
