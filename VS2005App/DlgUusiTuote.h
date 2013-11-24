#pragma once
#include "afxwin.h"

// DlgUusiTuote dialog
class DlgUusiTuote : public CDialog
{
	DECLARE_DYNAMIC(DlgUusiTuote)

public:
	DlgUusiTuote(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgUusiTuote();

// Dialog Data
	//{{AFX_DATA(DlgUusiTuote)
	enum { IDD = IDD_DLGUUSITUOTE };
	CStatic		m_picQuestion;
	CStatic		m_stcQuestion;
	CEdit		m_edtName;
	CEdit		m_edtProductNumber;
	CComboBox	m_cmbUnit;
	CEdit		m_edtPurchasePrice;
	CEdit		m_edtSellPrice;
	CEdit		m_edtAlv;
	CButton		m_btnOK;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgUusiTuote)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DlgUusiTuote)
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdtname();
	afx_msg void OnCbnSelchangeCmbunit();
	afx_msg void OnCbnEditchangeCmbunit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_sync;									// nimi lisätty/nimeä muokattu -> synkkaa listat
	int m_mode;									// tila: 0=uusi, 1=muokkaus
	CString m_productgroup_name;
	ItemData_type *m_pid;						// muokatessa alkuarvot

	CString m_name;
	CString m_productnumber;
	CString m_unit;
	CString m_purchaseprice;
	CString m_sellprice;
	CString m_alv;
};
