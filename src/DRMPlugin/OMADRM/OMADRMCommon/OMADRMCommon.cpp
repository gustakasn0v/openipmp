/** \file OMADRMCommon.cpp

    OMA DRM common tools.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "OMADRMCommon.h"

#include <time.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Get current time.

    \returns  Current time.
*/
NZSPtr<DateTime> OSTimer::GetTime() {
  time_t ltime;
  struct tm *gmt;
  tzset();
  time(&ltime);
  gmt = localtime(&ltime);
  char tmpbuf[128];
  strftime(tmpbuf, 128, "%Y-%m-%dT%H:%M:%SZ", gmt);
  return new DefDateTime(UTCTime(tmpbuf));
}

/*! \brief  Get current (definite) time.

    \returns  Current (definite) time.
*/
NZSPtr<DefDateTime> OSDefTimer::GetTime() {
  time_t ltime;
  struct tm *gmt;
  tzset();
  time(&ltime);
  gmt = localtime(&ltime);
  char tmpbuf[128];
  strftime(tmpbuf, 128, "%Y-%m-%dT%H:%M:%SZ", gmt);
  return new DefDateTime(UTCTime(tmpbuf));
}

/*! \brief  Create new session identifier, using previous one.

    \returns  Session identifier.
*/
NZSPtr<ROAPSessionID> DummySessionIDCreator::CreateSessionID(const SPtr<ROAPSessionID>& prevSessID) {
  if (prevSessID != 0) {
    return new ROAPSessionID(prevSessID->Get() + "a");
  } else {
    return new ROAPSessionID("a");
  }
}

} // namespace DRMPlugin
