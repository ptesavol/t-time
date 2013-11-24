// DlgLaskutus.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DlgLaskutus.h"
#include "defines.h"
#include "Paivays.h"
#include "Props.h"
#include "AccountingProgramWrapper.h"
#include "AccountingException.h"
#include "BdeException.h"
#include "DlgErittely.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgLaskutus dialog


DlgLaskutus::DlgLaskutus(CWnd* pParent /*=NULL*/)
	: CDialog(DlgLaskutus::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgLaskutus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgLaskutus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgLaskutus)
	DDX_Control(pDX, IDC_EDTMAKSUAIKA, m_edtMaksuaika);
	DDX_Control(pDX, IDC_CMBTILA, m_cmbTila);
	DDX_Control(pDX, IDC_BTNLASKKAIKKI, m_btnLaskKaikki);
	DDX_Control(pDX, IDC_BTNERITTELY, m_btnErittely);
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_DTPERAPAIVA, m_dtpErapaiva);
	DDX_Control(pDX, IDC_LSTASIAKKAAT, m_lstAsiakkaat);
	DDX_Control(pDX, IDC_CMBTILI, m_cmbTili);
	DDX_Control(pDX, IDC_CMBHINNAT, m_cmbHinnat);
	DDX_Control(pDX, IDC_CHKKAYNTIKERTA, m_chkKayntikerta);
	DDX_Control(pDX, IDC_BTNLASKVALITTU, m_btnLaskValittu);
	DDX_Control(pDX, IDC_CHKYHDISTATAPAHTUMAT, m_chkYhdistaTapahtumat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgLaskutus, CDialog)
	//{{AFX_MSG_MAP(DlgLaskutus)
	ON_BN_CLICKED(IDC_CHKKAYNTIKERTA, OnChkkayntikerta)
	ON_CBN_SELCHANGE(IDC_CMBHINNAT, OnSelchangeCmbhinnat)
	ON_WM_TIMER()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTASIAKKAAT, OnItemchangedLstasiakkaat)
	ON_BN_CLICKED(IDC_BTNLASKKAIKKI, OnBtnlaskkaikki)
	ON_CBN_SELCHANGE(IDC_CMBTILA, OnSelchangeCmbtila)
	ON_EN_CHANGE(IDC_EDTMAKSUAIKA, OnChangeEdtmaksuaika)
	ON_BN_CLICKED(IDC_BTNLASKVALITTU, OnBtnlaskvalittu)
	ON_BN_CLICKED(IDC_BTNERITTELY, OnBtnerittely)
	ON_BN_CLICKED(IDC_CHKYHDISTATAPAHTUMAT, &DlgLaskutus::OnChkyhdistatapahtumat)
	ON_BN_CLICKED(IDOK, &DlgLaskutus::OnBnClickedOk)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgLaskutus message handlers
