#if !defined(AFX_DLGPARSEINFO_H__61649B42_CB3A_4E2B_9030_80CBE277C293__INCLUDED_)
#define AFX_DLGPARSEINFO_H__61649B42_CB3A_4E2B_9030_80CBE277C293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParseInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgParseInfo dialog

class DlgParseInfo : public CDialog
{
// Construction
public:
	DlgParseInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgParseInfo)
	enum { IDD = IDD_DLGPARSE };
	CListCtrl	m_lstTiedostot;
	CStatic	m_stcEdistys;
	CButton	m_btnOK;
	CButton	m_btnLisaa;
	CStatic	m_stcInfo;
	CButton	m_chkParse;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgParseInfo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgParseInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnChkparse();
	afx_msg void OnDestroy();
	afx_msg void OnBtnlisaa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    void edistyminen(int);                           // seurataan parsimisen edistymist‰

    int m_como;                                      // Siirr‰/kopioi-tila
    int m_tila;                                      // : mist‰/mit‰ parsitaa (PARSE_SAAPUNEET, PARSE_FILES)
    CString m_path;                                  // :
    const char* m_lpcstr;                            // :
    int m_kaikki;                                    // parsittujen tietojen (rivit) kokonaism‰‰r‰
    int m_lisatty;                                   // joista onnistuneesti lis‰tty
    int m_samoja;                                    // joista samoja
    int m_ohitettu;                                  // joista ohitettu
    int m_virhe;                                     // joista ep‰onnistuneita
    CString m_virhe_str;                             // lyhyt virhekuvaus (muisti-, levy-, yms virhe numeraalisena)

    CWinThread *m_pCWinThread;
    friend UINT ThreadFunction(LPVOID);
    void AddFiles();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARSEINFO_H__61649B42_CB3A_4E2B_9030_80CBE277C293__INCLUDED_)
