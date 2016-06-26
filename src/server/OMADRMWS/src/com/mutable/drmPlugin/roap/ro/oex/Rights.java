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

import com.mutable.drmPlugin.xml.*;

public class Rights extends XmlChild {
	
	protected RightsContext context;
	protected Agreement agreement;



	public Rights(RightsContext context, Agreement agreement) {
		super();
		if (agreement==null || context==null)
			throw new IllegalArgumentException();
		this.agreement = agreement;
		this.context = context;
	}


	public Agreement getAgreement() {
		return agreement;
	}

	public RightsContext getContext() {
		return context;
	}
	
	public IElement asDomChildOf(IElement father,String path) {
		IElement newElem = super.asDomChildOf(father,path);
		setDomElement(newElem);
		return newElem;
	}
	
	public IDocument asDomDocument() {
		FactoryHelper fact = new FactoryHelper();
		DocumentHelper doc = (DocumentHelper) fact.createDocument("rights");
		setDomElement(doc.getRootElement());
		return doc;
	}

		
	public void setDomElement(IElement elem) {
		getContext().asDomChildOf(elem);
		getAgreement().asDomChildOf(elem);
	}
	
	public String domName() { return "rights"; }
	
	public static Rights instanceFromDomElement(IElement elem) {
		RightsContext ctx = RightsContext.instanceFromDomElement(elem.getChildElement("context"));
		Agreement agree = Agreement.instanceFromDomElement(elem.getChildElement("agreement"));
		return new Rights(ctx,agree);
	}

}
