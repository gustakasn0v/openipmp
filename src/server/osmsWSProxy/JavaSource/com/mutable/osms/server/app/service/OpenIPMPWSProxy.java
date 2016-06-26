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

package com.mutable.osms.server.app.service;

public class OpenIPMPWSProxy implements com.mutable.osms.server.app.service.OpenIPMPWS {
  private String _endpoint = null;
  private com.mutable.osms.server.app.service.OpenIPMPWS openIPMPWS = null;
  
  public OpenIPMPWSProxy() {
    _initOpenIPMPWSProxy();
  }
  
  private void _initOpenIPMPWSProxy() {
    try {
      openIPMPWS = (new com.mutable.osms.server.app.service.OpenIPMPWSServiceLocator()).getOpenIPMPWS();
      if (openIPMPWS != null) {
        if (_endpoint != null)
          ((javax.xml.rpc.Stub)openIPMPWS)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
        else
          _endpoint = (String)((javax.xml.rpc.Stub)openIPMPWS)._getProperty("javax.xml.rpc.service.endpoint.address");
      }
      
    }
    catch (javax.xml.rpc.ServiceException serviceException) {}
  }
  
  public String getEndpoint() {
    return _endpoint;
  }
  
  public void setEndpoint(String endpoint) {
    _endpoint = endpoint;
    if (openIPMPWS != null)
      ((javax.xml.rpc.Stub)openIPMPWS)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
    
  }
  
  public com.mutable.osms.server.app.service.OpenIPMPWS getOpenIPMPWS() {
    if (openIPMPWS == null)
      _initOpenIPMPWSProxy();
    return openIPMPWS;
  }
  
  public void ping() throws java.rmi.RemoteException{
    if (openIPMPWS == null)
      _initOpenIPMPWSProxy();
    openIPMPWS.ping();
  }
  
  public int login(java.lang.String userName, java.lang.String passwd) throws java.rmi.RemoteException{
    if (openIPMPWS == null)
      _initOpenIPMPWSProxy();
    return openIPMPWS.login(userName, passwd);
  }
  
  public int packageSecureContentWithParams(java.lang.String agentUserName, java.lang.String agentPassword, java.lang.String sourceFileURL, java.lang.String destinationFileURL, java.lang.String contentOwnerAppId, java.lang.String contentOwnerUserId, java.lang.String transactionID, java.lang.String validityStartDate, java.lang.String validityEndDate, int validityDays, int validityPlaycount, java.lang.String[] grantUsers) throws java.rmi.RemoteException{
    if (openIPMPWS == null)
      _initOpenIPMPWSProxy();
    return openIPMPWS.packageSecureContentWithParams(agentUserName, agentPassword, sourceFileURL, destinationFileURL, contentOwnerAppId, contentOwnerUserId, transactionID, validityStartDate, validityEndDate, validityDays, validityPlaycount, grantUsers);
  }
  
  public int packageSecureContentWithParamsForSingleUser(java.lang.String agentUserName, java.lang.String agentPassword, java.lang.String sourceFileURL, java.lang.String destinationFileURL, java.lang.String contentOwnerAppId, java.lang.String contentOwnerUserId, java.lang.String transactionID, java.lang.String validityStartDate, java.lang.String validityEndDate, int validityDays, int validityPlaycount, java.lang.String grantUser) throws java.rmi.RemoteException{
    if (openIPMPWS == null)
      _initOpenIPMPWSProxy();
    return openIPMPWS.packageSecureContentWithParamsForSingleUser(agentUserName, agentPassword, sourceFileURL, destinationFileURL, contentOwnerAppId, contentOwnerUserId, transactionID, validityStartDate, validityEndDate, validityDays, validityPlaycount, grantUser);
  }
  
  public int packageSecureContentWithMPEG_REL(java.lang.String agentUserName, java.lang.String agentPassword, java.lang.String contentOwnerAppId, java.lang.String contentOwnerUserId, java.lang.String transactionID, java.lang.String mpegREL) throws java.rmi.RemoteException{
    if (openIPMPWS == null)
      _initOpenIPMPWSProxy();
    return openIPMPWS.packageSecureContentWithMPEG_REL(agentUserName, agentPassword, contentOwnerAppId, contentOwnerUserId, transactionID, mpegREL);
  }
  
  
}