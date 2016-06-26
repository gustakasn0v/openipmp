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
package com.mutable.drmPlugin.roap.ro;

import com.mutable.drmPlugin.roap.imports.ds.Signature;
import com.mutable.drmPlugin.roap.imports.xenc.EncryptedKey;
import com.mutable.drmPlugin.roap.misc.DateTimeString;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.DocumentHelper;
import com.mutable.drmPlugin.xml.ElementHelper;
import com.mutable.drmPlugin.xml.FactoryHelper;
import com.mutable.drmPlugin.xml.IDocument;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;



public class RoPayload extends XmlChild {
	
	protected RoapIdentifier riId;
	protected Rights rights;
	protected Signature signature;
	protected DateTimeString timeStamp;
	protected EncryptedKey encKey;
	protected Version version;
	protected IdValue id;
//	protected boolean stateful, domainRo;
	protected UriValue riUrl;
	
	


	public RoPayload(RoapIdentifier rid, Rights rights,
			Signature signature, DateTimeString stamp,
			EncryptedKey key, IdValue id,  
			 Version version, 
//			 boolean stateful, boolean ro, 
			 UriValue url)  {
		super();
		if ( rid==null || rights==null //|| signature==null || stamp==null
				|| key==null || id==null )
			throw new IllegalArgumentException();
//		domainRo = ro;
		encKey = key;
		this.id = id;
		this.rights = rights;
		riId = rid;
		riUrl = url;
		this.signature = signature;
//		this.stateful = stateful;
		timeStamp = stamp;
		this.version = version;
	}

	public boolean isDomainRo() {
		return false;
	}

	public EncryptedKey getEncKey() {
		return encKey;
	}

	public IdValue getId() {
		return id;
	}

	public Rights getRights() {
		return rights;
	}

	public RoapIdentifier getRiId() {
		return riId;
	}

	public UriValue getRiUrl() {
		return riUrl;
	}

	public Signature getSignature() {
		return signature;
	}

	public boolean isStateful() {
		return false;
	}

	public DateTimeString getTimeStamp() {
		return timeStamp;
	}

	public Version getVersion() {
		return version;
	}
	
	public IElement asDomChildOf(IElement father, String name) {
		IElement newElem = super.asDomChildOf(father,name);
		setDomElement(newElem);
		return newElem;
		
	}
	
	public void setDomElement(IElement newElem) {
		newElem.addAttribute("version",getVersion().toString());
		newElem.addAttribute("id",getId().toString());
		if (getRiUrl()!=null) newElem.addAttribute("riURL",getRiUrl().toString());
		getRiId().asDomChildOf(newElem, "riID");
		getRights().asDomChildOf(newElem);
		if (getSignature()!=null) getSignature().asDomChildOf(newElem);
		if (getTimeStamp()!=null) newElem.addChildElement("timeStamp",getTimeStamp().toString());
		getEncKey().asDomChildOf(newElem);
	}
	
	public String domName() { return "ro"; }
	
	public IDocument asDomDocument() {
		FactoryHelper fact = new FactoryHelper();
		DocumentHelper doc = (DocumentHelper) fact.createDocument("ro");
		ElementHelper root = (ElementHelper) doc.getRootElement();
		setDomElement(root);
		return doc;
	}


}
