// RELExLimitService.cpp : Defines the entry point for the DLL application.
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

#include "stdafx.h"
#include "RELExLimitService.h"

#include <stdio.h>


#define EXSERVICE_FAIL -100
#define EXSERVICE_FALSE -1

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

CRELExLimitService CRELExLimitService::s_relExLimitService;

// This is the constructor of a class that has been exported.
// see RELExLimitService.h for the class definition
CRELExLimitService::CRELExLimitService()
{ 
	//Initialize the state file name
	m_tszStateFileName = NULL;
	m_tszStateFileName = new TCHAR[MAX_PATH+1];
	if (m_tszStateFileName == NULL)
	{
		return;
	}

#ifdef _WINDOWS
	// Get the current directory and create the full path of the state file name
	TCHAR tszCurrentDir[MAX_PATH+1];
	TCHAR tszStateFName[] = _T("\\ExerciseLimit.cfg");
	GetCurrentDirectory(MAX_PATH, tszCurrentDir);
	if (_tcslen(tszCurrentDir) >= MAX_PATH - _tcslen(tszStateFName))
	{
		return;
	}
	_tcscpy(m_tszStateFileName, tszCurrentDir);
	_tcscat(m_tszStateFileName, tszStateFName);
#else
	_tcscpy(m_tszStateFileName, _T("\\My Documents\\MPEG-21 REL RS\\ExerciseLimit.cfg"));
#endif
	return; 
}

//------------------------------------------------------------------------------------------
//--FUNCTION initialize
//------------------------------------------------------------------------------------------
//--This function initializes the maximum count for the condition with the condition id (the 
//	license id is used as the condition id for now)
//--The input condition id is the id of the containing license and the maximum count is the
//	maximum exercise count for the corresponding condition..
//--The function returns S_OK after successful initialization.  S_FALSE if a value already
//	exists for the corresponding condition.  E_FAIL if there was an error.
//------------------------------------------------------------------------------------------
HRESULT CRELExLimitService::initialize(TCHAR *tszConditionId, int nMaximumCount)
{
	int nCount = 0;
	// Check to see if the state file already has a state for this condition
	if ((nCount = getRemainingCount(tszConditionId)) == EXSERVICE_FAIL)
	{
		return E_FAIL;
	}

	if (nCount != EXSERVICE_FALSE)
	{
		return S_FALSE;
	}

	// Create the line to append (Format: Conditionid=count\n)
	TCHAR tszCount[11];
	int nMaxIntLen = 10;
	_itot(nMaximumCount, tszCount, 10);

	TCHAR *tszLine;
	int nLen = _tcslen(tszCount);
	tszLine = new TCHAR[_tcslen(tszConditionId) + nMaxIntLen+3];
	if (tszLine == NULL)
	{
		// can't do much.  just return E_FAIL
		return E_FAIL;
	}
	_tcscpy(tszLine, tszConditionId);
	_tcscat(tszLine, _T("="));
	_tcscat(tszLine, tszCount);
	_tcscat(tszLine, _T("\n"));

	//Open the state file and append the text
	FILE *fileState = _tfopen(m_tszStateFileName, _T("a+"));
	if (fileState == NULL)
	{
		return E_FAIL;
	}

	HRESULT retVal = S_OK;
	if (_fputts(tszLine, fileState) == _TEOF)
	{
		retVal = E_FAIL;
	}
	fclose(fileState);
	return retVal;
}

//------------------------------------------------------------------------------------------
//--FUNCTION read
//------------------------------------------------------------------------------------------
//--This function reads the available count for the condition with the condition id (the 
//	license id is used as the condition id for now)
//--The input condition id is the id of the containing license.
//--The function returns the remaining exercise count for the given condition
//------------------------------------------------------------------------------------------
int CRELExLimitService::read(TCHAR *tszConditionId)
{
	return getRemainingCount(tszConditionId);
}

