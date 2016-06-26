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

import java.sql.*;
import com.mutable.io.*;
import java.util.*;
import java.io.*;

public class osmsDbPool
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}

	private OlLogger m_logger;

	private Connection m_conn;
	private String m_jdbcDriverName;
	private String m_url;
	private String m_user;
	private String m_password;

	private void connect() throws Exception
	{
		String methodName="checkOut";
		if(m_conn!=null)m_conn.close();
//			logDebug(methodName,"Locating jdbc driver...");
			Class.forName (m_jdbcDriverName);
//			logDebug(methodName,"Located jdbc driver!");

//			logDebug(methodName,"Getting Connection...");
			logDebug(methodName,"url="+m_url+" user="+m_user+" password="+m_password);
			m_conn = DriverManager.getConnection (m_url,m_user,m_password);
			m_conn.setAutoCommit(false);
//			logDebug(methodName,"Got Connection!");
	}
	public osmsDbPool(String jdbcDriverName,String url,String user,String password,OlLogger log) throws Exception
	{
		String methodName="dbPool.dbPool";
		logDebug(methodName,new File("").getCanonicalPath());
		m_jdbcDriverName=jdbcDriverName;
		m_url=url;
		m_user=user;
		m_password=password;
		m_logger=log;
		try
		{
			connect();

		}
		catch (Exception ex)
		{
			logError(methodName,"",ex);
		}


	}
	boolean m_bCheckout=false;
	public synchronized Connection checkOut() throws Exception
	{
		String methodName="checkOut";
//		logDebug(methodName,"");
		if(m_bCheckout) throw new Exception("Connection already checked out!");
		if(m_conn==null || m_conn.isClosed())
		{
			connect();
		}
		m_bCheckout=true;
		return m_conn;
	}
	public synchronized void checkIn(Connection conn) throws Exception
	{
		String methodName="checkIn";
//		logDebug(methodName,"");
		m_bCheckout=false;
//		m_conn.commit();
//		m_conn.close();
//		m_conn=null;
	}
}

/*
package com.mutable.osms.server.db;

import java.sql.*;
import com.mutable.io.OlLogger;

public class osmsDbPool
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}
	private Connection m_conn;
	boolean m_bCheckedOut=false;
	private OlLogger m_logger;

	public osmsDbPool(OlLogger logger)
	{
		m_logger = logger;
		try
		{
			System.out.println("Locating jdbc driver...");
			Class.forName ("oracle.jdbc.driver.OracleDriver");
			System.out.println("Located jdbc driver!");
			System.out.println("");

			System.out.println("Getting Connection...");
			m_conn = DriverManager.getConnection ("jdbc:oracle:thin:@localhost:1521:gdb", "osms", "osms");
			m_conn.setAutoCommit(false);
			System.out.println("Got Connection!");
			System.out.println("");
		}
		catch (Exception ex)
		{
			System.out.println(ex.toString());
		}

	}
	public Connection checkOut() throws Exception
	{
		if(m_bCheckedOut) throw new Exception("Connection Already Checked Out!");
		m_bCheckedOut=true;
		return m_conn;
	}
	public void checkIn(Connection conn)
	{
		m_bCheckedOut=false;
	}
}
*/