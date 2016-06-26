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
 * The Original Code is OpenIPMP.
 *
 * The Initial Developer of the Original Code is Mutable, Inc.
 * Portions created by Mutable, Inc. are
 * Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved.
 * 
 *
 */

/**
 * OsmsWebService.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.osms.server.ws;

public interface OsmsWebService extends java.rmi.Remote {
    public com.mutable.osms.server.ws.message.OsmsQueryResponse query(com.mutable.osms.server.ws.message.OsmsQueryRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsQueryFault;
    public com.mutable.osms.server.ws.message.OsmsLicenseResponse license(com.mutable.osms.server.ws.message.OsmsLicenseRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsLicenseFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault;
    public com.mutable.osms.server.ws.message.OsmsUserLoginResponse userLogin(com.mutable.osms.server.ws.message.OsmsUserLoginRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault;
    public com.mutable.osms.server.ws.message.OsmsUserLogoutResponse userLogout(com.mutable.osms.server.ws.message.OsmsUserLogoutRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsUserLogoutFault;
    public com.mutable.osms.server.ws.message.OsmsCreateUserResponse createUser(com.mutable.osms.server.ws.message.OsmsCreateUserRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsCreateUserFault;
    public com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse getContentKey(com.mutable.osms.server.ws.message.OsmsGetContentKeyRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsGetContentKeyFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault;
    public com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse registerContentAssignIdentifier(com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault;
    public com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse registerContentExistingIdentifier(com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierFault;
    public com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse registerDigitalItemInstance(com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceFault;
    public com.mutable.osms.server.ws.message.OsmsRegisterUserResponse registerUser(com.mutable.osms.server.ws.message.OsmsRegisterUserRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsRegisterUserFault;
    public com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse rightsAuthorization(com.mutable.osms.server.ws.message.OsmsRightsAuthorizationRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRightsAuthorizationFault;
}
