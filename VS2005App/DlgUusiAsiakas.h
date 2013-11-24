#pragma once
#include "afxwin.h"

// DlgUusiAsiakas dialog
class DlgUusiAsiakas : public CDialog
{
	DECLARE_DYNAMIC(DlgUusiAsiakas)

public:
	DlgUusiAsiakas(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgUusiAsiakas();

// Dialog Data
	//{{AFX_DATA(DlgUusiAsiakas)
	enum { IDD = IDD_DLGUUSIASIAKAS };
	CStatic		m_picQuestion;
	CStatic		m_stcQuestion;
	CEdit		m_edtName;
	CEdit		m_edtAddress;
	CComboBox	m_cmbBiller;
	CEdit		m_edtNote;
	CEdit		m_edtShortNote;
	CEdit		m_edtInfo;
	CEdit		m_edtCustomerNumber;
	CButton		m_btnOK;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgUusiAsiakas)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DlgUusiAsiakas)
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCmbbiller();
	afx_msg void OnCbnEditchangeCmbbiller();
	afx_msg void OnEnChangeEdtname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_sync;									// nimi lisätty/nimeä muokattu -> synkkaa listat
	int m_mode;									// tila: 0=uusi, 1=muokkaus
	CString m_region_name;
	ItemData_workplace *m_pid;					// muokatessa alkuarvot

	CString m_name;
	CString m_address;
	CString m_biller_name;
	CString m_note;
	CString m_shortnote;
	CString m_info;
	CString m_customernumber;
};
