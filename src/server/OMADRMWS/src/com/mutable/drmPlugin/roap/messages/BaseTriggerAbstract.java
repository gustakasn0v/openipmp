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

import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;

/**
 * The common content of trigger components of Roap-Trigger messages.
 * 
 *
 */
public abstract class BaseTriggerAbstract extends XmlChild {
	
	protected RoapIdentifier riId;
	protected Nonce nonce;
	protected UriValue roapUrl;
	protected IdValue id;
	


	public BaseTriggerAbstract(RoapIdentifier rid, Nonce nonce, 
			UriValue url, IdValue id) {
		super();
		if ( rid==null || url==null )
			throw new IllegalArgumentException();
		this.id = id;
		this.nonce = nonce;
		riId = rid;
		roapUrl = url;
	}

	public IdValue getId() {
		return id;
	}

	public Nonce getNonce() {
		return nonce;
	}

	public RoapIdentifier getRiId() {
		return riId;
	}

	public UriValue getRoapUrl() {
		return roapUrl;
	}

	public IElement asDomChildOf(IElement father, String name) {
		IElement newElem = father.addChildElement(name);
		newElem.addAttribute("id", getId().toString());
		getRiId().asDomChildOf(newElem,"riID");
		newElem.addChildElement("nonce",getNonce().toString());
		newElem.addChildElement("roapURL",getRoapUrl().toString());
		return newElem;
	
	}
	
	
}