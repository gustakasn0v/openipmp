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

import java.util.Iterator;

import com.mutable.drmPlugin.crypto.IPublicKey;
import com.mutable.drmPlugin.crypto.PublicKeyImpl;
import com.mutable.drmPlugin.roap.messages.DeviceHelloRequest;
import com.mutable.drmPlugin.roap.messages.RegistrationRequest;
import com.mutable.drmPlugin.roap.messages.SuccessRiHelloResponse;
import com.mutable.drmPlugin.roap.messages.extensions.CertificateCachingExtension;
import com.mutable.drmPlugin.roap.messages.extensions.DeviceHelloExtensions;
import com.mutable.drmPlugin.roap.messages.extensions.FullDeviceDetails;
import com.mutable.drmPlugin.roap.messages.extensions.FullPeerKeyIdentifier;
import com.mutable.drmPlugin.roap.messages.extensions.NoOcspResponse;
import com.mutable.drmPlugin.roap.messages.extensions.RiHelloExtensions;
import com.mutable.drmPlugin.roap.messages.status.AbortStatus;
import com.mutable.drmPlugin.roap.messages.status.AccessDeniedStatus;
import com.mutable.drmPlugin.roap.messages.status.InvalidCertificateChainStatus;
import com.mutable.drmPlugin.roap.messages.status.MalformedRequestStatus;
import com.mutable.drmPlugin.roap.messages.status.SignatureErrorStatus;
import com.mutable.drmPlugin.roap.messages.status.Status;
import com.mutable.drmPlugin.roap.messages.status.SuccessStatus;
import com.mutable.drmPlugin.roap.messages.status.TrustedRootCertificateNotPresentStatus;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.KeyIdentifier;
import com.mutable.drmPlugin.roap.misc.KeyIdentifiers;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.server.DeviceContext;
import com.mutable.drmPlugin.server.IRegistrationDatabase;
import com.mutable.drmPlugin.server.RiContext;
import com.mutable.drmPlugin.server.RiHelloProtocolContext;
import com.mutable.drmPlugin.server.ServerAbstract;
import com.mutable.drmPlugin.server.maps.KeyId2DevCtx;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.Base64StringVector;
import com.mutable.drmPlugin.tools.UriVector;

	/**
	 * Implementation of IRegistrationDatabase relying on a map holding
	 * DeviceContexts. It also holds the RiContext, and provides some 
	 * other services depending on its data.
	 * 
	 * 
	 *
	 */
public class RegDatabase implements IRegistrationDatabase {
	
	protected ServerAbstract server;
	protected KeyId2DevCtx deviceContexts;
	protected RiContext riContext;
	
	

	public DeviceContext getContext(RoapIdentifier id) {
		return (DeviceContext) deviceContexts.get(id);
	}

	public boolean addContext(DeviceContext ctx) {
		try {
			deviceContexts.put(ctx.getId(),ctx);
		} catch (RuntimeException e) {
			e.printStackTrace();
			return false;
		};		
		return true;
	}

	/**
	 * Validating  an incoming DeviceHelloRequest, and creating/updating the
	 * relevant DeviceContext and RiHelloProtocolContext if needed. 
	 * 
	 * @return a fresh SessionId or null, depending on the validation.
	 * 
	 * @see com.mutable.drmPlugin.server.DeviceContext com.mutable.drmPlugin.server.RiHelloProtocolContext
	 * 
	 */
	public SessionId updateContext(RoapIdentifier id, DeviceHelloRequest request) {
		DeviceContext oldCtx = getContext(id);
		RiContext myContext = getRiContext();
		Nonce myNonce = server.createNonce();	
		UriVector hisAlgos = request.getSupportedAlgorithms();
		UriVector algorithms = (hisAlgos==null) 
								? myContext.getAlgorithms() 
								: myContext.getAlgorithms().intersection(hisAlgos);
		DeviceHelloExtensions dexts = request.getExtensions();
		CertificateCachingExtension devCaching = 
			dexts==null ? null : (CertificateCachingExtension)dexts.getData().firstElement();			
		Version version = request.getVersion();
		if (!version.equals(myContext.getVersion())) return null;
		IPublicKey devPublicKey = (oldCtx==null) ? null : oldCtx.getPublicKey();
		CertificateChain chain = (oldCtx==null) ? null : oldCtx.getCertChain();
		DeviceContext newCtx = new DeviceContext(id,devPublicKey,null,chain,null,algorithms,version,devCaching,null);
		SessionId sessionId = server.createSessionId(null);
		RiHelloExtensions exts = new RiHelloExtensions(
				devPublicKey!=null ? new FullPeerKeyIdentifier(true,id.getIdentifier()) : null,
				(devPublicKey==null && devCaching!=null) ? myContext.getCaching() : null,
				myContext.getDetails());
		SuccessRiHelloResponse response =
			new SuccessRiHelloResponse(
							new SuccessStatus(),
							sessionId,
							version,
							myContext.getId(),
							algorithms,
							myNonce,
							myContext.getTrusted(),
							myContext.getServerInfo(),
							exts);					
		if (!server.addHelloCtx(new RiHelloProtocolContext(newCtx,request,response)) 				) 
			return null;
		return sessionId;
	}

