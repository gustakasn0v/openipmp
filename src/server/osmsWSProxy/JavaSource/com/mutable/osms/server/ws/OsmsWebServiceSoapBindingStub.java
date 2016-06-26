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
 * OsmsWebServiceSoapBindingStub.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.osms.server.ws;

public class OsmsWebServiceSoapBindingStub extends org.apache.axis.client.Stub implements com.mutable.osms.server.ws.OsmsWebService {
    private java.util.Vector cachedSerClasses = new java.util.Vector();
    private java.util.Vector cachedSerQNames = new java.util.Vector();
    private java.util.Vector cachedSerFactories = new java.util.Vector();
    private java.util.Vector cachedDeserFactories = new java.util.Vector();

    static org.apache.axis.description.OperationDesc [] _operations;

    static {
        _operations = new org.apache.axis.description.OperationDesc[11];
        _initOperationDesc1();
        _initOperationDesc2();
    }

    private static void _initOperationDesc1(){
        org.apache.axis.description.OperationDesc oper;
        org.apache.axis.description.ParameterDesc param;
        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("query");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsQueryRequest"), com.mutable.osms.server.ws.message.OsmsQueryRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsQueryResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsQueryResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "queryReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsQueryFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsQueryFault"), 
                      true
                     ));
        _operations[0] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("license");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsLicenseRequest"), com.mutable.osms.server.ws.message.OsmsLicenseRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsLicenseResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsLicenseResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "licenseReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsLicenseFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsLicenseFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        _operations[1] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("userLogin");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginRequest"), com.mutable.osms.server.ws.message.OsmsUserLoginRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsUserLoginResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "userLoginReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        _operations[2] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("userLogout");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLogoutRequest"), com.mutable.osms.server.ws.message.OsmsUserLogoutRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLogoutResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsUserLogoutResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "userLogoutReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLogoutFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLogoutFault"), 
                      true
                     ));
        _operations[3] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("createUser");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsCreateUserRequest"), com.mutable.osms.server.ws.message.OsmsCreateUserRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsCreateUserResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsCreateUserResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "createUserReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsCreateUserFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsCreateUserFault"), 
                      true
                     ));
        _operations[4] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("getContentKey");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsGetContentKeyRequest"), com.mutable.osms.server.ws.message.OsmsGetContentKeyRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsGetContentKeyResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "getContentKeyReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsGetContentKeyFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsGetContentKeyFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        _operations[5] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("registerContentAssignIdentifier");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentAssignIdentifierRequest"), com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentAssignIdentifierResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "registerContentAssignIdentifierReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentAssignIdentifierFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        _operations[6] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("registerContentExistingIdentifier");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentExistingIdentifierRequest"), com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentExistingIdentifierResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "registerContentExistingIdentifierReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentExistingIdentifierFault"), 
                      true
                     ));
        _operations[7] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("registerDigitalItemInstance");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterDigitalItemInstanceRequest"), com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterDigitalItemInstanceResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "registerDigitalItemInstanceReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterDigitalItemInstanceFault"), 
                      true
                     ));
        _operations[8] = oper;

        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("registerUser");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterUserRequest"), com.mutable.osms.server.ws.message.OsmsRegisterUserRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterUserResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsRegisterUserResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "registerUserReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsRegisterUserFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterUserFault"), 
                      true
                     ));
        _operations[9] = oper;

    }

    private static void _initOperationDesc2(){
        org.apache.axis.description.OperationDesc oper;
        org.apache.axis.description.ParameterDesc param;
        oper = new org.apache.axis.description.OperationDesc();
        oper.setName("rightsAuthorization");
        param = new org.apache.axis.description.ParameterDesc(new javax.xml.namespace.QName("", "msg"), org.apache.axis.description.ParameterDesc.IN, new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRightsAuthorizationRequest"), com.mutable.osms.server.ws.message.OsmsRightsAuthorizationRequest.class, false, false);
        oper.addParameter(param);
        oper.setReturnType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRightsAuthorizationResponse"));
        oper.setReturnClass(com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse.class);
        oper.setReturnQName(new javax.xml.namespace.QName("", "rightsAuthorizationReturn"));
        oper.setStyle(org.apache.axis.constants.Style.RPC);
        oper.setUse(org.apache.axis.constants.Use.ENCODED);
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsUserLoginFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault"), 
                      true
                     ));
        oper.addFault(new org.apache.axis.description.FaultDesc(
                      new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "fault"),
                      "com.mutable.osms.server.ws.message.OsmsRightsAuthorizationFault",
                      new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRightsAuthorizationFault"), 
                      true
                     ));
        _operations[10] = oper;

    }

    public OsmsWebServiceSoapBindingStub() throws org.apache.axis.AxisFault {
         this(null);
    }

    public OsmsWebServiceSoapBindingStub(java.net.URL endpointURL, javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
         this(service);
         super.cachedEndpoint = endpointURL;
    }

    public OsmsWebServiceSoapBindingStub(javax.xml.rpc.Service service) throws org.apache.axis.AxisFault {
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
            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsCreateUserFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsCreateUserFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsCreateUserRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsCreateUserRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsCreateUserResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsCreateUserResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsGetContentKeyFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsGetContentKeyFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsGetContentKeyRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsGetContentKeyRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsGetContentKeyResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsLicenseFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsLicenseFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsLicenseRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsLicenseRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsLicenseResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsLicenseResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsQueryFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsQueryFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsQueryRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsQueryRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsQueryResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsQueryResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentAssignIdentifierFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentAssignIdentifierRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentAssignIdentifierResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentExistingIdentifierFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentExistingIdentifierRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterContentExistingIdentifierResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterDigitalItemInstanceFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterDigitalItemInstanceRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterDigitalItemInstanceResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterUserFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterUserFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterUserRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterUserRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterUserResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRegisterUserResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRightsAuthorizationFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRightsAuthorizationFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRightsAuthorizationRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRightsAuthorizationRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRightsAuthorizationResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsUserLoginFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsUserLoginRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLoginResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsUserLoginResponse.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLogoutFault");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsUserLogoutFault.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLogoutRequest");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsUserLogoutRequest.class;
            cachedSerClasses.add(cls);
            cachedSerFactories.add(beansf);
            cachedDeserFactories.add(beandf);

            qName = new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsUserLogoutResponse");
            cachedSerQNames.add(qName);
            cls = com.mutable.osms.server.ws.message.OsmsUserLogoutResponse.class;
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

    public com.mutable.osms.server.ws.message.OsmsQueryResponse query(com.mutable.osms.server.ws.message.OsmsQueryRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsQueryFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[0]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "query"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsQueryResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsQueryResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsQueryResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsQueryFault) {
              throw (com.mutable.osms.server.ws.message.OsmsQueryFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsLicenseResponse license(com.mutable.osms.server.ws.message.OsmsLicenseRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsLicenseFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[1]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "license"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsLicenseResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsLicenseResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsLicenseResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsLicenseFault) {
              throw (com.mutable.osms.server.ws.message.OsmsLicenseFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsUserLoginResponse userLogin(com.mutable.osms.server.ws.message.OsmsUserLoginRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[2]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "userLogin"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsUserLoginResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsUserLoginResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsUserLoginResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsUserLogoutResponse userLogout(com.mutable.osms.server.ws.message.OsmsUserLogoutRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsUserLogoutFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[3]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "userLogout"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsUserLogoutResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsUserLogoutResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsUserLogoutResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLogoutFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLogoutFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsCreateUserResponse createUser(com.mutable.osms.server.ws.message.OsmsCreateUserRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsCreateUserFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[4]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "createUser"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsCreateUserResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsCreateUserResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsCreateUserResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsCreateUserFault) {
              throw (com.mutable.osms.server.ws.message.OsmsCreateUserFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse getContentKey(com.mutable.osms.server.ws.message.OsmsGetContentKeyRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsGetContentKeyFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[5]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "getContentKey"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsGetContentKeyFault) {
              throw (com.mutable.osms.server.ws.message.OsmsGetContentKeyFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse registerContentAssignIdentifier(com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierFault, com.mutable.osms.server.ws.message.OsmsUserLoginFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[6]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "registerContentAssignIdentifier"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierFault) {
              throw (com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse registerContentExistingIdentifier(com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[7]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "registerContentExistingIdentifier"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierFault) {
              throw (com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse registerDigitalItemInstance(com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[8]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "registerDigitalItemInstance"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceFault) {
              throw (com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsRegisterUserResponse registerUser(com.mutable.osms.server.ws.message.OsmsRegisterUserRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsRegisterUserFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[9]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "registerUser"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsRegisterUserResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsRegisterUserResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsRegisterUserResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsRegisterUserFault) {
              throw (com.mutable.osms.server.ws.message.OsmsRegisterUserFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

    public com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse rightsAuthorization(com.mutable.osms.server.ws.message.OsmsRightsAuthorizationRequest msg) throws java.rmi.RemoteException, com.mutable.osms.server.ws.message.OsmsUserLoginFault, com.mutable.osms.server.ws.message.OsmsRightsAuthorizationFault {
        if (super.cachedEndpoint == null) {
            throw new org.apache.axis.NoEndPointException();
        }
        org.apache.axis.client.Call _call = createCall();
        _call.setOperation(_operations[10]);
        _call.setUseSOAPAction(true);
        _call.setSOAPActionURI("");
        _call.setSOAPVersion(org.apache.axis.soap.SOAPConstants.SOAP11_CONSTANTS);
        _call.setOperationName(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "rightsAuthorization"));

        setRequestHeaders(_call);
        setAttachments(_call);
 try {        java.lang.Object _resp = _call.invoke(new java.lang.Object[] {msg});

        if (_resp instanceof java.rmi.RemoteException) {
            throw (java.rmi.RemoteException)_resp;
        }
        else {
            extractAttachments(_call);
            try {
                return (com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse) _resp;
            } catch (java.lang.Exception _exception) {
                return (com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse) org.apache.axis.utils.JavaUtils.convert(_resp, com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse.class);
            }
        }
  } catch (org.apache.axis.AxisFault axisFaultException) {
    if (axisFaultException.detail != null) {
        if (axisFaultException.detail instanceof java.rmi.RemoteException) {
              throw (java.rmi.RemoteException) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsUserLoginFault) {
              throw (com.mutable.osms.server.ws.message.OsmsUserLoginFault) axisFaultException.detail;
         }
        if (axisFaultException.detail instanceof com.mutable.osms.server.ws.message.OsmsRightsAuthorizationFault) {
              throw (com.mutable.osms.server.ws.message.OsmsRightsAuthorizationFault) axisFaultException.detail;
         }
   }
  throw axisFaultException;
}
    }

}
