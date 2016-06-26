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
#include <malloc.h>
#include <stdio.h>

#include "busobj/RightsHost.h"
#include "tools/MemMan.h"

// Class RightsHost 

RightsHost::RightsHost()
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_URL);
    MemMan::construct(&m_Port);
	MemMan::construct(&m_XML_str);
}

RightsHost::RightsHost(RightsHost* right)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_URL);
    MemMan::construct(&m_Port);
	MemMan::construct(&m_XML_str);

	// copy complex member variables from input object
    MemMan::copy(&m_URL, (char*) right->get_URL());
    MemMan::copy(&m_Port, right->get_Port());
	MemMan::copy(&m_XML_str, (char*) right->get_XML_str());
}

RightsHost::~RightsHost()
{
	// free memory: (destruct) complex member variables
    MemMan::destruct(&m_URL);
    MemMan::destruct(&m_Port);
	MemMan::destruct(&m_XML_str);
}

// Get and Set Operations for Class Attributes

/** RightsHost URL string */   
const char* RightsHost::get_URL () const
{ return m_URL; }
void RightsHost::set_URL (char* pValue)
{ MemMan::copy(&m_URL, pValue); }

/** RightsHost Port */   
const int RightsHost::get_Port () const
{ return m_Port; }
void RightsHost::set_Port (int value)
{ MemMan::copy(&m_Port, value); }

// raw XML string
const char* RightsHost::get_XML_str () const
{ return m_XML_str; }
void RightsHost::set_XML_str (char* value)
{ MemMan::copy(&m_XML_str, value); }

