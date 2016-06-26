/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */


/**
 * @file BasicNode.hpp
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */
  
#if !defined(_BASICNODE_H____OF_AXIS_INCLUDED_)
#define _BASICNODE_H____OF_AXIS_INCLUDED_

#include "GDefine.hpp"
#include <axis/IAttribute.hpp>
#include <list>

AXIS_CPP_NAMESPACE_START

class SoapSerializer;

typedef enum { ELEMENT_NODE=1, CHARACTER_NODE} NODE_TYPE;

/*
 * @class BasicNode
 * @brief interface for the BasicNode class.
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/25 samisa
 * Added constructors, copy constructure and pure virtual clone for copy constructing derived classes
 */

/*
 * Revision 1.2  2004/06/13 roshan
 * Added doxygen comments to help autobuild API docs
 */

/*
 * Revision 1.3  2004/07/28 roshan
 * Added the method getLocalName()
 */

class BasicNode
{
public:

    /**
      * Returns the Attribute of this node, corresponding to the given 
      * prefix/localname pair or the given namespace URI/localname pair. 
      * The users could get the attributes with the 
      * following combinations of pairs.
      *  1. by prefix and localname pair (here the namespace URI(i.e pachURI
      *      has to be a empty string)) or
      *  2. by namespace URI and localname pair (here the prefix
      *      (i.e pachPrefix has to be a empty string)).
      * The operation behavior depends on the TYPE of the node.
      */
    virtual IAttribute* getAttribute(AxisChar* pachPrefix, AxisChar* pachURI, AxisChar* pachLocalname) = 0;

    /**
      * Returns the first Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
    virtual IAttribute* getFirstAttribute() = 0;

    /**
      * Returns the last Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
    virtual IAttribute* getLastAttribute() = 0;

    /**
      * Returns the next Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
    virtual IAttribute* getNextAttribute() = 0;

    /**
      * Returns the current Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
    virtual IAttribute* getCurrentAttribute() = 0;


    /** 
      * Creates an Attribute and adds it to this Basic Node. 
      * 
      * @param localname The local name of the attribute. 
      * @param prefix The prefix of the attribute. 
      * @param uri The namespace uri of the attribute. 
      * @param value The value of the attribute. 
      * 
      * @return A pointer to the created Attribute will be returned. 
      */
    virtual IAttribute* createAttribute(const AxisChar* localname, 
            const AxisChar* prefix, const AxisChar* uri, 
            const AxisChar* value) =0;

    /** 
      * Creates an Attribute and adds it to this Basic Node. 
      * 
      * @param localname The local name of the attribute. 
      * @param prefix The prefix of the attribute. 
      * @param value The value of the attribute. 
      * 
      * @return A pointer to the created Attribute will be returned. 
      */
    virtual IAttribute* createAttribute(const AxisChar* localname,
        const AxisChar* prefix, const AxisChar* value)=0 ;

    /**
      * Creates an Attribute and adds it to this Basic Node.
      *
      * @param localname The local name of the attribute.
      * @param value The value of the attribute.
      *
      * @return A pointer to the created Attribute will be returned.
      */
    virtual IAttribute* createAttribute(const AxisChar* localname,
        const AxisChar* value)=0 ;

    /**
      * Returns the local name of this node. The operation
      * behavior depends on the TYPE of the node.
      * 
      * @return The localname of this element.
      */
    virtual const AxisChar* getLocalName() = 0; 

    /**
      * Returns the number of child elements of this element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The number of child elements of this element. The return value
      * behavior depends on the TYPE of the node.
      */
    virtual int getNoOfChildren() = 0;

    /**
      * Gets the first Child Node of this Complex Element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The first Child Node of this Element.
      */
    virtual BasicNode* getFirstChild() = 0;

    /**
      * Gets the last Child Node of this Complex Element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The last Child Node of this Element.
      */
    virtual BasicNode* getLastChild() = 0;

    /**
      * Get the Child Node of the given position. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param iChildPosition The child position.
      * @return The Child Node of the given position.
      */
    virtual BasicNode* getChild(int iChildPosition) = 0;

    /**
      * Adds the given child node to this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pBasicNode the child node to be added to this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int addChild(BasicNode* pBasicNode) =0;

    /**
      * Gets the Node Type of the Element.
      *
      * @return The Node Type of the Element.
      */
    virtual NODE_TYPE getNodeType() const =0;

    /**
      * Gets and return the value of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @return The value of this Element.
      */    
    virtual const AxisChar* getValue() const =0;

    /**
      * Sets the value of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachValue The value to be set
      * @return AXIS_SUCCESS to indicate success.
      */   
    virtual int setValue(const AxisChar* pachValue)=0;
    
    /**
      * Sets the namespace URI of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachURI the namespace URI of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int setURI(const AxisChar* sURI) =0;

    /**
      * Sets the local name of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachLocalName the local name of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int setLocalName(const AxisChar* sLocalName) =0;

    /**
      * Sets the prefix of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachPrefix the prefix of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
    virtual int setPrefix(const AxisChar* sPrefix) =0;

    /**
      * Returns the namespace URI of this node.  The operation behavior
      * depends on the TYPE of the node.
      */
    virtual const AxisChar* getURI() = 0;

    /**
      * Returns the prefix  of this node.  The operation behavior
      * depends on the TYPE of the node.
      */
    virtual const AxisChar* getPrefix() = 0;

    virtual int serialize(SoapSerializer& pSZ) =0;
    virtual int serialize(SoapSerializer& pSZ, 
    std::list<AxisChar*>& lstTmpNameSpaceStack) =0;
    BasicNode();
    BasicNode(const AxisChar* pachValue, NODE_TYPE eNodeType = ELEMENT_NODE);
    BasicNode(const BasicNode& rCopy);
    virtual BasicNode* clone() = 0;
    virtual ~BasicNode();

protected:
    /**
      * Used to store the Node Type, which is either ELEMENT_NODE or 
      * CHARACTER_NODE.
      */
    NODE_TYPE m_iNodeType;

    /**
      * Used to store the value. The usage of this variable depends on the TYPE
      * of the node.
      */
    AxisChar* m_pachValue;

};

AXIS_CPP_NAMESPACE_END

#endif 

