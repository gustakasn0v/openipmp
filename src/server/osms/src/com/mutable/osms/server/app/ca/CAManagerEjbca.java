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
import java.security.Key;
import java.security.PrivateKey;
import java.security.PublicKey;
import javax.crypto.SecretKey;
import java.security.KeyPair;
import java.security.SecureRandom;
import java.security.KeyPairGenerator;
import java.security.Security;
import java.security.KeyStore;
import java.security.cert.Certificate;
import java.security.cert.X509Certificate;
import java.rmi.RemoteException;

import javax.naming.Context;

import se.anatom.ejbca.ca.exception.AuthStatusException;
import se.anatom.ejbca.ca.exception.AuthLoginException;
import se.anatom.ejbca.ca.sign.*;
import se.anatom.ejbca.ra.*;
import se.anatom.ejbca.util.*;

import com.mutable.io.OlLogger;
import com.mutable.io.tools.CryptoTool;

public class CAManagerEjbca implements CAManagerInterface
{

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
	private ISignSession m_SignSession;
	private IUserAdminSession m_AdminSession;
	private Certificate[] m_chain;

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
	public CAManagerEjbca(OlLogger log)
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
	public void Initialize() throws Exception
	{

		String methodName="Initialize";
		logDebug(methodName,"get jndi context!");
		Context JNDIContext = new javax.naming.InitialContext();

		logDebug(methodName,"Look up RSASignSession");
		Object obj = JNDIContext.lookup("RSASignSession");
		logDebug(methodName,"create signSessionHome");
		ISignSessionHome signHome = (ISignSessionHome)javax.rmi.PortableRemoteObject.narrow(obj, ISignSessionHome.class);
		m_SignSession = signHome.create();

		logDebug(methodName,"Lookup UserAdminSession");
		obj = JNDIContext.lookup("UserAdminSession");
		logDebug(methodName,"create adminSessionHome");
		IUserAdminSessionHome adminHome = (IUserAdminSessionHome)javax.rmi.PortableRemoteObject.narrow(obj, IUserAdminSessionHome.class);
		m_AdminSession = adminHome.create();

		logDebug(methodName,"get CertChain");
		m_chain = m_SignSession.getCertificateChain();

	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public KeyStore buildKeyStore(String p_UserName, PrivateKey p_Key, Certificate p_Cert) throws Exception
	{
		KeyStore thisKeyStore = KeyTools.createP12(p_UserName, p_Key, (X509Certificate)p_Cert, (X509Certificate)m_chain[0]);
		return thisKeyStore;
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public void addUser(String userName,String password,String emailAddr)throws Exception
	{
		String dn = "C=US, O=Mutable Inc, OU=Software Engineering, CN="+userName;
		int type = 1;
		m_AdminSession.addUser(userName, password, dn, emailAddr, type);
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public Certificate createCertificate(String userName, String password, PublicKey publicKey) throws Exception,AuthLoginException
	{
		return m_SignSession.createCertificate(userName, password, publicKey);
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public byte[] generateSignedSHA1Digest(byte[] bytesToSign) throws Exception
	{
		return m_SignSession.generateSignedSHA1Digest(bytesToSign);
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public boolean verifyBytesAndSignedSHA1Digest(byte[] p_OriginalBytes, byte[] p_SignedBytes) throws Exception
	{
		return m_SignSession.verifyBytesAndSignedSHA1Digest(p_OriginalBytes, p_SignedBytes);
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public Certificate getCaCertificate()
	{
		return (X509Certificate)m_chain[0];
	}
}

