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
 * The Original Code is OpenIPMP.
 * 
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 *  
 * 
 */

package net.mutable.collections;

import java.util.Enumeration;
import java.util.Hashtable;

public class Map {
	private Hashtable subject;
	
	public Map(){
		subject = new Hashtable();
	}
	
	private Map(Hashtable subject){
		this.subject = subject;
	}
	
	public Object clone(){
		return new Map((Hashtable)subject.clone());
	}
	
	public Map add(Object key, Object value){
		Map ret = new Map();
		ret.subject.putAll(subject);
		ret.subject.put(key, value);

		return ret;
	}
	
	public Set getkeys(){
		Enumeration i = subject.keys();
		Set ret = new Set();
		while (i.hasMoreElements()){
			ret.add(i.nextElement());
		}
		return ret;
	}
	
	public boolean contains(Object key){
		return subject.containsKey(key);
	}
	
	public Object get(Object key){
		return subject.get(key);
	}
}
