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

import java.util.Vector;

import com.mutable.drmPlugin.crypto.IPublicKey;
import com.mutable.drmPlugin.roap.imports.ds.CanonicalizationMethod;
import com.mutable.drmPlugin.roap.imports.ds.DigestMethod;
import com.mutable.drmPlugin.roap.imports.ds.DigestValue;
import com.mutable.drmPlugin.roap.imports.ds.References;
import com.mutable.drmPlugin.roap.imports.ds.Reference;
import com.mutable.drmPlugin.roap.imports.ds.Signature;
import com.mutable.drmPlugin.roap.imports.ds.SignatureMethod;
import com.mutable.drmPlugin.roap.imports.ds.SignatureValue;
import com.mutable.drmPlugin.roap.imports.ds.SignedInfo;
import com.mutable.drmPlugin.roap.imports.xenc.CValueCipherData;
import com.mutable.drmPlugin.roap.imports.xenc.CipherData;
import com.mutable.drmPlugin.roap.imports.xenc.EncryptedKey;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.roap.ro.ProtectedRo;
import com.mutable.drmPlugin.roap.ro.RoPayload;
import com.mutable.drmPlugin.roap.ro.oex.Rights;
import com.mutable.drmPlugin.server.IRoDatabase;
import com.mutable.drmPlugin.server.ServerAbstract;
import com.mutable.drmPlugin.server.maps.ContentIdHash2Key;
import com.mutable.drmPlugin.server.maps.DeviceId2ContentId2RoId;
import com.mutable.drmPlugin.server.maps.RoId2ContentIdRights;
import com.mutable.drmPlugin.tools.Base64String;
import com.mutable.drmPlugin.tools.IdValue;
import com.mutable.drmPlugin.tools.Pair;
import com.mutable.drmPlugin.tools.UriValue;
import com.mutable.drmPlugin.tools.UriVector;

/**
 * implementation of IRoDatabase maintaining three maps, also providing
 * some other services relying on the information contained in its maps
 * 
 * 
 *
 */
public class RoDatabase implements IRoDatabase {
	
	protected ServerAbstract server;
	
	protected ContentIdHash2Key ci2k;
	protected DeviceId2ContentId2RoId di2ci2ri;
	protected RoId2ContentIdRights ri2cir;

	/** 
	 * constructor with fresh maps
	 * @param server
	 * 
	 */
	public RoDatabase(ServerAbstract server) {
		super();
		this.server=server;
		ci2k = new ContentIdHash2Key();
		di2ci2ri = new DeviceId2ContentId2RoId();
		ri2cir = new RoId2ContentIdRights();
	}
	
	/**
	 * constructor with given maps
	 * @param server
	 * @param ci2k
	 * @param di2ci2ri
	 * @param ri2cir
	 */
	
	public RoDatabase(ServerAbstract server,
			ContentIdHash2Key ci2k,
			DeviceId2ContentId2RoId di2ci2ri,
			RoId2ContentIdRights ri2cir) {
		super();
		this.server=server;
		this.ci2k = ci2k;
		this.di2ci2ri = di2ci2ri;
		this.ri2cir = ri2cir;
	}
	
	/* accessing the maps */

	/*
	 * the final call below is separated and wired via server to provide a hook
	 * for subclasses of  <code>ServerAbstract</code>, used by <code>Server</code>
	 * 
	 * @see ServerAbstract 
	 * @see Server
	 * 
	 */
	public boolean addRights(RoapIdentifier deviceId, UriValue contentId,
								Rights rights) {
		Vector v = new Vector();
		v.add(contentId);
		IdValue roId = createRoId(deviceId, new UriVector(v));
		return server.addRights(deviceId,contentId,roId,rights);
	}
	
	public boolean addRights(RoapIdentifier deviceId, UriValue contentId,
								IdValue roId, Rights rights) {	
		try {
			IdValue oldRoid = (IdValue) di2ci2ri.get(deviceId,contentId);
			if (!di2ci2ri.put(deviceId,contentId,roId) || !ri2cir.put(roId, new Pair(contentId,rights)))
				return false;
			if (oldRoid!=null) ri2cir.remove(oldRoid);
		} catch(Exception e) { return false; };
		return true;
	}

