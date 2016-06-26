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


package com.mutable.osms.server.bo;

/**
 * <p>Title: osmsEncryptedKey </p>
 * <p>Description: Class houses the attributes and methods required to support key transport</p>
 * @version 1.0
 */

public class osmsEncryptedKey
{

    public osmsEncryptedKey()
    {
		//TODO: Change this from hard coding
		this.setEncryptionMethodAlg("http://www.w3.org/2001/04/xmlenc#rsa-1_5/");
		this.setEncryptedKeyAlg("http://www.w3.org/2001/04/xmlenc#blowfish128/");
    }

	public void print()
	{
		String methodName = "print";
		System.out.println("*************************************************************************************************");
		System.out.println("************************************ ENCRYPTED KEY OBJECT **************************************");
		System.out.println("*************************************************************************************************");
		System.out.println("getEncryptionMethodAlg: " + getEncryptionMethodAlg());
		System.out.println("getEncryptedKeyAlg: "     + getEncryptedKeyAlg());
		System.out.println("*************************************************************************************************");

	}

	//Encryption Method Algorithm
	private String m_EncryptionMethodAlg;
	public String getEncryptionMethodAlg()
	{
		return m_EncryptionMethodAlg;
	}
	public void setEncryptionMethodAlg(String EncryptionMethodAlg)
	{
		m_EncryptionMethodAlg = EncryptionMethodAlg;
	}

	//Base64 Encoded Key
	private String m_EncryptedKey;
	public String getEncryptedKey()
	{
		return m_EncryptedKey;
	}
	public void setEncryptedKey(String EncryptedKey)
	{
		m_EncryptedKey = EncryptedKey;
	}

	//Algorithm of Encrypted Key
	private String m_EncryptedKeyAlg;
	public String getEncryptedKeyAlg()
	{
		return m_EncryptedKeyAlg;
	}
	public void setEncryptedKeyAlg(String EncryptedKeyAlg)
	{
		m_EncryptedKeyAlg = EncryptedKeyAlg;
	}

	//Osms Certificate of Signer
	private osmsCertificate m_SignerOsmsCertificate=null;
	public void setSignerOsmsCertificate(osmsCertificate SignerOsmsCertificate)
	{
		m_SignerOsmsCertificate=SignerOsmsCertificate;
	}
	public osmsCertificate getSignerOsmsCertificate()
	{
		return m_SignerOsmsCertificate;
	}

	//Base64 Certificate of Signer
	private String m_SignerCertificate=null;
	public void setSignerCertificate(String SignerCertificate)
	{
		m_SignerCertificate=SignerCertificate;
	}
	public String getSignerCertificate()
	{
		return m_SignerCertificate;
	}

	//Protected key (protected with server secret key)
	private byte[] m_ProtectedKey;
	public byte[] getProtectedKey()
	{
		return m_ProtectedKey;
	}
	public void setProtectedKey(byte[] ProtectedKey)
	{
		m_ProtectedKey = ProtectedKey;
	}
}
