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
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;

public class Reference extends XmlChild {
	
	protected Transforms transforms;
	protected DigestMethod digestMethod;
	protected DigestValue digestValue;
	protected IdValue id;
	protected UriValue uri, type;
	


	/**
	 * 
	 * @param method and  @param value are mandatory elements
	 * @param tr is an optional element
	 * @param id , @param type and @param uri are optional attributes
	 */
	public Reference(DigestMethod method, DigestValue value, 
			IdValue id, Transforms tr, UriValue type, UriValue uri) {
		super();
		if (method==null || value==null) 
			throw new IllegalArgumentException();
		digestMethod = method;
		digestValue = value;
		this.id = id;
		this.transforms = (tr==null ? null : (Transforms) tr.nonEmptyOrNull());
		this.type = type;
		this.uri = uri;
	}

	public DigestMethod getDigestMethod() {
		return digestMethod;
	}

	public DigestValue getDigestValue() {
		return digestValue;
	}

	public IdValue getId() {
		return id;
	}

	public Transforms getTransforms() {
		return transforms;
	}

	public UriValue getType() {
		return type;
	}

	public UriValue getUri() {
		return uri;
	}
	
	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		if (getId()!=null) newElem.addAttribute("ID",getId().toString());
		if (getType()!=null) newElem.addAttribute("type",getType().toString());
		if (getUri()!=null) newElem.addAttribute("URI",getUri().toString());
		getDigestMethod().asDomChildOf(newElem);
		newElem.addChildElement("DigestValue",getDigestValue().toString());
		return newElem;
		
	}
	
	public static Reference instanceFromDomElement(IElement elem) {
		String idString = elem.getAttributeStringValue("ID");
		IdValue id = (idString==null) ? null : new IdValue(idString);
		String typeString = elem.getAttributeStringValue("type");
		UriValue type = (typeString==null) ? null : new UriValue(typeString);
		String uriString = elem.getAttributeStringValue("URI");
		UriValue uri = (uriString==null) ? null : new UriValue(uriString);
		DigestMethod dm = DigestMethod.instanceFromDomElement(elem.getChildElement("DigestMethod"));
		DigestValue dv = new DigestValue(elem.getChildStringValue("DigestValue"));
		return new Reference(dm,dv,id,null,type,uri);
	}

	public String domName() {
		return "Reference";
	}

}
