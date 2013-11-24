// taikaDlg.h : header file
//
#if !defined(AFX_TAIKADLG_H__A05B1C1E_5C98_44B7_A714_2840A2DC21D6__INCLUDED_)
#define AFX_TAIKADLG_H__A05B1C1E_5C98_44B7_A714_2840A2DC21D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PpageRaportit.h"
#include "PpageListat.h"
#include "PpageTyomatkat.h"

/////////////////////////////////////////////////////////////////////////////
// CTaikaDlg dialog
class CTaikaDlg : public CDialog
{
// Construction
public:
	CTaikaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTaikaDlg)
	enum { IDD = IDD_TAIKA_DIALOG };
	CTabCtrl	m_tabMain;
	CStatic	m_picPlaceHolder;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaikaDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual void OnOK();
    virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTaikaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnAvaaRaportti();
	afx_msg void OnTalletaRaportti();
	afx_msg void OnVarmuuskopioiTietokanta();
	afx_msg void OnVaihdaTietokanta();
	afx_msg void OnTalletaListat();
	afx_msg void OnAvaaListat();
	afx_msg void OnAvaaRaporttiTm();
	afx_msg void OnTalletaRaporttiTm();
	afx_msg void OnSiivoaTietokanta();
	afx_msg void OnEmail();
	afx_msg void OnAbout();
	afx_msg void OnValitsekaikki();
	afx_msg void OnAvaa();
	afx_msg void OnTalleta();
	afx_msg void OnEtsi();
	afx_msg void OnEtsiF3();
	afx_msg void OnPoista();
	afx_msg void OnUusi();
	afx_msg void OnSelchangeTabmain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
	afx_msg void OnAsetukset();
	afx_msg void OnLuoUusiTietokanta();
	afx_msg void OnImport();
	afx_msg void OnTuoLaskutusohjelmasta();
	afx_msg void OnPaivitaV5();
	//}}AFX_MSG
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    afx_msg LRESULT OnMsgUusiRaportti(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()

public:
    void luoKansiot(CString app_path);
    void setRaporttiMenu(UINT nIndex);
    void setListatMenu(UINT nIndex);
	void paivitaNaytot(BOOL date, BOOL select, BOOL database, int type);
	void syncListat(int from, int type);
    void usedDB();
	BOOL poista();

	PpageRaportit pageRaportit;
    PpageListat pageListat;
    PpageTyomatkat pageTyomatkat;

    CMenu *m_pMenu;                                    // Menu

    int m_mainShowMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAIKADLG_H__A05B1C1E_5C98_44B7_A714_2840A2DC21D6__INCLUDED_)
