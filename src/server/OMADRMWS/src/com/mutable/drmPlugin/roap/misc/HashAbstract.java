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

import com.mutable.drmPlugin.tools.*;
import com.mutable.drmPlugin.xml.IElement;

public abstract class HashAbstract extends KeyIdentifier {

	protected Base64String hash;
	protected UriValue algorithm;



	public HashAbstract() {
		super();
	}

	public HashAbstract(Base64String hash) {
		super();
		if (hash==null) throw new IllegalArgumentException();
		this.hash = hash;
		algorithm = new UriValue("http://www.w3.org/2000/09/xmldsig#sha1");
	}

	public HashAbstract(Base64String hash, UriValue algorithm ) {
		super();
		if (hash==null || algorithm==null) throw new IllegalArgumentException();
		this.algorithm = algorithm;
		this.hash = hash;
	}





	public int hashCode() {
		return hash.hashCode()+algorithm.hashCode();
	}



	public UriValue getAlgorithm() {
		return algorithm;
	}



	public Base64String getHash() {
		return hash;
	}


	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		newElem.addAttribute("algorithm", getAlgorithm().toString());
		newElem.addChildElement("hash",getHash().toString());
		return newElem;
		
	}
	
	public String toString() { return hash.toString(); }

}
