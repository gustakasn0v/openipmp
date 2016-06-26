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

package com.mutable.osmsOnline.server.app;

import com.mutable.osms.server.app.*;
import com.mutable.osms.server.bo.*;
import com.mutable.io.OlLogger;
import com.mutable.osms.common.io.message.*;

/**
* ProcessMessageUserLogoutRequest is the openIPMP class that manages the logout process from the jsp pages.
*
* <p>
* @version      1.0
* @since      	1.0
*/

public class ProcessMessageUserLogoutRequest
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
    public String process(osmsMessageUserLogoutRequest req,osmsUsers a_user)
	{
		logDebug("process",a_user!=null&&a_user.getUserName()!=null?a_user.getUserName():null);
		osmsMessage rsp;
		String rspName;
		if(a_user!=null&&a_user.getUserName()!=null)
		{
			rsp = osmsGlobalObjectManager.getInstance().getLoginManager().processLogoutRequest(req,a_user);
			if(rsp!=null)
		    {
				rspName = rsp.getClass().getName();
				if (rspName.equals("com.mutable.osms.common.io.message.osmsMessageUserLogoutResponse"))
				{
					a_user=null;
					return "You were successfully logged out of the system";
				}
				else
				{
					if (rspName.equals("com.mutable.osms.common.io.message.osmsMessageUserLogoutResponseError"))
					{
						logDebug("process",((osmsMessageUserLogoutResponseError)rsp).getResponseString());
						a_user=null;
						return "You were logged out of the system";
					}
				}
		    }
		}
		a_user=null;
		return "You are no longer logged into the system";
    }
}