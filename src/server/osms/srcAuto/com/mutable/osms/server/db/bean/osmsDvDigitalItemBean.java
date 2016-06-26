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

public class  osmsDvDigitalItemBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int DIGITAL_ITEM_ID
	private Integer m_DigitalItemId;
	public Integer getDigitalItemId ()
	{return m_DigitalItemId;}
	public void setDigitalItemId (Integer pDigitalItemId)
	{m_DigitalItemId = pDigitalItemId;}

	//int CA_CERTIFICATE_ID
	private Integer m_CaCertificateId;
	public Integer getCaCertificateId ()
	{return m_CaCertificateId;}
	public void setCaCertificateId (Integer pCaCertificateId)
	{m_CaCertificateId = pCaCertificateId;}

	//int CONTENT_ID
	private Integer m_ContentId;
	public Integer getContentId ()
	{return m_ContentId;}
	public void setContentId (Integer pContentId)
	{m_ContentId = pContentId;}

	//int DOI_ID
	private Integer m_DoiId;
	public Integer getDoiId ()
	{return m_DoiId;}
	public void setDoiId (Integer pDoiId)
	{m_DoiId = pDoiId;}

	//varchar MIME_TYPE
	private String m_MimeType;
	public String getMimeType ()
	{return m_MimeType;}
	public void setMimeType (String pMimeType)
	{m_MimeType = pMimeType;}

	//blob ENCRYPTED_KEY
	private byte[] m_EncryptedKey;
	public byte[] getEncryptedKey ()
	{return m_EncryptedKey;}
	public void setEncryptedKey (byte[] pEncryptedKey)
	{m_EncryptedKey = pEncryptedKey;}

	//int KEY_LENGTH
	private Integer m_KeyLength;
	public Integer getKeyLength ()
	{return m_KeyLength;}
	public void setKeyLength (Integer pKeyLength)
	{m_KeyLength = pKeyLength;}

	//int KEY_ALGORITHM_ID
	private Integer m_KeyAlgorithmId;
	public Integer getKeyAlgorithmId ()
	{return m_KeyAlgorithmId;}
	public void setKeyAlgorithmId (Integer pKeyAlgorithmId)
	{m_KeyAlgorithmId = pKeyAlgorithmId;}

	//int ENCRYPTION_KEY_ID
	private Integer m_EncryptionKeyId;
	public Integer getEncryptionKeyId ()
	{return m_EncryptionKeyId;}
	public void setEncryptionKeyId (Integer pEncryptionKeyId)
	{m_EncryptionKeyId = pEncryptionKeyId;}

	//varchar CONTENT_DIGEST
	private String m_ContentDigest;
	public String getContentDigest ()
	{return m_ContentDigest;}
	public void setContentDigest (String pContentDigest)
	{m_ContentDigest = pContentDigest;}

	//int DIGEST_ALGORITHM_ID
	private Integer m_DigestAlgorithmId;
	public Integer getDigestAlgorithmId ()
	{return m_DigestAlgorithmId;}
	public void setDigestAlgorithmId (Integer pDigestAlgorithmId)
	{m_DigestAlgorithmId = pDigestAlgorithmId;}

	//blob CONTENT_SIGNATURE
	private byte[] m_ContentSignature;
	public byte[] getContentSignature ()
	{return m_ContentSignature;}
	public void setContentSignature (byte[] pContentSignature)
	{m_ContentSignature = pContentSignature;}

	//int SIG_ALGORITHM_ID
	private Integer m_SigAlgorithmId;
	public Integer getSigAlgorithmId ()
	{return m_SigAlgorithmId;}
	public void setSigAlgorithmId (Integer pSigAlgorithmId)
	{m_SigAlgorithmId = pSigAlgorithmId;}

	//varchar WATERMARK_DATA
	private String m_WatermarkData;
	public String getWatermarkData ()
	{return m_WatermarkData;}
	public void setWatermarkData (String pWatermarkData)
	{m_WatermarkData = pWatermarkData;}

	//int TOOL_IDENTIFIER
	private Integer m_ToolIdentifier;
	public Integer getToolIdentifier ()
	{return m_ToolIdentifier;}
	public void setToolIdentifier (Integer pToolIdentifier)
	{m_ToolIdentifier = pToolIdentifier;}

	//varchar RIGHTS_HOST_URL
	private String m_RightsHostUrl;
	public String getRightsHostUrl ()
	{return m_RightsHostUrl;}
	public void setRightsHostUrl (String pRightsHostUrl)
	{m_RightsHostUrl = pRightsHostUrl;}

	//varchar RIGHTS_HOST_PORT
	private String m_RightsHostPort;
	public String getRightsHostPort ()
	{return m_RightsHostPort;}
	public void setRightsHostPort (String pRightsHostPort)
	{m_RightsHostPort = pRightsHostPort;}

	//varchar LICENSE_TYPE
	private String m_LicenseType;
	public String getLicenseType ()
	{return m_LicenseType;}
	public void setLicenseType (String pLicenseType)
	{m_LicenseType = pLicenseType;}

	//char IS_REVOKED_FLAG
	private String m_IsRevokedFlag;
	public String getIsRevokedFlag ()
	{return m_IsRevokedFlag;}
	public void setIsRevokedFlag (String pIsRevokedFlag)
	{m_IsRevokedFlag = pIsRevokedFlag;}

	//char IS_PROTECTED_FLAG
	private String m_IsProtectedFlag;
	public String getIsProtectedFlag ()
	{return m_IsProtectedFlag;}
	public void setIsProtectedFlag (String pIsProtectedFlag)
	{m_IsProtectedFlag = pIsProtectedFlag;}

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
	public void copyPropertiesTo (osmsDvDigitalItemBean target)
	{

		target.setDigitalItemId (getDigitalItemId());
		target.setCaCertificateId (getCaCertificateId());
		target.setContentId (getContentId());
		target.setDoiId (getDoiId());
		target.setMimeType (getMimeType());
		target.setEncryptedKey (getEncryptedKey());
		target.setKeyLength (getKeyLength());
		target.setKeyAlgorithmId (getKeyAlgorithmId());
		target.setEncryptionKeyId (getEncryptionKeyId());
		target.setContentDigest (getContentDigest());
		target.setDigestAlgorithmId (getDigestAlgorithmId());
		target.setContentSignature (getContentSignature());
		target.setSigAlgorithmId (getSigAlgorithmId());
		target.setWatermarkData (getWatermarkData());
		target.setToolIdentifier (getToolIdentifier());
		target.setRightsHostUrl (getRightsHostUrl());
		target.setRightsHostPort (getRightsHostPort());
		target.setLicenseType (getLicenseType());
		target.setIsRevokedFlag (getIsRevokedFlag());
		target.setIsProtectedFlag (getIsProtectedFlag());
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
    	if (!(pObj instanceof osmsDvDigitalItemBean)) return false;
	    osmsDvDigitalItemBean obj = (osmsDvDigitalItemBean) pObj;


		if (this.getDigitalItemId () != obj.getDigitalItemId () &&
			(this.getDigitalItemId () == null ||
			obj.getDigitalItemId () == null ||
			this.getDigitalItemId ().equals (obj.getDigitalItemId ()))) return false;

		if (this.getCaCertificateId () != obj.getCaCertificateId () &&
			(this.getCaCertificateId () == null ||
			obj.getCaCertificateId () == null ||
			this.getCaCertificateId ().equals (obj.getCaCertificateId ()))) return false;

		if (this.getContentId () != obj.getContentId () &&
			(this.getContentId () == null ||
			obj.getContentId () == null ||
			this.getContentId ().equals (obj.getContentId ()))) return false;

		if (this.getDoiId () != obj.getDoiId () &&
			(this.getDoiId () == null ||
			obj.getDoiId () == null ||
			this.getDoiId ().equals (obj.getDoiId ()))) return false;

		if (this.getMimeType () != obj.getMimeType () &&
			(this.getMimeType () == null ||
			obj.getMimeType () == null ||
			this.getMimeType ().equals (obj.getMimeType ()))) return false;

		if (this.getEncryptedKey () != obj.getEncryptedKey () &&
			(this.getEncryptedKey () == null ||
			obj.getEncryptedKey () == null ||
			this.getEncryptedKey ().equals (obj.getEncryptedKey ()))) return false;

		if (this.getKeyLength () != obj.getKeyLength () &&
			(this.getKeyLength () == null ||
			obj.getKeyLength () == null ||
			this.getKeyLength ().equals (obj.getKeyLength ()))) return false;

		if (this.getKeyAlgorithmId () != obj.getKeyAlgorithmId () &&
			(this.getKeyAlgorithmId () == null ||
			obj.getKeyAlgorithmId () == null ||
			this.getKeyAlgorithmId ().equals (obj.getKeyAlgorithmId ()))) return false;

		if (this.getEncryptionKeyId () != obj.getEncryptionKeyId () &&
			(this.getEncryptionKeyId () == null ||
			obj.getEncryptionKeyId () == null ||
			this.getEncryptionKeyId ().equals (obj.getEncryptionKeyId ()))) return false;

		if (this.getContentDigest () != obj.getContentDigest () &&
			(this.getContentDigest () == null ||
			obj.getContentDigest () == null ||
			this.getContentDigest ().equals (obj.getContentDigest ()))) return false;

		if (this.getDigestAlgorithmId () != obj.getDigestAlgorithmId () &&
			(this.getDigestAlgorithmId () == null ||
			obj.getDigestAlgorithmId () == null ||
			this.getDigestAlgorithmId ().equals (obj.getDigestAlgorithmId ()))) return false;

		if (this.getContentSignature () != obj.getContentSignature () &&
			(this.getContentSignature () == null ||
			obj.getContentSignature () == null ||
			this.getContentSignature ().equals (obj.getContentSignature ()))) return false;

		if (this.getSigAlgorithmId () != obj.getSigAlgorithmId () &&
			(this.getSigAlgorithmId () == null ||
			obj.getSigAlgorithmId () == null ||
			this.getSigAlgorithmId ().equals (obj.getSigAlgorithmId ()))) return false;

		if (this.getWatermarkData () != obj.getWatermarkData () &&
			(this.getWatermarkData () == null ||
			obj.getWatermarkData () == null ||
			this.getWatermarkData ().equals (obj.getWatermarkData ()))) return false;

		if (this.getToolIdentifier () != obj.getToolIdentifier () &&
			(this.getToolIdentifier () == null ||
			obj.getToolIdentifier () == null ||
			this.getToolIdentifier ().equals (obj.getToolIdentifier ()))) return false;

		if (this.getRightsHostUrl () != obj.getRightsHostUrl () &&
			(this.getRightsHostUrl () == null ||
			obj.getRightsHostUrl () == null ||
			this.getRightsHostUrl ().equals (obj.getRightsHostUrl ()))) return false;

		if (this.getRightsHostPort () != obj.getRightsHostPort () &&
			(this.getRightsHostPort () == null ||
			obj.getRightsHostPort () == null ||
			this.getRightsHostPort ().equals (obj.getRightsHostPort ()))) return false;

		if (this.getLicenseType () != obj.getLicenseType () &&
			(this.getLicenseType () == null ||
			obj.getLicenseType () == null ||
			this.getLicenseType ().equals (obj.getLicenseType ()))) return false;

		if (this.getIsRevokedFlag () != obj.getIsRevokedFlag () &&
			(this.getIsRevokedFlag () == null ||
			obj.getIsRevokedFlag () == null ||
			this.getIsRevokedFlag ().equals (obj.getIsRevokedFlag ()))) return false;

		if (this.getIsProtectedFlag () != obj.getIsProtectedFlag () &&
			(this.getIsProtectedFlag () == null ||
			obj.getIsProtectedFlag () == null ||
			this.getIsProtectedFlag ().equals (obj.getIsProtectedFlag ()))) return false;

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

		System.out.println("DigitalItemId = "+this.getDigitalItemId());
		System.out.println("CaCertificateId = "+this.getCaCertificateId());
		System.out.println("ContentId = "+this.getContentId());
		System.out.println("DoiId = "+this.getDoiId());
		System.out.println("MimeType = "+this.getMimeType());
		System.out.println("EncryptedKey = "+this.getEncryptedKey());
		System.out.println("KeyLength = "+this.getKeyLength());
		System.out.println("KeyAlgorithmId = "+this.getKeyAlgorithmId());
		System.out.println("EncryptionKeyId = "+this.getEncryptionKeyId());
		System.out.println("ContentDigest = "+this.getContentDigest());
		System.out.println("DigestAlgorithmId = "+this.getDigestAlgorithmId());
		System.out.println("ContentSignature = "+this.getContentSignature());
		System.out.println("SigAlgorithmId = "+this.getSigAlgorithmId());
		System.out.println("WatermarkData = "+this.getWatermarkData());
		System.out.println("ToolIdentifier = "+this.getToolIdentifier());
		System.out.println("RightsHostUrl = "+this.getRightsHostUrl());
		System.out.println("RightsHostPort = "+this.getRightsHostPort());
		System.out.println("LicenseType = "+this.getLicenseType());
		System.out.println("IsRevokedFlag = "+this.getIsRevokedFlag());
		System.out.println("IsProtectedFlag = "+this.getIsProtectedFlag());
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
