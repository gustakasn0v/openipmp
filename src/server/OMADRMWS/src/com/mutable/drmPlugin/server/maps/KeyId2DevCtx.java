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

import java.io.IOException;
import java.util.Iterator;

import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.server.DeviceContext;
import com.mutable.drmPlugin.tools.TypedMap;
import com.mutable.drmPlugin.xml.FactoryHelper;
import com.mutable.drmPlugin.xml.IDocument;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;

public class KeyId2DevCtx extends TypedMap {

	public KeyId2DevCtx() {
		super();
	}

	public Class keyClass() {
		return RoapIdentifier.class;
	}

	public Class valClass() {
		return DeviceContext.class;
	}
	
	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */
	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("DeviceContexts");
		for (Iterator i=map.keySet().iterator();i.hasNext();)
			((DeviceContext) get(i.next())).asDomChildOf(newElem);
		return newElem;
	}

	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */

	public static KeyId2DevCtx instanceFromDomElement(IElement elem) throws IOException {
		KeyId2DevCtx theMap = new KeyId2DevCtx();
		IElements elems = elem.getAllChildren();
		for (Iterator i=elems.iterator();i.hasNext();) {
			DeviceContext ctx = DeviceContext.instanceFromDomElement((IElement)i.next());
			theMap.put(ctx.getId(),ctx);
		};
		return theMap;
		
	}
	
	public static KeyId2DevCtx instanceFromFile(String path) throws IOException {
		IDocument doc = (new FactoryHelper()).fileInDocument(path);
		return instanceFromDomElement(doc.getRootElement());
	}
	

}
