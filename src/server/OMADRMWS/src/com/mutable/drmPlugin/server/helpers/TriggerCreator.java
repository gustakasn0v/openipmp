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

import com.mutable.drmPlugin.roap.messages.*;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.Version;
import com.mutable.drmPlugin.roap.ro.RoIdContentId;
import com.mutable.drmPlugin.roap.ro.RoIdContentIds;
import com.mutable.drmPlugin.server.ITriggerCreator;
import com.mutable.drmPlugin.server.RiContext;
import com.mutable.drmPlugin.server.ServerAbstract;
import com.mutable.drmPlugin.server.nonRoapMessages.InitialRoRequest;
import com.mutable.drmPlugin.tools.*;
import java.util.*;

public class TriggerCreator implements ITriggerCreator {
	
	protected ServerAbstract server;
	static IdValue stupidId = new IdValue("aa");

	public RegistrationRequestTrigger makeRegTrigger(InitialRoRequest request) {
		Nonce nonce = server.createNonce();
		RiContext riCtx = server.getRiContext();
		RoapIdentifier riId = riCtx.getId();
		UriValue riUrl = riCtx.getUrl();
		Version ver = riCtx.getVersion();
		
		BaseRegRequestTrigger baseTrigger = 
			new BaseRegRequestTrigger(riId,nonce,riUrl,stupidId);
		return new RegistrationRequestTrigger(baseTrigger,null,null,ver,false);
	}

	public RoAcquisitionTrigger makeRoTrigger(InitialRoRequest request) {
		RiContext riCtx = server.getRiContext();
		RoapIdentifier riId = riCtx.getId();
		UriValue riUrl = riCtx.getUrl();
		Nonce nonce = server.createNonce();
		IdValue roId = server.getRoId(request.getDeviceId(),
								(UriValue)request.getContents().getData().firstElement());
		if (roId==null) return null;
		Vector v = new Vector();
		v.add(new RoIdContentId(roId,request.getContents()));
		BaseRoAcquTrigger btrig = new BaseRoAcquTrigger(riId,nonce,riUrl,stupidId,new RoIdContentIds(v));
		return new RoAcquisitionTrigger(btrig,null,null,riCtx.getVersion(),false);
	}

	public TriggerCreator(ServerAbstract server) {
		super();
		// TODO Auto-generated constructor stub
		this.server = server;
	}

}
