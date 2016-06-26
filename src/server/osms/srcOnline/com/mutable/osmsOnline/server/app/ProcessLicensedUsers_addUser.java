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

/**
 * <p>Title: </p>
 * <p>Description:  </p>
 * @version 1.0
 */


package com.mutable.osmsOnline.server.app;

import java.sql.Timestamp;
import com.mutable.io.OlLogger;
import com.mutable.osms.server.app.osmsGlobalObjectManager;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.common.io.message.*;

public class ProcessLicensedUsers_addUser
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+" : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PROPERTIES
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	String m_errorMsg;
	public void setErrorMessage(String msg){m_errorMsg=msg;}
	public String getErrorMessage(){return m_errorMsg;}

	String m_userName;
	public void setUserName(String userName){m_userName=userName;}
	public String getUserName(){return m_userName;}

	String m_StartDate;
	public void setStartDate(String StartDate){m_StartDate=StartDate;}
	public String getStartDate(){return m_StartDate;}

	String m_EndDate;
	public void setEndDate(String EndDate){m_EndDate=EndDate;}
	public String getEndDate(){return m_EndDate;}

	String m_ContentId;
	public void setContentId(String ContentId){m_ContentId=ContentId;}
	public String getContentId(){return m_ContentId;}

	String m_PrimaryTitle;
	public void setPrimaryTitle(String PrimaryTitle){m_PrimaryTitle=PrimaryTitle;}
	public String getPrimaryTitle(){return m_PrimaryTitle;}

	String m_DoiIdentifier;
	public void setDoiIdentifier(String DoiIdentifier){m_DoiIdentifier=DoiIdentifier;}
	public String getDoiIdentifier(){return m_DoiIdentifier;}

	private String m_LicenseType=null;
	public String getLicenseType(){return m_LicenseType;}
	public void setLicenseType(String LicenseType){m_LicenseType=LicenseType;}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger m_logger= osmsGlobalObjectManager.getInstance().getLogger();
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	public String process(osmsUsers a_user)
	{

		String methodName="process";
		try
		{
			logDebug(methodName,m_DoiIdentifier+" "+m_userName+" "+m_StartDate+"="+DateTool.convertToDate(m_StartDate)+" "+m_EndDate+" "+m_LicenseType);
			osmsMessageRightsAuthorizationRequest message = new osmsMessageRightsAuthorizationRequest();
			message.setContentId(m_DoiIdentifier);
			message.setUserName(m_userName);
			message.setStartDate(DateTool.convertToDate(m_StartDate));
			if(message.getStartDate()==null) return "StartDate is not in a legal format!";
			message.setEndDate(DateTool.convertToDate(m_EndDate));
			message.setLicenseType(m_LicenseType);
			if(message.getEndDate()==null) return "EndDate is not in a legal format!";

			osmsMessage response = osmsGlobalObjectManager.getInstance().getRightsManager().processRightsAuthorizationRequest(message,a_user);

			String rspName = response.getClass().getName();

			if (rspName.equals("com.mutable.osms.common.io.message.osmsMessageRightsAuthorizationResponse"))
			{
				return null;
			}
			if(rspName.equals("com.mutable.osms.common.io.message.osmsMessageLicenseResponseError"))
			{
				return ((osmsMessageLicenseResponseError)response).getResponseString();
			}
			return "Unknow Error - "+rspName;

		}
		catch (Exception ex)
		{
			logError(methodName,"",ex);
			return "Unknow Error - "+ex.toString();
		}

/*
		logDebug(methodName,"itemId="+getItemId());
		try
		{
			osmsUsers user=osmsGlobalObjectManager.getInstance().getDatabase().getUsersByUserId(new Long(this.getUser()));
			if(user==null)
			{
				return "user "+this.getUser()+" doesnt exist!";
			}

			osmsContent item = osmsGlobalObjectManager.getInstance().getDatabase().getContentByContentId(new Long(this.getItemId()));
//			osmsIpmpResource resource = osmsGlobalObjectManager.getInstance().getDatabase().getIpmpResourceByResourceId(item.getResourceId());
			osmsIpmpAgreement agreement = new osmsIpmpAgreement();
			agreement.setAssignedToUser(user.getUserId());
			agreement.setRegisteredBy(item.getRegisteredBy());
			agreement.setContentId(item.getContentId());
			osmsGlobalObjectManager.getInstance().getDatabase().insertIpmpAgreement(agreement);

		}
		catch (Exception ex)
		{
			return ex.toString();
		}


		return "No Error!";
*/
	}
}

