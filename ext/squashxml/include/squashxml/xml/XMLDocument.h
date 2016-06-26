/* ***** BEGIN LICENSE BLOCK *****
 *	The contents of this file are subject to the Mozilla Public License
 *	Version 1.1 (the "License"); you may not use this file except in
 *	compliance with the License. You may obtain a copy of the License at
 *	http://www.mozilla.org/MPL/
 *
 *	Software distributed under the License is distributed on an "AS IS"
 *	basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *	License for the specific language governing rights and limitations
 *	under the License.
 *
 *	The Original Code is SquashXML.
 *
 *	The Initial Developer of the Original Code is Ayman A. Gebrail.
 *	Portions created by Ayman A. Gebrail are
 *	Copyright (C) 2002 Ayman A. Gebrail. All Rights Reserved.
 *
 *  Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef XMLDocument_H
#define XMLDocument_H


// TODO: Do a proper upgrade from 1.6 to 2.1 (i.e. remove use of deprecated class)
#include <xercesc/util/PlatformUtils.hpp>
//#include <xercesc/parsers/DOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/dom/deprecated/DOM_Document.hpp>
#include <xercesc/dom/deprecated/DOM_Document.hpp>

// CJM: need this for the port to Xerces 2.3
#include <xercesc/dom/deprecated/DOMParser.hpp>

#include "squashxml/tools/ByteArray.h"
#include "squashxml/tools/HashMap.h"
#include "squashxml/tools/Date.h"
#include "squashxml/xml/datatype/DataTypeAttribute.h"

XERCES_CPP_NAMESPACE_USE

class XMLDocument
{
public:
	XMLDocument();
	~XMLDocument();

	static char* xmlPrefix(){ return "<?xml version=\"1.0\"?>\n"; };

	char* encode(bool usePrefixFlag=true);
	bool decode(const char* bytes, const char* name);

	char* getString(char* path);
	char* getString(char* path, DataTypeAttribute* dtAttribute);
	char* getString(char* path, DataTypeAttribute** dtAttribute);
	bool setString(char* path, char* value);
	bool setString(char* path, DataTypeAttribute* dtAttribute, char* value);
	bool setString(char* path, DataTypeAttribute** dtAttribute, char* value);

	Date* getDate(char* path);
	Date* getDate(char* path, DataTypeAttribute* dtAttribute);
	Date* getDate(char* path, DataTypeAttribute** dtAttribute);
	bool setDate(char* path, Date value);
	bool setDate(char* path, DataTypeAttribute* dtAttribute, Date value);
	bool setDate(char* path, DataTypeAttribute** dtAttribute, Date value);


	int getInteger(char* path);
	int getInteger(char* path, DataTypeAttribute* dtAttribute);
	int getInteger(char* path, DataTypeAttribute** dtAttribute);
	bool setInteger(char* path, int value);
	bool setInteger(char* path, DataTypeAttribute* dtAttribute, int value);
	bool setInteger(char* path, DataTypeAttribute** dtAttribute, int value);


	long getLong(char* path);
	long getLong(char* path, DataTypeAttribute* dtAttribute);
	long getLong(char* path, DataTypeAttribute** dtAttribute);
	bool setLong(char* path, long value);
	bool setLong(char* path, DataTypeAttribute* dtAttribute, long value);
	bool setLong(char* path, DataTypeAttribute** dtAttribute, long value);


	ByteArray* getBytes(char* path);
	ByteArray* getBytes(char* path, DataTypeAttribute* dtAttribute);
	ByteArray* getBytes(char* path, DataTypeAttribute** dtAttribute);
	bool setBytes(char* path, ByteArray* value);
	bool setBytes(char* path, DataTypeAttribute* dtAttribute, ByteArray* value);
	bool setBytes(char* path, DataTypeAttribute** dtAttribute, ByteArray* value);

	char* getAttributeValue(char* path, char* attributeName);
	DataTypeAttribute** getAttributeList(char* path);
	
	/** CJM 4/17/03 */
	bool setAttributeList(char* path, DataTypeAttribute**);

	XMLDocument* getSubDoc(char* path);
	bool remove(char* path);
	HashMap* getDocList(char* name);
	XMLDocument* clone();

private:
	// Contains one of DOM's Parser instances.
	DOMParser* mReader;
	DOM_Document mDoc;
	DOM_Node mRootNode;

	XMLDocument(const XMLDocument* srcDCD, DOM_Node subNode);

	char* encode(DOM_Node currNode);

	bool doAttributesMatch(DOM_Node currNode, DataTypeAttribute** dtAttributes);
	DOM_Node getNode(DOM_Node currNode, char* path, DataTypeAttribute** dtAttributes);

	char* getValue(DOM_Node currNode, char* path, DataTypeAttribute** dtAttributes);
	bool setValue(DOM_Node currNode, char* path, DataTypeAttribute** dtAttributes, char* value);

	DOM_Node clone(DOM_Node currNode);

	XMLDocument* getSubDoc(DOM_Node currNode, char* path);

	char* strclone(char* refstr);
};


class ListNodeFilter : public DOM_NodeFilter
{
public:

	ListNodeFilter(char* name);
	~ListNodeFilter();
	short acceptNode(const class DOM_Node &n) const;

private:
	char* mNodeName;
};

#endif // XMLDocument_H
