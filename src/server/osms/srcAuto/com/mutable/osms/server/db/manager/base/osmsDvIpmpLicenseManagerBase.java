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
package com.mutable.osms.server.db.manager.base;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;

import java.sql.ResultSet;
import java.sql.Connection;
import java.sql.PreparedStatement;

import java.io.Serializable;
import java.util.Vector;

import com.mutable.osms.server.db.bean.*;

public class osmsDvIpmpLicenseManagerBase implements Serializable
{
	private String m_tablename="IPMP_LICENSE";
	protected String getTableName(){return m_tablename;}
	protected String getSqlResultSet() {return m_sqlResultSet;}
	private String m_sqlResultSet=
		(
			(new StringBuffer())
			.append(" IPMP_LICENSE.LICENSE_ID")
			.append(", ").append(" IPMP_LICENSE.CA_CERTIFICATE_ID")
			.append(", ").append(" IPMP_LICENSE.LICENSE_IDENTIFIER")
			.append(", ").append(" IPMP_LICENSE.DIGITAL_ITEM_ID")
			.append(", ").append(" IPMP_LICENSE.ISSUED_TO_USER")
			.append(", ").append(" IPMP_LICENSE.AGREEMENT_ID")
			.append(", ").append(" IPMP_LICENSE.LICENSE_TYPE")
			.append(", ").append(" IPMP_LICENSE.XML_STRING")
			.append(", ").append(" IPMP_LICENSE.LICENSE_DIGEST")
			.append(", ").append(" IPMP_LICENSE.DIGEST_ALGORITHM_ID")
			.append(", ").append(" IPMP_LICENSE.LICENSE_SIGNATURE")
			.append(", ").append(" IPMP_LICENSE.SIG_ALGORITHM_ID")
			.append(", ").append(" IPMP_LICENSE.MAINTENANCE_FLAG")
			.append(", ").append(" IPMP_LICENSE.LAST_UPDATED_BY")
			.append(", ").append(" IPMP_LICENSE.LAST_UPDATED_ON")
			.append(", ").append(" IPMP_LICENSE.CREATED_BY")
			.append(", ").append(" IPMP_LICENSE.CREATED_ON")
		).toString();

/*
	private String m_sqlResultSet=" IPMP_LICENSE.LICENSE_ID,  IPMP_LICENSE.CA_CERTIFICATE_ID,  IPMP_LICENSE.LICENSE_IDENTIFIER,  IPMP_LICENSE.DIGITAL_ITEM_ID,  IPMP_LICENSE.ISSUED_TO_USER,  IPMP_LICENSE.AGREEMENT_ID,  IPMP_LICENSE.LICENSE_TYPE,  IPMP_LICENSE.XML_STRING,  IPMP_LICENSE.LICENSE_DIGEST,  IPMP_LICENSE.DIGEST_ALGORITHM_ID,  IPMP_LICENSE.LICENSE_SIGNATURE,  IPMP_LICENSE.SIG_ALGORITHM_ID,  IPMP_LICENSE.MAINTENANCE_FLAG,  IPMP_LICENSE.LAST_UPDATED_BY,  IPMP_LICENSE.LAST_UPDATED_ON,  IPMP_LICENSE.CREATED_BY,  IPMP_LICENSE.CREATED_ON";
*/
	//------------------------------------------------------------------
	// mapResultSet2Bean
	//------------------------------------------------------------------
	protected osmsDvIpmpLicenseBean mapResultSet2Bean(ResultSet rs)
		throws Exception
	{
			int i=1;

			osmsDvIpmpLicenseBean bean = new osmsDvIpmpLicenseBean();
			bean.setLicenseId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setCaCertificateId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setLicenseIdentifier((String)ConvertObject2String(rs.getObject(i++)));
			bean.setDigitalItemId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setIssuedToUser((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setAgreementId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setLicenseType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setXmlString((String)ConvertObject2String(rs.getObject(i++)));
			bean.setLicenseDigest((String)ConvertObject2String(rs.getObject(i++)));
			bean.setDigestAlgorithmId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setLicenseSignature((byte[])ConvertObject2byte(rs.getObject(i++)));
			bean.setSigAlgorithmId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setMaintenanceFlag((String)ConvertObject2String(rs.getObject(i++)));
			bean.setLastUpdatedBy((String)ConvertObject2String(rs.getObject(i++)));
			bean.setLastUpdatedOn((Timestamp)ConvertObject2Timestamp(rs.getObject(i++)));
			bean.setCreatedBy((String)ConvertObject2String(rs.getObject(i++)));
			bean.setCreatedOn((Timestamp)ConvertObject2Timestamp(rs.getObject(i++)));
			return bean;
	}

	//------------------------------------------------------------------
	// PROTECTED getNextSequence
	//------------------------------------------------------------------
/*
	protected Long getNextSequence(Connection conn)
		throws Exception
	{
		//GET NEXT SEQ NUMBER
		String sql = "SELECT "+this.getTableName()+"_SEQ.NEXTVAL FROM DUAL";
		PreparedStatement statement = conn.prepareStatement(sql.toString());
		ResultSet rs = statement.executeQuery();
		rs.next();
		Long seq = (Long)ConvertObject2Long(rs.getObject(1));
		rs.close();
		statement.close();
		return seq;

	
		osmsDvPkControlManagerBase managerPkControl = new osmsDvPkControlManagerBase();
		osmsDvPkControlBean[] bean = managerPkControl.getByTableName("ipmp_license",conn);
		Long seq= bean[0].getCurrPkValue();
		bean[0].setCurrPkValue(new Long(seq.intValue()+1));
		managerPkControl.update(bean[0],conn);

		return new Long(seq.intValue()+1);
		

	}
*/

	//------------------------------------------------------------------
	// PROTECTED executeQuery
	//------------------------------------------------------------------
	protected osmsDvIpmpLicenseBean[] executeQuery(PreparedStatement statement,Connection conn)
		throws Exception
	{
		ResultSet rs=null;
		osmsDvIpmpLicenseBean[] ret=null;
		try
		{
			rs = statement.executeQuery();

			Vector beans = new Vector();
			while (rs.next())
			{

				beans.addElement(mapResultSet2Bean(rs));
			}
			if(beans.size() == 0) return null;

			ret = new osmsDvIpmpLicenseBean[beans.size()];
			for(int i=0;i<beans.size();i++)
				ret[i]=(osmsDvIpmpLicenseBean)beans.elementAt(i);

		}
		finally
		{
			if(rs!=null)rs.close();
			if(statement!=null)statement.close();
		}
		return ret;
	}

	//------------------------------------------------------------------
	// PROTECTED SELECT
	//------------------------------------------------------------------
	protected osmsDvIpmpLicenseBean[] get(Connection conn,String postWhere)
		throws Exception
	{

		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)
			.append(" from  ")
			.append(getTableName())
			.append(" ");
		if(postWhere!=null && !postWhere.trim().equals(""))
			sql.append(" where ").append(postWhere);
/*		
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)
			.append(" from ")
			.append(getTableName());
		if(postWhere!=null && !postWhere.trim().equals(""))
			sql.append(" where ").append(postWhere);
*/
		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		return executeQuery(statement,conn);
	}


	protected osmsDvIpmpLicenseBean[] getByLicenseId(Integer pLicenseId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" LICENSE_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pLicenseId);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpLicenseBean[] getByLicenseIdentifier(String pLicenseIdentifier,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" LICENSE_IDENTIFIER = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pLicenseIdentifier);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpLicenseBean[] getByAgreementId(Integer pAgreementId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" AGREEMENT_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pAgreementId);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpLicenseBean[] getByIssuedToUser(Integer pIssuedToUser,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" ISSUED_TO_USER = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pIssuedToUser);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpLicenseBean[] getBySigAlgorithmId(Integer pSigAlgorithmId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" SIG_ALGORITHM_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pSigAlgorithmId);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpLicenseBean[] getByDigestAlgorithmId(Integer pDigestAlgorithmId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" DIGEST_ALGORITHM_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pDigestAlgorithmId);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpLicenseBean[] getByDigitalItemId(Integer pDigitalItemId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" DIGITAL_ITEM_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pDigitalItemId);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpLicenseBean[] getByCaCertificateId(Integer pCaCertificateId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" CA_CERTIFICATE_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pCaCertificateId);

		return executeQuery(statement,conn);
	}



