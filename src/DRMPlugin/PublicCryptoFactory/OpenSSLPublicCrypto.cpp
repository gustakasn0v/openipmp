/**	\file OpenSSLPublicCrypto.cpp

	OpenSSL public crypto implementations.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	
*/

#include "OpenSSLPublicCrypto.h"
#include <sys/stat.h>

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Get certificate expiraton time as UTC time.

    \param  cert      input, X509 certificate.

    \returns  Certificate expiraton time as UTC time. If fails,
              throws PublicCryptoException.
*/
static UTCTime GetExpirationTimeAsUTC(X509* cert) {
  if (cert == 0) {
    throw PublicCryptoException();
  }
  ASN1_TIME* t = X509_get_notAfter(cert);
  ASN1_GENERALIZEDTIME* gt = ASN1_TIME_to_generalizedtime(t, NULL);

  char* tt = (char*)gt->data;
  char* ret = (char*)malloc(21);

  ret[0] = tt[0]; ret[1] = tt[1]; ret[2] = tt[2]; ret[3] = tt[3];
  ret[4] = '-';
  ret[5] = tt[4]; ret[6] = tt[5];
  ret[7] = '-';
  ret[8] = tt[6]; ret[9] = tt[7];
  ret[10] = 'T';
  ret[11] = tt[8]; ret[12] = tt[9];
  ret[13] = ':';
  ret[14] = tt[10]; ret[15] = tt[11];
  ret[16] = ':';
  ret[17] = tt[12]; ret[18] = tt[13];
  ret[19] = 'Z';
  ret[20] = '\0';

  M_ASN1_GENERALIZEDTIME_free(gt);

  UTCTime utc(ret);
  free(ret);
  return utc;
}

/*! \brief  MD5 hash calculator.
*/
/*! \brief  Calculate hash.

    \param  data          input, data to be hashed.
    \param  hash          output, hash of data.

    \returns  Boolean indicating success or failure.
*/
bool MD5OpenSSLHasher::Hash(const ByteSeq& data, ByteSeq& hash) {
  ByteT *hhash = (ByteT*)malloc(EVP_md5()->md_size);
  if (hhash  == NULL) {
    return false;
  }
  int ret = 1;
  unsigned int hashlen = 0;
  ret = EVP_Digest((void*)data.GetFirst(), (unsigned int)data.GetLength(),
    hhash, &hashlen, EVP_md5(), /* ENGINE *impl */ 0);
  if (ret != 1) {
    free(hhash );
    return false;
  }
  hash = ByteSeq(hhash, hashlen);
  free(hhash);

  return true;
}

/*! \brief  SHA1 hash calculator.
*/
/*! \brief  Calculate hash.

    \param  data          input, data to be hashed.
    \param  hash          output, hash of data.

    \returns  Boolean indicating success or failure.
*/
bool SHA1OpenSSLHasher::Hash(const ByteSeq& data, ByteSeq& hash) {
  ByteT *hhash = (ByteT*)malloc(EVP_sha1()->md_size);
  if (hhash  == NULL) {
    return false;
  }
  int ret = 1;
  unsigned int hashlen = 0;
  ret = EVP_Digest((void*)data.GetFirst(), (unsigned int)data.GetLength(),
    hhash, &hashlen, EVP_sha1(), /* ENGINE *impl */ 0);
  if (ret != 1) {
    free(hhash );
    return false;
  }
  hash = ByteSeq(hhash, hashlen);
  free(hhash);

  return true;
}

