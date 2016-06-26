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

public class osmsContentGridBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvContentGridBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsContentGridBase()
	{m_osmsDvContentGridBean= new osmsDvContentGridBean();}
	public osmsContentGridBase(osmsDvContentGridBean bean)
	{m_osmsDvContentGridBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvContentGridBean m_osmsDvContentGridBean;
	public osmsDvContentGridBean getContentGridBean()
	{return m_osmsDvContentGridBean;}
	public void setContentGridBean (osmsDvContentGridBean bean)
	{m_osmsDvContentGridBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getContentId ()
	{return m_osmsDvContentGridBean.getContentId ();}
	public void setContentId (Integer pContentId)
	{m_osmsDvContentGridBean.setContentId(pContentId);}

	public Integer getGridId ()
	{return m_osmsDvContentGridBean.getGridId ();}
	public void setGridId (Integer pGridId)
	{m_osmsDvContentGridBean.setGridId(pGridId);}

	public String getMaintenanceFlag ()
	{return m_osmsDvContentGridBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvContentGridBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvContentGridBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvContentGridBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvContentGridBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvContentGridBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvContentGridBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvContentGridBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvContentGridBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvContentGridBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvContentGridBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
