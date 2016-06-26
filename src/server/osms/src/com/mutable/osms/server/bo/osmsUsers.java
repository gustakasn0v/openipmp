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

package com.mutable.osms.server.bo;

import java.sql.Timestamp;
import java.io.Serializable;
import java.util.Date;

import com.mutable.osms.server.db.bean.*;
import com.mutable.osms.server.bo.base.*;
import com.mutable.io.OlLogger;
import com.mutable.osms.server.app.*;

public class osmsUsers extends osmsUsersBase implements Serializable
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(log!=null)log.debug(className,method+"() : "+message);}
	private void logWarning(String method,String message){if(log!=null)log.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(log!=null)log.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(log!=null)log.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(log!=null)log.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	OlLogger log;

	public osmsUsers(osmsDvUsersBean bean){super(bean);		log=osmsGlobalObjectManager.getInstance().getLogger();}
	public osmsUsers(){super();		log=osmsGlobalObjectManager.getInstance().getLogger();}


	private boolean m_IsLoggedIn=false;
	public void isLoggedIn(boolean isLoggedIn)
	{
		m_IsLoggedIn=isLoggedIn;
	}
	public boolean isLoggedIn()
	{
		return m_IsLoggedIn;
	}
	public void login()
	{
		String methodName = "osmsUsers:login";
		logDebug(methodName,"Processing login for user: "+this.getUserName());
		isLoggedIn(true);
		//Try to generate a login record for this user
		try
		{
			osmsLoginHistory lh = new osmsLoginHistory();
			lh.setUserId(this.getUserId());
			lh.setLoginTime(new Timestamp(new Date().getTime()));
			this.setLoginHistory(lh);
			osmsGlobalObjectManager.getInstance().getDatabase().insertLoginHistory(lh);
		}
		catch(Exception e)
		{
			logError(methodName, "Encountered exception trying to create a login record...continuing: ", e);
		}
	}

	public void logout()
	{
		String methodName = "osmsUsers:logout";
		logDebug(methodName,"Processing logout for user: "+this.getUserName());
		isLoggedIn(false);
		//Try to update the user's login record
		try
		{
		    if(this.getLoginHistory()!=null)
			{
			    this.getLoginHistory().setLogoffTime(new Timestamp(new Date().getTime()));
		        osmsGlobalObjectManager.getInstance().getDatabase().updateLoginHistory(this.getLoginHistory());
			    this.setLoginHistory(null);
			}
			else
			{
				logDebug(methodName,"Could not update login history record for: "+this.getUserName());
			}
		}
		catch(Exception e)
		{
			logError(methodName, "Encountered exception trying to update login record...continuing: ", e);
		}
	}

	private byte[] m_secStore;
	public byte[] getUserSecurityStore()
	{
		return m_secStore;
	}
	public void setUserSecurityStore(byte[] ba)
	{
		m_secStore=ba;
	}
	public String[] getLicenses()
	{
		String[] ret = {"one","two"};
		return ret;
	}

	//Login History
	private osmsLoginHistory m_loginHistory;
	public osmsLoginHistory getLoginHistory()
	{
		return m_loginHistory;
	}
	public void setLoginHistory(osmsLoginHistory loginHistory)
	{
		m_loginHistory=loginHistory;
	}

	//OSMS Certificate
	private osmsCertificate m_osmsCertificate;
	public osmsCertificate getOsmsCertificate()
	{
		return m_osmsCertificate;
	}
	public void setOsmsCertificate(osmsCertificate osmsCert)
	{
		m_osmsCertificate=osmsCert;
	}
	
	/** C. Mollis SPE needs the cleartext password */
	private String m_ClearTextPassword;
	public String getClearTextPassword ()
	{
		return m_ClearTextPassword;
	}
	
	public void setClearTextPassword( String password)
	{
		m_ClearTextPassword = password;
	}
	
	public static void main(String[] args)
	{

		Timestamp t = new Timestamp(new Date().getTime());
		System.out.println( new Date().toString());
		System.out.println( t.toString());

	}
}

