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
 * OMADRMWS.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.omadrm.ws;

public interface OMADRMWS extends java.rmi.Remote {
    public com.mutable.omadrm.ws.roap.WSAddContentKeyResponse addContentKey(com.mutable.omadrm.ws.roap.WSAddContentKeyRequest add_key_request) throws java.rmi.RemoteException;
    public com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse addDeviceRights(com.mutable.omadrm.ws.roap.WSAddDeviceRightsRequest add_rights_request) throws java.rmi.RemoteException;
    public com.mutable.omadrm.ws.roap.WSRIHello hello(com.mutable.omadrm.ws.roap.WSDeviceHello message) throws java.rmi.RemoteException;
    public com.mutable.omadrm.ws.roap.WSRegistrationResponse registration(com.mutable.omadrm.ws.roap.WSRegistrationRequest message) throws java.rmi.RemoteException;
    public com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger initialRO(com.mutable.omadrm.ws.roap.WSInitialRORequest message) throws java.rmi.RemoteException;
    public com.mutable.omadrm.ws.roap.WSROResponse roAcquisition(com.mutable.omadrm.ws.roap.WSRORequest message) throws java.rmi.RemoteException;
}
