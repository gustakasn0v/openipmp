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
 * Authenticate.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.sony.spe.cinedrm.webservices;

public interface Authenticate extends javax.xml.rpc.Service {
    public java.lang.String getAuthenticateSoapAddress();

    public com.sony.spe.cinedrm.webservices.AuthenticateSoap getAuthenticateSoap() throws javax.xml.rpc.ServiceException;

    public com.sony.spe.cinedrm.webservices.AuthenticateSoap getAuthenticateSoap(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
}
