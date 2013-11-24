#if !defined(AFX_DLGSIIVOATIETOKANTA_H__29A781EF_A21A_49D4_A8DA_27DFE51153EF__INCLUDED_)
#define AFX_DLGSIIVOATIETOKANTA_H__29A781EF_A21A_49D4_A8DA_27DFE51153EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSiivoaTietokanta.h : header file
//
#include "ColorStatic.h"

/////////////////////////////////////////////////////////////////////////////
// DlgSiivoaTietokanta dialog

class DlgSiivoaTietokanta : public CDialog
{
// Construction
public:
	DlgSiivoaTietokanta(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSiivoaTietokanta)
	enum { IDD = IDD_DLGSIIVOATIETOKANTA };
	CButton	m_chkLaskuttamattomatMyynnit;
	CButton	m_chkLaskutetutMyynnit;
	CButton	m_chkTuotteet;
	CButton	m_chkTuoteryhmat;
	CButton	m_btnCancel;
	CButton	m_btnPoista;
	CColorStatic	m_stcInfo;
	CButton	m_chkLaskuttamattomatTyoajat;
	CButton	m_chkLaskutetutTyoajat;
	CButton	m_chkTyotyypit;
	CButton	m_chkTyontekijat;
	CButton	m_chkTyomatkat;
	CButton	m_chkLaskuttajat;
	CButton	m_chkAsiakkaat;
	CButton	m_chkAsiakasryhmat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSiivoaTietokanta)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSiivoaTietokanta)
	afx_msg void OnBtnpoista();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    BOOL m_siivottu;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSIIVOATIETOKANTA_H__29A781EF_A21A_49D4_A8DA_27DFE51153EF__INCLUDED_)
