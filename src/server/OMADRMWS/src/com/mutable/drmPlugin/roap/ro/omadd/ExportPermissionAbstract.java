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
package com.mutable.drmPlugin.roap.ro.omadd;

import com.mutable.drmPlugin.roap.ro.odd.PermissionElementAbstract;
import com.mutable.drmPlugin.roap.ro.oex.Constraint;
import com.mutable.drmPlugin.xml.*;

public abstract class ExportPermissionAbstract extends
		PermissionElementAbstract {

	protected boolean validateConstraint(Constraint c) {
		return ( c!=null && c.getSystem()!=null );
	}


	public ExportPermissionAbstract(Constraint constraint) {
		super(constraint);
		// TODO Auto-generated constructor stub
	}
	
	public String domName() { return "export"; }

	public abstract String getMode();
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = super.asDomChildOf(father);
		newElem.addAttribute("mode",getMode());
		return newElem;
		
	}
	

}