BOOL DlgLaskutus::OnInitDialog() 
{
    CRect cr;
    DbSqlite db;
    Paivays paivays;
    COleDateTime odt;
    vector <CString> wp_vect;
    vector <CString> r_vect;
    pair<int,int> day_pari;
    vector <CString> day_vect;
    pair<string, string> ba_pari;
    CString cs, wp_id, ap_path;
    vector<pair<string,string> > ba_vect;
    int i, j, s, t, sel, count;
    vector <ItemData*> tvect;

	CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGLASKUTUS_C1"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("DLGLASKUTUS_C2"));
	SetDlgItemText(IDC_BTNLASKKAIKKI, Props::i().lang("DLGLASKUTUS_C3"));
	SetDlgItemText(IDC_BTNLASKVALITTU, Props::i().lang("DLGLASKUTUS_C4"));
	SetDlgItemText(IDC_BTNERITTELY, Props::i().lang("DLGLASKUTUS_C5"));
	SetDlgItemText(IDC_CHKKAYNTIKERTA, Props::i().lang("DLGLASKUTUS_C6"));
	SetDlgItemText(IDC_CHKYHDISTATAPAHTUMAT, Props::i().lang("DLGLASKUTUS_C7"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("DLGLASKUTUS_C8"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("DLGLASKUTUS_C9"));
	SetDlgItemText(IDC_STATIC4, Props::i().lang("DLGLASKUTUS_C10"));
	SetDlgItemText(IDC_STATIC6, Props::i().lang("DLGLASKUTUS_C11"));
	SetDlgItemText(IDOK, Props::i().lang("DLGLASKUTUS_C12"));

    // Värillinen tausta info-tekstille. Oletuksena taustan värinen.
	m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), "");        

	ListView_SetExtendedListViewStyleEx(m_lstAsiakkaat.GetSafeHwnd(),  // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_lstAsiakkaat.GetClientRect(&cr);                                // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstAsiakkaat.InsertColumn(0, Props::i().lang("DLGLASKUTUS_1") , LVCFMT_LEFT, (int)(cr.right * 0.25), -1);
    m_lstAsiakkaat.InsertColumn(1, Props::i().lang("DLGLASKUTUS_2"), LVCFMT_LEFT, (int)(cr.right * 0.08), -1);
    m_lstAsiakkaat.InsertColumn(2, Props::i().lang("DLGLASKUTUS_3"), LVCFMT_LEFT, (int)(cr.right * 0.18), -1);
    m_lstAsiakkaat.InsertColumn(3, Props::i().lang("DLGLASKUTUS_4"), LVCFMT_LEFT, (int)(cr.right * 0.489), -1);

	kopioi_m_tapahtumat();                           // Tee kopio m_tapahtumat vektorista, , käytetään varsinaiseen laskutukseen

    if(Props::i().get(OPTIONS_LASKUTUSOHJELMA) != LAS_NONE)   // Laskutusohjelma asetettu
	{
      m_kayntikerta = Props::i().get(OPTIONS_KAYNTIKERTAVELOITUS).c_str();
      m_hinnat = Props::i().get(OPTIONS_HINNAT).c_str();
      m_laskutustila = Props::i().get(OPTIONS_LASKUTUSTILA).c_str();

      cs = Props::i().get(OPTIONS_LASKUNMAKSUAIKA).c_str();   // : eräpäivä / maksuaika
	  odt = COleDateTime::GetCurrentTime();
	  odt.m_dt += atof(cs);
      m_dtpErapaiva.SetTime(odt);
      m_edtMaksuaika.SetWindowText(cs);

      if(m_laskutustila == LTILA_KAIKKI)                 // : Laskunmaksutila
        m_cmbTila.SetCurSel(0);
      else if(m_laskutustila == LTILA_LASKUTTAMATTOMAT)
        m_cmbTila.SetCurSel(1);
      else if(m_laskutustila == LTILA_LASKUTETUT)
        m_cmbTila.SetCurSel(2);

      if(m_kayntikerta == C_FALSE)                       // : Käyntikertaveloitus
        m_chkKayntikerta.SetCheck(0);
      else
        m_chkKayntikerta.SetCheck(1);

      if(m_hinnat == HINNAT_LASKOHJ)                     // : Hinnat
        m_cmbHinnat.SetCurSel(0);
      else
        m_cmbHinnat.SetCurSel(1);

      AccountingProgramWrapper::open();                   // :: hae/aseta tilinumerot
      ba_vect = AccountingProgramWrapper::ap->getBankAccounts();
      for(i=0, j=ba_vect.size(); i<j; i++)
	  {
        ba_pari = ba_vect[i];
        cs.Format("%s: %s", ba_pari.first.c_str(), ba_pari.second.c_str());
        m_cmbTili.AddString((LPCSTR)cs);
	  }
      m_cmbTili.SetCurSel(0);
      AccountingProgramWrapper::close();                 // ::

      m_workplace_id.clear();                            // ::: Asiakkaiden WorkUnit.WorkPlace_id:t talteen (yksi asiakasta kohti)
      count = 0;                                         // ::: Asiakkaiden nimet (yksi nimi per asiakas), tapahtumien määrä
      tvect = m_tapahtumat;                              // :::  + Asiakasnumero ja tapahtumien aikaväli (ajalla, HUOM! ei ajalta) listaan
      if(!tvect.empty()) t = atoi(tvect[0]->WorkPlace_id);
      while(1)
	  {
        if(!tvect.empty())
		{ s = atoi(tvect[0]->WorkPlace_id); tvect[0]->kasitelty = FALSE; }   // seuraava id ja merkitse samalla käsittelemättömäksi
        else
          s = -1;

        if(s != t)
		{
          wp_id.Format("%d", t);	  
          m_workplace_id.push_back(wp_id);               // Talleta id

                                                         // Hae id:llä asiakkaan tiedot
          wp_vect = db.haeTaulusta("WorkPlace", "Name, CustomerNumber, Region_id", 3, "", 1, "", "id", "=", wp_id);
          r_vect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", wp_vect[2]);

          cs = r_vect[0] + SEPARATOR + wp_vect[0];
          i = m_lstAsiakkaat.GetItemCount();             // Asiakasryhmä - Asiakas
          sel = m_lstAsiakkaat.InsertItem(LVIF_TEXT, i, cs, 0, 0, 0, 0);

          m_lstAsiakkaat.SetItem(sel, 1, LVIF_TEXT, wp_vect[1], 0, 0, 0, 0); // Asiakasnumero

          day_pari = paivays.haeMinMax(day_vect);        // aloitus (min) <-> lopetus (max) päivät
          if(day_pari.first == day_pari.second)          // Ajalta
            cs = paivays.date2string(day_pari.first);
          else
            cs.Format("%s%s%s", paivays.date2string(day_pari.first), SEPARATOR, paivays.date2string(day_pari.second));
          m_lstAsiakkaat.SetItem(sel, 2, LVIF_TEXT, cs, 0, 0, 0, 0);

          pair <int,int> pari = haeTila(wp_id);
          cs.Format(Props::i().lang("DLGLASKUTUS_5"), count, count == 1 ? Props::i().lang("DLGLASKUTUS_6") : Props::i().lang("DLGLASKUTUS_7"), pari.second);
          m_lstAsiakkaat.SetItem(sel, 3, LVIF_TEXT, cs, 0, 0, 0, 0);

          t = s;                                         // alusta seuraava kierros
          count = 1;
          day_vect.clear();
          if(!tvect.empty()) day_vect.push_back(tvect[0]->StartDate);
		}
        else
		{
          count++;
          day_vect.push_back(tvect[0]->StartDate);
		}

        if(!tvect.empty()) tvect.erase(tvect.begin());   // seuraava elementti tai break kun lista on käyty läpi
        else break;
	  }

                                                         // :::: Yhdistetäänkö samalla tuotekoodilla olevat työajat/tapahtumat samalle riville laskussa
	  m_yhdistatapahtumat = Props::i().get(OPTIONS_YHDISTATAPAHTUMAT).c_str();
      if(m_yhdistatapahtumat == C_FALSE)
        m_chkYhdistaTapahtumat.SetCheck(0);
      else
        m_chkYhdistaTapahtumat.SetCheck(1);

	  teeYhdiste();                                      // ::::: Tee m_yhdistatapahtumat valinnan mukainen lista tapahtumista

      if(m_nayta == ID_WORKUNIT)                         // :::::: Oikea teksti tilan mukaan
        m_chkYhdistaTapahtumat.SetWindowText(Props::i().lang("DLGLASKUTUS_8"));
	  else
        m_chkYhdistaTapahtumat.SetWindowText(Props::i().lang("DLGLASKUTUS_9"));
	}
    else                                             // Laskutusohjelma asettamatta
	{
      m_btnLaskKaikki.EnableWindow(FALSE);
      m_btnLaskValittu.EnableWindow(FALSE);
      m_btnErittely.EnableWindow(FALSE);
      m_lstAsiakkaat.EnableWindow(FALSE);
      m_chkKayntikerta.EnableWindow(FALSE);
      m_cmbHinnat.EnableWindow(FALSE);
      m_cmbTili.EnableWindow(FALSE);
      m_chkKayntikerta.EnableWindow(FALSE);
	  m_chkYhdistaTapahtumat.EnableWindow(FALSE);
      m_dtpErapaiva.EnableWindow(FALSE);

      m_err_str = Props::i().lang("DLGLASKUTUS_10");
      SetTimer(0, 500, NULL);                            // vilkutetaan virhettä m_stcInfo-kotrollissa
	}

    return TRUE;
}

void DlgLaskutus::OnDestroy()
{
	CDialog::OnDestroy();

    // Vapauta muisti
    for(int i=0; i<m_tapahtumat_laskutukseen.size(); i++) delete m_tapahtumat_laskutukseen.at(i);
	m_tapahtumat_laskutukseen.clear();
}

BOOL DlgLaskutus::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)  // Estetään RETURNIN JA ESCAPEN  painaminen dialogissa (dialogi ei sulkeudu vahingossa)
	{
      if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void DlgLaskutus::OnTimer(UINT nIDEvent) 
{
    static int c = 0;
    CString cs;

    KillTimer(nIDEvent);

    if(c%2 > 0)  m_stcInfo.coloredInfo(LIGHTRED, m_err_str); // Vilkutetaan virhettä
    else m_stcInfo.coloredInfo(LIGHTRED, "");

    if(++c < 14) SetTimer(0, 500, NULL);                     // 14 kertaa laskuri käyntiin uudestaan
    else c = 0;                                              // ja pois n kerran jälkeen

	CDialog::OnTimer(nIDEvent);
}

void DlgLaskutus::OnChkkayntikerta() 
{
    CString cs;

    if(m_chkKayntikerta.GetCheck() == 0) m_kayntikerta = C_FALSE;
    else m_kayntikerta = C_TRUE;

    Props::i().set(OPTIONS_KAYNTIKERTAVELOITUS, (LPCSTR)m_kayntikerta);
}

void DlgLaskutus::OnChkyhdistatapahtumat()
{
    CString cs;

	if(m_chkYhdistaTapahtumat.GetCheck() == 0) m_yhdistatapahtumat = C_FALSE;
    else m_yhdistatapahtumat = C_TRUE;

    Props::i().set(OPTIONS_YHDISTATAPAHTUMAT, (LPCSTR)m_yhdistatapahtumat);

	teeYhdiste();                                    // Tee valinnan mukainen lista
}

void DlgLaskutus::OnSelchangeCmbhinnat() 
{
    int s;
    CString cs;

    if((s = m_cmbHinnat.GetCurSel()) != CB_ERR)
	{
      if(s == 0) m_hinnat = HINNAT_LASKOHJ;
      else m_hinnat = HINNAT_MATKAPUH;

      Props::i().set(OPTIONS_HINNAT, (LPCSTR)m_hinnat);
	}
}

void DlgLaskutus::OnSelchangeCmbtila() 
{
    int i, j;
    CString cs;
    pair <int,int> pari;

    if((i = m_cmbTila.GetCurSel()) != CB_ERR)
	{
      if(i == 0) m_laskutustila = LTILA_KAIKKI;
      else if(i == 1) m_laskutustila = LTILA_LASKUTTAMATTOMAT;
      else if(i == 2) m_laskutustila = LTILA_LASKUTETUT;

      Props::i().set(OPTIONS_LASKUTUSTILA, (LPCSTR)m_laskutustila);
	}

    // Muuta tilan teksti vastaamaan valintaa
    for(i=0, j=m_workplace_id.size(); i<j; i++)
	{
      pari = haeTila(m_workplace_id[i]);
      cs.Format(Props::i().lang("DLGLASKUTUS_5"), pari.first, pari.first == 1 ? Props::i().lang("DLGLASKUTUS_6") : Props::i().lang("DLGLASKUTUS_7"), pari.second);
      m_lstAsiakkaat.SetItem(i, 3, LVIF_TEXT, cs, 0, 0, 0, 0);
	}
}

void DlgLaskutus::OnItemchangedLstasiakkaat(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    // Enabloi tai disabloi painikkeet sen mukaan onko listassa valittuna itemi
    if(m_lstAsiakkaat.GetFirstSelectedItemPosition() == NULL)
      m_btnLaskValittu.EnableWindow(FALSE);
    else
      m_btnLaskValittu.EnableWindow(TRUE);

    // Enabloi tai disabloi painikkeet sen mukaan onko listassa itemejä
    if(m_lstAsiakkaat.GetItemCount() == 0)
      m_btnErittely.EnableWindow(FALSE);
    else
      m_btnErittely.EnableWindow(TRUE);

    *pResult = 0;
}

void DlgLaskutus::OnChangeEdtmaksuaika() 
{
    CString cs;
    COleDateTime odt;

    m_edtMaksuaika.GetWindowText(cs);
    Props::i().set(OPTIONS_LASKUNMAKSUAIKA, (LPCSTR)cs);

    odt = COleDateTime::GetCurrentTime();            // Uusi eräpäivä
    odt.m_dt += atof(cs);
    m_dtpErapaiva.SetTime(odt);
}

void DlgLaskutus::OnBtnerittely() 
{
    DlgErittely dlg;
    dlg.m_tapahtumat = m_tapahtumat;
    dlg.m_mode = MODE_ASIAKKAAT;
	dlg.m_nayta = m_nayta;
    dlg.DoModal();
}

void DlgLaskutus::OnBtnlaskkaikki() 
{ // Laskutetaan listan kaikki tapahtumat
    DbSqlite db;
    COleDateTime duedate;
    vector <CString> vect;
    vector <CString> worktype_vect;
    int i, j, r, l_ok, as;
    CString account, hinnat, laskohj, kertakaynti, cs;
    CString anim[8] = { "-", " -", "  -", "   -", "    -", "   -", "  -", " -" };

    try
	{                                                // Hae kaikki työtyypit
      if((worktype_vect = db.haeTaulusta("WorkType", "DISTINCT id, ProductNumber", 2, "", 0)).size() == 0) throw(ERR_WORKTYPE);

      m_dtpErapaiva.GetTime(duedate);                // Epäpäivä

      i = m_cmbTili.GetCurSel();                     // Ota account mjonosta vain tilinumero
      if(i == CB_ERR) throw(ERR_ACCOUNT);
      m_cmbTili.GetLBText(i, account);
      j = account.GetLength();
      for(i=0; i<j; i++) { if(account[i] == ':') break; }
      account = account.Right(j-i-2);

      j = m_workplace_id.size();                     // Ota laskutettavien asiakkaiden määrä, nollaa näytettävä laskuri
      as = 0;
      this->EnableWindow(FALSE);                     // estetään nappuloiden painelu
      m_lstAsiakkaat.SetFocus();                     // aseta focus

      while(!m_workplace_id.empty())                 // LASKUTETAAN ASIAKASKOHTAISESTI KAIKKI ANNETUT TAPAHTUMAT
	  {
        cs.Format(Props::i().lang("DLGLASKUTUS_11"), j > 1 ? Props::i().lang("DLGLASKUTUS_12") : Props::i().lang("DLGLASKUTUS_13"), ++as, j, anim[as%8]);
        m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), cs); // päivitetään näytettävää laskuria

        if((vect = db.haeTaulusta("WorkPlace", "CustomerNumber", 1, "", 1, "", "id", "=", m_workplace_id[0])).size() == 0) throw(ERR_CUSTOMERNUMBER);

        l_ok = 0;                                        // laskuta asiakas
        if((r = laskuta(m_workplace_id[0], vect[0], account, duedate, worktype_vect, &l_ok)) != RETURN_OK) throw(r);

        m_lstAsiakkaat.DeleteItem(0);                    // : poistetaan käsitellyt listasta
	    m_workplace_id.erase(m_workplace_id.begin());    // : ja vektorista

        m_lstAsiakkaat.SetItem(0, 0, LVIF_STATE, 0, 0, LVIS_SELECTED, LVIS_SELECTED, 0);
        m_lstAsiakkaat.EnsureVisible(0, FALSE);
	  }

      m_stcInfo.coloredInfo(LIGHTGREEN, j > 1 ? Props::i().lang("DLGLASKUTUS_14") : Props::i().lang("DLGLASKUTUS_15"));
      this->EnableWindow(TRUE);
      m_btnLaskKaikki.EnableWindow(FALSE);               // Nappulat pois käytöstä, koska lista tyhjä
      m_btnLaskValittu.EnableWindow(FALSE);
      m_btnErittely.EnableWindow(FALSE);
      m_lstAsiakkaat.EnableWindow(FALSE);
      m_cmbTila.EnableWindow(FALSE);
	}
    catch(int err)
	{
      this->EnableWindow(TRUE);

      if(err == ERR_MEMORYERR1) m_err_str = Props::i().lang("DLGLASKUTUS_16");
      else if(err == ERR_ACCOUNT) m_err_str = Props::i().lang("DLGLASKUTUS_17");
      else if(err == ERR_WORKTYPE) m_err_str = Props::i().lang("DLGLASKUTUS_18");
      else if(err == ERR_CUSTOMERNUMBER) m_err_str = Props::i().lang("DLGLASKUTUS_19");
      SetTimer(0, 500, NULL);
	}
}

