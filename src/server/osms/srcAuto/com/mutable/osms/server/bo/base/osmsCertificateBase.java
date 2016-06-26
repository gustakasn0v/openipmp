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

public class osmsCertificateBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvCertificateBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsCertificateBase()
	{m_osmsDvCertificateBean= new osmsDvCertificateBean();}
	public osmsCertificateBase(osmsDvCertificateBean bean)
	{m_osmsDvCertificateBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvCertificateBean m_osmsDvCertificateBean;
	public osmsDvCertificateBean getCertificateBean()
	{return m_osmsDvCertificateBean;}
	public void setCertificateBean (osmsDvCertificateBean bean)
	{m_osmsDvCertificateBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getCertificateId ()
	{return m_osmsDvCertificateBean.getCertificateId ();}
	public void setCertificateId (Integer pCertificateId)
	{m_osmsDvCertificateBean.setCertificateId(pCertificateId);}

	public String getCertificateTypeCode ()
	{return m_osmsDvCertificateBean.getCertificateTypeCode ();}
	public void setCertificateTypeCode (String pCertificateTypeCode)
	{m_osmsDvCertificateBean.setCertificateTypeCode(pCertificateTypeCode);}

	public Integer getCaCertificateId ()
	{return m_osmsDvCertificateBean.getCaCertificateId ();}
	public void setCaCertificateId (Integer pCaCertificateId)
	{m_osmsDvCertificateBean.setCaCertificateId(pCaCertificateId);}

	public Integer getVersion ()
	{return m_osmsDvCertificateBean.getVersion ();}
	public void setVersion (Integer pVersion)
	{m_osmsDvCertificateBean.setVersion(pVersion);}

	public String getSerialNum ()
	{return m_osmsDvCertificateBean.getSerialNum ();}
	public void setSerialNum (String pSerialNum)
	{m_osmsDvCertificateBean.setSerialNum(pSerialNum);}

	public Timestamp getNotValidBeforeDt ()
	{return m_osmsDvCertificateBean.getNotValidBeforeDt ();}
	public void setNotValidBeforeDt (Timestamp pNotValidBeforeDt)
	{m_osmsDvCertificateBean.setNotValidBeforeDt(pNotValidBeforeDt);}

	public Timestamp getNotValidAfterDt ()
	{return m_osmsDvCertificateBean.getNotValidAfterDt ();}
	public void setNotValidAfterDt (Timestamp pNotValidAfterDt)
	{m_osmsDvCertificateBean.setNotValidAfterDt(pNotValidAfterDt);}

	public byte[] getCertificate ()
	{return m_osmsDvCertificateBean.getCertificate ();}
	public void setCertificate (byte[] pCertificate)
	{m_osmsDvCertificateBean.setCertificate(pCertificate);}

	public byte[] getPublicKey ()
	{return m_osmsDvCertificateBean.getPublicKey ();}
	public void setPublicKey (byte[] pPublicKey)
	{m_osmsDvCertificateBean.setPublicKey(pPublicKey);}

	public byte[] getEncryptedPrivateKey ()
	{return m_osmsDvCertificateBean.getEncryptedPrivateKey ();}
	public void setEncryptedPrivateKey (byte[] pEncryptedPrivateKey)
	{m_osmsDvCertificateBean.setEncryptedPrivateKey(pEncryptedPrivateKey);}

	public Integer getEncryptionKeyId ()
	{return m_osmsDvCertificateBean.getEncryptionKeyId ();}
	public void setEncryptionKeyId (Integer pEncryptionKeyId)
	{m_osmsDvCertificateBean.setEncryptionKeyId(pEncryptionKeyId);}

	public Integer getAlgorithmId ()
	{return m_osmsDvCertificateBean.getAlgorithmId ();}
	public void setAlgorithmId (Integer pAlgorithmId)
	{m_osmsDvCertificateBean.setAlgorithmId(pAlgorithmId);}

	public Integer getRevocationId ()
	{return m_osmsDvCertificateBean.getRevocationId ();}
	public void setRevocationId (Integer pRevocationId)
	{m_osmsDvCertificateBean.setRevocationId(pRevocationId);}

	public String getActionCode ()
	{return m_osmsDvCertificateBean.getActionCode ();}
	public void setActionCode (String pActionCode)
	{m_osmsDvCertificateBean.setActionCode(pActionCode);}

	public String getStatusFlag ()
	{return m_osmsDvCertificateBean.getStatusFlag ();}
	public void setStatusFlag (String pStatusFlag)
	{m_osmsDvCertificateBean.setStatusFlag(pStatusFlag);}

	public String getMaintenanceFlag ()
	{return m_osmsDvCertificateBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvCertificateBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvCertificateBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvCertificateBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvCertificateBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvCertificateBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvCertificateBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvCertificateBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvCertificateBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvCertificateBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvCertificateBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
