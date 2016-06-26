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
#include "busobj/DOI.h"
#include "tools/MemMan.h"

// Class DOI 

DOI::DOI()
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_DOI_idStr);
    MemMan::construct(&m_StructuralType);
    MemMan::construct(&m_Mode);
    MemMan::construct(&m_IdentifierType);
    MemMan::construct(&m_IdentifierValue);
    MemMan::construct(&m_Title);
    MemMan::construct(&m_PrimaryAgent);
    MemMan::construct(&m_PrimaryAgentRole);
    MemMan::construct(&m_XML_str);
}

DOI::DOI(DOI* right)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_DOI_idStr);
    MemMan::construct(&m_StructuralType);
    MemMan::construct(&m_Mode);
    MemMan::construct(&m_IdentifierType);
    MemMan::construct(&m_IdentifierValue);
    MemMan::construct(&m_Title);
    MemMan::construct(&m_PrimaryAgent);
    MemMan::construct(&m_PrimaryAgentRole);
    MemMan::construct(&m_XML_str);

	// copy complex member variables from input object
    MemMan::copy(&m_DOI_idStr, (char*) right->get_DOI_idStr());
    MemMan::copy(&m_StructuralType, (char*) right->get_StructuralType());
    MemMan::copy(&m_Mode, (char*) right->get_Mode());
    MemMan::copy(&m_IdentifierType, (char*) right->get_IdentifierType());
    MemMan::copy(&m_IdentifierValue, (char*) right->get_IdentifierValue());
    MemMan::copy(&m_Title, (char*) right->get_Title());
    MemMan::copy(&m_PrimaryAgent, (char*) right->get_PrimaryAgent());
    MemMan::copy(&m_PrimaryAgentRole, (char*) right->get_PrimaryAgentRole());
    MemMan::copy(&m_XML_str, (char*) right->get_XML_str());
}

DOI::~DOI()
{
	// free memory: (destruct) complex member variables
    MemMan::destruct(&m_DOI_idStr);
    MemMan::destruct(&m_StructuralType);
    MemMan::destruct(&m_Mode);
    MemMan::destruct(&m_IdentifierType);
    MemMan::destruct(&m_IdentifierValue);
    MemMan::destruct(&m_Title);
    MemMan::destruct(&m_PrimaryAgent);
    MemMan::destruct(&m_PrimaryAgentRole);
    MemMan::destruct(&m_XML_str);
}

// status check method
int DOI::get_Status ()
{
// TODO: This is hardcoded for now ... should check validity of the DOI,
//       and determine whether or not is contains an empty or TBD <DOI> element,
//       or if it contains an externally generated DOI
	return(DOI_NEEDS_MASTER_ASSIGNED);
//	return(DOI_IS_EXTERNALLY_GENERATED);
}

// Get and Set Operations for Class Attributes

/** DOI id string */   
const char* DOI::get_DOI_idStr () const
{ return m_DOI_idStr; }
void DOI::set_DOI_idStr (char* pDOI_idStr)
{ MemMan::copy(&m_DOI_idStr, pDOI_idStr); }

// TODO: Do we also need a DOIApplicationProfile? It's mentioned in the handbook
//       (http://www.doi.org/handbook_2000/metadata.html), but is not found in the example ...

/** Structural Type */     
// TODO: This should be an enumeration with the following items:
    // TangibleFixation (Physical)
    // Intangible Fixation (Digital)
    // Performance (SpatioTemporal)
    // Abstraction (Abstract)
const char* DOI::get_StructuralType () const
{ return m_StructuralType; }
void DOI::set_StructuralType (char* pStructuralType)
{ MemMan::copy(&m_StructuralType, pStructuralType); }

/** Mode */     
// TODO: These should be flags
    // Visual
    // Audio
    // Audiovisual
    // Abstract 
const char* DOI::get_Mode () const
{ return m_Mode; }
void DOI::set_Mode (char* pMode)
{ MemMan::copy(&m_Mode, pMode); }

// TODO: This should support an array
/** Identifier Type */     
const char* DOI::get_IdentifierType () const
{ return m_IdentifierType; }
void DOI::set_IdentifierType (char* pIdentifierType)
{ MemMan::copy(&m_IdentifierType, pIdentifierType); }

// TODO: This should support an array
/** Identifier Value */     
const char* DOI::get_IdentifierValue () const
{ return m_IdentifierValue; }
void DOI::set_IdentifierValue (char* pIdentifierValue)
{ MemMan::copy(&m_IdentifierValue, pIdentifierValue); }

// TODO: This should support an array
/** Title */     
const char* DOI::get_Title () const
{ return m_Title; }
void DOI::set_Title (char* pTitle)
{ MemMan::copy(&m_Title, pTitle); }

// TODO: This should support an array
/** Primary Agent (Artist) */     
const char* DOI::get_PrimaryAgent () const
{ return m_PrimaryAgent; }
void DOI::set_PrimaryAgent (char* pPrimaryAgent)
{ MemMan::copy(&m_PrimaryAgent, pPrimaryAgent); }

// TODO: This should support an array (of enumerated items from a namespace, e.g. Author, Publisher, Editor).
/** Primary Agent Role */     
const char* DOI::get_PrimaryAgentRole () const
{ return m_PrimaryAgentRole; }
void DOI::set_PrimaryAgentRole (char* pPrimaryAgentRole)
{ MemMan::copy(&m_PrimaryAgentRole, pPrimaryAgentRole); }

/** raw XML string */     
const char* DOI::get_XML_str () const
{ return m_XML_str; }
void DOI::set_XML_str (char* pXMLstr)
{ MemMan::copy(&m_XML_str, pXMLstr); }
