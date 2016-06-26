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
package com.mutable.drmPlugin.roap.ro.oex;

import com.mutable.drmPlugin.roap.imports.ds.KeyInfo;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.xml.*;

public class AgreementAsset extends Asset {
	
	protected IdValue id;
	protected AssetContext context;
	protected Inherit inherit;
	protected Digest digest;
	protected KeyInfo keyInfo;
	


	

	public AgreementAsset(IdValue id, 
			AssetContext context, Inherit inherit, 
			Digest digest, KeyInfo info) {
		this.context = context;
		this.digest = digest;
		this.id = id;
		this.inherit = inherit;
		keyInfo = info;
	}


	public String XmlEncode(String varName) {
		// TODO Auto-generated method stub
		return null;
	}

	public Context getContext() {
		return context;
	}

	public Digest getDigest() {
		return digest;
	}

	public IdValue getId() {
		return id;
	}

	public Inherit getInherit() {
		return inherit;
	}

	public KeyInfo getKeyInfo() {
		return keyInfo;
	}
	
	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		if (getId()!=null) newElem.addAttribute("id",getId().toString());
		if (getContext()!=null) getContext().asDomChildOf(newElem);
		if (getInherit()!=null) getInherit().asDomChildOf(newElem);
		if (getDigest()!=null) getDigest().asDomChildOf(newElem);
		return newElem;
	}
	
	public static AgreementAsset instanceFromDomElement(IElement elem) {
		String idString = elem.getAttributeStringValue("id");
		IdValue id = (idString==null) ? null : new IdValue(idString);
		IElement ctxElem = elem.getChildElement("context");
		AssetContext ctx = (ctxElem==null) ? null : AssetContext.instanceFromDomElement(ctxElem);
		IElement inhElem = elem.getChildElement("inherit");
		Inherit inh = (inhElem==null) ? null : Inherit.instanceFromDomElement(inhElem);
		IElement digElem = elem.getChildElement("digest");
		Digest dig = (digElem==null) ? null : Digest.instanceFromDomElement(digElem);
		return new AgreementAsset(id,ctx,inh,dig,null);
	}

}
