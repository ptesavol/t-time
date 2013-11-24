// IpeDlgComboBox.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "IpeDlgComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IpeDlgComboBox dialog


IpeDlgComboBox::IpeDlgComboBox(CWnd* pParent /*=NULL*/)
	: CDialog(IpeDlgComboBox::IDD, pParent), m_lastKey(0)
{
	//{{AFX_DATA_INIT(IpeDlgComboBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void IpeDlgComboBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IpeDlgComboBox)
	DDX_Control(pDX, IDC_CMBONE, m_cmbOne);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IpeDlgComboBox, CDialog)
	//{{AFX_MSG_MAP(IpeDlgComboBox)
	ON_CBN_SELCHANGE(IDC_CMBONE, OnSelchangeCmbone)
	ON_CBN_CLOSEUP(IDC_CMBONE, OnCloseupCmbone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IpeDlgComboBox message handlers
BOOL IpeDlgComboBox::OnInitDialog() 
{
    CDialog::OnInitDialog();

    // Dialogin ja CComboBoxin koko ja sijainti Ipe-luokasta ja ComboBoxin listan korkeudesta
    RECT rect;
    m_cmbOne.GetClientRect(&rect);
    this->SetWindowPos(NULL, m_Ipe.x, m_Ipe.y, m_Ipe.w, rect.bottom - rect.top, SWP_NOZORDER);
    m_cmbOne.SetWindowPos(NULL, 0, 0, m_Ipe.w, rect.bottom - rect.top, SWP_NOZORDER|SWP_NOMOVE);

    // alusta CComboBox
    CString cs, sep;
    int i, j, s, row, i_cols, t_cols;
    vector<CString> *pvect;

	pvect = m_Ipe.getVector();                       // Vektorista alkioita valikkoon
    t_cols = m_Ipe.getCols();                        // sarakkeita
    if(!m_Ipe.isItemData()) i_cols = t_cols;
    else i_cols = t_cols - 1;
	row  = pvect->size() / t_cols;                   // rivejä
    sep = m_Ipe.getSeparator();                      // erotin sarakkeiden välille

    for(i=0; i<row; i++)                             // Rivejä
	{
      cs = "";
      for(j=0; j<i_cols; j++)                            // niissä sarakkeita
	  {
        cs += pvect->at(i*t_cols + j);
        if(j + 1 < i_cols) cs += sep;
	  }
      s = m_cmbOne.AddString(cs);
      if(m_Ipe.isItemData())                             // lisää tarvittaessa ItemData
        m_cmbOne.SetItemData(s, atoi(pvect->at(i*t_cols + j)));
	}      

    m_cmbOne.SetFocus();
    m_cmbOne.ShowDropDown(TRUE);
    if((row = m_cmbOne.FindString(0, m_Ipe.getString())) != CB_ERR)  // Valitaan teksti valikosta jos löytyy
      m_cmbOne.SetCurSel(row);

    if((s = m_cmbOne.GetCurSel()) != CB_ERR) m_Ipe.setItemData((m_cmbOne.GetItemData(s)));
    else m_Ipe.setItemData(ITDA_ERR);

    // Varmista, että tila on editoimaton tässä vaiheessa
    m_Ipe.unEdited();

	// Salli OnCloseupCmbone()-funktion toiminto
	m_cancel = true;

    return FALSE;                          // Focus asetettu -> palauta FALSE
}

void IpeDlgComboBox::OnOK()
{
    CDialog::OnOK();
}

void IpeDlgComboBox::OnCancel() 
{
    m_Ipe.unEdited();
    CDialog::OnCancel();
}

BOOL IpeDlgComboBox::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)                  // Napataan Enter, Escape ja Tab
	{
	  m_lastKey = pMsg->wParam;
	  int shift = ((GetKeyState(VK_SHIFT) & 0x8000) ? 2 : 0);

      if(pMsg->wParam == VK_RETURN)
	  { m_cancel = false;this->OnOK(); }									//
      else if(pMsg->wParam == VK_ESCAPE)
        this->OnCancel();													//
	  else if(pMsg->wParam == VK_TAB)
	  { m_cancel = false; m_Ipe.setTabbedOut(shift + 1); this->OnOK(); }	//
	}

    return CDialog::PreTranslateMessage(pMsg);
}

void IpeDlgComboBox::OnSelchangeCmbone() 
{
    int s;
    CString cs;

    m_cmbOne.GetWindowText(cs);                          // Teksti muuttui -> talleta
    m_Ipe.setString((LPCSTR)cs);

    if((s = m_cmbOne.GetCurSel()) != CB_ERR) m_Ipe.setItemData(m_cmbOne.GetItemData(s));
    //else m_Ipe.setItemData(ITDA_ERR);

	if(m_lastKey != VK_DOWN && m_lastKey != VK_UP) OnOK();	// salli drop downing selaus
	m_lastKey = 0;
}

void IpeDlgComboBox::OnCloseupCmbone() 
{ // Painettu ListBoxin ulkopuolella -> ei valintaa -> dialogi kiinni
    if(m_cancel) this->OnCancel();
}