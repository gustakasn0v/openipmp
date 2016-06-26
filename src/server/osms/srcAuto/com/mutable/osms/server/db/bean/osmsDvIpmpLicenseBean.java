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

public class  osmsDvIpmpLicenseBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int LICENSE_ID
	private Integer m_LicenseId;
	public Integer getLicenseId ()
	{return m_LicenseId;}
	public void setLicenseId (Integer pLicenseId)
	{m_LicenseId = pLicenseId;}

	//int CA_CERTIFICATE_ID
	private Integer m_CaCertificateId;
	public Integer getCaCertificateId ()
	{return m_CaCertificateId;}
	public void setCaCertificateId (Integer pCaCertificateId)
	{m_CaCertificateId = pCaCertificateId;}

	//varchar LICENSE_IDENTIFIER
	private String m_LicenseIdentifier;
	public String getLicenseIdentifier ()
	{return m_LicenseIdentifier;}
	public void setLicenseIdentifier (String pLicenseIdentifier)
	{m_LicenseIdentifier = pLicenseIdentifier;}

	//int DIGITAL_ITEM_ID
	private Integer m_DigitalItemId;
	public Integer getDigitalItemId ()
	{return m_DigitalItemId;}
	public void setDigitalItemId (Integer pDigitalItemId)
	{m_DigitalItemId = pDigitalItemId;}

	//int ISSUED_TO_USER
	private Integer m_IssuedToUser;
	public Integer getIssuedToUser ()
	{return m_IssuedToUser;}
	public void setIssuedToUser (Integer pIssuedToUser)
	{m_IssuedToUser = pIssuedToUser;}

	//int AGREEMENT_ID
	private Integer m_AgreementId;
	public Integer getAgreementId ()
	{return m_AgreementId;}
	public void setAgreementId (Integer pAgreementId)
	{m_AgreementId = pAgreementId;}

	//varchar LICENSE_TYPE
	private String m_LicenseType;
	public String getLicenseType ()
	{return m_LicenseType;}
	public void setLicenseType (String pLicenseType)
	{m_LicenseType = pLicenseType;}

	//text XML_STRING
	private String m_XmlString;
	public String getXmlString ()
	{return m_XmlString;}
	public void setXmlString (String pXmlString)
	{m_XmlString = pXmlString;}

	//varchar LICENSE_DIGEST
	private String m_LicenseDigest;
	public String getLicenseDigest ()
	{return m_LicenseDigest;}
	public void setLicenseDigest (String pLicenseDigest)
	{m_LicenseDigest = pLicenseDigest;}

	//int DIGEST_ALGORITHM_ID
	private Integer m_DigestAlgorithmId;
	public Integer getDigestAlgorithmId ()
	{return m_DigestAlgorithmId;}
	public void setDigestAlgorithmId (Integer pDigestAlgorithmId)
	{m_DigestAlgorithmId = pDigestAlgorithmId;}

	//blob LICENSE_SIGNATURE
	private byte[] m_LicenseSignature;
	public byte[] getLicenseSignature ()
	{return m_LicenseSignature;}
	public void setLicenseSignature (byte[] pLicenseSignature)
	{m_LicenseSignature = pLicenseSignature;}

	//int SIG_ALGORITHM_ID
	private Integer m_SigAlgorithmId;
	public Integer getSigAlgorithmId ()
	{return m_SigAlgorithmId;}
	public void setSigAlgorithmId (Integer pSigAlgorithmId)
	{m_SigAlgorithmId = pSigAlgorithmId;}

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
	public void copyPropertiesTo (osmsDvIpmpLicenseBean target)
	{

		target.setLicenseId (getLicenseId());
		target.setCaCertificateId (getCaCertificateId());
		target.setLicenseIdentifier (getLicenseIdentifier());
		target.setDigitalItemId (getDigitalItemId());
		target.setIssuedToUser (getIssuedToUser());
		target.setAgreementId (getAgreementId());
		target.setLicenseType (getLicenseType());
		target.setXmlString (getXmlString());
		target.setLicenseDigest (getLicenseDigest());
		target.setDigestAlgorithmId (getDigestAlgorithmId());
		target.setLicenseSignature (getLicenseSignature());
		target.setSigAlgorithmId (getSigAlgorithmId());
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
    	if (!(pObj instanceof osmsDvIpmpLicenseBean)) return false;
	    osmsDvIpmpLicenseBean obj = (osmsDvIpmpLicenseBean) pObj;


		if (this.getLicenseId () != obj.getLicenseId () &&
			(this.getLicenseId () == null ||
			obj.getLicenseId () == null ||
			this.getLicenseId ().equals (obj.getLicenseId ()))) return false;

		if (this.getCaCertificateId () != obj.getCaCertificateId () &&
			(this.getCaCertificateId () == null ||
			obj.getCaCertificateId () == null ||
			this.getCaCertificateId ().equals (obj.getCaCertificateId ()))) return false;

		if (this.getLicenseIdentifier () != obj.getLicenseIdentifier () &&
			(this.getLicenseIdentifier () == null ||
			obj.getLicenseIdentifier () == null ||
			this.getLicenseIdentifier ().equals (obj.getLicenseIdentifier ()))) return false;

		if (this.getDigitalItemId () != obj.getDigitalItemId () &&
			(this.getDigitalItemId () == null ||
			obj.getDigitalItemId () == null ||
			this.getDigitalItemId ().equals (obj.getDigitalItemId ()))) return false;

		if (this.getIssuedToUser () != obj.getIssuedToUser () &&
			(this.getIssuedToUser () == null ||
			obj.getIssuedToUser () == null ||
			this.getIssuedToUser ().equals (obj.getIssuedToUser ()))) return false;

		if (this.getAgreementId () != obj.getAgreementId () &&
			(this.getAgreementId () == null ||
			obj.getAgreementId () == null ||
			this.getAgreementId ().equals (obj.getAgreementId ()))) return false;

		if (this.getLicenseType () != obj.getLicenseType () &&
			(this.getLicenseType () == null ||
			obj.getLicenseType () == null ||
			this.getLicenseType ().equals (obj.getLicenseType ()))) return false;

		if (this.getXmlString () != obj.getXmlString () &&
			(this.getXmlString () == null ||
			obj.getXmlString () == null ||
			this.getXmlString ().equals (obj.getXmlString ()))) return false;

		if (this.getLicenseDigest () != obj.getLicenseDigest () &&
			(this.getLicenseDigest () == null ||
			obj.getLicenseDigest () == null ||
			this.getLicenseDigest ().equals (obj.getLicenseDigest ()))) return false;

		if (this.getDigestAlgorithmId () != obj.getDigestAlgorithmId () &&
			(this.getDigestAlgorithmId () == null ||
			obj.getDigestAlgorithmId () == null ||
			this.getDigestAlgorithmId ().equals (obj.getDigestAlgorithmId ()))) return false;

		if (this.getLicenseSignature () != obj.getLicenseSignature () &&
			(this.getLicenseSignature () == null ||
			obj.getLicenseSignature () == null ||
			this.getLicenseSignature ().equals (obj.getLicenseSignature ()))) return false;

		if (this.getSigAlgorithmId () != obj.getSigAlgorithmId () &&
			(this.getSigAlgorithmId () == null ||
			obj.getSigAlgorithmId () == null ||
			this.getSigAlgorithmId ().equals (obj.getSigAlgorithmId ()))) return false;

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

		System.out.println("LicenseId = "+this.getLicenseId());
		System.out.println("CaCertificateId = "+this.getCaCertificateId());
		System.out.println("LicenseIdentifier = "+this.getLicenseIdentifier());
		System.out.println("DigitalItemId = "+this.getDigitalItemId());
		System.out.println("IssuedToUser = "+this.getIssuedToUser());
		System.out.println("AgreementId = "+this.getAgreementId());
		System.out.println("LicenseType = "+this.getLicenseType());
		System.out.println("XmlString = "+this.getXmlString());
		System.out.println("LicenseDigest = "+this.getLicenseDigest());
		System.out.println("DigestAlgorithmId = "+this.getDigestAlgorithmId());
		System.out.println("LicenseSignature = "+this.getLicenseSignature());
		System.out.println("SigAlgorithmId = "+this.getSigAlgorithmId());
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
