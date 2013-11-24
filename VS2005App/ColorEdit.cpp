// ColorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "taika.h"
#include "ColorEdit.h"

// CColorEdit
IMPLEMENT_DYNAMIC(CColorEdit, CEdit)

CColorEdit::CColorEdit()
{
	m_crTx = RGB(0, 0, 0);
	m_crBk = RGB(255, 255, 255);
	m_pBkBrush = new CBrush(m_crBk);
}

CColorEdit::~CColorEdit()
{}

BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CColorEdit message handlers
void CColorEdit::OnDestroy()
{
	CEdit::OnDestroy();

	delete m_pBkBrush;
}

HBRUSH CColorEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_crTx);
	pDC->SetBkColor(m_crBk);
	return *m_pBkBrush;
}

void CColorEdit::SetColors(COLORREF bkRGB, COLORREF txRGB)
{
	m_crBk = bkRGB;
	if(m_pBkBrush->GetSafeHandle())
		m_pBkBrush->DeleteObject();
	m_pBkBrush->CreateSolidBrush(bkRGB);

	m_crTx = txRGB;

	Invalidate(TRUE);
}