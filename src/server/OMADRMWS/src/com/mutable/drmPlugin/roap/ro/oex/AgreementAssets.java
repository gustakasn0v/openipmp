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

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlVector;

/**
 * VectorValue holding AgreementAsset values
 * @see AgreementAsset
 * 
 *
 */

public class AgreementAssets extends XmlVector {

	protected Class elementClass() { return AgreementAsset.class; }
	


	public AgreementAssets(Vector data) {
		super(data);
		// TODO Auto-generated constructor stub
	}

	public AgreementAssets() {
		super();
		// TODO Auto-generated constructor stub
	}
	
/*	public IElements asDomChildrenOf(IElement elem) {
		Vector v = new Vector();
		for(Iterator i=iterator();i.hasNext();) 
			v.add(((AgreementAsset)i.next()).asDomChildOf(elem));
		return new IElements(v);			
	}
*/
	public static AgreementAssets instanceFromDomElements(IElements elems) {
		Vector v = new Vector();
		for(Iterator i=elems.iterator();i.hasNext();)
			v.add(AgreementAsset.instanceFromDomElement((IElement)i.next()));
		return new AgreementAssets(v);
	}



}
