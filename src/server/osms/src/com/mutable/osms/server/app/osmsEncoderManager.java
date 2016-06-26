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

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.mutable.io.OlLogger;
import com.mutable.io.tools.CryptoTool;
import com.mutable.io.tools.ExternalCommand;
import com.mutable.osms.server.bo.osmsOpenIpmpEncoderInfo;
import com.mutable.osms.server.bo.osmsUsers;
import com.mutable.osms.server.db.osmsDatabase;
import com.mutable.osms.server.io.xml.XMLEncoderInfo;
import com.mutable.osms.server.io.xml.XMLOpenIpmpEncoderInfo;

/**
* osmsEncoderManager is the openIPMP class that protects content by
* calling the external mp4creator application. 
*/
public class osmsEncoderManager {
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
	// CONSTRUCTORS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
    * Class constructor which creates a new osmsContentManager object.  The constructor sets the objects private members, log and configuration.
    */
    public osmsEncoderManager()
	{
    	String methodName = "osmsEncoderManager()";
    	
		log=osmsGlobalObjectManager.getInstance().getLogger();
		osmsServerConfiguration m_Config = osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration();
		
		m_RightsServerPort = m_Config.getRightsHostPort();
		m_RightsServerUrl = m_Config.getRightsHostUrl();
		m_ServerPort = m_Config.getServerPort(); 
		
		m_EncoderPath = m_Config.getEncoderPath();
		File encoderPath = new File(m_EncoderPath);
		
		if (!encoderPath.exists()){
			logError(methodName, "Encoder path " + m_EncoderPath + " does not exist.");
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	/**
    * The OlLogger object used for logging purposes.
    */
	private OlLogger log = null;

	/**
	 * Server port.
	 */
	private String m_ServerPort = null;
	
	/**
	 * Rights server IP.
	 */
	private String m_RightsServerPort = null;
	
	/**
	 * Rights server URL.
	 */
	private String m_RightsServerUrl = null;
	
	/**
	 * Encoder path.
	 */
	private String m_EncoderPath = null;
	
	private static long defaultTimeout = 50;
	public static long getDefaultTimeout(){
		return defaultTimeout;
	}
	
	private static SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
	
	/**
	 * Protects MP4 file and issues licenses for a list of users.
	 * @param username
	 * @param password
	 * @param inFile
	 * @param outFile
	 * @param beginDate
	 * @param endDate
	 * @param users
	 * @throws IOException 
	 * @throws InterruptedException
	 */
	public void encode(String username, String password, String inFile, String outFile, String licType, Date beginDate, Date endDate, String[] users) throws Exception {
		String methodName = "encode";
		logDebug(methodName, "");
		File xmlFile = null;
		try{
			checkParameters(username, password, licType, inFile, outFile);
			
			// Create business object with encoder info for OpenIPMP signaling  
			osmsOpenIpmpEncoderInfo info = new osmsOpenIpmpEncoderInfo();
			info.setUsername(username);
			info.setPassword(password);
			info.setHostInfo("localhost:" + m_ServerPort);
			info.setRightsInfo(m_RightsServerUrl + ":" + m_RightsServerPort);
			logDebug(methodName, "Business object with encoder info created.");

			// Create XML document
			XMLEncoderInfo infoDoc = new XMLOpenIpmpEncoderInfo();
			infoDoc.encodeBusinessObject(info);
			logDebug(methodName, "Encoder info XML created.");
			
			// Create tmp file and write XML doc
			xmlFile = File.createTempFile("EncoderInfo", ".xml");
			FileOutputStream xmlOut = new FileOutputStream(xmlFile);
			String xmlString = infoDoc.encode(); 
			xmlOut.write(xmlString.getBytes());
			xmlOut.close();
			logDebug(methodName, "Encoder info XML written to temporary file " + xmlFile.getAbsolutePath());
			
			// Create external command string
			ExternalCommand cmd = new ExternalCommand(command(username, password, inFile, outFile, xmlFile.getAbsolutePath(), licType, beginDate, endDate, users));
			cmd.setTimeout(getDefaultTimeout());
			logDebug(methodName, "External encoder command created.");

			// Execute command
			int err = cmd.exec();
			if (err != 0){
				String msg = "External encoder command failed with error code " + err + ".";
				logError(methodName, msg);
				logError(methodName, "Stderr: " + cmd.getStdErr());
				throw new Exception(msg);
			}
			logDebug(methodName, "External encoder returned successfully.");
		}catch(Exception e){
			logError(methodName, "Encoding failed.");
			logError(methodName, "Error message: " + e.getMessage());
			throw e;
		}finally{
			if (xmlFile != null) xmlFile.delete();
			logDebug(methodName, "Deleting temporary file " + xmlFile.getAbsolutePath());			
		}
	}

	/**
	 * Protects MP4 file.
	 * @param username
	 * @param password
	 * @param inFile
	 * @param outFile
	 * @throws IOException 
	 * @throws InterruptedException
	 */
	public void encode(String username, String password, String inFile, String outFile) throws Exception {
		encode(username, password, inFile, outFile, "MPEGREL", null, null, null);
	}

	protected String command(String username, String password, String inFile, String outFile, String xmlFile, String licType, Date beginDate, Date endDate, String[] users) throws IOException {
		String cmd = m_EncoderPath +  " -E -U=" + xmlFile;
		
		if (users != null){
			for (int i=0; i<users.length; i++){
				cmd += " -X=LicenseGrant/" + users[i] + "/" + dateFormat.format(beginDate) + "/" + dateFormat.format(endDate) + "/" + licType; 
			}
		}

		return cmd
		     + " -Z=openipmp/bfs"
		     + " " + inFile
		     + " " + outFile;
	}
	
	protected void checkParameters(String username, String password, String licType, String inFile, String outFile) throws Exception{
		checkUser(username, password);
		checkLicType(licType);
		checkInFile(inFile);
		checkOutFile(outFile);
	}
	
	protected void checkUser(String username, String password) throws Exception{
		String methodName = "command";

		osmsGlobalObjectManager global = osmsGlobalObjectManager.getInstance();
		osmsDatabase db = global.getDatabase();

		osmsUsers user = db.getUsersByUserName(username);
		if (user == null){
			String msg = "User " + username + "not found in the database.";
			logError(methodName, msg);
			throw new Exception(msg);
		}

		String hashedPassword = hashedPassword = CryptoTool.base64Encode(CryptoTool.generateMD5Hash(password));

		if (user.getPassword().compareTo(hashedPassword) != 0){
			String msg = "Bad password.";
			logError(methodName, msg);
			throw new Exception(msg);
		}
	}
	
	public void checkLicType(String licType) throws Exception {
		if (!osmsRightsManager.getLicTypes().contains(licType)) {
			logError("checkLicType", "Bad license type: " + licType);
			throw new Exception();		
		}
	}
	
	public void checkOutFile(String outFileName) throws Exception {
		String methodName = "checkOutFile";
		File outFile = new File(outFileName);

		if (outFile.isDirectory()){
			String msg = "Output file " + outFile.getAbsolutePath() + " is a directory.";
			logError(methodName, msg);
			throw new IOException("msg");
		}
	}
	
	public void checkInFile(String inFileName) throws Exception {
		String methodName = "checkInFile";

		File inFile = new File(inFileName);

		if (!inFile.exists()){
			String msg = "Input file " + inFile.getAbsolutePath() + " does not exist.";
			logError(methodName, msg);
			throw new IOException("msg");
		}

		if (inFile.isDirectory()){
			String msg = "Input file " + inFile.getAbsolutePath() + " is a directory.";
			logError(methodName, msg);
			throw new IOException("msg");
		}
	}
}

