// DlgMoving.cpp : implementation file
#include "stdafx.h"
#include "DlgMoving.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgMoving dialog
DlgMoving::DlgMoving(CWnd* pParent /*=NULL*/)
	: CDialog(DlgMoving::IDD, pParent), m_pold_cbm(NULL)
{
	//{{AFX_DATA_INIT(DlgMoving)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgMoving::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgMoving)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgMoving, CDialog)
	//{{AFX_MSG_MAP(DlgMoving)
	ON_WM_CLOSE()
    ON_WM_PAINT()
    ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgMoving message handlers
BOOL DlgMoving::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL DlgMoving::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void DlgMoving::OnClose() { this->DestroyWindow(); }
void DlgMoving::OnOK() { this->DestroyWindow(); }
void DlgMoving::OnCancel() { this->DestroyWindow(); }
void DlgMoving::OnDestroy()
{
	void *p = (HBITMAP)m_pold_cbm;

	if(m_pold_cbm != NULL)                           // unselect created objects from the context
	{ m_cdc.SelectObject(m_pold_cbm); m_pold_cbm = NULL; }

	if(m_cdc.GetSafeHdc() != NULL)                   // destroy the context
		m_cdc.DeleteDC();
}

void DlgMoving::OnPaint()
{
	CPaintDC dc(this);

	if(m_cdc.GetSafeHdc() != NULL)
		dc.BitBlt(0, 0, m_cx, m_cy, &m_cdc, 0, 0, SRCCOPY);
}

/** ** ** ** ** ** ** ** ** ** **  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/
void DlgMoving::initDC(int cx, int cy, CDC *pImageCDC)
{ // Create compatible bitmap and device context and copy items image to the context
	CBitmap cbm;

	try
	{
		if(!cbm.CreateCompatibleBitmap(pImageCDC, cx, cy)) throw(0);
		if(!m_cdc.CreateCompatibleDC(pImageCDC)) throw(0);
		if((m_pold_cbm = m_cdc.SelectObject(&cbm)) == NULL) throw(0);
		m_cdc.BitBlt(0, 0, cx, cy, pImageCDC, 0, 0, SRCCOPY);
	}
	catch(...)
	{}

	m_cx = cx;
	m_cy = cy;

	cbm.DeleteObject();
}