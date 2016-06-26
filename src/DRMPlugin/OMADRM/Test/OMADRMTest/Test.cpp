#include <iostream>
#if defined (WIN32)
#include <crtdbg.h>
#endif
#include <openssl/x509.h>
#include <openssl/engine.h>
#include <sys/stat.h>

#include "OMADRMEncManagerFactory.h"
#include "OMADRMDecManagerFactory.h"
#include "PublicCryptoFactory.h"
#include "CipherFactory.h"
#include "XMLFactory.h"
#include "Base64Factory.h"
#include "ThreadSyncFactory.h"
#include "OMADRMCrypto.h"

using namespace DRMPlugin;


/*!	OpenSSL blowfish encryptor. Encrypts data.
*/
class OpenSSLBlowfishEncryptor: public BlowfishEncryptor {
public:
  OpenSSLBlowfishEncryptor(ByteT* k, UInt32T kSize, DRMLogger& logger):
    ctx(), cipher((EVP_CIPHER*)(EVP_bf_cfb())), key(k), iv(0), keySize(kSize) {
  }

  virtual ~OpenSSLBlowfishEncryptor() {
    if (key != 0) free(key); key = 0;
    if (iv != 0) free(iv); iv = 0;
  }

	/*!	Encrypts plaintext from in and returns ciphertext in out.

      \param  in        input, plaintext.
      \param  inSize    input, size of the plaintext.
      \param  out       output, ciphertext.
      \param  outLen    output, size of the ciphertext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Encrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen) {
	  *out = (ByteT*)malloc(inSize + EVP_MAX_KEY_LENGTH);
    if (*out == 0) {
      return false;
    }
	  int curLen2 = 0;
	  int curLen = inSize + EVP_MAX_KEY_LENGTH;

	  EVP_CIPHER_CTX_init(&ctx);
	  EVP_EncryptInit(&ctx, cipher, (unsigned char*)key, (unsigned char*)iv);
	  EVP_EncryptUpdate(&ctx, (unsigned char*)(*out), &curLen, (unsigned char*)in, inSize);
	  if (curLen > (int)inSize) {
      //! \todo: some error indicated in openIPMP.
      if (*out) free(*out);
		  return false;
	  }
	  EVP_EncryptFinal(&ctx, (unsigned char*)((*out) + curLen), &curLen2);
	  EVP_CIPHER_CTX_cleanup(&ctx);
	  if (curLen2) {
      //! \todo: some error indicated in openIPMP.
      if (*out) free(*out);
		  return false;
	  }
    *outLen = curLen;

    return true;
  }

private:
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER* cipher;
	ByteT* key;
	ByteT* iv;
  UInt32T keySize;
};

/*!	OpenSSL blowfish decryptor. Decrypts data.
*/
class OpenSSLBlowfishDecryptor: public BlowfishDecryptor {
public:
  OpenSSLBlowfishDecryptor(ByteT* k, UInt32T kSize, DRMLogger& logger): ctx(),
    cipher((EVP_CIPHER*)(EVP_bf_cfb())), key(k), iv(0), keySize(kSize) {
  }

  virtual ~OpenSSLBlowfishDecryptor() {
    if (key != 0) free(key); key = 0;
    if (iv != 0) free(iv); iv = 0;
  }

