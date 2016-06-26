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

public class osmsAltIdentifierBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvAltIdentifierBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsAltIdentifierBase()
	{m_osmsDvAltIdentifierBean= new osmsDvAltIdentifierBean();}
	public osmsAltIdentifierBase(osmsDvAltIdentifierBean bean)
	{m_osmsDvAltIdentifierBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvAltIdentifierBean m_osmsDvAltIdentifierBean;
	public osmsDvAltIdentifierBean getAltIdentifierBean()
	{return m_osmsDvAltIdentifierBean;}
	public void setAltIdentifierBean (osmsDvAltIdentifierBean bean)
	{m_osmsDvAltIdentifierBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getAltIdentifierId ()
	{return m_osmsDvAltIdentifierBean.getAltIdentifierId ();}
	public void setAltIdentifierId (Integer pAltIdentifierId)
	{m_osmsDvAltIdentifierBean.setAltIdentifierId(pAltIdentifierId);}

	public String getIdentifierTypeCode ()
	{return m_osmsDvAltIdentifierBean.getIdentifierTypeCode ();}
	public void setIdentifierTypeCode (String pIdentifierTypeCode)
	{m_osmsDvAltIdentifierBean.setIdentifierTypeCode(pIdentifierTypeCode);}

	public String getIdentifier ()
	{return m_osmsDvAltIdentifierBean.getIdentifier ();}
	public void setIdentifier (String pIdentifier)
	{m_osmsDvAltIdentifierBean.setIdentifier(pIdentifier);}

	public String getMaintenanceFlag ()
	{return m_osmsDvAltIdentifierBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvAltIdentifierBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvAltIdentifierBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvAltIdentifierBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvAltIdentifierBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvAltIdentifierBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvAltIdentifierBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvAltIdentifierBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvAltIdentifierBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvAltIdentifierBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvAltIdentifierBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
