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

import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.IXmlChild;
/**
 * Adapter for java.security.interfaces.RSAPrivateKey.
 * 
 * 
 *
 */
public interface IPrivateKey extends IXmlChild {


	/**
	 * 
	 * @param data string to be signed
	 * @return base64-encoding of the MD5withRSA signature
	 */
	public Base64String sign(String data);
	
	/**
	 * In j14 the sun provider doesn't provide an implementation; bouncycastle
	 * provider is used for this server.

	 * 
	 * @param data base64-encoding of the  encryption
	 * @return base64-encoding of the plain text;  if RSA/ECB/PKCS1Padding decryption
	 * fails, null is returned
	 * 
	 */

	public Base64String decrypt(Base64String data);

}
