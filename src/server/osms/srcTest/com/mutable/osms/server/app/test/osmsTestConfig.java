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

package com.mutable.osms.server.app.test;

import java.io.File;
import java.security.KeyStore;
import java.util.Properties;

import squashxml.xml.XMLDocument;
import squashxml.xml.datatype.DataTypeAttribute;

import com.mutable.io.tools.CryptoTool;
import com.mutable.io.tools.FileTool;
import com.mutable.osms.common.io.message.osmsMessage;
import com.mutable.osms.common.io.message.osmsMessageUserLoginRequest;
import com.mutable.osms.common.io.message.osmsMessageUserLoginResponse;
import com.mutable.osms.server.app.osmsEncoderManager;
import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.app.osmsLoginManager;
import com.mutable.osms.server.bo.osmsUsers;
import com.mutable.osms.server.db.osmsDatabase;

import junit.framework.TestCase;

public class osmsTestConfig extends TestCase {
	private static String xmlConfigFileName = "serverTestConfigData.xml";

	private static String osmsTestConfigTag = "osmsTestConfig";
	private static String usernameTag = "testUser.username";
	private static String passwordTag = "testUser.password";
	private static String badUsernameTag = "testUser.badUsername";
	private static String pkcs12PathTag = "pkcsStorage.path";
	private static String inFileNameTag = "ioFiles.inFile";
	private static String outFileNameTag = "ioFiles.outFile";
	private static String badInFileNameTag = "ioFiles.badInFile";
	private static String badOutFileNameTag = "ioFiles.badOutFile";
	private static String openipmpPathTag = "openipmp.path";
	
	private XMLDocument xmlDoc = null;
	
	private String[] licTypes = null;
	private String badLicType = "BADLICTYPE";

	private osmsGlobalObjectManager global = null;
	
	public osmsTestConfig() throws Exception{
		init(FileTool.sreadFile(xmlConfigFileName));
	}

	public void init(String xmlString) throws Exception {
		// decode input file
		xmlDoc = new XMLDocument();
		assertTrue(xmlDoc.decode(xmlString, osmsTestConfigTag));
		
		// set global object manager
		osmsGlobalObjectManager.setOpenIpmpParentDirectory(new File(getOpenipmpPath()));
		global = osmsGlobalObjectManager.getInstance();
		
		// download user pkcs12 if necessary
		String pkcs12Path = getPkcs12Path();
		String username = getUsername();
		String password = getPassword();

	}
	
	private String getString(String tag){
		return xmlDoc.getString(tag, (DataTypeAttribute[])null);
		// retrieve data
	}

	public String getOpenipmpPath(){
		String ret = getString(openipmpPathTag);
		return ret;
	}
	
	public String getPkcs12Path(){
		return getString(pkcs12PathTag);
	}
	
	public String getUsername(){
		return getString(usernameTag);
	}
	
	public String getPassword(){
		return getString(passwordTag);
	}
	
	public String getBadUsername(){
		return getString(badUsernameTag);
	}
	
	public String getInFileName(){
		return getString(inFileNameTag);
	}

	public String getOutFileName(){
		return getString(outFileNameTag);
	}
	
	public String getBadInFileName(){
		return getString(badInFileNameTag);
	}

	public String getBadOutFileName(){
		return getString(badOutFileNameTag);
	}

	public String[] getLicTypes(){
		if (licTypes == null){
			licTypes = new String[2];
			licTypes[0] = "ODRL";
			licTypes[1] = "MPEGREL";
		}
		return (String[])licTypes.clone();
	}

	public String getBadLicType(){
		return badLicType;
	}
	
	public void testGlobalOsmsParameters() {
		osmsEncoderManager encoder;
		osmsDatabase db;
		osmsLoginManager loginMgm;

		assertNotNull(global);

		encoder = global.getEncoderManager();
		db = global.getDatabase();
		loginMgm = global.getLoginManager();

		assertNotNull(encoder);
		assertNotNull(db);
		assertNotNull(loginMgm);
	}

