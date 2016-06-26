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

public class  osmsDvAlgorithmBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int ALGORITHM_ID
	private Integer m_AlgorithmId;
	public Integer getAlgorithmId ()
	{return m_AlgorithmId;}
	public void setAlgorithmId (Integer pAlgorithmId)
	{m_AlgorithmId = pAlgorithmId;}

	//varchar NAME
	private String m_Name;
	public String getName ()
	{return m_Name;}
	public void setName (String pName)
	{m_Name = pName;}

	//varchar OBJECT_IDENTIFIER
	private String m_ObjectIdentifier;
	public String getObjectIdentifier ()
	{return m_ObjectIdentifier;}
	public void setObjectIdentifier (String pObjectIdentifier)
	{m_ObjectIdentifier = pObjectIdentifier;}

	//varchar URL
	private String m_Url;
	public String getUrl ()
	{return m_Url;}
	public void setUrl (String pUrl)
	{m_Url = pUrl;}

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
	public void copyPropertiesTo (osmsDvAlgorithmBean target)
	{

		target.setAlgorithmId (getAlgorithmId());
		target.setName (getName());
		target.setObjectIdentifier (getObjectIdentifier());
		target.setUrl (getUrl());
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
    	if (!(pObj instanceof osmsDvAlgorithmBean)) return false;
	    osmsDvAlgorithmBean obj = (osmsDvAlgorithmBean) pObj;


		if (this.getAlgorithmId () != obj.getAlgorithmId () &&
			(this.getAlgorithmId () == null ||
			obj.getAlgorithmId () == null ||
			this.getAlgorithmId ().equals (obj.getAlgorithmId ()))) return false;

		if (this.getName () != obj.getName () &&
			(this.getName () == null ||
			obj.getName () == null ||
			this.getName ().equals (obj.getName ()))) return false;

		if (this.getObjectIdentifier () != obj.getObjectIdentifier () &&
			(this.getObjectIdentifier () == null ||
			obj.getObjectIdentifier () == null ||
			this.getObjectIdentifier ().equals (obj.getObjectIdentifier ()))) return false;

		if (this.getUrl () != obj.getUrl () &&
			(this.getUrl () == null ||
			obj.getUrl () == null ||
			this.getUrl ().equals (obj.getUrl ()))) return false;

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

		System.out.println("AlgorithmId = "+this.getAlgorithmId());
		System.out.println("Name = "+this.getName());
		System.out.println("ObjectIdentifier = "+this.getObjectIdentifier());
		System.out.println("Url = "+this.getUrl());
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
