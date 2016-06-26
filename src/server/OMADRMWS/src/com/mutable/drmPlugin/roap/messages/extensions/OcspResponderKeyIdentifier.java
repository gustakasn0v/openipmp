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

import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.xml.*;


public class OcspResponderKeyIdentifier extends Extension {
	
	protected KeyIdentifier identifier;


	public OcspResponderKeyIdentifier(boolean cr, KeyIdentifier identifier) {
		super(cr);
		if (identifier==null) throw new IllegalArgumentException();
		this.identifier = identifier;
	}

	public KeyIdentifier getIdentifier() {
		return identifier;
	}
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = super.asDomChildOf(father);
		((X509SPKIHash)getIdentifier()).asDomChildOf(newElem);
		return newElem;
	}
	
	public static OcspResponderKeyIdentifier instanceFromDomElement(IElement elem) {
		boolean cr = elem.getAttributeBooleanValue("critical");
		X509SPKIHash kid = X509SPKIHash.instanceFromDomElement(elem.getChildElement("identifier"));
		return new OcspResponderKeyIdentifier(cr,kid);
	}

	protected String xsiType() {
		return "roap:OcspResponderKeyIdentifier";
	}

}
