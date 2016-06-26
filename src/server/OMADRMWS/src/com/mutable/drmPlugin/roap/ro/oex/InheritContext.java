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

import com.mutable.drmPlugin.roap.ro.odd.InheritUid;
import com.mutable.drmPlugin.roap.ro.odd.Uids;
import com.mutable.drmPlugin.xml.IElement;

public class InheritContext extends Context {



	/**
	 * defaults are fine here, since the only constructor
	 * will impose validity
	 */

	protected boolean validateUids(Uids u) {
		return true;
	}
	
	/**
	 * according to OMA-DRM-REL_V2_0-20041210C p.10
	 * version should be absent and the single uid
	 * should be an InheritUid
	 * 
	 */
	public InheritContext(InheritUid uid) {
		super(null, new Uids(uid));
	}
	public static InheritContext instanceFromDomElement(IElement elem) {
		Uids uids = Uids.instanceFromDomElement(elem);
		return new InheritContext((InheritUid)uids.getData().firstElement());
	}

}
