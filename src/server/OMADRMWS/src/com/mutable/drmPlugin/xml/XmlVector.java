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

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.tools.VectorValue;

/** 
 * This is a VectorValue that goes to XML. 
 * It is assumed that for each concrete subclass
 *  the elementClass() implements IXmlChild
 * 
 * 
 *
 */

public abstract class XmlVector extends VectorValue  {

	public XmlVector(Vector data) {
		super(data);
	}

	public XmlVector() {
		super();
	}

	
	public IElements asDomChildrenOf(IElement father) {
		Vector v = new Vector();
		for(Iterator i = iterator();i.hasNext();) {
			IXmlChild mem = (IXmlChild) (i.next());
			IElement e = mem.asDomChildOf(father);
			v.add(e);
		};
		return new IElements(v);
	}
	
	public IElements asDomChildrenOf(IElement father, String name) {
		Vector v = new Vector();
		for(Iterator i = iterator();i.hasNext();)
			v.add(((XmlChild)i.next()).asDomChildOf(father,name));
		return new IElements(v);
	}
	
	public IElement asDomChildOf(IElement father, String name) {
		IElement newElem = father.addChildElement(name);
		asDomChildrenOf(newElem);
		return newElem;
	}
	


}
