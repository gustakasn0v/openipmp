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

public class OpenIPMPWSTestConfig {
	private static String username = "testuser";
	private static String password = "openipmp";
	private static String badUsername = "badusername";
	private static String inFileName = "C:\\tmp\\test30.mp4";
	private static String outFileName = "C:\\tmp\\enc-test30.mp4";
	private static String badInFileName = "C:\\tmp\\test30-376533732457324572.mp4";
	private static String badOutFileName = "C:\\tmp\\";
	private static String[] userNames = null;

	public static String getUsername(){
		return username;
	}
	
	public static String getPassword(){
		return password;
	}
	
	public static String getBadUsername(){
		return badUsername;
	}
	
	public static String getInFileName(){
		return inFileName;
	}

	public static String getOutFileName(){
		return outFileName;
	}
	
	public static String getBadInFileName(){
		return badInFileName;
	}

	public static String getBadOutFileName(){
		return badOutFileName;
	}
	
	public static String[] getUserNames(){
		if (userNames == null){
			userNames = new String[2];
			userNames[0] = "davor";
			userNames[1] = "davor2";
		}
		return (String[])userNames.clone();
	}
}
