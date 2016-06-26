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

package com.mutable.osms.server.ws;

import com.mutable.osms.server.ws.message.*;
import com.mutable.osms.common.io.message.*;

/**
 * class OsmsMessageTranslator
 * -> for com.mutable.osms.server.ws.message <-> com.mutable.osms.common.io.message
 *    message translation   
 */

public class OsmsMessageTranslator {
	
	public static OsmsUserLoginFault convert(osmsMessageUserLoginResponseError msg) {
		return new OsmsUserLoginFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageUserLoginRequest convert(OsmsUserLoginRequest msg) {
		osmsMessageUserLoginRequest req = new osmsMessageUserLoginRequest();
		req.setUserName(msg.getUserName());
		req.setPassword(msg.getPassword());
		return req;
	}
	public static OsmsUserLoginResponse convert(osmsMessageUserLoginResponse msg) {
		OsmsUserLoginResponse rsp = new OsmsUserLoginResponse();
		rsp.setResponseString(msg.getResponseString());
		return rsp;
	}
	
	public static OsmsUserLogoutFault convert(osmsMessageUserLogoutResponseError msg) {
		return new OsmsUserLogoutFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageUserLogoutRequest convert(OsmsUserLogoutRequest msg) {
		return new osmsMessageUserLogoutRequest();
	}
	public static OsmsUserLogoutResponse convert(osmsMessageUserLogoutResponse msg) {
		OsmsUserLogoutResponse rsp = new OsmsUserLogoutResponse();
		rsp.setResponseString(msg.getResponseString());
		return rsp;
	}

	public static OsmsCreateUserFault convert(osmsMessageCreateUserResponseError msg) {
		return new OsmsCreateUserFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageCreateUserRequest convert(OsmsCreateUserRequest msg) {
		osmsMessageCreateUserRequest req = new osmsMessageCreateUserRequest();
		req.setAddressLine1(msg.getAddressLine1());
		req.setAddressLine2(msg.getAddressLine2());
		req.setAddressLine3(msg.getAddressLine3());
		req.setAltPhoneNumber(msg.getAltPhoneNumber());
		req.setCity(msg.getCity());
		req.setCountry(msg.getCountry());
		req.setEmailAddress(msg.getEmailAddress());
		req.setFaxPhoneNumber(msg.getFaxPhoneNumber());
		req.setFirstName(msg.getFirstName());
		req.setLastName(msg.getLastName());
		req.setMainPhoneNumber(msg.getMainPhoneNumber());
		req.setOrganizationName(msg.getOrganizationName());
		req.setOrganizationUnit(msg.getOrganizationUnit());
		req.setPassword(msg.getPassword());
		req.setSalutation(msg.getSalutation());
		req.setSecretAnswer(msg.getSecretAnswer());
		req.setSecretQuestion(msg.getSecretQuestion());
		req.setSuffix(msg.getSuffix());
		req.setUserName(msg.getUserName());
		req.setZipCode(msg.getZipCode());
		return req;
	}
	public static OsmsCreateUserResponse convert(osmsMessageCreateUserResponse msg) {
		OsmsCreateUserResponse rsp = new OsmsCreateUserResponse();
		rsp.setResponseString(msg.getResponseString());
		return rsp;
	}

	public static OsmsGetContentKeyFault convert(osmsMessageGetContentKeyResponseError msg) {
		return new OsmsGetContentKeyFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageGetContentKeyRequest convert(OsmsGetContentKeyRequest msg) {
		osmsMessageGetContentKeyRequest req = new osmsMessageGetContentKeyRequest();
		req.setDigitalItemInstanceId(msg.getDigitalItemInstanceId());
		req.setMetadataType(msg.getMetadataType());
		return req;
	}
	public static OsmsGetContentKeyResponse convert(osmsMessageGetContentKeyResponse msg) {
		OsmsGetContentKeyResponse rsp = new OsmsGetContentKeyResponse();
		rsp.setAuxDataXml(msg.getAuxDataXml());
		rsp.setKeyXml(msg.getKeyXml());
		return rsp;
	}
	
	public static OsmsLicenseFault convert(osmsMessageLicenseResponseError msg) {
		return new OsmsLicenseFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageLicenseRequest convert(OsmsLicenseRequest msg) {
		osmsMessageLicenseRequest req = new osmsMessageLicenseRequest();
		req.setContentId(msg.getContentId());
		req.setRightsInfo(msg.getRightsInfo());
		return req;
	}
	public static OsmsLicenseResponse convert(osmsMessageLicenseResponse msg) {
		OsmsLicenseResponse rsp = new OsmsLicenseResponse();
		rsp.setLicense(msg.getLicense());
		return rsp;
	}

	public static OsmsQueryFault convert(osmsMessageResponseError msg) { // note the type is osmsMessageResponseError, not osmsMessageQueryResponseError
		return new OsmsQueryFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageQueryRequest convert(OsmsQueryRequest msg) {
		osmsMessageQueryRequest req = new osmsMessageQueryRequest();
		req.setType(msg.getType());
		return req;
	}
	public static OsmsQueryResponse convert(osmsMessageQueryResponse msg) {
		OsmsQueryResponse rsp = new OsmsQueryResponse();
		rsp.setHeading(msg.getHeading());
		rsp.setLength(msg.getLength());
		rsp.setResults(msg.getResults());
		return rsp;
	}

	public static OsmsRegisterContentAssignIdentifierFault convert(osmsMessageRegisterContentAssignIdentifierResponseError msg) {
		return new OsmsRegisterContentAssignIdentifierFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageRegisterContentAssignIdentifierRequest convert(OsmsRegisterContentAssignIdentifierRequest msg) {
		osmsMessageRegisterContentAssignIdentifierRequest req = new osmsMessageRegisterContentAssignIdentifierRequest();
		req.setMetadataType(msg.getMetadataType());
		req.setMetadataXml(msg.getMetadataXml());
		return req;
	}
	public static OsmsRegisterContentAssignIdentifierResponse convert(osmsMessageRegisterContentAssignIdentifierResponse msg) {
		OsmsRegisterContentAssignIdentifierResponse rsp = new OsmsRegisterContentAssignIdentifierResponse();
		rsp.setMetadataType(msg.getMetadataType());
		rsp.setMetadataXml(msg.getMetadataXml());
		return rsp;
	}

	public static OsmsRegisterContentExistingIdentifierFault convert(osmsMessageRegisterContentExistingIdentifierResponseError msg) {
		return new OsmsRegisterContentExistingIdentifierFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageRegisterContentExistingIdentifierRequest convert(OsmsRegisterContentExistingIdentifierRequest msg) {
		osmsMessageRegisterContentExistingIdentifierRequest req = new osmsMessageRegisterContentExistingIdentifierRequest();
		req.setMetadataType(msg.getMetadataType());
		req.setMetadataXml(msg.getMetadataXml());
		return req;
	}
	public static OsmsRegisterContentExistingIdentifierResponse convert(osmsMessageRegisterContentExistingIdentifierResponse msg) {
		OsmsRegisterContentExistingIdentifierResponse rsp = new OsmsRegisterContentExistingIdentifierResponse();
		rsp.setResponseString(msg.getResponseString());
		return rsp;
	}
	
	public static OsmsRegisterDigitalItemInstanceFault convert(osmsMessageRegisterDigitalItemInstanceResponseError msg) {
		return new OsmsRegisterDigitalItemInstanceFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageRegisterDigitalItemInstanceRequest convert(OsmsRegisterDigitalItemInstanceRequest msg) {
		osmsMessageRegisterDigitalItemInstanceRequest req = new osmsMessageRegisterDigitalItemInstanceRequest();
		req.setAuxDataXml(msg.getAuxDataXml());
		req.setKeyXml(msg.getKeyXml());
		req.setMetadataType(msg.getMetadataType());
		req.setMetadataXml(msg.getMetadataXml());
		return req;
	}
	public static OsmsRegisterDigitalItemInstanceResponse convert(osmsMessageRegisterDigitalItemInstanceResponse msg) {
		OsmsRegisterDigitalItemInstanceResponse rsp = new OsmsRegisterDigitalItemInstanceResponse();
		rsp.setAuxDataXml(msg.getAuxDataXml());
		rsp.setMetadataType(msg.getMetadataType());
		rsp.setMetadataXml(msg.getMetadataXml());
		rsp.setSignatureXml(msg.getSignatureXml());
		return rsp;
	}

	public static OsmsRegisterUserFault convert(osmsMessageRegisterUserResponseError msg) {
		return new OsmsRegisterUserFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageRegisterUserRequest convert(OsmsRegisterUserRequest msg) {
		osmsMessageRegisterUserRequest req = new osmsMessageRegisterUserRequest();
		req.setEmailAddress(msg.getEmailAddress());
		req.setPassword(msg.getPassword());
		req.setPasswordConfirm(msg.getPasswordConfirm());
		req.setUserName(msg.getUserName());
		return req;
	}
	public static OsmsRegisterUserResponse convert(osmsMessageRegisterUserResponse msg) {
		OsmsRegisterUserResponse rsp = new OsmsRegisterUserResponse();
		rsp.setUserName(msg.getUserName());
		rsp.setUserSecurityStore(msg.getUserSecurityStore());
		return rsp;
	}		

	public static OsmsRightsAuthorizationFault convert(osmsMessageRightsAuthorizationResponseError msg) {
		return new OsmsRightsAuthorizationFault(msg.getErrorCode(), msg.getResponseString());
	}
	public static osmsMessageRightsAuthorizationRequest convert(OsmsRightsAuthorizationRequest msg) {
		osmsMessageRightsAuthorizationRequest req = new osmsMessageRightsAuthorizationRequest();
		req.setContentId(msg.getContentId());
		req.setEndDate(msg.getEndDate());
		req.setLicenseType(msg.getLicenseType());
		req.setStartDate(msg.getStartDate());
		req.setUserName(msg.getUserName());
		return req;
	}
	public static OsmsRightsAuthorizationResponse convert(osmsMessageRightsAuthorizationResponse msg) {
		OsmsRightsAuthorizationResponse rsp = new OsmsRightsAuthorizationResponse();
		rsp.setTransactionId(msg.getTransactionId());
		return rsp;
	}
}
