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
/**
 * OMADRMWSBindingImpl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.omadrm.ws;

import com.mutable.omadrm.ws.roap.*;
import com.mutable.drmPlugin.server.TestServer;

public class OMADRMWSBindingImpl implements com.mutable.omadrm.ws.OMADRMWS{
	
    public WSAddContentKeyResponse addContentKey(WSAddContentKeyRequest add_key_request) /*throws java.rmi.RemoteException */ {
 //    return new WSAddContentKeyResponse("abc");
        return new WSAddContentKeyResponse(TestServer.handleAddContentKeyRequest(add_key_request.getMsg()));
    }

    public WSAddDeviceRightsResponse addDeviceRights(WSAddDeviceRightsRequest add_rights_request) throws java.rmi.RemoteException {
        return new WSAddDeviceRightsResponse(TestServer.handleAddDeviceRightsRequest(add_rights_request.getMsg()));
    }

    public com.mutable.omadrm.ws.roap.WSRIHello hello(com.mutable.omadrm.ws.roap.WSDeviceHello message) throws java.rmi.RemoteException {
        return new WSRIHello(TestServer.handleDeviceHelloRequest(message.getMsg()));
    }

    public com.mutable.omadrm.ws.roap.WSRegistrationResponse registration(com.mutable.omadrm.ws.roap.WSRegistrationRequest message) throws java.rmi.RemoteException {
        return new WSRegistrationResponse(TestServer.handleRegistrationRequest(message.getMsg()));
    }

    public WSROAcquisitionTrigger initialRO(WSInitialRORequest message) throws java.rmi.RemoteException {
        return new WSROAcquisitionTrigger(TestServer.handleInitialRoRequest(message.getMsg()));
    }

    public com.mutable.omadrm.ws.roap.WSROResponse roAcquisition(com.mutable.omadrm.ws.roap.WSRORequest message) throws java.rmi.RemoteException {
        return new WSROResponse(TestServer.handleRoRequest(message.getMsg()));
   }

}
