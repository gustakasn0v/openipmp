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

package squashxml.xml;

import java.io.*;
import java.util.*;

import org.xml.sax.*;

import org.w3c.dom.*;
import org.w3c.dom.traversal.*;

import org.apache.xerces.parsers.DOMParser;
import org.apache.xerces.dom.*;
import org.apache.xml.serialize.*;

import squashxml.xml.datatype.*;

//======================================================================
//======================================================================
public class XMLDocument
{
  // Contains one of DOM's Parser instances.
  DOMParser mReader;

  Document mDoc;
  Node mRootNode;

  public static String xmlPrefix = "<?xml version=\"1.0\"?>\n";

  //======================================================================
  //======================================================================
  public XMLDocument()
  {
	try
	{
	  // Create DOM Parser
	  //
	  mReader = new DOMParser();

	  mDoc = null;
	  mRootNode = null;
	}
	catch (Exception e)
	{
	  e.printStackTrace();
	  mReader = null;
	}
  }

  private XMLDocument(XMLDocument srcDCD, Node subNode)
  {
	mReader = srcDCD.mReader;
	mDoc = srcDCD.mDoc;
	mRootNode = subNode;
  }



  //======================================================================
  //======================================================================
  public String encode()
  {
		return encode(true);
  }
  public String encode(boolean usePrefixFlag)
  {
	  try
	  {


		  if (mDoc == null)
	    	  return null;

/*
		  if (mRootNode != mDoc.getDocumentElement())
		  {
			  return null;
		  }
*/
		  String result = "";
		  if (usePrefixFlag)
		  {
			  result += xmlPrefix;
		  }
		  String encoded = encode(mRootNode);
		  result += encoded;

		  return result;
	  }
	  catch (Exception ex)
	  {
		  return null;
	  }
  }
  String encode(Node currNode)
  {
	  String result = "";

	  if (currNode == null)
	  {
		  return result;
	  }


	  switch( currNode.getNodeType() )
	  {
		  case Node.ELEMENT_NODE:
		  {
			  result += "<" + currNode.getNodeName();
//			  System.out.println("----------\n"+result+"\n------------");
			  NamedNodeMap nnodeMap = currNode.getAttributes();

			  for (int i = 0; i < nnodeMap.getLength(); i++)
			  {
				  Node attNode = nnodeMap.item(i);
				  result += " " + (attNode.getNodeName()) + "=\"" + attNode.getNodeValue() + "\"";
//				  System.out.println("----------\n"+result+"\n------------");
			  }
			  result += ">";
//			  System.out.println("----------\n"+result+"\n------------");
			  Node child = currNode.getFirstChild();
			  while (child != null)
			  {
				  String childStr = encode(child);
				  result += childStr;
//				  System.out.println("----------\n"+result+"\n------------");
				  child = child.getNextSibling();
			  }
			  result += "</" + currNode.getNodeName() + ">";
//			  System.out.println("----------\n"+result+"\n------------");
			  return result;
		  }
		  case Node.TEXT_NODE:
		  case Node.CDATA_SECTION_NODE:
		  {
			  String reservedChars = "<>&'\"";
			  String str = currNode.getNodeValue();
			  boolean bSpecialChars = false;
			  int len = str.length();
			  for (int i = 0; i < len; i++)
			  {
				  if (reservedChars.indexOf(str.charAt(i)) != -1)
				  {
					  bSpecialChars = true;
					  break;
				  }
			  }
			  if (bSpecialChars == false)
			  {
				  result += str;
//	 System.out.println("----------\n"+result+"\n------------");
			  }
			  else
			  {
				  result += "<![CDATA[" + str + "]]>";
//				  System.out.println("----------\n"+result+"\n------------");
			  }
			  return result;
		  }
		  default:
		  {
			  return result;
		  }
	  }
  }


  //======================================================================
  //======================================================================
  public String Xencode()
  {
	if (mDoc == null)
	  return null;

	try
	{
	  if (mRootNode != mDoc.getDocumentElement())
	  {
		  return null;
	  }
	  XMLSerializer xmlS = new XMLSerializer();
	  ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
	  xmlS.setOutputByteStream(outputStream);
	  xmlS.serialize(mDoc);
	  return outputStream.toString();
	}
	catch (Throwable e)
	{
	  e.printStackTrace();
	}
	return null;
  }