/*! \brief  Encrypt data.

    \param  pkey            input, public key.
    \param  data            input, data to encrypt.
    \param  enc             output, encrypted data.

    \returns  Boolean indicating success or failure.
*/
static bool RSAMD5OpenSSLEncrypt(EVP_PKEY* pkey, const ByteSeq& data, ByteSeq& enc) {
  ByteT* dta = (ByteT*)data.GetFirst();
  unsigned int dtalen = (unsigned int)data.GetLength();
  enc = ByteSeq();
  ByteT* encdata = 0;
  while (dtalen >= (unsigned int)(RSA_size(pkey->pkey.rsa) - RSA_PKCS1_PADDING_SIZE)) {
    if ((encdata = (ByteT*)malloc(RSA_size(pkey->pkey.rsa))) == NULL) {
      return false;
    }
    int enclen = RSA_public_encrypt(RSA_size(pkey->pkey.rsa) - RSA_PKCS1_PADDING_SIZE,
      dta, encdata, pkey->pkey.rsa, RSA_PKCS1_PADDING);
    //  how to check failure?
    if (enclen <= 0) {
      free(encdata);
      return false;
    }
    enc += ByteSeq(encdata, (unsigned int)enclen);
    free(encdata);
    dtalen -= (RSA_size(pkey->pkey.rsa) - RSA_PKCS1_PADDING_SIZE);
    dta += (RSA_size(pkey->pkey.rsa) - RSA_PKCS1_PADDING_SIZE);
  }
  if ((encdata = (ByteT*)malloc(RSA_size(pkey->pkey.rsa))) == NULL) {
    return false;
  }
  int enclen = RSA_public_encrypt(dtalen, dta, encdata, pkey->pkey.rsa,
    RSA_PKCS1_PADDING);
  //  how to check failure?
  if (enclen <= 0) {
    free(encdata);
    return false;
  }
  enc += ByteSeq(encdata, (unsigned int)enclen);
  free(encdata);
  return true;
}

/*! \brief  Decrypt data.

    \param  pkey            input, private key.
    \param  data            input, data to decrypt.
    \param  dec             output, decrypted data.

    \returns  Boolean indicating success or failure.
*/
static bool RSAMD5OpenSSLDecrypt(EVP_PKEY* pkey, const ByteSeq& data, ByteSeq& dec) {
  ByteT* dta = (ByteT*)data.GetFirst();
  unsigned int dtalen = (unsigned int)data.GetLength();
  dec = ByteSeq();
  ByteT* decdata = 0;
  while (dtalen > 0) {
    if ((decdata = (ByteT*)malloc(RSA_size(pkey->pkey.rsa))) == NULL) {
      return false;
    }
    int declen = RSA_private_decrypt(RSA_size(pkey->pkey.rsa), dta, decdata,
      pkey->pkey.rsa, RSA_PKCS1_PADDING);
    //  how to check failure?
    if (declen <= 0) {
      free(decdata);
      return false;
    }
    dec += ByteSeq(decdata, (unsigned int)declen);
    free(decdata);
    dtalen -= RSA_size(pkey->pkey.rsa);
    dta += RSA_size(pkey->pkey.rsa);
  }
  return true;
}

/*! \brief  Sign data.

    \param  pkey            input, private key.
    \param  data            input, hash of data to be signed.
    \param  sig             output, signature data.

    \returns  Boolean indicating success or failure.
*/
static bool RSAMD5OpenSSLSign(EVP_PKEY* pkey, const ByteSeq& data, ByteSeq& sig) {
  ByteT* sigret = (ByteT*)malloc(RSA_size(pkey->pkey.rsa));
  unsigned int siglen = 0;
  if (RSA_sign(NID_md5, (ByteT*)data.GetFirst(), (unsigned int)data.GetLength(),
      sigret, &siglen, pkey->pkey.rsa) != 1) {
    free(sigret);
    return false;
  }
  sig = ByteSeq(sigret, siglen);
  free(sigret);

  return true;
}

/*! \brief  Verify signature.

    \param  pkey            input, public key.
    \param  sigValue        input, signature value.
    \param  data            input, signed hash.

    \returns  Boolean indicating success or failure.
*/
static bool RSAMD5OpenSSLVerify(EVP_PKEY* pkey, const ByteSeq& sigValue, const ByteSeq& data) {
  return (RSA_verify(NID_md5, (ByteT*)data.GetFirst(), (unsigned int)data.GetLength(),
    (ByteT*)sigValue.GetFirst(), (unsigned int)sigValue.GetLength(),
    pkey->pkey.rsa) == 1);
}

