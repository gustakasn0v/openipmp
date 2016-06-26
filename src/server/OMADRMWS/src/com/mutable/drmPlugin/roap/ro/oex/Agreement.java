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

import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;

public class Agreement extends XmlChild {
	
	protected AgreementAssets assets;
	protected Permissions permissions;


	public AgreementAssets getAssets() {
		return assets;
	}

	public Permissions getPermissions() {
		return permissions;
	}

	public Agreement(AgreementAssets assets, Permissions permissions) {
		super();
		if (assets==null || assets.isEmpty()) throw new IllegalArgumentException();
		this.assets = assets;
		this.permissions = (permissions==null 
							? null 
							: (Permissions) permissions.nonEmptyOrNull());
	}
	
	public IElement asDomChildOf(IElement father, String path) {
		IElement newElem = super.asDomChildOf(father,path);
		assets.asDomChildrenOf(newElem);
		permissions.asDomChildrenOf(newElem);
		return newElem;
	}
	
	public String domName() { return "agreement"; }
	
	public static Agreement instanceFromDomElement(IElement elem) {
		AgreementAssets assets = AgreementAssets.instanceFromDomElements(elem.getChildElements("asset"));
		Permissions permissions = Permissions.instanceFromDomElements(elem.getChildElements("permission"));
		return new Agreement(assets,permissions);
	}

}
