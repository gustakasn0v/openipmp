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

public class  osmsDvUsersBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int USER_ID
	private Integer m_UserId;
	public Integer getUserId ()
	{return m_UserId;}
	public void setUserId (Integer pUserId)
	{m_UserId = pUserId;}

	//varchar USER_NAME
	private String m_UserName;
	public String getUserName ()
	{return m_UserName;}
	public void setUserName (String pUserName)
	{m_UserName = pUserName;}

	//varchar PASSWORD
	private String m_Password;
	public String getPassword ()
	{return m_Password;}
	public void setPassword (String pPassword)
	{m_Password = pPassword;}

	//varchar SECRET_QUESTION
	private String m_SecretQuestion;
	public String getSecretQuestion ()
	{return m_SecretQuestion;}
	public void setSecretQuestion (String pSecretQuestion)
	{m_SecretQuestion = pSecretQuestion;}

	//varchar SECRET_ANSWER
	private String m_SecretAnswer;
	public String getSecretAnswer ()
	{return m_SecretAnswer;}
	public void setSecretAnswer (String pSecretAnswer)
	{m_SecretAnswer = pSecretAnswer;}

	//varchar SALUTATION
	private String m_Salutation;
	public String getSalutation ()
	{return m_Salutation;}
	public void setSalutation (String pSalutation)
	{m_Salutation = pSalutation;}

	//varchar FIRST_NAME
	private String m_FirstName;
	public String getFirstName ()
	{return m_FirstName;}
	public void setFirstName (String pFirstName)
	{m_FirstName = pFirstName;}

	//varchar LAST_NAME
	private String m_LastName;
	public String getLastName ()
	{return m_LastName;}
	public void setLastName (String pLastName)
	{m_LastName = pLastName;}

	//varchar SUFFIX
	private String m_Suffix;
	public String getSuffix ()
	{return m_Suffix;}
	public void setSuffix (String pSuffix)
	{m_Suffix = pSuffix;}

	//varchar JOB_TITLE
	private String m_JobTitle;
	public String getJobTitle ()
	{return m_JobTitle;}
	public void setJobTitle (String pJobTitle)
	{m_JobTitle = pJobTitle;}

	//varchar EMAIL_ADDRESS
	private String m_EmailAddress;
	public String getEmailAddress ()
	{return m_EmailAddress;}
	public void setEmailAddress (String pEmailAddress)
	{m_EmailAddress = pEmailAddress;}

	//varchar URL
	private String m_Url;
	public String getUrl ()
	{return m_Url;}
	public void setUrl (String pUrl)
	{m_Url = pUrl;}

	//varchar ADDRESS_LINE1
	private String m_AddressLine1;
	public String getAddressLine1 ()
	{return m_AddressLine1;}
	public void setAddressLine1 (String pAddressLine1)
	{m_AddressLine1 = pAddressLine1;}

	//varchar ADDRESS_LINE2
	private String m_AddressLine2;
	public String getAddressLine2 ()
	{return m_AddressLine2;}
	public void setAddressLine2 (String pAddressLine2)
	{m_AddressLine2 = pAddressLine2;}

	//varchar ADDRESS_LINE3
	private String m_AddressLine3;
	public String getAddressLine3 ()
	{return m_AddressLine3;}
	public void setAddressLine3 (String pAddressLine3)
	{m_AddressLine3 = pAddressLine3;}

	//varchar CITY
	private String m_City;
	public String getCity ()
	{return m_City;}
	public void setCity (String pCity)
	{m_City = pCity;}

	//char STATE_CODE
	private String m_StateCode;
	public String getStateCode ()
	{return m_StateCode;}
	public void setStateCode (String pStateCode)
	{m_StateCode = pStateCode;}

	//varchar ZIP_CODE
	private String m_ZipCode;
	public String getZipCode ()
	{return m_ZipCode;}
	public void setZipCode (String pZipCode)
	{m_ZipCode = pZipCode;}

	//char COUNTRY_CODE
	private String m_CountryCode;
	public String getCountryCode ()
	{return m_CountryCode;}
	public void setCountryCode (String pCountryCode)
	{m_CountryCode = pCountryCode;}

	//varchar ATTENTION_TEXT
	private String m_AttentionText;
	public String getAttentionText ()
	{return m_AttentionText;}
	public void setAttentionText (String pAttentionText)
	{m_AttentionText = pAttentionText;}

	//varchar MAIN_PHONE_NUMBER
	private String m_MainPhoneNumber;
	public String getMainPhoneNumber ()
	{return m_MainPhoneNumber;}
	public void setMainPhoneNumber (String pMainPhoneNumber)
	{m_MainPhoneNumber = pMainPhoneNumber;}

	//varchar ALT_PHONE_NUMBER
	private String m_AltPhoneNumber;
	public String getAltPhoneNumber ()
	{return m_AltPhoneNumber;}
	public void setAltPhoneNumber (String pAltPhoneNumber)
	{m_AltPhoneNumber = pAltPhoneNumber;}

	//varchar FAX_PHONE_NUMBER
	private String m_FaxPhoneNumber;
	public String getFaxPhoneNumber ()
	{return m_FaxPhoneNumber;}
	public void setFaxPhoneNumber (String pFaxPhoneNumber)
	{m_FaxPhoneNumber = pFaxPhoneNumber;}

	//varchar ORG_UNIT_NAME
	private String m_OrgUnitName;
	public String getOrgUnitName ()
	{return m_OrgUnitName;}
	public void setOrgUnitName (String pOrgUnitName)
	{m_OrgUnitName = pOrgUnitName;}

	//int ORGANIZATION_ID
	private Integer m_OrganizationId;
	public Integer getOrganizationId ()
	{return m_OrganizationId;}
	public void setOrganizationId (Integer pOrganizationId)
	{m_OrganizationId = pOrganizationId;}

	//int CERTIFICATE_ID
	private Integer m_CertificateId;
	public Integer getCertificateId ()
	{return m_CertificateId;}
	public void setCertificateId (Integer pCertificateId)
	{m_CertificateId = pCertificateId;}

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
	public void copyPropertiesTo (osmsDvUsersBean target)
	{

		target.setUserId (getUserId());
		target.setUserName (getUserName());
		target.setPassword (getPassword());
		target.setSecretQuestion (getSecretQuestion());
		target.setSecretAnswer (getSecretAnswer());
		target.setSalutation (getSalutation());
		target.setFirstName (getFirstName());
		target.setLastName (getLastName());
		target.setSuffix (getSuffix());
		target.setJobTitle (getJobTitle());
		target.setEmailAddress (getEmailAddress());
		target.setUrl (getUrl());
		target.setAddressLine1 (getAddressLine1());
		target.setAddressLine2 (getAddressLine2());
		target.setAddressLine3 (getAddressLine3());
		target.setCity (getCity());
		target.setStateCode (getStateCode());
		target.setZipCode (getZipCode());
		target.setCountryCode (getCountryCode());
		target.setAttentionText (getAttentionText());
		target.setMainPhoneNumber (getMainPhoneNumber());
		target.setAltPhoneNumber (getAltPhoneNumber());
		target.setFaxPhoneNumber (getFaxPhoneNumber());
		target.setOrgUnitName (getOrgUnitName());
		target.setOrganizationId (getOrganizationId());
		target.setCertificateId (getCertificateId());
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
    	if (!(pObj instanceof osmsDvUsersBean)) return false;
	    osmsDvUsersBean obj = (osmsDvUsersBean) pObj;


		if (this.getUserId () != obj.getUserId () &&
			(this.getUserId () == null ||
			obj.getUserId () == null ||
			this.getUserId ().equals (obj.getUserId ()))) return false;

		if (this.getUserName () != obj.getUserName () &&
			(this.getUserName () == null ||
			obj.getUserName () == null ||
			this.getUserName ().equals (obj.getUserName ()))) return false;

		if (this.getPassword () != obj.getPassword () &&
			(this.getPassword () == null ||
			obj.getPassword () == null ||
			this.getPassword ().equals (obj.getPassword ()))) return false;

		if (this.getSecretQuestion () != obj.getSecretQuestion () &&
			(this.getSecretQuestion () == null ||
			obj.getSecretQuestion () == null ||
			this.getSecretQuestion ().equals (obj.getSecretQuestion ()))) return false;

		if (this.getSecretAnswer () != obj.getSecretAnswer () &&
			(this.getSecretAnswer () == null ||
			obj.getSecretAnswer () == null ||
			this.getSecretAnswer ().equals (obj.getSecretAnswer ()))) return false;

		if (this.getSalutation () != obj.getSalutation () &&
			(this.getSalutation () == null ||
			obj.getSalutation () == null ||
			this.getSalutation ().equals (obj.getSalutation ()))) return false;

		if (this.getFirstName () != obj.getFirstName () &&
			(this.getFirstName () == null ||
			obj.getFirstName () == null ||
			this.getFirstName ().equals (obj.getFirstName ()))) return false;

		if (this.getLastName () != obj.getLastName () &&
			(this.getLastName () == null ||
			obj.getLastName () == null ||
			this.getLastName ().equals (obj.getLastName ()))) return false;

		if (this.getSuffix () != obj.getSuffix () &&
			(this.getSuffix () == null ||
			obj.getSuffix () == null ||
			this.getSuffix ().equals (obj.getSuffix ()))) return false;

		if (this.getJobTitle () != obj.getJobTitle () &&
			(this.getJobTitle () == null ||
			obj.getJobTitle () == null ||
			this.getJobTitle ().equals (obj.getJobTitle ()))) return false;

		if (this.getEmailAddress () != obj.getEmailAddress () &&
			(this.getEmailAddress () == null ||
			obj.getEmailAddress () == null ||
			this.getEmailAddress ().equals (obj.getEmailAddress ()))) return false;

		if (this.getUrl () != obj.getUrl () &&
			(this.getUrl () == null ||
			obj.getUrl () == null ||
			this.getUrl ().equals (obj.getUrl ()))) return false;

		if (this.getAddressLine1 () != obj.getAddressLine1 () &&
			(this.getAddressLine1 () == null ||
			obj.getAddressLine1 () == null ||
			this.getAddressLine1 ().equals (obj.getAddressLine1 ()))) return false;

		if (this.getAddressLine2 () != obj.getAddressLine2 () &&
			(this.getAddressLine2 () == null ||
			obj.getAddressLine2 () == null ||
			this.getAddressLine2 ().equals (obj.getAddressLine2 ()))) return false;

		if (this.getAddressLine3 () != obj.getAddressLine3 () &&
			(this.getAddressLine3 () == null ||
			obj.getAddressLine3 () == null ||
			this.getAddressLine3 ().equals (obj.getAddressLine3 ()))) return false;

		if (this.getCity () != obj.getCity () &&
			(this.getCity () == null ||
			obj.getCity () == null ||
			this.getCity ().equals (obj.getCity ()))) return false;

		if (this.getStateCode () != obj.getStateCode () &&
			(this.getStateCode () == null ||
			obj.getStateCode () == null ||
			this.getStateCode ().equals (obj.getStateCode ()))) return false;

		if (this.getZipCode () != obj.getZipCode () &&
			(this.getZipCode () == null ||
			obj.getZipCode () == null ||
			this.getZipCode ().equals (obj.getZipCode ()))) return false;

		if (this.getCountryCode () != obj.getCountryCode () &&
			(this.getCountryCode () == null ||
			obj.getCountryCode () == null ||
			this.getCountryCode ().equals (obj.getCountryCode ()))) return false;

		if (this.getAttentionText () != obj.getAttentionText () &&
			(this.getAttentionText () == null ||
			obj.getAttentionText () == null ||
			this.getAttentionText ().equals (obj.getAttentionText ()))) return false;

		if (this.getMainPhoneNumber () != obj.getMainPhoneNumber () &&
			(this.getMainPhoneNumber () == null ||
			obj.getMainPhoneNumber () == null ||
			this.getMainPhoneNumber ().equals (obj.getMainPhoneNumber ()))) return false;

		if (this.getAltPhoneNumber () != obj.getAltPhoneNumber () &&
			(this.getAltPhoneNumber () == null ||
			obj.getAltPhoneNumber () == null ||
			this.getAltPhoneNumber ().equals (obj.getAltPhoneNumber ()))) return false;

		if (this.getFaxPhoneNumber () != obj.getFaxPhoneNumber () &&
			(this.getFaxPhoneNumber () == null ||
			obj.getFaxPhoneNumber () == null ||
			this.getFaxPhoneNumber ().equals (obj.getFaxPhoneNumber ()))) return false;

		if (this.getOrgUnitName () != obj.getOrgUnitName () &&
			(this.getOrgUnitName () == null ||
			obj.getOrgUnitName () == null ||
			this.getOrgUnitName ().equals (obj.getOrgUnitName ()))) return false;

		if (this.getOrganizationId () != obj.getOrganizationId () &&
			(this.getOrganizationId () == null ||
			obj.getOrganizationId () == null ||
			this.getOrganizationId ().equals (obj.getOrganizationId ()))) return false;

		if (this.getCertificateId () != obj.getCertificateId () &&
			(this.getCertificateId () == null ||
			obj.getCertificateId () == null ||
			this.getCertificateId ().equals (obj.getCertificateId ()))) return false;

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

		System.out.println("UserId = "+this.getUserId());
		System.out.println("UserName = "+this.getUserName());
		System.out.println("Password = "+this.getPassword());
		System.out.println("SecretQuestion = "+this.getSecretQuestion());
		System.out.println("SecretAnswer = "+this.getSecretAnswer());
		System.out.println("Salutation = "+this.getSalutation());
		System.out.println("FirstName = "+this.getFirstName());
		System.out.println("LastName = "+this.getLastName());
		System.out.println("Suffix = "+this.getSuffix());
		System.out.println("JobTitle = "+this.getJobTitle());
		System.out.println("EmailAddress = "+this.getEmailAddress());
		System.out.println("Url = "+this.getUrl());
		System.out.println("AddressLine1 = "+this.getAddressLine1());
		System.out.println("AddressLine2 = "+this.getAddressLine2());
		System.out.println("AddressLine3 = "+this.getAddressLine3());
		System.out.println("City = "+this.getCity());
		System.out.println("StateCode = "+this.getStateCode());
		System.out.println("ZipCode = "+this.getZipCode());
		System.out.println("CountryCode = "+this.getCountryCode());
		System.out.println("AttentionText = "+this.getAttentionText());
		System.out.println("MainPhoneNumber = "+this.getMainPhoneNumber());
		System.out.println("AltPhoneNumber = "+this.getAltPhoneNumber());
		System.out.println("FaxPhoneNumber = "+this.getFaxPhoneNumber());
		System.out.println("OrgUnitName = "+this.getOrgUnitName());
		System.out.println("OrganizationId = "+this.getOrganizationId());
		System.out.println("CertificateId = "+this.getCertificateId());
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
