#if !defined(AFX_DLGSMTP_H__C5D5B29D_DD7F_4546_81F1_D2CCEF0FEB51__INCLUDED_)
#define AFX_DLGSMTP_H__C5D5B29D_DD7F_4546_81F1_D2CCEF0FEB51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSMTP.h : header file
//
#include "ColorStatic.h"

/////////////////////////////////////////////////////////////////////////////
// DlgSMTP dialog

class DlgSMTP : public CDialog
{
// Construction
public:
	DlgSMTP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSMTP)
	enum { IDD = IDD_DLGSMTP };
	CStatic	m_stcAttachment;
	CButton	m_chkLaskuttajat;
	CButton	m_chkAsiakkaat;
	CButton	m_chkTuotteet;
	CComboBox	m_cmbSMTPServer;
	CEdit	m_edtPassword;
	CButton	m_chkKaytaAuth;
	CButton	m_chkMuistaUn;
	CColorStatic	m_stcInfo;
	CEdit	m_edtUsername;
	CEdit	m_edtSMTPPort;
	CButton	m_btnCancel;
	CEdit	m_edtRecipients;
	CButton	m_btnLaheta;
	CButton	m_chkTyotyypit;
	CButton	m_btnPolku;
	CEdit	m_edtFrom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSMTP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSMTP)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnpolku();
	afx_msg void OnBtnlaheta();
	afx_msg void OnChangeEdtrecipients();
	afx_msg void OnChangeEdtfrom();
	virtual void OnCancel();
	afx_msg void OnChangeEdtport();
	afx_msg void OnChkmuistaun();
	afx_msg void OnChangeEdtpassword();
	afx_msg void OnChangeEdtusername();
	afx_msg void OnChkkaytaauth();
	afx_msg void OnEditchangeCmbsmtpserver();
	afx_msg void OnSelchangeCmbsmtpserver();
	afx_msg void OnChktyotyypit();
	afx_msg void OnChktuotteet();
	afx_msg void OnRadlahde();
	afx_msg void OnChkasiakkaat();
	afx_msg void OnChklaskuttajat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_mode;
    int m_attach_from;
    int m_asiakkaat;
    int m_laskuttajat;
    int m_tyotyypit;
	int m_tuotteet;
    CString m_attachmentpath;
    CString m_attachmentfilename;
    CString m_recipients;
    CString m_from;
    CString m_SMTPServer;
    CString m_SMTPPort;
    CString m_username;
    CString m_password;
    BOOL m_kayta_auth;
    BOOL m_muista_un;

    CBitmap m_cbm;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSMTP_H__C5D5B29D_DD7F_4546_81F1_D2CCEF0FEB51__INCLUDED_)
