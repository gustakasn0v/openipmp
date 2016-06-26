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

#include "busobj/factories/RightsHost_Factory.h"
#include "squashxml/xml/XMLDocument.h"
#include "squashxml/tools/FileLogger.h"

RightsHost_Factory::RightsHost_Factory()
{
}

RightsHost_Factory::~RightsHost_Factory()
{
}

// create RightsHost instance with hardcoded values
RightsHost* RightsHost_Factory::CreateInstanceFromFile (const char* xml_filename)
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
    fclose(fp);

    // instantiate new RightsHost
    RightsHost* pRightsHost = NULL;
	pRightsHost = CreateInstance(xmlText);

	// free xml memory buffer
    free(xmlText);

	return(pRightsHost);
}

// create RightsHost instance with values initialized from parsed XML stream
RightsHost* RightsHost_Factory::CreateInstance (const char* xml_stream)
{

	// make sure xml_stream is populated
	if (!xml_stream) {
        gLogger->logError("Aborting attempt to parse NULL xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
	}

    // instantiate new RightsHost
    RightsHost* pRightsHost = new RightsHost();

	// instantiate XMLDocument
	XMLDocument xdoc;

    // decode xml text buffer into an XMLDocument
    if ( !xdoc.decode(xml_stream, "RightsHost") ) {
        gLogger->logError("Failed attempt parse xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
    }

    // RightsHost URL
    char* RightsHostURLVal = xdoc.getString("URL");
    if (RightsHostURLVal == NULL)
    {
        gLogger->logError("URL value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pRightsHost->set_URL( RightsHostURLVal );
    delete[] RightsHostURLVal;

    // RightsHost Port
    char* RightsHostPortVal = xdoc.getString("Port");
    if (RightsHostPortVal == NULL)
    {
        gLogger->logError("Port value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pRightsHost->set_Port( atoi(RightsHostPortVal) );
    delete[] RightsHostPortVal;

    // set XML string on RightsHost, free memory
    pRightsHost->set_XML_str ( (char*) xml_stream);
	
    // return newly created RightsHost
    return(pRightsHost);
}
