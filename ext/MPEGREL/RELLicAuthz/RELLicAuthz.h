#ifndef GUARD_RELLICENSEAUTHORIZATION_h
#define GUARD_RELLICENSEAUTHORIZATION_h

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

#ifdef RELLICAUTHZ_EXPORTS
#define RELLICAUTHZ_API __declspec(dllexport)
#else
#define RELLICAUTHZ_API __declspec(dllimport)
#endif

class CRELStringArray;

using namespace MSXML;

const CComBSTR LICENSE_GROUP(L"licenseGroup");
const CComBSTR KEY_HOLDER(L"keyHolder");
const CComBSTR DIGITAL_RESOURCE(L"digitalResource");
const CComBSTR DI_REFERENCE(L"diReference");
const CComBSTR VALIDITY_INTERVAL(L"validityInterval");
const CComBSTR EXERCISE_LIMIT(L"exerciseLimit");
const CComBSTR ALL_CONDITIONS(L"allConditions");
const CComBSTR GRANT(L"grant");
const CComBSTR ISSUER(L"issuer");
const CComBSTR PLAY(L"play");
const CComBSTR LICENSE_PART_ID_REF(L"licensePartIdRef");
const CComBSTR VAR_REF(L"varRef");
const CComBSTR XSI_TYPE(L"xsi:type");
const CComBSTR NO_LICENSE_ID(L"RELNOLICIDSUPPLIED");
const CComBSTR EX_LIMIT_WSDL_URI(L"http://www.contentguard.com/schema/2003/05/cgwsdl.xml");
const CComBSTR EX_LIMIT_BINDING(L"cgwsdl:dllBinding");

// XPATH expressions used in the program
#ifdef _WINDOWS
const CComBSTR	XPATH_ALL_CHILDREN(L"child::*");
const CComBSTR	XPATH_RESOURCE_URI(L"self::*[local-name()=\"digitalResource\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/child::*[local-name()=\"nonSecureIndirect\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/@URI");
const CComBSTR	XPATH_RESOURCE_DII(L"self::*[local-name()=\"diReference\"][namespace-uri()=\"urn:mpeg:mpeg21:2002:01-REL-NS\"]/child::*[local-name()=\"identifier\"][namespace-uri()=\"urn:mpeg:mpeg21:2002:01-REL-NS\"]");
const CComBSTR	XPATH_ALL_ATTRIBUTES(L"descendant-or-self::*/attribute::*");
const CComBSTR	XPATH_ALL_LICENSES(L"child::*[local-name()=\"license\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]");
const CComBSTR	XPATH_KEY_HOLDER_MODULUS(L"child::*[local-name()=\"info\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/child::*[local-name()=\"KeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"RSAKeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"Modulus\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]");
const CComBSTR	XPATH_KEY_HOLDER_EXPONENT(L"child::*[local-name()=\"info\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/child::*[local-name()=\"KeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"RSAKeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"Exponent\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]");
const CComBSTR	XPATH_LICENSE_ISSUERS(L"child::*[local-name()=\"issuer\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]");
const CComBSTR	XPATH_VI_NOT_AFTER(L"child::*[local-name()=\"notAfter\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]");
const CComBSTR	XPATH_VI_NOT_BEFORE(L"child::*[local-name()=\"notBefore\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]");
const CComBSTR	XPATH_ISSUER_MODULUS(L"self::*[local-name()=\"issuer\"]/child::*[local-name()=\"Signature\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"KeyInfo\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"KeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"RSAKeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"Modulus\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]");
const CComBSTR	XPATH_ISSUER_EXPONENT(L"self::*[local-name()=\"issuer\"]/child::*[local-name()=\"Signature\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"KeyInfo\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"KeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"RSAKeyValue\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]/child::*[local-name()=\"Exponent\"][namespace-uri()=\"http://www.w3.org/2000/09/xmldsig#\"]");
const CComBSTR  XPATH_EX_LIMIT_WSDL_URI(L"self::*[local-name()=\"exerciseLimit\"]/child::*[local-name()=\"serviceReference\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/child::*[local-name()=\"wsdlAddress\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]/child::*[local-name()=\"kind\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]/child::*[local-name()=\"wsdl\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]/child::*[local-name()=\"nonSecureIndirect\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/@URI");
const CComBSTR  XPATH_EX_LIMIT_BINDING(L"self::*[local-name()=\"exerciseLimit\"]/child::*[local-name()=\"serviceReference\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/child::*[local-name()=\"wsdlAddress\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]/child::*[local-name()=\"kind\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]/child::*[local-name()=\"binding\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]");
const CComBSTR  XPATH_EX_LIMIT_SERVICE_URI(L"self::*[local-name()=\"exerciseLimit\"]/child::*[local-name()=\"serviceReference\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/child::*[local-name()=\"wsdlAddress\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]/child::*[local-name()=\"address\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2sx\"]/child::*[local-name()=\"digitalResource\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/child::*[local-name()=\"nonSecureIndirect\"][namespace-uri()=\"http://www.xrml.org/schema/2002/05/xrml2core\"]/@URI");

