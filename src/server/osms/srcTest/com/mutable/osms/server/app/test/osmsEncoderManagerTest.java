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
import java.util.Date;

import net.mutable.collections.Set;
import net.mutable.expressions.ComprehensionExp;
import net.mutable.expressions.ConstExp;
import net.mutable.expressions.Expression;
import net.mutable.expressions.Variable;
import net.mutable.predicates.ForAllPredicate;
import net.mutable.predicates.SubsetEqPredicate;


import com.mutable.osms.server.app.osmsEncoderManager;
import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.bo.osmsContent;
import com.mutable.osms.server.bo.osmsUsers;
import com.mutable.osms.server.db.osmsDatabase;

import junit.framework.Assert;
import junit.framework.TestCase;

/**
 * Test for encoderManager.
 * 
 * @warning Server must be running in JBoss in order for this test to work.
 *
 */
public class osmsEncoderManagerTest extends TestCase {
	private osmsUsers[] users = null;
	private String[] userNames ;
	private osmsGlobalObjectManager global;
	private osmsEncoderManager encoder;
	private osmsDatabase db;
	private String username;
	private String badUsername;
	private String password;
	private String inFileName;
	private String outFileName;
	private String badInFileName;
	private String badOutFileName;
	private String[] licTypes; 
	private String badLicType; 
	private Date beginDate;
	private Date endDate;

	public void setUp() throws Exception {
		osmsTestConfig config = new osmsTestConfig();

		osmsGlobalObjectManager.setOpenIpmpParentDirectory(new File(config.getOpenipmpPath()));
		global = osmsGlobalObjectManager.getInstance();
		encoder = global.getEncoderManager();
		db = global.getDatabase();
		
		username = config.getUsername();
		password = config.getPassword();
		badUsername = config.getBadUsername();
		inFileName = config.getInFileName();
		outFileName = config.getOutFileName();
		badInFileName = config.getBadInFileName();
		badOutFileName = config.getBadOutFileName();
		licTypes = config.getLicTypes();
		badLicType = config.getBadLicType();

		beginDate = new Date();
		endDate = (Date)beginDate.clone();
		endDate.setYear(endDate.getYear() + 1);

		users = db.getUsers();
		userNames = new String[users.length];

		for (int i=0; i<users.length; i++){
			userNames[i] = users[i].getUserName(); 
		}

	}
	
	public void testEncoding(){
		try{
			encoder.encode(username, password, inFileName, outFileName);
			File outFile = new File(outFileName);
			assertTrue(outFile.exists());
			assertTrue(outFile.isFile());
		}catch (Exception e){
			fail("Encoding failed with exception: " + e.getLocalizedMessage());
		}
	}
	
	public void testEncodingAndAuthentication() throws Exception{
		for (int i=0; i<licTypes.length; i++){
			testEncodingAndAuthentication(licTypes[i]);
		}
	}

