/*
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
 */
#include "crypto/CryptoManager.h"
#include "tools/MemMan.h"

#include <iostream>
#include <assert.h>

#include <openssl/opensslv.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include <openssl/conf.h>

#include <busobj/Exception.h>

#include "busobj/ODRLLicense.h"
#include "busobj/MPEGRELLicense.h"
#include "squashxml/xml/XMLDocument.h"
#include "squashxml/tools/FileTool.h"
#include "squashxml/tools/FileLogger.h"


#define FILE_DELIMITER  "/"
#define EXT_DELIMITER   "."
#define ANY_FILE        "*"
#define EXT_P12         "p12"
#define P12_FILE        EXT_DELIMITER EXT_P12

//TODO:  This values need to be globally defined...
#define NID_License		200
#define NID_LicenseList 201

#ifndef MAX_PATH
#define MAX_PATH		255
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/** OpenIPMP/OpenSSL 9.7  don't really need this if PTHREADS is defined 
#ifdef LINUX
//#include <typedefs.h>
#include <pthread.h>
#endif
*/

#ifdef WIN32
#include <windows.h>
#endif
#ifdef SOLARIS
#include <synch.h>
#include <thread.h>
#endif
#ifdef IRIX
#include <ulocks.h>
#include <sys/prctl.h>
#endif
#ifdef PTHREADS
#include <pthread.h>
#endif
#include <openssl/lhash.h>
#include <openssl/crypto.h>
#include <openssl/buffer.h>

/** OpenIPMP/OpenSSL 9.7 */
// #include <openssl/e_os.h>

/** OpenIPMP/OpenSSL 9.7 */
#include <openssl/e_os2.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>
//#include "cryptlib.h"
#include <openssl/pkcs12.h>

//#include "threadlock.h"

void CRYPTO_thread_setup(void);
void CRYPTO_thread_cleanup(void);

static void irix_locking_callback(int mode,int type,char *file,int line);
static void solaris_locking_callback(int mode,int type,char *file,int line);
static void win32_locking_callback(int mode,int type,char *file,int line);
static void pthreads_locking_callback(int mode,int type,char *file,int line);

static unsigned long irix_thread_id(void );
static unsigned long solaris_thread_id(void );
static unsigned long pthreads_thread_id(void );

/** OpenIPMP pkcs12 management..modified OpenSSL routines to include user rights storage */

static int OpenIPMP_parse_pk12( PKCS12 *p12, const char *pass, int passlen,
		EVP_PKEY **pkey, X509 **cert, STACK_OF(X509) **ca, STACK_OF(ASN1_TYPE)** licenses);

static int OpenIPMP_parse_bags( STACK_OF(PKCS12_SAFEBAG) *bags, const char *pass,
		       int passlen, EVP_PKEY **pkey, X509 **cert,
		       STACK_OF(X509) **ca, STACK_OF(ASN1_TYPE)** licenses, ASN1_OCTET_STRING **keyid,
		       char *keymatch);

static int OpenIPMP_parse_bag( PKCS12_SAFEBAG *bag, const char *pass, int passlen,
			EVP_PKEY **pkey, X509 **cert, STACK_OF(X509) **ca, STACK_OF(ASN1_TYPE)** licenses,
			ASN1_OCTET_STRING **keyid, char *keymatch);

/** OpenIPMP/OpenSSL 9.7 */
static PKCS12_SAFEBAG *OpenIPMP_PKCS12_pack_safebag ( char *obj, int (*i2d)(), int nid1, int nid2 );


/* usage:
 * CRYPTO_thread_setup();
 * application code
 * CRYPTO_thread_cleanup();
 */

#define THREAD_STACK_SIZE (16*1024)

#ifdef WIN32

static HANDLE *lock_cs = 0;

void CRYPTO_thread_setup(void)
	{
  if (lock_cs != 0) {
    return;
  }

	int i;

	lock_cs=(void**)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(HANDLE));
	for (i=0; i<CRYPTO_num_locks(); i++)
		{
		lock_cs[i]=CreateMutex(NULL,FALSE,NULL);
		}

	CRYPTO_set_locking_callback((void (*)(int,int,const char *,int))win32_locking_callback);
	/* id callback defined */
	}

void CRYPTO_thread_cleanup(void)
	{
  if (lock_cs == 0) {
    return;
  }

	int i;

	CRYPTO_set_locking_callback(NULL);
	for (i=0; i<CRYPTO_num_locks(); i++)
		CloseHandle(lock_cs[i]);
	OPENSSL_free(lock_cs);

  lock_cs = 0;
	}

void win32_locking_callback(int mode, int type, char *file, int line)
	{
	if (mode & CRYPTO_LOCK)
		{
		WaitForSingleObject(lock_cs[type],INFINITE);
		}
	else
		{
		ReleaseMutex(lock_cs[type]);
		}
	}

#endif /* WIN32 */

#ifdef SOLARIS

#define USE_MUTEX

#ifdef USE_MUTEX
static mutex_t *lock_cs;
#else
static rwlock_t *lock_cs;
#endif
static long *lock_count;

void CRYPTO_thread_setup(void)
	{
	int i;

#ifdef USE_MUTEX
	lock_cs=OPENSSL_malloc(CRYPTO_num_locks() * sizeof(mutex_t));
#else
	lock_cs=OPENSSL_malloc(CRYPTO_num_locks() * sizeof(rwlock_t));
#endif
	lock_count=OPENSSL_malloc(CRYPTO_num_locks() * sizeof(long));
	for (i=0; i<CRYPTO_num_locks(); i++)
		{
		lock_count[i]=0;
#ifdef USE_MUTEX
		mutex_init(&(lock_cs[i]),USYNC_THREAD,NULL);
#else
		rwlock_init(&(lock_cs[i]),USYNC_THREAD,NULL);
#endif
		}

	CRYPTO_set_id_callback((unsigned long (*)())solaris_thread_id);
	CRYPTO_set_locking_callback((void (*)())solaris_locking_callback);
	}

void CRYPTO_thread_cleanup(void)
	{
	int i;

	CRYPTO_set_locking_callback(NULL);
	for (i=0; i<CRYPTO_num_locks(); i++)
		{
#ifdef USE_MUTEX
		mutex_destroy(&(lock_cs[i]));
#else
		rwlock_destroy(&(lock_cs[i]));
#endif
		}
	OPENSSL_free(lock_cs);
	OPENSSL_free(lock_count);
	}

