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
package com.mutable.drmPlugin.server.mysql;

import java.io.IOException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.server.DeviceContext;
import com.mutable.drmPlugin.server.maps.KeyId2DevCtx;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.xml.FactoryHelper;
import com.mutable.drmPlugin.xml.IDocument;
import java.sql.Connection;

public class RegDbMySqlHelper {
	
	Connection con;
	PreparedStatement listContexts, insertContext, updateContext;
	
	public RegDbMySqlHelper(Connection con, String cTable) throws SQLException {
		this.con = con;
		listContexts = con.prepareStatement(
				"select * from "+cTable);
		insertContext = con.prepareStatement(
				"insert into "+cTable+" values(?,?)");
		updateContext = con.prepareStatement(
				"update "+cTable
				+" set context =?"
				+" where device_id = ?");
	}
	
	public KeyId2DevCtx getContexts() {
		KeyId2DevCtx contextMap = new KeyId2DevCtx();
		try {
			ResultSet rs = listContexts.executeQuery();
			while (rs.next()) {
				RoapIdentifier deviceId = new RoapIdentifier(new X509SPKIHash(new Base64String(rs.getString(1))));
				String ctxString = new String((byte[])rs.getObject(2));
				IDocument doc = (new FactoryHelper()).decodeDocument(ctxString);
				DeviceContext devCtx = DeviceContext.instanceFromDomElement(doc.getRootElement());
				contextMap.put(deviceId,devCtx);
			};
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
		return contextMap;
	}
	
	public boolean insertContext(RoapIdentifier deviceId,DeviceContext ctx) {
		try {
			insertContext.clearParameters();
			insertContext.setString(1,deviceId.toString());
			String ctxString = ctx.asDomDocument().encode();
			insertContext.setBytes(2,ctxString.getBytes());
			insertContext.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
		
	}
	
	public boolean updateContext(RoapIdentifier deviceId, DeviceContext ctx) {
		try {
			updateContext.clearParameters();
			updateContext.setString(2,deviceId.toString());
			String ctxString = ctx.asDomDocument().encode();
			updateContext.setBytes(1,ctxString.getBytes());
			updateContext.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
		
	}

}
