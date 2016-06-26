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

public class osmsUsersBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvUsersBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsUsersBase()
	{m_osmsDvUsersBean= new osmsDvUsersBean();}
	public osmsUsersBase(osmsDvUsersBean bean)
	{m_osmsDvUsersBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvUsersBean m_osmsDvUsersBean;
	public osmsDvUsersBean getUsersBean()
	{return m_osmsDvUsersBean;}
	public void setUsersBean (osmsDvUsersBean bean)
	{m_osmsDvUsersBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getUserId ()
	{return m_osmsDvUsersBean.getUserId ();}
	public void setUserId (Integer pUserId)
	{m_osmsDvUsersBean.setUserId(pUserId);}

	public String getUserName ()
	{return m_osmsDvUsersBean.getUserName ();}
	public void setUserName (String pUserName)
	{m_osmsDvUsersBean.setUserName(pUserName);}

	public String getPassword ()
	{return m_osmsDvUsersBean.getPassword ();}
	public void setPassword (String pPassword)
	{m_osmsDvUsersBean.setPassword(pPassword);}

	public String getSecretQuestion ()
	{return m_osmsDvUsersBean.getSecretQuestion ();}
	public void setSecretQuestion (String pSecretQuestion)
	{m_osmsDvUsersBean.setSecretQuestion(pSecretQuestion);}

	public String getSecretAnswer ()
	{return m_osmsDvUsersBean.getSecretAnswer ();}
	public void setSecretAnswer (String pSecretAnswer)
	{m_osmsDvUsersBean.setSecretAnswer(pSecretAnswer);}

	public String getSalutation ()
	{return m_osmsDvUsersBean.getSalutation ();}
	public void setSalutation (String pSalutation)
	{m_osmsDvUsersBean.setSalutation(pSalutation);}

	public String getFirstName ()
	{return m_osmsDvUsersBean.getFirstName ();}
	public void setFirstName (String pFirstName)
	{m_osmsDvUsersBean.setFirstName(pFirstName);}

	public String getLastName ()
	{return m_osmsDvUsersBean.getLastName ();}
	public void setLastName (String pLastName)
	{m_osmsDvUsersBean.setLastName(pLastName);}

	public String getSuffix ()
	{return m_osmsDvUsersBean.getSuffix ();}
	public void setSuffix (String pSuffix)
	{m_osmsDvUsersBean.setSuffix(pSuffix);}

	public String getJobTitle ()
	{return m_osmsDvUsersBean.getJobTitle ();}
	public void setJobTitle (String pJobTitle)
	{m_osmsDvUsersBean.setJobTitle(pJobTitle);}

	public String getEmailAddress ()
	{return m_osmsDvUsersBean.getEmailAddress ();}
	public void setEmailAddress (String pEmailAddress)
	{m_osmsDvUsersBean.setEmailAddress(pEmailAddress);}

	public String getUrl ()
	{return m_osmsDvUsersBean.getUrl ();}
	public void setUrl (String pUrl)
	{m_osmsDvUsersBean.setUrl(pUrl);}

	public String getAddressLine1 ()
	{return m_osmsDvUsersBean.getAddressLine1 ();}
	public void setAddressLine1 (String pAddressLine1)
	{m_osmsDvUsersBean.setAddressLine1(pAddressLine1);}

	public String getAddressLine2 ()
	{return m_osmsDvUsersBean.getAddressLine2 ();}
	public void setAddressLine2 (String pAddressLine2)
	{m_osmsDvUsersBean.setAddressLine2(pAddressLine2);}

	public String getAddressLine3 ()
	{return m_osmsDvUsersBean.getAddressLine3 ();}
	public void setAddressLine3 (String pAddressLine3)
	{m_osmsDvUsersBean.setAddressLine3(pAddressLine3);}

	public String getCity ()
	{return m_osmsDvUsersBean.getCity ();}
	public void setCity (String pCity)
	{m_osmsDvUsersBean.setCity(pCity);}

	public String getStateCode ()
	{return m_osmsDvUsersBean.getStateCode ();}
	public void setStateCode (String pStateCode)
	{m_osmsDvUsersBean.setStateCode(pStateCode);}

	public String getZipCode ()
	{return m_osmsDvUsersBean.getZipCode ();}
	public void setZipCode (String pZipCode)
	{m_osmsDvUsersBean.setZipCode(pZipCode);}

	public String getCountryCode ()
	{return m_osmsDvUsersBean.getCountryCode ();}
	public void setCountryCode (String pCountryCode)
	{m_osmsDvUsersBean.setCountryCode(pCountryCode);}

	public String getAttentionText ()
	{return m_osmsDvUsersBean.getAttentionText ();}
	public void setAttentionText (String pAttentionText)
	{m_osmsDvUsersBean.setAttentionText(pAttentionText);}

	public String getMainPhoneNumber ()
	{return m_osmsDvUsersBean.getMainPhoneNumber ();}
	public void setMainPhoneNumber (String pMainPhoneNumber)
	{m_osmsDvUsersBean.setMainPhoneNumber(pMainPhoneNumber);}

	public String getAltPhoneNumber ()
	{return m_osmsDvUsersBean.getAltPhoneNumber ();}
	public void setAltPhoneNumber (String pAltPhoneNumber)
	{m_osmsDvUsersBean.setAltPhoneNumber(pAltPhoneNumber);}

	public String getFaxPhoneNumber ()
	{return m_osmsDvUsersBean.getFaxPhoneNumber ();}
	public void setFaxPhoneNumber (String pFaxPhoneNumber)
	{m_osmsDvUsersBean.setFaxPhoneNumber(pFaxPhoneNumber);}

	public String getOrgUnitName ()
	{return m_osmsDvUsersBean.getOrgUnitName ();}
	public void setOrgUnitName (String pOrgUnitName)
	{m_osmsDvUsersBean.setOrgUnitName(pOrgUnitName);}

	public Integer getOrganizationId ()
	{return m_osmsDvUsersBean.getOrganizationId ();}
	public void setOrganizationId (Integer pOrganizationId)
	{m_osmsDvUsersBean.setOrganizationId(pOrganizationId);}

	public Integer getCertificateId ()
	{return m_osmsDvUsersBean.getCertificateId ();}
	public void setCertificateId (Integer pCertificateId)
	{m_osmsDvUsersBean.setCertificateId(pCertificateId);}

	public String getStatusFlag ()
	{return m_osmsDvUsersBean.getStatusFlag ();}
	public void setStatusFlag (String pStatusFlag)
	{m_osmsDvUsersBean.setStatusFlag(pStatusFlag);}

	public String getMaintenanceFlag ()
	{return m_osmsDvUsersBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvUsersBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvUsersBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvUsersBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvUsersBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvUsersBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvUsersBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvUsersBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvUsersBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvUsersBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvUsersBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
