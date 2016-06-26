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
package com.mutable.osms.server.db.manager;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;
import java.sql.*;

import java.io.Serializable;
import java.util.Vector;

import com.mutable.osms.server.db.manager.base.*;
import com.mutable.osms.server.db.bean.*;

public class osmsDvUsersManager extends osmsDvUsersManagerBase implements Serializable
{


	//------------------------------------------------------------------
	// PRIVATE getNextSequence
	//------------------------------------------------------------------
	private Integer getNextSequence(Connection conn)
		throws Exception
	{
		osmsDvPkControlManagerBase managerPkControl = new osmsDvPkControlManagerBase();
		osmsDvPkControlBean[] bean = managerPkControl.getByTableName(getTableName(),conn);
		Integer seq= bean[0].getCurrPkValue();
		bean[0].setCurrPkValue(new Integer(seq.intValue()+1));
		managerPkControl.update(bean[0],conn);

		return new Integer(seq.intValue()+1);


	}

	//------------------------------------------------------------------
	// INSERT
	//------------------------------------------------------------------
	public void insert(osmsDvUsersBean bean,Connection conn)
		throws Exception
	{
		Integer seq = getNextSequence(conn);
		bean.setUserId( seq);
		super.insert(bean,conn);
	}

}
