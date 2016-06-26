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

package com.mutable.osms.server.bo;

import java.io.Serializable;

public abstract class osmsEncoderInfo implements Serializable
{
	private String username = null;
	public String getUsername() {
		return username;
	}
	public void setUsername(String username){
		this.username = username;
	}
	
	private String password = null;
	public String getPassword() {
		return password;
	}
	public void setPassword(String password){
		this.password = password;
	}

	private String hostInfo = null;
	public String getHostInfo() {
		return hostInfo;
	}
	public void setHostInfo(String hostInfo){
		this.hostInfo = hostInfo;
	}

	private String rightsInfo = null;
	public String getRightsInfo() {
		return rightsInfo;
	}
	public void setRightsInfo(String rightsInfo){
		this.rightsInfo = rightsInfo;
	}

	public boolean equals(Object arg){
		try{
			osmsEncoderInfo rhs = (osmsEncoderInfo)arg;
			return username.equals(rhs.getUsername()) && 
		       password.equals(rhs.getPassword()) &&
		       hostInfo.equals(rhs.getHostInfo()) &&
		       rightsInfo.equals(rhs.getRightsInfo());			
		}catch(Exception e){
			return false;
		}
	}
}
