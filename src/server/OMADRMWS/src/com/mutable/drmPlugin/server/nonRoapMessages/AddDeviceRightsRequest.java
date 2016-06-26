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

import com.mutable.drmPlugin.roap.messages.ServerMessage;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;

/**
 * The encoder message
 * sending rights for a content for a device
 * 
 * 
 *
 */

public class AddDeviceRightsRequest extends ServerMessage {
	
	protected Rights rights;
	protected RoapIdentifier deviceId;
	protected UriValue contentId;
	protected Nonce nonce;
	
	/**
	 * constructor
	 */


	public AddDeviceRightsRequest(Rights rights, UriValue cid, RoapIdentifier rid, Nonce nonce) {
		super();
		if (rights==null || cid==null || rid==null || nonce==null)
			throw new IllegalArgumentException();
		contentId = cid;
		deviceId = rid;
		this.nonce = nonce;
		this.rights = rights;
	}

	/**
	 * accessors
	 */

	public UriValue getContentId() {
		return contentId;
	}

	public RoapIdentifier getDeviceId() {
		return deviceId;
	}

	public Nonce getNonce() {
		return nonce;
	}

	public Rights getRights() {
		return rights;
	}

	/** 
	 * implementing @see XmlDocument
	 * 
	 */
	public void setDomElement(IElement root) {	
		rights.asDomChildOf(root);
		deviceId.asDomChildOf(root,"deviceID");
		root.addChildElement("contentID", contentId.toString());
		root.addChildElement("nonce", nonce.toString());
	}
	
	public String documentName() { return "addContentKeyRequest"; }

	/** 
	 * instance creation from xml
	 * 
	 */

	public static AddDeviceRightsRequest instanceFromDomElement(IElement elem) {
		return new AddDeviceRightsRequest(
				Rights.instanceFromDomElement(elem.getChildElement("rights")),
				new UriValue(elem.getChildStringValue("contentID")),
				RoapIdentifier.instanceFromDomElement(elem.getChildElement("deviceID")),
				new Nonce(elem.getChildStringValue("nonce")));
		
	}

}
