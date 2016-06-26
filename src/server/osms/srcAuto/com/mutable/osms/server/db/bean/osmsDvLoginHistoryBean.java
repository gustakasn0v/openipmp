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
  * <p>Description: </p>
  * @version 1.0
  */
package com.mutable.osms.server.db.bean;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;

import java.io.Serializable;
import java.util.Date;

public class  osmsDvLoginHistoryBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int LOGIN_ID
	private Integer m_LoginId;
	public Integer getLoginId ()
	{return m_LoginId;}
	public void setLoginId (Integer pLoginId)
	{m_LoginId = pLoginId;}

	//int USER_ID
	private Integer m_UserId;
	public Integer getUserId ()
	{return m_UserId;}
	public void setUserId (Integer pUserId)
	{m_UserId = pUserId;}

	//varchar IP_ADDRESS
	private String m_IpAddress;
	public String getIpAddress ()
	{return m_IpAddress;}
	public void setIpAddress (String pIpAddress)
	{m_IpAddress = pIpAddress;}

	//datetime LOGIN_TIME
	private Timestamp m_LoginTime;
	public Timestamp getLoginTime ()
	{return m_LoginTime;}
	public void setLoginTime (Timestamp pLoginTime)
	{m_LoginTime = pLoginTime;}

	//datetime LOGOFF_TIME
	private Timestamp m_LogoffTime;
	public Timestamp getLogoffTime ()
	{return m_LogoffTime;}
	public void setLogoffTime (Timestamp pLogoffTime)
	{m_LogoffTime = pLogoffTime;}

	//datetime CLIENT_LOGIN_TIME
	private Timestamp m_ClientLoginTime;
	public Timestamp getClientLoginTime ()
	{return m_ClientLoginTime;}
	public void setClientLoginTime (Timestamp pClientLoginTime)
	{m_ClientLoginTime = pClientLoginTime;}

	//datetime CLIENT_LOGOFF_TIME
	private Timestamp m_ClientLogoffTime;
	public Timestamp getClientLogoffTime ()
	{return m_ClientLogoffTime;}
	public void setClientLogoffTime (Timestamp pClientLogoffTime)
	{m_ClientLogoffTime = pClientLogoffTime;}

	//char MAINTENANCE_FLAG
	private String m_MaintenanceFlag;
	public String getMaintenanceFlag ()
	{return m_MaintenanceFlag;}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_MaintenanceFlag = pMaintenanceFlag;}

	//varchar LAST_UPDATED_BY
	private String m_LastUpdatedBy;
	public String getLastUpdatedBy ()
	{return m_LastUpdatedBy;}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_LastUpdatedBy = pLastUpdatedBy;}

	//datetime LAST_UPDATED_ON
	private Timestamp m_LastUpdatedOn;
	public Timestamp getLastUpdatedOn ()
	{return m_LastUpdatedOn;}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_LastUpdatedOn = pLastUpdatedOn;}

	//varchar CREATED_BY
	private String m_CreatedBy;
	public String getCreatedBy ()
	{return m_CreatedBy;}
	public void setCreatedBy (String pCreatedBy)
	{m_CreatedBy = pCreatedBy;}

	//datetime CREATED_ON
	private Timestamp m_CreatedOn;
	public Timestamp getCreatedOn ()
	{return m_CreatedOn;}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_CreatedOn = pCreatedOn;}


	//-------------------------------------
	// copyPropertiesTo method
	//-------------------------------------
	public void copyPropertiesTo (osmsDvLoginHistoryBean target)
	{

		target.setLoginId (getLoginId());
		target.setUserId (getUserId());
		target.setIpAddress (getIpAddress());
		target.setLoginTime (getLoginTime());
		target.setLogoffTime (getLogoffTime());
		target.setClientLoginTime (getClientLoginTime());
		target.setClientLogoffTime (getClientLogoffTime());
		target.setMaintenanceFlag (getMaintenanceFlag());
		target.setLastUpdatedBy (getLastUpdatedBy());
		target.setLastUpdatedOn (getLastUpdatedOn());
		target.setCreatedBy (getCreatedBy());
		target.setCreatedOn (getCreatedOn());
	}


