/**	\file IXMLDocument.h

	Interfaces for XML document.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#if !defined (IXMLDOCUMENT_H)
#define IXMLDOCUMENT_H

#include <string>
#include <vector>
#include "BasicTypes.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Exception used for XML error.
*/
class XMLException {
};

/*! \brief  XML attribute.
*/
class IXMLAttribute {
public:
  virtual ~IXMLAttribute() {
  }

  /*! \brief  Set attribute value from string.

      \param  val       input, attribute value.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStrValue(const std::string& val) = 0;

  /*! \brief  Set attribute value from boolean.

      \param  val       input, attribute value.

      \returns  Boolean indicating success or failure.
  */
  bool SetBoolValue(const bool& val) {
    return SetStrValue((val == true)? ("true"): ("false"));
  }

  /*! \brief  Set attribute value as integer.

      \param  val       input, attribute value.

      \returns  Boolean indicating success or failure.
  */
  bool SetIntValue(const int& val) {
    return SetStrValue(IntToString(val));
  }

  /*  \brief  Set attribute value from byte sequence.

      \param  val       input, attribute value.

      \returns  Boolean indicating success or failure.
  */
//  bool SetBytesValue(const ByteSeq& val);

  /*! \brief  Get attribute name.

      \returns  Atrribute name.
  */
  virtual std::string GetName() = 0;

  /*! \brief  Get attribute value as string.

      \returns  Attribute value.
  */
  virtual std::string GetStrValue() = 0;

  /*! \brief  Get attribute value as boolean.

      If string representation of the attribute value is neither true nor
      false, it will fail.

      \returns  Attribute value. If fails, throws XMLException.
  */
  bool GetBoolValue() {
    if ((GetStrValue() != "true") && (GetStrValue() != "false")) {
      throw XMLException();
    }
    return ((GetStrValue() == "true")? (true): (false));
  }

  /*! \brief  Get attribute value as integer.

      If string representation of the attribute value contains non-numeric
      characters, it will fail.

      \returns  Attribute value. If fails, throws XMLException.
  */
  int GetIntValue() {
    return StringToInt(GetStrValue());
  }

  /*  \brief  Get attribute value as byte sequence.

      If string representation of the attribute value cannot be decoded as
      byte sequence, it will fail.

      \returns  Attribute value. If fails, throws XMLException.
  */
//  ByteSeq GetBytesValue();

  /*! \brief  Encode as string.

      \returns  Encoded string.
  */
  std::string Encode() {
    return GetName() + "=\"" + GetStrValue() + "\"";
  }
};

/*! \brief  XML element.
*/
class IXMLElement {
public:
  virtual ~IXMLElement() {
  }

  /*! \brief  Set element value from string.

      \param  val       input, element value.

      \returns  Boolean indicating success or failure.
  */
  virtual bool SetStrValue(const std::string& val) = 0;

  /*! \brief  Set element value from boolean.

      \param  val       input, element value.

      \returns  Boolean indicating success or failure.
  */
  bool SetBoolValue(const bool& val) {
    return SetStrValue((val == true)? ("true"): ("false"));
  }

  /*! \brief  Set element value as integer.

      \param  val       input, element value.

      \returns  Boolean indicating success or failure.
  */
  bool SetIntValue(const int& val) {
    return SetStrValue(IntToString(val));
  }

  /*  \brief  Set element value from byte sequence.

      \param  val       input, element value.

      \returns  Boolean indicating success or failure.
  */
//  bool SetBytesValue(const ByteSeq& val);

  /*! \brief  Add attribute with given name and value.

      \param  name      input, attribute name.
      \param  val       input, attribute value.

      \returns  Child element with given name. If zero, failed.
  */
  virtual IXMLAttribute* AddAttribute(const std::string& name, const
    std::string& val) = 0;

  /*! \brief  Add child element with given path.

      Path elements' names must be divided by a dot (".").

      \param  path      input, child element path.

      \returns  Child element with given path. If zero, failed.
  */
  virtual IXMLElement* AddChildElement(const std::string& path) = 0;

  /*! \brief  Add child element with given path and value.

      Path elements' names must be divided by a dot (".").

      \param  path      input, child element path.
      \param  val       input, child element value.

      \returns  Child element with given path and value. If zero, failed.
  */
  IXMLElement* AddChildElement(const std::string& path, const std::string& val) {
    IXMLElement* elem = AddChildElement(path);
    elem->SetStrValue(val);
    return elem;
  }

