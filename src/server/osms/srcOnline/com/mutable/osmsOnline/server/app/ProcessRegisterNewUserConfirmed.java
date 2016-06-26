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

import com.mutable.io.OlLogger;
import com.mutable.osms.server.app.*;
import com.mutable.osms.server.bo.*;
import com.mutable.osms.common.io.message.*;

public class ProcessRegisterNewUserConfirmed
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
	// PROPERTIES
	//
	///////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	private OlLogger m_logger= osmsGlobalObjectManager.getInstance().getLogger();
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PRIVATE MEMBERS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//
	// PUBLIC METHODS
	//
	///////////////////////////////////////////////////////////////////////////////////////////////
	public String process(osmsUsers a_user)
	{
		String methodName="process";
		logDebug(methodName,"");
		if(a_user.getUserSecurityStore()==null)
		{
			osmsRightsManager rightsMan = osmsGlobalObjectManager.getInstance().getRightsManager();
			byte[] ba = rightsMan.AquireUserKeyStore(a_user);
			if(ba==null)return "Failed to aquire rights, Unkown Error!";
			a_user.setUserSecurityStore(ba);
			return null;
		}
		return null;


	}
}


