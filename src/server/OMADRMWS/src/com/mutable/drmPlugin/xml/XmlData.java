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

/**
 * abstract functionality of an object which can externalize both as an xml element
 * of an encompassing document and as a stand-alone xml document
 * 
 * reuses the implementation of @see XmlDocument
 * 
 * subclasses need to implement abstract methods of @see XmlDocument
 * 
 * 
 *
 */

public abstract class XmlData extends XmlDocument implements IXmlChild {

	/**
	 * implementing @see IXmlChild
	 * 
	 */
	public IElement asDomChildOf(IElement father, String path) {
		IElement newElem = father.addChildElement(path);
		setDomElement(newElem);
		return newElem;
	}

	public IElement asDomChildOf(IElement father) {
		return asDomChildOf(father,domName());
	}
	
	public String domName() { return documentName(); }

}
