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
package com.mutable.drmPlugin.tools;

/**
 * This is a special TypedMap where valueClass is also a TypedMap. It represents
 * a map of type keyClass()*valClass().keyClass() -> valClass().valClass, or 
 * isomorphically of type keyClass() -> (valClass().keyClass() -> valClass().valClass()).
 * So it has a 2-argument get, a 3-argument put, and 2-argument remove and containsKey
 * methods.
 *  
 * @see TypedMap
 * 
 *
 */


public abstract class TypedTwoMap extends TypedMap {

	public TypedTwoMap() {
		super();
		// TODO Auto-generated constructor stub
	}
	
	
	public Object get(Object key, Object valKey) {
		if (!keyClass().isInstance(key))
			throw new Error("key "+key.toString()+" is not "+keyClass().toString());
		if (!map.containsKey(key)) return null;
		return ((TypedMap)map.get(key)).get(valKey);
		
	}
	
	public boolean put(Object key, Object valKey, Object valVal)  {
		try {
			if (!keyClass().isInstance(key))
				throw new Error("key "+key.toString()+" is not "+keyClass().toString());
			if (!map.containsKey(key)) map.put(key,valClass().newInstance());
			((TypedMap)map.get(key)).put(valKey,valVal);
		} catch (Exception e) { return false; };
		return true;
	}
	
	public boolean containsKeys(Object key, Object valKey) {
		if (!containsKey(key)) return false;
		return ((TypedMap)map.get(key)).containsKey(valKey);
	}
	
	public boolean remove(Object key, Object valKey) {
		if (!containsKey(key)) return false;
		return ((TypedMap)map.get(key)).remove(valKey);
	}
}
