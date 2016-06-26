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

public class osmsContentBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvContentBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsContentBase()
	{m_osmsDvContentBean= new osmsDvContentBean();}
	public osmsContentBase(osmsDvContentBean bean)
	{m_osmsDvContentBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvContentBean m_osmsDvContentBean;
	public osmsDvContentBean getContentBean()
	{return m_osmsDvContentBean;}
	public void setContentBean (osmsDvContentBean bean)
	{m_osmsDvContentBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getContentId ()
	{return m_osmsDvContentBean.getContentId ();}
	public void setContentId (Integer pContentId)
	{m_osmsDvContentBean.setContentId(pContentId);}

	public String getIdentifierTypeCode ()
	{return m_osmsDvContentBean.getIdentifierTypeCode ();}
	public void setIdentifierTypeCode (String pIdentifierTypeCode)
	{m_osmsDvContentBean.setIdentifierTypeCode(pIdentifierTypeCode);}

	public String getPrimaryIdentifier ()
	{return m_osmsDvContentBean.getPrimaryIdentifier ();}
	public void setPrimaryIdentifier (String pPrimaryIdentifier)
	{m_osmsDvContentBean.setPrimaryIdentifier(pPrimaryIdentifier);}

	public String getPrimaryArtist ()
	{return m_osmsDvContentBean.getPrimaryArtist ();}
	public void setPrimaryArtist (String pPrimaryArtist)
	{m_osmsDvContentBean.setPrimaryArtist(pPrimaryArtist);}

	public String getPrimaryTitle ()
	{return m_osmsDvContentBean.getPrimaryTitle ();}
	public void setPrimaryTitle (String pPrimaryTitle)
	{m_osmsDvContentBean.setPrimaryTitle(pPrimaryTitle);}

	public Timestamp getReleaseDate ()
	{return m_osmsDvContentBean.getReleaseDate ();}
	public void setReleaseDate (Timestamp pReleaseDate)
	{m_osmsDvContentBean.setReleaseDate(pReleaseDate);}

	public Timestamp getLicenseBeginDate ()
	{return m_osmsDvContentBean.getLicenseBeginDate ();}
	public void setLicenseBeginDate (Timestamp pLicenseBeginDate)
	{m_osmsDvContentBean.setLicenseBeginDate(pLicenseBeginDate);}

	public String getLicenseType ()
	{return m_osmsDvContentBean.getLicenseType ();}
	public void setLicenseType (String pLicenseType)
	{m_osmsDvContentBean.setLicenseType(pLicenseType);}

	public Integer getRegisteredBy ()
	{return m_osmsDvContentBean.getRegisteredBy ();}
	public void setRegisteredBy (Integer pRegisteredBy)
	{m_osmsDvContentBean.setRegisteredBy(pRegisteredBy);}

	public String getMaintenanceFlag ()
	{return m_osmsDvContentBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvContentBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvContentBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvContentBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvContentBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvContentBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvContentBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvContentBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvContentBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvContentBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvContentBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
