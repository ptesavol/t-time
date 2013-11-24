// DlgErittely.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DlgErittely.h"
#include "Props.h"
#include "Paivays.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ONECM                              10
#define TWOCM                              20
#define THREECM                            30
#define TOP_Y                              (ONECM + 2)               // tulostusalueen yläreuna (12 mm paperin yläreunasta)
#define OFS                                3                         // Ala-/ylätunnistetekstin keskitys

/////////////////////////////////////////////////////////////////////////////
// DlgErittely dialog
DlgErittely::DlgErittely(CWnd* pParent /*=NULL*/)
	: CDialog(DlgErittely::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgErittely)
	//}}AFX_DATA_INIT
}

void DlgErittely::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgErittely)
	DDX_Control(pDX, IDC_STCOPT5, m_stcOpt5);
	DDX_Control(pDX, IDC_STCOPT4, m_stcOpt4);
	DDX_Control(pDX, IDC_STCOPT3, m_stcOpt3);
	DDX_Control(pDX, IDC_STCOPT2, m_stcOpt2);
	DDX_Control(pDX, IDC_STCOPT1, m_stcOpt1);
	DDX_Control(pDX, IDC_CHKKMKORVAUS, m_chkKmKorvaus);
	DDX_Control(pDX, IDC_CMBFONTTI, m_cmbFontti);
	DDX_Control(pDX, IDC_CMBFONTINKOKO, m_cmbFontinkoko);
	DDX_Control(pDX, IDC_CHKYLAPAIVAYS, m_chkYlapaivays);
	DDX_Control(pDX, IDC_EDTYLATUNNISTE, m_edtYlatunniste);
	DDX_Control(pDX, IDC_EDTALATUNNISTE, m_edtAlatunniste);
	DDX_Control(pDX, IDC_CHKYLATUNNISTE, m_chkYlatunniste);
	DDX_Control(pDX, IDC_CHKALATUNNISTE, m_chkAlatunniste);
	DDX_Control(pDX, IDC_CHKSIVUTUS, m_chkSivutus);
	DDX_Control(pDX, IDC_CMB5, m_cmb5);
	DDX_Control(pDX, IDC_CMB4, m_cmb4);
	DDX_Control(pDX, IDC_CMB3, m_cmb3);
	DDX_Control(pDX, IDC_CMB2, m_cmb2);
	DDX_Control(pDX, IDC_CMB1, m_cmb1);
	DDX_Control(pDX, IDC_CHKYHDISTATAPAHTUMAT, m_chkYhdistaTapahtumat);
	DDX_Control(pDX, IDC_CMBYHTEENVETO, m_cmbYhteenveto);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgErittely, CDialog)
	//{{AFX_MSG_MAP(DlgErittely)
	ON_BN_CLICKED(IDC_BTNTULOSTA, OnBtntulosta)
	ON_CBN_SELCHANGE(IDC_CMB1, OnSelchangeCmb1)
	ON_CBN_SELCHANGE(IDC_CMB2, OnSelchangeCmb2)
	ON_CBN_SELCHANGE(IDC_CMB3, OnSelchangeCmb3)
	ON_CBN_SELCHANGE(IDC_CMB4, OnSelchangeCmb4)
	ON_CBN_SELCHANGE(IDC_CMB5, OnSelchangeCmb5)
	ON_BN_CLICKED(IDC_CHKSIVUTUS, OnChksivutus)
	ON_BN_CLICKED(IDC_CHKALATUNNISTE, OnChkalatunniste)
	ON_BN_CLICKED(IDC_CHKYLATUNNISTE, OnChkylatunniste)
	ON_BN_CLICKED(IDC_CHKYLAPAIVAYS, OnChkylapaivays)
	ON_CBN_SELCHANGE(IDC_CMBFONTINKOKO, OnSelchangeCmbfontinkoko)
	ON_EN_CHANGE(IDC_EDTALATUNNISTE, OnChangeEdtalatunniste)
	ON_EN_CHANGE(IDC_EDTYLATUNNISTE, OnChangeEdtylatunniste)
	ON_CBN_SELCHANGE(IDC_CMBFONTTI, OnSelchangeCmbfontti)
	ON_BN_CLICKED(IDC_CHKKMKORVAUS, OnChkkmkorvaus)
	ON_BN_CLICKED(IDC_CHKYHDISTATAPAHTUMAT, &DlgErittely::OnChkyhdistatapahtumat)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_CMBYHTEENVETO, &DlgErittely::OnCbnSelchangeCmbyhteenveto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgErittely message handlers
