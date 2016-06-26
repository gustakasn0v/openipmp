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
#include "busobj/IPMP_ContentIdentity.h"
#include "busobj/factories/DOI_Factory.h"
#include "busobj/factories/DigitalSignature_Factory.h"
#include "tools/MemMan.h"
#include "squashxml/tools/FileLogger.h"
#include "tools/MemMan.h"
#include "squashxml/xml/XMLDocument.h"

#include <string> // for std::string
#include <cctype> // for tolower
#include <algorithm> // for std::stransform

#define BEGIN_TAG	"<IPMP_ContentIdentity>\n"
#define END_TAG	"\n</IPMP_ContentIdentity>\n"

// Class IPMP_ContentIdentity

IPMP_ContentIdentity::IPMP_ContentIdentity()
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_XML_str);
    MemMan::construct(&m_DOI_XML_str);
    MemMan::construct(&m_DigitalSignature_XML_str);

	// initialize member references to complex objects
    m_IPMP_MetaData = NULL;
    m_DOI = NULL;
    m_DigitalSignature = NULL;
}

IPMP_ContentIdentity::IPMP_ContentIdentity(IPMP_ContentIdentity* right)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_XML_str);
    MemMan::construct(&m_DOI_XML_str);
    MemMan::construct(&m_DigitalSignature_XML_str);

	// check for NULL
	if (!right)
		return;

	// copy complex member variables from input object
    MemMan::copy(&m_XML_str, (char*) right->get_XML_str());
    MemMan::copy(&m_DOI_XML_str, (char*) right->get_DOI_XML_str());
    MemMan::copy(&m_DigitalSignature_XML_str, (char*) right->get_DigitalSignature_XML_str());

	// construct copies of complex input objects and set member references
	if ( right->get_IPMP_MetaData() )
		m_IPMP_MetaData = new IPMP_MetaData( (IPMP_MetaData*) right->get_IPMP_MetaData());
	else
		m_IPMP_MetaData = NULL;
	if (  right->get_DOI() )
		m_DOI = new DOI( (DOI*) right->get_DOI());
	else
		m_DOI = NULL;
	if ( right->get_DigitalSignature() )
		m_DigitalSignature = new DigitalSignature( (DigitalSignature*) right->get_DigitalSignature());
	else
		m_DigitalSignature = NULL;
}

IPMP_ContentIdentity::IPMP_ContentIdentity(IPMP_MetaData* pMetaData, DOI* pDOI, DigitalSignature* pDigitalSignature)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_XML_str);
    MemMan::construct(&m_DOI_XML_str);
    MemMan::construct(&m_DigitalSignature_XML_str);

	// construct copies of complex input objects and set member references
    m_IPMP_MetaData = new IPMP_MetaData(pMetaData);
    m_DOI = new DOI(pDOI);
    m_DigitalSignature = new DigitalSignature(pDigitalSignature);
}

IPMP_ContentIdentity::IPMP_ContentIdentity(IPMP_MetaData* pMetaData, DOI* pDOI)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_XML_str);
    MemMan::construct(&m_DOI_XML_str);
    MemMan::construct(&m_DigitalSignature_XML_str);

	// construct copies of complex input objects and set member references
    m_IPMP_MetaData = new IPMP_MetaData(pMetaData);
    m_DOI = new DOI(pDOI);
    m_DigitalSignature = NULL;
}

IPMP_ContentIdentity::IPMP_ContentIdentity(DOI* pDOI, DigitalSignature* pDigitalSignature)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_XML_str);
    MemMan::construct(&m_DOI_XML_str);
    MemMan::construct(&m_DigitalSignature_XML_str);

	// construct copies of complex input objects and set member references
    m_DOI = new DOI(*pDOI);
    m_DigitalSignature = new DigitalSignature(*pDigitalSignature);
    m_IPMP_MetaData = NULL;
}

IPMP_ContentIdentity::~IPMP_ContentIdentity()
{
	// free memory: (destruct) complex member variables
    MemMan::destruct(&m_XML_str);
    MemMan::destruct(&m_DOI_XML_str);
    MemMan::destruct(&m_DigitalSignature_XML_str);

	// free memory: (destruct) complex objects pointed to be member references
    if (m_IPMP_MetaData)
        delete m_IPMP_MetaData;
    if (m_DOI)
        delete m_DOI;
    if (m_DigitalSignature)
        delete m_DigitalSignature;
}

// IPMP_MetaData
const IPMP_MetaData* IPMP_ContentIdentity::get_IPMP_MetaData () const
{ return m_IPMP_MetaData; }
void IPMP_ContentIdentity::set_IPMP_MetaData (IPMP_MetaData* value)
{
	if (m_IPMP_MetaData)
		delete m_IPMP_MetaData;
	m_IPMP_MetaData = new IPMP_MetaData(value);
}

// IPMP_ContentIdentity
const DOI* IPMP_ContentIdentity::get_DOI () const
{ return m_DOI; }
void IPMP_ContentIdentity::set_DOI (DOI* value)
{
	if (m_DOI)
		delete m_DOI;
	m_DOI = new DOI(value);
}

// title
const char* IPMP_ContentIdentity::get_Title () const
{
    if (!m_isSetupFlag)
        return(NULL);	// TODO: this should throw an exception
    else
        return( get_DOI()->get_Title() );
}
void IPMP_ContentIdentity::set_Title (char* value)
{
    if (!m_isSetupFlag)
        return;		// TODO: this should throw an exception
    else
        m_DOI->set_Title(value);
}

