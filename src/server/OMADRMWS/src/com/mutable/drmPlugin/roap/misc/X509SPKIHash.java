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

import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;

public class X509SPKIHash extends HashAbstract {
	

	public boolean equals(Object o) {
	    if (!X509SPKIHash.class.isInstance(o)) return false;
		return hash.equals(((X509SPKIHash)o).getHash());
	}

	
	public X509SPKIHash(Base64String hash) {
		super(hash);
	}

	public X509SPKIHash(Base64String hash, UriValue algorithm ) {
		super(hash,algorithm);
	}
	
	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		newElem.addAttribute("xsi:type","roap:X509SPKIHash");
		return newElem;
	}

	public static X509SPKIHash instanceFromDomElement(IElement elem) {
		UriValue algo = new UriValue(elem.getAttributeStringValue("algorithm"));
		Base64String hash = new Base64String(elem.getChildStringValue("hash"));
		return new X509SPKIHash(hash,algo);
	}
	public String domName() { return "keyIdentifier"; }

}
