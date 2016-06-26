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
 * OMADRMWSBindingSkeleton.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.omadrm.ws;

public class OMADRMWSBindingSkeleton implements com.mutable.omadrm.ws.OMADRMWS, org.apache.axis.wsdl.Skeleton {
    private com.mutable.omadrm.ws.OMADRMWS impl;
    private static java.util.Map _myOperations = new java.util.Hashtable();
    private static java.util.Collection _myOperationsList = new java.util.ArrayList();

    /**
    * Returns List of OperationDesc objects with this name
    */
    public static java.util.List getOperationDescByName(java.lang.String methodName) {
        return (java.util.List)_myOperations.get(methodName);
    }

    /**
    * Returns Collection of OperationDescs
    */
    public static java.util.Collection getOperationDescs() {
        return _myOperationsList;
    }

    static {
        org.apache.axis.description.OperationDesc _oper;
        org.apache.axis.description.FaultDesc _fault;
        org.apache.axis.description.ParameterDesc [] _params;
        _params = new org.apache.axis.description.ParameterDesc [] {
            new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "add_key_request"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddContentKeyRequest"), com.mutable.omadrm.ws.roap.WSAddContentKeyRequest.class, false, false), 
        };
        _oper = new org.apache.axis.description.OperationDesc("addContentKey", _params, new javax.xml.namespace.QName("", "add_key_response"));
        _oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddContentKeyResponse"));
        _oper.setElementQName(new javax.xml.namespace.QName("", "addContentKey"));
        _oper.setSoapAction("");
        _myOperationsList.add(_oper);
        if (_myOperations.get("addContentKey") == null) {
            _myOperations.put("addContentKey", new java.util.ArrayList());
        }
        ((java.util.List)_myOperations.get("addContentKey")).add(_oper);
        _params = new org.apache.axis.description.ParameterDesc [] {
            new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "add_rights_request"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddDeviceRightsRequest"), com.mutable.omadrm.ws.roap.WSAddDeviceRightsRequest.class, false, false), 
        };
        _oper = new org.apache.axis.description.OperationDesc("addDeviceRights", _params, new javax.xml.namespace.QName("", "add_rights_response"));
        _oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddDeviceRightsResponse"));
        _oper.setElementQName(new javax.xml.namespace.QName("", "addDeviceRights"));
        _oper.setSoapAction("");
        _myOperationsList.add(_oper);
        if (_myOperations.get("addDeviceRights") == null) {
            _myOperations.put("addDeviceRights", new java.util.ArrayList());
        }
        ((java.util.List)_myOperations.get("addDeviceRights")).add(_oper);
        _params = new org.apache.axis.description.ParameterDesc [] {
            new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSDeviceHello"), com.mutable.omadrm.ws.roap.WSDeviceHello.class, false, false), 
        };
        _oper = new org.apache.axis.description.OperationDesc("hello", _params, new javax.xml.namespace.QName("", "message"));
        _oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRIHello"));
        _oper.setElementQName(new javax.xml.namespace.QName("", "hello"));
        _oper.setSoapAction("");
        _myOperationsList.add(_oper);
        if (_myOperations.get("hello") == null) {
            _myOperations.put("hello", new java.util.ArrayList());
        }
        ((java.util.List)_myOperations.get("hello")).add(_oper);
        _params = new org.apache.axis.description.ParameterDesc [] {
            new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRegistrationRequest"), com.mutable.omadrm.ws.roap.WSRegistrationRequest.class, false, false), 
        };
        _oper = new org.apache.axis.description.OperationDesc("registration", _params, new javax.xml.namespace.QName("", "message"));
        _oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRegistrationResponse"));
        _oper.setElementQName(new javax.xml.namespace.QName("", "registration"));
        _oper.setSoapAction("");
        _myOperationsList.add(_oper);
        if (_myOperations.get("registration") == null) {
            _myOperations.put("registration", new java.util.ArrayList());
        }
        ((java.util.List)_myOperations.get("registration")).add(_oper);
        _params = new org.apache.axis.description.ParameterDesc [] {
            new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSInitialRORequest"), com.mutable.omadrm.ws.roap.WSInitialRORequest.class, false, false), 
        };
        _oper = new org.apache.axis.description.OperationDesc("initialRO", _params, new javax.xml.namespace.QName("", "message"));
        _oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSROAcquisitionTrigger"));
        _oper.setElementQName(new javax.xml.namespace.QName("", "initialRO"));
        _oper.setSoapAction("");
        _myOperationsList.add(_oper);
        if (_myOperations.get("initialRO") == null) {
            _myOperations.put("initialRO", new java.util.ArrayList());
        }
        ((java.util.List)_myOperations.get("initialRO")).add(_oper);
        _params = new org.apache.axis.description.ParameterDesc [] {
            new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRORequest"), com.mutable.omadrm.ws.roap.WSRORequest.class, false, false), 
        };
        _oper = new org.apache.axis.description.OperationDesc("roAcquisition", _params, new javax.xml.namespace.QName("", "message"));
        _oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSROResponse"));
        _oper.setElementQName(new javax.xml.namespace.QName("", "roAcquisition"));
        _oper.setSoapAction("");
        _myOperationsList.add(_oper);
        if (_myOperations.get("roAcquisition") == null) {
            _myOperations.put("roAcquisition", new java.util.ArrayList());
        }
        ((java.util.List)_myOperations.get("roAcquisition")).add(_oper);
    }

    public OMADRMWSBindingSkeleton() {
        this.impl = new com.mutable.omadrm.ws.OMADRMWSBindingImpl();
    }

    public OMADRMWSBindingSkeleton(com.mutable.omadrm.ws.OMADRMWS impl) {
        this.impl = impl;
    }
    public com.mutable.omadrm.ws.roap.WSAddContentKeyResponse addContentKey(com.mutable.omadrm.ws.roap.WSAddContentKeyRequest add_key_request) throws java.rmi.RemoteException
    {
        com.mutable.omadrm.ws.roap.WSAddContentKeyResponse ret = impl.addContentKey(add_key_request);
        return ret;
    }

    public com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse addDeviceRights(com.mutable.omadrm.ws.roap.WSAddDeviceRightsRequest add_rights_request) throws java.rmi.RemoteException
    {
        com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse ret = impl.addDeviceRights(add_rights_request);
        return ret;
    }

    public com.mutable.omadrm.ws.roap.WSRIHello hello(com.mutable.omadrm.ws.roap.WSDeviceHello message) throws java.rmi.RemoteException
    {
        com.mutable.omadrm.ws.roap.WSRIHello ret = impl.hello(message);
        return ret;
    }

    public com.mutable.omadrm.ws.roap.WSRegistrationResponse registration(com.mutable.omadrm.ws.roap.WSRegistrationRequest message) throws java.rmi.RemoteException
    {
        com.mutable.omadrm.ws.roap.WSRegistrationResponse ret = impl.registration(message);
        return ret;
    }

    public com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger initialRO(com.mutable.omadrm.ws.roap.WSInitialRORequest message) throws java.rmi.RemoteException
    {
        com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger ret = impl.initialRO(message);
        return ret;
    }

    public com.mutable.omadrm.ws.roap.WSROResponse roAcquisition(com.mutable.omadrm.ws.roap.WSRORequest message) throws java.rmi.RemoteException
    {
        com.mutable.omadrm.ws.roap.WSROResponse ret = impl.roAcquisition(message);
        return ret;
    }

}