  /*! \brief  Get element name.

      \returns  Element name.
  */
  virtual std::string GetName() = 0;

  /*! \brief  Get element value as string.

      \returns  Element value. If fails, throws XMLException.
  */
  virtual std::string GetStrValue() = 0;

  /*! \brief  Get element value as boolean.

      If string representation of the element value is neither true nor
      false, it will fail.

      \returns  Element value. If fails, throws XMLException.
  */
  bool GetBoolValue() {
    if ((GetStrValue() != "true") && (GetStrValue() != "false")) {
      throw XMLException();
    }
    return ((GetStrValue() == "true")? (true): (false));
  }

  /*! \brief  Get element value as integer.

      If string representation of the element value contains non-numeric
      characters, it will fail.

      \returns  Element value. If fails, throws XMLException.
  */
  int GetIntValue() {
    return StringToInt(GetStrValue());
  }

  /*  \brief  Get element value as byte sequence.

      If string representation of the element value cannot be decoded as
      byte sequence, it will fail.

      \returns  Element value. If fails, throws XMLException.
  */
//  ByteSeq GetBytesValue();

  /*! \brief  Get all attributes with given name.

      \param  name      input, attribute name.

      \returns  Attributes with given name.
  */
  virtual std::vector<IXMLAttribute*> GetAttributes(const std::string& name) = 0;

  /*! \brief  Get first child element.

      \returns  First child element.
  */
  virtual IXMLElement* GetFirstChild() = 0;

  /*! \brief  Get first sibling element.

      \returns  First sibling element.
  */
  virtual IXMLElement* GetFirstSibling() = 0;

  /*! \brief  Get all child elements.

      \returns  Child elements.
  */
  virtual std::vector<IXMLElement*> GetAllChildElements() = 0;

  /*! \brief  Get all child elements and assert that number of child elements is
              at least 1.

      \returns  Child elements. If fails, throws XMLException.
  */
  std::vector<IXMLElement*> GetOneOrMoreChildElements() {
    std::vector<IXMLElement*> elements = GetAllChildElements();
    if (elements.size() == 0) {
      throw XMLException();
    }
    return elements;
  }

  /*! \brief  Get all child elements with given name.

      \param  name      input, element name.

      \returns  Child elements with given name.
  */
  std::vector<IXMLElement*> GetChildElementsByName(const std::string& name) {
    std::vector<IXMLElement*> elements = GetAllChildElements();
    std::vector<IXMLElement*> ret;
    for (unsigned int i = 0; i < elements.size(); i++) {
      if (elements[i]->GetName() == name) {
        ret.push_back(elements[i]);
      }
    }
    return ret;
  }

  /*! \brief  Get all child elements with given name and assert that number of
              elements is at least 1.

      \param  name      input, element name.

      \returns  Child elements with given name. If fails, throws XMLException.
  */
  std::vector<IXMLElement*> GetOneOrMoreChildElementsByName(const std::string& name) {
    std::vector<IXMLElement*> elems = GetChildElementsByName(name);
    if (elems.size() == 0) {
      throw XMLException();
    }
    return elems;
  }

  /*! \brief  Get all child elements with given name and assert that number of
              elements is at most 1.

      \param  name      input, element name.

      \returns  Child elements with given name. If fails, throws XMLException.
  */
  IXMLElement* GetAtMostOneChildElementByName(const std::string& name) {
    std::vector<IXMLElement*> elems = GetChildElementsByName(name);
    if (elems.size() > 1) {
      throw XMLException();
    } else if (elems.size() == 0) {
      return 0;
    } else {
      return elems[0];
    }
  }

  /*! \brief  Get child element with given path.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns this element.

      \param  path      input, child element path.

      \returns  Child element with given path. If zero, failed.
  */
  virtual IXMLElement* GetChildElement(const std::string& path) = 0;

  /*! \brief  Get value of the child element with given path as string.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns this element's value.

      \sa GetStrValue().

      \param  path      input, element path.

      \returns  Value of the child element with given path. If fails, throws
                XMLException.
  */
  std::string GetChildStrValue(const std::string& path) {
    IXMLElement* elem = GetChildElement(path);
    if (elem == 0) {
      throw XMLException();
    }
    return elem->GetStrValue();
  }

