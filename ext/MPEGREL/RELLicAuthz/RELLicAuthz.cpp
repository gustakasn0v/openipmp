// RELLicAuthz.cpp : Defines the entry point for the DLL application.
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

using namespace MSXML;


#include <stdio.h>
#include "RELLicAuthz.h"
#include "CGUtil.h"
#include "RELStringArray.h"

TCHAR *STATE_ID = _T("stateId");

const BSTR CRELLicAuthz::NS_XRML_CORE = L"http://www.xrml.org/schema/2002/05/xrml2core";
const BSTR CRELLicAuthz::NS_XRML_SX = L"http://www.xrml.org/schema/2002/05/xrml2sx";
const BSTR CRELLicAuthz::NS_MX = L"urn:mpeg:mpeg21:2002:01-REL-NS";
const BSTR CRELLicAuthz::NS_DSIG = L"http://www.w3.org/2000/09/xmldsig#";
const BSTR CRELLicAuthz::NS_XSI = L"http://www.w3.org/2001/XMLSchema-instance";

typedef int (*READFN)(TCHAR *tszConditionId);
typedef int (*UPDATEFN)(TCHAR *tszConditionId, int nExerciseCount);


//------------------------------------------------------------------------------------------
//--FUNCTION DllMain
//------------------------------------------------------------------------------------------
//--This function defines the entry point for the DLL application
//------------------------------------------------------------------------------------------
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	HRESULT hr = E_FAIL;
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
#ifdef _WINDOWS
			hr = CoInitialize(NULL);
#else
			hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
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

//------------------------------------------------------------------------------------------
//--FUNCTION CRELLicAuthz
//------------------------------------------------------------------------------------------
// This is the constructor of the exported class.
// see RELLicenseAuthorization.h for the class definition
//------------------------------------------------------------------------------------------
CRELLicAuthz::CRELLicAuthz()
{
	m_bstrError = NULL;
	m_bstrLog = NULL;
	return; 
}

CRELLicAuthz::~CRELLicAuthz()
{
	if (m_bstrError != NULL)
	{
		::SysFreeString(m_bstrError);
	}
	if (m_bstrLog != NULL)
	{
		::SysFreeString(m_bstrLog);
	}
}

//------------------------------------------------------------------------------------------
//--FUNCTION attributesAreSupported
//------------------------------------------------------------------------------------------
//--This function checks the REL document we are working with to see if there are
//  any unsupported attributes being used. If there are, the program will exit with an error.
//--It takes an IXMLDOMNodePtr containing an XML node as input.
//------------------------------------------------------------------------------------------

