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

package com.mutable.osms.server.io.xml.test;

import com.mutable.osms.server.bo.osmsOpenIpmpEncoderInfo;
import com.mutable.osms.server.io.xml.XMLEncoderInfo;
import com.mutable.osms.server.io.xml.XMLOpenIpmpEncoderInfo;

import junit.framework.TestCase;

public class XMLOpenIPMPEncoderInfoTest extends TestCase {
	XMLOpenIpmpEncoderInfo xmlInfo;
	osmsOpenIpmpEncoderInfo beanInfo;
	
	protected void setUp(){
		xmlInfo = new XMLOpenIpmpEncoderInfo();

		beanInfo = new osmsOpenIpmpEncoderInfo();
		
		beanInfo.setUsername("davor");
		beanInfo.setPassword("runje");
		beanInfo.setHostInfo("host:1234");
		beanInfo.setRightsInfo("rights:5678");
		
	}

	public void testConstruction(){
		assertEquals("username/password", xmlInfo.getString(XMLEncoderInfo.getUserTag()));
		assertEquals("localhost:8080", xmlInfo.getString(XMLEncoderInfo.getHostInfoTag()));
		assertEquals("localhost:8080", xmlInfo.getString(XMLEncoderInfo.getRightsInfoTag()));

		assertEquals("davor", beanInfo.getUsername());
		assertEquals("runje", beanInfo.getPassword());
		assertEquals("host:1234", beanInfo.getHostInfo());
		assertEquals("rights:5678", beanInfo.getRightsInfo());
	}
	
	public void testConvertToBusinessObject(){
		osmsOpenIpmpEncoderInfo defInfo = xmlInfo.convertToBusinessObject();

		assertEquals("username", defInfo.getUsername());
		assertEquals("password", defInfo.getPassword());
		assertEquals("localhost:8080", defInfo.getHostInfo());
		assertEquals("localhost:8080", defInfo.getRightsInfo());

	}
	
	public void testEncodeBusinessObject(){
		xmlInfo.encodeBusinessObject(beanInfo);
		
		assertTrue(beanInfo.equals(xmlInfo.convertToBusinessObject()));	
	}
	
	public void testEncodeDecode(){
		xmlInfo.encodeBusinessObject(beanInfo);
		String xmlString = xmlInfo.encode();
		XMLOpenIpmpEncoderInfo xmlInfo2 = new XMLOpenIpmpEncoderInfo();
		xmlInfo2.decode(xmlString, XMLEncoderInfo.getRootTag());
		osmsOpenIpmpEncoderInfo beanInfo2 = xmlInfo2.convertToBusinessObject();

		assertTrue(beanInfo2.equals(beanInfo));
	}
}
