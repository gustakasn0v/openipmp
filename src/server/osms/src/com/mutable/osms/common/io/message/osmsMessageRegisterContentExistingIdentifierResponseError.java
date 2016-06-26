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
 * <p>Title: osmsMessageRegisterContentExistingIdentifierResponseError</p>
 * <p>Description: </p>
 * @version 1.0
 */

public class osmsMessageRegisterContentExistingIdentifierResponseError extends osmsMessageResponseError
{
	//constructs
	public osmsMessageRegisterContentExistingIdentifierResponseError()
	{
		super(osmsMessage.osmsMESSAGE_REGISTER_CONTENT_EXISTING_IDENTIFIER_RESPONSE_ERROR);
	}
	public osmsMessageRegisterContentExistingIdentifierResponseError(int errCode, String errMsg)
	{
		super(osmsMessage.osmsMESSAGE_REGISTER_CONTENT_ASSIGN_IDENTIFIER_RESPONSE_ERROR, errCode, errMsg);
	}
}