BOOL DlgErittely::OnInitDialog() 
{
    int t, s;
    CString id;
    Paivays paivays;
    pair<int,int> day_pari;
    pair<CString, pair<int, int> > id_pari;
    vector <CString> day_vect;
    vector <ItemData*> w_vect;
    vector <ItemData_travel*> t_vect;

    CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGERITTELY_C1"));
	SetDlgItemText(IDC_STCOPT6, Props::i().lang("DLGERITTELY_C2"));
	SetDlgItemText(IDC_STCOPT7, Props::i().lang("DLGERITTELY_C3"));
	m_chkYlatunniste.SetWindowText(Props::i().lang("DLGERITTELY_C4"));
	m_chkAlatunniste.SetWindowText(Props::i().lang("DLGERITTELY_C5"));
	m_chkYlapaivays.SetWindowText(Props::i().lang("DLGERITTELY_C6"));
	m_chkKmKorvaus.SetWindowText(Props::i().lang("DLGERITTELY_C7"));
	SetDlgItemText(IDC_BTNTULOSTA, Props::i().lang("DLGERITTELY_C8"));
	SetDlgItemText(IDCANCEL, Props::i().lang("DLGERITTELY_C9"));

    m_cmb1.ResetContent();                           // Tyhjennä listat
    m_cmb2.ResetContent();
    m_cmb3.ResetContent();
    m_cmb4.ResetContent();
    m_cmb5.ResetContent();

	kopioi_m_tapahtumat();                           // Tee kopio m_tapahtumat vektorista

    if(m_mode == MODE_ASIAKKAAT)
	{
      m_opt1 = Props::i().get(OPTIONS_PRNT_ASNIMI).c_str();                    //
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_1"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_2"));
      m_cmb1.SetCurSel(atoi(m_opt1));
      m_stcOpt1.SetWindowText(Props::i().lang("DLGERITTELY_3"));
      m_opt2 = Props::i().get(OPTIONS_PRNT_ASALOITUSPVM).c_str();              //
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_4"));
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_5"));
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_6"));
      m_cmb2.SetCurSel(atoi(m_opt2));
      m_stcOpt2.SetWindowText(Props::i().lang("DLGERITTELY_7"));
      m_opt3 = Props::i().get(OPTIONS_PRNT_ASLOPETUSPVM).c_str();              //
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_4"));
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_5"));
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_6"));
      m_cmb3.SetCurSel(atoi(m_opt3));
      m_stcOpt3.SetWindowText(Props::i().lang("DLGERITTELY_8"));
      m_opt4 = Props::i().get(OPTIONS_PRNT_ASTYOAIKA).c_str();                 //
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_9"));
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_10"));
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_11"));
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_12"));
      m_cmb4.SetCurSel(atoi(m_opt4));
      m_stcOpt4.SetWindowText(Props::i().lang("DLGERITTELY_13"));
      m_opt5 = Props::i().get(OPTIONS_PRNT_ASTYOTYYPIT).c_str();               //
      m_cmb5.AddString(Props::i().lang("DLGERITTELY_14"));
      m_cmb5.AddString(Props::i().lang("DLGERITTELY_15"));
      m_cmb5.SetCurSel(atoi(m_opt5));
      m_stcOpt5.SetWindowText(Props::i().lang("DLGERITTELY_16"));
      m_chkSivutus.SetWindowText(Props::i().lang("DLGERITTELY_17"));		   //
      m_cmbYhteenveto.ResetContent();                                          //
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_18"));
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_19"));
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_20"));
      m_chkKmKorvaus.ShowWindow(SW_HIDE);                                      //
      this->SetWindowText(Props::i().lang("DLGERITTELY_21"));				   //
	  m_yhdistatapahtumat = Props::i().get(OPTIONS_PRNT_YHDISTATAPAHTUMAT).c_str(); //
      if(m_yhdistatapahtumat == C_FALSE) m_chkYhdistaTapahtumat.SetCheck(0);
      else m_chkYhdistaTapahtumat.SetCheck(1);
      if(m_nayta == ID_WORKUNIT) m_chkYhdistaTapahtumat.SetWindowText(Props::i().lang("DLGERITTELY_22"));
	  else m_chkYhdistaTapahtumat.SetWindowText(Props::i().lang("DLGERITTELY_23"));
      m_chkYhdistaTapahtumat.ShowWindow(SW_SHOW);
	}
    else if(m_mode == MODE_TYOAJAT)
	{
      m_opt1 = Props::i().get(OPTIONS_PRNT_TTALOITUSPVM).c_str();              //
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_4"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_5"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_6"));
      m_cmb1.SetCurSel(atoi(m_opt1));
      m_stcOpt1.SetWindowText(Props::i().lang("DLGERITTELY_7"));
      m_opt2 = Props::i().get(OPTIONS_PRNT_TTLOPETUSPVM).c_str();              //
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_4"));
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_5"));
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_6"));
      m_cmb2.SetCurSel(atoi(m_opt2));
      m_stcOpt2.SetWindowText(Props::i().lang("DLGERITTELY_8"));
      m_opt3 = Props::i().get(OPTIONS_PRNT_TTTYOAIKA).c_str();                 //
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_9"));
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_10"));
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_11"));
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_12"));
      m_cmb3.SetCurSel(atoi(m_opt3));
      m_stcOpt3.SetWindowText(Props::i().lang("DLGERITTELY_13"));
      m_opt4 = Props::i().get(OPTIONS_PRNT_TTTYOTYYPIT).c_str();               //
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_14"));
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_15"));
      m_cmb4.SetCurSel(atoi(m_opt4));
      m_stcOpt4.SetWindowText(Props::i().lang("DLGERITTELY_16"));
      m_opt5 = "";                                                             //
	  m_cmb5.EnableWindow(FALSE);
      m_stcOpt5.SetWindowText("");
      m_chkSivutus.SetWindowText(Props::i().lang("DLGERITTELY_24"));		   //
      m_cmbYhteenveto.ResetContent();                                          //
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_18"));
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_25"));
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_26"));
      m_chkKmKorvaus.ShowWindow(SW_HIDE);                                      //
      this->SetWindowText(Props::i().lang("DLGERITTELY_27"));				   //
	  m_yhdistatapahtumat = Props::i().get(OPTIONS_PRNT_YHDISTATAPAHTUMAT).c_str(); //
      if(m_yhdistatapahtumat == C_FALSE) m_chkYhdistaTapahtumat.SetCheck(0);
      else m_chkYhdistaTapahtumat.SetCheck(1);
      if(m_nayta == ID_WORKUNIT) m_chkYhdistaTapahtumat.SetWindowText(Props::i().lang("DLGERITTELY_22"));
	  else m_chkYhdistaTapahtumat.SetWindowText(Props::i().lang("DLGERITTELY_23"));
      m_chkYhdistaTapahtumat.ShowWindow(SW_SHOW);
	}
    else if(m_mode == MODE_TYOMATKAT)
	{
      m_opt1 = Props::i().get(OPTIONS_PRNT_TMPAIVAYKSET).c_str();              //
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_28"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_29"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_30"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_31"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_32"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_33"));
      m_cmb1.AddString(Props::i().lang("DLGERITTELY_6"));
      m_cmb1.SetCurSel(atoi(m_opt1));
      m_stcOpt1.SetWindowText(Props::i().lang("DLGERITTELY_34"));
      m_opt2 = Props::i().get(OPTIONS_PRNT_TMMATKA).c_str();                  //
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_35"));
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_36"));
      m_cmb2.AddString(Props::i().lang("DLGERITTELY_37"));
      m_cmb2.SetCurSel(atoi(m_opt2));
      m_stcOpt2.SetWindowText(Props::i().lang("DLGERITTELY_38"));
      m_opt3 = Props::i().get(OPTIONS_PRNT_TMLUKEMAT).c_str();                //
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_39"));
      m_cmb3.AddString(Props::i().lang("DLGERITTELY_40"));
      m_cmb3.SetCurSel(atoi(m_opt3));
      m_stcOpt3.SetWindowText(Props::i().lang("DLGERITTELY_41"));
      m_opt4 = Props::i().get(OPTIONS_PRNT_TMYKSAJOA).c_str();                //
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_42"));
      m_cmb4.AddString(Props::i().lang("DLGERITTELY_43"));
      m_cmb4.SetCurSel(atoi(m_opt4));
      m_stcOpt4.SetWindowText(Props::i().lang("DLGERITTELY_43"));
      m_opt5 = Props::i().get(OPTIONS_PRNT_TMTYOAJOA).c_str();                //
      m_cmb5.AddString(Props::i().lang("DLGERITTELY_44"));
      m_cmb5.AddString(Props::i().lang("DLGERITTELY_45"));
      m_cmb5.SetCurSel(atoi(m_opt5));
      m_stcOpt5.SetWindowText(Props::i().lang("DLGERITTELY_46"));
      m_chkSivutus.SetWindowText(Props::i().lang("DLGERITTELY_24"));		   //
      m_cmbYhteenveto.ResetContent();                                          //
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_18"));
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_25"));
	  m_cmbYhteenveto.AddString(Props::i().lang("DLGERITTELY_26"));
      m_chkKmKorvaus.ShowWindow(SW_SHOW);                                      //
      this->SetWindowText(Props::i().lang("DLGERITTELY_47"));				   //
      m_chkYhdistaTapahtumat.SetCheck(0);                                      //
      m_chkYhdistaTapahtumat.SetWindowText("");
      m_chkYhdistaTapahtumat.ShowWindow(SW_HIDE);
	}

    id = Props::i().get(OPTIONS_PRNT_SIVUTUS).c_str();    // Sivutus/yhtenäinen tulostus
    m_chkSivutus.SetCheck((m_sivutus = (id == C_TRUE ? TRUE : FALSE)));
    if(m_mode == MODE_ASIAKKAAT) m_chkSivutus.SetWindowText(Props::i().lang("DLGERITTELY_17"));
    else if(m_mode == MODE_TYOAJAT || m_mode == MODE_TYOMATKAT) m_chkSivutus.SetWindowText(Props::i().lang("DLGERITTELY_24"));

    id = Props::i().get(OPTIONS_PRNT_YLATUNNISTE).c_str();// Ylätunniste käytössä?
    if(id == C_FALSE) m_ylatunniste = FALSE; else m_ylatunniste = TRUE;
    m_edtYlatunniste.EnableWindow(m_ylatunniste);
    m_chkYlatunniste.SetCheck(m_ylatunniste);

    id = Props::i().get(OPTIONS_PRNT_ALATUNNISTE).c_str();// Alatunniste käytössä?
    if(id == C_FALSE) m_alatunniste = FALSE; else m_alatunniste = TRUE;
    m_edtAlatunniste.EnableWindow(m_alatunniste);
    m_chkAlatunniste.SetCheck(m_alatunniste);

    id = Props::i().get(OPTIONS_PRNT_YLAPAIVAYS).c_str(); // Yläpäiväys päällä?
    if(id == C_FALSE) m_ylapaivays = FALSE; else m_ylapaivays = TRUE;
    m_chkYlapaivays.SetCheck(m_ylapaivays);

	m_yhteenveto = Props::i().get(OPTIONS_PRNT_YHTEENVETO).c_str();
	if(m_yhteenveto == C_ONLY) m_cmbYhteenveto.SetCurSel(2);
	else if(m_yhteenveto == C_TRUE) m_cmbYhteenveto.SetCurSel(1);
	else m_cmbYhteenveto.SetCurSel(0);

    id = Props::i().get(OPTIONS_PRNT_KMKORVAUS).c_str();  // Kilometrikorvaus päällä?
    if(id == C_FALSE) m_kmkorvaus = FALSE; else m_kmkorvaus = TRUE;
    m_chkKmKorvaus.SetCheck(m_kmkorvaus);

    id = Props::i().get(OPTIONS_PRNT_FONTINKOKO).c_str(); // Fontin koko
    m_fontsize = atoi(id);
    if(id == FONTSIZE_8) t = 0;
    if(id == FONTSIZE_10) t = 1;
    if(id == FONTSIZE_12) t = 2;
    if(id == FONTSIZE_14) t = 3;
    m_cmbFontinkoko.SetCurSel(t);

    CPrintDialog printDlg(FALSE);                    // : Fonttien nimet
    LOGFONT logf = { 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, ""};
    printDlg.GetDefaults();
    EnumFontFamiliesEx(printDlg.m_pd.hDC, &logf, (FONTENUMPROC)enumFontFamExProc, (LPARAM)&m_cmbFontti, 0);
    GlobalFree(printDlg.m_pd.hDevMode);
    GlobalFree(printDlg.m_pd.hDevNames);
    ::DeleteDC(printDlg.m_pd.hDC);
    id = Props::i().get(OPTIONS_PRNT_FONTINNIMI).c_str(); // : Valitun fontin nimi asetuksista
    if((s = m_cmbFontti.FindString(-1, id)) == CB_ERR) m_cmbFontti.SetCurSel(0);
    else m_cmbFontti.SetCurSel(s);

    m_strYlatunniste = Props::i().get(OPTIONS_PRNT_YLATUNNISTE_TEXT).c_str();
    m_edtYlatunniste.SetWindowText(m_strYlatunniste);// Ylätunnisteen teksi

    m_strAlatunniste = Props::i().get(OPTIONS_PRNT_ALATUNNISTE_TEXT).c_str();
    m_edtAlatunniste.SetWindowText(m_strAlatunniste);// Alatunnisteen teksi

    if(m_mode == MODE_ASIAKKAAT || m_mode==MODE_TYOAJAT) // Asiakkaiden WorkUnit.WorkPlace_id:t (DISTINCT, vain yksi per asiakas)
	{                                                    // + tapahtumien aikaväli (ajalla, HUOM! ei ajalta) m_id-vektoriin. JA VIELÄ LOPUKSI YHDISTE.
      m_id.clear();
      w_vect = m_tapahtumat_tulostukseen;
      if(!w_vect.empty()) t = atoi(w_vect[0]->WorkPlace_id);

      while(1)
	  {
        if(!w_vect.empty()) s = atoi(w_vect[0]->WorkPlace_id);       // seuraava id
        else s = -1;

        if(s != t)
		{
          id.Format("%d", t);                            // Talleta : id
          day_pari = paivays.haeMinMax(day_vect);        //         :: min/max päiväys
          id_pari.first = id;                            //         :
          id_pari.second = day_pari;                     // id vektoriin
          m_id.push_back(id_pari);

          t = s;                                         // alusta seuraava kierros
          day_vect.clear();
          if(!w_vect.empty()) day_vect.push_back(w_vect[0]->StartDate);
		}
        else day_vect.push_back(w_vect[0]->StartDate);

        if(!w_vect.empty()) w_vect.erase(w_vect.begin());// seuraava elementti tai break kun lista on käyty läpi
        else break;
	  }

      teeYhdiste();                                      // Yhdiste nyt, kun m_id on tehty!!!
	}
    else if(m_mode == MODE_TYOMATKAT)                // TravelUnit.Worker_id:t talteen (yksi työntekijää kohti)
	{                                                // + tapahtumien aikaväli (ajalla, HUOM! ei ajalta)
      m_id.clear();
      t_vect = m_tyomatkat;
      if(!t_vect.empty()) t = atoi(t_vect[0]->Worker_id);

      while(1)
	  {
        if(!t_vect.empty()) s=atoi(t_vect[0]->Worker_id);// seuraava id
        else s = -1;

        if(s != t)
		{
          id.Format("%d", t);                            // Talleta : id
          day_pari = paivays.haeMinMax(day_vect);        //         :: min/max päiväys
          id_pari.first = id;                            //         :
          id_pari.second = day_pari;                     // id vektoriin
          m_id.push_back(id_pari);

          t = s;                                         // alusta seuraava kierros
          day_vect.clear();
          if(!t_vect.empty()) day_vect.push_back(t_vect[0]->StartDate);
		}
        else day_vect.push_back(t_vect[0]->StartDate);

        if(!t_vect.empty()) t_vect.erase(t_vect.begin());// seuraava elementti tai break kun lista on käyty läpi
        else break;
	  }
	}

    return TRUE;
}

void DlgErittely::OnDestroy()
{
    CDialog::OnDestroy();

    // Vapauta muisti
    for(int i=0; i<m_tapahtumat_tulostukseen.size(); i++) delete m_tapahtumat_tulostukseen.at(i);
	m_tapahtumat_tulostukseen.clear();
}

void DlgErittely::OnSelchangeCmb1() 
{
    int s;
    if((s = m_cmb1.GetCurSel()) == CB_ERR) return;

    if(m_mode == MODE_ASIAKKAAT)
	{
      if(s == 0) m_opt1 = PRNT_ASNIMINRO;
      if(s == 1) m_opt1 = PRNT_ASNIMI;
      Props::i().set(OPTIONS_PRNT_ASNIMI, (LPCSTR)m_opt1);
	}
    else if(m_mode == MODE_TYOAJAT)
	{
      if(s == 0) m_opt1 = PRNT_PVM_AIKA;
      if(s == 1) m_opt1 = PRNT_PVM;
      if(s == 2) m_opt1 = PRNT_EI_PVM;
      Props::i().set(OPTIONS_PRNT_TTALOITUSPVM, (LPCSTR)m_opt1);
	}
    if(m_mode == MODE_TYOMATKAT)
	{
      if(s == 0) m_opt1 = PRNT_PVM_AIKA_MOLEMMAT;
      if(s == 1) m_opt1 = PRNT_PVM_MOLEMMAT;
      if(s == 2) m_opt1 = PRNT_PVM_AIKA_ALOITUS;
      if(s == 3) m_opt1 = PRNT_PVM_ALOITUS;
      if(s == 4) m_opt1 = PRNT_PVM_AIKA_LOPETUS;
      if(s == 5) m_opt1 = PRNT_PVM_LOPETUS;
      if(s == 6) m_opt1 = PRNT_EI_PVM_TM;
      Props::i().set(OPTIONS_PRNT_TMPAIVAYKSET, (LPCSTR)m_opt1);
	}
}

