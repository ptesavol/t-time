#if !defined(AFX_COLORLISTCTRL_H__50AE96DB_62D4_43A2_85E0_E3019D9928A7__INCLUDED_)
#define AFX_COLORLISTCTRL_H__50AE96DB_62D4_43A2_85E0_E3019D9928A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl window
#define COLOR                              0x00FFE0C1
#define WHITE                              0x00FFFFFF
#define SELECTED                           0x00C56A31
#define NOFOCUS                            0x00D8ECEC

class CColorListCtrl : public CListCtrl
{
// Construction
public:
	CColorListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorListCtrl)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLISTCTRL_H__50AE96DB_62D4_43A2_85E0_E3019D9928A7__INCLUDED_)
