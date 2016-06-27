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

#ifdef WIN32
#	include <io.h>
#else
#	include <unistd.h>
#endif


#include <iostream>
#include <string>
#include <map>

using namespace std;

#include "squashxml/xml/XMLDocument.h"
#include "squashxml/xml/datatype/DataTypeByteArray.h"
#include "squashxml/xml/datatype/DataTypeCharArray.h"
#include "squashxml/xml/datatype/DataTypeDate.h"
#include "squashxml/xml/datatype/DataTypeInt.h"
#include "squashxml/xml/datatype/DataTypeLong.h"

#include "squashxml/tools/FileLogger.h"


static DOM_Node NULL_DOM_Node;

//======================================================================
//======================================================================
XMLDocument::XMLDocument()
{
    try
    {
		static bool bDone = false;
		if (!bDone)
		{
			bDone = true;
//			XMLPlatformUtils::Initialize();
			NULL_DOM_Node = NULL;
		}

		// Create DOM Parser
		//
//		mReader = new DOMParser();
		mReader = 0;

		mDoc = NULL;
		mRootNode = NULL;
    }
    catch (const XMLException& toCatch)
    {
		char msg[1024];
		sprintf(msg, "Error during initialization! Message:\n%s\n", XMLString::transcode(toCatch.getMessage()));
		gLogger->logError(msg);
        return;
    }
    catch (...)
    {
		gLogger->logError("UNKNOWN Error during initialization!");
        return;
    }
}


XMLDocument::XMLDocument(const XMLDocument* srcDCD, DOM_Node subNode)
{
	mReader = srcDCD->mReader;
	mDoc = srcDCD->mDoc;
	mRootNode = subNode;
}


XMLDocument::~XMLDocument()
{
	if (mDoc != NULL)
	{
		DOM_Element elem = mDoc.getDocumentElement();
		if (mRootNode == elem && mReader != NULL)
			delete mReader;
	}
}

//======================================================================
//======================================================================

char* XMLDocument::encode(DOM_Node currNode)
{
	string result = "";

	if (currNode == NULL)
		return strclone((char*)result.c_str());

	switch (currNode.getNodeType())
	{
		case DOM_Node::ELEMENT_NODE:
		{
      char* tmp = currNode.getNodeName().transcode();
			result += (string)"<" + (string)tmp;
      delete[] tmp;
			DOM_NamedNodeMap nnodeMap = currNode.getAttributes();
			for (unsigned int i = 0; i < nnodeMap.getLength(); i++)
			{
				DOM_Node attNode = nnodeMap.item(i);
        tmp = attNode.getNodeName().transcode();
        char* tmp1 = attNode.getNodeValue().transcode();
				result += (string)" " + (string)tmp + (string)"=\"" + (string)tmp1 + (string)"\"";
        delete[] tmp;
        delete[] tmp1;
			}
			result += (string)">";
			DOM_Node child = currNode.getFirstChild();
			while (child != NULL)
			{
				char *childStr = encode(child);
				result += childStr;
				delete[] childStr;
				child = child.getNextSibling();
			}
      tmp = currNode.getNodeName().transcode();
			result += (string)"</" + (string)tmp + ">";
      delete[] tmp;

			return strclone((char*)result.c_str());
		}
		case DOM_Node::TEXT_NODE:
		case DOM_Node::CDATA_SECTION_NODE:
		{
			static char reservedChars[] = "<>&'\"";
			char *str = currNode.getNodeValue().transcode();
			bool bSpecialChars = false;
			int len = strlen(str);
			for (int i = 0; i < len; i++)
			{
				if (strchr(reservedChars, str[i]) != NULL)
				{
					bSpecialChars = true;
					break;
				}
			}
			if (bSpecialChars == false)
				result += (string)str;
			else
				result += (string)"<![CDATA[" + (string)str + (string)"]]>";
      delete[] str;
			return strclone((char*)result.c_str());
		}
		default:
		{
			return strclone((char*)result.c_str());
		}
	}
}


