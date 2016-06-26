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

public class osmsDoiAgentBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiAgentBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsDoiAgentBase()
	{m_osmsDvDoiAgentBean= new osmsDvDoiAgentBean();}
	public osmsDoiAgentBase(osmsDvDoiAgentBean bean)
	{m_osmsDvDoiAgentBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvDoiAgentBean m_osmsDvDoiAgentBean;
	public osmsDvDoiAgentBean getDoiAgentBean()
	{return m_osmsDvDoiAgentBean;}
	public void setDoiAgentBean (osmsDvDoiAgentBean bean)
	{m_osmsDvDoiAgentBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getDoiAgentId ()
	{return m_osmsDvDoiAgentBean.getDoiAgentId ();}
	public void setDoiAgentId (Integer pDoiAgentId)
	{m_osmsDvDoiAgentBean.setDoiAgentId(pDoiAgentId);}

	public Integer getDoiId ()
	{return m_osmsDvDoiAgentBean.getDoiId ();}
	public void setDoiId (Integer pDoiId)
	{m_osmsDvDoiAgentBean.setDoiId(pDoiId);}

	public Integer getSequence ()
	{return m_osmsDvDoiAgentBean.getSequence ();}
	public void setSequence (Integer pSequence)
	{m_osmsDvDoiAgentBean.setSequence(pSequence);}

	public String getAgentType ()
	{return m_osmsDvDoiAgentBean.getAgentType ();}
	public void setAgentType (String pAgentType)
	{m_osmsDvDoiAgentBean.setAgentType(pAgentType);}

	public String getAgentName ()
	{return m_osmsDvDoiAgentBean.getAgentName ();}
	public void setAgentName (String pAgentName)
	{m_osmsDvDoiAgentBean.setAgentName(pAgentName);}

	public String getRole1 ()
	{return m_osmsDvDoiAgentBean.getRole1 ();}
	public void setRole1 (String pRole1)
	{m_osmsDvDoiAgentBean.setRole1(pRole1);}

	public String getRole2 ()
	{return m_osmsDvDoiAgentBean.getRole2 ();}
	public void setRole2 (String pRole2)
	{m_osmsDvDoiAgentBean.setRole2(pRole2);}

	public String getRole3 ()
	{return m_osmsDvDoiAgentBean.getRole3 ();}
	public void setRole3 (String pRole3)
	{m_osmsDvDoiAgentBean.setRole3(pRole3);}

	public String getRole4 ()
	{return m_osmsDvDoiAgentBean.getRole4 ();}
	public void setRole4 (String pRole4)
	{m_osmsDvDoiAgentBean.setRole4(pRole4);}

	public String getMaintenanceFlag ()
	{return m_osmsDvDoiAgentBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvDoiAgentBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvDoiAgentBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvDoiAgentBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvDoiAgentBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvDoiAgentBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvDoiAgentBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvDoiAgentBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvDoiAgentBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvDoiAgentBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiAgentBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
