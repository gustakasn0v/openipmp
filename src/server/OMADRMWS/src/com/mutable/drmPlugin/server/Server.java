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
package com.mutable.drmPlugin.server;

import java.io.IOException;
import java.sql.SQLException;

import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.server.helpers.RegDatabase;
import com.mutable.drmPlugin.server.helpers.RoDatabase;
import com.mutable.drmPlugin.server.maps.ContentIdHash2Key;
import com.mutable.drmPlugin.server.maps.DeviceId2ContentId2RoId;
import com.mutable.drmPlugin.server.maps.KeyId2DevCtx;
import com.mutable.drmPlugin.server.maps.RoId2ContentIdRights;
import com.mutable.drmPlugin.server.mysql.ServerMySqlHelper;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.Pair;
import com.mutable.drmPlugin.tools.UriValue;

/**
 * This is the mother class implementing the OMADRM server, building upon TestServer and ServerAbstract. 
 * It stores all its data
 * in a MySql database.  The maps of the RegDatabase
 * and RoDatabase helpers are designed to be in sync with the MySql database at all 
 * times - in consequence the MySql database is read only at initialization. 
 * It gets however written in runtime, with registration and rights data.
 * The implementation
 * expects that the MySql database is kept safe by administrative means - critical 
 * cryptographic information is  stored there in the open.  At startup the server reads
 * the database info (driver, path, user, password, table names) from an xml config file. Everything else
 * (existing contexts, rights, server data etc) is expected to be in the MySql database.
 * The current implementation provides scripts for MySql database creation and maintenance.
 * 
 * @see ServerMySqlHelper TestServer ServerAbstract
 * 
 *
 */
public class Server extends TestServer {
	
//	public static TestServer server = new Server();

	ServerMySqlHelper helper;

	public Server() {
		super();
	}
	
	public void initializeData() throws IOException, SQLException, ClassNotFoundException {
		helper = new ServerMySqlHelper(this);
		setFromDatabase();
	}

	public void setFromDatabase() {
		RiContext riCtx = helper.getRiContext();
		KeyId2DevCtx ki2dc = helper.getContexts();
		ContentIdHash2Key ci2k = helper.getEncKeys();
		Pair roIdsRights = helper.getRoidsRights();
		regDb = new RegDatabase(this,ki2dc,riCtx);
		roDb = new RoDatabase(this,ci2k,
				(DeviceId2ContentId2RoId) roIdsRights.getFst(),
				(RoId2ContentIdRights) roIdsRights.getSnd());
	}

	public boolean insertContext(RoapIdentifier deviceId, DeviceContext ctx) {
		return helper.insertContext(deviceId, ctx);
	}

	public boolean insertEncKey(Base64String contentIdHash, Base64String encKey) {
		return helper.insertEncKey(contentIdHash, encKey);
	}

	public boolean insertRoIdRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		return helper.insertRoIdRights(deviceId, contentId, roId, rights);
	}

	public boolean updateContext(RoapIdentifier deviceId, DeviceContext ctx) {
		return helper.updateContext(deviceId, ctx);
	}

	public boolean updateEncKey(Base64String contentIdHash, Base64String encKey) {
		return helper.updateEncKey(contentIdHash, encKey);
	}

	public boolean updateRoIdRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		return helper.updateRoIdRights(deviceId, contentId, roId, rights);
	}

	public boolean addContentKey(UriValue contentId, Base64String encKey) {
		Base64String hash = hash(contentId.toString());
		boolean success = (getContentKey(contentId)==null) 
							? insertEncKey(hash,encKey)
							: updateEncKey(hash,encKey);
		return success && super.addContentKey(contentId, encKey);
	}

	public boolean addContext(DeviceContext ctx) {
		RoapIdentifier deviceId = ctx.getId();
		boolean success = (getContext(deviceId)==null) 
							? insertContext(deviceId,ctx)
		                    : updateContext(deviceId,ctx);
		return success && super.addContext(ctx);
	}

	public boolean addRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		boolean success = (getRoId(deviceId,contentId)==null)
							? insertRoIdRights(deviceId,contentId,roId,rights)
							: updateRoIdRights(deviceId,contentId,roId,rights);
		return success && super.addRights(deviceId, contentId, roId, rights);
	}


}