	public void testIOTestFiles(){
		String inFileName = getInFileName();
		String outFileName = getOutFileName();
		
		File inFile = new File(inFileName);
		File outFile = new File(getOutFileName());

		assertTrue("File " + inFileName + " does not exists.", inFile.exists());
		assertTrue(inFileName + " is a directory.", inFile.isFile());
		assertFalse(outFileName + " is a directory.", outFile.isDirectory());
	}
	
	public void testBadIOTestFiles(){
		String badInFileName = getBadInFileName();
		String badOutFileName = getBadOutFileName();

		File badInFile = new File(badInFileName);
		File badOutFile = new File(badOutFileName);

		assertFalse("File " + badInFileName + " exists.", badInFile.exists());
		assertTrue(badOutFileName + " is not a directory.", badOutFile.isDirectory());
	}
	
	public void testPkcsDirectory(){
		String pkcs12Path = getPkcs12Path();
		File pkcs12Dir = new File(pkcs12Path);
		
		assertTrue("PKCS directory " + pkcs12Path + " does not exist.", pkcs12Dir.exists());
		assertTrue("PKCS directory " + pkcs12Path + " is not a directory.", pkcs12Dir.isDirectory());

	}
	
	public void testTestUser(){
		String username = getUsername();
		String password = getPassword();

		osmsDatabase db = global.getDatabase();

		osmsUsers testUser = null;
		try{
			testUser = db.getUsersByUserName(username);
		}catch (Exception e){
			fail("Unexpected exception thrown: " + e.getMessage());			
		}
		
		if (testUser == null)
			fail("User with name " + username + " does not exist.");

		// Log in user
		osmsMessageUserLoginRequest req = new osmsMessageUserLoginRequest();
		req.setUserName(username);
		req.setPassword(password);

		osmsLoginManager loginMgm = global.getLoginManager();
		osmsMessage res = loginMgm.processLoginRequest(req, testUser);

		assertTrue("Login failed.", res.getClass() == osmsMessageUserLoginResponse.class);
	}
	
	public void testUserPkcsStore(){
		String pkcs12Path = getPkcs12Path();
		String username = getUsername();
		String password = getPassword();
		
		String pkcs12FileName = pkcs12Path + "/" + username + ".p12";
		File pkcs12File = new File(pkcs12FileName);

		assertTrue("PKCS file " + pkcs12FileName + " does not exist.", pkcs12File.exists());
		
		byte[] keyStoreArray = null;
		try {
			keyStoreArray = FileTool.readFile(pkcs12FileName);
			assertNotNull("Reading of PKCS file " + pkcs12FileName + " failed.", keyStoreArray);
		} catch (Exception e) {
			fail("Reading of PKCS file " + pkcs12FileName + " failed with exception: " + e);
		}
		
		try {
			KeyStore keyStore = CryptoTool.decodeKeyStore(keyStoreArray, "PKCS12", password);
			assertNotNull("Decoding of PKCS 12 key store failed.", keyStore);
		} catch (Exception e) {
			fail("Decoding of PKCS 12 key store failed with exception: " + e);
		}
	}

	public void testBadTestUser(){
		String badUsername = getBadUsername();

		osmsDatabase db = global.getDatabase();

		try{
			assertNull("User with name " + badUsername + " is exists!", db.getUsersByUserName(badUsername));
		}catch (Exception e){
			fail("Unexpected exception thrown: " + e.getMessage());			
		}
	}
	
	public void testBadLicType(){
		String[] tmpLicTypes = getLicTypes();
		for (int i=0; i<licTypes.length; i++){
			assertFalse("License type " + badLicType + " in " + tmpLicTypes, badLicType.equals(tmpLicTypes[i]));
		}
	}

	public void testUsers() throws Exception {
		osmsDatabase db = global.getDatabase();

		osmsUsers[] users = db.getUsers();

		assertTrue("There must be some users in the database.", users.length > 0);
	}

	public void testOpenipmpPath() throws Exception {
		// TODO
		File openipmp = new File(getOpenipmpPath());
	}

}