void DlgErittely::OnSelchangeCmb2() 
{
    int s;
    if((s = m_cmb2.GetCurSel()) == CB_ERR) return;

    if(m_mode == MODE_ASIAKKAAT)
	{
      if(s == 0) m_opt2 = PRNT_PVM_AIKA;
      if(s == 1) m_opt2 = PRNT_PVM;
      if(s == 2) m_opt2 = PRNT_EI_PVM;
      Props::i().set(OPTIONS_PRNT_ASALOITUSPVM, (LPCSTR)m_opt2);
	}
    else if(m_mode == MODE_TYOAJAT)
	{
      if(s == 0) m_opt2 = PRNT_PVM_AIKA;
      if(s == 1) m_opt2 = PRNT_PVM;
      if(s == 2) m_opt2 = PRNT_EI_PVM;
      Props::i().set(OPTIONS_PRNT_TTLOPETUSPVM, (LPCSTR)m_opt2);
	}
    if(m_mode == MODE_TYOMATKAT)
	{
      if(s == 0) m_opt2 = PRNT_MATKAT_TARKOITUS;
      if(s == 1) m_opt2 = PRNT_MATKAT;
      if(s == 2) m_opt2 = PRNT_EI_MATKAT;
      Props::i().set(OPTIONS_PRNT_TMMATKA, (LPCSTR)m_opt2);
	}
}

void DlgErittely::OnSelchangeCmb3() 
{
    int s;
    if((s = m_cmb3.GetCurSel()) == CB_ERR) return;

    if(m_mode == MODE_ASIAKKAAT)
	{
      if(s == 0) m_opt3 = PRNT_PVM_AIKA;
      if(s == 1) m_opt3 = PRNT_PVM;
      if(s == 2) m_opt3 = PRNT_EI_PVM;
      Props::i().set(OPTIONS_PRNT_ASLOPETUSPVM, (LPCSTR)m_opt3);
	}
    else if(m_mode == MODE_TYOAJAT)
	{
      if(s == 0) m_opt3 = PRNT_TYOAIKA_MIN;
      if(s == 1) m_opt3 = PRNT_TYOAIKA_H;
      if(s == 2) m_opt3 = PRNT_TYOAIKA_KERTOINA;
      if(s == 3) m_opt3 = PRNT_EI_TYOAIKA;
      Props::i().set(OPTIONS_PRNT_TTTYOAIKA, (LPCSTR)m_opt3);
	}
    if(m_mode == MODE_TYOMATKAT)
	{
      if(s == 0) m_opt3 = PRNT_LUKEMAT;
      if(s == 1) m_opt3 = PRNT_EI;
      Props::i().set(OPTIONS_PRNT_TMLUKEMAT, (LPCSTR)m_opt3);
	}
}

void DlgErittely::OnSelchangeCmb4() 
{
    int s;
    if((s = m_cmb4.GetCurSel()) == CB_ERR) return;

    if(m_mode == MODE_ASIAKKAAT)
	{
      if(s == 0) m_opt4 = PRNT_TYOAIKA_MIN;
      if(s == 1) m_opt4 = PRNT_TYOAIKA_H;
      if(s == 2) m_opt4 = PRNT_TYOAIKA_KERTOINA;
      if(s == 3) m_opt4 = PRNT_EI_TYOAIKA;
      Props::i().set(OPTIONS_PRNT_ASTYOAIKA, (LPCSTR)m_opt4);
	}
    else if(m_mode == MODE_TYOAJAT)
	{
      if(s == 0) m_opt4 = PRNT_TYOTYYPIT;
      if(s == 1) m_opt4 = PRNT_EI;
      Props::i().set(OPTIONS_PRNT_TTTYOTYYPIT, (LPCSTR)m_opt4);
	}
    if(m_mode == MODE_TYOMATKAT)
	{
      if(s == 0) m_opt4 = PRNT_YKSAJOA;
      if(s == 1) m_opt4 = PRNT_EI;
      Props::i().set(OPTIONS_PRNT_TMYKSAJOA, (LPCSTR)m_opt4);
	}
}

void DlgErittely::OnSelchangeCmb5() 
{
    int s;
    if((s = m_cmb5.GetCurSel()) == CB_ERR) return;

    if(m_mode == MODE_ASIAKKAAT)
	{
      if(s == 0) m_opt5 = PRNT_TYOTYYPIT;
      if(s == 1) m_opt5 = PRNT_EI;
      Props::i().set(OPTIONS_PRNT_ASTYOTYYPIT, (LPCSTR)m_opt5);
	}
    else if(m_mode == MODE_TYOAJAT)
	{}
    if(m_mode == MODE_TYOMATKAT)
	{
      if(s == 0) m_opt5 = PRNT_TYOAJOA;
      if(s == 1) m_opt5 = PRNT_EI;
      Props::i().set(OPTIONS_PRNT_TMTYOAJOA, (LPCSTR)m_opt5);
	}
}

void DlgErittely::OnChksivutus() 
{
    m_sivutus = (m_chkSivutus.GetCheck() == 0 ? FALSE : TRUE);
    if(m_sivutus) Props::i().set(OPTIONS_PRNT_SIVUTUS, C_TRUE);
    else Props::i().set(OPTIONS_PRNT_SIVUTUS, C_FALSE);
}

void DlgErittely::OnChkylatunniste() 
{
    m_ylatunniste = (m_chkYlatunniste.GetCheck() == 0 ? FALSE : TRUE);
    if(m_ylatunniste) Props::i().set(OPTIONS_PRNT_YLATUNNISTE, C_TRUE);
    else Props::i().set(OPTIONS_PRNT_YLATUNNISTE, C_FALSE);

    m_edtYlatunniste.EnableWindow(m_ylatunniste);
}

void DlgErittely::OnChkalatunniste() 
{
    m_alatunniste = (m_chkAlatunniste.GetCheck() == 0 ? FALSE : TRUE);
    if(m_alatunniste) Props::i().set(OPTIONS_PRNT_ALATUNNISTE, C_TRUE);
    else Props::i().set(OPTIONS_PRNT_ALATUNNISTE, C_FALSE);

    m_edtAlatunniste.EnableWindow(m_alatunniste);
}

void DlgErittely::OnChkylapaivays() 
{
    m_ylapaivays = (m_chkYlapaivays.GetCheck() == 0 ? FALSE : TRUE);
    if(m_ylapaivays) Props::i().set(OPTIONS_PRNT_YLAPAIVAYS, C_TRUE);
    else Props::i().set(OPTIONS_PRNT_YLAPAIVAYS, C_FALSE);
}

void DlgErittely::OnCbnSelchangeCmbyhteenveto()
{
	if(m_cmbYhteenveto.GetCurSel() == 2)
		m_yhteenveto = C_ONLY;
	else if(m_cmbYhteenveto.GetCurSel() == 1)
		m_yhteenveto = C_TRUE;
	else
		m_yhteenveto = C_FALSE;
    Props::i().set(OPTIONS_PRNT_YHTEENVETO, (LPCSTR)m_yhteenveto);
}

void DlgErittely::OnChkkmkorvaus() 
{
    m_kmkorvaus = (m_chkKmKorvaus.GetCheck() == 0 ? FALSE : TRUE);
    if(m_kmkorvaus) Props::i().set(OPTIONS_PRNT_KMKORVAUS, C_TRUE);
    else Props::i().set(OPTIONS_PRNT_KMKORVAUS, C_FALSE);
}

void DlgErittely::OnChkyhdistatapahtumat()
{
    CString cs;

	if(m_chkYhdistaTapahtumat.GetCheck() == 0) m_yhdistatapahtumat = C_FALSE;
    else m_yhdistatapahtumat = C_TRUE;

    Props::i().set(OPTIONS_PRNT_YHDISTATAPAHTUMAT, (LPCSTR)m_yhdistatapahtumat);

	teeYhdiste();                                    // Tee valinnan mukainen lista
}

void DlgErittely::OnSelchangeCmbfontinkoko() 
{
    int s;
    CString cs;

    if((s = m_cmbFontinkoko.GetCurSel()) == CB_ERR) return;
    if(s == 0) cs = FONTSIZE_8;
    else if(s == 1) cs = FONTSIZE_10;
    else if(s == 2) cs = FONTSIZE_12;
    else if(s == 3) cs = FONTSIZE_14;
    m_fontsize = atoi(cs);
    Props::i().set(OPTIONS_PRNT_FONTINKOKO, (LPCSTR)cs);
}

void DlgErittely::OnSelchangeCmbfontti() 
{
    int s;

    if((s = m_cmbFontti.GetCurSel()) == CB_ERR) return;
    m_cmbFontti.GetLBText(s, m_fontname);
    Props::i().set(OPTIONS_PRNT_FONTINNIMI, (LPCSTR)m_fontname);
}

void DlgErittely::OnChangeEdtylatunniste() 
{
    m_edtYlatunniste.GetWindowText(m_strYlatunniste);
    Props::i().set(OPTIONS_PRNT_YLATUNNISTE_TEXT, (LPCSTR)m_strYlatunniste);
}

void DlgErittely::OnChangeEdtalatunniste() 
{
    m_edtAlatunniste.GetWindowText(m_strAlatunniste);
    Props::i().set(OPTIONS_PRNT_ALATUNNISTE_TEXT, (LPCSTR)m_strAlatunniste);
}

void DlgErittely::OnBtntulosta() 
{
    if(m_mode == MODE_ASIAKKAAT) asiakkaat();
    else if(m_mode == MODE_TYOAJAT) tyontekijat();
    else if(m_mode == MODE_TYOMATKAT) tyomatkat();

    OnOK();
}

