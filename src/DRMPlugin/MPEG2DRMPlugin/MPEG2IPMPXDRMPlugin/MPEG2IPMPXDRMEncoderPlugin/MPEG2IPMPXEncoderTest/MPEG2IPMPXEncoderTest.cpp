/**
    \defgroup mpeg2drmencoder mpeg2 DRM encoder documentation.
*/
/**   \file MPEG2IPMPXEncoderTest.cpp

      \ingroup mpeg2drmencoder

      Test of MPEG2 DRM encoding with IPMPX signalling.

      The Initial Developer of the Original Code is Mutable, Inc. <br>
      Portions created by Mutable, Inc. are <br>
      Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

      
*/

#include "MPEG2IPMPXEncoder.h"
#include "XMLFactory.h"
#include "ThreadSyncFactory.h"
#include "ICipher.h"

using namespace DRMPlugin;
using namespace MPEG2IPMPXDRMPlugin;

#include <iostream>
#if defined (WIN32)
#include <crtdbg.h>
#endif
#include <sys/stat.h>

/*! \brief  MPEG2IPMPX test encoder usage for DRM encryption.

    DRM options are the following:
      - -W=xmlFileName: set name of the XML configuration file. XML file contains
        necessary information for DRM encryption, which is dependent on the
        ContentInfoManager and DRM encoder manager used. See specific manager
        documentation for correct format of the XML file.

      - -X=xmlPath;value: used to set sensitive information that shouldn't appear
        in the XML configuration file. General format is xmlPath/value, where
        xmlPath stands for tree path in the XML tree (of the XML configuration
        file), and value stands for the value to be set for the node corresponding
        to that path. If path doesn't exist, it will be an error. This option can
        be used multiple times.

      - -Y=drm;enc: set drm method and encryption method (openipmp/bfs, openipmp/ctr).

    Sample XML file for encryption: <a href="../EncoderInfo.xml">EncoderInfo</a>.


    Sample command line for openIPMP encryption:

    <em>mp4creator -E -W=EncoderInfo.xml -X=UserName;danijelk -X=UserPass;ipmp -X=License;danijelk;2005-08-31;2006-08-31;ODRL -Y=openipmp;bfs</em>.

    \retval   0        indicating success
    \retval   !=0      indicating failure.
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

  std::string usageString = 
    " <options>\n"
    "  Options:\n"
    "  -W=xmlFileName           If encrypting, set name of the XML configuration file.\n"
    "  -X=xmlPath;value         If encrypting, used to set sensitive information."
    "  -Y=drm;enc               If encrypting, set drm method and encryption method\n"
    "                           (openipmp/ctr, openipmp/bfs).\n";

  std::string drmMethod = "", encMethod = "", xmlFileName = "";
  std::vector<std::string> sensitive;
  int start = 0, end = 0;

  int opt = 1;
  while (opt < argc) {
    std::string option = argv[opt++];
    if (option.size() < 4) {
      //  Error.
      std::cout << "Invalid option!" << std::endl;
      continue;
    }
    if ((option[0] != '-') || (option[2] != '=')) {
      //  Error.
      std::cout << "Invalid option!" << std::endl;
      continue;
    }
    if (option[1] == 'W') {
      xmlFileName = option.data() + 3;
    } else if (option[1] == 'X') {
      sensitive.push_back(std::string(option.data() + 3));
    } else if (option[1] == 'Y') {
      start = 3;
      end = 3;
      // find ';' delimiter (or end of string)
      while ((option[end] != 0) && (option[end] != ';')) {
        end++;
      }
      if (option[end] == 0) {
        //  Error.
        std::cout << "Invalid -Y option!" << std::endl;
        continue;
      }
      option[end] = '\0';

      drmMethod = option.data() + start;
      encMethod = option.data() + end + 1;
    } else {
      //  Error.
      std::cout << "Invalid option " << option[1] << std::endl;
      continue;
    }
  }

  if (drmMethod == "") {
    std::cout << "Missing drm method!" << std::endl;
    return -1;
  }
  if (encMethod == "") {
    std::cout << "Missing encryption method!" << std::endl;
    return -1;
  }

  EncMethod encryption;
  if (encMethod == "ctr") {
    encryption = AES128CTR;
  } else if (encMethod == "bfs") {
    encryption = BLOWFISH;
  } else {
    std::cout << "Invalid encryption method!" << std::endl;
    return -1;
  }
  
  DRMLogger logger;

  IXMLDocument* xmlDoc = 0;
  IXMLElement* root = 0;

  if (xmlFileName != "") {
    xmlDoc = XMLFactory::DecodeDocumentFromFile(xmlFileName, logger);

    if (xmlDoc == 0) {
      std::cout << "Invalid XML configuration file!" << std::endl;
      return -1;
    }

    root = xmlDoc->GetRootElement();
    if (root == 0) {
      std::cout << "Invalid XML configuration file!" << std::endl;
      delete xmlDoc;
      return -1;
    }

    unsigned int count  = 0;
    for (count = 0; count < sensitive.size(); count++) {
      char* slash = strchr(sensitive[count].data(), ';');
      if (slash == NULL) {
        std::cout << "Invalid sensitive data!" << std::endl;
        delete xmlDoc;
        return -1;
      }
      std::string path = std::string(sensitive[count].begin(), std::string::iterator(slash));
      std::string value = std::string(std::string::iterator(++slash), sensitive[count].end());
      if (root->AddChildElement(path, value) == 0) {
        std::cout << "Invalid XML file!" << std::endl;
        delete xmlDoc;
        return -1;
      }
    }
  }

  FILE* sample = fopen("sample.mpg", "wb");
  //  Put 5*200*1024 data to sample file.
  for (unsigned int i = 0; i < 5; i++) {
    ByteT buffer[200*1024];
    fwrite(buffer, 200*1024, 1, sample);
  }
  fclose(sample);

  MPEG2IPMPXTStreamEncoder tEncoder(logger);

  std::string input = "sample.mpg";
  if (tEncoder.Encode(input, "tstream.mpg", root, encryption) == false) {
    std::cout << "Transport stream encode test failed." << std::endl;
    if (xmlDoc != 0) delete xmlDoc;
    return -1;
  }

  MPEG2IPMPXPStreamEncoder pEncoder(logger);

  input = "sample.mpg";
  if (pEncoder.Encode(input, "pstream.mpg", root, encryption) == false) {
    std::cout << "Program stream encode test failed." << std::endl;
    if (xmlDoc != 0) delete xmlDoc;
    return -1;
  }

  std::cout << "MPEG2 IPMPX DRM encode test passed." << std::endl;

  if (xmlDoc != 0) delete xmlDoc;

  return 0;
}
