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

package net.mutable.predicates;

import java.util.Iterator;


import net.mutable.collections.Map;
import net.mutable.collections.Set;
import net.mutable.expressions.Expression;
import net.mutable.expressions.Variable;

public class ForAllPredicate extends Predicate {
	private Variable v;
	private Expression se;
	private Predicate p;
	
	public ForAllPredicate(Variable v, Expression se, Predicate p){
		this.v = v;
		this.se = se;
		this.p = p;
	}

	public boolean eval(Map val) throws Exception {
		Set s = (Set)se.eval(val);
		if (val.contains(v)){
			// TODO: exception type
			throw new Exception();
		}
		for (Iterator i = s.iterator(); i.hasNext(); ){
			Map val2 = val.add(v, i.next());
			if (!p.eval(val2)){
				return false;				
			}
		}
		return true;
	}
	
	public String toString(){
		return "forall " + v + " in " + se + " holds " + p;
	}

}