/*! \brief  Encode as byte array.

    \param  pkey          input, public key.
    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
static bool RSAMD5OpenSSLPublicKeyEncode(EVP_PKEY* pkey, ByteSeq& encoded) {
  int dersize = i2d_PublicKey(pkey, NULL);
  if (dersize <= 0) {
    return false;
  }
  ByteT* der = (ByteT*)malloc((unsigned int)dersize);
  if (der == NULL) {
    return false;
  }
  ByteT* tmp = der;
  dersize = i2d_PublicKey(pkey, &tmp);
  encoded = ByteSeq(der, dersize);
  free(der);
  return true;
}

/*! \brief  Encode as byte array.

    \param  pkey          input, private key.
    \param  encoded       output, encoded byte array.

    \returns  Boolean indicating success or failure.
*/
static bool RSAMD5OpenSSLPrivateKeyEncode(EVP_PKEY* pkey, ByteSeq& encoded) {
  int dersize = i2d_PrivateKey(pkey, NULL);
  if (dersize <= 0) {
    return false;
  }
  ByteT* der = (ByteT*)malloc((unsigned int)dersize);
  if (der == NULL) {
    return false;
  }
  ByteT* tmp = der;
  dersize = i2d_PrivateKey(pkey, &tmp);
  encoded = ByteSeq(der, dersize);
  free(der);
  return true;
}

/*! \brief  Parse X509 certificate from input data.

    \param  data        input, data.
    \param  datalen     input, data length.

    \returns  New X509 structure. If fails, 0.
*/
X509* ParseX509CertFromData(ByteT* data, unsigned int datalen) {
  return d2i_X509(NULL, &data, datalen);
}

/*! \brief  Parse X509 certificate from a file.

    \param  fname       input, file name.

    \returns  New X509 structure. If fails, 0.
*/
X509* ParseX509CertFromFile(const std::string& fname) {
  FILE* fp = fopen(fname.data(), "rb");
  if (fp == NULL) {
    return 0;
  }
  struct stat tstat;
  stat(fname.data(), &tstat);
  unsigned int byteslen = tstat.st_size;
  ByteT* bytes = (ByteT*)malloc(byteslen);
  fread(bytes, byteslen, 1, fp);
  fclose(fp);
  X509* ret = ParseX509CertFromData(bytes, byteslen);
  free(bytes);
  return ret;
}

/*! \brief  Certificate verifier helper routine for cleaning X509 stack
    
    \param  sk        input-output, X509 stack.
*/
static void cleanX509Stack(STACK_OF(X509)* sk) {
  if (sk == NULL) {
    return;
  }
  for (int i = 0; i < sk_X509_num(sk); i++) {
    if (sk_X509_value(sk, i) != NULL) {
			X509_free(sk_X509_value(sk, i));
    }
  }
	sk_free(sk);
}

/*! \brief  Verify certificate chain.

    Assume that the chain starts with a certificate issued by root.
    If successful, return last certificate.

    \param  root        input, root certificate.
    \param  chain       input, certificate chain, ending with certificate
                        to verify.
    \param  logger      input, message logger.

    \returns  Last certificate. If zero, failed.
*/
static X509* OpenSSLVerifyChain(const ByteSeq& root, const std::vector<ByteSeq>& chain, DRMLogger& logger) {
  //  First parse the root certificate.
  X509* cert = ParseX509CertFromData((ByteT*)root.GetFirst(), (unsigned int)root.GetLength());
  if (cert == 0) {
    logger.UpdateLog("OpenSSLVerifyChain: parse root certificate failed...");
    return 0;
  }
  if (chain.size() == 0) {
    X509_free(cert);
    logger.UpdateLog("OpenSSLVerifyChain: empty certificate chain...");
    return 0;
  }

  STACK_OF(X509)* trusted = sk_X509_new_null();
  sk_X509_push(trusted, cert);

  STACK_OF(X509)* untrusted = sk_X509_new_null();
  unsigned int i = 0;
  for (i = 0; i < (chain.size() - 1); i++) {
    cert = ParseX509CertFromData((ByteT*)chain[i].GetFirst(),
      (unsigned int)chain[i].GetLength());
    if (cert == 0) {
      logger.UpdateLog("OpenSSLVerifyChain: parse intermediate certificate failed...");
      cleanX509Stack(trusted);
      cleanX509Stack(untrusted);
      return 0;
    }
    sk_X509_push(untrusted, cert);
  }
  //  Last certificate in the chain is the one we want to verify.
  cert = ParseX509CertFromData((ByteT*)chain[i].GetFirst(),
    (unsigned int)chain[i].GetLength());
  if (cert == 0) {
    logger.UpdateLog("OpenSSLVerifyChain: parse verified certificate failed...");
    cleanX509Stack(trusted);
    cleanX509Stack(untrusted);
    return 0;
  }

  X509_STORE* store = X509_STORE_new();
  X509_STORE_CTX* storectx = X509_STORE_CTX_new();
  if (X509_STORE_CTX_init(storectx, store, NULL, NULL) != 1) {
    cleanX509Stack(trusted);
    cleanX509Stack(untrusted);
    X509_free(cert);
    return 0;
  }

  X509_STORE_CTX_set_cert(storectx, cert);
  X509_STORE_CTX_trusted_stack(storectx, trusted);
  X509_STORE_CTX_set_chain(storectx, untrusted);
	OpenSSL_add_all_algorithms();
  if (X509_verify_cert(storectx) != 1) {
    const char* err = X509_verify_cert_error_string(storectx->error);
    logger.UpdateLog("OpenSSLVerifyChain: " + std::string(err) + "...");
    cleanX509Stack(trusted);
    cleanX509Stack(untrusted);
    X509_free(cert);
    X509_STORE_free(store);
    X509_STORE_CTX_free(storectx);
    return 0;
  }

  cleanX509Stack(trusted);
  cleanX509Stack(untrusted);
  X509_STORE_free(store);
  X509_STORE_CTX_free(storectx);

  return cert;
}

