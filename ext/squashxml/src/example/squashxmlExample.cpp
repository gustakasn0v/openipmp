/* ***** BEGIN LICENSE BLOCK *****
 *	The contents of this file are subject to the Mozilla Public License
 *	Version 1.1 (the "License"); you may not use this file except in
 *	compliance with the License. You may obtain a copy of the License at
 *	http://www.mozilla.org/MPL/
 *
 *	Software distributed under the License is distributed on an "AS IS"
 *	basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *	License for the specific language governing rights and limitations
 *	under the License.
 *
 *	The Original Code is SquashXML.
 *
 *	The Initial Developer of the Original Code is Ayman A. Gebrail.
 *	Portions created by Ayman A. Gebrail are
 *	Copyright (C) 2002 Ayman A. Gebrail. All Rights Reserved.
 *
 *  Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

// squashxmlExample.cpp
//

#include "squashxml/xml/XMLDocument.h"
#include "squashxml/example/xmldoc/XMLDocDOIKernel.h"
#include "squashxml/tools/FileTool.h"
#include "squashxml/tools/FileLogger.h"


/*
bool TestXMLDocDOIKernel()
{
	gLogger->logInfo("TestXMLDocDOIKernel - Started");

	// Read the XML input
	ByteArray* pBytes = FileTool::readFile("DOIkernel.xml");
	if (pBytes == NULL)
	{
		gLogger->logError("TestXMLDocDOIKernel - could not read sample xml file.");
		return false;
	}


	// Create and Parse the XMLDocument
	XMLDocDOIKernel* pDocDOI = new XMLDocDOIKernel((char*)pBytes->data());
	if (pDocDOI == NULL)
	{
		gLogger->logError("CFileChooserDlg::TestXMLDocDOIKernel - could not create XMLDocDOIKernel");
		return false;
	}
	delete pBytes;

	pDocDOI->demo();

	delete pDocDOI;

	gLogger->logInfo("TestXMLDocDOIKernel - Done!");

	return true;
}
*/

