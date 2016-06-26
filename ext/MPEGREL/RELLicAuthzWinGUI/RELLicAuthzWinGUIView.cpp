// RELLicAuthzWinGUIView.cpp : implementation of the CRELLicAuthzWinGUIView class
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
#include "RELLicAuthzWinGUI.h"

#include "RELLicAuthzWinGUIDoc.h"
#include "RELLicAuthzWinGUIView.h"

#include "CGUtil.h"

using namespace MSXML;
#include "RELLicAuthzDriver.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRELLicAuthzWinGUIView

IMPLEMENT_DYNCREATE(CRELLicAuthzWinGUIView, CFormView)

BEGIN_MESSAGE_MAP(CRELLicAuthzWinGUIView, CFormView)
	//{{AFX_MSG_MAP(CRELLicAuthzWinGUIView)
	ON_BN_CLICKED(IDC_BN_LIC_FILE, OnBrowseLicFile)
	ON_BN_CLICKED(IDC_BN_QUERY_FILE, OnBrowseQueryFile)
	ON_BN_CLICKED(IDC_BN_TEST, OnTest)
	ON_BN_CLICKED(IDC_CHECK_LOG, OnCheckLog)
	ON_BN_CLICKED(IDC_BN_CLEAR_LOG, OnBnClearLog)
	ON_COMMAND(ID_HELP_README, OnHelpReadme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRELLicAuthzWinGUIView construction/destruction

CRELLicAuthzWinGUIView::CRELLicAuthzWinGUIView()
	: CFormView(CRELLicAuthzWinGUIView::IDD)
	, m_bIssuerAndConditionPrint(FALSE)
	, m_bLog(FALSE)
	, m_bValidate(FALSE)
{
	//{{AFX_DATA_INIT(CRELLicAuthzWinGUIView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	TCHAR *tszCurrDir = m_strCurrDir.GetBuffer(MAX_PATH+1);
	DWORD dwLen = GetCurrentDirectory(MAX_PATH, tszCurrDir);
	m_tLogFileName = new TCHAR[MAX_PATH];
	if (m_tLogFileName == NULL)
	{
		// can't do much.  just return
		AfxMessageBox("Out of memory.  Please close the application.");
		return;
	}
	_tcscpy(m_tLogFileName, tszCurrDir);
	_tcscat(m_tLogFileName, _T("\\AuthorizationSession.log"));
	m_strCurrDir.ReleaseBuffer();
	RenameLogFile();
	::CoInitialize(NULL);
}

CRELLicAuthzWinGUIView::~CRELLicAuthzWinGUIView()
{
	if (m_tLogFileName)
	{
		delete [] m_tLogFileName;
		m_tLogFileName = NULL;
	}
	::CoUninitialize();
}

void CRELLicAuthzWinGUIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRELLicAuthzWinGUIView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Check(pDX, IDC_CHECK_PRINT, m_bIssuerAndConditionPrint);
	DDX_Check(pDX, IDC_CHECK_LOG, m_bLog);
	DDX_Check(pDX, IDC_CHECK_VALIDATE, m_bValidate);
	//}}AFX_DATA_MAP
}

BOOL CRELLicAuthzWinGUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CRELLicAuthzWinGUIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();

	GetDlgItem(IDC_CHECK_PRINT)->ShowWindow(SW_HIDE);
}

/////////////////////////////////////////////////////////////////////////////
// CRELLicAuthzWinGUIView diagnostics

