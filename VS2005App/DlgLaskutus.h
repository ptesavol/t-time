#if !defined(AFX_DLGLASKUTUS_H__7C3BBEDE_4564_45AB_B72A_4D2F8B911BED__INCLUDED_)
#define AFX_DLGLASKUTUS_H__7C3BBEDE_4564_45AB_B72A_4D2F8B911BED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLaskutus.h : header file
//
#include "ColorStatic.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// DlgLaskutus dialog

class DlgLaskutus : public CDialog
{
// Construction
public:
	DlgLaskutus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgLaskutus)
	enum { IDD = IDD_DLGLASKUTA };
	CEdit	m_edtMaksuaika;
	CComboBox	m_cmbTila;
	CButton	m_btnLaskKaikki;
	CButton	m_btnErittely;
	CColorStatic	m_stcInfo;
	CDateTimeCtrl	m_dtpErapaiva;
	CListCtrl	m_lstAsiakkaat;
	CComboBox	m_cmbTili;
	CComboBox	m_cmbHinnat;
	CButton	m_chkKayntikerta;
	CButton	m_btnLaskValittu;
	CButton m_chkYhdistaTapahtumat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgLaskutus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgLaskutus)
	virtual BOOL OnInitDialog();
	afx_msg void OnChkkayntikerta();
	afx_msg void OnSelchangeCmbhinnat();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnItemchangedLstasiakkaat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnlaskkaikki();
	afx_msg void OnSelchangeCmbtila();
	afx_msg void OnChangeEdtmaksuaika();
	afx_msg void OnBtnlaskvalittu();
	afx_msg void OnBtnerittely();
	afx_msg void OnChkyhdistatapahtumat();
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CString m_kayntikerta;
    CString m_hinnat;
    CString m_laskutustila;
	CString m_yhdistatapahtumat;

    CString m_err_str;
public:
    int laskuta(CString workplace_id, CString customernumber, CString account, COleDateTime duedate, vector <CString> worktype_vect, int *l_ok);
    pair <int,int> haeTila(CString wp_id);
	void teeYhdiste();
    BOOL kopioi_m_tapahtumat();

	CString m_nayta;                                  // työaikoja vai tuotteita WorkType-taulusta
    vector <ItemData*> m_tapahtumat;                  // Laskutettavien tapahtumien tiedot välitetään tätä kautta raporttisivulta
	vector <ItemData*> m_tapahtumat_laskutukseen;     // tähän valitaan kaikki tai yhdistetyt tapahtumat (m_yhdistatapahtumat tilan mukaan)
    vector <CString> m_workplace_id;                  // Tähän asetetaan asiakkaiden WorkUnit.WorkPlace_id:t (yksi asiakasta kohti)
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLASKUTUS_H__7C3BBEDE_4564_45AB_B72A_4D2F8B911BED__INCLUDED_)
