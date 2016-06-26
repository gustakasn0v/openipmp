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

public class  osmsDvAltIdentifierBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int ALT_IDENTIFIER_ID
	private Integer m_AltIdentifierId;
	public Integer getAltIdentifierId ()
	{return m_AltIdentifierId;}
	public void setAltIdentifierId (Integer pAltIdentifierId)
	{m_AltIdentifierId = pAltIdentifierId;}

	//varchar IDENTIFIER_TYPE_CODE
	private String m_IdentifierTypeCode;
	public String getIdentifierTypeCode ()
	{return m_IdentifierTypeCode;}
	public void setIdentifierTypeCode (String pIdentifierTypeCode)
	{m_IdentifierTypeCode = pIdentifierTypeCode;}

	//varchar IDENTIFIER
	private String m_Identifier;
	public String getIdentifier ()
	{return m_Identifier;}
	public void setIdentifier (String pIdentifier)
	{m_Identifier = pIdentifier;}

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
	public void copyPropertiesTo (osmsDvAltIdentifierBean target)
	{

		target.setAltIdentifierId (getAltIdentifierId());
		target.setIdentifierTypeCode (getIdentifierTypeCode());
		target.setIdentifier (getIdentifier());
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
    	if (!(pObj instanceof osmsDvAltIdentifierBean)) return false;
	    osmsDvAltIdentifierBean obj = (osmsDvAltIdentifierBean) pObj;


		if (this.getAltIdentifierId () != obj.getAltIdentifierId () &&
			(this.getAltIdentifierId () == null ||
			obj.getAltIdentifierId () == null ||
			this.getAltIdentifierId ().equals (obj.getAltIdentifierId ()))) return false;

		if (this.getIdentifierTypeCode () != obj.getIdentifierTypeCode () &&
			(this.getIdentifierTypeCode () == null ||
			obj.getIdentifierTypeCode () == null ||
			this.getIdentifierTypeCode ().equals (obj.getIdentifierTypeCode ()))) return false;

		if (this.getIdentifier () != obj.getIdentifier () &&
			(this.getIdentifier () == null ||
			obj.getIdentifier () == null ||
			this.getIdentifier ().equals (obj.getIdentifier ()))) return false;

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

		System.out.println("AltIdentifierId = "+this.getAltIdentifierId());
		System.out.println("IdentifierTypeCode = "+this.getIdentifierTypeCode());
		System.out.println("Identifier = "+this.getIdentifier());
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
