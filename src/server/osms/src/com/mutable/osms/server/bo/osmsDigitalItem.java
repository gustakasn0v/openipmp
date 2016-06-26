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
  * <p>Description: </p>
  * @version 1.0
  */

package com.mutable.osms.server.bo;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;

import java.io.Serializable;

import com.mutable.osms.server.db.bean.*;
import com.mutable.osms.server.bo.base.*;

public class osmsDigitalItem extends osmsDigitalItemBase implements Serializable
{
	private osmsDigitalItem[] m_digitalItems;
	public osmsDigitalItem[] getDigitalItems()
	{
		return m_digitalItems;
	}
	public void setDigitalItems(osmsDigitalItem[] digitalItems)
	{
		m_digitalItems=digitalItems;
	}
	private osmsDoi m_doi;
	public osmsDoi getDoi()
	{
		return m_doi;
	}
	public void setDoi(osmsDoi doi)
	{
		m_doi=doi;
	}
	private osmsUsers m_registeredByUser;
	public osmsUsers getRegisteredByUser()
	{
		return m_registeredByUser;
	}
	public void setRegisteredByUser(osmsUsers registeredByUser)
	{
		m_registeredByUser=registeredByUser;
	}

	private osmsContent m_content;
	public osmsContent getContent()
	{
		return m_content;
	}
	public void setContent(osmsContent content)
	{
		m_content=content;
	}
}
