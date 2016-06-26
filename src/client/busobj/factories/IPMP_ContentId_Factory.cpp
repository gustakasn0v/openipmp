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

#include "busobj/factories/IPMP_ContentId_Factory.h"
#include "squashxml/xml/XMLDocument.h"
#include "squashxml/tools/FileLogger.h"

IPMP_ContentId_Factory::IPMP_ContentId_Factory()
{
}

IPMP_ContentId_Factory::~IPMP_ContentId_Factory()
{
}

// create IPMP_ContentId instance with hardcoded values
IPMP_ContentIdentity* IPMP_ContentId_Factory::CreateInstanceFromFile (const char* xml_filename)
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

    // instantiate new IPMP_ContentId
    IPMP_ContentIdentity* pIPMP_ContentId = NULL;
	pIPMP_ContentId = CreateInstance(xmlText);

	// free xml memory buffer
    free(xmlText);

	return(pIPMP_ContentId);
}

// create IPMP_ContentIdentity instance with values initialized from parsed XML stream
IPMP_ContentIdentity* IPMP_ContentId_Factory::CreateInstance (const char* xml_stream)
{

	// make sure xml_stream is populated
	if (!xml_stream) {
        gLogger->logError("Aborting attempt to parse NULL xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
	}

    // instantiate new IPMP_ContentId
    IPMP_ContentIdentity* pIPMP_ContentId = new IPMP_ContentIdentity();

	// instantiate XMLDocument
	XMLDocument xdoc;

    // decode xml text buffer into an XMLDocument
    if ( !xdoc.decode(xml_stream, "IPMP_ContentIdentity") ) {
        gLogger->logError("Failed attempt parse xml stream.");
        return(NULL);	// TODO: this should probably throw an exception
    }

    // doi:KernelMetadata - Required
/************ This is not guaranteed to provide xml with original whitespace and 
 ************ element order (Canonicalization) which will be necessary for 
 ************ Signature checking. Furthermore, XMLDocument cannot encode()
 ************ a SubDoc for some reason ...
 ************ Therefore, this code has been replaced with KLUDGE code below.
    XMLDocument* DOI_SubDoc = xdoc.getSubDoc("doi:KernelMetadata");
    if (DOI_SubDoc == NULL)
    {
        gLogger->logError("doi:KernelMetadata element missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pIPMP_ContentId->set_DOI_XML_str(DOI_SubDoc->encode() );
    delete[] DOI_SubDoc;
***************/

    /***** KLUDGE doi:KernelMetadata - Required ***/
    
    // initialize stl std::string with xml stream and create lowercase transformation
    std::string fullxml = xml_stream;
    std::string fullxml_lower = xml_stream;
    std::string::size_type pos1=0, pos2=0;
    std::transform(fullxml_lower.begin(), fullxml_lower.end(), fullxml_lower.begin(), tolower);
    
    // find DOI start tag
    pos1 = fullxml_lower.find ("<doi:kernelmetadata",0);
    if (pos1 == std::string::npos) {
        gLogger->logError("<doi:KernelMetadata> tag not found in IPMP_ContentId.");
        return(NULL);
    }
    
    // find DOI end tag
    pos2 = fullxml_lower.find ("</doi:kernelmetadata>",0);
    if (pos1 == std::string::npos) {
        gLogger->logError("</doi:KernelMetadata> tag not found in IPMP_ContentId.");
        return(NULL);
    }
    pos2 += strlen("</doi:KernelMetadata>");
    
    // extract DOI xml substring from original (mixed case) xml stream
    std::string doixml = fullxml.substr(pos1, (pos2 - pos1) );
    pIPMP_ContentId->set_DOI_XML_str( (char*)  doixml.c_str() );

    /***** doi:KernelMetadata - Required - end ***/

    // Signature - Required
/************ This is not guaranteed to provide xml with original whitespace and 
 ************ element order (Canonicalization) which should not matter for the 
 ************ Signature. More importantly, XMLDocument cannot encode()
 ************ a SubDoc for some reason ...
 ************ Therefore, this code has been replaced with KLUDGE code below.
    XMLDocument* DigitalSignature_SubDoc = xdoc.getSubDoc("Signature");
    if (DigitalSignature_SubDoc == NULL)
    {
        gLogger->logError("Signature element missing!");
        return(NULL);	// TODO: this should probably throw an exception
    }
    pIPMP_ContentId->set_DigitalSignature_XML_str(DigitalSignature_SubDoc->encode() );
    delete[] DigitalSignature_SubDoc;
***************/


    /***** KLUDGE Signature - Required ***/

    // find DOI start tag
    pos1 = fullxml_lower.find ("<signature",0);
    if (pos1 == std::string::npos) {
        gLogger->logError("<Signature> tag not found in IPMP_ContentId.");
        return(NULL);
    }
    
    // find DOI end tag
    pos2 = fullxml_lower.find ("</signature>",0);
    if (pos1 == std::string::npos) {
        gLogger->logError("</Signature> tag not found in IPMP_ContentId.");
        return(NULL);
    }
    pos2 += strlen("</Signature>");
    
    // extract DOI xml substring from original (mixed case) xml stream
    std::string sigxml = fullxml.substr(pos1, (pos2 - pos1) );
    pIPMP_ContentId->set_DigitalSignature_XML_str( (char*)  sigxml.c_str() );

    /***** Signature - Required - end ***/

    // set raw XML string on IPMP_ContentId
    pIPMP_ContentId->set_XML_str ( (char*) xml_stream);
	    
    // return newly created IPMP_ContentId
    return(pIPMP_ContentId);
 }
