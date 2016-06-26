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
 * OMADRMWSBindingStub.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.omadrm.ws;

public class OMADRMWSBindingStub extends org.apache.axis.client.Stub implements com.mutable.omadrm.ws.OMADRMWS {
    private java.util.Vector cachedSerClasses = new java.util.Vector();
    private java.util.Vector cachedSerQNames = new java.util.Vector();
    private java.util.Vector cachedSerFactories = new java.util.Vector();
    private java.util.Vector cachedDeserFactories = new java.util.Vector();

    static org.apache.axis.description.OperationDesc [] _operations;

    static {
        _operations = new org.apache.axis.description.OperationDesc[6];
        _initOperationDesc1();
    }

    private static void _initOperationDesc1(){
        org.apache.axis.description.OperationDesc oper;
        org.apache.axis.description.ParameterDesc param;
        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("addContentKey");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "add_key_request"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddContentKeyRequest"), com.mutable.omadrm.ws.roap.WSAddContentKeyRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddContentKeyResponse"));
        oper.setReturnClass(com.mutable.omadrm.ws.roap.WSAddContentKeyResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "add_key_response"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        _operations[0] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("addDeviceRights");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "add_rights_request"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddDeviceRightsRequest"), com.mutable.omadrm.ws.roap.WSAddDeviceRightsRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddDeviceRightsResponse"));
        oper.setReturnClass(com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "add_rights_response"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        _operations[1] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("hello");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSDeviceHello"), com.mutable.omadrm.ws.roap.WSDeviceHello.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRIHello"));
        oper.setReturnClass(com.mutable.omadrm.ws.roap.WSRIHello.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "message"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        _operations[2] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("registration");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRegistrationRequest"), com.mutable.omadrm.ws.roap.WSRegistrationRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRegistrationResponse"));
        oper.setReturnClass(com.mutable.omadrm.ws.roap.WSRegistrationResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "message"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        _operations[3] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("initialRO");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSInitialRORequest"), com.mutable.omadrm.ws.roap.WSInitialRORequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSROAcquisitionTrigger"));
        oper.setReturnClass(com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "message"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        _operations[4] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("roAcquisition");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "message"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRORequest"), com.mutable.omadrm.ws.roap.WSRORequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSROResponse"));
        oper.setReturnClass(com.mutable.omadrm.ws.roap.WSROResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "message"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        _operations[5] = oper;

    }

    public OMADRMWSBindingStub() throws org.apache.axis.AxisFault {
         this(null);
    }

    public OMADRMWSBindingStub(java.net.URL endpointURL, javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
         this(service);
         super.cachedEndpoint = endpointURL;
    }

    public OMADRMWSBindingStub(javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
        if (service == null) {
            super.service = new org.apache.axis.client.Service();
        } else {
            super.service = service;
        }
        ((org.apache.axis.client.Service)super.service).setTypeMappingVersion("1.2");
            java.lang.Class cls;
            javax.xml.namespace.QName qName;
            javax.xml.namespace.QName qName2;
            java.lang.Class beansf = org.apache.axis.encoding.ser.BeanSerializerFactory.class;
            java.lang.Class beandf = org.apache.axis.encoding.ser.BeanDeserializerFactory.class;
            java.lang.Class enumsf = org.apache.axis.encoding.ser.EnumSerializerFactory.class;
            java.lang.Class enumdf = org.apache.axis.encoding.ser.EnumDeserializerFactory.class;
            java.lang.Class arraysf = org.apache.axis.encoding.ser.ArraySerializerFactory.class;
            java.lang.Class arraydf = org.apache.axis.encoding.ser.ArrayDeserializerFactory.class;
            java.lang.Class simplesf = org.apache.axis.encoding.ser.SimpleSerializerFactory.class;
            java.lang.Class simpledf = org.apache.axis.encoding.ser.SimpleDeserializerFactory.class;
            java.lang.Class simplelistsf = org.apache.axis.encoding.ser.SimpleListSerializerFactory.class;
            java.lang.Class simplelistdf = org.apache.axis.encoding.ser.SimpleListDeserializerFactory.class;
            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddContentKeyRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSAddContentKeyRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddContentKeyResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSAddContentKeyResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddDeviceRightsRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSAddDeviceRightsRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSAddDeviceRightsResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSDeviceHello");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSDeviceHello.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSInitialRORequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSInitialRORequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRegistrationRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSRegistrationRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRegistrationResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSRegistrationResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRIHello");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSRIHello.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSROAcquisitionTrigger");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSRORequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSRORequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://roap.ws.omadrm.mutable.com", "WSROResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.omadrm.ws.roap.WSROResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

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
            // All the type mapping information is registered
            // when the first call is made.
            // The type mapping information is actually registered in
            // the TypeMappingRegistry of the service, which
            // is the reason why registration is only needed for the first call.
            synchronized (this) {
                if (firstCall()) {
                    // must set encoding style before registering serializers
                    _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
                    _call.setEncodingStyle(org.apache.axis.Constants.URI_SOAP11_ENC);
                    for (int i = 0; i < cachedSerFactories.size(); ++i) {
                        java.lang.Class cls = (java.lang.Class) cachedSerClasses.get(i);
                        javax.xml.namespace.QName qName =
                                (javax.xml.namespace.QName) cachedSerQNames.get(i);
                        java.lang.Object x = cachedSerFactories.get(i);
                        if (x instanceof Class) {
                            java.lang.Class sf = (java.lang.Class)
                                 cachedSerFactories.get(i);
                            java.lang.Class df = (java.lang.Class)
                                 cachedDeserFactories.get(i);
                            _call.registerTypeMapping(cls, qName, sf, df, false);
                        }
                        else if (x instanceof javax.xml.rpc.encoding.SerializerFactory) {
                            org.apache.axis.encoding.SerializerFactory sf = (org.apache.axis.encoding.SerializerFactory)
                                 cachedSerFactories.get(i);
                            org.apache.axis.encoding.DeserializerFactory df = (org.apache.axis.encoding.DeserializerFactory)
                                 cachedDeserFactories.get(i);
                            _call.registerTypeMapping(cls, qName, sf, df, false);
                        }
                    }
                }
            }
            return _call;
        }
        catch (java.lang.Throwable _t) {
            throw new org.apache.axis.AxisFault("Failure trying to get the Call object", _t);
        }
    }

    public com.mutable.omadrm.ws.roap.WSAddContentKeyResponse addContentKey(com.mutable.omadrm.ws.roap.WSAddContentKeyRequest add_key_request) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[0]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("", "addContentKey"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {add_key_request});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.omadrm.ws.roap.WSAddContentKeyResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.omadrm.ws.roap.WSAddContentKeyResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.omadrm.ws.roap.WSAddContentKeyResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
  throw axisFaultException;
}
    }

    public com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse addDeviceRights(com.mutable.omadrm.ws.roap.WSAddDeviceRightsRequest add_rights_request) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[1]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("", "addDeviceRights"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {add_rights_request});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.omadrm.ws.roap.WSAddDeviceRightsResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
  throw axisFaultException;
}
    }

    public com.mutable.omadrm.ws.roap.WSRIHello hello(com.mutable.omadrm.ws.roap.WSDeviceHello message) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[2]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("", "hello"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {message});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.omadrm.ws.roap.WSRIHello) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.omadrm.ws.roap.WSRIHello) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.omadrm.ws.roap.WSRIHello.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
  throw axisFaultException;
}
    }

    public com.mutable.omadrm.ws.roap.WSRegistrationResponse registration(com.mutable.omadrm.ws.roap.WSRegistrationRequest message) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[3]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("", "registration"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {message});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.omadrm.ws.roap.WSRegistrationResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.omadrm.ws.roap.WSRegistrationResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.omadrm.ws.roap.WSRegistrationResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
  throw axisFaultException;
}
    }

    public com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger initialRO(com.mutable.omadrm.ws.roap.WSInitialRORequest message) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[4]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("", "initialRO"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {message});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.omadrm.ws.roap.WSROAcquisitionTrigger.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
  throw axisFaultException;
}
    }

    public com.mutable.omadrm.ws.roap.WSROResponse roAcquisition(com.mutable.omadrm.ws.roap.WSRORequest message) throws java.rmi.RemoteException {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[5]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("", "roAcquisition"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {message});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.omadrm.ws.roap.WSROResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.omadrm.ws.roap.WSROResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.omadrm.ws.roap.WSROResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
  throw axisFaultException;
}
    }

}
