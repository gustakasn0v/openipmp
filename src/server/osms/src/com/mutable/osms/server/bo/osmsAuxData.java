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


package com.mutable.osms.server.bo;

/**
 * <p>Title: osmsAuxData </p>
 * <p>Description: Business Object Class for managing auxillary data </p>
 * @version 1.0
 */

import java.io.Serializable;

import com.mutable.osms.server.db.bean.*;
import com.mutable.osms.server.bo.base.*;

public class osmsAuxData implements Serializable
{
	//Tool Identifier registered to manage/protect the content
	private Integer m_toolIdentifier;
	public Integer getToolIdentifier()
	{
		return m_toolIdentifier;
	}
	public void setToolIdentifier(Integer toolIdentifier)
	{
		m_toolIdentifier=toolIdentifier;
	}

	//Host or IP Address of the Right's host used for rights resolution
	private String m_rightsHostUrl;
	public String getRightsHostUrl()
	{
		return m_rightsHostUrl;
	}
	public void setRightsHostUrl(String rightsHostUrl)
	{
		m_rightsHostUrl=rightsHostUrl;
	}

	//Port of the Right's host used for rights resolution
	private String m_rightsHostPort;
	public String getRightsHostPort()
	{
		return m_rightsHostPort;
	}
	public void setRightsHostPort(String rightsHostPort)
	{
		m_rightsHostPort=rightsHostPort;
	}

	//Content protection indicator
	private boolean m_isProtected;
	public boolean isProtected()
	{
		return m_isProtected;
	}
	public void setIsProtected(boolean isProtected)
	{
		m_isProtected=isProtected;
	}

}

