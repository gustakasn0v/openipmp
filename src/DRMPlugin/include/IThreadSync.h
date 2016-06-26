/**	\file IThreadSync.h

  Thread and synchronization objects' interfaces.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (ITHREADSYNC_H)
#define ITHREADSYNC_H

#include <vector>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for thread and synchronization objects' error.
*/
class ThreadSyncException {
};

/*! \brief  Mutex interface.
*/
class IMutex {
public:
  /*! \brief  Destructor.

      In derived classes, if fails throws ThreadSyncException.
  */
  virtual ~IMutex() {
  }

  /*! \brief  Obtain mutex lock. Waits for finite time.

      \param  timeout     input, wait timeout.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Lock(unsigned int timeout) = 0;

  /*! \brief  Obtain mutex lock. Waits infinitely.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Lock() = 0;

  /*! \brief  Release mutex lock.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Release() = 0;
};

/*! \brief  Event interface.

    Event is manually resetable.
*/
class IEvent {
public:
  /*! \brief  Destructor.

      In derived classes, if fails throws ThreadSyncException.
  */
  virtual ~IEvent() {
  }

  /*! \brief  Wait till event becomes signaled. Waits for finite time.

      \param  timeout     input, wait timeout.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Wait(unsigned int timeout) = 0;

  /*! \brief  Wait till event becomes signaled. Waits infinitely.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Wait() = 0;

  /*! \brief  Set event to signaled.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Set() = 0;

  /*! \brief  Set event to unsignaled.

      \returns  Boolean indicating success or failure.
  */
  virtual bool Unset() = 0;
};

/*! \brief  Wait till all events become signaled. Waits infinitely.

    \param  events        input, events to wait for.

    \returns  Boolean indicating success or failure.
*/
static bool WaitForEvents(const std::vector<IEvent*>& events) {
  for (unsigned int i = 0; i < events.size(); i++) {
    if (events[i]->Wait() == false) {
      return false;
    }
  }
  return true;
}

/*! \brief  Thread interface.

    Threads are run when they are created.
*/
class IThread {
public:
  /*! \brief  Destructor.

      In derived classes, if fails throws ThreadSyncException.
  */
  virtual ~IThread() {
  }
};

} // namespace DRMPlugin

#endif // !defined (ITHREADSYNC_H)
