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
 * A wrapper around a key-homogenous  and value-homogenous java.util.HashMap. 
 * Each concrete subclass must
 * implement the protected methods keyClass, valClass. Instances of concrete subclasses
 * are guaranteed to be key-homogenous and value-homogenous.  
 * It exposes java.util.HashMap.get, java.util.HashMap.put, java.utilHashMap.containsKey,
 * java.util.HashMap.isEmpty, java.util.HashMap.remove and java.util.HashMap.toString.
 * With generics this would not be needed.
 * 
 * @see java.util.HashMap
 * 
 *
 */

public abstract class TypedMap {
	
	protected java.util.HashMap map;

	public TypedMap() {
		super();
		map = new java.util.HashMap();
	}
	
	public abstract Class keyClass();
	public abstract Class valClass();

	public Object get(Object key) {
		if (!keyClass().isInstance(key))
			throw new Error("key "+key.toString()+" is not "+keyClass().toString());
		return map.get(key);
	}
	
	public boolean containsKey(Object key) {
		if (!keyClass().isInstance(key)) 
			throw new Error("key "+key.toString()+" is not "+keyClass().toString());
		return map.containsKey(key);
	}
	
	public boolean put(Object key, Object value) {
		try {
			if (!keyClass().isInstance(key))
				throw new Error("key "+key.toString()+" is not "+keyClass().toString());
			if (!valClass().isInstance(value))
				throw new Error("value "+value.toString()+" is not "+valClass().toString());
			map.put(key,value);
		} catch (Exception e) { return false; };
		return true;
	}
	
	public boolean remove(Object key) {
		if (!keyClass().isInstance(key))
			throw new Error("key "+key.toString()+" is not "+keyClass().toString());
		return (map.remove(key)!=null);
	}

	public boolean isEmpty() {
		return map.isEmpty();
	}

	public String toString() {
		return map.toString();
	}


}


