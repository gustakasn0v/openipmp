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

package com.mutable.osms.server.app.service.test;



import java.rmi.RemoteException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.mutable.osms.server.app.service.OpenIPMPWS;
import com.mutable.osms.server.app.service.OpenIPMPWSProxy;

import junit.framework.TestCase;

public class OpenIPMPWSTest extends TestCase {
	private OpenIPMPWS ws;
	private String username;
	private String password;
	private String badUsername;
	private String inFileName;
	private String outFileName;
	private String badInFileName;
	private String badOutFileName;
	private String[] userNames;
	private Date begin;
	private Date end;
	private DateFormat dateFormat;

	public void setUp(){
		ws = new OpenIPMPWSProxy();
		
		username = OpenIPMPWSTestConfig.getUsername();
		password = OpenIPMPWSTestConfig.getPassword();
		badUsername = OpenIPMPWSTestConfig.getBadUsername();
		inFileName = OpenIPMPWSTestConfig.getInFileName();
		outFileName = OpenIPMPWSTestConfig.getOutFileName();
		badInFileName = OpenIPMPWSTestConfig.getBadInFileName();
		badOutFileName = OpenIPMPWSTestConfig.getBadOutFileName();
		userNames = OpenIPMPWSTestConfig.getUserNames();

		begin = new Date();
		end = new Date();
		end.setYear(end.getYear()+1);
		dateFormat = new SimpleDateFormat("yyyy-MM-dd");
	}
	
	public void testGetEndpoint(){
		assertNotNull(((OpenIPMPWSProxy)ws).getEndpoint());
	}
	
	public void testLogin() throws Exception {
		assertEquals(0, ws.login(username, password));
	}

	public void testLoginWithBadPassword() throws Exception {
		assertEquals(1, ws.login(username, password + "bad"));
	}
	
	public void testLoginWithNullUsername() throws Exception {
		assertEquals(1, ws.login(null, password));
	}

	public void testLoginWithNullPassword() throws Exception {
		assertEquals(1, ws.login(username, null));
	}
	
	public void testLoginWithBadUsername() throws Exception {
		assertEquals(1, ws.login(badUsername, password));
	}

	public void testPackageSecureContentWithParams(){		
		try {
			assertEquals(0, ws.packageSecureContentWithParams(username, password, inFileName, outFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}

	public void testPackageSecureContentWithParamsWithBadUsername(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(badUsername, password, inFileName, outFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}

	public void testPackageSecureContentWithParamsWithBadPassword(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(username, password + "bad", inFileName, outFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}
	
	public void testPackageSecureContentWithParamsWithBadInFileName(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(username, password, badInFileName, outFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}
	
	public void testPackageSecureContentWithParamsWithBadOutFileName(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(username, password, inFileName, badOutFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}

	public void testPackageSecureContentWithParamsWithNullUsername(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(null, password, inFileName, outFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}

	public void testPackageSecureContentWithParamsWithNullPassword(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(username, null, inFileName, outFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}
	
	public void testPackageSecureContentWithParamsWithNullInFileName(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(username, password, null, outFileName, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}
	
	public void testPackageSecureContentWithParamsWithNullOutFileName(){
		try {
			assertEquals(1, ws.packageSecureContentWithParams(username, password, inFileName, null, null, null, null, dateFormat.format(begin), dateFormat.format(end), 0, 0, userNames));
		} catch (RemoteException e) {
			fail("Unexpected exception: " + e.getMessage());
		}
	}
}
