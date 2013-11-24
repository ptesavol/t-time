// IpeDlgEdit.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "IpeDlgEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IpeDlgEdit dialog
IpeDlgEdit::IpeDlgEdit(CWnd* pParent /*=NULL*/)
	: CDialog(IpeDlgEdit::IDD, pParent), m_lastKey(0)
{
	//{{AFX_DATA_INIT(IpeDlgEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void IpeDlgEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IpeDlgEdit)
	DDX_Control(pDX, IDC_EDTONE, m_edtOne);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(IpeDlgEdit, CDialog)
	//{{AFX_MSG_MAP(IpeDlgEdit)
	ON_EN_CHANGE(IDC_EDTONE, OnChangeEdtone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IpeDlgEdit message handlers
BOOL IpeDlgEdit::OnInitDialog() 
{
    RECT rect;

    CDialog::OnInitDialog();

    // Dialogin ja CEditin koko ja sijainti Ipe-luokasta
    this->SetWindowPos(NULL, m_Ipe.x, m_Ipe.y, m_Ipe.w, m_Ipe.h, SWP_NOZORDER);
    m_edtOne.SetWindowPos(NULL, 0, 0, m_Ipe.w, m_Ipe.h, SWP_NOZORDER|SWP_NOMOVE);

    // alusta CEdit
    m_edtOne.SetFocus();
    m_edtOne.SetWindowText(m_Ipe.getString());
    m_edtOne.SetSel(0, -1, TRUE);

    // Varmista, että tila on editoimaton tässä vaiheessa
    m_Ipe.unEdited();

    // Nappaa hiiri ja hae dialogin koko (modaalisen dialogin ulkopuolella klikattu -> sulje dialogi)
    SetCapture();                                    // Hiiren viestit
    this->GetWindowRect(&rect);                      // Dialogin koko
    m_dlgWidth = rect.right - rect.left;
    m_dlgHeight = rect.bottom- rect.top;

	return FALSE;
}

void IpeDlgEdit::OnOK()
{
    // Palauta hiiri
    ReleaseCapture();

    CDialog::OnOK();
}

void IpeDlgEdit::OnCancel() 
{
    // Palauta hiiri
    ReleaseCapture();

    m_Ipe.unEdited();
	CDialog::OnCancel();
}

BOOL IpeDlgEdit::PreTranslateMessage(MSG* pMsg) 
{
    UINT mes = pMsg->message;

    if(mes == WM_KEYDOWN)                            // Napataan Enter, Escape ja Tab
	{
	  int shift = ((GetKeyState(VK_SHIFT) & 0x8000) ? 2 : 0);

      if(pMsg->wParam == VK_RETURN)
        this->OnOK();														//
      else if(pMsg->wParam == VK_ESCAPE)
        this->OnCancel();													//
	  else if(pMsg->wParam == VK_TAB)
	  { m_Ipe.setTabbedOut(shift + 1); this->OnOK(); }						//
	}
    // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - 
    // Dialogin ulkopuolella klikkaaminen sulkee dialogin ja peruuttaa editoinnin
    if(mes == WM_LBUTTONDOWN)
	{
      short xPos = LOWORD(pMsg->lParam);
      short yPos = HIWORD(pMsg->lParam);
      if(xPos < 0 || yPos < 0) this->OnCancel();
      if(xPos > m_dlgWidth || yPos > m_dlgHeight) this->OnOK();
	}

    // Lähetä hiirelle kuuluvat viestit lapsikkunoille (täytyy olla parempikin tapa?)
    if(mes >= WM_MOUSEFIRST && mes <= WM_MOUSELAST)
	{
      SendMessageToDescendants(mes, pMsg->wParam, pMsg->lParam, FALSE, FALSE);
      SetCapture();
	}
    // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - 

	return CDialog::PreTranslateMessage(pMsg);
}

void IpeDlgEdit::OnChangeEdtone() 
{
    CString cs;

    m_edtOne.GetWindowText(cs);                          // Testi muuttui -> talleta
    m_Ipe.setString((LPCSTR)cs);
}
