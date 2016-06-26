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

import java.io.*;
import java.util.*;

//import java.security.*;  NOTE- dont uses this because import java.security.Certificate confilicts with java.security.cert.Certificate
import java.security.Key;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.KeyPair;
import java.security.SecureRandom;
import java.security.KeyPairGenerator;
import java.security.KeyStore;
import java.security.Security;
import java.security.KeyFactory;
import java.security.cert.Certificate;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;

import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;


import javax.crypto.*;
import javax.crypto.spec.DESKeySpec;

import com.mutable.io.OlLogger;
import com.mutable.io.tools.*;

import com.mutable.osms.server.app.osmsGlobalObjectManager;

public class CertificateAuthority
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC STATIC METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger m_logger = null;
	private SecretKey m_MasterSecretKey;
	private CAManagerInterface m_caManager;



	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// STATIC METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	private static KeyPair generateKeyPair() throws Exception
	{
		return CryptoTool.generateKeyPair(768,"RSA","BC");
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static byte[] encodePublicKey(PublicKey key) //throws Exception
	{
		return key.getEncoded();
	}
	public static PublicKey decodePublicKey(byte[] ba) throws Exception
	{
		KeyFactory keyfact = KeyFactory.getInstance("RSA","BC");
		PublicKey pk = keyfact.generatePublic(new X509EncodedKeySpec(ba));
		return pk;
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static byte[] encodePrivateKey(PrivateKey key) //throws Exception
	{
		return key.getEncoded();
	}
	public static PrivateKey decodePrivateKey(byte[] ba) throws Exception
	{
		KeyFactory keyfact = KeyFactory.getInstance("RSA","BC");
		PrivateKey pk = keyfact.generatePrivate(new PKCS8EncodedKeySpec(ba));
		return pk;
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static byte[] encrypt(byte[] ba,PublicKey key) throws Exception
	{
		return CryptoTool.encrypt(ba,key,"RSA","ECB","PKCS1Padding");

	}
	public static byte[] decrypt(byte[] ba,PrivateKey key) throws Exception
	{
		return CryptoTool.decrypt(ba,key,"RSA","ECB","PKCS1Padding");
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static Certificate decodeCertificate(byte[] baCert) throws Exception
	{
		CertificateFactory cf = CertificateFactory.getInstance("X.509");
		return cf.generateCertificate(new ByteArrayInputStream(baCert));
	}
	public static byte[] encodeCertificate(Certificate cert) throws Exception
	{
		return cert.getEncoded();
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public CertificateAuthority(OlLogger log)
	{
		m_logger=log;
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public void Initialize(String EncryptMasterSecretKeyFileName,CAManagerInterface caManager) throws Exception
	{
		String methodName="Initialize";

		logDebug(methodName,"get Master Secret Key");
		ObjectInputStream in = new ObjectInputStream(new FileInputStream(EncryptMasterSecretKeyFileName));
		m_MasterSecretKey = (SecretKey)in.readObject();
		in.close();

		m_caManager=caManager;
		if(m_caManager==null) throw new Exception("CertificateAuthority was not initialized properly!");

	}



	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param IdentityCertIssuanceRequest
	* @returns IdentityCertIssuanceResponse
	* @throws CertificateManagementException
	**-------------------------------------------------------------------*/
	public IdentityCertIssuanceResponse issueIdentityCertificate(IdentityCertIssuanceRequest p_Req) throws Exception
	{
		String methodName="issueIdentityCertificate";
		//-------------------------------------------
		// Validate Input
		//-------------------------------------------
		if (p_Req == null) throw new Exception("Cert Request cannot be null");
		if ((p_Req.getUserName() == null) || (p_Req.getUserName().length() == 0) ) throw new Exception("Username cannot be null.");
		if ((p_Req.getPassword() == null) || (p_Req.getPassword().length() == 0) ) throw new Exception("Password cannot be null.");
//		if ((p_Req.getNotBefore() == null) ) throw new Exception("NotBefore Date cannot be null");
//		if ((p_Req.getNotAfter() == null) ) throw new Exception("NotAfter Date cannot be null");
		if ((p_Req.getEmailAddr() == null) ) throw new Exception("Email Addr cannot be null");

		//-------------------------------------------
		//Create user in CA management db
		//-------------------------------------------
		logDebug(methodName,"Create user in CA management db");
		if(m_caManager==null) throw new Exception("CertificateAuthority was not initialized properly!");
		m_caManager.addUser(p_Req.getUserName(), p_Req.getPassword(),  p_Req.getEmailAddr());

		//-------------------------------------------
		//Generate KeyPair for this user
		//-------------------------------------------
		logDebug(methodName,"Generate KeyPair");
		KeyPair keypair = generateKeyPair();
		if(keypair==null)throw new Exception("Failed To Generate Key Pair");

		//------------------------------------------------------
		//Create Signed Certificate that matches the private key
		//------------------------------------------------------
		logDebug(methodName,"Create Signed Certificate");
		Certificate signedCert = m_caManager.createCertificate(p_Req.getUserName(), p_Req.getPassword(), keypair.getPublic());
		if (signedCert == null)throw new Exception("Failed To Sign Certificate");

		//-------------------------------------------
		//Build User Key Store
		//-------------------------------------------
		logDebug(methodName,"Build User Key Store");
		KeyStore keystore = buildKeyStore(p_Req.getUserName(),  keypair.getPrivate(), signedCert);
		if(keystore==null)throw new Exception("Failed To Build Security Store");

		//-------------------------------------------
		//Create and return response
		//-------------------------------------------
		logDebug(methodName,"Create and return response");
		IdentityCertIssuanceResponse resp = new IdentityCertIssuanceResponse();
		resp.setCertificate(signedCert);
		resp.setKeyPair(keypair);
		resp.setUserSecurityStore(keystore);
		return resp;
	}


	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* encryptPrivateKey() - Encrypts the DER-encoded PrivateKey octetstring with supplied key.
	* @param PrivateKey spec to encrypt
	* @returns byte[] Encrypted ASN.1 encoded encrypted octetstring
	**-------------------------------------------------------------------*/
	public Certificate getCaCertificate() throws Exception
	{
		return m_caManager.getCaCertificate();
	}
	public byte[] generateSignedSHA1Digest(byte[] ba) throws Exception
	{
		return m_caManager.generateSignedSHA1Digest(ba);
	}
	/** verifySignature() - Verify the authenticity and integrity of a series of bytes signed with the CA public key.
	*
	*  @param byte[] p_Bytes, byte[] p_Signature
	*  @return boolean - isAuthentic
	*/
	public boolean verifyBytesAndSignedSHA1Digest(byte[] p_OriginalBytes, byte[] p_SignedDigest) throws Exception
	{
		return m_caManager.verifyBytesAndSignedSHA1Digest(p_OriginalBytes, p_SignedDigest);
	}

	public KeyStore buildKeyStore(String p_UserName, PrivateKey p_Key, Certificate p_Cert) throws Exception
	{
		return m_caManager.buildKeyStore(p_UserName, p_Key, p_Cert);
	}

	 /*-------------------------------------------------------------------
	 * Description:
	 * XXXXX
	 *
	 * encryptPrivateKey() - Encrypts the DER-encoded PrivateKey octetstring with supplied key.
	 * @param PrivateKey spec to encrypt
	 * @returns byte[] Encrypted ASN.1 encoded encrypted octetstring
	 **-------------------------------------------------------------------*/
	 public byte[] encryptWithSecretKey(byte[] ba) throws Exception
	 {
		 return CryptoTool.encrypt(ba,this.m_MasterSecretKey,"DES","ECB","PKCS5Padding");
	 }
	 public byte[] decryptWithSecretKey(byte[] ba) throws Exception
	 {
		 return CryptoTool.decrypt(ba,this.m_MasterSecretKey,"DES","ECB","PKCS5Padding");
	 }




	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// DEBUG
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	public static void main(String[] args)
	{

		OlLogger log = new OlLogger();
		try
		{

			log.debug("","START");

			CertificateAuthority ca;
			if(false)
			{
				CAManagerEjbca caManager= new CAManagerEjbca(log);
				caManager.Initialize();

				Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());
				ca = new CertificateAuthority(log);
				ca.Initialize("lib"+File.separator+"mastersecret.ser",caManager);
			}
			else
			{
				ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
			}

			if(true)
			{
				KeyPair keypair = generateKeyPair();
				System.out.println("format = "+ keypair.getPrivate().getFormat());
				System.out.println("format = "+ keypair.getPublic().getFormat());
				byte[] epk = encodePrivateKey(keypair.getPrivate());
				PrivateKey prvkey = decodePrivateKey(epk);
				epk = encodePublicKey(keypair.getPublic());
				PublicKey  pubkey = decodePublicKey(epk);
				System.out.println("format = "+ prvkey.getFormat());
				System.out.println("format = "+ pubkey.getFormat());

				return;
			}
			if(false)
			{
				IdentityCertIssuanceRequest req = new IdentityCertIssuanceRequest();
				req.setEmailAddr("xx@yahoo.com");
				req.setPassword("xx");
				req.setUserName("xx"+new Date().getTime());

				IdentityCertIssuanceResponse resp= ca.issueIdentityCertificate(req);

				//byte[] ba = resp.getCertificate().getEncoded();
				//Certificate cert = ca.getCertfromByteArray(ba);
				//
				//ca.writeFile(req.getUserName()+".p12",resp.getUserSecurityStore());
				//log.debug("","END");
			}

		}
		catch (Exception ex)
		{
			log.error("","",ex);
		}
		System.exit(0);

	}

}
