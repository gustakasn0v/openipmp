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

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.X509SPKIHash;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.server.ServerAbstract;
import com.mutable.drmPlugin.server.maps.ContentIdHash2Key;
import com.mutable.drmPlugin.server.maps.DeviceId2ContentId2RoId;
import com.mutable.drmPlugin.server.maps.RoId2ContentIdRights;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.Pair;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.FactoryHelper;
import com.mutable.drmPlugin.xml.IDocument;
import java.sql.Connection;

public class RoDbMySqlHelper {
	Connection con;
	ServerAbstract server;
	
	PreparedStatement listEncKeys, insertEncKey, updateEncKey;
	PreparedStatement listRoIdsRights, insertRoIdRights, updateRoIdRights;

	public RoDbMySqlHelper(Connection con, ServerAbstract server, String eTable, String rTable) throws SQLException {
		this.con = con;
		this.server = server;
		listEncKeys = con.prepareStatement(
				"select * from "+eTable);
		insertEncKey = con.prepareStatement(
				"insert into "+eTable+" values(?,?)");
		updateEncKey = con.prepareStatement(
				"update "+eTable
				+" set enc_key = ?"
				+" where content_id = ?");
		listRoIdsRights = con.prepareStatement(
				"select * from "+rTable);
		insertRoIdRights = con.prepareStatement(
				"insert into "+rTable+" values(?,?,?,?,?)");
		updateRoIdRights = con.prepareStatement(
				"update "+rTable
				+" set full_content_id = ?,"
				+" roid = ?,"
				+" rights = ? "				
				+" where device_id = ? and content_id = ?");
	}

	public ContentIdHash2Key getEncKeys() {
		ContentIdHash2Key keyMap = new ContentIdHash2Key();
		try {
			ResultSet rs = listEncKeys.executeQuery();
			while (rs.next()) {
				Base64String contentIdHash = new Base64String(rs.getString(1));
				Base64String encKey = new Base64String(rs.getString(2));
				keyMap.put(contentIdHash,encKey);
			};
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		};
		return keyMap;
	}

	public boolean insertEncKey(Base64String contentIdHash,Base64String encKey) {
		try {
			insertEncKey.clearParameters();
			insertEncKey.setString(1,contentIdHash.toString());
			insertEncKey.setString(2,encKey.toString());
			insertEncKey.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
		
	}
	
	public boolean updateEncKey(Base64String contentIdHash,Base64String encKey) {
		try {
			updateEncKey.clearParameters();
			updateEncKey.setString(2,contentIdHash.toString());
			updateEncKey.setString(1,encKey.toString());
			updateEncKey.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
		
	}
	
	public Pair getRoidsRights() {
		DeviceId2ContentId2RoId di2ci2ri = new DeviceId2ContentId2RoId();
		RoId2ContentIdRights ri2cir = new RoId2ContentIdRights();
		try {
			ResultSet rs = listRoIdsRights.executeQuery();
			while (rs.next()) {
				RoapIdentifier devId = new RoapIdentifier(new X509SPKIHash(new Base64String(rs.getString(1))));
				UriValue contentId = new UriValue(new String((byte[])rs.getObject(3)));
				IdValue roId = new IdValue(new String((byte[])rs.getObject(4)));
				String rightsString = new String((byte[])rs.getObject(5));
				IDocument doc = (new FactoryHelper()).decodeDocument(rightsString);    
				Rights rights = Rights.instanceFromDomElement(doc.getRootElement());
				di2ci2ri.put(devId,contentId,roId);
				ri2cir.put(roId,new Pair(contentId,rights));
			};
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		};
		return new Pair(di2ci2ri,ri2cir);
	}

	public boolean insertRoIdRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		try {
			insertRoIdRights.clearParameters();
			insertRoIdRights.setString(1,deviceId.toString());
			insertRoIdRights.setString(2,server.hash(contentId.toString()).toString());
			insertRoIdRights.setBytes(3,contentId.toString().getBytes());
			insertRoIdRights.setBytes(4,roId.toString().getBytes());
			insertRoIdRights.setBytes(5,rights.asDomDocument().encode().getBytes());
			insertRoIdRights.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
	}

	public boolean updateRoIdRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		try {
			updateRoIdRights.clearParameters();
			updateRoIdRights.setString(4,deviceId.toString());
			updateRoIdRights.setString(5,server.hash(contentId.toString()).toString());
			updateRoIdRights.setBytes(1,contentId.toString().getBytes());
			updateRoIdRights.setBytes(2,roId.toString().getBytes());
			updateRoIdRights.setBytes(3,rights.asDomDocument().encode().getBytes());
			updateRoIdRights.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
	}

}