void DlgErittely::asiakkaat()
{
    CDC dc;
    DWORD e;
    CPen cpen;
    RECT rect;
    DOCINFO di;
    CString cs;
    CSize csize;
    DbSqlite db;
    BOOL print;
    CFont cfont;
    CFont cfont8;
    CFont cfontul;
    TEXTMETRIC tm;
    Paivays paivays;
    DEVMODE *pdm = NULL;
    vector <CString> vect;
    BOOL docStarted = FALSE;
    vector <CString> un_vect;
    pair<CString,CString> pari;
    CPrintDialog printDlg(FALSE);
    map <CString, float> total_single;
    vector <pair<CString,CString> > wp_vect;
    vector <pair<CString,CString> > wt_vect;
    int i, s, j, c, wti, wts, uni, uns, tab, tabm, nHeight, textRows, row;
    float cyCharHeight, cyCharHeightx2, cyCharHeight8, dpi_x, dpi_y, cx, cy, page_w, page_h, top_y, left_x, top, left, cnv;

    try
	{ // Työtyypit id ja nimi
      if((s = (vect = db.haeTaulusta("WorkType", "id, Name", 2, "Name", 0)).size()) == 0) throw(ERR_ERITTELY_AS_5);
      for(i=0; i<s; i+=2)
	  {
        pari.first = vect[i];
        pari.second = vect[i + 1];

        wt_vect.push_back(pari);
	  }
      wts = wt_vect.size();

      // Asiakkaiden nimet ja asiakasnumerot m_id-taulun mukaisessa järjestyksessä
      for(i=0, s=m_id.size(); i<s; i++)
	  {
        if((vect = db.haeTaulusta("WorkPlace", "Name, CustomerNumber", 2, "", 1, "", "id", "=", m_id[i].first)).size() == 0) throw(ERR_ERITTELY_AS_5);
        pari.first = vect[0];
        pari.second = vect[1];
        wp_vect.push_back(pari);
	  }

      // Yksiköiden nimet
      if((vect = db.haeTaulusta("Units", "*", 1, "", 0)).size() == 0) throw(ERR_ERITTELY_AS_5);
      for(i=0, uns=vect.size(); i<uns; i++) un_vect.push_back(vect[i]);

      printDlg.m_pd.Flags &= ~PD_RETURNDEFAULT;
      printDlg.m_pd.Flags |= PD_USEDEVMODECOPIESANDCOLLATE|PD_RETURNDC|PD_NOSELECTION|PD_HIDEPRINTTOFILE;

      if(printDlg.DoModal() == IDCANCEL) throw(ERR_ERITTELY_AS_2);
      if(printDlg.m_pd.hDevMode)                     // Pysytysuuntainen A4 (210 mm * 297 mm)
	  {
        pdm = (DEVMODE*)GlobalLock(printDlg.m_pd.hDevMode);
        if(pdm->dmPaperSize != DMPAPER_A4) throw(ERR_ERITTELY_AS_3);
        if(pdm->dmOrientation != DMORIENT_PORTRAIT) throw(ERR_ERITTELY_AS_4);
        if(pdm) GlobalUnlock(printDlg.m_pd.hDevMode);
	  }

      dc.Attach(printDlg.GetPrinterDC());            // Konteksti

      dpi_x = (float)dc.GetDeviceCaps(LOGPIXELSX);   // dpi-arvot : "For printers, the logical inch is always equal to the physical inch.", msdn2
      dpi_y = (float)dc.GetDeviceCaps(LOGPIXELSY);
      page_h = (float)dc.GetDeviceCaps(VERTSIZE);
      page_w = (float)dc.GetDeviceCaps(HORZSIZE);
      cx = dpi_x / 25.4f;                            // tuumat millimetreiksi
      cy = dpi_y / 25.4f;

      left_x = ONECM * cx;                           // tulostuksen x-aloituskohta
      top_y = TOP_Y * cy;                            // tulostuksen y-aloituskohta
      tab = (int)(((float)(page_w - TWOCM) / 4.0f) * cx);      // Tabuloidun tekstin suorakaiteen leveys ja välien koko (4 tietoa riviä kohti)
      tabm = tab - 1 * cx;

      cpen.CreatePen(PS_SOLID, 1, (COLORREF)0);      // Luo musta kynä
	  dc.SelectObject(cpen);

      nHeight = -MulDiv(m_fontsize, (int)dpi_y, 72);          // Luo n pikselin fontit
      cfont.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);
      nHeight = -MulDiv(m_fontsize, (int)dpi_y, 72);
      cfontul.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, TRUE, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);
      nHeight = -MulDiv(8, (int)dpi_y, 72);
      cfont8.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);

      dc.SelectObject(cfont);                        // Hae fonttien korkeudet loogisina yksiköinä
      dc.GetTextMetrics(&tm);
      cyCharHeight = (float)(tm.tmHeight + tm.tmExternalLeading);
      cyCharHeightx2 = cyCharHeight * 2;
      dc.SelectObject(cfont8);
      dc.GetTextMetrics(&tm);
      cyCharHeight8 = (float)(tm.tmHeight + tm.tmExternalLeading);

      textRows = (int)(((page_h * cy)- (2 * TOP_Y * cy)) / cyCharHeight);       // Maksimirivimäärä valitulla fontilla

      // Aloita tulostus
      ZeroMemory (&di, sizeof (DOCINFO));
      di.cbSize = sizeof(DOCINFO);
      di.lpszDocName = Props::i().lang("DLGERITTELY_48");
      if(dc.StartDoc(&di) <= 0) throw(ERR_ERITTELY_AS_1);
      docStarted = TRUE;

      row = 0;                                       // Aloita ensimmäisen sivun tulostus
      top = top_y;
      if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1);
      tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8);

      for(i=0, s=m_id.size(); i<s; i++)              // Käsiteltävät asiakkaat
	  {
        // tulosta asiakkaan nimi ja mahdollisesti myös asiakasnumero
        dc.SelectObject(cfontul);
        if(m_opt1 == PRNT_ASNIMINRO) cs.Format(Props::i().lang("DLGERITTELY_49"), wp_vect[i].first, wp_vect[i].second);
        else if(m_opt1 == PRNT_ASNIMI) cs = wp_vect[i].first;
        dc.TextOut(left_x, top, cs);
        top += cyCharHeightx2;                           // : Aina tulostettaessa rivi tarkistetaan täyttyikö paperi!!!
		if((row += 2) > textRows)                        // : Jos täyttyy, aloitetaan uusi ja piirretään ylä-/alatunisteet
		{ dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

        // tulosta alustus
        dc.SelectObject(cfont);
        if(m_id[i].second.first != m_id[i].second.second)
          cs.Format(Props::i().lang("DLGERITTELY_50"), paivays.date2string(m_id[i].second.first), paivays.date2string(m_id[i].second.second));
        else
          cs.Format(Props::i().lang("DLGERITTELY_51"), paivays.date2string(m_id[i].second.first));
        dc.TextOut(left_x, top, cs);
        top += cyCharHeightx2; if((row += 2) > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

        // tulosta otsikot
        left = left_x;
        dc.SelectObject(cfontul);
        if(m_opt2 != PRNT_EI_PVM && m_yhteenveto != C_ONLY) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_1"), Props::i().langl("ERITTELY_1")); left += tab; }
        if(m_opt3 != PRNT_EI_PVM && m_yhteenveto != C_ONLY) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_2"), Props::i().langl("ERITTELY_2")); left += tab; }
        if(m_opt4 != PRNT_EI_TYOAIKA) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_3"), Props::i().langl("ERITTELY_3")); left += tab; }
        if(m_opt5 != PRNT_EI) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_4"), Props::i().langl("ERITTELY_4")); left += tab; }
        top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

        // Tulostetaan vain käsiteltävän asiakkaan tiedot, jos ei ole valittu vain yhteenvetoa!
        if(m_yhteenveto != C_ONLY)
        {
          dc.SelectObject(cfont);
          for(j=0, c=m_tapahtumat_tulostukseen.size(); j<c; j++)
          {
            left = left_x;                                 // Vasempaan reunaan joka kierroksen alussa!!!

            if(m_tapahtumat_tulostukseen[j]->WorkPlace_id != m_id[i].first) continue;

            for(wti=0; wti<wts; wti++)                     // Hae työtyypin nimi (nopeampaa kuin hakea levyltä tietokannasta?)
		    {
              if(wt_vect[wti].first != m_tapahtumat_tulostukseen[j]->WorkType_id) continue;
              break;
		    }

			if(m_opt2 != PRNT_EI_PVM)                      // Aloitusaika
		    {
              if(m_opt2 == PRNT_PVM_AIKA) cs.Format("%s, %s", paivays.date2string(m_tapahtumat_tulostukseen[j]->StartDate), paivays.time2string(m_tapahtumat_tulostukseen[j]->StartTime));
              else cs.Format("%s", paivays.date2string(m_tapahtumat_tulostukseen[j]->StartDate));

              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
              left += tab;
  		    }
            if(m_opt3 != PRNT_EI_PVM)                      // Lopetusaika
		    {
              if(m_opt3 == PRNT_PVM_AIKA) cs.Format("%s, %s", paivays.date2string(m_tapahtumat_tulostukseen[j]->EndDate), paivays.time2string(m_tapahtumat_tulostukseen[j]->EndTime));
              else cs.Format("%s", paivays.date2string(m_tapahtumat_tulostukseen[j]->EndDate));

              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
              left += tab;
		    }
            if(m_opt4 != PRNT_EI_TYOAIKA)                  // Työaika minuutteina, tunteina tai kertoina, muut arvot semmoisenaan - perässä yksikkö
		    {
              cnv = atof(m_tapahtumat_tulostukseen[j]->UnitValue);
              if(m_opt4 == PRNT_TYOAIKA_H && m_tapahtumat_tulostukseen[j]->Unit == _UNIT_MIN_)
	  			  cs.Format("%.2f %s", cnv / 60.0f, _UNIT_HOUR_);
              else if(m_opt4 == PRNT_TYOAIKA_MIN && m_tapahtumat_tulostukseen[j]->Unit == _UNIT_MIN_)
				  cs.Format("%.0f %s", cnv, _UNIT_MIN_);
              else if(m_opt4 == PRNT_TYOAIKA_KERTOINA && m_tapahtumat_tulostukseen[j]->Unit == _UNIT_MIN_)
				  cs.Format("1 %s", Props::i().lang("_UNIT_CALL_"));
              else 
				  cs.Format("%.2f %s", cnv, m_tapahtumat_tulostukseen[j]->Unit);

              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
              left += tab;
		    }
            if(m_opt5 != PRNT_EI)                          // Työtyyppi/tuote nimi
		    {
              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(wt_vect[wti].second, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
		    }
            top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
		  }
        }

        // Yhteenveto käsiteltävälle asiakkaalle tehdyistä töistä yksiköittäin->tyypeittäin (lumityö 12 min, lumityö 3 kg ?!??!)
        if((m_yhteenveto == C_TRUE || m_yhteenveto == C_ONLY) && m_opt4 != PRNT_EI_TYOAIKA)
		{
          total_single.clear();
          dc.SelectObject(cfont);

		  // Aseta oikeaan sarakkeeseen huomioiden onko päiväykset valittu näkymään (rivin alkuun oletuksena)
		  left = left_x + (m_opt2 != PRNT_EI_PVM && m_yhteenveto != C_ONLY ? tab : 0) + 
			              (m_opt3 != PRNT_EI_PVM && m_yhteenveto != C_ONLY ? tab : 0);

          top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
          rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
          cs = Props::i().lang("DLGERITTELY_52"); dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
          top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

          for(uni=0; uni<uns; uni++)
		  {
            for(wti=0; wti<wts; wti++)
			{
              cnv = 0.0f;
              print = FALSE;
              for(j=0, c=m_tapahtumat_tulostukseen.size(); j<c; j++)
			  {
                if(m_tapahtumat_tulostukseen[j]->WorkPlace_id != m_id[i].first) continue;
                if(m_tapahtumat_tulostukseen[j]->WorkType_id != wt_vect[wti].first) continue;
                if(m_tapahtumat_tulostukseen[j]->Unit != un_vect[uni]) continue;

                if(m_opt4 == PRNT_TYOAIKA_MIN || m_opt4 == PRNT_TYOAIKA_H)        // Työajat (ID_WORKUNIT) tai myynnit (ID_SALESUNIT) summataan yhteen
				{ cnv += atof(m_tapahtumat_tulostukseen[j]->UnitValue); print = TRUE; }
                else                                 // Työkerrat (ID_WORKUNIT) lasketaan yhteen, myynnit (ID_SALESUNIT) summataan yhteen
				{
                  if(m_tapahtumat_tulostukseen[j]->Type != ID_SALESUNIT) { cnv += 1.0f; print = TRUE; }
                  else { cnv += atof(m_tapahtumat_tulostukseen[j]->UnitValue); print = TRUE; }
				}
			  }

              // tulosta työtyypille tietyllä yksiköllä tehty työ
              if(print)                                  // vain jos jotain tulostettavaa (myös nollat)
			  {
                total_single[un_vect[uni]] += cnv;       // Totaali summa tyypeittäin

                if(un_vect[uni] == _UNIT_MIN_ && m_opt4 == PRNT_TYOAIKA_MIN) cs.Format("%.0f %s", cnv, _UNIT_MIN_);
                else if(un_vect[uni] == _UNIT_MIN_ && m_opt4 == PRNT_TYOAIKA_H) cs.Format("%.2f %s", cnv / 60.0f, _UNIT_HOUR_);
                else if(un_vect[uni] == _UNIT_MIN_ && (m_opt4 == PRNT_EI_TYOAIKA || m_opt4 == PRNT_TYOAIKA_KERTOINA)) cs.Format("%.0f %s", cnv, cnv == 1.0f ? Props::i().lang("DLGERITTELY_53") : Props::i().lang("DLGERITTELY_54"));
                else cs.Format("%.2f %s", cnv, un_vect[uni]);

				rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
				dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
				if(m_opt5 != PRNT_EI)
				{
                  rect.left = left + tab; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
                  dc.DrawText(wt_vect[wti].second, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
				}
                top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
			  }
			}
		  }

          if(/*summa &&*/ total_single.size() > 0)										// Summa yhteensä kenttien arvoista tyypeittäin
		  {
            dc.MoveTo(left, top + cyCharHeight / 2);
            dc.LineTo(left + tabm / 2, top + cyCharHeight / 2);
            top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

            map<CString, float>::iterator it = total_single.begin();
            while(it != total_single.end())
            {
              if(it->first == _UNIT_MIN_ && m_opt4 == PRNT_TYOAIKA_MIN) cs.Format("%.0f %s", it->second, _UNIT_MIN_);
              else if(it->first == _UNIT_MIN_ && m_opt4 == PRNT_TYOAIKA_H) cs.Format("%.2f %s", it->second / 60.0f, _UNIT_HOUR_);
              else if(it->first == _UNIT_MIN_ && (m_opt4 == PRNT_EI_TYOAIKA || m_opt4 == PRNT_TYOAIKA_KERTOINA)) cs.Format("%.0f %s", it->second, it->second == 1.0f ? Props::i().lang("DLGERITTELY_53") : Props::i().lang("DLGERITTELY_54"));
              else cs.Format("%.2f %s", it->second, it->first);

              rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
              top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

              it++;
            }
		  }
		}

        // Uusi sivu asiakkaille (vain jos uusia asiakkaita tulostettavana) tai jatketaan samalle sivulle (yhtä riviä alempaa)
        if(m_sivutus && i + 1 != s)
		{ dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
        else
		{ top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_AS_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); } }
	  }

      // Aloita tulostus
      dc.EndDoc();
	}
    catch(int err)
	{
      if(docStarted) dc.EndDoc();                    // Keskeytä dokumentin tulostus
      if(pdm) GlobalUnlock(printDlg.m_pd.hDevMode);  // Vapauta!!!

      if(err == ERR_ERITTELY_AS_1)
	  {
        LPVOID lpMsgBuf;
        if((e = GetLastError()) != ERROR_SUCCESS)
		{
          FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
          cs.Format(Props::i().lang("DLGERITTELY_55"), e, lpMsgBuf); err = err;
          LocalFree(lpMsgBuf);
		}
	  }
      else if(err == ERR_ERITTELY_AS_2)
	  {
        if((e = CommDlgExtendedError()) != 0)
          cs.Format(Props::i().lang("DLGERITTELY_56"), e);
	  }
      else if(err == ERR_ERITTELY_AS_3) cs = Props::i().lang("DLGERITTELY_57");
      else if(err == ERR_ERITTELY_AS_4) cs = Props::i().lang("DLGERITTELY_58");
      else if(err == ERR_ERITTELY_AS_5) cs = Props::i().lang("DLGERITTELY_59");

      if(err > ERR_ERITTELY_AS_2 || e != ERROR_SUCCESS) MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
}

void DlgErittely::tyontekijat()
{ // Tulostetaan työntekijä kohtaisesti asiakkaiden tapahtumat - m_tapahtumat_tulostukseen-vektorissa asiakkaat.
    CDC dc;
    DWORD e;
    CPen cpen;
    RECT rect;
    DOCINFO di;
    CString cs;
    CSize csize;
    DbSqlite db;
    CFont cfont;
    CFont cfont8;
    CFont cfontul;
	CFont cfontbold;
    TEXTMETRIC tm;
    BOOL asn_print;
    Paivays paivays;
    DEVMODE *pdm = NULL;
    vector <CString> vect;
    BOOL docStarted = FALSE;
    vector <CString> un_vect;
    pair<CString,CString> pari;
    CPrintDialog printDlg(FALSE);
    vector <pair<CString,CString> > wp_vect;
    vector <pair<CString,CString> > wt_vect;
    map <CString, float> total_single, total_all;
    pair <pair<CString,CString>, pair<int,int> > pari2;
    vector < pair <pair<CString,CString>, pair<int,int> > > wo_vect;
    int i, s, j, c, woi, wos, wti, wts, uni, uns, tab, tabm, nHeight, textRows, row, max, min;
    float cyCharHeight, cyCharHeightx2, cyCharHeight8, dpi_x, dpi_y, cx, cy, page_w, page_h, top_y, left_x, top, left, cnv;

    try
	{ // Työtyypit id ja nimi
      if((s = (vect = db.haeTaulusta("WorkType", "id, Name", 2, "Name", 0)).size()) == 0) throw(ERR_ERITTELY_TT_5);
      for(i=0; i<s; i+=2)
	  {
        pari.first = vect[i];
        pari.second = vect[i + 1];
        wt_vect.push_back(pari);
	  }
      wts = wt_vect.size();

      // Asiakkaiden nimet ja asiakasnumerot m_id taulun mukaisessa järjestyksessä (m_id:ssä asiakkaiden yksilölliset (DISTINCT) id:t)
      for(i=0, s=m_id.size(); i<s; i++)
	  {
        if((vect = db.haeTaulusta("WorkPlace", "Name, CustomerNumber", 2, "", 1, "", "id", "=", m_id[i].first)).size() == 0) throw(ERR_ERITTELY_TT_5);
        pari.first = vect[0];
        pari.second = vect[1];
        wp_vect.push_back(pari);
	  }

      // Yksiköiden nimet
      if((vect = db.haeTaulusta("Units", "*", 1, "", 0)).size() == 0) throw(ERR_ERITTELY_TT_5);
      for(i=0, uns=vect.size(); i<uns; i++) un_vect.push_back(vect[i]);

      // Haetaan asiakkaiden työntekijöiden id;t ja nimet (kehnosti toteutettu koodin pätkä: redundanssia hakuehtoon, esim. id='1' or id='1' or id='1' or id='1' or id='1' or ... )
      cs = "SELECT id, Name FROM Worker WHERE";
      for(i=0; i<m_tapahtumat_tulostukseen.size(); i++)
	  {
        cs += " id='" + m_tapahtumat_tulostukseen[i]->Worker_id + "'";
        if(i + 1 < m_tapahtumat_tulostukseen.size()) cs += " OR";
        else cs += ";";
	  }
	  if((s  = (vect = db.freeQuery(cs, 2)).size()) == 0) throw(ERR_ERITTELY_TT_5);
      //if((s = (vect = db.haeTaulusta("Worker", "id, Name", 2, "Name", 0)).size()) == 0) throw(ERR_ERITTELY_TT_5);
      for(i=0; i<s; i+=2)
	  {
        pari2.first.first = vect[i];
        pari2.first.second = vect[i + 1];
        wo_vect.push_back(pari2);
	  }
      wos = wo_vect.size();

      // Haetaan työntekijöille pienin ja suurin aloituspäiväys heidän tekemistä töistä
      for(woi=0; woi<wos; woi++)
	  {
        max = 0;
        min = 0x7FFFFFFF;

        for(i=0, s=m_tapahtumat_tulostukseen.size(); i<s; i++)
		{
          if(m_tapahtumat_tulostukseen[i]->Worker_id != wo_vect[woi].first.first) continue;

          j = atoi(m_tapahtumat_tulostukseen[i]->StartDate);
          if(j > max) max = j;
          if(j < min) min = j;
		}

        wo_vect[woi].second.first = min;
        wo_vect[woi].second.second = max;
	  }

      printDlg.m_pd.Flags &= ~PD_RETURNDEFAULT;
      printDlg.m_pd.Flags |= PD_USEDEVMODECOPIESANDCOLLATE|PD_RETURNDC|PD_NOSELECTION|PD_HIDEPRINTTOFILE;

      if(printDlg.DoModal() == IDCANCEL) throw(ERR_ERITTELY_TT_2);
      if(printDlg.m_pd.hDevMode)                     // Pysytysuuntainen A4 (210 mm * 297 mm)
	  {
        pdm = (DEVMODE*)GlobalLock(printDlg.m_pd.hDevMode);
        if(pdm->dmPaperSize != DMPAPER_A4) throw(ERR_ERITTELY_TT_3);
        if(pdm->dmOrientation != DMORIENT_PORTRAIT) throw(ERR_ERITTELY_TT_4);
        if(pdm) GlobalUnlock(printDlg.m_pd.hDevMode);
	  }

      dc.Attach(printDlg.GetPrinterDC());            // Konteksti

      dpi_x = (float)dc.GetDeviceCaps(LOGPIXELSX);   // dpi-arvot : "For printers, the logical inch is always equal to the physical inch.", msdn2
      dpi_y = (float)dc.GetDeviceCaps(LOGPIXELSY);
      page_h = (float)dc.GetDeviceCaps(VERTSIZE);
      page_w = (float)dc.GetDeviceCaps(HORZSIZE);
      cx = dpi_x / 25.4f;                            // tuumat millimetreiksi
      cy = dpi_y / 25.4f;

      left_x = ONECM * cx;                           // tulostuksen x-aloituskohta
      top_y = TOP_Y * cy;                            // tulostuksen y-aloituskohta
      tab = (int)(((float)(page_w - TWOCM) / 4.0f) * cx);      // Tabuloidun tekstin suorakaiteen leveys ja välien koko (4 tietoa riviä kohti)
      tabm = tab - 1 * cx;

      cpen.CreatePen(PS_SOLID, 1, (COLORREF)0);      // Luo musta kynä
	  dc.SelectObject(cpen);

      nHeight = -MulDiv(m_fontsize, (int)dpi_y, 72);          // Luo n pikselin fontit
      cfont.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);
      nHeight = -MulDiv(m_fontsize, (int)dpi_y, 72);
      cfontul.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, TRUE, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);
      nHeight = -MulDiv(m_fontsize, (int)dpi_y, 72);
      cfontbold.CreateFont(nHeight, 0, 0, 0, FW_BOLD, 0, FALSE, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);
      nHeight = -MulDiv(8, (int)dpi_y, 72);
      cfont8.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);

      dc.SelectObject(cfont);                        // Hae fonttien korkeudet loogisina yksiköinä
      dc.GetTextMetrics(&tm);
      cyCharHeight = (float)(tm.tmHeight + tm.tmExternalLeading);
      cyCharHeightx2 = cyCharHeight * 2;
      dc.SelectObject(cfont8);
      dc.GetTextMetrics(&tm);
      cyCharHeight8 = (float)(tm.tmHeight + tm.tmExternalLeading);

      textRows = (int)(((page_h * cy)- (2 * TOP_Y * cy)) / cyCharHeight);       // Maksimirivimäärä valitulla fontilla

      // Aloita tulostus
      ZeroMemory (&di, sizeof (DOCINFO));
      di.cbSize = sizeof(DOCINFO);
      di.lpszDocName = Props::i().lang("DLGERITTELY_48");
      if(dc.StartDoc(&di) <= 0) throw(ERR_ERITTELY_TT_1);
      docStarted = TRUE;

      row = 0;                                       // Aloita ensimmäisen sivun tulostus
      top = top_y;
      if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1);
      tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8);

      for(woi=0; woi<wos; woi++)                     // Työntekijän työt tietyille asiakkaille
	  {
        dc.SelectObject(cfontul);                        // : alustus työntekijälle
        if(wo_vect[woi].second.first != wo_vect[woi].second.second)
          cs.Format(Props::i().lang("DLGERITTELY_60"), wo_vect[woi].first.second, paivays.date2string(wo_vect[woi].second.first), paivays.date2string(wo_vect[woi].second.second));
        else
          cs.Format(Props::i().lang("DLGERITTELY_61"), wo_vect[woi].first.second, paivays.date2string(wo_vect[woi].second.first));
        dc.TextOut(left_x, top, cs);
        top += cyCharHeight; if(row++ > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

        for(i=0, s=m_id.size(); i<s; i++)                // :: Käsiteltävät asiakkaat m_id:vektorin järjestyksessä (m_id:ssä asiakkaan id vain kerran, kun taas m_tapahtumat_tulostukseen-vektorissa asiakas voi esiintyä usena kerran (monta tapahtumaa samalle asiakkaalle))
		{
          asn_print = FALSE;
          for(j=0, c=m_tapahtumat_tulostukseen.size(); j<c; j++)      // :: tulostetaan tapahtuma vain jos se on käsiteltävän työntekijän (wo_vect) käsiteltävälle asiakkaalle (m_id)
		  {
            if(m_tapahtumat_tulostukseen[j]->Worker_id != wo_vect[woi].first.first) continue;// Käsiteltävä työntekijä
            if(m_tapahtumat_tulostukseen[j]->WorkPlace_id != m_id[i].first) continue;        // ja käsiteltävä asiakas?

            if(!asn_print) // tulosta asiakkaan nimi, asiakasnumero ja otsikot vain kerran työntekijälleen
			{
              dc.SelectObject(cfont);
              top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
              cs.Format(Props::i().lang("DLGERITTELY_62"), wp_vect[i].first);
              if(wp_vect[i].second != "") cs += "(" + wp_vect[i].second + ")";
              dc.TextOut(left_x, top, cs);
              top += cyCharHeightx2; if((row += 2) > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

              left = left_x;
              dc.SelectObject(cfontul);
              if(m_opt1 != PRNT_EI_PVM && m_yhteenveto != C_ONLY) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_1"), Props::i().langl("ERITTELY_1")); left += tab; }
              if(m_opt2 != PRNT_EI_PVM && m_yhteenveto != C_ONLY) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_2"), Props::i().langl("ERITTELY_2")); left += tab; }
              if(m_opt3 != PRNT_EI_TYOAIKA) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_3"), Props::i().langl("ERITTELY_3")); left += tab; }
              if(m_opt4 != PRNT_EI) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_4"), Props::i().langl("ERITTELY_4")); left += tab; }
              top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

              asn_print = TRUE;
			}

            // Tulostetaan, jos ei ole valittu vain yhteenvetoa!
            if(m_yhteenveto != C_ONLY)
            {
              for(wti=0; wti<wts; wti++)                     // Hae työtyypin nimi (nopeampaa kuin hakea levyltä tietokannasta?)
			  {
                if(wt_vect[wti].first != m_tapahtumat_tulostukseen[j]->WorkType_id) continue;
                break;
			  }

              dc.SelectObject(cfont);                        // Normaali fontilla
              left = left_x;                                 // Vasempaan reunaan joka kierroksen alussa!!!
              if(m_opt1 != PRNT_EI_PVM)                      // Aloitusaika
			  {
                if(m_opt1 == PRNT_PVM_AIKA) cs.Format("%s, %s", paivays.date2string(m_tapahtumat_tulostukseen[j]->StartDate), paivays.time2string(m_tapahtumat_tulostukseen[j]->StartTime));
                else cs.Format("%s", paivays.date2string(m_tapahtumat_tulostukseen[j]->StartDate));

                rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
                dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
                left += tab;
			  }
              if(m_opt2 != PRNT_EI_PVM)                      // Lopetusaika
			  {
                if(m_opt2 == PRNT_PVM_AIKA) cs.Format("%s, %s", paivays.date2string(m_tapahtumat_tulostukseen[j]->EndDate), paivays.time2string(m_tapahtumat_tulostukseen[j]->EndTime));
                else cs.Format("%s", paivays.date2string(m_tapahtumat_tulostukseen[j]->EndDate));

                rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
                dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
                left += tab;
			  }
              if(m_opt3 != PRNT_EI_TYOAIKA)                  // Työaika minuutteina, tunteina tai kertoina, muut arvot semmoisenaan - perässä yksikkö
			  {
                cnv = atof(m_tapahtumat_tulostukseen[j]->UnitValue);
                if(m_opt3 == PRNT_TYOAIKA_H && m_tapahtumat_tulostukseen[j]->Unit == _UNIT_MIN_) 
                  cs.Format("%.2f %s", cnv / 60.0f, _UNIT_HOUR_);
                else if(m_opt3 == PRNT_TYOAIKA_MIN && m_tapahtumat_tulostukseen[j]->Unit == _UNIT_MIN_) 
                  cs.Format("%.0f %s", cnv, _UNIT_MIN_);
                else if(m_opt3 == PRNT_TYOAIKA_KERTOINA && m_tapahtumat_tulostukseen[j]->Unit == _UNIT_MIN_)
                  cs.Format("1 %s", Props::i().lang("_UNIT_CALL_"));
                else 
                  cs.Format("%.2f %s", cnv, m_tapahtumat_tulostukseen[j]->Unit);

                rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
                dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
                left += tab;
			  }
              if(m_opt4 != PRNT_EI)                          // Työtyyppi
			  {
                rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
                dc.DrawText(wt_vect[wti].second, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
			  }
              top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
			}
		  }

          // Yhteenveto käsiteltävälle asiakkaalle tehdyistä töistä yksiköittäin->tyypeittäin (lumityö 12 min, lumityö 3 kg, jne)
          if(((m_yhteenveto == C_TRUE || m_yhteenveto == C_ONLY) && m_opt3 != PRNT_EI_TYOAIKA) && asn_print) // jos asiakkaalle tehty töitä
		  {
            total_single.clear();
            dc.SelectObject(cfont);

		    // Aseta oikeaan sarakkeeseen huomioiden onko päiväykset valittu näkymään (rivin alkuun oletuksena)
		    left = left_x + (m_opt1 != PRNT_EI_PVM && m_yhteenveto != C_ONLY ? tab : 0) + 
			                (m_opt2 != PRNT_EI_PVM && m_yhteenveto != C_ONLY ? tab : 0);

            top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
            rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
            cs = Props::i().lang("DLGERITTELY_52"); dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
            top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

            for(uni=0; uni<uns; uni++)
			{
              for(wti=0; wti<wts; wti++)
			  {
                cnv = 0.0f;
                asn_print = FALSE;
                for(j=0, c=m_tapahtumat_tulostukseen.size(); j<c; j++)
				{
                  if(m_tapahtumat_tulostukseen[j]->Worker_id != wo_vect[woi].first.first) continue;
                  if(m_tapahtumat_tulostukseen[j]->WorkPlace_id != m_id[i].first) continue;
                  if(m_tapahtumat_tulostukseen[j]->WorkType_id != wt_vect[wti].first) continue;
                  if(m_tapahtumat_tulostukseen[j]->Unit != un_vect[uni]) continue;

                  if(m_opt3 == PRNT_TYOAIKA_MIN || m_opt3 == PRNT_TYOAIKA_H)    // Työajat (ID_WORKUNIT) tai myynnit (ID_SALESUNIT) summataan yhteen
				  { cnv += atof(m_tapahtumat_tulostukseen[j]->UnitValue); asn_print = TRUE; }
                  else                                 // Työkerrat (ID_WORKUNIT) lasketaan yhteen, myynnit (ID_SALESUNIT) summataan yhteen
				  {
                    if(m_tapahtumat_tulostukseen[j]->Type != ID_SALESUNIT) { cnv += 1.0f; asn_print = TRUE; }
                    else { cnv += atof(m_tapahtumat_tulostukseen[j]->UnitValue); asn_print = TRUE; }
				  }
				}
                // tulosta työtyypille tietyllä yksiköllä tehty työ
                if(asn_print)                          // vain jos jotain tulostettavaa (myös nollat)
				{
                  total_single[un_vect[uni]] += cnv;       // Totaali summa tyypeittäin + kaikki yhteensä
                  total_all[un_vect[uni]] += cnv;

                  if(un_vect[uni] == _UNIT_MIN_ && m_opt3 == PRNT_TYOAIKA_MIN) cs.Format("%.0f %s", cnv, _UNIT_MIN_);
                  else if(un_vect[uni] == _UNIT_MIN_ && m_opt3 == PRNT_TYOAIKA_H) cs.Format("%.2f %s", cnv / 60.0f, _UNIT_HOUR_);
                  else if(un_vect[uni] == _UNIT_MIN_ && (m_opt3 == PRNT_EI_TYOAIKA || m_opt3 == PRNT_TYOAIKA_KERTOINA)) cs.Format("%.0f %s", cnv, cnv == 1.0f ? Props::i().lang("DLGERITTELY_53") : Props::i().lang("DLGERITTELY_54"));
                  else cs.Format("%.2f %s", cnv, un_vect[uni]);

                  rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
                  dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
				  if(m_opt4 != PRNT_EI)
				  {
                    rect.left = left + tab; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
                    dc.DrawText(wt_vect[wti].second, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
				  }
                  top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
				}
			  }
			}

			if(/*summa &&*/ total_single.size() > 0)										// Summa yhteensä kenttien arvoista tyypeittäin
		    {
              dc.MoveTo(left, top + cyCharHeight / 2);
              dc.LineTo(left + tabm / 2, top + cyCharHeight / 2);
              top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

              map<CString, float>::iterator it = total_single.begin();
              while(it != total_single.end())
              {
                if(it->first == _UNIT_MIN_ && m_opt3 == PRNT_TYOAIKA_MIN) cs.Format("%.0f %s", it->second, _UNIT_MIN_);
                else if(it->first == _UNIT_MIN_ && m_opt3 == PRNT_TYOAIKA_H) cs.Format("%.2f %s", it->second / 60.0f, _UNIT_HOUR_);
                else if(it->first == _UNIT_MIN_ && (m_opt3 == PRNT_EI_TYOAIKA || m_opt3 == PRNT_TYOAIKA_KERTOINA)) cs.Format("%.0f %s", it->second, it->second == 1.0f ? Props::i().lang("DLGERITTELY_53") : Props::i().lang("DLGERITTELY_54"));
                else cs.Format("%.2f %s", it->second, it->first);

                rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
                dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
                top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

                it++;
              }
		    }
		  }

        }

        if(/*summa &&*/ total_all.size() > 0)			// Summa kaikkien yhteensä kenttien arvoista kaikista asiakkaista tyypeittäin
        {
		  // Aseta oikeaan sarakkeeseen huomioiden onko päiväykset valittu näkymään (rivin alkuun oletuksena)
		  left = left_x + (m_opt1 != PRNT_EI_PVM && m_yhteenveto != C_ONLY ? tab : 0) + 
                          (m_opt2 != PRNT_EI_PVM && m_yhteenveto != C_ONLY ? tab : 0);

          dc.SelectObject(cfontbold);
          top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
          rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
		  dc.DrawText(Props::i().lang("DLGERITTELY_53"), &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
          top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

          dc.SelectObject(cfont);
          map<CString, float>::iterator it = total_all.begin();
          while(it != total_all.end())
          {
            if(it->first == _UNIT_MIN_ && m_opt3 == PRNT_TYOAIKA_MIN) cs.Format("%.0f %s", it->second, _UNIT_MIN_);
            else if(it->first == _UNIT_MIN_ && m_opt3 == PRNT_TYOAIKA_H) cs.Format("%.2f %s", it->second / 60.0f, _UNIT_HOUR_);
            else if(it->first == _UNIT_MIN_ && (m_opt3 == PRNT_EI_TYOAIKA || m_opt3 == PRNT_TYOAIKA_KERTOINA)) cs.Format("%.0f %s", it->second, it->second == 1.0f ? Props::i().lang("DLGERITTELY_53") : Props::i().lang("DLGERITTELY_54"));
            else cs.Format("%.2f %s", it->second, it->first);

            rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
            dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
            top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

            it++;
          }
        }
        total_all.clear();

        // Uusi sivu työntekijälle (vain jos uusia työntekijöitä tulostettavana) tai jatketaan samalle sivulle (yhtä riviä alempaa)
        if(m_sivutus)
		{ 
          dc.EndPage();
          row = 0; 
          top = top_y;
		  if(woi + 1 != wos)               // ei uutta sivua, jos ei enää työntekijöitä käsiteltävänä
          { if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
		}
        else
		{
          top += cyCharHeight;
          if(++row > textRows)
		  { 
            dc.EndPage(); row = 0; top = top_y;
            if(woi + 1 != wos)             // ei uutta sivua, jos ei enää työntekijöitä käsiteltävänä
			{ if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TT_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
		  }
		}
	  }

      // Aloita tulostus
      dc.EndDoc();
	}
    catch(int err)
	{
      if(docStarted) dc.EndDoc();                    // Keskeytä dokumentin tulostus
      if(pdm) GlobalUnlock(printDlg.m_pd.hDevMode);  // Vapauta!!!

      if(err == ERR_ERITTELY_TT_1)
	  {
        LPVOID lpMsgBuf;
        if((e = GetLastError()) != ERROR_SUCCESS)
		{
          FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
          cs.Format(Props::i().lang("DLGERITTELY_55"), e, lpMsgBuf); err = err;
          LocalFree(lpMsgBuf);
		}
	  }
      else if(err == ERR_ERITTELY_TT_2)
	  {
        if((e = CommDlgExtendedError()) != 0)
          cs.Format(Props::i().lang("DLGERITTELY_56"), e);
	  }
      else if(err == ERR_ERITTELY_TT_3) cs = Props::i().lang("DLGERITTELY_58");
      else if(err == ERR_ERITTELY_TT_4) cs = Props::i().lang("DLGERITTELY_58");
      else if(err == ERR_ERITTELY_TT_5) cs = Props::i().lang("DLGERITTELY_59");

      if(err > ERR_ERITTELY_TT_2 || e != ERROR_SUCCESS) MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
}

void DlgErittely::tyomatkat()
{
    CDC dc;
    DWORD e;
    CPen cpen;
    RECT rect;
    DOCINFO di;
    CString cs;
    CSize csize;
    DbSqlite db;
    CFont cfont;
    CFont cfont8;
    CFont cfontul;
    TEXTMETRIC tm;
    Paivays paivays;
    DEVMODE *pdm = NULL;
    vector <CString> vect;
    BOOL docStarted = FALSE;
    vector <CString> wo_vect;
    CPrintDialog printDlg(FALSE);
    int i, s, j, c, tab, tabm, nHeight, textRows, row;
    float cyCharHeight, cyCharHeightx2, cyCharHeight8, dpi_x, dpi_y, cx, cy, page_w, page_h, top_y, left_x, top, left, cnv, start, end, t_ajo, kmkerroin;

    try
	{
      // Työntekijöiden nimet m_id-taulun mukaisessa järjestyksessä
      for(i=0, s=m_id.size(); i<s; i++)
	  {
        if((vect = db.haeTaulusta("Worker", "Name", 1, "", 1, "", "id", "=", m_id[i].first)).size() == 0) throw(ERR_ERITTELY_TM_5);
        wo_vect.push_back(vect[0]);
	  }

      cs = Props::i().get(OPTIONS_KMKERROIN).c_str();// Hae kilometrikorvauskerroin asetuksista
      kmkerroin = atof(cs);

      printDlg.m_pd.Flags &= ~PD_RETURNDEFAULT;
      printDlg.m_pd.Flags |= PD_USEDEVMODECOPIESANDCOLLATE|PD_RETURNDC|PD_NOSELECTION|PD_HIDEPRINTTOFILE;

      if(printDlg.DoModal() == IDCANCEL) throw(ERR_ERITTELY_TM_2);
      if(printDlg.m_pd.hDevMode)                     // Pysytysuuntainen A4 (210 mm * 297 mm)
	  {
        pdm = (DEVMODE*)GlobalLock(printDlg.m_pd.hDevMode);
        if(pdm->dmPaperSize != DMPAPER_A4) throw(ERR_ERITTELY_TM_3);
        if(pdm->dmOrientation != DMORIENT_PORTRAIT) throw(ERR_ERITTELY_TM_4);
        if(pdm) GlobalUnlock(printDlg.m_pd.hDevMode);
	  }

      dc.Attach(printDlg.GetPrinterDC());            // Konteksti

      dpi_x = (float)dc.GetDeviceCaps(LOGPIXELSX);   // dpi-arvot : "For printers, the logical inch is always equal to the physical inch.", msdn2
      dpi_y = (float)dc.GetDeviceCaps(LOGPIXELSY);
      page_h = (float)dc.GetDeviceCaps(VERTSIZE);
      page_w = (float)dc.GetDeviceCaps(HORZSIZE);
      cx = dpi_x / 25.4f;                            // tuumat millimetreiksi
      cy = dpi_y / 25.4f;

      left_x = ONECM * cx;                           // tulostuksen x-aloituskohta
      top_y = TOP_Y * cy;                            // tulostuksen y-aloituskohta
      tab = (int)(((float)(page_w - TWOCM) / 4.0f) * cx);      // Tabuloidun tekstin suorakaiteen leveys ja välien koko (4 tietoa riviä kohti)
      tabm = tab - 1 * cx;

      cpen.CreatePen(PS_SOLID, 1, (COLORREF)0);      // Luo musta kynä
	  dc.SelectObject(cpen);

      nHeight = -MulDiv(m_fontsize, (int)dpi_y, 72);          // Luo n pikselin fontit
      cfont.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);
      nHeight = -MulDiv(m_fontsize, (int)dpi_y, 72);
      cfontul.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, TRUE, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);
      nHeight = -MulDiv(8, (int)dpi_y, 72);
      cfont8.CreateFont(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, m_fontname);

      dc.SelectObject(cfont);                        // Hae fonttien korkeudet loogisina yksiköinä
      dc.GetTextMetrics(&tm);
      cyCharHeight = (float)(tm.tmHeight + tm.tmExternalLeading);
      cyCharHeightx2 = cyCharHeight * 2;
      dc.SelectObject(cfont8);
      dc.GetTextMetrics(&tm);
      cyCharHeight8 = (float)(tm.tmHeight + tm.tmExternalLeading);

      textRows = (int)(((page_h * cy)- (2 * TOP_Y * cy)) / cyCharHeight);       // Maksimirivimäärä valitulla fontilla

      // Aloita tulostus
      ZeroMemory (&di, sizeof (DOCINFO));
      di.cbSize = sizeof(DOCINFO);
      di.lpszDocName = Props::i().lang("DLGERITTELY_48");
      if(dc.StartDoc(&di) <= 0) throw(ERR_ERITTELY_TM_1);
      docStarted = TRUE;

      row = 0;                                       // Aloita ensimmäisen sivun tulostus
      top = top_y;
      if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1);
      tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8);

      for(i=0, s=m_id.size(); i<s; i++)              // Käsiteltävät työntekijät
	  {
        // tulosta alustus
        dc.SelectObject(cfont);
        if(m_id[i].second.first != m_id[i].second.second)
          cs.Format(Props::i().lang("DLGERITTELY_64"), wo_vect[i], paivays.date2string(m_id[i].second.first), paivays.date2string(m_id[i].second.second));
        else
          cs.Format(Props::i().lang("DLGERITTELY_65"), wo_vect[i], paivays.date2string(m_id[i].second.first));
        dc.TextOut(left_x, top, cs);
        top += cyCharHeightx2; if((row += 2) > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

        // tulosta otsikot
        left = left_x;
        dc.SelectObject(cfontul);
        if(m_opt3 == PRNT_LUKEMAT && m_yhteenveto != C_ONLY) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_5"), Props::i().langl("ERITTELY_5")); left += tab; }
        if(m_opt4 == PRNT_YKSAJOA && m_yhteenveto != C_ONLY) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_6"), Props::i().langl("ERITTELY_6")); left += tab; }
        if(m_opt5 == PRNT_TYOAJOA) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_7"), Props::i().langl("ERITTELY_7")); left += tab; }
        if(m_kmkorvaus && m_opt5 == PRNT_TYOAJOA) { dc.TextOut(left, top, (LPCSTR)Props::i().lang("ERITTELY_8"), Props::i().langl("ERITTELY_8")); left += tab; }
        top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

        t_ajo = 0.0f;
        for(j=0, c=m_tyomatkat.size(); j<c; j++)     // Tulostetaan työntekijöiden tiedot erikseen
		{
          if(m_tyomatkat[j]->Worker_id != m_id[i].first) continue;

          start = atof(m_tyomatkat[j]->StartMeter);      // Alku ja loppulukemat, varmista että ovat oikeassa järjestyksessä
          end   = atof(m_tyomatkat[j]->EndMeter);
          cnv = fabs(end - start);                       // työajo
          t_ajo += cnv;                                  // Yhteenvetoa varten

          // Tulosta, jos vain yhteenveto ei ole valittuna!
		  if(m_yhteenveto != C_ONLY)
		  {
            // Tulostetaan kuvaus työmatkasta: lähtö-määränpää, tarkoitus: ajat
            dc.SelectObject(cfont);
            cs = "";
            if(m_opt2 == PRNT_MATKAT_TARKOITUS)            // : -/-/-
              cs = m_tyomatkat[j]->StartPlace + " - " + m_tyomatkat[j]->EndPlace + ", " + m_tyomatkat[j]->Purpose;
            else if(m_opt2 == PRNT_MATKAT)
              cs = m_tyomatkat[j]->StartPlace + " - " + m_tyomatkat[j]->EndPlace;
            if(m_opt1 != PRNT_EI_PVM_TM)
              cs += ": ";       // : -/-/-
            if(m_opt1 == PRNT_PVM_AIKA_MOLEMMAT)
              cs += Props::i().lang("DLGERITTELY_66") + paivays.date2string(m_tyomatkat[j]->StartDate) + " " + paivays.time2string(m_tyomatkat[j]->StartTime) + Props::i().lang("DLGERITTELY_67") + paivays.date2string(m_tyomatkat[j]->EndDate) + " " + paivays.time2string(m_tyomatkat[j]->EndTime);
            else if(m_opt1 == PRNT_PVM_MOLEMMAT)
              cs += Props::i().lang("DLGERITTELY_66") + paivays.date2string(m_tyomatkat[j]->StartDate) + Props::i().lang("DLGERITTELY_67") + paivays.date2string(m_tyomatkat[j]->EndDate);
            else if(m_opt1 == PRNT_PVM_AIKA_ALOITUS)
              cs += Props::i().lang("DLGERITTELY_66") + paivays.date2string(m_tyomatkat[j]->StartDate) + " " + paivays.time2string(m_tyomatkat[j]->StartTime);
            else if(m_opt1 == PRNT_PVM_ALOITUS)
              cs += Props::i().lang("DLGERITTELY_66") + paivays.date2string(m_tyomatkat[j]->StartDate);
            else if(m_opt1 == PRNT_PVM_AIKA_LOPETUS)
              cs += Props::i().lang("DLGERITTELY_67") + paivays.date2string(m_tyomatkat[j]->EndDate) + " " + paivays.time2string(m_tyomatkat[j]->EndTime);
            else if(m_opt1 == PRNT_PVM_LOPETUS)
              cs += Props::i().lang("DLGERITTELY_67") + paivays.date2string(m_tyomatkat[j]->EndDate);
            dc.TextOut(left_x, top, cs);                   // : -/-/-
            top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

            left = left_x;                                 // Vasempaan reunaan joka kierroksen alussa!!!
            dc.SelectObject(cfont);
            if(m_opt3 == PRNT_LUKEMAT)                     // Mittarilukemat
		    {
              cs.Format("%.2f - %.2f", start, end);
              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
              left += tab;
		    }
            if(m_opt4 == PRNT_YKSAJOA)                     // Yksityisajoa
		    {
              cs = m_tyomatkat[j]->Private + Props::i().lang("DLGERITTELY_68");
              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
              left += tab;
		    }
            if(m_opt5 == PRNT_TYOAJOA)                     // Työajoa
		    {
              cs.Format(Props::i().lang("DLGERITTELY_69"), cnv);
              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
              left += tab;
		    }
            if(m_opt5 == PRNT_TYOAJOA && m_kmkorvaus)      // Kilometrikorvaus
		    {
              cs.Format(Props::i().lang("DLGERITTELY_70"), cnv * kmkerroin);
              rect.left = left; rect.top = top; rect.right = left + tabm; rect.bottom = top + cyCharHeight;
              dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
		    }
            top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
		  }
		}

        if((m_yhteenveto == C_TRUE || m_yhteenveto == C_ONLY) && m_opt5 == PRNT_TYOAJOA)
		{
          dc.SelectObject(cfont);

		  // Aseta oikeaan sarakkeeseen huomioiden onko aiemmat sarakkeet valittu näkymään (rivin alkuun oletuksena)
		  left = left_x + (m_opt3 == PRNT_LUKEMAT && m_yhteenveto != C_ONLY ? tab : 0) + 
			              (m_opt4 == PRNT_YKSAJOA && m_yhteenveto != C_ONLY ? tab : 0);

          top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
          rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
          cs = Props::i().lang("DLGERITTELY_52"); dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
          top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }

          if(m_kmkorvaus) cs.Format(Props::i().lang("DLGERITTELY_71"), t_ajo, kmkerroin);  // :  -/-/-
          else cs.Format(Props::i().lang("DLGERITTELY_69"), t_ajo);
          rect.left = left; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
          dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);    // :  -/-/-
          if(m_kmkorvaus)                                                          // :: +/+/+
		  {
            cs.Format(Props::i().lang("DLGERITTELY_70"),  t_ajo * kmkerroin);
            rect.left = left + tab; rect.top = top; rect.right = rect.left + tabm; rect.bottom = top + cyCharHeight;
            dc.DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
		  }

          top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
		}

        // Uusi sivu työntekijöille (vain jos uusia työntekijöitä tulostettavana) tai jatketaan samalle sivulle (yhtä riviä alempaa)
        if(m_sivutus && i + 1 != s)
		{ dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); }
        else
		{ top += cyCharHeight; if(++row > textRows) { dc.EndPage(); row = 0; top = top_y; if(dc.StartPage() <= 0) throw(ERR_ERITTELY_TM_1); tunnisteet(&dc, cx, cy, page_w, page_h, &cfont8, cyCharHeight8); } }
	  }

      // Aloita tulostus
      dc.EndDoc();
	}
    catch(int err)
	{
      if(docStarted) dc.EndDoc();                    // Keskeytä dokumentin tulostus
      if(pdm) GlobalUnlock(printDlg.m_pd.hDevMode);  // Vapauta!!!

      if(err == ERR_ERITTELY_TM_1)
	  {
        LPVOID lpMsgBuf;
        if((e = GetLastError()) != ERROR_SUCCESS)
		{
          FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
          cs.Format(Props::i().lang("DLGERITTELY_55"), e, lpMsgBuf); err = err;
          LocalFree(lpMsgBuf);
		}
	  }
      else if(err == ERR_ERITTELY_TM_2)
	  {
        if((e = CommDlgExtendedError()) != 0)
          cs.Format(Props::i().lang("DLGERITTELY_56"), e);
	  }
      else if(err == ERR_ERITTELY_TM_3) cs = Props::i().lang("DLGERITTELY_57");
      else if(err == ERR_ERITTELY_TM_4) cs = Props::i().lang("DLGERITTELY_58");
      else if(err == ERR_ERITTELY_TM_5) cs = Props::i().lang("DLGERITTELY_59");

      if(err > ERR_ERITTELY_TM_2 || e != ERROR_SUCCESS) MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}
}

