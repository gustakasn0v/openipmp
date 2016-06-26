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


package com.mutable.osms.common.io.message;

/**
 * <p>Title: osmsMessageCreateUserRequest</p>
 * <p>Description: </p>
 * @version 1.0
 */

public class osmsMessageCreateUserRequest extends osmsMessage
{
	//constructs
	public osmsMessageCreateUserRequest()
	{
		super(osmsMessage.osmsMESSAGE_CREATE_USER_REQUEST);
	}

	//bean properties
	private String m_UserName=null;
	public String getUserName(){return m_UserName;}
	public void setUserName(String UserName){m_UserName=UserName;}

	private String m_Password=null;
	public String getPassword(){return m_Password;}
	public void setPassword(String Password){m_Password=Password;}

	private String m_EmailAddress=null;
	public String getEmailAddress(){return m_EmailAddress;}
	public void setEmailAddress(String EmailAddress){m_EmailAddress=EmailAddress;}

	private String m_Salutation=null;
	public String getSalutation(){return m_Salutation;}
	public void setSalutation(String Salutation){m_Salutation=Salutation;}

	private String m_FirstName=null;
	public String getFirstName(){return m_FirstName;}
	public void setFirstName(String FirstName){m_FirstName=FirstName;}

	private String m_LastName=null;
	public String getLastName(){return m_LastName;}
	public void setLastName(String LastName){m_LastName=LastName;}

	private String m_Suffix=null;
	public String getSuffix(){return m_Suffix;}
	public void setSuffix(String Suffix){m_Suffix=Suffix;}

	private String m_SecretQuestion=null;
	public String getSecretQuestion(){return m_SecretQuestion;}
	public void setSecretQuestion(String SecretQuestion){m_SecretQuestion=SecretQuestion;}

	private String m_SecretAnswer=null;
	public String getSecretAnswer(){return m_SecretAnswer;}
	public void setSecretAnswer(String SecretAnswer){m_SecretAnswer=SecretAnswer;}

	private String m_OrganizationName=null;
	public String getOrganizationName(){return m_OrganizationName;}
	public void setOrganizationName(String OrganizationName){m_OrganizationName=OrganizationName;}

	private String m_OrganizationUnit=null;
	public String getOrganizationUnit(){return m_OrganizationUnit;}
	public void setOrganizationUnit(String OrganizationUnit){m_OrganizationUnit=OrganizationUnit;}

	private String m_MainPhoneNumber=null;
	public String getMainPhoneNumber(){return m_MainPhoneNumber;}
	public void setMainPhoneNumber(String MainPhoneNumber){m_MainPhoneNumber=MainPhoneNumber;}

	private String m_AltPhoneNumber=null;
	public String getAltPhoneNumber(){return m_AltPhoneNumber;}
	public void setAltPhoneNumber(String AltPhoneNumber){m_AltPhoneNumber=AltPhoneNumber;}

	private String m_FaxPhoneNumber=null;
	public String getFaxPhoneNumber(){return m_FaxPhoneNumber;}
	public void setFaxPhoneNumber(String FaxPhoneNumber){m_FaxPhoneNumber=FaxPhoneNumber;}


	private String m_AddressLine1=null;
	public String getAddressLine1(){return m_AddressLine1;}
	public void setAddressLine1(String AddressLine1){m_AddressLine1=AddressLine1;}

	private String m_AddressLine2=null;
	public String getAddressLine2(){return m_AddressLine2;}
	public void setAddressLine2(String AddressLine2){m_AddressLine2=AddressLine2;}

	private String m_AddressLine3=null;
	public String getAddressLine3(){return m_AddressLine3;}
	public void setAddressLine3(String AddressLine3){m_AddressLine3=AddressLine3;}

	private String m_City=null;
	public String getCity(){return m_City;}
	public void setCity(String City){m_City=City;}

	private String m_State=null;
	public String getState(){return m_State;}
	public void setState(String State){m_State=State;}

	private String m_ZipCode=null;
	public String getZipCode(){return m_ZipCode;}
	public void setZipCode(String ZipCode){m_ZipCode=ZipCode;}

	private String m_Country=null;
	public String getCountry(){return m_Country;}
	public void setCountry(String Country){m_Country=Country;}
}