#ifdef _DEBUG
void CRELLicAuthzWinGUIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRELLicAuthzWinGUIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CRELLicAuthzWinGUIDoc* CRELLicAuthzWinGUIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRELLicAuthzWinGUIDoc)));
	return (CRELLicAuthzWinGUIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRELLicAuthzWinGUIView message handlers

void CRELLicAuthzWinGUIView::OnBrowseLicFile()
{
	// TODO: Add your control notification handler code here
	CString strFileName = ShowFileDialog(_T("Select License File"));
	if (strFileName.GetLength() > 0)
		SetDlgItemText(IDC_EDIT_LIC_FILE, strFileName);
}

void CRELLicAuthzWinGUIView::OnBrowseQueryFile()
{
	// TODO: Add your control notification handler code here
	CString strFileName = ShowFileDialog(_T("Select Query File"));
	if (strFileName.GetLength() > 0)
		SetDlgItemText(IDC_EDIT_QUERY_FILE, strFileName);
}

void CRELLicAuthzWinGUIView::OnTest()
{
	// TODO: Add your control notification handler code here
	USES_CONVERSION;
	UpdateData(true);
	int nMaxLength = 256;
	CString strLicFileName;
	GetDlgItemText(IDC_EDIT_LIC_FILE, strLicFileName);
	if (strLicFileName.GetLength() == 0)
	{
		AfxMessageBox(_T("Please select the license file"));
		return;
	}

	CString strQueryFileName;
	GetDlgItemText(IDC_EDIT_QUERY_FILE, strQueryFileName);
	if (strQueryFileName.GetLength() == 0)
	{
		AfxMessageBox(_T("Please select the query file"));
		return;
	}
	CRELLicAuthzDriver driver;
	if (m_bLog && m_tLogFileName != NULL)
	{
		driver.setLogFileName(m_tLogFileName);
	}
	else
	{
		m_bIssuerAndConditionPrint = FALSE;
	}
	bool bIssCondPrint = false;
	if (m_bIssuerAndConditionPrint)
		bIssCondPrint = true;

	if (m_bValidate)
	{
		driver.setValidationFlag(true);
	}
	TCHAR tszTemp[MAX_PATH+2];
	GetCurrentDirectory(MAX_PATH, tszTemp);
	SetCurrentDirectory(m_strCurrDir);
	BSTR bstrLicFileName = T2BSTR(strLicFileName.GetBuffer(strLicFileName.GetLength() + 1));
	BSTR bstrQueryFileName = T2BSTR(strQueryFileName.GetBuffer(strQueryFileName.GetLength() + 1));
	CComPtr<IXMLDOMDocument> spLicenseDoc, spQueryDoc;
	VARIANT_BOOL bLicLoad = VARIANT_FALSE;
	VARIANT_BOOL bQueryLoad = VARIANT_FALSE;

	HRESULT hr = E_FAIL;
	if (m_bValidate)
	{
		hr = CGUtil::load(CComBSTR(bstrLicFileName), spLicenseDoc, bLicLoad, true);
	}
	else
	{
		hr = CGUtil::load(CComBSTR(bstrLicFileName), spLicenseDoc, bLicLoad, false);
	}
	if (hr == S_OK && bLicLoad == VARIANT_TRUE && spLicenseDoc != NULL)
		hr = CGUtil::load(CComBSTR(bstrQueryFileName), spQueryDoc, bQueryLoad);
	if (bstrLicFileName)
		::SysFreeString(bstrLicFileName);
	if (bstrQueryFileName)
		::SysFreeString(bstrQueryFileName);
	if (hr != S_OK || bQueryLoad == VARIANT_FALSE || spQueryDoc == NULL)
	{
		MessageBox(_T("Unable to load eitheR the license or the query file"), 
			_T("License authorization status"), MB_OK | MB_ICONEXCLAMATION);
	}

	CComBSTR bstrLic, bstrQuery;
	hr = spLicenseDoc->get_xml(&bstrLic);
	if (S_OK == hr)
		hr = spQueryDoc->get_xml(&bstrQuery);
	if (hr == S_OK)
		hr = driver.relAuthorizeRight(bstrLic, bstrQuery, bIssCondPrint);

	SetCurrentDirectory(tszTemp);

	strLicFileName.ReleaseBuffer();
	strQueryFileName.ReleaseBuffer();
	CString strLogInfo;
	if (m_bLog)
	{
		strLogInfo.Format(_T(".  Please refer the log file '%s' for more information."), m_tLogFileName);
	}
	if (hr == S_OK)
	{
		CString strMsg(_T("License authorization successful"));
		strMsg += strLogInfo;
		MessageBox(strMsg, _T("License authorization status"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("License authorization unsuccessful. Hresult=%0x"), hr);
		strMsg += strLogInfo;
		MessageBox(strMsg, _T("License authorization status"), MB_OK | MB_ICONEXCLAMATION);
	}

	// Read the log file and print it on to the screen.  This is not the most efficient way, but will work.
	if (m_bLog)
	{
		CString strFileContents = GetLogFileContents(m_tLogFileName);
		if (strFileContents.GetLength() <= 0)
		{
			return;
		}
		CWnd *pWnd = GetFocus();
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RESULTS);
		pEdit->SetFocus();
		SetDlgItemText(IDC_EDIT_RESULTS, strFileContents);
		int nLineCount = pEdit->GetLineCount();
		pEdit->LineScroll(nLineCount);
		pWnd->SetFocus();
	}
}

CString CRELLicAuthzWinGUIView::ShowFileDialog(CString strTitle)
{
	CString strFileName;
	if (strTitle.GetLength() <= 0)
	{
		// Can't do much.  Just return.
	}

	CFileDialog dlg(TRUE, NULL, _T("*.xml"), OFN_OVERWRITEPROMPT, _T("Xml files (*.xml)|*.xml|All files (*.*)|*.*||"));
	dlg.m_ofn.lpstrTitle = strTitle;
	if (dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetPathName();
	}

	return strFileName;
}

CString CRELLicAuthzWinGUIView::GetLogFileContents(TCHAR *tLogFileName)
{
	CString strFileContents;
	FILE *fp = NULL;
	fp = _tfopen(tLogFileName, "r");
	if (fp == NULL)
	{
		AfxMessageBox(_T("Could not open log file for reading"));
		return strFileContents;
	}

	TCHAR szTemp[256];
	int nCharCount = 1;
	while (fgets(szTemp, 256, fp ) != NULL)
	{
		strFileContents += szTemp;
		strFileContents += _T("\r\n");
	}
	fclose(fp);

	return strFileContents;
}

void CRELLicAuthzWinGUIView::OnCheckLog() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CWnd *pWnd = GetDlgItem(IDC_CHECK_PRINT);
	if (m_bLog)
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}

