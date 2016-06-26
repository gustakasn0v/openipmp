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
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.interfaces.RSAPublicKey;
import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.Base64StringVector;

/**
 * Implementation of ICertificateVerifier.
 * 
 *
 */
public class CertificateVerifier implements ICertificateVerifier {
	
	protected PublicKeyImplVector trustedKeys;
	
	public CertificateVerifier(Base64StringVector trustedCerts) {
//		if (trustedCerts==null||trustedCerts.isEmpty()) 
//			throw new IllegalArgumentException();
		Vector v = new Vector();
		for(Iterator i=trustedCerts.iterator();i.hasNext();)
			v.add(PublicKeyImpl.instanceFromEncodedCert((Base64String)i.next()));
		this.trustedKeys = new PublicKeyImplVector(v);
		
	}

	public CertificateVerifier(PublicKeyImplVector trustedKeys) {
		super();
//		if (trustedKeys==null||trustedKeys.isEmpty()) 
//			throw new IllegalArgumentException();
		this.trustedKeys = trustedKeys;
	}

	public IPublicKey verifyChain(CertificateChain chain) {
		if (chain==null||chain.isEmpty()) return null;
		/* the weird OMADRM border case when a server should trust any certificate */
		if (trustedKeys==null || trustedKeys.isEmpty()) {
			Base64String cert = (Base64String) chain.getData().lastElement();
			return PublicKeyImpl.instanceFromEncodedCert(cert);
		}
		Iterator i = chain.iterator();
		PublicKeyImpl found = (PublicKeyImpl) verifyFirst((Base64String)i.next());
		for (;i.hasNext();) {
			found = (PublicKeyImpl) verifyAny((Base64String)i.next(), found);
			if (found==null) return found;
		}
		return found;
	}

	
	protected IPublicKey verifyFirst(Base64String certString) {
		for (Iterator i=trustedKeys.iterator(); i.hasNext();){
			PublicKeyImpl theKey = (PublicKeyImpl) i.next();
			PublicKeyImpl foundKey = (PublicKeyImpl) verifyAny(certString, theKey);
			if (foundKey!=null) return foundKey;
		};
		return null;
	}
	
	protected IPublicKey verifyAny(Base64String certString, PublicKeyImpl key) {
		Certificate cert;
		try {
			cert = CertificateHelper.base64String2Cert(certString);
		} catch (CertificateException e) {
			return null;
		}
		return (key.verify(cert)) 
			    ? new PublicKeyImpl((RSAPublicKey)cert.getPublicKey()) 
			    : null;
	}

	

}
