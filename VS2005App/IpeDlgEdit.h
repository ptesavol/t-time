#if !defined(AFX_IPEDLGEDIT_H__067F7F7E_C833_4AD5_9E79_A67DBB200B92__INCLUDED_)
#define AFX_IPEDLGEDIT_H__067F7F7E_C833_4AD5_9E79_A67DBB200B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IpeDlgEdit.h : header file
//
#include "Ipe.h"

/////////////////////////////////////////////////////////////////////////////
// IpeDlgEdit dialog

class IpeDlgEdit : public CDialog
{
// Construction
public:
	IpeDlgEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IpeDlgEdit)
	enum { IDD = IDD_DLGIPEEDIT };
	CEdit	m_edtOne;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IpeDlgEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IpeDlgEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdtone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    Ipe m_Ipe;                             // InPlaceEdit (viestintä)
    short m_dlgWidth;                     // Dialogin leveys/korkeus
    short m_dlgHeight;
	WPARAM m_lastKey;

    virtual void OnOK();
    virtual void OnCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPEDLGEDIT_H__067F7F7E_C833_4AD5_9E79_A67DBB200B92__INCLUDED_)
