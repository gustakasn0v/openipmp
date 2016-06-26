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

import com.mutable.drmPlugin.tools.*;
import java.security.cert.*;
import java.io.*;

/**
 * Utility for conversion between base64 representation and java.security.cert.Certificate objects
 * 
 * 
 *
 */
public class CertificateHelper {
	
	public static Base64String cert2Base64String(Certificate cert) throws CertificateEncodingException  {
		return new Base64String(cert.getEncoded());
	}
	
	public static Certificate base64String2Cert(Base64String string) throws CertificateException {
		byte[] certBytes = string.asByteArray();
		ByteArrayInputStream is = new ByteArrayInputStream(certBytes);
		CertificateFactory cf = CertificateFactory.getInstance("X509");
		Certificate cert = cf.generateCertificate(is);
		return cert;

	}

}
