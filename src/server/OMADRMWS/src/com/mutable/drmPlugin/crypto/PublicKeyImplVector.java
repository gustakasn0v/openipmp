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
package com.mutable.drmPlugin.crypto;

import java.security.KeyStore;
import java.security.KeyStoreException;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlVector;

/**
 * VectorValue holding  PublicKeyImpl values
 * @see PublicKeyImpl
 * 
 * 
 *
 */
public class PublicKeyImplVector extends XmlVector {

	public PublicKeyImplVector() {
		super();
	}

	public PublicKeyImplVector(Vector data) {
		super(data);
	}

	protected Class elementClass() {
		return PublicKeyImpl.class;
	}

	
	
/*	public IElement asDomChildOf(IElement father,String name) {
		IElement newElem = father.addChildElement(name);
		for(Iterator i = iterator();i.hasNext();)
			((PublicKeyImpl)i.next()).asDomChildOf(newElem);
		return newElem;
	}
*/
	public static PublicKeyImplVector instanceFromDomElement(IElement elem) {
		Vector v = new Vector();
		IElements children = elem.getAllChildren();
		for(Iterator i = children.iterator();i.hasNext();)
			v.add(PublicKeyImpl.instanceFromDomElement((IElement)i.next()));
		return new PublicKeyImplVector(v);
	}
	
	/**
	 * extracting all public keys stored in a java keystore; not really used for the current server
	 * 
	 */
	
	public static PublicKeyImplVector instanceFromKeyStore(KeyStore ks) throws KeyStoreException {
		Vector v = new Vector();
		Enumeration en = ks.aliases();
		for(;en.hasMoreElements();)
			v.add(PublicKeyImpl.instanceFromKeyStore(ks,(String)en.nextElement()));
		return new PublicKeyImplVector(v);
		
	}

}