	//------------------------------------------------------------------
	// SELECT
	//------------------------------------------------------------------
	public osmsDvIpmpLicenseBean[] get(Connection conn)
		throws Exception
	{
		return get( conn,"");
	}

	public osmsDvIpmpLicenseBean[] getByLicenseId(Integer pLicenseId,Connection conn)
		throws Exception
	{
		return getByLicenseId( pLicenseId,conn,"");
	}

	public osmsDvIpmpLicenseBean[] getByLicenseIdentifier(String pLicenseIdentifier,Connection conn)
		throws Exception
	{
		return getByLicenseIdentifier( pLicenseIdentifier,conn,"");
	}

	public osmsDvIpmpLicenseBean[] getByAgreementId(Integer pAgreementId,Connection conn)
		throws Exception
	{
		return getByAgreementId( pAgreementId,conn,"");
	}

	public osmsDvIpmpLicenseBean[] getByIssuedToUser(Integer pIssuedToUser,Connection conn)
		throws Exception
	{
		return getByIssuedToUser( pIssuedToUser,conn,"");
	}

	public osmsDvIpmpLicenseBean[] getBySigAlgorithmId(Integer pSigAlgorithmId,Connection conn)
		throws Exception
	{
		return getBySigAlgorithmId( pSigAlgorithmId,conn,"");
	}

