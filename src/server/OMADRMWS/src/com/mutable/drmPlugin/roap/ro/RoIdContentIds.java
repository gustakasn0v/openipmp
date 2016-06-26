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
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlVector;

/**
 * VectorValue holding RoIdContentId values
 * @see RoIdContentId
 * 
 *
 */

public class RoIdContentIds extends XmlVector {

	protected Class elementClass() {
		return RoIdContentId.class;
	}


	public RoIdContentIds(Vector data) {
		super(data);
	}

	public RoIdContentIds() {
		super();
	}
	
	/**
	 * You don't want to see the code here. In view of brain-damaged OMADRM formatting,
	 * ignoring happily the structuring
	 * capabilities and intents of xml - a roId followed by one or more contentIds
	 * followed possibly by another roId followed by... - all flattened, there is no 
	 * high-level way to parse the mess.
	 * 
	 */
	public static RoIdContentIds instanceFromDomElement(IElement elem) {
		IElement first = elem.getFirstChild();
		Vector vall = new Vector();
		for(IElement current=first; !current.getName().equals("roID");current=current.getNextSibling()) 
			first = current;
		for(IElement cr=first;cr.getName().equals("roID");) {
			IdValue id = new IdValue(cr.getStringValue());
			Vector cv = new Vector();
			for(IElement cc=cr.getNextSibling();cc.getName().equals("contentID");cc=cc.getNextSibling(),cr=cc) {
				cv.add(new UriValue(cc.getStringValue()));
			};
			vall.add(new RoIdContentId(id, new UriVector(cv)));	
		};
		return new RoIdContentIds(vall);
	}
	
	public IElements asDomChildrenOf(IElement father) {
		Vector v = new Vector();
		for(Iterator i = iterator();i.hasNext();) {
			IElements elems = ((RoIdContentId)i.next()).asDomChildrenOf(father,"roID");
			v.addAll(elems.getData());
		};
		return new IElements(v);
	}
	
	

}