void solaris_locking_callback(int mode, int type, char *file, int line)
	{
#if 0
	fprintf(stderr,"thread=%4d mode=%s lock=%s %s:%d\n",
		CRYPTO_thread_id(),
		(mode&CRYPTO_LOCK)?"l":"u",
		(type&CRYPTO_READ)?"r":"w",file,line);
#endif

#if 0
	if (CRYPTO_LOCK_SSL_CERT == type)
		fprintf(stderr,"(t,m,f,l) %ld %d %s %d\n",
			CRYPTO_thread_id(),
			mode,file,line);
#endif
	if (mode & CRYPTO_LOCK)
		{
#ifdef USE_MUTEX
		mutex_lock(&(lock_cs[type]));
#else
		if (mode & CRYPTO_READ)
			rw_rdlock(&(lock_cs[type]));
		else
			rw_wrlock(&(lock_cs[type]));
#endif
		lock_count[type]++;
		}
	else
		{
#ifdef USE_MUTEX
		mutex_unlock(&(lock_cs[type]));
#else
		rw_unlock(&(lock_cs[type]));
#endif
		}
	}

unsigned long solaris_thread_id(void)
	{
	unsigned long ret;

	ret=(unsigned long)thr_self();
	return(ret);
	}
#endif /* SOLARIS */

#ifdef IRIX
/* I don't think this works..... */

static usptr_t *arena;
static usema_t **lock_cs;

void CRYPTO_thread_setup(void)
	{
	int i;
	char filename[20];

	strcpy(filename,"/tmp/mttest.XXXXXX");
	mktemp(filename);

	usconfig(CONF_STHREADIOOFF);
	usconfig(CONF_STHREADMALLOCOFF);
	usconfig(CONF_INITUSERS,100);
	usconfig(CONF_LOCKTYPE,US_DEBUGPLUS);
	arena=usinit(filename);
	unlink(filename);

	lock_cs=OPENSSL_malloc(CRYPTO_num_locks() * sizeof(usema_t *));
	for (i=0; i<CRYPTO_num_locks(); i++)
		{
		lock_cs[i]=usnewsema(arena,1);
		}

	CRYPTO_set_id_callback((unsigned long (*)())irix_thread_id);
	CRYPTO_set_locking_callback((void (*)())irix_locking_callback);
	}

void CRYPTO_thread_cleanup(void)
	{
	int i;

	CRYPTO_set_locking_callback(NULL);
	for (i=0; i<CRYPTO_num_locks(); i++)
		{
		char buf[10];

		sprintf(buf,"%2d:",i);
		usdumpsema(lock_cs[i],stdout,buf);
		usfreesema(lock_cs[i],arena);
		}
	OPENSSL_free(lock_cs);
	}

void irix_locking_callback(int mode, int type, char *file, int line)
	{
	if (mode & CRYPTO_LOCK)
		{
		uspsema(lock_cs[type]);
		}
	else
		{
		usvsema(lock_cs[type]);
		}
	}

unsigned long irix_thread_id(void)
	{
	unsigned long ret;

	ret=(unsigned long)getpid();
	return(ret);
	}
#endif /* IRIX */

/* Linux and a few others */
#ifdef PTHREADS
/** OpenIPMP/OpenSSL 9.7
#ifdef LINUX
*/

static pthread_mutex_t *lock_cs;
static long *lock_count;

void CRYPTO_thread_setup(void)
	{
	int i;

	lock_cs=(pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(pthread_mutex_t));
	lock_count=(long *)OPENSSL_malloc(CRYPTO_num_locks() * sizeof(long));
	for (i=0; i<CRYPTO_num_locks(); i++)
		{
		lock_count[i]=0;
		pthread_mutex_init(&(lock_cs[i]),NULL);
		}

	CRYPTO_set_id_callback((unsigned long (*)())pthreads_thread_id);
	CRYPTO_set_locking_callback((void (*)(int, int, const char *, int))pthreads_locking_callback);
	}

void CRYPTO_thread_cleanup(void)
	{
	int i;

	CRYPTO_set_locking_callback(NULL);
	for (i=0; i<CRYPTO_num_locks(); i++)
		{
		pthread_mutex_destroy(&(lock_cs[i]));
		}
	OPENSSL_free(lock_cs);
	OPENSSL_free(lock_count);
	}

void pthreads_locking_callback(int mode, int type, char *file,
	     int line)
      {
#if 0
	fprintf(stderr,"thread=%4d mode=%s lock=%s %s:%d\n",
		CRYPTO_thread_id(),
		(mode&CRYPTO_LOCK)?"l":"u",
		(type&CRYPTO_READ)?"r":"w",file,line);
#endif
#if 0
	if (CRYPTO_LOCK_SSL_CERT == type)
		fprintf(stderr,"(t,m,f,l) %ld %d %s %d\n",
		CRYPTO_thread_id(),
		mode,file,line);
#endif
	if (mode & CRYPTO_LOCK)
		{
		pthread_mutex_lock(&(lock_cs[type]));
		lock_count[type]++;
		}
	else
		{
		pthread_mutex_unlock(&(lock_cs[type]));
		}
	}

unsigned long pthreads_thread_id(void)
	{
	unsigned long ret;

	ret=(unsigned long)pthread_self();
	return(ret);
	}

#endif /* PTHREADS / LINUX */


/* Parse the outer PKCS#12 structure */

