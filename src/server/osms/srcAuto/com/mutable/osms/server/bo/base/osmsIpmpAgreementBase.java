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

public class osmsIpmpAgreementBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvIpmpAgreementBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsIpmpAgreementBase()
	{m_osmsDvIpmpAgreementBean= new osmsDvIpmpAgreementBean();}
	public osmsIpmpAgreementBase(osmsDvIpmpAgreementBean bean)
	{m_osmsDvIpmpAgreementBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvIpmpAgreementBean m_osmsDvIpmpAgreementBean;
	public osmsDvIpmpAgreementBean getIpmpAgreementBean()
	{return m_osmsDvIpmpAgreementBean;}
	public void setIpmpAgreementBean (osmsDvIpmpAgreementBean bean)
	{m_osmsDvIpmpAgreementBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getAgreementId ()
	{return m_osmsDvIpmpAgreementBean.getAgreementId ();}
	public void setAgreementId (Integer pAgreementId)
	{m_osmsDvIpmpAgreementBean.setAgreementId(pAgreementId);}

	public Integer getContentId ()
	{return m_osmsDvIpmpAgreementBean.getContentId ();}
	public void setContentId (Integer pContentId)
	{m_osmsDvIpmpAgreementBean.setContentId(pContentId);}

	public Timestamp getStartDate ()
	{return m_osmsDvIpmpAgreementBean.getStartDate ();}
	public void setStartDate (Timestamp pStartDate)
	{m_osmsDvIpmpAgreementBean.setStartDate(pStartDate);}

	public Timestamp getEndDate ()
	{return m_osmsDvIpmpAgreementBean.getEndDate ();}
	public void setEndDate (Timestamp pEndDate)
	{m_osmsDvIpmpAgreementBean.setEndDate(pEndDate);}

	public Integer getUserLicenseLimit ()
	{return m_osmsDvIpmpAgreementBean.getUserLicenseLimit ();}
	public void setUserLicenseLimit (Integer pUserLicenseLimit)
	{m_osmsDvIpmpAgreementBean.setUserLicenseLimit(pUserLicenseLimit);}

	public Integer getGlobalLicenseLimit ()
	{return m_osmsDvIpmpAgreementBean.getGlobalLicenseLimit ();}
	public void setGlobalLicenseLimit (Integer pGlobalLicenseLimit)
	{m_osmsDvIpmpAgreementBean.setGlobalLicenseLimit(pGlobalLicenseLimit);}

	public String getLicenseType ()
	{return m_osmsDvIpmpAgreementBean.getLicenseType ();}
	public void setLicenseType (String pLicenseType)
	{m_osmsDvIpmpAgreementBean.setLicenseType(pLicenseType);}

	public Integer getAssignedToUser ()
	{return m_osmsDvIpmpAgreementBean.getAssignedToUser ();}
	public void setAssignedToUser (Integer pAssignedToUser)
	{m_osmsDvIpmpAgreementBean.setAssignedToUser(pAssignedToUser);}

	public Integer getAssignedToGroup ()
	{return m_osmsDvIpmpAgreementBean.getAssignedToGroup ();}
	public void setAssignedToGroup (Integer pAssignedToGroup)
	{m_osmsDvIpmpAgreementBean.setAssignedToGroup(pAssignedToGroup);}

	public Integer getRegisteredBy ()
	{return m_osmsDvIpmpAgreementBean.getRegisteredBy ();}
	public void setRegisteredBy (Integer pRegisteredBy)
	{m_osmsDvIpmpAgreementBean.setRegisteredBy(pRegisteredBy);}

	public String getXmlString ()
	{return m_osmsDvIpmpAgreementBean.getXmlString ();}
	public void setXmlString (String pXmlString)
	{m_osmsDvIpmpAgreementBean.setXmlString(pXmlString);}

	public String getMaintenanceFlag ()
	{return m_osmsDvIpmpAgreementBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvIpmpAgreementBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvIpmpAgreementBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvIpmpAgreementBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvIpmpAgreementBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvIpmpAgreementBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvIpmpAgreementBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvIpmpAgreementBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvIpmpAgreementBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvIpmpAgreementBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvIpmpAgreementBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
