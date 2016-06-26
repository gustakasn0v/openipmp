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

public class  osmsDvContentBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int CONTENT_ID
	private Integer m_ContentId;
	public Integer getContentId ()
	{return m_ContentId;}
	public void setContentId (Integer pContentId)
	{m_ContentId = pContentId;}

	//varchar IDENTIFIER_TYPE_CODE
	private String m_IdentifierTypeCode;
	public String getIdentifierTypeCode ()
	{return m_IdentifierTypeCode;}
	public void setIdentifierTypeCode (String pIdentifierTypeCode)
	{m_IdentifierTypeCode = pIdentifierTypeCode;}

	//varchar PRIMARY_IDENTIFIER
	private String m_PrimaryIdentifier;
	public String getPrimaryIdentifier ()
	{return m_PrimaryIdentifier;}
	public void setPrimaryIdentifier (String pPrimaryIdentifier)
	{m_PrimaryIdentifier = pPrimaryIdentifier;}

	//varchar PRIMARY_ARTIST
	private String m_PrimaryArtist;
	public String getPrimaryArtist ()
	{return m_PrimaryArtist;}
	public void setPrimaryArtist (String pPrimaryArtist)
	{m_PrimaryArtist = pPrimaryArtist;}

	//varchar PRIMARY_TITLE
	private String m_PrimaryTitle;
	public String getPrimaryTitle ()
	{return m_PrimaryTitle;}
	public void setPrimaryTitle (String pPrimaryTitle)
	{m_PrimaryTitle = pPrimaryTitle;}

	//datetime RELEASE_DATE
	private Timestamp m_ReleaseDate;
	public Timestamp getReleaseDate ()
	{return m_ReleaseDate;}
	public void setReleaseDate (Timestamp pReleaseDate)
	{m_ReleaseDate = pReleaseDate;}

	//datetime LICENSE_BEGIN_DATE
	private Timestamp m_LicenseBeginDate;
	public Timestamp getLicenseBeginDate ()
	{return m_LicenseBeginDate;}
	public void setLicenseBeginDate (Timestamp pLicenseBeginDate)
	{m_LicenseBeginDate = pLicenseBeginDate;}

	//varchar LICENSE_TYPE
	private String m_LicenseType;
	public String getLicenseType ()
	{return m_LicenseType;}
	public void setLicenseType (String pLicenseType)
	{m_LicenseType = pLicenseType;}

	//int REGISTERED_BY
	private Integer m_RegisteredBy;
	public Integer getRegisteredBy ()
	{return m_RegisteredBy;}
	public void setRegisteredBy (Integer pRegisteredBy)
	{m_RegisteredBy = pRegisteredBy;}

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
	public void copyPropertiesTo (osmsDvContentBean target)
	{

		target.setContentId (getContentId());
		target.setIdentifierTypeCode (getIdentifierTypeCode());
		target.setPrimaryIdentifier (getPrimaryIdentifier());
		target.setPrimaryArtist (getPrimaryArtist());
		target.setPrimaryTitle (getPrimaryTitle());
		target.setReleaseDate (getReleaseDate());
		target.setLicenseBeginDate (getLicenseBeginDate());
		target.setLicenseType (getLicenseType());
		target.setRegisteredBy (getRegisteredBy());
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
    	if (!(pObj instanceof osmsDvContentBean)) return false;
	    osmsDvContentBean obj = (osmsDvContentBean) pObj;


		if (this.getContentId () != obj.getContentId () &&
			(this.getContentId () == null ||
			obj.getContentId () == null ||
			this.getContentId ().equals (obj.getContentId ()))) return false;

		if (this.getIdentifierTypeCode () != obj.getIdentifierTypeCode () &&
			(this.getIdentifierTypeCode () == null ||
			obj.getIdentifierTypeCode () == null ||
			this.getIdentifierTypeCode ().equals (obj.getIdentifierTypeCode ()))) return false;

		if (this.getPrimaryIdentifier () != obj.getPrimaryIdentifier () &&
			(this.getPrimaryIdentifier () == null ||
			obj.getPrimaryIdentifier () == null ||
			this.getPrimaryIdentifier ().equals (obj.getPrimaryIdentifier ()))) return false;

		if (this.getPrimaryArtist () != obj.getPrimaryArtist () &&
			(this.getPrimaryArtist () == null ||
			obj.getPrimaryArtist () == null ||
			this.getPrimaryArtist ().equals (obj.getPrimaryArtist ()))) return false;

		if (this.getPrimaryTitle () != obj.getPrimaryTitle () &&
			(this.getPrimaryTitle () == null ||
			obj.getPrimaryTitle () == null ||
			this.getPrimaryTitle ().equals (obj.getPrimaryTitle ()))) return false;

		if (this.getReleaseDate () != obj.getReleaseDate () &&
			(this.getReleaseDate () == null ||
			obj.getReleaseDate () == null ||
			this.getReleaseDate ().equals (obj.getReleaseDate ()))) return false;

		if (this.getLicenseBeginDate () != obj.getLicenseBeginDate () &&
			(this.getLicenseBeginDate () == null ||
			obj.getLicenseBeginDate () == null ||
			this.getLicenseBeginDate ().equals (obj.getLicenseBeginDate ()))) return false;

		if (this.getLicenseType () != obj.getLicenseType () &&
			(this.getLicenseType () == null ||
			obj.getLicenseType () == null ||
			this.getLicenseType ().equals (obj.getLicenseType ()))) return false;

		if (this.getRegisteredBy () != obj.getRegisteredBy () &&
			(this.getRegisteredBy () == null ||
			obj.getRegisteredBy () == null ||
			this.getRegisteredBy ().equals (obj.getRegisteredBy ()))) return false;

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

		System.out.println("ContentId = "+this.getContentId());
		System.out.println("IdentifierTypeCode = "+this.getIdentifierTypeCode());
		System.out.println("PrimaryIdentifier = "+this.getPrimaryIdentifier());
		System.out.println("PrimaryArtist = "+this.getPrimaryArtist());
		System.out.println("PrimaryTitle = "+this.getPrimaryTitle());
		System.out.println("ReleaseDate = "+this.getReleaseDate());
		System.out.println("LicenseBeginDate = "+this.getLicenseBeginDate());
		System.out.println("LicenseType = "+this.getLicenseType());
		System.out.println("RegisteredBy = "+this.getRegisteredBy());
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
