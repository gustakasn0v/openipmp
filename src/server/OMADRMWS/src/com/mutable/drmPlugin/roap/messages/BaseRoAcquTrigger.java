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
import com.mutable.drmPlugin.roap.ro.RoIdContentIds;
import com.mutable.drmPlugin.tools.*;
import com.mutable.drmPlugin.xml.*;

/**
 * The trigger component of RoAcquisitionTrigger messages.
 * 
 * 
 *
 */

public class BaseRoAcquTrigger extends BaseTriggerAbstract {
	
	protected RoIdContentIds contents;
	
	public BaseRoAcquTrigger(RoapIdentifier rid, Nonce nonce, UriValue url, 
			IdValue id, RoIdContentIds contents) {
		super(rid, nonce, url, id);
		if ( contents==null || contents.isEmpty() )
			throw new IllegalArgumentException();
		this.contents = contents;
	}
	public RoIdContentIds getContents() {
		return contents;
	}
	
	public String domName() { return "roAcquisition"; }
	
	public IElement asDomChildOf(IElement father) {
		IElement elem = super.asDomChildOf(father);
		contents.asDomChildrenOf(elem);
		return elem;
	}
	
	public static BaseRoAcquTrigger instanceFromDomElement(IElement elem) {
		RoapIdentifier rid = RoapIdentifier.instanceFromDomElement(elem.getChildElement("riID"));
		IdValue id = new IdValue(elem.getAttributeStringValue("id"));
		Nonce nonce = new Nonce(elem.getChildStringValue("nonce"));
		UriValue url = new UriValue(elem.getChildStringValue("roapURL"));
		RoIdContentIds contents= RoIdContentIds.instanceFromDomElement(elem);
		return new BaseRoAcquTrigger(rid,nonce,url,id,contents);
	}
	

}
