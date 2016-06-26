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
import com.mutable.drmPlugin.roap.ro.odd.*;
import com.mutable.drmPlugin.roap.ro.odd.Version;
import com.mutable.drmPlugin.xml.*;

public abstract class Context extends XmlChild {
	
	protected Version version;
	protected Uids uids;

	
	protected  boolean validateVersion(Version v) {
		return v==null;
	}
	protected  boolean validateUids(Uids u) {
		return (u==null || u.getData().size()<=1);
	}

	protected Context(Version v, Uids u) {
		super();
		if (!validateVersion(v) || !validateUids(u))
			throw new IllegalArgumentException();
		this.version = v;
		this.uids = u;
	}

	public Version getVersion() {
		return version;
	}

	public Uids getUids() {
		return uids;
	}
	
	public IElement asDomChildOf(IElement father,String name) {
		IElement newElem = super.asDomChildOf(father,name);
		if (version!=null) version.asDomChildOf(newElem);
		if (uids!=null)
			for(Iterator i=uids.iterator();i.hasNext();)
				((Uid)i.next()).asDomChildOf(newElem);
		return newElem;
	}
	
	public String domName() { return "context"; }

}
