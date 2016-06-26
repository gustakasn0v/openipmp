/**
    \defgroup mpeg2drmplayer mpeg2 DRM player documentation.
*/
/**   \file MPEG2IPMPXDecoderTest.cpp

      \ingroup mpeg2drmplayer

      MPEG2 decoder test with IPMPX signalling.

      The Initial Developer of the Original Code is Mutable, Inc. <br>
      Portions created by Mutable, Inc. are <br>
      Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

      
*/

#include "MPEG2IPMPXParser.h"
#include "IPMPToolManager.h"
#include "ThreadSyncFactory.h"
#include <iostream>
#if defined (WIN32)
#include <crtdbg.h>
#endif
#include <sys/stat.h>
#include "DRMLogger.h"

using namespace DRMPlugin;
using namespace MPEG2IPMPXDRMPlugin;

/*! \brief  IPMP terminal.

    Used for user/IPMP tool manager communication.
*/
class IPMPTerminal: public IIPMPTerminal {
public:
  /*! \brief  Constructor.
  */
  IPMPTerminal() {
  }

  virtual ~IPMPTerminal() {
  }

  /*! \brief  User text.

      \param  text          input, text to be presented to the user.
      
      \returns Boolean indicating success or failure.
  */
  virtual bool UserText(const std::string& text) {
    std::cout << text;
    return true;
  }

  /*! \brief  User query/response.

      \param  query         input, user query.
      \param  response      output, user response.
      
      \returns Boolean indicating success or failure.
  */
  virtual bool UserQA(const std::string& query, std::string& response) {
    std::cout << query;
    std::cin >> response;
    return true;
  }
};

/*! \brief  Transport stream parse test.

    \param  stream        input, stream to be parsed.
    \param  logger        input, message logger.

    \returns Boolean indicating success ir failure.
*/
bool TStreamParseTest(ByteSeq& stream, DRMLogger& logger) {
  MPEG2IPMPXTStreamParser tParser(new IPMPToolManager(new IPMPTerminal(), logger), logger);
  return tParser.ParseStream(stream);
}

/*! \brief  Program stream parse test.

    \param  stream        input, stream to be parsed.
    \param  logger        input, message logger.

    \returns Boolean indicating success ir failure.
*/
bool PStreamParseTest(ByteSeq& stream, DRMLogger& logger) {
  MPEG2IPMPXPStreamParser pParser(new IPMPToolManager(new IPMPTerminal(), logger), logger);
  return pParser.ParseStream(stream);
}

/*! \brief  Decoder test.

    First parameter expected is transport stream file name and second
    is program stream file name.
*/
int main(int argc, char* argv[]) {
#if defined (WIN32)
#if defined(_DEBUG)
	int tempflag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
	tempflag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag( tempflag );

  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_WNDW );
  _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_WNDW );
  _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_WNDW );
//  _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
//  _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR );
//  _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR );
#endif // _DEBUG
#endif // WIN32

  DRMLogger logger(ThreadSyncFactory::GetGlobalMutex());

  if (argc < 3) {
    std::cout << "Wrong number of arguments." << std::endl;
    return -1;
  }

  struct stat tstat;
  stat(argv[1], &tstat);
  FILE* in = fopen(argv[1], "rb");
  if (in == NULL) {
    std::cout << "Cannot open transport stream file." << std::endl;
    return -1;
  }
  ByteT* buffer = (ByteT*)malloc(tstat.st_size);
  fread(buffer, tstat.st_size, 1, in);
  fclose(in);

  ByteSeq tstream(buffer, tstat.st_size);
  free(buffer);

  if (TStreamParseTest(tstream, logger) == false) {
    std::cout << "Transport stream parse test failed." << std::endl;
    return -1;
  }

  stat(argv[2], &tstat);
  in = fopen(argv[2], "rb");
  if (in == NULL) {
    std::cout << "Cannot open program stream file." << std::endl;
    return -1;
  }
  buffer = (ByteT*)malloc(tstat.st_size);
  fread(buffer, tstat.st_size, 1, in);
  fclose(in);

  ByteSeq pstream(buffer, tstat.st_size);
  free(buffer);

  if (PStreamParseTest(pstream, logger) == false) {
    std::cout << "Program stream parse test failed." << std::endl;
    return -1;
  }

  std::cout << "Decoder test passed." << std::endl;

  return 0;
}
