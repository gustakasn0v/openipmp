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
package com.mutable.drmPlugin.roap.ro.odd;

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlVector;

/**
 * VectorValue holding Uid values
 * @see Uid
 * 
 *
 */

public class Uids extends XmlVector {	
	
	protected Class elementClass() { return Uid.class; }

	
	

	public Uids(Vector data) {
		super(data);
		// TODO Auto-generated constructor stub
	}

	/**
	 * it will often be needed to construct
	 * a singleton Uids
	 * 
	 */
	
	public Uids(Uid anUid) {
		super();
		data.add(anUid);
	}

	
	public static Uids instanceFromDomElement(IElement elem) {
		if (elem==null) return null;
		IElements children = elem.getChildElements("uid");
		Vector v = new Vector();
		for(Iterator i=children.iterator();i.hasNext();)
			v.add(Uid.instanceFromDomElement((IElement)i.next()));
		return new Uids(v);
	}

}
