/**	\file XMLFactory.cpp

	XML document management using xerces-c library.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "XMLFactory.h"
#include "XMLDocument.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/dom/deprecated/DOM_Document.hpp>
#include <xercesc/dom/deprecated/DOMParser.hpp>

XERCES_CPP_NAMESPACE_USE

#include <iostream>
#include <sys/stat.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*!  \brief  Class used for handling globals.
*/
class XMLGlobalHandler {
public:
  /*!  \brief  Constructor.
  */
  XMLGlobalHandler() {
    XMLPlatformUtils::Initialize();
  }

  /*!  \brief  Destructor.
  */
  ~XMLGlobalHandler() {
    XMLPlatformUtils::Terminate();
  }
};

static XMLGlobalHandler xmlGlobalHandler;

/*! \brief  XML factory.
*/
/*! \brief  Create a new XML document with root node with given name.

    \param  name        input, root node name.
    \param  logger      input, message logger.

    \returns  New XML document. If fails, returns 0.
*/
IXMLDocument* XMLFactory::CreateDocument(const std::string& name, DRMLogger& logger) {
  try {
    return new XMLDocument("<" + name + "></" + name + ">", logger);
  }
  catch (...) {
    logger.UpdateLog("XMLFactory::CreateDocument: unknown exception...");
    return 0;
  }
}

/*! \brief  Create a new XML document from encoded XML string.

    \param  xml         input, encoded XML string.
    \param  logger      input, message logger.

    \returns  New XML document. If fails, returns 0.
*/
IXMLDocument* XMLFactory::DecodeDocument(const std::string& xml, DRMLogger& logger) {
  try {
    return new XMLDocument(xml, logger);
  }
  catch (...) {
    logger.UpdateLog("XMLFactory::DecodeDocument: unknown exception...");
    return 0;
  }
}

/*! \brief  Create a new XML document from file.

    \param  fname       input, file name.
    \param  logger      input, message logger.

    \returns  New XML document. If fails, returns 0.
*/
IXMLDocument* XMLFactory::DecodeDocumentFromFile(const std::string& fname, DRMLogger& logger) {
  FILE* fp = fopen(fname.data(), "rb");
  if (fp == NULL) {
    logger.UpdateLog("XMLFactory::DecodeDocumentFromFile: cannot open " + fname + "...");
    return 0;
  }
  struct stat tstat;
  stat(fname.data(), &tstat);
  char* xmlText = (char*)malloc(tstat.st_size + 1);
  fread(xmlText, tstat.st_size, 1, fp);
	xmlText[tstat.st_size] = '\0';
  fclose(fp);
  std::string xml = xmlText;
  free(xmlText);
  return DecodeDocument(xml, logger);
}

} // namespace DRMPlugin
