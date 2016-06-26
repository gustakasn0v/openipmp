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
package com.mutable.drmPlugin.roap.messages.extensions;

import java.util.Iterator;

import com.mutable.drmPlugin.tools.StringVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;

public class DomainNameWhiteList extends Extension {
	
	StringVector theList;


	public DomainNameWhiteList(boolean cr, StringVector list) {
		super(cr);
		if (list==null || list.isEmpty() || list.getData().size()>5)
			throw new IllegalArgumentException();
		theList = list;
	}
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = super.asDomChildOf(father);
		for (Iterator i=theList.iterator();i.hasNext();)
			newElem.addChildElement("dn",(String)i.next());
		return newElem;
	}
	
	public static DomainNameWhiteList instanceFromDomElement(IElement elem) {
		StringVector list = new StringVector();
		java.util.Vector vec = list.getData();
		IElements children = elem.getChildElements("dn");
		for (Iterator i=children.iterator();i.hasNext();)
			vec.add(((IElement)i.next()).getStringValue());
		return new DomainNameWhiteList(elem.getAttributeBooleanValue("critical"),list);
			
	}

	protected String xsiType() {
		return "roap:DomainNameWhiteList";
	}

}
