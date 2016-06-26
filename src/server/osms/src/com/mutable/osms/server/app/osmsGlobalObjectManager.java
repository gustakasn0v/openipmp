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

package com.mutable.osms.server.app;

import java.io.*;
import java.lang.reflect.*;
import java.sql.*;
import java.text.*;
import java.util.*;
import java.security.Security;
//import org.w3c.dom.*;
//import org.xml.sax.*;
//import org.apache.xerces.parsers.*;

import com.mutable.io.*;
import com.mutable.io.tools.FileTool;
import com.mutable.io.tools.StringTool;
//import com.mutable.io.message.dispatcher.*;
//import com.mutable.scheduler.*;
import com.mutable.osms.server.db.*;
import com.mutable.osms.server.app.ca.*;
import com.mutable.osms.server.app.osmsLoginManager;
import com.mutable.osms.server.io.xml.XMLServerConfigurationDocument;
public class osmsGlobalObjectManager
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

	private osmsGlobalObjectManager() throws Exception
	{

	}
	private OlLogger m_logger = new OlLogger();
	public OlLogger getLogger(){return m_logger;}

//	dbPool m_dbPool = new dbPool("oracle.jdbc.driver.OracleDriver","jdbc:oracle:thin:@localhost:1521:gdb","OSMSDEMO","osmsdemo");
//	osmsDbPool m_dbPool = new osmsDbPool("org.gjt.mm.mysql.Driver","jdbc:mysql://localhost:3306/MySql", "", "",m_logger);
//	osmsDbPool m_dbPool = new osmsDbPool("oracle.jdbc.driver.OracleDriver","jdbc:oracle:thin:@localhost:1521:gdb", "osms", "osms",m_logger);
	private osmsDbPool m_dbPool = null;
	public osmsDbPool getDBPool()
	{
		return m_dbPool;
	}

	private osmsServerConfiguration m_osmsServerConfiguration = null;
	public osmsServerConfiguration getOsmsServerConfiguration(){return m_osmsServerConfiguration;}

//	private OlMessageDispatcherCallbackInterface m_dispatchCallback = new osmsServerDispatchCallback(m_logger);
//	public OlMessageDispatcherCallbackInterface getDispatchCallback(){return m_dispatchCallback;}

