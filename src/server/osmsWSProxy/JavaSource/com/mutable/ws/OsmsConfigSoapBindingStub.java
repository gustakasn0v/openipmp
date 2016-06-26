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

 * OsmsConfigSoapBindingStub.java

 *

 * This file was auto-generated from WSDL

 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.

 */



package com.mutable.ws;



public class OsmsConfigSoapBindingStub extends org.apache.axis.client.Stub implements com.mutable.ws.OsmsConfig {

    private java.util.Vector cachedSerClasses = new java.util.Vector();

    private java.util.Vector cachedSerQNames = new java.util.Vector();

    private java.util.Vector cachedSerFactories = new java.util.Vector();

    private java.util.Vector cachedDeserFactories = new java.util.Vector();



    static org.apache.axis.description.OperationDesc [] _operations;



    static {

        _operations = new org.apache.axis.description.OperationDesc[3];

        _initOperationDesc1();

    }


    private static void _initOperationDesc1(){

        org.apache.axis.description.OperationDesc oper;

        org.apache.axis.description.ParameterDesc param;

        oper = new org.apache.axis.description.OperationDesc();

        oper.setName("getServerPort");

        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));

        oper.setReturnClass(java.lang.String.class);

        oper.setReturnQName(new javax.xml.namespace.QName("", "getServerPortReturn"));

        oper.setStyle(org.apache.axis.constants.Style.RPC);

        oper.setUse(org.apache.axis.constants.Use.ENCODED);

        _operations[0] = oper;



        oper = new org.apache.axis.description.OperationDesc();

        oper.setName("getRightsHostPort");

        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));

        oper.setReturnClass(java.lang.String.class);

        oper.setReturnQName(new javax.xml.namespace.QName("", "getRightsHostPortReturn"));

        oper.setStyle(org.apache.axis.constants.Style.RPC);

        oper.setUse(org.apache.axis.constants.Use.ENCODED);

        _operations[1] = oper;



        oper = new org.apache.axis.description.OperationDesc();

        oper.setName("getRightsHostUrl");

        oper.setReturnType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));

        oper.setReturnClass(java.lang.String.class);

        oper.setReturnQName(new javax.xml.namespace.QName("", "getRightsHostUrlReturn"));

        oper.setStyle(org.apache.axis.constants.Style.RPC);

        oper.setUse(org.apache.axis.constants.Use.ENCODED);

        _operations[2] = oper;



    }



    public OsmsConfigSoapBindingStub() throws org.apache.axis.AxisFault {

         this(null);

    }



    public OsmsConfigSoapBindingStub(java.net.URL endpointURL, javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {

         this(service);

         super.cachedEndpoint = endpointURL;

    }



    public OsmsConfigSoapBindingStub(javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {

        if (service == null) {

            super.service = new org.apache.axis.client.Service();

        } else {

            super.service = service;

        }

        ((org.apache.axis.client.Service)super.service).setTypeMappingVersion("1.2");

    }



    protected org.apache.axis.client.Call createCall() throws java.rmi.RemoteException {

        try {

            org.apache.axis.client.Call _call = super._createCall();

            if (super.maintainSessionSet) {

                _call.setMaintainSession(super.maintainSession);

            }

            if (super.cachedUsername != null) {

                _call.setUsername(super.cachedUsername);

            }

            if (super.cachedPassword != null) {

                _call.setPassword(super.cachedPassword);

            }

            if (super.cachedEndpoint != null) {

                _call.setTargetEndpointAddress(super.cachedEndpoint);

            }

            if (super.cachedTimeout != null) {

                _call.setTimeout(super.cachedTimeout);

            }

            if (super.cachedPortName != null) {

                _call.setPortName(super.cachedPortName);

            }

            java.util.Enumeration keys = super.cachedProperties.keys();

            while (keys.hasMoreElements()) {

                java.lang.String key = (java.lang.String) keys.nextElement();

                _call.setProperty(key, super.cachedProperties.get(key));

            }

            return _call;

        }

        catch (java.lang.Throwable _t) {

            throw new org.apache.axis.AxisFault("Failure trying to get the Call object", _t);

        }

    }



    public java.lang.String getServerPort() throws java.rmi.RemoteException {

        if (super.cachedEndpoint == null) {

            throw new org.apache.axis.NoEndPointException();

        }

        org.apache.axis.client.Call _call = createCall();

        _call.setOperation(_operations[0]);

        _call.setUseSOAPAction(true);

        _call.setSOAPActionURI("");

        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);

        _call.setOperationName(new javax.xml.namespace.QName("http://ws.mutable.com", "getServerPort"));



        setRequestHeaders(_call);

        setAttachments(_call);

 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {});



        if (_resp instanceof java.rmi.RemoteException) {

            throw (java.rmi.RemoteException)_resp;

        }

        else {

            extractAttachments(_call);

            try {

                return (java.lang.String) _resp;

            } catch (java.lang.Exception _exception) {

                return (java.lang.String) org.apache.axis.utils.JavaUtils.convert(_resp, java.lang.String.class);

            }

        }

  } catch (org.apache.axis.AxisFault axisFaultException) {

  throw axisFaultException;

}

    }



    public java.lang.String getRightsHostPort() throws java.rmi.RemoteException {

        if (super.cachedEndpoint == null) {

            throw new org.apache.axis.NoEndPointException();

        }

        org.apache.axis.client.Call _call = createCall();

        _call.setOperation(_operations[1]);

        _call.setUseSOAPAction(true);

        _call.setSOAPActionURI("");

        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);

        _call.setOperationName(new javax.xml.namespace.QName("http://ws.mutable.com", "getRightsHostPort"));



        setRequestHeaders(_call);

        setAttachments(_call);

 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {});



        if (_resp instanceof java.rmi.RemoteException) {

            throw (java.rmi.RemoteException)_resp;

        }

        else {

            extractAttachments(_call);

            try {

                return (java.lang.String) _resp;

            } catch (java.lang.Exception _exception) {

                return (java.lang.String) org.apache.axis.utils.JavaUtils.convert(_resp, java.lang.String.class);

            }

        }

  } catch (org.apache.axis.AxisFault axisFaultException) {

  throw axisFaultException;

}

    }



    public java.lang.String getRightsHostUrl() throws java.rmi.RemoteException {

        if (super.cachedEndpoint == null) {

            throw new org.apache.axis.NoEndPointException();

        }

        org.apache.axis.client.Call _call = createCall();

        _call.setOperation(_operations[2]);

        _call.setUseSOAPAction(true);

        _call.setSOAPActionURI("");

        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);

        _call.setOperationName(new javax.xml.namespace.QName("http://ws.mutable.com", "getRightsHostUrl"));



        setRequestHeaders(_call);

        setAttachments(_call);

 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {});



        if (_resp instanceof java.rmi.RemoteException) {

            throw (java.rmi.RemoteException)_resp;

        }

        else {

            extractAttachments(_call);

            try {

                return (java.lang.String) _resp;

            } catch (java.lang.Exception _exception) {

                return (java.lang.String) org.apache.axis.utils.JavaUtils.convert(_resp, java.lang.String.class);

            }

        }

  } catch (org.apache.axis.AxisFault axisFaultException) {

  throw axisFaultException;

}

    }



}

