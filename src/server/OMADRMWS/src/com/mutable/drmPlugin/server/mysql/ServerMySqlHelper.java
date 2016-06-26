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
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.crypto.PrivateKeyImpl;
import com.mutable.drmPlugin.crypto.PublicKeyImpl;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.server.DeviceContext;
import com.mutable.drmPlugin.server.RiContext;
import com.mutable.drmPlugin.server.ServerAbstract;
import com.mutable.drmPlugin.server.maps.ContentIdHash2Key;
import com.mutable.drmPlugin.server.maps.KeyId2DevCtx;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.Base64StringVector;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.Pair;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.xml.FactoryHelper;
import com.mutable.drmPlugin.xml.IDocument;
import com.mutable.drmPlugin.xml.IElement;
import com.mutable.drmPlugin.xml.XmlException;

/**
 * The helper class performing all  MySql operations on behalf of the Server.
 * It maintains a single MySql connection, sharing it with the subordinate helpers
 * RegDbMySqlHelper and RoDbMySqlHelper, which are created and employed only by
 * this helper. All initialization of the server goes through this helper: at
 * startup it reads the database metadata from the appropriate config file
 * "..\\openIpmp\\OMADRM\\server_config.xml" and populates the
 * RegDatabase and RoDatabase. All database access and modification
 * also goes through this helper.
 * 
 * @see com.mutable.drmPlugin.server.Server 
 * @see RegDbMySqlHelper 
 * @see RoDbMySqlHelper 
 * @see com.mutable.drmPlugin.server.helpers.RegDatabase 
 * @see com.mutable.drmPlugin.server.helpers.RoDatabase
 * 
 *
 */
public class ServerMySqlHelper {
	
	public String mySqlDriver, mySqlPath, mySqlUser, mySqlPass;
	public String ctxTable, ekTable, roTable;
	public String riTable, dCaTable, riChainTable;
	public String riUrl;
	Connection con;
	ServerAbstract server;
	PreparedStatement getRiContext, storeRiContext;
	PreparedStatement getDeviceCas, storeDeviceCa;
	PreparedStatement getRiCertChain, storeRiChainElement;
	RegDbMySqlHelper regHelper;
	RoDbMySqlHelper roHelper;
	
	public ServerMySqlHelper(ServerAbstract server) throws ClassNotFoundException,SQLException {
		if (!setNamesFromFile(
				/*System.getProperty("user.dir")+"\\config\\server_config.xml"*/
				"../openIPMP/OMADRM/server_config.xml"))
			throw new XmlException();
		Class.forName(mySqlDriver);
		con = DriverManager.getConnection(mySqlPath,mySqlUser,mySqlPass);
		getRiContext = con.prepareStatement(
				"select * from "+riTable);
		storeRiContext = con.prepareStatement(
				"insert into "+riTable
				+" (private_key,context) values (?,?)");
		getDeviceCas = con.prepareStatement(
				"select * from "+dCaTable);
		storeDeviceCa = con.prepareStatement(
				"insert into "+dCaTable+" (cert) values(?)");
		getRiCertChain = con.prepareStatement(
				"select * from "+riChainTable);
		storeRiChainElement = con.prepareStatement(
				"insert into "+riChainTable+" (cert) values(?)");	
		regHelper = new RegDbMySqlHelper(con,ctxTable);
		roHelper = new RoDbMySqlHelper(con,server,ekTable,roTable);
	}
	
	protected boolean setNamesFromFile(String path) {
		IDocument doc = (new FactoryHelper()).fileInDocument(path);
		if (doc==null) return false;
		IElement root = doc.getRootElement();
		mySqlDriver = root.getChildStringValue("mySqlDriver");
		mySqlPath = root.getChildStringValue("mySqlPath");
		mySqlUser = root.getChildStringValue("mySqlUser");
		mySqlPass = root.getChildStringValue("mySqlPass");
		ekTable = root.getChildStringValue("rightsDatabase.encKeys");
		ctxTable = root.getChildStringValue("registrationDatabase.deviceContexts");
		roTable = root.getChildStringValue("rightsDatabase.rights");
		riTable = root.getChildStringValue("ri.context");
		dCaTable = root.getChildStringValue("ri.deviceCa");
		riChainTable = root.getChildStringValue("ri.riChain");
		riUrl = root.getChildStringValue("ri.url");
		return true;
	}
	
	
	
