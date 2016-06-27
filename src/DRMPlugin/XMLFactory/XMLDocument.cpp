/**	\file XMLDocument.cpp

	XML document implementation using xerces-c library.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "XMLDocument.h"

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
/*! \brief  Constructor.

    \param  logger    message logger.
*/
XMLAttribute::XMLAttribute(DRMLogger& logger): domAttr(DOM_Attr()), attLogger(logger) {
}

/*! \brief  Constructor.

    \param  att     DOM attribute.
    \param  logger  message logger.

    If fails, throws XMLException.
*/
XMLAttribute::XMLAttribute(DOM_Attr att, DRMLogger& logger): domAttr(att), attLogger(logger) {
  if (domAttr == NULL) {
    domAttr = DOM_Attr();
  }
}

XMLAttribute::~XMLAttribute() {
}

/*! \brief  Set attribute value from string.

    \param  val       input, attribute value.

    \returns  Boolean indicating success or failure.
*/
bool XMLAttribute::SetStrValue(const std::string& val) {
  domAttr.setValue(DOMString(val.data()));
  return true;
}

/*! \brief  Get attribute name.

    \returns  Atrribute name.
*/
std::string XMLAttribute::GetName() {
  char* name = domAttr.getNodeName().transcode();
  std::string ret(name);
  delete[] name;
  return ret;
}

/*! \brief  Get attribute value as string.

    \returns  Attribute value.
*/
std::string XMLAttribute::GetStrValue() {
  char* val = domAttr.getNodeValue().transcode();
  std::string ret(val);
  delete[] val;
  return ret;
}

/*! \brief  XML element implementation using xerces-c library.
*/
/*! \brief  Constructor.

    \param  logger      message logger.
*/
XMLElement::XMLElement(DRMLogger& logger): domElem(DOM_Element()), attributes(), elements(), sibling(0), elemLogger(logger) {
}

/*! \brief  Constructor.

    \param  elem      DOM element.
    \param  logger    message logger.

    If fails, throws XMLException.
*/
XMLElement::XMLElement(DOM_Element elem, DRMLogger& logger): domElem(elem), attributes(), elements(), elemLogger(logger) {
  if (domElem == NULL) {
    domElem = DOM_Element();
  }
  //  First set up attributes.
  DOM_NamedNodeMap attrs = domElem.getAttributes();
  if (attrs != NULL) {
    unsigned int attrnum = attrs.getLength();
    for (unsigned int i = 0; i < attrnum; i++) {
      DOM_Node attr = attrs.item(i);
      DOM_Attr att(*((DOM_Attr*)(DOM_Node*)(&attr)));
      attributes.push_back(new XMLAttribute(att, elemLogger));
    }
  }
  DOM_Node child = domElem.getFirstChild();
  while (child != NULL) {
    if (child.getNodeType() == DOM_Node::ELEMENT_NODE) {
      DOM_Element el(*((DOM_Element*)(DOM_Node*)(&child)));
      elements.push_back(new XMLElement(el, elemLogger));
    }
	  child = child.getNextSibling();
  }
  DOM_Node sib = domElem.getNextSibling();
  if (sib != NULL) {
    if (sib.getNodeType() == DOM_Node::ELEMENT_NODE) {
      DOM_Element el(*((DOM_Element*)(DOM_Node*)(&sib)));
      sibling = new XMLElement(el, elemLogger);
    } else {
      sibling = 0;
    }
  } else {
    sibling = 0;
  }
}

XMLElement::~XMLElement() {
  unsigned int i = 0;
  for (i = 0; i < attributes.size(); i++) {
    delete attributes[i];
  }
  for (i = 0; i < elements.size(); i++) {
    delete elements[i];
  }
  if (sibling != 0) delete sibling; sibling = 0;
}

/*! \brief  Set element value from string.

    \param  val       input, attribute value.

    \returns  Boolean indicating success or failure.
*/
bool XMLElement::SetStrValue(const std::string& val) {
  DOM_Document doc = domElem.getOwnerDocument();
  unsigned int i = 0;
  char reservedChars[] = "<>&'\"";
  const char* str = val.data();
	for (i = 0; i < strlen(str); i++) {
		if (strchr(reservedChars, str[i]) != NULL) {
			break;
		}
	}
  if (i != strlen(str)) {
    elemLogger.UpdateLog(GetName() + "::SetStrValue: value " + val + " contains unallowed characters...");
    return false;
  }
	DOM_Node child;
  try {
  	child = GetValueNode();
    child.setNodeValue(DOMString(val.data()));
  }
  catch (XMLException) {
    DOM_Text value = doc.createTextNode(DOMString(val.data()));
    domElem.appendChild(value);
  }

  return true;
}

