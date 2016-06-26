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

import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.IXmlChild;

/**
 * Adapter for java.security.interfaces.RSAPubliceKey.
 * 
 * 
 *
 */
public interface IPublicKey extends IXmlChild {
	/**
	 * verifies base64-encoding of a MD5withRSA signature of data 
	 * 
	 */
	public boolean verify(Base64String signature, String data);
	/**
	 * 
	 * @param data base64-encoding of the subject
	 * @return base64-encoding of the RSA/ECB/PKCS1Padding encryption of the subject
	 */
	public Base64String encrypt(Base64String data);
	
	/**
	 * @return identifier according to "http://www.w3.org/2000/09/xmldsig#sha1"
	 * @see KeyIdentifier
	 * 
	 */
	public KeyIdentifier getIdentifier();

}
