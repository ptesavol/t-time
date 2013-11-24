#pragma once
#include "afxwin.h"

// DlgUusiTyotyyppi dialog
class DlgUusiTyotyyppi : public CDialog
{
	DECLARE_DYNAMIC(DlgUusiTyotyyppi)

public:
	DlgUusiTyotyyppi(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgUusiTyotyyppi();

// Dialog Data
	//{{AFX_DATA(DlgUusiTyotyyppi)
	enum { IDD = IDD_DLGUUSITYOTYYPPI };
	CStatic	m_picQuestion;
	CStatic	m_stcQuestion;
	CEdit	m_edtName;
	CEdit	m_edtProductNumber;
	CButton	m_btnOK;
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgUusiTyotyyppi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DlgUusiTyotyyppi)
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdtname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_sync;									// nimi lisätty/nimeä muokattu -> synkkaa listat
	int m_mode;									// tila: 0=uusi, 1=muokkaus
	ItemData_type *m_pid;						// muokatessa alkuarvot

	CString m_name;
	CString m_productnumber;
};
