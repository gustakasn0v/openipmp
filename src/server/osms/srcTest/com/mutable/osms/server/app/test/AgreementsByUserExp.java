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

import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.bo.osmsIpmpAgreement;
import com.mutable.osms.server.bo.osmsUsers;
import com.mutable.osms.server.db.osmsDatabase;

import net.mutable.collections.Map;
import net.mutable.collections.Set;
import net.mutable.expressions.Expression;

public class AgreementsByUserExp extends Expression {
	private Expression userExp;
	
	public AgreementsByUserExp(Expression userExp){
		this.userExp = userExp;
	}

	public Object eval(Map val) throws Exception {
		osmsDatabase db = osmsGlobalObjectManager.getInstance().getDatabase();
		
		osmsUsers user = (osmsUsers)userExp.eval(val);
		osmsIpmpAgreement[] agreements = db.getIpmpAgreementByAssignedToUser(user.getUserId());
		
		return new Set(agreements);
	}
	
	public String toString(){
		return userExp + ".agreements";
	}

}