/*! \brief  RSAMD5 public key encryptor and verifier.
*/
/*! \brief  Constructor.

    \param  key       public key.

    If fails, throws PublicCryptoException.
*/
RSAMD5OpenSSLPublicEncryptorVerifier::RSAMD5OpenSSLPublicEncryptorVerifier(
    EVP_PKEY* key): pkey(key), hasher(new MD5OpenSSLHasher()) {
  if (pkey == 0) {
    throw PublicCryptoException();
  }
  if (pkey->pkey.rsa == 0) {
    throw PublicCryptoException();
  }
}

RSAMD5OpenSSLPublicEncryptorVerifier::~RSAMD5OpenSSLPublicEncryptorVerifier() {
  if (pkey != 0) EVP_PKEY_free(pkey); pkey = 0;
  if (hasher != 0) delete hasher; hasher = 0;
}

/*! \brief  Encode as byte array.

    \param  out         output, encoded data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicEncryptorVerifier::Encode(ByteSeq& out) {
  return RSAMD5OpenSSLPublicKeyEncode(pkey, out);
}

/*! \brief  Encrypt data.

    \param  in          input, data to encrypt.
    \param  out         output, encrypted data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicEncryptorVerifier::Encrypt(const ByteSeq& in, ByteSeq& out) {
  return RSAMD5OpenSSLEncrypt(pkey, in, out);
}

/*! \brief  Get hash calculator.

    \returns  Hash calculator.
*/
IHasher* RSAMD5OpenSSLPublicEncryptorVerifier::GetHasher() {
  return hasher;
}

/*! \brief  Verify signature.

    \param  in          input, data to verify.
    \param  sig         input, signature data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicEncryptorVerifier::Verify(const ByteSeq& in, const ByteSeq& sig) {
  ByteSeq hash;
  if (hasher->Hash(in, hash) == false) {
    return false;
  }
  return RSAMD5OpenSSLVerify(pkey, sig, hash);
}

/*! \brief  RSAMD5 public key decryptor and signer.
*/
/*! \brief  Constructor.

    \param  key       public key.

    If fails, throws PublicCryptoException.
*/
RSAMD5OpenSSLPublicDecryptorSigner::RSAMD5OpenSSLPublicDecryptorSigner(EVP_PKEY* key):
    pkey(key), hasher(new MD5OpenSSLHasher()) {
  if (pkey == 0) {
    throw PublicCryptoException();
  }
  if (pkey->pkey.rsa == 0) {
    throw PublicCryptoException();
  }
}

RSAMD5OpenSSLPublicDecryptorSigner::~RSAMD5OpenSSLPublicDecryptorSigner() {
  if (pkey != 0) EVP_PKEY_free(pkey); pkey = 0;
  if (hasher != 0) delete hasher; hasher = 0;
}

