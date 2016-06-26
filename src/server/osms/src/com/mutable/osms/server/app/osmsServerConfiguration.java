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


package com.mutable.osms.server.app;

import com.mutable.io.OlLogger;
import com.mutable.osms.server.app.*;
import com.mutable.osms.server.io.xml.XMLServerConfigurationDocument;

import java.io.*;

/**
* osmsServerConfiguration is the openIPMP class that houses the system
* configuration settings.  Settings related to the following items are managed:
* <ul>
*   <li>Server (Ports)
*   <li>Database (DB Provider, driver, connect url, connect user, connect password, etc...)
*   <li>Logging (Log File names, directory locations, etc...)
*   <li>Application Security (Symmetric key sizes, identifiers and providers, master secret keys, etc...)
*   <li>openIPMP Configuration (Application constants, template names, template directory locations, etc...)
* </ul>
* <p>
* @version      1.0
* @since      	1.0
*/

public class osmsServerConfiguration
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(log!=null)log.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(log!=null)log.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(log!=null)log.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(log!=null)log.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(log!=null)log.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	/**
    * The OlLogger object used for logging purposes.
    */
	OlLogger log;

	/**
    * Class constructor which creates a new osmsServerConfiguration object.  The constructor sets the object's private log member.
    */
    public osmsServerConfiguration()
    {
		log=osmsGlobalObjectManager.getInstance().getLogger();
    }

	//
	// SERVER SECTION
	//

	/**
    * The port the server is listening on.
    */
	private String m_ServerPort;
	/**
    * Gets the server's port.
	* @return the server's port
    */
	public String getServerPort()
	{
		return m_ServerPort;
	}
	/**
    * Sets the server's port to the supplied value.
	* @param ServerPort specifies the server's port
    */
	private void setServerPort(String ServerPort)
	{
		m_ServerPort=ServerPort;
	}

	//
	// DATABASE SECTION
	//

	/**
    * The name of the database provider (i.e., Oracle, MySql, etc...).
    */
	private String m_DbProvider;
	/**
    * Gets the name of the database provider.
	* @return the name of the database provider
    */
	public String getDbProvider()
	{
		return m_DbProvider;
	}
	/**
    * Sets the name of the database provider to the supplied value.
	* @param DbProvider specifies the name of the database provider
    */
	private void setDbProvider(String DbProvider)
	{
		m_DbProvider=DbProvider;
	}

	/**
    * The database driver.
    */
	private String m_DbDriver;
	/**
    * Gets the database driver.
	* @return the database driver
    */
	public String getDbDriver()
	{
		return m_DbDriver;
	}
	/**
    * Sets the database driver to the supplied value.
	* @param DbDriver   specifies the database provider
    */
	private void setDbDriver(String DbDriver)
	{
		m_DbDriver=DbDriver;
	}

	/**
    * The database connect url.
    */
	private String m_DbConnectUrl;
	/**
    * Gets the database connect url.
	* @return the database connect url
    */
	public String getDbConnectUrl()
	{
		return m_DbConnectUrl;
	}
	/**
    * Sets the database connect url to the supplied value.
	* @param DbConnectUrl   specifies the database connect url
    */
	private void setDbConnectUrl(String DbConnectUrl)
	{
		m_DbConnectUrl=DbConnectUrl;
	}

	/**
    * The user name the application users to connect to the database with.
    */
	private String m_DbUserName;
	/**
    * Gets the user name the application uses to connect to the datbase with.
	* @return the user name the application uses to connect to the datbase with
    */
	public String getDbUserName()
	{
		return m_DbUserName;
	}
	/**
    * Sets the database user name to the supplied value.
	* @param DbUserName specifies the database user name
    */
	private void setDbUserName(String DbUserName)
	{
		m_DbUserName=DbUserName;
	}

	/**
    * The password for the database user
    */
	private String m_DbPassword;
	/**
    * Gets the password for the database user.
	* @return the password for the database user
    */
	public String getDbPassword()
	{
		return m_DbPassword;
	}
	/**
    * Sets the password for the database user to the supplied value.
	* @param DbPassword   specifies the password for the database user
    */
	private void setDbPassword(String DbPassword)
	{
		m_DbPassword=DbPassword;
	}

	//
	//LOG SECTION
	//

	/**
    * The file name for the debug log file.
    */
	private String m_LogDebugFileName;
	/**
    * Gets the name of the debug log file.
	* @return the name of the debug log file
    */
	public String getLogDebugFileName()
	{
		return m_LogDebugFileName;
	}
	/**
    * Sets the name of the debug log file to the supplied value.
	* @param LogDebugFileName   specifies the name of the debug log file
    */
	private void setLogDebugFileName(String LogDebugFileName)
	{
		m_LogDebugFileName=LogDebugFileName;
	}

	/**
    * The path (relative to the application directory) for the debug log file.
    */
	private String m_LogDebugFilePath;
	/**
    * Gets the path (relative to the application directory) of the debug log file.
	* @return the path of the debug log file
    */
	public String getLogDebugFilePath()
	{
		return m_LogDebugFilePath;
	}
	/**
    * Sets the path (relative to the application directory) of the debug log file to the supplied value.
	* @param LogDebugFilePath   specifies the path of the debug log file
    */
	private void setLogDebugFilePath(String LogDebugFilePath)
	{
		m_LogDebugFilePath=LogDebugFilePath;
	}

	/**
    * The file name for the error log file.
    */
	private String m_LogErrorFileName;
	/**
    * Gets the name of the error log file.
	* @return the name of the error log file
    */
	public String getLogErrorFileName()
	{
		return m_LogErrorFileName;
	}
	/**
    * Sets the name of the error log file to the supplied value.
	* @param LogErrorFileName   specifies the name of the error log file
    */
	private void setLogErrorFileName(String LogErrorFileName)
	{
		m_LogErrorFileName=LogErrorFileName;
	}

	/**
    * The path (relative to the application directory) for the eror log file.
    */
	private String m_LogErrorFilePath;
	/**
    * Gets the path (relative to the application directory) of the error log file.
	* @return the path of the error log file
    */
	public String getLogErrorFilePath()
	{
		return m_LogErrorFilePath;
	}
	/**
    * Sets the path (relative to the application directory) of the error log file to the supplied value.
	* @param LogErrorFilePath   specifies the path of the error log file
    */
	private void setLogErrorFilePath(String LogErrorFilePath)
	{
		m_LogErrorFilePath=LogErrorFilePath;
	}

	/**
    * The file name for the general info log file.
    */
	private String m_LogInfoFileName;
	/**
    * Gets the name of the general info log file.
	* @return the name of the general info log file
    */
	public String getLogInfoFileName()
	{
		return m_LogInfoFileName;
	}
	/**
    * Sets the name of the info log file to the supplied value.
	* @param LogInfoFileName   specifies the name of the info log file
    */
	private void setLogInfoFileName(String LogInfoFileName)
	{
		m_LogInfoFileName=LogInfoFileName;
	}

	/**
    * The path (relative to the application directory) for the general info log file.
    */
	private String m_LogInfoFilePath;
	/**
    * Gets the path (relative to the application directory) of the general info log file.
	* @return the path of the general info log file
    */
	public String getLogInfoFilePath()
	{
		return m_LogInfoFilePath;
	}
	/**
    * Sets the path (relative to the application directory) of the general info log file to the supplied value.
	* @param LogInfoFilePath   specifies the path of the general info log file
    */
	private void setLogInfoFilePath(String LogInfoFilePath)
	{
		m_LogInfoFilePath=LogInfoFilePath;
	}

	/**
    * The file name for the default log file.
    */
	private String m_LogAllFileName;
	/**
    * Gets the name of the default log file.
	* @return the name of the default log file
    */
	public String getLogAllFileName()
	{
		return m_LogAllFileName;
	}
	/**
    * Sets the name of the default log file to the supplied value.
	* @param LogAllFileName   specifies the name of the default log file
    */
	private void setLogAllFileName(String LogAllFileName)
	{
		m_LogAllFileName=LogAllFileName;
	}

	/**
    * The path (relative to the application directory) for the default log file.
    */
	private String m_LogAllFilePath;
	/**
    * Gets the path (relative to the application directory) of the default log file.
	* @return the path of the default log file
    */
	public String getLogAllFilePath()
	{
		return m_LogAllFilePath;
	}
	/**
    * Sets the path (relative to the application directory) of the default log file to the supplied value.
	* @param LogAllFilePath   specifies the path of the default log file
    */
	private void setLogAllFilePath(String LogAllFilePath)
	{
		m_LogAllFilePath=LogAllFilePath;
	}

	//
	//SECURITY SECTION
	//

	/**
    * The identifier for the symmetric key algorithm.
    */
	private String m_SymmetricAlgorithmId;
	/**
    * Gets the identifier for the symmetric key algorithm.
	* @return the identifier for the symmetric key algorithm
    */
	public String getSymmetricAlgorithmId()
	{
		return m_SymmetricAlgorithmId;
	}
	private void setSymmetricAlgorithmId(String SymmetricAlgorithmId)
	{
		m_SymmetricAlgorithmId=SymmetricAlgorithmId;
	}

	/**
    * The identifier for the symmetric key algorithm provider.
    */
	private String m_SymmetricProviderId;
	/**
    * Gets the identifier of the provider of the symmetric key algorithm.
	* @return the identifier of the provider of the symmetric key algorithm
    */
	public String getSymmetricProviderId()
	{
		return m_SymmetricProviderId;
	}
	private void setSymmetricProviderId(String SymmetricProviderId)
	{
		m_SymmetricProviderId=SymmetricProviderId;
	}

	/**
    * The padding used with symmetric key encryption.
    */
	private String m_SymmetricPadding;
	/**
    * Gets the padding that is used for symmetric key encryption.
	* @return the padding that is used for symmetric key encryption
    */
	public String getSymmetricPadding()
	{
		return m_SymmetricPadding;
	}
	private void setSymmetricPadding(String SymmetricPadding)
	{
		m_SymmetricPadding=SymmetricPadding;
	}

	/**
    * The size (in bits) of the symmetric keys.
    */
	private Integer m_SymmetricKeySize;
	/**
    * Gets the size (in bits) of the symmetric keys.
	* @return the size (in bits) of the symmetric keys
    */
	public Integer getSymmetricKeySize()
	{
		return m_SymmetricKeySize;
	}
	private void setSymmetricKeySize(Integer SymmetricKeySize)
	{
		m_SymmetricKeySize=SymmetricKeySize;
	}

	/**
    * The identifier for the asymmetric key algorithm.
    */
	private String m_AsymmetricAlgorithmId;
	/**
    * Gets the identifier of the asymmetric key algorithm.
	* @return the identifier of the asymmetric key algorithm
    */
	public String getAsymmetricAlgorithmId()
	{
		return m_AsymmetricAlgorithmId;
	}
	private void setAsymmetricAlgorithmId(String AsymmetricAlgorithmId)
	{
		m_AsymmetricAlgorithmId=AsymmetricAlgorithmId;
	}

	/**
    * The identifier for the asymmetric key algorithm provider.
    */
	private String m_AsymmetricProviderId;
	/**
    * Gets the identifier of the provider of the asymmetric key algorithm.
	* @return the identifier of the provider of the asymmetric key algorithm
    */
	public String getAsymmetricProviderId()
	{
		return m_AsymmetricProviderId;
	}
	private void setAsymmetricProviderId(String AsymmetricProviderId)
	{
		m_AsymmetricProviderId=AsymmetricProviderId;
	}

	/**
    * The size (in bits) of the asymmetric keys.
    */
	private Integer m_AsymmetricKeySize;
	/**
    * Gets the size (in bits) of the asymmetric keys.
	* @return the size (in bits) of the asymmetric keys
    */
	public Integer getAsymmetricKeySize()
	{
		return m_AsymmetricKeySize;
	}
	private void setAsymmetricKeySize(Integer AsymmetricKeySize)
	{
		m_AsymmetricKeySize=AsymmetricKeySize;
	}

	/**
    * The master secret key objects.
    */
	private osmsMasterKey[] m_MasterKeys;
	/**
    * Gets the master secret key objects.
	* @return the master secret key objects
    */
	public osmsMasterKey[] getMasterKeys()
	{
		return m_MasterKeys;
	}
	private void setMasterKeys(osmsMasterKey[] MasterKeys)
	{
		m_MasterKeys=MasterKeys;
	}

	//
	//DOI SECTION
	//

	/**
    * The code for DOIs.
    */
	private String m_DoiCode;
	/**
    * Gets the code for DOIs.
	* @return the code for DOIs
    */
	public String getDoiCode()
	{
		return m_DoiCode;
	}
	private void setDoiCode(String DoiCode)
	{
		m_DoiCode=DoiCode;
	}

	/**
    * The default DOI application profile to use.
    */
	private String m_DoiAppProfile;
	/**
    * Gets the default DOI application profile.
	* @return the default DOI application profile
    */
	public String getDoiAppProfile()
	{
		return m_DoiAppProfile;
	}
	private void setDoiAppProfile(String DoiAppProfile)
	{
		m_DoiAppProfile=DoiAppProfile;
	}

	/**
    * The DOI Master Identifier prefix.
    */
	private String m_DoiMasterPrefix;
	/**
    * Gets the DOI Master Identifier prefix.
	* @return the DOI Master Identifier prefix
    */
	public String getDoiMasterPrefix()
	{
		return m_DoiMasterPrefix;
	}
	private void setDoiMasterPrefix(String DoiMasterPrefix)
	{
		m_DoiMasterPrefix=DoiMasterPrefix;
	}

	/**
    * The name of the DB table for assigning Master Identifier suffixes.
    */
	private String m_DoiMasterSuffixTable;
	/**
    * Gets the name of the DB table for assigning Master Identifier suffixes.
	* @return the name of the DB table for assigning Master Identifier suffixes
    */
	public String getDoiMasterSuffixTable()
	{
		return m_DoiMasterSuffixTable;
	}
	private void setDoiMasterSuffixTable(String DoiMasterSuffixTable)
	{
		m_DoiMasterSuffixTable=DoiMasterSuffixTable;
	}

	/**
    * The DOI Instance Identifier prefix.
    */
	private String m_DoiInstancePrefix;
	/**
    * Gets the DOI Instance Identifier prefix.
	* @return the DOI Instance Identifier prefix
    */
	public String getDoiInstancePrefix()
	{
		return m_DoiInstancePrefix;
	}
	private void setDoiInstancePrefix(String DoiInstancePrefix)
	{
		m_DoiInstancePrefix=DoiInstancePrefix;
	}

	/**
    * The name of the DB table for assigning Instance Identifier suffixes.
    */
	private String m_DoiInstanceSuffixTable;
	/**
    * Gets the name of the DB table for assigning Instance Identifier suffixes.
	* @return the name of the DB table for assigning Instance Identifier suffixes
    */
	public String getDoiInstanceSuffixTable()
	{
		return m_DoiInstanceSuffixTable;
	}
	private void setDoiInstanceSuffixTable(String DoiInstanceSuffixTable)
	{
		m_DoiInstanceSuffixTable=DoiInstanceSuffixTable;
	}

	/**
    * The Name of the Authority registering DOIs.
    */
	private String m_DoiAssertorAuthName;
	public String getDoiAssertorAuthName()
	{
		return m_DoiAssertorAuthName;
	}
	private void setDoiAssertorAuthName(String DoiAssertorAuthName)
	{
		m_DoiAssertorAuthName=DoiAssertorAuthName;
	}

	/**
    * The type of the Authority registering DOIs.
    */
	private String m_DoiAssertorAuthType;
	public String getDoiAssertorAuthType()
	{
		return m_DoiAssertorAuthType;
	}
	private void setDoiAssertorAuthType(String DoiAssertorAuthType)
	{
		m_DoiAssertorAuthType=DoiAssertorAuthType;
	}

	/**
    * The identifier of the Authority registering DOIs.
    */
	private String m_DoiAssertorAuthIdentifier;
	public String getDoiAssertorAuthIdentifier()
	{
		return m_DoiAssertorAuthIdentifier;
	}
	private void setDoiAssertorAuthIdentifier(String DoiAssertorAuthIdentifier)
	{
		m_DoiAssertorAuthIdentifier=DoiAssertorAuthIdentifier;
	}

	/**
    * The Url of the Authority registering DOIs.
    */
	private String m_DoiAssertorAuthUrl;
	public String getDoiAssertorAuthUrl()
	{
		return m_DoiAssertorAuthUrl;
	}
	private void setDoiAssertorAuthUrl(String DoiAssertorAuthUrl)
	{
		m_DoiAssertorAuthUrl=DoiAssertorAuthUrl;
	}

	/**
    * The default Organization code for DOI registrants.
    */
	private String m_DoiRegOrganizationType;
	public String getDoiRegOrganizationType()
	{
		return m_DoiRegOrganizationType;
	}
	private void setDoiRegOrganizationType(String DoiRegOrganizationType)
	{
		m_DoiRegOrganizationType=DoiRegOrganizationType;
	}

	/**
    * The default Person code for DOI registrants.
    */
	private String m_DoiRegPersonType;
	public String getDoiRegPersonType()
	{
		return m_DoiRegPersonType;
	}
	private void setDoiRegPersonType(String DoiRegPersonType)
	{
		m_DoiRegPersonType=DoiRegPersonType;
	}

	/**
    * The code for GRIDs (Global Resource Identifier).
    */
	private String m_GridCode;
	/**
    * Gets the code for GRIDs.
	* @return the code for GRIDs
    */
	public String getGridCode()
	{
		return m_GridCode;
	}
	private void setGridCode(String GridCode)
	{
		m_GridCode=GridCode;
	}

	/**
    * The file name for the DOI Template.
    */
	private String m_TemplateDoiFileName;
	public String getTemplateDoiFileName()
	{
		return m_TemplateDoiFileName;
	}
	private void setTemplateDoiFileName(String TemplateDoiFileName)
	{
		m_TemplateDoiFileName=TemplateDoiFileName;
	}

	//Template Doi File Path
	private String m_TemplateDoiFilePath;
	public String getTemplateDoiFilePath()
	{
		return m_TemplateDoiFilePath;
	}
	private void setTemplateDoiFilePath(String TemplateDoiFilePath)
	{
		m_TemplateDoiFilePath=TemplateDoiFilePath;
	}

	/**
    * The file name for the AuxData Template.
    */
	private String m_TemplateAuxDataFileName;
	public String getTemplateAuxDataFileName()
	{
		return m_TemplateAuxDataFileName;
	}
	private void setTemplateAuxDataFileName(String TemplateAuxDataFileName)
	{
		m_TemplateAuxDataFileName=TemplateAuxDataFileName;
	}

	//Template AuxData File Path
	private String m_TemplateAuxDataFilePath;
	public String getTemplateAuxDataFilePath()
	{
		return m_TemplateAuxDataFilePath;
	}
	private void setTemplateAuxDataFilePath(String TemplateAuxDataFilePath)
	{
		m_TemplateAuxDataFilePath=TemplateAuxDataFilePath;
	}

	/**
    * The file name for the Signature Template.
    */
	private String m_TemplateSignatureFileName;
	public String getTemplateSignatureFileName()
	{
		return m_TemplateSignatureFileName;
	}
	private void setTemplateSignatureFileName(String TemplateSignatureFileName)
	{
		m_TemplateSignatureFileName=TemplateSignatureFileName;
	}

	//Template Signature File Path
	private String m_TemplateSignatureFilePath;
	public String getTemplateSignatureFilePath()
	{
		return m_TemplateSignatureFilePath;
	}
	private void setTemplateSignatureFilePath(String TemplateSignatureFilePath)
	{
		m_TemplateSignatureFilePath=TemplateSignatureFilePath;
	}

	/**
    * The file name for the License ODRL Template.
    */
	private String m_TemplateLicenseOdrlFileName;
	public String getTemplateLicenseOdrlFileName()
	{
		return m_TemplateLicenseOdrlFileName;
	}
	private void setTemplateLicenseOdrlFileName(String TemplateLicenseOdrlFileName)
	{
		m_TemplateLicenseOdrlFileName=TemplateLicenseOdrlFileName;
	}

	//Template LicenseOdrl File Path
	private String m_TemplateLicenseOdrlFilePath;
	public String getTemplateLicenseOdrlFilePath()
	{
		return m_TemplateLicenseOdrlFilePath;
	}
	private void setTemplateLicenseOdrlFilePath(String TemplateLicenseOdrlFilePath)
	{
		m_TemplateLicenseOdrlFilePath=TemplateLicenseOdrlFilePath;
	}

	/**
    * The file name for the Encrypted Key Transport Template.
    */
	private String m_TemplateEncryptedKeyFileName;
	public String getTemplateEncryptedKeyFileName()
	{
		return m_TemplateEncryptedKeyFileName;
	}
	private void setTemplateEncryptedKeyFileName(String TemplateEncryptedKeyFileName)
	{
		m_TemplateEncryptedKeyFileName=TemplateEncryptedKeyFileName;
	}

	//Template Encrypted Key Transport File Path
	private String m_TemplateEncryptedKeyFilePath;
	public String getTemplateEncryptedKeyFilePath()
	{
		return m_TemplateEncryptedKeyFilePath;
	}
	private void setTemplateEncryptedKeyFilePath(String TemplateEncryptedKeyFilePath)
	{
		m_TemplateEncryptedKeyFilePath=TemplateEncryptedKeyFilePath;
	}

	/**
    * The Url for the rights host.
    */
	private String m_RightsHostUrl;
	public String getRightsHostUrl()
	{
		return m_RightsHostUrl;
	}
	private void setRightsHostUrl(String RightsHostUrl)
	{
		m_RightsHostUrl=RightsHostUrl;
	}

	/**
    * The Port for the rights host.
    */
	private String m_RightsHostPort;
	public String getRightsHostPort()
	{
		return m_RightsHostPort;
	}
	private void setRightsHostPort(String RightsHostPort)
	{
		m_RightsHostPort=RightsHostPort;
	}

	/**
    * The code for the PLAY Intent.
    */
	private String m_IntentPlay;
	public String getIntentPlay()
	{
		return m_IntentPlay;
	}
	private void setIntentPlay(String IntentPlay)
	{
		m_IntentPlay=IntentPlay;
	}

	/**
    * The audit user id for database updates.
    */
	private String m_AuditUpdateUser;
	public String getAuditUpdateUser()
	{
		return m_AuditUpdateUser;
	}
	private void setAuditUpdateUser(String AuditUpdateUser)
	{
		m_AuditUpdateUser=AuditUpdateUser;
	}

	/**
    * The audit user id for database creates.
    */
	private String m_AuditCreateUser;
	public String getAuditCreateUser()
	{
		return m_AuditCreateUser;
	}
	private void setAuditCreateUser(String AuditCreateUser)
	{
		m_AuditCreateUser=AuditCreateUser;
	}

	//
	// Encoder Section
	//
	private String m_EncoderPath;
	public String getEncoderPath()
	{
		return m_EncoderPath;
	}
	private void setEncoderPath(String EncoderPath)
	{
		m_EncoderPath=EncoderPath;
	}

	/** C. Mollis 10-3-05 */
	// ExternalAuth Section
	//
	private String m_SPEAuthUser;
	public String getSPEAuthUser()
	{
		return m_SPEAuthUser;
	}
	private void setSPEAuthUser(String authSwitch)
	{
		m_SPEAuthUser= authSwitch;
	}
	
	
	//
	// Non-XML Section
	//
	//OpenIPMP Parent Directory
	private File m_OpenIpmpParentDir;
	public File getOpenIpmpParentDir()
	{
		return m_OpenIpmpParentDir;
	}
	public void setOpenIpmpParentDir(File OpenIpmpParentDir)
	{
		m_OpenIpmpParentDir=OpenIpmpParentDir;
	}

	//OpenIPMP Aux Data Template Xml
	private String m_OpenIpmpTemplateAuxDataXml;
	public String getOpenIpmpTemplateAuxDataXml()
	{
		return m_OpenIpmpTemplateAuxDataXml;
	}
	public void setOpenIpmpTemplateAuxDataXml(String OpenIpmpTemplateAuxDataXml)
	{
		m_OpenIpmpTemplateAuxDataXml=OpenIpmpTemplateAuxDataXml;
	}

	//OpenIPMP Signature Template Xml
	private String m_OpenIpmpTemplateSignatureXml;
	public String getOpenIpmpTemplateSignatureXml()
	{
		return m_OpenIpmpTemplateSignatureXml;
	}
	public void setOpenIpmpTemplateSignatureXml(String OpenIpmpTemplateSignatureXml)
	{
		m_OpenIpmpTemplateSignatureXml=OpenIpmpTemplateSignatureXml;
	}

	//OpenIPMP DOI Template Xml
	private String m_OpenIpmpTemplateDoiXml;
	public String getOpenIpmpTemplateDoiXml()
	{
		return m_OpenIpmpTemplateDoiXml;
	}
	public void setOpenIpmpTemplateDoiXml(String OpenIpmpTemplateDoiXml)
	{
		m_OpenIpmpTemplateDoiXml=OpenIpmpTemplateDoiXml;
	}

	//OpenIPMP ODRL Template Xml
	private String m_OpenIpmpTemplateOdrlXml;
	public String getOpenIpmpTemplateOdrlXml()
	{
		return m_OpenIpmpTemplateOdrlXml;
	}
	public void setOpenIpmpTemplateOdrlXml(String OpenIpmpTemplateOdrlXml)
	{
		m_OpenIpmpTemplateOdrlXml=OpenIpmpTemplateOdrlXml;
	}

	//OpenIPMP Encrypted Key Template Xml
	private String m_OpenIpmpTemplateEncryptedKeyXml;
	public String getOpenIpmpTemplateEncryptedKeyXml()
	{
		return m_OpenIpmpTemplateEncryptedKeyXml;
	}
	public void setOpenIpmpTemplateEncryptedKeyXml(String OpenIpmpTemplateEncryptedKeyXml)
	{
		m_OpenIpmpTemplateEncryptedKeyXml=OpenIpmpTemplateEncryptedKeyXml;
	}

	/*-------------------------------------------------------------------
	* public void build(XMLServerConfigurationDocument doc) throws Exception
	*
	* Description: set private attributes from xml configuration document
	*
	* @param XMLServerConfigurationDocument doc
	* @return void
	**-------------------------------------------------------------------*/
	public void build(XMLServerConfigurationDocument doc) throws Exception
	{
		String methodName = "build";
		try
		{
		    doc.validate();
			setServerPort(doc.getString(doc.getTagServerPort()));
			setDbProvider(doc.getString(doc.getTagDbProvider()));
			setDbDriver(doc.getString(doc.getTagDbDriver()));
			setDbConnectUrl(doc.getString(doc.getTagDbConnectUrl()));
			setDbUserName(doc.getString(doc.getTagDbUserName()));
			setDbPassword(doc.getString(doc.getTagDbPassword()));
			setLogAllFileName(doc.getString(doc.getTagLogAllFileName()));
			setLogAllFilePath(doc.getString(doc.getTagLogAllFilePath()));
			setLogDebugFileName(doc.getString(doc.getTagLogDebugFileName()));
			setLogDebugFilePath(doc.getString(doc.getTagLogDebugFilePath()));
			setLogErrorFileName(doc.getString(doc.getTagLogErrorFileName()));
			setLogErrorFilePath(doc.getString(doc.getTagLogErrorFilePath()));
			setLogInfoFileName(doc.getString(doc.getTagLogInfoFileName()));
			setLogInfoFilePath(doc.getString(doc.getTagLogInfoFilePath()));
			setSymmetricAlgorithmId(doc.getString(doc.getTagSymmetricAlgorithmId()));
			setSymmetricProviderId(doc.getString(doc.getTagSymmetricProviderId()));
			setSymmetricPadding(doc.getString(doc.getTagSymmetricPadding()));
			setSymmetricKeySize(doc.getInteger(doc.getTagSymmetricKeySize()));
			setAsymmetricAlgorithmId(doc.getString(doc.getTagAsymmetricAlgorithmId()));
			setAsymmetricProviderId(doc.getString(doc.getTagAsymmetricProviderId()));
			setAsymmetricKeySize(doc.getInteger(doc.getTagAsymmetricKeySize()));
			setDoiCode(doc.getString(doc.getTagDoiCode()));
			setDoiAppProfile(doc.getString(doc.getTagDoiAppProfile()));
			setDoiMasterPrefix(doc.getString(doc.getTagDoiMasterPrefix()));
			setDoiMasterSuffixTable(doc.getString(doc.getTagDoiMasterSuffixTable()));
			setDoiInstancePrefix(doc.getString(doc.getTagDoiInstancePrefix()));
			setDoiInstanceSuffixTable(doc.getString(doc.getTagDoiInstanceSuffixTable()));
			setDoiAssertorAuthName(doc.getString(doc.getTagDoiAssertorAuthName()));
			setDoiAssertorAuthType(doc.getString(doc.getTagDoiAssertorAuthType()));
			setDoiAssertorAuthIdentifier(doc.getString(doc.getTagDoiAssertorAuthIdentifier()));
			setDoiAssertorAuthUrl(doc.getString(doc.getTagDoiAssertorAuthUrl()));
			setDoiRegOrganizationType(doc.getString(doc.getTagDoiRegOrganizationType()));
			setDoiRegPersonType(doc.getString(doc.getTagDoiRegPersonType()));
			setGridCode(doc.getString(doc.getTagGridCode()));
			setTemplateDoiFileName(doc.getString(doc.getTagTemplateDoiFileName()));
			setTemplateDoiFilePath(doc.getString(doc.getTagTemplateDoiFilePath()));
			setTemplateAuxDataFileName(doc.getString(doc.getTagTemplateAuxDataFileName()));
			setTemplateAuxDataFilePath(doc.getString(doc.getTagTemplateAuxDataFilePath()));
			setTemplateSignatureFileName(doc.getString(doc.getTagTemplateSignatureFileName()));
			setTemplateSignatureFilePath(doc.getString(doc.getTagTemplateSignatureFilePath()));
			setTemplateLicenseOdrlFileName(doc.getString(doc.getTagTemplateLicenseOdrlFileName()));
			setTemplateLicenseOdrlFilePath(doc.getString(doc.getTagTemplateLicenseOdrlFilePath()));
			setTemplateEncryptedKeyFileName(doc.getString(doc.getTagTemplateEncryptedKeyFileName()));
			setTemplateEncryptedKeyFilePath(doc.getString(doc.getTagTemplateEncryptedKeyFilePath()));
			setRightsHostUrl(doc.getString(doc.getTagRightsHostUrl()));
			setRightsHostPort(doc.getString(doc.getTagRightsHostPort()));
			setIntentPlay(doc.getString(doc.getTagIntentPlay()));
			setAuditUpdateUser(doc.getString(doc.getTagAuditUpdateUser()));
			setAuditCreateUser(doc.getString(doc.getTagAuditCreateUser()));
			setEncoderPath(doc.getString(doc.getTagEncoderPath()));
			setSPEAuthUser( doc.getString( doc.getTagSPEAuthUser() ) );
			//TODO: Master Secret Key handling
//			this.setXXX(doc.getString(doc.getTagMasterKeys());
//			this.setXXX(doc.getString(doc.getTagMasterKey());
//			this.setXXX(doc.getString(doc.getTagMasterKeyId());
//			this.setXXX(doc.getString(doc.getTagMasterKeyFileName());
//			this.setXXX(doc.getString(doc.getTagMasterKeyPath());
		}
		catch (osmsServerConfigurationException e)
		{
			System.out.println("Error encountered in: "+className+":"+methodName+" "+e.getErrorCode()+" "+e.getMessage()+" "+e.getErrorXmlTag());
			logError(methodName, e.getErrorCode()+" "+e.getMessage(), e);
			throw e;
		}
	}

	public void print()
	{
		String methodName = "print";
		logInfo(methodName, "*************************************************************************************************");
		logInfo(methodName, "***************************** OPENIPMP SERVER CONFIGURATION *************************************");
		logInfo(methodName, "*************************************************************************************************");
		logInfo(methodName, "ServerPort: " + getServerPort());
		logInfo(methodName, "DbProvider: " + getDbProvider());
		logInfo(methodName, "DbDriver: " + getDbDriver());
		logInfo(methodName, "DbConnectUrl: " + getDbConnectUrl());
		logInfo(methodName, "DbUserName: " + getDbUserName());
		logInfo(methodName, "DbPassword: " + getDbPassword());
		logInfo(methodName, "LogAllFileName: " + getLogAllFileName());
		logInfo(methodName, "LogAllFilePath: " + getLogAllFilePath());
		logInfo(methodName, "logDebugFileName: " + getLogDebugFileName());
		logInfo(methodName, "logDebugFilePath: " + getLogDebugFilePath());
		logInfo(methodName, "LogErrorFileName: " + getLogErrorFileName());
		logInfo(methodName, "LogErrorFilePath: " + getLogErrorFilePath());
		logInfo(methodName, "LogInfoFileName: " + getLogInfoFileName());
		logInfo(methodName, "LogInfoFilePath: " + getLogInfoFilePath());
		logInfo(methodName, "SymmetricAlgorithmId: " + getSymmetricAlgorithmId());
		logInfo(methodName, "SymmetricProviderId: " + getSymmetricProviderId());
		logInfo(methodName, "SymmetricPadding: " + getSymmetricPadding());
		logInfo(methodName, "SymmetricKeySize: " + getSymmetricKeySize());
		logInfo(methodName, "AsymmetricAlgorithmId: " + getAsymmetricAlgorithmId());
		logInfo(methodName, "AsymmetricProviderId: " + getAsymmetricProviderId());
		logInfo(methodName, "AsymmetricKeySize: " + getAsymmetricKeySize());
		logInfo(methodName, "DoiCode: " + getDoiCode());
		logInfo(methodName, "DoiAppProfile: " + getDoiAppProfile());
		logInfo(methodName, "DoiMasterPrefix: " + getDoiMasterPrefix());
		logInfo(methodName, "DoiMasterSuffixTable: " + getDoiMasterSuffixTable());
		logInfo(methodName, "DoiInstancePrefix: " + getDoiInstancePrefix());
		logInfo(methodName, "DoiInstanceSuffixTable: " + getDoiInstanceSuffixTable());
		logInfo(methodName, "DoiAssertorAuthName: " + getDoiAssertorAuthName());
		logInfo(methodName, "DoiAssertorAuthType: " + getDoiAssertorAuthType());
		logInfo(methodName, "DoiAssertorAuthIdentifier: " + getDoiAssertorAuthIdentifier());
		logInfo(methodName, "DoiAssertorAuthUrl: " + getDoiAssertorAuthUrl());
		logInfo(methodName, "DoiRegOrganizationType: " + getDoiRegOrganizationType());
		logInfo(methodName, "DoiRegPersonType: " + getDoiRegPersonType());
		logInfo(methodName, "GridCode: " + getGridCode());
		logInfo(methodName, "TemplateDoiFileName: " + getTemplateDoiFileName());
		logInfo(methodName, "TemplateDoiFilePath: " + getTemplateDoiFilePath());
		logInfo(methodName, "TemplateAuxDataFileName: " + getTemplateAuxDataFileName());
		logInfo(methodName, "TemplateAuxDataFilePath: " + getTemplateAuxDataFilePath());
		logInfo(methodName, "TemplateSignatureFileName: " + getTemplateSignatureFileName());
		logInfo(methodName, "TemplateSignatureFilePath: " + getTemplateSignatureFilePath());
		logInfo(methodName, "TemplateLicenseOdrlFileName: " + getTemplateLicenseOdrlFileName());
		logInfo(methodName, "TemplateLicenseOdrlFilePath: " + getTemplateLicenseOdrlFilePath());
		logInfo(methodName, "TemplateEncryptedKeyFileName: " + getTemplateEncryptedKeyFileName());
		logInfo(methodName, "TemplateEncryptedKeyFilePath: " + getTemplateEncryptedKeyFilePath());
		logInfo(methodName, "RightsHostUrl: " + getRightsHostUrl());
		logInfo(methodName, "RightsHostPort: " + getRightsHostPort());
		logInfo(methodName, "IntentPlay: " + getIntentPlay());
		logInfo(methodName, "AuditUpdateUser: " + getAuditUpdateUser());
		logInfo(methodName, "AuditCreateUser: " + getAuditCreateUser());
		logInfo(methodName, "EncoderPath: " + getEncoderPath());
		logInfo(methodName, "SPEAuthUser: " + getSPEAuthUser () );
			//TODO: Master Secret Key handling
//			logInfo(methodName, ": " + getXXX());
//			logInfo(methodName, ": " + getXXX());
//			logInfo(methodName, ": " + getXXX());
//			logInfo(methodName, ": " + getXXX());
//			logInfo(methodName, ": " + getXXX());
		logInfo(methodName, "*************************************************************************************************");
	}


	/**
	 * <p>Title: osmsMasterKey</p>
	 * <p>Description: Object that manages information about a secret key</p>
	 * @version 1.0
	 */

	private class osmsMasterKey
	{

		public osmsMasterKey()
		{
		}
		//Master Key File Name
		private String m_MasterKeyFileName;
		public String getMasterKeyFileName()
		{
			return m_MasterKeyFileName;
		}
		private void setMasterKeyFileName(String MasterKeyFileName)
		{
			m_MasterKeyFileName=MasterKeyFileName;
		}

		//Master Key File Path
		private String m_MasterKeyFilePath;
		public String getMasterKeyFilePath()
		{
			return m_MasterKeyFilePath;
		}
		private void setMasterKeyFilePath(String MasterKeyFilePath)
		{
			m_MasterKeyFilePath=MasterKeyFilePath;
		}

		//Master Key Id
		private Integer m_MasterKeyId;
		public Integer getMasterKeyId()
		{
			return m_MasterKeyId;
		}
		private void setMasterKeyId(Integer MasterKeyId)
		{
			m_MasterKeyId=MasterKeyId;
		}
	}
}