	public void testEncodingAndAuthentication(String licType) throws Exception{
		Set oldContent = null;
		try {
			osmsContent[] con = db.getContent();
			if (con == null)
				oldContent = new Set();
			else
				oldContent = new Set(con);
		}catch (Exception e){
			Assert.fail("Getting content list from database failed with exception: " + e.getLocalizedMessage());
		}

		try {
			encoder.encode(username, password, inFileName, outFileName, licType, beginDate, endDate, userNames);
			File outFile = new File(outFileName);
			assertTrue(outFile.exists());
			assertTrue(outFile.isFile());
		}catch (Exception e){
			Assert.fail("Encoding and authorization for license type " + licType + " failed with exception: " + e.getLocalizedMessage());
		}

		Set newContent = null; 
		try {
			osmsContent[] con = db.getContent();
			if (con == null)
				newContent = new Set();
			else
				newContent = new Set(db.getContent());
		}catch (Exception e){
			Assert.fail("Getting content list from database failed with exception: " + e.getLocalizedMessage());
		}

		Variable x = new Variable("x");
		Expression oldContentE = new ConstExp(oldContent, "oldContent");
		Expression contentIdE = new ContentIdExp(x);
		Expression newContentE = new ConstExp(newContent, "newContent");
		
		// {x.contentId | x in oldContent}
		Expression oldContentIdsE = new ComprehensionExp(oldContentE, x, null, contentIdE);
		// {x.contentId | x in newContent}
		Expression newContentIdsE = new ComprehensionExp(newContentE, x, null, contentIdE);
		
		System.out.println("Old content IDs = " + oldContentIdsE + " = " + oldContentIdsE.eval());
		System.out.println("New content IDs = " + newContentIdsE + " = " + newContentIdsE.eval());
		
		Set oldContentIds = (Set)oldContentIdsE.eval();
		Set newContentIds = (Set)newContentIdsE.eval();
		
		assertTrue("No new content found when encoding and authorizing for license type " + licType + ".", oldContentIds.subset(newContentIds));

		Set freshContentIds = newContentIds.difference(oldContentIds);
		System.out.println("Fresh content IDs = " + freshContentIds);
		
		Set usersSet = new Set(users);
		
		Variable u = new Variable("u");
		
		ComprehensionExp userAgreementsE = new ComprehensionExp(new AgreementsByUserExp(u), x, new ContentIdExp(x)); 
		
		// forall u in users holds freshContentIds <= {x.contentId | x in u.agreements}
		ForAllPredicate forAllP = new ForAllPredicate(u, new ConstExp(usersSet, "users"), new SubsetEqPredicate(new ConstExp(freshContentIds, "freshContentIds"), userAgreementsE));
		
		System.out.println("Condition: " + forAllP);
		
		assertTrue(forAllP.eval());
	}

	public void testEncodingWithBadUsername(){
		try{
			encoder.encode(badUsername, password, inFileName, outFileName);
			fail("Encoding with a bad username did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithEmptyUsername(){
		try{
			encoder.encode("", password, inFileName, outFileName);
			fail("Encoding with empty username did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithNullUsername(){
		try{
			encoder.encode(null, password, inFileName, outFileName);
			fail("Encoding with null username did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithBadPassword(){
		try{
			encoder.encode(username, password + "wrong", inFileName, outFileName);
			fail("Encoding with a bad password did not fail.");
		}catch (Exception e){
		}
	}

	public void testEncodingWithEmptyPassword(){
		try{
			encoder.encode(username, "", inFileName, outFileName);
			fail("Encoding with empty password did not fail.");
		}catch (Exception e){
		}
	}

	public void testEncodingWithNullPassword(){
		try{
			encoder.encode(username, null, inFileName, outFileName);
			fail("Encoding with null password did not fail.");
		}catch (Exception e){
		}
	}

	public void testEncodingWithBadInputFile(){
		try{
			encoder.encode(username, password, badInFileName, outFileName);
			fail("Encoding with a bad input file did not fail.");
		}catch (Exception e){
		}
	}

	public void testEncodingWithEmptyInputFile(){
		try{
			encoder.encode(username, password, "", outFileName);
			fail("Encoding with empty input file did not fail.");
		}catch (Exception e){
		}
	}

	public void testEncodingWithNullInputFile(){
		try{
			encoder.encode(username, password, null, outFileName);
			fail("Encoding with null input file did not fail.");
		}catch (Exception e){
		}
	}

	public void testEncodingWithBadOutputFile(){
		try{
			encoder.encode(username, password, inFileName, badOutFileName);
			fail("Encoding with a bad output file did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithEmptyOutputFile(){
		try{
			encoder.encode(username, password, inFileName, "");
			fail("Encoding with empty output file did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithNullOutputFile(){
		try{
			encoder.encode(username, password, inFileName, null);
			fail("Encoding with null output file did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithEmptyLicenseType(){
		try{
			encoder.encode(username, password, inFileName, outFileName, "", beginDate, endDate, userNames);
			fail("Encoding with empty license type did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithBadLicenseType(){
		try{
			encoder.encode(username, password, inFileName, outFileName, badLicType, beginDate, endDate, userNames);
			fail("Encoding with a bad license type did not fail.");
		}catch (Exception e){
		}
	}
	
	public void testEncodingWithNullLicenseType(){
		try{
			encoder.encode(username, password, inFileName, outFileName, null, beginDate, endDate, userNames);
			fail("Encoding with a bad license type did not fail.");
		}catch (Exception e){
		}
	}
}