  /*! \brief  Get value of the child element with given path as boolean.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns this element's value.

      \sa GetBoolValue().

      \param  path      input, element path.

      \returns  Value of the child element with given path. If fails, throws
                XMLException.
  */
  bool GetChildBoolValue(const std::string& path) {
    IXMLElement* elem = GetChildElement(path);
    if (elem == 0) {
      throw XMLException();
    }
    return elem->GetBoolValue();
  }

  /*! \brief  Get value of the child element with given path as integer.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns this element's value.

      \sa GetIntValue().

      \param  path      input, element path.

      \returns  Value of the child element with given path. If fails, throws
                XMLException.
  */
  int GetChildIntValue(const std::string& path) {
    IXMLElement* elem = GetChildElement(path);
    if (elem == 0) {
      throw XMLException();
    }
    return elem->GetIntValue();
  }

  /*  \brief  Get value of the child element with given path as byte sequence.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns this element's value.

      \sa GetBytesValue().

      \param  path      input, element path.

      \returns  Value of the child element with given path. If fails, throws
                XMLException.
  */
//  ByteSeq GetChildBytesValue(const std::string& path);

  /*! \brief  Get attribute with given name of the child element with given path.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns this element's attribute
      with given name.

      \param  path      input, child element path.
      \param  name      input, attribute name.

      \returns  Attribute with given name of the child element with given path.
                If zero, failed.
  */
  IXMLAttribute* GetChildAttribute(const std::string& path, const std::string& name) {
    IXMLElement* elem = GetChildElement(path);
    if (elem == 0) {
      return 0;
    }
    std::vector<IXMLAttribute*> atts = elem->GetAttributes(name);
    if ((atts.size() == 0) || (atts.size() > 1)) {
      return 0;
    }
    return atts[0];
  }

  /*! \brief  Get value of the attribute with given name of the child element
              with given path as string.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns value of this element's
      attribute with given name.

      \sa IXMLAttribute::GetStrValue().

      \param  path      input, element path.
      \param  name      input, attribute name.

      \returns  Value of the attribute with given name of the child element
                with given path. If fails, throws XMLException.
  */
  std::string GetChildAttrStrValue(const std::string& path, const std::string& name) {
    IXMLAttribute* att = GetChildAttribute(path, name);
    if (att == 0) {
      throw XMLException();
    }
    return att->GetStrValue();
  }

  /*! \brief  Get value of the attribute with given name of the child element
              with given path as boolean.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns value of this element's
      attribute with given name.

      \sa IXMLAttribute::GetBoolValue().

      \param  path      input, element path.
      \param  name      input, attribute name.

      \returns  Value of the attribute with given name of the child element
                with given path. If fails, throws XMLException.
  */
  bool GetChildAttrBoolValue(const std::string& path, const std::string& name) {
    IXMLAttribute* att = GetChildAttribute(path, name);
    if (att == 0) {
      throw XMLException();
    }
    return att->GetBoolValue();
  }

  /*! \brief  Get value of the attribute with given name of the child element
              with given path as integer.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns value of this element's
      attribute with given name.

      \sa IXMLAttribute::GetIntValue().

      \param  path      input, element path.
      \param  name      input, attribute name.

      \returns  Value of the attribute with given name of the child element
                with given path. If fails, throws XMLException.
  */
  int GetChildAttrIntValue(const std::string& path, const std::string& name) {
    IXMLAttribute* att = GetChildAttribute(path, name);
    if (att == 0) {
      throw XMLException();
    }
    return att->GetIntValue();
  }

  /*  \brief  Get value of the attribute with given name of the child element
              with given path as byte sequence.

      Path elements' names must be divided by a dot (".").
      If path is an empty string (""), returns value of this element's
      attribute with given name.

      \sa IXMLAttribute::GetBytesValue().

      \param  path      input, element path.
      \param  name      input, attribute name.

      \returns  Value of the attribute with given name of the child element
                with given path. If fails, throws XMLException.
  */
//  ByteSeq GetChildAttrBytesValue(const std::string& path, const std::string& name);

  /*! \brief  Encode as string.

      \returns  Encoded string.
  */
  virtual std::string Encode() = 0;
};

/*! \brief  XML document.
*/
class IXMLDocument {
public:
  virtual ~IXMLDocument() {
  }

  /*! \brief  Get root element.

      \returns  Root element. If zero, failed.
  */
  virtual IXMLElement* GetRootElement() = 0;

  /*! \brief  Encode as string.

      \returns  Encoded string.
  */
  virtual std::string Encode() = 0;
};

} // namespace DRMPlugin

#endif // !defined (IXMLDOCUMENT_H)
