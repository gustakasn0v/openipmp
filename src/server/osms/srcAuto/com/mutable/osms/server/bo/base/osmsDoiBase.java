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

public class osmsDoiBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiBean BEGIN
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//-------------------------------------
	// constructs
	//-------------------------------------
	public osmsDoiBase()
	{m_osmsDvDoiBean= new osmsDvDoiBean();}
	public osmsDoiBase(osmsDvDoiBean bean)
	{m_osmsDvDoiBean=bean;}

	//-------------------------------------
	// bean
	//-------------------------------------
	private osmsDvDoiBean m_osmsDvDoiBean;
	public osmsDvDoiBean getDoiBean()
	{return m_osmsDvDoiBean;}
	public void setDoiBean (osmsDvDoiBean bean)
	{m_osmsDvDoiBean=bean;}

	//-------------------------------------
	// properties
	//-------------------------------------

	public Integer getDoiId ()
	{return m_osmsDvDoiBean.getDoiId ();}
	public void setDoiId (Integer pDoiId)
	{m_osmsDvDoiBean.setDoiId(pDoiId);}

	public String getDoiProfileCode ()
	{return m_osmsDvDoiBean.getDoiProfileCode ();}
	public void setDoiProfileCode (String pDoiProfileCode)
	{m_osmsDvDoiBean.setDoiProfileCode(pDoiProfileCode);}

	public String getDoiIdentifier ()
	{return m_osmsDvDoiBean.getDoiIdentifier ();}
	public void setDoiIdentifier (String pDoiIdentifier)
	{m_osmsDvDoiBean.setDoiIdentifier(pDoiIdentifier);}

	public String getStructuralType ()
	{return m_osmsDvDoiBean.getStructuralType ();}
	public void setStructuralType (String pStructuralType)
	{m_osmsDvDoiBean.setStructuralType(pStructuralType);}

	public String getIssuedInternally ()
	{return m_osmsDvDoiBean.getIssuedInternally ();}
	public void setIssuedInternally (String pIssuedInternally)
	{m_osmsDvDoiBean.setIssuedInternally(pIssuedInternally);}

	public String getVersion ()
	{return m_osmsDvDoiBean.getVersion ();}
	public void setVersion (String pVersion)
	{m_osmsDvDoiBean.setVersion(pVersion);}

	public String getXmlString ()
	{return m_osmsDvDoiBean.getXmlString ();}
	public void setXmlString (String pXmlString)
	{m_osmsDvDoiBean.setXmlString(pXmlString);}

	public String getIsAudioFlag ()
	{return m_osmsDvDoiBean.getIsAudioFlag ();}
	public void setIsAudioFlag (String pIsAudioFlag)
	{m_osmsDvDoiBean.setIsAudioFlag(pIsAudioFlag);}

	public String getIsAbstractFlag ()
	{return m_osmsDvDoiBean.getIsAbstractFlag ();}
	public void setIsAbstractFlag (String pIsAbstractFlag)
	{m_osmsDvDoiBean.setIsAbstractFlag(pIsAbstractFlag);}

	public String getIsAudiovisualFlag ()
	{return m_osmsDvDoiBean.getIsAudiovisualFlag ();}
	public void setIsAudiovisualFlag (String pIsAudiovisualFlag)
	{m_osmsDvDoiBean.setIsAudiovisualFlag(pIsAudiovisualFlag);}

	public String getIsVisualFlag ()
	{return m_osmsDvDoiBean.getIsVisualFlag ();}
	public void setIsVisualFlag (String pIsVisualFlag)
	{m_osmsDvDoiBean.setIsVisualFlag(pIsVisualFlag);}

	public String getPrimaryTitleText ()
	{return m_osmsDvDoiBean.getPrimaryTitleText ();}
	public void setPrimaryTitleText (String pPrimaryTitleText)
	{m_osmsDvDoiBean.setPrimaryTitleText(pPrimaryTitleText);}

	public String getPrimaryTitleLanguage ()
	{return m_osmsDvDoiBean.getPrimaryTitleLanguage ();}
	public void setPrimaryTitleLanguage (String pPrimaryTitleLanguage)
	{m_osmsDvDoiBean.setPrimaryTitleLanguage(pPrimaryTitleLanguage);}

	public String getPrimaryAgentName ()
	{return m_osmsDvDoiBean.getPrimaryAgentName ();}
	public void setPrimaryAgentName (String pPrimaryAgentName)
	{m_osmsDvDoiBean.setPrimaryAgentName(pPrimaryAgentName);}

	public String getPrimaryAgentType ()
	{return m_osmsDvDoiBean.getPrimaryAgentType ();}
	public void setPrimaryAgentType (String pPrimaryAgentType)
	{m_osmsDvDoiBean.setPrimaryAgentType(pPrimaryAgentType);}

	public String getPrimaryAgentRole ()
	{return m_osmsDvDoiBean.getPrimaryAgentRole ();}
	public void setPrimaryAgentRole (String pPrimaryAgentRole)
	{m_osmsDvDoiBean.setPrimaryAgentRole(pPrimaryAgentRole);}

	public String getAssertAuthType ()
	{return m_osmsDvDoiBean.getAssertAuthType ();}
	public void setAssertAuthType (String pAssertAuthType)
	{m_osmsDvDoiBean.setAssertAuthType(pAssertAuthType);}

	public String getAssertAuthName ()
	{return m_osmsDvDoiBean.getAssertAuthName ();}
	public void setAssertAuthName (String pAssertAuthName)
	{m_osmsDvDoiBean.setAssertAuthName(pAssertAuthName);}

	public String getAssertRegType ()
	{return m_osmsDvDoiBean.getAssertRegType ();}
	public void setAssertRegType (String pAssertRegType)
	{m_osmsDvDoiBean.setAssertRegType(pAssertRegType);}

	public String getAssertRegName ()
	{return m_osmsDvDoiBean.getAssertRegName ();}
	public void setAssertRegName (String pAssertRegName)
	{m_osmsDvDoiBean.setAssertRegName(pAssertRegName);}

	public String getAssertIdentifier ()
	{return m_osmsDvDoiBean.getAssertIdentifier ();}
	public void setAssertIdentifier (String pAssertIdentifier)
	{m_osmsDvDoiBean.setAssertIdentifier(pAssertIdentifier);}

	public String getAssertIdentifierType ()
	{return m_osmsDvDoiBean.getAssertIdentifierType ();}
	public void setAssertIdentifierType (String pAssertIdentifierType)
	{m_osmsDvDoiBean.setAssertIdentifierType(pAssertIdentifierType);}

	public String getMaintenanceFlag ()
	{return m_osmsDvDoiBean.getMaintenanceFlag ();}
	public void setMaintenanceFlag (String pMaintenanceFlag)
	{m_osmsDvDoiBean.setMaintenanceFlag(pMaintenanceFlag);}

	public String getLastUpdatedBy ()
	{return m_osmsDvDoiBean.getLastUpdatedBy ();}
	public void setLastUpdatedBy (String pLastUpdatedBy)
	{m_osmsDvDoiBean.setLastUpdatedBy(pLastUpdatedBy);}

	public Timestamp getLastUpdatedOn ()
	{return m_osmsDvDoiBean.getLastUpdatedOn ();}
	public void setLastUpdatedOn (Timestamp pLastUpdatedOn)
	{m_osmsDvDoiBean.setLastUpdatedOn(pLastUpdatedOn);}

	public String getCreatedBy ()
	{return m_osmsDvDoiBean.getCreatedBy ();}
	public void setCreatedBy (String pCreatedBy)
	{m_osmsDvDoiBean.setCreatedBy(pCreatedBy);}

	public Timestamp getCreatedOn ()
	{return m_osmsDvDoiBean.getCreatedOn ();}
	public void setCreatedOn (Timestamp pCreatedOn)
	{m_osmsDvDoiBean.setCreatedOn(pCreatedOn);}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// osmsDvDoiBean END
	//
	//////////////////////////////////////////////////////////////////////////////////////////////


}
