#pragma once
#include "afxwin.h"

// DlgUusiLaskuttaja dialog
class DlgUusiLaskuttaja : public CDialog
{
	DECLARE_DYNAMIC(DlgUusiLaskuttaja)

public:
	DlgUusiLaskuttaja(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgUusiLaskuttaja();

// Dialog Data
	//{{AFX_DATA(DlgUusiLaskuttaja)
	enum { IDD = IDD_DLGUUSILASKUTTAJA };
	CStatic	m_picQuestion;
	CStatic	m_stcQuestion;
	CEdit	m_edtName;
	CEdit	m_edtEmail;
	CButton	m_btnOK;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgUusiLaskuttaja)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DlgUusiLaskuttaja)
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdtname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_sync;									// nimi lisätty/nimeä muokattu -> synkkaa listat
	int m_mode;									// tila: 0=uusi, 1=muokkaus
	ItemData_biller *m_pid;						// muokatessa alkuarvot

	CString m_name;
	CString m_email;
};
