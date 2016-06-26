// RELLicAuthzDriver.cpp : Defines the entry point for the DLL application.
//

/***********************************************************************************
*
* COPYRIGHT AND LICENSE
*
* Copyright (c) 2003, ContentGuard Holdings, Inc.
*
* ContentGuard OPEN MPEG REL LICENSE AGREEMENT
*
*
* IMPORTANT: READ THIS AGREEMENT ("AGREEMENT") CAREFULLY. THIS SOFTWARE IS LICENSED 
* TO YOU SUBJECT TO THIS AGREEMENT. 
* 
* INSTALLING OR USING THIS SOFTWARE, CLICKING THE "I AGREE" BUTTON, OR OTHERWISE 
* ATTEMPTING TO DOWNLOAD, INSTALL, COPY, MODIFY OR USE ANY PART OF THE SOFTWARE WILL 
* INDICATE THAT YOU HAVE READ, UNDERSTOOD, AND ACCEPTED THESE TERMS AND CONDITIONS. 
* DO NOT PROCEED IN ANY SUCH MANNER UNLESS YOU ARE ABLE AND WILLING TO ENTER INTO AND 
* COMPLY WITH THIS AGREEMENT. CONTENTGUARD STRONGLY RECOMMENDS THAT YOU COPY, PRINT OUT 
* OR DOWNLOAD A COPY OF THIS AGREEMENT AND KEEP IT IN A SAFE PLACE FOR FUTURE REFERENCE. 
* IF YOU DO NOT AGREE TO THE TERMS OF THIS AGREEMENT, THEN DO NOT USE OR COPY THE 
* SOFTWARE AND IMMEDIATELY DESTROY ANY COPY OF THE SOFTWARE YOU MAY HAVE OBTAINED. 
* 
* THIS IS A LICENSE FOR SAMPLE SOFTWARE WHICH MEANS THAT THE SOFTWARE IS A LIMITED 
* VERSION WHICH CONTENTGUARD HAS NOT RELEASED FOR COMMERCIAL USE. THIS SOFTWARE MAY 
* INCUR OPERATING DIFFICULTIES BEYOND YOUR OR CONTENTGUARD’S EXPECTATIONS AND THE FINAL 
* OR COMPLETE VERSIONS OF THE SOFTWARE WHICH CONTENTGUARD MAY RELEASE FOR COMMERCIAL 
* USE IS SUBJECT TO CHANGE.
* 
* 
* 
* 1. Software Definition: The software licensed under this Agreement is the ContentGuard 
* OPEN MPEG REL (in pre-release, incomplete form) software and associated documentation 
* (the "Software"). 
* 
* 2. License Grant: ContentGuard, Inc. ("ContentGuard") hereby grants to you a royalty-free, 
* non-exclusive, license to use, reproduce, "Modify", display, perform, sublicense and 
* distribute the Software. "Modify" means to make any additions to or deletions from the 
* source code of the Software and "Modification" means any such additions or deletions. 
* No right or license is granted herein by ContentGuard other than those which are 
* expressly and unambiguously set forth in this Agreement. Without limiting the immediately 
* preceding sentence, but subject to Section 3 below, no rights or licenses are granted 
* expressly, or by implication, estoppel or otherwise, to any patent rights or trademarks 
* or trade secrets of ContentGuard or any other person in any jurisdiction.  
* 
* 3. Limited Covenant Not To Sue: ContentGuard covenants not to sue you or any person to 
* whom you distribute the Software under any patent owned or controlled by ContentGuard 
* for use of the Software in its original unmodified form.  However, this covenant does 
* not apply to (i) the Software in a form other than its original unmodified form, or 
* (ii) any service, application, system, software, product or other thing which may be 
* used in connection with the Software, or into which the Software may be incorporated, 
* or which may be incorporated into the Software. 
* 
* 4. No Additional Licenses: This Agreement does not grant you a license in any copyright, 
* patent, trademark, trade secret or other intellectual property right concerning any 
* service, application, system, software, product or other thing (including anything you 
* develop using the Software). 
* 
* 5. Grant Back and Covenant Not to Sue: (1) You grant ContentGuard a royalty-free, 
* non-exclusive, license to use, reproduce, Modify, display, perform, sublicense and 
* distribute any Modifications to the Software. (2) You covenant not to sue ContentGuard 
* or any person to whom ContentGuard distributes the Software under any patent owned or 
* controlled by you for use of any Modifications to the Software. However, this covenant 
* does not apply to (i) the Software in a form other than its original form as so Modified, 
* or (ii) any service, application, system, software, product or other thing which may be 
* used in connection with the Software as Modified, or into which the Software as Modified 
* may be incorporated, or which may be incorporated into the Software as Modified.
* 
* 6. Ownership of Software: The Software contains material that is protected by patent, 
* copyright, trade secret, trademark and other intellectual property laws, and by 
* international treaty provisions. ContentGuard retains all right, title and interest in 
* and to the Software, including all patent, copyright, trade secret, trademark, and other 
* intellectual property rights therein. 
* 
* 7. License Limitations: You may not: (i) alter, remove, or cover any patent, copyright, 
* trade secret, trademark, logo, proprietary or licensing notice(s) in or on any part of 
* the Software; (ii) directly or indirectly, export, import or transmit the Software to any 
* country in contravention of the laws of that country or the laws of the United States.  

* 8. Your Indemnity of ContentGuard: You hereby indemnify ContentGuard and hold it, its 
* parents, officers, directors, employees, and agents harmless from, and will defend them 
* against, any and all claims arising out of the use of the Software by you. 
* 
* 9. NO WARRANTY AND WARRANTY DISCLAIMER: The Software may undergo further revisions and 
* changes and may not be made available, in its complete form or otherwise, for commercial 
* licensing. This software may incur operating difficulties beyond your or ContentGuard’s 
* expectations and ContentGuard does not warrant that the Software will be free of design 
* errors or bugs. THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. 
* CONTENTGUARD AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, WHETHER EXPRESS OR IMPLIED 
* (INCLUDING WITHOUT LIMITATION, ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE, OR NON-INFRINGEMENT) OR STATUTORY OR OTHERWISE, REGARDING OR RELATED 
* TO THE SOFTWARE, ITS USE OR ANY INABILITY TO USE IT, THE RESULTS OF ITS USE, AND THIS 
* AGREEMENT. CONTENTGUARD DOES NOT WARRANT THAT THE SOFTWARE IS ERROR FREE OR THAT IT WILL 
* FUNCTION WITHOUT INTERRUPTION. TO THE EXTENT THAT CONTENTGUARD CANNOT DISCLAIM ANY IMPLIED 
* WARRANTIES, THE DURATION AND EXTENT OF SUCH WARRANTY SHALL BE THE MINIMUM PERIOD ALLOWED 
* UNDER ANY APPLICABLE LAW. 
* 
* 10. LIMITATION OF LIABILITY AND REMEDIES: IN NO EVENT SHALL CONTENTGUARD BE LIABLE TO YOU 
* OR ANY THIRD PARTY FOR ANY PROPERTY DAMAGE, PERSONAL INJURY, LOSS OF PROFITS, LOSS OR 
* INTERRUPTION OF BUSINESS, LOSS OF REVENUE, LOSS OF USE, LOSS OF DATA OR OTHER INFORMATION, 
* LOSS OF PRIVACY, FAILURE TO MEET ANY DUTY (INCLUDING OF GOOD FAITH OR OF REASONABLE CARE), 
* NEGLIGENCE, OR OTHER LOSS (INCLUDING PECUNIARY AND NON-PECUNIARY LOSS) OR FOR ANY INDIRECT, 
* SPECIAL, INCIDENTAL, CONSEQUENTIAL, EXEMPLARY OR PUNITIVE DAMAGES, REGARDLESS OF THE FORM 
* OR CAUSE OF ACTION (WHETHER IN AN ACTION IN CONTRACT OR TORT OR BASED ON A WARRANTY), 
* WHETHER IN CONNECTION WITH, UNDER, OR RELATED TO THIS AGREEMENT OR OTHERWISE, EVEN IF 
* CONTENTGUARD HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSSES OR DAMAGES AND EVEN IF SUCH 
* LOSSES OR  DAMAGES ARE FORESEEABLE. WE DISCLAIM ALL LIABILITY FOR INFRINGEMENT OF ANY 
* INTELLECTUAL PROPERTY RIGHTS RELATING TO THE SOFTWARE. SOME STATES/COUNTRIES DO NOT ALLOW 
* THE EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES, SO THE 
* ABOVE LIMITATION MAY NOT BE APPLICABLE TO YOU. IN SUCH STATES/COUNTRIES, CONTENTGUARD'S 
* LIABILITY IS LIMITED TO THE GREATEST EXTENT PERMITTED BY LAW. 
* 
* 11. Termination: ContentGuard may terminate the license of Section 2 should the Software 
* become, or in ContentGuard's opinion be likely to become, the subject of a claim of 
* infringement of a patent, trade secret, copyright, trademark, or other intellectual property 
* right.  
* 
* 12. U.S. Government Restricted Rights: The Software is provided to the U.S. government as a 
* commercial item strictly under the terms and conditions of this Agreement and includes only 
* those rights customarily available to the public. The U.S. government is not authorized to 
* permit disclosure by any agency or other part of the federal government that exceeds in any 
* way the use and disclosure rights (1) conveyed to the U.S. government in this Agreement or 
* (2) provided in FAR 12.212 (Computer Software) and (for Department of Defense use or disclosure) 
* DFAR 227.7202-3 (Rights in Commercial Computer Software or Computer Software Documentation), 
* whichever set of rights provides in (1) or (2) are the more restrictive. 
* 
* 13. Choice of Law: The rights and obligations of ContentGuard and you shall be governed by, 
* and this Agreement shall be construed in accordance with, the laws of the State of Delaware, 
* United States of America and controlling United States federal law, without regard to any 
* principles of conflict of laws which would result in a different choice of laws. Any action 
* or legal proceeding for relief arising out of or relating to this Agreement must be brought in, 
* and you and ContentGuard consent to the exclusive venue and jurisdiction of, and agree not to 
* seek transfer from, any federal and/or state courts having subject matter jurisdiction in 
* Delaware. However, you agree that ContentGuard may bring an action in any court having 
* proper venue and jurisdiction if such action seeks injunctive or other equitable relief 
* concerning protection of its intellectual property rights in the Software. 
* 
* 14. Entire Agreement: This Agreement contains the entire agreement between you and ContentGuard 
* with regard to its subject matter. Any waiver or modification of this Agreement shall be 
* effective only if it is in writing and signed by both you and ContentGuard. 
* 
* 15. Severability: The terms and conditions stated herein are declared to be severable. If a 
* court of competent jurisdiction finds any part of this Agreement invalid or unenforceable, the 
* remaining terms of this Agreement shall be valid and enforceable in such jurisdiction and this 
* Agreement will remain in effect with the provision omitted, unless omission would frustrate the 
* intent of the parties, in which case this Agreement shall immediately terminate.
***********************************************************************************/

