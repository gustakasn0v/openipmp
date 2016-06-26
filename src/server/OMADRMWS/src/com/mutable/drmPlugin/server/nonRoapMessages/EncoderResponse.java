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
import com.mutable.drmPlugin.xml.IElement;

/**
 * the class representing two forms of response to
 * two kinds of encoder messages
 * 
 * 
 *
 */
public abstract class EncoderResponse extends ServerMessage {
	
	protected boolean success;
	protected Nonce nonce;

	/**
	 * constructor
	 * @param nonce is mandatory
	 */

	public EncoderResponse(Nonce nonce, boolean success) {
		super();
//		if (nonce==null) throw new IllegalArgumentException();
		this.nonce = nonce;
		this.success = success;
	}

	/**
	 * accessors
	 */

	public Nonce getNonce() {
		return nonce;
	}

	public boolean isSuccess() {
		return success;
	}

	/** 
	 * partial implementation of @see XmlDocument
	 * 
	 */
	public void setDomElement(IElement root) {	
		root.addChildElement("success", (new Boolean(success)).toString());
		root.addChildElement("nonce", (nonce!=null) ? nonce.toString() : "");
		
	}
	


}
