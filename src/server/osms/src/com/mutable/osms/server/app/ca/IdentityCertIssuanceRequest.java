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


package com.mutable.osms.server.app.ca;

/**
 * Title:        CA Test 1
 * Description:  Encapsulate the data necessary to complete an ID Cert issuance req
 * @version 1.0
 */
import java.util.Date;

public class IdentityCertIssuanceRequest
{
  /**
   * instance data
   */
  private String m_UserName;
  private String m_Password;
//  private Date m_NotBefore;
//  private Date m_NotAfter;
  private String m_EmailAddr;

  public IdentityCertIssuanceRequest()
  {
  }

  /** setUserName
   *  sets the user name on the request object
   *  @param String
   *  @return void
   */
  public void setUserName(String p_Name)
  {
    m_UserName = p_Name;
  }
  /**
   * getUserName
   * returns the user name
   * @param void
   * @return String
   */
  public String getUserName()
  {
    return m_UserName;
  }

  /**
   * setPassword
   * sets the password for this request
   * @param String
   * @return void
   */
  public void setPassword(String p_Password)
  {
    m_Password = p_Password;
  }

  /**
   * getPassword
   * return the password for this request
   * @param void
   * @return String
   */
  public String getPassword()
  {
    return m_Password;
  }

  /** setNotBefore
   *  @param Date
   *  @return void
   */
/*
  public void setNotBefore(Date p_Date)
  {
      m_NotBefore = p_Date;
  }
  public Date getNotBefore()
  {
    return m_NotBefore;
  }
  public void setNotAfter(Date p_Date)
  {
    m_NotAfter = p_Date;
  }
  public Date getNotAfter()
  {
    return m_NotAfter;
  }
*/
  /**
   * set email addr
   */
  public void setEmailAddr(String p_Email)
  {
    m_EmailAddr = p_Email;
  }

  /**
   * get email addr
   */
  public String getEmailAddr()
  {
    return m_EmailAddr;
  }

}