/***********************************************************************************
* Please note that #ifdef _WINDOWS means that it is assumed to be running on 
* Windows with MSXML 4, Else it is assumed to be running on CE using MSXML 3).
***********************************************************************************/

#include "stdafx.h"
#include <stdio.h>

using namespace MSXML;

#include "RELLicAuthzDriver.h"
#include "RELLicAuthz.h"
#include "CGUtil.h"



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
#ifdef _WINDOWS
			CoInitialize(NULL);
#else
			CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			CoUninitialize();
			break;
    }
    return TRUE;
}

// This is the constructor of a class that has been exported.
// see RELLicenseAuthorizationDriver.h for the class definition
CRELLicAuthzDriver::CRELLicAuthzDriver() : m_bValidate(false)
{ 
	return; 
}

//------------------------------------------------------------------------------------------
//--FUNCTION logIssuers
//------------------------------------------------------------------------------------------
//--This function is used to print the issuers for the matching grants.  This is called 
//  if the '-d' flag was used when running the driver.
//------------------------------------------------------------------------------------------
CComBSTR CRELLicAuthzDriver::logIssuers(CRELStringArray* prelstaIssuers)
{
	USES_CONVERSION;
	CComPtr<IXMLDOMParseError>  spXMLError = NULL;	// For XML errors
	CComPtr<IXMLDOMDocument>	spIssuer;	
	CComPtr<IXMLDOMNode>		spXMLNodeTemp = NULL;	
	HRESULT						hr;
	long						nErrorCode = E_FAIL;						// For error codes
	CComBSTR					bstrIssuerModulus; 
	CComBSTR					bstrIssuerExponent;
	CComBSTR					bstrLog;

	if(NULL == prelstaIssuers)
	{
		return E_INVALIDARG;
	}//END IF

	// Print out the Issuers
	bstrLog = L"\r\nISSUERS FOR ALL MATCHING GRANTS:\r\n";
	int nIssuerCount = prelstaIssuers->getLength();
	for (int nIdx = 0; nIdx < nIssuerCount; nIdx++)
	{
		// Load each issuer into DOM tree so we can pull out the modulus and exponent for display
		spIssuer = NULL;
		VARIANT_BOOL bLoad = VARIANT_FALSE;
		BSTR bstrTmp = (*prelstaIssuers)[nIdx].m_str;
		if(CGUtil::loadXML(bstrTmp, spIssuer, bLoad) != S_OK || bLoad == VARIANT_FALSE)
		{
			bstrLog += L"Failed to create issuer DOM \r\n";
			if (spIssuer != NULL)
				hr = spIssuer->get_parseError(&spXMLError);

			if(spXMLError != NULL)
			{
				hr = spXMLError->get_errorCode(&nErrorCode);
				if (hr == S_OK && nErrorCode != 0)
				{
					hr = CGUtil::ReportError(spXMLError, bstrLog);
				}//END IF
			}//END IF
			return bstrLog;
		}//END IF

		spXMLNodeTemp = NULL;
		hr = spIssuer->selectSingleNode (XPATH_ISSUER_MODULUS_FROM_ROOT, &spXMLNodeTemp);
		if (!SUCCEEDED(hr))
			return NULL;
		if (spXMLNodeTemp != NULL)
			hr = spXMLNodeTemp->get_text(&bstrIssuerModulus);
		else
			bstrIssuerModulus = L"Missing modulus.";

		spXMLNodeTemp = NULL;
		hr = spIssuer->selectSingleNode (XPATH_ISSUER_EXPONENT_FROM_ROOT, &spXMLNodeTemp);
		if (!SUCCEEDED(hr))
			return NULL;
		if (spXMLNodeTemp != NULL)
			hr = spXMLNodeTemp->get_text(&bstrIssuerExponent);
		else
			bstrIssuerExponent = L"Missing exponent.";


		TCHAR tTemp[256];
		_stprintf(tTemp, _T("Issuer #%d:\r\n"), nIdx+1);
		BSTR bstrTemp = T2BSTR(tTemp);
		bstrLog += bstrTemp;
		::SysFreeString(bstrTemp);
		bstrLog += L"           Modulus=[";
		bstrLog += bstrIssuerModulus;
		bstrLog += L"]\r\n";
		bstrLog += L"           Exponent=[";
		bstrLog += bstrIssuerExponent;
		bstrLog += L"]\r\n";
	}//END FOR LOOP

	return bstrLog;
}//END FUNCTION printIssuers


