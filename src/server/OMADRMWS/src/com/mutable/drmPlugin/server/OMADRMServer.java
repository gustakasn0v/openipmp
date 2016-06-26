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
import com.mutable.drmPlugin.server.nonRoapMessages.AddContentKeyRequest;
import com.mutable.drmPlugin.server.nonRoapMessages.AddContentKeyResponse;
import com.mutable.drmPlugin.server.nonRoapMessages.AddDeviceRightsRequest;
import com.mutable.drmPlugin.server.nonRoapMessages.AddDeviceRightsResponse;
import com.mutable.drmPlugin.server.nonRoapMessages.InitialRoRequest;

/** 
 * OMADRM Server interface, with three additional (non-Roap) messages.
 *  
 * 
 */

public interface OMADRMServer {
	
	/**
	 * The encoder message providing the server with an encryption key for a content.
	 */
	public AddContentKeyResponse handleAddContentKeyRequest(AddContentKeyRequest request);
	/**
	 * The encoder message providing the server with rights for a device and content.
	 */
	public AddDeviceRightsResponse handleAddDeviceRightsRequest(AddDeviceRightsRequest request);
	/**
	 * The device message requesting a RoAcquisitionTrigger containing a RoId for a given content.
	 */
	public RoapTriggerAbstract handleInitialRoRequest(InitialRoRequest request);
	/**
	 * The first half of the 4-pass Roap Registration Protocol.
	 */
	public RiHelloResponse handleDeviceHelloRequest(DeviceHelloRequest request);
	/**
	 * The second half of the 4-pass Roap Registration Protocol.
	 */
	public RegistrationResponse handleRegistrationRequest(RegistrationRequest request);
	/**
	 * The 2-pass Roap Rights Acquisition Protocol.
	 */
	public RoResponse handleRoRequest(RoRequest request);
	

}
