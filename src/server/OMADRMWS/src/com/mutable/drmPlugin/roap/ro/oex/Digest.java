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
package com.mutable.drmPlugin.roap.ro.oex;

import com.mutable.drmPlugin.roap.imports.ds.DigestMethod;
import com.mutable.drmPlugin.roap.imports.ds.DigestValue;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;


public class Digest extends XmlChild {
	protected DigestValue digestValue;


	
	public String XmlEncode() {
		// TODO Auto-generated method stub
		return null;
	}

	public String XmlEncode(String varName) {
		// TODO Auto-generated method stub
		return null;
	}

	public Digest(DigestValue value) {
		super();
		if (value==null) throw new IllegalArgumentException();
		digestValue = value;
	}

	public DigestValue getDigestValue() {
		return digestValue;
	}
	public DigestMethod getDigestMethod() {
		return new DigestMethod("http://www.w3.org/2000/09/xmldsig#sha1");
	}
	
	public UriValue getAlgorithm() {
		return getDigestMethod().getAlgorithm();
	}
	
	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		getDigestMethod().asDomChildOf(newElem);
		newElem.addChildElement("DigestValue",getDigestValue().toString());
		return newElem;
	}
	
	public String domName() { return "digest"; }
	
	public static Digest instanceFromDomElement(IElement elem) {
		return new Digest(new DigestValue(elem.getChildStringValue("DigestValue")));
	}
	

}
