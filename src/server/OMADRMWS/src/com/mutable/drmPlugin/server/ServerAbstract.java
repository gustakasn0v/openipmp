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

import java.util.Iterator;
import java.util.Vector;

import com.mutable.drmPlugin.crypto.ICertificateVerifier;
import com.mutable.drmPlugin.crypto.IHasher;
import com.mutable.drmPlugin.crypto.INonceCreator;
import com.mutable.drmPlugin.crypto.IPublicKey;
import com.mutable.drmPlugin.roap.messages.DeviceHelloRequest;
import com.mutable.drmPlugin.roap.messages.FailureRegistrationResponse;
import com.mutable.drmPlugin.roap.messages.FailureRiHelloResponse;
import com.mutable.drmPlugin.roap.messages.FailureRoResponse;
import com.mutable.drmPlugin.roap.messages.RegistrationRequest;
import com.mutable.drmPlugin.roap.messages.RegistrationRequestTrigger;
import com.mutable.drmPlugin.roap.messages.RegistrationResponse;
import com.mutable.drmPlugin.roap.messages.RiHelloResponse;
import com.mutable.drmPlugin.roap.messages.RoAcquisitionTrigger;
import com.mutable.drmPlugin.roap.messages.RoRequest;
import com.mutable.drmPlugin.roap.messages.RoResponse;
import com.mutable.drmPlugin.roap.messages.RoapTriggerAbstract;
import com.mutable.drmPlugin.roap.messages.SuccessRegistrationResponse;
import com.mutable.drmPlugin.roap.messages.TwoPassRoResponse;
import com.mutable.drmPlugin.roap.messages.extensions.RegistrationResponseExtensions;
import com.mutable.drmPlugin.roap.messages.status.AbortStatus;
import com.mutable.drmPlugin.roap.messages.status.AccessDeniedStatus;
import com.mutable.drmPlugin.roap.messages.status.FailureStatus;
import com.mutable.drmPlugin.roap.messages.status.NotRegisteredStatus;
import com.mutable.drmPlugin.roap.messages.status.SignatureErrorStatus;
import com.mutable.drmPlugin.roap.messages.status.Status;
import com.mutable.drmPlugin.roap.messages.status.SuccessStatus;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.roap.ro.ProtectedRo;
import com.mutable.drmPlugin.roap.ro.ProtectedRos;
import com.mutable.drmPlugin.roap.ro.RoInfo;
import com.mutable.drmPlugin.roap.ro.RoInfos;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.server.helpers.Logger;
import com.mutable.drmPlugin.server.nonRoapMessages.AddContentKeyRequest;
import com.mutable.drmPlugin.server.nonRoapMessages.AddContentKeyResponse;
import com.mutable.drmPlugin.server.nonRoapMessages.AddDeviceRightsRequest;
import com.mutable.drmPlugin.server.nonRoapMessages.AddDeviceRightsResponse;
import com.mutable.drmPlugin.server.nonRoapMessages.InitialRoRequest;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.Base64StringVector;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.Pair;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;

/**
 * Core OMADRM server functionality, with abstract databases. In addition
 * to providing a full implementation of OMADRMServer interface, this class
 * defines a bunch of workhorse methods, driving different helpers as specified by
 * impelemented helper interfaces. The 
 * subclasses TestServer, ServerWithXml, Server
 * elaborate on and implement initialization and storage.
 * 
 * 
 *
 */
