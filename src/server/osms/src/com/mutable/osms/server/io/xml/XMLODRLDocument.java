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

package com.mutable.osms.server.io.xml;

import java.util.*;
import java.io.*;

import squashxml.xml.*;

import com.mutable.io.tools.*;
import com.mutable.io.OlLogger;

import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.app.ca.CertificateAuthority;

public class XMLODRLDocument extends XMLDocument
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
	private String template =
			"<o-ex:rights o-ex:id=\"MyRightsData\" xmlns:ds=\"http://www.w3.org/2000/09/xmldsig#\" xmlns:enc=\"http://www.w3.org/2001/04/xmlenc#\" xmlns:o-dd=\"http://odrl.net/1.1/ODRL-DD\" xmlns:o-ex=\"http://odrl.net/1.1/ODRL-EX\" xmlns:o-doi=\"http://www.doi.org/\">"+
			"<o-ex:agreement>"+
			"	<o-ex:context>"+
			"		<o-dd:uid>XXXI SEE YOU XXXXXXXXXXXXX</o-dd:uid>"+
			"		<o-dd:remark>OpenIPMP License Identifier</o-dd:remark>"+
			"	</o-ex:context>"+
			"	<o-ex:asset>"+
			"		<o-ex:context>"+
			"			<o-dd:uid>"+
			"				<o-doi:DOI>XXXXXXXXXXXXXXXXXXXXX</o-doi:DOI>"+
			"			</o-dd:uid>"+
			"		</o-ex:context>"+
			""+
			"		<ds:KeyInfo>"+
			"			<enc:EncryptedKey>"+
			"				<enc:EncryptionMethod Algorithm=\"http://www.w3.org/2001/04/xmlenc#rsa-1_5/\"></enc:EncryptionMethod>"+
			"				<ds:KeyInfo>"+
			"					<ds:X509Data>"+
			"						<ds:X509Certificate>XXXXXXXXXXXXX Users Cert XXXXXXXXXXXXXXXXXXXX</ds:X509Certificate>"+
			"					</ds:X509Data>"+
			"					<enc:CipherData>"+
			"						<enc:CipherValue>XXXXXXXXXXXXXXXXXXXX content-key encrypted with the users-publickey and then base-encoded XXXXXXXXXXXXXXXXXXXXXXx</enc:CipherValue>"+
			"					</enc:CipherData>"+
			"				</ds:KeyInfo>"+
			"			</enc:EncryptedKey>"+
			"		</ds:KeyInfo>"+
			"	</o-ex:asset>"+
			"	<o-ex:permission>"+
			"		<o-dd:play>"+
			"			<o-ex:constraint>"+
			"				<o-dd:datetime>"+
			"					<o-dd:start>XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1999-11-24T18:20:00XXXXXXXXXXXXXXXXXXXXXXXXXXX</o-dd:start>"+
			"					<o-dd:end>XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX2003-11-25T18:20:00XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx</o-dd:end>"+
			"				</o-dd:datetime>"+
			"			</o-ex:constraint>"+
			"		</o-dd:play>"+
			"	</o-ex:permission>"+
			"	<o-ex:party>"+
			"		<o-ex:context>"+
			"			<o-dd:uid>Unique ID of the user?  Should be the users public key here?</o-dd:uid>"+
			"		</o-ex:context>"+
			"	</o-ex:party>"+
			"</o-ex:agreement>"+
			""+
			"<ds:Signature>"+
			"	<ds:SignedInfo>"+
			"		<ds:CanonicalizationMethod ds:Algorithm=\"http://www.w3.org/TR/2001/REC-xml-c14-20010315\"></ds:CanonicalizationMethod>"+
			"		<ds:SignatureMethod ds:Algorithm=\"http://www.w3.org/2000/09/xmldsig#rsa-sha1\"></ds:SignatureMethod>"+
			"		<ds:Reference ds:URI=\"#MyRightsData\">"+
			"			<ds:Transforms>"+
			"				<ds:Transform ds:Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\"></ds:Transform>"+
			"				<ds:Transform ds:Algortithm=\"http://www.w3.org/TR/2001/REC-xml-c14n-20010315\"></ds:Transform>"+
			"			</ds:Transforms>"+
			"			<ds:DigestMethod ds:Algorithm=\"http://www.w3.org/2000/09/xmldsig#sha1\"></ds:DigestMethod>"+
			"			<ds:DigestValue>XXXXXXXXXXXXXXXXXXXX Hashed agrreement XXXXXXXXXXXXXXXXXXXXXXXXXXX</ds:DigestValue>"+
			"		</ds:Reference>"+
			"	</ds:SignedInfo>"+
			"	<ds:KeyInfo>"+
			"		<ds:X509Data>"+
			"			<ds:X509Certificate>XXXXXXXXXXXXXXXX CA Cert XXXXXXXXXXXXXXXXXXXXXXXXXXX</ds:X509Certificate>"+
			"		</ds:X509Data>"+
			"	</ds:KeyInfo>"+
			"	<ds:SignatureValue>XXXXXXXXXXXXXXXXXXXXXXX CA signed rights-minus-signature XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX</ds:SignatureValue>"+
			"</ds:Signature>"+
			""+
			"</o-ex:rights>";

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	private String convertDate(Date d,boolean zeroPadding)
	{
		Calendar cal = Calendar.getInstance();
		cal.setTime(d);
		String str;
		int year   = cal.get(Calendar.YEAR);
		int month  = cal.get(Calendar.MONTH)+1;
		int day    = cal.get(Calendar.DAY_OF_MONTH);
		int hour   = cal.get(Calendar.HOUR_OF_DAY);
		int minute = cal.get(Calendar.MINUTE);
		int sec    = cal.get(Calendar.SECOND);

		if(zeroPadding)
		{
			StringBuffer sb = new StringBuffer();
			sb.append(year).append("-");

			int i;
			String seperator;

			i=month;seperator="-";
			if(i>=10)sb.append(i).append(seperator);else sb.append("0").append(i).append(seperator);

			i=day;seperator="T";
			if(i>=10)sb.append(i).append(seperator);else sb.append("0").append(i).append(seperator);

			i=hour;seperator=":";
			if(i>=10)sb.append(i).append(seperator);else sb.append("0").append(i).append(seperator);

			i=minute;seperator=":";
			if(i>=10)sb.append(i).append(seperator);else sb.append("0").append(i).append(seperator);

			i=sec;seperator="";
			if(i>=10)sb.append(i).append(seperator);else sb.append("0").append(i).append(seperator);

			return sb.toString();
		}
		else
		{
			StringBuffer sb = new StringBuffer();
			return sb.append(year).append("-").append(month).append("-").append(day).append("T").append(hour).append(":").append(minute).append(":").append(sec).toString();
		}

		//TODO - 	1999-11-24T18:20:00
	}

	/*-------------------------------------------------------------------
	* Description:
	* XXXXX
	*
	* @param XXX   - xxxxxx
	* @return XXXX - xxxxxx
	**-------------------------------------------------------------------*/
	private XMLODRLDocument CloneODRL()throws Exception
	{
//		System.out.println("--------------------------");
//		System.out.println(this.encode(false));
//		System.out.println("--------------------------");
		return new XMLODRLDocument(this.encode(false));
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
	public XMLODRLDocument()
	{
		String xmlString=null;
		try
		{
//			xmlString =readFile("templates\\licenseODRL2.xml");
			xmlString = template;
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
			return;
		}
		super.decode(xmlString,"o-ex:rights");
	}
	private boolean isGoodDocument = false;

	public XMLODRLDocument(String xmlString)
	{
		isGoodDocument = super.decode(xmlString, "o-ex:rights");
	}
/*
	private void buildSignature(String DigestValue,String X509Certificate, String SignatureValue)
	{
//		System.out.println("DigestValue="+DigestValue);
		setString("ds:Signature.ds:SignedInfo.ds:Reference.ds:DigestValue",DigestValue);
		setString("ds:Signature.ds:KeyInfo.ds:X509Data.ds:X509Certificate",X509Certificate);
		setString("ds:Signature.ds:SignatureValue",SignatureValue);
	}
*/
	public void build(String uid,String DOI,String X509Certificate,String CipherValue,Date startDate,Date endDate) throws Exception
	{
		setString("o-ex:agreement.o-ex:context.o-dd:uid",uid);
		setString("o-ex:agreement.o-ex:asset.o-ex:context.o-dd:uid.o-doi:DOI",DOI);
		setString("o-ex:agreement.o-ex:asset.ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.ds:X509Data.ds:X509Certificate",X509Certificate);
		setString("o-ex:agreement.o-ex:asset.ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.enc:CipherData.enc:CipherValue",CipherValue);

		setString("o-ex:agreement.o-ex:permission.o-dd:play.o-ex:constraint.o-dd:datetime.o-dd:start",convertDate(startDate,true));
		setString("o-ex:agreement.o-ex:permission.o-dd:play.o-ex:constraint.o-dd:datetime.o-dd:end",convertDate(endDate,true));
		signDocument();
	}
	public void signDocument()throws Exception
	{
		CertificateAuthority ca = osmsGlobalObjectManager.getInstance().getCerfiticateAuthority();
		//-------------------
		//build agreement xml
		//-------------------
		XMLDocument doc = this.CloneODRL();
		doc.remove("ds:Signature");
		String agreement = doc.encode(false);

		//----------
		//set values
		//----------
		setString("ds:Signature.ds:SignedInfo.ds:Reference.ds:DigestValue", CryptoTool.base64Encode(CryptoTool.generateSHA1Hash(agreement)));
		setString("ds:Signature.ds:KeyInfo.ds:X509Data.ds:X509Certificate", CryptoTool.base64Encode(ca.getCaCertificate().getEncoded()));
		setString("ds:Signature.ds:SignatureValue",                         CryptoTool.base64Encode(ca.generateSignedSHA1Digest(agreement.getBytes())));

		//TESTING
//		FileTool.writeFile("c:\\_users\\joe\\agreement.xml",agreement);
//		FileTool.writeFile("c:\\_users\\joe\\agreement.sha1",CryptoTool.generateSHA1Hash( agreement));
//		FileTool.writeFile("c:\\_users\\joe\\agreement.sha1.base64",CryptoTool.base64Encode(CryptoTool.generateSHA1Hash( agreement)));
//		FileTool.writeFile("c:\\_users\\joe\\ca.cer",ca.getCaCertificate().getEncoded());
//		FileTool.writeFile("c:\\_users\\joe\\license.xml",this.encode(false));
	}

	public static void main(String[] args)
	{
		try
		{

			XMLODRLDocument doc1 = new XMLODRLDocument();
//			doc1.decode(FileTool.readFile("templates\\licenseODRL2.xml"),"o-ex:rights");

			System.out.println("---orginal----------------------------------");
			System.out.println( doc1.template);

			System.out.println("---orginal----------------------------------");
			System.out.println( doc1.encode(false));

			System.out.println( "---agreement----------------------------------");
			doc1.build("uid","DOI","X509Certificate","CipherValue",new Date(),new Date());
			System.out.println(doc1.encode(false));

			System.out.println("----signature---------------------------------");
//			doc1.signDocument("X509Certificate");
			System.out.println( doc1.encode(false));

		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}
}





/*
  try
  {
   XMLODRLDocument doc1 = new XMLODRLDocument(readFile("C:\\localsecurity\\licenseODRL.xml"));
   System.out.println("isGoodDocument="+doc1.isGoodDocument);

   DataTypeAttribute[] dtAtts=doc1.getAttributeList("o-ex:rights");
   System.out.println("dtAtts size = "+(dtAtts==null?"null":new Integer(dtAtts.length).toString()));

   System.out.println( doc1.getString("o-ex:agreement.o-ex:context.o-dd:uid"));
   System.out.println( doc1.getAttributeValue("o-ex:rights","o-ex:id"));

   System.out.println("============================");
   System.out.println(doc1.encode(false));

   XMLDocument context = doc1.remove("o-ex:agreement.o-ex:context");
   System.out.println("============================");
   System.out.println(doc1.encode(false));

   doc1.add("o-ex:agreement",context);
   System.out.println("============================");
   System.out.println(doc1.encode(false));
  }
  catch (Exception ex)
  {
   ex.printStackTrace();
  }
*/