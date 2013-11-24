// DlgSiirraAsiakkaat.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DlgSiirraAsiakkaat.h"
#include "DbSqlite.h"
#include "Props.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSiirraAsiakkaat dialog
DlgSiirraAsiakkaat::DlgSiirraAsiakkaat(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSiirraAsiakkaat::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSiirraAsiakkaat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void DlgSiirraAsiakkaat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSiirraAsiakkaat)
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_LSTASIAKKAAT, m_lstAsiakkaat);
	DDX_Control(pDX, IDC_LSTASIAKASRYHMAT, m_lstAsiakasryhma);
	DDX_Control(pDX, IDC_BTNSIIRRA, m_btnSiirra);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgSiirraAsiakkaat, CDialog)
	//{{AFX_MSG_MAP(DlgSiirraAsiakkaat)
	ON_LBN_SELCHANGE(IDC_LSTASIAKASRYHMAT, OnSelchangeLstasiakasryhmat)
	ON_BN_CLICKED(IDC_BTNSIIRRA, OnBtnsiirra)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSiirraAsiakkaat message handlers
BOOL DlgSiirraAsiakkaat::OnInitDialog() 
{
    int i, s;
    CString cs;
    DbSqlite db;
    vector <CString> vect;

	CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGSIIRRASIAKKAAT_C1"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("DLGSIIRRASIAKKAAT_C2"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGSIIRRASIAKKAAT_C3"));
	SetDlgItemText(IDC_BTNSIIRRA, Props::i().lang("DLGSIIRRASIAKKAAT_C4"));
	SetDlgItemText(IDOK, Props::i().lang("DLGSIIRRASIAKKAAT_C5"));

    s = m_asiakkaat.size();                          // Siirrett‰v‰t asiakkaat listaan
    for(i=0; i<s; i++)
	{
      vect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", m_asiakkaat[i]->Region_id);
      cs.Format("%s%s%s", vect[0], SEPARATOR, m_asiakkaat[i]->Name);
      m_lstAsiakkaat.AddString(cs);
      m_asiakkaat[i]->kasitelty = FALSE;
	}
	                                                 // Asiakasryhm‰t listaan
    s = (vect = db.haeTaulusta("Region", "Name", 1, "position", 1, "",  "Name", "<>", m_region)).size();
    for(i=0; i<s; i++)
      m_lstAsiakasryhma.AddString(vect[i]);
    OnSelchangeLstasiakasryhmat();

    return TRUE;
}

BOOL DlgSiirraAsiakkaat::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)  // Estet‰‰n RETURNIN painaminen dialogissa (dialogi ei sulkeudu vahingossa)
	{ if(pMsg->wParam == VK_RETURN) return TRUE; }
	
	return CDialog::PreTranslateMessage(pMsg);
}


void DlgSiirraAsiakkaat::OnSelchangeLstasiakasryhmat() 
{
    int s;

    if((s = m_lstAsiakasryhma.GetCurSel()) == LB_ERR)
      m_btnSiirra.EnableWindow(FALSE);
    else
      m_btnSiirra.EnableWindow(TRUE);
}

void DlgSiirraAsiakkaat::OnBtnsiirra() 
{
    DbSqlite db;
    int i, s, r = 0, p = 1;
    CString cs, region;
    vector <CString> vect, vectm;

    if((s = m_lstAsiakasryhma.GetCurSel()) == LB_ERR) return;        // Hae kohde asiakasryhm‰n nimi
    m_lstAsiakasryhma.GetText(s, region);
    if(region == "") return;
    if((vect = db.haeTaulusta("Region", "id", 1, "", 1, "", "Name", "=", region)).size() == 0) return;

    vectm = db.haeTaulusta("WorkPlace", "max(position)", 1, "", 1, "", WORKPLACE_REGION_ID, "=", vect[0]);
	if(vectm.size() != 0) p = atoi(vectm[0]) + 1;

    if((s = m_asiakkaat.size()) == 0) return;                        // Muuta regionit asiakkaisiin, position listan loppuun
    for(i=0; i<s; i++)
	{
      cs.Format("%d", p++);
      m_asiakkaat[i]->kasitelty = db.paivitaYleinen_id("WorkPlace", WORKPLACE_REGION_ID, vect[0], "", "", m_asiakkaat[i]->id, FALSE);
      m_asiakkaat[i]->kasitelty = db.paivitaYleinen_id("WorkPlace", WORKPLACE_POSITION, cs, "", "", m_asiakkaat[i]->id, FALSE);
	}

	// Korjaa l‰hde asikasryhm‰n positionit 1...
	db.jarjestaPosition("WorkPlace", "Region_id", m_asiakkaat[0]->Region_id, "position", TRUE);

    m_lstAsiakkaat.ResetContent();                                   // Disabloi kontrollit, n‰yt‰ tilanne
    m_btnSiirra.EnableWindow(FALSE);
    m_lstAsiakasryhma.EnableWindow(FALSE);
    for(i=0; i<s; i++)
	{
      vect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", m_asiakkaat[i]->Region_id); // vanha regionin nimi

      if(m_asiakkaat[i]->kasitelty == RETURN_OK)
	  { r++; cs.Format(Props::i().lang("DLGSIIRRASIAKKAAT_1"), vect[0], SEPARATOR, m_asiakkaat[i]->Name, region); }
      else if(m_asiakkaat[i]->kasitelty == RETURN_EXISTS)
        cs.Format(Props::i().lang("DLGSIIRRASIAKKAAT_2"), vect[0], SEPARATOR, m_asiakkaat[i]->Name, region);
      else if(m_asiakkaat[i]->kasitelty == RETURN_EXISTS)
        cs.Format(Props::i().lang("DLGSIIRRASIAKKAAT_3"), vect[0], SEPARATOR, m_asiakkaat[i]->Name);

      m_lstAsiakkaat.AddString(cs);
	}

    if(r == s)                                        // OK, n‰ytet‰‰n palatessa kohderegion
	{
      m_region = region;
	  m_stcInfo.SetWindowText((m_asiakkaat.size() > 1 ? Props::i().lang("DLGSIIRRASIAKKAAT_4") : Props::i().lang("DLGSIIRRASIAKKAAT_5")) + Props::i().lang("DLGSIIRRASIAKKAAT_6"));
	}
    else                                             // Virheen sattuessa, n‰ytet‰‰n entinen region
	{
      m_region = "";
      m_stcInfo.SetWindowText(r == 0 ? Props::i().lang("DLGSIIRRASIAKKAAT_7") : Props::i().lang("DLGSIIRRASIAKKAAT_8"));
	}
}
