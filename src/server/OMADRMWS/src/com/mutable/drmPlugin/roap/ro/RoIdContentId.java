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
package com.mutable.drmPlugin.roap.ro;

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlChild;




public class RoIdContentId extends XmlChild {

	protected IdValue id;
	protected UriVector contentIds;
	

	public RoIdContentId(IdValue id, UriVector ids) {
		super();
		contentIds = ids;
		this.id = id;
	}

	public UriVector getContentIds() {
		return contentIds;
	}

	public IdValue getId() {
		return id;
	}
	
	IElements asDomChildrenOf(IElement elem,String path) {
		Vector v = new Vector();
		v.add(elem.addChildElement(path,id.toString()));
		for(Iterator i=contentIds.iterator();i.hasNext();) 
			v.add(elem.addChildElement("contentID",i.next().toString()));
		return new IElements(v);
	}
	
	public String domName() { return "roID"; }
	
	


}
