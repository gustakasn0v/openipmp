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

import com.mutable.drmPlugin.roap.messages.RegistrationRequestTrigger;
import com.mutable.drmPlugin.roap.messages.RoAcquisitionTrigger;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.server.IProtocolTracker;
import com.mutable.drmPlugin.server.RiHelloProtocolContext;
import com.mutable.drmPlugin.server.maps.Nonce2RegTrigger;
import com.mutable.drmPlugin.server.maps.Nonce2RoAcquisitionTrigger;
import com.mutable.drmPlugin.server.maps.SessionId2RiHelloProtocolContext;

public class ProtocolTracker implements IProtocolTracker {
	protected Nonce2RegTrigger regTriggerMap = new Nonce2RegTrigger();
	protected Nonce2RoAcquisitionTrigger roTriggerMap = new Nonce2RoAcquisitionTrigger();
	protected SessionId2RiHelloProtocolContext contextMap = new SessionId2RiHelloProtocolContext();

	public RegistrationRequestTrigger getRegTrigger(Nonce nonce) {
		if (nonce==null) throw new Error("null nonce");
		if (!regTriggerMap.containsKey(nonce)) return null;
		return (RegistrationRequestTrigger) regTriggerMap.get(nonce);
	}

	public RoAcquisitionTrigger getRoTrigger(Nonce nonce) {
		if (nonce==null) throw new Error("null nonce");
		if (!roTriggerMap.containsKey(nonce)) return null;
		return (RoAcquisitionTrigger) roTriggerMap.get(nonce);

	}

	public RiHelloProtocolContext getHelloCtx(SessionId id) {
		if (id==null) throw new Error("null id");
		if (!contextMap.containsKey(id)) return null;
		return (RiHelloProtocolContext) contextMap.get(id);

	}

	public boolean addRegTrigger(RegistrationRequestTrigger trigger) {
		if (trigger==null) return false;
		Nonce nonce = trigger.getNonce();
		if (nonce==null || regTriggerMap.containsKey(nonce)) return false;
		regTriggerMap.put(nonce,trigger);
		return true;
	}

	public boolean addRoTrigger(RoAcquisitionTrigger trigger) {
		if (trigger==null) return false;
		Nonce nonce = trigger.getNonce();
		if (nonce==null || roTriggerMap.containsKey(nonce)) return false;
		roTriggerMap.put(nonce,trigger);
		return true;
	}

	public boolean addHelloCtx(RiHelloProtocolContext ctx) {
		if (ctx==null) return false;
		SessionId id = ctx.getRHello().getSessionId();
		if (id==null || contextMap.containsKey(id)) return false;
		contextMap.put(id, ctx);
		return true;
	}

	public boolean removeRegTrigger(Nonce nonce) {
		return (nonce!=null) && regTriggerMap.remove(nonce);		
	}

	public boolean removeRoTrigger(Nonce nonce) {
		return (nonce!=null) && roTriggerMap.remove(nonce);		
	}

	public boolean removeHelloCtx(SessionId id) {
		return (id!=null) && contextMap.remove(id);		
	}

}
