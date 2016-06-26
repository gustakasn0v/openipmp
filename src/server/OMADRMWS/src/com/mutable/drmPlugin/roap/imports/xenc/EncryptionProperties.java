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

import java.util.Vector;

import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.xml.XmlVector;

/**
 * VectorValue holding EncryptionProperty values
 * @see EncryptionProperty
 * 
 *
 */

public class EncryptionProperties extends XmlVector {
	
	protected IdValue id;

	protected Class elementClass() { return EncryptionProperty.class; }



	
	public EncryptionProperties(Vector data, IdValue id) {
		super(data);
		// TODO Auto-generated constructor stub
		this.id = id;
	}

	public IdValue getId() {
		return id;
	}
	
	public Vector getProperties() {
		return getData();
	}

}