/*! \brief  Add attribute with given name and value.

    \param  name      input, attribute name.
    \param  val       input, attribute value.

    \returns  Child element with given name. If zero, failed.
*/
IXMLAttribute* XMLElement::AddAttribute(const std::string& name, const
    std::string& val) {
  DOM_Document doc = domElem.getOwnerDocument();
  DOM_Attr newatt = doc.createAttribute(DOMString(name.data()));
  newatt.setValue(DOMString(val.data()));
  try {
    IXMLAttribute* attr = new XMLAttribute(newatt, elemLogger);
    domElem.setAttributeNode(newatt);
    attributes.push_back(attr);
    return attr;
  }
  catch (XMLException) {
    return 0;
  }
}

/*! \brief  Add child element with given path.

    Path elements' names must be divided by a dot (".").

    \param  path      input, child element path.

    \returns  Child element with given path. If zero, failed.
*/
IXMLElement* XMLElement::AddChildElement(const std::string& path) {
  char* dot = const_cast<char*>(strchr(path.data(), '.'));
  if (dot != NULL) {
    IXMLElement* elem = AddChildElement(std::string(path.begin(), std::string::const_iterator(dot)));
    if (elem == 0) {
      elemLogger.UpdateLog(GetName() + "::AddChildElement: cannot add node with path " + path + "...");
      return 0;
    }
    return elem->AddChildElement(std::string(std::string::const_iterator(++dot), path.end()));
  }
  DOM_Document doc = domElem.getOwnerDocument();
  DOM_Element newelem = doc.createElement(DOMString(path.data()));
  try {
    IXMLElement* elem = new XMLElement(newelem, elemLogger);
    domElem.appendChild(newelem);
    elements.push_back(elem);
    return elem;
  }
  catch (XMLException) {
    return 0;
  }
}

/*! \brief  Get element name.

    \returns  Element name.
*/
std::string XMLElement::GetName() {
  char* name = domElem.getNodeName().transcode();
  std::string ret(name);
  delete[] name;
  return ret;
}

/*! \brief  Get element value as string.

    \returns  Element value. If fails, throws XMLException.
*/
std::string XMLElement::GetStrValue() {
  DOM_Node child = GetValueNode();
  char* val = child.getNodeValue().transcode();
  std::string ret(val);
  delete[] val;
  return ret;
}

/*! \brief  Get node containing (string) value.

    \returns  Node containing (string) value. If fails, throws XMLException.
*/
DOM_Node XMLElement::GetValueNode() {
  DOM_Node child = domElem.getFirstChild();
  if (child == NULL) {
//    elemLogger.UpdateLog(GetName() + ": not a string node...");
    throw XMLException();
  }
  DOM_Node sib  = child.getNextSibling();
  if (sib != NULL) {
//    elemLogger.UpdateLog(GetName() + ": not a string node...");
    throw XMLException();
  }
  if (child.getNodeType() != DOM_Node::TEXT_NODE) {
//    elemLogger.UpdateLog(GetName() + ": not a string node...");
    throw XMLException();
  }
  return child;
}

/*! \brief  Get all attributes with given name.

    \param  name      input, attribute name.

    \returns  Attributes with given name.
*/
std::vector<IXMLAttribute*> XMLElement::GetAttributes(const std::string& name) {
  std::vector<IXMLAttribute*> ret;
  for (unsigned int i = 0; i < attributes.size(); i++) {
    if (attributes[i]->GetName() == name) {
      ret.push_back(attributes[i]);
    }
  }
  return ret;
}

/*! \brief  Get first child element.

    \returns  First child element.
*/
IXMLElement* XMLElement::GetFirstChild() {
  //  Check this.
  if (elements.size() > 0) {
    return elements[0];
  }
  return 0;
}

