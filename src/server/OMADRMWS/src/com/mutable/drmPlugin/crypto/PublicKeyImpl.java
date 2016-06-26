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

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.security.KeyFactory;
import java.security.KeyStore;
import java.security.Signature;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.interfaces.RSAPublicKey;
import java.security.spec.X509EncodedKeySpec;

import javax.crypto.Cipher;

import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlChild;

/**
 * A wrapper around a java.security.interfaces.RSAPublicKey.
 * 
 * 
 *
 */
public class PublicKeyImpl extends XmlChild implements IPublicKey {
	
	protected RSAPublicKey theKey;
	
	public PublicKeyImpl(RSAPublicKey key) {
		theKey = key;
	}
	

	public Base64String encrypt(Base64String data) {
		byte[] crypt;
			try {
				Cipher c = Cipher.getInstance("RSA/ECB/PKCS1Padding");
				c.init(Cipher.ENCRYPT_MODE,theKey);
				crypt = c.doFinal(data.asByteArray());
			}
			catch (Exception e) {
				e.printStackTrace();
				return null;
			};
			return new Base64String(crypt);

	}

	public boolean verify(Base64String signature, String data) {
		byte[] theSig = signature.asByteArray();
		boolean result;
			
			try {
				Signature sigOb = Signature.getInstance("MD5withRSA");
				sigOb.initVerify(theKey);
				sigOb.update(data.getBytes());
				result = sigOb.verify(theSig);
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			};
			return result;
	}
	
	public boolean verify(Certificate cert) {
		try {
			cert.verify(theKey);
		} catch (Exception e) {
			return false;
		};
		return true;
	}
	
	public com.mutable.drmPlugin.roap.misc.KeyIdentifier getIdentifier() {
		X509SPKIHash kid;
		try {
			kid = new X509SPKIHash((new Base64String(
					new sun.security.x509.KeyIdentifier(theKey).getIdentifier())));
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		};
		return kid;
	}

	/**
	 * @return unencrypted x509 binary representation of the key
	 * 
	 */
	public byte[] asByteArray() {
		return theKey.getEncoded();
	}
	
	/**
	 * @return unencrypted x509 base64 representation of the key,
	 * without pem formatting
	 * 
	 */
	public Base64String asBase64String() {
		return new Base64String(asByteArray());
	}

	
	public IElement asDomChildOf(IElement father,String name) {
		return father.addChildElement(name,asBase64String().toString());
	}

	
	
	public String domName() { return "publicKey"; }

	/**
	 * generates an instance from unencrypted x509 binary encoding
	 */
	public static PublicKeyImpl instanceFromByteArray(byte[] encoded) {
		RSAPublicKey newKey;
		try {
			X509EncodedKeySpec ksp = new X509EncodedKeySpec(encoded);
			KeyFactory kf = java.security.KeyFactory.getInstance("RSA");
			newKey = (RSAPublicKey) kf.generatePublic(ksp);
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
		return new PublicKeyImpl(newKey);
	}
	/**
	 * generates an instance from unencrypted x509 base64 encoding without pem formatting
	 */
	
	public static PublicKeyImpl instanceFromBase64String(Base64String encoded) {
		return instanceFromByteArray(encoded.asByteArray());
	}
	
	public static PublicKeyImpl instanceFromDomElement(IElement elem) {
		try{
			return instanceFromBase64String(new Base64String(elem.getStringValue()));
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}				
	}
	/**
	 * @return extracts a public key from a java keystore, not really used for the current server
	 */
	public static PublicKeyImpl instanceFromKeyStore(KeyStore ks, String alias) {
		RSAPublicKey key;
		try {
			Certificate cert = ks.getCertificate(alias);
			key = (RSAPublicKey) cert.getPublicKey();

		} catch (Exception e) {
			e.printStackTrace();
			return null;
		};
		return new PublicKeyImpl(key);
	}
	/**
	 * @return extracts a public key from a java keystore, not really used for the current server
	 */
	
	public static PublicKeyImpl instanceFromKeyStore(KeyStore ks, KeyIdentifier id) {
		return instanceFromKeyStore(ks,((X509SPKIHash)id).getHash().toString());
	}
	
	/**
	 * 
	 * @param certString base64-encoding of a public key certificate
	 * @return present representation of the certified key, null if input is invalid
	 */
	public static PublicKeyImpl instanceFromEncodedCert(Base64String certString) {
		Certificate cert;
		try {
			cert = CertificateHelper.base64String2Cert(certString);
		} catch (CertificateException e) {
			return null;
		}
		return  new PublicKeyImpl((RSAPublicKey)cert.getPublicKey()); 
	}
	
	
	
	
	
	




}
