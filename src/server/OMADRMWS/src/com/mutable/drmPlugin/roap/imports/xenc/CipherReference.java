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
package com.mutable.drmPlugin.roap.imports.xenc;

import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IXmlChild;

public class CipherReference  {
	
	protected XencTransforms transforms;
	protected UriValue uri;

	public String XmlEncode() {
		// TODO Auto-generated method stub
		return null;
	}

	public String XmlEncode(String varName) {
		// TODO Auto-generated method stub
		return null;
	}

	/**
	 * 
	 * @param transforms is an optional element, and
	 * @param uri is a required attribute
	 */
	public CipherReference(XencTransforms transforms, UriValue uri) {
		super();
		if (uri==null) throw new IllegalArgumentException();
		this.transforms = transforms;
		this.uri = uri;
	}

	public XencTransforms getTransforms() {
		return transforms;
	}

	public UriValue getUri() {
		return uri;
	}

}
