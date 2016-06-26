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

public class  osmsDvIpmpAgreementBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int AGREEMENT_ID
	private Integer m_AgreementId;
	public Integer getAgreementId ()
	{return m_AgreementId;}
	public void setAgreementId (Integer pAgreementId)
	{m_AgreementId = pAgreementId;}

	//int CONTENT_ID
	private Integer m_ContentId;
	public Integer getContentId ()
	{return m_ContentId;}
	public void setContentId (Integer pContentId)
	{m_ContentId = pContentId;}

	//datetime START_DATE
	private Timestamp m_StartDate;
	public Timestamp getStartDate ()
	{return m_StartDate;}
	public void setStartDate (Timestamp pStartDate)
	{m_StartDate = pStartDate;}

	//datetime END_DATE
	private Timestamp m_EndDate;
	public Timestamp getEndDate ()
	{return m_EndDate;}
	public void setEndDate (Timestamp pEndDate)
	{m_EndDate = pEndDate;}

	//int USER_LICENSE_LIMIT
	private Integer m_UserLicenseLimit;
	public Integer getUserLicenseLimit ()
	{return m_UserLicenseLimit;}
	public void setUserLicenseLimit (Integer pUserLicenseLimit)
	{m_UserLicenseLimit = pUserLicenseLimit;}

	//int GLOBAL_LICENSE_LIMIT
	private Integer m_GlobalLicenseLimit;
	public Integer getGlobalLicenseLimit ()
	{return m_GlobalLicenseLimit;}
	public void setGlobalLicenseLimit (Integer pGlobalLicenseLimit)
	{m_GlobalLicenseLimit = pGlobalLicenseLimit;}

	//varchar LICENSE_TYPE
	private String m_LicenseType;
	public String getLicenseType ()
	{return m_LicenseType;}
	public void setLicenseType (String pLicenseType)
	{m_LicenseType = pLicenseType;}

	//int ASSIGNED_TO_USER
	private Integer m_AssignedToUser;
	public Integer getAssignedToUser ()
	{return m_AssignedToUser;}
	public void setAssignedToUser (Integer pAssignedToUser)
	{m_AssignedToUser = pAssignedToUser;}

	//int ASSIGNED_TO_GROUP
	private Integer m_AssignedToGroup;
	public Integer getAssignedToGroup ()
	{return m_AssignedToGroup;}
	public void setAssignedToGroup (Integer pAssignedToGroup)
	{m_AssignedToGroup = pAssignedToGroup;}

	//int REGISTERED_BY
	private Integer m_RegisteredBy;
	public Integer getRegisteredBy ()
	{return m_RegisteredBy;}
	public void setRegisteredBy (Integer pRegisteredBy)
	{m_RegisteredBy = pRegisteredBy;}

	//text XML_STRING
	private String m_XmlString;
	public String getXmlString ()
	{return m_XmlString;}
	public void setXmlString (String pXmlString)
	{m_XmlString = pXmlString;}

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
	public void copyPropertiesTo (osmsDvIpmpAgreementBean target)
	{

		target.setAgreementId (getAgreementId());
		target.setContentId (getContentId());
		target.setStartDate (getStartDate());
		target.setEndDate (getEndDate());
		target.setUserLicenseLimit (getUserLicenseLimit());
		target.setGlobalLicenseLimit (getGlobalLicenseLimit());
		target.setLicenseType (getLicenseType());
		target.setAssignedToUser (getAssignedToUser());
		target.setAssignedToGroup (getAssignedToGroup());
		target.setRegisteredBy (getRegisteredBy());
		target.setXmlString (getXmlString());
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
    	if (!(pObj instanceof osmsDvIpmpAgreementBean)) return false;
	    osmsDvIpmpAgreementBean obj = (osmsDvIpmpAgreementBean) pObj;


		if (this.getAgreementId () != obj.getAgreementId () &&
			(this.getAgreementId () == null ||
			obj.getAgreementId () == null ||
			this.getAgreementId ().equals (obj.getAgreementId ()))) return false;

		if (this.getContentId () != obj.getContentId () &&
			(this.getContentId () == null ||
			obj.getContentId () == null ||
			this.getContentId ().equals (obj.getContentId ()))) return false;

		if (this.getStartDate () != obj.getStartDate () &&
			(this.getStartDate () == null ||
			obj.getStartDate () == null ||
			this.getStartDate ().equals (obj.getStartDate ()))) return false;

		if (this.getEndDate () != obj.getEndDate () &&
			(this.getEndDate () == null ||
			obj.getEndDate () == null ||
			this.getEndDate ().equals (obj.getEndDate ()))) return false;

		if (this.getUserLicenseLimit () != obj.getUserLicenseLimit () &&
			(this.getUserLicenseLimit () == null ||
			obj.getUserLicenseLimit () == null ||
			this.getUserLicenseLimit ().equals (obj.getUserLicenseLimit ()))) return false;

		if (this.getGlobalLicenseLimit () != obj.getGlobalLicenseLimit () &&
			(this.getGlobalLicenseLimit () == null ||
			obj.getGlobalLicenseLimit () == null ||
			this.getGlobalLicenseLimit ().equals (obj.getGlobalLicenseLimit ()))) return false;

		if (this.getLicenseType () != obj.getLicenseType () &&
			(this.getLicenseType () == null ||
			obj.getLicenseType () == null ||
			this.getLicenseType ().equals (obj.getLicenseType ()))) return false;

		if (this.getAssignedToUser () != obj.getAssignedToUser () &&
			(this.getAssignedToUser () == null ||
			obj.getAssignedToUser () == null ||
			this.getAssignedToUser ().equals (obj.getAssignedToUser ()))) return false;

		if (this.getAssignedToGroup () != obj.getAssignedToGroup () &&
			(this.getAssignedToGroup () == null ||
			obj.getAssignedToGroup () == null ||
			this.getAssignedToGroup ().equals (obj.getAssignedToGroup ()))) return false;

		if (this.getRegisteredBy () != obj.getRegisteredBy () &&
			(this.getRegisteredBy () == null ||
			obj.getRegisteredBy () == null ||
			this.getRegisteredBy ().equals (obj.getRegisteredBy ()))) return false;

		if (this.getXmlString () != obj.getXmlString () &&
			(this.getXmlString () == null ||
			obj.getXmlString () == null ||
			this.getXmlString ().equals (obj.getXmlString ()))) return false;

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

		System.out.println("AgreementId = "+this.getAgreementId());
		System.out.println("ContentId = "+this.getContentId());
		System.out.println("StartDate = "+this.getStartDate());
		System.out.println("EndDate = "+this.getEndDate());
		System.out.println("UserLicenseLimit = "+this.getUserLicenseLimit());
		System.out.println("GlobalLicenseLimit = "+this.getGlobalLicenseLimit());
		System.out.println("LicenseType = "+this.getLicenseType());
		System.out.println("AssignedToUser = "+this.getAssignedToUser());
		System.out.println("AssignedToGroup = "+this.getAssignedToGroup());
		System.out.println("RegisteredBy = "+this.getRegisteredBy());
		System.out.println("XmlString = "+this.getXmlString());
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
