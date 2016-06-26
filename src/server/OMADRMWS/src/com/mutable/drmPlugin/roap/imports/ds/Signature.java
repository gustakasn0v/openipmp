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
package com.mutable.drmPlugin.roap.imports.ds;

import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.xml.*;

public class Signature extends XmlChild {
	
	protected SignedInfo sigInfo;
	protected SignatureValue sigValue;
	protected KeyInfo keyInfo;
	protected Objects objects;
	protected IdValue id;
	

	

	
	/**
	 * 
	 * @param sinfo and  @param value are mandatory elements,	 
	 * @param kinfo and @param objects are optional, and
	 * @param id is an optional attribute
	 */

	public Signature(SignedInfo sinfo, SignatureValue value,  
			KeyInfo kinfo, Objects objects, IdValue id) {
		super();
		if (/* sinfo==null ||  */ value==null) throw new IllegalArgumentException();
		this.id = id;
		keyInfo = kinfo;
		this.objects = (objects==null ? null : (Objects) objects.nonEmptyOrNull());
		sigInfo = sinfo;
		sigValue = value;
	}

	public IdValue getId() {
		return id;
	}

	public KeyInfo getKeyInfo() {
		return keyInfo;
	}

	public Objects getObjects() {
		return objects;
	}

	public SignedInfo getSigInfo() {
		return sigInfo;
	}

	public SignatureValue getSigValue() {
		return sigValue;
	}
	
	public IElement asDomChildOf(IElement father, String name) {
		IElement newElem = super.asDomChildOf(father,name);
		if (getId()!=null) newElem.addAttribute("Id",getId().toString());
		getSigInfo().asDomChildOf(newElem);
		newElem.addChildElement("SignatureValue",getSigValue().toString());
		return newElem;
	}
	
	
	public static Signature instanceFromDomElement(IElement elem) {
		String idString = elem.getAttributeStringValue("Id");
		IdValue id = (idString==null) ? null : new IdValue(idString);
		SignedInfo sinfo = SignedInfo.instanceFromDomElement(elem.getChildElement("SignedInfo"));
		return new Signature(sinfo,new SignatureValue(elem.getChildStringValue("SignatureValue"),null),null,null,id);
	}

	public String domName() {
		return "Signature";
	}

}
