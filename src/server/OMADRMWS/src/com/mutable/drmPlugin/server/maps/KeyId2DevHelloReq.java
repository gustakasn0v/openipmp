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

import com.mutable.drmPlugin.server.DeviceContext;
import com.mutable.drmPlugin.tools.TypedMap;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.roap.messages.*;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;

public class KeyId2DevHelloReq extends TypedMap {

	public KeyId2DevHelloReq() {
		super();
		// TODO Auto-generated constructor stub
	}

	public Class keyClass() {
		return RoapIdentifier.class;
	}

	public Class valClass() {
		return DeviceHelloRequest.class;
	}
	
	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */

	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("DeviceHelloRequests");
		for (Iterator i=map.keySet().iterator();i.hasNext();)
			((DeviceContext) get(i.next())).asDomChildOf(newElem);
		return newElem;
	}
	
	/**
	 * hook for ServerWithXml, not really needed for current Server
	 */

	public static KeyId2DevHelloReq instanceFromDomElement(IElement elem) {
		KeyId2DevHelloReq theMap = new KeyId2DevHelloReq();
		IElements elems = elem.getAllChildren();
		for (Iterator i=elems.iterator();i.hasNext();) {
			DeviceHelloRequest req = DeviceHelloRequest.instanceFromDomElement((IElement)i.next());
			theMap.put((RoapIdentifier)req.getDeviceIds().getData().firstElement(),req);
		};
		return theMap;
		
	}

}