#else
const CComBSTR	XPATH_ALL_CHILDREN(L"*");
const CComBSTR	XPATH_RESOURCE_URI(L"nonSecureIndirect/@URI");
const CComBSTR	XPATH_RESOURCE_DII(L"mx:identifier");
const CComBSTR	XPATH_ALL_ATTRIBUTES(L"//@*");
const CComBSTR	XPATH_ALL_LICENSES(L"license");
const CComBSTR	XPATH_KEY_HOLDER_MODULUS(L"info/dsig:KeyValue/dsig:RSAKeyValue/dsig:Modulus");
const CComBSTR	XPATH_KEY_HOLDER_EXPONENT(L"info/dsig:KeyValue/dsig:RSAKeyValue/dsig:Exponent");
const CComBSTR	XPATH_LICENSE_ISSUERS(L"issuer");
const CComBSTR	XPATH_VI_NOT_AFTER(L"notAfter");
const CComBSTR	XPATH_VI_NOT_BEFORE(L"notBefore");
const CComBSTR	XPATH_ISSUER_MODULUS(L"dsig:Signature/dsig:KeyInfo/dsig:KeyValue/dsig:RSAKeyValue/dsig:Modulus");
const CComBSTR	XPATH_ISSUER_EXPONENT(L"dsig:Signature/dsig:KeyInfo/dsig:KeyValue/dsig:RSAKeyValue/dsig:Exponent");
const CComBSTR  XPATH_EX_LIMIT_WSDL_URI(L"serviceReference/sx:wsdlAddress/sx:kind/sx:wsdl/nonSecureIndirect/@URI");
const CComBSTR  XPATH_EX_LIMIT_BINDING(L"serviceReference/sx:wsdlAddress/sx:kind/sx:binding");
const CComBSTR  XPATH_EX_LIMIT_SERVICE_URI(L"serviceReference/sx:wsdlAddress/sx:address/digitalResource/nonSecureIndirect/@URI");
#endif

// This class is exported from the RELLicenseAuthorization.dll
class RELLICAUTHZ_API CRELLicAuthz {
public:
	static const BSTR NS_XRML_CORE;
	static const BSTR NS_XRML_SX;
	static const BSTR NS_MX;
	static const BSTR NS_DSIG;
	static const BSTR NS_XSI;

	CRELLicAuthz(void);
	virtual ~CRELLicAuthz(void);

	//------------------------------------------------------------------------------------------
	//--FUNCTION GetErrorString
	//------------------------------------------------------------------------------------------
	//--This function returns the error string.  This will be called if there was an error 
	//  (as indicated by the HRESULT returned).
	//--Parameters:
	//		CComBSTR rbstrError	->The buffer for the output error string
	//------------------------------------------------------------------------------------------
	HRESULT getErrorString(CComBSTR &rbstrError);

	//------------------------------------------------------------------------------------------
	//--FUNCTION GetLogString
	//------------------------------------------------------------------------------------------
	//--This function returns the log string.  This can then be stored in the desired place.
	//--Parameters:
	//		CComBSTR rbstrRELDoc							->REL from the input license document
	//------------------------------------------------------------------------------------------
	HRESULT getLogString(CComBSTR &rbstrLog);

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
										  CRELStringArray** pprelstaIssuers);

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
	HRESULT validateCondition(BSTR bstrCondition, BSTR bstrReferenceTime, int nExerciseCount, bool bUpdate);


protected:
	HRESULT attributesAreSupported(CComPtr<IXMLDOMElement> spxmlNode);

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
	//		BSTR *pbstrResourceDII					->returns resource ID extracted from pbstrRELResource
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
				BSTR *pbstrResourceDII);

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
							);


	//------------------------------------------------------------------------------------------
	//--FUNCTION validateELCondition
	//------------------------------------------------------------------------------------------
	//--This function checks to see if the user can exercise the right for the intended usage count
	//  indicated by the 'nExerciseCount' variable.  This function contacts the local service to
	//  verify this.
	//  It checks to see if the condition has been met.
	//------------------------------------------------------------------------------------------
	HRESULT validateELCondition(CComPtr<IXMLDOMElement> spELConditionElt, int nExerciseCount, bool bUpdate);


	//------------------------------------------------------------------------------------------
	//--FUNCTION validateVICondition
	//------------------------------------------------------------------------------------------
	//--This function is passed in a string containing an REL validityInterval condition (wstrCondition), 
	//  and a string containing an ISO date time (wstrReferenceTime) to check against the condition.
	//  It checks to see if the condition has been met.
	//------------------------------------------------------------------------------------------
	HRESULT validateVICondition(CComPtr<IXMLDOMElement> spValidityIntervalElt, BSTR bstrReferenceTime);

	//------------------------------------------------------------------------------------------
	//--FUNCTION accessExLimitService
	//------------------------------------------------------------------------------------------
	//--This function accesses the exercise limit service and, depending on the input parameter
	//  bUpdate, either reads in the remaining count from the service or updates the remaining
	//  count in the local state reference file.  In the case it reads in the remaining count, 
	//  it determines if the exercise count input variable is less than or equal to the remaining
	//  count to indicate the sucessful validation of the condition.
	//------------------------------------------------------------------------------------------
	HRESULT accessExLimitService(TCHAR *tszPath, BSTR bstrConditionId, int nExerciseCount, bool bUpdate);

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
	HRESULT CRELLicAuthz::validateConditionHelper(CComPtr<IXMLDOMElement> spCondElt, BSTR bstrReferenceTime, int nExerciseCount, bool bUpdate);


private:
	BSTR m_bstrError;
	BSTR m_bstrLog;
};

#endif // GUARD_RELLICENSEAUTHORIZATION_h