// artist
const char* IPMP_ContentIdentity::get_Artist () const
{
    if (!m_isSetupFlag)
        return(NULL);	// TODO: this should throw an exception
    else
        return( get_DOI()->get_PrimaryAgent() );
}
void IPMP_ContentIdentity::set_Artist (char* value)
{
    if (!m_isSetupFlag)
        return;		// TODO: this should throw an exception
    else
        m_DOI->set_PrimaryAgent(value);
}

// rights host
const char* IPMP_ContentIdentity::get_RightsHost () const
{
    if (!m_isSetupFlag)
        return(NULL);	// TODO: this should throw an exception
    else
        return( get_IPMP_MetaData()->get_RightsHost() );
}
void IPMP_ContentIdentity::set_RightsHost (char* value)
{
    if (!m_isSetupFlag)
        return;		// TODO: this should throw an exception
    else
        m_IPMP_MetaData->set_RightsHost(value);
}

// protected flag
const bool IPMP_ContentIdentity::get_ProtectedFlag () const
{
    if (!m_isSetupFlag)
        return(NULL);	// TODO: this should throw an exception
    else
        return( get_IPMP_MetaData()->get_ProtectedContentFlag() );
}
void IPMP_ContentIdentity::set_ProtectedFlag (bool value)
{
    if (!m_isSetupFlag)
        return;		// TODO: this should throw an exception
    else
        m_IPMP_MetaData->set_ProtectedContentFlag(value);
}

// full IPMP_ContentId XML string
const char* IPMP_ContentIdentity::get_XML_str () const
{ return m_XML_str; }
void IPMP_ContentIdentity::set_XML_str (char* value)
{ MemMan::copy(&m_XML_str, value); }

// DOI XML string
const char* IPMP_ContentIdentity::get_DOI_XML_str () const
{ return m_DOI_XML_str; }
void IPMP_ContentIdentity::set_DOI_XML_str (char* value)
{ MemMan::copy(&m_DOI_XML_str, value); }

// DigitalSignature XML string
const char* IPMP_ContentIdentity::get_DigitalSignature_XML_str () const
{ return m_DigitalSignature_XML_str; }
void IPMP_ContentIdentity::set_DigitalSignature_XML_str (char* value)
{ MemMan::copy(&m_DigitalSignature_XML_str, value); }

// resource key facade
const char* IPMP_ContentIdentity::get_ResourceKey () const
{
  //  if (!m_isSetupFlag)
    //    return(NULL);	// TODO: this should throw an exception
   // else
        return( get_DOI()->get_DOI_idStr() );
}

// encode IPMP_ContentIdentity full XML string
const char* IPMP_ContentIdentity::encode ()
{

	// check for local DOI xml string
	if (!m_DOI_XML_str) {

		// check for DOI object
		if ( !m_DOI ) {
			gLogger->logError("IPMP_ContentIdentity cannot resolve any DOI.");
			return(NULL);
		}

		// check for DOI object's xml string
		if ( !m_DOI->get_XML_str() ) {
			gLogger->logError("IPMP_ContentIdentity has DOI object, but cannot obtain XML.");
			return(NULL);
		}

		// set local DOI XML string with xml string from DOI object
		set_DOI_XML_str( (char*) m_DOI->get_XML_str() );
	}

	// check for local DigitalSignature xml string
	if (!m_DigitalSignature_XML_str) {

		// check for DigitalSignature object
		if ( !m_DigitalSignature ) {
			gLogger->logError("IPMP_ContentIdentity cannot resolve any DigitalSignature.");
			return(NULL);
		}

		// check for DigitalSignature object's xml string
		if ( !m_DigitalSignature->get_XML_str() ) {
			gLogger->logError("IPMP_ContentIdentity has DigitalSignature object, but cannot obtain XML.");
			return(NULL);
		}

		// set local DigitalSignature XML string with xml string from DigitalSignature object
		set_DigitalSignature_XML_str( (char*) m_DigitalSignature->get_XML_str() );
	}

	// allocate and build full xml string and return
	int total_len = strlen(XMLDocument::xmlPrefix()) + strlen(BEGIN_TAG) + strlen(m_DOI_XML_str) + strlen(m_DigitalSignature_XML_str) + strlen(END_TAG);
	char* encoded_str = (char*) malloc(total_len);
	sprintf(encoded_str, "%s%s%s%s%s", XMLDocument::xmlPrefix(), BEGIN_TAG, m_DOI_XML_str, m_DigitalSignature_XML_str, END_TAG);
	return(encoded_str);

}

// decode DOI and DigitalSignature XML strings into their respective objects
bool IPMP_ContentIdentity::decode ()
{

	// delete current DOI, check DOI string, decode a new one from the DOI xml string
	if (m_DOI)
		delete m_DOI;
	if (m_DOI_XML_str)
		m_DOI = DOI_Factory::CreateInstance(m_DOI_XML_str);
	else
		gLogger->logWarning("Attempt to decode empty DOI xml string.");
	if (!m_DOI)
		gLogger->logWarning("Failed to generate a DOI.");

	// delete current DigitalSignature, check DigitalSignature string, decode a new one from the DigitalSignature xml string
	if (m_DigitalSignature)
		delete m_DigitalSignature;
	if (m_DigitalSignature_XML_str)
		m_DigitalSignature = DigitalSignature_Factory::CreateInstance(m_DigitalSignature_XML_str);
	else
		gLogger->logWarning("Attempt to decode empty DigitalSignature xml string.");
	if (!m_DigitalSignature)
		gLogger->logWarning("Failed to generate a DigitalSignature.");

	// return success or failure based on presence of decoded objects ...
	return(m_DOI && m_DigitalSignature);
}
