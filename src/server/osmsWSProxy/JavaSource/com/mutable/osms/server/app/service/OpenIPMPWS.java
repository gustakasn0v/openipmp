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
 * OpenIPMPWS.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2.1 Jun 14, 2005 (09:15:57 EDT) WSDL2Java emitter.
 */

package com.mutable.osms.server.app.service;

public interface OpenIPMPWS extends java.rmi.Remote {
    public void ping() throws java.rmi.RemoteException;
    public int login(java.lang.String userName, java.lang.String passwd) throws java.rmi.RemoteException;
    public int packageSecureContentWithParams(java.lang.String agentUserName, java.lang.String agentPassword, java.lang.String sourceFileURL, java.lang.String destinationFileURL, java.lang.String contentOwnerAppId, java.lang.String contentOwnerUserId, java.lang.String transactionID, java.lang.String validityStartDate, java.lang.String validityEndDate, int validityDays, int validityPlaycount, java.lang.String[] grantUsers) throws java.rmi.RemoteException;
    public int packageSecureContentWithParamsForSingleUser(java.lang.String agentUserName, java.lang.String agentPassword, java.lang.String sourceFileURL, java.lang.String destinationFileURL, java.lang.String contentOwnerAppId, java.lang.String contentOwnerUserId, java.lang.String transactionID, java.lang.String validityStartDate, java.lang.String validityEndDate, int validityDays, int validityPlaycount, java.lang.String grantUser) throws java.rmi.RemoteException;
    public int packageSecureContentWithMPEG_REL(java.lang.String agentUserName, java.lang.String agentPassword, java.lang.String contentOwnerAppId, java.lang.String contentOwnerUserId, java.lang.String transactionID, java.lang.String mpegREL) throws java.rmi.RemoteException;
}