	/*!	Decrypts ciphertext from in and returns plaintext in out.

      \param  in        input, ciphertext.
      \param  inSize    input, size of the ciphertext.
      \param  out       output, plaintext.
      \param  outLen    output, size of the plaintext.

      \return Boolean indicating success or failure.
	*/
	virtual bool Decrypt(ByteT* in, UInt32T inSize, ByteT** out, UInt32T* outLen) {
	  *out = (ByteT*)malloc(inSize + EVP_MAX_KEY_LENGTH);
    if (*out == 0) {
      return false;
    }
	  int curLen2 = 0;
	  int curLen = inSize + EVP_MAX_KEY_LENGTH;

	  EVP_DecryptInit(&ctx, cipher, (unsigned char*)key, (unsigned char*)iv);
	  EVP_DecryptUpdate(&ctx, (unsigned char*)(*out), &curLen, (unsigned char*)in, inSize);
	  if (curLen != inSize) {
      //! \todo: some error indicated in openIPMP.
      if (*out) free(*out);
		  return false;
	  }
	  EVP_DecryptFinal(&ctx, (unsigned char*)((*out) + curLen), &curLen2);
	  EVP_CIPHER_CTX_cleanup(&ctx);
	  if (curLen2) {
      //! \todo: some error indicated in openIPMP.
      if (*out) free(*out);
		  return false;
	  }
    *outLen = curLen;

    return true;
  }

private:
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER* cipher;
	ByteT* key;
	ByteT* iv;
  UInt32T keySize;
};


bool BlowfishTest() {
  ByteT bytes1[] = {0x30, 0x82, 0x03, 0xE9, 0x30, 0x82, 0x02, 0xD1, 0xA0, 0x03,
    0x02, 0x01, 0x02, 0x02, 0x09, 0x00, 0xA4, 0xF7, 0x86, 0x53, 0xA8, 0x1C, 0x48,
    0x87, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01,
    0x04, 0x05, 0x00, 0x30, 0x56, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04,
    0x06, 0x13, 0x02, 0x48, 0x52, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04,
    0x08, 0x13, 0x06, 0x5A, 0x61, 0x67, 0x72, 0x65, 0x62, 0x31, 0x0F, 0x30, 0x0D,
    0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x06, 0x5A, 0x61, 0x67, 0x72, 0x65, 0x62,
    0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x07, 0x41, 0x64,
    0x6E, 0x65, 0x63, 0x74, 0x6F, 0x31, 0x13};

  DRMLogger logger;

  ByteT* ekey1;
  if (CipherFactory::RndGenerate(&ekey1, 16) == false) {
    return false;
  }
  BlowfishEncryptor* enc1 = CipherFactory::GetBlowfishEncryptor(ekey1, (UInt32T)16, logger);
  if (enc1 == 0) {
    return false;
  }

  ByteT* ekey2 = (ByteT*)malloc(16);
  memcpy(ekey2, ekey1, 16);

  BlowfishEncryptor* enc2 = new OpenSSLBlowfishEncryptor(ekey2, (UInt32T)16, logger);

  ByteT* ebytes1;
  UInt32T elen1;

  if (enc1->Encrypt(bytes1, sizeof(bytes1), &ebytes1, &elen1) == false) {
    delete enc1;
    delete enc2;
    return false;
  }

  ByteT* ebytes2;
  UInt32T elen2;

  if (enc2->Encrypt(bytes1, sizeof(bytes1), &ebytes2, &elen2) == false) {
    free(ebytes1);
    delete enc1;
    delete enc2;
    return false;
  }

  free(ebytes1);
  free(ebytes2);

  if (enc1->Encrypt(bytes1, sizeof(bytes1), &ebytes1, &elen1) == false) {
    delete enc1;
    delete enc2;
    return false;
  }

  if (enc2->Encrypt(bytes1, sizeof(bytes1), &ebytes2, &elen2) == false) {
    free(ebytes1);
    delete enc1;
    delete enc2;
    return false;
  }

  bool ret = true;
  ret = ret && (elen1 == elen2);
  if (ret) {
    ret = ret && (memcmp(ebytes1, ebytes2, elen1) == 0);
  }

  if (!ret) {
    free(ebytes1);
    free(ebytes2);
    delete enc1;
    delete enc2;
    return ret;
  }

  ByteT* dkey1 = (ByteT*)malloc(16);
  memcpy(dkey1, ekey1, 16);

  delete enc1;
  delete enc2;

  BlowfishDecryptor* dec1 = CipherFactory::GetBlowfishDecryptor(dkey1, 16, logger);
  if (dec1 == 0) {
    free(ebytes1);
    free(ebytes2);
    return false;
  }

  ByteT* dkey2 = (ByteT*)malloc(16);
  memcpy(dkey2, dkey1, 16);

  BlowfishDecryptor* dec2 = new OpenSSLBlowfishDecryptor(dkey2, 16, logger);

  ByteT* dbytes1;
  UInt32T dlen1;
  if (dec1->Decrypt(ebytes1, elen1, &dbytes1, &dlen1) == false) {
    free(ebytes1);
    free(ebytes2);
    delete dec1;
    delete dec2;
    return false;
  }

  ByteT* dbytes2;
  UInt32T dlen2;
  if (dec2->Decrypt(ebytes2, elen2, &dbytes2, &dlen2) == false) {
    free(ebytes1);
    free(ebytes2);
    free(dbytes1);
    delete dec1;
    delete dec2;
    return false;
  }

  free(ebytes1);
  free(ebytes2);
  delete dec1;
  delete dec2;

  ret = ret && (dlen1 == dlen2);
  if (ret) {
    ret = ret && (memcmp(dbytes1, dbytes2, dlen1) == 0);
  }
  free(dbytes1);
  free(dbytes2);

  return ret;
}

bool Base64Test() {
  ByteT bytes1[] = {0x30, 0x82, 0x03, 0xE9, 0x30, 0x82, 0x02, 0xD1, 0xA0, 0x03,
    0x02, 0x01, 0x02, 0x02, 0x09, 0x00, 0xA4, 0xF7, 0x86, 0x53, 0xA8, 0x1C, 0x48,
    0x87, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01,
    0x04, 0x05, 0x00, 0x30, 0x56, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04,
    0x06, 0x13, 0x02, 0x48, 0x52, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04,
    0x08, 0x13, 0x06, 0x5A, 0x61, 0x67, 0x72, 0x65, 0x62, 0x31, 0x0F, 0x30, 0x0D,
    0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x06, 0x5A, 0x61, 0x67, 0x72, 0x65, 0x62,
    0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x07, 0x41, 0x64,
    0x6E, 0x65, 0x63, 0x74, 0x6F, 0x31, 0x13};
  Base64StringT b64;
  Base64Factory::Encode(ByteSeq(bytes1, sizeof(bytes1)), b64);
  ByteSeq dbytes;
  Base64Factory::Decode(b64, dbytes);
  if (memcmp(bytes1, dbytes.GetFirst(), sizeof(bytes1)) == 0) {
    std::cout << std::string("OK...") << std::endl;
  } else {
    std::cout << std::string("ERR...") << std::endl;
  }

  ByteT bytes[] = {0xf1, 0xaa, 0xb};
  Base64Factory::Encode(ByteSeq(bytes, 3), b64);
  std::cout << std::string("3->4 Base64= ");
  std::cout << b64.BString() << std::endl;
  Base64Factory::Decode(b64, dbytes);
  if (memcmp(bytes, dbytes.GetFirst(), 3) == 0) {
    std::cout << std::string("3->4 OK...") << std::endl;
  } else {
    std::cout << std::string("3->4 ERR...") << std::endl;
  }
  Base64Factory::Encode(ByteSeq(bytes, 2), b64);
  std::cout << std::string("2->4 Base64= ");
  std::cout << b64.BString() << std::endl;
  Base64Factory::Decode(b64, dbytes);
  if (memcmp(bytes, dbytes.GetFirst(), 2) == 0) {
    std::cout << std::string("2->4 OK...") << std::endl;
  } else {
    std::cout << std::string("2->4 ERR...") << std::endl;
  }
  Base64Factory::Encode(ByteSeq(bytes, 1), b64);
  std::cout << std::string("1->4 Base64= ");
  std::cout << b64.BString() << std::endl;
  Base64Factory::Decode(b64, dbytes);
  if (memcmp(bytes, dbytes.GetFirst(), 1) == 0) {
    std::cout << std::string("1->4 OK...") << std::endl;
  } else {
    std::cout << std::string("1->4 ERR...") << std::endl;
  }
  Base64Factory::Encode(ByteSeq(bytes, 0), b64);
  std::cout << std::string("0->4 Base64= ");
  std::cout << b64.BString() << std::endl;
  Base64Factory::Decode(b64, dbytes);
  if (memcmp(bytes, dbytes.GetFirst(), 0) == 0) {
    std::cout << std::string("0->4 OK...") << std::endl;
  } else {
    std::cout << std::string("0->4 ERR...") << std::endl;
  }
  return true;
}

bool Encode(IOMADRMEncManager* agent, DRMPlugin::IXMLElement* xml) {
  //  Simulate encryption.
  std::string content1 = "test content 1";
  AES128CBCEncryptor* enc1 = agent->CreateAES128CBCEnc(content1, xml);
  if (enc1 == 0) {
    return false;
  }
  delete enc1;
  if (agent->AddLicense(content1, xml) == false) {
    return false;
  }

  std::string content2 = "test content 2";
  AES128CTREncryptor* enc2 = agent->CreateAES128CTREnc(content2, xml);
  if (enc2 == 0) {
    return false;
  }
  delete enc2;
  if (agent->AddLicense(content2, xml) == false) {
    return false;
  }

  return true;
}

bool Decode(IOMADRMDecManager* agent) {
  //  Simulate decryption.
  DRMLogger logger;
  std::string content1 = "test content 1";
  Base64StringT b64;
  if (Base64Factory::Encode(ByteSeq((ByteT*)content1.data(), content1.size()), b64) == false) {
    return false;
  }
//  OMADRMInfo info1((ByteT)(AES128CBC), 1, 0, b64.BString(), 0x0200,
//    "localhost:8080", "", "", "", "", "", logger);
  OMADRMInfo info1((ByteT)(AES128CBC), 1, 0, b64.BString(), 0x0200,
    "161.53.118.61:8080", "", "", "", "", "", logger);
  IOMADRMDecryptor* dec1 = agent->CreateDecryptor(info1, 0);
  if (dec1 == 0) {
    return false;
  }
  delete dec1;

  dec1 = agent->CreateDecryptor(info1, 0);
  if (dec1 == 0) {
    return false;
  }
  delete dec1;

  std::string content2 = "test content 2";
  if (Base64Factory::Encode(ByteSeq((ByteT*)content2.data(), content2.size()), b64) == false) {
    return false;
  }
//  OMADRMInfo info2((ByteT)(AES128CTR), 0, 0, b64.BString(), 0x0200,
//    "localhost:8080", "", "", "", "", "", logger);
  OMADRMInfo info2((ByteT)(AES128CTR), 0, 0, b64.BString(), 0x0200,
    "161.53.118.61:8080", "", "", "", "", "", logger);
  IOMADRMDecryptor* dec2 = agent->CreateDecryptor(info2, 0);
  if (dec2 == 0) {
    return false;
  }
  delete dec2;

  return true;
}

bool OpenSSLTest() {
  unsigned char bin1[] = {0xab, 0xcd, 0xff, 0x12, 0x00, 0x00};
  unsigned char *b64 = (unsigned char*)malloc(((sizeof(bin1)+2)/3)*4+1);
  EVP_EncodeBlock(b64, bin1, sizeof(bin1));
  std::cout << (const char*)b64 << std::endl;
  unsigned int len = strlen((const char*)b64);
  unsigned int i = len;
  while ((i >= 1) && (b64[i-1] == '=') && ((len-i) < 3)) {
    i--;
  }
  if ((len-i) == 3) {
    // err
  }
  unsigned int dbinsize = (i/4)*3;
  if (i != len) {
    dbinsize += (((len-i) == 1)? (2): (1));
  }
  unsigned char *dbin = (unsigned char*)malloc(((len+3)/4)*3);
  EVP_DecodeBlock(dbin, b64, len);
  bool check = (dbinsize == sizeof(bin1));
  check = (memcmp(bin1, dbin, dbinsize) == 0);
  free(b64);
  free(dbin);

  unsigned char bin2[] = {0xab, 0xcd, 0xff, 0x12, 0x00};
  b64 = (unsigned char*)malloc(((sizeof(bin2)+2)/3)*4+1);
  EVP_EncodeBlock(b64, bin2, sizeof(bin2));
  std::cout << (const char*)b64 << std::endl;
  len = strlen((const char*)b64);
  i = len;
  while ((i >= 1) && (b64[i-1] == '=') && ((len-i) < 3)) {
    i--;
  }
  if ((len-i) == 3) {
    // err
  }
  dbinsize = (i/4)*3;
  if (i != len) {
    dbinsize += (((len-i) == 1)? (2): (1));
  }
  dbin = (unsigned char*)malloc(((len+3)/4)*3);
  EVP_DecodeBlock(dbin, b64, len);
  check = (dbinsize == sizeof(bin2));
  check = (memcmp(bin2, dbin, dbinsize) == 0);
  free(b64);
  free(dbin);

  unsigned char bin3[] = {0xab, 0xcd, 0xff, 0x12};
  b64 = (unsigned char*)malloc(((sizeof(bin3)+2)/3)*4+1);
  EVP_EncodeBlock(b64, bin3, sizeof(bin3));
  std::cout << (const char*)b64 << std::endl;
  len = strlen((const char*)b64);
  i = len;
  while ((i >= 1) && (b64[i-1] == '=') && ((len-i) < 3)) {
    i--;
  }
  if ((len-i) == 3) {
    // err
  }
  dbinsize = (i/4)*3;
  if (i != len) {
    dbinsize += (((len-i) == 1)? (2): (1));
  }
  dbin = (unsigned char*)malloc(((len+3)/4)*3);
  EVP_DecodeBlock(dbin, b64, len);
  check = (dbinsize == sizeof(bin3));
  check = (memcmp(bin3, dbin, dbinsize) == 0);
  free(b64);
  free(dbin);


  struct stat tstat;
  ByteT* tmp;

  FILE* cacertf = fopen("OMACACert.der", "rb");
  if (cacertf == NULL) {
    return false;
  }
  stat("OMACACert.der", &tstat);
  unsigned int cacertbyteslen = tstat.st_size;
  ByteT* cacertbytes = (ByteT*)malloc(cacertbyteslen);
  fread(cacertbytes, cacertbyteslen, 1, cacertf);
  fclose(cacertf);

  X509* cacert = 0;
  tmp = cacertbytes;
  cacert = d2i_X509(NULL, &tmp, cacertbyteslen);
  free(cacertbytes);
  if (cacert == 0) {
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }

  FILE* cakeyf = fopen("OMACAKey.der", "rb");
  if (cakeyf == NULL) {
    return false;
  }
  stat("OMACAKey.der", &tstat);
  unsigned int cakeybyteslen = tstat.st_size;
  ByteT* cakeybytes = (ByteT*)malloc(cakeybyteslen);
  fread(cakeybytes, cakeybyteslen, 1, cakeyf);
  fclose(cakeyf);

  EVP_PKEY* cakey = 0;
  tmp = cakeybytes;
  cakey = d2i_AutoPrivateKey(NULL, &tmp, cakeybyteslen);
  free(cakeybytes);
  if (cakey == 0) {
    X509_free(cacert);
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }

  if (cakey->pkey.rsa == 0) {
    EVP_PKEY_free(cakey);
    X509_free(cacert);
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }

  std::string data = "Data to be signed";
  ByteT* datahash = (ByteT*)malloc(EVP_md5()->md_size);
  unsigned int datahashlen;
  int ret = 1;
  ret = EVP_Digest((char*)(data.data()), data.size(), datahash, &datahashlen, EVP_md5(),
    /* ENGINE *impl */ 0);

  ByteT* sigret = (ByteT*)malloc(RSA_size(cakey->pkey.rsa));
  unsigned int siglen = 0;
  ret = RSA_sign(NID_md5, datahash, datahashlen, sigret, &siglen, cakey->pkey.rsa);

  tmp = cacert->cert_info->key->public_key->data;
  EVP_PKEY* capubkey = d2i_PublicKey(EVP_PKEY_RSA, NULL, &tmp,
    cacert->cert_info->key->public_key->length);

  if (capubkey == 0) {
    free(sigret);
    free(datahash);
    EVP_PKEY_free(capubkey);
    EVP_PKEY_free(cakey);
    X509_free(cacert);
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }

  if (capubkey->pkey.rsa == 0) {
    free(sigret);
    free(datahash);
    EVP_PKEY_free(capubkey);
    EVP_PKEY_free(cakey);
    X509_free(cacert);
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }

  ret = RSA_verify(NID_md5, datahash, datahashlen, sigret, siglen, capubkey->pkey.rsa);

  free(sigret);
  free(datahash);

  data = "Data to be encrypted";
  ByteT* encdata = (ByteT*)malloc(RSA_size(capubkey->pkey.rsa));
  unsigned int enclen = RSA_public_encrypt(data.size(), (ByteT*)data.data(),
    encdata, capubkey->pkey.rsa, RSA_PKCS1_PADDING);
  ByteT* decdata = (ByteT*)malloc(RSA_size(capubkey->pkey.rsa));
  unsigned int declen = RSA_private_decrypt(enclen, encdata, decdata, cakey->pkey.rsa,
    RSA_PKCS1_PADDING);
  
  std::string dec((const char*)decdata, (const char*)(decdata + declen));
  free(decdata);
  free(encdata);

  if (data != dec) {
    EVP_PKEY_free(capubkey);
    EVP_PKEY_free(cakey);
    X509_free(cacert);
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }

  int isize = i2d_PublicKey(capubkey, NULL);


  EVP_PKEY_free(capubkey);
  EVP_PKEY_free(cakey);


  FILE* devicecertf = fopen("deviceCertSigned.der", "rb");
  if (devicecertf == NULL) {
    X509_free(cacert);
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }
  stat("deviceCertSigned.der", &tstat);
  unsigned int devicecertbyteslen = tstat.st_size;
  ByteT* devicecertbytes = (ByteT*)malloc(devicecertbyteslen);
  fread(devicecertbytes, devicecertbyteslen, 1, devicecertf);
  fclose(devicecertf);

  X509* devicecert = 0;
  tmp = devicecertbytes;
  devicecert = d2i_X509(NULL, &tmp, devicecertbyteslen);
  free(devicecertbytes);
  if (devicecert == 0) {
    X509_free(cacert);
    EVP_cleanup();
    ERR_free_strings();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    return false;
  }

  STACK_OF(X509)* stack = sk_X509_new_null();
  sk_X509_push(stack, cacert);
  X509_STORE* store = X509_STORE_new();
  X509_STORE_CTX* storectx = X509_STORE_CTX_new();
  ret = X509_STORE_CTX_init(storectx, store, NULL, NULL);

  X509_STORE_CTX_set_cert(storectx, devicecert);
  X509_STORE_CTX_trusted_stack(storectx, stack);
//  X509_STORE_CTX_set_chain(storectx, stack);
	OpenSSL_add_all_algorithms();
  ret = X509_verify_cert(storectx);

  const char* err = X509_verify_cert_error_string(storectx->error);

  sk_X509_free(stack);
  X509_STORE_free(store);
  X509_STORE_CTX_free(storectx);
  X509_free(devicecert);
  X509_free(cacert);

  EVP_cleanup();
  ERR_free_strings();
  CRYPTO_cleanup_all_ex_data();
  ERR_remove_state(0);

  return true;
}

bool XercesXMLTest() {
  DRMLogger logger;

  DRMPlugin::IXMLDocument* xml1 = XMLFactory::CreateDocument("TestXMLInfo", logger);
  DRMPlugin::IXMLElement* root1 = xml1->GetRootElement();
  DRMPlugin::IXMLElement* tag1 = root1->AddChildElement("tag1");
  DRMPlugin::IXMLAttribute* tag1att = tag1->AddAttribute("type", "tag");
  DRMPlugin::IXMLElement* tag2 = tag1->AddChildElement("tag2");
  DRMPlugin::IXMLAttribute* tag2att = tag2->AddAttribute("type", "tag");
  DRMPlugin::IXMLElement* tag3 = root1->AddChildElement("tag3");
  DRMPlugin::IXMLAttribute* tag3att1 = tag3->AddAttribute("type1", "tag");
  DRMPlugin::IXMLAttribute* tag3att2 = tag3->AddAttribute("type2", "tag");

//  std::cout << xml1->Encode() << std::endl;

  delete xml1;

/*
  std::string xmldata = "\
    <TestXMLInfo>\
     <tag1 type1=\"aaa\" type2=\"bbb\">\
      tag1value\
     </tag1>\
     <tag2>\
      <tag3 type=\"ccc\">\
       tag3value\
      </tag3>\
     </tag2>\
    </TestXMLInfo>";
*/
  std::string xmldata = "<TestXMLInfo><tag1 type1=\"aaa\" type2=\"bbb\"><>&</tag1><tag2><tag3 type=\"ccc\">tag3value</tag3></tag2></TestXMLInfo>";

  DRMPlugin::IXMLDocument* xml2 = XMLFactory::DecodeDocument(xmldata, logger);
  DRMPlugin::IXMLElement* root2 = xml2->GetRootElement();

  tag1 = root2->GetChildElement("tag1");
  tag1->SetStrValue("<>&");
  tag1->SetStrValue("tag1value2");

  std::cout << tag1->GetName() << " " << tag1->GetStrValue() << std::endl;

  DRMPlugin::IXMLElement* tag4 = root2->AddChildElement("tag4");
  DRMPlugin::IXMLAttribute* tag4att = tag4->AddAttribute("type", "tag41");
  tag4->SetStrValue("<>&");
  tag4->SetStrValue("tag4value2");

  std::cout << tag4->GetName() << " " << tag4->GetStrValue() << std::endl;

  tag4 = root2->AddChildElement("tag4");
  tag4att = tag4->AddAttribute("type", "tag42");
  tag4->SetStrValue("tag4value2");

//  std::cout << xml2->Encode() << std::endl;

  std::cout << tag4->GetName() << " " << tag4->GetStrValue() << std::endl;

  std::vector<DRMPlugin::IXMLElement*> tag4elems = root2->GetChildElementsByName("tag4");
  for (unsigned int i = 0; i < tag4elems.size(); i++) {
//    std::cout << tag4elems[i]->Encode() << std::endl;
  }

  xmldata = xml2->Encode();
  delete xml2;

  DRMPlugin::IXMLDocument* xml3 = XMLFactory::DecodeDocument(xmldata, logger);
  DRMPlugin::IXMLElement* root3 = xml3->GetRootElement();
  DRMPlugin::IXMLElement* element3 =
    root3->AddChildElement("Element1.Element2.Element3", "element3value");
  element3->AddAttribute("attribute3", "value3");
  DRMPlugin::IXMLAttribute* attr = element3->AddAttribute("attribute4", IntToString(175));

  std::cout << xml3->Encode() << std::endl;

  std::cout << root3->GetChildStrValue("Element1.Element2.Element3") << std::endl;
  std::cout << root3->GetChildAttrStrValue("Element1.Element2.Element3", "attribute3") << std::endl;

  delete xml3;

  return true;
}

bool CipherTest() {
  ByteT bytes1[] = {0x30, 0x82, 0x03, 0xE9, 0x30, 0x82, 0x02, 0xD1, 0xA0, 0x03,
    0x02, 0x01, 0x02, 0x02, 0x09, 0x00, 0xA4, 0xF7, 0x86, 0x53, 0xA8, 0x1C, 0x48,
    0x87, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01,
    0x04, 0x05, 0x00, 0x30, 0x56, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04,
    0x06, 0x13, 0x02, 0x48, 0x52, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04,
    0x08, 0x13, 0x06, 0x5A, 0x61, 0x67, 0x72, 0x65, 0x62, 0x31, 0x0F, 0x30, 0x0D,
    0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x06, 0x5A, 0x61, 0x67, 0x72, 0x65, 0x62,
    0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x07, 0x41, 0x64,
    0x6E, 0x65, 0x63, 0x74, 0x6F, 0x31, 0x13};

  ByteT* key;
  if (CipherFactory::RndGenerate(&key, 16) == false) {
    return false;
  }
  DRMLogger logger;
  BlowfishEncryptor* enc = CipherFactory::GetBlowfishEncryptor(key, 16, logger);
  if (enc == 0) {
    return false;
  }
  ByteT* dkey = (ByteT*)malloc(16);
  memcpy(dkey, key, 16);

  ByteT* ebytes1;
  UInt32T elen1;

  if (enc->Encrypt(bytes1, sizeof(bytes1), &ebytes1, &elen1) == false) {
    delete enc;
    return false;
  }

  ByteT* ebytes2;
  UInt32T elen2;

  if (enc->Encrypt(bytes1, sizeof(bytes1) - 5, &ebytes2, &elen2) == false) {
    free(ebytes1);
    delete enc;
    return false;
  }
  delete enc;

  BlowfishDecryptor* dec = CipherFactory::GetBlowfishDecryptor(dkey, 16, logger);
  if (dec == 0) {
    free(ebytes1);
    free(ebytes2);
    return false;
  }

  ByteT* dbytes1;
  UInt32T dlen1;
  if (dec->Decrypt(ebytes1, elen1, &dbytes1, &dlen1) == false) {
    free(ebytes1);
    free(ebytes2);
    delete dec;
    return false;
  }

  ByteT* dbytes2;
  UInt32T dlen2;
  if (dec->Decrypt(ebytes2, elen2, &dbytes2, &dlen2) == false) {
    free(ebytes1);
    free(ebytes2);
    free(dbytes1);
    delete dec;
    return false;
  }
  delete dec;

  bool ret = (memcmp(bytes1, dbytes1, sizeof(bytes1)) == 0) &&
    (memcmp(bytes1, dbytes2, sizeof(bytes1) - 5) == 0);
  free(ebytes1);
  free(ebytes2);
  free(dbytes1);
  free(dbytes2);
  
  if (ret == true) {
    std::cout << std::string("OK...") << std::endl;
  } else {
    std::cout << std::string("ERR...") << std::endl;
  }

  return ret;
}

class MemException {
};

class MemTest {
public:
  MemTest(ByteT* in, unsigned int len): input(in), inlen(len) {
    if (input != 0) delete input; input = 0;
    throw MemException();
  }

