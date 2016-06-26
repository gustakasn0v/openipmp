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
import java.security.KeyStore;
import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.crypto.IPrivateKey;
import com.mutable.drmPlugin.crypto.IPublicKey;
import com.mutable.drmPlugin.crypto.KeyStoreHelper;
import com.mutable.drmPlugin.crypto.PrivateKeyImpl;
import com.mutable.drmPlugin.roap.messages.extensions.CertificateCachingExtension;
import com.mutable.drmPlugin.roap.messages.extensions.DeviceDetails;
import com.mutable.drmPlugin.roap.messages.extensions.DomainNameWhiteList;
import com.mutable.drmPlugin.roap.messages.extensions.EmptyDeviceDetails;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.Base64StringVector;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;

/**
 * The class encapsulating all server-specific data.
 *  
 * 
 *
 */
public class RiContext extends AgentContextAbstract {
	
	protected ServerAbstract server;
	
	protected Base64String riCaCert;
	
	protected IPrivateKey privateKey;
	
	protected Base64StringVector trustedDeviceCerts;
	protected Base64StringVector ocspResponses;
	protected DomainNameWhiteList whiteList;
	protected Base64String serverInfo;
	protected EmptyDeviceDetails details;
	
	public RiContext(ServerAbstract server) {
		super();
		this.server = server;
	}

	
	public RiContext() { super(); }
	
	public RiContext(RoapIdentifier id, IPublicKey key, UriValue url, CertificateChain chain, KeyIdentifiers trusted, UriVector algorithms, Version version, CertificateCachingExtension caching, IPrivateKey privateKey, Base64StringVector responses, Base64String info, 
			Base64StringVector certs, DomainNameWhiteList list, EmptyDeviceDetails details) {
		super(id, key, url, chain, trusted, algorithms, version, caching);
		this.privateKey = privateKey;
		ocspResponses = responses;
		serverInfo = info;
		trustedDeviceCerts = certs;
		whiteList = list;
		this.details = details;
	}

	public Base64StringVector getOcspResponses() {
		return ocspResponses;
	}

	public Base64String getServerInfo() {
		return serverInfo;
	}

	public DomainNameWhiteList getWhiteList() {
		return whiteList;
	}

	public EmptyDeviceDetails getDetails() {
		return details;
	}

	public IPrivateKey getPrivateKey() {
		return privateKey;
	}
	
	public Base64String getRiCaCert() {
		return riCaCert;
	}


	public Base64StringVector getTrustedDeviceCerts() {
		return trustedDeviceCerts;
	}

	public boolean isRi() { return true; }
	
	/* implementing IxmlDocument */
	
	public void setDomElement(IElement newElem) {
		super.setDomElement(newElem);
		for(Iterator i=getOcspResponses().iterator();i.hasNext();)
			newElem.addChildElement("ocspResponse", i.next().toString());
		newElem.addChildElement("serverInfo", getServerInfo().toString());
		IElement extElem = newElem.getChildElement("extensions");
		if (extElem==null) extElem = newElem.addChildElement("extensions");
		getWhiteList().asDomChildOf(extElem);
		getDetails().asDomChildOf(extElem);
	}
	
	public String documentName() { return "RIContext"; }
	
	public void setFromDomElement(IElement elem) throws IOException {
		super.setFromDomElement(elem);
		IElement trustedCertsElem = elem.getChildElement("trustedCerts");
		if (trustedCertsElem!=null) {
			Vector v = new Vector();
			IElements cElems = trustedCertsElem.getAllChildren();
			for(Iterator i = cElems.iterator();i.hasNext();)
				v.add(new Base64String(((IElement)i.next()).getStringValue()));
			trustedDeviceCerts = new Base64StringVector(v);
		};
		IElements rElems = elem.getChildElements("ocspResponse");
		Vector v = new Vector();
		for(Iterator i=rElems.iterator();i.hasNext();)
			v.add(new Base64String(((IElement)i.next()).getStringValue()));
		ocspResponses = new Base64StringVector(v);
		serverInfo = new Base64String(elem.getChildStringValue("serverInfo"));
		IElement extElem = elem.getChildElement("extensions");
		IElements exts = extElem.getAllChildren();
		for (Iterator i=exts.iterator();i.hasNext();) {
			IElement ee = (IElement) i.next();
			if (ee.getAttributeStringValue("xsi:type").equals("roap:DomainNameWhiteList"))
				whiteList = DomainNameWhiteList.instanceFromDomElement(ee);
			if (ee.getAttributeStringValue("xsi:type").equals("roap:DeviceDetails"))
				details = (EmptyDeviceDetails) DeviceDetails.instanceFromDomElement(ee);
				
		};
		
	}

	public static RiContext instanceFromDomElement(IElement elem) throws IOException {
		RiContext inst = new RiContext();
		inst.setFromDomElement(elem);
		return inst;
	}

	/**
	 * A service method for xml-keystores based server. 
	 * 
	 * @param ks
	 * @throws IOException
	 */
	public void setPrivateKeyFromKeyStore(KeyStore ks) throws IOException {
		privateKey = PrivateKeyImpl.instanceFromKeyStore(ks,
				id.getIdentifier(), ((ServerWithXml)server).getPrivateKeyPass());
		
	}
	
	/**
	 * A service method for xml-keystores based server. 
	 * 
	 * @param ks
	 * @throws IOException
	 */
	
	public void setTrustedCertsFromKeyStore(KeyStore ks)  {
		trustedDeviceCerts = KeyStoreHelper.getCertificates(ks,trusted);
		riCaCert = (Base64String) trustedDeviceCerts.getData().firstElement();

	}





	/* some setters */
	
	public void setPrivateKey(IPrivateKey privateKey) {
		this.privateKey = privateKey;
	}


	public void setRiCaCert(Base64String riCaCert) {
		this.riCaCert = riCaCert;
	}


	public void setTrustedDeviceCerts(Base64StringVector trustedDeviceCerts) {
		this.trustedDeviceCerts = trustedDeviceCerts;
	}
	

}
