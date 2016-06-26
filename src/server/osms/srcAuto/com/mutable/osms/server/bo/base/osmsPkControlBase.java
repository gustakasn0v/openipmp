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

public class osmsPkControlBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvPkControlBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsPkControlBase()
	{m_osmsDvPkControlBean= new osmsDvPkControlBean();}
	public osmsPkControlBase(osmsDvPkControlBean bean)
	{m_osmsDvPkControlBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvPkControlBean m_osmsDvPkControlBean;
	public osmsDvPkControlBean getPkControlBean()
	{return m_osmsDvPkControlBean;}
	public void setPkControlBean (osmsDvPkControlBean bean)
	{m_osmsDvPkControlBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public String getTableName ()
	{return m_osmsDvPkControlBean.getTableName ();}
	public void setTableName (String pTableName)
	{m_osmsDvPkControlBean.setTableName(pTableName);}

	public Integer getCurrPkValue ()
	{return m_osmsDvPkControlBean.getCurrPkValue ();}
	public void setCurrPkValue (Integer pCurrPkValue)
	{m_osmsDvPkControlBean.setCurrPkValue(pCurrPkValue);}

	public String getMaintenanceFlag ()
	{return m_osmsDvPkControlBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvPkControlBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvPkControlBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvPkControlBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvPkControlBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvPkControlBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvPkControlBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvPkControlBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvPkControlBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvPkControlBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvPkControlBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