void DlgLaskutus::OnBtnlaskvalittu() 
{	
    DbSqlite db;
    COleDateTime duedate;
    vector <CString> vect;
    vector <CString> worktype_vect;
    int i, j, r;
    POSITION pos;
    CString account, hinnat, laskohj, kertakaynti, cs;

    try
	{                                                    // Hae kaikki työtyypit
      if((worktype_vect = db.haeTaulusta("WorkType", "DISTINCT id, ProductNumber", 2, "", 0)).size() == 0) throw(ERR_WORKTYPE);

      m_dtpErapaiva.GetTime(duedate);                    // Epäpäivä

      i = m_cmbTili.GetCurSel();                         // Ota account mjonosta vain tilinumero
      if(i == CB_ERR) throw(ERR_ACCOUNT);
      m_cmbTili.GetLBText(i, account);
      j = account.GetLength();
      for(i=0; i<j; i++) { if(account[i] == ':') break; }
      account = account.Right(j-i-2);

      m_stcInfo.coloredInfo(GetSysColor(COLOR_3DFACE), Props::i().lang("DLGLASKUTUS_20"));
      this->EnableWindow(FALSE);

      // LASKUTETAAN VALITUN ASIAKKAAN ANNETUT TAPAHTUMAT
      if(!(pos = m_lstAsiakkaat.GetFirstSelectedItemPosition())) throw(ERR_SELCUSTOMER);
      i = m_lstAsiakkaat.GetNextSelectedItem(pos); j = 0;

      if((vect = db.haeTaulusta("WorkPlace", "CustomerNumber", 1, "", 1, "", "id", "=", m_workplace_id[i])).size() == 0) throw(ERR_CUSTOMERNUMBER);
      if((r = laskuta(m_workplace_id[i], vect[0], account, duedate, worktype_vect, &j)) != RETURN_OK) throw(r);
      m_lstAsiakkaat.DeleteItem(i);                  // : poistetaan käsitellyt listasta
	  m_workplace_id.erase(m_workplace_id.begin() + i/*&m_workplace_id[i]*/);      // : ja vektorista

      m_stcInfo.coloredInfo(LIGHTGREEN, Props::i().lang("DLGLASKUTUS_21"));
      this->EnableWindow(TRUE);
      if(m_lstAsiakkaat.GetItemCount() == 0)
	  {
        m_btnLaskKaikki.EnableWindow(FALSE);         // Nappulat pois käytöstä, jos lista tyhjä
        m_btnLaskValittu.EnableWindow(FALSE);
        m_btnErittely.EnableWindow(FALSE);
        m_lstAsiakkaat.EnableWindow(FALSE);
        m_cmbTila.EnableWindow(FALSE);
	  }
	}
    catch(int err)
	{
      this->EnableWindow(TRUE);

      if(err == ERR_MEMORYERR1) m_err_str = Props::i().lang("DLGLASKUTUS_16");
      else if(err == ERR_ACCOUNT) m_err_str = Props::i().lang("DLGLASKUTUS_17");
      else if(err == ERR_WORKTYPE) m_err_str = Props::i().lang("DLGLASKUTUS_18");
      else if(err == ERR_CUSTOMERNUMBER) m_err_str = Props::i().lang("DLGLASKUTUS_19");
      else if(err == ERR_SELCUSTOMER) m_err_str = Props::i().lang("DLGLASKUTUS_22");
      SetTimer(0, 500, NULL);
	}

}

