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
package com.mutable.drmPlugin.server;

import java.io.IOException;
import java.util.Iterator;

import com.mutable.drmPlugin.crypto.IPublicKey;
import com.mutable.drmPlugin.roap.messages.extensions.CertificateCachingExtension;
import com.mutable.drmPlugin.roap.messages.extensions.DeviceDetails;
import com.mutable.drmPlugin.roap.messages.extensions.FullDeviceDetails;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;

/**
 * represents the info that the server maintains about a registered device
 * 
 * @see com.mutable.drmPlugin.server.helpers.RegDatabase AgentContextAbstract
 * 
 * 
 *
 */
public class DeviceContext extends AgentContextAbstract {
	
	DeviceDetails details;

	/**
	 * constructor
	 * 
	 * @param id
	 * @param key
	 * @param url
	 * @param chain
	 * @param trusted
	 * @param algorithms
	 * @param version
	 * @param caching
	 * @param details  new wrt AgentContextAbstract
	 * 
	 */
	public DeviceContext(RoapIdentifier id, IPublicKey key, UriValue url,
			CertificateChain chain, KeyIdentifiers trusted,
			UriVector algorithms, Version version,
			CertificateCachingExtension caching, DeviceDetails details) {
		super(id, key, url, chain, trusted, algorithms, version, caching);
		this.details = details;
	}

	public DeviceContext() {
		super();
	}
	
	public DeviceDetails getDetails() {
		return details;
	}
	
/*	public IElement asDomChildOf(IElement father) {
		IElement newElem = super.asDomChildOf(father);
		getDetails().asDomChildOf(newElem);
		return newElem;
	}
*/
	
	public void setDomElement(IElement elem) {
		super.setDomElement(elem);
		if (details!=null) {
			IElement extElem = (caching==null) 
								? elem.addChildElement("extensions")
								: elem.getChildElement("extensions");
		    details.asDomChildOf(extElem);
		}
	}
	
	public String documentName() { return "deviceContext"; }
	
	public void setFromDomElement(IElement elem) throws IOException {
		super.setFromDomElement(elem);
		IElement extElem = elem.getChildElement("extensions");
		if (extElem!=null) {
			IElements exts = extElem.getAllChildren();
			for (Iterator i=exts.iterator(); i.hasNext();) {
				IElement ee = (IElement) i.next();
				if (ee.getAttributeStringValue("xsi:type").equals("roap:DeviceDetails"))
					details = (FullDeviceDetails) DeviceDetails.instanceFromDomElement(ee);
			}
		}		
	}
	
	public static DeviceContext instanceFromDomElement(IElement elem) throws IOException {
		DeviceContext inst = new DeviceContext();
		inst.setFromDomElement(elem);
		return inst;
	}



}
