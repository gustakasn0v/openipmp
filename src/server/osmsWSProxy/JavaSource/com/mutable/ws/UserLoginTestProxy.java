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



public class UserLoginTestProxy implements com.mutable.ws.UserLoginTest {

  private String _endpoint = null;

  private com.mutable.ws.UserLoginTest userLoginTest = null;

  

  public UserLoginTestProxy() {

    _initUserLoginTestProxy();

  }

  

  private void _initUserLoginTestProxy() {

    try {

      userLoginTest = (new com.mutable.ws.UserLoginTestServiceLocator()).getUserLoginTest();

      if (userLoginTest != null) {

        if (_endpoint != null)

          ((javax.xml.rpc.Stub)userLoginTest)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);

        else

          _endpoint = (String)((javax.xml.rpc.Stub)userLoginTest)._getProperty("javax.xml.rpc.service.endpoint.address");

      }

      

    }

    catch (javax.xml.rpc.ServiceException serviceException) {}

  }

  

  public String getEndpoint() {

    return _endpoint;

  }

  

  public void setEndpoint(String endpoint) {

    _endpoint = endpoint;

    if (userLoginTest != null)

      ((javax.xml.rpc.Stub)userLoginTest)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);

    

  }

  

  public com.mutable.ws.UserLoginTest getUserLoginTest() {

    if (userLoginTest == null)

      _initUserLoginTestProxy();

    return userLoginTest;

  }

  

  public java.lang.String login(java.lang.String userName, java.lang.String password) throws java.rmi.RemoteException{

    if (userLoginTest == null)

      _initUserLoginTestProxy();

    return userLoginTest.login(userName, password);

  }

  

  

}