char* XMLDocument::encode(bool usePrefixFlag /* =true */ )
{
	if (mDoc == NULL)
		return NULL;

	try
	{
/*
		if (mRootNode != mDoc.getDocumentElement())
		{
			return NULL;
		}

		XMLSerializer* xmlS = new XMLSerializer();
		ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
		xmlS.setOutputByteStream(outputStream);
		xmlS.serialize(mDoc);  // mRootNode?
		return outputStream.toString();
		delete xmlS;
*/
		string result = "";
		if (usePrefixFlag)
		{
			result += xmlPrefix();
		}
		char* encoded = encode(mRootNode);
		result += (string)encoded;
		delete[] encoded;

		return strclone((char*)result.c_str());
	}
    catch (const XMLException& toCatch)
    {
		char msg[1024];
		sprintf(msg, "Error during encode()! Message:\n%s\n", XMLString::transcode(toCatch.getMessage()));
		gLogger->logError(msg);
    }
    catch (...)
    {
		gLogger->logError("UNKNOWN Error during encode()!");
    }
	return NULL;
}


//======================================================================
//======================================================================
bool XMLDocument::decode(const char* bytes, const char* name)
{
	try
	{
		MemBufInputSource byteInput((const XMLByte *const)bytes, (const unsigned int )strlen(bytes), (char *const)"xmldocument");
    if (mReader == 0) mReader = new DOMParser();
		mReader->parse(byteInput);
		mDoc = mReader->getDocument();
		if (mDoc != NULL)
		{
			DOM_Element elem = mDoc.getDocumentElement();
			mRootNode = elem;
      char* tmp = mRootNode.getNodeName().transcode();
			if (strcmp(tmp, name) != 0)
			{ // Wrong Document
				  mDoc = NULL;
				  mRootNode = NULL;
			}
      delete[] tmp;
		}
	}
    catch (const XMLException& toCatch)
    {
    if (mReader != 0) delete mReader;
		char msg[1024];
		sprintf(msg, "Error during decode()! Message:\n%s\n", XMLString::transcode(toCatch.getMessage()));
		gLogger->logError(msg);
    }
    catch (...)
    {
    if (mReader != 0) delete mReader;
		gLogger->logError("UNKNOWN Error during decode()!");
    }
	return mDoc != NULL;
}

//======================================================================
//======================================================================
char* XMLDocument::getString(char* path)
{
	return getString(path, (DataTypeAttribute*)NULL);
}
char* XMLDocument::getString(char* path, DataTypeAttribute* dtAttribute)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return getString(path, dtAttributes);
}
char* XMLDocument::getString(char* path, DataTypeAttribute** dtAttributes)
{
	return getValue(mRootNode, path, dtAttributes);
}

bool XMLDocument::setString(char* path, char* value)
{
	return setString(path, (DataTypeAttribute*)NULL, value);
}
bool XMLDocument::setString(char* path, DataTypeAttribute* dtAttribute, char* value)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return setString(path, dtAttributes, value);
}
bool XMLDocument::setString(char* path, DataTypeAttribute** dtAttributes, char* value)
{
	return setValue(mRootNode, path, dtAttributes, value);
}


Date* XMLDocument::getDate(char* path)
{
	return getDate(path, (DataTypeAttribute*)NULL);
}
Date* XMLDocument::getDate(char* path, DataTypeAttribute* dtAttribute)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return getDate(path, dtAttributes);
}
Date* XMLDocument::getDate(char* path, DataTypeAttribute** dtAttributes)
{
	static DataTypeDate dtDate;
  char* tmp = getValue(mRootNode, path, dtAttributes);
	Date* ret = new Date((Date*)dtDate.decode(tmp));
  delete[] tmp;
  return ret;
}

bool XMLDocument::setDate(char* path, Date value)
{
	return setDate(path, (DataTypeAttribute*)NULL, value);
}
bool XMLDocument::setDate(char* path, DataTypeAttribute* dtAttribute, Date value)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return setDate(path, dtAttributes, value);
}
bool XMLDocument::setDate(char* path, DataTypeAttribute** dtAttributes, Date value)
{
	static DataTypeDate dtDate;
	return setValue(mRootNode, path, dtAttributes, dtDate.encode((void*)&value));
}


