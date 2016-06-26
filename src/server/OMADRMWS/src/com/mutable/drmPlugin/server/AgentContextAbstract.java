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

import com.mutable.drmPlugin.crypto.IPublicKey;
import com.mutable.drmPlugin.crypto.KeyStoreHelper;
import com.mutable.drmPlugin.crypto.PublicKeyImpl;
import com.mutable.drmPlugin.roap.messages.extensions.CertificateCachingExtension;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.IElements;
import com.mutable.drmPlugin.xml.XmlData;

/**
 * The common content of DeviceContext and RiContext
 * 
 * 
 * 
 * @see DeviceContext  RiContext
 *
 */
public abstract class AgentContextAbstract extends XmlData {
	
	protected RoapIdentifier id;
	protected IPublicKey publicKey;
	protected UriValue url;
	protected CertificateChain certChain;
	protected KeyIdentifiers trusted;
	protected UriVector algorithms;
	protected Version version;
	protected CertificateCachingExtension caching;
	
	
	/* hook for subclasses */
	
	protected AgentContextAbstract(){};
	
	/**
	 * constructor
	 * @param id is required
	 * @param key
	 * @param url
	 * @param chain
	 * @param trusted
	 * @param algorithms
	 * @param version
	 * @param caching
	 */
	public AgentContextAbstract(RoapIdentifier id, IPublicKey key,
			UriValue url, CertificateChain chain, 
			 KeyIdentifiers trusted, UriVector algorithms,
			 Version version, CertificateCachingExtension caching) {
		
		super();
		if (id==null)
			throw new IllegalArgumentException();
		this.algorithms = algorithms;
		certChain = chain;
		this.id = id;
		publicKey = key;
		this.trusted = trusted;
		this.url = url;
		this.version = version;
		this.caching = caching;
	}

	/* accessors */
	
	public UriVector getAlgorithms() {
		return algorithms;
	}

	public CertificateChain getCertChain() {
		return certChain;
	}

	public RoapIdentifier getId() {
		return id;
	}

	public IPublicKey getPublicKey() {
		return publicKey;
	}

	public KeyIdentifiers getTrusted() {
		return trusted;
	}

	public UriValue getUrl() {
		return url;
	}

	public CertificateCachingExtension getCaching() {
		return caching;
	}

	public Version getVersion() {
		return version;
	}
	
	public boolean isRi() { return false; }
	
	/* implementing IXmlDocument */
	
	public void setDomElement(IElement newElem){
		id.asDomChildOf(newElem,"id");
		if (url!=null)
			newElem.addChildElement("url",url.toString());
		if (!isRi()) {
			if (certChain!=null) certChain.asDomChildOf(newElem);
			if (trusted!=null) {
			IElement trustedElem = newElem.addChildElement("trustedAuthorites");
			java.util.Vector trustedIds = trusted.getData();
			for (Iterator i=trustedIds.iterator();i.hasNext();)
				((X509SPKIHash)i.next()).asDomChildOf(trustedElem);
			};
		};
		if (algorithms!=null && !algorithms.isEmpty()) {
			IElement algoElem = newElem.addChildElement("algorithms");
			for (Iterator i=algorithms.iterator();i.hasNext();)
				algoElem.addChildElement("algorithm",i.next().toString());
		};
		if (version!=null) version.asDomChildOf(newElem,"version");
		if (caching!=null) {
			IElement extElem = newElem.addChildElement("extensions");
			caching.asDomChildOf(extElem);
		};		
	}
	
	public void setFromDomElement(IElement elem) throws IOException {
		IElement idElem = elem.getChildElement("id");
		id = new RoapIdentifier(X509SPKIHash.instanceFromDomElement(idElem.getChildElement("keyIdentifier")));
		String urlString = elem.getChildStringValue("url");
		url = (urlString==null) ? null : new UriValue(urlString);
		IElement chainElem = elem.getChildElement("certificateChain");
		if (chainElem!=null) {
			certChain = CertificateChain.instanceFromDomElement(chainElem);
			publicKey = PublicKeyImpl.instanceFromEncodedCert((Base64String) certChain.getData().lastElement());
		};
		IElement trustedElem = elem.getChildElement("trustedAuthorities");
		if (trustedElem!=null) {
			IElements trustedElems = trustedElem.getChildElements("keyIdentifier");
			java.util.Vector trustedIds = new java.util.Vector();
			trusted = new KeyIdentifiers(trustedIds);
			for (int i=0; i<trustedElems.getData().size(); i++)
				trustedIds.add(X509SPKIHash.instanceFromDomElement((IElement)trustedElems.getData().elementAt(i)));
		};
		java.util.Vector algos = new java.util.Vector();
		algorithms = new UriVector(algos);
		IElement algoElem = elem.getChildElement("algorithms");
		if (algoElem!=null) {
			for (Iterator i=algoElem.getChildElements("algorithm").iterator();i.hasNext();) {
				algos.add(new UriValue(((IElement)i.next()).getStringValue()));
			};
		};
		version = Version.instanceFromDomElement(elem.getChildElement("version"));
		IElement extElem = elem.getChildElement("extensions");
		if (extElem!=null) {
			IElements exts = extElem.getAllChildren();
			for (Iterator i=exts.iterator(); i.hasNext();) {
				IElement ee = (IElement) i.next();
				if (ee.getAttributeStringValue("xsi:type").equals("roap:CertificateCaching"))
					caching = CertificateCachingExtension.instanceFromDomElement(ee);				
			}
		}
	}
	
	/**
	 * a service method for xml-keystores version of the server
	 * 
	 * @param ks
	 */
	public void setChainAndKeyFromStore(KeyStore ks) {
		certChain = KeyStoreHelper.getCertChain(ks,id.getIdentifier());
		publicKey = PublicKeyImpl.instanceFromKeyStore(ks,id.getIdentifier());
		if (certChain==null || publicKey==null) throw new Error("keystore error");
		
	}

	/* some setters */
	
	public void setAlgorithms(UriVector algorithms) {
		this.algorithms = algorithms;
	}

	public void setCaching(CertificateCachingExtension caching) {
		this.caching = caching;
	}

	public void setCertChain(CertificateChain certChain) {
		this.certChain = certChain;
	}

	public void setId(RoapIdentifier id) {
		this.id = id;
	}

	public void setPublicKey(IPublicKey publicKey) {
		this.publicKey = publicKey;
	}

	public void setTrusted(KeyIdentifiers trusted) {
		this.trusted = trusted;
	}

	public void setUrl(UriValue url) {
		this.url = url;
	}

	public void setVersion(Version version) {
		this.version = version;
	}

}
