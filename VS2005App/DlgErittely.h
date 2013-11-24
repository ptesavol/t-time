#include "afxwin.h"
#if !defined(AFX_DLGERITTELY_H__6A637D25_1741_455F_95F3_D613F5D27E94__INCLUDED_)
#define AFX_DLGERITTELY_H__6A637D25_1741_455F_95F3_D613F5D27E94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgErittely.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgErittely dialog

class DlgErittely : public CDialog
{
// Construction
public:
	DlgErittely(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgErittely)
	enum { IDD = IDD_DLGERITTELY };
	CStatic	m_stcOpt5;
	CStatic	m_stcOpt4;
	CStatic	m_stcOpt3;
	CStatic	m_stcOpt2;
	CStatic	m_stcOpt1;
	CButton	m_chkKmKorvaus;
	CComboBox	m_cmbFontti;
	CComboBox	m_cmbFontinkoko;
	CButton	m_chkYlapaivays;
	CEdit	m_edtYlatunniste;
	CEdit	m_edtAlatunniste;
	CButton	m_chkYlatunniste;
	CButton	m_chkAlatunniste;
	CButton	m_chkPaivays;
	CButton	m_chkSivutus;
	CComboBox	m_cmb5;
	CComboBox	m_cmb4;
	CComboBox	m_cmb3;
	CComboBox	m_cmb2;
	CComboBox	m_cmb1;
	CButton m_chkYhdistaTapahtumat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgErittely)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgErittely)
	afx_msg void OnBtntulosta();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmb1();
	afx_msg void OnSelchangeCmb2();
	afx_msg void OnSelchangeCmb3();
	afx_msg void OnSelchangeCmb4();
	afx_msg void OnSelchangeCmb5();
	afx_msg void OnChksivutus();
	afx_msg void OnChkalatunniste();
	afx_msg void OnChkylatunniste();
	afx_msg void OnChkylapaivays();
	afx_msg void OnSelchangeCmbfontinkoko();
	afx_msg void OnChangeEdtalatunniste();
	afx_msg void OnChangeEdtylatunniste();
	afx_msg void OnCbnSelchangeCmbyhteenveto();
	afx_msg void OnSelchangeCmbfontti();
	afx_msg void OnChkkmkorvaus();
	afx_msg void OnChkyhdistatapahtumat();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    void asiakkaat();
    void tyontekijat();
    void tyomatkat();
    void tunnisteet(CDC *pdc, float cx, float cy, float page_w, float page_h, CFont *pf, float cyCharHeight8);
	void teeYhdiste();
    BOOL kopioi_m_tapahtumat();
    friend int CALLBACK enumFontFamExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam);

    vector <ItemData*> m_tapahtumat;                 // tapahtumat (WorkUnit) erittelyyn
	vector <ItemData*> m_tapahtumat_tulostukseen;    // tähän yhdistetyt työtyypit tapahtumissa rapottisivulta tulostettaessa (m_yhdistatapahtumat tilan mukaan)
    vector <ItemData_travel*> m_tyomatkat;           // työmatkat (TravelUnit) erittelyyn
    vector <pair<CString, pair<int, int> > > m_id;   // Asiakkaiden/työntekijöiden id:t (yksi tulostettavaa asiakasta/työntekijää kohti)

    int m_mode;                                      // MODE_ASIAKKAAT, MODE_TYOMATKAT, MODE_TYOAJAT
	CString m_nayta;                                 // työajat vai tuotteet WorkType-taulusta
    BOOL m_sivutus;                                  // asiakkaat/työntekijät omille sivuilleen
    BOOL m_ylatunniste;
    BOOL m_alatunniste;
    BOOL m_ylapaivays;
    BOOL m_alapaivays;
    CString m_yhteenveto;
    BOOL m_kmkorvaus;
    int m_fontsize;
    CString m_fontname;
    CString m_strYlatunniste;
    CString m_strAlatunniste;
    CString m_yhdistatapahtumat;

    CString m_opt1;
    CString m_opt2;
    CString m_opt3;
    CString m_opt4;
    CString m_opt5;
	CComboBox m_cmbYhteenveto;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGERITTELY_H__6A637D25_1741_455F_95F3_D613F5D27E94__INCLUDED_)
