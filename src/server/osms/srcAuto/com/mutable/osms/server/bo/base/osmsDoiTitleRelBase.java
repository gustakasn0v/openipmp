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

public class osmsDoiTitleRelBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiTitleRelBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsDoiTitleRelBase()
	{m_osmsDvDoiTitleRelBean= new osmsDvDoiTitleRelBean();}
	public osmsDoiTitleRelBase(osmsDvDoiTitleRelBean bean)
	{m_osmsDvDoiTitleRelBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvDoiTitleRelBean m_osmsDvDoiTitleRelBean;
	public osmsDvDoiTitleRelBean getDoiTitleRelBean()
	{return m_osmsDvDoiTitleRelBean;}
	public void setDoiTitleRelBean (osmsDvDoiTitleRelBean bean)
	{m_osmsDvDoiTitleRelBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getDoiId ()
	{return m_osmsDvDoiTitleRelBean.getDoiId ();}
	public void setDoiId (Integer pDoiId)
	{m_osmsDvDoiTitleRelBean.setDoiId(pDoiId);}

	public Integer getTitleId ()
	{return m_osmsDvDoiTitleRelBean.getTitleId ();}
	public void setTitleId (Integer pTitleId)
	{m_osmsDvDoiTitleRelBean.setTitleId(pTitleId);}

	public String getMaintenanceFlag ()
	{return m_osmsDvDoiTitleRelBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvDoiTitleRelBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvDoiTitleRelBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvDoiTitleRelBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvDoiTitleRelBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvDoiTitleRelBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvDoiTitleRelBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvDoiTitleRelBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvDoiTitleRelBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvDoiTitleRelBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiTitleRelBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
