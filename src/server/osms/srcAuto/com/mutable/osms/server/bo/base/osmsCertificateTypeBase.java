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

public class osmsCertificateTypeBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvCertificateTypeBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsCertificateTypeBase()
	{m_osmsDvCertificateTypeBean= new osmsDvCertificateTypeBean();}
	public osmsCertificateTypeBase(osmsDvCertificateTypeBean bean)
	{m_osmsDvCertificateTypeBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvCertificateTypeBean m_osmsDvCertificateTypeBean;
	public osmsDvCertificateTypeBean getCertificateTypeBean()
	{return m_osmsDvCertificateTypeBean;}
	public void setCertificateTypeBean (osmsDvCertificateTypeBean bean)
	{m_osmsDvCertificateTypeBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public String getCertificateTypeCode ()
	{return m_osmsDvCertificateTypeBean.getCertificateTypeCode ();}
	public void setCertificateTypeCode (String pCertificateTypeCode)
	{m_osmsDvCertificateTypeBean.setCertificateTypeCode(pCertificateTypeCode);}

	public String getDescription ()
	{return m_osmsDvCertificateTypeBean.getDescription ();}
	public void setDescription (String pDescription)
	{m_osmsDvCertificateTypeBean.setDescription(pDescription);}

	public Integer getDefaultValidityDays ()
	{return m_osmsDvCertificateTypeBean.getDefaultValidityDays ();}
	public void setDefaultValidityDays (Integer pDefaultValidityDays)
	{m_osmsDvCertificateTypeBean.setDefaultValidityDays(pDefaultValidityDays);}

	public String getMaintenanceFlag ()
	{return m_osmsDvCertificateTypeBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvCertificateTypeBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvCertificateTypeBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvCertificateTypeBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvCertificateTypeBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvCertificateTypeBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvCertificateTypeBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvCertificateTypeBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvCertificateTypeBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvCertificateTypeBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvCertificateTypeBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
