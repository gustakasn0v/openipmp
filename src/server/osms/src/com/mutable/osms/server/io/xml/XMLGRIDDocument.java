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
 * Copyright (C) Mutable, Inc. 2002-2003.  All Rights Reserved.
 * 
 *
 */


package com.mutable.osms.server.io.xml;

import java.util.*;
import java.io.*;

import squashxml.xml.*;

import com.mutable.io.tools.FileTool;
import com.mutable.io.tools.StringTool;
import com.mutable.osms.server.app.osmsServerConfiguration;
import com.mutable.osms.server.bo.*;

/**
* The XMLGRIDDocument class manages operations related to parsing, converting and
* encoding GRID XML Documents.
* <p>
* @version      1.1
* @since      	1.1
*/

public class XMLGRIDDocument extends XMLDocument
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * Default class constructor which creates a new XMLGRIDDocument object.
    */
	public XMLGRIDDocument()
	{
    }
	/**
    * Class constructor which creates a new XMLGRIDDocument object.  The constructor initializes the object from the xml string parameter.
	*
	* @param xmlString  an xml string used to initialize the object
    */
	public XMLGRIDDocument(String xmlString)
	{
		isGoodDocument = super.decode(xmlString, "grid:Metadata");
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * An osmsGrid business object.
    */
	private osmsGrid m_Grid = null;
	/**
    * An osmsContent business object.
    */
	private osmsContent m_Content = null;
	/**
    * Indicates whether the xml document is well formed and parsed correctly.
    */
	private boolean isGoodDocument = false;
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
	* Converts this xml document to an osmsContent business object.
	*
	* @return an osmsContent business object (NOTE: Returns null if the document was initialized properly or if required nodes are missing from the xml document)
	*/
	public osmsContent convertRegisterContentRequestToBusinessObject()
	{
		if (!isGoodDocument)
		    return null;

		//Setup Content and GRID
		m_Content = new osmsContent();
		m_Content.setIdentifierTypeCode("GRID");
		m_Content.setPrimaryIdentifier(StringTool.isStringValid(this.getString("GRID"))?this.getString("GRID"):null);
		m_Content.setPrimaryArtist("Artist");
		m_Content.setPrimaryTitle("Title");

		m_Grid = new osmsGrid();
		m_Grid.setGrid(StringTool.isStringValid(this.getString("GRID"))?this.getString("GRID"):null);
		m_Grid.setPrimaryArtist("Artist");
		m_Grid.setPrimaryTitle("Title");
		m_Content.setGrid(m_Grid);

		return m_Content;
	}
	/**
	* Updates the XMLGRIDDocument object with the values from an osmsContent business object and returns the document as an xml string.
	*
	* @param content   an osmsContent business object
	* @return the XMLGRIDDocument object as an xml string (NOTE: Returns null if an error is encountered)
	*/
    public String encodeRegisterContentResponse(osmsContent content)
    {
		if (!isGoodDocument)
		    return null;

		//Set Primary Identifier
		if (content.getGrid()!=null)
		{
		    this.setString("GRID",content.getPrimaryIdentifier());
		}

		return super.encode(false);
    }
}

