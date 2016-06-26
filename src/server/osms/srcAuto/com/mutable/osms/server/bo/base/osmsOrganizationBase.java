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

public class osmsOrganizationBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvOrganizationBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsOrganizationBase()
	{m_osmsDvOrganizationBean= new osmsDvOrganizationBean();}
	public osmsOrganizationBase(osmsDvOrganizationBean bean)
	{m_osmsDvOrganizationBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvOrganizationBean m_osmsDvOrganizationBean;
	public osmsDvOrganizationBean getOrganizationBean()
	{return m_osmsDvOrganizationBean;}
	public void setOrganizationBean (osmsDvOrganizationBean bean)
	{m_osmsDvOrganizationBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getOrganizationId ()
	{return m_osmsDvOrganizationBean.getOrganizationId ();}
	public void setOrganizationId (Integer pOrganizationId)
	{m_osmsDvOrganizationBean.setOrganizationId(pOrganizationId);}

	public Integer getContactUser ()
	{return m_osmsDvOrganizationBean.getContactUser ();}
	public void setContactUser (Integer pContactUser)
	{m_osmsDvOrganizationBean.setContactUser(pContactUser);}

	public String getOrgTypeCode ()
	{return m_osmsDvOrganizationBean.getOrgTypeCode ();}
	public void setOrgTypeCode (String pOrgTypeCode)
	{m_osmsDvOrganizationBean.setOrgTypeCode(pOrgTypeCode);}

	public String getOrganizationName ()
	{return m_osmsDvOrganizationBean.getOrganizationName ();}
	public void setOrganizationName (String pOrganizationName)
	{m_osmsDvOrganizationBean.setOrganizationName(pOrganizationName);}

	public String getStatusFlag ()
	{return m_osmsDvOrganizationBean.getStatusFlag ();}
	public void setStatusFlag (String pStatusFlag)
	{m_osmsDvOrganizationBean.setStatusFlag(pStatusFlag);}

	public String getMaintenanceFlag ()
	{return m_osmsDvOrganizationBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvOrganizationBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvOrganizationBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvOrganizationBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvOrganizationBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvOrganizationBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvOrganizationBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvOrganizationBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvOrganizationBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvOrganizationBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvOrganizationBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
