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
#include "busobj/IPMP_MediaContext.h"
#include "squashxml/tools/FileLogger.h"

// Initialize the decryption mutex object 
//#ifndef __OPENIPMPSINGLETHREADED
//SDL_mutex* IPMP_MediaContext::m_DecryptMutex = NULL;
//#endif

// TODO: Should just include a header file that defines NULL
//#define NULL	0

IPMP_MediaContext::IPMP_MediaContext()
{
	// initialize member references to complex objects
    m_IPMP_ContentIdentity = NULL;
    m_CipherCtx = NULL;
}

IPMP_MediaContext::IPMP_MediaContext(IPMP_MediaContext* right)
{

	if (!right)
		return;

	// construct copies of complex input objects and set member references
	if ( right->get_IPMP_ContentIdentity() )
		m_IPMP_ContentIdentity = new IPMP_ContentIdentity( (IPMP_ContentIdentity*) right->get_IPMP_ContentIdentity());
	else 
		m_IPMP_ContentIdentity = NULL;
	if ( right->get_CipherContext() )
		m_CipherCtx = new CipherContext( (CipherContext &) *right->get_CipherContext() );
	else
		m_CipherCtx = NULL;
}

IPMP_MediaContext::IPMP_MediaContext(IPMP_ContentIdentity* pIPMP_ContentId, CipherContext* pCipherCtx)
{
	// construct copies of complex input objects and set member references
	if ( pIPMP_ContentId )
		m_IPMP_ContentIdentity = new IPMP_ContentIdentity(pIPMP_ContentId);
	else 
		m_IPMP_ContentIdentity = NULL;
	if ( pCipherCtx )
		m_CipherCtx = new CipherContext(*pCipherCtx);
	else
		m_CipherCtx = NULL;
}

IPMP_MediaContext::~IPMP_MediaContext()
{
	// free memory: (destruct) complex objects pointed to be member references
    if (m_IPMP_ContentIdentity)
        delete m_IPMP_ContentIdentity;
    if (m_CipherCtx)
	delete m_CipherCtx;
}

// IPMP_ContentIdentity
const IPMP_ContentIdentity* IPMP_MediaContext::get_IPMP_ContentIdentity () const
{ return m_IPMP_ContentIdentity; }
void IPMP_MediaContext::set_IPMP_ContentIdentity (IPMP_ContentIdentity* value)
{
	if (m_IPMP_ContentIdentity)
		delete m_IPMP_ContentIdentity;
	m_IPMP_ContentIdentity = new IPMP_ContentIdentity(value);
}

// Cipher
const CipherContext* IPMP_MediaContext::get_CipherContext () const
{ return m_CipherCtx; }
void IPMP_MediaContext::set_CipherContext (CipherContext* value)
{
	if (m_CipherCtx)
		delete m_CipherCtx;
	m_CipherCtx = new CipherContext( (CipherContext &) *value );
}

// protected flag
const bool IPMP_MediaContext::get_ProtectedFlag () const
{
    // TODO: This needs to be reworked
//    if (!isSetup() )
//        return(NULL);	// TODO: this should throw an exception
//    else
	if (m_IPMP_ContentIdentity)
        return( m_IPMP_ContentIdentity->get_ProtectedFlag() );
	else
		return(false);
}
void IPMP_MediaContext::set_ProtectedFlag (bool value)
{
    // TODO: This needs to be reworked
//    if (!isSetup() )
//        return;		// TODO: this should throw an exception
//    else
	if (m_IPMP_ContentIdentity)
        m_IPMP_ContentIdentity->set_ProtectedFlag(value);
}

