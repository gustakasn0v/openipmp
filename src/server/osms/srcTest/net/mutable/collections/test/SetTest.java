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

package net.mutable.collections.test;

import java.util.Iterator;


import net.mutable.collections.Map;
import net.mutable.collections.Set;
import net.mutable.expressions.ConstExp;
import net.mutable.expressions.Variable;
import net.mutable.predicates.AndPredicate;
import net.mutable.predicates.ForAllPredicate;
import net.mutable.predicates.LessThanPredicate;
import net.mutable.predicates.NotPredicate;
import net.mutable.predicates.Predicate;
import junit.framework.TestCase;

public class SetTest extends TestCase {
	private String[] names;
	private Integer[] numbers;
	private Set s1;
	private Set s2;
	
	public void setUp(){
		names = new String[4];
		names[0] = "Davor";
		names[1] = "Zoki";
		names[2] = "Dinko";
		names[3] = "Danko Bananko";
		
		numbers = new Integer[10];
		numbers[0] = new Integer(0);
		numbers[1] = new Integer(1);
		for (int i=2; i<numbers.length; i++)
			numbers[i] = new Integer(numbers[(i-1+numbers.length) % numbers.length].intValue() + numbers[(i-2+numbers.length) % numbers.length].intValue());

		s1 = new Set(names);
		s2 = new Set(numbers);
	}

	public static void testConstractionFromArray(Set s, Object[] a){

		for (int i = 0; i<a.length; i++)
			assertTrue(s.contains(a[i]));

		assertFalse(s.contains(new Object()));
	}
	
	public void testConstractionFromArray(){
		testConstractionFromArray(s1, names);
		testConstractionFromArray(s2, numbers);
	}

	public static void testAdd(Set s, Object r){
		Set t = (Set)s.clone(); 
		t.add(r);
		
		if (s.contains(r)){
			assertTrue(s.equals(t));
		}else{
			assertTrue(s.subseteq(t));
		}

	}

	public void testAdd(){
		testAdd(s1, "Bea");

		Iterator i = s1.iterator();
		i.next();
		testAdd(s1, i.next());

		i = s1.iterator();
		testAdd(s1, i.next());
	}

	public static void testRemove(Set s, Object r){
		Set t = (Set)s.clone(); 
		t.remove(r);
		
		if (s.contains(r)){
			assertTrue(t.subset(s));
		}else{
			assertTrue(t.equals(s));
		}

	}

	public void testRemove(){
		testRemove(s1, new Integer(-1));

		Iterator i = s1.iterator();
		i.next();
		testRemove(s1, i.next());

		i = s1.iterator();
		testRemove(s1, i.next());
	}
	
	public void testSubsets(){
		Set s3 = (Set)s1.clone();

		assertTrue(s1.subseteq(s1));
		assertFalse(s1.subseteq(s2)); 
		assertFalse(s2.subseteq(s1)); 
		assertTrue(s2.subseteq(s2));

		assertFalse(s1.subset(s1));
		assertFalse(s1.subset(s2)); 
		assertFalse(s2.subset(s1)); 
		assertFalse(s2.subset(s2));

		assertTrue(s1.equals(s1));
		assertFalse(s1.equals(s2)); 
		assertFalse(s2.equals(s1)); 
		assertTrue(s2.equals(s2));

		assertTrue(s1.subseteq(s3));
		assertTrue(s3.subseteq(s1));
		assertFalse(s1.subset(s3));
		assertFalse(s3.subset(s1));
		assertTrue(s1.equals(s3));
		assertTrue(s3.equals(s1));
	}
	
	public static void testUnion(Set s, Set t){
		Set u = s.union(t);

		// Unions is bigger than its components
		assertTrue(s.subseteq(u));
		assertTrue(t.subseteq(u));
		if (s.equals(t)){
			assertFalse(s.subset(u));
			assertFalse(t.subset(u));
			assertTrue(s.equals(u));
			assertTrue(t.equals(u));
		}else if (s.subset(t)){
			assertTrue(s.subset(u));
			assertFalse(t.subset(u));
			assertFalse(s.equals(u));
			assertTrue(t.equals(u));
		}else if (t.subset(s)){
			assertFalse(s.subset(u));
			assertTrue(t.subset(u));
			assertTrue(s.equals(u));
			assertFalse(t.equals(u));
		}else{
			assertTrue(s.subset(u));
			assertTrue(t.subset(u));
			assertFalse(s.equals(u));
			assertFalse(t.equals(u));
		}

		// No unnecessary elements in the union
		for (Iterator i = u.iterator(); i.hasNext(); ){
			Object o = i.next();
			assertTrue("Union contains element " + o.toString() + " not occuring in its components " + s + ", " + t + ".", s.contains(o) || t.contains(o));
		}

		assertTrue("Union is not commutative.", u.equals(t.union(s)));
	}
	
	public void testUnion(){
		testUnion(s1, s2);
		testUnion(s1, s1);
		Set s3 = (Set)s1.clone();
		s3.remove(s3.iterator().next());
		testUnion(s1, s3);
	}

	public static void testIntersection(Set s, Set t){
		Set u = s.intersection(t);

		// Intersection is smaller than its components
		assertTrue(u.subseteq(s));
		assertTrue(u.subseteq(t));
		if (s.equals(t)){
			assertFalse(u.subset(s));
			assertFalse(u.subset(t));
			assertTrue(u.equals(s));
			assertTrue(u.equals(t));
		}else if (s.subset(t)){
			assertFalse(u.subset(s));
			assertTrue(u.subset(t));
			assertTrue(u.equals(s));
			assertFalse(u.equals(t));
		}else if (t.subset(s)){
			assertTrue(u.subset(s));
			assertFalse(u.subset(t));
			assertFalse(u.equals(s));
			assertTrue(u.equals(t));
		}else{
			assertTrue(u.subset(s));
			assertTrue(u.subset(t));
			assertFalse(u.equals(s));
			assertFalse(u.equals(t));
		}

		// No unnecessary elements in the union
		for (Iterator i = s.iterator(); i.hasNext(); ){
			Object o = i.next();
			assertTrue("Union does not contain element " + o.toString() + " occuring in both of its components " + s + ", " + t + ".", !t.contains(o) || u.contains(o));
		}

		assertTrue("Intersection is not commutative.", u.equals(t.intersection(s)));
	}

	public void testIntersection(){
		testIntersection(s1, s2);
		testIntersection(s1, s1);
		Set s3 = (Set)s1.clone();
		s3.remove(s3.iterator().next());
		testIntersection(s1, s3);
	}

	public void testComprehension(){
		Set s = (Set)s2.clone();
		Variable v = new Variable("x");
		Predicate p1 = new LessThanPredicate(new ConstExp(new Integer(3)), v);
		Predicate p2 = new LessThanPredicate(v, new ConstExp(new Integer(10)));
		Predicate p = new AndPredicate(p1, p2);
		Set t = null;
		try {
			t = s.comprehension(v, v, p, new Map());
		} catch (Exception e) {
			fail("Unexpected exception: " + e.getMessage());
		}
		Predicate forAll1 = new ForAllPredicate(v, new ConstExp(t), p);
		Predicate forAll2 = new ForAllPredicate(v, new ConstExp(s.difference(t)), new NotPredicate(p));
		try {
			assertTrue(forAll1.eval(new Map()));
			assertTrue(forAll2.eval(new Map()));
		} catch (Exception e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}

}
