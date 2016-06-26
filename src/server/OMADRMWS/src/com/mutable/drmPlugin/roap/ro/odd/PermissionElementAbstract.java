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
package com.mutable.drmPlugin.roap.ro.odd;

import com.mutable.drmPlugin.roap.ro.oex.Constraint;
import com.mutable.drmPlugin.roap.ro.omadd.*;
import com.mutable.drmPlugin.xml.*;

public abstract class PermissionElementAbstract extends XmlChild {
	

	protected Constraint constraint;
	
	protected  boolean validateConstraint(Constraint c) { return true; }


	public PermissionElementAbstract(Constraint constraint) {
		super();
		if (!validateConstraint(constraint)) throw new IllegalArgumentException();
		this.constraint = constraint;
	}
	
	
	public IElement asDomChildOf(IElement father, String path) {
		IElement newElem = super.asDomChildOf(father, path);
		constraint.asDomChildOf(newElem);
		return newElem;
	}
	
	public static PermissionElementAbstract instanceFromDomElement(IElement elem) {
		IElement celem = elem.getChildElement("constraint");
		Constraint ctr = Constraint.instanceFromDomElement(celem);
		String tag = elem.getName();
		if (tag.equals("play")) return new PlayPermission(ctr);
		if (tag.equals("print")) return new PrintPermission(ctr);
		if (tag.equals("execute")) return new ExecutePermission(ctr);
		if (tag.equals("display")) return new DisplayPermission(ctr);
		if (tag.equals("export")) {
			String modeString = elem.getAttributeStringValue("mode");
				if (modeString!=null) {
					if (modeString.equals("copy"))
						return new CopyPermission(ctr);
					if (modeString.equals("move"))
						return new MovePermission(ctr);
				} else return null;
		};
		return null;
		
	}


}
