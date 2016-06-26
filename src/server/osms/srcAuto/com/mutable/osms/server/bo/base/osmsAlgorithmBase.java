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

public class osmsAlgorithmBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvAlgorithmBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsAlgorithmBase()
	{m_osmsDvAlgorithmBean= new osmsDvAlgorithmBean();}
	public osmsAlgorithmBase(osmsDvAlgorithmBean bean)
	{m_osmsDvAlgorithmBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvAlgorithmBean m_osmsDvAlgorithmBean;
	public osmsDvAlgorithmBean getAlgorithmBean()
	{return m_osmsDvAlgorithmBean;}
	public void setAlgorithmBean (osmsDvAlgorithmBean bean)
	{m_osmsDvAlgorithmBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getAlgorithmId ()
	{return m_osmsDvAlgorithmBean.getAlgorithmId ();}
	public void setAlgorithmId (Integer pAlgorithmId)
	{m_osmsDvAlgorithmBean.setAlgorithmId(pAlgorithmId);}

	public String getName ()
	{return m_osmsDvAlgorithmBean.getName ();}
	public void setName (String pName)
	{m_osmsDvAlgorithmBean.setName(pName);}

	public String getObjectIdentifier ()
	{return m_osmsDvAlgorithmBean.getObjectIdentifier ();}
	public void setObjectIdentifier (String pObjectIdentifier)
	{m_osmsDvAlgorithmBean.setObjectIdentifier(pObjectIdentifier);}

	public String getUrl ()
	{return m_osmsDvAlgorithmBean.getUrl ();}
	public void setUrl (String pUrl)
	{m_osmsDvAlgorithmBean.setUrl(pUrl);}

	public String getMaintenanceFlag ()
	{return m_osmsDvAlgorithmBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvAlgorithmBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvAlgorithmBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvAlgorithmBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvAlgorithmBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvAlgorithmBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvAlgorithmBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvAlgorithmBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvAlgorithmBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvAlgorithmBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvAlgorithmBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