static int OpenIPMP_parse_pk12 (PKCS12 *p12, const char *pass, int passlen,
	     EVP_PKEY **pkey, X509 **cert, STACK_OF(X509) **ca, STACK_OF(ASN1_TYPE)** licenses)
{
	STACK_OF(PKCS7) *asafes;
	STACK_OF(PKCS12_SAFEBAG) *bags;
	int i, bagnid;
	PKCS7 *p7;
	ASN1_OCTET_STRING *keyid = NULL;

	char keymatch = 0;

	if (!( asafes = M_PKCS12_unpack_authsafes (p12))) return 0;

/**	OpenIPMP/OpenSSL 9.7 this is the old implementation of M_PKCS12_unpack_authsafes 	
	if (!( asafes = ASN1_seq_unpack_PKCS7((p12)->authsafes->d.data->data,(p12)->authsafes->d.data->length, d2i_PKCS7, PKCS7_free))) return 0;
*/
	for (i = 0; i < sk_PKCS7_num (asafes); i++) 
	{
		p7 = sk_PKCS7_value (asafes, i);
		bagnid = OBJ_obj2nid (p7->type);
		if (bagnid == NID_pkcs7_data) {
			bags = M_PKCS12_unpack_p7data(p7);
/**	OpenIPMP/OpenSSL 9..7 this is the old implementation of M_PKCS12_unpack_p7data(p7)
			bags = ASN1_seq_unpack_PKCS12_SAFEBAG((p7)->d.data->data, p7->d.data->length,d2i_PKCS12_SAFEBAG, PKCS12_SAFEBAG_free);
*/
		} else if (bagnid == NID_pkcs7_encrypted) {

			/** OpenIPMP/OpenSSL 9.7 
				
				This macro didn't compile in earlier versions of openipmp, openssl, and gcc <=3.3	
				For openssl 9.7, these are no longer macros so I'm putting them back in.
			 */
			bags = M_PKCS12_unpack_p7encdata(p7, pass, passlen);
/*			
			bags = PKCS12_decrypt_d2i_PKCS12_SAFEBAG((p7)->d.encrypted->enc_data->algorithm,
			           d2i_PKCS12_SAFEBAG, PKCS12_SAFEBAG_free, 
				   (pass), (passlen), 
			           (p7)->d.encrypted->enc_data->enc_data, 3);
*/


		} else continue;
		if (!bags) {
			sk_PKCS7_pop_free(asafes, PKCS7_free);
			return 0;
		}
	    	if (!OpenIPMP_parse_bags(bags, pass, passlen, pkey, cert, ca, licenses,
							 &keyid, &keymatch)) {
			sk_PKCS12_SAFEBAG_pop_free(bags, PKCS12_SAFEBAG_free);
			sk_PKCS7_pop_free(asafes, PKCS7_free);
			return 0;
		}
		sk_PKCS12_SAFEBAG_pop_free(bags, PKCS12_SAFEBAG_free);
	}
	sk_PKCS7_pop_free(asafes, PKCS7_free);
	if (keyid) M_ASN1_OCTET_STRING_free(keyid);
	return 1;
}

static int OpenIPMP_parse_bags (STACK_OF(PKCS12_SAFEBAG) *bags, const char *pass,
		       int passlen, EVP_PKEY **pkey, X509 **cert,
		       STACK_OF(X509) **ca, STACK_OF(ASN1_TYPE)** licenses, ASN1_OCTET_STRING **keyid,
		       char *keymatch)
{
	int i;
	for (i = 0; i < sk_PKCS12_SAFEBAG_num(bags); i++) {
    if (!OpenIPMP_parse_bag(sk_PKCS12_SAFEBAG_value (bags, i), pass, passlen, pkey, cert, ca, licenses, keyid, keymatch)) {
      return 0;
    }
	}
	return 1;
}

#define MATCH_KEY  0x1
#define MATCH_CERT 0x2
#define MATCH_ALL  0x3

static int OpenIPMP_parse_bag(PKCS12_SAFEBAG *bag, const char *pass, int passlen,
		      EVP_PKEY **pkey, X509 **cert, STACK_OF(X509) **ca, STACK_OF(ASN1_TYPE)** licenses,
		      ASN1_OCTET_STRING **keyid,
	     char *keymatch)
{
	PKCS8_PRIV_KEY_INFO *p8;
	X509 *x509;
	ASN1_OCTET_STRING *lkey = NULL, *ckid = NULL;
	ASN1_TYPE *attrib;
	ASN1_BMPSTRING *fname = NULL;

	if ((attrib = PKCS12_get_attr (bag, NID_friendlyName)))
		fname = attrib->value.bmpstring;

	if ((attrib = PKCS12_get_attr (bag, NID_localKeyID))) {
		lkey = attrib->value.octet_string;
		ckid = lkey;
	}

	/* Check for any local key id matching (if needed) */
	if (lkey && ((*keymatch & MATCH_ALL) != MATCH_ALL)) {
		if (*keyid) {
			if (M_ASN1_OCTET_STRING_cmp(*keyid, lkey)) lkey = NULL;
		} else {
			if (!(*keyid = M_ASN1_OCTET_STRING_dup(lkey))) {
				PKCS12err(PKCS12_F_PARSE_BAGS,ERR_R_MALLOC_FAILURE);
				return 0;
		    }
		}
	}
	
	switch (M_PKCS12_bag_type(bag))
	{
	case NID_keyBag:
		if (!lkey || !pkey) return 1;	
		if (!(*pkey = EVP_PKCS82PKEY(bag->value.keybag))) return 0;
		*keymatch |= MATCH_KEY;
	break;

	case NID_pkcs8ShroudedKeyBag:
		if (!lkey || !pkey) return 1;	
		if (!(p8 = M_PKCS12_decrypt_skey(bag, pass, passlen)))

				return 0;
		*pkey = EVP_PKCS82PKEY(p8);
		PKCS8_PRIV_KEY_INFO_free(p8);
		if (!(*pkey)) return 0;
		*keymatch |= MATCH_KEY;
	break;

	case NID_certBag:
		if (M_PKCS12_cert_bag_type(bag) != NID_x509Certificate )
								 return 1;
		if (!(x509 = M_PKCS12_certbag2x509(bag))) return 0;
		if(ckid) X509_keyid_set1(x509, ckid->data, ckid->length);
		if(fname) {
			int len;
			unsigned char *data;
			len = ASN1_STRING_to_UTF8(&data, fname);
			if(len > 0) {
				X509_alias_set1(x509, data, len);
				OPENSSL_free(data);
			}
		}


		if (lkey) {
			*keymatch |= MATCH_CERT;
			if (cert) *cert = x509;
			else X509_free(x509);
		} else {
			if(ca) sk_X509_push (*ca, x509);
			else X509_free(x509);
		}
	break;

	case NID_safeContentsBag:
		return OpenIPMP_parse_bags(bag->value.safes, pass, passlen,
			 		pkey, cert, ca, licenses, keyid, keymatch);
	break;

	case NID_License:
		return 1;
	break;

	case NID_LicenseList:	//license object
		{
			/** TODO: CJM I think I should have to unpack this string.. but
					  I probably screwed up the types when I ASN1-encoded it..
					  
					  ..for now, use the stuff below.

				ASN1_TYPE* entitlement = (ASN1_TYPE*)ASN1_unpack_string(bag->value.bag->value.octet,(char *(*)())d2i_ASN1_TYPE);
			*/
			
			if (licenses)
			{
				//make a new ASN1_TYPE object
//				ASN1_TYPE* thisLicense = ASN1_TYPE_new();
//				ASN1_TYPE_set_octetstring(thisLicense, (unsigned char*)bag->value.bag->value.octet->data, bag->value.bag->value.octet->length);
#ifdef MACOSX
				ASN1_TYPE* entitlement = (ASN1_TYPE*)ASN1_unpack_string(bag->value.bag->value.octet,(char *(*)(...))d2i_ASN1_TYPE);

#else
				ASN1_TYPE* entitlement = (ASN1_TYPE*)ASN1_unpack_string(bag->value.bag->value.octet,(char *(*)())d2i_ASN1_TYPE);
#endif
//				sk_ASN1_TYPE_push(*licenses, thisLicense);

				sk_ASN1_TYPE_push(*licenses, entitlement);
			}


			return 1;
		}
	break;


	default:
		return 1;
	break;
	}
	return 1;
}

