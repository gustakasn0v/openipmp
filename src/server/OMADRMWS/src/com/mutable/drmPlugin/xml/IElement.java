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

public interface IElement extends INode {


	public IAttribute addAttribute(String name, String value);
	public IElement addChildElement(String path);
	public IElement addChildElement(String path, String value);
	public IAttribute getAttribute(String name);
	public String getAttributeStringValue(String name);
	public boolean getAttributeBooleanValue(String name);
	public int getAttributeIntValue(String name);
	public byte[] getAttributeBytesValue(String name);
	public IElements getChildElements(String name);
	public IElement getChildElement(String path);
	public String getChildStringValue(String path);
	public boolean getChildBooleanValue(String path);
	public int getChildIntValue(String path);
	public byte[] getChildBytesValue(String path);
	public IAttribute getChildAttribute(String path, String name);
	public String getChildAttributeStringValue(String path, String name);
	public boolean getChildAttributeBooleanValue(String path, String name);
	public int getChildAttributeIntValue(String path, String name);
	public byte[] getChildAttributeBytesValue(String path, String name);
	public IElement getFirstChild();
	public IElement getNextSibling();
	public IElements getAllChildren();


}
