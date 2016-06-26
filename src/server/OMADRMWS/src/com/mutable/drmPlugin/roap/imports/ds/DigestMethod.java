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
package com.mutable.drmPlugin.roap.imports.ds;

import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;

public class DigestMethod extends UriValue {

	public DigestMethod(String data) {
		super(data);
		// TODO Auto-generated constructor stub
	}

	public DigestMethod() {
		this("http://www.w3.org./2000/09/xmldsig#sha1");
	}

	
	public UriValue getAlgorithm() {
		return new UriValue(getData());
	}
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("DigestMethod");
		newElem.addAttribute("Algorithm",getAlgorithm().toString());
		return newElem;
	}
	
	public static DigestMethod instanceFromDomElement(IElement elem) {
		return new DigestMethod(elem.getAttributeStringValue("Algorithm"));
	}
	
}
