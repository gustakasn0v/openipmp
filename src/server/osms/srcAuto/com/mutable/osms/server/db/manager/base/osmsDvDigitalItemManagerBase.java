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

public class osmsDvDigitalItemManagerBase implements Serializable
{
	private String m_tablename="DIGITAL_ITEM";
	protected String getTableName(){return m_tablename;}
	protected String getSqlResultSet() {return m_sqlResultSet;}
	private String m_sqlResultSet=
		(
			(new StringBuffer())
			.append(" DIGITAL_ITEM.DIGITAL_ITEM_ID")
			.append(", ").append(" DIGITAL_ITEM.CA_CERTIFICATE_ID")
			.append(", ").append(" DIGITAL_ITEM.CONTENT_ID")
			.append(", ").append(" DIGITAL_ITEM.DOI_ID")
			.append(", ").append(" DIGITAL_ITEM.MIME_TYPE")
			.append(", ").append(" DIGITAL_ITEM.ENCRYPTED_KEY")
			.append(", ").append(" DIGITAL_ITEM.KEY_LENGTH")
			.append(", ").append(" DIGITAL_ITEM.KEY_ALGORITHM_ID")
			.append(", ").append(" DIGITAL_ITEM.ENCRYPTION_KEY_ID")
			.append(", ").append(" DIGITAL_ITEM.CONTENT_DIGEST")
			.append(", ").append(" DIGITAL_ITEM.DIGEST_ALGORITHM_ID")
			.append(", ").append(" DIGITAL_ITEM.CONTENT_SIGNATURE")
			.append(", ").append(" DIGITAL_ITEM.SIG_ALGORITHM_ID")
			.append(", ").append(" DIGITAL_ITEM.WATERMARK_DATA")
			.append(", ").append(" DIGITAL_ITEM.TOOL_IDENTIFIER")
			.append(", ").append(" DIGITAL_ITEM.RIGHTS_HOST_URL")
			.append(", ").append(" DIGITAL_ITEM.RIGHTS_HOST_PORT")
			.append(", ").append(" DIGITAL_ITEM.LICENSE_TYPE")
			.append(", ").append(" DIGITAL_ITEM.IS_REVOKED_FLAG")
			.append(", ").append(" DIGITAL_ITEM.IS_PROTECTED_FLAG")
			.append(", ").append(" DIGITAL_ITEM.REGISTERED_BY")
			.append(", ").append(" DIGITAL_ITEM.MAINTENANCE_FLAG")
			.append(", ").append(" DIGITAL_ITEM.LAST_UPDATED_BY")
			.append(", ").append(" DIGITAL_ITEM.LAST_UPDATED_ON")
			.append(", ").append(" DIGITAL_ITEM.CREATED_BY")
			.append(", ").append(" DIGITAL_ITEM.CREATED_ON")
		).toString();

/*
	private String m_sqlResultSet=" DIGITAL_ITEM.DIGITAL_ITEM_ID,  DIGITAL_ITEM.CA_CERTIFICATE_ID,  DIGITAL_ITEM.CONTENT_ID,  DIGITAL_ITEM.DOI_ID,  DIGITAL_ITEM.MIME_TYPE,  DIGITAL_ITEM.ENCRYPTED_KEY,  DIGITAL_ITEM.KEY_LENGTH,  DIGITAL_ITEM.KEY_ALGORITHM_ID,  DIGITAL_ITEM.ENCRYPTION_KEY_ID,  DIGITAL_ITEM.CONTENT_DIGEST,  DIGITAL_ITEM.DIGEST_ALGORITHM_ID,  DIGITAL_ITEM.CONTENT_SIGNATURE,  DIGITAL_ITEM.SIG_ALGORITHM_ID,  DIGITAL_ITEM.WATERMARK_DATA,  DIGITAL_ITEM.TOOL_IDENTIFIER,  DIGITAL_ITEM.RIGHTS_HOST_URL,  DIGITAL_ITEM.RIGHTS_HOST_PORT,  DIGITAL_ITEM.LICENSE_TYPE,  DIGITAL_ITEM.IS_REVOKED_FLAG,  DIGITAL_ITEM.IS_PROTECTED_FLAG,  DIGITAL_ITEM.REGISTERED_BY,  DIGITAL_ITEM.MAINTENANCE_FLAG,  DIGITAL_ITEM.LAST_UPDATED_BY,  DIGITAL_ITEM.LAST_UPDATED_ON,  DIGITAL_ITEM.CREATED_BY,  DIGITAL_ITEM.CREATED_ON";
*/
	//------------------------------------------------------------------
	// mapResultSet2Bean
	//------------------------------------------------------------------
	protected osmsDvDigitalItemBean mapResultSet2Bean(ResultSet rs)
		throws Exception
	{
			int i=1;

			osmsDvDigitalItemBean bean = new osmsDvDigitalItemBean();
			bean.setDigitalItemId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setCaCertificateId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setContentId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setDoiId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setMimeType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setEncryptedKey((byte[])ConvertObject2byte(rs.getObject(i++)));
			bean.setKeyLength((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setKeyAlgorithmId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setEncryptionKeyId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setContentDigest((String)ConvertObject2String(rs.getObject(i++)));
			bean.setDigestAlgorithmId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setContentSignature((byte[])ConvertObject2byte(rs.getObject(i++)));
			bean.setSigAlgorithmId((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setWatermarkData((String)ConvertObject2String(rs.getObject(i++)));
			bean.setToolIdentifier((Integer)ConvertObject2Integer(rs.getObject(i++)));
			bean.setRightsHostUrl((String)ConvertObject2String(rs.getObject(i++)));
			bean.setRightsHostPort((String)ConvertObject2String(rs.getObject(i++)));
			bean.setLicenseType((String)ConvertObject2String(rs.getObject(i++)));
			bean.setIsRevokedFlag((String)ConvertObject2String(rs.getObject(i++)));
			bean.setIsProtectedFlag((String)ConvertObject2String(rs.getObject(i++)));
			bean.setRegisteredBy((Integer)ConvertObject2Integer(rs.getObject(i++)));
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
		osmsDvPkControlBean[] bean = managerPkControl.getByTableName("digital_item",conn);
		Long seq= bean[0].getCurrPkValue();
		bean[0].setCurrPkValue(new Long(seq.intValue()+1));
		managerPkControl.update(bean[0],conn);

		return new Long(seq.intValue()+1);
		

	}
*/

	//------------------------------------------------------------------
	// PROTECTED executeQuery
	//------------------------------------------------------------------
	protected osmsDvDigitalItemBean[] executeQuery(PreparedStatement statement,Connection conn)
		throws Exception
	{
		ResultSet rs=null;
		osmsDvDigitalItemBean[] ret=null;
		try
		{
			rs = statement.executeQuery();

			Vector beans = new Vector();
			while (rs.next())
			{

				beans.addElement(mapResultSet2Bean(rs));
			}
			if(beans.size() == 0) return null;

			ret = new osmsDvDigitalItemBean[beans.size()];
			for(int i=0;i<beans.size();i++)
				ret[i]=(osmsDvDigitalItemBean)beans.elementAt(i);

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
	protected osmsDvDigitalItemBean[] get(Connection conn,String postWhere)
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


	protected osmsDvDigitalItemBean[] getByDigitalItemId(Integer pDigitalItemId,Connection conn,String postWhere)
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

	protected osmsDvDigitalItemBean[] getByCaCertificateId(Integer pCaCertificateId,Connection conn,String postWhere)
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

	protected osmsDvDigitalItemBean[] getByDoiId(Integer pDoiId,Connection conn,String postWhere)
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

	protected osmsDvDigitalItemBean[] getByContentId(Integer pContentId,Connection conn,String postWhere)
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

	protected osmsDvDigitalItemBean[] getByKeyAlgorithmId(Integer pKeyAlgorithmId,Connection conn,String postWhere)
		throws Exception
	{
		StringBuffer sql = new StringBuffer();
		sql.append("Select  ")
			.append(m_sqlResultSet)

			.append(" from  ")
			.append(getTableName())
			.append(" ")

			.append(" where ")
			.append(" KEY_ALGORITHM_ID = ? ")

			.append(postWhere);

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		statement.setObject(i++,pKeyAlgorithmId);

		return executeQuery(statement,conn);
	}

	protected osmsDvDigitalItemBean[] getByDigestAlgorithmId(Integer pDigestAlgorithmId,Connection conn,String postWhere)
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

	protected osmsDvDigitalItemBean[] getBySigAlgorithmId(Integer pSigAlgorithmId,Connection conn,String postWhere)
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

	protected osmsDvDigitalItemBean[] getByRegisteredBy(Integer pRegisteredBy,Connection conn,String postWhere)
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



	//------------------------------------------------------------------
	// SELECT
	//------------------------------------------------------------------
	public osmsDvDigitalItemBean[] get(Connection conn)
		throws Exception
	{
		return get( conn,"");
	}

	public osmsDvDigitalItemBean[] getByDigitalItemId(Integer pDigitalItemId,Connection conn)
		throws Exception
	{
		return getByDigitalItemId( pDigitalItemId,conn,"");
	}

	public osmsDvDigitalItemBean[] getByCaCertificateId(Integer pCaCertificateId,Connection conn)
		throws Exception
	{
		return getByCaCertificateId( pCaCertificateId,conn,"");
	}

	public osmsDvDigitalItemBean[] getByDoiId(Integer pDoiId,Connection conn)
		throws Exception
	{
		return getByDoiId( pDoiId,conn,"");
	}

	public osmsDvDigitalItemBean[] getByContentId(Integer pContentId,Connection conn)
		throws Exception
	{
		return getByContentId( pContentId,conn,"");
	}

	public osmsDvDigitalItemBean[] getByKeyAlgorithmId(Integer pKeyAlgorithmId,Connection conn)
		throws Exception
	{
		return getByKeyAlgorithmId( pKeyAlgorithmId,conn,"");
	}

	public osmsDvDigitalItemBean[] getByDigestAlgorithmId(Integer pDigestAlgorithmId,Connection conn)
		throws Exception
	{
		return getByDigestAlgorithmId( pDigestAlgorithmId,conn,"");
	}

	public osmsDvDigitalItemBean[] getBySigAlgorithmId(Integer pSigAlgorithmId,Connection conn)
		throws Exception
	{
		return getBySigAlgorithmId( pSigAlgorithmId,conn,"");
	}

	public osmsDvDigitalItemBean[] getByRegisteredBy(Integer pRegisteredBy,Connection conn)
		throws Exception
	{
		return getByRegisteredBy( pRegisteredBy,conn,"");
	}




	//------------------------------------------------------------------
	// UPDATE
	//------------------------------------------------------------------
	public synchronized void update(osmsDvDigitalItemBean bean,Connection conn)
		throws Exception
	{
		//TEMPORARY SOLUTION TO SET TIME STAMPS
		bean.setLastUpdatedOn(new Timestamp(new Date().getTime()));

		StringBuffer sql = new StringBuffer();
		sql.append(" UPDATE  ")
		.append(getTableName())
		.append(" SET ")
			
		.append("CA_CERTIFICATE_ID = ? ")
			.append(", ").append("CONTENT_ID = ? ")
			.append(", ").append("DOI_ID = ? ")
			.append(", ").append("MIME_TYPE = ? ")
			.append(", ").append("ENCRYPTED_KEY = ? ")
			.append(", ").append("KEY_LENGTH = ? ")
			.append(", ").append("KEY_ALGORITHM_ID = ? ")
			.append(", ").append("ENCRYPTION_KEY_ID = ? ")
			.append(", ").append("CONTENT_DIGEST = ? ")
			.append(", ").append("DIGEST_ALGORITHM_ID = ? ")
			.append(", ").append("CONTENT_SIGNATURE = ? ")
			.append(", ").append("SIG_ALGORITHM_ID = ? ")
			.append(", ").append("WATERMARK_DATA = ? ")
			.append(", ").append("TOOL_IDENTIFIER = ? ")
			.append(", ").append("RIGHTS_HOST_URL = ? ")
			.append(", ").append("RIGHTS_HOST_PORT = ? ")
			.append(", ").append("LICENSE_TYPE = ? ")
			.append(", ").append("IS_REVOKED_FLAG = ? ")
			.append(", ").append("IS_PROTECTED_FLAG = ? ")
			.append(", ").append("REGISTERED_BY = ? ")
			.append(", ").append("MAINTENANCE_FLAG = ? ")
			.append(", ").append("LAST_UPDATED_BY = ? ")
			.append(", ").append("LAST_UPDATED_ON = ? ")
			.append(", ").append("CREATED_BY = ? ")
			.append(", ").append("CREATED_ON = ? ")

		.append(" where ")
		.append("DIGITAL_ITEM_ID = ? ")
		.append("");

		PreparedStatement statement = conn.prepareStatement(sql.toString());
		int i=1;

		if(bean.getCaCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCaCertificateId());
		if(bean.getContentId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getContentId());
		if(bean.getDoiId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDoiId());
		if(bean.getMimeType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getMimeType());
		if(bean.getEncryptedKey()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getEncryptedKey());
		if(bean.getKeyLength()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getKeyLength());
		if(bean.getKeyAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getKeyAlgorithmId());
		if(bean.getEncryptionKeyId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getEncryptionKeyId());
		if(bean.getContentDigest()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getContentDigest());
		if(bean.getDigestAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigestAlgorithmId());
		if(bean.getContentSignature()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getContentSignature());
		if(bean.getSigAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getSigAlgorithmId());
		if(bean.getWatermarkData()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getWatermarkData());
		if(bean.getToolIdentifier()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getToolIdentifier());
		if(bean.getRightsHostUrl()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getRightsHostUrl());
		if(bean.getRightsHostPort()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getRightsHostPort());
		if(bean.getLicenseType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseType());
		if(bean.getIsRevokedFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsRevokedFlag());
		if(bean.getIsProtectedFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsProtectedFlag());
		if(bean.getRegisteredBy()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getRegisteredBy());
		if(bean.getMaintenanceFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getMaintenanceFlag());
		if(bean.getLastUpdatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLastUpdatedBy());
		if(bean.getLastUpdatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getLastUpdatedOn());
		if(bean.getCreatedBy()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getCreatedBy());
		if(bean.getCreatedOn()==null)statement.setNull(i++,java.sql.Types.TIMESTAMP); else statement.setObject(i++,bean.getCreatedOn());

		if(bean.getDigitalItemId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigitalItemId());


		statement.executeUpdate();
		statement.close();
	}




	//------------------------------------------------------------------
	// INSERT
	//------------------------------------------------------------------
	public void insert(osmsDvDigitalItemBean bean,Connection conn)
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

		.append(")");



		PreparedStatement statement = conn.prepareStatement(sql.toString());

		int i=1;
		if(bean.getDigitalItemId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigitalItemId());
		if(bean.getCaCertificateId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getCaCertificateId());
		if(bean.getContentId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getContentId());
		if(bean.getDoiId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDoiId());
		if(bean.getMimeType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getMimeType());
		if(bean.getEncryptedKey()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getEncryptedKey());
		if(bean.getKeyLength()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getKeyLength());
		if(bean.getKeyAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getKeyAlgorithmId());
		if(bean.getEncryptionKeyId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getEncryptionKeyId());
		if(bean.getContentDigest()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getContentDigest());
		if(bean.getDigestAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getDigestAlgorithmId());
		if(bean.getContentSignature()==null)statement.setNull(i++,java.sql.Types.BINARY); else statement.setObject(i++,bean.getContentSignature());
		if(bean.getSigAlgorithmId()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getSigAlgorithmId());
		if(bean.getWatermarkData()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getWatermarkData());
		if(bean.getToolIdentifier()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getToolIdentifier());
		if(bean.getRightsHostUrl()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getRightsHostUrl());
		if(bean.getRightsHostPort()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getRightsHostPort());
		if(bean.getLicenseType()==null)statement.setNull(i++,java.sql.Types.VARCHAR); else statement.setObject(i++,bean.getLicenseType());
		if(bean.getIsRevokedFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsRevokedFlag());
		if(bean.getIsProtectedFlag()==null)statement.setNull(i++,java.sql.Types.CHAR); else statement.setObject(i++,bean.getIsProtectedFlag());
		if(bean.getRegisteredBy()==null)statement.setNull(i++,java.sql.Types.INTEGER); else statement.setObject(i++,bean.getRegisteredBy());
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
