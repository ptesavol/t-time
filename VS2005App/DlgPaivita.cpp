// DlgPaivita.cpp : implementation file
//

#include "stdafx.h"
#include "taika.h"
#include "DlgPaivita.h"
#include "Props.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgPaivita dialog


DlgPaivita::DlgPaivita(CWnd* pParent /*=NULL*/)
	: CDialog(DlgPaivita::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgPaivita)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgPaivita::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgPaivita)
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_PIC, m_stcPic);
	DDX_Control(pDX, IDC_STCVANHAT, m_stcVanhat);
	DDX_Control(pDX, IDC_STCUUDET, m_stcUudet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgPaivita, CDialog)
	//{{AFX_MSG_MAP(DlgPaivita)
	ON_BN_CLICKED(IDC_YES, OnYes)
	ON_BN_CLICKED(IDC_YESTOALL, OnYestoall)
	ON_BN_CLICKED(IDC_NOTOALL, OnNotoall)
	ON_BN_CLICKED(IDC_NOT, OnNot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgPaivita message handlers
void DlgPaivita::OnYes() 
{ EndDialog(R_YES); }

void DlgPaivita::OnYestoall() 
{ EndDialog(R_YESTA); }

void DlgPaivita::OnNot() 
{ EndDialog(R_NO); }

void DlgPaivita::OnNotoall() 
{ EndDialog(R_NOTA); }

BOOL DlgPaivita::OnInitDialog() 
{
    CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGPAIVITA_C1"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("DLGPAIVITA_C2"));
	SetDlgItemText(IDC_STATIC6, Props::i().lang("DLGPAIVITA_C3"));
	SetDlgItemText(IDC_YES, Props::i().lang("DLGPAIVITA_C4"));
	SetDlgItemText(IDC_YESTOALL, Props::i().lang("DLGPAIVITA_C5"));
	SetDlgItemText(IDC_NOT, Props::i().lang("DLGPAIVITA_C6"));
	SetDlgItemText(IDC_NOTOALL, Props::i().lang("DLGPAIVITA_C7"));

    int i,s;
    CString cs;

    if(m_mode == UPDATE_ASIAKAS)
      m_stcInfo.SetWindowText(Props::i().lang("DLGPAIVITA_1"));
    else if(m_mode == UPDATE_LASKUTTAJA)
      m_stcInfo.SetWindowText(Props::i().lang("DLGPAIVITA_2"));
    else if(m_mode == UPDATE_TYOTYYPPI)
      m_stcInfo.SetWindowText(Props::i().lang("DLGPAIVITA_3"));
    else if(m_mode == UPDATE_TUOTE)
      m_stcInfo.SetWindowText(Props::i().lang("DLGPAIVITA_4"));

    m_stcPic.SetIcon(LoadIcon(NULL, IDI_EXCLAMATION));

    for(i=0, s = m_vect_v.size(); i<s; i++)
      cs += m_vect_v[i] + "\r\n";
    m_stcVanhat.SetWindowText(cs);
    
    cs = "";
	for(i=0, s = m_vect_u.size(); i<s; i++)
      cs += m_vect_u[i] + "\r\n";
    m_stcUudet.SetWindowText(cs);

    return TRUE;
}

BOOL DlgPaivita::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)  // Estetään RETURNIN JA ESCAPEN painaminen dialogissa (dialogi ei sulkeudu vahingossa)
	{
      if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}