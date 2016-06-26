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
 * <p>Title: osmsMessageRightsAuthorizationArrayRequest</p>
 * <p>Description: </p>
 * @version 1.0
 */

//import java.sql.Timestamp;
import java.util.Date;
public class osmsMessageRightsAuthorizationArrayRequest extends osmsMessage
{
	//bean properties

	private String m_ContentId=null;
	public String getContentId(){return m_ContentId;}
	public void setContentId(String ContentId){m_ContentId=ContentId;}

	// these properties are inteneded for processing inside the server
	private String[] m_UserNames=null;
	public String[] getUserNames(){return m_UserNames;}
	public void setUserNames(String[] UserNames){m_UserNames=UserNames;}

	// these properties are inteneded for transport
	//   (the current squashxml XML-RPC transport protocol does not have array capablities,
	//    and so therefore these functions are intended to provide transformation between
	//    a comma or whitespace delimited string)
//	private String m_UserNameDelimString=null;
//	public String getUserNameDelimString(){return m_UserNameDelimString;}
//	public void setUserNameDelimString(String UserNameDelimString){m_UserNameDelimString=UserNameDelimString;}
	
	public Date m_startDate=null;
	public Date getStartDate(){return m_startDate;}
	public void setStartDate(Date date){m_startDate=date;}

	public Date m_endDate=null;
	public Date getEndDate(){return m_endDate;}
	public void setEndDate(Date date){m_endDate=date;}

	private String m_LicenseType=null;
	public String getLicenseType(){return m_LicenseType;}
	public void setLicenseType(String LicenseType){m_LicenseType=LicenseType;}
/*
	private String m_ContentId=null;
	public String getContentId(){return m_ContentId;}
	public void setContentId(String ContentId){m_ContentId=ContentId;}

	private String m_AgentName=null;
	public String getAgentName(){return m_AgentName;}
	public void setAgentName(String AgentName){m_AgentName=AgentName;}

	private String m_AgentPassword=null;
	public String getAgentPassword(){return m_AgentPassword;}
	public void setAgentPassword(String AgentPassword){m_AgentPassword=AgentPassword;}

	private String m_UserName=null;
	public String getUserName(){return m_UserName;}
	public void setUserName(String UserName){m_UserName=UserName;}

	private String m_Action=null;
	public String getAction(){return m_Action;}
	public void setAction(String Action){m_Action=Action;}

	private String m_RightsInfo=null;
	public String getRightsInfo(){return m_RightsInfo;}
	public void setRightsInfo(String RightsInfo){m_RightsInfo=RightsInfo;}
*/
	//constructs
	public osmsMessageRightsAuthorizationArrayRequest()
	{
		super(osmsMessage.osmsMESSAGE_RIGHTS_AUTHORIZATION_ARRAY_REQUEST);
	}
}
