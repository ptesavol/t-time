// IpeDlgComboBox2.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "IpeDlgComboBox2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IpeDlgComboBox2 dialog
IpeDlgComboBox2::IpeDlgComboBox2(CWnd* pParent /*=NULL*/)
	: CDialog(IpeDlgComboBox2::IDD, pParent), m_lastKey(0)
{
	//{{AFX_DATA_INIT(IpeDlgComboBox2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void IpeDlgComboBox2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IpeDlgComboBox2)
	DDX_Control(pDX, IDC_CMBONE, m_cmbOne);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(IpeDlgComboBox2, CDialog)
	//{{AFX_MSG_MAP(IpeDlgComboBox2)
	ON_CBN_SELCHANGE(IDC_CMBONE, OnSelchangeCmbone)
	ON_CBN_EDITCHANGE(IDC_CMBONE, OnEditchangeCmbone)
	ON_CBN_CLOSEUP(IDC_CMBONE, OnCloseupCmbone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IpeDlgComboBox2 message handlers
BOOL IpeDlgComboBox2::OnInitDialog() 
{
    CDialog::OnInitDialog();

    // Dialogin ja CComboBoxin koko ja sijainti Ipe-luokasta ja ComboBoxin listan korkeudesta
    RECT rect;
    m_cmbOne.GetClientRect(&rect);
    this->SetWindowPos(NULL, m_Ipe.x, m_Ipe.y, m_Ipe.w, rect.bottom - rect.top, SWP_NOZORDER);
    m_cmbOne.SetWindowPos(NULL, 0, 0, m_Ipe.w, rect.bottom - rect.top, SWP_NOZORDER|SWP_NOMOVE);

    // alusta CComboBox
    CString cs, sep;
    int i, j, row, col;
    vector<CString> *pvect;
	
	pvect = m_Ipe.getVector();                       // Vektorista alkioita valikkoon
    col = m_Ipe.getCols();                           // sarakkeita
	row  = pvect->size() / col;                      // rivejä
    sep = m_Ipe.getSeparator();                      // erotin sarakkeiden välille

    for(i=0; i<row; i++)                                 // Rivejä
	{
      cs = "";
      for(j=0; j<col; j++)                                 // niissä sarakkeita
	  {
        cs += pvect->at(i*col + j);
        if(j + 1 < col) cs += sep;
	  }
      m_cmbOne.AddString(cs);
	}      

    m_cmbOne.SetFocus();
    m_cmbOne.ShowDropDown(TRUE);
    m_cmbOne.SetWindowText(m_Ipe.getString());                       // asetetaan vielä teksti - jos FindString ei löydäkään nimeä listasta
    if((row = m_cmbOne.FindString(0, m_Ipe.getString())) != CB_ERR)  // Valitaan teksti valikosta jos löytyy
      m_cmbOne.SetCurSel(row);
    m_cmbOne.SetEditSel(0, -1);                                      // Teksti valituksi

    // Varmista, että tila on editoimaton tässä vaiheessa
    m_Ipe.unEdited();

	// Salli OnCloseupCmbone()-funktion toiminto
	m_cancel = true;

    return FALSE;                          // Focus asetettu -> palauta FALSE
}

void IpeDlgComboBox2::OnOK()
{
    CDialog::OnOK();
}

void IpeDlgComboBox2::OnCancel() 
{
    m_Ipe.unEdited();
    CDialog::OnCancel();
}

BOOL IpeDlgComboBox2::PreTranslateMessage(MSG* pMsg) 
{
    UINT mes = pMsg->message;

    if(pMsg->message == WM_KEYDOWN)                  // Napataan Enter, Escape ja Tab
	{
	  m_lastKey = pMsg->wParam;
	  int shift = ((GetKeyState(VK_SHIFT) & 0x8000) ? 2 : 0);

      if(pMsg->wParam == VK_RETURN)
	  { m_cancel = false; this->OnOK(); }									//
      else if(pMsg->wParam == VK_ESCAPE)
        this->OnCancel();													//
	  else if(pMsg->wParam == VK_TAB)
	  { m_cancel = false; m_Ipe.setTabbedOut(shift + 1); this->OnOK(); }	//
	}

    return CDialog::PreTranslateMessage(pMsg);
}

void IpeDlgComboBox2::OnSelchangeCmbone() 
{
    CString cs;

    m_cmbOne.GetLBText(m_cmbOne.GetCurSel(), cs);			// Teksti muuttui -> talleta
    m_Ipe.setString((LPCSTR)cs);

	if(m_lastKey != VK_DOWN && m_lastKey != VK_UP) OnOK();	// salli drop downing selaus
	m_lastKey = 0;
}

void IpeDlgComboBox2::OnEditchangeCmbone() 
{
    CString cs;

    m_cmbOne.GetWindowText(cs);                          // Teksti muuttui -> talleta
    m_Ipe.setString((LPCSTR)cs);
}

void IpeDlgComboBox2::OnCloseupCmbone() 
{ // Painettu ListBoxin ulkopuolella -> ei valintaa -> dialogi kiinni
    if(m_cancel) this->OnCancel();
}