	public osmsDvIpmpLicenseBean[] getByDigestAlgorithmId(Integer pDigestAlgorithmId,Connection conn)
		throws Exception
	{
		return getByDigestAlgorithmId( pDigestAlgorithmId,conn,"");
	}

	public osmsDvIpmpLicenseBean[] getByDigitalItemId(Integer pDigitalItemId,Connection conn)
		throws Exception
	{
		return getByDigitalItemId( pDigitalItemId,conn,"");
	}

	public osmsDvIpmpLicenseBean[] getByCaCertificateId(Integer pCaCertificateId,Connection conn)
		throws Exception
	{
		return getByCaCertificateId( pCaCertificateId,conn,"");
	}




	//------------------------------------------------------------------
	// UPDATE
	//------------------------------------------------------------------
	public synchronized void update(osmsDvIpmpLicenseBean bean,Connection conn)
		throws Exception
	{
		//TEMPORARY SOLUTION TO SET TIME STAMPS
		bean.setLastUpdatedOn(new Timestamp(new Date().getTime()));

		StringBuffer sql = new StringBuffer();
		sql.append(" UPDATE  ")
		.append(getTableName())
		.append(" SET ")
			
		.append("CA_CERTIFICATE_ID = ? ")
			.append(", ").append("LICENSE_IDENTIFIER = ? ")
			.append(", ").append("DIGITAL_ITEM_ID = ? ")
			.append(", ").append("ISSUED_TO_USER = ? ")
			.append(", ").append("AGREEMENT_ID = ? ")
			.append(", ").append("LICENSE_TYPE = ? ")
			.append(", ").append("XML_STRING = ? ")
			.append(", ").append("LICENSE_DIGEST = ? ")
			.append(", ").append("DIGEST_ALGORITHM_ID = ? ")
			.append(", ").append("LICENSE_SIGNATURE = ? ")
			.append(", ").append("SIG_ALGORITHM_ID = ? ")
			.append(", ").append("MAINTENANCE_FLAG = ? ")
			.append(", ").append("LAST_UPDATED_BY = ? ")
			.append(", ").append("LAST_UPDATED_ON = ? ")
			.append(", ").append("CREATED_BY = ? ")
			.append(", ").append("CREATED_ON = ? ")

		.append(" where ")
		.append("LICENSE_ID = ? ")
		.append("");

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		if(bean.getCaCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCaCertificateId());
		if(bean.getLicenseIdentifier()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseIdentifier());
		if(bean.getDigitalItemId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigitalItemId());
		if(bean.getIssuedToUser()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getIssuedToUser());
		if(bean.getAgreementId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAgreementId());
		if(bean.getLicenseType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseType());
		if(bean.getXmlString()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getXmlString());
		if(bean.getLicenseDigest()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseDigest());
		if(bean.getDigestAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigestAlgorithmId());
		if(bean.getLicenseSignature()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getLicenseSignature());
		if(bean.getSigAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getSigAlgorithmId());
		if(bean.getMaintenanceFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getMaintenanceFlag());
		if(bean.getLastUpdatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastUpdatedBy());
		if(bean.getLastUpdatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getLastUpdatedOn());
		if(bean.getCreatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCreatedBy());
		if(bean.getCreatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getCreatedOn());

		if(bean.getLicenseId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getLicenseId());


		statement.executeUpdate();
		statement.close();
	}




