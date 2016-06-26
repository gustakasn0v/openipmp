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
 * @version 1.1
 */
package com.mutable.osms.server.db;

import java.sql.Time;
import java.sql.Timestamp;
import java.sql.Connection;
import java.util.Date;

import java.util.Vector;
import java.io.*;

import com.mutable.io.tools.StringTool;
import com.mutable.osms.server.db.manager.*;
import com.mutable.osms.server.db.bean.*;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.server.app.*;


public class osmsDatabase extends osmsDatabaseBase implements Serializable
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PROPERTIES
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private osmsServerConfiguration m_Config;// = osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration();

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	public osmsDatabase()
	{
		osmsGlobalObjectManager gman =osmsGlobalObjectManager.getInstance();
//		gman.
		m_Config = osmsGlobalObjectManager.getInstance().getOsmsServerConfiguration();
	}
	public Integer assignDoiIdentifierSequenceByType(String identifierType)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
		    Integer identifierSeq = m_osmsDvDoiManager.getNextIdentifierNumber(identifierType, conn);
			conn.commit();
			return identifierSeq;
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception(e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}

	public void insertContentDoiFull(osmsContent bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());

		    //Make sure the user object of the registering user is set
			if(bo.getRegisteredByUser()==null)
				throw new Exception("Content/DOI Insert failed because user was not set");

		    //Insert Content/DOI related objects
			if(bo.getContentDoi()==null) bo.setContentDoi(new osmsContentDoi());
			if(bo.getDoi()==null /*|| bo.getContentDoi()==null*/)
			{
				throw new Exception("Content/DOI Insert failed because DOI was not set");
			}

		    //Insert DOI related objects
			if(bo.getDoi()!=null)
			{
				this.insertDoiFull(bo.getDoi(),conn);
			}

		    //Insert Content
			bo.setRegisteredBy(bo.getRegisteredByUser().getUserId());
		    bo.setLastUpdatedBy(m_Config.getAuditUpdateUser());
		    bo.setCreatedBy(m_Config.getAuditCreateUser());
			m_osmsDvContentManager.insert(bo.getContentBean(),conn);

		    //Insert ContentDoi
			bo.getContentDoi().setDoiId(bo.getDoi().getDoiId());
			bo.getContentDoi().setContentId(bo.getContentId());
		    bo.setLastUpdatedBy(m_Config.getAuditUpdateUser());
		    bo.setCreatedBy(m_Config.getAuditCreateUser());
			m_osmsDvContentDoiManager.insert(bo.getContentDoi().getContentDoiBean(),conn);

			conn.commit();
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception(e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}

	public void insertContentGridFull(osmsContent bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());

		    //Make sure the user object of the registering user is set
			if(bo.getRegisteredByUser()==null)
				throw new Exception("Content/GRID Insert failed because user was not set");

		    //Insert Content/Grid related objects
			if(bo.getGrid()==null || bo.getContentGrid()==null)
			{
				throw new Exception("Content/GRID Insert failed because GRID or Content/GRID was not set");
			}

		    //Insert Grid related objects
			if(bo.getGrid()!=null)
			{
				this.m_osmsDvGridManager.insert(bo.getGrid().getGridBean(),conn);
			}

		    //Insert Content
			bo.setRegisteredBy(bo.getRegisteredByUser().getUserId());
		    bo.setLastUpdatedBy(m_Config.getAuditUpdateUser());
		    bo.setCreatedBy(m_Config.getAuditCreateUser());
			m_osmsDvContentManager.insert(bo.getContentBean(),conn);

		    //Insert Content/Grid
			bo.getContentGrid().setGridId(bo.getGrid().getGridId());
			bo.getContentGrid().setContentId(bo.getContentId());
		    bo.setLastUpdatedBy(m_Config.getAuditUpdateUser());
		    bo.setCreatedBy(m_Config.getAuditCreateUser());
			m_osmsDvContentGridManager.insert(bo.getContentGrid().getContentGridBean(),conn);

			conn.commit();
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception(e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}
	public void insertDigitalItemFull(osmsDigitalItem bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());

		    //Make sure the user object of the registering user is set
			if(bo.getRegisteredByUser()==null)
				throw new Exception("DigitalItem Insert failed because user was not set properly");

		    //Make sure the content object is set
			if(bo.getContent()==null)
				throw new Exception("DigitalItem Insert failed because content was not set properly");

		    //Make sure the doi object is set
			if(bo.getDoi()==null)
				throw new Exception("DigitalItem Insert failed because content was not set properly");

		    //Insert DOI related objects
			if(bo.getDoi()!=null)
			{
				this.insertDoiFull(bo.getDoi(),conn);
			}

		    //Insert DigitalItem
			bo.setContentId(bo.getContent().getContentId());
			bo.setDoiId(bo.getDoi().getDoiId());
			bo.setRegisteredBy(bo.getRegisteredByUser().getUserId());
		    bo.setLastUpdatedBy(m_Config.getAuditUpdateUser());
		    bo.setCreatedBy(m_Config.getAuditCreateUser());

			m_osmsDvDigitalItemManager.insert(bo.getDigitalItemBean(),conn);

			conn.commit();
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception(e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}

	public void insertDoiFull(osmsDoi bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());

			this.insertDoiFull(bo,conn);

			conn.commit();
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception(e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}

	private void insertDoiFull(osmsDoi bo, Connection conn)
		throws Exception
	{
		String methodName = "insertDoiFull";
		try
		{
		    //Insert DOI
			if(bo==null)
				throw new Exception(methodName + "DOI cannot be null");

			bo.setLastUpdatedBy(m_Config.getAuditUpdateUser());
			bo.setCreatedBy(m_Config.getAuditCreateUser());
			m_osmsDvDoiManager.insert(bo.getDoiBean(),conn);

			//Insert DOI Titles
			if(bo.getDoiTitles()!=null)
		    {
				for(int i=0; i < bo.getDoiTitles().length; i++)
				{
				    bo.getDoiTitles()[i].setLastUpdatedBy(m_Config.getAuditUpdateUser());
				    bo.getDoiTitles()[i].setCreatedBy(m_Config.getAuditCreateUser());
					m_osmsDvDoiTitleManager.insert(bo.getDoiTitles()[i].getDoiTitleBean(),conn);

					osmsDoiTitleRel titleRel = new osmsDoiTitleRel();
					titleRel.setDoiId(bo.getDoiId());
					titleRel.setTitleId(bo.getDoiTitles()[i].getTitleId());
					titleRel.setLastUpdatedBy(m_Config.getAuditUpdateUser());
					titleRel.setCreatedBy(m_Config.getAuditCreateUser());
					m_osmsDvDoiTitleRelManager.insert(titleRel.getDoiTitleRelBean(),conn);
				}
			}

			//Insert DOI Alt Identifiers
			if(bo.getAltIdentifiers()!=null)
			{
				for(int i=0; i < bo.getAltIdentifiers().length; i++)
				{
				    osmsAltIdentifier id = bo.getAltIdentifiers()[i];

					//Make sure Identifier Type (first five characters after removing leading and trailing whitepspac) is supplied and known, otherwise create a new Identifier Type

					//Remove leading and trailing whitespace
					String codeTrimmed = null;
					if(StringTool.isStringValid(id.getIdentifierTypeCode()) && StringTool.isStringValid(id.getIdentifierTypeCode().trim()))
						codeTrimmed = id.getIdentifierTypeCode().trim();
					else
						codeTrimmed = "UNKOW";

					int maxSize = 5;
					int size = (codeTrimmed.length()<=maxSize?codeTrimmed.length():maxSize);
					String idTypeCode = new String(codeTrimmed.substring(0,size));

					osmsIdentifierType idType = this.getIdentifierTypeByIdentifierTypeCode(idTypeCode.toUpperCase(),conn);

					if(idType==null) //Not found, create a new one
					{
						idType = new osmsIdentifierType();
						idType.setIdentifierTypeCode(idTypeCode.toUpperCase());
						idType.setLastUpdatedBy(m_Config.getAuditUpdateUser());
						idType.setCreatedBy(m_Config.getAuditCreateUser());
						m_osmsDvIdentifierTypeManager.insert(idType.getIdentifierTypeBean(),conn);
					}

				    //Alt Identifier - Determine if Alt Identifier already exists
					osmsAltIdentifier[] existingIds = convertBean2BO(this.m_osmsDvAltIdentifierManager.getAltIdentifierByIdentifierAndIdentifierType(id.getIdentifier(),idType.getIdentifierTypeCode(),conn));
					if(existingIds!=null && existingIds[0]!=null)
					{
						//Alt Identifier already exists, so save order related to this doi
						Integer altIdOrder = id.getAltIdOrder();
						id=existingIds[0];
						id.setAltIdOrder(altIdOrder);
					}
					else
					{
						id.setIdentifierTypeCode(idType.getIdentifierTypeCode());
						id.setLastUpdatedBy(m_Config.getAuditUpdateUser());
						id.setCreatedBy(m_Config.getAuditCreateUser());
						this.m_osmsDvAltIdentifierManager.insert(id.getAltIdentifierBean(),conn);
					}

				    //DOI-Alt Identifier relationship
					osmsDoiAltIdentifier rel = new osmsDoiAltIdentifier();
					rel.setDoiId(bo.getDoiId());
					rel.setAltIdentifierId(id.getAltIdentifierId());
					rel.setSequence(id.getAltIdOrder());
					rel.setLastUpdatedBy(m_Config.getAuditUpdateUser());
					rel.setCreatedBy(m_Config.getAuditCreateUser());
					m_osmsDvDoiAltIdentifierManager.insert(rel.getDoiAltIdentifierBean(),conn);
				}
			}

			if(bo.getDoiAgents()!=null)
			{
				for(int i=0; i < bo.getDoiAgents().length; i++)
				{
					bo.getDoiAgents()[i].setDoiId(bo.getDoiId());
				    bo.getDoiAgents()[i].setLastUpdatedBy(m_Config.getAuditUpdateUser());
				    bo.getDoiAgents()[i].setCreatedBy(m_Config.getAuditCreateUser());
					this.m_osmsDvDoiAgentManager.insert(bo.getDoiAgents()[i].getDoiAgentBean(),conn);
				}
			}
			conn.commit();
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception(e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}
	public osmsIdentifierType getIdentifierTypeByIdentifierTypeCode(String idTypeCode, Connection conn) throws Exception
	{
			try
			{
				osmsIdentifierType[] bos = convertBean2BO(m_osmsDvIdentifierTypeManager.getByIdentifierTypeCode(idTypeCode,conn));

				//RETURN
				if(bos!=null)
				{
					if (bos.length!=1) throw new Exception("Expected one row returned for in getIdentifierTypeByIdentifierTypeCode, recieved "+bos.length);
				}

				if(bos==null || bos[0]==null)
					return null;

				return bos[0];
			}
			catch(Exception e)
			{
				throw e;
			}
	}


	public osmsIpmpAgreement[] getIpmpAgreementByAssignedToUserAndDOIIdentifier/*AndPermissionType*/(Integer userId,String contentIdentifier/*,String permissionType*/) throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.getIpmpAgreementByAssignedToUserAndDOIIdentifier(userId,contentIdentifier/*,permissionType*/,conn));
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
			return bos;

		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception("osmsDatabaseBase.getIpmpAgreementByAssignedToUserAndDOIIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}
	public osmsDigitalItem getDigitalItemByDoiIdentifier(String contentIdentifier) throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getDigitalItemByDoiIdentifier(contentIdentifier,conn));
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null)
			{
				return null;
			}
			if (bos.length!=1)
			{
				throw new Exception("Expected one row returned for in getDigitalItemByDoiIdentifier, recieved "+bos.length);
			}
			return bos[0];
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception("osmsDatabaseBase.getDigitalItemByDoiIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}

	public void insertLoginHistory(osmsLoginHistory bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());

			bo.setCreatedBy(m_Config.getAuditCreateUser());
			bo.setLastUpdatedBy(m_Config.getAuditUpdateUser());
			this.m_osmsDvLoginHistoryManager.insert(bo.getLoginHistoryBean(),conn);

			conn.commit();
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception(e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}

	public osmsIpmpAgreement[] getIpmpAgreementWithAssignedToOsmsUserByContentId(Integer contentId)
			throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.getByContentId( contentId,conn));

			for (int i = 0; bos!=null && i < bos.length; i++)
			{
				osmsUsers[] users = convertBean2BO(this.m_osmsDvUsersManager.getByUserId(bos[i].getAssignedToUser(),conn));
				if(bos!=null)
				{
					if (users.length!=1) throw new Exception("Expected one row returned for in getIpmpAgreementWithAssignedToOsmsUserByContentId, recieved "+bos.length);
					bos[i].setAssignedToOsmsUser(users[0]);
				}
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			return bos;
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception("osmsDatabaseBase.getIpmpAgreementByContentId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}


	}
	public osmsIpmpLicense getIpmpLicenseByAgreementIdAndDigitalItemId(Integer agreementId,Integer digitalItemId)throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByAgreementIdAndDigitalItemId(agreementId,digitalItemId,conn));
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null)
			{
				return null;
			}
			if (bos.length!=1)
			{
				throw new Exception("Expected one row returned for in getDigitalItemByDoiIdentifier, recieved "+bos.length);
			}
			return bos[0];
		}
		catch(Exception e)
		{
			try
			{
				conn.rollback();
			}
			catch(Exception ee)
			{
				throw new Exception("osmsDatabaseBase.getDigitalItemByDoiIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}
}


