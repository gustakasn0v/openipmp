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

package net.mutable.expressions;

import net.mutable.collections.Map;
import net.mutable.collections.Set;
import net.mutable.predicates.Predicate;

public class ComprehensionExp extends Expression {
	private Expression s;
	private Variable v;
	private Predicate p;
	private Expression e;

	public ComprehensionExp(Expression s, Variable v, Predicate p, Expression e){
		this.s = s;
		this.v = v;
		this.p = p;
		this.e = e;
	}
	
	public ComprehensionExp(Expression s, Variable v, Expression e){
		this.s = s;
		this.v = v;
		this.p = null;
		this.e = e;
	}
	
	public Object eval(Map val) throws Exception {
		return ((Set)s.eval(val)).comprehension(e, v, p, val);
	}
	
	public String toString(){
		if (p != null)
			return "{" + e + " | " + v + " in " + s + " where " + p + "}";
		else
			return "{" + e + " | " + v + " in " + s + "}";
	}

}
