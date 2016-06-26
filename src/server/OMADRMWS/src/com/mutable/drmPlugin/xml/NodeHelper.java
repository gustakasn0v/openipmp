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

import org.w3c.dom.Node;

import com.mutable.drmPlugin.tools.Base64String;

public class NodeHelper implements INode {

	protected Node domNode;
	
	public NodeHelper(Node node) {
		super();
		domNode = node;
	}

	public String getName() {
		return domNode.getNodeName();
	}


	public String getStringValue() {
		return  domNode.getNodeValue();
	}

	public boolean getBooleanValue() {
		String s = getStringValue();
		if (!s.equals("true") && !s.equals("false"))
			throw new XmlException();
		return s.equals("true");
	}

	public int getIntValue() {
		int i;
		try {
			i = Integer.parseInt(getStringValue());
		}
		catch (Exception e) {
			throw new XmlException();
		};
		return i;
	}

	public byte[] getBytesValue() {
		byte b[];
		try {
			b = (new Base64String(getStringValue())).asByteArray();
		}
		catch (Exception e) {
			throw new XmlException();
		};
		return b;
	}

	public boolean setStringValue(String v) {
		try {
			domNode.setNodeValue(v);
		}
		catch (Exception e) {
			return false;
		};
		return true;
	
	}

	public boolean setBooleanValue(boolean v) {
		return setStringValue(v ? "true" : "false");
	}

	public boolean setIntValue(int v) {
		return setStringValue(Integer.toString(v));
	}

	public boolean setBytesValue(byte[] v) {
		return setStringValue((new Base64String(v)).toString());
	}

	public IDocument getOwnerDocument() {
		return new DocumentHelper(domNode.getOwnerDocument());
	}

	public IElement getParentElement() {
		return new ElementHelper((org.w3c.dom.Element) domNode.getParentNode());

	}






}
