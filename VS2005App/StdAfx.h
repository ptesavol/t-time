// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#if !defined(AFX_STDAFX_H__8B69F80B_E800_45BF_B142_2AC5D5C9BD1A__INCLUDED_)
#define AFX_STDAFX_H__8B69F80B_E800_45BF_B142_2AC5D5C9BD1A__INCLUDED_

#define WINVER 0x0401                      // earlier 98, NT
/*
#define WINVER 0x0500                      // Windows 2000
#define _WIN32_WINNT 0x0500

#define WINVER 0x0501                      // Windows XP, Windows Server 2003
#define _WIN32_WINNT 0x0501

#define WINVER 0x0502                      // Windows XP with SP2, Windows Server 2003 SP1
#define _WIN32_WINNT 0x0502

#define WINVER 0x0600                      // Windows Vista, Windows Server 2008. 
#define _WIN32_WINNT 0x0600

Windows Server 2008	0x0600
Windows Vista	0x0600
Windows Server 2003 with SP1, Windows XP with SP2	0x0502
Windows Server 2003, Windows XP	0x0501
Windows 2000	0x0500
*/

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#pragma warning(disable:4200)

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>       // CSmtp
#include <afxsock.h>
#include <afxpriv.h>
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8B69F80B_E800_45BF_B142_2AC5D5C9BD1A__INCLUDED_)
