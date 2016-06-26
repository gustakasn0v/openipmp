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

import com.mutable.drmPlugin.roap.messages.extensions.RegistrationRequestExtensions;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.DateTimeString;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.*;

/**
 * RegistrationRequest message of the
 * 4-pass Roap registration protocol
 * 
 * 
 *
 */

public class RegistrationRequest extends RoapRequest {
	
	SessionId sessionId;
	Nonce nonce;
	DateTimeString time;
	CertificateChain certificateChain;
	KeyIdentifiers trustedAuthorities;
	Base64String serverInfo;
	RegistrationRequestExtensions extensions;
	Base64String signature;


	public RegistrationRequest(Nonce tNonce, SessionId id, 
			Nonce dNonce, DateTimeString time, CertificateChain chain, 
			KeyIdentifiers authorities, Base64String info, 
			RegistrationRequestExtensions extensions,  
			Base64String signature ) {
		super(tNonce);
		if ( id==null || dNonce==null || time==null || signature==null)
			throw new IllegalArgumentException();
		certificateChain = (chain==null
							? null
							: (CertificateChain) chain.nonEmptyOrNull());
		this.extensions = (extensions==null
							? null
							: (RegistrationRequestExtensions) extensions.nonEmptyOrNull());
		nonce = dNonce;
		serverInfo = info;
		sessionId = id;
		this.signature = signature;
		this.time = time;
		trustedAuthorities = (authorities==null
								? null
								: (KeyIdentifiers) authorities);
	}

	/*
	 * accessors
	 */

	public CertificateChain getCertificateChain() {
		return certificateChain;
	}

	public RegistrationRequestExtensions getExtensions() {
		return extensions;
	}

	public Nonce getNonce() {
		return nonce;
	}

	public Base64String getServerInfo() {
		return serverInfo;
	}

	public SessionId getSessionId() {
		return sessionId;
	}

	public Base64String getSignature() {
		return signature;
	}

	public DateTimeString getTime() {
		return time;
	}

	public KeyIdentifiers getTrustedAuthorities() {
		return trustedAuthorities;
	}
	
	/* 
	 * implementing  XmlDocument
	 * 
	 */
	
	public void setDomElement(IElement root) {
		super.setDomElement(root);
		root.addAttribute("sessionId",sessionId.toString());
		root.addChildElement("nonce",nonce.toString());
		root.addChildElement("time",getTime().toString());
		if (certificateChain!=null) certificateChain.asDomChildOf(root);
		if (trustedAuthorities != null)
			getTrustedAuthorities().asDomChildOf(root,"trustedAuthorities");
		root.addChildElement("serverInfo",getServerInfo().toString());
		extensions.asDomChildOf(root);
		if (signature!=null) root.addChildElement("signature",signature.toString());
	}

	public String documentName() {
		return "RegistrationRequest";
	}

	/* 
	 * instance creation from xml
	 * 
	 */

	public static RegistrationRequest instanceFromDomElement(IElement elem) {
		SessionId sid = new SessionId(elem.getAttributeStringValue("sessionId"));
		String tNonceString = elem.getAttributeStringValue("triggerNonce");
		Nonce triggerNonce = (tNonceString==null) ? null : new Nonce(tNonceString);
		String nonceString = elem.getChildStringValue("nonce");
		Nonce nonce = (nonceString==null) ? null : new Nonce(nonceString);
		DateTimeString time = new DateTimeString(elem.getChildStringValue("time"));
		IElement chainElem = elem.getChildElement("certificateChain");
		CertificateChain chain = (chainElem==null) 
								? null 
								: CertificateChain.instanceFromDomElement(chainElem);
		IElement trustedElem = elem.getChildElement("trustedAuthorities");
		KeyIdentifiers trusted=null;
		if (trustedElem!=null) 
			trusted = KeyIdentifiers.instanceFromDomElement(trustedElem,"keyIdentifier");
		Base64String si = new Base64String(elem.getChildStringValue("serverInfo"));
		IElement extElement = elem.getChildElement("extensions");			
		if (extElement!=null && extElement.getAllChildren().isEmpty())
			throw new XmlException();
		RegistrationRequestExtensions exts = 
			(extElement==null) ? null : RegistrationRequestExtensions.instanceFromDomElement(extElement);
		Base64String sig = new Base64String(elem.getChildStringValue("signature"));
		return new RegistrationRequest(triggerNonce,sid,nonce,time,chain,trusted,si,exts,sig);
		

	}

	public void setSignature(Base64String signature) {
		this.signature = signature;
	}

}