void DlgErittely::tunnisteet(CDC *pdc, float cx, float cy, float page_w, float page_h, CFont *pf, float cyCharHeight8)
{
    RECT rect;
    CString cs;
    COleDateTime odt;

    pdc->SelectObject(*pf);

    if(m_ylatunniste)                                // Ylätunniste - teksti
	{
      rect.left = ONECM * cx;                            // sentti vas. reunasta
      rect.right = rect.left + (page_w - THREECM) * cx;  // leveys - kaksi senttiä päiväykselle tilaa
      rect.top = OFS * cy;                               // n milliä yläreunasta
      rect.bottom = rect.top + cyCharHeight8;            // fontin korkeuden verran tilaa
      pdc->DrawText(m_strYlatunniste, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
	}

    if(m_ylapaivays)                                 // Ylätunniste päiväys
	{
      odt = odt.GetCurrentTime();
      cs.Format("%d.%d.%d", odt.GetDay(), odt.GetMonth(), odt.GetYear());

      rect.left = (page_w - THREECM) * cx;               // Ylätunnisteesta oikealle
      rect.right = rect.left + TWOCM * cx;               // pari senttiä tilaa päiväykselle
      rect.top = OFS * cy;                               // n milliä alatunnisteen viivasta
      rect.bottom = rect.top + cyCharHeight8;            // fontin korkeuden verran tilaa
      pdc->DrawText(cs, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_RIGHT);
	}

    if(m_alatunniste)                                // Alatunniste - teksti
	{
      rect.left = ONECM * cx;                            // sentti vas. reunasta
      rect.right = rect.left + (page_w - TWOCM) * cx;    // leveys (varataan tilaa sivunumeroinnille)
      rect.top = (page_h - ONECM + OFS) * cy;            // n milliä alatunnisteen viivasta
      rect.bottom = rect.top + cyCharHeight8;            // fontin korkeuden verran tilaa
      pdc->DrawText(m_strAlatunniste, &rect, DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP|DT_LEFT);
	}

    pdc->MoveTo(ONECM * cx, ONECM * cy);             // Ylätunniste - viiva
    pdc->LineTo((page_w - ONECM) * cx, ONECM * cy);

    pdc->MoveTo(ONECM * cx, (page_h - ONECM) * cy);  // Alatunniste - viiva
    pdc->LineTo((page_w - ONECM) * cx, (page_h - ONECM) * cy);
}

void DlgErittely::teeYhdiste()
{ // Muutetaan työtyyppien id:t samoiksi sellaisiin tapahtumiin joitten työtyyppien tuotenumerot on samat!!!
	int i, wpid, mtl, mtlc, s, wps, mtls;
    DbSqlite db;
	CString id, prodnum;
    vector <CString> vect;
    map <CString, CString> wt_map;

	kopioi_m_tapahtumat();                           // Tee kopio m_tapahtumat vektorista

    if(m_yhdistatapahtumat != C_FALSE)                // Yhdistys valittu?
	{
      // Tehdään map WorkType tietueista. Indeksinä id ja arvona tuotenumero.
      s = (vect = db.haeTaulusta("WorkType", "id, ProductNumber", 2, (m_nayta == ID_WORKUNIT ? "position_work" : "position_product"), 1, "", "Type", "=", (m_nayta == ID_WORKUNIT ? WORK : PRODUCT))).size();
      for(i=0; i<s; i+=2) wt_map[vect[i]] = vect[i + 1];  //wt_vect.push_back(pair<CString, CString>(vect[i], vect[i + 1]));

      mtls = m_tapahtumat_tulostukseen.size();
      wps = m_id.size();
	  for(wpid=0; wpid<wps; wpid++)                // : Käydään tapahtumat läpi asiakaskohtaisesti
	  {
        for(mtl=0; mtl<mtls/* - 1*/; mtl++)
		{
          // tapahtuman workplacet erilaiset => ei käsitellä (: Käydään tapahtumat läpi asiakaskohtaisesti)
          if(m_tapahtumat_tulostukseen[mtl]->WorkPlace_id != m_id[wpid].first) continue;

          // otetaan tapahtuman työtyypin id ja tuotenumero - pois, jos tuotenumero on asettamatta
          id = m_tapahtumat_tulostukseen[mtl]->WorkType_id;
          if((prodnum = wt_map[id]) == "") continue;

          for(mtlc=mtl+1; mtlc<mtls; mtlc++)
		  {
            // Eli ideana on asettaa WorkType_id:t samoiksi, jos tuotenumerot on samat.
            // Tulostettaessa nämä sitten näytetään samoilla nimillä ja yhteenvedossa ne lasketana yhteen.
            if(m_tapahtumat_tulostukseen[mtlc]->WorkType_id != id && 
               wt_map[m_tapahtumat_tulostukseen[mtlc]->WorkType_id] == prodnum &&
			   wt_map[m_tapahtumat_tulostukseen[mtlc]->WorkType_id] != _UNSET_)
              m_tapahtumat_tulostukseen[mtlc]->WorkType_id = id;
		  }
		}
	  }

	}
}

BOOL DlgErittely::kopioi_m_tapahtumat()
{
    ItemData *pid;

    for(int i=0; i<m_tapahtumat_tulostukseen.size(); i++) delete m_tapahtumat_tulostukseen.at(i);
	m_tapahtumat_tulostukseen.clear();

	for(int i=0; i<m_tapahtumat.size(); i++)
    {
      pid = new ItemData;
	  m_tapahtumat_tulostukseen.push_back(pid);

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
    }

    return TRUE;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
int CALLBACK enumFontFamExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam)
{
    CString cs;
    CComboBox *pcb = (CComboBox*)lParam;

    cs = lpelfe->elfLogFont.lfFaceName;
    if(pcb->FindString(-1, cs) == CB_ERR)            // Lisätään nimi joka ei ole jo listassa
	{
      cs.Left(30);                                       // CFont.CreateFont hyväksyy vain 30 merkkiä pitkät fontin nimet
      pcb->AddString(cs);
	}

    return 1;
}