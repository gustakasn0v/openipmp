/*
 * LICENSE AND COPYRIGHT INFORMATION:
 *
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 * 
 *
 */
package com.mutable.drmPlugin.xml;

import java.util.Iterator;
import java.util.Vector;

import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class ElementHelper extends NodeHelper implements IElement {
	
	public String getName() {
		return ((Element) domNode).getTagName();
	}


	public ElementHelper(Element e) {
		super(e);
	}


	public boolean addAttributeBase(String name, String value) {
		try {
			((Element) domNode).setAttribute(name,value);
		}
		catch (Exception e) { return false; };
		return true;
	}
	
	public IAttribute addAttribute(String name, String value) {
		if (!addAttributeBase(name,value)) return null;
		return getAttribute(name);
	}

	public IElement addChildElement(String path) {
		Element current =  (Element) domNode;
		try {
			java.util.StringTokenizer tk = new java.util.StringTokenizer(path,".");
			Document doc = domNode.getOwnerDocument();
			while (tk.hasMoreTokens()) {
				Node newNode = doc.createElement(tk.nextToken());
				current = (Element) current.appendChild(newNode);
			}
		} catch (Exception e) {
			throw new XmlException();
		};
		return new ElementHelper(current);
	}

	public IElement addChildElement(String path, String value) {
		IElement newElem = addChildElement(path);
		if (newElem==null || !newElem.setStringValue(value)) return null;
		return newElem;
	}

	public IAttribute getAttribute(String name) {
		Attr attribute = ((Element)domNode).getAttributeNode(name);
		return (attribute==null) ? null : new AttributeHelper(attribute);
	}

	public boolean getAttributeBooleanValue(String name) {
		IAttribute attr = getAttribute(name);
		if (attr==null) throw new XmlException();
		return attr.getBooleanValue() ;
	}

	public byte[] getAttributeBytesValue(String name) {
		IAttribute attr = getAttribute(name);
		return (attr==null) ? null : attr.getBytesValue() ;
	}

	public int getAttributeIntValue(String name) {
		IAttribute attr = getAttribute(name);
		if (attr==null) throw new XmlException();
		return attr.getIntValue() ;
	}

	public String getAttributeStringValue(String name) {
		IAttribute att = getAttribute(name);
		return (att==null) ? null : att.getStringValue() ;
		
	}

	public IElements getChildElements(String name) {
		IElements children = getAllChildren();
		Vector v = new Vector();
		for (Iterator i=children.iterator();i.hasNext();) {
			IElement current = (IElement)i.next();
			if (current.getName().equals(name))
				v.add(current);
		};
/*		NodeList theList = ((Element) domNode).getElementsByTagName(name);
		java.util.Vector v = new java.util.Vector();
		for (int i=0; i< theList.getLength(); i++)
			v.add(i, new ElementHelper((Element) theList.item(i)));
*/
		return new IElements(v);

	}

	public IElement getChildElement(String path) {
		Element current =  (Element) domNode;
		try {
			java.util.StringTokenizer tk = new java.util.StringTokenizer(path,".");
			while (tk.hasMoreTokens()) {
				IElements children = (new ElementHelper(current)).getChildElements(tk.nextToken());			
				if (children.getData().size() != 1) return null;
				current = (Element) ((ElementHelper) children.getData().firstElement()).domNode;
			}
		} catch (Exception e) {
			return null;
		};
		return new ElementHelper(current);

	}

	public String getChildStringValue(String path) {
		IElement child = getChildElement(path);
		return (child==null) ? null : child.getStringValue();
	}

	public boolean getChildBooleanValue(String path) {
		IElement child = getChildElement(path);
		if (child==null) throw new XmlException();
		return child.getBooleanValue();
	}

	public int getChildIntValue(String path) {
		IElement child = getChildElement(path);
		if (child==null) throw new XmlException();
		return child.getIntValue();
	}

	public byte[] getChildBytesValue(String path) {
		IElement child = getChildElement(path);
		return (child==null) ? null : child.getBytesValue();
	}

	public IAttribute getChildAttribute(String path, String name) {
		IElement child = getChildElement(path);
		return (child==null) ? null : child.getAttribute(name);
	}

	public String getChildAttributeStringValue(String path, String name) {
		IAttribute att = getChildAttribute(path,name);
		return (att==null) ? null : att.getStringValue() ;
	}

	public boolean getChildAttributeBooleanValue(String path, String name) {
		IAttribute att = getChildAttribute(path,name);
		if (att==null) throw new XmlException();
		return att.getBooleanValue();
	}

	public int getChildAttributeIntValue(String path, String name) {
		IAttribute att = getChildAttribute(path,name);
		if (att==null) throw new XmlException();
		return att.getIntValue();
	}

	public byte[] getChildAttributeBytesValue(String path, String name) {
		IAttribute att = getChildAttribute(path,name);
		return (att==null) ? null : att.getBytesValue();
	}


	public IElement getFirstChild() {
		Element first = (Element) domNode.getFirstChild();
		return (first==null) ? null : new ElementHelper(first);
	
	}

	public IElement getNextSibling() {
		Element next = (Element) domNode.getNextSibling();
		return (next==null) ? null : new ElementHelper(next);
	}

	public IElements getAllChildren() {
		NodeList theList = domNode.getChildNodes();
		java.util.Vector v = new java.util.Vector();
		for (int i=0; i<theList.getLength(); i++)
			if (theList.item(i).getNodeType()==Node.ELEMENT_NODE)
				v.add(new ElementHelper((Element) theList.item(i)));
		return new IElements(v);
	}


	public String getStringValue() {
		NodeList theList = domNode.getChildNodes();
		if (theList.getLength()==0) throw new XmlException();
		org.w3c.dom.Node child = theList.item(0);
		if (child.getNodeType()!=Node.CDATA_SECTION_NODE && child.getNodeType()!=Node.TEXT_NODE)
			throw new XmlException();
		return child.getNodeValue();
	}


	public boolean setStringValue(String v) {
//		if (getStringValue()==v) return true;
		NodeList theList = domNode.getChildNodes();
		if (theList.getLength()!=0) return false;
		String reservedChars = "<>&'"+String.valueOf('"');
		boolean isText = true;
		for (int i=0; i<v.length(); i++)
			if (reservedChars.indexOf(v.charAt(i))!=-1)
				isText=false;
		Node newChild = isText ? domNode.getOwnerDocument().createTextNode(v)
								: domNode.getOwnerDocument().createCDATASection(v);
		try {
			domNode.appendChild(newChild);
		} catch(Exception e) {
			return false;
		};
		return true;

	}

}
