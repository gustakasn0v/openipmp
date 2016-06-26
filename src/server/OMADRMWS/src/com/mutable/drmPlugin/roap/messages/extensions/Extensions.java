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

import java.util.Vector;

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlVector;

/**
 * The common content of extension vectors of different Roap messages.
 * Validity is  ensured by  constructors of concrete subclasses.
 * 
 *
 */
public abstract class Extensions extends XmlVector {

	protected Extensions(Vector data) {
		super(data);
	}
	
	protected Extensions() {
		super();
	}
	
	
	public IElement asDomChildOf(IElement father) {
		return super.asDomChildOf(father,"extensions");
	}

	
	protected Class elementClass() { return Extension.class; }
	

}
