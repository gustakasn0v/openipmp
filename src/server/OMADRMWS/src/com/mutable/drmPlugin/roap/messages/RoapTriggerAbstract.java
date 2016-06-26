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

import com.mutable.drmPlugin.roap.imports.ds.*;
import com.mutable.drmPlugin.roap.imports.xenc.*;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.xml.*;

/**
 * The common content of  all server trigger messages of Roap protocols
 * 
 * 
 *
 */

public abstract class RoapTriggerAbstract extends ServerMessage  {
	
	protected Signature signature;
	protected EncryptedKey encKey;
	protected Version version;
	protected boolean proxy;



	public RoapTriggerAbstract(Signature signature, EncryptedKey key, 
			Version version, boolean proxy) {
		super();
		if ( version==null )
			throw new IllegalArgumentException();
		encKey = key;
		this.proxy = proxy;
		this.signature = signature;
		this.version = version;
	}

	/*
	 * accessors
	 */

	public EncryptedKey getEncKey() {
		return encKey;
	}

	public boolean isProxy() {
		return proxy;
	}

	public Signature getSignature() {
		return signature;
	}

	public Version getVersion() {
		return version;
	}

	/* 
	 * partial implementation of @see XmlDocument
	 * 
	 */

	public String documentName() { return "roapTrigger"; }
	
	/*
	 * hook for subclasses to complete the implementation of  XmlDocument
	 */
	
	protected IElement setDomElement(IElement elem, BaseTriggerAbstract theTrigger) {
		elem.addAttribute("version",getVersion().toString());
		if (isProxy()) elem.addAttribute("proxy","true");
		theTrigger.asDomChildOf(elem);
		if (signature!=null) signature.asDomChildOf(elem);
		if (encKey!=null) encKey.asDomChildOf(elem);
		return elem;
		
	}
	

}
