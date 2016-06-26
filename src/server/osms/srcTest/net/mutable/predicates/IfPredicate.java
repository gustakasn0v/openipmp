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

import net.mutable.collections.Map;

public class IfPredicate extends Predicate {
	private Predicate guard;
	private Predicate p1;
	private Predicate p2;
	
	public IfPredicate(Predicate guard, Predicate p1, Predicate p2){
		this.guard = guard;
		this.p1 = p1;
		this.p2 = p2;
	}

	public boolean eval(Map val) throws Exception {
		if (guard.eval(val))
			return p1.eval(val);
		else
			return p2.eval(val);
	}

	public String toString(){
		return "(if " + guard.toString() +
		       " then " + p1.toString() + 
		       " else " + p2.toString() + ")";
	}
}