int XMLDocument::getInteger(char* path)
{
	return getInteger(path, (DataTypeAttribute*)NULL);
}
int XMLDocument::getInteger(char* path, DataTypeAttribute* dtAttribute)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return getInteger(path, dtAttributes);
}
int XMLDocument::getInteger(char* path, DataTypeAttribute** dtAttributes)
{
	static DataTypeInt dtInt;
  char* tmp = getValue(mRootNode, path, dtAttributes);
	// BE CAREFUL WITH THIS! 
	// THIS CAN BREAK 64-bit compatibility!
	void* ptr = dtInt.decode(tmp);
	int ret = *((int*)&ptr);
  delete[] tmp;
  return ret;
}

bool XMLDocument::setInteger(char* path, int value)
{
	return setInteger(path, (DataTypeAttribute*)NULL, value);
}
bool XMLDocument::setInteger(char* path, DataTypeAttribute* dtAttribute, int value)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return setInteger(path, dtAttributes, value);
}
bool XMLDocument::setInteger(char* path, DataTypeAttribute** dtAttributes, int value)
{
	static DataTypeInt dtInt;
	return setValue(mRootNode, path, dtAttributes, dtInt.encode((void*)value));
}


long XMLDocument::getLong(char* path)
{
	return getLong(path, (DataTypeAttribute*)NULL);
}
long XMLDocument::getLong(char* path, DataTypeAttribute* dtAttribute)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return getLong(path, dtAttributes);
}
long XMLDocument::getLong(char* path, DataTypeAttribute** dtAttributes)
{
	static DataTypeLong dtLong;
  char* tmp = getValue(mRootNode, path, dtAttributes);
	long ret = (long)dtLong.decode(tmp);
  delete[] tmp;
  return ret;
}

bool XMLDocument::setLong(char* path, long value)
{
	return setLong(path, (DataTypeAttribute*)NULL, value);
}
bool XMLDocument::setLong(char* path, DataTypeAttribute* dtAttribute, long value)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return setLong(path, dtAttributes, value);
}
bool XMLDocument::setLong(char* path, DataTypeAttribute** dtAttributes, long value)
{
	static DataTypeLong dtLong;
	return setValue(mRootNode, path, dtAttributes, dtLong.encode((void*)value));
}


ByteArray* XMLDocument::getBytes(char* path)
{
	return getBytes(path, (DataTypeAttribute*)NULL);
}
ByteArray* XMLDocument::getBytes(char* path, DataTypeAttribute* dtAttribute)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return getBytes(path, dtAttributes);
}
ByteArray* XMLDocument::getBytes(char* path, DataTypeAttribute** dtAttributes)
{
	static DataTypeByteArray dtByteArray;
  char* tmp = getValue(mRootNode, path, dtAttributes);
  ByteArray* ret = (ByteArray*)dtByteArray.decode(tmp);
  delete[] tmp;
	return ret;
}

bool XMLDocument::setBytes(char* path, ByteArray* value)
{
	return setBytes(path, (DataTypeAttribute*)NULL, value);
}
bool XMLDocument::setBytes(char* path, DataTypeAttribute* dtAttribute, ByteArray* value)
{
	DataTypeAttribute* dtAttributes[2];
	dtAttributes[0] = dtAttribute;
	dtAttributes[1] = (DataTypeAttribute*)NULL;
	return setBytes(path, dtAttributes, value);
}
bool XMLDocument::setBytes(char* path, DataTypeAttribute** dtAttributes, ByteArray* value)
{
	static DataTypeByteArray dtByteArray;
	return setValue(mRootNode, path, dtAttributes, dtByteArray.encode((void*)&value));
}