/*
	//-------------------------------------
	// equals method
	//-------------------------------------
	public boolean equals (Object pObj)
	{
    	if (!(pObj instanceof osmsDvLoginHistoryBean)) return false;
	    osmsDvLoginHistoryBean obj = (osmsDvLoginHistoryBean) pObj;


		if (this.getLoginId () != obj.getLoginId () &&
			(this.getLoginId () == null ||
			obj.getLoginId () == null ||
			this.getLoginId ().equals (obj.getLoginId ()))) return false;

		if (this.getUserId () != obj.getUserId () &&
			(this.getUserId () == null ||
			obj.getUserId () == null ||
			this.getUserId ().equals (obj.getUserId ()))) return false;

		if (this.getIpAddress () != obj.getIpAddress () &&
			(this.getIpAddress () == null ||
			obj.getIpAddress () == null ||
			this.getIpAddress ().equals (obj.getIpAddress ()))) return false;

		if (this.getLoginTime () != obj.getLoginTime () &&
			(this.getLoginTime () == null ||
			obj.getLoginTime () == null ||
			this.getLoginTime ().equals (obj.getLoginTime ()))) return false;

		if (this.getLogoffTime () != obj.getLogoffTime () &&
			(this.getLogoffTime () == null ||
			obj.getLogoffTime () == null ||
			this.getLogoffTime ().equals (obj.getLogoffTime ()))) return false;

		if (this.getClientLoginTime () != obj.getClientLoginTime () &&
			(this.getClientLoginTime () == null ||
			obj.getClientLoginTime () == null ||
			this.getClientLoginTime ().equals (obj.getClientLoginTime ()))) return false;

		if (this.getClientLogoffTime () != obj.getClientLogoffTime () &&
			(this.getClientLogoffTime () == null ||
			obj.getClientLogoffTime () == null ||
			this.getClientLogoffTime ().equals (obj.getClientLogoffTime ()))) return false;

		if (this.getMaintenanceFlag () != obj.getMaintenanceFlag () &&
			(this.getMaintenanceFlag () == null ||
			obj.getMaintenanceFlag () == null ||
			this.getMaintenanceFlag ().equals (obj.getMaintenanceFlag ()))) return false;

		if (this.getLastUpdatedBy () != obj.getLastUpdatedBy () &&
			(this.getLastUpdatedBy () == null ||
			obj.getLastUpdatedBy () == null ||
			this.getLastUpdatedBy ().equals (obj.getLastUpdatedBy ()))) return false;

		if (this.getLastUpdatedOn () != obj.getLastUpdatedOn () &&
			(this.getLastUpdatedOn () == null ||
			obj.getLastUpdatedOn () == null ||
			this.getLastUpdatedOn ().equals (obj.getLastUpdatedOn ()))) return false;

		if (this.getCreatedBy () != obj.getCreatedBy () &&
			(this.getCreatedBy () == null ||
			obj.getCreatedBy () == null ||
			this.getCreatedBy ().equals (obj.getCreatedBy ()))) return false;

		if (this.getCreatedOn () != obj.getCreatedOn () &&
			(this.getCreatedOn () == null ||
			obj.getCreatedOn () == null ||
			this.getCreatedOn ().equals (obj.getCreatedOn ()))) return false;

	 	return true;
	}
*/	


	//-------------------------------------
	// print method
	//-------------------------------------
	public void print()
	{

		System.out.println("LoginId = "+this.getLoginId());
		System.out.println("UserId = "+this.getUserId());
		System.out.println("IpAddress = "+this.getIpAddress());
		System.out.println("LoginTime = "+this.getLoginTime());
		System.out.println("LogoffTime = "+this.getLogoffTime());
		System.out.println("ClientLoginTime = "+this.getClientLoginTime());
		System.out.println("ClientLogoffTime = "+this.getClientLogoffTime());
		System.out.println("MaintenanceFlag = "+this.getMaintenanceFlag());
		System.out.println("LastUpdatedBy = "+this.getLastUpdatedBy());
		System.out.println("LastUpdatedOn = "+this.getLastUpdatedOn());
		System.out.println("CreatedBy = "+this.getCreatedBy());
		System.out.println("CreatedOn = "+this.getCreatedOn());
	}
	protected Time ConvertObject2Time(Object obj)
	{
		return (Time)obj;
	}

	
}
