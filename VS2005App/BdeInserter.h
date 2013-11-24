// BdeInserter.h : main header file for the BDEINSERTER application
//

#if !defined(AFX_BDEINSERTER_H__F6F4C925_57EE_11D8_80E8_0010A4DF8E4B__INCLUDED_)
#define AFX_BDEINSERTER_H__F6F4C925_57EE_11D8_80E8_0010A4DF8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBdeInserterApp:
// See BdeInserter.cpp for the implementation of this class
//

class CBdeInserterApp : public CWinApp
{
public:
	CBdeInserterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBdeInserterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBdeInserterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BDEINSERTER_H__F6F4C925_57EE_11D8_80E8_0010A4DF8E4B__INCLUDED_)
