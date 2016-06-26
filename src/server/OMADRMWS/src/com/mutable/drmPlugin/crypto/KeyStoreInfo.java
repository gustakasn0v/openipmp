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
package com.mutable.drmPlugin.crypto;

import com.mutable.drmPlugin.xml.*;

/**
 * Structure holding data about a java keystore, not really used in the current server.
 * 
 * 
 *
 */

public class KeyStoreInfo {

	public KeyStoreInfo() {
		super();
		// TODO Auto-generated constructor stub
	}
	
	protected String path, type, pass;
	
	public static String defaultType() { return "JKS"; }
	public static String defaultPass() { return "omadrm";}



	public String getPass() {
		if (pass==null) return KeyStoreInfo.defaultPass();
		return pass;
	}
	public String getPath() {
		return path;
	}
	public String getType() {
		if (type==null) return KeyStoreInfo.defaultType();
		return type;
	}
	public KeyStoreInfo(String path, String type, String pass) {
		super();
		// TODO Auto-generated constructor stub
		this.path = path;
		this.type = type;
		this.pass = pass;
	}
	public KeyStoreInfo(String path, String type) {
		super();
		// TODO Auto-generated constructor stub
		this.path = path;
		this.type = type;
	}
	public KeyStoreInfo(String path) {
		super();
		// TODO Auto-generated constructor stub
		this.path = path;
	}
	
	public IElement asDomChildOf(IElement father) {
		IElement newElem = father.addChildElement("KeyStore");
		newElem.addAttribute("path",path);
		if (type!=null) newElem.addAttribute("type",type);
		if (pass!=null) newElem.addAttribute("pass",pass);
		return newElem;
	}
	
	public IElement asDomChildOf(IElement father, String name) {
		IElement newElem = father.addChildElement(name);
		asDomChildOf(newElem);
		return newElem;
	}
	
	public static KeyStoreInfo instanceFromDomElement(IElement elem) {
		return new KeyStoreInfo(elem.getAttributeStringValue("path"),
						elem.getAttributeStringValue("type"),
						elem.getAttributeStringValue("pass"));
	}
	
}
