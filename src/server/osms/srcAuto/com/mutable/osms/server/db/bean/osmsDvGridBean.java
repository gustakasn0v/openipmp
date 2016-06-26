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

public class  osmsDvGridBean  implements Serializable
{
	//-------------------------------------
	// properties
	//-------------------------------------

	//int GRID_ID
	private Integer m_GridId;
	public Integer getGridId ()
	{return m_GridId;}
	public void setGridId (Integer pGridId)
	{m_GridId = pGridId;}

	//varchar GRID
	private String m_Grid;
	public String getGrid ()
	{return m_Grid;}
	public void setGrid (String pGrid)
	{m_Grid = pGrid;}

	//varchar PRIMARY_ARTIST
	private String m_PrimaryArtist;
	public String getPrimaryArtist ()
	{return m_PrimaryArtist;}
	public void setPrimaryArtist (String pPrimaryArtist)
	{m_PrimaryArtist = pPrimaryArtist;}

	//varchar PRIMARY_TITLE
	private String m_PrimaryTitle;
	public String getPrimaryTitle ()
	{return m_PrimaryTitle;}
	public void setPrimaryTitle (String pPrimaryTitle)
	{m_PrimaryTitle = pPrimaryTitle;}

	//varchar ISSUING_COMPANY
	private String m_IssuingCompany;
	public String getIssuingCompany ()
	{return m_IssuingCompany;}
	public void setIssuingCompany (String pIssuingCompany)
	{m_IssuingCompany = pIssuingCompany;}

	//text XML_STRING
	private String m_XmlString;
	public String getXmlString ()
	{return m_XmlString;}
	public void setXmlString (String pXmlString)
	{m_XmlString = pXmlString;}

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
	public void copyPropertiesTo (osmsDvGridBean target)
	{

		target.setGridId (getGridId());
		target.setGrid (getGrid());
		target.setPrimaryArtist (getPrimaryArtist());
		target.setPrimaryTitle (getPrimaryTitle());
		target.setIssuingCompany (getIssuingCompany());
		target.setXmlString (getXmlString());
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
    	if (!(pObj instanceof osmsDvGridBean)) return false;
	    osmsDvGridBean obj = (osmsDvGridBean) pObj;


		if (this.getGridId () != obj.getGridId () &&
			(this.getGridId () == null ||
			obj.getGridId () == null ||
			this.getGridId ().equals (obj.getGridId ()))) return false;

		if (this.getGrid () != obj.getGrid () &&
			(this.getGrid () == null ||
			obj.getGrid () == null ||
			this.getGrid ().equals (obj.getGrid ()))) return false;

		if (this.getPrimaryArtist () != obj.getPrimaryArtist () &&
			(this.getPrimaryArtist () == null ||
			obj.getPrimaryArtist () == null ||
			this.getPrimaryArtist ().equals (obj.getPrimaryArtist ()))) return false;

		if (this.getPrimaryTitle () != obj.getPrimaryTitle () &&
			(this.getPrimaryTitle () == null ||
			obj.getPrimaryTitle () == null ||
			this.getPrimaryTitle ().equals (obj.getPrimaryTitle ()))) return false;

		if (this.getIssuingCompany () != obj.getIssuingCompany () &&
			(this.getIssuingCompany () == null ||
			obj.getIssuingCompany () == null ||
			this.getIssuingCompany ().equals (obj.getIssuingCompany ()))) return false;

		if (this.getXmlString () != obj.getXmlString () &&
			(this.getXmlString () == null ||
			obj.getXmlString () == null ||
			this.getXmlString ().equals (obj.getXmlString ()))) return false;

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

		System.out.println("GridId = "+this.getGridId());
		System.out.println("Grid = "+this.getGrid());
		System.out.println("PrimaryArtist = "+this.getPrimaryArtist());
		System.out.println("PrimaryTitle = "+this.getPrimaryTitle());
		System.out.println("IssuingCompany = "+this.getIssuingCompany());
		System.out.println("XmlString = "+this.getXmlString());
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
