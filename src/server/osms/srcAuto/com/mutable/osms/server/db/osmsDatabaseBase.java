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
package com.mutable.osms.server.db;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;

import java.sql.Connection;
import java.sql.DriverManager;

import java.util.Vector;
import java.io.*;

import com.mutable.osms.server.db.manager.*;
import com.mutable.osms.server.db.manager.base.*;
import com.mutable.osms.server.db.bean.*;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.server.app.osmsGlobalObjectManager;


public class osmsDatabaseBase implements Serializable
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



	protected osmsDvAlgorithmManager m_osmsDvAlgorithmManager = new osmsDvAlgorithmManager();
	protected osmsDvAltIdentifierManager m_osmsDvAltIdentifierManager = new osmsDvAltIdentifierManager();
	protected osmsDvCertificateManager m_osmsDvCertificateManager = new osmsDvCertificateManager();
	protected osmsDvCertificateTypeManager m_osmsDvCertificateTypeManager = new osmsDvCertificateTypeManager();
	protected osmsDvContentManager m_osmsDvContentManager = new osmsDvContentManager();
	protected osmsDvContentDoiManager m_osmsDvContentDoiManager = new osmsDvContentDoiManager();
	protected osmsDvContentGridManager m_osmsDvContentGridManager = new osmsDvContentGridManager();
	protected osmsDvDigitalItemManager m_osmsDvDigitalItemManager = new osmsDvDigitalItemManager();
	protected osmsDvDoiManager m_osmsDvDoiManager = new osmsDvDoiManager();
	protected osmsDvDoiAgentManager m_osmsDvDoiAgentManager = new osmsDvDoiAgentManager();
	protected osmsDvDoiAltIdentifierManager m_osmsDvDoiAltIdentifierManager = new osmsDvDoiAltIdentifierManager();
	protected osmsDvDoiProfileManager m_osmsDvDoiProfileManager = new osmsDvDoiProfileManager();
	protected osmsDvDoiTitleManager m_osmsDvDoiTitleManager = new osmsDvDoiTitleManager();
	protected osmsDvDoiTitleRelManager m_osmsDvDoiTitleRelManager = new osmsDvDoiTitleRelManager();
	protected osmsDvGridManager m_osmsDvGridManager = new osmsDvGridManager();
	protected osmsDvIdentifierTypeManager m_osmsDvIdentifierTypeManager = new osmsDvIdentifierTypeManager();
	protected osmsDvIpmpAgreementManager m_osmsDvIpmpAgreementManager = new osmsDvIpmpAgreementManager();
	protected osmsDvIpmpLicenseManager m_osmsDvIpmpLicenseManager = new osmsDvIpmpLicenseManager();
	protected osmsDvLoginHistoryManager m_osmsDvLoginHistoryManager = new osmsDvLoginHistoryManager();
	protected osmsDvOrgTypeManager m_osmsDvOrgTypeManager = new osmsDvOrgTypeManager();
	protected osmsDvOrganizationManager m_osmsDvOrganizationManager = new osmsDvOrganizationManager();
	protected osmsDvPkControlManager m_osmsDvPkControlManager = new osmsDvPkControlManager();
	protected osmsDvUsersManager m_osmsDvUsersManager = new osmsDvUsersManager();




	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE/PROTECTED METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------
	// convertBean2BO
	//------------------------------------------------------------------

	protected osmsAlgorithm[] convertBean2BO(osmsDvAlgorithmBean[] beans)
	{
		if(beans!=null)
		{
			osmsAlgorithm[] bos =new osmsAlgorithm[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsAlgorithm();
				bos[i].setAlgorithmBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsAltIdentifier[] convertBean2BO(osmsDvAltIdentifierBean[] beans)
	{
		if(beans!=null)
		{
			osmsAltIdentifier[] bos =new osmsAltIdentifier[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsAltIdentifier();
				bos[i].setAltIdentifierBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsCertificate[] convertBean2BO(osmsDvCertificateBean[] beans)
	{
		if(beans!=null)
		{
			osmsCertificate[] bos =new osmsCertificate[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsCertificate();
				bos[i].setCertificateBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsCertificateType[] convertBean2BO(osmsDvCertificateTypeBean[] beans)
	{
		if(beans!=null)
		{
			osmsCertificateType[] bos =new osmsCertificateType[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsCertificateType();
				bos[i].setCertificateTypeBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsContent[] convertBean2BO(osmsDvContentBean[] beans)
	{
		if(beans!=null)
		{
			osmsContent[] bos =new osmsContent[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsContent();
				bos[i].setContentBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsContentDoi[] convertBean2BO(osmsDvContentDoiBean[] beans)
	{
		if(beans!=null)
		{
			osmsContentDoi[] bos =new osmsContentDoi[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsContentDoi();
				bos[i].setContentDoiBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsContentGrid[] convertBean2BO(osmsDvContentGridBean[] beans)
	{
		if(beans!=null)
		{
			osmsContentGrid[] bos =new osmsContentGrid[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsContentGrid();
				bos[i].setContentGridBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsDigitalItem[] convertBean2BO(osmsDvDigitalItemBean[] beans)
	{
		if(beans!=null)
		{
			osmsDigitalItem[] bos =new osmsDigitalItem[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsDigitalItem();
				bos[i].setDigitalItemBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsDoi[] convertBean2BO(osmsDvDoiBean[] beans)
	{
		if(beans!=null)
		{
			osmsDoi[] bos =new osmsDoi[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsDoi();
				bos[i].setDoiBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsDoiAgent[] convertBean2BO(osmsDvDoiAgentBean[] beans)
	{
		if(beans!=null)
		{
			osmsDoiAgent[] bos =new osmsDoiAgent[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsDoiAgent();
				bos[i].setDoiAgentBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsDoiAltIdentifier[] convertBean2BO(osmsDvDoiAltIdentifierBean[] beans)
	{
		if(beans!=null)
		{
			osmsDoiAltIdentifier[] bos =new osmsDoiAltIdentifier[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsDoiAltIdentifier();
				bos[i].setDoiAltIdentifierBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsDoiProfile[] convertBean2BO(osmsDvDoiProfileBean[] beans)
	{
		if(beans!=null)
		{
			osmsDoiProfile[] bos =new osmsDoiProfile[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsDoiProfile();
				bos[i].setDoiProfileBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsDoiTitle[] convertBean2BO(osmsDvDoiTitleBean[] beans)
	{
		if(beans!=null)
		{
			osmsDoiTitle[] bos =new osmsDoiTitle[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsDoiTitle();
				bos[i].setDoiTitleBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsDoiTitleRel[] convertBean2BO(osmsDvDoiTitleRelBean[] beans)
	{
		if(beans!=null)
		{
			osmsDoiTitleRel[] bos =new osmsDoiTitleRel[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsDoiTitleRel();
				bos[i].setDoiTitleRelBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsGrid[] convertBean2BO(osmsDvGridBean[] beans)
	{
		if(beans!=null)
		{
			osmsGrid[] bos =new osmsGrid[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsGrid();
				bos[i].setGridBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsIdentifierType[] convertBean2BO(osmsDvIdentifierTypeBean[] beans)
	{
		if(beans!=null)
		{
			osmsIdentifierType[] bos =new osmsIdentifierType[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsIdentifierType();
				bos[i].setIdentifierTypeBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsIpmpAgreement[] convertBean2BO(osmsDvIpmpAgreementBean[] beans)
	{
		if(beans!=null)
		{
			osmsIpmpAgreement[] bos =new osmsIpmpAgreement[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsIpmpAgreement();
				bos[i].setIpmpAgreementBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsIpmpLicense[] convertBean2BO(osmsDvIpmpLicenseBean[] beans)
	{
		if(beans!=null)
		{
			osmsIpmpLicense[] bos =new osmsIpmpLicense[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsIpmpLicense();
				bos[i].setIpmpLicenseBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsLoginHistory[] convertBean2BO(osmsDvLoginHistoryBean[] beans)
	{
		if(beans!=null)
		{
			osmsLoginHistory[] bos =new osmsLoginHistory[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsLoginHistory();
				bos[i].setLoginHistoryBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsOrgType[] convertBean2BO(osmsDvOrgTypeBean[] beans)
	{
		if(beans!=null)
		{
			osmsOrgType[] bos =new osmsOrgType[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsOrgType();
				bos[i].setOrgTypeBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsOrganization[] convertBean2BO(osmsDvOrganizationBean[] beans)
	{
		if(beans!=null)
		{
			osmsOrganization[] bos =new osmsOrganization[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsOrganization();
				bos[i].setOrganizationBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsPkControl[] convertBean2BO(osmsDvPkControlBean[] beans)
	{
		if(beans!=null)
		{
			osmsPkControl[] bos =new osmsPkControl[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsPkControl();
				bos[i].setPkControlBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	protected osmsUsers[] convertBean2BO(osmsDvUsersBean[] beans)
	{
		if(beans!=null)
		{
			osmsUsers[] bos =new osmsUsers[beans.length];
			for(int i=0;i<beans.length;i++)
			{
				bos[i]= new osmsUsers();
				bos[i].setUsersBean(beans[i]);
			}
			return bos;
		}
		return null;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//------------------------------------------------------------------
	// Algorithm
	//------------------------------------------------------------------
	public osmsAlgorithm[] getAlgorithm()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsAlgorithm[] bos = convertBean2BO(m_osmsDvAlgorithmManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getAlgorithm()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsAlgorithm getAlgorithmByAlgorithmId(Integer pAlgorithmId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsAlgorithm[] bos = convertBean2BO(m_osmsDvAlgorithmManager.getByAlgorithmId( pAlgorithmId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getAlgorithmByAlgorithmId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getAlgorithmByAlgorithmId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsAlgorithm getAlgorithmByObjectIdentifier(String pObjectIdentifier)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsAlgorithm[] bos = convertBean2BO(m_osmsDvAlgorithmManager.getByObjectIdentifier( pObjectIdentifier,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getAlgorithmByObjectIdentifier, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getAlgorithmByObjectIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertAlgorithm(osmsAlgorithm bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvAlgorithmManager.insert(bo.getAlgorithmBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateAlgorithm(osmsAlgorithm bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvAlgorithmManager.update(bo.getAlgorithmBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// AltIdentifier
	//------------------------------------------------------------------
	public osmsAltIdentifier[] getAltIdentifier()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsAltIdentifier[] bos = convertBean2BO(m_osmsDvAltIdentifierManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getAltIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsAltIdentifier getAltIdentifierByAltIdentifierId(Integer pAltIdentifierId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsAltIdentifier[] bos = convertBean2BO(m_osmsDvAltIdentifierManager.getByAltIdentifierId( pAltIdentifierId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getAltIdentifierByAltIdentifierId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getAltIdentifierByAltIdentifierId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsAltIdentifier getAltIdentifierByIdentifierAndIdentifierTypeCode(String pIdentifier,String pIdentifierTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsAltIdentifier[] bos = convertBean2BO(m_osmsDvAltIdentifierManager.getByIdentifierAndIdentifierTypeCode( pIdentifier, pIdentifierTypeCode,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getAltIdentifierByIdentifierAndIdentifierTypeCode, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getAltIdentifierByIdentifierAndIdentifierTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsAltIdentifier[] getAltIdentifierByIdentifierTypeCode(String pIdentifierTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsAltIdentifier[] bos = convertBean2BO(m_osmsDvAltIdentifierManager.getByIdentifierTypeCode( pIdentifierTypeCode,conn));
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
				throw new Exception("osmsDatabaseBase.getAltIdentifierByIdentifierTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertAltIdentifier(osmsAltIdentifier bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvAltIdentifierManager.insert(bo.getAltIdentifierBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateAltIdentifier(osmsAltIdentifier bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvAltIdentifierManager.update(bo.getAltIdentifierBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// Certificate
	//------------------------------------------------------------------
	public osmsCertificate[] getCertificate()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificate[] bos = convertBean2BO(m_osmsDvCertificateManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getCertificate()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsCertificate getCertificateByCertificateId(Integer pCertificateId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificate[] bos = convertBean2BO(m_osmsDvCertificateManager.getByCertificateId( pCertificateId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getCertificateByCertificateId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getCertificateByCertificateId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsCertificate getCertificateBySerialNum(String pSerialNum)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificate[] bos = convertBean2BO(m_osmsDvCertificateManager.getBySerialNum( pSerialNum,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getCertificateBySerialNum, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getCertificateBySerialNum()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsCertificate[] getCertificateByCertificateTypeCode(String pCertificateTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificate[] bos = convertBean2BO(m_osmsDvCertificateManager.getByCertificateTypeCode( pCertificateTypeCode,conn));
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
				throw new Exception("osmsDatabaseBase.getCertificateByCertificateTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsCertificate[] getCertificateByAlgorithmId(Integer pAlgorithmId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificate[] bos = convertBean2BO(m_osmsDvCertificateManager.getByAlgorithmId( pAlgorithmId,conn));
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
				throw new Exception("osmsDatabaseBase.getCertificateByAlgorithmId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsCertificate[] getCertificateByCaCertificateId(Integer pCaCertificateId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificate[] bos = convertBean2BO(m_osmsDvCertificateManager.getByCaCertificateId( pCaCertificateId,conn));
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
				throw new Exception("osmsDatabaseBase.getCertificateByCaCertificateId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertCertificate(osmsCertificate bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvCertificateManager.insert(bo.getCertificateBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateCertificate(osmsCertificate bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvCertificateManager.update(bo.getCertificateBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// CertificateType
	//------------------------------------------------------------------
	public osmsCertificateType[] getCertificateType()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificateType[] bos = convertBean2BO(m_osmsDvCertificateTypeManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getCertificateType()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsCertificateType getCertificateTypeByCertificateTypeCode(String pCertificateTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsCertificateType[] bos = convertBean2BO(m_osmsDvCertificateTypeManager.getByCertificateTypeCode( pCertificateTypeCode,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getCertificateTypeByCertificateTypeCode, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getCertificateTypeByCertificateTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertCertificateType(osmsCertificateType bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvCertificateTypeManager.insert(bo.getCertificateTypeBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateCertificateType(osmsCertificateType bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvCertificateTypeManager.update(bo.getCertificateTypeBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// Content
	//------------------------------------------------------------------
	public osmsContent[] getContent()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContent[] bos = convertBean2BO(m_osmsDvContentManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getContent()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsContent getContentByContentId(Integer pContentId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContent[] bos = convertBean2BO(m_osmsDvContentManager.getByContentId( pContentId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getContentByContentId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getContentByContentId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsContent getContentByPrimaryIdentifierAndIdentifierTypeCode(String pPrimaryIdentifier,String pIdentifierTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContent[] bos = convertBean2BO(m_osmsDvContentManager.getByPrimaryIdentifierAndIdentifierTypeCode( pPrimaryIdentifier, pIdentifierTypeCode,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getContentByPrimaryIdentifierAndIdentifierTypeCode, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getContentByPrimaryIdentifierAndIdentifierTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsContent[] getContentByRegisteredBy(Integer pRegisteredBy)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContent[] bos = convertBean2BO(m_osmsDvContentManager.getByRegisteredBy( pRegisteredBy,conn));
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
				throw new Exception("osmsDatabaseBase.getContentByRegisteredBy()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsContent[] getContentByIdentifierTypeCode(String pIdentifierTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContent[] bos = convertBean2BO(m_osmsDvContentManager.getByIdentifierTypeCode( pIdentifierTypeCode,conn));
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
				throw new Exception("osmsDatabaseBase.getContentByIdentifierTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertContent(osmsContent bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvContentManager.insert(bo.getContentBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateContent(osmsContent bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvContentManager.update(bo.getContentBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// ContentDoi
	//------------------------------------------------------------------
	public osmsContentDoi[] getContentDoi()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContentDoi[] bos = convertBean2BO(m_osmsDvContentDoiManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getContentDoi()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsContentDoi getContentDoiByContentId(Integer pContentId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContentDoi[] bos = convertBean2BO(m_osmsDvContentDoiManager.getByContentId( pContentId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getContentDoiByContentId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getContentDoiByContentId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsContentDoi getContentDoiByDoiId(Integer pDoiId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContentDoi[] bos = convertBean2BO(m_osmsDvContentDoiManager.getByDoiId( pDoiId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getContentDoiByDoiId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getContentDoiByDoiId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertContentDoi(osmsContentDoi bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvContentDoiManager.insert(bo.getContentDoiBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateContentDoi(osmsContentDoi bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvContentDoiManager.update(bo.getContentDoiBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// ContentGrid
	//------------------------------------------------------------------
	public osmsContentGrid[] getContentGrid()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContentGrid[] bos = convertBean2BO(m_osmsDvContentGridManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getContentGrid()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsContentGrid getContentGridByContentId(Integer pContentId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContentGrid[] bos = convertBean2BO(m_osmsDvContentGridManager.getByContentId( pContentId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getContentGridByContentId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getContentGridByContentId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsContentGrid getContentGridByGridId(Integer pGridId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsContentGrid[] bos = convertBean2BO(m_osmsDvContentGridManager.getByGridId( pGridId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getContentGridByGridId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getContentGridByGridId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertContentGrid(osmsContentGrid bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvContentGridManager.insert(bo.getContentGridBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateContentGrid(osmsContentGrid bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvContentGridManager.update(bo.getContentGridBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// DigitalItem
	//------------------------------------------------------------------
	public osmsDigitalItem[] getDigitalItem()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItem()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsDigitalItem getDigitalItemByDigitalItemId(Integer pDigitalItemId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getByDigitalItemId( pDigitalItemId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDigitalItemByDigitalItemId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDigitalItemByDigitalItemId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsDigitalItem[] getDigitalItemByCaCertificateId(Integer pCaCertificateId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getByCaCertificateId( pCaCertificateId,conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItemByCaCertificateId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDigitalItem[] getDigitalItemByDoiId(Integer pDoiId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getByDoiId( pDoiId,conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItemByDoiId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDigitalItem[] getDigitalItemByContentId(Integer pContentId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getByContentId( pContentId,conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItemByContentId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDigitalItem[] getDigitalItemByKeyAlgorithmId(Integer pKeyAlgorithmId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getByKeyAlgorithmId( pKeyAlgorithmId,conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItemByKeyAlgorithmId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDigitalItem[] getDigitalItemByDigestAlgorithmId(Integer pDigestAlgorithmId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getByDigestAlgorithmId( pDigestAlgorithmId,conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItemByDigestAlgorithmId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDigitalItem[] getDigitalItemBySigAlgorithmId(Integer pSigAlgorithmId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getBySigAlgorithmId( pSigAlgorithmId,conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItemBySigAlgorithmId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDigitalItem[] getDigitalItemByRegisteredBy(Integer pRegisteredBy)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDigitalItem[] bos = convertBean2BO(m_osmsDvDigitalItemManager.getByRegisteredBy( pRegisteredBy,conn));
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
				throw new Exception("osmsDatabaseBase.getDigitalItemByRegisteredBy()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertDigitalItem(osmsDigitalItem bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDigitalItemManager.insert(bo.getDigitalItemBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateDigitalItem(osmsDigitalItem bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDigitalItemManager.update(bo.getDigitalItemBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// Doi
	//------------------------------------------------------------------
	public osmsDoi[] getDoi()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoi[] bos = convertBean2BO(m_osmsDvDoiManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getDoi()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsDoi getDoiByDoiId(Integer pDoiId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoi[] bos = convertBean2BO(m_osmsDvDoiManager.getByDoiId( pDoiId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDoiByDoiId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDoiByDoiId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDoi getDoiByDoiIdentifier(String pDoiIdentifier)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoi[] bos = convertBean2BO(m_osmsDvDoiManager.getByDoiIdentifier( pDoiIdentifier,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDoiByDoiIdentifier, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDoiByDoiIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsDoi[] getDoiByDoiProfileCode(String pDoiProfileCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoi[] bos = convertBean2BO(m_osmsDvDoiManager.getByDoiProfileCode( pDoiProfileCode,conn));
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
				throw new Exception("osmsDatabaseBase.getDoiByDoiProfileCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertDoi(osmsDoi bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiManager.insert(bo.getDoiBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateDoi(osmsDoi bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiManager.update(bo.getDoiBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// DoiAgent
	//------------------------------------------------------------------
	public osmsDoiAgent[] getDoiAgent()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiAgent[] bos = convertBean2BO(m_osmsDvDoiAgentManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getDoiAgent()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsDoiAgent getDoiAgentByDoiAgentId(Integer pDoiAgentId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiAgent[] bos = convertBean2BO(m_osmsDvDoiAgentManager.getByDoiAgentId( pDoiAgentId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDoiAgentByDoiAgentId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDoiAgentByDoiAgentId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsDoiAgent[] getDoiAgentByDoiId(Integer pDoiId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiAgent[] bos = convertBean2BO(m_osmsDvDoiAgentManager.getByDoiId( pDoiId,conn));
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
				throw new Exception("osmsDatabaseBase.getDoiAgentByDoiId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertDoiAgent(osmsDoiAgent bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiAgentManager.insert(bo.getDoiAgentBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateDoiAgent(osmsDoiAgent bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiAgentManager.update(bo.getDoiAgentBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// DoiAltIdentifier
	//------------------------------------------------------------------
	public osmsDoiAltIdentifier[] getDoiAltIdentifier()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiAltIdentifier[] bos = convertBean2BO(m_osmsDvDoiAltIdentifierManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getDoiAltIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsDoiAltIdentifier getDoiAltIdentifierByDoiIdAndAltIdentifierId(Integer pDoiId,Integer pAltIdentifierId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiAltIdentifier[] bos = convertBean2BO(m_osmsDvDoiAltIdentifierManager.getByDoiIdAndAltIdentifierId( pDoiId, pAltIdentifierId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDoiAltIdentifierByDoiIdAndAltIdentifierId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDoiAltIdentifierByDoiIdAndAltIdentifierId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsDoiAltIdentifier[] getDoiAltIdentifierByDoiId(Integer pDoiId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiAltIdentifier[] bos = convertBean2BO(m_osmsDvDoiAltIdentifierManager.getByDoiId( pDoiId,conn));
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
				throw new Exception("osmsDatabaseBase.getDoiAltIdentifierByDoiId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDoiAltIdentifier[] getDoiAltIdentifierByAltIdentifierId(Integer pAltIdentifierId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiAltIdentifier[] bos = convertBean2BO(m_osmsDvDoiAltIdentifierManager.getByAltIdentifierId( pAltIdentifierId,conn));
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
				throw new Exception("osmsDatabaseBase.getDoiAltIdentifierByAltIdentifierId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertDoiAltIdentifier(osmsDoiAltIdentifier bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiAltIdentifierManager.insert(bo.getDoiAltIdentifierBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateDoiAltIdentifier(osmsDoiAltIdentifier bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiAltIdentifierManager.update(bo.getDoiAltIdentifierBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// DoiProfile
	//------------------------------------------------------------------
	public osmsDoiProfile[] getDoiProfile()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiProfile[] bos = convertBean2BO(m_osmsDvDoiProfileManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getDoiProfile()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsDoiProfile getDoiProfileByDoiProfileCode(String pDoiProfileCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiProfile[] bos = convertBean2BO(m_osmsDvDoiProfileManager.getByDoiProfileCode( pDoiProfileCode,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDoiProfileByDoiProfileCode, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDoiProfileByDoiProfileCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertDoiProfile(osmsDoiProfile bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiProfileManager.insert(bo.getDoiProfileBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateDoiProfile(osmsDoiProfile bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiProfileManager.update(bo.getDoiProfileBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// DoiTitle
	//------------------------------------------------------------------
	public osmsDoiTitle[] getDoiTitle()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiTitle[] bos = convertBean2BO(m_osmsDvDoiTitleManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getDoiTitle()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsDoiTitle getDoiTitleByTitleId(Integer pTitleId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiTitle[] bos = convertBean2BO(m_osmsDvDoiTitleManager.getByTitleId( pTitleId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDoiTitleByTitleId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDoiTitleByTitleId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertDoiTitle(osmsDoiTitle bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiTitleManager.insert(bo.getDoiTitleBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateDoiTitle(osmsDoiTitle bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiTitleManager.update(bo.getDoiTitleBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// DoiTitleRel
	//------------------------------------------------------------------
	public osmsDoiTitleRel[] getDoiTitleRel()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiTitleRel[] bos = convertBean2BO(m_osmsDvDoiTitleRelManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getDoiTitleRel()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsDoiTitleRel getDoiTitleRelByDoiIdAndTitleId(Integer pDoiId,Integer pTitleId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiTitleRel[] bos = convertBean2BO(m_osmsDvDoiTitleRelManager.getByDoiIdAndTitleId( pDoiId, pTitleId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getDoiTitleRelByDoiIdAndTitleId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getDoiTitleRelByDoiIdAndTitleId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsDoiTitleRel[] getDoiTitleRelByDoiId(Integer pDoiId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiTitleRel[] bos = convertBean2BO(m_osmsDvDoiTitleRelManager.getByDoiId( pDoiId,conn));
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
				throw new Exception("osmsDatabaseBase.getDoiTitleRelByDoiId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsDoiTitleRel[] getDoiTitleRelByTitleId(Integer pTitleId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsDoiTitleRel[] bos = convertBean2BO(m_osmsDvDoiTitleRelManager.getByTitleId( pTitleId,conn));
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
				throw new Exception("osmsDatabaseBase.getDoiTitleRelByTitleId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertDoiTitleRel(osmsDoiTitleRel bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiTitleRelManager.insert(bo.getDoiTitleRelBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateDoiTitleRel(osmsDoiTitleRel bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvDoiTitleRelManager.update(bo.getDoiTitleRelBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// Grid
	//------------------------------------------------------------------
	public osmsGrid[] getGrid()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsGrid[] bos = convertBean2BO(m_osmsDvGridManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getGrid()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsGrid getGridByGridId(Integer pGridId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsGrid[] bos = convertBean2BO(m_osmsDvGridManager.getByGridId( pGridId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getGridByGridId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getGridByGridId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsGrid getGridByGrid(String pGrid)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsGrid[] bos = convertBean2BO(m_osmsDvGridManager.getByGrid( pGrid,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getGridByGrid, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getGridByGrid()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertGrid(osmsGrid bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvGridManager.insert(bo.getGridBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateGrid(osmsGrid bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvGridManager.update(bo.getGridBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// IdentifierType
	//------------------------------------------------------------------
	public osmsIdentifierType[] getIdentifierType()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIdentifierType[] bos = convertBean2BO(m_osmsDvIdentifierTypeManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getIdentifierType()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsIdentifierType getIdentifierTypeByIdentifierTypeCode(String pIdentifierTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIdentifierType[] bos = convertBean2BO(m_osmsDvIdentifierTypeManager.getByIdentifierTypeCode( pIdentifierTypeCode,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getIdentifierTypeByIdentifierTypeCode, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getIdentifierTypeByIdentifierTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertIdentifierType(osmsIdentifierType bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvIdentifierTypeManager.insert(bo.getIdentifierTypeBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateIdentifierType(osmsIdentifierType bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvIdentifierTypeManager.update(bo.getIdentifierTypeBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// IpmpAgreement
	//------------------------------------------------------------------
	public osmsIpmpAgreement[] getIpmpAgreement()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpAgreement()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsIpmpAgreement getIpmpAgreementByAgreementId(Integer pAgreementId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.getByAgreementId( pAgreementId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getIpmpAgreementByAgreementId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getIpmpAgreementByAgreementId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsIpmpAgreement[] getIpmpAgreementByRegisteredBy(Integer pRegisteredBy)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.getByRegisteredBy( pRegisteredBy,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpAgreementByRegisteredBy()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpAgreement[] getIpmpAgreementByAssignedToUser(Integer pAssignedToUser)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.getByAssignedToUser( pAssignedToUser,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpAgreementByAssignedToUser()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpAgreement[] getIpmpAgreementByAssignedToGroup(Integer pAssignedToGroup)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.getByAssignedToGroup( pAssignedToGroup,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpAgreementByAssignedToGroup()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpAgreement[] getIpmpAgreementByContentId(Integer pContentId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpAgreement[] bos = convertBean2BO(m_osmsDvIpmpAgreementManager.getByContentId( pContentId,conn));
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



	public void insertIpmpAgreement(osmsIpmpAgreement bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvIpmpAgreementManager.insert(bo.getIpmpAgreementBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateIpmpAgreement(osmsIpmpAgreement bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvIpmpAgreementManager.update(bo.getIpmpAgreementBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// IpmpLicense
	//------------------------------------------------------------------
	public osmsIpmpLicense[] getIpmpLicense()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpLicense()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsIpmpLicense getIpmpLicenseByLicenseId(Integer pLicenseId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByLicenseId( pLicenseId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getIpmpLicenseByLicenseId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseByLicenseId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpLicense getIpmpLicenseByLicenseIdentifier(String pLicenseIdentifier)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByLicenseIdentifier( pLicenseIdentifier,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getIpmpLicenseByLicenseIdentifier, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseByLicenseIdentifier()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsIpmpLicense[] getIpmpLicenseByAgreementId(Integer pAgreementId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByAgreementId( pAgreementId,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseByAgreementId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpLicense[] getIpmpLicenseByIssuedToUser(Integer pIssuedToUser)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByIssuedToUser( pIssuedToUser,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseByIssuedToUser()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpLicense[] getIpmpLicenseBySigAlgorithmId(Integer pSigAlgorithmId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getBySigAlgorithmId( pSigAlgorithmId,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseBySigAlgorithmId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpLicense[] getIpmpLicenseByDigestAlgorithmId(Integer pDigestAlgorithmId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByDigestAlgorithmId( pDigestAlgorithmId,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseByDigestAlgorithmId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpLicense[] getIpmpLicenseByDigitalItemId(Integer pDigitalItemId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByDigitalItemId( pDigitalItemId,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseByDigitalItemId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsIpmpLicense[] getIpmpLicenseByCaCertificateId(Integer pCaCertificateId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsIpmpLicense[] bos = convertBean2BO(m_osmsDvIpmpLicenseManager.getByCaCertificateId( pCaCertificateId,conn));
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
				throw new Exception("osmsDatabaseBase.getIpmpLicenseByCaCertificateId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertIpmpLicense(osmsIpmpLicense bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvIpmpLicenseManager.insert(bo.getIpmpLicenseBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateIpmpLicense(osmsIpmpLicense bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvIpmpLicenseManager.update(bo.getIpmpLicenseBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// LoginHistory
	//------------------------------------------------------------------
	public osmsLoginHistory[] getLoginHistory()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsLoginHistory[] bos = convertBean2BO(m_osmsDvLoginHistoryManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getLoginHistory()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsLoginHistory getLoginHistoryByLoginId(Integer pLoginId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsLoginHistory[] bos = convertBean2BO(m_osmsDvLoginHistoryManager.getByLoginId( pLoginId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getLoginHistoryByLoginId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getLoginHistoryByLoginId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsLoginHistory[] getLoginHistoryByUserId(Integer pUserId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsLoginHistory[] bos = convertBean2BO(m_osmsDvLoginHistoryManager.getByUserId( pUserId,conn));
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
				throw new Exception("osmsDatabaseBase.getLoginHistoryByUserId()" + e.toString() + " "+ee.toString());
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
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvLoginHistoryManager.insert(bo.getLoginHistoryBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateLoginHistory(osmsLoginHistory bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvLoginHistoryManager.update(bo.getLoginHistoryBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// OrgType
	//------------------------------------------------------------------
	public osmsOrgType[] getOrgType()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsOrgType[] bos = convertBean2BO(m_osmsDvOrgTypeManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getOrgType()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsOrgType getOrgTypeByOrgTypeCode(String pOrgTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsOrgType[] bos = convertBean2BO(m_osmsDvOrgTypeManager.getByOrgTypeCode( pOrgTypeCode,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getOrgTypeByOrgTypeCode, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getOrgTypeByOrgTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertOrgType(osmsOrgType bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvOrgTypeManager.insert(bo.getOrgTypeBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateOrgType(osmsOrgType bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvOrgTypeManager.update(bo.getOrgTypeBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// Organization
	//------------------------------------------------------------------
	public osmsOrganization[] getOrganization()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsOrganization[] bos = convertBean2BO(m_osmsDvOrganizationManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getOrganization()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsOrganization getOrganizationByOrganizationId(Integer pOrganizationId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsOrganization[] bos = convertBean2BO(m_osmsDvOrganizationManager.getByOrganizationId( pOrganizationId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getOrganizationByOrganizationId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getOrganizationByOrganizationId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsOrganization getOrganizationByOrganizationName(String pOrganizationName)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsOrganization[] bos = convertBean2BO(m_osmsDvOrganizationManager.getByOrganizationName( pOrganizationName,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getOrganizationByOrganizationName, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getOrganizationByOrganizationName()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsOrganization[] getOrganizationByContactUser(Integer pContactUser)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsOrganization[] bos = convertBean2BO(m_osmsDvOrganizationManager.getByContactUser( pContactUser,conn));
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
				throw new Exception("osmsDatabaseBase.getOrganizationByContactUser()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsOrganization[] getOrganizationByOrgTypeCode(String pOrgTypeCode)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsOrganization[] bos = convertBean2BO(m_osmsDvOrganizationManager.getByOrgTypeCode( pOrgTypeCode,conn));
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
				throw new Exception("osmsDatabaseBase.getOrganizationByOrgTypeCode()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertOrganization(osmsOrganization bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvOrganizationManager.insert(bo.getOrganizationBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateOrganization(osmsOrganization bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvOrganizationManager.update(bo.getOrganizationBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// PkControl
	//------------------------------------------------------------------
	public osmsPkControl[] getPkControl()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsPkControl[] bos = convertBean2BO(m_osmsDvPkControlManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getPkControl()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsPkControl getPkControlByTableName(String pTableName)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsPkControl[] bos = convertBean2BO(m_osmsDvPkControlManager.getByTableName( pTableName,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getPkControlByTableName, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getPkControlByTableName()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}


	public void insertPkControl(osmsPkControl bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvPkControlManager.insert(bo.getPkControlBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updatePkControl(osmsPkControl bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvPkControlManager.update(bo.getPkControlBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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





	//------------------------------------------------------------------
	// Users
	//------------------------------------------------------------------
	public osmsUsers[] getUsers()
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsUsers[] bos = convertBean2BO(m_osmsDvUsersManager.get(conn));
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
				throw new Exception("osmsDatabaseBase.getUsers()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}
	}




	public osmsUsers getUsersByUserId(Integer pUserId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsUsers[] bos = convertBean2BO(m_osmsDvUsersManager.getByUserId( pUserId,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getUsersByUserId, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getUsersByUserId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsUsers getUsersByUserName(String pUserName)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsUsers[] bos = convertBean2BO(m_osmsDvUsersManager.getByUserName( pUserName,conn));
			if(bos!=null)
			{
				if (bos.length!=1) throw new Exception("Expected one row returned for in getUsersByUserName, recieved "+bos.length);
			}
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			conn.commit();

			//RETURN
			if(bos==null) return null;
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
				throw new Exception("osmsDatabaseBase.getUsersByUserName()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public osmsUsers[] getUsersByOrganizationId(Integer pOrganizationId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsUsers[] bos = convertBean2BO(m_osmsDvUsersManager.getByOrganizationId( pOrganizationId,conn));
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
				throw new Exception("osmsDatabaseBase.getUsersByOrganizationId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}




	public osmsUsers[] getUsersByCertificateId(Integer pCertificateId)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			osmsUsers[] bos = convertBean2BO(m_osmsDvUsersManager.getByCertificateId( pCertificateId,conn));
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
				throw new Exception("osmsDatabaseBase.getUsersByCertificateId()" + e.toString() + " "+ee.toString());
			}
			throw e;
		}
		finally
		{
			osmsGlobalObjectManager.getInstance().getDBPool().checkIn(conn);
		}

	}



	public void insertUsers(osmsUsers bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvUsersManager.insert(bo.getUsersBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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


	public void updateUsers(osmsUsers bo)
		throws Exception
	{
		Connection conn=null;
		try
		{
			conn= (Connection) (osmsGlobalObjectManager.getInstance().getDBPool().checkOut());
			//BEGIN DO WORK vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			m_osmsDvUsersManager.update(bo.getUsersBean(),conn);
			//END DO WORK ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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






}



/*
class osmsGlobalObjectManager
{
	private static osmsGlobalObjectManager instance = new osmsGlobalObjectManager();
	private osmsGlobalObjectManager()
	{
	}
	public static osmsGlobalObjectManager getInstance()
	{
		return instance;

	}
	dbPool m_dbPool = new dbPool();
	public dbPool getDBPool()
	{
		return m_dbPool;
	}
}
class dbPool
{
	private Connection m_conn;
	public dbPool()
	{
		try
		{
			System.out.println("Locating jdbc driver...");
			Class.forName ("org.gjt.mm.mysql.Driver");
			System.out.println("Located jdbc driver!");
			System.out.println("");

			System.out.println("Getting Connection...");
			m_conn = DriverManager.getConnection ("jdbc:mysql://localhost:3306/OSMS", "", "");
			m_conn.setAutoCommit(false);
			System.out.println("Got Connection!");
			System.out.println("");
		}
		catch (Exception ex)
		{
			System.out.println(ex.toString());
		}

	}
	public Connection checkOut()
	{
		return m_conn;
	}
	public void checkIn(Connection conn)
	{
	}
}
*/
