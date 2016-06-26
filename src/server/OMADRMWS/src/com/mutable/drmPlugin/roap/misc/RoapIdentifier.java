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

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;


public class RoapIdentifier extends XmlChild {
	
	protected KeyIdentifier identifier;

	public RoapIdentifier() {
		super();
	}

	
	
	public boolean equals(Object o) {
		if (!RoapIdentifier.class.isInstance(o)) return false;
		return identifier.equals(((RoapIdentifier)o).getIdentifier());
	}

	
	
	public int hashCode() {
		return identifier.hashCode();
	}
	
	
	public RoapIdentifier(KeyIdentifier identifier) {
		super();
		this.identifier = identifier;
	}

	public KeyIdentifier getIdentifier() {
		return identifier;
	}
	
	public IElement asDomChildOf(IElement father, String name) {
		IElement newElem = super.asDomChildOf(father,name);
		getIdentifier().asDomChildOf(newElem);
		return newElem;
	}
	
	public static RoapIdentifier instanceFromDomElement(IElement elem) {
		return new RoapIdentifier(X509SPKIHash.instanceFromDomElement(elem.getFirstChild()));
	}
	
	/**
	 * the following is a silly default, RoapIdentifier will also be used
	 * at least as riID too
	 */
	public String domName() { return "deviceID"; }

	public String toString() { return identifier.toString(); }

}
