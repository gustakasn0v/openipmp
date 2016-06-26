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

import com.mutable.drmPlugin.roap.messages.RegistrationRequestTrigger;
import com.mutable.drmPlugin.roap.messages.RoAcquisitionTrigger;
import com.mutable.drmPlugin.roap.misc.Nonce;
import com.mutable.drmPlugin.roap.misc.SessionId;

/** 
 * The protocol tracking services that the server relies on, linking nonces and
 * sessionIds to Roap-Trigger messages and RiHelloProtocolContexts.
 * 
 * @see RegistrationRequestTrigger 
 * @see RoAcquisitionTrigger 
 * @see RiHelloProtocolContext
 * 
 * 
 * 
 */
public interface IProtocolTracker {
	
	public RegistrationRequestTrigger getRegTrigger(Nonce nonce);
	public RoAcquisitionTrigger getRoTrigger(Nonce nonce);
	public RiHelloProtocolContext getHelloCtx(SessionId id);
	public boolean addRegTrigger(RegistrationRequestTrigger trigger);
	public boolean addRoTrigger(RoAcquisitionTrigger trigger);
	public boolean addHelloCtx(RiHelloProtocolContext ctx);
	public boolean removeRegTrigger(Nonce nonce);
	public boolean removeRoTrigger(Nonce nonce);
	public boolean removeHelloCtx(SessionId id);

}