bool CryptoManager::parseP12Instance(PKCS12 *p12, const char *pass, EVP_PKEY **pkey, X509 **cert,
	     STACK_OF(X509) **ca, STACK_OF(ASN1_TYPE)** licenses)
{
		/* Check for NULL PKCS12 structure */

	if(!p12) {
		PKCS12err(PKCS12_F_PKCS12_PARSE,PKCS12_R_INVALID_NULL_PKCS12_POINTER);
		return 0;
	}

	/* Allocate stack for ca certificates if needed */
	if ((ca != NULL) && (*ca == NULL)) {
		if (!(*ca = sk_X509_new_null())) {
			PKCS12err(PKCS12_F_PKCS12_PARSE,ERR_R_MALLOC_FAILURE);
			return 0;
		}
	}

	if ((licenses != NULL) && (*licenses == NULL)) 
	{
		if (!(*licenses = sk_ASN1_TYPE_new_null())) 
		{
			PKCS12err(PKCS12_F_PKCS12_PARSE, ERR_R_MALLOC_FAILURE);
			return 0;
		}
	}

	if(pkey) *pkey = NULL;
	if(cert) *cert = NULL;

	/* Check the mac */

	/* If password is zero length or NULL then try verifying both cases
	 * to determine which password is correct. The reason for this is that
	 * under PKCS#12 password based encryption no password and a zero length
	 * password are two different things...
	 */

	if(!pass || !*pass) {
		if(PKCS12_verify_mac(p12, NULL, 0)) pass = NULL;
		else if(PKCS12_verify_mac(p12, "", 0)) pass = "";
		else {
			PKCS12err(PKCS12_F_PKCS12_PARSE,PKCS12_R_MAC_VERIFY_FAILURE);
			goto err;
		}
	} else if (!PKCS12_verify_mac(p12, pass, -1)) {
		PKCS12err(PKCS12_F_PKCS12_PARSE,PKCS12_R_MAC_VERIFY_FAILURE);
		goto err;
	}

	if (!OpenIPMP_parse_pk12 (p12, pass, -1, pkey, cert, ca, licenses))
		{
		PKCS12err(PKCS12_F_PKCS12_PARSE,PKCS12_R_PARSE_ERROR);
		goto err;
		}

	return 1;

 err:

	if (pkey && *pkey) EVP_PKEY_free(*pkey);
	if (cert && *cert) X509_free(*cert);
	if (ca) sk_X509_pop_free(*ca, X509_free);
	return 0;

}

////////////////////////////////////////////////////////////////////////////////////////////////
CryptoManager::CryptoManager()
{
	MemMan::construct(&m_P12FilePath);
	MemMan::construct(&m_RandomNumberFilePath);

	//setup multithreading support
//	CRYPTO_thread_setup();

	/** this sets up the algorithm support so I can call EVP_get_cipherbyname..*/
	OpenSSL_add_all_algorithms();
//	ERR_load_crypto_strings();

	//set a default path
	setP12FilePath(".\\");

}

CryptoManager::~CryptoManager()
{
	MemMan::destruct(&m_P12FilePath);
	MemMan::destruct(&m_RandomNumberFilePath);

  EVP_cleanup();
  ERR_free_strings();
  CRYPTO_cleanup_all_ex_data();
  ERR_remove_state(0);
//  ENGINE_cleanup();
//  CONF_modules_unload(1);
//  ERR_clear_error();

	//clean up multithreading support
//	CRYPTO_thread_cleanup();
}

//P12FilePath
char* CryptoManager::getP12FilePath()
{
	return m_P12FilePath;
}

void CryptoManager::setP12FilePath(char* p_FilePath)
{
	MemMan::copy(&m_P12FilePath, p_FilePath);
}


//random number file path
void CryptoManager::setRandomNumberFilePath(char* p_RandomNumberFilePath)
{
	MemMan::copy(&m_RandomNumberFilePath, p_RandomNumberFilePath);
}

// initialize key
bool CryptoManager::randomizeKey(unsigned char* p_Key, int p_LengthInBytes)
{
	char buffer[200];
	const char* filename;

	assert(p_Key);
	assert(p_LengthInBytes > 0);

	/** if windows, use the entropy file created by WinRand.exe.  If linux, open /dev/random */

    if (m_RandomNumberFilePath == NULL) {
          filename = RAND_file_name(buffer, sizeof buffer);
		  setRandomNumberFilePath(buffer);
	}

	/** load the random number file */
    int bytes = RAND_load_file(m_RandomNumberFilePath, -1);

	/** get the key */
	if (!RAND_bytes(p_Key, p_LengthInBytes))
	{
		//TODO: throw an exception
		gLogger->logError("CryptoManager::randomizeKey : bad return code from RAND_bytes.");
		RAND_cleanup();
		return false; 
	}

	RAND_cleanup();
	return true;

}

bool CryptoManager::init(HashContext* p_Ctx, char* p_HashAlg=NULL)
{
	assert(p_Ctx);

	if (!p_HashAlg)
		p_Ctx->setHashType(EVP_sha1());
	else
	{
		//TODO check return codes from EVP_get_digestbyname..
		p_Ctx->setHashType(EVP_get_digestbyname(p_HashAlg));
	}

	/** initialize the HashCtx */
	p_Ctx->hashInit();

	return true;
}

bool CryptoManager::init(CipherContext* p_Ctx, char* p_KeyAlg=NULL, int p_KeyLengthInBits=0)
{
	unsigned char key[30];

	assert(p_Ctx);

	if (!p_KeyAlg)
	{
		//default to 128 blowfish
		p_Ctx->setCipher( (EVP_CIPHER*) EVP_bf_cfb());
		p_Ctx->setKeyLength(128);
	}
	else
	{
		assert(p_KeyLengthInBits > 0);
		p_Ctx->setCipher((struct evp_cipher_st*)EVP_get_cipherbyname(p_KeyAlg));
		p_Ctx->setKeyLength(p_KeyLengthInBits);
	}

	//generate random key
	if (!randomizeKey(key, EVP_MAX_KEY_LENGTH))
	{
		//TODO catch EXCeption and rethrow
		gLogger->logError("CryptoManager::init(CipherContxt) : bad return code from randomizeKey");
		return false;
	}

	/** CJM 3/27/02 set up the key NOTE: this function should not be used anymore...
		but I'm going to leave in the functionality for backward compatibility
	*/
	p_Ctx->setKeyBytes(key, EVP_MAX_KEY_LENGTH);

	/** CJM 3/27/02 this function should be used instead */
	OctetString keyObject;

	keyObject.octets = key;
	keyObject.len = (p_KeyLengthInBits/8);

	p_Ctx->setKey(&keyObject);

	return true;
}