//======================================================================
//======================================================================
DataTypeAttribute** XMLDocument::getAttributeList(char* path)
{
	if (mDoc == NULL)
		return NULL;

	if (path == NULL)
		return NULL;

	DOM_Node child = getNode(mRootNode, path, NULL);
	if (child == NULL)
		return NULL;

	DOM_NamedNodeMap nnodeMap = child.getAttributes();
	int len = nnodeMap.getLength();
	if (len == 0)
		return NULL;

	DataTypeAttribute** dtAttributes = new DataTypeAttribute*[len+1];
	for (int i = 0; i < len; i++)
	{
		DOM_Node attNode = nnodeMap.item(i);
    char* tmp = attNode.getNodeName().transcode();
    char* tmp1 = attNode.getNodeValue().transcode();
		dtAttributes[i] = new DataTypeAttribute(tmp, tmp1);
    delete[] tmp;
    delete[] tmp1;
	}
	dtAttributes[len] = (DataTypeAttribute*)NULL;
	return dtAttributes;
}

//======================================================================
// CJM 4/17/03 ..Needed to update an attribute list... for ContentGuard
//======================================================================
bool XMLDocument::setAttributeList(char* path, DataTypeAttribute** dtAttributes)
{
	if (mDoc == NULL)
		return false;

	if (path == NULL)
		return false;

	DOM_Node child = getNode(mRootNode, path, NULL);
	char* value = getString(path);

	if (child == NULL)
		return false;

	short nType = child.getNodeType();

	DOM_Node parent = child.getParentNode();
	if (parent == NULL)
		return false;

	char* childName = child.getNodeName().transcode();
	DOM_NamedNodeMap nnodeMap = child.getAttributes();

	parent.removeChild(child);
	DOM_Element childElement = mDoc.createElement(childName);
  delete[] childName;

	int a = 0;
	DataTypeAttribute* dtAttribute;
	while ((dtAttribute = (DataTypeAttribute*)dtAttributes[a++]) != (DataTypeAttribute*)NULL)
	{

		childElement.setAttribute(dtAttribute->getName(), dtAttribute->getValue());
	}

	if (nType == DOM_Node::TEXT_NODE)
	{
		DOM_Text childText = mDoc.createTextNode((value == NULL)?"":value);
		childElement.appendChild(childText);
	}
	else
	{
		if (nType == DOM_Node::CDATA_SECTION_NODE)
		{
			DOM_CDATASection childCData = mDoc.createCDATASection((value == NULL)?"":value);
			childElement.appendChild(childCData);
		}
	}

	parent.appendChild(childElement);

	return true;

}

char* XMLDocument::getAttributeValue(char* path, char* attributeName)
{
	if (attributeName == NULL)
		return NULL;

	DataTypeAttribute** dtAttributes = getAttributeList(path);
	if (dtAttributes == NULL)
		return NULL;

	int i = 0;
	DataTypeAttribute* dtAttribute;
	while ((dtAttribute = (DataTypeAttribute*)dtAttributes[i++]) != (DataTypeAttribute*)NULL)
	{
		if (strcmp(dtAttribute->getName(), attributeName) == 0)
			return strclone(dtAttribute->getValue());
	}

	return NULL;
}


//======================================================================
//======================================================================
XMLDocument* XMLDocument::getSubDoc(char* path)
{
	if (mDoc == NULL)
		return NULL;
	return getSubDoc(mRootNode, path);
}

//======================================================================
//======================================================================
bool XMLDocument::remove(char* path)
{
	XMLDocument* pGone = getSubDoc(mRootNode, path);
	if (pGone == NULL)
		return false;

	pGone->mRootNode.getParentNode().removeChild(pGone->mRootNode);
	delete pGone;
	return true;
}


//======================================================================
//======================================================================
HashMap* XMLDocument::getDocList(char* name)
{

	if (mDoc == NULL)
		return NULL;
	ListNodeFilter* listnodeFilter = new ListNodeFilter(name);
	DOM_NodeIterator ni = mDoc.createNodeIterator(mRootNode, DOM_NodeFilter::SHOW_ELEMENT, listnodeFilter, true);

	int i = 1;
	DOM_Node n;
	HashMap* pHash = new HashMap();
	while ((n = ni.nextNode()) != NULL)
	{
		XMLDocument* xmlDoc = new XMLDocument(this, n);
		char uName[128];
		sprintf(uName, "%s-%d", name, i++);
		pHash->put(uName, (void*)xmlDoc);
	}

	delete listnodeFilter;
	return pHash;
}


