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

package com.mutable.osms.server.ws.message;

public class OsmsCreateUserRequest implements java.io.Serializable {
	private String userName = null;
	private String password = null;
	private String emailAddress = null;
	private String salutation = null;
	private String firstName = null;
	private String lastName = null;
	private String suffix = null;
	private String secretQuestion = null;
	private String secretAnswer = null;
	private String organizationName = null;
	private String organizationUnit = null;
	private String mainPhoneNumber = null;
	private String altPhoneNumber = null;
	private String faxPhoneNumber = null;
	private String addressLine1 = null;
	private String addressLine2 = null;
	private String addressLine3 = null;
	private String city = null;
	private String state = null;
	private String zipCode = null;
	private String country = null;
	
	public OsmsCreateUserRequest(String line1, String line2, String line3, String number, String city, String country, String address, String number2, String name, String name2, String number3, String name3, String unit, String password, String salutation, String answer, String question, String state, String suffix, String name4, String code) {
		addressLine1 = line1;
		addressLine2 = line2;
		addressLine3 = line3;
		altPhoneNumber = number;
		this.city = city;
		this.country = country;
		emailAddress = address;
		faxPhoneNumber = number2;
		firstName = name;
		lastName = name2;
		mainPhoneNumber = number3;
		organizationName = name3;
		organizationUnit = unit;
		this.password = password;
		this.salutation = salutation;
		secretAnswer = answer;
		secretQuestion = question;
		this.state = state;
		this.suffix = suffix;
		userName = name4;
		zipCode = code;
	}

	public OsmsCreateUserRequest() {
	}

	public String getAddressLine1() {
		return addressLine1;
	}

	public void setAddressLine1(String addressLine1) {
		this.addressLine1 = addressLine1;
	}

	public String getAddressLine2() {
		return addressLine2;
	}

	public void setAddressLine2(String addressLine2) {
		this.addressLine2 = addressLine2;
	}

	public String getAddressLine3() {
		return addressLine3;
	}

	public void setAddressLine3(String addressLine3) {
		this.addressLine3 = addressLine3;
	}

	public String getAltPhoneNumber() {
		return altPhoneNumber;
	}

	public void setAltPhoneNumber(String altPhoneNumber) {
		this.altPhoneNumber = altPhoneNumber;
	}

	public String getCity() {
		return city;
	}

	public void setCity(String city) {
		this.city = city;
	}

	public String getCountry() {
		return country;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	public String getEmailAddress() {
		return emailAddress;
	}

	public void setEmailAddress(String emailAddress) {
		this.emailAddress = emailAddress;
	}

	public String getFaxPhoneNumber() {
		return faxPhoneNumber;
	}

	public void setFaxPhoneNumber(String faxPhoneNumber) {
		this.faxPhoneNumber = faxPhoneNumber;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getMainPhoneNumber() {
		return mainPhoneNumber;
	}

	public void setMainPhoneNumber(String mainPhoneNumber) {
		this.mainPhoneNumber = mainPhoneNumber;
	}

	public String getOrganizationName() {
		return organizationName;
	}

	public void setOrganizationName(String organizationName) {
		this.organizationName = organizationName;
	}

	public String getOrganizationUnit() {
		return organizationUnit;
	}

	public void setOrganizationUnit(String organizationUnit) {
		this.organizationUnit = organizationUnit;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getSalutation() {
		return salutation;
	}

	public void setSalutation(String salutation) {
		this.salutation = salutation;
	}

	public String getSecretAnswer() {
		return secretAnswer;
	}

	public void setSecretAnswer(String secretAnswer) {
		this.secretAnswer = secretAnswer;
	}

	public String getSecretQuestion() {
		return secretQuestion;
	}

	public void setSecretQuestion(String secretQuestion) {
		this.secretQuestion = secretQuestion;
	}

	public String getState() {
		return state;
	}

	public void setState(String state) {
		this.state = state;
	}

	public String getSuffix() {
		return suffix;
	}

	public void setSuffix(String suffix) {
		this.suffix = suffix;
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public String getZipCode() {
		return zipCode;
	}

	public void setZipCode(String zipCode) {
		this.zipCode = zipCode;
	}
}
