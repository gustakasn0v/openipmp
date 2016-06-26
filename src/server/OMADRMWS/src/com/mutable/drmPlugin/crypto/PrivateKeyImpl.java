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

import java.security.KeyFactory;
import java.security.KeyStore;
import java.security.Signature;
import java.security.interfaces.RSAPrivateKey;
import java.security.spec.PKCS8EncodedKeySpec;

import javax.crypto.Cipher;

import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;

/**
 * A wrapper around  java.security.interfaces.RSAPrivateKey.
 * 
 * 
 *
 */

public class PrivateKeyImpl extends XmlChild implements IPrivateKey {
	
	protected RSAPrivateKey theKey;

	public PrivateKeyImpl(RSAPrivateKey theKey) {
		this.theKey = theKey;
	}

	public Base64String sign(String data) {
		byte[] sigBytes;
		try {
			Signature sig = Signature.getInstance("MD5withRSA");
			sig.initSign(theKey);
			sig.update(data.getBytes());
			sigBytes = sig.sign();
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		} ;
		return new Base64String(sigBytes);
	}

	public Base64String decrypt(Base64String data) {
		byte[] plain;
		try {
			Cipher c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
			c.init(Cipher.DECRYPT_MODE,theKey);
			plain = c.doFinal(data.asByteArray());
		}
		catch (Exception e) {
			e.printStackTrace();
			return null;
		};
		return new Base64String(plain);

}

	/**
	 * @return unencrypted pkcs8 binary representation of the key
	 * 
	 */
	public byte[] asByteArray() {
		return theKey.getEncoded();
	}
	
	/**
	 * @return unencrypted pkcs8 base64 representation of the key,
	 * without pem formatting
	 * 
	 */
	public Base64String asBase64String() {
		return new Base64String(asByteArray());
	}
	
	public IElement asDomChildOf(IElement father,String name) {
		return father.addChildElement(name,asBase64String().toString());
	}
	
	public String domName() { return "privateKey"; }

	public static PrivateKeyImpl instanceFromDomElement(IElement elem) {
		try{
			return instanceFromBase64String(new Base64String(elem.getStringValue()));
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}				
	}

	/**
	 * @return extracts a private key from a java keystore, not really used for the current server
	 */
	
	public static PrivateKeyImpl instanceFromKeyStore(KeyStore ks, String alias, String keyPass) {
		RSAPrivateKey key;

		try {
			key = (RSAPrivateKey) ks.getKey(alias, keyPass.toCharArray());
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		};
		return new PrivateKeyImpl(key);
	}

	/**
	 * @return extracts a private key from a java keystore, not really used for the current server
	 */

	public static PrivateKeyImpl instanceFromKeyStore(KeyStore ks, KeyIdentifier id, String pass) {
		return instanceFromKeyStore(ks,((X509SPKIHash)id).getHash().toString(),pass);
	}
	
	/**
	 * generates an instance from unencrypted pkcs8 binary encoding
	 */
	public static PrivateKeyImpl instanceFromByteArray(byte[] encoded) {
		RSAPrivateKey newKey;
		try {
			PKCS8EncodedKeySpec ksp = new PKCS8EncodedKeySpec(encoded);
			KeyFactory kf = java.security.KeyFactory.getInstance("RSA");
			newKey = (RSAPrivateKey) kf.generatePrivate(ksp);
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
		return new PrivateKeyImpl(newKey);
	}

	/**
	 * generates an instance from unencrypted pkcs8 base64 encoding withour pem formatting
	 */

	public static PrivateKeyImpl instanceFromBase64String(Base64String encoded) {
		return instanceFromByteArray(encoded.asByteArray());
	}

}
