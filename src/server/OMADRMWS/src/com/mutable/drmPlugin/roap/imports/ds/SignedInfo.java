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
import java.util.*;


public class SignedInfo extends XmlChild {
	
	protected CanonicalizationMethod canonMethod;
	protected SignatureMethod signMethod;
	protected References references;
	protected IdValue id;


	

	/**
	 * @param id is an optional attribute, others are mandatory elements
	 * @param references should be a nonempty sequence of Reference objects
	 *
	 */
	public SignedInfo(CanonicalizationMethod method, SignatureMethod method2, 
			References references, IdValue id) {
		super();
		if (method==null || method2==null || references==null || references.isEmpty()) 
			throw new IllegalArgumentException();
		canonMethod = method;
		this.id = id;
		this.references = references;
		signMethod = method2;
	}

	public CanonicalizationMethod getCanonMethod() {
		return canonMethod;
	}

	public IdValue getId() {
		return id;
	}

	public References getReferences() {
		return references;
	}

	public SignatureMethod getSignMethod() {
		return signMethod;
	}
	
	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		if (getId()!=null) newElem.addAttribute("ID",getId().toString());
		getCanonMethod().asDomChildOf(newElem);
		getSignMethod().asDomChildOf(newElem);
		getReferences().asDomChildrenOf(newElem);
		return newElem;
	}
	
	public static SignedInfo instanceFromDomElement(IElement elem) {
		String idString = elem.getAttributeStringValue("ID");
		IdValue id = (idString==null) ? null : new IdValue(idString);
		CanonicalizationMethod cm = new CanonicalizationMethod();
		SignatureMethod sm = new SignatureMethod();
		Vector v = new Vector();
		IElements refElems = elem.getChildElements("Reference");
		for(Iterator i=refElems.iterator();i.hasNext();)
			v.add(Reference.instanceFromDomElement((IElement)i.next()));
		References refs = new References(v);
		return new SignedInfo(cm,sm,refs,id);
	}

	public String domName() {
		return "SignedInfo";
	}

}
