#if !defined(AFX_DLGINFO_H__2C4CD0AD_D4A4_40D2_AC8C_FE75F34AC66E__INCLUDED_)
#define AFX_DLGINFO_H__2C4CD0AD_D4A4_40D2_AC8C_FE75F34AC66E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfo.h : header file
//
#include "Ipe.h"

/////////////////////////////////////////////////////////////////////////////
// DlgInfo dialog

class DlgInfo : public CDialog
{
// Construction
public:
	DlgInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgInfo)
	enum { IDD = IDD_DLGINFO };
	CListCtrl	m_lstLista;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgInfo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    afx_msg void OnMoving(UINT, LPRECT);
	DECLARE_MESSAGE_MAP()

    virtual void OnCancel();

public:
    short m_dlgWidth;                                // Dialogin leveys/korkeus, sijainti
    short m_dlgHeight;
    short m_dlgXPos;
    short m_dlgYPos;
    CBitmap m_bmpSulje;

    int m_mode;                                      // MODE_VALITUT/MODE_KAIKKINAYTETYT
    int m_time_mode;                                 // Ajat minuutteina vai tunteina
    CListCtrl *m_pCListCtrl;                         // Eriteltävät työtyypit
    CString m_caption;

    Ipe m_Ipe;                                       // InPlaceEdit (viestintä)
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFO_H__2C4CD0AD_D4A4_40D2_AC8C_FE75F34AC66E__INCLUDED_)
