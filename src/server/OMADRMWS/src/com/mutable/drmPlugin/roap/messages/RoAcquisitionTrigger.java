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
import com.mutable.drmPlugin.roap.ro.RoIdContentIds;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;

/**
 * RoAcquisitionTrigger message used by 
 * server to trigger the
 * 2-pass Roap rights acquisition protocol.
 * 
 * In this implementation of the server used as a response to InitialRoRequest
 * 
 * 
 *
 */

public class RoAcquisitionTrigger extends RoapTriggerAbstract {
	

	protected BaseRoAcquTrigger roAcquisition;


	public RoAcquisitionTrigger(BaseRoAcquTrigger acquisition,
			Signature signature, EncryptedKey key, 
			Version version, boolean proxy) {
		super(signature, key, version, proxy);
		if (acquisition==null) throw new IllegalArgumentException();
		roAcquisition = acquisition;
	}

	/*
	 * accessors
	 */

	public BaseRoAcquTrigger getRoAcquisition() {
		return roAcquisition;
	}

	public IdValue getId() {
		return roAcquisition.getId();
	}

	public Nonce getNonce() {
		return roAcquisition.getNonce();
	}

	public RoapIdentifier getRiId() {
		return roAcquisition.getRiId();
	}

	public UriValue getRoapUrl() {
		return roAcquisition.getRoapUrl();
	}

	public RoIdContentIds getContents() {
		return roAcquisition.getContents();
	}

	/*
	 * completing the implementation of XmlDocument using super hook
	 * 
	 */

	public void setDomElement(IElement elem) {
		super.setDomElement(elem,getRoAcquisition());
	}
	


}
