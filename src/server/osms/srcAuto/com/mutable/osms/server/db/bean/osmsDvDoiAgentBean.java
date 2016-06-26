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
package com.mutable.osms.server.db.bean;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;

import java.io.Serializable;
import java.util.Date;

public class  osmsDvDoiAgentBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int DOI_AGENT_ID
	private Integer m_DoiAgentId;
	public Integer getDoiAgentId ()
	{return m_DoiAgentId;}
	public void setDoiAgentId (Integer pDoiAgentId)
	{m_DoiAgentId = pDoiAgentId;}

	//int DOI_ID
	private Integer m_DoiId;
	public Integer getDoiId ()
	{return m_DoiId;}
	public void setDoiId (Integer pDoiId)
	{m_DoiId = pDoiId;}

	//int SEQUENCE
	private Integer m_Sequence;
	public Integer getSequence ()
	{return m_Sequence;}
	public void setSequence (Integer pSequence)
	{m_Sequence = pSequence;}

	//varchar AGENT_TYPE
	private String m_AgentType;
	public String getAgentType ()
	{return m_AgentType;}
	public void setAgentType (String pAgentType)
	{m_AgentType = pAgentType;}

	//varchar AGENT_NAME
	private String m_AgentName;
	public String getAgentName ()
	{return m_AgentName;}
	public void setAgentName (String pAgentName)
	{m_AgentName = pAgentName;}

	//varchar ROLE1
	private String m_Role1;
	public String getRole1 ()
	{return m_Role1;}
	public void setRole1 (String pRole1)
	{m_Role1 = pRole1;}

	//varchar ROLE2
	private String m_Role2;
	public String getRole2 ()
	{return m_Role2;}
	public void setRole2 (String pRole2)
	{m_Role2 = pRole2;}

	//varchar ROLE3
	private String m_Role3;
	public String getRole3 ()
	{return m_Role3;}
	public void setRole3 (String pRole3)
	{m_Role3 = pRole3;}

	//varchar ROLE4
	private String m_Role4;
	public String getRole4 ()
	{return m_Role4;}
	public void setRole4 (String pRole4)
	{m_Role4 = pRole4;}

	//char MAINTENANCE_FLAG
	private String m_MaintenanceFlag;
	public String getMaintenanceFlag ()
	{return m_MaintenanceFlag;}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_MaintenanceFlag = pMaintenanceFlag;}

	//varchar LAST_UPDATED_BY
	private String m_LastUpdatedBy;
	public String getLastUpdatedBy ()
	{return m_LastUpdatedBy;}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_LastUpdatedBy = pLastUpdatedBy;}

	//datetime LAST_UPDATED_ON
	private Timestamp m_LastUpdatedOn;
	public Timestamp getLastUpdatedOn ()
	{return m_LastUpdatedOn;}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_LastUpdatedOn = pLastUpdatedOn;}

	//varchar CREATED_BY
	private String m_CreatedBy;
	public String getCreatedBy ()
	{return m_CreatedBy;}
	public void setCreatedBy (String pCreatedBy)
	{m_CreatedBy = pCreatedBy;}

	//datetime CREATED_ON
	private Timestamp m_CreatedOn;
	public Timestamp getCreatedOn ()
	{return m_CreatedOn;}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_CreatedOn = pCreatedOn;}


	//-------------------------------------
	// copyPropertiesTo method
	//-------------------------------------
	public void copyPropertiesTo (osmsDvDoiAgentBean target)
	{

		target.setDoiAgentId (getDoiAgentId());
		target.setDoiId (getDoiId());
		target.setSequence (getSequence());
		target.setAgentType (getAgentType());
		target.setAgentName (getAgentName());
		target.setRole1 (getRole1());
		target.setRole2 (getRole2());
		target.setRole3 (getRole3());
		target.setRole4 (getRole4());
		target.setMaintenanceFlag (getMaintenanceFlag());
		target.setLastUpdatedBy (getLastUpdatedBy());
		target.setLastUpdatedOn (getLastUpdatedOn());
		target.setCreatedBy (getCreatedBy());
		target.setCreatedOn (getCreatedOn());
	}


