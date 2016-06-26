#ifndef LICENSE_HPP
#define LICENSE_HPP

#include "openssl/x509.h"
#include "busobj/UserContext.h"
#include "tools/MemMan.h"

class UserContext;

/**
*	License.h
*
*	Copyright (c) 2001 Mutable, Inc.  All rights reserved.
*/

//openssl stuff

class License 
{
	  
	public:

	/**
	*
	*	authorize()  
	*
	*	@param unsigned char*  //TODO:  define the common elements to be passed to the authorization functions for 
	*									any rights language.
	*	@returns bool
	*/
	virtual bool authorize(char*, UserContext*, char*, OctetString*) = 0;

	/**
		destructor 
	*/
	virtual ~License() {}

	/**
	*	dup()
	*
	*	@param void
	*	@returns License*
	*/
	virtual License* dup() = 0;

	/**
	*
	*	toString()
	*	@param void
	*	@returns char*
	*/
	virtual char* toString() = 0;

	/**
	*	setKey()
	*
	*	@param char*
	*	@returns void
	*/
	virtual void setKey(char*) = 0;

	/**
	*	getKey()
	*
	*	@param void
	*	@returns char*
	*/
	virtual char* getKey() = 0;

	/**
	*	setBytes()
	*
	*	@param unsigned char*
	*	@returns void
	*/

    //## Assignment Operation (generated)
};


#endif
