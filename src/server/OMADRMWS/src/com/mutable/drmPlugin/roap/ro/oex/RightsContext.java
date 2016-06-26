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

import com.mutable.drmPlugin.roap.ro.odd.RightsUid;
import com.mutable.drmPlugin.roap.ro.odd.Uids;
import com.mutable.drmPlugin.roap.ro.odd.Version;
import com.mutable.drmPlugin.xml.IElement;

public class RightsContext extends Context {

	public RightsContext(Version v, Uids u) {
		super(v, u);
	}



	
	protected boolean validateVersion(Version v) {
		return super.validateVersion(v) || v.equals(new Version("2.0"));
	}
	
	protected boolean validateUids(Uids u) {
		if (!super.validateUids(u)) return false;
		if (u==null) return true;
		if (!u.getData().isEmpty()) 
			if (!(u.getData().firstElement() instanceof RightsUid))
					return false;
		return true;	
	}


	
	
	
	public static RightsContext instanceFromDomElement(IElement elem) {
		Uids uids = Uids.instanceFromDomElement(elem);
		String verString = elem.getChildStringValue("version");
		Version v = (verString==null) ? null : new Version(verString);
		return new RightsContext(v,uids);
	}


}