//======================================================================
//======================================================================
XMLDocument* XMLDocument::clone()
{
	if (mDoc == NULL || mRootNode == NULL)
	  return NULL;
	DOM_Node newNode = clone(mRootNode);
	if (newNode != NULL)
	{
	   if (mRootNode != mDoc.getDocumentElement())
			mRootNode.getParentNode().appendChild(newNode);
	   return new XMLDocument(this, newNode);
	}
	return NULL;
}

//======================================================================
//======================================================================
//======================================================================
//======================================================================
//======================================================================
//======================================================================
char* XMLDocument::strclone(char* refstr)
{
	if (refstr == NULL)
		return NULL;
	int len = strlen(refstr);
	char *dupstr = new char[len+1];
	strcpy(dupstr, refstr);
	return dupstr;
}

DOM_Node XMLDocument::clone(DOM_Node currNode)
{
	switch (currNode.getNodeType())
	{
		case DOM_Node::ELEMENT_NODE:
		{
			DOM_Element elem = mDoc.createElement(currNode.getNodeName());
			DOM_NamedNodeMap nnodeMap = currNode.getAttributes();
			for (unsigned int i = 0; i < nnodeMap.getLength(); i++)
			{
				DOM_Node attNode = nnodeMap.item(i);
				elem.setAttribute(attNode.getNodeName(), attNode.getNodeValue());
			}
			DOM_Node child = currNode.getFirstChild();
			while (child != NULL)
			{
				DOM_Node cNode = clone(child);
				if (cNode != NULL)
					elem.appendChild(cNode);
				child = child.getNextSibling();
			}
			return (DOM_Node)elem;
		}
		case DOM_Node::TEXT_NODE:
		{
			DOM_Text childText = mDoc.createTextNode(currNode.getNodeValue());
			return (DOM_Node)childText;
		}
		case DOM_Node::CDATA_SECTION_NODE:
		{
			DOM_CDATASection childCData = mDoc.createCDATASection(currNode.getNodeValue());
			return (DOM_Node)childCData;
		}
		default:
		{
			return NULL_DOM_Node;
		}
	}
}

//======================================================================
//======================================================================
bool XMLDocument::doAttributesMatch(DOM_Node currNode, DataTypeAttribute** dtAttributes)
{
	DOM_NamedNodeMap nnodeMap = currNode.getAttributes();
	int len = nnodeMap.getLength();
	int a = 0;
	DataTypeAttribute* dtAttribute;
	while ((dtAttribute = (DataTypeAttribute*)dtAttributes[a++]) != (DataTypeAttribute*)NULL)
	{
		bool isFound = false;
		for (int i = 0; i < len && !isFound; i++)
		{
			DOM_Node attNode = nnodeMap.item(i);
      char* tmp = attNode.getNodeName().transcode();
      char* tmp1 = attNode.getNodeValue().transcode();
			if (strcmp(dtAttribute->getName(), tmp) == 0 &&
				strcmp(dtAttribute->getValue(), tmp1) == 0)
			{
				isFound = true;
			}
      delete[] tmp;
      delete[] tmp1;
		}
		if (!isFound)
			return false;
	}

	return true;
}



DOM_Node XMLDocument::getNode(DOM_Node currNode, char* path, DataTypeAttribute** dtAttributes)
{
	if (path == NULL)
		return NULL_DOM_Node;

	char* currName = currNode.getNodeName().transcode();

  if (strcmp(currName, path) == 0 && (dtAttributes == NULL || doAttributesMatch(currNode, dtAttributes))) {
    delete[] currName;
		return currNode;
  }
  delete[] currName;

	char* cp = strchr(path, '.');
	char pathName[256];
	if (cp == NULL)
		strcpy(pathName, path);
	else
	{
		strncpy(pathName, path, cp - path);
		pathName[cp - path] = '\0';
	}

	DOM_Node child = currNode.getFirstChild();
	while (child != NULL)
	{
		char* childName = child.getNodeName().transcode();
		if (child.getNodeType() != DOM_Node::ELEMENT_NODE)
		{
			child = child.getNextSibling();
      delete[] childName;
			continue;
		}

		if (strcmp(pathName, childName) == 0)
		{
      if (cp != NULL) {
        delete[] childName;
				return getNode(child, cp+1, dtAttributes);
      }

			if (dtAttributes != NULL)
			{
				if (!doAttributesMatch(child, dtAttributes))
				{
					child = child.getNextSibling();
          delete[] childName;
					continue;
				}
			}

      delete[] childName;
			return child;
		}

    delete[] childName;
		child = child.getNextSibling();
	}
 	return NULL_DOM_Node;
}


