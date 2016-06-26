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
 * <p>Title: </p>
 * <p>Description: </p>
 * @version 1.0
 */

import java.util.Date;


public class osmsMessageGetContentKeyRequest extends osmsMessage
{
	//constructs
	public osmsMessageGetContentKeyRequest ()
	{
		super(osmsMessage.osmsMESSAGE_GET_CONTENT_KEY_REQUEST);
	}

	//bean properties
	private String m_MetadataType=null;
	public String getMetadataType(){return m_MetadataType;}
	public void setMetadataType(String MetadataType){m_MetadataType=MetadataType;}

	private String m_DigitalItemInstanceId=null;
	public String getDigitalItemInstanceId(){return m_DigitalItemInstanceId;}
	public void setDigitalItemInstanceId(String DigitalItemInstanceId){m_DigitalItemInstanceId=DigitalItemInstanceId;}
}