void CryptoManager::generateKey(char* p_Alg, int p_LengthInBits)
{
	unsigned char key[30];

	randomizeKey(key, EVP_MAX_KEY_LENGTH);

	/** now I've got random key byte array.. construct a Cipher construct */
	EVP_CIPHER_CTX* ctx;
	EVP_CIPHER* cipher;
	unsigned char msg[50] = "this is  a test message.";
	char ivec[EVP_MAX_IV_LENGTH] = {0};  //zero for now
	int msgLen = strlen((char*)msg) + 1;
	int cipherTextLen = 0;


	ctx = (EVP_CIPHER_CTX*)malloc(sizeof(EVP_CIPHER_CTX));
	EVP_CIPHER_CTX_init(ctx);

	unsigned char* cipherText = (unsigned char*)malloc((msgLen+EVP_MAX_KEY_LENGTH)*sizeof(char));
	memset(cipherText, 0x00, msgLen+EVP_MAX_KEY_LENGTH);

	cipher = (struct evp_cipher_st*)EVP_get_cipherbyname(p_Alg);

	assert(cipher);

	if (!cipher) {
		//TODO: throw an exception 
    std::cout << "CryptoManager::generateKey : cannot construct Cipher instance." << std::endl;
		return;
	}

	EVP_EncryptInit(ctx, cipher, key, (unsigned char*)ivec);

	/** set the key length, default is 128 for our blowfish */
	int ret = EVP_CIPHER_CTX_set_key_length(ctx, p_LengthInBits/8);

	//TODO check ret
	
	int extLen;
	EVP_EncryptUpdate(ctx, cipherText, &cipherTextLen, msg, msgLen);
	EVP_EncryptFinal(ctx, &cipherText[cipherTextLen], &extLen);

	/** calculate total cipher text len */
	cipherTextLen += extLen;
	
	EVP_CIPHER_CTX_cleanup(ctx);

	free(cipherText);
	free(ctx);
}


//dump licenses
/**
	TODO: need to change the OpenSSL functions to add the list of ASN1_STRING entitlements to 
	the list of objects contained in the PKCS12 file - review PKCS12_create function to see
	what needs to be changed
*/
void CryptoManager::dumpEntitlements()
{
	PKCS12_SAFEBAG *bag;
	STACK_OF(ASN1_TYPE) *myEntitlements;
	ASN1_TYPE *thisEntitlement, *anotherEntitlement;
	ASN1_STRING* current;

	char* entitlement1 = "this is a test entitlement";
	char* entitlement2 = "this is another test entitlement";
	char buf[60];

	//create a new entitlement ASN1 type
	thisEntitlement = ASN1_TYPE_new();
//	anotherEntitlement = ASN1_TYPE_new();

	ASN1_TYPE_set_octetstring(thisEntitlement, (unsigned char*)entitlement1, strlen(entitlement1));
//	ASN1_TYPE_set_octetstring(anotherEntitlement, (unsigned char*)entitlement2, strlen(entitlement2));

	//create a new stack of ASN1_TYPEs
	myEntitlements = sk_ASN1_TYPE_new_null();

  std::cout << "current number of elements " << sk_num(myEntitlements) << std::endl;

	sk_ASN1_TYPE_push(myEntitlements, thisEntitlement);
//	sk_ASN1_TYPE_push(myEntitlements, anotherEntitlement);

  std::cout << "current number of elements " << sk_num(myEntitlements) << std::endl;

	//loop through the entitlements
	for (int j=0; j < sk_ASN1_TYPE_num(myEntitlements); j++)
	{
		char buf[60];
		ASN1_TYPE* currentValue = sk_ASN1_TYPE_value(myEntitlements, j);
		int bytes = ASN1_TYPE_get_octetstring(currentValue, (unsigned char*)buf, 60);  //last param is MAX_LENGTH
		if (bytes != -1)
			buf[bytes] = 0x00;

		printf(" curr value %s\n", buf);
	}

	//bag = createP12EntitlementSafeBag((char*)thisEntitlement, (int (__cdecl*)(void))i2d_ASN1_TYPE, NID_Entitlement, NID_EntitlementList);
}


/*** 
*
*		createDummyEntitlements
*/
STACK_OF(ASN1_TYPE)* CryptoManager::createDummyEntitlements()
{
	STACK_OF(ASN1_TYPE) *entitlementsList;
	ASN1_TYPE *thisEntitlement, *anotherEntitlement;
	ASN1_STRING* current;

	char entitlement1[12048];
	char entitlement2[12048];

	for (int j=0; j < 12048; j++)
	{
		entitlement1[j] = 'a';
		entitlement2[j] = 'b';
	}

//	strcpy(entitlement1, "this is a test");
//	strcpy(entitlement2, "this is another test");

	//create a new entitlement ASN1 type
	thisEntitlement = ASN1_TYPE_new();
	anotherEntitlement = ASN1_TYPE_new();

	ASN1_TYPE_set_octetstring(thisEntitlement, (unsigned char*)entitlement1, 12048);
	ASN1_TYPE_set_octetstring(anotherEntitlement, (unsigned char*)entitlement2, 12048);

	//create a new stack of ASN1_TYPEs
	entitlementsList = sk_ASN1_TYPE_new_null();

	sk_ASN1_TYPE_push(entitlementsList, thisEntitlement);
	sk_ASN1_TYPE_push(entitlementsList, anotherEntitlement);

	return entitlementsList;
}


