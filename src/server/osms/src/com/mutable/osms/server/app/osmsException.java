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


package com.mutable.osms.server.app;

/**
 * <p>Title: osmsException </p>
 * <p>Description: Exception class specific to osms Application</p>
 * @version 1.0
 */

import java.lang.Exception;

public class osmsException extends Exception
{
	private int m_ErrorCode;
	private void setErrorCode(int ErrorCode)
	{
		m_ErrorCode=ErrorCode;
	}
	public int getErrorCode()
	{
		return m_ErrorCode;
	}

	public osmsException(int ErrorCode, String p_Message)
	{
		super(p_Message);
		this.setErrorCode(ErrorCode);
	}
}