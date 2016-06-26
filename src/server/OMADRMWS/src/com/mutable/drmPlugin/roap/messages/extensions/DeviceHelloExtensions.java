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

/**
 * Extensions for DeviceHelloRequest
 * 
 * @see com.mutable.drmPlugin.roap.messages.DeviceHelloRequest
 * 
 *
 */
public class DeviceHelloExtensions extends Extensions {

	protected Class elementClass() { return CertificateCachingExtension.class; }

	
	
	
	protected DeviceHelloExtensions() { super(); }

	/**
	 * By OMA-DRM-DRM-V2_0-20041210-C pp.30-31
	 * the only allowable extension is a (single) CertificateCachingExtension
	 */
	
	public DeviceHelloExtensions(CertificateCachingExtension cce) {
		super();
		data.add(cce);
	}
	
	

}