	public RiContext getRiContext() {
		try {
			ResultSet rs = getRiContext.executeQuery();
			if (!rs.first()) return null;
			String riCtxString = new String((byte[])rs.getObject(3));
			IDocument riCtxDoc = (new FactoryHelper()).decodeDocument(riCtxString);
			if (riCtxDoc==null) return null;
			RiContext riCtx = RiContext.instanceFromDomElement(riCtxDoc.getRootElement());
			if (riCtx==null) return null;
			PrivateKeyImpl priv = PrivateKeyImpl.instanceFromByteArray((byte[])rs.getObject(2));
			if (priv==null) return null;
			Base64StringVector caAndChain = getRiCertChain();
			if (caAndChain==null) return null;
			Base64StringVector deviceCas = getDeviceCas();
//			if (deviceCas==null) return null;
			Iterator i = caAndChain.iterator();
			Base64String caCert = (Base64String) i.next();
			Vector v = new Vector();
			for (;i.hasNext();)
				v.add((Base64String)i.next());
			CertificateChain chain = new CertificateChain(v);
			riCtx.setPrivateKey(priv);
			riCtx.setRiCaCert(caCert);
			riCtx.setCertChain(chain);
			riCtx.setTrustedDeviceCerts(deviceCas);
			Vector v2 = new Vector();
			for (Iterator j=deviceCas.iterator();j.hasNext();)
				v2.add(PublicKeyImpl.instanceFromEncodedCert((Base64String)j.next()).getIdentifier());
			riCtx.setTrusted(new KeyIdentifiers(v2));
			riCtx.setUrl(new UriValue(riUrl));
			return riCtx;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}

	public boolean storeRiContext(RiContext riCtx) {
		try {
			String riCtxString = riCtx.asDomDocument().encode();
			Base64String caCert = riCtx.getRiCaCert();
			Base64StringVector certChain = riCtx.getCertChain();
			Base64StringVector trustedCerts = riCtx.getTrustedDeviceCerts();
			storeRiContext.clearParameters();
			storeRiContext.setBytes(1,((PrivateKeyImpl)riCtx.getPrivateKey()).asByteArray());
			storeRiContext.setBytes(2,riCtxString.getBytes());
			storeRiContext.executeUpdate();
			if (!storeRiCertChain(caCert,certChain)) return false;
			if (!storeDeviceCas(trustedCerts)) return false;
			return true;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}
	
	public Base64StringVector getDeviceCas() {
		Vector v;
		try {
			ResultSet rs = getDeviceCas.executeQuery();
			v = new Vector();
			for(;rs.next();)
				v.add(new Base64String((byte[])rs.getObject(2)));
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
		return new Base64StringVector(v);	
	}
	
	public boolean storeDeviceCas(Base64StringVector cas) {
		try {
			for(Iterator i=cas.iterator();i.hasNext();) {
				byte[] caBytes = ((Base64String)i.next()).asByteArray();
				storeDeviceCa.clearParameters();
				storeDeviceCa.setBytes(1,caBytes);
				storeDeviceCa.executeUpdate();
			};
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
	}
	
	public Base64StringVector getRiCertChain() {
		Vector v;
		try {
			ResultSet rs = getRiCertChain.executeQuery();
			v = new Vector();
			for(;rs.next();)
				v.add(new Base64String((byte[])rs.getObject(2)));
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
		return new Base64StringVector(v);	
	}
	
	public boolean storeRiCertChain(Base64String riCaCert, Base64StringVector chain) {
		try {
			byte[] certBytes = riCaCert.asByteArray();
			storeRiChainElement.clearParameters();
			storeRiChainElement.setBytes(1,certBytes);
			storeRiChainElement.executeUpdate();
			for(Iterator i=chain.iterator();i.hasNext();) {
				certBytes = ((Base64String)i.next()).asByteArray();
				storeRiChainElement.clearParameters();
				storeRiChainElement.setBytes(1,certBytes);
				storeRiChainElement.executeUpdate();
			};
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		};
		return true;
	}

	public KeyId2DevCtx getContexts() {
		return regHelper.getContexts();
	}

	public boolean insertContext(RoapIdentifier deviceId, DeviceContext ctx) {
		return regHelper.insertContext(deviceId, ctx);
	}

	public boolean updateContext(RoapIdentifier deviceId, DeviceContext ctx) {
		return regHelper.updateContext(deviceId, ctx);
	}

	public ContentIdHash2Key getEncKeys() {
		return roHelper.getEncKeys();
	}

	public Pair getRoidsRights() {
		return roHelper.getRoidsRights();
	}

	public boolean insertEncKey(Base64String contentIdHash, Base64String encKey) {
		return roHelper.insertEncKey(contentIdHash, encKey);
	}

	public boolean insertRoIdRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		return roHelper.insertRoIdRights(deviceId, contentId, roId, rights);
	}

	public boolean updateEncKey(Base64String contentIdHash, Base64String encKey) {
		return roHelper.updateEncKey(contentIdHash, encKey);
	}

	public boolean updateRoIdRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		return roHelper.updateRoIdRights(deviceId, contentId, roId, rights);
	}

}