  //======================================================================
  //======================================================================
  public boolean decode(String xmlString, String name)
  {
	try
	{
	  ByteArrayInputStream inputStream = new ByteArrayInputStream(xmlString.getBytes());
	  InputSource inputSource = new InputSource(inputStream);
	  mReader.parse(inputSource);
	  mDoc = mReader.getDocument();
	  if (mDoc != null)
	  {
		mRootNode = mDoc.getDocumentElement();
		if (mRootNode.getNodeName().compareToIgnoreCase(name) != 0)
		{ // Wrong Document
		  mDoc = null;
		  mRootNode = null;
		}
	  }
	}
	catch (Exception e)
	{
	  e.printStackTrace();
	}
	return mDoc != null;
  }


  //======================================================================
  //======================================================================
  public String getString(String path)
  {
	  return getString(path, (DataTypeAttribute[])null);
  }
  public String getString(String path, DataTypeAttribute dtAttribute)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return getString(path, dtAttributes);
  }
  public String getString(String path, DataTypeAttribute[] dtAttributes)
  {
	  return getValue(mRootNode, path, dtAttributes);
  }

  public boolean setString(String path, String value)
  {
	  return setString(path, (DataTypeAttribute[])null, value);
  }
  public boolean setString(String path, DataTypeAttribute dtAttribute, String value)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return setString(path, dtAttributes, value);
  }
  public boolean setString(String path, DataTypeAttribute[] dtAttributes, String value)
  {
	  return setValue(mRootNode, path, dtAttributes, value);
  }


  public Date getDate(String path)
  {
	  return getDate(path, (DataTypeAttribute[])null);
  }
  public Date getDate(String path, DataTypeAttribute dtAttribute)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return getDate(path, dtAttributes);
  }
  public Date getDate(String path, DataTypeAttribute[] dtAttributes)
  {
	  DataTypeDate dtDate = new DataTypeDate();
	  return (Date)dtDate.decode(getValue(mRootNode, path, dtAttributes));
  }

  public boolean setDate(String path, Date value)
  {
	  return setDate(path, (DataTypeAttribute[])null, value);
  }
  public boolean setDate(String path, DataTypeAttribute dtAttribute, Date value)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return setDate(path, dtAttributes, value);
  }
  public boolean setDate(String path, DataTypeAttribute[] dtAttributes, Date value)
  {
	  DataTypeDate dtDate = new DataTypeDate();
	  return setValue(mRootNode, path, dtAttributes, dtDate.encode(value));
  }


  public Integer getInteger(String path)
  {
	  return getInteger(path, (DataTypeAttribute[])null);
  }
  public Integer getInteger(String path, DataTypeAttribute dtAttribute)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return getInteger(path, dtAttributes);
  }
  public Integer getInteger(String path, DataTypeAttribute[] dtAttributes)
  {
	  DataTypeInt dtInt = new DataTypeInt();
	  return (Integer)dtInt.decode(getValue(mRootNode, path, dtAttributes));
  }

  public boolean setInteger(String path, Integer value)
  {
	  return setInteger(path, (DataTypeAttribute[])null, value);
  }
  public boolean setInteger(String path, DataTypeAttribute dtAttribute, Integer value)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return setInteger(path, dtAttributes, value);
  }
  public boolean setInteger(String path, DataTypeAttribute[] dtAttributes, Integer value)
  {
	  DataTypeInt dtInteger = new DataTypeInt();
	  return setValue(mRootNode, path, dtAttributes, dtInteger.encode(value));
  }


  public Long getLong(String path)
  {
	  return getLong(path, (DataTypeAttribute[])null);
  }
  public Long getLong(String path, DataTypeAttribute dtAttribute)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return getLong(path, dtAttributes);
  }
  public Long getLong(String path, DataTypeAttribute[] dtAttributes)
  {
	  DataTypeLong dtLong = new DataTypeLong();
	  return (Long)dtLong.decode(getValue(mRootNode, path, dtAttributes));
  }

  public boolean setLong(String path, Long value)
  {
	  return setLong(path, (DataTypeAttribute[])null, value);
  }
  public boolean setLong(String path, DataTypeAttribute dtAttribute, Long value)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return setLong(path, dtAttributes, value);
  }
  public boolean setLong(String path, DataTypeAttribute[] dtAttributes, Long value)
  {
	  DataTypeLong dtLong = new DataTypeLong();
	  return setValue(mRootNode, path, dtAttributes, dtLong.encode(value));
  }


  public byte[] getBytes(String path)
  {
	  return getBytes(path, (DataTypeAttribute[])null);
  }
  public byte[] getBytes(String path, DataTypeAttribute dtAttribute)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return getBytes(path, dtAttributes);
  }
  public byte[] getBytes(String path, DataTypeAttribute[] dtAttributes)
  {
	  DataTypeByteArray dtByteArray = new DataTypeByteArray();
	  return (byte[])dtByteArray.decode(getValue(mRootNode, path, dtAttributes));
  }

  public boolean setBytes(String path, byte[] value)
  {
	  return setBytes(path, (DataTypeAttribute[])null, value);
  }
  public boolean setBytes(String path, DataTypeAttribute dtAttribute, byte[] value)
  {
	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[1];
	  dtAttributes[0] = dtAttribute;
	  return setBytes(path, dtAttributes, value);
  }
  public boolean setBytes(String path, DataTypeAttribute[] dtAttributes, byte[] value)
  {
	  DataTypeByteArray dtByteArray = new DataTypeByteArray();
	  return setValue(mRootNode, path, dtAttributes, dtByteArray.encode(value));
  }


  //======================================================================
  //======================================================================
  public DataTypeAttribute[] getAttributeList(String path)
  {
	  if (mDoc == null)
		  return null;

	  if (path == null)
		  return null;

	  Node child = getNode(mRootNode, path, null);
	  if (child == null)
		  return null;

	  NamedNodeMap nnodeMap = child.getAttributes();
	  int len = nnodeMap.getLength();
	  if (len == 0)
		  return null;

	  DataTypeAttribute dtAttributes[] = new DataTypeAttribute[len];
	  for (int i = 0; i < len; i++)
	  {
		  Node attNode = nnodeMap.item(i);
		  dtAttributes[i] = new DataTypeAttribute(attNode.getNodeName(), attNode.getNodeValue());
	  }
	  return dtAttributes;
  }

  public String getAttributeValue(String path, String attributeName)
  {
	  if (attributeName == null)
		  return null;

	  DataTypeAttribute dtAttributes[] = getAttributeList(path);
	  if (dtAttributes == null)
		  return null;

	  for (int i = 0; i < dtAttributes.length; i++)
		  if (dtAttributes[i].getName().compareToIgnoreCase(attributeName) == 0)
			  return dtAttributes[i].getValue();

	  return null;
  }

  //======================================================================
  //======================================================================
  public XMLDocument getSubDoc(String path)
  {
	if (mDoc == null)
	  return null;
	return getSubDoc(mRootNode, path);
  }


  //======================================================================
  //======================================================================
  public Vector getDocList(String name)
  {
	if (mDoc == null)
	  return null;

	NodeIterator ni = ((DocumentTraversal)mDoc).createNodeIterator(
		mRootNode, NodeFilter.SHOW_ELEMENT, new ListNodeFilter(name), true);

	Node n;
	Vector v = new Vector();
	while ((n = ni.nextNode()) != null)
	  v.add(new XMLDocument(this, n));

	return v;
  }

  //======================================================================
  //======================================================================
  public XMLDocument Clone()
  {
	if (mDoc == null || mRootNode == null)
	  return null;
	Node newNode = clone(mRootNode);
	if (newNode != null)
	{
	   if (mRootNode != mDoc.getDocumentElement())
		 mRootNode.getParentNode().appendChild(newNode);
	   return new XMLDocument(this, newNode);
	}
	return null;
  }

  //======================================================================
  //======================================================================
  public XMLDocument remove(String path)
  {
	  XMLDocument pGone = getSubDoc(mRootNode, path);
	  if (pGone == null)
	   return null;

   pGone.mRootNode.getParentNode().removeChild(pGone.mRootNode);
   return pGone;
  }

  //======================================================================
  //======================================================================
  public boolean add(String path,XMLDocument doc)
  {
	  XMLDocument pGone = getSubDoc(mRootNode, path);
	  if (pGone == null)
	   return false;

   pGone.mRootNode.appendChild(doc.mRootNode);
   return true;
  }

  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  private Node clone(Node currNode)
  {
	  short nType = currNode.getNodeType();
	  switch (currNode.getNodeType())
	  {
		  case Node.ELEMENT_NODE:
			  Element elem = mDoc.createElement(currNode.getNodeName());
			  NamedNodeMap nnodeMap = currNode.getAttributes();
			  for (int i = 0; i < nnodeMap.getLength(); i++)
			  {
				  Node attNode = nnodeMap.item(i);
				  elem.setAttribute(attNode.getNodeName(), attNode.getNodeValue());
			  }
			  Node child = currNode.getFirstChild();
			  while (child != null)
			  {
				  Node cNode = clone(child);
				  if (cNode != null)
					  elem.appendChild(cNode);
				  child = child.getNextSibling();
			  }
			  return elem;
		  case Node.TEXT_NODE:
			  Text childText = mDoc.createTextNode(currNode.getNodeValue());
			  return (Node)childText;
		  case Node.CDATA_SECTION_NODE:
			  CDATASection childCData = mDoc.createCDATASection(currNode.getNodeValue());
			  return (Node)childCData;
		  default:
			  return null;
	  }
  }

  //======================================================================
  //======================================================================
  private boolean doAttributesMatch(Node currNode, DataTypeAttribute[] dtAttributes)
  {
	  NamedNodeMap nnodeMap = currNode.getAttributes();
	  int len = nnodeMap.getLength();


	  for (int a = 0; a < dtAttributes.length; a++)
	  {
		  boolean isFound = false;
		  DataTypeAttribute dtAttribute = dtAttributes[a];
		  for (int i = 0; i < len && !isFound; i++)
		  {

			  Node attNode = nnodeMap.item(i);
			  if (dtAttribute.getName().compareToIgnoreCase(attNode.getNodeName()) == 0 &&
				  dtAttribute.getValue().compareToIgnoreCase(attNode.getNodeValue()) == 0)
			  {
				  isFound = true;
			  }
		  }
		  if (!isFound)
			  return false;
	  }

	  return true;
  }

  private Node getNode(Node currNode, String path, DataTypeAttribute[] dtAttributes)
  {
	if (path == null)
		return null;

	String currName = currNode.getNodeName();
	if (currName.compareToIgnoreCase(path) == 0 && (dtAttributes == null || doAttributesMatch(currNode, dtAttributes)))
		return currNode;

	int iDot = path.indexOf('.');
	String pathName;
	if (iDot == -1)
	  pathName = path;
	else
	  pathName = path.substring(0, iDot);

	Node child = currNode.getFirstChild();
	while (child != null)
	{
//String childName = child.getNodeName();
	  if (child.getNodeType() != Node.ELEMENT_NODE)
	  {
		child = child.getNextSibling();
		continue;
	  }

	  if (pathName.compareToIgnoreCase(child.getNodeName()) == 0)
	  {
		  if (iDot != -1)
			return getNode(child, path.substring(iDot+1), dtAttributes);

		  if (dtAttributes != null)
		  {
			if (!doAttributesMatch(child, dtAttributes))
			{
			  child = child.getNextSibling();
			  continue;
			}
		  }

		  return child;
	  }

	  child = child.getNextSibling();
	}
	return null;
  }


  //======================================================================
  //======================================================================
  private String getValue(Node currNode, String path, DataTypeAttribute[] dtAttributes)
  {
	if (mDoc == null)
		return null;

	if (path == null)
		return null;

	Node child = getNode(currNode, path, dtAttributes);
	if (child == null)
		return null;

	child = child.getFirstChild();
	if (child == null)
		return null;

	// If siblings exist, this is not an leaf, but a branch
	Node sib  = child.getNextSibling();
	if (sib != null)
		return null;

	if (child.getNodeType() != Node.TEXT_NODE && child.getNodeType() != Node.CDATA_SECTION_NODE)
		return null;

	return child.getNodeValue();
  }


  //======================================================================
  //======================================================================
  private boolean setValue(Node currNode, String path, DataTypeAttribute[] dtAttributes, String value)
  {
	if (mDoc == null)
		return false;

	if (path == null)
		return false;

	Node child = getNode(currNode, path, dtAttributes);
	if (child == null)
		return false;
	Node parent = child.getParentNode();
	if (parent == null)
		return false;

	Node grandChild = child.getFirstChild();
	short nType = Node.TEXT_NODE;
	if (grandChild != null)
	{
		nType = grandChild.getNodeType();
		if (nType != Node.TEXT_NODE && nType != Node.CDATA_SECTION_NODE)
			return false;
	}

	String childName = child.getNodeName();
	NamedNodeMap nnodeMap = child.getAttributes();

	parent.removeChild(child);
	Element childElement = mDoc.createElement(childName);
	for (int i = 0; i < nnodeMap.getLength(); i++)
	{
		Node attNode = nnodeMap.item(i);
		childElement.setAttribute(attNode.getNodeName(), attNode.getNodeValue());
	}

	if (value == null)
		value = "";
	if (nType == Node.TEXT_NODE)
	{
	  Text childText = mDoc.createTextNode(value);
	  childElement.appendChild(childText);
	}
	else
	{
	  CDATASection childCData = mDoc.createCDATASection(value);
	  childElement.appendChild(childCData);
	}
	parent.appendChild(childElement);

	return true;
  }

  //======================================================================
  //======================================================================
  private XMLDocument getSubDoc(Node currNode, String path)
  {
	if (path == null)
			return null;

	Node child = getNode(currNode, path, null);
	if (child == null)
		return null;

	return new XMLDocument(this, child);
  }


  //======================================================================
  //======================================================================
  private class ListNodeFilter implements NodeFilter
  {
	private String mNodeName;

	public ListNodeFilter(String name)
	{
	  mNodeName = name;
	}

	public short acceptNode(Node n)
	{
	  if (n.getNodeType() == Node.ELEMENT_NODE && n.getNodeName().compareToIgnoreCase(mNodeName) == 0)
		  return FILTER_ACCEPT;

	  // Not interested
	  return FILTER_SKIP;
	}
  }
