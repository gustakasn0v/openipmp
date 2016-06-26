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
 * <p>Title: osmsMessageRegisterDigitalItemInstanceResponseError</p>
 * <p>Description: </p>
 * @version 1.0
 */

public class osmsMessageRegisterDigitalItemInstanceResponseError extends osmsMessageResponseError
{
	//constructs
	public osmsMessageRegisterDigitalItemInstanceResponseError()
	{
		super(osmsMessage.osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR);
	}
	public osmsMessageRegisterDigitalItemInstanceResponseError(int errCode, String errMsg)
	{
		super(osmsMessage.osmsMESSAGE_REGISTER_DIGITAL_ITEM_INSTANCE_RESPONSE_ERROR, errCode, errMsg);
	}
}