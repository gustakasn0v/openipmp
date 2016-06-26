/**	\file ThreadSyncFactory.h

	Thread and synchronization objects management.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (THREADSYNCFACTORY_H)
#define THREADSYNCFACTORY_H

#include "IThreadSync.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined THREADSYNCFACTORY_EXPORTS
#define THREADSYNCFACTORY_EXPORT __declspec(dllexport)
#else
#define THREADSYNCFACTORY_EXPORT __declspec(dllimport)
#endif // THREADSYNCFACTORY_EXPORTS
#elif defined (LINUX)
#define THREADSYNCFACTORY_EXPORT
#else
#define THREADSYNCFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Thread and synchronization objects manager.
*/
class ThreadSyncFactory {
public:
  /*! \brief  Get new mutex.

      \param  logger    input, message logger.

      \returns  New mutex. If fails, 0.
  */
  static THREADSYNCFACTORY_EXPORT IMutex* GetMutex(DRMLogger& logger);

  /*! \brief  Get new global mutex.

      \returns  New mutex. If fails, 0.
  */
  static THREADSYNCFACTORY_EXPORT IMutex* GetGlobalMutex();

  /*! \brief  Get new event.

      \param  logger    input, message logger.

      \returns  New event. If fails, 0.
  */
  static THREADSYNCFACTORY_EXPORT IEvent* GetEvent(DRMLogger& logger);

  /*! \brief  Get new thread.

      \param  start     thread start function.
      \param  par       thread function parameters.
      \param  logger    input, message logger.

      \returns  New thread. If fails, 0.
  */
  static THREADSYNCFACTORY_EXPORT IThread* GetThread(void (*start)(void*), void* par, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (THREADSYNCFACTORY_H)
