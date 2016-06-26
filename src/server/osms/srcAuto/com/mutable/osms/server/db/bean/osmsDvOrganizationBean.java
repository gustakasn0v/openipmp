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

public class  osmsDvOrganizationBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int ORGANIZATION_ID
	private Integer m_OrganizationId;
	public Integer getOrganizationId ()
	{return m_OrganizationId;}
	public void setOrganizationId (Integer pOrganizationId)
	{m_OrganizationId = pOrganizationId;}

	//int CONTACT_USER
	private Integer m_ContactUser;
	public Integer getContactUser ()
	{return m_ContactUser;}
	public void setContactUser (Integer pContactUser)
	{m_ContactUser = pContactUser;}

	//varchar ORG_TYPE_CODE
	private String m_OrgTypeCode;
	public String getOrgTypeCode ()
	{return m_OrgTypeCode;}
	public void setOrgTypeCode (String pOrgTypeCode)
	{m_OrgTypeCode = pOrgTypeCode;}

	//varchar ORGANIZATION_NAME
	private String m_OrganizationName;
	public String getOrganizationName ()
	{return m_OrganizationName;}
	public void setOrganizationName (String pOrganizationName)
	{m_OrganizationName = pOrganizationName;}

	//char STATUS_FLAG
	private String m_StatusFlag;
	public String getStatusFlag ()
	{return m_StatusFlag;}
	public void setStatusFlag (String pStatusFlag)
	{m_StatusFlag = pStatusFlag;}

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
	public void copyPropertiesTo (osmsDvOrganizationBean target)
	{

		target.setOrganizationId (getOrganizationId());
		target.setContactUser (getContactUser());
		target.setOrgTypeCode (getOrgTypeCode());
		target.setOrganizationName (getOrganizationName());
		target.setStatusFlag (getStatusFlag());
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
    	if (!(pObj instanceof osmsDvOrganizationBean)) return false;
	    osmsDvOrganizationBean obj = (osmsDvOrganizationBean) pObj;


		if (this.getOrganizationId () != obj.getOrganizationId () &&
			(this.getOrganizationId () == null ||
			obj.getOrganizationId () == null ||
			this.getOrganizationId ().equals (obj.getOrganizationId ()))) return false;

		if (this.getContactUser () != obj.getContactUser () &&
			(this.getContactUser () == null ||
			obj.getContactUser () == null ||
			this.getContactUser ().equals (obj.getContactUser ()))) return false;

		if (this.getOrgTypeCode () != obj.getOrgTypeCode () &&
			(this.getOrgTypeCode () == null ||
			obj.getOrgTypeCode () == null ||
			this.getOrgTypeCode ().equals (obj.getOrgTypeCode ()))) return false;

		if (this.getOrganizationName () != obj.getOrganizationName () &&
			(this.getOrganizationName () == null ||
			obj.getOrganizationName () == null ||
			this.getOrganizationName ().equals (obj.getOrganizationName ()))) return false;

		if (this.getStatusFlag () != obj.getStatusFlag () &&
			(this.getStatusFlag () == null ||
			obj.getStatusFlag () == null ||
			this.getStatusFlag ().equals (obj.getStatusFlag ()))) return false;

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

		System.out.println("OrganizationId = "+this.getOrganizationId());
		System.out.println("ContactUser = "+this.getContactUser());
		System.out.println("OrgTypeCode = "+this.getOrgTypeCode());
		System.out.println("OrganizationName = "+this.getOrganizationName());
		System.out.println("StatusFlag = "+this.getStatusFlag());
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
