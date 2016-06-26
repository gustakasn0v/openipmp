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
package com.mutable.drmPlugin.roap.imports.xenc;

import com.mutable.drmPlugin.roap.imports.ds.KeyInfo;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.*;

public class EncryptedKey extends Encrypted {
	
	protected ReferenceList refList;
	protected Base64String carriedKeyName, recipient;
	public EncryptedKey(EncryptionMethod method, KeyInfo info, CipherData data, EncryptionProperties properties, IdValue id, UriValue type, Base64String mime, UriValue encoding, Base64String name, Base64String recipient, ReferenceList list) {
		super(method, info, data, properties, id, type, mime, encoding);
		// TODO Auto-generated constructor stub
		carriedKeyName = name;
		this.recipient = recipient;
		refList = list;
	}
	public Base64String getCarriedKeyName() {
		return carriedKeyName;
	}
	public Base64String getRecipient() {
		return recipient;
	}
	public ReferenceList getRefList() {
		return refList;
	}
	
	public String domName() { return "encKey.CipherData.CipherValue"; }
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("encKey.CipherData.CipherValue",
							((CValueCipherData) getCipherData()).toString());
		return newElem;
	}

}
