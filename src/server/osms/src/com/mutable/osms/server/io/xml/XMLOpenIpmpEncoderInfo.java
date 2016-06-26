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

import com.mutable.io.OlLogger;
import com.mutable.osms.server.bo.osmsEncoderInfo;
import com.mutable.osms.server.bo.osmsOpenIpmpEncoderInfo;

/**
 * XML document needed by the EncoderManager.
 * 
 */
public class XMLOpenIpmpEncoderInfo extends XMLEncoderInfo {

	/**
	 * Template for constructing XML document.
	 */
	protected static String template = 
		"<EncoderInfo>" + "\n" +
			"<ContentTitle>title</ContentTitle>" + "\n" +
			"<UserInfo>username/password</UserInfo>" + "\n" +
			"<OpenIPMPHostInfo>localhost:8080</OpenIPMPHostInfo>" + "\n" +
			"<RightsHostInfo>localhost:8080</RightsHostInfo>" + "\n" +
			"<LicenseGrant></LicenseGrant>" + "\n" +
			"<doi:KernelMetadata xmlns:doi=\"http://www.doi.org/\">" + "\n" +
				"<DOI>TBD</DOI>" + "\n" +
				"<Identifiers>" + "\n" +
					"<Identifier>" + "\n" +
						"<IdentifierType>ISWC</IdentifierType>" + "\n" +
						"<IdentifierValue>T-034.524.680</IdentifierValue>" + "\n" +
					"</Identifier>" + "\n" +
				"</Identifiers>" + "\n" +
				"<Titles>" + "\n" +
					"<Title>" + "\n" +
						"<TitleValue>title</TitleValue>" + "\n" +
						"<Language>en</Language>" + "\n" +
					"</Title>" + "\n" +
				"</Titles>" + "\n" +
				"<StructuralType>visual</StructuralType>" + "\n" +
				"<Modes>" + "\n" +
					"<Mode>visual</Mode>" + "\n" +
				"</Modes>" + "\n" +
				"<PrimaryAgents>" + "\n" +
					"<Agent sequence=\"1\">" + "\n" +
						"<Name>" + "\n" +
							"<NameType>Person</NameType>" + "\n" +
							"<NameValue>Matt Witte</NameValue>" + "\n" +
						"</Name>" + "\n" +
						"<Roles>" + "\n" +
							"<Role>Artist</Role>" + "\n" +
						"</Roles>" + "\n" +
					"</Agent>" + "\n" +
					"<Agent sequence=\"2\">" + "\n" +
						"<Name>" + "\n" +
							"<NameType>Person</NameType>" + "\n" +
							"<NameValue>Freddy</NameValue>" + "\n" +
						"</Name>" + "\n" +
						"<Roles>" + "\n" +
							"<Role>Directory</Role>" + "\n" +
						"</Roles>" + "\n" +
					"</Agent>" + "\n" +
				"</PrimaryAgents>" + "\n" +
				"<Assertor>" + "\n" +
					"<Registrant>" + "\n" +
						"<Name>" + "\n" +
							"<NameType></NameType>" + "\n" +
							"<NameValue></NameValue>" + "\n" +
						"</Name>" + "\n" +
						"<Identifier>" + "\n" +
							"<IdentifierType>PublisherCode</IdentifierType>" + "\n" +
							"<IdentifierValue>9901</IdentifierValue>" + "\n" +
						"</Identifier>" + "\n" +
					"</Registrant>" + "\n" +
					"<Authority>" + "\n" +
						"<Name>" + "\n" +
							"<NameType>Organization</NameType>" + "\n" +
							"<NameValue>Mutable</NameValue>" + "\n" +
						"</Name>" + "\n" +
					"</Authority>" + "\n" +
				"</Assertor>" + "\n" +
			"</doi:KernelMetadata>" + "\n" +
		"</EncoderInfo>";

	/**
	 * Default constructor is initialized from a template. The XML
	 * document constructed should be initialized by encodeBusinessObject()
	 * method.
	 *
	 */
	public XMLOpenIpmpEncoderInfo(){
		super.decode(template, getRootTag());
	}
	
	/**
	 * Encodes business object into XML document.
	 * 
	 * @param info
	 */
	public void encodeBusinessObject(osmsOpenIpmpEncoderInfo info){
		super.encodeBusinessObject(info);
	}
	
	/**
	 * Converts XML document into business object.
	 * 
	 * @return Business object.
	 */
	public osmsOpenIpmpEncoderInfo convertToBusinessObject(){
		osmsOpenIpmpEncoderInfo info = new osmsOpenIpmpEncoderInfo();
		convertToBusinessObject(info);
		return info;
	}

	public boolean equals(Object arg){
		try{
			osmsOpenIpmpEncoderInfo rhs = (osmsOpenIpmpEncoderInfo)arg;
			return super.equals(rhs);			
		}catch(Exception e){
			return false;
		}
	}	
}
