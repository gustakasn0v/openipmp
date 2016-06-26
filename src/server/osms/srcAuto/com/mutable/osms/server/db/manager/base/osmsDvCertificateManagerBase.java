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

public class osmsDvCertificateManagerBase implements Serializable
{
	private String m_tablename="CERTIFICATE";
	protected String getTableName(){return m_tablename;}
	protected String getSqlResultSet() {return m_sqlResultSet;}
	private String m_sqlResultSet=
		(
			(new StringBuffer())
			.append(" CERTIFICATE.CERTIFICATE_ID")
			.append(", ").append(" CERTIFICATE.CERTIFICATE_TYPE_CODE")
			.append(", ").append(" CERTIFICATE.CA_CERTIFICATE_ID")
			.append(", ").append(" CERTIFICATE.VERSION")
			.append(", ").append(" CERTIFICATE.SERIAL_NUM")
			.append(", ").append(" CERTIFICATE.NOT_VALID_BEFORE_DT")
			.append(", ").append(" CERTIFICATE.NOT_VALID_AFTER_DT")
			.append(", ").append(" CERTIFICATE.CERTIFICATE")
			.append(", ").append(" CERTIFICATE.PUBLIC_KEY")
			.append(", ").append(" CERTIFICATE.ENCRYPTED_PRIVATE_KEY")
			.append(", ").append(" CERTIFICATE.ENCRYPTION_KEY_ID")
			.append(", ").append(" CERTIFICATE.ALGORITHM_ID")
			.append(", ").append(" CERTIFICATE.REVOCATION_ID")
			.append(", ").append(" CERTIFICATE.ACTION_CODE")
			.append(", ").append(" CERTIFICATE.STATUS_FLAG")
			.append(", ").append(" CERTIFICATE.MAINTENANCE_FLAG")
			.append(", ").append(" CERTIFICATE.LAST_UPDATED_BY")
			.append(", ").append(" CERTIFICATE.LAST_UPDATED_ON")
			.append(", ").append(" CERTIFICATE.CREATED_BY")
			.append(", ").append(" CERTIFICATE.CREATED_ON")
		).toString();

/*
	private String m_sqlResultSet=" CERTIFICATE.CERTIFICATE_ID,  CERTIFICATE.CERTIFICATE_TYPE_CODE,  CERTIFICATE.CA_CERTIFICATE_ID,  CERTIFICATE.VERSION,  CERTIFICATE.SERIAL_NUM,  CERTIFICATE.NOT_VALID_BEFORE_DT,  CERTIFICATE.NOT_VALID_AFTER_DT,  CERTIFICATE.CERTIFICATE,  CERTIFICATE.PUBLIC_KEY,  CERTIFICATE.ENCRYPTED_PRIVATE_KEY,  CERTIFICATE.ENCRYPTION_KEY_ID,  CERTIFICATE.ALGORITHM_ID,  CERTIFICATE.REVOCATION_ID,  CERTIFICATE.ACTION_CODE,  CERTIFICATE.STATUS_FLAG,  CERTIFICATE.MAINTENANCE_FLAG,  CERTIFICATE.LAST_UPDATED_BY,  CERTIFICATE.LAST_UPDATED_ON,  CERTIFICATE.CREATED_BY,  CERTIFICATE.CREATED_ON";
*/
	//------------------------------------------------------------------
	// mapResultSet2Bean
	//------------------------------------------------------------------
	protected osmsDvCertificateBean mapResultSet2Bean(ResultSet rs)
		throws Exception
	{
			int i=1;

			osmsDvCertificateBean bean = new osmsDvCertificateBean();
			bean.setCertificateId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setCertificateTypeCode((String)ConvertObject2String(rs.getObject(i++)));
			bean.setCaCertificateId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setVersion((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setSerialNum((String)ConvertObject2String(rs.getObject(i++)));
			bean.setNotValidBeforeDt((Timestamp)ConvertObject2Timestamp(rs.getObject(i++)));
			bean.setNotValidAfterDt((Timestamp)ConvertObject2Timestamp(rs.getObject(i++)));
			bean.setCertificate((byte[])ConvertObject2byte(rs.getObject(i++)));
			bean.setPublicKey((byte[])ConvertObject2byte(rs.getObject(i++)));
			bean.setEncryptedPrivateKey((byte[])ConvertObject2byte(rs.getObject(i++)));
			bean.setEncryptionKeyId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setAlgorithmId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setRevocationId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setActionCode((String)ConvertObject2String(rs.getObject(i++)));
			bean.setStatusFlag((String)ConvertObject2String(rs.getObject(i++)));
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
		osmsDvPkControlBean[] bean = managerPkControl.getByTableName("certificate",conn);
		Long seq= bean[0].getCurrPkValue();
		bean[0].setCurrPkValue(new Long(seq.intValue()+1));
		managerPkControl.update(bean[0],conn);

		return new Long(seq.intValue()+1);
		

	}
*/

	//------------------------------------------------------------------
	// PROTECTED executeQuery
	//------------------------------------------------------------------
	protected osmsDvCertificateBean[] executeQuery(PreparedStatement statement,Connection conn)
		throws Exception
	{
		ResultSet rs=null;
		osmsDvCertificateBean[] ret=null;
		try
		{
			rs = statement.executeQuery();

			Vector beans = new Vector();
			while (rs.next())
			{

				beans.addElement(mapResultSet2Bean(rs));
			}
			if(beans.size() == 0) return null;

			ret = new osmsDvCertificateBean[beans.size()];
			for(int i=0;i<beans.size();i++)
				ret[i]=(osmsDvCertificateBean)beans.elementAt(i);

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
	protected osmsDvCertificateBean[] get(Connection conn,String postWhere)
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


	protected osmsDvCertificateBean[] getByCertificateId(Integer pCertificateId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" CERTIFICATE_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pCertificateId);

		return executeQuery(statement,conn);
	}

	protected osmsDvCertificateBean[] getBySerialNum(String pSerialNum,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" SERIAL_NUM = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pSerialNum);

		return executeQuery(statement,conn);
	}

	protected osmsDvCertificateBean[] getByCertificateTypeCode(String pCertificateTypeCode,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" CERTIFICATE_TYPE_CODE = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pCertificateTypeCode);

		return executeQuery(statement,conn);
	}

	protected osmsDvCertificateBean[] getByAlgorithmId(Integer pAlgorithmId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" ALGORITHM_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pAlgorithmId);

		return executeQuery(statement,conn);
	}

	protected osmsDvCertificateBean[] getByCaCertificateId(Integer pCaCertificateId,Connection conn,String postWhere)
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
	public osmsDvCertificateBean[] get(Connection conn)
		throws Exception
	{
		return get( conn,"");
	}

	public osmsDvCertificateBean[] getByCertificateId(Integer pCertificateId,Connection conn)
		throws Exception
	{
		return getByCertificateId( pCertificateId,conn,"");
	}

	public osmsDvCertificateBean[] getBySerialNum(String pSerialNum,Connection conn)
		throws Exception
	{
		return getBySerialNum( pSerialNum,conn,"");
	}

	public osmsDvCertificateBean[] getByCertificateTypeCode(String pCertificateTypeCode,Connection conn)
		throws Exception
	{
		return getByCertificateTypeCode( pCertificateTypeCode,conn,"");
	}

	public osmsDvCertificateBean[] getByAlgorithmId(Integer pAlgorithmId,Connection conn)
		throws Exception
	{
		return getByAlgorithmId( pAlgorithmId,conn,"");
	}

	public osmsDvCertificateBean[] getByCaCertificateId(Integer pCaCertificateId,Connection conn)
		throws Exception
	{
		return getByCaCertificateId( pCaCertificateId,conn,"");
	}




	//------------------------------------------------------------------
	// UPDATE
	//------------------------------------------------------------------
	public synchronized void update(osmsDvCertificateBean bean,Connection conn)
		throws Exception
	{
		//TEMPORARY SOLUTION TO SET TIME STAMPS
		bean.setLastUpdatedOn(new Timestamp(new Date().getTime()));

		StringBuffer sql = new StringBuffer();
		sql.append(" UPDATE  ")
		.append(getTableName())
		.append(" SET ")
			
		.append("CERTIFICATE_TYPE_CODE = ? ")
			.append(", ").append("CA_CERTIFICATE_ID = ? ")
			.append(", ").append("VERSION = ? ")
			.append(", ").append("SERIAL_NUM = ? ")
			.append(", ").append("NOT_VALID_BEFORE_DT = ? ")
			.append(", ").append("NOT_VALID_AFTER_DT = ? ")
			.append(", ").append("CERTIFICATE = ? ")
			.append(", ").append("PUBLIC_KEY = ? ")
			.append(", ").append("ENCRYPTED_PRIVATE_KEY = ? ")
			.append(", ").append("ENCRYPTION_KEY_ID = ? ")
			.append(", ").append("ALGORITHM_ID = ? ")
			.append(", ").append("REVOCATION_ID = ? ")
			.append(", ").append("ACTION_CODE = ? ")
			.append(", ").append("STATUS_FLAG = ? ")
			.append(", ").append("MAINTENANCE_FLAG = ? ")
			.append(", ").append("LAST_UPDATED_BY = ? ")
			.append(", ").append("LAST_UPDATED_ON = ? ")
			.append(", ").append("CREATED_BY = ? ")
			.append(", ").append("CREATED_ON = ? ")

		.append(" where ")
		.append("CERTIFICATE_ID = ? ")
		.append("");

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		if(bean.getCertificateTypeCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getCertificateTypeCode());
		if(bean.getCaCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCaCertificateId());
		if(bean.getVersion()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getVersion());
		if(bean.getSerialNum()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSerialNum());
		if(bean.getNotValidBeforeDt()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getNotValidBeforeDt());
		if(bean.getNotValidAfterDt()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getNotValidAfterDt());
		if(bean.getCertificate()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getCertificate());
		if(bean.getPublicKey()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getPublicKey());
		if(bean.getEncryptedPrivateKey()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getEncryptedPrivateKey());
		if(bean.getEncryptionKeyId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getEncryptionKeyId());
		if(bean.getAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAlgorithmId());
		if(bean.getRevocationId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getRevocationId());
		if(bean.getActionCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getActionCode());
		if(bean.getStatusFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getStatusFlag());
		if(bean.getMaintenanceFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getMaintenanceFlag());
		if(bean.getLastUpdatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastUpdatedBy());
		if(bean.getLastUpdatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getLastUpdatedOn());
		if(bean.getCreatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCreatedBy());
		if(bean.getCreatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getCreatedOn());

		if(bean.getCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCertificateId());


		statement.executeUpdate();
		statement.close();
	}




	//------------------------------------------------------------------
	// INSERT
	//------------------------------------------------------------------
	public void insert(osmsDvCertificateBean bean,Connection conn)
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
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")

		.append(")");



		PreparedStatement statement = conn.prepareStatement(sql.toString());

		int i=1;
		if(bean.getCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCertificateId());
		if(bean.getCertificateTypeCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getCertificateTypeCode());
		if(bean.getCaCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCaCertificateId());
		if(bean.getVersion()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getVersion());
		if(bean.getSerialNum()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSerialNum());
		if(bean.getNotValidBeforeDt()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getNotValidBeforeDt());
		if(bean.getNotValidAfterDt()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getNotValidAfterDt());
		if(bean.getCertificate()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getCertificate());
		if(bean.getPublicKey()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getPublicKey());
		if(bean.getEncryptedPrivateKey()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getEncryptedPrivateKey());
		if(bean.getEncryptionKeyId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getEncryptionKeyId());
		if(bean.getAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAlgorithmId());
		if(bean.getRevocationId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getRevocationId());
		if(bean.getActionCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getActionCode());
		if(bean.getStatusFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getStatusFlag());
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