	public Rights getRights(RoapIdentifier deviceId, UriValue contentId) {
		try {
			IdValue roId = (IdValue) di2ci2ri.get(deviceId,contentId);
			return (Rights) getContentIdRights(roId).getSnd();
		} catch (Exception e) { return null; }
	}



	public boolean addContentKey(UriValue contentId, Base64String encKey) {
		try {
			ci2k.put(server.hash(contentId.toString()),encKey);
		} catch(Exception e) { return false; };
		return true;
	}

	public Base64String getContentKey(UriValue contentId) {
		return (Base64String) ci2k.get(server.hash(contentId.toString()));
	}
	
	public boolean addRoId(RoapIdentifier deviceId, UriValue contentId, IdValue roId) {
		try {
			di2ci2ri.put(deviceId,contentId,roId);
		} catch (Exception e) {return false;};
		return true;
	}
	
	public IdValue getRoId(RoapIdentifier deviceId, UriValue contentId) {
		return (IdValue) di2ci2ri.get(deviceId,contentId);
	}

	public Pair getContentIdRights(IdValue roId) {
		return (Pair) ri2cir.get(roId);
	}


	/* creating and checking roids */
	
	public IdValue createRoId(RoapIdentifier deviceId, UriVector contentIds) {
		return server.createRoId(deviceId, contentIds);
	}

	/* misc further services */
	
	public boolean checkRoId(RoapIdentifier deviceId, IdValue roId) {
		try {
			UriValue contentId = (UriValue) getContentIdRights(roId).getFst();
			IdValue storedRoid = getRoId(deviceId,contentId);
			return roId.equals(storedRoid);
		} catch(Exception e) { return false; }
	}

	
	protected EncryptedKey makeEncryptedKey(RoapIdentifier deviceId,UriValue contentId) {
		try {
			Base64String theKey = (Base64String) ci2k.get(server.hash(contentId.toString()));
			IPublicKey devKey = server.getContext(deviceId).getPublicKey();
			CipherData cipher = new CValueCipherData(devKey.encrypt(theKey).toString());
			return new EncryptedKey(null,null,cipher,null,null,null,null,null,null,null,null);
		} catch (Exception e) { return null; }
	}
	
	protected RoPayload makeRoPayload(RoapIdentifier deviceId,UriValue contentId) {
		try {
			EncryptedKey encKey = makeEncryptedKey(deviceId,contentId);
			Rights rights = getRights(deviceId,contentId);
			RoapIdentifier riId = server.getRiContext().getId();
			UriValue riUrl = server.getRiContext().getUrl();
			IdValue roId = getRoId(deviceId,contentId);
			Version ver = server.getRiContext().getVersion();
			return new RoPayload(riId,rights,null,null,encKey,roId,ver,riUrl);
		} catch (Exception e) {
			return null;
		}
	}
	
	protected Signature dsSign(RoPayload ro) {
		String toSign = ro.asDomDocument().encode();
	log("payloadString",toSign);
		Vector v = new Vector();
		v.add(new Reference(new DigestMethod(),new DigestValue(server.hash(toSign).toString()),null,null,null,null));
		SignedInfo info = new SignedInfo(
				new CanonicalizationMethod(),
				new SignatureMethod(),
				new References(v),
				null);
		Base64String sig = server.getRiContext().getPrivateKey().sign(toSign);
		SignatureValue sigVal = new SignatureValue(sig.toString(),null);
		return new Signature(info,sigVal,null,null,null);		
	}
	
	public ProtectedRo makeProtectedRo(RoapIdentifier deviceId,UriValue contentId,IdValue roId) {
		if (!checkRoId(deviceId,roId)) return null;
		RoPayload ro = makeRoPayload(deviceId,contentId);
		Signature sig = dsSign(ro);
		return new ProtectedRo(ro,sig);
	}
	
	public static void log(String header, String message) {
		Logger.log(header,message);
	}

}