//	private OlScheduler m_scheduler = new OlScheduler(m_logger);
//	public OlScheduler getScheduler(){return m_scheduler;}

	private osmsDatabase m_osmsDatabase;
	public osmsDatabase getDatabase(){return m_osmsDatabase;}

	private osmsRightsManager m_osmsRightsManager;
	public osmsRightsManager getRightsManager() {return m_osmsRightsManager;}

	private osmsLoginManager m_osmsLoginManager;
	public osmsLoginManager getLoginManager() {return m_osmsLoginManager;}

	private osmsContentManager m_osmsContentManager;
	public osmsContentManager getContentManager() {return m_osmsContentManager;}

	private osmsEncoderManager m_osmsEncoderManager;
	public osmsEncoderManager getEncoderManager() {return m_osmsEncoderManager;}

	private CertificateAuthority m_ca;
	public CertificateAuthority getCerfiticateAuthority(){return m_ca;}

	private int m_port=9999;
	public int getPort(){return m_port;}

    private static osmsGlobalObjectManager instance = null;
    public static osmsGlobalObjectManager getInstance()
	{
		String methodName="osmsGlobalObjectManager";
        if (instance == null)
		{
			try
			{
				instance = new osmsGlobalObjectManager();
				instance.init(null);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}

        return instance;
    }
	private CAManagerEjbca caManager;

	private static File m_OpenIpmpDir = null;
	public static File getOpenIpmpParentDirectory() {return m_OpenIpmpDir;}
	public static void setOpenIpmpParentDirectory(File openIpmpDir) throws Exception
	{
		m_OpenIpmpDir = openIpmpDir;
	}
	private void setOpenIpmpParentDirectory() throws Exception
		{
		String openIPMPDirName = "openIPMP";
		String methodName = "setOpenIpmpParentDirectory";

		//Get Current directory (should be something like ..\jboss\bin)
		File curDir = new File(System.getProperty("user.dir"));
		if(!curDir.exists() || !curDir.isDirectory())
			throw new Exception("Error encountered determining current directory");

		logDebug(methodName, "Absolute path to current Directory is: " + curDir.getAbsolutePath());

		//Go up to the main jboss directory (should be something like ..\jboss\)
		File parentDir = curDir.getParentFile();
		if(!parentDir.exists() || !parentDir.isDirectory())
			throw new Exception("Parent Directory does not exist or does not exist as a directory");

		logDebug(methodName, "Absolute path to parent Directory is: " + parentDir.getAbsolutePath());

		//Go down to the openIPMP directory (should be something like ..\jboss\openIPMP)
		File openIPMPDir = new File(parentDir, openIPMPDirName);
		if(!openIPMPDir.exists() || !openIPMPDir.isDirectory())
			throw new Exception("openIPMP Directory does not exist or does not exist as a directory");

		logDebug(methodName, "Absolute path to openIPMP Directory is: " + openIPMPDir.getAbsolutePath());

		m_OpenIpmpDir = openIPMPDir;
	}

	public boolean checkOpenIpmpParentDirectory(){
		if (m_OpenIpmpDir != null)
			return (!m_OpenIpmpDir.exists() || !m_OpenIpmpDir.isDirectory());
		else
			return false;
	}

	private osmsServerConfiguration loadConfigurationDataFromFile() throws Exception
	{
		String methodName = "loadConfigurationDataFromFile";

		File openIPMPDir = this.getOpenIpmpParentDirectory();

		//Make sure openIPMPDir exists and is a directory
		if(openIPMPDir.exists() && openIPMPDir.isDirectory())
		{
			String fileName = openIPMPDir+File.separator+"serverConfigData.xml";
			logDebug(methodName, "Trying to read file: "+fileName);
			XMLServerConfigurationDocument doc = new XMLServerConfigurationDocument(FileTool.sreadFile(fileName));

			//Check and see if document was parsed correctly
			if(doc==null)
				throw new Exception("Error encountered parsing configuration data");

			//Attempt to validate the document (makes sure all required parameters supplied, otherwise validate throws an Exception)
			doc.validate();

			osmsServerConfiguration osc = new osmsServerConfiguration();
			osc.build(doc);
			osc.print();
			return osc;
		}
		else
		{
			throw new Exception("Could not find openIPMP Directory");
		}
	}
	private String getTemplateFromFile(String Path, String FileName) throws Exception
	{
		String methodName = "getTemplateFromFile";
		logDebug(methodName, "Processing template file: "+m_OpenIpmpDir.getAbsolutePath()+File.separator+Path+File.separator+FileName);

		File templateFile = new File(m_OpenIpmpDir,Path+File.separator+FileName);
		if(!templateFile.exists())
			throw new Exception("Could not find Template File: "+m_OpenIpmpDir.getAbsolutePath()+File.separator+Path+File.separator+FileName);

		logDebug(methodName, "Successfully processed template file: "+FileName);
		//logDebug(methodName, "Template file is: "+FileTool.sreadFile(templateFile.getAbsolutePath()));
		return(FileTool.sreadFile(templateFile.getAbsolutePath()));
	}
	private void loadTemplates() throws Exception
	{
		osmsServerConfiguration osc = m_osmsServerConfiguration;
		String templateXmlString = null;

		//Read Templates and set xml on osmsServerConfiguration object
		osc.setOpenIpmpTemplateAuxDataXml(getTemplateFromFile(osc.getTemplateAuxDataFilePath(), osc.getTemplateAuxDataFileName()));
		osc.setOpenIpmpTemplateDoiXml(getTemplateFromFile(osc.getTemplateDoiFilePath(), osc.getTemplateDoiFileName()));
		osc.setOpenIpmpTemplateOdrlXml(getTemplateFromFile(osc.getTemplateLicenseOdrlFilePath(), osc.getTemplateLicenseOdrlFileName()));
		osc.setOpenIpmpTemplateSignatureXml(getTemplateFromFile(osc.getTemplateSignatureFilePath(), osc.getTemplateSignatureFileName()));
		osc.setOpenIpmpTemplateEncryptedKeyXml(getTemplateFromFile(osc.getTemplateEncryptedKeyFilePath(), osc.getTemplateEncryptedKeyFileName()));

		//Validate all templates were loaded
		if(!StringTool.isStringValid(osc.getOpenIpmpTemplateAuxDataXml()))
			throw new Exception("Could not load Aux Data Template File");
		if(!StringTool.isStringValid(osc.getOpenIpmpTemplateDoiXml()))
			throw new Exception("Could not load DOI Template File");
		if(!StringTool.isStringValid(osc.getOpenIpmpTemplateOdrlXml()))
			throw new Exception("Could not load License ODRL Template File");
		if(!StringTool.isStringValid(osc.getOpenIpmpTemplateSignatureXml()))
			throw new Exception("Could not load Signature Template File");
		if(!StringTool.isStringValid(osc.getOpenIpmpTemplateEncryptedKeyXml()))
			throw new Exception("Could not load Encrypted Key Template File");
	}
	public void init(String config)
	{
		String methodName = "init";
		logDebug(methodName,"");

		//Attempt to find and set openIPMP Parent data directory
		if (!checkOpenIpmpParentDirectory())
			try
			{
				setOpenIpmpParentDirectory();
				logDebug(methodName, "Processing of openIPMP Parent directory was successful");
			}
			catch (Exception e)
			{
				logError(methodName,"",e);
			}

		//Attempt to load configuration data from xml configuration file
		try
		{
			m_osmsServerConfiguration = loadConfigurationDataFromFile();
			if(m_osmsServerConfiguration==null)
				throw new Exception("Error encountered parsing xml configuration file into configuration object...configuration object was null");

			logDebug(methodName, "Processing of xml configuration file was successful");
		}
		catch (Exception e)
		{
			logError(methodName,"",e);
		}

		//Attempt to load templates from configuration data and populate template xml on ServerConfiguration object
		try
		{
			logDebug(methodName, "Loading templates...");
			loadTemplates();
			logDebug(methodName, "Loading of templates was successful");
		}
		catch (Exception e)
		{
			logError(methodName,"",e);
		}

		//Attempt to initialize dbPool
		try
		{
			osmsServerConfiguration osc = getOsmsServerConfiguration();
			m_dbPool = new osmsDbPool(osc.getDbDriver(), osc.getDbConnectUrl(), osc.getDbUserName(), osc.getDbPassword(), m_logger);
			if(m_dbPool==null)
				throw new Exception("Error trying to initialize DBPool...DBPool was null");

			logDebug(methodName, "Initialization of DBPool was successful");
		}
		catch (Exception e)
		{
			logError(methodName,"",e);
		}

		m_osmsContentManager=new osmsContentManager();
		m_osmsDatabase=new osmsDatabase();
		m_osmsRightsManager=new osmsRightsManager(m_logger);
		m_osmsLoginManager=new osmsLoginManager();
		m_osmsEncoderManager=new osmsEncoderManager();

		try
		{
			// intialize logger
			OutputStreamWriter os;
			BufferedWriter OutStream;
			FileOutputStream fos;
			osmsServerConfiguration osc = getOsmsServerConfiguration();

		    //Log Debug
			File debugDir = new File(getOpenIpmpParentDirectory(), osc.getLogDebugFilePath());
			if(!debugDir.exists())
		    {
				if(!debugDir.mkdir())
				{
					logError(methodName, "Writing DEBUG Log file to OpenIPMP Parent directory because could not create directory: " + debugDir.getAbsolutePath());
					debugDir = new File(this.getOpenIpmpParentDirectory().getAbsolutePath());
				}
		    }
			File debugLogFile = new File(debugDir, osc.getLogDebugFileName());
			fos = new FileOutputStream(debugLogFile);
			os = new OutputStreamWriter(fos);
			OutStream = new BufferedWriter(os);
			m_logger.addFileDebug(OutStream);

		    //Log Error
			File errorDir = new File(getOpenIpmpParentDirectory(), osc.getLogErrorFilePath());
			if(!errorDir.exists())
		    {
				if(!errorDir.mkdir())
				{
					logError(methodName, "Writing ERROR Log file to OpenIPMP Parent directory because could not create directory: " + errorDir.getAbsolutePath());
					errorDir = new File(this.getOpenIpmpParentDirectory().getAbsolutePath());
				}
		    }
			File errorLogFile = new File(errorDir, osc.getLogErrorFileName());
			fos = new FileOutputStream(errorLogFile);
			os = new OutputStreamWriter(fos);
			OutStream = new BufferedWriter(os);
			m_logger.addFileError(OutStream);

		    //Log Info
			File infoDir = new File(getOpenIpmpParentDirectory(), osc.getLogInfoFilePath());
			if(!infoDir.exists())
		    {
				if(!infoDir.mkdir())
				{
					logError(methodName, "Writing INFO Log file to OpenIPMP Parent directory because could not create directory: " + infoDir.getAbsolutePath());
					infoDir = new File(this.getOpenIpmpParentDirectory().getAbsolutePath());
				}
		    }
			File infoLogFile = new File(infoDir, osc.getLogInfoFileName());
			fos = new FileOutputStream(infoLogFile);
			os = new OutputStreamWriter(fos);
			OutStream = new BufferedWriter(os);
			m_logger.addFileInfo(OutStream);

		    //Log All
			File allDir = new File(getOpenIpmpParentDirectory(), osc.getLogAllFilePath());
			if(!allDir.exists())
		    {
				if(!allDir.mkdir())
				{
					logError(methodName, "Writing ALL Log file to OpenIPMP Parent directory because could not create directory: " + allDir.getAbsolutePath());
					allDir = new File(this.getOpenIpmpParentDirectory().getAbsolutePath());
				}
		    }
			File allLogFile = new File(allDir, osc.getLogAllFileName());
			fos = new FileOutputStream(allLogFile);
			os = new OutputStreamWriter(fos);
			OutStream = new BufferedWriter(os);
			m_logger.addFileDebug(OutStream);
			m_logger.addFileError(OutStream);
			m_logger.addFileInfo(OutStream);
			m_logger.setError(true);

			//Initialize CA
			Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());
			caManager= new CAManagerEjbca(m_logger);
			caManager.Initialize();
			m_ca=new CertificateAuthority(m_logger);
			logDebug(methodName,new File("").getCanonicalPath());
			m_ca.Initialize("lib"+File.separator+"mastersecret.ser",caManager);

		}
		catch(Exception e)
		{
			logError(methodName,"",e);
		}
    }
}


