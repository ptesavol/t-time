// taika.h : main header file for the TAIKA application
//

#if !defined(AFX_TAIKA_H__1F1F0755_76D0_454D_9CF0_DEA388B98439__INCLUDED_)
#define AFX_TAIKA_H__1F1F0755_76D0_454D_9CF0_DEA388B98439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#pragma warning(disable:4786)
#include "resource.h"		// main symbols
#include "DbSqlite.h"       // tietokanta
#include "Parse.h"          // parsinta
#include "AccountingProgram.h"
#include "DlgEtsi.h"

/////////////////////////////////////////////////////////////////////////////
// CTaikaApp:
// See taika.cpp for the implementation of this class
//
class CTaikaApp : public CWinApp
{
public:
	CTaikaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaikaApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTaikaApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    CString m_app_title;					// ohjelman nimi
    CString m_app_path;						// Ohjelman käynnistyskansio
    CString m_opt_path;						// Asetustiedoston polku\nimi
    CString m_db_path;						// tietokannan polku\nimi

    int m_yanc_wp;							// Yes (R_YES), Yes to All (R_YESTA), No (R_NO), No to ALl (R_NOTA)
    int m_yanc_b;
    int m_yanc_wt;

    HACCEL m_hAccelerators;

    DlgEtsi m_dlgEtsi;						// Etsi-dialogi

    int m_sync_raportit;					// Eri näyttöjen listojen synkronointi
    int m_sync_listat;
    int m_sync_tyomatkat;

    CImageList *m_pCImageList;             // Yhteinen ImageList listoille
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAIKA_H__1F1F0755_76D0_454D_9CF0_DEA388B98439__INCLUDED_)