	//------------------------------------------------------------------
	// INSERT
	//------------------------------------------------------------------
	public void insert(osmsDvIpmpLicenseBean bean,Connection conn)
		throws Exception
	{

		//TEMPORARY SOLUTION TO SET TIME STAMPS
		bean.setCreatedOn(new Timestamp(new Date().getTime()));
		bean.setLastUpdatedOn(new Timestamp(new Date().getTime()));
		


		StringBuffer sql = new StringBuffer();
		sql.append(" INSERT INTO  ")
		.append(getTableName())

		.append("(")
			.append(m_sqlResultSet)
		.append(")")
		.append(" VALUES ")
		.append("(")

		.append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")

		.append(")");



		PreparedStatement statement = conn.prepareStatement(sql.toString());

		int i=1;
		if(bean.getLicenseId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getLicenseId());
		if(bean.getCaCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCaCertificateId());
		if(bean.getLicenseIdentifier()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseIdentifier());
		if(bean.getDigitalItemId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigitalItemId());
		if(bean.getIssuedToUser()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getIssuedToUser());
		if(bean.getAgreementId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAgreementId());
		if(bean.getLicenseType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseType());
		if(bean.getXmlString()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getXmlString());
		if(bean.getLicenseDigest()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseDigest());
		if(bean.getDigestAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigestAlgorithmId());
		if(bean.getLicenseSignature()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getLicenseSignature());
		if(bean.getSigAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getSigAlgorithmId());
		if(bean.getMaintenanceFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getMaintenanceFlag());
		if(bean.getLastUpdatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastUpdatedBy());
		if(bean.getLastUpdatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getLastUpdatedOn());
		if(bean.getCreatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCreatedBy());
		if(bean.getCreatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getCreatedOn());

		statement.executeUpdate();
		statement.close();
	}

	//------------------------------------------------------------------
	// CONVERT OBJECT
	//------------------------------------------------------------------
	protected Long ConvertObject2Long(Object obj)
	{
		if (obj==null)return null;
		if(obj.getClass().getName().equals("java.lang.Long"))
		{
			return (Long)obj;
		}
		else
		{
			java.math.BigDecimal b=null;
			Long l=null;
			b = (java.math.BigDecimal)obj;
			if(b==null) l = null;
			else l = new Long(b.longValue());
			return l;
		}
	}
	protected String ConvertObject2String(Object obj)
	{
		return (String)obj;
	}
	protected Float ConvertObject2Float(Object obj)
	{
		if(obj==null) return null;
		else if(obj.getClass().getName().equals("java.lang.Float"))
		{
			return (Float)obj;
		}
		else
		{
			Float f=null;
			java.math.BigDecimal b=null;
			b = (java.math.BigDecimal)obj;
			if(b==null) f = null;
			else f = new Float(b.floatValue());
			return f;
		}
	}
	protected Double ConvertObject2Double(Object obj)
	{
		if(obj==null) return null;
		else if(obj.getClass().getName().equals("java.lang.Double"))
		{
			return (Double)obj;
		}
		else
		{
			Double d=null;
			java.math.BigDecimal b=null;
			b = (java.math.BigDecimal)obj;
			if(b==null) d = null;
			else d = new Double(b.doubleValue());
			return d;
		}
	}
	protected Timestamp ConvertObject2Timestamp(Object obj)
	{
		return (Timestamp)obj;
	}
	protected byte[] ConvertObject2byte(Object obj)
	{
		return (byte[])obj;
	}
	protected char[] ConvertObject2char(Object obj)
	{
		return (char[])obj;
	}
	protected Integer ConvertObject2Integer(Object obj)
	{
		if (obj==null)return null;
		if(obj.getClass().getName().equals("java.lang.Integer"))
		{
			return (Integer)obj;
		}
		else 
		{
			java.math.BigDecimal b=null;
			Integer l=null;
			b = (java.math.BigDecimal)obj;
			if(b==null) l = null;
			else l = new Integer(b.intValue());
			return l;
		}
	}
	protected Boolean ConvertObject2Boolean(Object obj)
	{
		return (Boolean)obj;
	}
	protected Short ConvertObject2Short(Object obj)
	{
		return (Short)obj;
	}
	protected Byte ConvertObject2Byte(Object obj)
	{
		return (Byte)obj;
	}
	protected Date ConvertObject2Date(Object obj)
	{
		return (Date)obj;
	}
	protected Time ConvertObject2Time(Object obj)
	{
		return (Time)obj;
	}
}
