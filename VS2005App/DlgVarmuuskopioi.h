#if !defined(AFX_DLGVARMUUSKOPIOI_H__BC2C77D2_3F8F_44BC_98E8_F9929404C5BC__INCLUDED_)
#define AFX_DLGVARMUUSKOPIOI_H__BC2C77D2_3F8F_44BC_98E8_F9929404C5BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVarmuuskopioi.h : header file
//
#include "ColorStatic.h"

/////////////////////////////////////////////////////////////////////////////
// DlgVarmuuskopioi dialog

class DlgVarmuuskopioi : public CDialog
{
// Construction
public:
	DlgVarmuuskopioi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgVarmuuskopioi)
	enum { IDD = IDD_DLGVARMUUSKOPIOINTI };
	CStatic	m_stcVKopioitava;
	CColorStatic	m_stcInfo;
	CButton	m_btnVarmuuskopioi;
	CButton	m_btnCancel;
	CButton	m_chkMatka;
	CEdit	m_edtPath;
	CEdit	m_edtFileName;
	CButton	m_chkPoista;
	CButton	m_btnPolku;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgVarmuuskopioi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgVarmuuskopioi)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnvarmuuskopioi();
	afx_msg void OnBtnpolku();
	afx_msg void OnRadkopioi();
	afx_msg void OnChangeEdtfilename();
	afx_msg void OnChangeEdtpath();
	afx_msg void OnChkmatka();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    friend int CALLBACK BrowseCallbackProc_SL(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData);

    CBitmap m_cbm;
    CString m_filename;
    CString m_path;
    CString m_tila;
    BOOL m_matka;
    BOOL m_bVarmuuskopioitu;

    CWinThread *m_pCWinThread;
    friend UINT ThreadFunction_vk(LPVOID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVARMUUSKOPIOI_H__BC2C77D2_3F8F_44BC_98E8_F9929404C5BC__INCLUDED_)
