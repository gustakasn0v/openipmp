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

public class osmsIdentifierTypeBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvIdentifierTypeBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsIdentifierTypeBase()
	{m_osmsDvIdentifierTypeBean= new osmsDvIdentifierTypeBean();}
	public osmsIdentifierTypeBase(osmsDvIdentifierTypeBean bean)
	{m_osmsDvIdentifierTypeBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvIdentifierTypeBean m_osmsDvIdentifierTypeBean;
	public osmsDvIdentifierTypeBean getIdentifierTypeBean()
	{return m_osmsDvIdentifierTypeBean;}
	public void setIdentifierTypeBean (osmsDvIdentifierTypeBean bean)
	{m_osmsDvIdentifierTypeBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public String getIdentifierTypeCode ()
	{return m_osmsDvIdentifierTypeBean.getIdentifierTypeCode ();}
	public void setIdentifierTypeCode (String pIdentifierTypeCode)
	{m_osmsDvIdentifierTypeBean.setIdentifierTypeCode(pIdentifierTypeCode);}

	public String getDescription ()
	{return m_osmsDvIdentifierTypeBean.getDescription ();}
	public void setDescription (String pDescription)
	{m_osmsDvIdentifierTypeBean.setDescription(pDescription);}

	public String getMaintenanceFlag ()
	{return m_osmsDvIdentifierTypeBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvIdentifierTypeBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvIdentifierTypeBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvIdentifierTypeBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvIdentifierTypeBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvIdentifierTypeBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvIdentifierTypeBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvIdentifierTypeBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvIdentifierTypeBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvIdentifierTypeBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvIdentifierTypeBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