  ~MemTest() {
    if (input != 0) delete input;
  }

private:
  ByteT* input;
  unsigned int inlen;
};

class MemTest2 {
public:
  MemTest2(ByteT* in, unsigned int len): mtest(0) {
    try {
      mtest = new MemTest(in, len);
    }
    catch (MemException) {
      mtest = 0;
    }
//    throw MemException();
  }

  ~MemTest2() {
    if (mtest != 0) delete mtest;
  }

private:
  MemTest* mtest;
};

int main(int argc, char* argv[]) {
#if defined (_DEBUG) && defined (WIN32)
	int tempflag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
	tempflag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag( tempflag );

  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_WNDW );
  _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_WNDW );
  _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_WNDW );
//  _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
//  _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR );
//  _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR );
#endif

//  ByteT* mbytes = (ByteT*)malloc(100);
//  MemTest2 mt(mbytes, 100);
//  return true;

//  return BlowfishTest();

//  return CipherTest();

//  return Base64Test();

//  return XercesXMLTest();

//  return OpenSSLTest();

  //  Check encode/decode test switch.
  std::string usage = "Usage:\n"
    "  -E                              encode test.\n"
    "  -D                              decode test.\n";

  bool encode = false;
  bool decode = false;
  if (argc < 2) {
    //  No parameters.
    std::cout << usage << std::endl;
    return -1;
  } else if (strcmp(argv[1], "-E") == 0) {
    //  Encode test.
    encode = true;
  } else if (strcmp(argv[1], "-D") == 0) {
    //  Decode test.
    decode = true;
  } else {
    //  Wrong parameters.
    std::cout << "Wrong parameters. " << usage << std::endl;
    return -1;
  }

  DRMLogger logger;

  if (encode == true) {
    //  Encode test.
    DRMPlugin::IXMLDocument* encagentxml = XMLFactory::DecodeDocumentFromFile("OMADRMEncoderInfo.xml", logger);
    if (encagentxml == 0) {
      std::cout << "Encode test failed!" << std::endl;
      return -1;
    }
    if (encagentxml->GetRootElement()->AddChildElement("License") == 0) {
      delete encagentxml;
      std::cout << "Encode test failed!" << std::endl;
      return -1;
    }

//    if (encagentxml->GetRootElement()->GetChildElement("License")->SetStrValue("UAIW0cQze1cM+gRGXWGTJf6cMkc=;2006-01-02T00:00:00Z;2006-12-31T00:00:00Z") == false) {
    if (encagentxml->GetRootElement()->GetChildElement("License")->SetStrValue("6VPdxZv2UV11SUR4l1nst+x0YQs=;2006-01-02T00:00:00Z;2006-12-31T00:00:00Z") == false) {
      delete encagentxml;
      std::cout << "Encode test failed!" << std::endl;
      return -1;
    }

    IOMADRMEncManager* encManager =
      OMADRMEncManagerFactory::GetOMADRMEncManager(0, logger);

    IOMADRMEncManager* encManager2 =
      OMADRMEncManagerFactory::GetOMADRMEncManager(0, logger);
    delete encManager2;

    if (Encode(encManager, encagentxml->GetRootElement()) == false) {
      delete encagentxml;
      delete encManager;
      std::cout << "Encode test failed!" << std::endl;
      return -1;
    }

    delete encagentxml;
    delete encManager;

    std::cout << "Encode test passed!" << std::endl;
  } else if (decode == true) {
    //  Decode test.
    DRMPlugin::IXMLDocument* agentxml = XMLFactory::DecodeDocumentFromFile("OMADRMPlayerInfo.xml", logger);
    if (agentxml == 0) {
      std::cout << "Decode test failed!" << std::endl;
      return -1;
    }

    IOMADRMDecManager* decManager =
      OMADRMDecManagerFactory::GetOMADRMDecManager(agentxml->GetRootElement(),
      logger);
    delete agentxml;

    if (Decode(decManager) == false) {
      delete decManager;
      std::cout << "Decode test failed!" << std::endl;
      return -1;
    }

    delete decManager;

    std::cout << "Decode test passed!" << std::endl;
  } else {
    // Should not happen.
    std::cout << usage << std::endl;
    return -1;
  }

  return 0;
}
