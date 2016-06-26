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

public class osmsContentDoiBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvContentDoiBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsContentDoiBase()
	{m_osmsDvContentDoiBean= new osmsDvContentDoiBean();}
	public osmsContentDoiBase(osmsDvContentDoiBean bean)
	{m_osmsDvContentDoiBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvContentDoiBean m_osmsDvContentDoiBean;
	public osmsDvContentDoiBean getContentDoiBean()
	{return m_osmsDvContentDoiBean;}
	public void setContentDoiBean (osmsDvContentDoiBean bean)
	{m_osmsDvContentDoiBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getContentId ()
	{return m_osmsDvContentDoiBean.getContentId ();}
	public void setContentId (Integer pContentId)
	{m_osmsDvContentDoiBean.setContentId(pContentId);}

	public Integer getDoiId ()
	{return m_osmsDvContentDoiBean.getDoiId ();}
	public void setDoiId (Integer pDoiId)
	{m_osmsDvContentDoiBean.setDoiId(pDoiId);}

	public String getMaintenanceFlag ()
	{return m_osmsDvContentDoiBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvContentDoiBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvContentDoiBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvContentDoiBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvContentDoiBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvContentDoiBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvContentDoiBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvContentDoiBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvContentDoiBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvContentDoiBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvContentDoiBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
