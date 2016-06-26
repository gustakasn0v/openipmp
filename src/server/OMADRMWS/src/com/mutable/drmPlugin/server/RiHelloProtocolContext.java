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

/**
 * A protocol-tracking helper class, providing a book-keeping service for the 4-pass Roap Registration Protocol.
 * 
 * @see com.mutable.drmPlugin.server.helpers.ProtocolTracker
 * 
 * 
 *
 */

public class RiHelloProtocolContext {

protected DeviceContext dCtx;
protected DeviceHelloRequest dHello;
protected SuccessRiHelloResponse rHello;

public RiHelloProtocolContext(DeviceContext ctx, DeviceHelloRequest hello, SuccessRiHelloResponse oYeah) {
	super();
	if (ctx==null || hello==null || oYeah==null)
		throw new IllegalArgumentException();
	dCtx = ctx;
	dHello = hello;
	rHello = oYeah;
}

public DeviceContext getDCtx() {
	return dCtx;
}

public DeviceHelloRequest getDHello() {
	return dHello;
}

public SuccessRiHelloResponse getRHello() {
	return rHello;
}

}
