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
* The XMLAuxDataDocument class manages operations related to parsing, converting and
* encoding Auxillary Data XML Documents.
* @version      1.0
* @since      	1.0
*/

public class XMLAuxDataDocument extends XMLDocument
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * Default class constructor which creates a new XMLAuxDataDocument object.
    */
	public XMLAuxDataDocument()
	{
    }
	/**
    * Class constructor which creates a new XMLAuxDataDocument object.  The constructor initializes the object from the xml string parameter.
	*
	* @param xmlString  an xml string used to initialize the object
    */
	public XMLAuxDataDocument(String xmlString)
	{
		isGoodDocument = super.decode(xmlString, "AuxData");
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * osmsAuxData business object.
    */
	private osmsAuxData m_AuxData = null;
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

	private final String m_TagToolId = "ToolId";
	private final String m_TagProtectedFlag = "ProtectedFlag";
	private final String m_TagRightsHostUrl = "RightsHost.URL";
	private final String m_TagRightsHostPort = "RightsHost.Port";

	/**
	* Builds the XMLAuxDataDocument object with the values from an osmsAuxData business object
	*
	* @param    auxData    an osmsAuxData business object
	*/
	private void buildAuxDataXml(osmsAuxData auxData)
	{
		this.setString(m_TagRightsHostUrl,auxData.getRightsHostUrl());
		this.setString(m_TagRightsHostPort,auxData.getRightsHostPort());

		//If document was built from template
		if(isFromTemplate)
		{
		    this.setString(m_TagProtectedFlag,auxData.isProtected()?"True":"False");
		    this.setInteger(m_TagToolId,auxData.getToolIdentifier());
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
	* Converts this xml document to an osmsAuxData business object.
	*
	* @return an osmsAuxData business object (NOTE: Returns null if the document was initialized properly)
	*/
	public osmsAuxData convertAuxDataToBusinessObject()
	{
		if (!isGoodDocument)
		    return null;

		//Create new business object
		m_AuxData = new osmsAuxData();

		//Set Tool Identifier
		m_AuxData.setToolIdentifier(this.getInteger(m_TagToolId));

		//Set Protected Flag - assume protection unless specified to be "false"
		if(this.getString(m_TagProtectedFlag)!=null)
		    m_AuxData.setIsProtected(this.getString(m_TagProtectedFlag).equalsIgnoreCase("FALSE")?false:true);
		else
		    m_AuxData.setIsProtected(true);

		return m_AuxData;
	}
	/**
	* Updates the XMLAuxDataDocument object with the values from an osmsAuxData business object and returns the document as an xml string.
	*
	* @param auxData    an osmsAuxData business object
	* @return the XMLAuxDataDocument object as an xml string (NOTE: Returns null if an error is encountered)
	*/
    public String encodeAuxDataResponse(osmsAuxData auxData)
    {
		if (!isGoodDocument)
		    return null;

		//Update document's values with attribute from Aux Data business object
		if (auxData!=null)
		    this.buildAuxDataXml(auxData);

		return super.encode();
    }
}