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

package com.mutable.osms.server.io.xml;

import com.mutable.osms.server.bo.osmsEncoderInfo;
import com.mutable.osms.server.bo.osmsOpenIpmpEncoderInfo;

import squashxml.xml.XMLDocument;

// TODO: Support for OMA encoding.

public abstract class XMLEncoderInfo extends XMLDocument {
	static private String rootTag = "EncoderInfo";
	static private String userTag = "UserInfo";
	static private String hostInfoTag = "OpenIPMPHostInfo";
	static private String rightsInfoTag = "RightsHostInfo";
	
	static public String getRootTag(){ return rootTag; }
	static public String getUserTag(){ return userTag; }
	static public String getHostInfoTag(){ return hostInfoTag; }
	static public String getRightsInfoTag(){ return rightsInfoTag; }

	public void encodeBusinessObject(osmsEncoderInfo encoderInfo){
		setString(userTag, encoderInfo.getUsername() + "/" + encoderInfo.getPassword());
		setString(hostInfoTag, encoderInfo.getHostInfo());
		setString(rightsInfoTag, encoderInfo.getRightsInfo());
	}

	public void convertToBusinessObject(osmsEncoderInfo info){
		String user = getString(userTag);
		int pos = user.indexOf('/');
		info.setUsername(user.substring(0, pos));
		info.setPassword(user.substring(pos+1, user.length()));

		info.setHostInfo(getString(hostInfoTag));
		info.setRightsInfo(getString(rightsInfoTag));
	}
}