//------------------------------------------------------------------------------------------
//--FUNCTION extractRequestItemsFromString
//------------------------------------------------------------------------------------------
//--This function loads the two input files (REL license file & XML query file) into DOM and 
//  extracts the REL licenseGroup we will be querying agains and the query items. The query 
//  items are the user modulus, the user exponent, the REL right, the resource location URI, 
//  and the ISO date time to check agains validityInterval conditions we find.
//--Parameters:
//		CComBSTR bstrLicense			  ->the REL input license string
//		CComBSTR bstrQuery				  ->the XML query file
//		CComBSTR &rbstrLicenseGroup		  ->returns the licenseGroup extracted from wstrLicenseFileName
//		CComBSTR &rbstrUserModulus		  ->returns the user modulus extracted from wstrQueryFileName
//		CComBSTR &rbstrUserExponent		  ->returns the user exponent extracted from wstrQueryFileName
//		CComBSTR &rbstrRELRight			  ->returns the right extracted from wstrQueryFileName
//		CComBSTR &rbstrResourceLocationUri->returns the resource location URI extracted from wstrQueryFileName
//		CComBSTR &rbstrTimetoCheck		  ->returns the ISO date time extracted from wstrQueryFileName
//	    int		 &rnExCounttoCheck		  ->returns the intended exercise count for the right
//		bool	 &rbUpdate				  ->returns the flag that indicates whether to update the 
//											local statereference file.

//--All return parameters must be allocated by the caller
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthzDriver::extractRequestItemsFromString(
	CComBSTR bstrLicense,				
	CComBSTR bstrQuery,					
	CComBSTR &rbstrLicenseGroup,				
	CComBSTR &rbstrUserModulus,
	CComBSTR &rbstrUserExponent,
	CComBSTR &rbstrRELRight,				
	CComBSTR &rbstrResourceLocationUri,				  	  
	CComBSTR &rbstrTimetoCheck,
	int		 &rnExCounttoCheck,
	bool	 &rbUpdate)
{
	CComPtr<IXMLDOMDocument> spXMLLicenseDoc;		// For the license file
	CComPtr<IXMLDOMDocument> spXMLQueryDoc;		// For the input query file
	long				nErrorCode = E_FAIL;	// For error codes
	CComPtr<IXMLDOMParseError>  spXMLError = NULL;	// For XML errors
	HRESULT				hr;
	CComBSTR bstrLog;


	USES_CONVERSION;

	//
	// Load the license file into DOM
	//

	VARIANT_BOOL bLoad = VARIANT_FALSE;
	if(hr = CGUtil::loadXML(bstrLicense.m_str, spXMLLicenseDoc, bLoad) != S_OK || bLoad == VARIANT_FALSE)
    {
		bstrLog += L"Failed to load the input license\r\n";
		if (spXMLLicenseDoc != NULL)
		    hr = spXMLLicenseDoc->get_parseError(&spXMLError);

		if(spXMLError != NULL)
		{
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (hr == S_OK && nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrLog);
			}//END IF
		}//END IF
		CGUtil::writeLog(bstrLog);
		return E_FAIL;
    }//END IF

	// Load the XML query file into DOM
	bLoad = VARIANT_FALSE;
    if(hr = CGUtil::loadXML(bstrQuery.m_str, spXMLQueryDoc, bLoad) != S_OK || bLoad == VARIANT_FALSE)
    {
		bstrLog += L"Failed to load the input query\r\n";
		if (spXMLQueryDoc != NULL)
		    hr = spXMLQueryDoc->get_parseError(&spXMLError);
		if(spXMLError != NULL)
		{			
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (hr == S_OK && nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrLog);
			}//END IF
		}//END IF
		CGUtil::writeLog(bstrLog);
	    return E_FAIL;
    }//END IF

	return extractRequestItemsHelper(spXMLLicenseDoc, spXMLQueryDoc, rbstrLicenseGroup, 
		rbstrUserModulus, rbstrUserExponent, rbstrRELRight,				
		rbstrResourceLocationUri, rbstrTimetoCheck, rnExCounttoCheck,
		rbUpdate);


}//END FUNCTION extractRequestItemsFromString



