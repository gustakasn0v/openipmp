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

import java.security.NoSuchAlgorithmException;

import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.tools.Base64String;

/**
 * Implementation of IHasher.
 * 
 *
 */
public class Hasher implements IHasher {
	
	protected static java.security.MessageDigest md;
	
	static{
		try {
			md = java.security.MessageDigest.getInstance("SHA-1");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}

	public Base64String hash(String data) {
		md.update(data.getBytes());
		byte[] result = md.digest();
		md.reset();
		return new Base64String(result);
	}

	public KeyIdentifier makeKeyIdentifier(IPublicKey key) {
		return key.getIdentifier();
	}

}
