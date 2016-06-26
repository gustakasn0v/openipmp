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

import com.mutable.drmPlugin.roap.messages.*;
import com.mutable.drmPlugin.roap.messages.status.Status;
import com.mutable.drmPlugin.roap.misc.CertificateChain;
import com.mutable.drmPlugin.roap.misc.RoapIdentifier;
import com.mutable.drmPlugin.roap.misc.SessionId;
import com.mutable.drmPlugin.crypto.*;

/**
 * The DeviceContext and RiContext book-keeping services that the server relies on.
 * 
 * @see DeviceContext RiContext
 * 
 * 
 *
 */
public interface IRegistrationDatabase {
	public DeviceContext getContext(RoapIdentifier id);
	public boolean addContext(DeviceContext ctx);
	public SessionId updateContext(RoapIdentifier id, DeviceHelloRequest request);
	public Status updateContext(RoapIdentifier id, RegistrationRequest request);
	public RiContext getRiContext();
	public IPublicKey getDeviceKey(DeviceContext ctx, CertificateChain chain);

}
