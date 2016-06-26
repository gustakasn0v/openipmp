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

public class osmsDoi extends osmsDoiBase implements Serializable
{
	public static final String DOI_APP_PROFILE_KERNEL = "KERN";

	private osmsDoiProfile m_doiProfile;
	public osmsDoiProfile getDoiProfile()
	{
		return m_doiProfile;
	}
	public void setDoiProfile(osmsDoiProfile doiProfile)
	{
		m_doiProfile=doiProfile;
	}

	private osmsDoiAgent[] m_doiAgents;
	public osmsDoiAgent[] getDoiAgents()
	{
		return m_doiAgents;
	}
	public void setDoiAgents(osmsDoiAgent[] doiAgents)
	{
		m_doiAgents=doiAgents;
	}

	private osmsAltIdentifier[] m_altIdentifiers;
	public osmsAltIdentifier[] getAltIdentifiers()
	{
		return m_altIdentifiers;
	}
	public void setAltIdentifiers(osmsAltIdentifier[] altIdentifiers)
	{
		m_altIdentifiers=altIdentifiers;
	}

	private osmsDoiTitle[] m_doiTitles;
	public osmsDoiTitle[] getDoiTitles()
	{
		return m_doiTitles;
	}
	public void setDoiTitles(osmsDoiTitle[] doiTitles)
	{
		m_doiTitles=doiTitles;
	}
	private osmsDoi m_masterDoi;
	public osmsDoi getMasterDoi()
	{
		return m_masterDoi;
	}
	public void setMasterDoi(osmsDoi masterDoi)
	{
		m_masterDoi=masterDoi;
	}
}
