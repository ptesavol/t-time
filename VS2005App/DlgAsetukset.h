#if !defined(AFX_DLGASETUKSET_H__D75B2896_3FE6_4702_9E11_432213C75C8B__INCLUDED_)
#define AFX_DLGASETUKSET_H__D75B2896_3FE6_4702_9E11_432213C75C8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAsetukset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAsetukset dialog

class CDlgAsetukset : public CDialog
{
// Construction
public:
	CDlgAsetukset(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAsetukset)
	enum { IDD = IDD_DLGASETUKSET };
	CButton	m_btnOK;
	CStatic	m_stcLaskOhj;
	CComboBox	m_cmbLaskYritys;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAsetukset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAsetukset)
	afx_msg void OnRadlaskohj();
	afx_msg void OnSelchangeCmblaskyritys();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    friend int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lp, LPARAM pData);

    CString haeYritykset(CString polku, CString yritys);

    CString m_OPTIONS_LASKUTUSOHJELMA;
    CString m_OPTIONS_LASKUTUSOHJELMA_POLKU;
    CString m_OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU;
    CString m_OPTIONS_LASKUTUSOHJELMA_YRITYS ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGASETUKSET_H__D75B2896_3FE6_4702_9E11_432213C75C8B__INCLUDED_)