int DlgLaskutus::laskuta(CString workplace_id, CString customernumber, CString account, COleDateTime duedate, vector <CString> worktype_vect, int *l_ok)
{
    BOOL b, bvg;
    DbSqlite db;
    PriceComponent comp;
    vector <CString> vect;
    double total;
	vector<PriceComponent> units;
    int i, i_wt, s_wt, s_as, kertamaara, ret = RETURN_OK;
    CString cs, wtip;

    try
	{
      s_as = m_tapahtumat_laskutukseen.size();       // Annetut tapahtumat

      // LISÄTÄÄN KÄSITELTÄVÄN ASIAKKAAN KÄSITELTÄVÄN TYÖTYYPIN TYÖT HINTAKOMPONENTTIIN MATKAPUHELIMEN HINNOILLA
      if(m_hinnat == HINNAT_MATKAPUH)
      {
        s_wt = worktype_vect.size();
        for(i_wt=0; i_wt<s_wt; i_wt+=2)                // LASKUTUS TYÖTYYPEITTÄIN, MUTTA ERI TYÖTYYPPIEN TYÖT MENEE SAMALLE LASKULLE!!!
	    {
          for(i=0; i<s_as; i++)
		  {
            b = FALSE;
            if(m_tapahtumat_laskutukseen[i]->WorkPlace_id == workplace_id && m_tapahtumat_laskutukseen[i]->WorkType_id == worktype_vect[i_wt])
			{
              cs = m_tapahtumat_laskutukseen[i]->Charged;    // laskutustilan täsmättävä tapahtuman tilan kanssa
              if(m_laskutustila == LTILA_LASKUTTAMATTOMAT && cs == C_FALSE) b = TRUE;
              else if(m_laskutustila == LTILA_LASKUTETUT && cs == C_TRUE) b = TRUE;
              else if(m_laskutustila == LTILA_KAIKKI) b = TRUE;
			}

            if(b && m_tapahtumat_laskutukseen[i]->kasitelty == FALSE)  // käsitellään vain kerran joka tapauksessa!!!
			{
              comp.clear();                                  // Lisätään laskutettaviin
              comp.setUnit((LPCSTR)m_tapahtumat_laskutukseen[i]->Unit);
              comp.setAmount(atof(m_tapahtumat_laskutukseen[i]->UnitValue));
              comp.setUnitPrice(atof(m_tapahtumat_laskutukseen[i]->UnitPrice));
              comp.setTotalPrice(atof(m_tapahtumat_laskutukseen[i]->TotalPrice));
              comp.setProductId((LPCSTR)worktype_vect[i_wt + 1]);
			  comp.setWorktypeId((LPCSTR)worktype_vect[i_wt + 0]);
              comp.setVatPercent(atof(m_tapahtumat_laskutukseen[i]->Alv)/100.0f);
              comp.setDateTime(m_tapahtumat_laskutukseen[i]->StartDate, m_tapahtumat_laskutukseen[i]->StartTime, m_tapahtumat_laskutukseen[i]->EndDate, m_tapahtumat_laskutukseen[i]->EndTime);
              units.push_back(comp);
			}
		  }
		}
	  }
      // LISÄTÄÄN KÄSITELTÄVÄN ASIAKKAAN, KÄSITELTÄVÄN TYÖTYYPIN TYÖT HINTAKOMPONENTTIIN LASKUTUSOHJELMAN HINNOILLA
      else
      {
		AccountingProgramWrapper::open();              // HUOMIOIDAAN ALV-MUUTOKSET ELI TESTATAAN ONKO ALV-RYHMÄT KÄYTÖSSÄ
		bvg = AccountingProgramWrapper::ap->isVatGroup();
		AccountingProgramWrapper::close();

        s_wt = worktype_vect.size();
        for(i_wt=0; i_wt<s_wt; i_wt+=2)                // LASKUTUS TYÖTYYPEITTÄIN, MUTTA ERI TYÖTYYPPIEN TYÖT MENEE SAMALLE LASKULLE!!!
	    {
          // EI ALV-RYHMIÄ -> LISÄÄ KAIKKI SAMAN TYÖTYYPIN TYÖT SAMALLE RIVILLE LASKUUN (VANHA NEUVOSOHJELMAN TAPA)
		  if(!bvg)
		  {
            total = 0;                                     // uusi kierros
            kertamaara = 0;

            for(i=0; i<s_as; i++)
		    {
              b = FALSE;
              if(m_tapahtumat_laskutukseen[i]->WorkPlace_id == workplace_id && m_tapahtumat_laskutukseen[i]->WorkType_id == worktype_vect[i_wt])
		      {
                cs = m_tapahtumat_laskutukseen[i]->Charged;    // laskutustilan täsmättävä tapahtuman tilan kanssa
                if(m_laskutustila == LTILA_LASKUTTAMATTOMAT && cs == C_FALSE) b = TRUE;
                else if(m_laskutustila == LTILA_LASKUTETUT && cs == C_TRUE) b = TRUE;
                else if(m_laskutustila == LTILA_KAIKKI) b = TRUE;
		      }

              if(b && m_tapahtumat_laskutukseen[i]->kasitelty == FALSE)  // käsitellään vain kerran joka tapauksessa!!!
			  {
                if(m_tapahtumat_laskutukseen[i]->Unit == _UNIT_MIN_)       // Työajat
			    {
                  total += atof(m_tapahtumat_laskutukseen[i]->UnitValue) / 60.0f;   // työaika tunneiksi
                  kertamaara++;                                                     // kertamäärä
			    }
                else                                                       // Myynnin tapahtumat
                  total += atof(m_tapahtumat_laskutukseen[i]->UnitValue);
			  }
		    }

            if(m_kayntikerta == C_TRUE && kertamaara > 0)  // Käyntikertaveloitus
            {
              comp.clear();
              comp.setProductId((LPCSTR)worktype_vect[i_wt + 1]);
              comp.setWorktypeId((LPCSTR)worktype_vect[i_wt + 0]);
              comp.setAmount(kertamaara);
              units.push_back(comp);
		    }
            else if(total > 0)                             // Vain nollaa suuremmat laskutetaan
		    {
              comp.clear();
              comp.setProductId((LPCSTR)worktype_vect[i_wt + 1]);
              comp.setWorktypeId((LPCSTR)worktype_vect[i_wt + 0]);
              comp.setAmount(total);
              units.push_back(comp);
		    }
		  }
          // ALV-RYHMÄT KÄYTÖSSÄ -> KAIKKI TAPAHTUMAT ERIKSEEN, YHDISTELLÄÄN LASKUTUSVAIHEESSA TYÖTYYPEITTÄIN KÄYTTÄEN ALV-PROSENTTIA PERUSTEENA
		  else
		  {
            for(i=0; i<s_as; i++)
		    {
              b = FALSE;
              if(m_tapahtumat_laskutukseen[i]->WorkPlace_id == workplace_id && m_tapahtumat_laskutukseen[i]->WorkType_id == worktype_vect[i_wt])
		      {
                cs = m_tapahtumat_laskutukseen[i]->Charged;    // laskutustilan täsmättävä tapahtuman tilan kanssa
                if(m_laskutustila == LTILA_LASKUTTAMATTOMAT && cs == C_FALSE) b = TRUE;
                else if(m_laskutustila == LTILA_LASKUTETUT && cs == C_TRUE) b = TRUE;
                else if(m_laskutustila == LTILA_KAIKKI) b = TRUE;
		      }

              if(b && m_tapahtumat_laskutukseen[i]->kasitelty == FALSE)  // käsitellään vain kerran joka tapauksessa!!!
			  {
                if(m_tapahtumat_laskutukseen[i]->Unit == _UNIT_MIN_)       // Työajat
			    {
                  total = atof(m_tapahtumat_laskutukseen[i]->UnitValue) / 60.0f;   // työaika tunneiksi
                  kertamaara = 1;                                                  // kertamäärä
			    }
                else                                                       // Myynnin tapahtumat
                  total = atof(m_tapahtumat_laskutukseen[i]->UnitValue);

                if(m_kayntikerta == C_TRUE && kertamaara > 0)           // Käyntikertaveloitus
                {
                  comp.clear();
                  comp.setProductId((LPCSTR)worktype_vect[i_wt + 1]);
                  comp.setWorktypeId((LPCSTR)worktype_vect[i_wt + 0]);
                  comp.setAmount(kertamaara);
                  comp.setDateTime(m_tapahtumat_laskutukseen[i]->StartDate, m_tapahtumat_laskutukseen[i]->StartTime, m_tapahtumat_laskutukseen[i]->EndDate, m_tapahtumat_laskutukseen[i]->EndTime);
                  units.push_back(comp);
                }
                else if(total > 0)                                      // Vain nollaa suuremmat laskutetaan
		        {
                  comp.clear();
                  comp.setProductId((LPCSTR)worktype_vect[i_wt + 1]);
                  comp.setWorktypeId((LPCSTR)worktype_vect[i_wt + 0]);
                  comp.setAmount(total);
                  comp.setDateTime(m_tapahtumat_laskutukseen[i]->StartDate, m_tapahtumat_laskutukseen[i]->StartTime, m_tapahtumat_laskutukseen[i]->EndDate, m_tapahtumat_laskutukseen[i]->EndTime);
                  units.push_back(comp);
		        }

			  }
		    }
		  }

		}
      }

      if(units.size() > 0)     // LÄHETETÄÄN TIEDOT LASKUTUSOHJELMALLE, JOS JOTAIN LASKUTETTAVAA
      {
		cs = "";
		AccountingProgramWrapper::open();
		AccountingProgramWrapper::ap->createBill((LPCSTR)customernumber, units, (LPCSTR)account, duedate, (LPCSTR)cs, (LPCSTR)cs, (LPCSTR)m_hinnat);
        AccountingProgramWrapper::close();

		for(i_wt=0; i_wt<units.size(); i_wt++) // merkitään laskutetuiksi työtyypeittäin asikkaalle
		{
          wtip = ((PriceComponent)units.at(i_wt)).getWorktypeId().c_str();

          for(i=0; i<s_as; i++)                              // : merkitään käsiteltävän asiakkaan käsiteltävän työtyypin työt laskutetuiksi tietokantaan ja struktuuriin
	      {
            b = FALSE;
            if(m_tapahtumat_laskutukseen[i]->WorkPlace_id == workplace_id && m_tapahtumat_laskutukseen[i]->WorkType_id == wtip)
            {
              cs = m_tapahtumat_laskutukseen[i]->Charged;    // : mutta vain jos laskutustila täsmää tapahtuman tilan kanssa
              if(m_laskutustila == LTILA_LASKUTTAMATTOMAT && cs == C_FALSE) b = TRUE;
              else if(m_laskutustila == LTILA_LASKUTETUT && cs == C_TRUE) b = TRUE;
              else if(m_laskutustila == LTILA_KAIKKI) b = TRUE;
            }

            if(b)
            {
              CString moid = m_tapahtumat_laskutukseen[i]->WorkType_id; // palauta oikea WorkType_id tietokannan päivityksen ajaksi.
			  m_tapahtumat_laskutukseen[i]->WorkType_id = m_tapahtumat_laskutukseen[i]->oWorkType_id;
              if(db.paivitaWorkUnit(m_tapahtumat_laskutukseen[i], 1, "Charged", C_TRUE) == RETURN_OK)
              {
                m_tapahtumat_laskutukseen[i]->Charged = C_TRUE;   // laskutettu
                m_tapahtumat_laskutukseen[i]->kasitelty = TRUE;   // ja annettu tapahtuma käsitelty

                *l_ok += 1;                          // käsittelyjen lkm
			  }
              m_tapahtumat_laskutukseen[i]->WorkType_id = moid;
            }
		  }
		}

        units.clear();
      }
	}
    catch(int err)
	{
      ret = err;
	}
    catch (AccountingException& e)
	{
      m_err_str = Props::i().lang("DLGLASKUTUS_23"); m_err_str +=  e.getReason().c_str();
      ret = GEN_ERROR;
	} 
    catch (CBdeException* e)
	{
      m_err_str = Props::i().lang("DLGLASKUTUS_23") + e->GetErrorMessage(FALSE);
      e->Delete();
      ret = GEN_ERROR;
	}

    return ret;
}

