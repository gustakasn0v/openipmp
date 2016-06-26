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

public class osmsDoiProfileBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiProfileBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsDoiProfileBase()
	{m_osmsDvDoiProfileBean= new osmsDvDoiProfileBean();}
	public osmsDoiProfileBase(osmsDvDoiProfileBean bean)
	{m_osmsDvDoiProfileBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvDoiProfileBean m_osmsDvDoiProfileBean;
	public osmsDvDoiProfileBean getDoiProfileBean()
	{return m_osmsDvDoiProfileBean;}
	public void setDoiProfileBean (osmsDvDoiProfileBean bean)
	{m_osmsDvDoiProfileBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public String getDoiProfileCode ()
	{return m_osmsDvDoiProfileBean.getDoiProfileCode ();}
	public void setDoiProfileCode (String pDoiProfileCode)
	{m_osmsDvDoiProfileBean.setDoiProfileCode(pDoiProfileCode);}

	public String getProfileName ()
	{return m_osmsDvDoiProfileBean.getProfileName ();}
	public void setProfileName (String pProfileName)
	{m_osmsDvDoiProfileBean.setProfileName(pProfileName);}

	public String getTableName ()
	{return m_osmsDvDoiProfileBean.getTableName ();}
	public void setTableName (String pTableName)
	{m_osmsDvDoiProfileBean.setTableName(pTableName);}

	public String getDescShort ()
	{return m_osmsDvDoiProfileBean.getDescShort ();}
	public void setDescShort (String pDescShort)
	{m_osmsDvDoiProfileBean.setDescShort(pDescShort);}

	public String getDescLong ()
	{return m_osmsDvDoiProfileBean.getDescLong ();}
	public void setDescLong (String pDescLong)
	{m_osmsDvDoiProfileBean.setDescLong(pDescLong);}

	public String getMaintenanceFlag ()
	{return m_osmsDvDoiProfileBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvDoiProfileBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvDoiProfileBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvDoiProfileBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvDoiProfileBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvDoiProfileBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvDoiProfileBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvDoiProfileBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvDoiProfileBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvDoiProfileBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiProfileBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
