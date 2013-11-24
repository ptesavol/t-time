// DlgEtsi.cpp : implementation file
//

#include "stdafx.h"
#include "taika.h"
#include "DlgEtsi.h"
#include "Props.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEtsi dialog


DlgEtsi::DlgEtsi(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEtsi::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgEtsi)
	//}}AFX_DATA_INIT
    m_str_etsi = "";
}

void DlgEtsi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEtsi)
	DDX_Control(pDX, IDC_BTNETSI, m_btnEtsi);
	DDX_Control(pDX, IDC_LSTASIAKKAAT, m_lstAsiakkaat);
	DDX_Control(pDX, IDC_EDTETSI, m_edtEtsi);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgEtsi, CDialog)
	//{{AFX_MSG_MAP(DlgEtsi)
	ON_BN_CLICKED(IDC_BTNETSI, OnBtnetsi)
	ON_EN_CHANGE(IDC_EDTETSI, OnChangeEdtetsi)
	ON_LBN_SELCHANGE(IDC_LSTASIAKKAAT, OnSelchangeLstasiakkaat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEtsi message handlers
BOOL DlgEtsi::OnInitDialog() 
{
    int i, s;
    CString cs;

	CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGETSI_C1"));
	SetDlgItemText( IDC_STCAJAT, Props::i().lang("DLGETSI_C2"));
	SetDlgItemText(IDC_STATIC, Props::i().lang("DLGETSI_C3"));
	SetDlgItemText(IDC_STCINFO, Props::i().lang("DLGETSI_C4"));
	m_btnEtsi.SetWindowText(Props::i().lang("DLGETSI_C5"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGETSI_C6"));

    if(m_str_etsi != "")                             // vanhat asetukset
	{
      m_edtEtsi.SetWindowText(m_str_etsi);
      m_edtEtsi.SetSel(0, -1);
      m_btnEtsi.EnableWindow(TRUE);
	}
    else
	{
      m_edtEtsi.SetWindowText("");
      m_btnEtsi.EnableWindow(FALSE);
	}
    m_edtEtsi.SetFocus();

    m_lstAsiakkaat.ResetContent();                   // vanha hakutulos
    s = m_vect.size();
    for(i=0; i<s; i+=4)
	{
      cs.Format("%s%s%s", m_vect[i + 3], SEPARATOR, m_vect[i + 1]);
      m_lstAsiakkaat.AddString(cs);
	}
    m_count = s / 4;                                 // Nolla tai seta vanhan mukaan etsinnän indeksointi
    if(m_vect.size() == 0) m_pos = 0;
    if(m_lstAsiakkaat.SetCurSel(m_pos) == LB_ERR) m_pos = 0;

	return FALSE;
}

void DlgEtsi::OnChangeEdtetsi() 
{
    m_edtEtsi.GetWindowText(m_str_etsi);             // Etsi toimii vain kun tekstiä CEdit:ssä
    if(m_str_etsi != "") m_btnEtsi.EnableWindow(TRUE);
    else m_btnEtsi.EnableWindow(FALSE);

    m_lstAsiakkaat.ResetContent();                   // Tyhjennä CListBox
}

void DlgEtsi::OnBtnetsi() 
{
    int i, s;
    CString cs;
    DbSqlite db;
    vector <CString> vect;

    m_vect.clear();                                                                    // Vanhat pois
    m_lstAsiakkaat.ResetContent();

    if((s = (m_vect = db.etsi("WorkPlace", "id, Name, Region_id, CustomerNumber", 4, "Name", m_str_etsi, "Region_id")).size()) > 0)
	{
      for(i=0; i<s; i+=4)
	  {
        vect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", m_vect[i + 2]);
        if(vect.size() > 0 ) m_vect[i + 3] = vect[0]; else m_vect[i + 3] = _UNSET_;    // Talleta myös ryhmän nimi vektoriin
        cs.Format("%s%s%s", m_vect[i + 3], SEPARATOR, m_vect[i + 1]);
        m_lstAsiakkaat.AddString(cs);
	  }

      m_pos = 0;                                                                       // Nollaa etsinnän indeksointi
      m_count = s / 4;
      m_lstAsiakkaat.SetCurSel(0);
	}
    else this->FlashWindow(TRUE);
}

BOOL DlgEtsi::PreTranslateMessage(MSG* pMsg) 
{
    int sel;
    WPARAM wpar;

    if(pMsg->message == WM_KEYDOWN)
	{
      wpar = pMsg->wParam;

      if(wpar == VK_ESCAPE)                          // ESC painettu
        this->OnCancel();
      else if(wpar == VK_RETURN)                     // RETURNIN painettu
	  {
        sel = m_lstAsiakkaat.GetCurSel();

        if(m_btnEtsi.IsWindowEnabled() && sel == CB_ERR) // etsi uusi
          OnBtnetsi();
        else                                             // hyväksy valinta näytettäväksi
		{ m_pos = sel; this->OnOK(); }

        return TRUE;
	  }

      if(m_vect.size() > 0)
	  {
        if(wpar == VK_F3 || wpar == VK_DOWN)          // F3 tai VK_DOWN painettu
		{
          if(++m_pos == m_count) m_pos = 0;              // seuraava hakutuloksista
          m_lstAsiakkaat.SetCurSel(m_pos);

          return TRUE;
		}
        else if(wpar == VK_UP)                       // VK_UP painettu
		{
          if(--m_pos < 0) m_pos = m_count - 1;           // edellinen hakutuloksista
          m_lstAsiakkaat.SetCurSel(m_pos);

          return TRUE;
		}
	  }
	}

    return CDialog::PreTranslateMessage(pMsg);
}

void DlgEtsi::OnSelchangeLstasiakkaat() 
{
    if((m_pos = m_lstAsiakkaat.GetCurSel()) == LB_ERR) return;
    this->OnOK();
}

void DlgEtsi::OnOK()
{
    CDialog::OnOK();                                 // Poistu
}

void DlgEtsi::OnCancel() 
{
    CDialog::OnCancel();                             // Poistu
}

void DlgEtsi::clear()
{
    m_vect.clear();                                  // Nolla haku
    m_pos = 0;
    m_count = 0;
}