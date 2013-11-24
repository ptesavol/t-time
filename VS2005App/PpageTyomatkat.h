#if !defined(AFX_PPAGETYOMATKAT_H__72E3D93A_D32A_43D2_92AC_C026C812FD68__INCLUDED_)
#define AFX_PPAGETYOMATKAT_H__72E3D93A_D32A_43D2_92AC_C026C812FD68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PpageTyomatkat.h : header file
//
#include "ListctrlRaportit.h"
#include "DlgErittely.h"
#include "GenericChildDialog.h"
#include "DlgUusiTyomatka.h"

/////////////////////////////////////////////////////////////////////////////
// PpageTyomatkat dialog

class PpageTyomatkat : public CRHGenericChildDialog //public CPropertyPage
{
	//DECLARE_DYNCREATE(PpageTyomatkat)

// Construction
public:
	PpageTyomatkat();
	~PpageTyomatkat();

// Dialog Data
	//{{AFX_DATA(PpageTyomatkat)
	enum { IDD = IDD_TYOMATKAT_PROPP };
	CStatic	m_stcSep4;
	CStatic	m_stcSep3;
	CStatic	m_stcSep2;
	CStatic	m_stcSep1;
	CStatic	m_stcValitut;
	CStatic	m_stcYhteensa;
	CEdit	m_edtkmKerroin;
	CButton	m_btnPoistaValitut;
	CButton	m_bntLisaaUusi;
	CButton	m_btnErittely;
	CListBox	m_lstTyontekijat;
	ListctrlRaportit	m_lstTyomatkat;
	CDateTimeCtrl	m_dtpPaattyen;
	CDateTimeCtrl	m_dtpAlkaen;
	CButton	m_chkTyontekijat;
	CButton	m_btnPaattyen;
	CButton	m_btnAlkaen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PpageTyomatkat)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PpageTyomatkat)
	virtual BOOL OnInitDialog();
	afx_msg void OnDatetimechangeDtpalkaen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDtppaattyen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeLsttyontekijat();
	afx_msg void OnChktyontekijat();
	afx_msg void OnBtnalkaen();
	afx_msg void OnBtnpaattyen();
	afx_msg void OnBtnlisaauusi();
	afx_msg void OnBtnpoistavalitut();
	afx_msg void OnBtnerittely();
	afx_msg void OnChangeEdtkmkerroin();
	afx_msg void OnItemchangedLsttyomatkat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
    afx_msg LRESULT OnKickIdle(WPARAM wparam, LPARAM lparam);  // ON_UPDATE_COMMAND_UI
    afx_msg void OnUpdatePoistaValitut(CCmdUI* pCmdUI);
    afx_msg void OnUpdateErittely(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	virtual int CRHGetDialogID() { return IDD; };
    void windowSize();
    void uusiHaku(ItemData_travel *pid);
    void lisaaUusi(int mode);
	int  lisaaUusi(DlgUusiTyomatka *pd);
    void poistaValitut();
    void valitseKaikki();
    void muokkaaTyomatka(CRect cr, RECT rect, ItemData_travel *pid, LVHITTESTINFO hti);
    void columnHit(int iItem, int iSubItem);
    void eritteletNaytetytTyomatkat();
    void eritteleValitutTyomatkat();
    void eritteleValittujenTyomatkat();
    BOOL haeItemDataList(vector <ItemData_travel*> *pvect, int mode);
	void vapautaItemDataList(vector <ItemData_travel*> *pvect, int mode);
    void laskeMatkat();
    void paivitaTyontekijat(CString tyontekija, ItemData_travel *pid, BOOL haku);
    void paivitaPaivays(int type, CString date, ItemData_travel *pid, BOOL haku);
	CMenu * createMenu();

    DlgErittely m_DlgErittely;

    CBitmap m_bmpCalendar;                 // kalenteri-nappuloiden bitmap
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGETYOMATKAT_H__72E3D93A_D32A_43D2_92AC_C026C812FD68__INCLUDED_)
