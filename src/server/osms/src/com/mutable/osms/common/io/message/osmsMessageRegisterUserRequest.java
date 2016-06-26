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


package com.mutable.osms.common.io.message;

/**
 * <p>Title: osmsMessageRegisterUserRequest</p>
 * <p>Description: </p>
 * @version 1.0
 */

public class osmsMessageRegisterUserRequest extends osmsMessage
{

	//bean properties
	private String m_UserName=null;
	public String getUserName(){return m_UserName;}
	public void setUserName(String UserName){m_UserName=UserName;}

	private String m_EmailAddress=null;
	public String getEmailAddress(){return m_EmailAddress;}
	public void setEmailAddress(String EmailAddress){m_EmailAddress=EmailAddress;}

	private String m_Password=null;
	public String getPassword(){return m_Password;}
	public void setPassword(String Password){m_Password=Password;}

	private String m_PasswordConfirm=null;
	public String getPasswordConfirm(){return m_PasswordConfirm;}
	public void setPasswordConfirm(String PasswordConfirm){m_PasswordConfirm=PasswordConfirm;}

	//constructs
	public osmsMessageRegisterUserRequest()
	{
		super(osmsMessage.osmsMESSAGE_REGISTER_USER_REQUEST);
	}
}