bool TestXMLDocument()
{
	char msg[1024];


	gLogger->logInfo("TestXMLDocument - Started");

	// Read the XML input
	ByteArray* pBytes = FileTool::readFile("ContentID.xml");
	if (pBytes == NULL)
	{
		gLogger->logError("TestXMLDocument - could not read sample xml file.");
		return false;
	}


	// Create and Parse the XMLDocument
	XMLDocument* pDocDCD = new XMLDocument();
	if (pDocDCD == NULL)
	{
		gLogger->logError("TestXMLDocument - could not create XMLDocument");
		return false;
	}

	pDocDCD->decode(pBytes->data(), "CIDFMAIN");
	delete pBytes;


	// Getting a String Value
	//
	char* contractDeposit = pDocDCD->getString("RIGHTSOPERATING.PERMISSIONS.PCONTRACTDEPOSIT");
	sprintf(msg, "TestXMLDocument - \tcontractDeposit = %s", (contractDeposit == NULL)?"NULL":contractDeposit);
	gLogger->logInfo(msg);
	delete[] contractDeposit;

	// Setting a String Value
	//
	if (!pDocDCD->setString("RIGHTSOPERATING.PERMISSIONS.PCONTRACTDEPOSIT", "A verbal/handshake contract."))
		gLogger->logError("TestXMLDocument - failed to modify contract deposit");


	// Getting a Int
	int contractNum = pDocDCD->getInteger("RIGHTSOPERATING.PERMISSIONS.PCONTRACTNUMBER");
	sprintf(msg, "TestXMLDocument - \tcontractNumber = %d", contractNum);
	gLogger->logInfo(msg);

	// Setting a Int
	if (!pDocDCD->setInteger("RIGHTSOPERATING.PERMISSIONS.PCONTRACTNUMBER", 10018))
		gLogger->logError("TestXMLDocument - failed to modify contract number");


	// ALTERNATE SubDoc style code
	XMLDocument* permissions = pDocDCD->getSubDoc("RIGHTSOPERATING.PERMISSIONS");
	if (permissions != NULL)
	{
		// ALTERNATE SubDoc: Getting a String Value
		//
		char* contractDeposit2 = permissions->getString("PCONTRACTDEPOSIT");
		sprintf(msg, "TestXMLDocument - \tcontractDeposit2 = %s", (contractDeposit2 == NULL)?"NULL":contractDeposit2);
		gLogger->logInfo(msg);
		delete[] contractDeposit2;

		// ALTERNATE SubDoc: Getting a Int
		int contractNum2 = permissions->getInteger("PCONTRACTNUMBER");
		sprintf(msg, "TestXMLDocument - \tcontractNumber = %d", contractNum2);
		gLogger->logInfo(msg);

		delete permissions;
	}


	// Get all elements of the given name (e.g. "CREATOR" in DCD) as a collection of XMLDocument's.
	// NOTE: No path should be specified here.  The list of creators can be anywhere in the tree.
	//
	// TODO: This should be a Vector, not a HashMap, of XMLDocument's
	HashMap* creators = pDocDCD->getDocList("CREATOR");
	if (creators == NULL)
		gLogger->logError("TestXMLDocument - failed to find creator(s)");
	else
	{
		int len = creators->size();
		XMLDocument* creator = NULL;
		for (int i = 0; i < len; i++)
		{
			if (i == 0)
				creator = (XMLDocument*)creators->first();
			else
				creator = (XMLDocument*)creators->next();

			sprintf(msg, "Creator #%d ========", i+1);
			gLogger->logInfo(msg);
			if (creator == NULL)
			{
				gLogger->logError("\tNULL creator in list");
				continue;
			}

			// Get a String
			char* creatorID = creator->getString("CREATOR_ID");
			sprintf(msg, "TestXMLDocument - \tcreatorID = %s", (creatorID == NULL)?"NULL":creatorID);
			gLogger->logInfo(msg);
			delete[] creatorID;  creatorID = NULL;

			// Get another String
			char* popularName = creator->getString("POPULARNAME");
			sprintf(msg, "TestXMLDocument - \tpopularName = %s", (popularName == NULL)?"NULL":popularName);
			gLogger->logInfo(msg);
			delete[] popularName;  popularName = NULL;

			// Get a String qualified with a single attribute (name,value) pair.
			// e.g. <CONTACTPOINT type="Mail">ayman@nyc.rr.com</CONTACTPOINT>
			DataTypeAttribute mailAttribute("type", "Mail");
			char* contactMail = creator->getString("CONTACTPOINT", &mailAttribute);
			sprintf(msg, "TestXMLDocument - \tcontactMail = %s", (contactMail == NULL)?"NULL":contactMail);
			gLogger->logInfo(msg);
			delete[] contactMail;  contactMail = NULL;

			// Get the same String ("CONTACTPOINT") qualified with a different attribute
			// e.g. <CONTACTPOINT type="mainPhone">800-555-1212</CONTACTPOINT>
			DataTypeAttribute mainPhoneAttribute("type", "mainPhone");
			char* contactMainPhone = creator->getString("CONTACTPOINT", &mainPhoneAttribute);
			sprintf(msg, "TestXMLDocument - \tcontactMainPhone = %s", (contactMainPhone == NULL)?"NULL":contactMainPhone);
			gLogger->logInfo(msg);
			delete[] contactMainPhone;  contactMainPhone = NULL;
		}


		// Add a new creator to the list by: duplicating the last creator, and then modifying some values
		if (creator != NULL)
		{
			XMLDocument* newCreator = creator->clone();	// clone also adds the cloned branch to the document!
			newCreator->setString("CREATORNAME", "Ayman Gebrail");
			newCreator->setString("CREATOR_ID", "agebrail");
			newCreator->setString("POPULARNAME", "aymang.");

			Date* birthDate = new Date();	birthDate->now();	birthDate->setYear(1967); birthDate->setMonth(8); // ??
			newCreator->setDate("BIRTHDATE", birthDate);
			delete birthDate;

			newCreator->setString("AFFILIATION", "SquashXML");

			delete newCreator;
		}

		for (int x = 0; x < len; x++)
		{
			if (x == 0)
				creator = (XMLDocument*)creators->first();
			else
				creator = (XMLDocument*)creators->next();
			delete creator;
		}

		delete creators;
	}


	// Get/Set a String qualified with a collection of attributes
	// e.g. <GN_DETAILS type="main" code="I8.13">Hobby/MAJAN</GN_DETAILS>
	DataTypeAttribute mainAttribute("type", "main");
	DataTypeAttribute codeAttribute("code", "I8.13");
	DataTypeAttribute *attList[] = { &mainAttribute, &codeAttribute, /*DON'T FORGET*/(DataTypeAttribute*)NULL };
	char* genreDetails = pDocDCD->getString("CONTENT.CLASS.GENRE.GN_DETAILS", attList);
	sprintf(msg, "TestXMLDocument - \tgenreDetails = %s", (genreDetails == NULL)?"NULL":genreDetails);
	gLogger->logInfo(msg);
	delete[] genreDetails;  genreDetails = NULL;

	// Set a String qualified with a collection of attributes
	pDocDCD->setString("CONTENT.CLASS.GENRE.GN_DETAILS", attList, "Rap");


	// ONE MORE THING - Write the modified XML to a new file
	char* modifiedXML = pDocDCD->encode();
	if (modifiedXML == NULL)
		gLogger->logError("TestXMLDocument - Could not produce modified XML text");
	else
	{
		ByteArray bytes(modifiedXML, strlen(modifiedXML));
		FileTool::writeFile("ContentID-modified.xml", &bytes);
		delete[] modifiedXML;
	}


	delete pDocDCD;

	gLogger->logInfo("TestXMLDocument - Completed SUCESSFULLY");

	return true;
}