/*! \brief  Get first sibling element.

    \returns  First sibling element.
*/
IXMLElement* XMLElement::GetFirstSibling() {
  return sibling;
}

/*! \brief  Get all child elements.

    \returns  Child elements.
*/
std::vector<IXMLElement*> XMLElement::GetAllChildElements() {
  return elements;
}

/*! \brief  Get child element with given path.

    Path elements' names must be divided by a dot (".").
    If path is an empty string (""), returns this element.

    \param  path      input, child element path.

    \returns  Child element with given path. If zero, failed.
*/
IXMLElement* XMLElement::GetChildElement(const std::string& path) {
  if (path == "") {
    return this;
  }
  char* dot = const_cast<char*>(strchr(path.data(), '.'));
  if (dot != NULL) {
    std::vector<IXMLElement*> elems = GetChildElementsByName(std::string(path.begin(), std::string::const_iterator(dot)));
    if ((elems.size() == 0) || (elems.size() > 1)) {
//      elemLogger.UpdateLog(GetName() + "::GetChildElement: none or multiple nodes with path " + path + "...");
      return 0;
    }
    return elems[0]->GetChildElement(std::string(std::string::const_iterator(++dot), path.end()));
  }
  std::vector<IXMLElement*> elems = GetChildElementsByName(path);
  if ((elems.size() == 0) || (elems.size() > 1)) {
//    elemLogger.UpdateLog(GetName() + "::GetChildElement: none or multiple nodes with path " + path + "...");
    return 0;
  }
  return elems[0];
}

/*! \brief  Encode as string.

    \returns  Encoded string.
*/
std::string XMLElement::Encode() {
  unsigned int i = 0;
  std::string ret = "<" + GetName();
  //  Encode attributes.
  for (i = 0; i < attributes.size(); i++) {
    ret += " " + attributes[i]->Encode();
  }
  ret += ">";
  //  Encode elements.
  for (i = 0; i < elements.size(); i++) {
    ret += elements[i]->Encode();
  }
  //  Encode children that are not elements.
  DOM_Node child = domElem.getFirstChild();
  while (child != NULL) {
    if (child.getNodeType() != DOM_Node::ELEMENT_NODE) {
      char reservedChars[] = "<>&'\"";
      char* str = 0;
	    switch (child.getNodeType()) {
		    case DOM_Node::TEXT_NODE:
		    case DOM_Node::CDATA_SECTION_NODE:
			    str = child.getNodeValue().transcode();
			    for (i = 0; i < strlen(str); i++) {
				    if (strchr(reservedChars, str[i]) != NULL) {
					    break;
				    }
			    }
          if (i == strlen(str)) {
            ret += std::string(str);
          } else {
            ret += std::string("<![CDATA[") + std::string(str) + std::string("]]>");
          }
          delete[] str;
          break;
		    default:
          //  Error?
          break;
	    }
    }
	  child = child.getNextSibling();
  }

  ret += "</" + GetName() + ">";
  return ret;
}

/*! \brief  XML document implementation using xerces-c library.
*/
/*! \brief  Constructor.

    \param  xml       encoded xml string.
    \param  logger    message logger.

    If fails, throws XMLException.
*/
XMLDocument::XMLDocument(const std::string& xml, DRMLogger& logger): root(0), parser(0), doc(), docLogger(logger) {
  try {
    MemBufInputSource byteInput((const XMLByte* const)xml.data(),
      (const unsigned int)xml.size(), (char* const)"xmldocument");
    parser = new DOMParser();
    parser->parse(byteInput);
    doc = parser->getDocument();
    DOM_Element elem = doc.getDocumentElement();
    root = new XMLElement(elem, docLogger);
  }
  catch (...) {
    docLogger.UpdateLog("XMLDocument::ctor: xerces error...");
    if (parser != 0) delete parser;
    throw XMLException();
  }
}

XMLDocument::~XMLDocument() {
  if (root != 0) delete root;
  if (parser != 0) delete parser;
}

/*! \brief  Get root element.

    \returns  Root element. If zero, failed.
*/
IXMLElement* XMLDocument::GetRootElement() {
  return root;
}

/*! \brief  Encode as string.

    \returns  Encoded string.
*/
std::string XMLDocument::Encode() {
  return root->Encode();
}

} // namespace DRMPlugin
