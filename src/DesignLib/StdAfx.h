// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F8632548_0AD4_11D6_85B7_0060979DBC4B__INCLUDED_)
#define AFX_STDAFX_H__F8632548_0AD4_11D6_85B7_0060979DBC4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER >= 1927 
//HACK VS 16.7 ATL header bug 
#define __ATLIMAGE_H__ 
namespace ATL { class CImage; }
//#pragma warning( disable : 4150 4458 )   
//#pragma comment(lib, "gdiplus.lib")
#endif 

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F8632548_0AD4_11D6_85B7_0060979DBC4B__INCLUDED_)