/*
#include "squashxml/socket/SquashXMLServletClient.h"
#include "squashxml/example/XMLMessageExampleBase.h"
#include "squashxml/example/XMLMessageGenericError.h"
#include "squashxml/example/XMLMessageWhatDayOfWeek.h"
#include "squashxml/example/XMLMessageWhatDayOfWeekResponse.h"
#include "squashxml/tools/Date.h"

bool TestServletClient()
{

	XMLMessageWhatDayOfWeek whatDayOfWeek;
	Date dt; dt.setYear(1967); dt.setMonth(10); dt.setDay(22);
	whatDayOfWeek.setDateInQuestion(&dt);

	SquashXMLServletClient servletClient("127.0.0.1", 8080);
	if (!servletClient.connect())
		return false;
	XMLMessageBean* response = servletClient.sendRequestGetResponse(&whatDayOfWeek);
	if (response == NULL)
		return false;

	if (response->getMessageType() == XMLMessageExampleBase.WHAT_DAY_OF_WEEK_RESPONSE)
	{
		XMLMessageWhatDayOfWeekResponse* wdowResponse = (XMLMessageWhatDayOfWeekResponse*)response;
		char* answer = wdowResponse->getDayOfWeekDateInQuestion();


		dt.now();
		whatDayOfWeek.setDateInQuestion(&dt);

		delete response;
		response = servletClient.sendRequestGetResponse(&whatDayOfWeek);
		if (response == NULL)
			return false;

		if (response->getMessageType() == XMLMessageExampleBase.WHAT_DAY_OF_WEEK_RESPONSE)
		{
			wdowResponse = (XMLMessageWhatDayOfWeekResponse*)response;
			answer = wdowResponse->getDayOfWeekDateInQuestion();
		}

		bool breakpoint = true;
	}
	else if (response->getMessageType() == XMLMessageExampleBase.GENERIC_ERROR)
	{
		delete response;
		return false;
	}
	else
	{
		delete response;
		return false;
	}
	delete response;
	return true;
}

*/

int main(int argc, char** argv)
{
//	TestXMLDocDOIKernel();
	TestXMLDocument ();

//	TestServletClient();

	printf("Ayman ---> %s\n", XMLDocument::xmlPrefix());
	
	return 0;
}