//------------------------------------------------------------------------------------------
//--FUNCTION extractRequestItemsHelper
//------------------------------------------------------------------------------------------
//--This function loads the two input files (REL license file & XML query file) into DOM and 
//  extracts the REL licenseGroup we will be querying agains and the query items. The query 
//  items are the user modulus, the user exponent, the REL right, the resource location URI, 
//  and the ISO date time to check agains validityInterval conditions we find.
//--Parameters:
//		CComPtr<IXMLDOMDocument> spXMLLicenseDoc ->the REL input license document
//		CComPtr<IXMLDOMDocument> spXMLQueryDoc ->the XML query document
//		CComBSTR &rbstrLicenseGroup		  ->returns the licenseGroup extracted from wstrLicenseFileName
//		CComBSTR &rbstrUserModulus		  ->returns the user modulus extracted from wstrQueryFileName
//		CComBSTR &rbstrUserExponent		  ->returns the user exponent extracted from wstrQueryFileName
//		CComBSTR &rbstrRELRight	    		  ->returns the right extracted from wstrQueryFileName
//		CComBSTR &rbstrResourceLocationUri	  ->returns the resource location URI extracted from wstrQueryFileName
//		CComBSTR &rbstrTimetoCheck		  ->returns the ISO date time extracted from wstrQueryFileName
//	    int		 &rnExCounttoCheck		  ->returns the intended exercise count for the right
//		bool	 &rbUpdate				  ->returns the flag that indicates whether to update the 
//											local statereference file.

//--All return parameters must be allocated by the caller
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthzDriver::extractRequestItemsHelper(
	CComPtr<IXMLDOMDocument> spXMLLicenseDoc,				
	CComPtr<IXMLDOMDocument> spXMLQueryDoc,					
	CComBSTR &rbstrLicenseGroup,				
	CComBSTR &rbstrUserModulus,
	CComBSTR &rbstrUserExponent,
	CComBSTR &rbstrRELRight,				
	CComBSTR &rbstrResourceLocationUri,				  	  
	CComBSTR &rbstrTimetoCheck,
	int		 &rnExCounttoCheck,
	bool	 &rbUpdate)
{
	CComPtr<IXMLDOMNode>		spXMLNodeTemp = NULL;	
	HRESULT				hr;
	CComBSTR bstrLog;


	USES_CONVERSION;

	if (spXMLLicenseDoc == NULL || spXMLQueryDoc == NULL)
	{
		bstrLog += L"Invalid request input. Could not load either the license or the query\r\n"; 
		CGUtil::writeLog(bstrLog);
		return E_FAIL;	
	}

	//
	// Pull out the query items from the XML query file.
    //

	// Grab the modulus for the principal we want to test against
	hr = spXMLQueryDoc->selectSingleNode(XPATH_QUERY_MODULUS, &spXMLNodeTemp);
	if(hr != S_OK || spXMLNodeTemp == NULL)
	{
		bstrLog += L"Invalid request input. Could not find value for rsaModulus\r\n"; 
		CGUtil::writeLog(bstrLog);
		return E_FAIL;	
	}//END IF
	hr = spXMLNodeTemp->get_text(&rbstrUserModulus);
	if (hr != S_OK)
		return E_FAIL;

	// Grab the exponent for the principal we want to test against
	spXMLNodeTemp = NULL;
	hr = spXMLQueryDoc->selectSingleNode(XPATH_QUERY_EXPONENT, &spXMLNodeTemp);
	if(hr != S_OK || spXMLNodeTemp == NULL)
	{
		bstrLog += L"Invalid request input. Could not find value for rsaExponent\r\n"; 
		CGUtil::writeLog(bstrLog);
		return E_FAIL;
	}//END IF
	hr = spXMLNodeTemp->get_text(&rbstrUserExponent);
	if (hr != S_OK)
		return E_FAIL;

	// Grab the right we want to test for
	spXMLNodeTemp = NULL;
	hr = spXMLQueryDoc->selectSingleNode(XPATH_QUERY_RIGHT, &spXMLNodeTemp);
	if(spXMLNodeTemp== NULL || hr != S_OK)
	{
		bstrLog += L"Invalid request input. Could not find value for the right.\r\n"; 
		CGUtil::writeLog(bstrLog);
		return E_FAIL;
	}//END IF	
	hr = spXMLNodeTemp->get_xml(&rbstrRELRight);
	if (hr != S_OK)
		return E_FAIL;

	// Grab the uri for the resource we want to test for
	spXMLNodeTemp = NULL;
	hr = spXMLQueryDoc->selectSingleNode(XPATH_QUERY_RESOURCE_URI, &spXMLNodeTemp);
	if(spXMLNodeTemp == NULL || hr != S_OK)
	{
		bstrLog += L"Invalid request input. Could not find value for the resource uri.\r\n"; 
		CGUtil::writeLog(bstrLog);
		return E_FAIL;
	}//END IF	
	hr = spXMLNodeTemp->get_text(&rbstrResourceLocationUri);
	if (hr != S_OK)
		return E_FAIL;

	// Grab the time we want to use to compare against the validityInterval condition
	spXMLNodeTemp = NULL;
	hr = spXMLQueryDoc->selectSingleNode(XPATH_QUERY_REFERENCE_TIME, &spXMLNodeTemp);
	if(spXMLNodeTemp == NULL || hr != S_OK)
	{
		bstrLog += L"Invalid request input. Could not find value for the date/time.\r\n"; 
		CGUtil::writeLog(bstrLog);
		return E_FAIL;
	}//END IF	
    
	hr = spXMLNodeTemp->get_text(&rbstrTimetoCheck);
	if (hr != S_OK)
		return E_FAIL;

	// Grab the intended usage count from the query, if available
	spXMLNodeTemp = NULL;
	hr = spXMLQueryDoc->selectSingleNode(XPATH_QUERY_EXLIMIT_COUNT, &spXMLNodeTemp);
	if(spXMLNodeTemp == NULL || hr != S_OK)
	{
		rnExCounttoCheck = 1;
	}
	else
	{
		CComBSTR bstrCounttoCheck;
		hr = spXMLNodeTemp->get_text(&bstrCounttoCheck);
		if (hr != S_OK || bstrCounttoCheck.Length() == 0)
			return E_FAIL;
		TCHAR *tszCounttoCheck = OLE2T(bstrCounttoCheck);
		if (!tszCounttoCheck)
			return E_FAIL;

		// This will default to zero if we get an incompatible type
		rnExCounttoCheck = _ttoi(tszCounttoCheck);
	}//END IF	
    
	// Grab the 'update' attribute indicating whether to update the local state reference file
	spXMLNodeTemp = NULL;
	hr = spXMLQueryDoc->selectSingleNode(XPATH_QUERY_EXLIMIT_UPDATE, &spXMLNodeTemp);
	if(spXMLNodeTemp == NULL || hr != S_OK)
	{
		rbUpdate = false;
	}
	else
	{
		CComBSTR bstrUpdate;
		hr = spXMLNodeTemp->get_text(&bstrUpdate);
		if (hr != S_OK || bstrUpdate.Length() == 0)
			return E_FAIL;

		CComBSTR bstrTrue(L"true");
		if (CGUtil::compareBSTR(bstrTrue, bstrUpdate) == 0)
		{
			rbUpdate = true;
		}
		else
		{
			rbUpdate = false;
		}
	}

	// Pull the licenseGroup out of the REL license file
	CComPtr<IXMLDOMElement> spEltTemp;
	hr = spXMLLicenseDoc->get_documentElement(&spEltTemp);
	if (hr == S_OK)
		hr = spEltTemp->get_xml(&rbstrLicenseGroup);
	if (hr != S_OK)
		return E_FAIL;

	return S_OK;
}//END FUNCTION extractRequestItemsHelper



