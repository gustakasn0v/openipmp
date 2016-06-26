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

import java.util.*;
import com.mutable.drmPlugin.roap.ro.odd.SystemUid;
import com.mutable.drmPlugin.roap.ro.odd.Uids;
import com.mutable.drmPlugin.roap.ro.odd.Version;
import com.mutable.drmPlugin.xml.IElement;

public class SystemContext extends Context {

	public SystemContext(Version v, Uids u) {
		super(v, u);
		// TODO Auto-generated constructor stub
	}


	protected boolean validateUids(Uids u) {
		if (u!=null ) 
			for (Iterator i=u.iterator(); i.hasNext();)
				if (!(i.next() instanceof SystemUid))
					return false;
		return true;	
	}
	
	public static SystemContext instanceFromDomElement(IElement elem) {
		return new SystemContext(
				Version.instanceFromDomElement(elem.getChildElement("version")),
				Uids.instanceFromDomElement(elem));
	}


}