/*
	//-------------------------------------
	// equals method
	//-------------------------------------
	public boolean equals (Object pObj)
	{
    	if (!(pObj instanceof osmsDvDoiAgentBean)) return false;
	    osmsDvDoiAgentBean obj = (osmsDvDoiAgentBean) pObj;


		if (this.getDoiAgentId () != obj.getDoiAgentId () &&
			(this.getDoiAgentId () == null ||
			obj.getDoiAgentId () == null ||
			this.getDoiAgentId ().equals (obj.getDoiAgentId ()))) return false;

		if (this.getDoiId () != obj.getDoiId () &&
			(this.getDoiId () == null ||
			obj.getDoiId () == null ||
			this.getDoiId ().equals (obj.getDoiId ()))) return false;

		if (this.getSequence () != obj.getSequence () &&
			(this.getSequence () == null ||
			obj.getSequence () == null ||
			this.getSequence ().equals (obj.getSequence ()))) return false;

		if (this.getAgentType () != obj.getAgentType () &&
			(this.getAgentType () == null ||
			obj.getAgentType () == null ||
			this.getAgentType ().equals (obj.getAgentType ()))) return false;

		if (this.getAgentName () != obj.getAgentName () &&
			(this.getAgentName () == null ||
			obj.getAgentName () == null ||
			this.getAgentName ().equals (obj.getAgentName ()))) return false;

		if (this.getRole1 () != obj.getRole1 () &&
			(this.getRole1 () == null ||
			obj.getRole1 () == null ||
			this.getRole1 ().equals (obj.getRole1 ()))) return false;

		if (this.getRole2 () != obj.getRole2 () &&
			(this.getRole2 () == null ||
			obj.getRole2 () == null ||
			this.getRole2 ().equals (obj.getRole2 ()))) return false;

		if (this.getRole3 () != obj.getRole3 () &&
			(this.getRole3 () == null ||
			obj.getRole3 () == null ||
			this.getRole3 ().equals (obj.getRole3 ()))) return false;

		if (this.getRole4 () != obj.getRole4 () &&
			(this.getRole4 () == null ||
			obj.getRole4 () == null ||
			this.getRole4 ().equals (obj.getRole4 ()))) return false;

		if (this.getMaintenanceFlag () != obj.getMaintenanceFlag () &&
			(this.getMaintenanceFlag () == null ||
			obj.getMaintenanceFlag () == null ||
			this.getMaintenanceFlag ().equals (obj.getMaintenanceFlag ()))) return false;

		if (this.getLastUpdatedBy () != obj.getLastUpdatedBy () &&
			(this.getLastUpdatedBy () == null ||
			obj.getLastUpdatedBy () == null ||
			this.getLastUpdatedBy ().equals (obj.getLastUpdatedBy ()))) return false;

		if (this.getLastUpdatedOn () != obj.getLastUpdatedOn () &&
			(this.getLastUpdatedOn () == null ||
			obj.getLastUpdatedOn () == null ||
			this.getLastUpdatedOn ().equals (obj.getLastUpdatedOn ()))) return false;

		if (this.getCreatedBy () != obj.getCreatedBy () &&
			(this.getCreatedBy () == null ||
			obj.getCreatedBy () == null ||
			this.getCreatedBy ().equals (obj.getCreatedBy ()))) return false;

		if (this.getCreatedOn () != obj.getCreatedOn () &&
			(this.getCreatedOn () == null ||
			obj.getCreatedOn () == null ||
			this.getCreatedOn ().equals (obj.getCreatedOn ()))) return false;

	 	return true;
	}
*/	


	//-------------------------------------
	// print method
	//-------------------------------------
	public void print()
	{

		System.out.println("DoiAgentId = "+this.getDoiAgentId());
		System.out.println("DoiId = "+this.getDoiId());
		System.out.println("Sequence = "+this.getSequence());
		System.out.println("AgentType = "+this.getAgentType());
		System.out.println("AgentName = "+this.getAgentName());
		System.out.println("Role1 = "+this.getRole1());
		System.out.println("Role2 = "+this.getRole2());
		System.out.println("Role3 = "+this.getRole3());
		System.out.println("Role4 = "+this.getRole4());
		System.out.println("MaintenanceFlag = "+this.getMaintenanceFlag());
		System.out.println("LastUpdatedBy = "+this.getLastUpdatedBy());
		System.out.println("LastUpdatedOn = "+this.getLastUpdatedOn());
		System.out.println("CreatedBy = "+this.getCreatedBy());
		System.out.println("CreatedOn = "+this.getCreatedOn());
	}
	protected Time ConvertObject2Time(Object obj)
	{
		return (Time)obj;
	}

	
}
