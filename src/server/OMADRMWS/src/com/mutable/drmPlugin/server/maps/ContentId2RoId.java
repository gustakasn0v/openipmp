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
package com.mutable.drmPlugin.server.maps;

import java.util.Iterator;

import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.TypedMap;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlException;

public class ContentId2RoId extends TypedMap {

	public ContentId2RoId() {
		super();
		// TODO Auto-generated constructor stub
	}

	public Class keyClass() {
		return UriValue.class;
	}

	public Class valClass() {
		return IdValue.class;
	}

	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */

	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("ContentId2RoId");
		for (Iterator i=map.keySet().iterator();i.hasNext();) {
			UriValue key = (UriValue) i.next();
			key.asDomChildOf(newElem,"contentId");
			newElem.addChildElement("roId",((IdValue)map.get(key)).toString());
		};
		return newElem;
		
	}
	
	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */

	public static ContentId2RoId instanceFromDomElement(IElement elem) {
		ContentId2RoId theMap = new ContentId2RoId();
		IElements elems = elem.getAllChildren();
		for (Iterator i=elems.iterator();i.hasNext();) {
			UriValue contentId = new UriValue(((IElement)i.next()).getStringValue());
			if (!i.hasNext()) throw new XmlException();
			IdValue roId = new IdValue(((IElement)i.next()).getStringValue());
			theMap.put(contentId,roId);
		};
		return theMap;
	}

}
