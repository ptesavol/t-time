#if !defined(AFX_DLGETSI_H__5E943F87_E0EE_48BF_BF38_18BF07D1F8B7__INCLUDED_)
#define AFX_DLGETSI_H__5E943F87_E0EE_48BF_BF38_18BF07D1F8B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEtsi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEtsi dialog
class DlgEtsi : public CDialog
{
// Construction
public:
	DlgEtsi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgEtsi)
	enum { IDD = IDD_DLGETSI };
	CButton	m_btnEtsi;
	CListBox	m_lstAsiakkaat;
	CEdit	m_edtEtsi;
	CButton	m_chkKokonaiset;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEtsi)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEtsi)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnetsi();
	afx_msg void OnChangeEdtetsi();
	afx_msg void OnSelchangeLstasiakkaat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    virtual void OnOK();
    virtual void OnCancel();

    void clear();                              // Nollaa haku

    CString m_str_etsi;

    vector <CString> m_vect;                   // Tulokst
    int m_count;                               // Tulosten m‰‰r‰ vektorissa
    int m_pos;                                 // Nykyinen [0, m_count[
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGETSI_H__5E943F87_E0EE_48BF_BF38_18BF07D1F8B7__INCLUDED_)
