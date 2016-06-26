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

public class RetrievalMethod implements BasicKeyInfo {
	
	protected Transforms tr;
	protected UriValue uri, type;



	/**
	 * 
	 * @param tr is an optional element
	 * @param type is an optional attribute
	 * @param uri is a required attribute
	 */
	public RetrievalMethod(Transforms tr, UriValue type, UriValue uri) {
		super();
		if (uri==null) 
			throw new IllegalArgumentException();
		this.tr = (tr==null ? null : (Transforms) tr.nonEmptyOrNull());
		this.type = type;
		this.uri = uri;
	}

	public Transforms getTr() {
		return tr;
	}

	public UriValue getType() {
		return type;
	}

	public UriValue getUri() {
		return uri;
	}

}
