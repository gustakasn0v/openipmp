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

import com.mutable.io.tools.StringTool;
import squashxml.xml.*;

import com.mutable.osms.server.bo.*;

/**
* The XMLDigitalSignatureDocument class manages operations related to parsing, converting and
* encoding Digital Signature XML Documents.
* <p>
* @version      1.0
* @since      	1.0
*/

public class XMLDigitalSignatureDocument extends XMLDocument
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * Default class constructor which creates a new XMLDigitalSignatureDocument object.
    */
	public XMLDigitalSignatureDocument()
	{
    }

	/**
    * Class constructor which creates a new XMLDigitalSignatureDocument object.  The constructor initializes the object from the xml string parameter.
	*
	* @param xmlString  an xml string used to initialize the object
    */
	public XMLDigitalSignatureDocument(String xmlString)
	{
		isGoodDocument = super.decode(xmlString, "Signature");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
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
	/**
	* Builds the XMLDigitalSignatureDocument object with the values from an osmsDigitalSignature business object
	*
	* @param sig    an osmsDigitalSignature business object
	* @throws Exception if an error is encountered retrieving the attributes from the business object
	*/
	private void buildSignatureXml(osmsDigitalSignature sig) throws Exception
	{
		String methodName = "buildSignatureXml";

		//Validate business object
		if(sig==null)
			throw new Exception(methodName+": Signature object was null");
		if(sig.getDigestValue()==null)
			throw new Exception(methodName+": Digest was null");
		if(sig.getSignatureValue()==null)
			throw new Exception(methodName+": Signature was null");
		if(sig.getSignerCertificate()==null)
			throw new Exception(methodName+": Certificate of signer was null");

		//KeyInfo Section
		this.setString("KeyInfo.X509Data.X509Certificate",sig.getSignerCertificate());

		//Signed Info Section
		this.setString("SignedInfo.Reference.DigestValue",sig.getDigestValue());
		this.setString("SignatureValue",sig.getSignatureValue());

	/* Need a way to set attribute values
		this.setString("SignedInfo.CanonicalizationMethod",new DataTypeAttribute("Algorithm",sig.getCanonicalizationMethod()),sig.getCanonicalizationMethod());
		this.setString("SignedInfo.SignatureMethod",new DataTypeAttribute("Algorithm",sig.getSignatureMethod()),sig.getSignatureMethod());
		this.setString("SignedInfo.Reference.DigestMethod",new DataTypeAttribute("Algorithm",sig.getDigestMethod()),sig.getDigestMethod());
	*/

	/* Need a way to set attribute values
		//Transforms
		Vector vTransforms = this.getDocList("SignedInfo.Reference.Transforms");
		if (vTransforms == null || vTransforms.isEmpty())
			throw new Exception("Couldn't get Transforms section");

		int vTransformsLen = vTransforms.size();
		if(sig.getTransformMethods().length!=vTransformsLen)
			System.out.println("XMLDigitalSignatureDocument: transform lengths don't match...sigLength: "+" vs docLength "+vTransformsLen);
		for (int i = 0; i < vTransformsLen; i++)
		{
			XMLDocument xmlTransform = (XMLDocument)vTransforms.get(i);
			xmlTransform.setString("Transform",new DataTypeAttribute("Algorithm",sig.getTransformMethods()[i].toString()),null);
		}
	*/
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
	* Updates the XMLDigitalSignatureDocument object with the values from an osmsDigitalSignature business object and returns the document as an xml string.
	*
	* @param dSig   an osmsDigitalSignature business object
	* @return the XMLDigitalSignatureDocument object as an xml string (NOTE: Returns null if an error is encountered)
	*/
    public String encodeDigitalSignatureResponse(osmsDigitalSignature dSig)
    {
		if (!isGoodDocument)
		    return null;

		if (dSig==null)
			return null;

		if(!StringTool.isStringValid(dSig.getCanonicalizationMethod()))
			return null;

		if(!StringTool.isStringValid(dSig.getDigestMethod()))
			return null;

		if(!StringTool.isStringValid(dSig.getSignatureMethod()))
			return null;

		if(dSig.getTransformMethods()==null || dSig.getTransformMethods().length==0)
			return null;

		if(!StringTool.isStringValid(dSig.getSignerCertificate()))
			return null;

		//Update document's values with attribute from Digital Signature business object
		try
		{
			buildSignatureXml(dSig);
		}
		catch(Exception e)
		{
			System.out.println("Exception encountered trying to buildSignature: "+e.toString());
			return null;
		}
		return super.encode(false);
    }
}