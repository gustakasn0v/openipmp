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
 * <p>Title: osmsMessageAcquireUserKeyStoreResponse</p>
 * <p>Description: </p>
 * @version 1.0
 */



public class osmsMessageAcquireUserKeyStoreResponse extends osmsMessage
{

	//bean properties
	private String m_UserName=null;
	public String getUserName(){return m_UserName;}
	public void setUserName(String UserName){m_UserName=UserName;}

	private byte[] m_UserSecurityStore=null;
	public byte[] getUserSecurityStore(){return m_UserSecurityStore;}
	public void setUserSecurityStore(byte[] UserSecurityStore)
	{
		m_UserSecurityStore=new byte[UserSecurityStore.length];
		for(int i=0;i<UserSecurityStore.length;i++)
		{
			m_UserSecurityStore[i]=UserSecurityStore[i];
		}
	}

	//constructs
	public osmsMessageAcquireUserKeyStoreResponse()
	{
		super(osmsMessage.osmsMESSAGE_ACQUIRE_USER_KEY_STORE_RESPONSE);
	}

}