//======================================================================
//======================================================================
char* XMLDocument::getValue(DOM_Node currNode, char* path, DataTypeAttribute** dtAttributes)
{
	if (mDoc == NULL)
		return NULL;

	if (path == NULL)
		return NULL;

	DOM_Node child = getNode(currNode, path, dtAttributes);
	if (child == NULL)
		return NULL;

	child = child.getFirstChild();
	if (child == NULL)
		return NULL;

	// If siblings exist, this is not an leaf, but a branch
	DOM_Node sib  = child.getNextSibling();
	if (sib != NULL)
		return NULL;

	if (child.getNodeType() != DOM_Node::TEXT_NODE && child.getNodeType() != DOM_Node::CDATA_SECTION_NODE)
		return NULL;

	return child.getNodeValue().transcode();
}


//======================================================================
//======================================================================
bool XMLDocument::setValue(DOM_Node currNode, char* path, DataTypeAttribute** dtAttributes, char* value)
{
	if (mDoc == NULL)
		return false;

	if (path == NULL)
		return false;

	DOM_Node child = getNode(currNode, path, dtAttributes);
	if (child == NULL)
		return false;
	DOM_Node parent = child.getParentNode();
	if (parent == NULL)
		return false;

	DOM_Node grandChild = child.getFirstChild();
	short nType = DOM_Node::TEXT_NODE;
	if (grandChild != NULL)
	{
		nType = grandChild.getNodeType();
		if (nType != DOM_Node::TEXT_NODE && nType != DOM_Node::CDATA_SECTION_NODE)
			return false;
	}

	char* childName = child.getNodeName().transcode();
	DOM_NamedNodeMap nnodeMap = child.getAttributes();

	parent.removeChild(child);
	DOM_Element childElement = mDoc.createElement(childName);
  delete[] childName;
	for (unsigned int i = 0; i < nnodeMap.getLength(); i++)
	{
		DOM_Node attNode = nnodeMap.item(i);
		childElement.setAttribute(attNode.getNodeName(), attNode.getNodeValue());
	}

	if (nType == DOM_Node::TEXT_NODE)
	{
		DOM_Text childText = mDoc.createTextNode((value == NULL)?"":value);
		childElement.appendChild(childText);
	}
	else
	{
		DOM_CDATASection childCData = mDoc.createCDATASection((value == NULL)?"":value);
		childElement.appendChild(childCData);
	}
	parent.appendChild(childElement);

	return true;
}

//======================================================================
//======================================================================
XMLDocument* XMLDocument::getSubDoc(DOM_Node currNode, char* path)
{
	if (path == NULL)
		return NULL;

	DOM_Node child = getNode(currNode, path, NULL);
	if (child == NULL)
		return NULL;

	return new XMLDocument(this, child);
}


//======================================================================
//======================================================================
ListNodeFilter::ListNodeFilter(char* name)
{
	mNodeName = NULL;
	if (name == NULL)
		return;
	mNodeName = new char[strlen(name)+1];
	strcpy(mNodeName, name);
}

ListNodeFilter::~ListNodeFilter()
{
	if (mNodeName != NULL)
		delete[] mNodeName;
}

short ListNodeFilter::acceptNode(const class DOM_Node &n) const
{
  char* tmp = n.getNodeName().transcode();
  if (n.getNodeType() == DOM_Node::ELEMENT_NODE && strcmp(tmp, mNodeName) == 0) {
    delete[] tmp;
		return FILTER_ACCEPT;
  }

  delete[] tmp;
	// Not interested
	return FILTER_SKIP;
}
