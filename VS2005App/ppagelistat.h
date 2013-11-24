#if !defined(AFX_PPAGELISTAT_H__587F6A27_14F3_484C_9A0B_7215F0CDA47B__INCLUDED_)
#define AFX_PpageListat_H__587F6A27_14F3_484C_9A0B_7215F0CDA47B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpageListat.h : header file
//
#include "ListctrlRaportit.h"
#include "GenericChildDialog.h"
#include "DlgUusiAsiakas.h"
#include "DlgUusiTuote.h"
#include "DlgUusiTyotyyppi.h"
#include "DlgUusiLaskuttaja.h"

/////////////////////////////////////////////////////////////////////////////
// PpageListat dialog
class PpageListat : public CRHGenericChildDialog //public CPropertyPage
{
	//DECLARE_DYNCREATE(PpageListat)

// Construction
public:
	PpageListat();
	~PpageListat();

// Dialog Data
	//{{AFX_DATA(PpageListat)
	enum { IDD = IDD_LISTAT_PROPP };
	CStatic	m_stcSep2;
	ListctrlRaportit m_lstTuotteet;
	ListctrlRaportit m_lstTuoteryhmat;
	CSpinButtonCtrl	m_spn_2;
	CSpinButtonCtrl	m_spn_1;
	CButton	m_btnLisaa_2;
	CButton	m_btnLisaa_1;
	CButton	m_btnPoista_2;
	CButton	m_btnPoista_1;
	CTabCtrl	m_tabL;
	CButton	m_btnEtsi;
	CButton	m_btnPoisAsiakasRyhma;
	CSpinButtonCtrl	m_spnLaskuttajat;
	CSpinButtonCtrl	m_spnAsiakkaat;
	CSpinButtonCtrl	m_spnAsiakasryhmat;
	ListctrlRaportit	m_lstTyotyypit;
	ListctrlRaportit	m_lstLaskuttajat;
	CButton	m_btnSiirra;
	CButton	m_btnPoisAsiakas;
	CButton	m_btnLisAsiakasRyhma;
	CButton	m_btnLisAsiakas;
	ListctrlRaportit m_lstAsiakkaat;
	ListctrlRaportit m_lstAsiakasryhmat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PpageListat)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PpageListat)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnlisAsiakasRyhma();
	afx_msg void OnBtnlisAsiakas();
	afx_msg void OnBtnpoisAsiakas();
	afx_msg void OnBtnpoisAsiakasRyhma();
	afx_msg void OnItemchangedLstasiakasryhmat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSiirra();
	afx_msg void OnDeltaposSpnasiakasryhmat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpnasiakkaat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpn_2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnlisaa_1();
	afx_msg void OnBtnpoista_1();
	afx_msg void OnBtnlisaa_2();
	afx_msg void OnBtnpoista_2();
	afx_msg void OnBtnetsi();
	afx_msg void OnDeltaposSpn_1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedLsttuoteryhmat(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
    afx_msg LRESULT OnKickIdle(WPARAM wparam, LPARAM lparam);  // ON_UPDATE_COMMAND_UI
    afx_msg void OnUpdatePoistaValittuAsiakasRyhma(CCmdUI* pCmdUI);
    afx_msg void OnUpdatePoistaValitutAsiakkaat(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSiirraValitutAsiakkaat(CCmdUI* pCmdUI);
    afx_msg void OnUpdatePoistaValittuLaskuttaja(CCmdUI* pCmdUI);
    afx_msg void OnUpdatePoistaValittuTyotyyppi(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSpinAsiakasryhmat(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSpinAsiakkaat(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSpin_1(CCmdUI* pCmdUI);
    afx_msg void OnUpdateSpin_2(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	virtual int CRHGetDialogID() { return IDD; };
    void windowSize();
    void lisaa();
    void poista();
    void lisaaAsiakasRyhma();
    void lisaaAsiakas(int mode);
	int  lisaaAsiakas(DlgUusiAsiakas *pd);
    void poistaAsiakasRyhma();
    void poistaAsiakas();
    void siirraAsiakasRyhmaan();
    void lisaaLaskuttaja(int mode);
	int  lisaaLaskuttaja(DlgUusiLaskuttaja *pd);
    void poistaLaskuttaja();
    void lisaaTyotyyppi(int mode);
	int  lisaaTyotyyppi(DlgUusiTyotyyppi *pd);
    void poistaTyotyyppi();
    void lisaaTuoteryhma();
    void poistaTuoteryhma();
    void lisaaTuote(int mode);
	int  lisaaTuote(DlgUusiTuote *pd);
    void poistaTuote();
    void valitseKaikki();
    void muokkaaAsiakasRyhma(CRect, RECT, ItemData_region*, LVHITTESTINFO);
    void muokkaaAsiakas(CRect, RECT, ItemData_workplace*, LVHITTESTINFO);
    void muokkaaLaskuttaja(CRect, RECT, ItemData_biller*, LVHITTESTINFO);
    void muokkaaTyotyyppi(CRect, RECT, ItemData_type*, LVHITTESTINFO);
    void muokkaaTuoteryhma(CRect, RECT, ItemData_productgroup*, LVHITTESTINFO);
    void muokkaaTuotteet(CRect, RECT, ItemData_type*, LVHITTESTINFO);
    void paivitaAsiakasryhmat(CString region, BOOL antiloop);
    void paivitaAsiakkaat(CString name);
    void paivitaLaskuttajat(CString name);
    void paivitaTyotyypit(CString name);
    void paivitaTuoteryhmat(CString productgroup, BOOL antiloop);
    void paivitaTuotteet(CString name);
    void naytaEdit(ListctrlRaportit*);
    void deltapos(CString table, CString id_srce, CString group_id, CString group_field, CString field, int top_position, int direction, int old_list_pos, ListctrlRaportit *pLst);
    void movepos(int srce, int dest, ListctrlRaportit *pLst);
    void email();
    void etsi(int key);
    void paivitaTila();
	void setView();
    int importListat();
	CMenu * createMenu();

    BOOL m_updRegions;                               // Estetään viestien turhaa kiertoa
    BOOL m_updProductgroups;

    CBitmap m_bmpEtsi;                               // Etsi-nappulan bitmap

	CString m_showType;                              // Listojen näyttö typin mukaan
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGELISTAT_H__587F6A27_14F3_484C_9A0B_7215F0CDA47B__INCLUDED_)
