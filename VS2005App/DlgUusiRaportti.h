#if !defined(AFX_DLGUUSIRAPORTTI_H__EAE59DD5_D333_4356_9866_7A64378954CE__INCLUDED_)
#define AFX_DLGUUSIRAPORTTI_H__EAE59DD5_D333_4356_9866_7A64378954CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUusiRaportti.h : header file
//
#include "defines.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// DlgUusiRaportti dialog

class DlgUusiRaportti : public CDialog
{
// Construction
public:
	DlgUusiRaportti(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgUusiRaportti)
	enum { IDD = IDD_DLGUUSIRAPORTTI };
	CStatic		m_stcType;
	CComboBox	m_cmbTyotyyppi;
	CComboBox	m_cmbTyontekija;
	CComboBox	m_cmbAsiakasryhma;
	CComboBox	m_cmbAsiakas;
	CComboBox	m_cmbLaskuttaja;
	CEdit		m_edtAloitusaika;
	CEdit		m_edtLopetusaika;
	CEdit		m_edtMaara;
	CComboBox	m_cmbYksikko;
	CEdit		m_edtMyyntihinta;
	CEdit		m_edtKokonaishinta;
	CEdit		m_edtAlvprosentti;
	CStatic		m_stcQuestion;
	CStatic		m_picQuestion;
	CStatic		m_stcMaara;
	CButton		m_btnOK;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgUusiRaportti)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgUusiRaportti)
	afx_msg void OnSelchangeCmbasiakasryhma();
	afx_msg void OnEditchangeCmbasiakas();
	afx_msg void OnSelchangeCmbasiakas();
	afx_msg void OnEditchangeCmbasiakasryhma();
	afx_msg void OnEditchangeCmblaskuttaja();
	afx_msg void OnSelchangeCmblaskuttaja();
	afx_msg void OnEditchangeCmbtyontekija();
	afx_msg void OnSelchangeCmbtyontekija();
	afx_msg void OnEditchangeCmbtyotyyppi();
	afx_msg void OnSelchangeCmbtyotyyppi();
	afx_msg void OnEnChangeEdtaloitusaika();
	afx_msg void OnEnChangeEdtlopetusaika();
	afx_msg void OnEnChangeEdtmaara();
	afx_msg void OnEnChangeEdtmyyntihinta();
	afx_msg void OnEnChangeEdtkokonaishinta();
	afx_msg void OnEnChangeEdtalvprosentti();
	afx_msg void OnBnClickedCharged();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_sync;								// nimi lisätty/nimeä muokattu -> synkkaa listat
	int m_mode;								// tila: 0=uusi, 1=muokkaus
	BOOL m_init;
    ItemData *m_pid;						// muokatessa alkuarvot
	int m_ajat;							// aikojen näyttö: min, h, #1
    CString m_tyyppi;						// Lisäyksen tyyppi WORKUNIT tai SALESUNIT

    CString m_biller_name;
    CString m_workplace_name;
    CString m_region_name;
    CString m_worker_name;
    CString m_worktype_name;
	CString m_starttime;
	CString m_endtime;
	CString m_unitvalue;
	CString m_unit;
	CString m_unitprice;
	CString m_totalprice;
	CString m_alv;
	CString m_StartDate;
	CString m_StartTime;
	CString m_EndDate;
	CString m_EndTime;
	CString m_charged;

	void setValues(int from);
	vector<CString> getProduct();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUUSIRAPORTTI_H__EAE59DD5_D333_4356_9866_7A64378954CE__INCLUDED_)
