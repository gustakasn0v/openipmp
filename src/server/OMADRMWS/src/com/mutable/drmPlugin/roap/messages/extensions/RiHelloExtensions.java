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
 * Extensions for RiHelloResponse
 * 
 * @see com.mutable.drmPlugin.roap.messages.RiHelloResponse
 * 
 *
 */


public class RiHelloExtensions extends Extensions {



	

	/**
	 * By OMA-DRM-DRM-V2_0-20041210-C pp.32-33
	 * one of  peer, cr must be null
	 * @param peer PeerKeyIdentifier
	 * @param cr CertificateCachingExtension
	 * @param edd EmptyDeviceDetails
	 */
	
	public RiHelloExtensions(PeerKeyIdentifier peer, CertificateCachingExtension cr,
			EmptyDeviceDetails edd) {
		super();
		if ( peer!=null && cr!=null) throw new IllegalArgumentException();
		if (peer!=null) data.add(peer);
		if (cr!=null) data.add(cr);
		if (edd!=null) data.add(edd);

	}
	


}
