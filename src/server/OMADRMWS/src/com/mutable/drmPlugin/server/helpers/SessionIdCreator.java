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
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 * 
 *
 */
package com.mutable.drmPlugin.server.helpers;

import org.apache.axis.types.UnsignedInt;

import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.server.ISessionIdCreator;
import com.mutable.drmPlugin.server.ServerAbstract;

public class SessionIdCreator implements ISessionIdCreator {
	protected UnsignedInt lastId = new UnsignedInt(0);
	protected ServerAbstract server;

	public SessionId createSessionId(SessionId oldId) {
		lastId = (oldId==null) 
				? new UnsignedInt(lastId.intValue()+1)
				: new UnsignedInt(lastId.intValue()+oldId.getData().intValue());
		return new SessionId(lastId);
	}

	public SessionIdCreator(ServerAbstract server) {
		super();
		// TODO Auto-generated constructor stub
		this.server = server;
	}

}
