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


package com.mutable.osms.common.io.message;

/**
 * <p>Title: osmsMessageLicenseRequest</p>
 * <p>Description: </p>
 * @version 1.0
 */



public class osmsMessageLicenseRequest extends osmsMessage
{

	//bean properties
	private String m_ContentId=null;
	public String getContentId(){return m_ContentId;}
	public void setContentId(String ContentId){m_ContentId=ContentId;}

	private String m_RightsInfo=null;
	public String getRightsInfo(){return m_RightsInfo;}
	public void setRightsInfo(String RightsInfo){m_RightsInfo=RightsInfo;}


	//constructs
	public osmsMessageLicenseRequest()
	{
		super(osmsMessage.osmsMESSAGE_LICENSE_REQUEST);
	}
}