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
package com.mutable.drmPlugin.roap.misc;

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlVector;
/**
 * VectorValue holding KeyIdentifier values
 * @see KeyIdentifier
 * 
 *
 */

public class KeyIdentifiers extends XmlVector {

	protected Class elementClass() { return KeyIdentifier.class; }

	public KeyIdentifiers(Vector data) {
		super(data);
	}
	
	public KeyIdentifiers() { super(); }



	
	public Vector identifiers() { return getData(); }
	
	
	public static KeyIdentifiers instanceFromDomElement(IElement elem, String name) {
		IElements children = elem.getChildElements(name);
		Vector v = new Vector(); 
		if (children!=null) {
			for (Iterator i=children.iterator(); i.hasNext();) {
				v.add(X509SPKIHash.instanceFromDomElement(((IElement)i.next())));
			};
			return new KeyIdentifiers(v);
		};
		return null;
	}

}
