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

public class osmsDvUsersManagerBase implements Serializable
{
	private String m_tablename="USERS";
	protected String getTableName(){return m_tablename;}
	protected String getSqlResultSet() {return m_sqlResultSet;}
	private String m_sqlResultSet=
		(
			(new StringBuffer())
			.append(" USERS.USER_ID")
			.append(", ").append(" USERS.USER_NAME")
			.append(", ").append(" USERS.PASSWORD")
			.append(", ").append(" USERS.SECRET_QUESTION")
			.append(", ").append(" USERS.SECRET_ANSWER")
			.append(", ").append(" USERS.SALUTATION")
			.append(", ").append(" USERS.FIRST_NAME")
			.append(", ").append(" USERS.LAST_NAME")
			.append(", ").append(" USERS.SUFFIX")
			.append(", ").append(" USERS.JOB_TITLE")
			.append(", ").append(" USERS.EMAIL_ADDRESS")
			.append(", ").append(" USERS.URL")
			.append(", ").append(" USERS.ADDRESS_LINE1")
			.append(", ").append(" USERS.ADDRESS_LINE2")
			.append(", ").append(" USERS.ADDRESS_LINE3")
			.append(", ").append(" USERS.CITY")
			.append(", ").append(" USERS.STATE_CODE")
			.append(", ").append(" USERS.ZIP_CODE")
			.append(", ").append(" USERS.COUNTRY_CODE")
			.append(", ").append(" USERS.ATTENTION_TEXT")
			.append(", ").append(" USERS.MAIN_PHONE_NUMBER")
			.append(", ").append(" USERS.ALT_PHONE_NUMBER")
			.append(", ").append(" USERS.FAX_PHONE_NUMBER")
			.append(", ").append(" USERS.ORG_UNIT_NAME")
			.append(", ").append(" USERS.ORGANIZATION_ID")
			.append(", ").append(" USERS.CERTIFICATE_ID")
			.append(", ").append(" USERS.STATUS_FLAG")
			.append(", ").append(" USERS.MAINTENANCE_FLAG")
			.append(", ").append(" USERS.LAST_UPDATED_BY")
			.append(", ").append(" USERS.LAST_UPDATED_ON")
			.append(", ").append(" USERS.CREATED_BY")
			.append(", ").append(" USERS.CREATED_ON")
		).toString();

/*
	private String m_sqlResultSet=" USERS.USER_ID,  USERS.USER_NAME,  USERS.PASSWORD,  USERS.SECRET_QUESTION,  USERS.SECRET_ANSWER,  USERS.SALUTATION,  USERS.FIRST_NAME,  USERS.LAST_NAME,  USERS.SUFFIX,  USERS.JOB_TITLE,  USERS.EMAIL_ADDRESS,  USERS.URL,  USERS.ADDRESS_LINE1,  USERS.ADDRESS_LINE2,  USERS.ADDRESS_LINE3,  USERS.CITY,  USERS.STATE_CODE,  USERS.ZIP_CODE,  USERS.COUNTRY_CODE,  USERS.ATTENTION_TEXT,  USERS.MAIN_PHONE_NUMBER,  USERS.ALT_PHONE_NUMBER,  USERS.FAX_PHONE_NUMBER,  USERS.ORG_UNIT_NAME,  USERS.ORGANIZATION_ID,  USERS.CERTIFICATE_ID,  USERS.STATUS_FLAG,  USERS.MAINTENANCE_FLAG,  USERS.LAST_UPDATED_BY,  USERS.LAST_UPDATED_ON,  USERS.CREATED_BY,  USERS.CREATED_ON";
*/
	//------------------------------------------------------------------
	// mapResultSet2Bean
	//------------------------------------------------------------------
	protected osmsDvUsersBean mapResultSet2Bean(ResultSet rs)
		throws Exception
	{
			int i=1;

			osmsDvUsersBean bean = new osmsDvUsersBean();
			bean.setUserId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setUserName((String)ConvertObject2String(rs.getObject(i++)));
			bean.setPassword((String)ConvertObject2String(rs.getObject(i++)));
			bean.setSecretQuestion((String)ConvertObject2String(rs.getObject(i++)));
			bean.setSecretAnswer((String)ConvertObject2String(rs.getObject(i++)));
			bean.setSalutation((String)ConvertObject2String(rs.getObject(i++)));
			bean.setFirstName((String)ConvertObject2String(rs.getObject(i++)));
			bean.setLastName((String)ConvertObject2String(rs.getObject(i++)));
			bean.setSuffix((String)ConvertObject2String(rs.getObject(i++)));
			bean.setJobTitle((String)ConvertObject2String(rs.getObject(i++)));
			bean.setEmailAddress((String)ConvertObject2String(rs.getObject(i++)));
			bean.setUrl((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAddressLine1((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAddressLine2((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAddressLine3((String)ConvertObject2String(rs.getObject(i++)));
			bean.setCity((String)ConvertObject2String(rs.getObject(i++)));
			bean.setStateCode((String)ConvertObject2String(rs.getObject(i++)));
			bean.setZipCode((String)ConvertObject2String(rs.getObject(i++)));
			bean.setCountryCode((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAttentionText((String)ConvertObject2String(rs.getObject(i++)));
			bean.setMainPhoneNumber((String)ConvertObject2String(rs.getObject(i++)));
			bean.setAltPhoneNumber((String)ConvertObject2String(rs.getObject(i++)));
			bean.setFaxPhoneNumber((String)ConvertObject2String(rs.getObject(i++)));
			bean.setOrgUnitName((String)ConvertObject2String(rs.getObject(i++)));
			bean.setOrganizationId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setCertificateId((Integer)ConvertObject2Integer(rs.getObject(i++)));
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
		osmsDvPkControlBean[] bean = managerPkControl.getByTableName("users",conn);
		Long seq= bean[0].getCurrPkValue();
		bean[0].setCurrPkValue(new Long(seq.intValue()+1));
		managerPkControl.update(bean[0],conn);

		return new Long(seq.intValue()+1);
		

	}
*/

	//------------------------------------------------------------------
	// PROTECTED executeQuery
	//------------------------------------------------------------------
	protected osmsDvUsersBean[] executeQuery(PreparedStatement statement,Connection conn)
		throws Exception
	{
		ResultSet rs=null;
		osmsDvUsersBean[] ret=null;
		try
		{
			rs = statement.executeQuery();

			Vector beans = new Vector();
			while (rs.next())
			{

				beans.addElement(mapResultSet2Bean(rs));
			}
			if(beans.size() == 0) return null;

			ret = new osmsDvUsersBean[beans.size()];
			for(int i=0;i<beans.size();i++)
				ret[i]=(osmsDvUsersBean)beans.elementAt(i);

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
	protected osmsDvUsersBean[] get(Connection conn,String postWhere)
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


	protected osmsDvUsersBean[] getByUserId(Integer pUserId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" USER_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pUserId);

		return executeQuery(statement,conn);
	}

	protected osmsDvUsersBean[] getByUserName(String pUserName,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" USER_NAME = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pUserName);

		return executeQuery(statement,conn);
	}

	protected osmsDvUsersBean[] getByOrganizationId(Integer pOrganizationId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" ORGANIZATION_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pOrganizationId);

		return executeQuery(statement,conn);
	}

	protected osmsDvUsersBean[] getByCertificateId(Integer pCertificateId,Connection conn,String postWhere)
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



	//------------------------------------------------------------------
	// SELECT
	//------------------------------------------------------------------
	public osmsDvUsersBean[] get(Connection conn)
		throws Exception
	{
		return get( conn,"");
	}

	public osmsDvUsersBean[] getByUserId(Integer pUserId,Connection conn)
		throws Exception
	{
		return getByUserId( pUserId,conn,"");
	}

	public osmsDvUsersBean[] getByUserName(String pUserName,Connection conn)
		throws Exception
	{
		return getByUserName( pUserName,conn,"");
	}

	public osmsDvUsersBean[] getByOrganizationId(Integer pOrganizationId,Connection conn)
		throws Exception
	{
		return getByOrganizationId( pOrganizationId,conn,"");
	}

	public osmsDvUsersBean[] getByCertificateId(Integer pCertificateId,Connection conn)
		throws Exception
	{
		return getByCertificateId( pCertificateId,conn,"");
	}




	//------------------------------------------------------------------
	// UPDATE
	//------------------------------------------------------------------
	public synchronized void update(osmsDvUsersBean bean,Connection conn)
		throws Exception
	{
		//TEMPORARY SOLUTION TO SET TIME STAMPS
		bean.setLastUpdatedOn(new Timestamp(new Date().getTime()));

		StringBuffer sql = new StringBuffer();
		sql.append(" UPDATE  ")
		.append(getTableName())
		.append(" SET ")
			
		.append("USER_NAME = ? ")
			.append(", ").append("PASSWORD = ? ")
			.append(", ").append("SECRET_QUESTION = ? ")
			.append(", ").append("SECRET_ANSWER = ? ")
			.append(", ").append("SALUTATION = ? ")
			.append(", ").append("FIRST_NAME = ? ")
			.append(", ").append("LAST_NAME = ? ")
			.append(", ").append("SUFFIX = ? ")
			.append(", ").append("JOB_TITLE = ? ")
			.append(", ").append("EMAIL_ADDRESS = ? ")
			.append(", ").append("URL = ? ")
			.append(", ").append("ADDRESS_LINE1 = ? ")
			.append(", ").append("ADDRESS_LINE2 = ? ")
			.append(", ").append("ADDRESS_LINE3 = ? ")
			.append(", ").append("CITY = ? ")
			.append(", ").append("STATE_CODE = ? ")
			.append(", ").append("ZIP_CODE = ? ")
			.append(", ").append("COUNTRY_CODE = ? ")
			.append(", ").append("ATTENTION_TEXT = ? ")
			.append(", ").append("MAIN_PHONE_NUMBER = ? ")
			.append(", ").append("ALT_PHONE_NUMBER = ? ")
			.append(", ").append("FAX_PHONE_NUMBER = ? ")
			.append(", ").append("ORG_UNIT_NAME = ? ")
			.append(", ").append("ORGANIZATION_ID = ? ")
			.append(", ").append("CERTIFICATE_ID = ? ")
			.append(", ").append("STATUS_FLAG = ? ")
			.append(", ").append("MAINTENANCE_FLAG = ? ")
			.append(", ").append("LAST_UPDATED_BY = ? ")
			.append(", ").append("LAST_UPDATED_ON = ? ")
			.append(", ").append("CREATED_BY = ? ")
			.append(", ").append("CREATED_ON = ? ")

		.append(" where ")
		.append("USER_ID = ? ")
		.append("");

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		if(bean.getUserName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getUserName());
		if(bean.getPassword()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPassword());
		if(bean.getSecretQuestion()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSecretQuestion());
		if(bean.getSecretAnswer()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSecretAnswer());
		if(bean.getSalutation()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSalutation());
		if(bean.getFirstName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getFirstName());
		if(bean.getLastName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastName());
		if(bean.getSuffix()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSuffix());
		if(bean.getJobTitle()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getJobTitle());
		if(bean.getEmailAddress()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getEmailAddress());
		if(bean.getUrl()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getUrl());
		if(bean.getAddressLine1()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAddressLine1());
		if(bean.getAddressLine2()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAddressLine2());
		if(bean.getAddressLine3()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAddressLine3());
		if(bean.getCity()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCity());
		if(bean.getStateCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getStateCode());
		if(bean.getZipCode()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getZipCode());
		if(bean.getCountryCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getCountryCode());
		if(bean.getAttentionText()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAttentionText());
		if(bean.getMainPhoneNumber()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getMainPhoneNumber());
		if(bean.getAltPhoneNumber()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAltPhoneNumber());
		if(bean.getFaxPhoneNumber()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getFaxPhoneNumber());
		if(bean.getOrgUnitName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getOrgUnitName());
		if(bean.getOrganizationId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getOrganizationId());
		if(bean.getCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCertificateId());
		if(bean.getStatusFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getStatusFlag());
		if(bean.getMaintenanceFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getMaintenanceFlag());
		if(bean.getLastUpdatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastUpdatedBy());
		if(bean.getLastUpdatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getLastUpdatedOn());
		if(bean.getCreatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCreatedBy());
		if(bean.getCreatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getCreatedOn());

		if(bean.getUserId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getUserId());


		statement.executeUpdate();
		statement.close();
	}




	//------------------------------------------------------------------
	// INSERT
	//------------------------------------------------------------------
	public void insert(osmsDvUsersBean bean,Connection conn)
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
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")
		.append(", ").append("?")

		.append(")");



		PreparedStatement statement = conn.prepareStatement(sql.toString());

		int i=1;
		if(bean.getUserId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getUserId());
		if(bean.getUserName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getUserName());
		if(bean.getPassword()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getPassword());
		if(bean.getSecretQuestion()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSecretQuestion());
		if(bean.getSecretAnswer()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSecretAnswer());
		if(bean.getSalutation()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSalutation());
		if(bean.getFirstName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getFirstName());
		if(bean.getLastName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastName());
		if(bean.getSuffix()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getSuffix());
		if(bean.getJobTitle()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getJobTitle());
		if(bean.getEmailAddress()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getEmailAddress());
		if(bean.getUrl()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getUrl());
		if(bean.getAddressLine1()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAddressLine1());
		if(bean.getAddressLine2()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAddressLine2());
		if(bean.getAddressLine3()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAddressLine3());
		if(bean.getCity()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCity());
		if(bean.getStateCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getStateCode());
		if(bean.getZipCode()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getZipCode());
		if(bean.getCountryCode()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getCountryCode());
		if(bean.getAttentionText()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAttentionText());
		if(bean.getMainPhoneNumber()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getMainPhoneNumber());
		if(bean.getAltPhoneNumber()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getAltPhoneNumber());
		if(bean.getFaxPhoneNumber()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getFaxPhoneNumber());
		if(bean.getOrgUnitName()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getOrgUnitName());
		if(bean.getOrganizationId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getOrganizationId());
		if(bean.getCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCertificateId());
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