//------------------------------------------------------------------------------------------
//--FUNCTION extractRequestItems
//------------------------------------------------------------------------------------------
//--This function loads the two input files (REL license file & XML query file) into DOM and 
//  extracts the REL licenseGroup we will be querying agains and the query items. The query 
//  items are the user modulus, the user exponent, the REL right, the resource location URI, 
//  and the ISO date time to check agains validityInterval conditions we find.
//--Parameters:
//		CComBSTR bstrLicenseFileName		  ->the REL input license document
//		CComBSTR bstrQueryFileName		  ->the XML query file
//		CComBSTR &rbstrLicenseGroup		  ->returns the licenseGroup extracted from wstrLicenseFileName
//		CComBSTR &rbstrUserModulus		  ->returns the user modulus extracted from wstrQueryFileName
//		CComBSTR &rbstrUserExponent		  ->returns the user exponent extracted from wstrQueryFileName
//		CComBSTR &rbstrRELRight	    		  ->returns the right extracted from wstrQueryFileName
//		CComBSTR &rbstrResourceLocationUri	  ->returns the resource location URI extracted from wstrQueryFileName
//		CComBSTR &rbstrTimetoCheck		  ->returns the ISO date time extracted from wstrQueryFileName
//	    int		 &rnExCounttoCheck		  ->returns the intended exercise count for the right
//		bool	 &rbUpdate				  ->returns the flag that indicates whether to update the 
//											local statereference file.

//--All return parameters must be allocated by the caller
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthzDriver::extractRequestItems(
	CComBSTR bstrLicenseFileName,				
	CComBSTR bstrQueryFileName,					
	CComBSTR &rbstrLicenseGroup,				
	CComBSTR &rbstrUserModulus,
	CComBSTR &rbstrUserExponent,
	CComBSTR &rbstrRELRight,				
	CComBSTR &rbstrResourceLocationUri,				  	  
	CComBSTR &rbstrTimetoCheck,
	int		 &rnExCounttoCheck,
	bool	 &rbUpdate)
{
	CComPtr<IXMLDOMDocument> spXMLLicenseDoc;		// For the license file
	CComPtr<IXMLDOMDocument> spXMLQueryDoc;		// For the input query file
	CComPtr<IXMLDOMParseError>  spXMLError = NULL;	// For XML errors
	long				nErrorCode = E_FAIL;	// For error codes

	HRESULT				hr;
	CComBSTR bstrLog;

	//
	// Load the license file into DOM
	//

	VARIANT_BOOL bLoad = VARIANT_FALSE;
	if(hr = CGUtil::load(bstrLicenseFileName, spXMLLicenseDoc, bLoad, m_bValidate) != S_OK || bLoad == VARIANT_FALSE)
    {
		bstrLog += L"Failed to load ";
		bstrLog += bstrLicenseFileName;
		bstrLog += L"\r\n";
		if (spXMLLicenseDoc != NULL)
		    hr = spXMLLicenseDoc->get_parseError(&spXMLError);

		if(spXMLError != NULL)
		{
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (hr == S_OK && nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrLog);
			}//END IF
		}//END IF
		CGUtil::writeLog(bstrLog);
		return E_FAIL;
    }//END IF

	// Load the XML query file into DOM
	bLoad = VARIANT_FALSE;
    if(hr = CGUtil::load(bstrQueryFileName, spXMLQueryDoc, bLoad) != S_OK || bLoad == VARIANT_FALSE)
    {
		bstrLog += L"Failed to load ";
		bstrLog += bstrQueryFileName;
		bstrLog += L"\r\n";
		if (spXMLQueryDoc != NULL)
		    hr = spXMLQueryDoc->get_parseError(&spXMLError);
		if(spXMLError != NULL)
		{			
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (hr == S_OK && nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrLog);
			}//END IF
		}//END IF
		CGUtil::writeLog(bstrLog);
	    return E_FAIL;
    }//END IF

	return extractRequestItemsHelper(spXMLLicenseDoc, spXMLQueryDoc, rbstrLicenseGroup, 
		rbstrUserModulus, rbstrUserExponent, rbstrRELRight,				
		rbstrResourceLocationUri, rbstrTimetoCheck, rnExCounttoCheck,
		rbUpdate);

}//END FUNCTION extractRequestItems


