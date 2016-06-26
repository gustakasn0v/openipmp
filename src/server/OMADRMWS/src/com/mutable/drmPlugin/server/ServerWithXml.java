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
import java.security.KeyStore;

import com.mutable.drmPlugin.crypto.KeyStoreHelper;
import com.mutable.drmPlugin.crypto.KeyStoreInfo;
import com.mutable.drmPlugin.server.helpers.RegDatabase;
import com.mutable.drmPlugin.server.helpers.RoDatabase;
import com.mutable.drmPlugin.server.maps.KeyId2DevCtx;
import com.mutable.drmPlugin.server.mysql.ServerMySqlHelper;
import com.mutable.drmPlugin.tools.Pair;
import com.mutable.drmPlugin.xml.FactoryHelper;
import com.mutable.drmPlugin.xml.IDocument;
import com.mutable.drmPlugin.xml.IElement;

/**
 * This is an incomplete implementation of a server based on databases stored as
 * xml files, and cryptographic content (keys, certificates) stored in Java keystores.
 * It is not used in the current server implementation, but has been used in its  
 * development. This class, and various methods (even some classes) supporting it 
 * scattered around, are
 * included here just for the convenience of anyone wishing to experiment with
 * and build upon the 
 * current implementation.
 * 
 *
 */
public class ServerWithXml extends TestServer {

	KeyStoreInfo riStoreInfo;
	KeyStoreInfo devStoreInfo;
	KeyStore riStore;
	KeyStore devStore;
	ServerMySqlHelper helper;

//	protected static TestServer theServer = new ServerWithXml();
	
	public ServerWithXml() {
		super();
	}

	public void initializeData() throws IOException {
		setFromFile(getConfigPath());
	}

	public String getConfigPath() { return System.getProperty("user.dir")+"\\config\\xml\\server.xml"; }
	
	public KeyStore getDeviceKeyStore() {	
		return devStore;
	}

	public String getPrivateKeyPass() {
		return "omadrm";
	}

	public KeyStore getRissuerKeyStore() {
		// TODO Auto-generated method stub
		return riStore;
	}

	public void setFromFile(String path) throws IOException {
		IDocument doc = (new FactoryHelper()).fileInDocument(path) ;
		setFromDomElement(doc.getRootElement());
	}

	public void setFromDomElement(IElement elem) throws IOException {
		riStoreInfo = KeyStoreInfo.instanceFromDomElement(elem.getChildElement("keyStores.rissuerStore"));
		riStore = KeyStoreHelper.readKeyStore(riStoreInfo);
		devStoreInfo = KeyStoreInfo.instanceFromDomElement(elem.getChildElement("keyStores.deviceStore"));
		devStore = KeyStoreHelper.readKeyStore(devStoreInfo);
		String regDbPath = elem.getChildStringValue("regDbPath");
		String roDbPath = elem.getChildStringValue("roDbPath");
		RiContext riCtx = new RiContext(this);
		riCtx.setFromDomElement(elem.getChildElement("RIContext"));
		riCtx.setChainAndKeyFromStore(riStore);
		riCtx.setPrivateKeyFromKeyStore(riStore);
		riCtx.setTrustedCertsFromKeyStore(riStore);
		regDb = new RegDatabase(this, KeyId2DevCtx.instanceFromFile(regDbPath),riCtx);
		roDb = new RoDatabase(this); //TODO
	}


}
