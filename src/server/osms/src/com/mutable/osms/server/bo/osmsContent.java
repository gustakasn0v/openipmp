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
  * @version 1.1
  */

package com.mutable.osms.server.bo;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;

import java.io.Serializable;

import com.mutable.osms.server.db.bean.*;
import com.mutable.osms.server.bo.base.*;

public class osmsContent extends osmsContentBase implements Serializable
{
	//DOI
	private osmsDoi m_doi;
	public osmsDoi getDoi()
	{
		return m_doi;
	}
	public void setDoi(osmsDoi doi)
	{
		m_doi=doi;
	}
	//Content/DOI
	private osmsContentDoi m_contentDoi;
	public osmsContentDoi getContentDoi()
	{
		return m_contentDoi;
	}
	public void setContentDoi(osmsContentDoi contentDoi)
	{
		m_contentDoi=contentDoi;
	}
	//GRID
	private osmsGrid m_grid;
	public osmsGrid getGrid()
	{
		return m_grid;
	}
	public void setGrid(osmsGrid grid)
	{
		m_grid=grid;
	}
	//Content/GRID
	private osmsContentGrid m_contentGrid;
	public osmsContentGrid getContentGrid()
	{
		return m_contentGrid;
	}
	public void setContentGrid(osmsContentGrid contentGrid)
	{
		m_contentGrid=contentGrid;
	}
	//Registering User
	private osmsUsers m_registeredByUser;
	public osmsUsers getRegisteredByUser()
	{
		return m_registeredByUser;
	}
	public void setRegisteredByUser(osmsUsers registeredByUser)
	{
		m_registeredByUser=registeredByUser;
	}
}
