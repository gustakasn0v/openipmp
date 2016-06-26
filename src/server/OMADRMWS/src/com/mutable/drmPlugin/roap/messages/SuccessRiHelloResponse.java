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

import com.mutable.drmPlugin.roap.messages.extensions.RiHelloExtensions;
import com.mutable.drmPlugin.roap.messages.status.SuccessStatus;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;
import com.mutable.drmPlugin.xml.IElement;

/**
 * Successful
 * RiHelloResponse server message of the
 * 4-pass Roap registration protocol
 * 
 * 
 *
 */

public class SuccessRiHelloResponse extends RiHelloResponse {
	
	protected SessionId sessionId;
	protected Version selectedVersion;
	protected RoapIdentifier riId;
	protected UriVector selectedAlgorithms;
	protected Nonce riNonce;
	protected KeyIdentifiers trustedAuthorities;	
	protected Base64String serverInfo;
	protected RiHelloExtensions extensions;



	
	public SuccessRiHelloResponse(SuccessStatus status, SessionId sid, 
								Version version, RoapIdentifier id, 
								UriVector algorithms, Nonce nonce, 
								KeyIdentifiers authorities, Base64String info,
								RiHelloExtensions extensions) {
		super(status);
		if ( sid==null || version==null || id==null || nonce==null ) 
			throw new IllegalArgumentException();
		this.extensions = (RiHelloExtensions) extensions.nonEmptyOrNull();
		riId = id;
		riNonce = nonce;
		selectedAlgorithms = (algorithms==null
								? algorithms
								: (UriVector) algorithms.nonEmptyOrNull());
		selectedVersion = version;
		serverInfo = info;
		sessionId = sid;
		trustedAuthorities = (authorities==null
								? null
								: (KeyIdentifiers) authorities);
	}

	/*
	 * accessors
	 */
	
	public RiHelloExtensions getExtensions() {
		return extensions;
	}

	public RoapIdentifier getRiId() {
		return riId;
	}

	public Nonce getRiNonce() {
		return riNonce;
	}

	public UriVector getSelectedAlgorithms() {
		return selectedAlgorithms;
	}

	public Version getSelectedVersion() {
		return selectedVersion;
	}

	public Base64String getServerInfo() {
		return serverInfo;
	}

	public SessionId getSessionId() {
		return sessionId;
	}

	public KeyIdentifiers getTrustedAuthorities() {
		return trustedAuthorities;
	}
	
	/*
	 * completing the implementation of XmlDocument
	 * 
	 */
	
	public  void setDomElement(IElement root) {
		super.setDomElement(root);
		root.addChildElement("selectedVersion",getSelectedVersion().toString());
		riId.asDomChildOf(root,"riID");
		for(Iterator i=getSelectedAlgorithms().iterator();i.hasNext();)
			root.addChildElement("selectedAlgorithm",((UriValue)i.next()).toString());
		root.addChildElement("riNonce",getRiNonce().toString());
		if (trustedAuthorities!=null) {
			IElement te = root.addChildElement("trustedAuthorities");
			for(Iterator i=getTrustedAuthorities().iterator();i.hasNext();)
				((X509SPKIHash)i.next()).asDomChildOf(te);
		};
		root.addChildElement("serverInfo",getServerInfo().toString());
		if (getExtensions()!=null) getExtensions().asDomChildOf(root);
		root.addAttribute("sessionId",getSessionId().toString());
	}

}