/** OpenIPMP/OpenSSL 9.7 
	
	Implementation of PKCS12_pack_safebag
*/
static PKCS12_SAFEBAG *OpenIPMP_PKCS12_pack_safebag (char *obj, int (*i2d)(), int nid1, int nid2 )
{
	PKCS12_BAGS *bag;
	PKCS12_SAFEBAG *safebag;
	if (!(bag = PKCS12_BAGS_new ())) {
		PKCS12err(PKCS12_F_PKCS12_PACK_SAFEBAG, ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	bag->type = OBJ_nid2obj(nid1);
#ifdef MACOSX
	if (!ASN1_pack_string(obj, (int (*)(...))i2d, &bag->value.octet)) {
#else
	if (!ASN1_pack_string(obj, (int (*)())i2d, &bag->value.octet)) {
#endif
		PKCS12err(PKCS12_F_PKCS12_PACK_SAFEBAG, ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	if (!(safebag = PKCS12_SAFEBAG_new ())) {
		PKCS12err(PKCS12_F_PKCS12_PACK_SAFEBAG, ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	safebag->value.bag = bag;
	safebag->type = OBJ_nid2obj(nid2);
	return safebag;
}



/** 
*
*
*	modified OpenSSL function PKCS12* PKCS12_create().
*
*/
PKCS12* CryptoManager::createP12Instance(char *pass, char *name, EVP_PKEY *pkey, X509 *cert,
	     STACK_OF(X509) *ca, STACK_OF(ASN1_TYPE) *licenses, int nid_key, int nid_cert, int iter, int mac_iter,
	     int keytype)
{
	PKCS12 *p12;
	STACK_OF(PKCS12_SAFEBAG) *bags;
	STACK_OF(PKCS7) *safes;
	PKCS12_SAFEBAG *bag;
	PKCS8_PRIV_KEY_INFO *p8;
	PKCS7 *authsafe;
	X509 *tcert;
	int i;
	unsigned char keyid[EVP_MAX_MD_SIZE];
	unsigned int keyidlen;

	/* Set defaults */
	if(!nid_cert) nid_cert = NID_pbe_WithSHA1And40BitRC2_CBC;
	if(!nid_key) nid_key = NID_pbe_WithSHA1And3_Key_TripleDES_CBC;
	if(!iter) iter = PKCS12_DEFAULT_ITER;
	if(!mac_iter) mac_iter = 1;

	if(!pkey || !cert) {
		PKCS12err(PKCS12_F_PKCS12_CREATE,PKCS12_R_INVALID_NULL_ARGUMENT);
		return NULL;
	}

	if(!X509_check_private_key(cert, pkey)) return NULL;

	if(!(bags = sk_PKCS12_SAFEBAG_new_null ())) {
		PKCS12err(PKCS12_F_PKCS12_CREATE,ERR_R_MALLOC_FAILURE);
		return NULL;
	}

	/* Add user certificate */

	/** OpenIPMP/OpenSSL 9.7 now calling the old 'macros' (which are now functions) 
	*/	
	if(!(bag = M_PKCS12_x5092certbag(cert))) return NULL;

/** OpenIPMP/OpenSSL 9.7  this was the old implementation of M_PKCS12_x5092certbag
#ifdef UNIXSTYLE 
	if (!(bag = PKCS12_pack_safebag((char*)cert, (int (*)(void))i2d_X509, NID_x509Certificate, NID_certBag))) return NULL;
#else
	if (!(bag = PKCS12_pack_safebag((char*)cert, (int (__cdecl *)(void))i2d_X509, NID_x509Certificate, NID_certBag))) return NULL;
#endif
*/
	if(name && !PKCS12_add_friendlyname(bag, name, -1)) return NULL;
	X509_digest(cert, EVP_sha1(), keyid, &keyidlen);
	if(!PKCS12_add_localkeyid(bag, keyid, keyidlen)) return NULL;

	if(!sk_PKCS12_SAFEBAG_push(bags, bag)) {
		PKCS12err(PKCS12_F_PKCS12_CREATE,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	
	/* Add all other certificates */
	if(ca) {
		for(i = 0; i < sk_X509_num(ca); i++) {
			tcert = sk_X509_value(ca, i);

		/** OpenIPMP/OpenSSL 9.7 now calling the old 'macros' (which are now functions */
			if(!(bag = M_PKCS12_x5092certbag(tcert))) return NULL;

/** OpenIPMP/OpenSSL this was the old implementation of M_PKCS12_x5092certbag
#ifdef UNIXSTYLE 
//			if(!(bag = PKCS12_pack_safebag((char*)tcert, (int (*)(void))i2d_X509, NID_x509Certificate, NID_certBag))) return NULL;

#else
//			if(!(bag = PKCS12_pack_safebag((char*)tcert, (int (__cdecl *)(void))i2d_X509, NID_x509Certificate, NID_certBag))) return NULL;
#endif
*/
			if(!sk_PKCS12_SAFEBAG_push(bags, bag)) {
				PKCS12err(PKCS12_F_PKCS12_CREATE,ERR_R_MALLOC_FAILURE);
				return NULL;
			}
		}
	}

	/** CJM add license processing 
		sequence is similar to the ca cert list above
		create a new safebag for each user entitlement and push it 
		onto the safebag array
	*/
	if (licenses)
	{
		for (i = 0; i < sk_ASN1_TYPE_num(licenses); i++) 
		{
			/** TODO: CJM 5/7/02  
				Need to fix the OID usage here for Licenses and LicenseList
				However, this would require changes to the openssl build..so for now a hack
			*/
			ASN1_TYPE* currentValue = sk_ASN1_TYPE_value(licenses, i);

			/** OpenIPMP/OpenSSL 9.7 Now calling re-implemented PKCS12_pack_safebag function.. */
#ifdef UNIXSTYLE 
			if (!(bag = OpenIPMP_PKCS12_pack_safebag((char*)currentValue, (int (*)(void))i2d_ASN1_TYPE, NID_License, NID_LicenseList))) return NULL;
#else
			if (!(bag = OpenIPMP_PKCS12_pack_safebag((char*)currentValue, (int (__cdecl *)(void))i2d_ASN1_TYPE, NID_License, NID_LicenseList))) return NULL;
#endif
			if(!sk_PKCS12_SAFEBAG_push(bags, bag)) {
				PKCS12err(PKCS12_F_PKCS12_CREATE,ERR_R_MALLOC_FAILURE);
				return NULL;
			}
		}
	}

	/* Turn certbags into encrypted authsafe */
	authsafe = PKCS12_pack_p7encdata (nid_cert, pass, -1, NULL, 0,
					  iter, bags);
	sk_PKCS12_SAFEBAG_pop_free(bags, PKCS12_SAFEBAG_free);

	if (!authsafe) return NULL;

	if(!(safes = sk_PKCS7_new_null ())
	   || !sk_PKCS7_push(safes, authsafe)) {
		PKCS12err(PKCS12_F_PKCS12_CREATE,ERR_R_MALLOC_FAILURE);
		return NULL;
	}

	/* Make a shrouded key bag */
	if(!(p8 = EVP_PKEY2PKCS8 (pkey))) return NULL;
	if(keytype && !PKCS8_add_keyusage(p8, keytype)) return NULL;
	bag = PKCS12_MAKE_SHKEYBAG (nid_key, pass, -1, NULL, 0, iter, p8);
	if(!bag) return NULL;
	PKCS8_PRIV_KEY_INFO_free(p8);
        if (name && !PKCS12_add_friendlyname (bag, name, -1)) return NULL;
	if(!PKCS12_add_localkeyid (bag, keyid, keyidlen)) return NULL;
	if(!(bags = sk_PKCS12_SAFEBAG_new_null())
	   || !sk_PKCS12_SAFEBAG_push (bags, bag)) {
		PKCS12err(PKCS12_F_PKCS12_CREATE,ERR_R_MALLOC_FAILURE);
		return NULL;
	}
	/* Turn it into unencrypted safe bag */
	if(!(authsafe = PKCS12_pack_p7data (bags))) return NULL;
	sk_PKCS12_SAFEBAG_pop_free(bags, PKCS12_SAFEBAG_free);
	if(!sk_PKCS7_push(safes, authsafe)) {
		PKCS12err(PKCS12_F_PKCS12_CREATE,ERR_R_MALLOC_FAILURE);
		return NULL;
	}

	if(!(p12 = PKCS12_init (NID_pkcs7_data))) return NULL;

	/** OpenIPMP/OpenSSL 9.7 call 'old' macro function now */
	if ( !M_PKCS12_pack_authsafes( p12, safes ) ) return NULL;

/* CJM line used to be if(!M_PKCS12_pack_authsafes (p12, safes)) return NULL; */
/** OpenIPMP/OpenSSL 9.7
#ifdef LINUX
	if (!ASN1_seq_pack_PKCS7((safes), (int (*)(void))i2d_PKCS7, &(p12)->authsafes->d.data->data, &(p12)->authsafes->d.data->length)) return NULL;
#else
	if (!ASN1_seq_pack_PKCS7((safes), (int (__cdecl *)(void))i2d_PKCS7, &(p12)->authsafes->d.data->data, &(p12)->authsafes->d.data->length)) return NULL;
#endif
*/
	sk_PKCS7_pop_free(safes, PKCS7_free);

	if(!PKCS12_set_mac (p12, pass, -1, NULL, 0, mac_iter, NULL))
	    return NULL;

	return p12;

}


//storeP12Instance
bool CryptoManager::storeP12Instance(UserContext* p_Ctx)
{
	PKCS12* p12;
	FILE *fp;
	char    pchMyP12[ MAX_PATH                                 +
                   ( sizeof( FILE_DELIMITER) - 1)               +
                   ( sizeof( P12_FILE)        - 1)];
	STACK_OF(ASN1_TYPE)* licenses=NULL;

	//TODO throw an exception if errors
	assert(p_Ctx);

	/**CJM 11-19-2002 handle no trailing slash */
	if (m_P12FilePath != NULL)
	{
		if ((m_P12FilePath[strlen(m_P12FilePath)] == '\\') || (m_P12FilePath[strlen(m_P12FilePath)] == '/') )
			sprintf( pchMyP12, "%s%s%s", m_P12FilePath, p_Ctx->getUserName(), P12_FILE);
		else
			sprintf( pchMyP12, "%s/%s%s", m_P12FilePath, p_Ctx->getUserName(), P12_FILE);
	}

	if (!(fp = fopen(pchMyP12, "rb"))) {
		gLogger->logError("CryptoManager::storeP12Instance : could not open output P12 file.");
		return false;
	}

	EVP_PKEY* testEnv = EVP_PKEY_new();

	//assign the keypair to the envelope..
	int ret = EVP_PKEY_assign_RSA(testEnv,p_Ctx->getPrivateKey());

	//loop over the licensesMap.. turn them into ASN1 strings to be saved in the p12 file
	HashMap& map = p_Ctx->getLicenseMap();

	if (map.size())
	{
		//create a new stack of ASN1_TYPEs
		licenses = sk_ASN1_TYPE_new_null();
		
		for (License* lic = (License*)map.first(); lic; lic = (License*)map.next())
		{
			ASN1_TYPE* newLicense = ASN1_TYPE_new();


			ASN1_OCTET_STRING* newLicenseOS = ASN1_OCTET_STRING_new ();


	//		ASN1_TYPE_set_octetstring(newLicense, (unsigned char*)lic->toString(), strlen(lic->toString()));


			ASN1_OCTET_STRING_set(newLicenseOS, (unsigned char*)lic->toString(), strlen(lic->toString() ) );
		 	ASN1_TYPE_set(newLicense, newLicenseOS->type, newLicenseOS);


			sk_ASN1_TYPE_push(licenses, newLicense);
		}
	}

	p12 = createP12Instance(p_Ctx->getPassword(), p_Ctx->getUserName(), testEnv, p_Ctx->getUserCert(), p_Ctx->getCaCertChain(), licenses, 0,0,0,0,0);

	if (!(fp = fopen(pchMyP12, "wb"))) {
	  if (licenses)
	  {
		  for (int i =0; i < sk_ASN1_TYPE_num(licenses); i++) 
			  ASN1_TYPE_free(sk_ASN1_TYPE_value(licenses, i));

		  sk_ASN1_TYPE_free(licenses);
		  licenses = NULL;
	  }
    OPENSSL_free(testEnv);
		gLogger->logError("CryptoManager::storeP12Instance : could not open p12 for writing.");
		return false;
	}

	//write out the new p12 instance
	int retcode =  i2d_PKCS12_fp(fp, p12);

	//check ret code 
	PKCS12_free(p12);

	//delete the existing stack
	if (licenses)
	{
		for (int i =0; i < sk_ASN1_TYPE_num(licenses); i++) 
			ASN1_TYPE_free(sk_ASN1_TYPE_value(licenses, i));

		sk_ASN1_TYPE_free(licenses);
		licenses = NULL;
	}
  OPENSSL_free(testEnv);

	fclose(fp);

	return true;
}


bool CryptoManager::decodeLicense(XMLDocument* p_LicenseDoc, 
								  char* p_XMLBuf,
								  char** p_HashKey, 
								  License** p_License)
{
		if (p_LicenseDoc == NULL)
			return false;

		//first try to decode ODRL
		if ((p_LicenseDoc->decode(p_XMLBuf, "o-ex:rights"))) 
		{
			*p_License = new ODRLLicense();
			((ODRLLicense*)(*p_License))->setBytes(p_XMLBuf);
			*p_HashKey = p_LicenseDoc->getString("o-ex:agreement.o-ex:asset.o-ex:context.o-dd:uid.o-doi:DOI");
		}
		else 
		{
			//next try to decode MPEG REL
			if ((p_LicenseDoc->decode(p_XMLBuf, "licenseGroup")))
			{
				*p_License = new MPEGRELLicense();
				((MPEGRELLicense*)(*p_License))->setBytes(p_XMLBuf);
				*p_HashKey = p_LicenseDoc->getString("license.grant.mx:diReference.mx:identifier");
			}
			else 
			{
				gLogger->logWarning("CryptoManager::Login : Cannot Decode license.");
				return false;
			}
		}

	return true;
}



//local login
bool CryptoManager::Login(UserContext* p_Ctx)
{
	//login into the pkcs#12 file
	FILE *fp;
	EVP_PKEY *pkey;
	X509 *cert;
	STACK_OF(X509) *ca = NULL;
	STACK_OF(ASN1_TYPE) *licenseList = NULL;
	PKCS12 *p12, *p12new;
	int i;
	char    pchMyP12[ MAX_PATH                                 +
                   ( sizeof( FILE_DELIMITER) - 1)               +
                   ( sizeof( P12_FILE)        - 1)];

	/** TODO: check Username and Password throw exception */
	if ( (!p_Ctx->getUserName()) || (!p_Ctx->getPassword()) ) {
		throw EXCEPTION(Exception::P12_MISSING_USER_AUTH_DATA);
	}
	
	/**CJM 11-19-2002 handle no trailing slash */
	if (m_P12FilePath != NULL)
	{
		if ((m_P12FilePath[strlen(m_P12FilePath)-1] == '\\') || (m_P12FilePath[strlen(m_P12FilePath)-1] == '/') )
			sprintf( pchMyP12, "%s%s%s", m_P12FilePath, p_Ctx->getUserName(), P12_FILE);
		else
			sprintf( pchMyP12, "%s/%s%s", m_P12FilePath, p_Ctx->getUserName(), P12_FILE);
	}

	if (!(fp = fopen(pchMyP12, "rb"))) {
		throw EXCEPTION(Exception::P12_MISSING_BASEPATH);
	}
	p12 = d2i_PKCS12_fp(fp, NULL);
	fclose (fp);

	if (!p12) {
		throw EXCEPTION(Exception::P12_ASN1_DECODE_ERROR);
	}

	if (!parseP12Instance(p12, p_Ctx->getPassword(), &pkey, &cert, &ca, &licenseList)) {
		throw EXCEPTION(Exception::P12_TOKEN_PARSE_ERROR);
	}

	//now you're logged in..
	p_Ctx->setLoggedInLocally(true);

	//set the licenses for this user  THIS IS DEPRECATED FUNCTIONALITY
	p_Ctx->setLicenses(licenseList);

	/** build the license map for this user..
	*/
	if (licenseList)
	{
		if (sk_ASN1_TYPE_num(licenseList) > 0)
		{
			char buf[25000];
			XMLDocument pLicenseDoc;
			for (int i=0; i < sk_ASN1_TYPE_num(licenseList); i++)
			{
				//LAME..  puts a cap on the size of an License
				ASN1_TYPE* currentValue = sk_ASN1_TYPE_value(licenseList, i);
				int bytes = ASN1_TYPE_get_octetstring(currentValue, (unsigned char*)buf, 25000);  //last param is MAX_LENGTH
				if (bytes != -1)
					buf[bytes] = 0x00;

				//TODO need to have a tag in the original license that determines what
				//	   kind of license it is (XRML, ODRL) so I know which object to create
				License* newLicense = NULL;
				char* dID = NULL;


				/** CJM hack to handle new ASN1 strings in openssl9.7 */
		//		char* buf2 = &(buf[4]);

				/** CJM 4/14/03 try to decode the MPEGREL or ODLRL license */
				if (!decodeLicense(&pLicenseDoc, buf, &dID, &newLicense))
					continue;

				p_Ctx->addLicenseToMap(dID, newLicense);
				delete[] dID;
			}
		}
	}
	
	/** ASN1 encode the PrivateKey, cert, and P12object and store them as OctetStrings */
	unsigned char* pSave=NULL;
	unsigned char* buffer=NULL;
	int length = 0;
	OctetString* temp = new OctetString();
	RSA* rsaPriv = NULL;

	/** set the private Key */
	rsaPriv = pkey->pkey.rsa;
	p_Ctx->setPrivateKey(rsaPriv);

	/** ASN.1 encode the private key and set it */
	length = i2d_RSAPrivateKey(rsaPriv, NULL);

	buffer = (unsigned char*)malloc(sizeof(unsigned char)*length);
	pSave = buffer;
	//this is going to set the addr of p to the end of the buffer, make sure you set it back to the beginning
	length = i2d_RSAPrivateKey(rsaPriv, &pSave);

	/* test reconstruction and envelope set 
	EVP_PKEY* testEnv = EVP_PKEY_new();

	pSave = buffer;

	RSA* testPriv = d2i_RSAPrivateKey(NULL, &pSave, length);

		//assign the keypair to the envelope..
	int ret = EVP_PKEY_assign_RSA(testEnv,testPriv);
	*/

	temp->octets = buffer;
	temp->len = length;

	p_Ctx->setPrivateKeyASN1(temp);

	free(buffer);

	//now ASN.1 encode the certificate
	p_Ctx->setUserCert(cert);
	length = i2d_X509(cert, NULL);

	if (length)
		buffer = (unsigned char*)malloc(sizeof(unsigned char)*length);
	else
	{
		//TODO throw exception
		//gLogger->logError("CryptoManager::Login: could not ASN1-encode user certificate.");
		return false;
	}

	pSave = buffer;
	length = i2d_X509(cert, &pSave);

	temp->octets = buffer;
	temp->len = length;

	p_Ctx->setUserCertASN1(temp);

	/** set the ca cert chain attre */
	p_Ctx->setCaCertChain(ca);

	free(buffer);
	free(temp);

	//destroy the local private key, cert, ca cert list, and licenses
	EVP_PKEY_free(pkey);
	X509_free(cert);
	PKCS12_free(p12);

	for (int j=0; j < sk_X509_num(ca); j++)
		X509_free(sk_X509_value(ca, j));

	for (int jj=0; jj < sk_ASN1_TYPE_num(licenseList); jj++)
		ASN1_TYPE_free(sk_ASN1_TYPE_value(licenseList, jj));

	sk_X509_free(ca);
	sk_ASN1_TYPE_free(licenseList);
	ca = NULL;
	licenseList = NULL;
	pkey = NULL;
	cert = NULL;

	return true;
}
