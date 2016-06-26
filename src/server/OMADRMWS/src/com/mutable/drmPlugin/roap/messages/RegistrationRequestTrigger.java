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

import com.mutable.drmPlugin.roap.imports.ds.Signature;
import com.mutable.drmPlugin.roap.imports.xenc.EncryptedKey;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.*;

/**
 * RegistrationRequestTrigger message used by 
 * server to trigger the
 * 4-pass Roap registration protocol
 * 
 * currently not really used in this implementation
 * 
 * 
 *
 */

public class RegistrationRequestTrigger extends RoapTriggerAbstract {

	protected BaseRegRequestTrigger registrationRequest;


	public RegistrationRequestTrigger(BaseRegRequestTrigger request,
			Signature signature, EncryptedKey key, 
			Version version, boolean proxy ) {
		super(signature, key, version, proxy);
		if (request==null) throw new IllegalArgumentException();
		registrationRequest = request;
	}


	/*
	 * accessors
	 */


	public BaseRegRequestTrigger getRegistrationRequest() {
		return registrationRequest;
	}

	public IdValue getId() {
		return registrationRequest.getId();
	}

	public Nonce getNonce() {
		return registrationRequest.getNonce();
	}

	public RoapIdentifier getRiId() {
		return registrationRequest.getRiId();
	}

	public UriValue getRoapUrl() {
		return registrationRequest.getRoapUrl();
	}

	/*
	 * completing the implementation of @see XmlDocument using super hook
	 * 
	 */
	public void setDomElement(IElement elem) {
		super.setDomElement(elem,getRegistrationRequest());
	}
	

}
