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

#include "squashxml/example/xmldoc/XMLDocDOIKernel.h"
#include "squashxml/tools/FileLogger.h"
#include "squashxml/tools/HashMap.h"

XMLDocDOIKernel::XMLDocDOIKernel(char* xmlText)
{
	isGoodDocument = XMLDocument::decode(xmlText, "doi:KernelMetadata");
}


bool XMLDocDOIKernel::demo()
{

	if (!isGoodDocument)
		return false;

	// DOI - Requried
	//
	char* DOIval = XMLDocument::getString("DOI");
	if (DOIval == NULL)
	{
		gLogger->logError("DOI value missing!");
		return false;
	}
	gLogger->logInfo("==== DOI:");
	gLogger->logInfo(DOIval);
	delete[] DOIval;

	// Identifiers - not requried
	//
	XMLDocument* identifiersSection = XMLDocument::getSubDoc("Identifiers");
	if (identifiersSection == NULL)
	{
		gLogger->logInfo("Identifiers Section Not Provided.");
	}
	else
	{
		HashMap *identifiersMap = identifiersSection->getDocList("Identifier");
		if (identifiersMap == NULL) // At least one Identifier must be present if Section exists (I think?)
		{
			gLogger->logError("Identifiers Section Empty.");
			delete identifiersSection;
			return false;
		}

		int ilen = identifiersMap->size();	// unbounded
		XMLDocument* identifier = NULL;
		gLogger->logInfo("==== Identifiers:");
		for (int i = 0; i < ilen; i++)
		{
			if (i == 0)
				identifier = (XMLDocument*)identifiersMap->first();
			else
				identifier = (XMLDocument*)identifiersMap->next();
			char* identType = identifier->getString("IdentifierType");
			char* identValue = identifier->getString("IdentifierValue");

			gLogger->logInfo("\t Indentifier:");
			gLogger->logInfo("\t\t Type:");
			gLogger->logInfo((identType == NULL) ? "NULL" : identType);
			gLogger->logInfo("\t\t Value:");
			gLogger->logInfo((identValue == NULL) ? "NULL" : identValue);

			if (identType != NULL)
				delete[] identType;
			if (identValue != NULL)
				delete[] identValue;

			delete identifier;
		}

		identifiersMap->clear();
		delete identifiersMap;

		delete identifiersSection;
	}



	// OR, Support for one Identifier
	char* identType = XMLDocument::getString("Identifiers.Identifier.IdentifierType");
	char* identValue = XMLDocument::getString("Identifiers.Identifier.IdentifierValue");

	gLogger->logInfo("\t Indentifier:");
	gLogger->logInfo("\t\t Type:");
	gLogger->logInfo((identType == NULL) ? "NULL" : identType);
	gLogger->logInfo("\t\t Value:");
	gLogger->logInfo((identValue == NULL) ? "NULL" : identValue);

	if (identType != NULL)
		delete[] identType;
	if (identValue != NULL)
		delete[] identValue;

	if (!XMLDocument::setString("Identifiers.Identifier.IdentifierValue", "S1234-5678(99)87654-3"))
	{
		gLogger->logError("Could not set Identifiers.Identifier.IdentifierValue");
		return false;
	}


	// Titles - not requried
	//
	XMLDocument* titlesSection = XMLDocument::getSubDoc("Titles");
	if (titlesSection == NULL)
	{
		gLogger->logInfo("Titles Section Not Provided.");
	}
	else
	{
		HashMap *titlesMap = titlesSection->getDocList("Title");
		if (titlesMap == NULL) // At least one Title must be present if Section exists (I think?)
		{
			gLogger->logError("Titles Section Empty.");
			delete titlesSection;
			return false;
		}

		int tlen = titlesMap->size();	// unbounded
		XMLDocument* title = NULL;
		gLogger->logInfo("==== Titles:");
		for (int i = 0; i < tlen; i++)
		{
			if (i == 0)
				title = (XMLDocument*)titlesMap->first();
			else
				title = (XMLDocument*)titlesMap->next();
			char* titleValue = title->getString("TitleValue");
			char* titleLang = title->getString("Language");

			gLogger->logInfo("\t Title:");
			gLogger->logInfo("\t\t Value:");
			gLogger->logInfo((titleValue == NULL) ? "NULL" : titleValue);
			gLogger->logInfo("\t\t Language:");
			gLogger->logInfo((titleLang == NULL) ? "NULL" : titleLang);

			if (titleValue != NULL)
				delete[] titleValue;
			if (titleLang != NULL)
				delete[] titleLang;

			delete title;
		}
		delete titlesMap;
		delete titlesSection;
	}


	// Structural Type - Requried
	//
	char* structuralType = XMLDocument::getString("StructuralType");
	// structuralType of: PhysicalFixation, DigitalFixation, Performance, Abstraction
	gLogger->logInfo("==== StructuralType:");
	gLogger->logInfo(structuralType);
	delete[] structuralType;


	// Modes - Requried
	//
	XMLDocument* modesSection = XMLDocument::getSubDoc("Modes");
	if (modesSection == NULL)
	{
		gLogger->logInfo("ERROR: Modes Section Not Provided.");
		return false;
	}

	HashMap *modesMap = modesSection->getDocList("Mode");
	if (modesMap == NULL) // At least one Mode must be present if Section exists (I think?)
	{
		gLogger->logError("Modes Section Empty.");
		delete modesSection;
		return false;
	}
	int mlen = modesMap->size();	// max of 4
	XMLDocument* mode = NULL;
	gLogger->logInfo("==== Modes:");
	for (int i = 0; i < mlen; i++)
	{
		if (i == 0)
			mode = (XMLDocument*)modesMap->first();
		else
			mode = (XMLDocument*)modesMap->next();

		char* modeValue = mode->getString("Mode");
		// modeValue of: Abstract, Audio, AudioVisual, Visual

		gLogger->logInfo("\t Mode:");
		gLogger->logInfo((modeValue == NULL) ? "NULL" : modeValue);

		if (modeValue != NULL)
			delete[] modeValue;

		delete mode;
	}
	delete modesMap;
	delete modesSection;


	// PrimaryAgents - Requried
	//
	XMLDocument* agentsSection = XMLDocument::getSubDoc("PrimaryAgents");
	if (agentsSection == NULL)
	{
		gLogger->logInfo("Agents Section Not Provided.");
		return false;
	}

	HashMap *agentsMap = agentsSection->getDocList("Agent");
	if (agentsMap == NULL) // At least one Agent must be present if Section exists (I think?)
	{
		gLogger->logError("Agents Section Empty.");
		delete agentsSection;
		return false;
	}

	int alen = agentsMap->size();	// unbounded
	XMLDocument* agent = NULL;
	gLogger->logInfo("==== Agent:");
	for (int a = 0; a < alen; a++)
	{
		if (a == 0)
			agent = (XMLDocument*)agentsMap->first();
		else
			agent = (XMLDocument*)agentsMap->next();

		gLogger->logInfo("\t Agent :");
		// Sequence

		gLogger->logInfo("\t\t Name:");
		char* nameType = agent->getString("Name.NameType");
		char* nameValue = agent->getString("Name.NameValue");

		gLogger->logInfo("\t\t\t NameType:");
		gLogger->logInfo((nameType == NULL) ? "NULL" : nameType);
		gLogger->logInfo("\t\t\t NameValue:");
		gLogger->logInfo((nameValue == NULL) ? "NULL" : nameValue);

		if (nameType != NULL)
			delete[] nameType;
		if (nameValue != NULL)
			delete[] nameValue;

		XMLDocument* rolesSection = agent->getSubDoc("Roles");
		if (rolesSection != NULL)
		{
			HashMap *rolesMap = rolesSection->getDocList("Role");
			if (rolesMap != NULL) // At least one Role must be present
			{
				int rlen = rolesMap->size();	// unbounded
				XMLDocument* role = NULL;
				gLogger->logInfo("\t\t Role:");
				for (int r = 0; r < rlen; r++)
				{
					if (r == 0)
						role = (XMLDocument*)rolesMap->first();
					else
						role = (XMLDocument*)rolesMap->next();
					char* roleValue = role->getString("Role");

					gLogger->logInfo("\t\t\t RoleValue:");
					gLogger->logInfo((roleValue == NULL) ? "NULL" : roleValue);

					if (roleValue != NULL)
						delete[] roleValue;

					delete role;
				}
				delete rolesMap;
			}
			delete rolesSection;
		}
		delete agent;
	}

	delete agentsMap;
	delete agentsSection;


	// Assertor - Not requried
	//
	XMLDocument* assertorSection = XMLDocument::getSubDoc("Assertor");
	if (assertorSection == NULL)
	{
		gLogger->logInfo("Assertor Section Not Provided.");
	}
	else
	{
		gLogger->logInfo("==== Assertor:");

		// The Registrant and Authority Sections in Assertor Have Identical Structures
		for (int ra = 0; ra < 2; ra++)
		{
			XMLDocument* regauthSection;
			if (ra == 0)
			{
				regauthSection = assertorSection->getSubDoc("Registrant");
				gLogger->logInfo("\t Registrant");
			}
			else
			{
				regauthSection = assertorSection->getSubDoc("Authority");
				gLogger->logInfo("\t Authority");
			}
			if (regauthSection == NULL)
			{
				gLogger->logError("\t ERROR: Section Not Provided.");
				return false;
			}

			// Name is required
			char* raNameType = regauthSection->getString("Name.NameType");
			char* raNameValue = regauthSection->getString("Name.NameValue");

			gLogger->logInfo("\t\t raName:");
			gLogger->logInfo("\t\t\t raNameType:");
			gLogger->logInfo((raNameType == NULL) ? "NULL" : raNameType);
			gLogger->logInfo("\t\t\t raNameValue:");
			gLogger->logInfo((raNameValue == NULL) ? "NULL" : raNameValue);

			if (raNameType != NULL)
				delete[] raNameType;
			if (raNameValue != NULL)
				delete[] raNameValue;

			XMLDocument* raIdentSection = regauthSection->getSubDoc("Identifier");
			if (raIdentSection != NULL) // Not required
			{
				char* identType = raIdentSection->getString("IdentifierType");
				char* identValue = raIdentSection->getString("IdentifierValue");

				gLogger->logInfo("\t\t raIndentifier:");
				gLogger->logInfo("\t\t\t raIdentType:");
				gLogger->logInfo((identType == NULL) ? "NULL" : identType);
				gLogger->logInfo("\t\t\t raIdentValue:");
				gLogger->logInfo((identValue == NULL) ? "NULL" : identValue);

				if (identType != NULL)
					delete[] identType;
				if (identValue != NULL)
					delete[] identValue;

				delete raIdentSection;
			}
			delete regauthSection;
		}
		delete assertorSection;
	}



	// If NEEDED, make changes by calling setString(), etc
	//

	// Obtaining the modified XML
	//
	char* modifiedXML = XMLDocument::encode();
	if (modifiedXML == NULL)
		gLogger->logError("Could not produce modified XML text");
	else
	{
		gLogger->logInfo("Modified XML below:");
		gLogger->logInfo(modifiedXML);
		delete[] modifiedXML;
	}

	return true;
}