pair <int,int> DlgLaskutus::haeTila(CString wp_id)
{ // Kuinka monta tapahtumaa tietyn asiakkaan tapahtumista vastaa nykyisestä laskutustilaa
    BOOL b;
    int i, j;
    CString cs;
    pair <int,int> pari;

    for(i=0, j=m_tapahtumat_laskutukseen.size(); i<j; i++)
	{
      b = FALSE;
      if(m_tapahtumat_laskutukseen[i]->WorkPlace_id == wp_id)
	  {
        pari.first++;

        cs = m_tapahtumat_laskutukseen[i]->Charged;   // täsmääkö laskutustila tapahtuman tilan kanssa
        if(m_laskutustila == LTILA_LASKUTTAMATTOMAT && cs == C_FALSE) b = TRUE;
        else if(m_laskutustila == LTILA_LASKUTETUT && cs == C_TRUE) b = TRUE;
        else if(m_laskutustila == LTILA_KAIKKI) b = TRUE;
	  }

      if(b && m_tapahtumat_laskutukseen[i]->kasitelty == FALSE) pari.second++;
	}

    return pari;
}

void DlgLaskutus::teeYhdiste()
{ // Muutetaan työtyyppien id:t samoiksi sellaisiin tapahtumiin joitten työtyyppien tuotenumerot on samat!!!
	int i, wpid, mtl, mtlc, s, wps, mtls;
    DbSqlite db;
	CString id, prodnum;
    vector <CString> vect;
    map <CString, CString> wt_map;

	kopioi_m_tapahtumat();                            // Tee kopio m_tapahtumat vektorista, käytetään varsinaiseen laskutukseen

    if(m_yhdistatapahtumat != C_FALSE)                // Yhdistys valittu?
	{
      // Tehdään map WorkType tietueista. Indeksinä id ja arvona tuotenumero.
      s = (vect = db.haeTaulusta("WorkType", "id, ProductNumber", 2, (m_nayta == ID_WORKUNIT ? "position_work" : "position_product"), 1, "", "Type", "=", (m_nayta == ID_WORKUNIT ? WORK : PRODUCT))).size();
      for(i=0; i<s; i+=2) wt_map[vect[i]] = vect[i + 1];  //wt_vect.push_back(pair<CString, CString>(vect[i], vect[i + 1]));

      mtls = m_tapahtumat_laskutukseen.size();
      wps = m_workplace_id.size();
	  for(wpid=0; wpid<wps; wpid++)                // : Käydään tapahtumat läpi asiakaskohtaisesti
	  {
        for(mtl=0; mtl<mtls - 1; mtl++)
		{
          // tapahtuman workplacet erilaiset => ei käsitellä (: Käydään tapahtumat läpi asiakaskohtaisesti)
          if(m_tapahtumat_laskutukseen[mtl]->WorkPlace_id != m_workplace_id[wpid]) continue;

          // otetaan tapahtuman työtyypin id ja tuotenumero - hyppää pois, jos tuotenumero on asettamatta
          id = m_tapahtumat_laskutukseen[mtl]->WorkType_id;
          if((prodnum = wt_map[id]) == "") continue;

          for(mtlc=mtl+1; mtlc<mtls; mtlc++)
		  {
            // Eli ideana on asettaa WorkType_id:t samoiksi, jos tuotenumerot on samat.
            // Laskutettaessa nämä lasketaan sitten yhteen, koska WorkType_id:t ovat samat!!!
            if(m_tapahtumat_laskutukseen[mtlc]->WorkType_id != id && 
               wt_map[m_tapahtumat_laskutukseen[mtlc]->WorkType_id] == prodnum)
              m_tapahtumat_laskutukseen[mtlc]->WorkType_id = id; 
		  }
		}
	  }

	}
}

