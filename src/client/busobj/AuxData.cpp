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

// for encode() string handling
#include <string>
using namespace std;

#include "busobj/AuxData.h"
#include "tools/MemMan.h"

// Class AuxData

AuxData::AuxData()
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_RightsHost_XML);
    MemMan::construct(&m_RightsHost_URL);
    MemMan::construct(&m_RightsHost_Port);
	MemMan::construct(&m_XML_str);
	MemMan::construct(&m_ToolId);

    // initialize simple member attributes
    m_ProtectedFlag = false;
}

AuxData::AuxData(AuxData* right)
{
	// initialize (construct) complex member variables
    MemMan::construct(&m_RightsHost_XML);
    MemMan::construct(&m_RightsHost_URL);
    MemMan::construct(&m_RightsHost_Port);
	MemMan::construct(&m_XML_str);
	MemMan::construct(&m_ToolId);

	// copy complex member variables from input object
	MemMan::copy(&m_RightsHost_XML, (char*) right->get_RightsHost_XML());
	MemMan::copy(&m_RightsHost_URL, (char*) right->get_RightsHost_URL());
	MemMan::copy(&m_RightsHost_Port, right->get_RightsHost_Port());
	MemMan::copy(&m_XML_str, (char*) right->get_XML_str());
	MemMan::copy(&m_ToolId, (char*) right->get_ToolId());

    // initialize simple member attribute with copied values from input object
    m_ProtectedFlag = right->get_ProtectedFlag();
}

AuxData::~AuxData()
{
	// free memory: (destruct) complex member variables
    MemMan::destruct(&m_RightsHost_XML);
    MemMan::destruct(&m_RightsHost_URL);
    MemMan::destruct(&m_RightsHost_Port);
	MemMan::destruct(&m_XML_str);
	MemMan::destruct(&m_ToolId);
}

// Get and Set Operations for Class Attributes

/** Protected Flag */
const bool AuxData::get_ProtectedFlag () const
{ return m_ProtectedFlag; }
void AuxData::set_ProtectedFlag (bool pValue)
{ m_ProtectedFlag = pValue; }

/** Tool Id */
const char* AuxData::get_ToolId () const
{ return m_ToolId; }
void AuxData::set_ToolId (char* pValue)
{ MemMan::copy(&m_ToolId,pValue); }

/** RightsHost XML string substring */
const char* AuxData::get_RightsHost_XML () const
{ return m_RightsHost_XML; }
void AuxData::set_RightsHost_XML (char* pValue)
{ MemMan::copy(&m_RightsHost_XML, pValue); }

/** RightsHost URL string */
const char* AuxData::get_RightsHost_URL () const
{ return m_RightsHost_URL; }
void AuxData::set_RightsHost_URL (char* pValue)
{ MemMan::copy(&m_RightsHost_URL, pValue); }

/** RightsHost Port */
const int AuxData::get_RightsHost_Port () const
{ return m_RightsHost_Port; }
void AuxData::set_RightsHost_Port (int value)
{ MemMan::copy(&m_RightsHost_Port, value); }

// raw XML string
const char* AuxData::get_XML_str () const
{ return m_XML_str; }
void AuxData::set_XML_str (char* value)
{ MemMan::copy(&m_XML_str, value); }

// TODO: This should be replaced with proper XML Document creation and encoding
char* AuxData::encode()
{

	string result = "";

    // start building xml string
    result += "<AuxData xmlns:osms=\"http://www.openipmp.org/\">\n";

		// encode ProtectedFlag
		result += "\t<ProtectedFlag>";
		if (m_ProtectedFlag)
			result += "True";
		else
			result += "False";
		result += "</ProtectedFlag>\n";

		// encode ToolId
		result += "\t<ToolId>";
		/** CJM 4/9/03 this is a hack here..
			the server's expecting to parse an integer,
			not a string..
		*/
		char toolid[50];
		sprintf(toolid, "%d", 200);

		result += toolid;
		result += "</ToolId>\n";

		// rights host
		result += "\t<RightsHost>\n";

			// encode URL
			// TODO: This can be confusing, should use initialized m_URL value
			result += "\t\t<URL>URLHere</URL>\n";

			// encode Port
			// TODO: This can be confusing, should use initialized m_Port value
			result += "\t\t<Port>9999</Port>\n";

	// end tags
		result += "\t</RightsHost>\n";
	result += "</AuxData>\n";

	// allocate space on heap for string and return it
	return( strdup( (char*)result.c_str() ) );

}
