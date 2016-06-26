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

import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IXmlChild;

public abstract class EncryptionMethod implements IXmlChild {
	
	protected KeySize keySize;
	protected Base64String oaepParams;
	protected UriValue algorithm;



	/**
	 * 
	 * @param size and @param params are optional elements, and
	 * @param algorithm is a required attribute
	 */
	public EncryptionMethod(KeySize size, Base64String params, 
								UriValue algorithm) {
		super();
		if (algorithm==null) throw new IllegalArgumentException();
		this.algorithm = algorithm;
		keySize = size;
	}

	public UriValue getAlgorithm() {
		return algorithm;
	}

	public KeySize getKeySize() {
		return keySize;
	}
	
	public Base64String getOaepParams() {
		return oaepParams;
	}

}
