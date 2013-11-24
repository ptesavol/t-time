#pragma once
#include "afxwin.h"

// DlgUusiTyomatka dialog
class DlgUusiTyomatka : public CDialog
{
	DECLARE_DYNAMIC(DlgUusiTyomatka)

public:
	DlgUusiTyomatka(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgUusiTyomatka();

// Dialog Data
	//{{AFX_DATA(DlgUusiTyomatka)
	enum { IDD = IDD_DLGUUSITYOMATKA };
	CComboBox	m_cmbWorker;
	CComboBox	m_cmbBiller;
	CEdit		m_edtStartMeter;
	CEdit		m_edtEndMeter;
	CEdit		m_edtPrivate;
	CEdit		m_edtStartTime;
	CEdit		m_edtEndTime;
	CEdit		m_edtStartPlace;
	CEdit		m_edtEndPlace;
	CEdit		m_edtPurpose;
	CStatic		m_picQuestion;
	CStatic		m_stcQuestion;
	CButton		m_btnOK;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgUusiTyomatka)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DlgUusiTyomatka)
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCmbworker();
	afx_msg void OnCbnEditchangeCmbworker();
	afx_msg void OnCbnSelchangeCmbbiller();
	afx_msg void OnCbnEditchangeCmbbiller();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_sync;								// nimi lisätty/nimeä muokattu -> synkkaa listat
	int m_mode;								// tila: 0=uusi, 1=muokkaus
	ItemData_travel *m_pid;					// muokatessa alkuarvot

	CString m_worker_name;
	CString m_biller_name;
	CString m_startmeter;
	CString m_endmeter;
	CString m_starttime;
	CString m_endtime;
	CString m_private;
	CString m_startplace;
	CString m_endplace;
	CString m_purpose;
	CString m_StartDate;
	CString m_StartTime;
	CString m_EndDate;
	CString m_EndTime;
};