	/**
	 * Validating  an incoming RegistrationRequest, and creating/updating the
	 * relevant DeviceContext and RiHelloProtocolContext if needed. 
	 * 
	 * @return appropriate Status for the response message
	 * 
	 * @see com.mutable.drmPlugin.server.DeviceContext com.mutable.drmPlugin.server.RiHelloProtocolContext 
	 * 
	 */

	public Status updateContext(RoapIdentifier id, RegistrationRequest request) {
		RiHelloProtocolContext hCtx = server.getHelloCtx(request.getSessionId());
		if (hCtx==null || !request.getSessionId().equals(hCtx.getRHello().getSessionId()))
			return new AccessDeniedStatus();
		Nonce nonce = request.getNonce();
		CertificateChain devChain = request.getCertificateChain();
		DeviceContext oldCtx = hCtx.getDCtx();
		IPublicKey devKey = getDeviceKey(oldCtx,devChain);
		if (devKey==null) return new InvalidCertificateChainStatus();
		devChain = oldCtx.getCertChain();
		Base64String sig = request.getSignature();
		request.setSignature(null);
		String dHelloString = hCtx.getDHello().asDomDocument().encode();
		String rHelloString = hCtx.getRHello().asDomDocument().encode();
		String reqString = request.asDomDocument().encode();
		String signed = dHelloString+rHelloString+reqString;
		if (!devKey.verify(sig,signed)) return new SignatureErrorStatus();
		request.setSignature(sig);
		KeyIdentifiers devTrusted = request.getTrustedAuthorities();
		if (devTrusted!=null && !devTrusted.isEmpty()) {
			Base64String caCert = getRiContext().getRiCaCert();
			KeyIdentifier caId = PublicKeyImpl.instanceFromEncodedCert(caCert).getIdentifier();
			if (!devTrusted.contains(caId)) return new TrustedRootCertificateNotPresentStatus();
		};
		UriVector devAlgos = oldCtx.getAlgorithms();
		FullPeerKeyIdentifier peer = null;
		NoOcspResponse no = null;
		FullDeviceDetails dd = null;
		if (request.getExtensions()!=null)
			for(Iterator i=request.getExtensions().iterator();i.hasNext();) {
				Object e = i.next();
				if (FullPeerKeyIdentifier.class.isInstance(e)) peer=(FullPeerKeyIdentifier)e;
				if (NoOcspResponse.class.isInstance(e)) no=(NoOcspResponse)e;
				if (FullDeviceDetails.class.isInstance(e)) dd=(FullDeviceDetails)e;
			};
		if (dd==null) return new MalformedRequestStatus();
	//	CertificateChain riChain = (peer==null) ? null : getRiContext().getCertChain();
	//	Base64StringVector resps = (no==null) ? getRiContext().getOcspResponses() : null;
		DeviceContext devCtx = new DeviceContext(id,devKey,null,devChain,devTrusted,devAlgos,getRiContext().getVersion(),oldCtx.getCaching(),dd);
		if (!server.addContext(devCtx) ||!server.removeHelloCtx(request.getSessionId())) return new AbortStatus();
		return new SuccessStatus();
	}


	public RiContext getRiContext() {
		return riContext;
	}

	/**
	 * constructor with given maps
	 * 
	 * @param server
	 * @param deviceContexts
	 * @param riContext
	 * 
	 */
	public RegDatabase(ServerAbstract server, KeyId2DevCtx deviceContexts, RiContext riContext) {
		super();
		this.server = server;
		this.deviceContexts = deviceContexts;
		this.riContext = riContext;
	}
	
	/** 
	 * fetches the device key, and updates the context with the new chain if needed 
	 * @param oldCtx
	 * @param chain
	 * 
	 * @return the currently valid key, if it can be inferred
	 * 
	 * 
	 */
	
	public IPublicKey getDeviceKey(DeviceContext oldCtx, CertificateChain chain) {
		IPublicKey devKey = oldCtx.getPublicKey();
		CertificateChain devChain = chain;
		if (devChain==null) {
			if (devKey==null) return null;
			else  devChain = oldCtx.getCertChain(); 
		}
		else devKey = server.verifyChain(devChain);
		if (devKey!=null) oldCtx.setCertChain(devChain);
		return devKey;
	}

}