BOOL DlgLaskutus::kopioi_m_tapahtumat()
{
    ItemData *pid;

    for(int i=0; i<m_tapahtumat_laskutukseen.size(); i++) delete m_tapahtumat_laskutukseen.at(i);
	m_tapahtumat_laskutukseen.clear();

	for(int i=0; i<m_tapahtumat.size(); i++)
    {
      pid = new ItemData;
	  m_tapahtumat_laskutukseen.push_back(pid);

	  pid->id = m_tapahtumat[i]->id;
	  pid->Worker_id = m_tapahtumat[i]->Worker_id;
	  pid->WorkPlace_id = m_tapahtumat[i]->WorkPlace_id;
	  pid->WorkType_id = m_tapahtumat[i]->WorkType_id;
	  pid->StartDate = m_tapahtumat[i]->StartDate;
	  pid->StartTime = m_tapahtumat[i]->StartTime;
	  pid->EndDate = m_tapahtumat[i]->EndDate;
	  pid->EndTime = m_tapahtumat[i]->EndTime;
	  pid->Unit = m_tapahtumat[i]->Unit;
	  pid->UnitValue = m_tapahtumat[i]->UnitValue;
      pid->Charged = m_tapahtumat[i]->Charged;
	  pid->UnitPrice = m_tapahtumat[i]->UnitPrice;
	  pid->TotalPrice = m_tapahtumat[i]->TotalPrice;
      pid->Alv = m_tapahtumat[i]->Alv;
	  pid->ReportName = m_tapahtumat[i]->ReportName;
	  pid->ReportDate = m_tapahtumat[i]->ReportDate;
      pid->Biller_id = m_tapahtumat[i]->Biller_id;
      pid->Type = m_tapahtumat[i]->Type;
	  pid->kasitelty = FALSE;
	  pid->oWorkType_id = m_tapahtumat[i]->WorkType_id;
    }

    return TRUE;
}

