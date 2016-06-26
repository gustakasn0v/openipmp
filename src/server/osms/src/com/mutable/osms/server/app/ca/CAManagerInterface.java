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
 * The Original Code is OpenIPMP.
 *
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 * 
 *
 */

 /**
  * <p>Title: </p>
  * <p>Description: </p>
  * @version 1.0
  */

package com.mutable.osms.server.app.ca;

import java.security.*;
import java.security.cert.Certificate;

public interface CAManagerInterface
{
	public void Initialize() throws Exception;
	public KeyStore buildKeyStore(String p_UserName, PrivateKey p_Key, Certificate p_Cert) throws Exception;
	public Certificate createCertificate(String userName, String password, PublicKey publicKey) throws Exception;
	public void addUser(String userName,String password,String emailAddr)throws Exception;
	public Certificate getCaCertificate()throws Exception;
	public byte[] generateSignedSHA1Digest(byte[] bytesToSign) throws Exception;
	public boolean verifyBytesAndSignedSHA1Digest(byte[] p_OriginalBytes, byte[] p_SignedDigest) throws Exception;
}