public abstract class ServerAbstract implements OMADRMServer,
				ICertificateVerifier,IHasher,INonceCreator,IProtocolTracker,
				IRegistrationDatabase,IRoDatabase,ISessionIdCreator,ITriggerCreator{

	/*
	 * helper interfaces
	 */
	protected IRegistrationDatabase regDb;
	protected IProtocolTracker tracker;
	protected IRoDatabase roDb;
	protected INonceCreator noncer;
	protected ICertificateVerifier certer;
	protected IHasher hasher;
	protected ISessionIdCreator sessioner;
	protected IRoIdCreator righter;
	protected ITriggerCreator triggerer;
	

	/*
	 * encoder interface
	 */
	
	/*
	 * implementing  OMADRMServer.handleAddContentKeyRequest
	 */
	public synchronized AddContentKeyResponse handleAddContentKeyRequest(
			AddContentKeyRequest request) {
		Nonce nonce=null;
		try {
			nonce = request.getNonce();
			UriValue contentId = request.getContent();
			Base64String encKey = request.getEncKey();
			boolean success = addContentKey(contentId, encKey);
			return new AddContentKeyResponse(nonce,success);
		} catch (RuntimeException e) {
			e.printStackTrace();
			return new AddContentKeyResponse(nonce,false);
		}
	}

	/*
	 * implementing  OMADRMServer.handleAddDeviceRightsRequest
	 */

	public synchronized AddDeviceRightsResponse handleAddDeviceRightsRequest(
			AddDeviceRightsRequest request) {
		Nonce nonce=null;
		try {
			nonce = request.getNonce();
			UriValue contentId = request.getContentId();
			RoapIdentifier deviceId = request.getDeviceId();
			Rights rights = request.getRights();
			Vector v = new Vector();
			v.add(contentId);
			boolean success = addRights(deviceId, contentId, rights);
			return new AddDeviceRightsResponse(nonce,success);
		} catch (RuntimeException e) {
			e.printStackTrace();
			return new AddDeviceRightsResponse(nonce,false);
		}

	}
	
	/*
	 * implementing  OMADRMServer.handleInitialRoRequest
	 */

	public synchronized RoapTriggerAbstract handleInitialRoRequest(InitialRoRequest request) {
		try {
			DeviceContext ctx = getContext(request.getDeviceId());
			RoapTriggerAbstract theTrigger;
			if (ctx==null) { 
				log("returning null to initial ro request","");
				theTrigger = makeRegTrigger(request);
				if (!addRegTrigger((RegistrationRequestTrigger) theTrigger)) theTrigger = null;
			}
			else{
				theTrigger = makeRoTrigger(request);
				if (theTrigger==null || !addRoTrigger((RoAcquisitionTrigger) theTrigger))
					return null;
			};
			return theTrigger;
		} catch (RuntimeException e) {
			e.printStackTrace();
			return null;
		}

	}

	/*
	 * roap 4-pass registration protocol
	 */
	
	/* 
	 * The updateContext call below does all validation, and updates the device context
	 * and protocol context including preparing the response, if needed. The call is delegated
	 * to RegDatabase
	 */
	/*
	 * implementing  OMADRMServer.handleDeviceHelloRequest
	 */

	public synchronized RiHelloResponse handleDeviceHelloRequest(DeviceHelloRequest request) {
		try {
			Nonce nonce = request.getTriggerNonce();
			if (nonce!=null && !removeRegTrigger(nonce)) // something wrong
				return new FailureRiHelloResponse(new AbortStatus());
			RoapIdentifier deviceId = (RoapIdentifier) request.getDeviceIds().getData().firstElement();
			log("to update context for",deviceId.toString());
			SessionId sessionId = updateContext(deviceId,request);	// does all validation, updates the device context if needed
			log("updated context for",deviceId.toString());
			if (sessionId==null) return new FailureRiHelloResponse(new AbortStatus());
			RiHelloProtocolContext rhCtx = getHelloCtx(sessionId);
			return rhCtx.getRHello();
		} catch (RuntimeException e) {
			e.printStackTrace();
			return new FailureRiHelloResponse(new AbortStatus());
		}
	
	}
	/* 
	 * The updateContext call below does all validation, 
	 * and creates/updates the device context
	 * and protocol context, if needed. The call is delegated
	 * to RegDatabase
	 */

	/*
	 * implementing  OMADRMServer.handleRegistrationRequest
	 */

	public synchronized RegistrationResponse handleRegistrationRequest(
			RegistrationRequest request) {
		try {
			SessionId sessionId = request.getSessionId();
			RiHelloProtocolContext helloContext = getHelloCtx(sessionId);
			if (helloContext==null) return new FailureRegistrationResponse(new AccessDeniedStatus());
			log("have hello context for request",null);
			DeviceHelloRequest dHello = helloContext.getDHello();
			RoapIdentifier deviceId = (RoapIdentifier) dHello.getDeviceIds().getData().firstElement();
			RiContext myContext = getRiContext();
			Base64StringVector resps = getRiContext().getOcspResponses();
			SuccessRegistrationResponse response = new SuccessRegistrationResponse(
					new SuccessStatus(),
					sessionId,
					myContext.getUrl(),
					myContext.getCertChain(),
					resps,
					new RegistrationResponseExtensions(myContext.getWhiteList()),
					null
					);
			String dataToSign = 
					request.asDomDocument().encode()+response.asDomDocument().encode();
			Base64String signature = myContext.getPrivateKey().sign(dataToSign);
			response.setSignature(signature);			
			log("to update context for",deviceId.toString());
			Status status = updateContext(deviceId,request);	// does all validation and updates/creates the device context if needed
			log("updated context for",deviceId.toString());
			if (!status.success()) return new FailureRegistrationResponse((FailureStatus) status, sessionId);
			return response;
		} catch (RuntimeException e) {
			e.printStackTrace();
			return new FailureRegistrationResponse(new AbortStatus());
		}
	}

	/*
	 * Roap 2-pass rights acquisition protocol
	 */
	
	/*
	 * implementing  OMADRMServer.handleRoRequest
	 */

	
	public synchronized RoResponse handleRoRequest(RoRequest request) {
		try {
			Nonce nonce = request.getTriggerNonce();
			if (nonce!=null && !removeRoTrigger(nonce)) // something wrong
				return new FailureRoResponse(new AbortStatus());
			RoapIdentifier devId = (RoapIdentifier) request.getDeviceId();
			DeviceContext devCtx = getContext(devId);
			IPublicKey devKey = getDeviceKey(devCtx,request.getCertificateChain());
			if (devKey==null) return new FailureRoResponse(new NotRegisteredStatus());
			Base64String sig = request.getSignature();
			request.setSignature(null);
			if (!devKey.verify(sig,request.asDomDocument().encode()))
				return new FailureRoResponse(new SignatureErrorStatus());
			RoInfos infos = request.getRoInfos();
			Vector v = new Vector();
			for(Iterator i=infos.iterator();i.hasNext();) {
				RoInfo info = (RoInfo) i.next();
				Pair cidRoId = (Pair) getContentIdRights(info.getRoId());
				UriValue uri = (UriValue) cidRoId.getFst();
//				IdValue ri = (IdValue) cidRoId.getSnd();
				ProtectedRo pr = makeProtectedRo(devId,uri,info.getRoId());
				v.add(pr/*makeProtectedRo(devId,(UriValue) cidRoId.getFst(),(IdValue)cidRoId.getSnd())*/);
			};
			if (v.contains(null)) return new FailureRoResponse(new AccessDeniedStatus());
			ProtectedRos ros = new ProtectedRos(v);
			TwoPassRoResponse temp = new TwoPassRoResponse(
										new SuccessStatus(),
										devId,
										getRiContext().getId(),
										ros,
										getRiContext().getCertChain(),
										getRiContext().getOcspResponses(),
										null,null,
										request.getNonce());
			String toSign = temp.asDomDocument().encode();
			Base64String mySig = getRiContext().getPrivateKey().sign(toSign);
			temp.setSignature(mySig);
			return temp;
		} catch (Exception e) {
			e.printStackTrace();
			return new FailureRoResponse(new AbortStatus());
		}
	}

	/*
	 * helpers
	 */
	
	public IPublicKey verifyChain(CertificateChain chain) {
		return certer.verifyChain(chain);
	}
	

	public Base64String hash(String data) {
		return hasher.hash(data);
	}

	public KeyIdentifier makeKeyIdentifier(IPublicKey key) {
		return hasher.makeKeyIdentifier(key);
	}

	public Nonce createNonce() {
		return noncer.createNonce();
	}




	



	public SessionId createSessionId(SessionId oldId) {
		return sessioner.createSessionId(oldId);
	}

	/*
	 * protocol tracking
	 */
	

	public RiHelloProtocolContext getHelloCtx(SessionId id) {
		return tracker.getHelloCtx(id);
	}


	public RegistrationRequestTrigger getRegTrigger(Nonce nonce) {
		return tracker.getRegTrigger(nonce);
	}


	public RoAcquisitionTrigger getRoTrigger(Nonce nonce) {
		return tracker.getRoTrigger(nonce);
	}


	public boolean addHelloCtx(RiHelloProtocolContext ctx) {
		return tracker.addHelloCtx(ctx);
	}


	public boolean addRegTrigger(RegistrationRequestTrigger trigger) {
		return tracker.addRegTrigger(trigger);
	}


	public boolean addRoTrigger(RoAcquisitionTrigger trigger) {
		return tracker.addRoTrigger(trigger);
	}


	public boolean removeHelloCtx(SessionId id) {
		return tracker.removeHelloCtx(id);
	}


	public boolean removeRegTrigger(Nonce nonce) {
		return tracker.removeRegTrigger(nonce);
	}

	public boolean removeRoTrigger(Nonce nonce) {
		return tracker.removeRoTrigger(nonce);
	}

	/*
	 * creating triggers
	 */
	

	public RegistrationRequestTrigger makeRegTrigger(InitialRoRequest request) {
		return triggerer.makeRegTrigger(request);
	}

	public RoAcquisitionTrigger makeRoTrigger(InitialRoRequest request) {
		return triggerer.makeRoTrigger(request);
	}

	/*
	 * registration database operations
	 */
	

	public boolean addContext(DeviceContext ctx) {
		log("adding context",ctx.getId().toString());
		return regDb.addContext(ctx);
	}


	public DeviceContext getContext(RoapIdentifier id) {
		log("getting context",id.toString());
		return regDb.getContext(id);
	}


	public RiContext getRiContext() {
		return regDb.getRiContext();
	}


	public Status updateContext(RoapIdentifier id, RegistrationRequest request) {
		return regDb.updateContext(id, request);
	}
	

	public IPublicKey getDeviceKey(DeviceContext ctx, CertificateChain chain) {
		log("getting device key",ctx.getId().toString());
		return regDb.getDeviceKey(ctx, chain);
	}

	
	public SessionId updateContext(RoapIdentifier id, DeviceHelloRequest request) {
		return regDb.updateContext(id, request);
	}
	
	/*
	 * rights database operations
	 */


	public boolean addContentKey(UriValue contentId, Base64String encKey) {
		log("adding content key for",contentId.toString());
		return roDb.addContentKey(contentId, encKey);
	}

	public Base64String getContentKey(UriValue contentId) {
		log("getting content key for",contentId.toString());
		return roDb.getContentKey(contentId);
	}

	public boolean addRoId(RoapIdentifier deviceId, UriValue contentId, IdValue roId) {
		log("adding roid for",deviceId.toString());
		return roDb.addRoId(deviceId, contentId, roId);
	}
	
	public IdValue getRoId(RoapIdentifier deviceId, UriValue contentId) {
		log("getting roid for",deviceId.toString());
		return roDb.getRoId(deviceId,contentId);
	}
	public IdValue createRoId(RoapIdentifier deviceId, UriVector contentIds) {
		return righter.createRoId(deviceId, contentIds);
	}
	public boolean addRights(RoapIdentifier deviceId, UriValue contentId, Rights rights) {
		log("adding rights for",deviceId.toString());
		return roDb.addRights(deviceId, contentId, rights);
	}
	
	public boolean addRights(RoapIdentifier deviceId, UriValue contentId, IdValue roId, Rights rights) {
		return roDb.addRights(deviceId, contentId, roId, rights);
	}

	public Pair getContentIdRights(IdValue roId) {
		log("getting content id and rights for",roId.toString());
		return roDb.getContentIdRights(roId);
	}
	public Rights getRights(RoapIdentifier deviceId, UriValue contentId) {
		log("getting rights for",deviceId.toString());
		return roDb.getRights(deviceId, contentId);
	}
	public ProtectedRo makeProtectedRo(RoapIdentifier devId,UriValue contentId,IdValue roId) {
		return roDb.makeProtectedRo(devId, contentId, roId);
	}
	
	/**
	 * logging
	 */
	
	public static void log(String header, String message) {
		Logger.log(header,message);
	}


}