/*
  //======================================================================
  // CJM 4/17/03 ..Needed to update an attribute list... for ContentGuard
  //======================================================================
  public boolean setAttributeList(String path, DataTypeAttribute[] dtAttributes)
  {
	  if (mDoc == null)
	   return false;

   if (path == null)
	   return false;

   Node child = getNode(mRootNode, path, null);
   String value = getString(path);

   if (child == null)
	   return false;

   short nType = child.getNodeType();

   Node parent = child.getParentNode();
   if (parent == null)
	   return false;

   String childName = child.getNodeName();//.transcode();
   NamedNodeMap nnodeMap = child.getAttributes();

   parent.removeChild(child);
   Element childElement = mDoc.createElement(childName);

   int a = 0;
   DataTypeAttribute dtAttribute;
   while ((dtAttribute = dtAttributes[a++]) != null)
   {

	   childElement.setAttribute(dtAttribute.getName(), dtAttribute.getValue());
   }
   if (nType == Node.TEXT_NODE)
   {
	   Text childText = mDoc.createTextNode((value == null)?"":value);
	   childElement.appendChild(childText);
   }
   else
   {
	   if (nType == Node.CDATA_SECTION_NODE)
	   {
		   CDATASection childCData = mDoc.createCDATASection((value == null)?"":value);
		   childElement.appendChild(childCData);
	   }
   }
   parent.appendChild(childElement);

   return true;

  }
  //======================================================================
  //======================================================================
  public static void main(String[] args)
  {
	  ///** initialize the templatestr note: these values will get overwritten
	  String m_QueryRELTemplate=
			  "<?xml version=\"1.0\"?>"
			  +"<query xmlns=\"http://www.contentguard.com/2002/exampleQueryNS\">"
			  +"<goalToCheck>"
			  +"<principalToCheck rsaModulus=\"XXXXXXXX\" rsaExponent=\"XX\"/>"
			  +"<rightToCheck>"
			  +"<mx:play xmlns:mx=\"urn:mpeg:mpeg21:2002:01-REL-NS\"/>"
			  +"</rightToCheck>"
			  +"<resourceToCheck uri=\"10.9901/12.i.2\"/>"
			  +"</goalToCheck>"
			  +"<simulationExerciseEnvironment>"
			  +"<time>YYYY-MM-DDT00:00:00</time>"
			  +"</simulationExerciseEnvironment>"
			  +"</query>";
	  XMLDocument queryDoc=new XMLDocument();

	  if (!(queryDoc.decode(m_QueryRELTemplate, "query")))
	  {
		  System.out.println("MPEGRELLicense::verifyPermissions : Unable to Decode QueryDoc.");
		  return;
	  }

	  String pModulus="joe";
	  String pExponent="gerard";
	  String p_Resource="nelson";
	  DataTypeAttribute modulusAttr=new DataTypeAttribute("rsaModulus", pModulus);
	  DataTypeAttribute exponentAttr=new DataTypeAttribute("rsaExponent", pExponent);
	  DataTypeAttribute doiAttr=new DataTypeAttribute("uri", p_Resource);

	  DataTypeAttribute principalAttList[] = { modulusAttr, exponentAttr, null };
	  DataTypeAttribute doiAttList[] = { doiAttr,null };

	  queryDoc.setAttributeList("goalToCheck.principalToCheck", principalAttList);
	  queryDoc.setAttributeList("goalToCheck.resourceToCheck", doiAttList);
	  System.out.println( queryDoc.encode());
  }
*/
}
