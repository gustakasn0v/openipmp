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

#include "busobj/factories/DOI_Factory.h"
#include "squashxml/xml/XMLDocument.h"
#include "squashxml/tools/FileLogger.h"

DOI_Factory::DOI_Factory()
{
}

DOI_Factory::~DOI_Factory()
{
}

// create dummy DOI instance with hardcoded values
DOI* DOI_Factory::CreateInstance ()
{

    // instantiate new DOI
    DOI* pDOI = new DOI();
 
    pDOI->set_DOI_idStr("10.9901/12.i.7389457");
    pDOI->set_StructuralType("Intangible Fixation (Digital)");
    pDOI->set_Mode("Audio");
    pDOI->set_IdentifierType("DOI-MASTER");
    pDOI->set_IdentifierValue("10.9901/12.m.78031");
    pDOI->set_Title("Generic Love Song Music Video");
    pDOI->set_PrimaryAgent("Matt Witte");
    pDOI->set_PrimaryAgentRole("Artist");

    pDOI->set_XML_str(" \
        <?xml version=\"1.0\" encoding=\"UTF-8\"?> \
        <doi:KernelMetadata xmlns:doi=\"http://www.doi.org/\"> \
        <DOI>10.9901/12.i.7389457</DOI> \
        <Identifiers> \
           <Identifier> \
              <IdentifierType>DOI-MASTER</IdentifierType> \
             <IdentifierValue>10.9901/12.m.78031</IdentifierValue> \
           </Identifier> \
           <Identifier> \
              <IdentifierType>ISWC</IdentifierType> \
              <IdentifierValue>T-034.524.680</IdentifierValue> \
           </Identifier> \
        </Identifiers> \
        <Titles><Title> \
           <TitleValue>Generic Love Song Music Video</TitleValue> \
           <Language>en</Language> \
        </Title></Titles> \
        <StructuralType>visual</StructuralType> \
        <Modes> \
           <Mode>visual</Mode> \
        </Modes> \
        <PrimaryAgents> \
           <Agent sequence=\"1\"><Name> \
              <NameType>Person</NameType> \
              <NameValue>Matt Witte</NameValue> \
           </Name><Roles> \
        <Role>Artist</Role> \
           </Roles></Agent> \
           <Agent sequence=\"2\"><Name> \
              <NameType>Person</NameType> \
              <NameValue>Freddy</NameValue> \
           </Name><Roles> \
              <Role>Directory</Role> \
           </Roles></Agent> \
        </PrimaryAgents> \
        </doi:KernelMetadata> \
    ");
    
    // return newly created DOI
    return(pDOI);
    
}

// create DOI instance with hardcoded values
DOI* DOI_Factory::CreateInstanceFromFile (const char* xml_filename)
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

    // instantiate new DOI
    DOI* pDOI = NULL;
	pDOI = CreateInstance(xmlText);

	// free xml memory buffer
    free(xmlText);

	return(pDOI);
}

// create DOI instance with values initialized from parsed XML stream
DOI* DOI_Factory::CreateInstance (const char* xml_stream)
{

	// make sure xml_stream is populated
	if (!xml_stream) {
        gLogger->logError("Aborting attempt to parse NULL xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
	}

    // instantiate new DOI
    DOI* pDOI = new DOI();
	
	// instantiate XMLDocument
	XMLDocument xdoc;

    // decode xml text buffer into an XMLDocument
    if ( !xdoc.decode(xml_stream, "doi:KernelMetadata") ) {
        gLogger->logError("Failed attempt parse xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
    }

    // DOI - Requried
    char* DOIval = xdoc.getString("DOI");
    if (DOIval == NULL)
    {
        gLogger->logError("DOI value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDOI->set_DOI_idStr(DOIval);
    delete[] DOIval;

    // Support for one Identifier
    // TODO: This should support an array of Identifiers, but here we support only one for now
    char* identType = xdoc.getString("Identifiers.Identifier.IdentifierType");
    char* identValue = xdoc.getString("Identifiers.Identifier.IdentifierValue");
    pDOI->set_IdentifierType(identType);
    pDOI->set_IdentifierValue(identValue);
    if (identType != NULL)
            delete[] identType;
    if (identValue != NULL)
            delete[] identValue;

    // Support for one Title
    // TODO: This should support an array of Titles, but here we support only one for now
    char* title = xdoc.getString("Titles.Title.TitleValue");
    pDOI->set_Title(title);
    if (title != NULL)
            delete[] title;

    // Structural Type - Requried
    char* structuralType = xdoc.getString("StructuralType");
    if (structuralType == NULL)
    {
        gLogger->logError("Structural Type value missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDOI->set_StructuralType(structuralType);
    delete[] structuralType;

    // Support for one Mode
    // TODO: This should support an array of Modes, but here we support only one for now
    char* mode = xdoc.getString("Modes.Mode");
    if (mode == NULL)
    {
        gLogger->logError("Modes section is missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDOI->set_Mode(mode);
    if (mode != NULL)
            delete[] mode;

    // Support for one PrimaryAgent
    // TODO: This should support an array of PrimaryAgents, but here we support only one for now
    char* primaryAgent = xdoc.getString("PrimaryAgents.Agent.Name.NameValue");
    if (primaryAgent == NULL)
    {
        gLogger->logError("PrimaryAgents section is missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDOI->set_PrimaryAgent(primaryAgent);
    if (primaryAgent != NULL)
            delete[] primaryAgent;

    // Support for one PrimaryAgentRole
    // TODO: This should support an array of PrimaryAgentRoles, but here we support only one for now
    char* primaryAgentRole = xdoc.getString("PrimaryAgents.Agent.Roles.Role.Role");
    if (primaryAgentRole == NULL)
    {
        gLogger->logError("PrimaryAgentRoles section is missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pDOI->set_PrimaryAgentRole(primaryAgentRole);
    if (primaryAgentRole != NULL)
            delete[] primaryAgentRole;

    // encode back to XML, set XML string on DOI, free memory
    pDOI->set_XML_str ( (char*) xml_stream);
	    
    // return newly created DOI
    return(pDOI);
 }