void DlgLaskutus::OnBnClickedOk()
{
    OnOK();
}

// Vanhentunut tapa käyttä matkapuhelimen hintoja laskutuksessa
        //float TotalPrice = 0;
        //if(m_hinnat == HINNAT_MATKAPUH)                  // käytä matkapuhelimessa määritettyjä hintoja
		//{
        //  for(i=0; i<s_as; i++)                              // : lisätään käsiteltävän asiakkaan, käsiteltävän työtyypin
		//  {                                                  // : työt kokonaishintaan
        //    if(m_tapahtumat_laskutukseen[i]->WorkPlace_id == workplace_id && m_tapahtumat_laskutukseen[i]->WorkType_id == worktype_vect[i_wt])
		//	{
        //      cs = m_tapahtumat_laskutukseen[i]->Charged;    // : mutta vain jos laskutustila täsmää tapahtuman tilan kanssa
        //      if(m_laskutustila == LTILA_LASKUTTAMATTOMAT && cs == C_FALSE)
        //        TotalPrice += atof(m_tapahtumat_laskutukseen[i]->TotalPrice);
        //      else if(m_laskutustila == LTILA_LASKUTETUT && cs == C_TRUE)
        //        TotalPrice += atof(m_tapahtumat_laskutukseen[i]->TotalPrice);
        //      else if(m_laskutustila == LTILA_KAIKKI)
        //        TotalPrice += atof(m_tapahtumat_laskutukseen[i]->TotalPrice);
		//	}
		//  }
		//}