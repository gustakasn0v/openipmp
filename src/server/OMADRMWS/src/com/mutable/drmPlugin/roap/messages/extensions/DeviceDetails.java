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
package com.mutable.drmPlugin.roap.messages.extensions;

import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;


public abstract class DeviceDetails extends Extension {

	protected String xsiType() {
		return "roap:DeviceDetails";
	}

	protected DeviceDetails(boolean cr) {
		super(cr);
	}
	
	public boolean isEmpty() { return true; }
	

	public String getManufacturer() {	return null; }

	public String getModel() { return null; }

	public String getVersion() { return null; }
	
	

	
	public static DeviceDetails instanceFromDomElement(IElement elem) {
		IElements children = elem.getAllChildren();
		return children.isEmpty()
			? (DeviceDetails) new EmptyDeviceDetails(elem.getAttributeBooleanValue("critical"))
			: (DeviceDetails) 
				new FullDeviceDetails(
					elem.getAttributeBooleanValue("critical"),
					elem.getChildStringValue("manufacturer"),
					elem.getChildStringValue("model"),
					elem.getChildStringValue("version"));
					
	}


}
