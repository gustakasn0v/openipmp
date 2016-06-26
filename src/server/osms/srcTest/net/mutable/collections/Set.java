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

import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;


import net.mutable.expressions.Expression;
import net.mutable.expressions.Variable;
import net.mutable.predicates.Predicate;

public class Set {
	private HashSet subject;
	
	public Set(){
		subject = new HashSet();
	}

	public Set(Object[] a){
		subject = new HashSet(a.length);
		for (int i=0; i<a.length; i++)
			add(a[i]);
	}

	public Set(Collection c){
		subject = new HashSet(c.size());
		addAll(c);
	}
	
	public Object clone(){
		return new Set(subject);
	}

	public Iterator iterator(){
		return subject.iterator();
	}
	
	public void add(Object o){
		subject.add(o);
	}

	public void addAll(Collection c){
		subject.addAll(c);
	}
	
	public void addAll(Set s){
		addAll(s.subject);
	}

	public void remove(Object o){
		subject.remove(o);
	}
	
	public void removeAll(Collection c){
		subject.removeAll(c);
	}
	
	public void removeAll(Set s){
		removeAll(s.subject);
	}
	
	public boolean contains(Object o){
		return subject.contains(o);
	}
	
	public Object findEqual(Object o){
		for (Iterator i = iterator(); i.hasNext(); ){
			Object n = i.next(); 
			if (n.equals(o))
				return n;			
		}
		return null;		
	}

	public Set union(Set rhs){
		Set ret = new Set(subject);
		ret.addAll(rhs);
		return ret;
	}

	public Set bigUnion(){
		Set ret = new Set();
		Iterator i = iterator();
		while(i.hasNext()){
			ret = ret.union((Set)i.next());
		}
		return ret;
	}
	
	public Set intersection(Set rhs){
		Set ret = new Set();
		Iterator i;
		for (i = iterator(); i.hasNext(); ){
			Object o = i.next();
			if (rhs.contains(o))
				ret.add(o);
		}
		return ret;
	}
	
	public Set bigIntersection() throws Exception{
		Set ret;
		Iterator i = iterator();
		if (i.hasNext()){
			ret = (Set)i.next();
			while(i.hasNext()){
				ret = ret.intersection((Set)i.next());
			}
			return ret;
		}else{
			throw new Exception();
		}
	}

	public Set difference(Set rhs){
		Set ret = new Set(subject);
		ret.removeAll(rhs);
		return ret;
	}

	public Set comprehension(Expression e, Variable v, Predicate p, Map val) throws Exception{
		Set ret = new Set();
		Iterator i = iterator();
		while (i.hasNext()){
			Object o = i.next();
			Map val2 = val.add(v, o);
			if ((p == null) || (p.eval(val2)))
				ret.add(e.eval(val2));
		}
		return ret;
	}
	
	public Set comprehension(Predicate p) throws Exception{
		Variable v = new Variable();
		return comprehension(v, v, p, new Map());
	}
	
	public boolean isEmpty(){
		return subject.isEmpty();
	}
	
	public boolean notEmpty(){
		return !isEmpty();
	}

	public boolean subseteq(Set s){
		for (Iterator i = iterator(); i.hasNext(); ){
			Object o = i.next();
			if (!s.contains(o))
				return false;
		}
		return true;
	}

	public boolean subset(Set s){
		return subseteq(s) && !s.subseteq(this);
	}

	public boolean equals(Object o){
		if (o.getClass() != Set.class)
			return false;
		Set s = (Set)o;
		return subseteq(s) && s.subseteq(this);
	}

	public String toString(){
		String ret = "{";
		Iterator i = subject.iterator();

		if (i.hasNext())
			ret = ret + i.next().toString();
		
		while (i.hasNext())
			ret = ret + ", " + i.next().toString();
		
		return ret + "}";
	}
}
