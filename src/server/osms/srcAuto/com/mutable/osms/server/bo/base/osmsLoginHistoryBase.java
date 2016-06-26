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
package com.mutable.osms.server.bo.base;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;

import java.io.Serializable;

import com.mutable.osms.server.db.bean.*;

public class osmsLoginHistoryBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvLoginHistoryBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsLoginHistoryBase()
	{m_osmsDvLoginHistoryBean= new osmsDvLoginHistoryBean();}
	public osmsLoginHistoryBase(osmsDvLoginHistoryBean bean)
	{m_osmsDvLoginHistoryBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvLoginHistoryBean m_osmsDvLoginHistoryBean;
	public osmsDvLoginHistoryBean getLoginHistoryBean()
	{return m_osmsDvLoginHistoryBean;}
	public void setLoginHistoryBean (osmsDvLoginHistoryBean bean)
	{m_osmsDvLoginHistoryBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getLoginId ()
	{return m_osmsDvLoginHistoryBean.getLoginId ();}
	public void setLoginId (Integer pLoginId)
	{m_osmsDvLoginHistoryBean.setLoginId(pLoginId);}

	public Integer getUserId ()
	{return m_osmsDvLoginHistoryBean.getUserId ();}
	public void setUserId (Integer pUserId)
	{m_osmsDvLoginHistoryBean.setUserId(pUserId);}

	public String getIpAddress ()
	{return m_osmsDvLoginHistoryBean.getIpAddress ();}
	public void setIpAddress (String pIpAddress)
	{m_osmsDvLoginHistoryBean.setIpAddress(pIpAddress);}

	public Timestamp getLoginTime ()
	{return m_osmsDvLoginHistoryBean.getLoginTime ();}
	public void setLoginTime (Timestamp pLoginTime)
	{m_osmsDvLoginHistoryBean.setLoginTime(pLoginTime);}

	public Timestamp getLogoffTime ()
	{return m_osmsDvLoginHistoryBean.getLogoffTime ();}
	public void setLogoffTime (Timestamp pLogoffTime)
	{m_osmsDvLoginHistoryBean.setLogoffTime(pLogoffTime);}

	public Timestamp getClientLoginTime ()
	{return m_osmsDvLoginHistoryBean.getClientLoginTime ();}
	public void setClientLoginTime (Timestamp pClientLoginTime)
	{m_osmsDvLoginHistoryBean.setClientLoginTime(pClientLoginTime);}

	public Timestamp getClientLogoffTime ()
	{return m_osmsDvLoginHistoryBean.getClientLogoffTime ();}
	public void setClientLogoffTime (Timestamp pClientLogoffTime)
	{m_osmsDvLoginHistoryBean.setClientLogoffTime(pClientLogoffTime);}

	public String getMaintenanceFlag ()
	{return m_osmsDvLoginHistoryBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvLoginHistoryBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvLoginHistoryBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvLoginHistoryBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvLoginHistoryBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvLoginHistoryBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvLoginHistoryBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvLoginHistoryBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvLoginHistoryBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvLoginHistoryBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvLoginHistoryBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
