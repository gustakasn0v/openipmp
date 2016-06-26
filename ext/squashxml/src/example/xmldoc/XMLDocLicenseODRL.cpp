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

#include "squashxml/example/xmldoc/XMLDocLicenseODRL.h"
#include "squashxml/tools/FileLogger.h"

XMLDocLicenseODRL::XMLDocLicenseODRL(char* xmlText)
{
	isGoodDocument = XMLDocument::decode(xmlText, "o-ex:rights");
}


bool XMLDocLicenseODRL::demo()
{

	if (!isGoodDocument)
		return false;

	// Getting a String Value
	//
	char* signatureValue = XMLDocument::getString("ds:Signature.ds:SignatureValue");
	gLogger->logInfo("Signature Value below:");
	gLogger->logInfo(signatureValue);
	delete[] signatureValue;

	char* certValue = XMLDocument::getString("ds:Signature.ds:KeyInfo.ds:X509Data.ds:X509Certificate");
	gLogger->logInfo("Certificate Value below:");
	gLogger->logInfo(certValue);
	delete[] certValue;


	char* uidValue = XMLDocument::getString("o-ex:agreement.o-ex:party.o-ex:context.o-dd:uid");
	gLogger->logInfo("User ID Value below:");
	gLogger->logInfo(uidValue);
	delete[] uidValue;

	// Removing a section
	//
	if (!XMLDocument::remove("ds:Signature"))
		return false;

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
