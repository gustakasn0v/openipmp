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
#include <stdio.h>
#include <sys/stat.h>

#include <string> // for std::string
#include <cctype> // for tolower
#include <algorithm> // for std::stransform

#include "busobj/factories/AuxData_Factory.h"
#include "squashxml/xml/XMLDocument.h"
#include "squashxml/tools/FileLogger.h"

AuxData_Factory::AuxData_Factory()
{
}

AuxData_Factory::~AuxData_Factory()
{
}

// create AuxData instance with hardcoded values
AuxData* AuxData_Factory::CreateInstanceFromFile (const char* xml_filename)
{

    // read from xml file into a memory buffer
    FILE* fp;
    struct stat tstat;
    stat(xml_filename, &tstat);
    fp = fopen(xml_filename, "rb");
    if (!fp) {
        gLogger->logError("Failed attempt to open xml file. Returning...");
        return(NULL);	// TODO: this should probably throw an exception
    }
    char* xmlText = (char*) malloc(tstat.st_size+1);
    fread(xmlText, tstat.st_size, 1, fp);
	xmlText[tstat.st_size]=0x00;
    fclose(fp);

    // instantiate new AuxData
    AuxData* pAuxData = NULL;
	pAuxData = CreateInstance(xmlText);

	// free xml memory buffer
    free(xmlText);

	return(pAuxData);
}

// create AuxData instance with values initialized from parsed XML stream
AuxData* AuxData_Factory::CreateInstance (const char* xml_stream)
{

	// make sure xml_stream is populated
	if (!xml_stream) {
        gLogger->logError("Aborting attempt to parse NULL xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
	}

    // instantiate new AuxData
    AuxData* pAuxData = new AuxData();

	// instantiate XMLDocument
	XMLDocument xdoc;

    // decode xml text buffer into an XMLDocument
    if ( !xdoc.decode(xml_stream, "AuxData") ) {
        gLogger->logError("Failed attempt parse xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
    }

    // Protected Flag - Required
	bool ProtectedFlagValBool = false;
    char* ProtectedFlagVal = xdoc.getString("ProtectedFlag");
    if (ProtectedFlagVal == NULL)
    {
        gLogger->logError("ProtectedFlag value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
	if ( stricmp("true", ProtectedFlagVal)==0 )
		ProtectedFlagValBool = true;
	else if ( stricmp("false", ProtectedFlagVal)==0 )
		ProtectedFlagValBool = false;
	else {
        gLogger->logError("Unable to understand boolean ProtectedFlag value.");
        return(NULL);	// TODO: this should probably throw an exception
	}
    pAuxData->set_ProtectedFlag(ProtectedFlagValBool);
    delete[] ProtectedFlagVal;

    // ToolId - Required
    char* ToolIdVal = xdoc.getString("ToolId");
    if (ToolIdVal == NULL)
    {
        gLogger->logError("ToolId value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pAuxData->set_ToolId( ToolIdVal );
    delete[] ToolIdVal;

    // RightsHost URL
    char* RightsHostURLVal = xdoc.getString("RightsHost.URL");
    if (RightsHostURLVal == NULL)
    {
        gLogger->logError("RightsHost.URL value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pAuxData->set_RightsHost_URL( RightsHostURLVal );
    delete[] RightsHostURLVal;

    // RightsHost Port
    char* RightsHostPortVal = xdoc.getString("RightsHost.Port");
    if (RightsHostPortVal == NULL)
    {
        gLogger->logError("RightsHost.Port value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pAuxData->set_RightsHost_Port( atoi(RightsHostPortVal) );
    delete[] RightsHostPortVal;

    // RightsHost Full XML
/************ XMLDocument cannot encode() a SubDoc for some reason ...
 ************ Therefore, this code has been replaced with KLUDGE code below.
    XMLDocument* RightsHostSubDoc = xdoc.getSubDoc("RightsHost");
    if (RightsHostSubDoc == NULL)
    {
        gLogger->logError("RightsHost value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pAuxData->set_RightsHost_XML( RightsHostSubDoc->encode() );
    delete[] RightsHostSubDoc;
***************/

    // initialize stl std::string with xml stream and create lowercase transformation
    std::string fullxml = xml_stream;
    std::string fullxml_lower = xml_stream;
	std::string::size_type pos1=0, pos2=0;
    std::transform(fullxml_lower.begin(), fullxml_lower.end(), fullxml_lower.begin(), tolower);

    // find RightsHost start tag
    pos1 = fullxml_lower.find ("<rightshost",0);
    if (pos1 == std::string::npos) {
        gLogger->logError("<RightsHost> tag not found in IPMP_ContentId.");
        return(NULL);
    }

    // find RightsHost end tag
    pos2 = fullxml_lower.find ("</rightshost>",0);
    if (pos1 == std::string::npos) {
        gLogger->logError("</RightsHost> tag not found in IPMP_ContentId.");
        return(NULL);
    }
    pos2 += strlen("</Signature>");

    // extract DOI xml substring from original (mixed case) xml stream
    std::string rhxml = XMLDocument::xmlPrefix() + fullxml.substr(pos1, (pos2 - pos1) );
    pAuxData->set_RightsHost_XML( (char*)  rhxml.c_str() );

    /***** RightsHost - Required - end ***/

    // set XML string on AuxData, free memory
    pAuxData->set_XML_str ( (char*) xml_stream);

    // return newly created AuxData
    return(pAuxData);
}
