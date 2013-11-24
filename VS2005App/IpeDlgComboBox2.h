#if !defined(AFX_IPEDLGCOMBOBOX2_H__9D47E0A6_7854_48ED_9246_3800D6E9FF32__INCLUDED_)
#define AFX_IPEDLGCOMBOBOX2_H__9D47E0A6_7854_48ED_9246_3800D6E9FF32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IpeDlgComboBox2.h : header file
//
#include "Ipe.h"

/////////////////////////////////////////////////////////////////////////////
// IpeDlgComboBox2 dialog

class IpeDlgComboBox2 : public CDialog
{
// Construction
public:
	IpeDlgComboBox2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IpeDlgComboBox2)
	enum { IDD = IDD_DLGIPECOMBO2 };
	CComboBox	m_cmbOne;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IpeDlgComboBox2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IpeDlgComboBox2)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmbone();
	afx_msg void OnEditchangeCmbone();
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

#endif // !defined(AFX_IPEDLGCOMBOBOX2_H__9D47E0A6_7854_48ED_9246_3800D6E9FF32__INCLUDED_)