//------------------------------------------------------------------------------------------
//--FUNCTION update
//------------------------------------------------------------------------------------------
//--This function updates the remaining exercise count for the given condition (the 
//	license id is used as the condition id for now).  It substracts the remaining exercise
//	count with the exercise count supplied, if the resulting value is non-negative.
//--The input condition id is the id of the containing license and the exercise count is
//	the number of times that the user wishes to exercise the right.
//--The function returns S_OK if the resultant value after substracting the input exercise
//	count from the remaining exercise count is non-negative.  S_FALSE if the resultant value
//	is negative.  E_FAIL if an error occurred.
//------------------------------------------------------------------------------------------
HRESULT CRELExLimitService::update(TCHAR *tszConditionId, int nExerciseCount)
{
	TCHAR *pIdx = NULL;
	if (tszConditionId == NULL || m_tszStateFileName == NULL)
	{
		return EXSERVICE_FAIL;  // A custom error level indicating
	}

	// Open the state file
	FILE *fileState = _tfopen(m_tszStateFileName, _T("r"));
	if (fileState == NULL)
	{
		return EXSERVICE_FALSE;
	}

	TCHAR tszNewStateFileName[MAX_PATH+2];
	_tcscpy(tszNewStateFileName, m_tszStateFileName);
	_tcscat(tszNewStateFileName, _T(".new"));
	FILE *fileStateNew = _tfopen(tszNewStateFileName, _T("w"));
	if (fileStateNew == NULL)
	{
		if (fileState != NULL)
		{
			fclose(fileState);
		}
		return EXSERVICE_FALSE;
	}

	// Fetch the condition ids one at a time and check to see if the supplied condition id matches the
	// existing condition id
	TCHAR tszLine[MAX_PATH];
	int nNewCount = 0;
	while (_fgetts(tszLine, MAX_PATH, fileState))
	{
		// Check the buffer
		pIdx = _tcschr(tszLine, _T('='));
		if (pIdx == NULL)
		{
			_fputts(tszLine, fileStateNew);
			continue;
		}

		*pIdx = _T('\0');
		if (_tcscmp(tszConditionId, tszLine) != 0)
		{
			*pIdx = _T('=');
			_fputts(tszLine, fileStateNew);
			continue;
		}
		nNewCount = _ttoi(pIdx+1) - nExerciseCount;
		if (nNewCount >= 0)
		{
			_tcscat(tszLine, _T("="));
			TCHAR tszCount[11];
			_itot(nNewCount, tszCount, 10);
			_tcscat(tszLine, tszCount);
			_tcscat(tszLine, _T("\n"));
		}
		else
		{
			*pIdx = _T('=');
		}
		_fputts(tszLine, fileStateNew);
	}
	
	if (fileState != NULL)
		fclose(fileState);
	if (fileStateNew != NULL)
		fclose(fileStateNew);

	// Rename the new configuration file to match the name of the original configuration file
	if (!SetFileAttributes(m_tszStateFileName, FILE_ATTRIBUTE_NORMAL) ||
		CopyFile(tszNewStateFileName, m_tszStateFileName, FALSE) == FALSE)
	{
		// Unable to copy the new configuration file to the original configuration file
		return E_FAIL;
	}
	DeleteFile(tszNewStateFileName);


	// if we did not get a match, we shall return S_FALSE;
	if (pIdx == NULL || nNewCount < 0)
	{
		return S_FALSE;
	}

	return S_OK;
}

//------------------------------------------------------------------------------------------
//--FUNCTION getRemainingCount
//------------------------------------------------------------------------------------------
//--This function gets the remaining exercise count for the given condition (the 
//	license id is used as the condition id for now).
//--The input condition id is the id of the containing license.
//--The function returns the remaining exercise count for the given condition
//------------------------------------------------------------------------------------------
int CRELExLimitService::getRemainingCount(TCHAR *tszConditionId)
{
	int nCount = EXSERVICE_FALSE;
	if (tszConditionId == NULL || m_tszStateFileName == NULL)
	{
		return EXSERVICE_FAIL;  // A custom error level indicating
	}

	// Open the state file
	FILE *fileState = _tfopen(m_tszStateFileName, _T("r"));
	if (fileState == NULL)
	{
		return EXSERVICE_FALSE;
	}

	// Fetch the condition ids one at a time and check to see if the supplied condition id matches the
	// existing condition id
	TCHAR tszLine[MAX_PATH];
	while (_fgetts(tszLine, MAX_PATH, fileState))
	{
		// Check the buffer and break if we found a match
		TCHAR *pIdx = NULL;
		pIdx = _tcschr(tszLine, _T('='));
		if (pIdx == NULL)
		{
			continue;
		}

		*pIdx = _T('\0');
		if (_tcscmp(tszConditionId, tszLine) != 0)
		{
			continue;
		}
		nCount = _ttoi(pIdx+1);
		break;
	}

	// Close the file and return
	fclose(fileState);
	return nCount;
}

// The list of exported functions
//------------------------------------------------------------------------------------------
//--FUNCTION initialize
//------------------------------------------------------------------------------------------
//--This function initializes the maximum count for the condition with the condition id (the 
//	license id is used as the condition id for now)
//--The input condition id is the id of the containing license and the maximum count is the
//	maximum exercise count for the corresponding condition..
//--The function returns S_OK after successful initialization.  S_FALSE if a value already
//	exists for the corresponding condition.  E_FAIL if there was an error.
//------------------------------------------------------------------------------------------
RELEXLIMITSERVICE_API HRESULT initialize(TCHAR *tszConditionId, int nMaximumCount)
{
	return CRELExLimitService::s_relExLimitService.initialize(tszConditionId, nMaximumCount);
}

//------------------------------------------------------------------------------------------
//--FUNCTION read
//------------------------------------------------------------------------------------------
//--This function reads the available count for the condition with the condition id (the 
//	license id is used as the condition id for now)
//--The input condition id is the id of the containing license.
//--The function returns the remaining exercise count for the given condition
//------------------------------------------------------------------------------------------
RELEXLIMITSERVICE_API int read(TCHAR *tszConditionId)
{
	return CRELExLimitService::s_relExLimitService.read(tszConditionId);
}

//------------------------------------------------------------------------------------------
//--FUNCTION update
//------------------------------------------------------------------------------------------
//--This function updates the remaining exercise count for the given condition (the 
//	license id is used as the condition id for now).  It substracts the remaining exercise
//	count with the exercise count supplied, if the resulting value is non-negative.
//--The input condition id is the id of the containing license and the exercise count is
//	the number of times that the user wishes to exercise the right.
//--The function returns S_OK if the resultant value after substracting the input exercise
//	count from the remaining exercise count is non-negative.  S_FALSE if the resultant value
//	is negative.  E_FAIL if an error occurred.
//------------------------------------------------------------------------------------------
RELEXLIMITSERVICE_API HRESULT update(TCHAR *tszConditionId, int nExerciseCount)
{
	return CRELExLimitService::s_relExLimitService.update(tszConditionId, nExerciseCount);
}

