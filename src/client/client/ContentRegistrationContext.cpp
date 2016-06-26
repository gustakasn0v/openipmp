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

#include "crypto/CryptoManager.h"	// must include prior to including crypto/CipherContext.h
#include "client/ContentRegistrationContext.h"

#include "tools/MemMan.h"
#include "squashxml/tools/ByteArray.h"
#include "squashxml/tools/FileTool.h"
#include "squashxml/tools/Date.h"
#include "squashxml/xml/XMLDocument.h"

// constructor
ContentRegistrationContext::ContentRegistrationContext()
{
    // initialize complex member attributes
    MemMan::construct(&m_username);
    MemMan::construct(&m_password);
    MemMan::construct(&m_ip);
    MemMan::construct(&m_xmlmetafile);
    MemMan::construct(&m_usedsigfile);
    MemMan::construct(&m_usekeyfile);
    MemMan::construct(&m_writekeyfile);
    MemMan::construct(&m_writemasterDOIfile);
    MemMan::construct(&m_writeinstanceDOIfile);
    MemMan::construct(&m_writedsigfile);

    // initialize simple member attributes
    m_port = NULL;
    m_secure = false;
}

// copy constructor
ContentRegistrationContext::ContentRegistrationContext(ContentRegistrationContext* right)
{
    // initialize complex member attributes
    MemMan::construct(&m_username);
    MemMan::construct(&m_password);
    MemMan::construct(&m_ip);
    MemMan::construct(&m_xmlmetafile);
    MemMan::construct(&m_usedsigfile);
    MemMan::construct(&m_usekeyfile);
    MemMan::construct(&m_writekeyfile);
    MemMan::construct(&m_writemasterDOIfile);
    MemMan::construct(&m_writeinstanceDOIfile);
    MemMan::construct(&m_writedsigfile);

    // initialize complex member attributes
    MemMan::copy(&m_username, (char*) right->get_username());
    MemMan::copy(&m_password, (char*) right->get_password());
    MemMan::copy(&m_ip, (char*) right->get_ip());
    MemMan::copy(&m_xmlmetafile, (char*) right->get_xmlmetafile());
    MemMan::copy(&m_usedsigfile, (char*) right->get_usedsigfile());
    MemMan::copy(&m_usekeyfile, (char*) right->get_usekeyfile());
    MemMan::copy(&m_writekeyfile, (char*) right->get_writekeyfile());
    MemMan::copy(&m_writemasterDOIfile, (char*) right->get_writemasterDOIfile());
    MemMan::copy(&m_writeinstanceDOIfile, (char*) right->get_writeinstanceDOIfile());
    MemMan::copy(&m_writedsigfile, (char*) right->get_writedsigfile());

    // initialize simple member attributes
    m_port = right->get_port();
    m_secure = right->get_secure();
}

// destructor
ContentRegistrationContext::~ContentRegistrationContext()
{
    // destroy complex member attributes
    MemMan::destruct(&m_username);
    MemMan::destruct(&m_password);
    MemMan::destruct(&m_ip);
    MemMan::destruct(&m_xmlmetafile);
    MemMan::destruct(&m_usedsigfile);
    MemMan::destruct(&m_usekeyfile);
    MemMan::destruct(&m_writekeyfile);
    MemMan::destruct(&m_writemasterDOIfile);
    MemMan::destruct(&m_writeinstanceDOIfile);
    MemMan::destruct(&m_writedsigfile);
}

// Implementation

// Get and Set Operations for Class Attributes

// username
const char* ContentRegistrationContext::get_username () const
{ return m_username; }
void ContentRegistrationContext::set_username (char* value)
{ MemMan::copy(&m_username, value); }

// password
const char* ContentRegistrationContext::get_password () const
{ return m_password; }
void ContentRegistrationContext::set_password (char* value)
{ MemMan::copy(&m_password, value); }

// ip address
const char* ContentRegistrationContext::get_ip () const
{ return m_ip; }
void ContentRegistrationContext::set_ip (char* value)
{ MemMan::copy(&m_ip, value); }

// port
const int ContentRegistrationContext::get_port () const
{ return m_port; }
void ContentRegistrationContext::set_port (int value)
{ m_port = value; }

// xml meta file
const char* ContentRegistrationContext::get_xmlmetafile () const
{ return m_xmlmetafile; }
void ContentRegistrationContext::set_xmlmetafile (char* value)
{ MemMan::copy(&m_xmlmetafile, value); }

// use digital signature file
const char* ContentRegistrationContext::get_usedsigfile () const
{ return m_usedsigfile; }
void ContentRegistrationContext::set_usedsigfile (char* value)
{ MemMan::copy(&m_usedsigfile, value); }

// use key data file
const char* ContentRegistrationContext::get_usekeyfile () const
{ return m_usekeyfile; }
void ContentRegistrationContext::set_usekeyfile (char* value)
{ MemMan::copy(&m_usekeyfile, value); }

// write key data file
const char* ContentRegistrationContext::get_writekeyfile () const
{ return m_writekeyfile; }
void ContentRegistrationContext::set_writekeyfile (char* value)
{ MemMan::copy(&m_writekeyfile, value); }

// write master DOI file
const char* ContentRegistrationContext::get_writemasterDOIfile () const
{ return m_writemasterDOIfile; }
void ContentRegistrationContext::set_writemasterDOIfile (char* value)
{ MemMan::copy(&m_writemasterDOIfile, value); }

// write instance DOI file
const char* ContentRegistrationContext::get_writeinstanceDOIfile () const
{ return m_writeinstanceDOIfile; }
void ContentRegistrationContext::set_writeinstanceDOIfile (char* value)
{ MemMan::copy(&m_writeinstanceDOIfile, value); }

// write digital signature file
const char* ContentRegistrationContext::get_writedsigfile () const
{ return m_writedsigfile; }
void ContentRegistrationContext::set_writedsigfile (char* value)
{ MemMan::copy(&m_writedsigfile, value); }

// secure flag
const bool ContentRegistrationContext::get_secure () const
{ return m_secure; }
void ContentRegistrationContext::set_secure (bool value)
{ m_secure = value; }
