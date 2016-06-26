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
 */
#ifndef BASICNODE_INCLUDED
#define BASICNODE_INCLUDED

typedef enum { ELEMENT_NODE=1, CHARACTER_NODE} AXISC_NODE_TYPE;

/*
 * @class BasicNode
 * @brief interface for the BasicNode class.
 *
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
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetAttribute(AXISCHANDLE basicNode, AxiscChar * pachPrefix, 
	AxiscChar * pachURI, AxiscChar * pachLocalname);

/**
      * Returns the first Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetFirstAttribute(AXISCHANDLE basicNode);

/**
      * Returns the last Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetLastAttribute(AXISCHANDLE basicNode);

/**
      * Returns the next Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetNextAttribute(AXISCHANDLE basicNode);

/**
      * Returns the current Attribute of this node. The operation
      * behavior depends on the TYPE of the node.
      */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetCurrentAttribute(AXISCHANDLE basicNode);

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
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateAttributeBasicNode(AXISCHANDLE basicNode, const AxiscChar * localname, 
	const AxiscChar * prefix, const AxiscChar * uri, const AxiscChar * value);

/** 
      * Creates an Attribute and adds it to this Basic Node. 
      * 
      * @param localname The local name of the attribute. 
      * @param prefix The prefix of the attribute. 
      * @param value The value of the attribute. 
      * 
      * @return A pointer to the created Attribute will be returned. 
      */

/**
      * Creates an Attribute and adds it to this Basic Node.
      *
      * @param localname The local name of the attribute.
      * @param value The value of the attribute.
      *
      * @return A pointer to the created Attribute will be returned.
      */

/**
      * Returns the local name of this node. The operation
      * behavior depends on the TYPE of the node.
      * 
      * @return The localname of this element.
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetLocalNameBasicNode(AXISCHANDLE basicNode);

/**
      * Returns the number of child elements of this element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The number of child elements of this element. The return value
      * behavior depends on the TYPE of the node.
      */
AXISC_STORAGE_CLASS_INFO int axiscGetNoOfChildrenBasicNode(AXISCHANDLE basicNode);

/**
      * Gets the first Child Node of this Complex Element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The first Child Node of this Element.
      */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetFirstChildBasicNodeBasicNode(AXISCHANDLE basicNode);

/**
      * Gets the last Child Node of this Complex Element. The operation
      * behavior depends on the TYPE of the node.
      *
      * @return The last Child Node of this Element.
      */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetLastChildBasicNodeBasicNode(AXISCHANDLE basicNode);

/**
      * Get the Child Node of the given position. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param iChildPosition The child position.
      * @return The Child Node of the given position.
      */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscGetChildBasicNodeBasicNode(AXISCHANDLE basicNode, int iChildPosition);

/**
      * Adds the given child node to this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pBasicNode the child node to be added to this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
AXISC_STORAGE_CLASS_INFO int axiscAddChildBasicNode(AXISCHANDLE basicNode, AXISCHANDLE pBasicNode);

/**
      * Gets the Node Type of the Element.
      *
      * @return The Node Type of the Element.
      */
AXISC_STORAGE_CLASS_INFO AXISC_NODE_TYPE axiscGetNodeType(AXISCHANDLE basicNode);

/**
      * Gets and return the value of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @return The value of this Element.
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetValueBasicNode(AXISCHANDLE basicNode);

/**
      * Sets the value of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachValue The value to be set
      * @return AXIS_SUCCESS to indicate success.
      */
AXISC_STORAGE_CLASS_INFO int axiscSetValueBasicNode(AXISCHANDLE basicNode, const AxiscChar * pachValue);

/**
      * Sets the namespace URI of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachURI the namespace URI of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
AXISC_STORAGE_CLASS_INFO int axiscSetURIBasicNode(AXISCHANDLE basicNode, const AxiscChar * sURI);

/**
      * Sets the local name of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachLocalName the local name of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
AXISC_STORAGE_CLASS_INFO int axiscSetLocalNameBasicNode(AXISCHANDLE basicNode, const AxiscChar * sLocalName);

/**
      * Sets the prefix of this Element. The operation behavior
      * depends on the TYPE of the node.
      *
      * @param pachPrefix the prefix of this Element.
      * @return AXIS_SUCCESS to indicate successfull operation.
      */
AXISC_STORAGE_CLASS_INFO int axiscSetPrefixBasicNode(AXISCHANDLE basicNode, const AxiscChar * sPrefix);

/**
      * Returns the namespace URI of this node.  The operation behavior
      * depends on the TYPE of the node.
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetURIBasicNode(AXISCHANDLE basicNode);

/**
      * Returns the prefix  of this node.  The operation behavior
      * depends on the TYPE of the node.
      */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetPrefixBasicNode(AXISCHANDLE basicNode);
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCloneBasicNodeBasicNode(AXISCHANDLE basicNode);
AXISC_STORAGE_CLASS_INFO void axiscDestroyBasicNode(AXISCHANDLE basicNode);

/**
      * Used to store the Node Type, which is either ELEMENT_NODE or 
      * CHARACTER_NODE.
      */
/**
      * Used to store the value. The usage of this variable depends on the TYPE
      * of the node.
      */


#endif // BASICNODE_INCLUDED
