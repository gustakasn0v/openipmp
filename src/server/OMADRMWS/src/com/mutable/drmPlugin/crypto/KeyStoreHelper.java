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

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.cert.CertificateEncodingException;
import java.security.cert.CertificateException;
import java.security.interfaces.RSAPublicKey;
import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.Base64StringVector;

/**
 * Helper class for handling java keystores; not really used in the present server.
 * 
 * 
 *
 */
public class KeyStoreHelper {

	public KeyStoreHelper() {
		super();
		// TODO Auto-generated constructor stub
	}
	
	protected static KeyStore readKeyStore(String path, String type, String pass) throws IOException {
		KeyStore ks = null;
		FileInputStream is;
		try {
			is = new FileInputStream(path);
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
			return null;
		};
		try {
			ks = KeyStore.getInstance(type);
			ks.load(is, pass.toCharArray());
		} catch (Exception e) {
			e.printStackTrace();
			ks = null;
		} finally { is.close(); };
		return ks;
	}
	
	public static KeyStore readKeyStore(KeyStoreInfo info) throws IOException {
		return KeyStoreHelper.readKeyStore(info.getPath(),info.getType(),info.getPass());
	}
	
	public static boolean writeKeyStore(KeyStore ks, String path, String pass) throws IOException {
		FileOutputStream os;
		try {
			os = new FileOutputStream(path);
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
			return false;
		};
		try {
			ks.store(os, pass.toCharArray());
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		} finally { os.close(); };
		return true;
	}
	
	public static boolean writeKeyStore(KeyStore ks, KeyStoreInfo info) throws IOException {
		return writeKeyStore(ks,info.getPath(),info.getPass());
		
	}
	
	
	
	public static CertificateChain getCertChain(KeyStore ks, KeyIdentifier subject)  {
		Vector v = new Vector();
		try {
			java.security.cert.Certificate[] certs = ks.getCertificateChain(((X509SPKIHash)subject).getHash().toString());
			if (certs==null || certs.length<2) return null;
			for (int i=certs.length-2; i>=0; i--) 
				v.add(new Base64String(certs[i].getEncoded()));
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		} 
		return new CertificateChain(v);
	}
	
	public static void putCertChain(KeyStore ks, CertificateChain chain) throws CertificateException, KeyStoreException {
		for(int i=chain.getData().size()-1;  i>=0; i--) {
			java.security.cert.Certificate cert = CertificateHelper.base64String2Cert((Base64String)chain.getData().elementAt(i));
			PublicKeyImpl theKey = new PublicKeyImpl((RSAPublicKey)cert.getPublicKey());
			String hashAlias = ((X509SPKIHash)theKey.getIdentifier()).getHash().toString();
			ks.setCertificateEntry(hashAlias,cert);
		}
	}
	
	public static PublicKeyImplVector getPublicKeys(KeyStore ks, KeyIdentifiers ids) {
		Vector v = new Vector();
		for (Iterator i=ids.iterator();i.hasNext();) {
			String alias = ((X509SPKIHash)i.next()).getHash().toString();
			v.add(PublicKeyImpl.instanceFromKeyStore(ks,alias));
		};
		return new PublicKeyImplVector(v);
	}
	
	public static Base64StringVector getCertificates(KeyStore ks, KeyIdentifiers ids) {
		Vector v = new Vector();
		for(Iterator i=ids.iterator();i.hasNext();) {
			String alias = ((X509SPKIHash)i.next()).getHash().toString();
			try {
				v.add(CertificateHelper.cert2Base64String(ks.getCertificate(alias)));
			} catch (CertificateEncodingException e) {
				e.printStackTrace();
				return null;
			} catch (KeyStoreException e) {
				e.printStackTrace();
				return null;
			}			
		};
		return new Base64StringVector(v);
	}

}
