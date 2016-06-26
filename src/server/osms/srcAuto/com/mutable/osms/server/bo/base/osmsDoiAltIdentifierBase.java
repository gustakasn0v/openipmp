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

public class osmsDoiAltIdentifierBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiAltIdentifierBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsDoiAltIdentifierBase()
	{m_osmsDvDoiAltIdentifierBean= new osmsDvDoiAltIdentifierBean();}
	public osmsDoiAltIdentifierBase(osmsDvDoiAltIdentifierBean bean)
	{m_osmsDvDoiAltIdentifierBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvDoiAltIdentifierBean m_osmsDvDoiAltIdentifierBean;
	public osmsDvDoiAltIdentifierBean getDoiAltIdentifierBean()
	{return m_osmsDvDoiAltIdentifierBean;}
	public void setDoiAltIdentifierBean (osmsDvDoiAltIdentifierBean bean)
	{m_osmsDvDoiAltIdentifierBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getDoiId ()
	{return m_osmsDvDoiAltIdentifierBean.getDoiId ();}
	public void setDoiId (Integer pDoiId)
	{m_osmsDvDoiAltIdentifierBean.setDoiId(pDoiId);}

	public Integer getAltIdentifierId ()
	{return m_osmsDvDoiAltIdentifierBean.getAltIdentifierId ();}
	public void setAltIdentifierId (Integer pAltIdentifierId)
	{m_osmsDvDoiAltIdentifierBean.setAltIdentifierId(pAltIdentifierId);}

	public Integer getSequence ()
	{return m_osmsDvDoiAltIdentifierBean.getSequence ();}
	public void setSequence (Integer pSequence)
	{m_osmsDvDoiAltIdentifierBean.setSequence(pSequence);}

	public String getMaintenanceFlag ()
	{return m_osmsDvDoiAltIdentifierBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvDoiAltIdentifierBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvDoiAltIdentifierBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvDoiAltIdentifierBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvDoiAltIdentifierBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvDoiAltIdentifierBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvDoiAltIdentifierBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvDoiAltIdentifierBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvDoiAltIdentifierBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvDoiAltIdentifierBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiAltIdentifierBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
