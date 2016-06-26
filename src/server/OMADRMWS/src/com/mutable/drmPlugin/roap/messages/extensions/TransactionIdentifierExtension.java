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
package com.mutable.drmPlugin.roap.messages.extensions;

import com.mutable.drmPlugin.roap.misc.TransactionId;
import com.mutable.drmPlugin.roap.misc.TransactionIds;
import com.mutable.drmPlugin.tools.*;
import com.mutable.drmPlugin.xml.*;
import java.util.*;

public class TransactionIdentifierExtension extends Extension {
	
	protected TransactionIds ids;


	public TransactionIdentifierExtension(boolean cr, TransactionIds ids) {
		super(cr);
		if (ids==null || ids.isEmpty()) throw new IllegalArgumentException();
		this.ids = ids;
	}

	public TransactionIds getIds() {
		return ids;
	}
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = super.asDomChildOf(father);
		for(Iterator i=ids.iterator();i.hasNext();) {
			TransactionId tid = (TransactionId) i.next();
			newElem.addChildElement("contentId",tid.getContentId().toString());
			newElem.addChildElement("id",tid.getId().toString());
		};
		return newElem;
	}
	
	public static TransactionIdentifierExtension instanceFromDomElement(IElement elem) {
		boolean cr = elem.getAttributeBooleanValue("critical");
		IElements elems = elem.getAllChildren();
		Vector v = new Vector();
		for(Iterator i=elems.iterator();i.hasNext();) {
			UriValue cid = new UriValue(((IElement)i.next()).getStringValue());
			StringValue id = new StringValue(((IElement)i.next()).getStringValue());
			v.add(new TransactionId(cid,id));
		};
		return new TransactionIdentifierExtension(cr,new TransactionIds(v));
	}

	protected String xsiType() {
		return "roap:TransactionIdentifier";
	}

}
