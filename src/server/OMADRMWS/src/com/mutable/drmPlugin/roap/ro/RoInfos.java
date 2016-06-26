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
package com.mutable.drmPlugin.roap.ro;

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.roap.misc.DcfHash;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlException;
import com.mutable.drmPlugin.xml.XmlVector;

/**
 * VectorValue holding RoInfo values
 * @see RoInfo
 * 
 *
 */

public class RoInfos extends XmlVector {

	public RoInfos(Vector data) {
		super(data);
	}

	public RoInfos() {
		super();
	}

	protected Class elementClass() {
		return RoInfo.class;
	}

	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("roInfo");
		for(Iterator i=iterator();i.hasNext();) {
			RoInfo info = (RoInfo)i.next();
			newElem.addChildElement("roID",info.getRoId().toString());
			if (info.getDcfHash()!=null) info.getDcfHash().asDomChildOf(newElem);
		};
		return newElem;
	}
	
	public static RoInfos instanceFromDomElement(IElement elem) {
		IElements elems = elem.getAllChildren();
		Vector v = new Vector();
		IElement childElem = null;
		for(Iterator i = elems.iterator();i.hasNext()||childElem!=null;) {
			if (childElem==null) childElem = (IElement) i.next();
			if (!childElem.getName().equals("roID")) throw new XmlException();
			IdValue roId = new IdValue(childElem.getStringValue());
			DcfHash hash = null;
			childElem = null;
			if (i.hasNext()) {
				IElement peek = (IElement) i.next();
				if (peek.getName().equals("dcfHash")) {
					hash = new DcfHash(new Base64String(peek.getChildStringValue("hash")));
				} else childElem = peek;
			};
			v.add(new RoInfo(roId,hash));
		};
		return new RoInfos(v);
	}

}
