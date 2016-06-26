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
 * OsmsWebServiceServiceLocator.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.osms.server.ws;

public class OsmsWebServiceServiceLocator extends org.apache.axis.client.Service implements com.mutable.osms.server.ws.OsmsWebServiceService {

    public OsmsWebServiceServiceLocator() {
    }


    public OsmsWebServiceServiceLocator(org.apache.axis.EngineConfiguration config) {
        super(config);
    }

    public OsmsWebServiceServiceLocator(java.lang.String wsdlLoc, javax.xml.namespace.QName sName) throws javax.xml.rpc.ServiceException {
        super(wsdlLoc, sName);
    }

    // Use to get a proxy class for OsmsWebService
    private java.lang.String OsmsWebService_address = "http://localhost:8080/openipmp/services/OsmsWebService";

    public java.lang.String getOsmsWebServiceAddress() {
        return OsmsWebService_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String OsmsWebServiceWSDDServiceName = "OsmsWebService";

    public java.lang.String getOsmsWebServiceWSDDServiceName() {
        return OsmsWebServiceWSDDServiceName;
    }

    public void setOsmsWebServiceWSDDServiceName(java.lang.String name) {
        OsmsWebServiceWSDDServiceName = name;
    }

    public com.mutable.osms.server.ws.OsmsWebService getOsmsWebService() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(OsmsWebService_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getOsmsWebService(endpoint);
    }

    public com.mutable.osms.server.ws.OsmsWebService getOsmsWebService(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            com.mutable.osms.server.ws.OsmsWebServiceSoapBindingStub _stub = new com.mutable.osms.server.ws.OsmsWebServiceSoapBindingStub(portAddress, this);
            _stub.setPortName(getOsmsWebServiceWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setOsmsWebServiceEndpointAddress(java.lang.String address) {
        OsmsWebService_address = address;
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        try {
            if (com.mutable.osms.server.ws.OsmsWebService.class.isAssignableFrom(serviceEndpointInterface)) {
                com.mutable.osms.server.ws.OsmsWebServiceSoapBindingStub _stub = new com.mutable.osms.server.ws.OsmsWebServiceSoapBindingStub(new java.net.URL(OsmsWebService_address), this);
                _stub.setPortName(getOsmsWebServiceWSDDServiceName());
                return _stub;
            }
        }
        catch (java.lang.Throwable t) {
            throw new javax.xml.rpc.ServiceException(t);
        }
        throw new javax.xml.rpc.ServiceException("There is no stub implementation for the interface:  " + (serviceEndpointInterface == null ? "null" : serviceEndpointInterface.getName()));
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(javax.xml.namespace.QName portName, Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        if (portName == null) {
            return getPort(serviceEndpointInterface);
        }
        java.lang.String inputPortName = portName.getLocalPart();
        if ("OsmsWebService".equals(inputPortName)) {
            return getOsmsWebService();
        }
        else  {
            java.rmi.Remote _stub = getPort(serviceEndpointInterface);
            ((org.apache.axis.client.Stub) _stub).setPortName(portName);
            return _stub;
        }
    }

    public javax.xml.namespace.QName getServiceName() {
        return new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "OsmsWebServiceService");
    }

    private java.util.HashSet ports = null;

    public java.util.Iterator getPorts() {
        if (ports == null) {
            ports = new java.util.HashSet();
            ports.add(new javax.xml.namespace.QName("http://ws.server.osms.mutable.com", "OsmsWebService"));
        }
        return ports.iterator();
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(java.lang.String portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        
if ("OsmsWebService".equals(portName)) {
            setOsmsWebServiceEndpointAddress(address);
        }
        else 
{ // Unknown Port Name
            throw new javax.xml.rpc.ServiceException(" Cannot set Endpoint Address for Unknown Port" + portName);
        }
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(javax.xml.namespace.QName portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        setEndpointAddress(portName.getLocalPart(), address);
    }

}
