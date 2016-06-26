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

public class osmsGridBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvGridBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsGridBase()
	{m_osmsDvGridBean= new osmsDvGridBean();}
	public osmsGridBase(osmsDvGridBean bean)
	{m_osmsDvGridBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvGridBean m_osmsDvGridBean;
	public osmsDvGridBean getGridBean()
	{return m_osmsDvGridBean;}
	public void setGridBean (osmsDvGridBean bean)
	{m_osmsDvGridBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getGridId ()
	{return m_osmsDvGridBean.getGridId ();}
	public void setGridId (Integer pGridId)
	{m_osmsDvGridBean.setGridId(pGridId);}

	public String getGrid ()
	{return m_osmsDvGridBean.getGrid ();}
	public void setGrid (String pGrid)
	{m_osmsDvGridBean.setGrid(pGrid);}

	public String getPrimaryArtist ()
	{return m_osmsDvGridBean.getPrimaryArtist ();}
	public void setPrimaryArtist (String pPrimaryArtist)
	{m_osmsDvGridBean.setPrimaryArtist(pPrimaryArtist);}

	public String getPrimaryTitle ()
	{return m_osmsDvGridBean.getPrimaryTitle ();}
	public void setPrimaryTitle (String pPrimaryTitle)
	{m_osmsDvGridBean.setPrimaryTitle(pPrimaryTitle);}

	public String getIssuingCompany ()
	{return m_osmsDvGridBean.getIssuingCompany ();}
	public void setIssuingCompany (String pIssuingCompany)
	{m_osmsDvGridBean.setIssuingCompany(pIssuingCompany);}

	public String getXmlString ()
	{return m_osmsDvGridBean.getXmlString ();}
	public void setXmlString (String pXmlString)
	{m_osmsDvGridBean.setXmlString(pXmlString);}

	public String getMaintenanceFlag ()
	{return m_osmsDvGridBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvGridBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvGridBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvGridBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvGridBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvGridBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvGridBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvGridBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvGridBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvGridBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvGridBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
