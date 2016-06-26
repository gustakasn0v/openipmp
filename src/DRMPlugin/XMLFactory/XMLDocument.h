/**	\file XMLDocument.h

	XML document implementation using xerces-c library.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (XMLDOCUMENT_H)
#define XMLDOCUMENT_H

#include "IXMLDocument.h"
#include "BasicTypes.h"
#include "DRMLogger.h"
#include <string>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/dom/deprecated/DOM_Document.hpp>
#include <xercesc/dom/deprecated/DOMParser.hpp>

XERCES_CPP_NAMESPACE_USE

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  XML attribute implementation using xerces-c library.
*/
class XMLAttribute: public IXMLAttribute {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.
  */
  XMLAttribute(DRMLogger& logger);

  /*! \brief  Constructor.

      \param  att     DOM attribute.
      \param  logger  message logger.

      If fails, throws XMLException.
  */
  XMLAttribute(DOM_Attr att, DRMLogger& logger);

  virtual ~XMLAttribute();

  /*! \brief  Set attribute value from string.

      \param  val       input, attribute value.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStrValue(const std::string& val);

  /*! \brief  Get attribute name.

      \returns  Atrribute name.
  */
  virtual std::string GetName();

  /*! \brief  Get attribute value as string.

      \returns  Attribute value.
  */
  virtual std::string GetStrValue();

private:
  //  DOM attribute.
  DOM_Attr domAttr;
  DRMLogger& attLogger;
};

/*! \brief  XML element implementation using xerces-c library.
*/
class XMLElement: public IXMLElement {
public:
  /*! \brief  Constructor.

      \param  logger      message logger.
  */
  XMLElement(DRMLogger& logger);

  /*! \brief  Constructor.

      \param  elem      DOM element.
      \param  logger    message logger.

      If fails, throws XMLException.
  */
  XMLElement(DOM_Element elem, DRMLogger& logger);

  virtual ~XMLElement();

  /*! \brief  Set element value from string.

      \param  val       input, attribute value.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStrValue(const std::string& val);

  /*! \brief  Add attribute with given name and value.

      \param  name      input, attribute name.
      \param  val       input, attribute value.

      \returns  Child element with given name. If zero, failed.
  */
  virtual IXMLAttribute* AddAttribute(const std::string& name, const
    std::string& val);

  /*! \brief  Add child element with given path.

      Path elements' names must be divided by a dot (".").

      \param  path      input, child element path.

      \returns  Child element with given path. If zero, failed.
  */
  virtual IXMLElement* AddChildElement(const std::string& path);

  /*! \brief  Get element name.

      \returns  Element name.
  */
  virtual std::string GetName();

  /*! \brief  Get element value as string.

      \returns  Element value. If fails, throws XMLException.
  */
  virtual std::string GetStrValue();

  /*! \brief  Get all attributes with given name.

      \param  name      input, attribute name.

      \returns  Attributes with given name.
  */
  virtual std::vector<IXMLAttribute*> GetAttributes(const std::string& name);

  /*! \brief  Get first child element.

      \returns  First child element.
  */
  virtual IXMLElement* GetFirstChild();

  /*! \brief  Get first sibling element.

      \returns  First sibling element.
  */
  virtual IXMLElement* GetFirstSibling();

  /*! \brief  Get all child elements.

      \returns  Child elements.
  */
  virtual std::vector<IXMLElement*> GetAllChildElements();

  /*! \brief  Get child element with given path.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns this element.

      \param  path      input, child element path.

      \returns  Child element with given path. If zero, failed.
  */
  virtual IXMLElement* GetChildElement(const std::string& path);

  /*! \brief  Encode as string.

      \returns  Encoded string.
  */
  virtual std::string Encode();

protected:
  /*! \brief  Get node containing (string) value.

      \returns  Node containing (string) value. If fails, throws XMLException.
  */
  DOM_Node GetValueNode();

private:
  //  DOM element.
  DOM_Element domElem;
  //  Contained attributes.
  std::vector<IXMLAttribute*> attributes;
  //  Contained elements.
  std::vector<IXMLElement*> elements;
  //  First sibling DOM element.
  IXMLElement* sibling;
  DRMLogger& elemLogger;
};

/*! \brief  XML document implementation using xerces-c library.
*/
class XMLDocument: public IXMLDocument {
public:
  /*! \brief  Constructor.

      \param  xml       encoded xml string.
      \param  logger    message logger.

      If fails, throws XMLException.
  */
  XMLDocument(const std::string& xml, DRMLogger& logger);

  virtual ~XMLDocument();

  /*! \brief  Get root element.

      \returns  Root element. If zero, failed.
  */
  virtual IXMLElement* GetRootElement();

  /*! \brief  Encode as string.

      \returns  Encoded string.
  */
  virtual std::string Encode();

private:
  IXMLElement* root;
  DOMParser* parser;
  DOM_Document doc;
  DRMLogger& docLogger;
};

} // namespace DRMPlugin

#endif // !defined (IXMLDOCUMENT_H)
