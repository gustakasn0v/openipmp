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
#include "busobj/IPMP_MetaData.h"
#include "tools/MemMan.h"
#include "squashxml/tools/FileLogger.h"

// TODO: Should just include a header file that defines NULL
#define NULL	0

// Class IPMP_MetaData 

IPMP_MetaData::IPMP_MetaData()
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_RightsHost);
    MemMan::construct(&m_PlugInName);
    MemMan::construct(&m_ContentId);
    MemMan::construct(&m_LanguageCode);
	MemMan::construct(&m_ToolId);

    // initialize simple member attributes
    m_ContentIdLength = NULL;
    m_ContentIdType = NULL;
    m_ContentIdFlag = NULL;
    m_ContentType = NULL;
    m_ContentTypeFlag = NULL;
    m_Compatibility = NULL;
    m_ProtectedContentFlag = NULL;
    m_ToolId = NULL;
}

IPMP_MetaData::IPMP_MetaData(IPMP_MetaData* right)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_RightsHost);
    MemMan::construct(&m_PlugInName);
    MemMan::construct(&m_ContentId);
    MemMan::construct(&m_LanguageCode);
	MemMan::construct(&m_ToolId);

	// copy complex member variables from input object
    MemMan::copy(&m_RightsHost, (char*) right->get_RightsHost());
    MemMan::copy(&m_PlugInName, (char*) right->get_PlugInName());
    MemMan::copy(&m_ContentId, (char*) right->get_ContentId());
    MemMan::copy(&m_LanguageCode, (char*) right->get_LanguageCode());
	MemMan::copy(&m_ToolId, (char*) right->get_ToolId());

    // initialize simple member attribute with copied values from input object
    m_ContentIdLength = right->get_ContentIdLength();
    m_ContentIdType = right->get_ContentIdType();
    m_ContentIdFlag = right->get_ContentIdFlag();
    m_ContentType = right->get_ContentType();
    m_ContentTypeFlag = right->get_ContentTypeFlag();
    m_Compatibility = right->get_Compatibility();
    m_ProtectedContentFlag = right->get_ProtectedContentFlag();
}

IPMP_MetaData::~IPMP_MetaData()
{
    // destroy complex member attributes
    MemMan::destruct(&m_RightsHost);
    MemMan::destruct(&m_PlugInName);
    MemMan::destruct(&m_ContentId);
    MemMan::destruct(&m_LanguageCode);
	MemMan::destruct(&m_ToolId);
}

bool IPMP_MetaData::init(IPMP_ContentIdentity* pIPMP_ContentId, AuxData* pAuxData)
{

	if ( !pAuxData || !pIPMP_ContentId ) {
		gLogger->logError("IPMP_ContentIdentity and/or AuxData object missing.");
		return(false);
	}

	// set member variables based on information derived from the AuxData object
	set_ProtectedContentFlag	( pAuxData->get_ProtectedFlag() );
	set_RightsHost				( (char*) pAuxData->get_RightsHost_XML() );
	set_ToolId					( (char*)pAuxData->get_ToolId() );
	
	// encode DOI xml and DigitalSignature xml in IPMP_ContentId wrapper to form contentId
	char* contentIdWrapper_XML_str = (char*) pIPMP_ContentId->encode();
	if ( !contentIdWrapper_XML_str ) {
		gLogger->logError("Unable to encode DOI xml and DigitalSignature xml in IPMP_ContentId wrapper.");
		return(false);
	}
	else {
		set_ContentId ( contentIdWrapper_XML_str );
		set_ContentIdLength ( strlen(contentIdWrapper_XML_str) );
// KLUDGE: Not sure why this wasn't ok - should be malloc'd in pIPMP_ContentId->encode()
//		free (contentIdWrapper_XML_str);
	}

	// set miscellanous member variables
    set_ContentIdType	( 2 );	// TODO: should use something that indicates DOI ???
    set_ContentIdFlag	( 1 );	// TODO: should indicate <true> that content id is set ???
    set_ContentType		( 3 );	// TODO: should look at pDOI->get_Mode() and set accordingly ???
    set_ContentTypeFlag	( 1 );	// TODO: how should this be set ???
    set_Compatibility	( 0 );	// TODO: not sure what this is or how to set it ...
	
	return(true);
}


// Get and Set Operations for Class Attributes

// rights resolution host
const char* IPMP_MetaData::get_RightsHost () const
{ return m_RightsHost; }
void IPMP_MetaData::set_RightsHost (char* value)
{ MemMan::copy(&m_RightsHost, value); }

// plug in dll name
const char* IPMP_MetaData::get_PlugInName () const
{ return m_PlugInName; }
void IPMP_MetaData::set_PlugInName (char* value)
{ MemMan::copy(&m_PlugInName, value); }

// content id
const char* IPMP_MetaData::get_ContentId () const
{ return m_ContentId; }
void IPMP_MetaData::set_ContentId (char* value)
{ MemMan::copy(&m_ContentId, value); }

// content id length
const int IPMP_MetaData::get_ContentIdLength () const
{ return m_ContentIdLength; }
void IPMP_MetaData::set_ContentIdLength (int value)
{ MemMan::copy(&m_ContentIdLength, value); }

// content id type
const int IPMP_MetaData::get_ContentIdType () const
{ return m_ContentIdType; }
void IPMP_MetaData::set_ContentIdType (int value)
{ MemMan::copy(&m_ContentIdType, value); }

// content id flag
const int IPMP_MetaData::get_ContentIdFlag () const
{ return m_ContentIdFlag; }
void IPMP_MetaData::set_ContentIdFlag (int value)
{ MemMan::copy(&m_ContentIdFlag, value); }

// content type (?)
const int IPMP_MetaData::get_ContentType () const
{ return m_ContentType; }
void IPMP_MetaData::set_ContentType (int value)
{ m_ContentType = value; }

// content type flag (?)
const int IPMP_MetaData::get_ContentTypeFlag () const
{ return m_ContentTypeFlag; }
void IPMP_MetaData::set_ContentTypeFlag (int value)
{ m_ContentTypeFlag = value; }

// compatibility (?)
const int IPMP_MetaData::get_Compatibility () const
{ return m_Compatibility; }
void IPMP_MetaData::set_Compatibility (int value)
{ m_Compatibility = value; }

// protected content flag
const int IPMP_MetaData::get_ProtectedContentFlag () const
{ return m_ProtectedContentFlag; }
void IPMP_MetaData::set_ProtectedContentFlag (int value)
{ m_ProtectedContentFlag = value; }

// tool id
const char* IPMP_MetaData::get_ToolId () const
{ return m_ToolId; }
void IPMP_MetaData::set_ToolId (char* value)
{ MemMan::copy(&m_ToolId,value); }

// language code
const char* IPMP_MetaData::get_LanguageCode () const
{ return m_LanguageCode; }
void IPMP_MetaData::set_LanguageCode (char* value)
{ MemMan::copy(&m_LanguageCode, value); }
