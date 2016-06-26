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

public class osmsDigitalItemBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDigitalItemBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsDigitalItemBase()
	{m_osmsDvDigitalItemBean= new osmsDvDigitalItemBean();}
	public osmsDigitalItemBase(osmsDvDigitalItemBean bean)
	{m_osmsDvDigitalItemBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvDigitalItemBean m_osmsDvDigitalItemBean;
	public osmsDvDigitalItemBean getDigitalItemBean()
	{return m_osmsDvDigitalItemBean;}
	public void setDigitalItemBean (osmsDvDigitalItemBean bean)
	{m_osmsDvDigitalItemBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getDigitalItemId ()
	{return m_osmsDvDigitalItemBean.getDigitalItemId ();}
	public void setDigitalItemId (Integer pDigitalItemId)
	{m_osmsDvDigitalItemBean.setDigitalItemId(pDigitalItemId);}

	public Integer getCaCertificateId ()
	{return m_osmsDvDigitalItemBean.getCaCertificateId ();}
	public void setCaCertificateId (Integer pCaCertificateId)
	{m_osmsDvDigitalItemBean.setCaCertificateId(pCaCertificateId);}

	public Integer getContentId ()
	{return m_osmsDvDigitalItemBean.getContentId ();}
	public void setContentId (Integer pContentId)
	{m_osmsDvDigitalItemBean.setContentId(pContentId);}

	public Integer getDoiId ()
	{return m_osmsDvDigitalItemBean.getDoiId ();}
	public void setDoiId (Integer pDoiId)
	{m_osmsDvDigitalItemBean.setDoiId(pDoiId);}

	public String getMimeType ()
	{return m_osmsDvDigitalItemBean.getMimeType ();}
	public void setMimeType (String pMimeType)
	{m_osmsDvDigitalItemBean.setMimeType(pMimeType);}

	public byte[] getEncryptedKey ()
	{return m_osmsDvDigitalItemBean.getEncryptedKey ();}
	public void setEncryptedKey (byte[] pEncryptedKey)
	{m_osmsDvDigitalItemBean.setEncryptedKey(pEncryptedKey);}

	public Integer getKeyLength ()
	{return m_osmsDvDigitalItemBean.getKeyLength ();}
	public void setKeyLength (Integer pKeyLength)
	{m_osmsDvDigitalItemBean.setKeyLength(pKeyLength);}

	public Integer getKeyAlgorithmId ()
	{return m_osmsDvDigitalItemBean.getKeyAlgorithmId ();}
	public void setKeyAlgorithmId (Integer pKeyAlgorithmId)
	{m_osmsDvDigitalItemBean.setKeyAlgorithmId(pKeyAlgorithmId);}

	public Integer getEncryptionKeyId ()
	{return m_osmsDvDigitalItemBean.getEncryptionKeyId ();}
	public void setEncryptionKeyId (Integer pEncryptionKeyId)
	{m_osmsDvDigitalItemBean.setEncryptionKeyId(pEncryptionKeyId);}

	public String getContentDigest ()
	{return m_osmsDvDigitalItemBean.getContentDigest ();}
	public void setContentDigest (String pContentDigest)
	{m_osmsDvDigitalItemBean.setContentDigest(pContentDigest);}

	public Integer getDigestAlgorithmId ()
	{return m_osmsDvDigitalItemBean.getDigestAlgorithmId ();}
	public void setDigestAlgorithmId (Integer pDigestAlgorithmId)
	{m_osmsDvDigitalItemBean.setDigestAlgorithmId(pDigestAlgorithmId);}

	public byte[] getContentSignature ()
	{return m_osmsDvDigitalItemBean.getContentSignature ();}
	public void setContentSignature (byte[] pContentSignature)
	{m_osmsDvDigitalItemBean.setContentSignature(pContentSignature);}

	public Integer getSigAlgorithmId ()
	{return m_osmsDvDigitalItemBean.getSigAlgorithmId ();}
	public void setSigAlgorithmId (Integer pSigAlgorithmId)
	{m_osmsDvDigitalItemBean.setSigAlgorithmId(pSigAlgorithmId);}

	public String getWatermarkData ()
	{return m_osmsDvDigitalItemBean.getWatermarkData ();}
	public void setWatermarkData (String pWatermarkData)
	{m_osmsDvDigitalItemBean.setWatermarkData(pWatermarkData);}

	public Integer getToolIdentifier ()
	{return m_osmsDvDigitalItemBean.getToolIdentifier ();}
	public void setToolIdentifier (Integer pToolIdentifier)
	{m_osmsDvDigitalItemBean.setToolIdentifier(pToolIdentifier);}

	public String getRightsHostUrl ()
	{return m_osmsDvDigitalItemBean.getRightsHostUrl ();}
	public void setRightsHostUrl (String pRightsHostUrl)
	{m_osmsDvDigitalItemBean.setRightsHostUrl(pRightsHostUrl);}

	public String getRightsHostPort ()
	{return m_osmsDvDigitalItemBean.getRightsHostPort ();}
	public void setRightsHostPort (String pRightsHostPort)
	{m_osmsDvDigitalItemBean.setRightsHostPort(pRightsHostPort);}

	public String getLicenseType ()
	{return m_osmsDvDigitalItemBean.getLicenseType ();}
	public void setLicenseType (String pLicenseType)
	{m_osmsDvDigitalItemBean.setLicenseType(pLicenseType);}

	public String getIsRevokedFlag ()
	{return m_osmsDvDigitalItemBean.getIsRevokedFlag ();}
	public void setIsRevokedFlag (String pIsRevokedFlag)
	{m_osmsDvDigitalItemBean.setIsRevokedFlag(pIsRevokedFlag);}

	public String getIsProtectedFlag ()
	{return m_osmsDvDigitalItemBean.getIsProtectedFlag ();}
	public void setIsProtectedFlag (String pIsProtectedFlag)
	{m_osmsDvDigitalItemBean.setIsProtectedFlag(pIsProtectedFlag);}

	public Integer getRegisteredBy ()
	{return m_osmsDvDigitalItemBean.getRegisteredBy ();}
	public void setRegisteredBy (Integer pRegisteredBy)
	{m_osmsDvDigitalItemBean.setRegisteredBy(pRegisteredBy);}

	public String getMaintenanceFlag ()
	{return m_osmsDvDigitalItemBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvDigitalItemBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvDigitalItemBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvDigitalItemBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvDigitalItemBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvDigitalItemBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvDigitalItemBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvDigitalItemBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvDigitalItemBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvDigitalItemBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDigitalItemBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
