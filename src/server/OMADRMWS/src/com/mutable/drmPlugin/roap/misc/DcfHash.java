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
package com.mutable.drmPlugin.roap.misc;

import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.UriValue;

public class DcfHash extends HashAbstract {

	protected Base64String hash;
	protected UriValue algorithm;


	public DcfHash(Base64String hash) {
		super(hash);
	}

	public DcfHash(Base64String hash,UriValue algorithm) {
		super(hash,algorithm);
	}

	public String domName() {
		return "dcfHash";
	}



	public boolean equals(Object o) {
	    if (!DcfHash.class.isInstance(o)) return false;
		return hash.equals(((DcfHash)o).getHash());
	}




}
