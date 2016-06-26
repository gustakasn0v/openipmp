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
 * <p>Description:  </p>
 * @version 1.0
 */


package com.mutable.osmsOnline.server.app;

import com.mutable.osms.server.app.*;
import com.mutable.osms.server.bo.*;
import com.mutable.io.OlLogger;
import com.mutable.osms.common.io.message.*;

public class ProcessMessageUserLoginRequest
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// LOGGING
	//
	//////////////////////////////////////////////////////////////////////////////////////////////
	private String className = getClass().getName().substring(getClass().getName().lastIndexOf(".")+1);
	private void logDebug(String method,String message){if(m_logger!=null)m_logger.debug(className,method+" : "+message);}
	private void logWarning(String method,String message){if(m_logger!=null)m_logger.warning(className,method+"() : "+message);}
	private void logError(String method,String message){if(m_logger!=null)m_logger.error(className,method+"() : "+message);}
	private void logError(String method,String message,Exception e){if(m_logger!=null)m_logger.error(className,method+"() : "+message,e);}
	private void logInfo(String method,String message){if(m_logger!=null)m_logger.info(className,method+"() : "+message);}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger m_logger= osmsGlobalObjectManager.getInstance().getLogger();
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
    public String process(osmsMessageUserLoginRequest req,osmsUsers a_user)
	{
		logDebug("process",req.getUserName()+" "+req.getPassword());
		osmsUsers user = osmsGlobalObjectManager.getInstance().getLoginManager().getUser(req.getUserName());
		osmsMessage rsp = osmsGlobalObjectManager.getInstance().getLoginManager().processLoginRequest(req,user);
		String rspName = rsp.getClass().getName();
		logDebug("process",rspName);

		if (rspName.equals("com.mutable.osms.common.io.message.osmsMessageUserLoginResponse"))
		{
			user.getUsersBean().copyPropertiesTo(a_user.getUsersBean());
			a_user.isLoggedIn(user.isLoggedIn());
			return null;
		}
		return "login Failed";
    }

}