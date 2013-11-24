#if !defined(AFX_DLGLUOUUSITIETOKANTA_H__61040252_1493_4989_92E0_6A3BAE18ED8D__INCLUDED_)
#define AFX_DLGLUOUUSITIETOKANTA_H__61040252_1493_4989_92E0_6A3BAE18ED8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLuoUusiTietokanta.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLuoUusiTietokanta dialog

class CDlgLuoUusiTietokanta : public CDialog
{
// Construction
public:
	CDlgLuoUusiTietokanta(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLuoUusiTietokanta)
	enum { IDD = IDD_DLGLUOUUSITIETOKANTA };
	CButton	m_btnCancel;
	CButton	m_btnOK;
	CStatic	m_stcPathName;
	CButton	m_btnFolder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLuoUusiTietokanta)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLuoUusiTietokanta)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnfolder();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    CBitmap m_cbm;
    CString m_filename;
    CString m_path;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLUOUUSITIETOKANTA_H__61040252_1493_4989_92E0_6A3BAE18ED8D__INCLUDED_)
