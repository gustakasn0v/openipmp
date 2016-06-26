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

public class osmsDvIpmpAgreementManagerBase implements Serializable
{
	private String m_tablename="IPMP_AGREEMENT";
	protected String getTableName(){return m_tablename;}
	protected String getSqlResultSet() {return m_sqlResultSet;}
	private String m_sqlResultSet=
		(
			(new StringBuffer())
			.append(" IPMP_AGREEMENT.AGREEMENT_ID")
			.append(", ").append(" IPMP_AGREEMENT.CONTENT_ID")
			.append(", ").append(" IPMP_AGREEMENT.START_DATE")
			.append(", ").append(" IPMP_AGREEMENT.END_DATE")
			.append(", ").append(" IPMP_AGREEMENT.USER_LICENSE_LIMIT")
			.append(", ").append(" IPMP_AGREEMENT.GLOBAL_LICENSE_LIMIT")
			.append(", ").append(" IPMP_AGREEMENT.LICENSE_TYPE")
			.append(", ").append(" IPMP_AGREEMENT.ASSIGNED_TO_USER")
			.append(", ").append(" IPMP_AGREEMENT.ASSIGNED_TO_GROUP")
			.append(", ").append(" IPMP_AGREEMENT.REGISTERED_BY")
			.append(", ").append(" IPMP_AGREEMENT.XML_STRING")
			.append(", ").append(" IPMP_AGREEMENT.MAINTENANCE_FLAG")
			.append(", ").append(" IPMP_AGREEMENT.LAST_UPDATED_BY")
			.append(", ").append(" IPMP_AGREEMENT.LAST_UPDATED_ON")
			.append(", ").append(" IPMP_AGREEMENT.CREATED_BY")
			.append(", ").append(" IPMP_AGREEMENT.CREATED_ON")
		).toString();

/*
	private String m_sqlResultSet=" IPMP_AGREEMENT.AGREEMENT_ID,  IPMP_AGREEMENT.CONTENT_ID,  IPMP_AGREEMENT.START_DATE,  IPMP_AGREEMENT.END_DATE,  IPMP_AGREEMENT.USER_LICENSE_LIMIT,  IPMP_AGREEMENT.GLOBAL_LICENSE_LIMIT,  IPMP_AGREEMENT.LICENSE_TYPE,  IPMP_AGREEMENT.ASSIGNED_TO_USER,  IPMP_AGREEMENT.ASSIGNED_TO_GROUP,  IPMP_AGREEMENT.REGISTERED_BY,  IPMP_AGREEMENT.XML_STRING,  IPMP_AGREEMENT.MAINTENANCE_FLAG,  IPMP_AGREEMENT.LAST_UPDATED_BY,  IPMP_AGREEMENT.LAST_UPDATED_ON,  IPMP_AGREEMENT.CREATED_BY,  IPMP_AGREEMENT.CREATED_ON";
*/
	//------------------------------------------------------------------
	// mapResultSet2Bean
	//------------------------------------------------------------------
	protected osmsDvIpmpAgreementBean mapResultSet2Bean(ResultSet rs)
		throws Exception
	{
			int i=1;

			osmsDvIpmpAgreementBean bean = new osmsDvIpmpAgreementBean();
			bean.setAgreementId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setContentId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setStartDate((Timestamp)ConvertObject2Timestamp(rs.getObject(i++)));
			bean.setEndDate((Timestamp)ConvertObject2Timestamp(rs.getObject(i++)));
			bean.setUserLicenseLimit((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setGlobalLicenseLimit((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setLicenseType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAssignedToUser((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setAssignedToGroup((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setRegisteredBy((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setXmlString((String)ConvertObject2String(rs.getObject(i++)));
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
		osmsDvPkControlBean[] bean = managerPkControl.getByTableName("ipmp_agreement",conn);
		Long seq= bean[0].getCurrPkValue();
		bean[0].setCurrPkValue(new Long(seq.intValue()+1));
		managerPkControl.update(bean[0],conn);

		return new Long(seq.intValue()+1);
		

	}
*/

	//------------------------------------------------------------------
	// PROTECTED executeQuery
	//------------------------------------------------------------------
	protected osmsDvIpmpAgreementBean[] executeQuery(PreparedStatement statement,Connection conn)
		throws Exception
	{
		ResultSet rs=null;
		osmsDvIpmpAgreementBean[] ret=null;
		try
		{
			rs = statement.executeQuery();

			Vector beans = new Vector();
			while (rs.next())
			{

				beans.addElement(mapResultSet2Bean(rs));
			}
			if(beans.size() == 0) return null;

			ret = new osmsDvIpmpAgreementBean[beans.size()];
			for(int i=0;i<beans.size();i++)
				ret[i]=(osmsDvIpmpAgreementBean)beans.elementAt(i);

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
	protected osmsDvIpmpAgreementBean[] get(Connection conn,String postWhere)
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


	protected osmsDvIpmpAgreementBean[] getByAgreementId(Integer pAgreementId,Connection conn,String postWhere)
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

	protected osmsDvIpmpAgreementBean[] getByRegisteredBy(Integer pRegisteredBy,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" REGISTERED_BY = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pRegisteredBy);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpAgreementBean[] getByAssignedToUser(Integer pAssignedToUser,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" ASSIGNED_TO_USER = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pAssignedToUser);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpAgreementBean[] getByAssignedToGroup(Integer pAssignedToGroup,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" ASSIGNED_TO_GROUP = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pAssignedToGroup);

		return executeQuery(statement,conn);
	}

	protected osmsDvIpmpAgreementBean[] getByContentId(Integer pContentId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" CONTENT_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pContentId);

		return executeQuery(statement,conn);
	}



	//------------------------------------------------------------------
	// SELECT
	//------------------------------------------------------------------
	public osmsDvIpmpAgreementBean[] get(Connection conn)
		throws Exception
	{
		return get( conn,"");
	}

	public osmsDvIpmpAgreementBean[] getByAgreementId(Integer pAgreementId,Connection conn)
		throws Exception
	{
		return getByAgreementId( pAgreementId,conn,"");
	}

	public osmsDvIpmpAgreementBean[] getByRegisteredBy(Integer pRegisteredBy,Connection conn)
		throws Exception
	{
		return getByRegisteredBy( pRegisteredBy,conn,"");
	}

	public osmsDvIpmpAgreementBean[] getByAssignedToUser(Integer pAssignedToUser,Connection conn)
		throws Exception
	{
		return getByAssignedToUser( pAssignedToUser,conn,"");
	}

	public osmsDvIpmpAgreementBean[] getByAssignedToGroup(Integer pAssignedToGroup,Connection conn)
		throws Exception
	{
		return getByAssignedToGroup( pAssignedToGroup,conn,"");
	}

	public osmsDvIpmpAgreementBean[] getByContentId(Integer pContentId,Connection conn)
		throws Exception
	{
		return getByContentId( pContentId,conn,"");
	}




	//------------------------------------------------------------------
	// UPDATE
	//------------------------------------------------------------------
	public synchronized void update(osmsDvIpmpAgreementBean bean,Connection conn)
		throws Exception
	{
		//TEMPORARY SOLUTION TO SET TIME STAMPS
		bean.setLastUpdatedOn(new Timestamp(new Date().getTime()));

		StringBuffer sql = new StringBuffer();
		sql.append(" UPDATE  ")
		.append(getTableName())
		.append(" SET ")
			
		.append("CONTENT_ID = ? ")
			.append(", ").append("START_DATE = ? ")
			.append(", ").append("END_DATE = ? ")
			.append(", ").append("USER_LICENSE_LIMIT = ? ")
			.append(", ").append("GLOBAL_LICENSE_LIMIT = ? ")
			.append(", ").append("LICENSE_TYPE = ? ")
			.append(", ").append("ASSIGNED_TO_USER = ? ")
			.append(", ").append("ASSIGNED_TO_GROUP = ? ")
			.append(", ").append("REGISTERED_BY = ? ")
			.append(", ").append("XML_STRING = ? ")
			.append(", ").append("MAINTENANCE_FLAG = ? ")
			.append(", ").append("LAST_UPDATED_BY = ? ")
			.append(", ").append("LAST_UPDATED_ON = ? ")
			.append(", ").append("CREATED_BY = ? ")
			.append(", ").append("CREATED_ON = ? ")

		.append(" where ")
		.append("AGREEMENT_ID = ? ")
		.append("");

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		if(bean.getContentId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getContentId());
		if(bean.getStartDate()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getStartDate());
		if(bean.getEndDate()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getEndDate());
		if(bean.getUserLicenseLimit()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getUserLicenseLimit());
		if(bean.getGlobalLicenseLimit()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getGlobalLicenseLimit());
		if(bean.getLicenseType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseType());
		if(bean.getAssignedToUser()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAssignedToUser());
		if(bean.getAssignedToGroup()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAssignedToGroup());
		if(bean.getRegisteredBy()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getRegisteredBy());
		if(bean.getXmlString()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getXmlString());
		if(bean.getMaintenanceFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getMaintenanceFlag());
		if(bean.getLastUpdatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastUpdatedBy());
		if(bean.getLastUpdatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getLastUpdatedOn());
		if(bean.getCreatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCreatedBy());
		if(bean.getCreatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getCreatedOn());

		if(bean.getAgreementId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAgreementId());


		statement.executeUpdate();
		statement.close();
	}




	//------------------------------------------------------------------
	// INSERT
	//------------------------------------------------------------------
	public void insert(osmsDvIpmpAgreementBean bean,Connection conn)
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

		.append(")");



		PreparedStatement statement = conn.prepareStatement(sql.toString());

		int i=1;
		if(bean.getAgreementId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAgreementId());
		if(bean.getContentId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getContentId());
		if(bean.getStartDate()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getStartDate());
		if(bean.getEndDate()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getEndDate());
		if(bean.getUserLicenseLimit()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getUserLicenseLimit());
		if(bean.getGlobalLicenseLimit()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getGlobalLicenseLimit());
		if(bean.getLicenseType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseType());
		if(bean.getAssignedToUser()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAssignedToUser());
		if(bean.getAssignedToGroup()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getAssignedToGroup());
		if(bean.getRegisteredBy()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getRegisteredBy());
		if(bean.getXmlString()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getXmlString());
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
