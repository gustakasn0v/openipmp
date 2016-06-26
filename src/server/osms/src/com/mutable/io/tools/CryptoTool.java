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

package com.mutable.io.tools;

import java.lang.*;
import java.lang.reflect.*;
import java.security.*;
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
import java.security.interfaces.*;

import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;

import javax.crypto.*;
import javax.crypto.spec.DESKeySpec;

import sun.misc.BASE64Encoder;
import sun.misc.BASE64Decoder;

public class CryptoTool
{
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static KeyPair generateKeyPair(int p_KeySize, String p_Alg,String p_secProviderCode)
			throws Exception
	{
		KeyPairGenerator keygen = KeyPairGenerator.getInstance(p_Alg,p_secProviderCode);
		keygen.initialize(p_KeySize,new SecureRandom());
		KeyPair rsaKeys = keygen.generateKeyPair();
		return rsaKeys;
	}
	public static byte[] encrypt(byte[] ba,PublicKey p_publicKey,String p_algorithm,String p_mode,String p_padding) throws Exception
	{
		Cipher cipher = Cipher.getInstance(p_algorithm+"/"+p_mode+"/"+p_padding);
		cipher.init(Cipher.ENCRYPT_MODE, p_publicKey);
		return cipher.doFinal(ba);
	}
	public static byte[] decrypt(byte[] ba,PrivateKey p_privateKey, String p_algorithm,String p_mode,String p_padding)throws Exception
	{
		Cipher cipher = Cipher.getInstance(p_algorithm+"/"+p_mode+"/"+p_padding);
		cipher.init(Cipher.DECRYPT_MODE, p_privateKey);
		return cipher.doFinal(ba);
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static SecretKey generateSecretKey(String cipherAlgorithm)
			throws Exception
	{
		KeyGenerator keyGenerator = KeyGenerator.getInstance(cipherAlgorithm);
		keyGenerator.init(new SecureRandom());
		SecretKey secretKey = keyGenerator.generateKey();
		return secretKey;
	}
	public static byte[] encrypt(byte[] ba,SecretKey p_secretKey,String p_algorithm,String p_mode,String p_padding) throws Exception
	{
		Cipher cipher = Cipher.getInstance(p_algorithm+"/"+p_mode+"/"+p_padding);
		cipher.init(Cipher.ENCRYPT_MODE, p_secretKey);
		return cipher.doFinal(ba);
	}

	public static byte[] decrypt(byte[] ba,SecretKey p_secretKey, String p_algorithm,String p_mode,String p_padding)throws Exception
	{
		Cipher cipher = Cipher.getInstance(p_algorithm+"/"+p_mode+"/"+p_padding);
		cipher.init(Cipher.DECRYPT_MODE, p_secretKey);
		return cipher.doFinal(ba);
	}

	/*-------------------------------------------------------------------
	* public static byte[] generateMD5Hash(String algorithm, String stringToHash)
	*
	* Description: Generates and returns a hash for the supplied String
	*
	* @param String stringToHash
	* @return hash as a byte[]
	**-------------------------------------------------------------------*/
	private static byte[] generateHash(String algorithm, String stringToHash) throws NoSuchAlgorithmException
	{
		MessageDigest md = MessageDigest.getInstance(algorithm);
		md.update(stringToHash.getBytes());
		return md.digest();
	}
	/*-------------------------------------------------------------------
	* public static byte[] generateMD5Hash(String algorithm, byte[] bytesToHash)
	*
	* Description: Generates and returns a hash for the supplied byte[]
	*
	* @param byte[] bytesToHash
	* @return hash as a byte[]
	**-------------------------------------------------------------------*/
	private static byte[] generateHash(String algorithm, byte[] bytesToHash) throws NoSuchAlgorithmException
	{
		MessageDigest md = MessageDigest.getInstance(algorithm);
		md.update(bytesToHash);
		return md.digest();
	}
	public static byte[] generateMD5Hash(String stringToHash) throws NoSuchAlgorithmException
	{
		return generateHash("MD5", stringToHash);
	}
	public static byte[] generateMD5Hash(byte[] bytesToHash) throws NoSuchAlgorithmException
	{
		return generateHash("MD5", bytesToHash);
	}
	public static byte[] generateSHA1Hash(String stringToHash) throws NoSuchAlgorithmException
	{
		return generateHash("SHA", stringToHash);
	}
	public static byte[] generateSHA1Hash(byte[] bytesToHash) throws NoSuchAlgorithmException
	{
		return generateHash("SHA", bytesToHash);
	}
	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static String base64Encode(byte[] ba)
	{
		return (new BASE64Encoder()).encode(ba);
	}
	public static byte[] base64Decode(String str) throws Exception
	{
		return (new BASE64Decoder()).decodeBuffer(str);
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static byte[] encodeKeyStore(KeyStore store,String password)throws Exception
	{
		ByteArrayOutputStream bOut = new ByteArrayOutputStream();
		store.store(bOut, password.toCharArray());
		return bOut.toByteArray();
	}
	public static KeyStore decodeKeyStore(byte[] ba,String type,String password)throws Exception
	{
		KeyStore store = KeyStore.getInstance(type);
		ByteArrayInputStream bis = new ByteArrayInputStream(ba);
		store.load(bis,password.toCharArray());
		return store;
	}














	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	public static void main(String[] args)
	{
		com.mutable.io.OlLogger log = new com.mutable.io.OlLogger();
		try
		{
			if(false)
			{
				log.debug("","generate SecretKey");
				SecretKey  key = CryptoTool.generateSecretKey("DES");
				String msg ="This is a test";

				log.debug("","encrypt");
				byte[] msgEncrypted = CryptoTool.encrypt(msg.getBytes(),key,"DES","ECB","PKCS5Padding");

				log.debug("","decrypt");
				byte[] msgDecrypted = CryptoTool.decrypt(msgEncrypted,key,"DES","ECB","PKCS5Padding");

				log.debug("",""+"key.toString() = "+key.toString());
				log.debug("",""+"msg = "+msg);
				log.debug("",""+"new String(msgEncrypted) = "+new String(msgEncrypted));
				log.debug("",""+"msgEncrypted.length = "+msgEncrypted.length);
				log.debug("",""+"new String(msgDecrypted) = "+new String(msgDecrypted));

			}
			if(true)
			{
				log.debug("","Add Provider");
				Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());
				KeyPairGenerator keygen = KeyPairGenerator.getInstance("RSA","BC");
				keygen.initialize(768,new SecureRandom());
				KeyPair rsaKeys = keygen.generateKeyPair();
				PublicKey pubKey = rsaKeys.getPublic();
				log.debug("",""+"pubKey = "+((RSAPublicKey)pubKey));
				log.debug("",""+"pubKey = "+((RSAPublicKey)pubKey));
				log.debug("",""+"Modulus = "+((RSAPublicKey)pubKey).getModulus() );
				log.debug("",""+"Modulus = "+new String (((RSAPublicKey)pubKey).getModulus().toByteArray()) );
				log.debug("",""+"PublicExponent = "+((RSAPublicKey)pubKey).getPublicExponent());
			}
			if(false)
			{
				log.debug("","Add Provider");
				Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());

				log.debug("","generate KeyPair");
				KeyPair keypair = CryptoTool.generateKeyPair(768,"RSA","BC");
				PublicKey pubKey = keypair.getPublic();

				PrivateKey prvKey = keypair.getPrivate();
				String msg ="This is a test";

				log.debug("","encrypt");
				byte[] msgEncrypted = CryptoTool.encrypt(msg.getBytes(),pubKey,"RSA","ECB","PKCS1Padding");

				log.debug("","decrypt");
				byte[] msgDecrypted = CryptoTool.decrypt(msgEncrypted,prvKey,"RSA","ECB","PKCS1Padding");

				log.debug("",""+"pubKey = "+pubKey);
				log.debug("",""+"Modulus = "+((RSAPublicKey)pubKey).getModulus());
				log.debug("",""+"PublicExponent = "+((RSAPublicKey)pubKey).getPublicExponent());

				log.debug("",""+"pubKey.toString() = "+pubKey.toString());

				log.debug("",""+"pubKey.getEncoded() = "+pubKey.getEncoded());
				log.debug("",""+"prvKey.toString() = "+prvKey.toString());
				log.debug("",""+"msg = "+msg);
				log.debug("",""+"new String(msgEncrypted) = "+new String(msgEncrypted));
				log.debug("",""+"new String(msgDecrypted) = "+new String(msgDecrypted));
				PrintObject.print(pubKey,false);
			}
			if(false)
			{
				log.debug("","Add Provider");
				Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());

				log.debug("","generate KeyPair");
				KeyPair keypair = CryptoTool.generateKeyPair(768,"RSA","BC");
				PublicKey pubKey = keypair.getPublic();
				PrivateKey prvKey = keypair.getPrivate();
				String msg ="This is a test";

				log.debug("","encrypt");
				byte[] msgEncrypted = CryptoTool.encrypt(msg.getBytes(),pubKey,"RSA","ECB","PKCS1Padding");

				log.debug("","decrypt");
				byte[] msgDecrypted = CryptoTool.decrypt(msgEncrypted,prvKey,"RSA","ECB","PKCS1Padding");

				log.debug("",""+"pubKey.toString() = "+pubKey.toString());
				log.debug("",""+"prvKey.toString() = "+prvKey.toString());
				log.debug("",""+"msg = "+msg);
				log.debug("",""+"new String(msgEncrypted) = "+new String(msgEncrypted));
				log.debug("",""+"new String(msgDecrypted) = "+new String(msgDecrypted));

			}
			if(false)
			{
				byte[] p12 = FileTool.readFile("C:\\Documents and Settings\\JOEN\\Desktop\\cmollis4.p12");
				KeyStore keystore = CryptoTool.decodeKeyStore(p12,"PKCS12","swordfish");
				System.out.println("type = "+keystore.getType());
			}
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}

	}
}

