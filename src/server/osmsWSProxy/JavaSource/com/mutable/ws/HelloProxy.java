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



public class HelloProxy implements com.mutable.ws.Hello {

  private String _endpoint = null;

  private com.mutable.ws.Hello hello = null;

  

  public HelloProxy() {

    _initHelloProxy();

  }

  

  private void _initHelloProxy() {

    try {

      hello = (new com.mutable.ws.HelloServiceLocator()).getHello();

      if (hello != null) {

        if (_endpoint != null)

          ((javax.xml.rpc.Stub)hello)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);

        else

          _endpoint = (String)((javax.xml.rpc.Stub)hello)._getProperty("javax.xml.rpc.service.endpoint.address");

      }

      

    }

    catch (javax.xml.rpc.ServiceException serviceException) {}

  }

  

  public String getEndpoint() {

    return _endpoint;

  }

  

  public void setEndpoint(String endpoint) {

    _endpoint = endpoint;

    if (hello != null)

      ((javax.xml.rpc.Stub)hello)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);

    

  }

  

  public com.mutable.ws.Hello getHello() {

    if (hello == null)

      _initHelloProxy();

    return hello;

  }

  

  public java.lang.String hello(java.lang.String name) throws java.rmi.RemoteException{

    if (hello == null)

      _initHelloProxy();

    return hello.hello(name);

  }

  

  

}