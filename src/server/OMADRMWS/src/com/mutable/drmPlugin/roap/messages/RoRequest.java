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

import com.mutable.drmPlugin.roap.messages.extensions.RoRequestExtensions;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.DateTimeString;
import com.mutable.drmPlugin.roap.misc.DomainIdentifier;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.ro.RoInfos;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlException;

/**
 * RoRequest message of the
 * 2-pass Roap rights acquisition protocol
 * 
 * 
 *
 */

public class RoRequest extends RoapRequest {
	
	protected RoapIdentifier deviceId;
	protected DomainIdentifier domainId;
	protected RoapIdentifier riId;
	protected Nonce nonce;
	protected DateTimeString dateTime;
	protected RoInfos roInfos;
	protected CertificateChain certificateChain;
	protected RoRequestExtensions extensions;
	protected Base64String signature;


	public RoRequest(Nonce tNonce, 
			RoapIdentifier devId, DomainIdentifier domId,
			RoapIdentifier rid, Nonce nonce, 
			DateTimeString time, RoInfos infos, 
			CertificateChain chain, RoRequestExtensions extensions, 
			Base64String signature) {
		super(tNonce);
		if (devId==null || rid==null || nonce==null || time==null || infos==null
				|| signature==null)
			throw new IllegalArgumentException();
		certificateChain = (chain==null
							? null
							: (CertificateChain)chain.nonEmptyOrNull());
		dateTime = time;
		deviceId = devId;
		domainId = domId;
		this.extensions = (extensions==null
							? null
							: (RoRequestExtensions) extensions.nonEmptyOrNull());
		this.nonce = nonce;
		riId = rid;
		roInfos = infos;
		this.signature = signature;
	}

	/*
	 * accessors
	 */

	public CertificateChain getCertificateChain() {
		return certificateChain;
	}

	public DateTimeString getDateTime() {
		return dateTime;
	}

	public RoapIdentifier getDeviceId() {
		return deviceId;
	}

	public DomainIdentifier getDomainId() {
		return domainId;
	}

	public RoRequestExtensions getExtensions() {
		return extensions;
	}

	public Nonce getNonce() {
		return nonce;
	}

	public RoapIdentifier getRiId() {
		return riId;
	}

	public RoInfos getRoInfos() {
		return roInfos;
	}

	public Base64String getSignature() {
		return signature;
	}
	
	protected String getDocumentName() {
		return "RORequest";
	}

	/* 
	 * implementing XmlDocument
	 * 
	 */

	public void setDomElement(IElement root) {
		super.setDomElement(root);
		getDeviceId().asDomChildOf(root,"deviceID");
		if (getDomainId()!=null) root.addChildElement("domainID",getDomainId().toString());
		getRiId().asDomChildOf(root,"riID");
		root.addChildElement("nonce",getNonce().toString());
		root.addChildElement("time",getDateTime().toString());
		getRoInfos().asDomChildOf(root);
		if (getCertificateChain()!=null) getCertificateChain().asDomChildOf(root);
		if (getExtensions()!=null) getExtensions().asDomChildOf(root);
		if (signature!=null) root.addChildElement("signature",signature.toString());	
	}

	public String documentName() {
		return "RORequest";
	}

	/* 
	 * instance creation from xml
	 * 
	 */

	public static RoRequest instanceFromDomElement(IElement elem) {
		Nonce tNonce = new Nonce(elem.getAttributeStringValue("triggerNonce"));
		RoapIdentifier devId = RoapIdentifier.instanceFromDomElement(elem.getChildElement("deviceID"));
		String domString = elem.getChildStringValue("domainID");
		DomainIdentifier domId = (domString==null) ? null : new DomainIdentifier(domString);
		RoapIdentifier riId = RoapIdentifier.instanceFromDomElement(elem.getChildElement("riID"));
		Nonce nonce = new Nonce(elem.getChildStringValue("nonce"));
		DateTimeString time = new DateTimeString(elem.getChildStringValue("time"));
		RoInfos infos = RoInfos.instanceFromDomElement(elem.getChildElement("roInfo"));
		CertificateChain chain = CertificateChain.instanceFromDomElement(elem.getChildElement("certificateChain"));
		IElement extElement = elem.getChildElement("extensions");
		if (extElement!=null && extElement.getAllChildren().isEmpty())
			throw new XmlException();
		RoRequestExtensions exts = 
			extElement==null ? null : RoRequestExtensions.instanceFromDomElement(extElement);
		Base64String sig = new Base64String(elem.getChildStringValue("signature"));
		return new RoRequest(tNonce,devId,domId,riId,nonce,time,infos,chain,exts,sig);
	}

	public void setSignature(Base64String signature) {
		this.signature = signature;
	}

}
