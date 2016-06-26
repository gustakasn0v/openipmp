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

package com.mutable.ws;

import com.mutable.io.tools.CryptoTool;
import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.app.osmsLoginManager;
import com.mutable.osms.server.bo.osmsUsers;

public class UserLoginTest {
	public String login(String userName, String password){
		try{
			osmsGlobalObjectManager instance = osmsGlobalObjectManager.getInstance();
			osmsLoginManager loginManager = instance.getLoginManager();
			osmsUsers user = loginManager.getUser(userName);
			
			String hashedPassword = CryptoTool.base64Encode( CryptoTool.generateMD5Hash(password));
			if (user.isLoggedIn()){
				return "User is already logged in.";
			}
			if (user.getPassword().compareTo(hashedPassword)==0){
				//Try to generate a login record for this user
				user.login();
				user.setPassword(password);
				return "Successful login into OSMS.";
			}else{
				return "Login failed: Wrong password!";
			}
		}catch(Exception e){
			return "Login failed: Wrong username.";
		}
	}
}
