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

public class  osmsDvDoiBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int DOI_ID
	private Integer m_DoiId;
	public Integer getDoiId ()
	{return m_DoiId;}
	public void setDoiId (Integer pDoiId)
	{m_DoiId = pDoiId;}

	//varchar DOI_PROFILE_CODE
	private String m_DoiProfileCode;
	public String getDoiProfileCode ()
	{return m_DoiProfileCode;}
	public void setDoiProfileCode (String pDoiProfileCode)
	{m_DoiProfileCode = pDoiProfileCode;}

	//varchar DOI_IDENTIFIER
	private String m_DoiIdentifier;
	public String getDoiIdentifier ()
	{return m_DoiIdentifier;}
	public void setDoiIdentifier (String pDoiIdentifier)
	{m_DoiIdentifier = pDoiIdentifier;}

	//varchar STRUCTURAL_TYPE
	private String m_StructuralType;
	public String getStructuralType ()
	{return m_StructuralType;}
	public void setStructuralType (String pStructuralType)
	{m_StructuralType = pStructuralType;}

	//char ISSUED_INTERNALLY
	private String m_IssuedInternally;
	public String getIssuedInternally ()
	{return m_IssuedInternally;}
	public void setIssuedInternally (String pIssuedInternally)
	{m_IssuedInternally = pIssuedInternally;}

	//varchar VERSION
	private String m_Version;
	public String getVersion ()
	{return m_Version;}
	public void setVersion (String pVersion)
	{m_Version = pVersion;}

	//text XML_STRING
	private String m_XmlString;
	public String getXmlString ()
	{return m_XmlString;}
	public void setXmlString (String pXmlString)
	{m_XmlString = pXmlString;}

	//char IS_AUDIO_FLAG
	private String m_IsAudioFlag;
	public String getIsAudioFlag ()
	{return m_IsAudioFlag;}
	public void setIsAudioFlag (String pIsAudioFlag)
	{m_IsAudioFlag = pIsAudioFlag;}

	//char IS_ABSTRACT_FLAG
	private String m_IsAbstractFlag;
	public String getIsAbstractFlag ()
	{return m_IsAbstractFlag;}
	public void setIsAbstractFlag (String pIsAbstractFlag)
	{m_IsAbstractFlag = pIsAbstractFlag;}

	//char IS_AUDIOVISUAL_FLAG
	private String m_IsAudiovisualFlag;
	public String getIsAudiovisualFlag ()
	{return m_IsAudiovisualFlag;}
	public void setIsAudiovisualFlag (String pIsAudiovisualFlag)
	{m_IsAudiovisualFlag = pIsAudiovisualFlag;}

	//char IS_VISUAL_FLAG
	private String m_IsVisualFlag;
	public String getIsVisualFlag ()
	{return m_IsVisualFlag;}
	public void setIsVisualFlag (String pIsVisualFlag)
	{m_IsVisualFlag = pIsVisualFlag;}

	//varchar PRIMARY_TITLE_TEXT
	private String m_PrimaryTitleText;
	public String getPrimaryTitleText ()
	{return m_PrimaryTitleText;}
	public void setPrimaryTitleText (String pPrimaryTitleText)
	{m_PrimaryTitleText = pPrimaryTitleText;}

	//varchar PRIMARY_TITLE_LANGUAGE
	private String m_PrimaryTitleLanguage;
	public String getPrimaryTitleLanguage ()
	{return m_PrimaryTitleLanguage;}
	public void setPrimaryTitleLanguage (String pPrimaryTitleLanguage)
	{m_PrimaryTitleLanguage = pPrimaryTitleLanguage;}

	//varchar PRIMARY_AGENT_NAME
	private String m_PrimaryAgentName;
	public String getPrimaryAgentName ()
	{return m_PrimaryAgentName;}
	public void setPrimaryAgentName (String pPrimaryAgentName)
	{m_PrimaryAgentName = pPrimaryAgentName;}

	//varchar PRIMARY_AGENT_TYPE
	private String m_PrimaryAgentType;
	public String getPrimaryAgentType ()
	{return m_PrimaryAgentType;}
	public void setPrimaryAgentType (String pPrimaryAgentType)
	{m_PrimaryAgentType = pPrimaryAgentType;}

	//varchar PRIMARY_AGENT_ROLE
	private String m_PrimaryAgentRole;
	public String getPrimaryAgentRole ()
	{return m_PrimaryAgentRole;}
	public void setPrimaryAgentRole (String pPrimaryAgentRole)
	{m_PrimaryAgentRole = pPrimaryAgentRole;}

	//varchar ASSERT_AUTH_TYPE
	private String m_AssertAuthType;
	public String getAssertAuthType ()
	{return m_AssertAuthType;}
	public void setAssertAuthType (String pAssertAuthType)
	{m_AssertAuthType = pAssertAuthType;}

	//varchar ASSERT_AUTH_NAME
	private String m_AssertAuthName;
	public String getAssertAuthName ()
	{return m_AssertAuthName;}
	public void setAssertAuthName (String pAssertAuthName)
	{m_AssertAuthName = pAssertAuthName;}

	//varchar ASSERT_REG_TYPE
	private String m_AssertRegType;
	public String getAssertRegType ()
	{return m_AssertRegType;}
	public void setAssertRegType (String pAssertRegType)
	{m_AssertRegType = pAssertRegType;}

	//varchar ASSERT_REG_NAME
	private String m_AssertRegName;
	public String getAssertRegName ()
	{return m_AssertRegName;}
	public void setAssertRegName (String pAssertRegName)
	{m_AssertRegName = pAssertRegName;}

	//varchar ASSERT_IDENTIFIER
	private String m_AssertIdentifier;
	public String getAssertIdentifier ()
	{return m_AssertIdentifier;}
	public void setAssertIdentifier (String pAssertIdentifier)
	{m_AssertIdentifier = pAssertIdentifier;}

	//varchar ASSERT_IDENTIFIER_TYPE
	private String m_AssertIdentifierType;
	public String getAssertIdentifierType ()
	{return m_AssertIdentifierType;}
	public void setAssertIdentifierType (String pAssertIdentifierType)
	{m_AssertIdentifierType = pAssertIdentifierType;}

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
	public void copyPropertiesTo (osmsDvDoiBean target)
	{

		target.setDoiId (getDoiId());
		target.setDoiProfileCode (getDoiProfileCode());
		target.setDoiIdentifier (getDoiIdentifier());
		target.setStructuralType (getStructuralType());
		target.setIssuedInternally (getIssuedInternally());
		target.setVersion (getVersion());
		target.setXmlString (getXmlString());
		target.setIsAudioFlag (getIsAudioFlag());
		target.setIsAbstractFlag (getIsAbstractFlag());
		target.setIsAudiovisualFlag (getIsAudiovisualFlag());
		target.setIsVisualFlag (getIsVisualFlag());
		target.setPrimaryTitleText (getPrimaryTitleText());
		target.setPrimaryTitleLanguage (getPrimaryTitleLanguage());
		target.setPrimaryAgentName (getPrimaryAgentName());
		target.setPrimaryAgentType (getPrimaryAgentType());
		target.setPrimaryAgentRole (getPrimaryAgentRole());
		target.setAssertAuthType (getAssertAuthType());
		target.setAssertAuthName (getAssertAuthName());
		target.setAssertRegType (getAssertRegType());
		target.setAssertRegName (getAssertRegName());
		target.setAssertIdentifier (getAssertIdentifier());
		target.setAssertIdentifierType (getAssertIdentifierType());
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
    	if (!(pObj instanceof osmsDvDoiBean)) return false;
	    osmsDvDoiBean obj = (osmsDvDoiBean) pObj;


		if (this.getDoiId () != obj.getDoiId () &&
			(this.getDoiId () == null ||
			obj.getDoiId () == null ||
			this.getDoiId ().equals (obj.getDoiId ()))) return false;

		if (this.getDoiProfileCode () != obj.getDoiProfileCode () &&
			(this.getDoiProfileCode () == null ||
			obj.getDoiProfileCode () == null ||
			this.getDoiProfileCode ().equals (obj.getDoiProfileCode ()))) return false;

		if (this.getDoiIdentifier () != obj.getDoiIdentifier () &&
			(this.getDoiIdentifier () == null ||
			obj.getDoiIdentifier () == null ||
			this.getDoiIdentifier ().equals (obj.getDoiIdentifier ()))) return false;

		if (this.getStructuralType () != obj.getStructuralType () &&
			(this.getStructuralType () == null ||
			obj.getStructuralType () == null ||
			this.getStructuralType ().equals (obj.getStructuralType ()))) return false;

		if (this.getIssuedInternally () != obj.getIssuedInternally () &&
			(this.getIssuedInternally () == null ||
			obj.getIssuedInternally () == null ||
			this.getIssuedInternally ().equals (obj.getIssuedInternally ()))) return false;

		if (this.getVersion () != obj.getVersion () &&
			(this.getVersion () == null ||
			obj.getVersion () == null ||
			this.getVersion ().equals (obj.getVersion ()))) return false;

		if (this.getXmlString () != obj.getXmlString () &&
			(this.getXmlString () == null ||
			obj.getXmlString () == null ||
			this.getXmlString ().equals (obj.getXmlString ()))) return false;

		if (this.getIsAudioFlag () != obj.getIsAudioFlag () &&
			(this.getIsAudioFlag () == null ||
			obj.getIsAudioFlag () == null ||
			this.getIsAudioFlag ().equals (obj.getIsAudioFlag ()))) return false;

		if (this.getIsAbstractFlag () != obj.getIsAbstractFlag () &&
			(this.getIsAbstractFlag () == null ||
			obj.getIsAbstractFlag () == null ||
			this.getIsAbstractFlag ().equals (obj.getIsAbstractFlag ()))) return false;

		if (this.getIsAudiovisualFlag () != obj.getIsAudiovisualFlag () &&
			(this.getIsAudiovisualFlag () == null ||
			obj.getIsAudiovisualFlag () == null ||
			this.getIsAudiovisualFlag ().equals (obj.getIsAudiovisualFlag ()))) return false;

		if (this.getIsVisualFlag () != obj.getIsVisualFlag () &&
			(this.getIsVisualFlag () == null ||
			obj.getIsVisualFlag () == null ||
			this.getIsVisualFlag ().equals (obj.getIsVisualFlag ()))) return false;

		if (this.getPrimaryTitleText () != obj.getPrimaryTitleText () &&
			(this.getPrimaryTitleText () == null ||
			obj.getPrimaryTitleText () == null ||
			this.getPrimaryTitleText ().equals (obj.getPrimaryTitleText ()))) return false;

		if (this.getPrimaryTitleLanguage () != obj.getPrimaryTitleLanguage () &&
			(this.getPrimaryTitleLanguage () == null ||
			obj.getPrimaryTitleLanguage () == null ||
			this.getPrimaryTitleLanguage ().equals (obj.getPrimaryTitleLanguage ()))) return false;

		if (this.getPrimaryAgentName () != obj.getPrimaryAgentName () &&
			(this.getPrimaryAgentName () == null ||
			obj.getPrimaryAgentName () == null ||
			this.getPrimaryAgentName ().equals (obj.getPrimaryAgentName ()))) return false;

		if (this.getPrimaryAgentType () != obj.getPrimaryAgentType () &&
			(this.getPrimaryAgentType () == null ||
			obj.getPrimaryAgentType () == null ||
			this.getPrimaryAgentType ().equals (obj.getPrimaryAgentType ()))) return false;

		if (this.getPrimaryAgentRole () != obj.getPrimaryAgentRole () &&
			(this.getPrimaryAgentRole () == null ||
			obj.getPrimaryAgentRole () == null ||
			this.getPrimaryAgentRole ().equals (obj.getPrimaryAgentRole ()))) return false;

		if (this.getAssertAuthType () != obj.getAssertAuthType () &&
			(this.getAssertAuthType () == null ||
			obj.getAssertAuthType () == null ||
			this.getAssertAuthType ().equals (obj.getAssertAuthType ()))) return false;

		if (this.getAssertAuthName () != obj.getAssertAuthName () &&
			(this.getAssertAuthName () == null ||
			obj.getAssertAuthName () == null ||
			this.getAssertAuthName ().equals (obj.getAssertAuthName ()))) return false;

		if (this.getAssertRegType () != obj.getAssertRegType () &&
			(this.getAssertRegType () == null ||
			obj.getAssertRegType () == null ||
			this.getAssertRegType ().equals (obj.getAssertRegType ()))) return false;

		if (this.getAssertRegName () != obj.getAssertRegName () &&
			(this.getAssertRegName () == null ||
			obj.getAssertRegName () == null ||
			this.getAssertRegName ().equals (obj.getAssertRegName ()))) return false;

		if (this.getAssertIdentifier () != obj.getAssertIdentifier () &&
			(this.getAssertIdentifier () == null ||
			obj.getAssertIdentifier () == null ||
			this.getAssertIdentifier ().equals (obj.getAssertIdentifier ()))) return false;

		if (this.getAssertIdentifierType () != obj.getAssertIdentifierType () &&
			(this.getAssertIdentifierType () == null ||
			obj.getAssertIdentifierType () == null ||
			this.getAssertIdentifierType ().equals (obj.getAssertIdentifierType ()))) return false;

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

		System.out.println("DoiId = "+this.getDoiId());
		System.out.println("DoiProfileCode = "+this.getDoiProfileCode());
		System.out.println("DoiIdentifier = "+this.getDoiIdentifier());
		System.out.println("StructuralType = "+this.getStructuralType());
		System.out.println("IssuedInternally = "+this.getIssuedInternally());
		System.out.println("Version = "+this.getVersion());
		System.out.println("XmlString = "+this.getXmlString());
		System.out.println("IsAudioFlag = "+this.getIsAudioFlag());
		System.out.println("IsAbstractFlag = "+this.getIsAbstractFlag());
		System.out.println("IsAudiovisualFlag = "+this.getIsAudiovisualFlag());
		System.out.println("IsVisualFlag = "+this.getIsVisualFlag());
		System.out.println("PrimaryTitleText = "+this.getPrimaryTitleText());
		System.out.println("PrimaryTitleLanguage = "+this.getPrimaryTitleLanguage());
		System.out.println("PrimaryAgentName = "+this.getPrimaryAgentName());
		System.out.println("PrimaryAgentType = "+this.getPrimaryAgentType());
		System.out.println("PrimaryAgentRole = "+this.getPrimaryAgentRole());
		System.out.println("AssertAuthType = "+this.getAssertAuthType());
		System.out.println("AssertAuthName = "+this.getAssertAuthName());
		System.out.println("AssertRegType = "+this.getAssertRegType());
		System.out.println("AssertRegName = "+this.getAssertRegName());
		System.out.println("AssertIdentifier = "+this.getAssertIdentifier());
		System.out.println("AssertIdentifierType = "+this.getAssertIdentifierType());
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
