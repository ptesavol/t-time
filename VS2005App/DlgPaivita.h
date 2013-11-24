#if !defined(AFX_DLGPAIVITA_H__28FC3B1D_62CB_4BB1_AE4D_B9A5AC3E4DDF__INCLUDED_)
#define AFX_DLGPAIVITA_H__28FC3B1D_62CB_4BB1_AE4D_B9A5AC3E4DDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPaivita.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgPaivita dialog

class DlgPaivita : public CDialog
{
// Construction
public:
	DlgPaivita(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgPaivita)
	enum { IDD = IDD_DLGPAIVITA };
	CStatic	m_stcInfo;
	CStatic	m_stcPic;
	CStatic	m_stcVanhat;
	CStatic	m_stcUudet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgPaivita)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgPaivita)
	virtual BOOL OnInitDialog();
	afx_msg void OnYes();
	afx_msg void OnYestoall();
	afx_msg void OnNotoall();
	afx_msg void OnNot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    vector <CString> m_vect_v;
    vector <CString> m_vect_u;

    int m_mode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPAIVITA_H__28FC3B1D_62CB_4BB1_AE4D_B9A5AC3E4DDF__INCLUDED_)
