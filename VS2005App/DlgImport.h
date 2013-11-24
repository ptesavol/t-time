#if !defined(AFX_DLGIMPORT_H__410A0823_F4E5_49C0_981D_C6F80DE23626__INCLUDED_)
#define AFX_DLGIMPORT_H__410A0823_F4E5_49C0_981D_C6F80DE23626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImport.h : header file
//
#include "ColorListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// DlgImport dialog

class DlgImport : public CDialog
{
// Construction
public:
	DlgImport(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgImport)
	enum { IDD = IDD_DLGIMPORT };
	CButton	m_btnOK;
	CButton	m_btnCancel;
	CStatic	m_stcInfo;
	CComboBox	m_cmbTila;
	CStatic	m_stcYritys;
	CColorListCtrl	m_lstOne;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgImport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgImport)
	afx_msg void OnSelchangeCmbtila();
	afx_msg void OnDestroy();
    afx_msg LRESULT OnMsgValitseKaikki(WPARAM wparam, LPARAM lparam);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    void haeAsiakkaat();
    void haeTyotyypit();
    void haeTuotteet();
    BOOL tuoAsiakkaat();
    BOOL tuoTyotyypit();
    BOOL tuoTuotteet();
    CString haeAlv(Alv *pAlv, string alvID, BOOL bvg);

    CImageList *m_pCImageList;
    BOOL m_update;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMPORT_H__410A0823_F4E5_49C0_981D_C6F80DE23626__INCLUDED_)
