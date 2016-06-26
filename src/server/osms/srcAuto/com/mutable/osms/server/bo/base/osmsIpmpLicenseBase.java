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

public class osmsIpmpLicenseBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvIpmpLicenseBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsIpmpLicenseBase()
	{m_osmsDvIpmpLicenseBean= new osmsDvIpmpLicenseBean();}
	public osmsIpmpLicenseBase(osmsDvIpmpLicenseBean bean)
	{m_osmsDvIpmpLicenseBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvIpmpLicenseBean m_osmsDvIpmpLicenseBean;
	public osmsDvIpmpLicenseBean getIpmpLicenseBean()
	{return m_osmsDvIpmpLicenseBean;}
	public void setIpmpLicenseBean (osmsDvIpmpLicenseBean bean)
	{m_osmsDvIpmpLicenseBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getLicenseId ()
	{return m_osmsDvIpmpLicenseBean.getLicenseId ();}
	public void setLicenseId (Integer pLicenseId)
	{m_osmsDvIpmpLicenseBean.setLicenseId(pLicenseId);}

	public Integer getCaCertificateId ()
	{return m_osmsDvIpmpLicenseBean.getCaCertificateId ();}
	public void setCaCertificateId (Integer pCaCertificateId)
	{m_osmsDvIpmpLicenseBean.setCaCertificateId(pCaCertificateId);}

	public String getLicenseIdentifier ()
	{return m_osmsDvIpmpLicenseBean.getLicenseIdentifier ();}
	public void setLicenseIdentifier (String pLicenseIdentifier)
	{m_osmsDvIpmpLicenseBean.setLicenseIdentifier(pLicenseIdentifier);}

	public Integer getDigitalItemId ()
	{return m_osmsDvIpmpLicenseBean.getDigitalItemId ();}
	public void setDigitalItemId (Integer pDigitalItemId)
	{m_osmsDvIpmpLicenseBean.setDigitalItemId(pDigitalItemId);}

	public Integer getIssuedToUser ()
	{return m_osmsDvIpmpLicenseBean.getIssuedToUser ();}
	public void setIssuedToUser (Integer pIssuedToUser)
	{m_osmsDvIpmpLicenseBean.setIssuedToUser(pIssuedToUser);}

	public Integer getAgreementId ()
	{return m_osmsDvIpmpLicenseBean.getAgreementId ();}
	public void setAgreementId (Integer pAgreementId)
	{m_osmsDvIpmpLicenseBean.setAgreementId(pAgreementId);}

	public String getLicenseType ()
	{return m_osmsDvIpmpLicenseBean.getLicenseType ();}
	public void setLicenseType (String pLicenseType)
	{m_osmsDvIpmpLicenseBean.setLicenseType(pLicenseType);}

	public String getXmlString ()
	{return m_osmsDvIpmpLicenseBean.getXmlString ();}
	public void setXmlString (String pXmlString)
	{m_osmsDvIpmpLicenseBean.setXmlString(pXmlString);}

	public String getLicenseDigest ()
	{return m_osmsDvIpmpLicenseBean.getLicenseDigest ();}
	public void setLicenseDigest (String pLicenseDigest)
	{m_osmsDvIpmpLicenseBean.setLicenseDigest(pLicenseDigest);}

	public Integer getDigestAlgorithmId ()
	{return m_osmsDvIpmpLicenseBean.getDigestAlgorithmId ();}
	public void setDigestAlgorithmId (Integer pDigestAlgorithmId)
	{m_osmsDvIpmpLicenseBean.setDigestAlgorithmId(pDigestAlgorithmId);}

	public byte[] getLicenseSignature ()
	{return m_osmsDvIpmpLicenseBean.getLicenseSignature ();}
	public void setLicenseSignature (byte[] pLicenseSignature)
	{m_osmsDvIpmpLicenseBean.setLicenseSignature(pLicenseSignature);}

	public Integer getSigAlgorithmId ()
	{return m_osmsDvIpmpLicenseBean.getSigAlgorithmId ();}
	public void setSigAlgorithmId (Integer pSigAlgorithmId)
	{m_osmsDvIpmpLicenseBean.setSigAlgorithmId(pSigAlgorithmId);}

	public String getMaintenanceFlag ()
	{return m_osmsDvIpmpLicenseBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvIpmpLicenseBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvIpmpLicenseBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvIpmpLicenseBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvIpmpLicenseBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvIpmpLicenseBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvIpmpLicenseBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvIpmpLicenseBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvIpmpLicenseBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvIpmpLicenseBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvIpmpLicenseBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