//------------------------------------------------------------------------------------------
//--FUNCTION relAuthorizeRight
//------------------------------------------------------------------------------------------
//--This is the only public function in this module.  This takes the REL license file & 
//  XML query file as input.  It uses the functions in this module for parsing the input files,
//  then calls the CRELLicAuthz module for validating the request and the condition.
//--Parameters:
//		TCHAR *tLicenseFileName		  ->the REL input license document
//		TCHAR *tQueryFileName		  ->the XML query file
//		bool bIssuerAndConditionPrint ->If true, the issuer and condition list will be logged
//--The function returns the following HRESULT values:
//	S_OK	if at least one matching grant was found and the conditions are satisfied
//	S_FALSE if no matching grants were found and/or the conditions are not satisfied
//	E_FAIL  if an error condition was encountered (an unsupported attribute for example)
//----------------------------------------------------------------------------------------------
HRESULT CRELLicAuthzDriver::relAuthorizeRight(
		TCHAR *tLicenseFileName, 
		TCHAR *tQueryFileName,
		bool bIssuerAndConditionPrint)
{
	USES_CONVERSION;
	CRELLicAuthz	authModule;
	HRESULT						hr = S_OK;							
	CComBSTR					bstrLicenseGroup;					// Will hold the REL licenseGroup extracted from the license file.
	CComBSTR					bstrUserModulus;					// Will hold the modulus (for a keyHolder) extracted from the XML query file.
	CComBSTR					bstrUserExponent;					// Will hold the exponent (for a keyHolder) extracted from the XML query file.
	CComBSTR					bstrResourceLocationUri;			// Will hold the resource uri extracted from the XML query file.	  	  
	CComBSTR					bstrTimetoCheck;					// Will hold the reference time (used as the time of exercise) extracted from the XML query file.	  	  
	CComBSTR					bstrRELKeyHolder = L"";				// Will hold the REL keyHolder that is constructed  using the modulus and exponent we pull from XML query file
	CComBSTR					bstrRELRight;						// Will hold the REL right we pull from XML query file
	CComBSTR					bstrDigResource = L"";				// Will hold the REL digital resource created using the resourceUri from the query file
	CComBSTR					bstrDiReference = L"";				// Will hold the REL diReference created using the resourceUri from the query file
	CRELStringArray				*prelstaIssuers = NULL;				// Pointer for the issuer vector that will be returned
	CComBSTR					bstrIssuer;							// For keyholder 
	CRELStringArray				*prelstaConditions = NULL;			// Pointer for the condition vector that will be returned
	CComBSTR					bstrCondition;						// Used in processing the conditions
	bool						bConditionMet = false;				// Used in processing the conditions
	CComBSTR					bstrLicenseFileName;				// For license file name
	CComBSTR					bstrQueryFileName;					// For input XML query file name
	int							nExCounttoCheck;					// For the intended exercise count
	bool						bUpdate;							// Update the local state reference file

	CComBSTR					bstrLog;							// Place-holder for the log (will be written to the log file later).
	
	if (tLicenseFileName == NULL || tQueryFileName == NULL)
	{
		return E_INVALIDARG;
	}

	// Convert the license file name into a BSTR
	BSTR bstrTemp = T2BSTR(tLicenseFileName);
	bstrLicenseFileName = bstrTemp;
	::SysFreeString(bstrTemp);

	// Convert the query file name into a BSTR
	bstrTemp = T2BSTR(tQueryFileName);
	bstrQueryFileName = bstrTemp;
	::SysFreeString(bstrTemp);

	hr = extractRequestItems(bstrLicenseFileName, bstrQueryFileName, bstrLicenseGroup,
			bstrUserModulus, bstrUserExponent, bstrRELRight, bstrResourceLocationUri,				  	  
			bstrTimetoCheck, nExCounttoCheck, bUpdate);
	if (hr != S_OK)
	{
		return hr;
	}
	//
	// Set up to load the REL License file & the XML query file
	//

	// Construct the principal
	bstrRELKeyHolder = L"<keyHolder xmlns=\"";
	bstrRELKeyHolder += CRELLicAuthz::NS_XRML_CORE;
	bstrRELKeyHolder += "\" xmlns:dsig=\"";
	bstrRELKeyHolder += CRELLicAuthz::NS_DSIG;
	bstrRELKeyHolder += "\"><info><dsig:KeyValue><dsig:RSAKeyValue><dsig:Modulus>";
	bstrRELKeyHolder +=	bstrUserModulus;
	bstrRELKeyHolder +=	L"</dsig:Modulus><dsig:Exponent>";
	bstrRELKeyHolder += bstrUserExponent; 
	bstrRELKeyHolder += L"</dsig:Exponent></dsig:RSAKeyValue></dsig:KeyValue></info></keyHolder>";


	// Construct the digital resource
	bstrDigResource = L"<digitalResource xmlns=\"";
	bstrDigResource += CRELLicAuthz::NS_XRML_CORE;
	bstrDigResource += "\"><nonSecureIndirect URI=\"";
	bstrDigResource += bstrResourceLocationUri;
	bstrDigResource += L"\"/></digitalResource>";
	
	// Construct the digital resource
	bstrDiReference = L"<mx:diReference xmlns:mx=\"";
	bstrDiReference += CRELLicAuthz::NS_MX;
	bstrDiReference += "\"><mx:identifier>";
	bstrDiReference += bstrResourceLocationUri;
	bstrDiReference += L"</mx:identifier></mx:diReference>";


	// Build the CRELStringArray class with these two elements
	CRELStringArray relstaResources;
	relstaResources.addItem(bstrDigResource);
	relstaResources.addItem(bstrDiReference);

	//
	// Call the CRELLicAuthz module
	//
	hr = authModule.validateRequest (bstrLicenseGroup, bstrRELKeyHolder, bstrRELRight, 
		relstaResources, &prelstaConditions, &prelstaIssuers);
	// NOTE: prelstaIssuers are returned by ValidateRequest to allow the application to 
	// perform trust authentication on the issuers before proceeding with authorization


	if (CGUtil::s_bLog)
		authModule.getLogString(bstrLog);

	if (hr == S_OK)  
	{
		//
		// Print out the Issuer and Conditions for the matching grants
		//

		if (bIssuerAndConditionPrint)
		{
			// Print out the Conditions
			bstrLog += L"\r\nCONDITIONS FOR ALL MATCHING GRANTS:\r\n" ;
			int nConditionCount = prelstaConditions->getLength();
			for (int nIdx = 0; nIdx < nConditionCount; nIdx++)
			{
				TCHAR tTemp[1024];
				TCHAR *tCond = OLE2T((*prelstaConditions)[nIdx]);
				_stprintf(tTemp, _T("Condition #%d: %s\r\n"), nIdx+1, tCond);
				bstrTemp = T2BSTR(tTemp);
				bstrLog += bstrTemp;
				::SysFreeString(bstrTemp);
			}//END FOR LOOP

			
			bstrLog += logIssuers(prelstaIssuers);
		}//END IF
		
		
		//
		// Matching grant found, now we need to evaluate the time condition
		//

		bstrLog += L"\r\n\r\nEVALUATING CONDITIONS\r\n";
		int nIdx;
		int nConditionCount = prelstaConditions->getLength();

		for (nIdx = 0; nIdx < nConditionCount; nIdx++)
		{
			if ((*prelstaConditions)[nIdx] == L"")
			{
				// If there was a grant with no condition, no need to evaluate further
				bConditionMet = true;
				// Exit on the first match
				break;
			}
			else
			{
				// We have a condition so lets evaluate it.			
				hr = authModule.validateCondition((*prelstaConditions)[nIdx], bstrTimetoCheck,
					nExCounttoCheck, bUpdate);
				if (S_OK == hr)
				{
					bConditionMet = true;
					// Exit on the first match
					break;
				}//END IF
			}//END IF
		}//END FOR LOOP


		// Was there a condition that was met?
		if (bConditionMet == true)
		{
			TCHAR tTemp[128];
			_stprintf(tTemp, _T("-->condition #%d was met\r\n"), nIdx+1);
			bstrTemp = T2BSTR(tTemp);
			bstrLog += bstrTemp;
			::SysFreeString(bstrTemp);
		}
		else if (nConditionCount == 0)
		{
			bstrLog += L"-->No conditions\r\n";
			bConditionMet = true;
		}
		else
		{
			// Matching grant found, but the condition failed
			bstrLog += L"-->conditions were not met\r\n";
		}//END IF

	}
	else if(hr == S_FALSE)
	{
		bstrLog += L"-->NO MATCHING GRANT WAS FOUND. \r\n";
	}
	else
	{
	  //There was a problem: hr was E_FAIL	
		CComBSTR bstrError;
		authModule.getErrorString(bstrError);
		bstrError += L"-->exiting program. \r\n";
		bstrLog += bstrError;
	}//END IF

	// Lets release the memory that we got for the conditions and issuers and the license ids when 
	// calling validateRequest.
	if(NULL != prelstaConditions)
		prelstaConditions->Release();
	//END IF
	if(NULL != prelstaIssuers)
		prelstaIssuers->Release();
	//END IF

	bstrLog += L"\r\n -- End of License Authorization -----\r\n\r\n";
	CGUtil::writeLog(bstrLog);

	if (hr == S_OK && bConditionMet == false)
		hr = S_FALSE;

	return hr;
}//END FUNCTION RELAuthorizeRight


