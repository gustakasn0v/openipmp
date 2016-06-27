/**	\file DRMLogger.h

  Logger is used to record logs.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (DRMLOGGER_H)
#define DRMLOGGER_H

#include <string>
#include <iostream>
#include "IThreadSync.h"
#include <stdio.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief Records logs.

    Saves logs to a local string. On destruction writes the saved log to a file.
*/
class DRMLogger {
public:
  /*! \brief  Constructor.

      \param		mtex		log mutex.

      If log mutex != 0, then logging is thread safe. Otherwise it's not.
  */
  DRMLogger(IMutex* mtex = 0): drmLog(), logMutex(mtex) {
  }

  /*! \brief  Destructor.
  
      Writes the saved log to a file.
  */
  virtual ~DRMLogger() {
    if (logMutex != 0) {
      if (logMutex->Lock() == false) return;
    }
    FILE* logfile = fopen("drmplugin.log", "wt");
    if (logfile != NULL) {
      fprintf(logfile, "%s\n", drmLog.data());
      fclose(logfile);
    }
    if (logMutex != 0) {
      logMutex->Release();
      delete logMutex; logMutex = 0;
    }
  }

  /*! \brief  Reset log to an empty string.
  */
  virtual void ResetLog() {
    if (logMutex != 0) {
      if (logMutex->Lock() == false) return;
    }
    drmLog = std::string();
    if (logMutex != 0) {
      logMutex->Release();
    }
  }

  /*! \brief  Add a message to the log.
  */
  virtual void UpdateLog(const std::string& message) {
    if (logMutex != 0) {
      if (logMutex->Lock() == false) return;
    }
    drmLog += (message + "\n");
    if (logMutex != 0) {
      logMutex->Release();
    }
  }

  /*! \brief  Get log.
  */
  virtual std::string GetLog() {
    if (logMutex != 0) {
      if (logMutex->Lock() == false) return "";
    }
    std::string ret = drmLog;
    if (logMutex != 0) {
      logMutex->Release();
    }
    return ret;
  }

protected:
  std::string drmLog;
  IMutex* logMutex;
};

/*! \brief Records logs.

    Saves logs to a local string and writes to standard output. On destruction
    writes the saved log to a file.
*/
class StdOutDRMLogger: public DRMLogger {
public:
  /*! \brief  Constructor.

      \param		mtex		log mutex.

      If log mutex != 0, then logging is thread safe. Otherwise it's not.
  */
  StdOutDRMLogger(IMutex* mtex = 0): DRMLogger(mtex) {
  }

  /*! \brief  Destructor.
  
      Writes the saved log to a file.
  */
  virtual ~StdOutDRMLogger() {
  }

  /*! \brief  Add a message to the log.
  */
  virtual void UpdateLog(const std::string& message) {
    if (logMutex != 0) {
      if (logMutex->Lock() == false) return;
    }
    std::cout << message << std::endl;
    drmLog += (message + "\n");
    if (logMutex != 0) {
      logMutex->Release();
    }
  }
};

} // namespace DRMPlugin

#endif // !defined (DRMLOGGER_H)
