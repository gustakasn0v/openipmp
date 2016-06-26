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


#ifndef MPEGRELLICENSE_HPP
#define MPEGRELLICENSE_HPP

/**
*	MPEGRELLicense.h
*
*	Copyright (c) 2003 Mutable, Inc.  All rights reserved.
*/
#include "tools/OlRaw.h"
#include "busobj/License.h"
#include "busobj/UserContext.h"
#include "squashxml/xml/XMLDocument.h"
#include <time.h>
#include "tools/OlMemMan.h"

class MPEGRELLicense : public License
{
private:
	char*		m_MPEGRELStream;  //raw XML stream...NULL TERMINATED!!!
	char*		m_Key;
	char		m_QueryRELTemplate[500];

public:

	/** constructors */
	MPEGRELLicense();

	MPEGRELLicense(MPEGRELLicense &right);

	//## Destructor (generated)
	~MPEGRELLicense();

    //## Assignment Operation (generated)
	const MPEGRELLicense & operator=(const MPEGRELLicense &right);

	//## Equality Operations (generated)
	int operator==(const MPEGRELLicense &right) const;

	int operator!=(const MPEGRELLicense &right) const;

	/**
	*
	*	authorize()  
	*
	*	@param unsigned char*  //TODO:  define the common elements to be passed to the authorization functions for 
	*									any rights language.
	*	@returns bool
	*/
	bool authorize(char*, UserContext*, char*, OctetString*);

	/**
	*	dup()
	*
	*	@param void
	*	@returns License*
	*/
	License* dup();

	/**
	*	toString()   returns null-terminated string representation of the license
	*
	*	@param void
	*	@returns char*
	*/
	char* toString();

	/**
	*	setBytes()
	*
	*	sets the null-terminated XML stream
	*
	*	@param char*
	*	@returns void
	*/
	void setBytes(char*);

	/**
	*	getBytes()
	*
	*	@param void
	*	@returns char* (do not delete!)
	*/
	char* getBytes();

	/**
	*	setKey()
	*	lookup key for this license
	*
	*	@param char*
	*	@returns void
	*/
	void setKey(char*);

	/**
	*	getKey()
	*
	*	@param void
	*	@returns char*
	*/
	char* getKey();

private:
	/**
	*	extractEncryptedKey()
	*
	*	@param XMLDocument*
	*	@param UserContext*
	*	@param OctetString*
	*	@returns bool
	*/
	bool extractEncryptedKey(XMLDocument* p_License, UserContext* p_Principal, OctetString* p_Key);

	/**
	*	verifyPermissions()
	*
	*	@param XMLDocument* License
	*	@param char* permission
	*	@param char* resource (contentID)
	*/
	bool verifyPermissions(XMLDocument* p_License, char* p_Permission, char* p_Resource);


    //## Assignment Operation (generated)
};


#endif