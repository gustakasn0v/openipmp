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
package com.mutable.drmPlugin.xml;

import java.util.Vector;

import com.mutable.drmPlugin.tools.VectorValue;

/**
 * VectorValue holding IAttribute values
 * @see IAttribute
 * 
 *
 */
public class IAttributes extends VectorValue {

	public IAttributes(Vector data) {
		super(data);
		// TODO Auto-generated constructor stub
	}

	public IAttributes() {
		super();
		// TODO Auto-generated constructor stub
	}

	protected Class elementClass() {
		return IAttribute.class;
	}


}