/*! \brief  Encode as byte array.

    \param  out         output, encoded data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicDecryptorSigner::Encode(ByteSeq& out) {
  return RSAMD5OpenSSLPublicKeyEncode(pkey, out);
}

/*! \brief  Encrypt data.

    \param  in          input, data to encrypt.
    \param  out         output, encrypted data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicDecryptorSigner::Encrypt(const ByteSeq& in, ByteSeq& out) {
  return RSAMD5OpenSSLEncrypt(pkey, in, out);
}

/*! \brief  Decrypt data.

    \param  in          input, data to decrypt.
    \param  out         output, decrypted data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicDecryptorSigner::Decrypt(const ByteSeq& in, ByteSeq& out) {
  return RSAMD5OpenSSLDecrypt(pkey, in, out);
}

/*! \brief  Get hash calculator.

    \returns  Hash calculator.
*/
IHasher* RSAMD5OpenSSLPublicDecryptorSigner::GetHasher() {
  return hasher;
}

/*! \brief  Verify signature.

    \param  in          input, data to verify.
    \param  sig         input, signature data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicDecryptorSigner::Verify(const ByteSeq& in, const ByteSeq& sig) {
  ByteSeq hash;
  if (hasher->Hash(in, hash) == false) {
    return false;
  }
  return RSAMD5OpenSSLVerify(pkey, sig, hash);
}

/*! \brief  Create signature.

    \param  in          input, data to sign.
    \param  sig         output, signature data.

    \returns  Boolean indicating success or failure.
*/
bool RSAMD5OpenSSLPublicDecryptorSigner::Sign(const ByteSeq& in, ByteSeq& sig) {
  ByteSeq hash;
  if (hasher->Hash(in, hash) == false) {
    return false;
  }
  return RSAMD5OpenSSLSign(pkey, hash, sig);
}

/*!	\brief  Constructor.

	\param		logger		message logger.
*/
OpenSSLCertVerifier::OpenSSLCertVerifier(DRMLogger& logger): verifierLogger(logger) {
}

/*! \brief  Get public key encryptor certificate.

    \param  cert        input, certificate data.

    \returns  Public key encryptor certificate. If zero, failed.
*/
IPublicEncryptorCertificate* OpenSSLCertVerifier::GetEncryptorCertificate(
    const ByteSeq& cert) {
  return GetEncryptorVerifierCertificate(cert);
}

/*! \brief  Get public key verifier certificate.

    \param  cert        input, certificate data.

    \returns  Public key verifier certificate. If zero, failed.
*/
IPublicVerifierCertificate* OpenSSLCertVerifier::GetVerifierCertificate(
    const ByteSeq& cert) {
  return GetEncryptorVerifierCertificate(cert);
}

/*! \brief  Get public key encryptor and verifier certificate.

    \param  cert        input, certificate data.

    \returns  Public key encryptor and verifier certificate. If zero, failed.
*/
IPublicEncryptorVerifierCertificate* OpenSSLCertVerifier::GetEncryptorVerifierCertificate(
    const ByteSeq& cert) {
  X509* cc = ParseX509CertFromData((ByteT*)cert.GetFirst(), (unsigned int)cert.GetLength());
  if (cc == 0) {
    return 0;
  }

  //  Take out public key.
  ByteT* tmp = cc->cert_info->key->public_key->data;
  EVP_PKEY* pubkey = d2i_PublicKey(EVP_PKEY_RSA, NULL, &tmp,
    cc->cert_info->key->public_key->length);
  if (pubkey == 0) {
    X509_free(cc);
    return 0;
  }
  if (pubkey->pkey.rsa == 0) {
    EVP_PKEY_free(pubkey);
    X509_free(cc);
    return 0;
  }

  try {
    return new X509OpenSSLPublicEncryptorVerifierCertificate(pubkey, cc);
  }
  catch (PublicCryptoException) {
    return 0;
  }
}

/*! \brief  Verify certificate chain.

    Assume that the chain starts with a certificate issued by root.
    If successful, return encryptor certificate from the last certificate.

    \param  root        input, root certificate.
    \param  chain       input, certificate chain, ending with certificate
                        to verify.

    \returns  Verified public key encryptor certificate. If zero, failed.
*/
IPublicEncryptorCertificate* OpenSSLCertVerifier::VerifyChainGetEncryptorCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain) {
  return VerifyChainGetEncryptorVerifierCertificate(root, chain);
}

