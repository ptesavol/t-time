#if !defined(AFX_DLGMOVING_H__6AFF4C76_8789_40F4_B62E_58F56BFCB742__INCLUDED_)
#define AFX_DLGMOVING_H__6AFF4C76_8789_40F4_B62E_58F56BFCB742__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMoving.h : header file
//

#include "taika.h"
#include "defines.h"

/////////////////////////////////////////////////////////////////////////////
// DlgMoving dialog
class DlgMoving : public CDialog
{
// Construction
public:
	DlgMoving(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgMoving)
	enum { IDD = IDD_DLGMOVING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgMoving)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnOK();
    virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgMoving)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
    afx_msg void OnPaint();
    afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    void initDC(int cx, int cy, CDC *pImageCDC);

    CDC m_cdc;
	CBitmap *m_pold_cbm;
    int m_cx;
	int m_cy;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOVING_H__6AFF4C76_8789_40F4_B62E_58F56BFCB742__INCLUDED_)
