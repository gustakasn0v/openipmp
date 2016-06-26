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
 * OsmsRegisterDigitalItemInstanceRequest.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.osms.server.ws.message;

public class OsmsRegisterDigitalItemInstanceRequest  implements java.io.Serializable {
    private java.lang.String auxDataXml;
    private java.lang.String keyXml;
    private java.lang.String metadataType;
    private java.lang.String metadataXml;

    public OsmsRegisterDigitalItemInstanceRequest() {
    }

    public OsmsRegisterDigitalItemInstanceRequest(
           java.lang.String auxDataXml,
           java.lang.String keyXml,
           java.lang.String metadataType,
           java.lang.String metadataXml) {
           this.auxDataXml = auxDataXml;
           this.keyXml = keyXml;
           this.metadataType = metadataType;
           this.metadataXml = metadataXml;
    }


    /**
     * Gets the auxDataXml value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @return auxDataXml
     */
    public java.lang.String getAuxDataXml() {
        return auxDataXml;
    }


    /**
     * Sets the auxDataXml value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @param auxDataXml
     */
    public void setAuxDataXml(java.lang.String auxDataXml) {
        this.auxDataXml = auxDataXml;
    }


    /**
     * Gets the keyXml value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @return keyXml
     */
    public java.lang.String getKeyXml() {
        return keyXml;
    }


    /**
     * Sets the keyXml value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @param keyXml
     */
    public void setKeyXml(java.lang.String keyXml) {
        this.keyXml = keyXml;
    }


    /**
     * Gets the metadataType value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @return metadataType
     */
    public java.lang.String getMetadataType() {
        return metadataType;
    }


    /**
     * Sets the metadataType value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @param metadataType
     */
    public void setMetadataType(java.lang.String metadataType) {
        this.metadataType = metadataType;
    }


    /**
     * Gets the metadataXml value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @return metadataXml
     */
    public java.lang.String getMetadataXml() {
        return metadataXml;
    }


    /**
     * Sets the metadataXml value for this OsmsRegisterDigitalItemInstanceRequest.
     * 
     * @param metadataXml
     */
    public void setMetadataXml(java.lang.String metadataXml) {
        this.metadataXml = metadataXml;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof OsmsRegisterDigitalItemInstanceRequest)) return false;
        OsmsRegisterDigitalItemInstanceRequest other = (OsmsRegisterDigitalItemInstanceRequest) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.auxDataXml==null && other.getAuxDataXml()==null) || 
             (this.auxDataXml!=null &&
              this.auxDataXml.equals(other.getAuxDataXml()))) &&
            ((this.keyXml==null && other.getKeyXml()==null) || 
             (this.keyXml!=null &&
              this.keyXml.equals(other.getKeyXml()))) &&
            ((this.metadataType==null && other.getMetadataType()==null) || 
             (this.metadataType!=null &&
              this.metadataType.equals(other.getMetadataType()))) &&
            ((this.metadataXml==null && other.getMetadataXml()==null) || 
             (this.metadataXml!=null &&
              this.metadataXml.equals(other.getMetadataXml())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        if (getAuxDataXml() != null) {
            _hashCode += getAuxDataXml().hashCode();
        }
        if (getKeyXml() != null) {
            _hashCode += getKeyXml().hashCode();
        }
        if (getMetadataType() != null) {
            _hashCode += getMetadataType().hashCode();
        }
        if (getMetadataXml() != null) {
            _hashCode += getMetadataXml().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(OsmsRegisterDigitalItemInstanceRequest.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("http://message.ws.server.osms.mutable.com", "OsmsRegisterDigitalItemInstanceRequest"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("auxDataXml");
        elemField.setXmlName(new javax.xml.namespace.QName("", "auxDataXml"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("keyXml");
        elemField.setXmlName(new javax.xml.namespace.QName("", "keyXml"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("metadataType");
        elemField.setXmlName(new javax.xml.namespace.QName("", "metadataType"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("metadataXml");
        elemField.setXmlName(new javax.xml.namespace.QName("", "metadataXml"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
