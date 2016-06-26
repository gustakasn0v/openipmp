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
package com.mutable.drmPlugin.server.nonRoapMessages;

import com.mutable.drmPlugin.tools.*;
import com.mutable.drmPlugin.roap.messages.*;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.xml.*;

/**
 * The encoder message
 * sending the encryption key for a content
 * 
 * 
 *
 */
public class AddContentKeyRequest extends ServerMessage {

	protected UriValue content;
	protected Base64String encKey;
	protected Nonce nonce;
	

/**
 * constructor
 */
	public AddContentKeyRequest(UriValue content, Base64String key, Nonce nonce) {
		super();
		if (content==null || key==null || nonce==null)
			throw new IllegalArgumentException();
		this.content = content;
		encKey = key;
		this.nonce = nonce;
	}

	/**
	 * accessors
	 */
	public UriValue getContent() {
		return content;
	}

	public Base64String getEncKey() {
		return encKey;
	}

	public Nonce getNonce() {
		return nonce;
	}

	/** 
	 * implementing @see XmlDocument
	 * 
	 */
	public void setDomElement(IElement root) {
		root.addChildElement("contentID", content.toString());
		root.addChildElement("encryptionKey", encKey.toString());
		root.addChildElement("nonce", nonce.toString());		
	}

	public String documentName() { return "addContentKeyRequest"; }
	
	/** 
	 * instance creationfrom xml
	 * 
	 */
	public static AddContentKeyRequest instanceFromDomElement(IElement elem) {
		return new AddContentKeyRequest(
				new UriValue(elem.getChildStringValue("contentID")),
				new Base64String(elem.getChildStringValue("encryptionKey")),
				new Nonce(elem.getChildStringValue("nonce")));
		
	}
	

}
