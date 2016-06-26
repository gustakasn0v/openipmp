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

package com.mutable.osms.server.ws.message;

public class OsmsRegisterUserResponse implements java.io.Serializable {
	private String userName = null;
	private byte[] userSecurityStore = null;
	
	public OsmsRegisterUserResponse(String name, byte[] userSecurityStore) {
		userName = name;
		this.userSecurityStore = new byte[userSecurityStore.length];
		for(int i=0; i<userSecurityStore.length; i++) {
			this.userSecurityStore[i] = userSecurityStore[i];
		}		
	}

	public OsmsRegisterUserResponse() {
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public byte[] getUserSecurityStore() {
		return userSecurityStore;
	}

	public void setUserSecurityStore(byte[] userSecurityStore) {
		this.userSecurityStore = new byte[userSecurityStore.length];
		for(int i=0; i<userSecurityStore.length; i++) {
			this.userSecurityStore[i] = userSecurityStore[i];
		}		
	}
}
