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
import com.mutable.drmPlugin.xml.*;

public class FullDeviceDetails extends DeviceDetails {
	
	protected String manufacturer, model, version;


	public FullDeviceDetails(boolean cr, String manufacturer, 
						String model, String version) {
		super(cr);
		if (manufacturer==null || model==null ||version==null)
			throw new IllegalArgumentException();
		this.manufacturer = manufacturer;
		this.model = model;
		this.version = version;
	}

	public String getManufacturer() {
		return manufacturer;
	}

	public String getModel() {
		return model;
	}

	public String getVersion() {
		return version;
	}
	
	public boolean isEmpty() { return false; }
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = super.asDomChildOf(father);
		newElem.addChildElement("manufacturer",getManufacturer().toString());
		newElem.addChildElement("model",getModel().toString());
		newElem.addChildElement("version",getVersion().toString());
		return newElem;
	}

}
