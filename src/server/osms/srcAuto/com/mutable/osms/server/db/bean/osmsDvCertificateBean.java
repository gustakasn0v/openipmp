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

public class  osmsDvCertificateBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int CERTIFICATE_ID
	private Integer m_CertificateId;
	public Integer getCertificateId ()
	{return m_CertificateId;}
	public void setCertificateId (Integer pCertificateId)
	{m_CertificateId = pCertificateId;}

	//char CERTIFICATE_TYPE_CODE
	private String m_CertificateTypeCode;
	public String getCertificateTypeCode ()
	{return m_CertificateTypeCode;}
	public void setCertificateTypeCode (String pCertificateTypeCode)
	{m_CertificateTypeCode = pCertificateTypeCode;}

	//int CA_CERTIFICATE_ID
	private Integer m_CaCertificateId;
	public Integer getCaCertificateId ()
	{return m_CaCertificateId;}
	public void setCaCertificateId (Integer pCaCertificateId)
	{m_CaCertificateId = pCaCertificateId;}

	//int VERSION
	private Integer m_Version;
	public Integer getVersion ()
	{return m_Version;}
	public void setVersion (Integer pVersion)
	{m_Version = pVersion;}

	//varchar SERIAL_NUM
	private String m_SerialNum;
	public String getSerialNum ()
	{return m_SerialNum;}
	public void setSerialNum (String pSerialNum)
	{m_SerialNum = pSerialNum;}

	//datetime NOT_VALID_BEFORE_DT
	private Timestamp m_NotValidBeforeDt;
	public Timestamp getNotValidBeforeDt ()
	{return m_NotValidBeforeDt;}
	public void setNotValidBeforeDt (Timestamp pNotValidBeforeDt)
	{m_NotValidBeforeDt = pNotValidBeforeDt;}

	//datetime NOT_VALID_AFTER_DT
	private Timestamp m_NotValidAfterDt;
	public Timestamp getNotValidAfterDt ()
	{return m_NotValidAfterDt;}
	public void setNotValidAfterDt (Timestamp pNotValidAfterDt)
	{m_NotValidAfterDt = pNotValidAfterDt;}

	//blob CERTIFICATE
	private byte[] m_Certificate;
	public byte[] getCertificate ()
	{return m_Certificate;}
	public void setCertificate (byte[] pCertificate)
	{m_Certificate = pCertificate;}

	//blob PUBLIC_KEY
	private byte[] m_PublicKey;
	public byte[] getPublicKey ()
	{return m_PublicKey;}
	public void setPublicKey (byte[] pPublicKey)
	{m_PublicKey = pPublicKey;}

	//blob ENCRYPTED_PRIVATE_KEY
	private byte[] m_EncryptedPrivateKey;
	public byte[] getEncryptedPrivateKey ()
	{return m_EncryptedPrivateKey;}
	public void setEncryptedPrivateKey (byte[] pEncryptedPrivateKey)
	{m_EncryptedPrivateKey = pEncryptedPrivateKey;}

	//int ENCRYPTION_KEY_ID
	private Integer m_EncryptionKeyId;
	public Integer getEncryptionKeyId ()
	{return m_EncryptionKeyId;}
	public void setEncryptionKeyId (Integer pEncryptionKeyId)
	{m_EncryptionKeyId = pEncryptionKeyId;}

	//int ALGORITHM_ID
	private Integer m_AlgorithmId;
	public Integer getAlgorithmId ()
	{return m_AlgorithmId;}
	public void setAlgorithmId (Integer pAlgorithmId)
	{m_AlgorithmId = pAlgorithmId;}

	//int REVOCATION_ID
	private Integer m_RevocationId;
	public Integer getRevocationId ()
	{return m_RevocationId;}
	public void setRevocationId (Integer pRevocationId)
	{m_RevocationId = pRevocationId;}

	//char ACTION_CODE
	private String m_ActionCode;
	public String getActionCode ()
	{return m_ActionCode;}
	public void setActionCode (String pActionCode)
	{m_ActionCode = pActionCode;}

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
	public void copyPropertiesTo (osmsDvCertificateBean target)
	{

		target.setCertificateId (getCertificateId());
		target.setCertificateTypeCode (getCertificateTypeCode());
		target.setCaCertificateId (getCaCertificateId());
		target.setVersion (getVersion());
		target.setSerialNum (getSerialNum());
		target.setNotValidBeforeDt (getNotValidBeforeDt());
		target.setNotValidAfterDt (getNotValidAfterDt());
		target.setCertificate (getCertificate());
		target.setPublicKey (getPublicKey());
		target.setEncryptedPrivateKey (getEncryptedPrivateKey());
		target.setEncryptionKeyId (getEncryptionKeyId());
		target.setAlgorithmId (getAlgorithmId());
		target.setRevocationId (getRevocationId());
		target.setActionCode (getActionCode());
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
    	if (!(pObj instanceof osmsDvCertificateBean)) return false;
	    osmsDvCertificateBean obj = (osmsDvCertificateBean) pObj;


		if (this.getCertificateId () != obj.getCertificateId () &&
			(this.getCertificateId () == null ||
			obj.getCertificateId () == null ||
			this.getCertificateId ().equals (obj.getCertificateId ()))) return false;

		if (this.getCertificateTypeCode () != obj.getCertificateTypeCode () &&
			(this.getCertificateTypeCode () == null ||
			obj.getCertificateTypeCode () == null ||
			this.getCertificateTypeCode ().equals (obj.getCertificateTypeCode ()))) return false;

		if (this.getCaCertificateId () != obj.getCaCertificateId () &&
			(this.getCaCertificateId () == null ||
			obj.getCaCertificateId () == null ||
			this.getCaCertificateId ().equals (obj.getCaCertificateId ()))) return false;

		if (this.getVersion () != obj.getVersion () &&
			(this.getVersion () == null ||
			obj.getVersion () == null ||
			this.getVersion ().equals (obj.getVersion ()))) return false;

		if (this.getSerialNum () != obj.getSerialNum () &&
			(this.getSerialNum () == null ||
			obj.getSerialNum () == null ||
			this.getSerialNum ().equals (obj.getSerialNum ()))) return false;

		if (this.getNotValidBeforeDt () != obj.getNotValidBeforeDt () &&
			(this.getNotValidBeforeDt () == null ||
			obj.getNotValidBeforeDt () == null ||
			this.getNotValidBeforeDt ().equals (obj.getNotValidBeforeDt ()))) return false;

		if (this.getNotValidAfterDt () != obj.getNotValidAfterDt () &&
			(this.getNotValidAfterDt () == null ||
			obj.getNotValidAfterDt () == null ||
			this.getNotValidAfterDt ().equals (obj.getNotValidAfterDt ()))) return false;

		if (this.getCertificate () != obj.getCertificate () &&
			(this.getCertificate () == null ||
			obj.getCertificate () == null ||
			this.getCertificate ().equals (obj.getCertificate ()))) return false;

		if (this.getPublicKey () != obj.getPublicKey () &&
			(this.getPublicKey () == null ||
			obj.getPublicKey () == null ||
			this.getPublicKey ().equals (obj.getPublicKey ()))) return false;

		if (this.getEncryptedPrivateKey () != obj.getEncryptedPrivateKey () &&
			(this.getEncryptedPrivateKey () == null ||
			obj.getEncryptedPrivateKey () == null ||
			this.getEncryptedPrivateKey ().equals (obj.getEncryptedPrivateKey ()))) return false;

		if (this.getEncryptionKeyId () != obj.getEncryptionKeyId () &&
			(this.getEncryptionKeyId () == null ||
			obj.getEncryptionKeyId () == null ||
			this.getEncryptionKeyId ().equals (obj.getEncryptionKeyId ()))) return false;

		if (this.getAlgorithmId () != obj.getAlgorithmId () &&
			(this.getAlgorithmId () == null ||
			obj.getAlgorithmId () == null ||
			this.getAlgorithmId ().equals (obj.getAlgorithmId ()))) return false;

		if (this.getRevocationId () != obj.getRevocationId () &&
			(this.getRevocationId () == null ||
			obj.getRevocationId () == null ||
			this.getRevocationId ().equals (obj.getRevocationId ()))) return false;

		if (this.getActionCode () != obj.getActionCode () &&
			(this.getActionCode () == null ||
			obj.getActionCode () == null ||
			this.getActionCode ().equals (obj.getActionCode ()))) return false;

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

		System.out.println("CertificateId = "+this.getCertificateId());
		System.out.println("CertificateTypeCode = "+this.getCertificateTypeCode());
		System.out.println("CaCertificateId = "+this.getCaCertificateId());
		System.out.println("Version = "+this.getVersion());
		System.out.println("SerialNum = "+this.getSerialNum());
		System.out.println("NotValidBeforeDt = "+this.getNotValidBeforeDt());
		System.out.println("NotValidAfterDt = "+this.getNotValidAfterDt());
		System.out.println("Certificate = "+this.getCertificate());
		System.out.println("PublicKey = "+this.getPublicKey());
		System.out.println("EncryptedPrivateKey = "+this.getEncryptedPrivateKey());
		System.out.println("EncryptionKeyId = "+this.getEncryptionKeyId());
		System.out.println("AlgorithmId = "+this.getAlgorithmId());
		System.out.println("RevocationId = "+this.getRevocationId());
		System.out.println("ActionCode = "+this.getActionCode());
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