/*! \brief  Verify certificate chain.

    Assume that the chain starts with a certificate issued by root.
    If successful, return verifier certificate from the last certificate.

    \param  root        input, root certificate.
    \param  chain       input, certificate chain, ending with certificate
                        to verify.

    \returns  Verified public key verifier certificate. If zero, failed.
*/
IPublicVerifierCertificate* OpenSSLCertVerifier::VerifyChainGetVerifierCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain) {
  return VerifyChainGetEncryptorVerifierCertificate(root, chain);
}

/*! \brief  Verify certificate chain.

    Assume that the chain starts with a certificate issued by root.
    If successful, return encryptor and verifier certificate from the
    last certificate.

    \param  root        input, root certificate.
    \param  chain       input, certificate chain, ending with certificate
                        to verify.

    \returns  Verified public key encryptor and verifier certificate. If zero, failed.
*/
IPublicEncryptorVerifierCertificate* OpenSSLCertVerifier::VerifyChainGetEncryptorVerifierCertificate(
    const ByteSeq& root, const std::vector<ByteSeq>& chain) {
  X509* cert = OpenSSLVerifyChain(root, chain, verifierLogger);
  if (cert == 0) {
    return 0;
  }

  //  Take out public key.
  ByteT* tmp = cert->cert_info->key->public_key->data;
  EVP_PKEY* pubkey = d2i_PublicKey(EVP_PKEY_RSA, NULL, &tmp,
    cert->cert_info->key->public_key->length);
  if (pubkey == 0) {
    X509_free(cert);
    return 0;
  }
  if (pubkey->pkey.rsa == 0) {
    EVP_PKEY_free(pubkey);
    X509_free(cert);
    return 0;
  }

  try {
    return new X509OpenSSLPublicEncryptorVerifierCertificate(pubkey, cert);
  }
  catch (PublicCryptoException) {
    return 0;
  }
}

/*! \brief  Verify certificate chain.

    Assume that the chain starts with a certificate issued by root.

    \param  root        input, root certificate.
    \param  chain       input, certificate chain, ending with certificate
                        to verify.

    \returns  Boolean indicating success or failure.
*/
bool OpenSSLCertVerifier::VerifyChain(const ByteSeq& root, const std::vector<ByteSeq>& chain) {
  X509* cert = OpenSSLVerifyChain(root, chain, verifierLogger);
  if (cert == 0) {
    return false;
  }

  X509_free(cert);
  return true;
}

/*! \brief  X509 certificate with public encryptor and verifier.
*/
/*! \brief  Constructor.

    \param  pk          public key.
    \param  cert        X509 certificate.

    If fails, throws PublicCryptoException.
*/
X509OpenSSLPublicEncryptorVerifierCertificate::X509OpenSSLPublicEncryptorVerifierCertificate(
  EVP_PKEY* pk, X509* cert):
  encver(new RSAMD5OpenSSLPublicEncryptorVerifier(pk)),
  expiration(FiniteTValue<UTCTime>(GetExpirationTimeAsUTC(cert))),
  certificate(cert) {
}

X509OpenSSLPublicEncryptorVerifierCertificate::~X509OpenSSLPublicEncryptorVerifierCertificate() {
  if (encver != 0) delete encver; encver = 0;
  if (certificate != 0) X509_free(certificate); certificate = 0;
}

/*! \brief  Encode as byte array.

    \param  out         output, encoded data.

    \returns  Boolean indicating success or failure.
*/
bool X509OpenSSLPublicEncryptorVerifierCertificate::Encode(ByteSeq& out) {
  ByteT* b = 0;
  int len = i2d_X509(certificate, NULL);
  if (len <= 0) {
    return false;
  }
  if ((b = (ByteT*)malloc(len)) == NULL) {
    return false;
  }
  ByteT* tmp = b;
  len = i2d_X509(certificate, &tmp);
  if (len <= 0) {
    free(b);
    return false;
  }
  out = ByteSeq(b, len);
  free(b);
  return true;
}

/*! \brief  Get expiration time.

    \returns  Expiration time.
*/
const TValue<UTCTime>& X509OpenSSLPublicEncryptorVerifierCertificate::GetExpirationTime() const {
  return expiration;
}

/*! \brief  Get public encryptor and verifier.

    \returns  Public encryptor and verifier.
*/
IPublicEncryptorVerifier* X509OpenSSLPublicEncryptorVerifierCertificate::GetPublicEncryptorVerifier() {
  return encver;
}

} // namespace DRMPlugin
