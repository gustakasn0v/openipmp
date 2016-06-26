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

package com.mutable.osms.server.ws;

public class OsmsWebServiceProxy implements com.mutable.osms.server.ws.OsmsWebService {
  private String _endpoint = null;
  private com.mutable.osms.server.ws.OsmsWebService osmsWebService = null;
  
  public OsmsWebServiceProxy() {
    _initOsmsWebServiceProxy();
  }
  
  private void _initOsmsWebServiceProxy() {
    try {
      osmsWebService = (new com.mutable.osms.server.ws.OsmsWebServiceServiceLocator()).getOsmsWebService();
      if (osmsWebService != null) {
        if (_endpoint != null)
          ((javax.xml.rpc.Stub)osmsWebService)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
        else
          _endpoint = (String)((javax.xml.rpc.Stub)osmsWebService)._getProperty("javax.xml.rpc.service.endpoint.address");
      }
      
    }
    catch (javax.xml.rpc.ServiceException serviceException) {}
  }
  
  public String getEndpoint() {
    return _endpoint;
  }
  
  public void setEndpoint(String endpoint) {
    _endpoint = endpoint;
    if (osmsWebService != null)
      ((javax.xml.rpc.Stub)osmsWebService)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
    
  }
  
  public com.mutable.osms.server.ws.OsmsWebService getOsmsWebService() {
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService;
  }
  
  public com.mutable.osms.server.ws.message.OsmsQueryResponse query(com.mutable.osms.server.ws.message.OsmsQueryRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsQueryFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.query(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsLicenseResponse license(com.mutable.osms.server.ws.message.OsmsLicenseRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsLicenseFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.license(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsUserLoginResponse userLogin(com.mutable.osms.server.ws.message.OsmsUserLoginRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.userLogin(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsUserLogoutResponse userLogout(com.mutable.osms.server.ws.message.OsmsUserLogoutRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsUserLogoutFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.userLogout(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsCreateUserResponse createUser(com.mutable.osms.server.ws.message.OsmsCreateUserRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsCreateUserFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.createUser(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse getContentKey(com.mutable.osms.server.ws.message.OsmsGetContentKeyRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsGetContentKeyFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.getContentKey(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse registerContentAssignIdentifier(com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.registerContentAssignIdentifier(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse registerContentExistingIdentifier(com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.registerContentExistingIdentifier(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse registerDigitalItemInstance(com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.registerDigitalItemInstance(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsRegisterUserResponse registerUser(com.mutable.osms.server.ws.message.OsmsRegisterUserRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsRegisterUserFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.registerUser(msg);
  }
  
  public com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse rightsAuthorization(com.mutable.osms.server.ws.message.OsmsRightsAuthorizationRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRightsAuthorizationFault{
    if (osmsWebService == null)
      _initOsmsWebServiceProxy();
    return osmsWebService.rightsAuthorization(msg);
  }
  
  public void setSOAPHeader(String userName, String password) {
      ((org.apache.axis.client.Stub)osmsWebService).setHeader("http://ws.server.osms.mutable.com", "userName", userName);
      ((org.apache.axis.client.Stub)osmsWebService).setHeader("http://ws.server.osms.mutable.com", "password", password);
  }
  
}