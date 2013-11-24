#if !defined(AFX_LISTCTRLRAPORTIT_H__64C52AAE_74E5_428B_89D3_A2C7079B2FD3__INCLUDED_)
#define AFX_LISTCTRLRAPORTIT_H__64C52AAE_74E5_428B_89D3_A2C7079B2FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListctrlRaportit.h : header file
//
#include "defines.h"
#include "AFXOLE.H"
#include "DlgMoving.h"

/////////////////////////////////////////////////////////////////////////////
// ListctrlRaportit window
class ListctrlRaportit : public CListCtrl
{
// Construction
public:
	ListctrlRaportit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ListctrlRaportit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ListctrlRaportit();

	// Generated message map functions
protected:
	//{{AFX_MSG(ListctrlRaportit)
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEndTrack(NMHDR* pNmhdr, LRESULT* pResult);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  // Siirtoon
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg LRESULT OnMsgTabNappain(WPARAM wparam, LPARAM lparam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
    int m_omistaja;                        // O_TYOAJAT, O_MYYNNIT,  O_ASIAKASRYHMA, O_ASIAKAS, O_LASKUTTAJA, O_TYOTYYPPI, O_TUOTE, O_TUOTERYHMA, O_TRAVEL
	CString m_props;

public:                                    // Siirrtoon tarvittavat muuttujat ja metodit
    void aloitaSiirto(CPoint point);
    void paataSiirto(CPoint point, BOOL cancelled);
    void siirra(CPoint point);
    LVHITTESTINFO itemHiirenKohdalla(CPoint point);

	LVHITTESTINFO m_hti;
    BOOL m_allowMoving;
	BOOL m_moving;
    int m_header_height;
    int m_item_height;
    int m_item_width;
    int m_client_width;
    int m_client_height;
    DlgMoving DlgMoving;

    BOOL m_allowDeleteItemData;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLRAPORTIT_H__64C52AAE_74E5_428B_89D3_A2C7079B2FD3__INCLUDED_)
