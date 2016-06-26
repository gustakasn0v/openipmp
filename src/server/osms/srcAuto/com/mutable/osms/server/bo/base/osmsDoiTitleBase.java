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

public class osmsDoiTitleBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiTitleBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsDoiTitleBase()
	{m_osmsDvDoiTitleBean= new osmsDvDoiTitleBean();}
	public osmsDoiTitleBase(osmsDvDoiTitleBean bean)
	{m_osmsDvDoiTitleBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvDoiTitleBean m_osmsDvDoiTitleBean;
	public osmsDvDoiTitleBean getDoiTitleBean()
	{return m_osmsDvDoiTitleBean;}
	public void setDoiTitleBean (osmsDvDoiTitleBean bean)
	{m_osmsDvDoiTitleBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getTitleId ()
	{return m_osmsDvDoiTitleBean.getTitleId ();}
	public void setTitleId (Integer pTitleId)
	{m_osmsDvDoiTitleBean.setTitleId(pTitleId);}

	public Integer getSequence ()
	{return m_osmsDvDoiTitleBean.getSequence ();}
	public void setSequence (Integer pSequence)
	{m_osmsDvDoiTitleBean.setSequence(pSequence);}

	public String getTitleText ()
	{return m_osmsDvDoiTitleBean.getTitleText ();}
	public void setTitleText (String pTitleText)
	{m_osmsDvDoiTitleBean.setTitleText(pTitleText);}

	public String getLanguage ()
	{return m_osmsDvDoiTitleBean.getLanguage ();}
	public void setLanguage (String pLanguage)
	{m_osmsDvDoiTitleBean.setLanguage(pLanguage);}

	public String getMaintenanceFlag ()
	{return m_osmsDvDoiTitleBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvDoiTitleBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvDoiTitleBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvDoiTitleBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvDoiTitleBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvDoiTitleBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvDoiTitleBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvDoiTitleBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvDoiTitleBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvDoiTitleBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiTitleBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
