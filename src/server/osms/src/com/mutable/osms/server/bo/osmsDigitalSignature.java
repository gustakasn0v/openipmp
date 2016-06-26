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
 * <p>Title: osmsDigitalSignature </p>
 * <p>Description: Class house the attributes and methods required for Digital Signatures</p>
 * @version 1.0
 */

public class osmsDigitalSignature
{

    public osmsDigitalSignature()
    {
		//TODO: Change this from hard coding
		this.setCanonicalizationMethod("http://www.w3.org/TR/2001/REC-xml-c14-20010315");
		this.setDigestMethod("http://www.w3.org/2000/09/xmldsig#sha1");
		this.setSignatureMethod("http://www.w3.org/2000/09/xmldsig#rsa-sha1");
		String[] transformMethods = new String[2];
		transformMethods[0] = "http://www.w3.org/2000/09/xmldsig#enveloped-signature";
		transformMethods[1] = "http://www.w3.org/TR/2001/REC-xml-c14n-20010315";
		this.setTransformMethods(transformMethods);
    }

	public void print()
	{
		String methodName = "print";
		System.out.println("*************************************************************************************************");
		System.out.println("********************************** DIGITAL SIGNATURE OBJECT *************************************");
		System.out.println("*************************************************************************************************");
		System.out.println("getCanonicalizationMethod: " + getCanonicalizationMethod());
		System.out.println("getDigestMethod: " + getDigestMethod());
		System.out.println("getSignatureMethod: " + getSignatureMethod());
		System.out.println("getTransformMethods[0]: " + getTransformMethods()[0]);
		System.out.println("getTransformMethods[1]: " + getTransformMethods()[1]);
		System.out.println("*************************************************************************************************");

	}

	//Bytes To Sign
	private byte[] m_BytesToSign=null;
	public void setBytesToSign(byte[] BytesToSign)
	{
		m_BytesToSign=BytesToSign;
	}
	public byte[] getBytesToSign()
	{
		return m_BytesToSign;
	}

	//Canonicalization Method
	private String m_CanonicalizationMethod;
	public String getCanonicalizationMethod()
	{
		return m_CanonicalizationMethod;
	}
	public void setCanonicalizationMethod(String CanonicalizationMethod)
	{
		m_CanonicalizationMethod = CanonicalizationMethod;
	}

	//Signature Method
	private String m_SignatureMethod;
	public String getSignatureMethod()
	{
		return m_SignatureMethod;
	}
	public void setSignatureMethod(String SignatureMethod)
	{
		m_SignatureMethod = SignatureMethod;
	}

	//Signature Algorithm
	private osmsAlgorithm m_SignatureAlgorithm;
	public osmsAlgorithm getSignatureAlgorithm()
	{
		return m_SignatureAlgorithm;
	}
	public void setSignatureAlgorithm(osmsAlgorithm SignatureAlgorithm)
	{
		m_SignatureAlgorithm = SignatureAlgorithm;
	}

	//Transform Methods
	private String[] m_TransformMethods;
	public String[] getTransformMethods()
	{
		return m_TransformMethods;
	}
	public void setTransformMethods(String[] TransformMethods)
	{
		m_TransformMethods = TransformMethods;
	}
	public void addTransformMethod(String TranformMethod) throws Exception
	{
		if (TranformMethod!=null)
		{
			String[] newTranformMethods;
			if(getTransformMethods()!=null)
			{
				newTranformMethods = new String[getTransformMethods().length+1];
				String[] oldTranformMethods = getTransformMethods();
				for(int i=0;i<oldTranformMethods.length;i++)
				{
				    newTranformMethods[i] = oldTranformMethods[i];
				}
				newTranformMethods[newTranformMethods.length-1] = TranformMethod;
			}
			else
			{
				newTranformMethods = new String[1];
				newTranformMethods[0] = TranformMethod;
			}
			this.setTransformMethods(newTranformMethods);
		}
    }

	//Digest Method
	private String m_DigestMethod;
	public String getDigestMethod()
	{
		return m_DigestMethod;
	}
	public void setDigestMethod(String DigestMethod)
	{
		m_DigestMethod = DigestMethod;
	}

	//Digest Algorithm
	private osmsAlgorithm m_DigestAlgorithm;
	public osmsAlgorithm getDigestAlgorithm()
	{
		return m_DigestAlgorithm;
	}
	public void setDigestAlgorithm(osmsAlgorithm DigestAlgorithm)
	{
		m_DigestAlgorithm = DigestAlgorithm;
	}

	//Digest Value
	private String m_DigestValue;
	public String getDigestValue()
	{
		return m_DigestValue;
	}
	public void setDigestValue(String DigestValue)
	{
		m_DigestValue = DigestValue;
	}

	//Signature Value
	private String m_SignatureValue;
	public String getSignatureValue()
	{
		return m_SignatureValue;
	}
	public void setSignatureValue(String SignatureValue)
	{
		m_SignatureValue = SignatureValue;
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
}