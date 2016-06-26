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
import java.security.Security;
import java.sql.SQLException;

import org.bouncycastle.jce.provider.BouncyCastleProvider;

import com.mutable.drmPlugin.crypto.CertificateVerifier;
import com.mutable.drmPlugin.crypto.Hasher;
import com.mutable.drmPlugin.crypto.NonceCreator;
import com.mutable.drmPlugin.roap.messages.DeviceHelloRequest;
import com.mutable.drmPlugin.roap.messages.FailureRegistrationResponse;
import com.mutable.drmPlugin.roap.messages.FailureRiHelloResponse;
import com.mutable.drmPlugin.roap.messages.FailureRoResponse;
import com.mutable.drmPlugin.roap.messages.RegistrationRequest;
import com.mutable.drmPlugin.roap.messages.RegistrationResponse;
import com.mutable.drmPlugin.roap.messages.RiHelloResponse;
import com.mutable.drmPlugin.roap.messages.RoRequest;
import com.mutable.drmPlugin.roap.messages.RoResponse;
import com.mutable.drmPlugin.roap.messages.RoapTriggerAbstract;
import com.mutable.drmPlugin.roap.messages.status.MalformedRequestStatus;
import com.mutable.drmPlugin.server.helpers.ProtocolTracker;
import com.mutable.drmPlugin.server.helpers.RoIdCreator;
import com.mutable.drmPlugin.server.helpers.SessionIdCreator;
import com.mutable.drmPlugin.server.helpers.TriggerCreator;
import com.mutable.drmPlugin.server.nonRoapMessages.AddContentKeyRequest;
import com.mutable.drmPlugin.server.nonRoapMessages.AddContentKeyResponse;
import com.mutable.drmPlugin.server.nonRoapMessages.AddDeviceRightsRequest;
import com.mutable.drmPlugin.server.nonRoapMessages.AddDeviceRightsResponse;
import com.mutable.drmPlugin.server.nonRoapMessages.InitialRoRequest;
import com.mutable.drmPlugin.xml.FactoryHelper;
import com.mutable.drmPlugin.xml.IDocument;
import com.mutable.omadrm.ws.OMADRMWSBindingImpl;

/**
 * TestServer refines ServerAbstract with a distinguished instance theServer, 
 * static methods
 * wiring external calls to this instance, and partial initialization creating
 * various helpers. The concrete subclasses need to initialize theServer and to
 * implement the initializeData() method,
 * which is expected to create the RegistrationDatabase
 * and RoDatabase helpers, initializing the server with conrete content.
 * 
 * @see Server 
 * @see ServerWithXml 
 * @see OMADRMWSBindingImpl
 * 
 *
 */
public abstract class TestServer extends ServerAbstract {
	
	public static TestServer theServer = new Server();
	
	/**
	 * Parses an input string to an AddContentKeyRequest object and invokes the
	 * appropriate handler on theServer.
	 * 
	 * @param msg string supposedly encoding an AddContentKeyRequest object
	 * @return string encoding the AddContentKeyResponse object
	 * 
	 * @see AddContentKeyRequest 
	 * @see AddContentKeyResponse
	 */
	public static String handleAddContentKeyRequest(String msg) {
		AddContentKeyRequest req=null;
		try {
			log("received:",msg);
			IDocument doc = (new FactoryHelper()).decodeDocument(msg);
			log("xml parsed",null);
			req = AddContentKeyRequest.instanceFromDomElement(doc.getRootElement());
			if (req!=null) log("dom parsed",null);
			AddContentKeyResponse res = theServer.handleAddContentKeyRequest(req);
			if (res!=null) log("request processed",null);
			else { log("processing failed",null); return null; }
			String ret = res.asDomDocument().encode();
			log("returning:",ret);
			return ret;
		} catch (RuntimeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return new AddContentKeyResponse(null,false).asDomDocument().encode();
		}		
	}
	
	/**
	 * Parses an input string to an AddDeviceRightsRequest object and invokes the
	 * appropriate handler on theServer.
	 * 
	 * @param msg string supposedly encoding an AddDeviceRightsRequest object
	 * @return string encoding the AddDeviceRightsResponse object
	 * 
	 * @see AddDeviceRightsRequest 
	 * @see AddDeviceRightsResponse
	 */

	public static String handleAddDeviceRightsRequest(String msg) {
		AddDeviceRightsRequest req=null;
		try {
			log("received:",msg);
			IDocument doc = (new FactoryHelper()).decodeDocument(msg);
			log("xml parsed",null);
			req = AddDeviceRightsRequest.instanceFromDomElement(doc.getRootElement());
			if (req!=null) log("dom parsed",null);
			AddDeviceRightsResponse res = theServer.handleAddDeviceRightsRequest(req);
			if (res!=null) log("request processed",null);
			else { log("processing failed",null); return null; }
			String ret = res.asDomDocument().encode();
			log("returning:",ret);
			return ret;
		} catch (RuntimeException e) {
			e.printStackTrace();
			return new AddDeviceRightsResponse(null,false).asDomDocument().encode();
		}
	}

	/**
	 * Parses an input string to an InitialRoRequest object and invokes the
	 * appropriate handler on theServer.
	 * 
	 * @param msg string supposedly encoding an InitialRoRequest object
	 * @return string encoding the AddContentKeyResponse object
	 * 
	 * @see InitialRoRequest 
	 * @see InitialRoResponse
	 */

