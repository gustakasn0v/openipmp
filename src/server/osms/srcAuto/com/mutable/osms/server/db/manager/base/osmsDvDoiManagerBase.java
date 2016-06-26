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

public class osmsDvDoiManagerBase implements Serializable
{
	private String m_tablename="DOI";
	protected String getTableName(){return m_tablename;}
	protected String getSqlResultSet() {return m_sqlResultSet;}
	private String m_sqlResultSet=
		(
			(new StringBuffer())
			.append(" DOI.DOI_ID")
			.append(", ").append(" DOI.DOI_PROFILE_CODE")
			.append(", ").append(" DOI.DOI_IDENTIFIER")
			.append(", ").append(" DOI.STRUCTURAL_TYPE")
			.append(", ").append(" DOI.ISSUED_INTERNALLY")
			.append(", ").append(" DOI.VERSION")
			.append(", ").append(" DOI.XML_STRING")
			.append(", ").append(" DOI.IS_AUDIO_FLAG")
			.append(", ").append(" DOI.IS_ABSTRACT_FLAG")
			.append(", ").append(" DOI.IS_AUDIOVISUAL_FLAG")
			.append(", ").append(" DOI.IS_VISUAL_FLAG")
			.append(", ").append(" DOI.PRIMARY_TITLE_TEXT")
			.append(", ").append(" DOI.PRIMARY_TITLE_LANGUAGE")
			.append(", ").append(" DOI.PRIMARY_AGENT_NAME")
			.append(", ").append(" DOI.PRIMARY_AGENT_TYPE")
			.append(", ").append(" DOI.PRIMARY_AGENT_ROLE")
			.append(", ").append(" DOI.ASSERT_AUTH_TYPE")
			.append(", ").append(" DOI.ASSERT_AUTH_NAME")
			.append(", ").append(" DOI.ASSERT_REG_TYPE")
			.append(", ").append(" DOI.ASSERT_REG_NAME")
			.append(", ").append(" DOI.ASSERT_IDENTIFIER")
			.append(", ").append(" DOI.ASSERT_IDENTIFIER_TYPE")
			.append(", ").append(" DOI.MAINTENANCE_FLAG")
			.append(", ").append(" DOI.LAST_UPDATED_BY")
			.append(", ").append(" DOI.LAST_UPDATED_ON")
			.append(", ").append(" DOI.CREATED_BY")
			.append(", ").append(" DOI.CREATED_ON")
		).toString();

/*
	private String m_sqlResultSet=" DOI.DOI_ID,  DOI.DOI_PROFILE_CODE,  DOI.DOI_IDENTIFIER,  DOI.STRUCTURAL_TYPE,  DOI.ISSUED_INTERNALLY,  DOI.VERSION,  DOI.XML_STRING,  DOI.IS_AUDIO_FLAG,  DOI.IS_ABSTRACT_FLAG,  DOI.IS_AUDIOVISUAL_FLAG,  DOI.IS_VISUAL_FLAG,  DOI.PRIMARY_TITLE_TEXT,  DOI.PRIMARY_TITLE_LANGUAGE,  DOI.PRIMARY_AGENT_NAME,  DOI.PRIMARY_AGENT_TYPE,  DOI.PRIMARY_AGENT_ROLE,  DOI.ASSERT_AUTH_TYPE,  DOI.ASSERT_AUTH_NAME,  DOI.ASSERT_REG_TYPE,  DOI.ASSERT_REG_NAME,  DOI.ASSERT_IDENTIFIER,  DOI.ASSERT_IDENTIFIER_TYPE,  DOI.MAINTENANCE_FLAG,  DOI.LAST_UPDATED_BY,  DOI.LAST_UPDATED_ON,  DOI.CREATED_BY,  DOI.CREATED_ON";
*/
	//------------------------------------------------------------------
	// mapResultSet2Bean
	//------------------------------------------------------------------
	protected osmsDvDoiBean mapResultSet2Bean(ResultSet rs)
		throws Exception
	{
			int i=1;

			osmsDvDoiBean bean = new osmsDvDoiBean();
			bean.setDoiId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setDoiProfileCode((String)ConvertObject2String(rs.getObject(i++)));
			bean.setDoiIdentifier((String)ConvertObject2String(rs.getObject(i++)));
			bean.setStructuralType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setIssuedInternally((String)ConvertObject2String(rs.getObject(i++)));
			bean.setVersion((String)ConvertObject2String(rs.getObject(i++)));
			bean.setXmlString((String)ConvertObject2String(rs.getObject(i++)));
			bean.setIsAudioFlag((String)ConvertObject2String(rs.getObject(i++)));
			bean.setIsAbstractFlag((String)ConvertObject2String(rs.getObject(i++)));
			bean.setIsAudiovisualFlag((String)ConvertObject2String(rs.getObject(i++)));
			bean.setIsVisualFlag((String)ConvertObject2String(rs.getObject(i++)));
			bean.setPrimaryTitleText((String)ConvertObject2String(rs.getObject(i++)));
			bean.setPrimaryTitleLanguage((String)ConvertObject2String(rs.getObject(i++)));
			bean.setPrimaryAgentName((String)ConvertObject2String(rs.getObject(i++)));
			bean.setPrimaryAgentType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setPrimaryAgentRole((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAssertAuthType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAssertAuthName((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAssertRegType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAssertRegName((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAssertIdentifier((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAssertIdentifierType((String)ConvertObject2String(rs.getObject(i++)));
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
		osmsDvPkControlBean[] bean = managerPkControl.getByTableName("doi",conn);
		Long seq= bean[0].getCurrPkValue();
		bean[0].setCurrPkValue(new Long(seq.intValue()+1));
		managerPkControl.update(bean[0],conn);

		return new Long(seq.intValue()+1);
		

	}
*/

	//------------------------------------------------------------------
	// PROTECTED executeQuery
	//------------------------------------------------------------------
	protected osmsDvDoiBean[] executeQuery(PreparedStatement statement,Connection conn)
		throws Exception
	{
		ResultSet rs=null;
		osmsDvDoiBean[] ret=null;
		try
		{
			rs = statement.executeQuery();

			Vector beans = new Vector();
			while (rs.next())
			{

				beans.addElement(mapResultSet2Bean(rs));
			}
			if(beans.size() == 0) return null;

			ret = new osmsDvDoiBean[beans.size()];
			for(int i=0;i<beans.size();i++)
				ret[i]=(osmsDvDoiBean)beans.elementAt(i);

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
	protected osmsDvDoiBean[] get(Connection conn,String postWhere)
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


	protected osmsDvDoiBean[] getByDoiId(Integer pDoiId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" DOI_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pDoiId);

		return executeQuery(statement,conn);
	}

	protected osmsDvDoiBean[] getByDoiIdentifier(String pDoiIdentifier,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" DOI_IDENTIFIER = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pDoiIdentifier);

		return executeQuery(statement,conn);
	}

	protected osmsDvDoiBean[] getByDoiProfileCode(String pDoiProfileCode,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" DOI_PROFILE_CODE = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pDoiProfileCode);

		return executeQuery(statement,conn);
	}



	//------------------------------------------------------------------
	// SELECT
	//------------------------------------------------------------------
	public osmsDvDoiBean[] get(Connection conn)
		throws Exception
	{
		return get( conn,"");
	}

	public osmsDvDoiBean[] getByDoiId(Integer pDoiId,Connection conn)
		throws Exception
	{
		return getByDoiId( pDoiId,conn,"");
	}

	public osmsDvDoiBean[] getByDoiIdentifier(String pDoiIdentifier,Connection conn)
		throws Exception
	{
		return getByDoiIdentifier( pDoiIdentifier,conn,"");
	}

	public osmsDvDoiBean[] getByDoiProfileCode(String pDoiProfileCode,Connection conn)
		throws Exception
	{
		return getByDoiProfileCode( pDoiProfileCode,conn,"");
	}




	//------------------------------------------------------------------
	// UPDATE
	//------------------------------------------------------------------
	public synchronized void update(osmsDvDoiBean bean,Connection conn)
		throws Exception
	{
		//TEMPORARY SOLUTION TO SET TIME STAMPS
		bean.setLastUpdatedOn(new Timestamp(new Date().getTime()));

		StringBuffer sql = new StringBuffer();
		sql.append(" UPDATE  ")
		.append(getTableName())
		.append(" SET ")
			
		.append("DOI_PROFILE_CODE = ? ")
			.append(", ").append("DOI_IDENTIFIER = ? ")
			.append(", ").append("STRUCTURAL_TYPE = ? ")
			.append(", ").append("ISSUED_INTERNALLY = ? ")
			.append(", ").append("VERSION = ? ")
			.append(", ").append("XML_STRING = ? ")
			.append(", ").append("IS_AUDIO_FLAG = ? ")
			.append(", ").append("IS_ABSTRACT_FLAG = ? ")
			.append(", ").append("IS_AUDIOVISUAL_FLAG = ? ")
			.append(", ").append("IS_VISUAL_FLAG = ? ")
			.append(", ").append("PRIMARY_TITLE_TEXT = ? ")
			.append(", ").append("PRIMARY_TITLE_LANGUAGE = ? ")
			.append(", ").append("PRIMARY_AGENT_NAME = ? ")
			.append(", ").append("PRIMARY_AGENT_TYPE = ? ")
			.append(", ").append("PRIMARY_AGENT_ROLE = ? ")
			.append(", ").append("ASSERT_AUTH_TYPE = ? ")
			.append(", ").append("ASSERT_AUTH_NAME = ? ")
			.append(", ").append("ASSERT_REG_TYPE = ? ")
			.append(", ").append("ASSERT_REG_NAME = ? ")
			.append(", ").append("ASSERT_IDENTIFIER = ? ")
			.append(", ").append("ASSERT_IDENTIFIER_TYPE = ? ")
			.append(", ").append("MAINTENANCE_FLAG = ? ")
			.append(", ").append("LAST_UPDATED_BY = ? ")
			.append(", ").append("LAST_UPDATED_ON = ? ")
			.append(", ").append("CREATED_BY = ? ")
			.append(", ").append("CREATED_ON = ? ")

		.append(" where ")
		.append("DOI_ID = ? ")
		.append("");

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		if(bean.getDoiProfileCode()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getDoiProfileCode());
		if(bean.getDoiIdentifier()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getDoiIdentifier());
		if(bean.getStructuralType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getStructuralType());
		if(bean.getIssuedInternally()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIssuedInternally());
		if(bean.getVersion()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getVersion());
		if(bean.getXmlString()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getXmlString());
		if(bean.getIsAudioFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsAudioFlag());
		if(bean.getIsAbstractFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsAbstractFlag());
		if(bean.getIsAudiovisualFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsAudiovisualFlag());
		if(bean.getIsVisualFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsVisualFlag());
		if(bean.getPrimaryTitleText()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryTitleText());
		if(bean.getPrimaryTitleLanguage()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryTitleLanguage());
		if(bean.getPrimaryAgentName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryAgentName());
		if(bean.getPrimaryAgentType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryAgentType());
		if(bean.getPrimaryAgentRole()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryAgentRole());
		if(bean.getAssertAuthType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertAuthType());
		if(bean.getAssertAuthName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertAuthName());
		if(bean.getAssertRegType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertRegType());
		if(bean.getAssertRegName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertRegName());
		if(bean.getAssertIdentifier()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertIdentifier());
		if(bean.getAssertIdentifierType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertIdentifierType());
		if(bean.getMaintenanceFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getMaintenanceFlag());
		if(bean.getLastUpdatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastUpdatedBy());
		if(bean.getLastUpdatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getLastUpdatedOn());
		if(bean.getCreatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCreatedBy());
		if(bean.getCreatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getCreatedOn());

		if(bean.getDoiId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDoiId());


		statement.executeUpdate();
		statement.close();
	}




	//------------------------------------------------------------------
	// INSERT
	//------------------------------------------------------------------
	public void insert(osmsDvDoiBean bean,Connection conn)
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
		if(bean.getDoiId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDoiId());
		if(bean.getDoiProfileCode()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getDoiProfileCode());
		if(bean.getDoiIdentifier()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getDoiIdentifier());
		if(bean.getStructuralType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getStructuralType());
		if(bean.getIssuedInternally()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIssuedInternally());
		if(bean.getVersion()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getVersion());
		if(bean.getXmlString()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getXmlString());
		if(bean.getIsAudioFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsAudioFlag());
		if(bean.getIsAbstractFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsAbstractFlag());
		if(bean.getIsAudiovisualFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsAudiovisualFlag());
		if(bean.getIsVisualFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsVisualFlag());
		if(bean.getPrimaryTitleText()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryTitleText());
		if(bean.getPrimaryTitleLanguage()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryTitleLanguage());
		if(bean.getPrimaryAgentName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryAgentName());
		if(bean.getPrimaryAgentType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryAgentType());
		if(bean.getPrimaryAgentRole()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPrimaryAgentRole());
		if(bean.getAssertAuthType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertAuthType());
		if(bean.getAssertAuthName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertAuthName());
		if(bean.getAssertRegType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertRegType());
		if(bean.getAssertRegName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertRegName());
		if(bean.getAssertIdentifier()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertIdentifier());
		if(bean.getAssertIdentifierType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAssertIdentifierType());
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
