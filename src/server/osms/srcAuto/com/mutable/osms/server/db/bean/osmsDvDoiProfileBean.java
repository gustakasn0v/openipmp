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

public class  osmsDvDoiProfileBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//varchar DOI_PROFILE_CODE
	private String m_DoiProfileCode;
	public String getDoiProfileCode ()
	{return m_DoiProfileCode;}
	public void setDoiProfileCode (String pDoiProfileCode)
	{m_DoiProfileCode = pDoiProfileCode;}

	//varchar PROFILE_NAME
	private String m_ProfileName;
	public String getProfileName ()
	{return m_ProfileName;}
	public void setProfileName (String pProfileName)
	{m_ProfileName = pProfileName;}

	//varchar TABLE_NAME
	private String m_TableName;
	public String getTableName ()
	{return m_TableName;}
	public void setTableName (String pTableName)
	{m_TableName = pTableName;}

	//varchar DESC_SHORT
	private String m_DescShort;
	public String getDescShort ()
	{return m_DescShort;}
	public void setDescShort (String pDescShort)
	{m_DescShort = pDescShort;}

	//varchar DESC_LONG
	private String m_DescLong;
	public String getDescLong ()
	{return m_DescLong;}
	public void setDescLong (String pDescLong)
	{m_DescLong = pDescLong;}

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
	public void copyPropertiesTo (osmsDvDoiProfileBean target)
	{

		target.setDoiProfileCode (getDoiProfileCode());
		target.setProfileName (getProfileName());
		target.setTableName (getTableName());
		target.setDescShort (getDescShort());
		target.setDescLong (getDescLong());
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
    	if (!(pObj instanceof osmsDvDoiProfileBean)) return false;
	    osmsDvDoiProfileBean obj = (osmsDvDoiProfileBean) pObj;


		if (this.getDoiProfileCode () != obj.getDoiProfileCode () &&
			(this.getDoiProfileCode () == null ||
			obj.getDoiProfileCode () == null ||
			this.getDoiProfileCode ().equals (obj.getDoiProfileCode ()))) return false;

		if (this.getProfileName () != obj.getProfileName () &&
			(this.getProfileName () == null ||
			obj.getProfileName () == null ||
			this.getProfileName ().equals (obj.getProfileName ()))) return false;

		if (this.getTableName () != obj.getTableName () &&
			(this.getTableName () == null ||
			obj.getTableName () == null ||
			this.getTableName ().equals (obj.getTableName ()))) return false;

		if (this.getDescShort () != obj.getDescShort () &&
			(this.getDescShort () == null ||
			obj.getDescShort () == null ||
			this.getDescShort ().equals (obj.getDescShort ()))) return false;

		if (this.getDescLong () != obj.getDescLong () &&
			(this.getDescLong () == null ||
			obj.getDescLong () == null ||
			this.getDescLong ().equals (obj.getDescLong ()))) return false;

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

		System.out.println("DoiProfileCode = "+this.getDoiProfileCode());
		System.out.println("ProfileName = "+this.getProfileName());
		System.out.println("TableName = "+this.getTableName());
		System.out.println("DescShort = "+this.getDescShort());
		System.out.println("DescLong = "+this.getDescLong());
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
