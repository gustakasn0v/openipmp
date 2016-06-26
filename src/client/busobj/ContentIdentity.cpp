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
#include "busobj/ContentIdentity.h"

// TODO: Should just include a header file that defines NULL
#define NULL	0

// Class ContentIdentity 
ContentIdentity::ContentIdentity()
{
}


ContentIdentity::~ContentIdentity()
{
}

// isSetup
const bool ContentIdentity::isSetup ()
{ return m_isSetupFlag; }

// DigitalSignature
const DigitalSignature* ContentIdentity::get_DigitalSignature () const
{ return m_DigitalSignature; }
void ContentIdentity::set_DigitalSignature (DigitalSignature* value)
{
	if (m_DigitalSignature)
		delete m_DigitalSignature;
	m_DigitalSignature = new DigitalSignature(value);
}
