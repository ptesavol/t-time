#if !defined(AFX_DLGSIIRRAASIAKKAAT_H__F4516AF5_4416_4513_BCAF_F8433B821309__INCLUDED_)
#define AFX_DLGSIIRRAASIAKKAAT_H__F4516AF5_4416_4513_BCAF_F8433B821309__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSiirraAsiakkaat.h : header file
//
#include "defines.h"

/////////////////////////////////////////////////////////////////////////////
// DlgSiirraAsiakkaat dialog

class DlgSiirraAsiakkaat : public CDialog
{
// Construction
public:
	DlgSiirraAsiakkaat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSiirraAsiakkaat)
	enum { IDD = IDD_DLGSIIRRAASIAKKAAT };
	CStatic	m_stcInfo;
	CListBox	m_lstAsiakkaat;
	CListBox	m_lstAsiakasryhma;
	CButton	m_btnSiirra;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSiirraAsiakkaat)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSiirraAsiakkaat)
	afx_msg void OnSelchangeLstasiakasryhmat();
	afx_msg void OnBtnsiirra();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    vector <ItemData_workplace*> m_asiakkaat;
    CString m_region;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSIIRRAASIAKKAAT_H__F4516AF5_4416_4513_BCAF_F8433B821309__INCLUDED_)
