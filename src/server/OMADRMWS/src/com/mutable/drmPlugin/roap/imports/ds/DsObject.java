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

import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.StringValue;
import com.mutable.drmPlugin.tools.UriValue;

public abstract class DsObject extends java.lang.Object  {
	
	protected IdValue id;
	protected UriValue encoding;
	protected StringValue mimeType;


	public DsObject(IdValue id, UriValue uri, StringValue mime) {
		super();
		this.id = id;
		encoding = uri;
		mimeType = mime;
	}
	

	public IdValue getId() {
		return id;
	}

	public UriValue getEncoding() {
		return encoding;
	}
	
	public StringValue getMimeType() {
		return mimeType;
	}

}
