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

import com.mutable.drmPlugin.tools.*;
import com.mutable.drmPlugin.xml.*;

public class ContentIdHash2Key extends TypedMap {

	public ContentIdHash2Key() {
		super();
	}

	public Class keyClass() {
		return Base64String.class;
	}

	public Class valClass() {
		return Base64String.class;
	}
	
	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */

	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("ContentIdHash2Key");
		for (Iterator i=map.keySet().iterator();i.hasNext();) {
			Base64String key = (Base64String) i.next();
			key.asDomChildOf(newElem,"contentIdHash");
			newElem.addChildElement("key",((Base64String)map.get(key)).toString());
		}
		return newElem;
		
	}
	
	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */

	public static ContentIdHash2Key instanceFromDomElement(IElement elem) {
		ContentIdHash2Key theMap = new ContentIdHash2Key();
		IElements elems = elem.getAllChildren();
		for (Iterator i=elems.iterator(); i.hasNext();) {
			Base64String contentIdHash = new Base64String(((IElement)i.next()).getStringValue());
			if (!i.hasNext()) throw new XmlException();
			Base64String key = new Base64String(((IElement)i.next()).getStringValue());
			theMap.put(contentIdHash,key);
		};
		return theMap;
	}

}
