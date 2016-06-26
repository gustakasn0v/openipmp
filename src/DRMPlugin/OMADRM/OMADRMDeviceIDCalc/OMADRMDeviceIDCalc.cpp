#include <iostream>
#if defined (WIN32)
#include <crtdbg.h>
#endif
//#include <sys/stat.h>

#include <string>
#include "PublicCryptoFactory.h"
//#include "XMLFactory.h"
//#include "Base64Factory.h"
//#include "ThreadSyncFactory.h"
#include "OMADRMCrypto.h"

using namespace DRMPlugin;

bool GetDeviceID(const std::string& certPath, std::string& devid) {
  DRMLogger logger;

  SPtr<OMAPublicCertificate> cer;
  try {
    cer = new OMAPublicCertificate(PublicCryptoFactory::ParsePublicEncryptorVerifierCertificateFromFile(certPath, logger));
  }
  catch (OMADRMCryptoException) {
    return false;
  }

  Base64StringT id;
  if (cer->GetKeyIdentifier(new OMADRMHasher(PublicCryptoFactory::GetSHA1Hasher(logger)),
      id) == false) {
    return false;
  }

  devid = id.BString();
  return true;
}

int main(int argc, char* argv[]) {
#if defined (_DEBUG) && defined (WIN32)
	int tempflag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
	tempflag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag( tempflag );

//  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
//	_CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
//  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_WNDW );
  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_WNDW );
  _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_WNDW );
//	_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR );
  _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_WNDW );
#endif

  //  Check encode/decode test switch.
  std::string usage = "Usage: OMADRMDeviceIDCalc <device certificate path>\n";

  std::string certPath;
  if (argc < 2) {
    //  No parameters.
    std::cout << usage << std::endl;
    return -1;
  } else {
    //  Device ID test.
    certPath = argv[1];
  }

  std::string id;
  if (GetDeviceID(certPath, id) == false) {
    std::cout << "Device ID calculation failed!" << std::endl;
    return -1;
  }

  //  Output deviceID for use in other projects.
  std::cout << "deviceID: " << id << std::endl;

  return 0;
}
