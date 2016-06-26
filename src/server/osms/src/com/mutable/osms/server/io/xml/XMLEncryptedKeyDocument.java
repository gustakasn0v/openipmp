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


package com.mutable.osms.server.io.xml;

import java.util.*;
import java.io.*;

import squashxml.xml.*;

import com.mutable.io.tools.FileTool;
import com.mutable.io.tools.StringTool;
import com.mutable.osms.server.bo.osmsEncryptedKey;

/**
* The XMLEncryptedKeyDocument class manages operations related to parsing, converting and
* encoding Encrypted Key Documents.
* <p>
* @version      1.0
* @since      	1.0
*/

public class XMLEncryptedKeyDocument extends XMLDocument
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * Default class constructor which creates a new XMLEncryptedKeyDocument object.
    */
	public XMLEncryptedKeyDocument()
	{
    }
	/**
    * Class constructor which creates a new XMLEncryptedKeyDocument object.  The constructor initializes the object from the xml string parameter.
	*
	* @param xmlString  an xml string used to initialize the object
    */
	public XMLEncryptedKeyDocument(String xmlString)
	{
		isGoodDocument = super.decode(xmlString, "KeyXml");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * An Encrypted Key business object.
	 */
	private osmsEncryptedKey m_Key = null;
	/**
    * Indicates whether the xml document is well formed and parsed correctly.
    */
	private boolean isGoodDocument = false;
	/**
    * Indicates whether the xml document was initialized from a template file.
    */
	private boolean isFromTemplate = false;
	/**
    * Returns a boolean indicating whether the xml document was initialized from a template file.
	*
	* @return a boolean indicating if the document initialized from a template file
    */
	public boolean isFromTemplate()
	{
		return isFromTemplate;
	}
	/**
    * Sets boolean indicating whether the xml document was initialized from a template file.
	*
	* @param bool   boolean indicating whether the document was initialized from a template file
    */
	public void isFromTemplate(boolean bool)
	{
		isFromTemplate = bool;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Tag Names Attributes
	private static final String m_TagEncryptedKey = "ds:KeyInfo.enc:EncryptedKey";
	private static final String m_TagEncryptionMethod = "ds:KeyInfo.enc:EncryptedKey.enc:EncryptionMethod";
	private static final String m_TagKeyInfo = "ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo";
	private static final String m_TagX509Data = "ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.ds:X509Data";
	private static final String m_TagX509Certificate = "ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.ds:X509Data.ds:X509Certificate";
	private static final String m_TagCipherData = "ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.enc:CipherData";
	private static final String m_TagCipherValue = "ds:KeyInfo.enc:EncryptedKey.ds:KeyInfo.enc:CipherData.enc:CipherValue";
	private static final String m_TagKeyAuxData = "KeyAuxData";
	private static final String m_TagKeyAuxDataEncryptionMethod = "KeyAuxData.enc:EncryptionMethod";

	/**
	* Builds the XMLEncryptedKeyDocument  object with the values from an osmsEncryptedKey business object
	*
	* @param key    an osmsEncryptedKey business object
	* @throws Exception if an error is encountered retrieving the attributes from the business object
	*/
	private void buildEncryptedKeyXml(osmsEncryptedKey key) throws Exception
	{
		String methodName = "buildEncryptedKeyXml";

		//Validate business object
		if(key==null)
			throw new Exception(methodName+": Encrypted Key object was null");
		if(key.getEncryptedKey()==null)
			throw new Exception(methodName+": Encrypted Key was null");
		if(key.getSignerCertificate()==null)
			throw new Exception(methodName+": Certificate of signer was null");

		this.setString(this.m_TagCipherValue, key.getEncryptedKey());
		this.setString(this.m_TagX509Certificate,key.getSignerCertificate());
		//TODO: Set Encryption Method Algorithm and Key Type when XML Document support is added
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	public osmsEncryptedKey convertEncryptedKeyXmlToBusinessObject()
	{
		if (!isGoodDocument)
		    return null;

		//Create new key business object
		m_Key = new osmsEncryptedKey();

		//Set attributes on business objects
		m_Key.setEncryptedKey(this.getString(this.m_TagCipherValue));
		m_Key.setEncryptedKeyAlg(this.getAttributeValue(m_TagKeyAuxDataEncryptionMethod,"Algorithm"));
		m_Key.setEncryptionMethodAlg(this.getAttributeValue(m_TagEncryptionMethod,"Algorithm"));
		m_Key.setSignerCertificate(this.getString(m_TagX509Certificate));

		System.out.println("m_TagEncryptedKey is " + this.getString(this.m_TagCipherValue));
		System.out.println("m_TagKeyAuxDataEncryptionMethod is " + this.getAttributeValue(m_TagKeyAuxDataEncryptionMethod,"Algorithm"));
		System.out.println("m_TagEncryptionMethod is " + this.getAttributeValue(m_TagEncryptionMethod,"Algorithm"));
		System.out.println("m_TagX509Certificate is " + this.getString(m_TagX509Certificate));
		return m_Key;
	}
	/**
	* Updates the XMLEncryptedKeyDocument object with the values from an osmsEncryptedKey business object and returns the document as an xml string.
	*
	* @param key   an osmsEncryptedKey business object
	* @return the XMLEncryptedKeyDocument object as an xml string (NOTE: Returns null if an error is encountered)
	*/
    public String encodeEncryptedKeyResponse(osmsEncryptedKey key)
    {
		if (!isGoodDocument)
		    return null;

		//Validation
		if (key==null)
			return null;

		if(!StringTool.isStringValid(key.getEncryptedKey()))
			return null;

		if(!StringTool.isStringValid(key.getEncryptedKeyAlg()))
			return null;

		if(!StringTool.isStringValid(key.getEncryptionMethodAlg()))
			return null;

		if(!StringTool.isStringValid(key.getSignerCertificate()))
			return null;

		//Update document's values with attribute from Encrypted Key business object
		try
		{
			this.buildEncryptedKeyXml(key);
		}
		catch(Exception e)
		{
			System.out.println("Exception encountered trying to buildEncryptedKey: "+e.toString());
			return null;
		}
		return super.encode();
    }

	public static void main(String[] args)
	{
		try
		{

			XMLEncryptedKeyDocument doc = new XMLEncryptedKeyDocument();
			doc.decode(FileTool.sreadFile("C:\\KeyTransport_Sample.xml"),"KeyXml");

			System.out.println("***********ORIG*****************");
			System.out.println(doc.encode());
			System.out.println("***********ALGORITHM************************");
			System.out.println(doc.getAttributeValue(m_TagEncryptionMethod,"Algorithm"));
			System.out.println("***********CERTIFICATE************************");
			System.out.println(doc.getString(m_TagX509Certificate));
			System.out.println("***********CIPHER************************");
			System.out.println(doc.getString(m_TagCipherValue));
			System.out.println("***********KEY_AUX************************");
			System.out.println(doc.getAttributeValue(m_TagKeyAuxDataEncryptionMethod,"Algorithm"));
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}
}