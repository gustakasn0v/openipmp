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
package com.mutable.drmPlugin.roap.messages;

import java.util.Iterator;

import com.mutable.drmPlugin.roap.messages.extensions.CertificateCachingExtension;
import com.mutable.drmPlugin.roap.messages.extensions.DeviceHelloExtensions;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.RoapIdentifiers;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlException;

/**
 * The DeviceHelloRequest message of the
 * 4-pass Roap registration protocol
 * 
 * 
 *
 */
public class DeviceHelloRequest extends RoapRequest {
	
	protected Version version;
	protected RoapIdentifiers deviceIds;
	protected UriVector supportedAlgorithms;
	protected DeviceHelloExtensions extensions;
	protected String encoding;

	


	public DeviceHelloRequest(Nonce nonce, Version version, 
			RoapIdentifiers ids, UriVector algorithms,
			DeviceHelloExtensions extensions) {
		super(nonce);
		if ( version==null || ids==null || ids.isEmpty()) 
			throw new IllegalArgumentException();
		deviceIds = ids;
		supportedAlgorithms = (algorithms==null
								? null
								: (UriVector) algorithms.nonEmptyOrNull());
		this.version = version;
		this.extensions = extensions;
	}

	public DeviceHelloExtensions getExtensions() {
		return extensions;
	}

	public RoapIdentifiers getDeviceIds() {
		return deviceIds;
	}

	public UriVector getSupportedAlgorithms() {
		return supportedAlgorithms;
	}

	public Version getVersion() {
		return version;
	}
	


	public void setDomElement(IElement root) {
		super.setDomElement(root);
		root.addChildElement("version",version.toString());
		java.util.Vector devIds = deviceIds.getData();
		for (Iterator i=devIds.iterator(); i.hasNext();) 
			((RoapIdentifier) i.next()).asDomChildOf(root,"deviceID");
		if (supportedAlgorithms!=null) {
			java.util.Vector algos = supportedAlgorithms.getData();
			for (Iterator i=algos.iterator(); i.hasNext();)
				((UriValue) i.next()).asDomChildOf(root,"supportedAlgorithm");
		};
		if (extensions!=null && !extensions.isEmpty()) 
			extensions.asDomChildOf(root);		
	}
	
	public String documentName() {
		return "DeviceHello";
	}

	

	public static DeviceHelloRequest instanceFromDomElement(IElement root) {
		String nonceString = root.getAttributeStringValue("triggerNonce");
		Nonce triggerNonce = (nonceString==null) ? null : new Nonce(nonceString);
		Version version = new Version(root.getChildStringValue("version"));
		IElements ids = root.getChildElements("deviceID");
		RoapIdentifiers keyIds = RoapIdentifiers.instanceFromDomElements(ids);
		IElements algos = root.getChildElements("supportedAlgorithm");
		UriVector uris = UriVector.instanceFromDomElements(algos);
		IElement extElement = root.getChildElement("extensions");
		if (extElement!=null && extElement.getAllChildren().isEmpty())
			throw new XmlException();
		DeviceHelloExtensions exts = (extElement==null )
							? null 
							: new DeviceHelloExtensions(
									CertificateCachingExtension.instanceFromDomElement(extElement.getFirstChild()));
		return new DeviceHelloRequest(triggerNonce,version,keyIds,uris,exts);

	}

	

}
