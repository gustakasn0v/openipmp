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

import com.mutable.drmPlugin.roap.messages.extensions.RegistrationResponseExtensions;
import com.mutable.drmPlugin.roap.messages.status.SuccessStatus;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.Base64StringVector;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;

/**
 * Ssuccessful
 * RegistrationResponse server message of the
 * 4-pass Roap registration protocol
 * 
 * 
 *
 */


public class SuccessRegistrationResponse extends RegistrationResponse {
	
	protected UriValue riUrl;
	protected CertificateChain certificateChain;
	protected Base64StringVector ocspResponses;
	protected RegistrationResponseExtensions extensions;
	protected Base64String signature;


	/*
	 * signature should also be non-null, but the constructor does not enforce
	 * this in order to enable creation of the string to sign
	 */
	public SuccessRegistrationResponse(SuccessStatus status, SessionId id, 
			UriValue uri, CertificateChain chain, 
			Base64StringVector responses, RegistrationResponseExtensions extensions, 			
			Base64String signature) {
		super(status);
		if (id==null || uri==null)
			throw new IllegalArgumentException();
		certificateChain = (chain==null
							? null
							: (CertificateChain) chain.nonEmptyOrNull());
		this.extensions = extensions;
		ocspResponses = responses;
		riUrl = uri;
		sessionId = id;
		this.signature = signature;
	}

	public CertificateChain getCertificateChain() {
		return certificateChain;
	}

	public RegistrationResponseExtensions getExtensions() {
		return extensions;
	}

	public Base64StringVector getOcspResponses() {
		return ocspResponses;
	}

	public UriValue getRiUrl() {
		return riUrl;
	}


	public Base64String getSignature() {
		return signature;
	}

	public void setSignature(Base64String signature) {
		this.signature = signature;
	}
	
	/*
	 * completing the implementation of XmlDocument
	 * 
	 */
	public void setDomElement(IElement root) {
		super.setDomElement(root);
		root.addChildElement("riURL",getRiUrl().toString());
		if (getCertificateChain()!=null) getCertificateChain().asDomChildOf(root);
		if (getOcspResponses()!=null)
			for(Iterator i = getOcspResponses().iterator();i.hasNext();)
				root.addChildElement("ocspResponse",((Base64String)i.next()).toString());
		if (getExtensions()!=null) getExtensions().asDomChildOf(root);
		if (getSignature()!=null) root.addChildElement("signature",getSignature().toString());
	}

}