/*****
 *
 * PRINT OBJECT
 *
****/
class PrintObject
{
	private static String StripPackage(String className)
	{
		int index = className.lastIndexOf(".");
		if(index==-1)return className;

		return className.substring(index+1);
	}
	private static String space(String[] args,int[] argsLen)
	{
		StringBuffer ret=new StringBuffer();

		for (int i = 0; i < args.length; i++)
		{
			ret.append(args[i]);
			ret.append("  ");
			for (int j = args[i].length(); j < argsLen[i]; j++)
			{
				ret.append(" ");
			}

		}

		return ret.toString();
	}
	public static void print(Object obj,boolean bSubClasses)
	{
		StringBuffer sb=new StringBuffer();
		sb.append("\n\tClass "+StripPackage(obj.getClass().getName())+" extends "+ StripPackage(obj.getClass().getSuperclass().getName()));
		Class[] ds=obj.getClass().getInterfaces();

		for (int d = 0; d < ds.length; d++)
		{
			if(d==0)sb.append(" implements ");
			else sb.append(", ");
			sb.append(StripPackage(ds[d].getName()));
		}
		sb.append("\n\t{");
		Method[] ms=obj.getClass().getMethods();
		for (int m = 0; m < ms.length; m++)
		{
			if(bSubClasses || (obj.getClass().getName().equals(ms[m].getDeclaringClass().getName())))
			{
				String[] frmt=new String[3];
				int[] frmtLen={20,20,20};
				sb.append("\n\t\t");
				frmt[0]=StripPackage(ms[m].getDeclaringClass().getName());
				frmt[1]=StripPackage(ms[m].getReturnType().getName());
				frmt[2]=ms[m].getName();
				Class[] ps =ms[m].getParameterTypes();
				frmt[2]+="(";
				for (int p = 0; p < ps.length; p++)
				{
					if(p!=0)frmt[2]+=",";
					frmt[2]+=StripPackage(ps[p].getName());
				}
				frmt[2]+=")";
				sb.append(space(frmt,frmtLen));
			}
		}
		sb.append("\n\t}\n");
		System.out.println(sb.toString());
	}
}

