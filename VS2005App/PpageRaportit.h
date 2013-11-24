#if !defined(AFX_PPAGERAPORTIT_H__9302C730_C726_4112_99AE_3A841185B884__INCLUDED_)
#define AFX_PPAGERAPORTIT_H__9302C730_C726_4112_99AE_3A841185B884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpageRaportit.h : header file
//
#include "ListctrlRaportit.h"
#include "DbSqlite.h"
#include "defines.h"
#include "Paivays.h"
#include "GenericChildDialog.h"
#include "DlgLaskutus.h"
#include "DlgErittely.h"
#include "afxcmn.h"
#include "DlgUusiRaportti.h"

/////////////////////////////////////////////////////////////////////////////
// PpageRaportit dialog

class PpageRaportit  : public CRHGenericChildDialog //public CPropertyPage
{
	//DECLARE_DYNCREATE(PpageRaportit)

// Construction
public:
	PpageRaportit();
	~PpageRaportit();

// Dialog Data
	//{{AFX_DATA(PpageRaportit)
	enum { IDD = IDD_RAPORTIT_PROPPAGE };
	CStatic	m_stcReport;
	CStatic	m_stcSep5;
	CStatic	m_stcSep4;
	CStatic	m_stcSep3;
	CStatic	m_stcSep2;
	CStatic	m_stcSep1;
	CButton	m_btnYhtMore;
	CButton	m_btnValMore;
	CStatic	m_stcValitut;
	CButton	m_btnEtsi;
	CButton	m_btnLaskuta;
	CButton	m_btnPaattyen;
	CButton	m_btnAlkaen;
	CStatic	m_stcAjat;
	CComboBox	m_cmbAika;
	CButton	m_btnErittely;
	CButton	m_btnPoistaValitut;
	CButton	m_btnLisaaUusi;
	CButton	m_chkTyotyypit;
	CButton	m_chkTyontekijat;
	CButton	m_chkAsiakkaat;
	CButton	m_chkAsiakasryhmat;
	CListBox	m_lstTyotyypit;
	CListBox	m_lstTyontekijat;
	CListBox	m_lstAsiakasryhmat;
	CListBox	m_lstAsiakkaat;
	ListctrlRaportit	m_lstTyoajat;
	ListctrlRaportit	m_lstMyynnit;
	ListctrlRaportit	*m_plstRaportit;
	CDateTimeCtrl	m_dtpPaattyen;
	CDateTimeCtrl	m_dtpAlkaen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PpageRaportit)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PpageRaportit)
	afx_msg void OnSelchangeLstasiakas();
	afx_msg void OnChktyotyypit();
	afx_msg void OnChkasiakasryhmat();
	afx_msg void OnChkasiakkaat();
	afx_msg void OnChktyontekijat();
	afx_msg void OnSelchangeLstasiakasryhma();
	afx_msg void OnSelchangeLsttyotyyppi();
	afx_msg void OnSelchangeLsttyontekija();
	afx_msg void OnDatetimechangeDtpalkaen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDtppaattyen(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnRdlaskutus();
	afx_msg void OnBtnlisaauusi();
	afx_msg void OnBtnpoistavalitut();
	afx_msg void OnBtnerittely();
	afx_msg void OnSelchangeCmbaika();
	afx_msg void OnBtnalkaen();
	afx_msg void OnBtnpaattyen();
	afx_msg void OnBtnlaskuta();
	afx_msg void OnDestroy();
	afx_msg void OnBtnetsi();
	afx_msg void OnRadnayta();
	afx_msg void OnItemchangedLstraportti(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnvalmore();
	afx_msg void OnBtnyhtmore();
	//}}AFX_MSG
    afx_msg LRESULT OnKickIdle(WPARAM wparam, LPARAM lparam);  // ON_UPDATE_COMMAND_UI
    afx_msg void OnUpdatePoistaValitut(CCmdUI* pCmdUI);
    afx_msg void OnUpdateLaskuta(CCmdUI* pCmdUI);
    afx_msg void OnUpdateErittely(CCmdUI* pCmdUI);
    afx_msg void OnUpdateValInfo(CCmdUI* pCmdUI);
    afx_msg void OnUpdateYhtInfo(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	virtual int CRHGetDialogID() { return IDD; };
    void windowSize();
	void OnSelchangeLstasiakasryhma(BOOL sel, BOOL haku);// Lisätään parametri jolla määritetään valitaanko asiakkaat
	void paivitaAARListat(CString asiakas, ItemData *pid, BOOL haku);
    void paivitaTyontekijat(CString tyontekija, ItemData *pid, BOOL haku);
    void paivitaTyotyyppi(CString tyotyyppi, ItemData *pid, BOOL haku);
    void paivitaPaivays(int type, CString, ItemData *pid, BOOL haku);
	void palautaValitut(DWORD id, CListBox *pCListBox);
    void lisaaTapahtuma(int mode);
	int  lisaaTapahtuma(DlgUusiRaportti *pd);
    void poistaItems();
    void valitseKaikki();
    void laskutaValitut();
    void laskutaKaikkiNaytetyt();
    void laskutaAsiakas();
	void laskutettu(int mode);
    void eritteleNaytetytTyot();
    void eritteleValitutTyot();
    void eritteleValitutAsiakasTyot();
    void eritteleNaytetytTyoajat();
    void eritteleValitutTyoajat();
    void eritteleValitutTyontekijaTyoajat();
    //void email();
    void etsi(int key);
    void laskeAjat();
	void PpageRaportit::onkoTyontekijaListassa(CString nimi, CString id);
    void muokkaaTapahtuma(CRect, RECT, ItemData*, LVHITTESTINFO);
    void columnHit(int iItem, int iSubItem);
    void uusiHaku(ItemData *pid);
    BOOL haeItemDataList(vector <ItemData*> *pvect, int mode);
    void vapautaItemDataLists(vector <ItemData*> *pvect, vector <ItemData*> *pvectT, int mode);
    int getMode();
	CMenu * createMenu();

    int m_laskutus;                        // näytetäänkö laskutetut/laskuttamattomat/kaikki (CHARGED/UNCHARGED/ALLREPORTS)
    CString m_nayta;                       // näytetäänkö työajat/myynnit
    int m_ajat;                            // ajat minuutteina/tunteina

    BOOL m_haku;                           // TRUE, jos haku ehdoilla mahdollistettu

    CBitmap m_bmpEtsi;                     // Etsi-nappulan ja Info- ja kalenteri-nappuloiden bitmapit
    CBitmap m_bmpInfo;
    CBitmap m_bmpCalendar;

    DlgLaskutus m_DlgLaskutus;
    DlgErittely m_DlgErittely;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGERAPORTIT_H__9302C730_C726_4112_99AE_3A841185B884__INCLUDED_)
