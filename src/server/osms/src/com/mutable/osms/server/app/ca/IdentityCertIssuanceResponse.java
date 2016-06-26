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
 * Title:        IdentityCertIssuanceRespose
 * Description:  Encapsulate the data necessary to complete an ID Cert issuance response
 * @version 1.0
 */

import java.security.cert.Certificate;
import java.security.KeyStore;
import java.security.KeyPair;

public class IdentityCertIssuanceResponse
{
  /** instance data */
  private Certificate m_Certificate;
//  private byte[] m_EncodedCertificate;
//  private byte[] m_EncryptedSecretKey;
//  private String m_CertificateChain;
  private KeyStore m_UserSecurityStore;
//  private int m_ESKId;

  public IdentityCertIssuanceResponse()
  {
  }

  /**
   * setCertificate
   * @param Certificate
   * @return void
   */
  public void setCertificate(Certificate p_Cert)
  {
    m_Certificate = p_Cert;
  }

  /**
   * getCertificate
   * @param void
   * @return Certificate
   */
  public Certificate getCertificate()
  {
    return m_Certificate;
  }

  /**
   * setEncodedCertificate - sets ASN.1 DER-encoded Cert
   * @param byte[]
   * @return void
   */
//  public void setEncodedCertificate(byte[] p_Cert)
//  {
//    m_EncodedCertificate = p_Cert;
//  }

  /**
   * getEncodedCertificate - returns an ASN.1 DER-encoded Cert
   * @param void
   * @return byte[]
   */
//  public byte[] getEncodedCertificate()
//  {
//    return m_EncodedCertificate;
//  }

  /**
   * setEncryptedSecretKey
   * @param byte[]
   * @return void
   */
/*
  public void setEncryptedSecretKey(byte[] p_Key)
  {
    m_EncryptedSecretKey = p_Key;
  }

  public byte[] getEncryptedSecretKey()
  {
    return m_EncryptedSecretKey;
  }
*/
  /**
   * setUserSecurityStore - set the PKCS12 structure that contains the user's signed certificate, certificate chain,
   * and private key.  The PKCS12 structure itself is encrypted with the user's password.
   */
  public void setUserSecurityStore(KeyStore p_Store)
  {
    m_UserSecurityStore = p_Store;
  }

  /**
   * getUserSecurityStore - return an encoded PKCS12 structure containing the users' security information
   */
  public KeyStore getUserSecurityStore()
  {
    return m_UserSecurityStore;
  }


  KeyPair m_KeyPair;
  public void  setKeyPair(KeyPair p_KeyPair)
  {
	  m_KeyPair=p_KeyPair;
  }
  public KeyPair getKeyPair()
  {
	  return m_KeyPair;
  }


  /**
   * set encrypted secret key id
   */
//  public void setESKId(int p_Id)
//  {
//    m_ESKId = p_Id;
//  }

  /**
   * get ecrypted secret key id
   */
//  public int getESKId()
//  {
//    return m_ESKId;
//  }


}