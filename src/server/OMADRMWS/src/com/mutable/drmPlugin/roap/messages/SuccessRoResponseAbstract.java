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

import com.mutable.drmPlugin.roap.messages.extensions.RoResponseExtensions;
import com.mutable.drmPlugin.roap.messages.status.SuccessStatus;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.ro.ProtectedRo;
import com.mutable.drmPlugin.roap.ro.ProtectedRos;
import com.mutable.drmPlugin.tools.*;
import com.mutable.drmPlugin.xml.*;
import java.util.*;

/**
 * The common contents of  successful 
 * RoResponse server message of the
 * 1-pass and 2-pass Roap rights acquisition protocol
 * 
 * only the 2-pass realization is used in current server implementation
 * 
 * 
 *
 */

public abstract class SuccessRoResponseAbstract extends RoResponse {
	
	protected RoapIdentifier deviceId;
	protected RoapIdentifier riId;
	protected ProtectedRos protectedRo;
	protected CertificateChain certificateChain;
	protected Base64StringVector ocspResponse;
	protected RoResponseExtensions extensions;
	protected Base64String signature;


	/*
	 * non-null signature is also required, but this is not enforced by the
	 * constructor in order to enable creation of a string to sign
	 */
	public SuccessRoResponseAbstract(SuccessStatus status, 
			RoapIdentifier did, RoapIdentifier rid, 
			ProtectedRos ro, CertificateChain chain, 
			Base64StringVector response, RoResponseExtensions extensions, 
			Base64String signature) {
		super(status);
		if ( did==null || rid==null 
				|| ro==null || ro.isEmpty())
			throw new IllegalArgumentException();
		certificateChain = (chain==null
							? null
							: (CertificateChain) chain.nonEmptyOrNull());
		deviceId = did;
		this.extensions = extensions;
		ocspResponse = response;
		protectedRo = ro;
		riId = rid;
		this.signature = signature;
	}

	/*
	 * accessors
	 */
	
	public CertificateChain getCertificateChain() {
		return certificateChain;
	}

	public RoapIdentifier getDeviceId() {
		return deviceId;
	}

	public RoResponseExtensions getExtensions() {
		return extensions;
	}

	public Base64StringVector getOcspResponse() {
		return ocspResponse;
	}

	public ProtectedRos getProtectedRo() {
		return protectedRo;
	}

	public RoapIdentifier getRiId() {
		return riId;
	}

	public Base64String getSignature() {
		return signature;
	}
	
	public Nonce getNonce() { return null; }

	/*
	 * completing the implementation of  XmlDocument
	 * 
	 */
	public void setDomElement(IElement elem) {
		super.setDomElement(elem);
		getDeviceId().asDomChildOf(elem,"deviceID");
		getRiId().asDomChildOf(elem,"riID");
		if (getNonce()!=null) elem.addChildElement("nonce",getNonce().toString());
		for(Iterator i = getProtectedRo().iterator();i.hasNext();)
			((ProtectedRo)i.next()).asDomChildOf(elem);
		if (getCertificateChain()!=null) getCertificateChain().asDomChildOf(elem);
		if (getOcspResponse()!=null)
			for(Iterator i=getOcspResponse().iterator();i.hasNext();)
				elem.addChildElement("ocspResponse",((Base64String)i.next()).toString());
		if (getExtensions()!=null) ((RoResponseExtensions)getExtensions()).asDomChildOf(elem);
		if (getSignature()!=null) elem.addChildElement("signature",getSignature().toString());
		
	}

	public void setSignature(Base64String signature) {
		this.signature = signature;
	}
 }
