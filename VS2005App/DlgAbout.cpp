// DlgAbout.cpp : implementation file
#include "stdafx.h"
#include "taika.h"
#include "DlgAbout.h"
#include "Props.h"

// CDlgAbout dialog
IMPLEMENT_DYNAMIC(CDlgAbout, CDialog)

CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/) : CDialog(CDlgAbout::IDD, pParent)
{}
CDlgAbout::~CDlgAbout()
{}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDTABOUT, m_edtAbout);
}

BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAbout message handlers
BOOL CDlgAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGABOUT_C1"));
	GetDlgItem(IDOK)->SetWindowText(Props::i().lang("DLGABOUT_C2"));

	CString cs;
	cs = Props::i().lang("DLGABOUT_1");
	cs += Props::i().lang("APPVERSION") + "\r\n\r\n";
	cs += Props::i().lang("DLGABOUT_2");
	cs += Props::i().lang("DLGABOUT_3");
	cs += Props::i().lang("DLGABOUT_4");
	cs += Props::i().lang("DLGABOUT_5");
	cs += Props::i().lang("DLGABOUT_6");
	cs += Props::i().lang("DLGABOUT_7");
	cs += Props::i().lang("DLGABOUT_8");

	m_edtAbout.SetWindowTextA(cs);
	m_edtAbout.SetColors(RGB(255, 255, 255), RGB(0, 0, 0));

	CDC *pDC = this->GetDC();
	pDC->SetBkColor(RGB(255, 255, 255));
	RedrawWindow();

	return TRUE;
}

BOOL CDlgAbout::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(255, 255, 255));    // dialog background color
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld);    // restore old brush

	return bRes;                       // CDialog::OnEraseBkgnd(pDC);
}