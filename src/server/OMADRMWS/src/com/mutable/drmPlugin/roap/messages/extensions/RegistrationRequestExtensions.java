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

import com.mutable.drmPlugin.xml.*;
import java.util.*;

/**
 * Extensions for RegistrationRequest
 * 
 * @see com.mutable.drmPlugin.roap.messages.RegistrationRequest
 * 
 *
 */

public class RegistrationRequestExtensions extends Extensions {
	
	
	protected RegistrationRequestExtensions() { super(); }
	
	/**
	 * By OMA-DRM-DRM-V2_0-20041210-C p.35
	 * one of no, kid must be null
	 * @param peer PeerKeyIdentifier
	 * @param no NoOcspResponse
	 * @param kid OcspResponderKeyIdentifier
	 * @param dd FullDeviceDetails
	 */

	public RegistrationRequestExtensions(PeerKeyIdentifier peer, NoOcspResponse no,
							OcspResponderKeyIdentifier kid, FullDeviceDetails dd) 	{ 
		super();
		if (no!=null && kid!=null) throw new IllegalArgumentException();
		if (peer!=null) data.add(peer); 
		if (no!=null) data.add(no);
		if (kid!=null) data.add(kid);
		if (dd!=null) data.add(dd);
	}
	
	/**
	 * by brain-damaged OMADRM formatting extension elements can be told apart only by
	 * the value of xsi:type attribute
	 */
	public static RegistrationRequestExtensions instanceFromDomElement(IElement elem) {
		if (elem==null) return null;
		PeerKeyIdentifier peer = null;
		NoOcspResponse no = null;
		OcspResponderKeyIdentifier kid = null;
		FullDeviceDetails dd = null;
		IElements elems = elem.getAllChildren();
		for(Iterator i=elems.iterator();i.hasNext();) {
			IElement ielem = (IElement) i.next();
			if (ielem.getAttributeStringValue("xsi:type").equals("roap:PeerKeyIdentifier"))
				peer = PeerKeyIdentifier.instanceFromDomElement(ielem);
			if (ielem.getAttributeStringValue("xsi:type").equals("roap:NoOcspResponse"))
				no = new NoOcspResponse(ielem.getAttributeBooleanValue("critical"));
			if (ielem.getAttributeStringValue("xsi:type").equals("roap:OcspResponderKeyIdentifier"))
				kid = OcspResponderKeyIdentifier.instanceFromDomElement(ielem);
			if (ielem.getAttributeStringValue("xsi:type").equals("roap:DeviceDetails"))
				dd = (FullDeviceDetails) DeviceDetails.instanceFromDomElement(ielem);
		};
		return new RegistrationRequestExtensions(peer,no,kid,dd);
	}
	
}
