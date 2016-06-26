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

package com.mutable.ws;



public class OsmsConfigProxy implements com.mutable.ws.OsmsConfig {

  private String _endpoint = null;

  private com.mutable.ws.OsmsConfig osmsConfig = null;

  

  public OsmsConfigProxy() {

    _initOsmsConfigProxy();

  }

  

  private void _initOsmsConfigProxy() {

    try {

      osmsConfig = (new com.mutable.ws.OsmsConfigServiceLocator()).getOsmsConfig();

      if (osmsConfig != null) {

        if (_endpoint != null)

          ((javax.xml.rpc.Stub)osmsConfig)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);

        else

          _endpoint = (String)((javax.xml.rpc.Stub)osmsConfig)._getProperty("javax.xml.rpc.service.endpoint.address");

      }

      

    }

    catch (javax.xml.rpc.ServiceException serviceException) {}

  }

  

  public String getEndpoint() {

    return _endpoint;

  }

  

  public void setEndpoint(String endpoint) {

    _endpoint = endpoint;

    if (osmsConfig != null)

      ((javax.xml.rpc.Stub)osmsConfig)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);

    

  }

  

  public com.mutable.ws.OsmsConfig getOsmsConfig() {

    if (osmsConfig == null)

      _initOsmsConfigProxy();

    return osmsConfig;

  }

  

  public java.lang.String getServerPort() throws java.rmi.RemoteException{

    if (osmsConfig == null)

      _initOsmsConfigProxy();

    return osmsConfig.getServerPort();

  }

  

  public java.lang.String getRightsHostPort() throws java.rmi.RemoteException{

    if (osmsConfig == null)

      _initOsmsConfigProxy();

    return osmsConfig.getRightsHostPort();

  }

  

  public java.lang.String getRightsHostUrl() throws java.rmi.RemoteException{

    if (osmsConfig == null)

      _initOsmsConfigProxy();

    return osmsConfig.getRightsHostUrl();

  }

  

  

}