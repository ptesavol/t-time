#if !defined(AFX_IPEDLGCOMBOBOX_H__F160CD66_30EF_4CF4_96A4_7F0E7B094B37__INCLUDED_)
#define AFX_IPEDLGCOMBOBOX_H__F160CD66_30EF_4CF4_96A4_7F0E7B094B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IpeDlgComboBox.h : header file
//
#include "Ipe.h"

/////////////////////////////////////////////////////////////////////////////
// IpeDlgComboBox dialog
class IpeDlgComboBox : public CDialog
{
// Construction
public:
	IpeDlgComboBox(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IpeDlgComboBox)
	enum { IDD = IDD_DLGIPECOMBO };
	CComboBox	m_cmbOne;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IpeDlgComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IpeDlgComboBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmbone();
	afx_msg void OnCloseupCmbone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    Ipe m_Ipe;                             // InPlaceEdit (viestintä)
    boolean m_cancel;					   // salli/estä OnCloseupCmbone()-funktion toiminto
	WPARAM m_lastKey;

    virtual void OnOK();
    virtual void OnCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPEDLGCOMBOBOX_H__F160CD66_30EF_4CF4_96A4_7F0E7B094B37__INCLUDED_)
