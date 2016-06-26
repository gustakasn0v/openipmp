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

package com.mutable.osms.server.app.test;

import com.mutable.osms.server.bo.osmsContent;
import com.mutable.osms.server.bo.osmsIpmpAgreement;

import net.mutable.collections.Map;
import net.mutable.expressions.Expression;
import net.mutable.expressions.Variable;

public class ContentIdExp extends Expression {
	private Variable v;
	
	public ContentIdExp(Variable v){
		this.v = v;
	}

	public Object eval(Map val) throws Exception {
		Object o = v.eval(val);
		if (o.getClass() == osmsContent.class){
			osmsContent content = (osmsContent)o;
			return content.getContentId();
		}
		
		if (o.getClass() == osmsIpmpAgreement.class){
			osmsIpmpAgreement agreement = (osmsIpmpAgreement)o;
			return agreement.getContentId();			
		}
		throw new Exception();
	}

	public String toString(){
		return v.toString() + ".contentId";
	}

}
