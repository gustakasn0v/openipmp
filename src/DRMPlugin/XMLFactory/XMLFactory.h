/**	\file XMLFactory.h

	XML document management using xerces-c library.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (XMLFACTORY_H)
#define XMLFACTORY_H

#include "IXMLDocument.h"
#include "DRMLogger.h"

#if defined (WIN32)
#if defined XMLFACTORY_EXPORTS
#define XMLFACTORY_EXPORT __declspec(dllexport)
#else
#define XMLFACTORY_EXPORT __declspec(dllimport)
#endif // XMLFACTORY_EXPORTS
#elif defined (LINUX)
#define XMLFACTORY_EXPORT
#else
#define XMLFACTORY_EXPORT
#endif

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  XML factory.
*/
class XMLFactory {
public:
  /*! \brief  Create a new XML document with root node with given name.

      \param  name        input, root node name.
      \param  logger      input, message logger.

      \returns  New XML document. If fails, returns 0.
  */
  static XMLFACTORY_EXPORT IXMLDocument* CreateDocument(const std::string& name, DRMLogger& logger);

  /*! \brief  Create a new XML document from encoded XML string.

      \param  xml         input, encoded XML string.
      \param  logger      input, message logger.

      \returns  New XML document. If fails, returns 0.
  */
  static XMLFACTORY_EXPORT IXMLDocument* DecodeDocument(const std::string& xml, DRMLogger& logger);

  /*! \brief  Create a new XML document from file.

      \param  fname       input, file name.
      \param  logger      input, message logger.

      \returns  New XML document. If fails, returns 0.
  */
  static XMLFACTORY_EXPORT IXMLDocument* DecodeDocumentFromFile(const std::string& fname, DRMLogger& logger);
};

} // namespace DRMPlugin

#endif // !defined (XMLFACTORY_H)
