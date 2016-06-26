// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__332EED85_1E02_4EA3_9908_1DDCE3BA2DAF__INCLUDED_)
#define AFX_STDAFX_H__332EED85_1E02_4EA3_9908_1DDCE3BA2DAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

// TODO: reference additional headers your program requires here

#include <atlbase.h>
#include <atlconv.h>
#include <comdef.h>

#include <objsafe.h>
namespace MSXML
{
#ifdef _WINDOWS
#import <msxml4.dll>
#include <msxml2.h>
#else
#include <msxml.h>
#endif
}
#include <ocidl.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__332EED85_1E02_4EA3_9908_1DDCE3BA2DAF__INCLUDED_)