// encrypt
bool IPMP_MediaContext::ProtectMediaSample(unsigned char* buffer, int length)
{

    // only encrypt if ProtectedFlag is set
//    if ( get_ProtectedFlag() )
 //   {
	unsigned char* new_buffer = (unsigned char*) malloc ( (length + EVP_MAX_KEY_LENGTH) * sizeof(unsigned char*) );
	int curLen2 = 0;
	int curLen = (length + EVP_MAX_KEY_LENGTH) * sizeof(unsigned char*);

	m_CipherCtx->encryptInit ();
	m_CipherCtx->encryptUpdate (buffer, (int) length, new_buffer, (int*) &curLen);
	if (curLen > length) {
		gLogger->logError("encryptUpdate() returned too many bytes; Must be using block cipher mode. Use overloaded encryptSample() with in and out buffers instead.");
		return(false);
	}

	m_CipherCtx->encryptFinal(&new_buffer[curLen], (int*) &curLen2);
	if (curLen2) {
		gLogger->logError("encryptFinal() returned bytes; Must be using block cipher mode, or other error. Use overloaded encryptSample() with in and out buffers instead.");
//		curLen += curLen2;        (this would only be for the overloaded function - see below)
		return(false);
	}

        // TODO: In the future, a updated Hash will also be calculated here
        // get_IPMP_ContentIdentity()->get_ContentHash()->hashUpdate (buffer, curLen);

        // copy memory back to its original location (remember: length=curLen) and delete temporary buffer
	memcpy(buffer, new_buffer, length);
	delete new_buffer;
  //  }

    return(true);
}

bool IPMP_MediaContext::ProtectMediaSample(unsigned char* in_buffer, int in_length, unsigned char* out_buffer, int out_length)
{

	return(true);
}


// decrypt
bool IPMP_MediaContext::UnlockMediaSample(unsigned char* buffer, int length)
{

    // only decrypt if ProtectedFlag is set
   // if ( get_ProtectedFlag() )
   // {
 
		unsigned char* new_buffer = (unsigned char*) malloc ( length * sizeof(unsigned char*) );
		int curLen = length;
		int curLen2 = 0;

//	#ifndef __OPENIPMPSINGLETHREADED
//		//synchronize access to the security lib
//		if ( SDL_LockMutex(IPMP_MediaContext::m_DecryptMutex) < 0 ) 
//		{
//			fprintf(stderr, "Couldn't lock mutex: %s", SDL_GetError());
//		}
//	#endif

		m_CipherCtx->decryptInit ();
		m_CipherCtx->decryptUpdate (buffer, length, new_buffer, &curLen);
		m_CipherCtx->decryptFinal( &(new_buffer)[length], &curLen2);
		if (curLen2) {
				gLogger->logError("decryptFinal() returned bytes; Must be using block cipher mode, or other error. Use overloaded encryptSample() with in and out buffers instead.");
				curLen += curLen2;
				return(false);
		}

		if (curLen != length) {
				gLogger->logError("decryptUpdate() returned too few bytes; Must be using block cipher mode. Use overloaded decryptSample() with in and out buffers instead.");
				return(false);
			}
            
			// copy memory back to its original location (remember: length=curLen) and delete temporary buffer
		memcpy(buffer, new_buffer, length);
		delete new_buffer;

//	#ifndef __OPENIPMPSINGLETHREADED
//		if ( SDL_UnlockMutex(IPMP_MediaContext::m_DecryptMutex) < 0 ) 
//		{
//			fprintf(stderr, "Couldn't unlock mutex: %s", SDL_GetError());
//		}
//	#endif

		return(true);

    //} // if ( get_ProtectedFlag() )
    return(true);

}

bool IPMP_MediaContext::UnlockMediaSample(unsigned char* in_buffer, int in_length, unsigned char* out_buffer, int out_length)
{
	return(true);
}

bool IPMP_MediaContext::createMutex()
{

//#ifndef __OPENIPMPSINGLETHREADED
//	if ( (IPMP_MediaContext::m_DecryptMutex=SDL_CreateMutex()) == NULL ) {
//		fprintf(stderr, "Couldn't create mutex: %s\n", SDL_GetError());
//		return false;
//		}
//#endif

	return true;
}