HRESULT CRELLicAuthz::attributesAreSupported(CComPtr<IXMLDOMElement> spxmlNode)
{
	USES_CONVERSION;
	CComPtr<IXMLDOMNodeList>	splstAttributeNodeList;	
	CComPtr<IXMLDOMNode>		spCurrAttributeNode;
	HRESULT						hr = S_OK;

	// Lets check to see is a valid DOM node pointer was sent
	if(spxmlNode == NULL)
	{
		CComBSTR bstrError(L"A NULL node pointer was passed in to function attributesAreSupported(...).\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_INVALIDARG;
	}//END IF

	// Grab all the attributes of all the nodes in the document
	hr = spxmlNode->selectNodes(XPATH_ALL_ATTRIBUTES, &splstAttributeNodeList);

	//If we got any attributes lets make sure there aren't any unsupported ones. 
	if (!SUCCEEDED(hr))
	{
		return hr;
	}

	long nLength = 0;

	splstAttributeNodeList->get_length(&nLength);

	hr = S_OK;

	// Loop through all the attributes in all the elements in the licenseGroup
	for (int i = 0; i < nLength; i++ )
	{
		spCurrAttributeNode = NULL;
		HRESULT hrTemp = splstAttributeNodeList->nextNode(&spCurrAttributeNode);
		if (hrTemp != S_OK)
		{
			return hrTemp;
		}
		
		// Test for xsi:type attribute type
		CComBSTR bstrNodeName;
		hrTemp = spCurrAttributeNode->get_nodeName(&bstrNodeName);
		if (hrTemp != S_OK)
		{
			return hrTemp;
		}
		if (CGUtil::compareBSTR(bstrNodeName, XSI_TYPE) == 0) 
		{
			CComBSTR bstrError(L"Encountered unsupported xsi:type attribute type.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			hr = S_FALSE;		
		}
		// Test for licensePartIdRef attribute type
		else if(CGUtil::compareBSTR(bstrNodeName, LICENSE_PART_ID_REF) == 0)
		{
			CComBSTR bstrError(L"Encountered unsupported licensePartIdRef attribute type.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			hr = S_FALSE;
		}
		// Test for varRef attribute type
		else if (CGUtil::compareBSTR(bstrNodeName, VAR_REF) == 0) 
		{
			CComBSTR bstrError(L"Encountered unsupported varRef attribute type.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			hr = S_FALSE;
		}//END IF
	}//END FOR LOOP
		

	return hr;
}//END FUNCTION attributesAreSupported

//------------------------------------------------------------------------------------------
//--FUNCTION extractRequestItems
//------------------------------------------------------------------------------------------
//--This function takes in four strings containing REL for the input license document we are
//  searching for and our query items: the keyHolder, the right, and the resource.
//--It returns a IXMLDOMNodePtr object containing the licenseGroup from the input license
//  document and five strings containing the items we are searching our license document for: 
//  the keyHolder Modulus, the keyHolder Exponent, the right base name, the right URI, and 
//  the resource location URI. 
//--Parameters:
//		BSTR bstrRELDoc							->REL from the input license document
//		BSTR bstrRELKeyHolder					->REL for the keyHolder to search for
//		BSTR bstrRELRight						->REL for the right to search for
//		CRELStringArray &rrelstaRELResource		->Array of REL for the resource to search for
//		IXMLDOMElement **ppRELLicenseGroup		->returns the licenseGroup extracted from wstrRELDoc
//		BSTR *pbstrKeyHolderModulus				->returns modulus extracted from bstrRELKeyHolder
//		BSTR *pbstrKeyHolderExponent			->returns exponent extracted from bstrRELKeyHolder
//		BSTR *pbstrRightBaseName				->returns right base name extracted from bstrRELRight
//		BSTR *pbstrRightUri						->returns right URI extracted from bstrRELRight
//		BSTR *pbstrResourceLocationUri			->returns resource URI extracted from pbstrRELResource
//		BSTR *pbstrResourceDII					->returns resource DII extracted from pbstrRELResource
//--All return parameters must be allocated by the caller.
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::extractRequestItems(
			BSTR bstrRELDoc, 
			BSTR bstrRELKeyHolder, 
			BSTR bstrRELRight, 
			CRELStringArray &rrelstaRELResource,
			IXMLDOMElement **ppRELLicenseGroup,
			BSTR *pbstrKeyHolderModulus,
			BSTR *pbstrKeyHolderExponent,
			BSTR *pbstrRightBaseName, 
			BSTR *pbstrRightUri, 
			BSTR *pbstrResourceLocationUri,
			BSTR *pbstrResourceDII)
{
	CComPtr<IXMLDOMParseError>  spXMLError;	// For XML errors
	CComPtr<IXMLDOMDocument> spRELDoc;	// For the keyHolder we're trying to evaluate
	CComPtr<IXMLDOMDocument> spInputKeyHolder;	// For the keyHolder we're trying to evaluate
	CComPtr<IXMLDOMDocument> spInputRight;	// For the right we're trying to evaluate
	CComPtr<IXMLDOMDocument> spInputResource;	// For the resource we're trying to evaluate
	CComPtr<IXMLDOMNode> spxmlNodeTemp;	// Temp node
	CComPtr<IXMLDOMElement> spEltTemp; // Temp element
	CComBSTR bstrRELResource;

	HRESULT						hr;
	LONG						nErrorCode = E_FAIL;	// For error codes

	// Lets make sure we got valid pointers for our output data.
	if(	ppRELLicenseGroup == NULL || 
		NULL == pbstrKeyHolderModulus || 
		NULL == pbstrKeyHolderExponent || 
		NULL == pbstrRightBaseName || 
		NULL == pbstrRightUri || 
		NULL == pbstrResourceLocationUri ||
		NULL == pbstrResourceDII)
	{
		return E_INVALIDARG;
	}//END IF


	// Load the keyHolder we're trying to get a match on into an XMLDomDocument
	VARIANT_BOOL bLoad = VARIANT_FALSE;
    if(CGUtil::loadXML (bstrRELKeyHolder, spInputKeyHolder, bLoad) != S_OK || bLoad == VARIANT_FALSE)
    {
		CComBSTR bstrError(L"Failed to create keyHolder DOM \r\n");
		if (spInputKeyHolder == NULL)
		{
			CGUtil::appendString(m_bstrError, bstrError);
			return E_FAIL;
		}
	    hr = spInputKeyHolder->get_parseError(&spXMLError);
		if(spXMLError != NULL)
		{
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrError);
			}//END IF
		}//END IF
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;
    }//END IF

	hr = spInputKeyHolder->get_documentElement(&spEltTemp);
	if (hr != S_OK)
	{
		CComBSTR bstrError(L"Unable to extract the document element from the input key holder.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_INVALIDARG;
	}

	CComBSTR bstrNodeName, bstrUri;
	hr = spEltTemp->get_baseName(&bstrNodeName);
	if (hr == S_OK)
	{
		hr = spEltTemp->get_namespaceURI(&bstrUri);
	}

	if (hr != S_OK || CGUtil::compareBSTR(bstrNodeName, KEY_HOLDER) != 0 ||
		CGUtil::compareBSTR(bstrUri, NS_XRML_CORE) != 0)
	{
		CComBSTR bstrError(L"Encountered unsupported query principal (expecting keyHolder).\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_INVALIDARG;
	}

	hr = spEltTemp->selectSingleNode(XPATH_KEY_HOLDER_MODULUS, &spxmlNodeTemp);
	if(hr != S_OK || spxmlNodeTemp == NULL)
	{
	    CComBSTR bstrTemp(L"Unsupported keyHolder.  Could not find modulus.\r\n");
		CGUtil::appendString(m_bstrError, bstrTemp);
		return E_FAIL;
	}//END IF

	hr = spxmlNodeTemp->get_text(pbstrKeyHolderModulus);
	if (hr != S_OK || *pbstrKeyHolderModulus == NULL)
	{
		CComBSTR bstrError(L"Unable to extract the key holder modulus\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return hr;
	}
	spxmlNodeTemp = NULL;

	hr = spEltTemp->selectSingleNode(XPATH_KEY_HOLDER_EXPONENT, &spxmlNodeTemp);
	if(hr != S_OK || spxmlNodeTemp == NULL)
	{
	    CComBSTR bstrTemp(L"Unsupported keyHolder.  Could not find exponent.\r\n");
		CGUtil::appendString(m_bstrError, bstrTemp);
		return E_FAIL;
	}//END IF
	hr = spxmlNodeTemp->get_text(pbstrKeyHolderExponent);;
	if (hr != S_OK)
	{
		CComBSTR bstrError(L"Unable to extract key holder exponent\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return hr;
	}
	spxmlNodeTemp = NULL;
	spEltTemp = NULL;

	// Load the right we're trying to test for into an XMLDomDocument

    if(CGUtil::loadXML (bstrRELRight, spInputRight, bLoad) != S_OK || bLoad == VARIANT_FALSE)
    {
		CComBSTR bstrError(L"Failed to create right DOM \r\n");
		spXMLError = NULL;
		if (spInputRight == NULL)
		{
			CGUtil::appendString(m_bstrError, bstrError);
			return E_FAIL;
		}
	    hr = spInputRight->get_parseError(&spXMLError);
		if(spXMLError != NULL)
		{
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrError);
			}//END IF
		}//END IF
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;
    }//END IF

	//--Since the document loaded fine we know we have a document element.  Lets
	//  get the name of the element and its uri.
	hr = spInputRight->get_documentElement(&spEltTemp);
	if (hr != S_OK || spEltTemp == NULL)
	{
		return E_FAIL;
	}
	hr = spEltTemp->get_baseName(pbstrRightBaseName);
	if (hr == S_OK)
	{
		hr = spEltTemp->get_namespaceURI(pbstrRightUri);
	}
	if (hr != S_OK)
	{
		return hr;
	}

	CComBSTR bstrRightBaseName(*pbstrRightBaseName);
	CComBSTR bstrRightURI(*pbstrRightUri);
	spEltTemp = NULL;

	// Lets make sure it is an mx play right.
	if(CGUtil::compareBSTR(bstrRightBaseName, PLAY) != 0 || CGUtil::compareBSTR(bstrRightURI, NS_MX) != 0)
	{
		CComBSTR bstrError(L"Encountered unsupported query right (expecting mx play).\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;		
	}//END IF


	// Load the resource(s) we're trying to test for into an XMLDomDocument

	int nInputResourceCount = rrelstaRELResource.getLength();
	if (nInputResourceCount < 1 || nInputResourceCount > 2)
	{
		CComBSTR bstrError(L"Encountered unsupported type or combination of resources (expecting a digitalResource and/or a diReference.).\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_INVALIDARG;
	}

	BOOL bDigResFound = FALSE;
	BOOL bDiRefFound = FALSE;

	for (int nResIdx = 0; nResIdx < nInputResourceCount; nResIdx++)
	{
		bstrRELResource = rrelstaRELResource[nResIdx];
		if(CGUtil::loadXML (bstrRELResource.m_str, spInputResource, bLoad) != S_OK || bLoad == VARIANT_FALSE)
		{
			CComBSTR bstrError(L"Failed to create resource DOM \r\n");
			spXMLError = NULL;
			if (spInputResource == NULL)
			{
				CGUtil::appendString(m_bstrError, bstrError);
				return E_FAIL;
			}
			hr = spInputResource->get_parseError(&spXMLError);
			if(spXMLError != NULL)
			{
				hr = spXMLError->get_errorCode(&nErrorCode);
				if (nErrorCode != 0)
				{
					hr = CGUtil::ReportError(spXMLError, bstrError);
				}//END IF
			}//END IF
			CGUtil::appendString(m_bstrError, bstrError);
			return E_FAIL;
		}//END IF

		hr = spInputResource->get_documentElement(&spEltTemp);

		if (hr == S_OK && spEltTemp != NULL)
		{
			hr = spEltTemp->get_baseName(&bstrNodeName);
		}
		if (hr == S_OK)
		{
			hr = spEltTemp->get_namespaceURI(&bstrUri);
		}

		if (hr != S_OK)
		{
			CComBSTR bstrError(L"Unable to extract the namespace uri or the base name of the resource.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			return E_INVALIDARG;
		}		
		
		if (CGUtil::compareBSTR(bstrNodeName, DIGITAL_RESOURCE) == 0 &&
			CGUtil::compareBSTR(bstrUri, NS_XRML_CORE) == 0)
		{
			if (bDigResFound == TRUE)
			{
				CComBSTR bstrError(L"Encountered unsupported combination of resources (expecting a digitalResource or a diReference).\r\n");
				CGUtil::appendString(m_bstrError, bstrError);
				return E_INVALIDARG;
			}
			bDigResFound = TRUE;
			hr = spEltTemp->selectSingleNode (XPATH_RESOURCE_URI, &spxmlNodeTemp);
			if(hr != S_OK || spxmlNodeTemp == NULL)
			{
				CComBSTR bstrError(L"Encountered unsupported resource (expecting a digitalResource).\r\n");
				CGUtil::appendString(m_bstrError, bstrError);
				return E_FAIL;	
			}//END IF

			hr = spxmlNodeTemp->get_text(pbstrResourceLocationUri);
			if (pbstrResourceLocationUri == NULL || hr != S_OK)
			{
				CComBSTR bstrError(L"Unable to extract the resource location uri from the resource supplied.\r\n");
				CGUtil::appendString(m_bstrError, bstrError);
				return E_FAIL;	
			}
		}
		else if (CGUtil::compareBSTR(bstrNodeName, DI_REFERENCE) == 0 &&
			CGUtil::compareBSTR(bstrUri, NS_MX) == 0)
		{
			if (bDiRefFound == TRUE)
			{
				CComBSTR bstrError(L"Encountered unsupported combination of resources (expecting a digitalResource or a diReference).\r\n");
				CGUtil::appendString(m_bstrError, bstrError);
				return E_INVALIDARG;
			}
			bDiRefFound = TRUE;
			hr = spEltTemp->selectSingleNode (XPATH_RESOURCE_DII, &spxmlNodeTemp);
			if(hr != S_OK || spxmlNodeTemp == NULL)
			{
				CComBSTR bstrError(L"Encountered unsupported resource (expecting a diReference).\r\n");
				CGUtil::appendString(m_bstrError, bstrError);
				return E_FAIL;	
			}//END IF

			hr = spxmlNodeTemp->get_text(pbstrResourceDII);
			if (pbstrResourceDII == NULL || hr != S_OK)
			{
				CComBSTR bstrError(L"Unable to extract the resource identifier uri from the resource supplied.\r\n");
				CGUtil::appendString(m_bstrError, bstrError);
				return E_FAIL;	
			}
		}
		else
		{			
			CComBSTR bstrError(L"Encountered unsupported resource (expecting a digitalResource or a diReference).\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			return E_INVALIDARG;

		}

		spEltTemp = NULL;
		spxmlNodeTemp = NULL;
		spInputResource = NULL;
	}
	if (bDigResFound == FALSE && bDiRefFound == FALSE)
	{
		CComBSTR bstrError(L"Encountered unsupported type or combination of resources (expecting a digitalResource and/or a diReference.).\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_INVALIDARG;
	}

	//
	// Load the licenseGroup string into an XMLDOMDocument
	//
		
    if(CGUtil::loadXML(bstrRELDoc, spRELDoc, bLoad)!=S_OK || bLoad == VARIANT_FALSE)
    {
		CComBSTR bstrError(L"Failed to create LicenseGroup DOM \r\n");
		spXMLError = NULL;
		if (spRELDoc == NULL)
		{
			CGUtil::appendString(m_bstrError, bstrError);
			return E_FAIL;
		}
	    hr = spRELDoc->get_parseError(&spXMLError);
		if(spXMLError != NULL)
		{
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrError);
			}//END IF
		}//END IF
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;
    }//END IF
	hr = spRELDoc->get_documentElement(ppRELLicenseGroup);
	if (hr != S_OK || *ppRELLicenseGroup == NULL)
	{		
		CComBSTR bstrError(L"Unable to load the license group\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;	
	}

	//--Check to see if the REL doc had an element and make sure it is an XrML2core licenseGroup
	CComBSTR bstrLicenseGroupBaseName, bstrLicenseGroupNSURI;
	hr = (*ppRELLicenseGroup)->get_baseName(&bstrLicenseGroupBaseName);
	if (hr == S_OK)
	{
		hr = (*ppRELLicenseGroup)->get_namespaceURI(&bstrLicenseGroupNSURI);
	}

	if (hr != S_OK)
	{
		CComBSTR bstrError(L"Unable to obtain the base name or the namespace uri of the license group\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;	
	}
    if(NULL == *ppRELLicenseGroup || 
	   CGUtil::compareBSTR(bstrLicenseGroupBaseName, LICENSE_GROUP) != 0 || 
	   CGUtil::compareBSTR(bstrLicenseGroupNSURI, NS_XRML_CORE) != 0)
	{
		CComBSTR bstrError(L"Encountered unsupported root element (expecting a licenseGroup).\r\n");		
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;	
	}//END IF*/

	return S_OK;
}

//------------------------------------------------------------------------------------------
//--FUNCTION GetErrorString
//------------------------------------------------------------------------------------------
//--This function returns the error string.  This will be called if there was an error 
//  (as indicated by the HRESULT returned).
//--Parameters:
//		CComBSTR rbstrError	->The buffer for the output error string
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::getErrorString(CComBSTR &rbstrError)
{
	rbstrError = m_bstrError;
	return S_OK;
}

//------------------------------------------------------------------------------------------
//--FUNCTION GetLogString
//------------------------------------------------------------------------------------------
//--This function returns the log string.  This can then be stored in the desired place.
//--Parameters:
//		CComBSTR rbstrRELDoc							->REL from the input license document
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::getLogString(CComBSTR &rbstrLog)
{
	rbstrLog = m_bstrLog;
	return S_OK;
}

//------------------------------------------------------------------------------------------
//--FUNCTION validateRequest
//------------------------------------------------------------------------------------------
//--This function takes in an REL license file, checks to see if there are any matching grants 
//  against the supplied query items (keyholder, right, and resource). It returns vectors of 
//  conditions for any conditions found in the matching grants, and vectors of issuers for the 
//  issuers of the matching grants.
//--Parameters:
//		BSTR bstrRELLicenseGroup			->REL from the input license document
//		BSTR bstrRELKeyHolder				->REL for the keyHolder(s) to search for
//		BSTR bstrRELRight					->REL for the right(s) to search for
//		CRELStringArray &rrelstaRELResource	->Array of REL for the resource(s) to search for.
//											  Please note that this array can have either a digitalResource
//											  or a diReference or one of each kind only.  Any other combination
//											  of resources is unsupported at the present.
//		CRELStringArray **pprelstaConditions	->Returns a pointer to a rel-string array of conditions. 
//		CRELStringArray **pprelstaIssuers		->Returns a pointer to a rel-string array of issuers 
//--The string arrays are initialized within the function ValidateRequest
//--The function returns the following HRESULT values:
//	S_OK	if at least one matching grant was found
//	S_FALSE if no matching grants were found
//	E_FAIL  if an error condition was encountered (an unsupported attribute for example)
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::validateRequest(BSTR bstrRELLicenseGroup, 
									  BSTR bstrRELKeyHolder, 
									  BSTR bstrRELRight, 
									  CRELStringArray &rrelstaRELResource, 
									  CRELStringArray** pprelstaConditions, 
									  CRELStringArray** pprelstaIssuers)
{
	USES_CONVERSION;

	CComPtr<IXMLDOMDocument> spRELDoc;			// For the REL Document
	CComBSTR			bstrRequestKeyHolderModulus;
	CComBSTR			bstrRequestKeyHolderExponent;
	CComBSTR			bstrRequestRightBaseName;
	CComBSTR			bstrRequestRightUri;
	CComBSTR			bstrRequestResourceLocationUri;
	CComBSTR			bstrCurrCondition;
	bool				bAtLeastOneMatch				= false;					// Used at the end to determine HRESULT return value
	HRESULT				hr								= S_OK;
	CComBSTR			bstrResourceDII;


	CComPtr<IXMLDOMElement> spRELLicenseGroup;				// For the licenseGroup
	CComPtr<IXMLDOMNodeList> splstLicenseNodes;				// Used to loop through the children of the licenseGroup
	CComPtr<IXMLDOMNodeList> splstLicenseNodeChildren;		// Used to loop through the children of the current license node
	CComPtr<IXMLDOMNode> spCurrLicNode = NULL;				// Temp for the current license node
	CComPtr<IXMLDOMNode> spCurrLicChildNode = NULL;			// Temp for the current license child node
	CComPtr<IXMLDOMNode> spKeyHolderNode = NULL;			// Will hold the keyHolder node from the grant we're searching
	CComPtr<IXMLDOMNode> spIssuerNode = NULL;				// Will hold the issuer node for the license that validates
	CComPtr<IXMLDOMNodeList> splstIssuerNodes;				// Used to loop through the issuers of a grant
	CComPtr<IXMLDOMNode> spCurrIssuer = NULL;				// Temp for the current issuer
	CComPtr<IXMLDOMNode> spXMLNodeTemp = NULL;				// Temp for node.

	*pprelstaConditions			= new CRELStringArray();	// Pointer to a vector of conditions we will be returning
	if (*pprelstaConditions == NULL)
	{
		CComBSTR bstrError(L"Out of memory\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}
	*pprelstaIssuers			= new CRELStringArray();	// Pointer to a vector of issuers we will be returning
	if (*pprelstaIssuers == NULL)
	{
		CComBSTR bstrError(L"Out of memory\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	//
	// Load the items we're querying the licenseGroup for into their respective DOM trees, or extract content some other way
	//
	hr = extractRequestItems(bstrRELLicenseGroup,bstrRELKeyHolder, bstrRELRight, 
		    rrelstaRELResource, &spRELLicenseGroup, 
			&bstrRequestKeyHolderModulus, &bstrRequestKeyHolderExponent,
			&bstrRequestRightBaseName, &bstrRequestRightUri, &bstrRequestResourceLocationUri,
			&bstrResourceDII);

    if(S_OK != hr)
	{
	  return hr;
	}//END IF

	//
	// Test the licenseGroup for various unsuported items
	//
	hr = attributesAreSupported(spRELLicenseGroup);
	if(S_OK != hr)
	{
	  return hr;
	}//END IF

	// 
	// Grab the licenses we will be working with out of the licenseGroup that was passed in to us
	//

	// Grab all the license nodes in the licenseGroup
	hr = spRELLicenseGroup->selectNodes(XPATH_ALL_LICENSES, &splstLicenseNodes);

	//Lets see if we have any licenses to look at.
	if(hr != S_OK)
	{
		return S_FALSE;
    }//END IF

	// Loop through all the licenses in the licenseGroup
	// We will exit upon success
	long nLicCount = 0;
	hr = splstLicenseNodes->get_length(&nLicCount);
	if (hr != S_OK)
	{
		return E_FAIL;
	}
	for (int nLicCounter = 0; nLicCounter < nLicCount; nLicCounter++)
	{
		CComBSTR bstrLog(L"ENTERING LICENSE... \r\n");
		CGUtil::appendString(m_bstrLog, bstrLog);

		spCurrLicNode =	NULL;
		hr = splstLicenseNodes->nextNode (&spCurrLicNode );
		if (hr != S_OK)
		{
			return hr;
		}

		// Grab all the children of the current license
		splstLicenseNodeChildren = NULL;
		hr = spCurrLicNode->get_childNodes(&splstLicenseNodeChildren);

		// If this license does not contain any children (i.e. grants) lets go to the next one.
		if(hr != S_OK)
		{
			continue;
		}//END IF

		// Grab all the issuers of this grant
		splstIssuerNodes = NULL;
		hr = spCurrLicNode->selectNodes (XPATH_LICENSE_ISSUERS, &splstIssuerNodes);

		long nLicNodeChildrenCount = 0;
		hr = splstLicenseNodeChildren->get_length(&nLicNodeChildrenCount);

		if (hr != S_OK || nLicNodeChildrenCount == 0)
		{
			continue;
		}

		for (int licChildCounter = 0; licChildCounter < nLicNodeChildrenCount; licChildCounter++)
		{
			spCurrLicChildNode = NULL;
			hr = splstLicenseNodeChildren->nextNode(&spCurrLicChildNode);

			CComBSTR bstrBaseName, bstrNSURI;
			hr = spCurrLicChildNode->get_baseName(&bstrBaseName);
			if (hr == S_OK)
			{
				hr = spCurrLicChildNode->get_namespaceURI(&bstrNSURI);
			}
			if (hr != S_OK)
			{
				continue;
			}

			// Lets check to see if this child (of the license) is an xrml2core grant.
			if (CGUtil::compareBSTR(GRANT, bstrBaseName) != 0 || 
				CGUtil::compareBSTR(NS_XRML_CORE, bstrNSURI) != 0)
			{
				// We only support grants whose parent is license so lets try the next one.
				continue;
			}//END IF

			// Ok, we found a grant node whose parent is a license node

			hr = isMatchingGrant(spCurrLicChildNode, bstrRequestKeyHolderModulus, 
						bstrRequestKeyHolderExponent, bstrRequestRightBaseName,
						bstrRequestRightUri, bstrRequestResourceLocationUri, bstrResourceDII, 
						bstrCurrCondition);

			if(S_OK == hr)
			{
				bstrLog = L"-->Found a match\r\n";
				CGUtil::appendString(m_bstrLog, bstrLog);

				//If there were no issuers in the license, lets push the condition onto the
				//condition vector and lets push an empty string in the issuer vector. 
				if(splstIssuerNodes == NULL)
				{
					// If there are no conditions either, there's nothing much to add to the vector.
					if (bstrCurrCondition.Length() != 0)
					{
						// Lets put a place holder for the issuer to keep in sync with the condition vector.
						if (hr == S_OK)
							hr = (*pprelstaIssuers)->addItem(L"");

						// Lets push in the condition for the current match.
						if (hr == S_OK)
							hr = (*pprelstaConditions)->addItem(bstrCurrCondition);

						if (hr != S_OK)
						{
							bstrLog = L"-->Out of memory\r\n";
							CGUtil::appendString(m_bstrLog, bstrLog);
							return hr;
						}
					}
				}
				else
				{
					long nIssuerCount = 0;
					hr = splstIssuerNodes->get_length(&nIssuerCount);
					if (hr != S_OK)
					{
						continue;
					}
					for (int issuerCounter = 0; issuerCounter < nIssuerCount; issuerCounter++)
					{
						spCurrIssuer = NULL;
						hr = splstIssuerNodes->nextNode (&spCurrIssuer);
						if (hr != S_OK || spCurrIssuer == NULL)
						{
							continue;
						}

						// Attach all the issuers to our issuer vector
						CComBSTR bstrTempXml;
						hr = spCurrIssuer->get_xml(&bstrTempXml);
						if (hr == S_OK)
						{
							if (hr == S_OK)
								hr = (*pprelstaIssuers)->addItem(bstrTempXml);

							// For each issuer, we need to associate a condition
							if (hr == S_OK)
								hr = (*pprelstaConditions)->addItem(bstrCurrCondition);

							if (hr != S_OK)
							{
								bstrLog = L"-->Out of memory\r\n";
								CGUtil::appendString(m_bstrLog, bstrLog);
								return hr;
							}
						}


						TCHAR tTemp[20];
						bstrLog = L"Issuer #";
						bstrLog += _itot(issuerCounter+1, tTemp, 10);
						bstrLog += L":\r\n";
						
						// Lets printout the issuer modulus
						CComBSTR bstrText = NULL;
						spXMLNodeTemp = NULL;
						hr = spCurrIssuer->selectSingleNode (XPATH_ISSUER_MODULUS, &spXMLNodeTemp);
						if (hr != S_OK || spXMLNodeTemp == NULL)
						{
							bstrLog.Append(L"           Modulus=[Missing modulus.]\r\n");
						}
						else
						{
							hr = spXMLNodeTemp->get_text(&bstrText);
							bstrLog.Append(L"           Modulus=[");
							bstrLog.AppendBSTR(bstrText);
							bstrLog.Append(L"]\r\n");
						}

						// Lets printout the issuer exponent.
						spXMLNodeTemp = NULL;
						hr = spCurrIssuer->selectSingleNode (XPATH_ISSUER_EXPONENT, &spXMLNodeTemp);
						if (hr != S_OK || spXMLNodeTemp == NULL)
						{
							bstrLog.Append(L"           Exponent=[Missing exponent.]\r\n");
						}
						else
						{
							hr = spXMLNodeTemp->get_text(&bstrText);
							bstrLog.Append(L"           Exponent=[");
							bstrLog.AppendBSTR(bstrText);
							bstrLog.Append(L"]\r\n");
						}
						CGUtil::appendString(m_bstrLog, bstrLog);
					}//END FOR LOOP
				}//END IF

				bAtLeastOneMatch = true;
			}//END IF

			// Reset the issuer iterator before going to the next grant(if we have issuers).
			if(splstIssuerNodes != NULL)
			{
				hr = splstIssuerNodes->reset();
			}//END IF
		}//END FOR LOOP (NEXT LICENSE CHILD)
	
		spCurrLicChildNode = NULL;
		splstLicenseNodeChildren = NULL;

	}//END FOR LOOP


	if (bAtLeastOneMatch)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;		
	}//END IF
	
}//END FUNCTION 

//------------------------------------------------------------------------------------------
//--FUNCTION isMatchingGrant
//------------------------------------------------------------------------------------------
//--This function is passed a grant DOM node and several items to check for; if all of them 
//  match within the grant, then the grant is considered a match. In addition, if a validityInterval
//  condition is found, it is returned.
//  The items to match against are a keyHolder modulus and exponent, a right, and a resource URI.
//--Parameters:
//		CComPtr<IXMLDOMNode>	spxmlNodeGrant	->Current DOM tree grant node we're checking
//		CComBSTR	bstrRequestKeyHolderModulus		->keyHolder modulus to check for
//		CComBSTR	bstrRequestKeyHolderExponent	->keyHolder exponent to check for
//		CComBSTR	bstrRequestRightBaseName		->right to check for
//		CComBSTR	bstrRequestRightUri				->right URI to check for
//		CComBSTR	bstrRequestResourceLocationUri	->resource URI to check for
//		CComBSTR	bstrRequestResourceDII			->resource identifier to check for
//		CComBSTR	&rbstrCurrCondition				->returns condition if one was found
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::isMatchingGrant(
						CComPtr<IXMLDOMNode>	spxmlNodeGrant, 
						CComBSTR			bstrRequestKeyHolderModulus, 
						CComBSTR			bstrRequestKeyHolderExponent,
						CComBSTR			bstrRequestRightBaseName,
						CComBSTR			bstrRequestRightUri,
						CComBSTR			bstrRequestResourceLocationUri,
						CComBSTR			bstrRequestResourceDII,
						CComBSTR			&rbstrCurrCondition
						)
{
	CComPtr<IXMLDOMNodeList>	splstGrantChildrenNodes;	// Used to loop through the children of the current grant node
	CComPtr<IXMLDOMNode>		spCurrGrantChildNode = NULL;		// Temp for the current grant child node
	CComPtr<IXMLDOMNode>		spDSIGModulusNode = NULL;			// Will hold the dsig:modulus node from the grant we're searching
	CComPtr<IXMLDOMNode>		spDSIGExponentNode = NULL;		// Will hold the dsig:exponent node from the grant we're searching
	CComPtr<IXMLDOMNode>		spResourceURINode = NULL;			// Will hold the URI of the digitalResource/nonSecureIndirect node
	CComPtr<IXMLDOMNode>		spResourceDIINode = NULL;			// Will hold the DII of the digitalResource/nonSecureIndirect node
	bool						bKeyHolderMatch = false;					// Used inside each grant to track keyHolder match
	bool						bRightMatch = false;						// Used inside each grant to track right match
	bool						bResourceMatch = false;						// Used inside each grant to track resource match
	HRESULT						hr = E_FAIL;

	// Lets make sure that we got a valid pointer.
	if(spxmlNodeGrant == NULL)
	{
		return E_INVALIDARG;
	}//END IF

	// Grab all the children of the current grant node
	CComBSTR bstrLog(L"ENTERING grant\r\n");
	CGUtil::appendString(m_bstrLog, bstrLog);
	hr = spxmlNodeGrant->get_childNodes(&splstGrantChildrenNodes);

	// Lets check to see if this grant is empty (if the license was validated this would have been tested).
	if (hr != S_OK) 
	{
		// Empty grant: This is not valid so we'll just return false.
		return S_FALSE;
	}//END IF

	long nGrantChildrenCount = 0;
	int nGrantEltChildCounter = -1;
	hr = splstGrantChildrenNodes->get_length(&nGrantChildrenCount);
	for (int nGrantChildCounter = 0; nGrantChildCounter < nGrantChildrenCount; nGrantChildCounter++)
	{
		spCurrGrantChildNode = NULL;
		hr = splstGrantChildrenNodes->nextNode (&spCurrGrantChildNode);
		if (hr != S_OK)
			continue;

		DOMNodeType nodeType;
		hr = spCurrGrantChildNode->get_nodeType(&nodeType);
		if (hr != S_OK || nodeType != NODE_ELEMENT)
		{
			continue;
		}
		nGrantEltChildCounter++;

		// Test the children of the grant
		CComBSTR bstrGrantChildName, bstrGrantChildUri;
		hr = spCurrGrantChildNode->get_baseName(&bstrGrantChildName);
		if (hr == S_OK)
		{
			hr = spCurrGrantChildNode->get_namespaceURI(&bstrGrantChildUri);
		}
		if (hr != S_OK)
		{
			return S_FALSE;
		}

		if (CGUtil::compareBSTR(KEY_HOLDER, bstrGrantChildName) == 0 && CGUtil::compareBSTR(NS_XRML_CORE, bstrGrantChildUri) == 0)
		{
			// Since we have a keyholder lets get the modulus and the exponent
			spDSIGModulusNode = NULL;
			spDSIGExponentNode = NULL;
			hr = spCurrGrantChildNode->selectSingleNode(XPATH_KEY_HOLDER_MODULUS, &spDSIGModulusNode);
			if (hr == S_OK)
			{
				hr = spCurrGrantChildNode->selectSingleNode(XPATH_KEY_HOLDER_EXPONENT, &spDSIGExponentNode);
			}
			if (hr != S_OK || spDSIGModulusNode == NULL || spDSIGExponentNode == NULL)
			{
				continue;
			}


			// Lets see if the keyHolder had the modulus and exponent and
			// that they matched those of the request keyHolder.
			CComBSTR bstrModulus, bstrExponent;
			hr = spDSIGModulusNode->get_text(&bstrModulus);
			if (hr == S_OK)
			{
				hr = spDSIGExponentNode->get_text(&bstrExponent);
			}
			if (hr == S_OK && CGUtil::compareBSTR(bstrRequestKeyHolderModulus, bstrModulus) == 0 &&
				CGUtil::compareBSTR(bstrRequestKeyHolderExponent, bstrExponent) == 0 ) 
			{
				bKeyHolderMatch = true;
				bstrLog = L"-->keyholder match\r\n";
				CGUtil::appendString(m_bstrLog, bstrLog);
			}
			else
			{
				bKeyHolderMatch = false;
				bstrLog = L"-->NO keyholder match\r\n";
				CGUtil::appendString(m_bstrLog, bstrLog);
			}//END IF

		}
		else if (CGUtil::compareBSTR(bstrGrantChildName, bstrRequestRightBaseName) == 0 
			&& CGUtil::compareBSTR(bstrGrantChildUri, bstrRequestRightUri) == 0)
		{
			if (nGrantEltChildCounter == 0)
			{
				// if the right was the first child, then there was no keyHolder, so grant is for all
				bKeyHolderMatch = true;
				bstrLog = L"-->keyholder match\r\n";
				CGUtil::appendString(m_bstrLog, bstrLog);
			}//END IF

			// We have a right
			bRightMatch = true;
			bstrLog = L"-->right match\r\n";
			CGUtil::appendString(m_bstrLog, bstrLog);
		}
		else if (CGUtil::compareBSTR(DIGITAL_RESOURCE, bstrGrantChildName) == 0 
			&& CGUtil::compareBSTR(NS_XRML_CORE, bstrGrantChildUri) == 0)
		{
			// We have a resource
			spResourceURINode = NULL;
			hr = spCurrGrantChildNode->selectSingleNode(XPATH_RESOURCE_URI, &spResourceURINode);

			//If no URI was specified we do not have a match.
			if(spResourceURINode != NULL && hr == S_OK)
			{
				CComBSTR bstrResURI;
				hr = spResourceURINode->get_text(&bstrResURI);
				if(CGUtil::compareBSTR(bstrResURI, bstrRequestResourceLocationUri) == 0 && hr == S_OK)
				{
					bResourceMatch = true;
					bstrLog = L"-->resource match\r\n";
					CGUtil::appendString(m_bstrLog, bstrLog);
				}
				else
				{
					bResourceMatch = false;
					bstrLog = L"-->NO resource match\r\n";
					CGUtil::appendString(m_bstrLog, bstrLog);
				}//END IF
			}//END IF

		}
		else if (CGUtil::compareBSTR(DI_REFERENCE, bstrGrantChildName) == 0 
			&& CGUtil::compareBSTR(NS_MX, bstrGrantChildUri) == 0)
		{
			// We have a resource
			spResourceDIINode = NULL;
			hr = spCurrGrantChildNode->selectSingleNode(XPATH_RESOURCE_DII, &spResourceDIINode);

			//If no URI was specified we do not have a match.
			if(spResourceDIINode != NULL && hr == S_OK)
			{
				CComBSTR bstrResDII;
				hr = spResourceDIINode->get_text(&bstrResDII);
				if(CGUtil::compareBSTR(bstrResDII, bstrRequestResourceDII) == 0 && hr == S_OK)
				{
					bResourceMatch = true;
					bstrLog = L"-->resource match\r\n";
					CGUtil::appendString(m_bstrLog, bstrLog);
				}
				else
				{
					bResourceMatch = false;
					bstrLog = L"-->NO resource match\r\n";
					CGUtil::appendString(m_bstrLog, bstrLog);
				}//END IF
			}//END IF

		}
		else if (CGUtil::compareBSTR(VALIDITY_INTERVAL, bstrGrantChildName) == 0 
			&& CGUtil::compareBSTR(NS_XRML_CORE, bstrGrantChildUri) == 0)
		{
			// We have a time condition, we want to return this
			bstrLog = L"-->we got a condition\r\n";
			CGUtil::appendString(m_bstrLog, bstrLog);

			hr = spCurrGrantChildNode->get_xml(&rbstrCurrCondition);
		}
		else if (CGUtil::compareBSTR(EXERCISE_LIMIT, bstrGrantChildName) == 0 
			&& CGUtil::compareBSTR(NS_XRML_SX, bstrGrantChildUri) == 0)
		{
			// We have a time condition, we want to return this
			bstrLog = L"-->we got a condition\r\n";
			CGUtil::appendString(m_bstrLog, bstrLog);

			hr = spCurrGrantChildNode->get_xml(&rbstrCurrCondition);
		}
		else if (CGUtil::compareBSTR(ALL_CONDITIONS, bstrGrantChildName) == 0 
			&& CGUtil::compareBSTR(NS_XRML_CORE, bstrGrantChildUri) == 0)
		{
			// We have a time condition, we want to return this
			bstrLog = L"-->we got a condition\r\n";
			CGUtil::appendString(m_bstrLog, bstrLog);

			hr = spCurrGrantChildNode->get_xml(&rbstrCurrCondition);
		}
		else
		{
			// We ran into an element that we are not aware of.
			CComBSTR bstrNodeName;
			hr = spCurrGrantChildNode->get_nodeName(&bstrNodeName);
			bstrLog = L"-->Encountered an unsupported element [";
			bstrLog.AppendBSTR(bstrNodeName);
			bstrLog.Append(L"]. Skipping this grant.\r\n");
			CGUtil::appendString(m_bstrLog, bstrLog);
			return E_FAIL;		
		}//END IF

	}//END FOR LOOP (NEXT GRANT CHILD)

		// Once we've met all our checks & examined all children of the grant node, grab the issuer
	return ((bKeyHolderMatch && bRightMatch && bResourceMatch) ? S_OK : S_FALSE);

}//END FUNCTION isMatchingGrant

//------------------------------------------------------------------------------------------
//--FUNCTION validateELCondition
//------------------------------------------------------------------------------------------
//--This function checks to see if the user can exercise the right for the intended usage count
//  indicated by the 'nExerciseCount' variable.  This function contacts the local service to
//  verify this.  The license id passed in is used as the condition id for now.
//  It checks to see if the condition has been met.
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::validateELCondition(CComPtr<IXMLDOMElement> spELConditionElt, int nExerciseCount, bool bUpdate)
{
	USES_CONVERSION;
	CComPtr<IXMLDOMNode> spXMLNode;
	CComBSTR bstrServiceURI;
	CComBSTR bstrWsdlURI;
	CComBSTR bstrBinding;

	// Check the parameters and extract the service uri from the license
	HRESULT hr = spELConditionElt->selectSingleNode(XPATH_EX_LIMIT_WSDL_URI, &spXMLNode);
	if (hr == S_OK)
		hr = spXMLNode->get_text(&bstrWsdlURI);

	if (hr != S_OK || bstrWsdlURI.Length() == 0)
	{
		CComBSTR bstrError(L"Invalid input condition.  Missing wsdl URI.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}
	if (CGUtil::compareBSTR(bstrWsdlURI, EX_LIMIT_WSDL_URI))
	{
		CComBSTR bstrError(L"Unsupported ExerciseLimit condition.  WsdlURI mismatch.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	spXMLNode = NULL;
	hr = spELConditionElt->selectSingleNode(XPATH_EX_LIMIT_BINDING, &spXMLNode);
	if (hr == S_OK)
		hr = spXMLNode->get_text(&bstrBinding);

	if (hr != S_OK || bstrBinding.Length() == 0)
	{
		CComBSTR bstrError(L"Invalid input condition.  Missing binding information.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}
	if (CGUtil::compareBSTR(bstrBinding, EX_LIMIT_BINDING))
	{
		CComBSTR bstrError(L"Unsupported ExerciseLimit condition.  Binding mismatch.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	spXMLNode = NULL;
	hr = spELConditionElt->selectSingleNode(XPATH_EX_LIMIT_SERVICE_URI, &spXMLNode);
	if (hr == S_OK)
		hr = spXMLNode->get_text(&bstrServiceURI);

	if (hr != S_OK || bstrServiceURI.Length() == 0)
	{
		CComBSTR bstrError(L"Invalid input condition.  Missing Service URI.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	// Trim the uri and call the service for the count
	TCHAR *tszServiceURI = OLE2T(bstrServiceURI);
	if (tszServiceURI == NULL)
	{
		CComBSTR bstrError(L"System Error.  Unable to convert a BSTR to a TCHAR.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}
	TCHAR *tszServicePath = _tcsstr(tszServiceURI, _T("///"));
	TCHAR *tszStateInfo = _tcsstr(tszServicePath, _T("?"));
	if (tszServicePath == NULL || tszStateInfo == NULL)
	{
		CComBSTR bstrError(L"Invalid Service URI format.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}
	tszServicePath += 3;  // To skip the "///"
	*tszStateInfo = _T('\0');
	TCHAR *tszId = _tcsstr(tszStateInfo+1, _T("="));
	if (tszId == NULL)
	{
		CComBSTR bstrError(L"Invalid Service URI format.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}
	*tszId = _T('\0');
	BSTR bstrConditionId = T2BSTR(tszId+1);
	if (bstrConditionId == NULL || _tcscmp(tszStateInfo+1, STATE_ID) != 0)
	{
		CComBSTR bstrError(L"Invalid service uri.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	hr = accessExLimitService(tszServicePath, bstrConditionId, nExerciseCount, bUpdate);
	::SysFreeString(bstrConditionId);

	// Compare the remaining count with the exercise count and return the status to the user
	return hr;
}


//------------------------------------------------------------------------------------------
//--FUNCTION validateVICondition
//------------------------------------------------------------------------------------------
//--This function is passed in a string containing an REL validityInterval condition (wstrCondition), 
//  and a string containing an ISO date time (wstrReferenceTime) to check against the condition.
//  It checks to see if the condition has been met.
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::validateVICondition(CComPtr<IXMLDOMElement> spValidityIntervalElt, 
										  BSTR bstrReferenceTime)
{
	LONG				nErrorCode = E_FAIL;						// For error codes
	HRESULT				hr = S_OK;
	double				dCompareResult;

	CComPtr<IXMLDOMNode> spNotBeforeNode	= NULL;			// Will hold the validityInterval/notBefore node
	CComPtr<IXMLDOMNode> spNotAfterNode	= NULL;			// Will hold the validityInterval/notAfter node
	hr = spValidityIntervalElt->selectSingleNode (XPATH_VI_NOT_BEFORE, &spNotBeforeNode);
	// Check the notBefore condition is it exists
	if (hr == S_OK && spNotBeforeNode != NULL)
	{
		// True if first parameter >= second parameter

		// See if wstrReferenceTime >= notBeforeTime
		CComBSTR bstrText;
		hr = spNotBeforeNode->get_text(&bstrText);
		if (hr != S_OK)
		{
			return S_FALSE;
		}
		hr = CGUtil::compareTime(bstrReferenceTime, bstrText, &dCompareResult);
		
		// Check to see if we were able to compare (The time format could have been wrong.)
		if (S_OK != hr)
		{
			CComBSTR bstrError(L"Invalid time format.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			return hr;
		}//END IF

		if (dCompareResult < 0.0)
		{
			return S_FALSE;
		}//END IF

	}//END IF
	
	// Check the notAfter condition if it exists
	hr = spValidityIntervalElt->selectSingleNode (XPATH_VI_NOT_AFTER, &spNotAfterNode);
	if (hr == S_OK && spNotAfterNode != NULL)
	{
		// True if first parameter >= second parameter
		CComBSTR bstrText;
		hr = spNotAfterNode->get_text(&bstrText);
		if (hr != S_OK)
		{
			return S_FALSE;
		}
		hr = CGUtil::compareTime(bstrReferenceTime, bstrText, &dCompareResult);

		// Check to see if we were able to compare (The time format could have been wrong.)
		if (S_OK != hr)
		{
			CComBSTR bstrError(L"Invalid time format.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			return hr;
		}//END IF

		if (dCompareResult > 0.0)
		{
			return S_FALSE;
		}//END IF
	}//END IF
	

	if (FAILED(hr))
	{
		return hr;
	}

	// If we got here, we either had no time constraints, or the ones that existed passed OK.
	return S_OK;
}//END FUNCTION validateVICondition

//------------------------------------------------------------------------------------------
//--FUNCTION validateCondition
//------------------------------------------------------------------------------------------
//--This function is passed in a string containing an REL condition (bstrCondition), 
//  a string containing an ISO date time (bstrReferenceTime) to check against the condition 
//  and an exercise count indicating the intended usage count for the right.  Please note
//  the condition passed in could either be a validityInterval, an exerciseLimit and an
//  allConditions that contains a combination of these conditions.
//  It checks to see if the condition has been met.
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::validateCondition(BSTR bstrCondition, BSTR bstrReferenceTime, int nExerciseCount,
										bool bUpdate)
{
	CComPtr<IXMLDOMDocument> spCondition;
	CComPtr<IXMLDOMNode> spAtomicCondNode;  // This will be used to denote each condition in allConditions
	CComPtr<IXMLDOMParseError>  spXMLError;	// For XML errors
	CComPtr<IXMLDOMElement> spCondElt;  // The root element of the input condition
	HRESULT hr = S_OK;
	LONG nErrorCode = E_FAIL;	// For error codes

	VARIANT_BOOL bLoad = VARIANT_FALSE;
	CComBSTR bstrTemp(bstrCondition);
	if (bstrTemp.Length() == 0)
	{
		return S_OK;
	}
	bstrTemp = L"";
    if(CGUtil::loadXML (bstrCondition, spCondition, bLoad) != S_OK || bLoad == VARIANT_FALSE)
    {
		CComBSTR bstrError(L"Failed to create condition DOM \r\n");
		if (spCondition == NULL)
		{
			CGUtil::appendString(m_bstrError, bstrError);
			return E_FAIL;
		}
	    hr = spCondition->get_parseError(&spXMLError);
		if(spXMLError != NULL)
		{
			hr = spXMLError->get_errorCode(&nErrorCode);
			if (nErrorCode != 0)
			{
				hr = CGUtil::ReportError(spXMLError, bstrError);
			}//END IF
		}//END IF
		CGUtil::appendString(m_bstrError, bstrError);
	    return E_FAIL;
    }//END IF

	hr = spCondition->get_documentElement(&spCondElt);
	if (hr != S_OK || spCondElt == NULL)
	{
		CComBSTR bstrError(L"Unable to extract the document element from the condition DOM \r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}
	return validateConditionHelper(spCondElt, bstrReferenceTime, nExerciseCount, bUpdate);
}

//------------------------------------------------------------------------------------------
//--FUNCTION validateConditionHelper
//------------------------------------------------------------------------------------------
//--This function is passed in a DOM element containing an REL condition (spCondElt), 
//  a string containing an ISO date time (bstrReferenceTime) to check against the condition 
//  and an exercise count indicating the intended usage count for the right.  Please note
//  the condition passed in could either be a validityInterval, an exerciseLimit and an
//  allConditions that contains a combination of these conditions.
//  It checks to see if the condition(s) have been met.
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::validateConditionHelper(CComPtr<IXMLDOMElement> spCondElt, BSTR bstrReferenceTime, 
											  int nExerciseCount, bool bUpdate)
{
	CComPtr<IXMLDOMNodeList> spCondNodeList; // For the list of conditions in allConditions
	CComPtr<IXMLDOMParseError>  spXMLError;	// For XML errors
	CComBSTR bstrCondName, bstrCondURI;
	CComPtr<IXMLDOMElement> spAtomicCondElt;
	CComPtr<IXMLDOMNode> spAtomicCondNode;


	HRESULT hr = spCondElt->get_baseName(&bstrCondName);
	if (hr == S_OK)
	{
		hr = spCondElt->get_namespaceURI(&bstrCondURI);
	}

	// Lets make sure we were given either an xrml2core:validityInterval or 
	// an xrml2sx:exerciseLimit or an xrml2core:allConditions
	if(	hr != S_OK)
	{
		CComBSTR bstrError(L"Unable to extract the base name or the namespace uri of the condition.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}//END IF

	if (CGUtil::compareBSTR(bstrCondName, VALIDITY_INTERVAL) == 0 &&
		CGUtil::compareBSTR(NS_XRML_CORE, bstrCondURI) == 0)
	{
		CComBSTR bstrLog(L"Encountered a validityInterval.  Validating...\r\n");
		CGUtil::appendString(m_bstrLog, bstrLog);
		return validateVICondition(spCondElt, bstrReferenceTime);
	}//END IF
	else if (CGUtil::compareBSTR(bstrCondName, EXERCISE_LIMIT) == 0 &&
		CGUtil::compareBSTR(NS_XRML_SX, bstrCondURI) == 0)
	{
		CComBSTR bstrLog(L"Encountered an exerciseLimit.  Validating...\r\n");
		CGUtil::appendString(m_bstrLog, bstrLog);
		return validateELCondition(spCondElt, nExerciseCount, bUpdate);
	}//END IF
	else if (CGUtil::compareBSTR(bstrCondName, ALL_CONDITIONS) != 0 ||
		CGUtil::compareBSTR(NS_XRML_CORE, bstrCondURI) != 0)
	{
		CComBSTR bstrError(L"Encountered unsupported condition (expecting a validityInterval or an exerciseLimit or an allConditions).\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}//END IF

	// We have an allConditions
	hr = spCondElt->selectNodes(XPATH_ALL_CHILDREN, &spCondNodeList);
	if (!SUCCEEDED(hr))
	{
		CComBSTR bstrError(L"Unable to query the condition DOM.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	if (spCondNodeList == NULL)
	{
		return S_OK;
	}

	long lNoConditions;
	hr = spCondNodeList->get_length(&lNoConditions);
	if (hr != S_OK)
	{
		CComBSTR bstrError(L"Unable to parse the conditions returned.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	for (long lIdx = 0; lIdx < lNoConditions; lIdx++)
	{
		spAtomicCondNode = NULL;
		hr = spCondNodeList->nextNode(&spAtomicCondNode);
		if (FAILED(hr))
		{
			CComBSTR bstrError(L"Unable to parse the condition returned.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			return E_FAIL;
		}

		if (spAtomicCondNode == NULL)
		{
			continue;
		}

		// Ignore all the children nodes that are not elements
		DOMNodeType nodeType;
		hr = spAtomicCondNode->get_nodeType(&nodeType);
		if (hr != S_OK)
		{
			CComBSTR bstrError(L"Unable to extract the node type of the condition.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			return E_FAIL;
		}
		else if (nodeType != NODE_ELEMENT)
		{
			continue;
		}
		spAtomicCondElt = NULL;
		hr = spAtomicCondNode->QueryInterface(__uuidof(IXMLDOMElement), reinterpret_cast<void**>(&spAtomicCondElt));
		if (hr == S_OK)
		{
			hr = validateConditionHelper(spAtomicCondElt, bstrReferenceTime, nExerciseCount, bUpdate);
		}
		if (hr != S_OK)
		{
			return hr;
		}
	}
	return S_OK;
}

//------------------------------------------------------------------------------------------
//--FUNCTION accessExLimitService
//------------------------------------------------------------------------------------------
//--This function accesses the exercise limit service and, depending on the input parameter
//  bUpdate, either reads in the remaining count from the service or updates the remaining
//  count in the local state reference file.  In the case it reads in the remaining count, 
//  it determines if the exercise count input variable is less than or equal to the remaining
//  count to indicate the sucessful validation of the condition.
//------------------------------------------------------------------------------------------
HRESULT CRELLicAuthz::accessExLimitService(TCHAR *tszPath, BSTR bstrConditionId, int nExerciseCount, bool bUpdate)
{
	USES_CONVERSION;
	if (tszPath == NULL || _tcslen(tszPath) == 0)
	{
		return S_FALSE;
	}
	HMODULE hDllService = ::LoadLibrary(tszPath);
	if (hDllService == NULL)
	{
		CComBSTR bstrError(L"Unable to load the local exercise limit service.  Please try a different license\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		return E_FAIL;
	}

	READFN readfptr;
	UPDATEFN updatefptr;

	if (bUpdate)
	{
		updatefptr = (UPDATEFN) GetProcAddress(hDllService, _T("update"));
		if (updatefptr ==	NULL)
		{
			CComBSTR bstrError(L"Unable to get the function pointers from the service.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			::FreeLibrary(hDllService);
			return E_FAIL;
		}
	}
	else
	{
		readfptr = (READFN) GetProcAddress(hDllService, _T("read"));
		if (readfptr ==	NULL)
		{
			CComBSTR bstrError(L"Unable to get the function pointers from the service.\r\n");
			CGUtil::appendString(m_bstrError, bstrError);
			::FreeLibrary(hDllService);
			return E_FAIL;
		}
	}


	TCHAR *tszConditionId = OLE2T(bstrConditionId);
	if (tszConditionId == NULL)
	{
		CComBSTR bstrError(L"Unable to get the function pointers from the service.\r\n");
		CGUtil::appendString(m_bstrError, bstrError);
		::FreeLibrary(hDllService);
		return E_FAIL;
	}

	HRESULT hr = S_OK;
	int nRemainingCount = 0;
	if (bUpdate)
	{
		hr = (*updatefptr)(tszConditionId, nExerciseCount);
	}
	else
	{
		int nRemainingCount = (*readfptr)(tszConditionId);
		hr = ((nRemainingCount >= nExerciseCount)? S_OK: S_FALSE);
	}
	::FreeLibrary(hDllService);

	return hr;
}

