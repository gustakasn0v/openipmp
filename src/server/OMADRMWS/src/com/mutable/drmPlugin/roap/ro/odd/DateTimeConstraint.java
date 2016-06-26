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

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;

public class DateTimeConstraint extends XmlChild  {
	
	protected Start start;
	protected End end;


	public DateTimeConstraint(End end, Start start) {
		super();
		this.end = end;
		this.start = start;
	}
	
	public IElement asDomChildOf(IElement father, String path ) {
		IElement newElem = super.asDomChildOf(father,path);
		if (start!=null)
			newElem.addChildElement("start",start.toString());
		if (end!=null)
			newElem.addChildElement("end",end.toString());
		return newElem;
	}
	
	public static DateTimeConstraint instanceFromDomElement(IElement elem) {
		return new DateTimeConstraint(
				new End(elem.getChildStringValue("end")),
				new Start(elem.getChildStringValue("start")));
	}
	
	public String domName() { return "datetime"; }

}
