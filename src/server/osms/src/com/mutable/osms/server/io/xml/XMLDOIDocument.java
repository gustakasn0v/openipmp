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
import com.mutable.osms.server.app.osmsServerConfiguration;
import com.mutable.osms.server.bo.*;

/**
* The XMLDOIDocument class manages operations related to parsing, converting and
* encoding DOI Kernel Metadata XML Documents.
* <p>
* @version      1.0
* @since      	1.0
*/

public class XMLDOIDocument extends XMLDocument
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * Default class constructor which creates a new XMLDOIDocument object.
    */
	public XMLDOIDocument()
	{
    }
	/**
    * Class constructor which creates a new XMLDOIDocument object.  The constructor initializes the object from the xml string parameter.
	*
	* @param xmlString  an xml string used to initialize the object
    */
	public XMLDOIDocument(String xmlString)
	{
		isGoodDocument = super.decode(xmlString, "doi:KernelMetadata");
	}
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * An osmsDoi business object.
    */
	private osmsDoi m_Doi = null;
	/**
    * An osmsContent business object.
    */
	private osmsContent m_Content = null;
	/**
    * An osmsDigitalItem business object.
    */
	private osmsDigitalItem m_DigitalItem = null;
	/**
    * Indicates whether the xml document is well formed and parsed correctly.
    */
	private boolean isGoodDocument = false;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
	* Parses Alternate Identifier Section of a DOI doc and creates and returns an array of osmsAltIdentifier with the values from the xml.
	*
	* @param xmlAltIdRoot   The root Alt Identifier node of the XMLDOIDocument as an XMLDocument.
	* @return an array of osmsAltIdentifier business objects, one for each alt identifier in the document
	* (NOTE: returns null if no alt identifiers exist in the document)
	*/
	private osmsAltIdentifier[] processAltIdentifiers(XMLDocument xmlAltIdRoot)
	{
		Vector vAltIds = xmlAltIdRoot.getDocList("Identifier");
		if (vAltIds == null || vAltIds.isEmpty())
			return null;

		int vAltIdsLen = vAltIds.size();
		osmsAltIdentifier[] altIds = new osmsAltIdentifier[vAltIdsLen];
		for (int i = 0; i < vAltIdsLen; i++)
		{
			XMLDocument xmlAltId = (XMLDocument)vAltIds.get(i);
			altIds[i] = new osmsAltIdentifier();
			altIds[i].setAltIdOrder(new Integer(i+1));
			altIds[i].setIdentifier(xmlAltId.getString("IdentifierValue"));
			altIds[i].setIdentifierTypeCode(xmlAltId.getString("IdentifierType"));
		}
		return altIds;
	}
	/**
	* Creates a new alternate identifier section of an XMLDOIDocument with the alternate identifiers from the original document and
	* the Master Doi Identifier from the Instance DOI (used in Register Digital Item use cases).
	*
	* @param xmlAltIdRoot   The root Alt Identifier node of the XMLDOIDocument as an XMLDocument.
	* @return   true (if document node was rebuilt successfullyaltIdSectionReconstructedSuccessfully) or false (if document node was not rebuilt successfully)
	*/
	private boolean rebuildAltIdentifierWithMasterDoi(XMLDocument xmlAltIdRoot)
	{
      // Original Alt Identifiers in Document
      Vector vAltIds = this.getDocList("Identifier");
      if (vAltIds == null || vAltIds.isEmpty())
          return false;

	  int newSize = vAltIds.size() + 1;

      XMLDocument newAltId = ((XMLDocument)vAltIds.get(0)).Clone();  // Added to the Document and "handle" returned.
      newAltId.setString("IdentifierValue", m_Doi.getMasterDoi().getDoiIdentifier());
      newAltId.setString("IdentifierType", "DOI");

      // Get updated list of Alt Identifiers after "cloning"
      vAltIds.clear();
      vAltIds = this.getDocList("Identifier");

      if (vAltIds == null || vAltIds.isEmpty())
          return false;

      // Further insanity/consistancy check
      if (vAltIds.size() != newSize)
          return false;

	  return true;
	}
	/**
	* Parses Titles Section of a DOI doc and creates and returns an array of osmsTitles with the values from the document.  Also,
	* sets the title related attributes on the object's doi and content business objects when they are not null.
	*
	* @param xmlTitleRoot   The root Title node of the XMLDOIDocument as an XMLDocument.
	* @return an array of osmsDoiTitle business objects, one for each title in the document
	*/
	private osmsDoiTitle[] processTitles(XMLDocument xmlTitleRoot)
	{
		Vector vTitles = xmlTitleRoot.getDocList("Title");
		if (vTitles == null || vTitles.isEmpty())
			return null;

		int vTitlesLen = vTitles.size();
		osmsDoiTitle[] titles = new osmsDoiTitle[vTitlesLen];
		for (int i = 0; i < vTitlesLen; i++)
		{
			XMLDocument xmlTitle = (XMLDocument)vTitles.get(i);
			titles[i] = new osmsDoiTitle();
			titles[i].setSequence(new Integer(i+1));
			if (i==0 && m_Doi!=null)
			{
				if (m_Doi!=null)
				{
				    m_Doi.setPrimaryTitleText(xmlTitle.getString("TitleValue"));
				    m_Doi.setPrimaryTitleLanguage(xmlTitle.getString("Language"));
				}

				//If Content object exists (Register Content requests, set Primary Title)
				if (m_Content!=null)
					m_Content.setPrimaryTitle(xmlTitle.getString("TitleValue"));
			}
			titles[i].setTitleText(xmlTitle.getString("TitleValue"));
			titles[i].setLanguage(xmlTitle.getString("Language"));
		}
		return titles;
	}
	/**
	* Parses Assertor Section of a DOI doc and sets the values on the doi object passed into the method.
	*
	* @param xmlAssertorRoot   The root Assertor node of the XMLDOIDocument as an XMLDocument.
	* @param doi    An osmsDoi business object that the method will set the assertor attributes on.
	*/
	private void processAssertor(XMLDocument xmlAssertorRoot, osmsDoi doi)
	{
		doi.setAssertRegName(xmlAssertorRoot.getString("Registrant.Name.NameValue"));
		doi.setAssertRegType(xmlAssertorRoot.getString("Registrant.Name.NameType"));
		return;
	}
	/**
	* Parses Modes Section of a DOI doc and updates the mode related attributes on the object's doi business object.
	*
	* @param xmlModeRoot   The root Mode node of the XMLDOIDocument as an XMLDocument.
	* @return   true (if doi business object exists and modes were found in document) or false (if doi business object is null or modes were not found in document)
	*/
	private boolean processModes(XMLDocument xmlModeRoot)
	{
		Vector vModes = xmlModeRoot.getDocList("Mode");
		if (vModes == null || vModes.isEmpty())
			return false;

		if (m_Doi==null)
		{
			System.out.println("Could not set modes on Doi because doi was null") ;
			return false;
		}

		int vModesLen = vModes.size();
		for (int i = 0; i < vModesLen; i++)
		{
			XMLDocument xmlMode = (XMLDocument)vModes.get(i);

			if(xmlMode.getString("Mode").equalsIgnoreCase("ABSTRACT"))
				m_Doi.setIsAbstractFlag("Y");
			else if(xmlMode.getString("Mode").equalsIgnoreCase("AUDIO"))
				m_Doi.setIsAudioFlag("Y");
			else if(xmlMode.getString("Mode").equalsIgnoreCase("AUDIOVISUAL"))
				m_Doi.setIsAudiovisualFlag("Y");
			else if(xmlMode.getString("Mode").equalsIgnoreCase("VISUAL"))
				m_Doi.setIsVisualFlag("Y");
		}
		return true;
	}
	/**
	* Parses Agent Section of a DOI doc and creates and returns an array of osmsDoiAgents with the values from the document.  Also,
	* sets the agent related attributes on the object's doi and content business objects when they are not null.
	*
	* @param xmlPrimaryAgentRoot   The root Agent node of the XMLDOIDocument as an XMLDocument.
	* @return an array of osmsDoiAgent business objects, one for each agent in the document
	*/
	private osmsDoiAgent[] processPrimaryAgents(XMLDocument xmlPrimaryAgentRoot)
	{
		Vector vAgents = xmlPrimaryAgentRoot.getDocList("Agent");
		if (vAgents == null || vAgents.isEmpty())
			return null;

		int vAgentsLen = vAgents.size();
		osmsDoiAgent[] agents = new osmsDoiAgent[vAgentsLen];
		for (int i = 0; i < vAgentsLen; i++)
		{
			boolean isPrimaryAgent = false;
			XMLDocument xmlAgent = (XMLDocument)vAgents.get(i);
			agents[i] = new osmsDoiAgent();
			agents[i].setSequence(new Integer(i+1));
			agents[i].setAgentName(xmlAgent.getString("Name.NameValue"));
			agents[i].setAgentType(xmlAgent.getString("Name.NameType"));

			//If Content object exists (Register Content requests, set Primary Title);
			if(m_Content!=null)
			{
				if(xmlAgent.getAttributeValue("Agent","sequence")!=null && xmlAgent.getAttributeValue("Agent","sequence").compareTo("1")==0)
				{
					isPrimaryAgent=true;
					m_Content.getDoi().setPrimaryAgentName(xmlAgent.getString("Name.NameValue"));
					m_Content.getDoi().setPrimaryAgentType(xmlAgent.getString("Name.NameType"));
				}
 				//TODO: Have to come to agreement on what agent.roles will be considered 'artist'
				if((!StringTool.isStringValid(m_Content.getPrimaryArtist())))
					m_Content.setPrimaryArtist(xmlAgent.getString("Name.NameValue"));
			}

			//Process Roles
			XMLDocument xmlRoleRoot = xmlAgent.getSubDoc("Roles");
			if (xmlRoleRoot == null)
				return null;

			Vector vRoles = xmlRoleRoot.getDocList("Role");
			if (vRoles == null || vRoles.isEmpty())
				return null;

			int vRolesLen = vRoles.size();
			for (int j = 0; j < vRolesLen && j < 4; j++) //Max of 4 roles per Agent supported
			{
				XMLDocument xmlRole = (XMLDocument)vRoles.get(j);
				switch (j)
				{
					case 0:
					{
						agents[i].setRole1(xmlRole.getString("Role"));
						if(isPrimaryAgent)
						{
						    m_Doi.setPrimaryAgentRole(xmlRole.getString("Role"));
						}
						break;
					}
					case 1:
					{
						agents[i].setRole2(xmlRole.getString("Role"));
						break;
					}
					case 2:
					{
						agents[i].setRole3(xmlRole.getString("Role"));
						break;
					}
					case 3:
					{
						agents[i].setRole4(xmlRole.getString("Role"));
						break;
					}
				}
			}
		}
		return agents;
	}
	/**
	* Sets Assertor related document values from atrributes on osmsDoi business objects.
	* @param doi   An osmsDoi business object that contains the Assertor values the document will be updated with.
	*/
	private void buildAssertorXml(osmsDoi doi)
	{
		this.setString("Assertor.Registrant.Name.NameType",doi.getAssertRegType());
		this.setString("Assertor.Registrant.Name.NameValue",doi.getAssertRegName());
		this.setString("Assertor.Registrant.Identifier.IdentifierType",doi.getAssertIdentifierType());
		this.setString("Assertor.Registrant.Identifier.IdentifierValue",doi.getAssertIdentifier());
		this.setString("Assertor.Authority.Name.NameType",doi.getAssertAuthType());
		this.setString("Assertor.Authority.Name.NameValue",doi.getAssertAuthName());
	}
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

		//Setup Content and DOI
		m_Content = new osmsContent();
		m_Content.setIdentifierTypeCode("DOI");
		m_Content.setPrimaryIdentifier(StringTool.isStringValid(this.getString("DOI"))?this.getString("DOI"):null);

		m_Doi = new osmsDoi();
		m_Content.setDoi(m_Doi);
		m_Doi.setDoiProfileCode(m_Doi.DOI_APP_PROFILE_KERNEL);
		m_Doi.setDoiIdentifier(StringTool.isStringValid(this.getString("DOI"))?this.getString("DOI"):null);

		//Process Alt Identifiers
		XMLDocument xmlAltIdRoot = this.getSubDoc("Identifiers");
		if (xmlAltIdRoot!=null)
		    m_Doi.setAltIdentifiers(this.processAltIdentifiers(xmlAltIdRoot));

		//Process Titles
		XMLDocument xmlTitleRoot = this.getSubDoc("Titles");
		if (xmlTitleRoot!=null)
			m_Doi.setDoiTitles(this.processTitles(xmlTitleRoot));

		//Process Structural Type
		m_Doi.setStructuralType(this.getString("StructuralType"));

		//Process Modes
		XMLDocument xmlModeRoot = this.getSubDoc("Modes");
		if (xmlModeRoot!=null)
			if (!this.processModes(xmlModeRoot))
				System.out.println("Modes could not be set!") ;

		//Process Agents
		XMLDocument xmlPrimaryAgentRoot = this.getSubDoc("PrimaryAgents");
		if (xmlPrimaryAgentRoot!=null)
			m_Doi.setDoiAgents(this.processPrimaryAgents(xmlPrimaryAgentRoot));

		//Process Assertor
		XMLDocument xmlAssertorRoot = this.getSubDoc("Assertor");
		if (xmlAssertorRoot==null)
		{
			System.out.println("Assertor is missing!") ;
			return null;
		}
		this.processAssertor(xmlAssertorRoot,m_Doi);

		return m_Content;
	}
	/**
	* Updates the XMLDOIDocument object with the values from an osmsContent business object and returns the document as an xml string.
	*
	* @param content   an osmsContent business object
	* @return the XMLDOIDocument object as an xml string (NOTE: Returns null if an error is encountered)
	*/
    public String encodeRegisterContentResponse(osmsContent content)
    {
		if (!isGoodDocument)
		    return null;

		//Set Primary Identifier and Assertor
		if (content.getDoi()!=null)
		{
		    this.setString("DOI",content.getPrimaryIdentifier());
		    this.buildAssertorXml(content.getDoi());
		}

		return super.encode(false);
    }
	/**
	* Converts this xml document to an osmsDigitalItem business object.
	*
	* @return an osmsDigitalItem business object (NOTE: Returns null if the document was initialized properly or if required nodes are missing from the xml document)
	*/
	public osmsDigitalItem convertRegisterDigitalItemRequestToBusinessObject()
	{
		if (!isGoodDocument)
		    return null;

		if(!StringTool.isStringValid(this.getString("DOI")))
		{
			System.out.println("DOI is missing!") ;
			return null;
		}

		//Setup Master DOI
		osmsDoi masterDoi = new osmsDoi();
		masterDoi.setDoiIdentifier(this.getString("DOI"));

		//Setup new Instance DOI (m_Doi)
		m_Doi = new osmsDoi();
		m_Doi.setDoiProfileCode(m_Doi.DOI_APP_PROFILE_KERNEL);
		m_Doi.setMasterDoi(masterDoi);

		//Process Alt Identifiers and add Master DOI to list of Alt Identifiers
		XMLDocument xmlAltIdRoot = this.getSubDoc("Identifiers");
		if (xmlAltIdRoot!=null)
		{
		    boolean rebuildSuccess = false;
			rebuildSuccess = rebuildAltIdentifierWithMasterDoi(xmlAltIdRoot);
		    if(rebuildSuccess)
			    m_Doi.setAltIdentifiers(this.processAltIdentifiers(xmlAltIdRoot));
			else
			{
				System.out.println("Unable to add Master DOI to list of Alt Identifiers") ;
				return null;
			}
		}

		//Process Titles
		XMLDocument xmlTitleRoot = this.getSubDoc("Titles");
		if (xmlTitleRoot!=null)
			m_Doi.setDoiTitles(this.processTitles(xmlTitleRoot));

		//Process Structural Type
		m_Doi.setStructuralType(this.getString("StructuralType"));

		//Process Modes
		XMLDocument xmlModeRoot = this.getSubDoc("Modes");
		if (xmlModeRoot!=null)
			if (!this.processModes(xmlModeRoot))
				System.out.println("Modes could not be set!") ;

		//Process Agents
		XMLDocument xmlPrimaryAgentRoot = this.getSubDoc("PrimaryAgents");
		if (xmlPrimaryAgentRoot!=null)
			m_Doi.setDoiAgents(this.processPrimaryAgents(xmlPrimaryAgentRoot));

		//Process Assertor
		XMLDocument xmlAssertorRoot = this.getSubDoc("Assertor");
		if (xmlAssertorRoot==null)
		{
			System.out.println("Assertor is missing!") ;
			return null;
		}
		this.processAssertor(xmlAssertorRoot,m_Doi);

		//Setup Digital Item and set Instance DOI
		m_DigitalItem = new osmsDigitalItem();
		m_DigitalItem.setDoi(m_Doi);

		return m_DigitalItem;
	}
	/**
	* Updates the XMLDOIDocument object with the values from an osmsDigitalItem business object and returns the document as an xml string.
	*
	* @param dItem   an osmsDigitalItem business object
	* @return the XMLDOIDocument object as an xml string (NOTE: Returns null if an error is encountered)
	*/
	public String encodeRegisterDigitalItemResponse(osmsDigitalItem dItem)
    {
		if (!isGoodDocument)
			return null;

		if (dItem==null || dItem.getDoi()==null || dItem.getDoi().getDoiIdentifier()==null)
			return null;

		//Set Primary Identifier
		this.setString("DOI",dItem.getDoi().getDoiIdentifier());

		//Set Assertor
		this.buildAssertorXml(dItem.getDoi());

		return super.encode(false);
	}
}

