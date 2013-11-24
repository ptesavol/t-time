#pragma once
#include "afxwin.h"
#include "ColorEdit.h"

// CDlgAbout dialog
class CDlgAbout : public CDialog
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAbout();

// Dialog Data
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

public:
	CColorEdit m_edtAbout;
};