#ifdef _WINDOWS
//------------------------------------------------------------------------------------------
//--FUNCTION relAuthorizeRight
//------------------------------------------------------------------------------------------
//--This is the only public function in this module.  This takes the REL license file & 
//  XML query file as input.  It uses the functions in this module for parsing the input files,
//  then calls the CRELLicAuthz module for validating the request and the condition.
//--Parameters:
//		BSTR bstrLicense		->the REL input license string
//		BSTR bstrQuery			->the XML query string
//		bool bIssuerAndConditionPrint	->If true, the issuer and condition list will be logged
//--The function returns the following HRESULT values:
//	S_OK	if at least one matching grant was found and the conditions are satisfied
//	S_FALSE if no matching grants were found and/or the conditions are not satisfied
//	E_FAIL  if an error condition was encountered (an unsupported attribute for example)
//----------------------------------------------------------------------------------------------
HRESULT CRELLicAuthzDriver::relAuthorizeRight(
		BSTR bstrLicense, 
		BSTR bstrQuery,
		bool bIssuerAndConditionPrint)
{
	USES_CONVERSION;
	CRELLicAuthz	authModule;
	HRESULT						hr = S_OK;							
	CComBSTR					bstrLicenseGroup;					// Will hold the REL licenseGroup extracted from the license file.
	CComBSTR					bstrUserModulus;					// Will hold the modulus (for a keyHolder) extracted from the XML query file.
	CComBSTR					bstrUserExponent;					// Will hold the exponent (for a keyHolder) extracted from the XML query file.
	CComBSTR					bstrResourceLocationUri;			// Will hold the resource uri extracted from the XML query file.	  	  
	CComBSTR					bstrTimetoCheck;					// Will hold the reference time (used as the time of exercise) extracted from the XML query file.	  	  
	CComBSTR					bstrRELKeyHolder = L"";				// Will hold the REL keyHolder that is constructed  using the modulus and exponent we pull from XML query file
	CComBSTR					bstrRELRight;						// Will hold the REL right we pull from XML query file
	CComBSTR					bstrDigResource = L"";				// Will hold the REL digital resource created using the resourceUri from the query file
	CComBSTR					bstrDiReference = L"";				// Will hold the REL diReference created using the resourceUri from the query file
	CRELStringArray				*prelstaIssuers = NULL;				// Pointer for the issuer vector that will be returned
	CComBSTR					bstrIssuer;							// For keyholder 
	CRELStringArray				*prelstaConditions = NULL;			// Pointer for the condition vector that will be returned
	CComBSTR					bstrCondition;						// Used in processing the conditions
	bool						bConditionMet = false;				// Used in processing the conditions
	int							nExCounttoCheck;					// For the intended exercise count
	bool						bUpdate;							// Update the local state reference file

	CComBSTR					bstrLog;							// Place-holder for the log (will be written to the log file later).

	BSTR						bstrTemp;
	
	if (bstrLicense == NULL || bstrQuery == NULL)
	{
		return E_INVALIDARG;
	}

	hr = extractRequestItemsFromString(bstrLicense, bstrQuery, bstrLicenseGroup,
			bstrUserModulus, bstrUserExponent, bstrRELRight, bstrResourceLocationUri,				  	  
			bstrTimetoCheck, nExCounttoCheck, bUpdate);
	if (hr != S_OK)
	{
		return hr;
	}
	//
	// Set up to load the REL License file & the XML query file
	//

	// Construct the principal
	bstrRELKeyHolder = L"<keyHolder xmlns=\"";
	bstrRELKeyHolder += CRELLicAuthz::NS_XRML_CORE;
	bstrRELKeyHolder += "\" xmlns:dsig=\"";
	bstrRELKeyHolder += CRELLicAuthz::NS_DSIG;
	bstrRELKeyHolder += "\"><info><dsig:KeyValue><dsig:RSAKeyValue><dsig:Modulus>";
	bstrRELKeyHolder +=	bstrUserModulus;
	bstrRELKeyHolder +=	L"</dsig:Modulus><dsig:Exponent>";
	bstrRELKeyHolder += bstrUserExponent; 
	bstrRELKeyHolder += L"</dsig:Exponent></dsig:RSAKeyValue></dsig:KeyValue></info></keyHolder>";


	// Construct the digital resource
	bstrDigResource = L"<digitalResource xmlns=\"";
	bstrDigResource += CRELLicAuthz::NS_XRML_CORE;
	bstrDigResource += "\"><nonSecureIndirect URI=\"";
	bstrDigResource += bstrResourceLocationUri;
	bstrDigResource += L"\"/></digitalResource>";
	
	// Construct the digital resource
	bstrDiReference = L"<mx:diReference xmlns:mx=\"";
	bstrDiReference += CRELLicAuthz::NS_MX;
	bstrDiReference += "\"><mx:identifier>";
	bstrDiReference += bstrResourceLocationUri;
	bstrDiReference += L"</mx:identifier></mx:diReference>";


	// Build the CRELStringArray class with these two elements
	CRELStringArray relstaResources;
	relstaResources.addItem(bstrDigResource);
	relstaResources.addItem(bstrDiReference);

	//
	// Call the CRELLicAuthz module
	//
	hr = authModule.validateRequest (bstrLicenseGroup, bstrRELKeyHolder, bstrRELRight, 
		relstaResources, &prelstaConditions, &prelstaIssuers);
	// NOTE: prelstaIssuers are returned by ValidateRequest to allow the application to 
	// perform trust authentication on the issuers before proceeding with authorization


	if (CGUtil::s_bLog)
		authModule.getLogString(bstrLog);

	if (hr == S_OK)  
	{
		//
		// Print out the Issuer and Conditions for the matching grants
		//

		if (bIssuerAndConditionPrint)
		{
			// Print out the Conditions
			bstrLog += L"\r\nCONDITIONS FOR ALL MATCHING GRANTS:\r\n" ;
			int nConditionCount = prelstaConditions->getLength();
			for (int nIdx = 0; nIdx < nConditionCount; nIdx++)
			{
				TCHAR tTemp[1024];
				TCHAR *tCond = OLE2T((*prelstaConditions)[nIdx]);
				_stprintf(tTemp, _T("Condition #%d: %s\r\n"), nIdx+1, tCond);
				bstrTemp = T2BSTR(tTemp);
				bstrLog += bstrTemp;
				::SysFreeString(bstrTemp);
			}//END FOR LOOP

			
			bstrLog += logIssuers(prelstaIssuers);
		}//END IF
		
		
		//
		// Matching grant found, now we need to evaluate the time condition
		//

		bstrLog += L"\r\n\r\nEVALUATING CONDITIONS\r\n";
		int nIdx;
		int nConditionCount = prelstaConditions->getLength();

		for (nIdx = 0; nIdx < nConditionCount; nIdx++)
		{
			if ((*prelstaConditions)[nIdx] == L"")
			{
				// If there was a grant with no condition, no need to evaluate further
				bConditionMet = true;
				// Exit on the first match
				break;
			}
			else
			{
				// We have a condition so lets evaluate it.			
				hr = authModule.validateCondition((*prelstaConditions)[nIdx], bstrTimetoCheck,
					nExCounttoCheck, bUpdate);
				if (S_OK == hr)
				{
					bConditionMet = true;
					// Exit on the first match
					break;
				}//END IF
			}//END IF
		}//END FOR LOOP


		// Was there a condition that was met?
		if (bConditionMet == true)
		{
			TCHAR tTemp[128];
			_stprintf(tTemp, _T("-->condition #%d was met\r\n"), nIdx+1);
			bstrTemp = T2BSTR(tTemp);
			bstrLog += bstrTemp;
			::SysFreeString(bstrTemp);
		}
		else if (nConditionCount == 0)
		{
			bstrLog += L"-->No conditions\r\n";
			bConditionMet = true;
		}
		else
		{
			// Matching grant found, but the condition failed
			bstrLog += L"-->conditions were not met\r\n";
		}//END IF

	}
	else if(hr == S_FALSE)
	{
		bstrLog += L"-->NO MATCHING GRANT WAS FOUND. \r\n";
	}
	else
	{
	  //There was a problem: hr was E_FAIL	
		CComBSTR bstrError;
		authModule.getErrorString(bstrError);
		bstrError += L"-->exiting program. \r\n";
		bstrLog += bstrError;
	}//END IF

	// Lets release the memory that we got for the conditions and issuers and the license ids when 
	// calling validateRequest.
	if(NULL != prelstaConditions)
		prelstaConditions->Release();
	//END IF
	if(NULL != prelstaIssuers)
		prelstaIssuers->Release();
	//END IF

	bstrLog += L"\r\n -- End of License Authorization -----\r\n\r\n";
	CGUtil::writeLog(bstrLog);

	if (hr == S_OK && bConditionMet == false)
		hr = S_FALSE;

	return hr;
}//END FUNCTION RELAuthorizeRight
#endif

//------------------------------------------------------------------------------------------
//--FUNCTION SetLogFileName
//------------------------------------------------------------------------------------------
//--This function sets the log file name.  This will prompt logging into the file-name supplied.
//--Parameters:
//		TCHAR *tLogFileName		  ->the log File Name
//----------------------------------------------------------------------------------------------
HRESULT CRELLicAuthzDriver::setLogFileName(TCHAR *tLogFileName)
{
	if (tLogFileName != NULL && _tcslen(tLogFileName) > 0)
	{
		CGUtil::s_bLog = true;
		CGUtil::s_tLogFileName = tLogFileName;
	}

	return S_OK;
}
