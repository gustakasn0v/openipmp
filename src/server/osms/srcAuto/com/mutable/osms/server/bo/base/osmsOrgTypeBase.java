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

public class osmsOrgTypeBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvOrgTypeBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsOrgTypeBase()
	{m_osmsDvOrgTypeBean= new osmsDvOrgTypeBean();}
	public osmsOrgTypeBase(osmsDvOrgTypeBean bean)
	{m_osmsDvOrgTypeBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvOrgTypeBean m_osmsDvOrgTypeBean;
	public osmsDvOrgTypeBean getOrgTypeBean()
	{return m_osmsDvOrgTypeBean;}
	public void setOrgTypeBean (osmsDvOrgTypeBean bean)
	{m_osmsDvOrgTypeBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public String getOrgTypeCode ()
	{return m_osmsDvOrgTypeBean.getOrgTypeCode ();}
	public void setOrgTypeCode (String pOrgTypeCode)
	{m_osmsDvOrgTypeBean.setOrgTypeCode(pOrgTypeCode);}

	public String getOrgTypeName ()
	{return m_osmsDvOrgTypeBean.getOrgTypeName ();}
	public void setOrgTypeName (String pOrgTypeName)
	{m_osmsDvOrgTypeBean.setOrgTypeName(pOrgTypeName);}

	public String getDescription ()
	{return m_osmsDvOrgTypeBean.getDescription ();}
	public void setDescription (String pDescription)
	{m_osmsDvOrgTypeBean.setDescription(pDescription);}

	public String getMaintenanceFlag ()
	{return m_osmsDvOrgTypeBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvOrgTypeBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvOrgTypeBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvOrgTypeBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvOrgTypeBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvOrgTypeBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvOrgTypeBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvOrgTypeBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvOrgTypeBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvOrgTypeBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvOrgTypeBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