void CRELLicAuthzWinGUIView::OnBnClearLog() 
{
	// TODO: Add your control notification handler code here
	if (m_tLogFileName == NULL)
	{
		return;
	}

	// Else, keep the log file as is, but make it empty.  This is achieved by opening the file in write mode
	// and closing it immediately.
	FILE *fp = NULL;
	fp = _tfopen(m_tLogFileName, "w");
	if (fp == NULL)
	{
		AfxMessageBox(_T("Unable to open the log file"));
		return;
	}

	fclose(fp);

	SetDlgItemText(IDC_EDIT_RESULTS, _T(""));
}

void CRELLicAuthzWinGUIView::RenameLogFile()
{
	CFileException ex;
	CFile fileLog;
	if (!fileLog.Open(m_tLogFileName, CFile::modeRead, &ex))
	{
		// Unable to open the log file for reading.
		return;
	}

	fileLog.Close();

	CString strSavedLogFileName(m_tLogFileName);
	// Find the last occurance of "."
	int nIdx = strSavedLogFileName.ReverseFind(_T('.'));
	CString strExtension("");
	if (nIdx >= 0)
	{
		strExtension = strSavedLogFileName.Right(strSavedLogFileName.GetLength() - nIdx);
		strSavedLogFileName = strSavedLogFileName.Left(nIdx);  // Removing the ".log" extension
	}

	CTime timeNow = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("%d%02d%02d%02d%02d%02d"), timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), timeNow.GetHour(), 
		timeNow.GetMinute(), timeNow.GetSecond());
	strSavedLogFileName += strTime + strExtension;
	CFile::Rename(m_tLogFileName, strSavedLogFileName);
}

void CRELLicAuthzWinGUIView::OnHelpReadme() 
{
	// TODO: Add your command handler code here	
	CString strWindowsDir(_tgetenv(_T("windir")));
	int nSepIdx = m_strCurrDir.ReverseFind(_T('\\'));
	CString strReadmePath = m_strCurrDir;
	if (nSepIdx > 0)
		strReadmePath = m_strCurrDir.Left(nSepIdx);
	if (nSepIdx > 0)
		nSepIdx = strReadmePath.ReverseFind(_T('\\'));
	if (nSepIdx > 0)
		strReadmePath = strReadmePath.Left(nSepIdx);

	CString strCommand = strWindowsDir + _T("\\notepad.exe ") + strReadmePath + _T("\\Readme.txt");

	UINT unExecReturn = WinExec(strCommand, SW_SHOWNORMAL);

	if (unExecReturn < 31) // This is according to MSDN documentation
	{
		AfxMessageBox(_T("Unable to display the readme file"));
	}
}
