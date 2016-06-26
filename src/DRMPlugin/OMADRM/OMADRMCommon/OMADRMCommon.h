/** \file OMADRMCommon.h

    OMA DRM common tools.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#if !defined (OMADRMCOMMON_H)
#define OMADRMCOMMON_H

#include "ROAPMessages.h"
#include <string>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for OMA DRM protocol exception.
*/
//class ProtocolException {
//};

/*! \brief  Timer. Retrieves time.
*/
class OMADRMTimer: public GC {
public:
  /*! \brief  Get current time.

      \returns  Current time.
  */
  virtual NZSPtr<DateTime> GetTime() = 0;
};

/*! \brief  Definite timer. Retrieves definite time.
*/
class OMADRMDefTimer: public GC {
public:
  /*! \brief  Get current (definite) time.

      \returns  Current (definite) time.
  */
  virtual NZSPtr<DefDateTime> GetTime() = 0;
};

/*! \brief  Session identifier creator.
*/
class OMADRMSessionIDCreator: public GC {
public:
  /*! \brief  Create new session identifier, using previous one.

      \returns  Session identifier.
  */
  virtual NZSPtr<ROAPSessionID> CreateSessionID(const SPtr<ROAPSessionID>& prevSessID) = 0;
};

/*! \brief  Timer using OS provided timing. Retrieves time.
*/
class OSTimer: public OMADRMTimer {
public:
  /*! \brief  Get current time.

      \returns  Current time.
  */
  virtual NZSPtr<DateTime> GetTime();
};

/*! \brief  Definite timer using OS provided timing. Retrieves definite time.
*/
class OSDefTimer: public OMADRMDefTimer {
public:
  /*! \brief  Get current (definite) time.

      \returns  Current (definite) time.
  */
  virtual NZSPtr<DefDateTime> GetTime();
};

/*! \brief  Dummy session identifier creator.
*/
class DummySessionIDCreator: public OMADRMSessionIDCreator {
public:
  /*! \brief  Create new session identifier, using previous one.

      \returns  Session identifier.
  */
  virtual NZSPtr<ROAPSessionID> CreateSessionID(const SPtr<ROAPSessionID>& prevSessID);
};

} // namespace DRMPlugin

#endif // !defined (OMADRMCOMMON_H)