	public static String handleInitialRoRequest(String msg) {
		try {
			log("received:",msg);
			IDocument doc = (new FactoryHelper()).decodeDocument(msg);
			log("xml parsed",null);
			InitialRoRequest req  = InitialRoRequest.instanceFromDomElement(doc.getRootElement());
			if (req!=null) log("dom parsed",null);
			RoapTriggerAbstract trigger = theServer.handleInitialRoRequest(req);
			if (trigger!=null) log("request processed",null);
			else { log("processing failed",null); return ""; }
			String ret = trigger.asDomDocument().encode();
			log("returning:",ret);
			return ret;
		} catch (RuntimeException e) {
			e.printStackTrace();
			return "";
		}
	}

	/**
	 * Parses an input string to a DeviceHelloRequest object and invokes the
	 * appropriate handler on theServer.
	 * 
	 * @param msg string supposedly encoding a DeviceHelloRequest object
	 * @return string encoding the RiHelloResponse object
	 * 
	 * @see DeviceHelloRequest 
	 * @see RiHelloResponse
	 */

	public static String handleDeviceHelloRequest(String msg) {
		try {
			log("received:",msg);
			IDocument doc = (new FactoryHelper()).decodeDocument(msg);
			log("xml parsed",null);
			DeviceHelloRequest req  = DeviceHelloRequest.instanceFromDomElement(doc.getRootElement());
			if (req!=null) log("dom parsed",null);
			RiHelloResponse res = theServer.handleDeviceHelloRequest(req);
			if (res!=null) log("request processed",null);
			else { log("processing failed",null); return null; }
			String ret = res.asDomDocument().encode();
			log("returning:",ret);
			return ret;
		} catch (RuntimeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return new FailureRiHelloResponse(new MalformedRequestStatus()).asDomDocument().encode();
		}
	}

	/**
	 * Parses an input string to a RegistrationRequest object and invokes the
	 * appropriate handler on theServer.
	 * 
	 * @param msg string supposedly encoding an RegistrationRequest object
	 * @return string encoding the RegistrationResponse object
	 * 
	 * @see RegistrationRequest 
	 * @see RegistrationResponse
	 */

	public static String handleRegistrationRequest(String msg) {
		try {
			log("received:",msg);
			IDocument doc = (new FactoryHelper()).decodeDocument(msg);
			log("xml parsed",null);
			RegistrationRequest req  = RegistrationRequest.instanceFromDomElement(doc.getRootElement());
			if (req!=null) log("dom parsed",null);
			RegistrationResponse res = theServer.handleRegistrationRequest(req);
			if (res!=null) log("request processed",null);
			else { log("processing failed",null); return null; }
			String ret = res.asDomDocument().encode();
			log("returning:",ret);
			return ret;
		} catch (RuntimeException e) {
			e.printStackTrace();
			return new FailureRegistrationResponse(new MalformedRequestStatus()).asDomDocument().encode();
		}
	}

	/**
	 * Parses an input string to a RoRequest object and invokes the
	 * appropriate handler on theServer.
	 * 
	 * @param msg string supposedly encoding an RoRequest object
	 * @return string encoding the RoResponse object
	 * 
	 * @see RoRequest 
	 * @see RoResponse
	 */
	
	public static String handleRoRequest(String msg) {
		try {
			log("received:",msg);
			IDocument doc = (new FactoryHelper()).decodeDocument(msg);
			log("xml parsed",null);
			RoRequest req  = RoRequest.instanceFromDomElement(doc.getRootElement());
			if (req!=null) log("dom parsed",null);
			RoResponse res = theServer.handleRoRequest(req);
			if (res!=null) log("request processed",null);
			else { log("processing failed",null); return null; }
			String ret = res.asDomDocument().encode();
			log("returning:",ret);
			return ret;
		} catch (RuntimeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return new FailureRoResponse(new MalformedRequestStatus()).asDomDocument().encode();
		}
	}

	/**
	 * The constructor creating all helpers. The RegistrationDatabase and RoDatabase
	 * helpers are expected from the abstract method initializeData().
	 *
	 */
	public TestServer()  {
		try {
			initializeData(); // sets the databases
		} catch (Exception e) {
			e.printStackTrace();
		}					
		tracker = new ProtocolTracker();
		noncer = new NonceCreator();
		certer = new CertificateVerifier(getRiContext().getTrustedDeviceCerts());
		hasher = new Hasher();
		triggerer = new TriggerCreator(this);
		righter = new RoIdCreator(this);
		sessioner = new SessionIdCreator(this);
		Security.addProvider(new BouncyCastleProvider());

	}

	/**
	 * The abstract method is expected to create the RegistrationDatabase and RoDatabase
	 * helpers and to populate them with initial data. It might raise different kinds of 
	 * exceptions, depending on its concrete incarnations.
	 * 
	 * @throws IOException
	 * @throws SQLException
	 * @throws ClassNotFoundException
	 */
	public abstract void initializeData() throws IOException, SQLException, ClassNotFoundException;
	
	/**
	 * Indicates where the config file appropriate to the concrete server is expected.
	 * 
	 * @see Server 
	 * @see ServerWithXml
	 */
	public String getConfigPath() { 
		return System.getProperty("user.dir")+"\\config\\server.xml"; 
	}
	
		
		


}
