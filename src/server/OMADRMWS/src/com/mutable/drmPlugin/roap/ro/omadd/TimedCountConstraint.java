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

import org.apache.axis.types.UnsignedInt;

import com.mutable.drmPlugin.tools.IntegerValue;
import com.mutable.drmPlugin.xml.IElement;

public class TimedCountConstraint extends IntegerValue {
	
	protected UnsignedInt timer;

	public TimedCountConstraint(UnsignedInt data) {
		super(data);
		timer=null;
	}

	public String XmlEncode() {
		// TODO Auto-generated method stub
		return null;
	}

	public String XmlEncode(String varName) {
		// TODO Auto-generated method stub
		return null;
	}

	public TimedCountConstraint(UnsignedInt data, UnsignedInt timer) {
		super(data);
		// TODO Auto-generated constructor stub
		this.timer = timer;
	}
	
	public UnsignedInt getCount() {
		return getData();
	}

	public UnsignedInt getTimer() {
		return timer;
	}

	public IElement asDomChildOf(IElement elem) {
		IElement newElem = elem.addChildElement("timed-count",toString());
		if (timer!=null) newElem.addAttribute("timer", timer.toString());
		return newElem;
	}
	
	public static TimedCountConstraint instanceFromDomElement(IElement elem) {
		return new TimedCountConstraint(
				new UnsignedInt(elem.getIntValue()),
				new UnsignedInt(elem.getAttributeIntValue("timer")));
	}

}
