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

public class EncoderProxy implements com.mutable.ws.Encoder {
  private String _endpoint = null;
  private com.mutable.ws.Encoder encoder = null;
  
  public EncoderProxy() {
    _initEncoderProxy();
  }
  
  private void _initEncoderProxy() {
    try {
      encoder = (new com.mutable.ws.EncoderServiceLocator()).getEncoder();
      if (encoder != null) {
        if (_endpoint != null)
          ((javax.xml.rpc.Stub)encoder)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
        else
          _endpoint = (String)((javax.xml.rpc.Stub)encoder)._getProperty("javax.xml.rpc.service.endpoint.address");
      }
      
    }
    catch (javax.xml.rpc.ServiceException serviceException) {}
  }
  
  public String getEndpoint() {
    return _endpoint;
  }
  
  public void setEndpoint(String endpoint) {
    _endpoint = endpoint;
    if (encoder != null)
      ((javax.xml.rpc.Stub)encoder)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
    
  }
  
  public com.mutable.ws.Encoder getEncoder() {
    if (encoder == null)
      _initEncoderProxy();
    return encoder;
  }
  
  public int encode(java.lang.String username, java.lang.String password, java.lang.String inFile, java.lang.String outFile) throws java.rmi.RemoteException{
    if (encoder == null)
      _initEncoderProxy();
    return encoder.encode(username, password, inFile, outFile);
  }
  
  
}