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

import com.mutable.io.tools.StringTool;
import com.mutable.osms.server.app.*;

/**
* The XMLServerConfigurationDocument class manages operations related to parsing, converting and
* encoding the server configuration document.
* <p>
* @version      1.0
* @since      	1.0
*/

public class XMLServerConfigurationDocument extends XMLDocument
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * Default class constructor which creates a new XMLServerConfigurationDocument object.
    */
	public XMLServerConfigurationDocument()
	{
    }
	/**
    * Class constructor which creates a new XMLServerConfigurationDocument object.  The constructor initializes the object from the xml string parameter.
	*
	* @param xmlString  an xml string used to initialize the object
    */
	public XMLServerConfigurationDocument(String xmlString)
	{
		isGoodDocument = super.decode(xmlString, "osms:ServerConfigurationData");
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * Server Configuration business object that manages the server's settings.
    */
	private osmsServerConfiguration m_ServerConfig = null;
	/**
    * Indicates whether the xml document is well formed and parsed correctly.
    */
	private boolean isGoodDocument = false;

	//Tag Names Attributes
	private final String m_TagServerConstants = "ServerConstants";
	private final String m_TagServerPort = "ServerConstants.Server.Port";
	private final String m_TagDbProvider = "ServerConstants.Database.Provider";
	private final String m_TagDbDriver = "ServerConstants.Database.Driver";
	private final String m_TagDbConnectUrl = "ServerConstants.Database.ConnectURL";
	private final String m_TagDbUserName = "ServerConstants.Database.UserName";
	private final String m_TagDbPassword = "ServerConstants.Database.Password";
	private final String m_TagLogDebugFileName = "ServerConstants.Logs.Debug.FileName";
	private final String m_TagLogDebugFilePath = "ServerConstants.Logs.Debug.Path";
	private final String m_TagLogErrorFileName = "ServerConstants.Logs.Error.FileName";
	private final String m_TagLogErrorFilePath = "ServerConstants.Logs.Error.Path";
	private final String m_TagLogInfoFileName = "ServerConstants.Logs.Info.FileName";
	private final String m_TagLogInfoFilePath = "ServerConstants.Logs.Info.Path";
	private final String m_TagLogAllFileName = "ServerConstants.Logs.All.FileName";
	private final String m_TagLogAllFilePath = "ServerConstants.Logs.All.Path";
	private final String m_TagSymmetricAlgorithmId = "ServerConstants.Security.SymmetricEncryption.Algorithm";
	private final String m_TagSymmetricProviderId = "ServerConstants.Security.SymmetricEncryption.Provider";
	private final String m_TagSymmetricPadding = "ServerConstants.Security.SymmetricEncryption.Padding";
	private final String m_TagSymmetricKeySize = "ServerConstants.Security.SymmetricEncryption.KeySize";
	private final String m_TagAsymmetricAlgorithmId = "ServerConstants.Security.AsymmetricEncryption.Algorithm";
	private final String m_TagAsymmetricProviderId = "ServerConstants.Security.AsymmetricEncryption.Provider";
	private final String m_TagAsymmetricKeySize = "ServerConstants.Security.AsymmetricEncryption.KeySize";
	private final String m_TagMasterKeys = "ServerConstants.Security.MasterKeys";
	private final String m_TagMasterKey = "MasterKey"; //Can occur multiple times so we get this off of subdoc MasterKeys
	private final String m_TagMasterKeyId = "MasterKey.KeyId"; //Occurs multiple times so we get this off of MasterKey
	private final String m_TagMasterKeyFileName = "MasterKey.FileName"; //Occurs multiple times so we get this off of MasterKey
	private final String m_TagMasterKeyPath = "MasterKey.Path"; //Occurs multiple times so we get this off of MasterKey
	private final String m_TagApplicationConstants = "ApplicationConstants";
	private final String m_TagDoiCode = "ApplicationConstants.DOI.Code";
	private final String m_TagDoiAppProfile = "ApplicationConstants.DOI.ApplicationProfile";
	private final String m_TagDoiMasterPrefix = "ApplicationConstants.DOI.Master.Prefix";
	private final String m_TagDoiMasterSuffixTable = "ApplicationConstants.DOI.Master.SuffixTable";
	private final String m_TagDoiInstancePrefix = "ApplicationConstants.DOI.Instance.Prefix";
	private final String m_TagDoiInstanceSuffixTable = "ApplicationConstants.DOI.Instance.SuffixTable";
	private final String m_TagDoiAssertorAuthName = "ApplicationConstants.DOI.Assertor.Authority.Name";
	private final String m_TagDoiAssertorAuthType = "ApplicationConstants.DOI.Assertor.Authority.Type";
	private final String m_TagDoiAssertorAuthIdentifier = "ApplicationConstants.DOI.Assertor.Authority.Identifier";
	private final String m_TagDoiAssertorAuthUrl = "ApplicationConstants.DOI.Assertor.Authority.URL";
	private final String m_TagDoiRegOrganizationType = "ApplicationConstants.DOI.Assertor.Registrant.OrganizationType";
	private final String m_TagDoiRegPersonType = "ApplicationConstants.DOI.Assertor.Registrant.PersonType";
	private final String m_TagGridCode = "ApplicationConstants.GRID.Code";
	private final String m_TagTemplateDoiFileName = "ApplicationConstants.Templates.DOI.FileName";
	private final String m_TagTemplateDoiFilePath = "ApplicationConstants.Templates.DOI.Path";
	private final String m_TagTemplateAuxDataFileName = "ApplicationConstants.Templates.AuxData.FileName";
	private final String m_TagTemplateAuxDataFilePath = "ApplicationConstants.Templates.AuxData.Path";
	private final String m_TagTemplateSignatureFileName = "ApplicationConstants.Templates.Signature.FileName";
	private final String m_TagTemplateSignatureFilePath = "ApplicationConstants.Templates.Signature.Path";
	private final String m_TagTemplateLicenseOdrlFileName = "ApplicationConstants.Templates.LicenseODRL.FileName";
	private final String m_TagTemplateLicenseOdrlFilePath = "ApplicationConstants.Templates.LicenseODRL.Path";
	private final String m_TagTemplateEncryptedKeyFileName = "ApplicationConstants.Templates.EncryptedKey.FileName";
	private final String m_TagTemplateEncryptedKeyFilePath = "ApplicationConstants.Templates.EncryptedKey.Path";
	private final String m_TagRightsHostUrl = "ApplicationConstants.RightsHost.URL";
	private final String m_TagRightsHostPort = "ApplicationConstants.RightsHost.Port";
	private final String m_TagIntentPlay = "ApplicationConstants.Intent.Play";
	private final String m_TagAuditUpdateUser = "ApplicationConstants.Audit.UpdateUser";
	private final String m_TagAuditCreateUser = "ApplicationConstants.Audit.CreateUser";
	private final String m_TagEncoderPath = "ApplicationConstants.Encoder.Path";
	/** C. Mollis 10/3/05 SPE-Specific authorization during license acquisition */
	private final String m_TagSPEAuthUser = "ApplicationConstants.ExternalAuth.SPEAuthUser";

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//Get Methods for Tag Strings
	public String getTagServerConstants() {return m_TagServerConstants;}
	public String getTagServerPort() {return m_TagServerPort;}
	public String getTagDbProvider() {return m_TagDbProvider;}
	public String getTagDbDriver() {return m_TagDbDriver;}
	public String getTagDbConnectUrl() {return m_TagDbConnectUrl;}
	public String getTagDbUserName() {return m_TagDbUserName;}
	public String getTagDbPassword() {return m_TagDbPassword;}
	public String getTagLogAllFileName() {return m_TagLogAllFileName;}
	public String getTagLogAllFilePath() {return m_TagLogAllFilePath;}
	public String getTagLogDebugFileName() {return m_TagLogDebugFileName;}
	public String getTagLogDebugFilePath() {return m_TagLogDebugFilePath;}
	public String getTagLogErrorFileName() {return m_TagLogErrorFileName;}
	public String getTagLogErrorFilePath() {return m_TagLogErrorFilePath;}
	public String getTagLogInfoFileName() {return m_TagLogInfoFileName;}
	public String getTagLogInfoFilePath() {return m_TagLogInfoFilePath;}
	public String getTagSymmetricAlgorithmId() {return m_TagSymmetricAlgorithmId;}
	public String getTagSymmetricProviderId() {return m_TagSymmetricProviderId;}
	public String getTagSymmetricPadding() {return m_TagSymmetricPadding;}
	public String getTagSymmetricKeySize() {return m_TagSymmetricKeySize;}
	public String getTagAsymmetricAlgorithmId() {return m_TagAsymmetricAlgorithmId;}
	public String getTagAsymmetricProviderId() {return m_TagAsymmetricProviderId;}
	public String getTagAsymmetricKeySize() {return m_TagAsymmetricKeySize;}
	public String getTagMasterKeys() {return m_TagMasterKeys;}
	public String getTagMasterKey() {return m_TagMasterKey;}
	public String getTagMasterKeyId() {return m_TagMasterKeyId;}
	public String getTagMasterKeyFileName() {return m_TagMasterKeyFileName;}
	public String getTagMasterKeyPath() {return m_TagMasterKeyPath;}
	public String getTagApplicationConstants() {return m_TagApplicationConstants;}
	public String getTagDoiCode() {return m_TagDoiCode;}
	public String getTagDoiAppProfile() {return m_TagDoiAppProfile;}
	public String getTagDoiMasterPrefix() {return m_TagDoiMasterPrefix;}
	public String getTagDoiMasterSuffixTable() {return m_TagDoiMasterSuffixTable;}
	public String getTagDoiInstancePrefix() {return m_TagDoiInstancePrefix;}
	public String getTagDoiInstanceSuffixTable() {return m_TagDoiInstanceSuffixTable;}
	public String getTagDoiAssertorAuthName() {return m_TagDoiAssertorAuthName;}
	public String getTagDoiAssertorAuthType() {return m_TagDoiAssertorAuthType;}
	public String getTagDoiAssertorAuthIdentifier() {return m_TagDoiAssertorAuthIdentifier;}
	public String getTagDoiAssertorAuthUrl() {return m_TagDoiAssertorAuthUrl;}
	public String getTagDoiRegOrganizationType() {return m_TagDoiRegOrganizationType;}
	public String getTagDoiRegPersonType() {return m_TagDoiRegPersonType;}
	public String getTagGridCode() {return m_TagGridCode;}
	public String getTagTemplateDoiFileName() {return m_TagTemplateDoiFileName;}
	public String getTagTemplateDoiFilePath() {return m_TagTemplateDoiFilePath;}
	public String getTagTemplateAuxDataFileName() {return m_TagTemplateAuxDataFileName;}
	public String getTagTemplateAuxDataFilePath() {return m_TagTemplateAuxDataFilePath;}
	public String getTagTemplateSignatureFileName() {return m_TagTemplateSignatureFileName;}
	public String getTagTemplateSignatureFilePath() {return m_TagTemplateSignatureFilePath;}
	public String getTagTemplateLicenseOdrlFileName() {return m_TagTemplateLicenseOdrlFileName;}
	public String getTagTemplateLicenseOdrlFilePath() {return m_TagTemplateLicenseOdrlFilePath;}
	public String getTagTemplateEncryptedKeyFileName() {return m_TagTemplateEncryptedKeyFileName;}
	public String getTagTemplateEncryptedKeyFilePath() {return m_TagTemplateEncryptedKeyFilePath;}
	public String getTagRightsHostUrl() {return m_TagRightsHostUrl;}
	public String getTagRightsHostPort() {return m_TagRightsHostPort;}
	public String getTagIntentPlay() {return m_TagIntentPlay;}
	public String getTagAuditUpdateUser() {return m_TagAuditUpdateUser;}
	public String getTagAuditCreateUser() {return m_TagAuditCreateUser;}
	public String getTagEncoderPath() {return m_TagEncoderPath;}
	/** C. Mollis 10/3/05 */
	public String getTagSPEAuthUser() {return m_TagSPEAuthUser; }

	/**
    * Validates the required server configuration parameters were supplied.
	*
	* @throws osmsServerConfigurationException if a required value is missing
    */
    public void validate() throws osmsServerConfigurationException
    {

		int errCode = 999;
		String errMissingValue = "Missing Configuration Value: ";

		//  NOTES:
		// (1) Required elements that are not provided should result in an osmsServerConfigurationException
		//     (throw exception as soon as a problem is encountered
		// (2) Non-required elements that are not provided should result in a warning message to the log file

		// ****************************************************************************
		//                  REQUIRED ELEMENT SECTION
		// ****************************************************************************
		if(!isGoodDocument)
		    throw new osmsServerConfigurationException(errCode, "Configuration xml failed to parse");

		if(!StringTool.isStringValid(this.getString(this.getTagAsymmetricAlgorithmId())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagAsymmetricAlgorithmId());

		if(!StringTool.isStringValid(this.getString(this.getTagAsymmetricKeySize())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagAsymmetricKeySize());

		if(!StringTool.isStringValid(this.getString(this.getTagAsymmetricProviderId())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagAsymmetricProviderId());

		if(!StringTool.isStringValid(this.getString(this.getTagAuditCreateUser())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagAuditCreateUser());

		if(!StringTool.isStringValid(this.getString(this.getTagAuditUpdateUser())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagAuditUpdateUser());

		if(!StringTool.isStringValid(this.getString(this.getTagDbConnectUrl())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDbConnectUrl());

		if(!StringTool.isStringValid(this.getString(this.getTagDbDriver())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDbDriver());

		if(!StringTool.isStringValid(this.getString(this.getTagDbProvider())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDbProvider());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiAppProfile())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiAppProfile());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiAssertorAuthIdentifier())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiAssertorAuthIdentifier());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiAssertorAuthName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiAssertorAuthName());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiAssertorAuthType())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiAssertorAuthType());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiAssertorAuthUrl())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiAssertorAuthUrl());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiCode())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiCode());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiMasterPrefix())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiMasterPrefix());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiMasterSuffixTable())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiMasterSuffixTable());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiInstancePrefix())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiInstancePrefix());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiInstanceSuffixTable())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiInstanceSuffixTable());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiRegOrganizationType())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiRegOrganizationType());

		if(!StringTool.isStringValid(this.getString(this.getTagDoiRegPersonType())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDoiRegPersonType());

		if(!StringTool.isStringValid(this.getString(this.getTagGridCode())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagGridCode());

		if(!StringTool.isStringValid(this.getString(this.getTagIntentPlay())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagIntentPlay());

		if(!StringTool.isStringValid(this.getString(this.getTagLogAllFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogAllFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagLogAllFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogAllFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagLogDebugFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogDebugFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagLogDebugFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogDebugFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagLogErrorFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogErrorFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagLogErrorFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogErrorFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagLogInfoFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogInfoFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagLogInfoFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagLogInfoFilePath());

		if(this.getSubDoc(this.getTagMasterKeys())==null)
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagMasterKeys());

		//TODO: Validate items under Master Secret Key

		if(!StringTool.isStringValid(this.getString(this.getTagRightsHostPort())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagRightsHostPort());

		if(!StringTool.isStringValid(this.getString(this.getTagRightsHostUrl())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagRightsHostUrl());

		if(!StringTool.isStringValid(this.getString(this.getTagServerPort())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagServerPort());

		if(!StringTool.isStringValid(this.getString(this.getTagSymmetricAlgorithmId())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagSymmetricAlgorithmId());

		if(!StringTool.isStringValid(this.getString(this.getTagSymmetricAlgorithmId())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagSymmetricAlgorithmId());

		if(!StringTool.isStringValid(this.getString(this.getTagSymmetricPadding())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagSymmetricPadding());

		if(!StringTool.isStringValid(this.getString(this.getTagSymmetricProviderId())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagSymmetricProviderId());

		if(!StringTool.isStringValid(this.getString(this.getTagSymmetricKeySize())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagSymmetricKeySize());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateAuxDataFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateAuxDataFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateAuxDataFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateAuxDataFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateSignatureFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateSignatureFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateSignatureFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateSignatureFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateDoiFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateDoiFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateDoiFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateDoiFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateLicenseOdrlFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateLicenseOdrlFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateLicenseOdrlFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateLicenseOdrlFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateEncryptedKeyFileName())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateEncryptedKeyFileName());

		if(!StringTool.isStringValid(this.getString(this.getTagTemplateEncryptedKeyFilePath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagTemplateEncryptedKeyFilePath());

		if(!StringTool.isStringValid(this.getString(this.getTagEncoderPath())))
		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagEncoderPath());
		
		/** C. Mollis 10/3/05 */
		if ( !StringTool.isStringValid( this.getString( this.getTagSPEAuthUser() ) ) )
			throw new osmsServerConfigurationException( errCode, errMissingValue, this.getTagSPEAuthUser());
		// ****************************************************************************
		//                  OPTIONAL ELEMENT SECTION
		// ****************************************************************************
//		if(!StringTool.isStringValid(this.getString(this.getTagDbPassword())))
//		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDbPassword());

//		if(!StringTool.isStringValid(this.getString(this.getTagDbUserName())))
//		    throw new osmsServerConfigurationException(errCode, errMissingValue, this.getTagDbUserName());

    }
}