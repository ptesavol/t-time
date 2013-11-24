// PpageListat.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "DbSqlite.h"
#include "PpageListat.h"
#include "taikaDlg.h"
#include "IpeDlgEdit.h"
#include "IpeDlgComboBox.h"
#include "IpeDlgComboBox2.h"
#include "DlgSiirraAsiakkaat.h"
#include "afxpriv.h"
#include "taikaDlg.h"
#include "DlgSMTP.h"
#include "StringHelper_luokka.h"
#include "Props.h"
#include "DlgImport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PpageListat property page

//IMPLEMENT_DYNCREATE(PpageListat, CPropertyPage)

PpageListat::PpageListat() //: CPropertyPage(PpageListat::IDD)
{
	//{{AFX_DATA_INIT(PpageListat)
	//}}AFX_DATA_INIT
    m_updRegions = TRUE;
    m_updProductgroups = FALSE;
}

PpageListat::~PpageListat()
{
}

void PpageListat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PpageListat)
	DDX_Control(pDX, IDC_STCSEP2, m_stcSep2);
	DDX_Control(pDX, IDC_LSTTUOTTEET, m_lstTuotteet);
	DDX_Control(pDX, IDC_LSTTUOTERYHMAT, m_lstTuoteryhmat);
	DDX_Control(pDX, IDC_SPN_2, m_spn_2);
	DDX_Control(pDX, IDC_SPN_1, m_spn_1);
	DDX_Control(pDX, IDC_BTNLISAA_2, m_btnLisaa_2);
	DDX_Control(pDX, IDC_BTNLISAA_1, m_btnLisaa_1);
	DDX_Control(pDX, IDC_BTNPOISTA_2, m_btnPoista_2);
	DDX_Control(pDX, IDC_BTNPOISTA_1, m_btnPoista_1);
	DDX_Control(pDX, IDC_TAB, m_tabL);
	DDX_Control(pDX, IDC_BTNETSI, m_btnEtsi);
	DDX_Control(pDX, IDC_BTNPOIS_RYHMA, m_btnPoisAsiakasRyhma);
	DDX_Control(pDX, IDC_SPNASIAKKAAT, m_spnAsiakkaat);
	DDX_Control(pDX, IDC_SPNASIAKASRYHMAT, m_spnAsiakasryhmat);
	DDX_Control(pDX, IDC_LSTTYOTYYPIT, m_lstTyotyypit);
	DDX_Control(pDX, IDC_LSTLASKUTTAJAT, m_lstLaskuttajat);
	DDX_Control(pDX, IDC_BTN_SIIRRA, m_btnSiirra);
	DDX_Control(pDX, IDC_BTNPOIS_ASIAKAS, m_btnPoisAsiakas);
	DDX_Control(pDX, IDC_BTNLIS_RYHMA, m_btnLisAsiakasRyhma);
	DDX_Control(pDX, IDC_BTNLIS_ASIAKAS, m_btnLisAsiakas);
	DDX_Control(pDX, IDC_LSTASIAKKAAT, m_lstAsiakkaat);
	DDX_Control(pDX, IDC_LSTASIAKASRYHMAT, m_lstAsiakasryhmat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PpageListat, CDialog)
	//{{AFX_MSG_MAP(PpageListat)
	ON_BN_CLICKED(IDC_BTNLIS_RYHMA, OnBtnlisAsiakasRyhma)
	ON_BN_CLICKED(IDC_BTNLIS_ASIAKAS, OnBtnlisAsiakas)
	ON_BN_CLICKED(IDC_BTNPOIS_ASIAKAS, OnBtnpoisAsiakas)
	ON_BN_CLICKED(IDC_BTNPOIS_RYHMA, OnBtnpoisAsiakasRyhma)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTASIAKASRYHMAT, OnItemchangedLstasiakasryhmat)
	ON_BN_CLICKED(IDC_BTN_SIIRRA, OnBtnSiirra)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPNASIAKASRYHMAT, OnDeltaposSpnasiakasryhmat)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPNASIAKKAAT, OnDeltaposSpnasiakkaat)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPN_2, OnDeltaposSpn_2)
	ON_BN_CLICKED(IDC_BTNLISAA_1, OnBtnlisaa_1)
	ON_BN_CLICKED(IDC_BTNPOISTA_1, OnBtnpoista_1)
	ON_BN_CLICKED(IDC_BTNLISAA_2, OnBtnlisaa_2)
	ON_BN_CLICKED(IDC_BTNPOISTA_2, OnBtnpoista_2)
	ON_BN_CLICKED(IDC_BTNETSI, OnBtnetsi)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPN_1, OnDeltaposSpn_1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTTUOTERYHMAT, OnItemchangedLsttuoteryhmat)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_KICKIDLE, OnKickIdle)              // ON_UPDATE_COMMAND_UI
    ON_UPDATE_COMMAND_UI(IDC_BTNPOIS_RYHMA, OnUpdatePoistaValittuAsiakasRyhma)
    ON_UPDATE_COMMAND_UI(IDC_BTNPOIS_ASIAKAS, OnUpdatePoistaValitutAsiakkaat)
    ON_UPDATE_COMMAND_UI(IDC_BTN_SIIRRA, OnUpdateSiirraValitutAsiakkaat)
    ON_UPDATE_COMMAND_UI(IDC_BTNPOIS_LASKUTTAJA, OnUpdatePoistaValittuLaskuttaja)
    ON_UPDATE_COMMAND_UI(IDC_BTNPOIS_TYOTYYPPI, OnUpdatePoistaValittuTyotyyppi)
    ON_UPDATE_COMMAND_UI(IDC_SPNASIAKASRYHMAT, OnUpdateSpinAsiakasryhmat)
    ON_UPDATE_COMMAND_UI(IDC_SPNASIAKKAAT, OnUpdateSpinAsiakkaat)
    ON_UPDATE_COMMAND_UI(IDC_SPN_1, OnUpdateSpin_1)
    ON_UPDATE_COMMAND_UI(IDC_SPN_2, OnUpdateSpin_2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PpageListat message handlers
BOOL PpageListat::OnInitDialog() 
{
    TCITEM tci;
    CString cs;
    CRect rcList;

	CDialog::OnInitDialog();

	m_btnLisaa_1.SetWindowText(Props::i().lang("PPAGELISTAT_C1"));
	m_btnLisaa_2.SetWindowText(Props::i().lang("PPAGELISTAT_C1"));
	m_btnLisAsiakas.SetWindowText(Props::i().lang("PPAGELISTAT_C1"));
	m_btnLisAsiakasRyhma.SetWindowText(Props::i().lang("PPAGELISTAT_C1"));
	m_btnPoista_1.SetWindowText(Props::i().lang("PPAGELISTAT_C2"));
	m_btnPoista_2.SetWindowText(Props::i().lang("PPAGELISTAT_C2"));
	m_btnPoisAsiakasRyhma.SetWindowText(Props::i().lang("PPAGELISTAT_C2"));
	m_btnPoisAsiakas.SetWindowText(Props::i().lang("PPAGELISTAT_C3"));
	m_btnSiirra.SetWindowText(Props::i().lang("PPAGELISTAT_C4"));

    // Etsi-nappulan bitmap
    m_bmpEtsi.LoadBitmap(IDB_BMPBINOCULAR);
    m_btnEtsi.SetBitmap(m_bmpEtsi);

    // Alusta listat
    m_lstAsiakasryhmat.m_omistaja = O_ASIAKASRYHMA;
	m_lstAsiakasryhmat.m_props = OPTIONS_LSTHEADER_LIAR;
	m_lstAsiakasryhmat.m_allowMoving = TRUE;
	ListView_SetExtendedListViewStyleEx(m_lstAsiakasryhmat.GetSafeHwnd(),       // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_lstAsiakasryhmat.GetClientRect(&rcList);                                  // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstAsiakasryhmat.InsertColumn(0, Props::i().lang("PPAGELISTAT_1"), LVCFMT_LEFT, rcList.right, -1);

    m_lstAsiakkaat.m_omistaja = O_ASIAKAS;
	m_lstAsiakkaat.m_props = OPTIONS_LSTHEADER_LIAS;
	m_lstAsiakkaat.m_allowMoving = TRUE;
	ListView_SetExtendedListViewStyleEx(m_lstAsiakkaat.GetSafeHwnd(),       // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    vector<string> vec = StringHelper::split(Props::i().get((LPCSTR)m_lstAsiakkaat.m_props), ';');
    if(vec.size() < 8)
	{
      m_lstAsiakkaat.GetClientRect(&rcList);                                  // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
	  rcList.right -= 18;
      m_lstAsiakkaat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstAsiakkaat.InsertColumn(1, Props::i().lang("PPAGELISTAT_2"), LVCFMT_LEFT, rcList.right * 0.20f, -1);
      m_lstAsiakkaat.InsertColumn(2, Props::i().lang("PPAGELISTAT_3"), LVCFMT_LEFT, rcList.right * 0.18f, -1);
      m_lstAsiakkaat.InsertColumn(3, Props::i().lang("PPAGELISTAT_4"), LVCFMT_LEFT, rcList.right * 0.18f, -1);
      m_lstAsiakkaat.InsertColumn(4, Props::i().lang("PPAGELISTAT_5"), LVCFMT_LEFT, rcList.right * 0.18f, -1);
      m_lstAsiakkaat.InsertColumn(5, Props::i().lang("PPAGELISTAT_6"), LVCFMT_LEFT, rcList.right * 0.18f, -1);
      m_lstAsiakkaat.InsertColumn(6, Props::i().lang("PPAGELISTAT_7"), LVCFMT_LEFT, rcList.right * 0.18f, -1);
      m_lstAsiakkaat.InsertColumn(7, Props::i().lang("PPAGELISTAT_8"), LVCFMT_LEFT, rcList.right * 0.08f, -1);
	}
    else
	{
      m_lstAsiakkaat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstAsiakkaat.InsertColumn(1, Props::i().lang("PPAGELISTAT_2"), LVCFMT_LEFT, StringHelper::parseInt(vec[1]), -1);
      m_lstAsiakkaat.InsertColumn(2, Props::i().lang("PPAGELISTAT_3"), LVCFMT_LEFT, StringHelper::parseInt(vec[2]), -1);
      m_lstAsiakkaat.InsertColumn(3, Props::i().lang("PPAGELISTAT_4"), LVCFMT_LEFT, StringHelper::parseInt(vec[3]), -1);
      m_lstAsiakkaat.InsertColumn(4, Props::i().lang("PPAGELISTAT_5"), LVCFMT_LEFT, StringHelper::parseInt(vec[4]), -1);
      m_lstAsiakkaat.InsertColumn(5, Props::i().lang("PPAGELISTAT_6"), LVCFMT_LEFT, StringHelper::parseInt(vec[5]), -1);
      m_lstAsiakkaat.InsertColumn(6, Props::i().lang("PPAGELISTAT_7"), LVCFMT_LEFT, StringHelper::parseInt(vec[6]), -1);
      m_lstAsiakkaat.InsertColumn(7, Props::i().lang("PPAGELISTAT_8"), LVCFMT_LEFT, StringHelper::parseInt(vec[7]), -1);
	}

    m_lstLaskuttajat.m_omistaja = O_LASKUTTAJA;
	m_lstLaskuttajat.m_props = OPTIONS_LSTHEADER_LILA;
    m_lstLaskuttajat.m_allowMoving = TRUE;
	ListView_SetExtendedListViewStyleEx(m_lstLaskuttajat.GetSafeHwnd(),       // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    vec = StringHelper::split(Props::i().get((LPCSTR)m_lstLaskuttajat.m_props), ';');
    if(vec.size() < 3)
	{
		m_lstLaskuttajat.GetClientRect(&rcList);
		rcList.right -= 18;
		m_lstLaskuttajat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
		m_lstLaskuttajat.InsertColumn(1, Props::i().lang("PPAGELISTAT_9"), LVCFMT_LEFT, rcList.right * 0.50f, -1);
	    m_lstLaskuttajat.InsertColumn(2, Props::i().lang("PPAGELISTAT_10"), LVCFMT_LEFT, rcList.right * 0.499f, -1);
	}
	else
	{
		m_lstLaskuttajat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
		m_lstLaskuttajat.InsertColumn(1, Props::i().lang("PPAGELISTAT_9"), LVCFMT_LEFT, StringHelper::parseInt(vec[1]), -1);
	    m_lstLaskuttajat.InsertColumn(2, Props::i().lang("PPAGELISTAT_10"), LVCFMT_LEFT, StringHelper::parseInt(vec[2]), -1);
	}

    m_lstTyotyypit.m_omistaja = O_TYOTYYPPI;
	m_lstTyotyypit.m_props = OPTIONS_LSTHEADER_LITT;
    m_lstTyotyypit.m_allowMoving = TRUE;
	ListView_SetExtendedListViewStyleEx(m_lstTyotyypit.GetSafeHwnd(),       // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    vec = StringHelper::split(Props::i().get((LPCSTR)m_lstTyotyypit.m_props), ';');
    if(vec.size() < 3)
	{
	    m_lstTyotyypit.GetClientRect(&rcList);                                  // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
		rcList.right -= 18;
		m_lstTyotyypit.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
		m_lstTyotyypit.InsertColumn(1, Props::i().lang("PPAGELISTAT_11"), LVCFMT_LEFT, rcList.right * 0.50f, -1);
	    m_lstTyotyypit.InsertColumn(2, Props::i().lang("PPAGELISTAT_12"), LVCFMT_LEFT, rcList.right * 0.499f, -1);
	}
	else
	{
		m_lstTyotyypit.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
		m_lstTyotyypit.InsertColumn(1, Props::i().lang("PPAGELISTAT_11"), LVCFMT_LEFT, StringHelper::parseInt(vec[1]), -1);
	    m_lstTyotyypit.InsertColumn(2, Props::i().lang("PPAGELISTAT_12"), LVCFMT_LEFT, StringHelper::parseInt(vec[2]), -1);
	}

    m_lstTuoteryhmat.m_omistaja = O_TUOTERYHMA;
	m_lstTuoteryhmat.m_props = OPTIONS_LSTHEADER_LITR;
	m_lstTuoteryhmat.m_allowMoving = TRUE;
	ListView_SetExtendedListViewStyleEx(m_lstTuoteryhmat.GetSafeHwnd(),      // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_lstTuoteryhmat.GetClientRect(&rcList);                                 // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstTuoteryhmat.InsertColumn(0, Props::i().lang("PPAGELISTAT_13"), LVCFMT_LEFT, rcList.right * 0.999f, -1);

    m_lstTuotteet.m_omistaja = O_TUOTE;
	m_lstTuotteet.m_props = OPTIONS_LSTHEADER_LITU;
	m_lstTuotteet.m_allowMoving = TRUE;
	ListView_SetExtendedListViewStyleEx(m_lstTuotteet.GetSafeHwnd(),         // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    vec = StringHelper::split(Props::i().get((LPCSTR)m_lstTuotteet.m_props), ';');
    if(vec.size() < 7)
	{
	    m_lstTuotteet.GetClientRect(&rcList);
		rcList.right -= 18;
		m_lstTuotteet.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
		m_lstTuotteet.InsertColumn(1, Props::i().lang("PPAGELISTAT_14"), LVCFMT_LEFT, rcList.right * 0.25f, -1);
	    m_lstTuotteet.InsertColumn(2, Props::i().lang("PPAGELISTAT_15"), LVCFMT_LEFT, rcList.right * 0.17f, -1);
		m_lstTuotteet.InsertColumn(3, Props::i().lang("PPAGELISTAT_16"), LVCFMT_LEFT, rcList.right * 0.10f, -1);
	    m_lstTuotteet.InsertColumn(4, Props::i().lang("PPAGELISTAT_17"), LVCFMT_LEFT, rcList.right * 0.14f, -1);
		m_lstTuotteet.InsertColumn(5, Props::i().lang("PPAGELISTAT_18"), LVCFMT_LEFT, rcList.right * 0.21f, -1);
	    m_lstTuotteet.InsertColumn(6, Props::i().lang("PPAGELISTAT_19"), LVCFMT_LEFT, rcList.right * 0.10f, -1);
	}
	else
	{
		m_lstTuotteet.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
		m_lstTuotteet.InsertColumn(1, Props::i().lang("PPAGELISTAT_14"), LVCFMT_LEFT, StringHelper::parseInt(vec[1]), -1);
	    m_lstTuotteet.InsertColumn(2, Props::i().lang("PPAGELISTAT_15"), LVCFMT_LEFT, StringHelper::parseInt(vec[2]), -1);
		m_lstTuotteet.InsertColumn(3, Props::i().lang("PPAGELISTAT_16"), LVCFMT_LEFT, StringHelper::parseInt(vec[3]), -1);
	    m_lstTuotteet.InsertColumn(4, Props::i().lang("PPAGELISTAT_17"), LVCFMT_LEFT, StringHelper::parseInt(vec[4]), -1);
		m_lstTuotteet.InsertColumn(5, Props::i().lang("PPAGELISTAT_18"), LVCFMT_LEFT, StringHelper::parseInt(vec[5]), -1);
	    m_lstTuotteet.InsertColumn(6, Props::i().lang("PPAGELISTAT_19"), LVCFMT_LEFT, StringHelper::parseInt(vec[6]), -1);
	}

	// jos listan päälle tulee muita kontrolleja, tämä estää niitä jäämästä alle tai, että niiden päälle piirretään
	m_lstAsiakasryhmat.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);
	m_lstAsiakkaat.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);
	m_lstLaskuttajat.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);
	m_lstTyotyypit.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);
	m_lstTuoteryhmat.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);
	m_lstTuotteet.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);

	m_lstAsiakasryhmat.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	m_lstAsiakkaat.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	m_lstLaskuttajat.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	m_lstTyotyypit.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	m_lstTuoteryhmat.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	m_lstTuotteet.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	// Asetetaan CImageList listoihin
	m_lstAsiakkaat.SetImageList(Props::e().m_pCImageList, LVSIL_SMALL);
	m_lstLaskuttajat.SetImageList(Props::e().m_pCImageList, LVSIL_SMALL);
	m_lstTyotyypit.SetImageList(Props::e().m_pCImageList, LVSIL_SMALL);
	m_lstTuotteet.SetImageList(Props::e().m_pCImageList, LVSIL_SMALL);

    // Alustetaan tab controlli
	tci.mask = TCIF_IMAGE|TCIF_TEXT; tci.iImage = 0; tci.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGELISTAT_20");
    m_tabL.InsertItem(0, &tci);
    tci.mask = TCIF_IMAGE|TCIF_TEXT; tci.iImage = 0; tci.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGELISTAT_21");
    m_tabL.InsertItem(1, &tci);
    tci.mask = TCIF_IMAGE|TCIF_TEXT; tci.iImage = 0; tci.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGELISTAT_22");
    m_tabL.InsertItem(2, &tci);

	// Näytetään laskuttajat-lista oletuksena
	m_showType = BILLER;

    paivitaAsiakasryhmat("", TRUE);                  // Tiedot listoihin
    paivitaAsiakkaat("");
    paivitaTila();

    OnSetActive();                                   // Päivitä kaikki kontrollit alustavasti

    return TRUE;
}

BOOL PpageListat::OnSetActive() 
{
    CString cs;
    static BOOL firstDraw = TRUE;

	// Aseta menu CTaikaDlg:iin
    CMenu *pMenu = ((CTaikaDlg*)GetParent())->m_pMenu;		// tuhoa edellinen
	if(pMenu) pMenu->DestroyMenu();
	pMenu = createMenu();									// luo uusi
	((CTaikaDlg*)GetParent())->m_pMenu = pMenu;
    AfxGetMainWnd()->SetMenu(pMenu);						// aseta uusi käyttöön
    AfxGetMainWnd()->DrawMenuBar();

    if(firstDraw)
	{         
      windowSize();                                  // Asettele kontrollit
		
      paivitaAsiakasryhmat("", TRUE);		         // Päivitä näyttö
      paivitaAsiakkaat("");
      paivitaTila();

	  firstDraw = FALSE;
	}

    if(Props::e().m_sync_listat != 0)
	{
      if((Props::e().m_sync_listat & SYNC_ASIAKASRYHMAT)) paivitaAsiakasryhmat("", TRUE);
      if((Props::e().m_sync_listat & SYNC_ASIAKKAAT)) paivitaAsiakkaat("");
      if((Props::e().m_sync_listat & SYNC_LASKUTTAJAT)) paivitaLaskuttajat("");
      if((Props::e().m_sync_listat & SYNC_TYOTYYPIT)) paivitaTyotyypit("");
      if((Props::e().m_sync_listat & SYNC_TUOTERYHMAT)) paivitaTuoteryhmat("", TRUE);
      if((Props::e().m_sync_listat & SYNC_TUOTTEET)) paivitaTuotteet("");

	  Props::e().m_sync_listat = 0;
	}

    return TRUE;//CDialog::OnSetActive();
}

void PpageListat::windowSize()
{
    RECT trect, crect;
    int bs, bss, page_width, page_height; // button size, button y-position

    if(m_lstLaskuttajat.GetSafeHwnd() == 0) return;
    if(m_lstTyotyypit.GetSafeHwnd() == 0) return;
    if(m_lstTuoteryhmat.GetSafeHwnd() == 0) return;
    if(m_lstTuotteet.GetSafeHwnd() == 0) return;
    if(m_spn_1.GetSafeHwnd() == 0) return;
    if(m_btnLisaa_1.GetSafeHwnd() == 0) return;
    if(m_btnPoista_1.GetSafeHwnd() == 0) return;
    if(m_spn_2.GetSafeHwnd() == 0) return;
    if(m_btnLisaa_2.GetSafeHwnd() == 0) return;
    if(m_btnPoista_2.GetSafeHwnd() == 0) return;
    if(m_stcSep2.GetSafeHwnd() == 0) return;
    if(m_spnAsiakasryhmat.GetSafeHwnd() == 0) return;
    if(m_btnLisAsiakasRyhma.GetSafeHwnd() == 0) return;
    if(m_btnPoisAsiakasRyhma.GetSafeHwnd() == 0) return;
    if(m_spnAsiakkaat.GetSafeHwnd() == 0) return;
    if(m_btnLisAsiakas.GetSafeHwnd() == 0) return;
    if(m_btnPoisAsiakas.GetSafeHwnd() == 0) return;
    if(m_btnSiirra.GetSafeHwnd() == 0) return;
    if(m_lstAsiakasryhmat.GetSafeHwnd() == 0) return;
    if(m_lstAsiakkaat.GetSafeHwnd() == 0) return;
    if(m_btnEtsi.GetSafeHwnd() == 0) return;

                                                                     // Z-järjestys kohdalleen muuten välilehti peittää kontrollit
    m_tabL.SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

    m_lstLaskuttajat.GetWindowRect(&trect);                          // nappuloiden koko
    bss = trect.bottom - trect.top;
    ((CTaikaDlg*)GetParent())->m_tabMain.GetItemRect(0, &trect);     // tabin headerin koko
    ((CTaikaDlg*)GetParent())->m_tabMain.GetClientRect(&crect);      // tabin koko

    page_width = crect.right - PAGE_LEFT - PAGE_RIGHT;               // sivun koko: w = tabin w - marginaalit, h = tabin h - tabin h - marginaalit
    page_height = crect.bottom - trect.bottom - PAGE_TOP - PAGE_BOTTOM;

    this->SetWindowPos(NULL, 0, 0, page_width, page_height, SWP_NOMOVE|SWP_NOZORDER); // muuta dialogin koko

	// Siirretään kontrollit
    m_tabL.GetItemRect(0, &trect);                                   // listojen tabin headerin koko
    m_tabL.GetClientRect(&crect);                                    // listojen tabin koko

    bs = page_height - crect.bottom;
    m_tabL.SetWindowPos(NULL, 0, bs, page_width - 1, 221, SWP_NOZORDER);

    bs += trect.bottom + PAGE_GAD_SPACE_L + PAGE_GAD_SPACE;
    m_lstLaskuttajat.SetWindowPos(NULL, PAGE_GAD_SPACE_L, bs, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_lstTyotyypit.SetWindowPos(NULL, PAGE_GAD_SPACE_L, bs, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_lstTuoteryhmat.SetWindowPos(NULL, PAGE_GAD_SPACE_L, bs, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_lstTuotteet.SetWindowPos(NULL, PAGE_GAD_SPACE_L + 320, bs, 0, 0, SWP_NOSIZE|SWP_NOZORDER);

    bss = bs + bss + PAGE_GAD_SPACE + 1;
	m_spn_1.SetWindowPos(NULL, PAGE_GAD_SPACE_L, bss - PAGE_GAD_SPACE + 1, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	m_btnLisaa_1.SetWindowPos(NULL, PAGE_GAD_SPACE_L + 23, bss, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	m_btnPoista_1.SetWindowPos(NULL, PAGE_GAD_SPACE_L + 143, bss, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	m_spn_2.SetWindowPos(NULL, PAGE_GAD_SPACE_L + 320, bss - PAGE_GAD_SPACE + 1, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	m_btnLisaa_2.SetWindowPos(NULL, PAGE_GAD_SPACE_L + 23 + 320, bss, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	m_btnPoista_2.SetWindowPos(NULL, PAGE_GAD_SPACE_L + 143 + 320, bss, 0, 0, SWP_NOSIZE|SWP_NOZORDER);

    bss = page_height - crect.bottom - PAGE_GAD_SPACE_L;
    m_stcSep2.SetWindowPos(NULL, 0, bss, page_width, 2, SWP_NOZORDER);
    m_spnAsiakasryhmat.SetWindowPos(NULL, 0, bss - 30, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_btnLisAsiakasRyhma.SetWindowPos(NULL, 23, bss - 27, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_btnPoisAsiakasRyhma.SetWindowPos(NULL, 105, bss - 27, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_spnAsiakkaat.SetWindowPos(NULL, 194, bss - 30, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_btnLisAsiakas.SetWindowPos(NULL, 217, bss - 27, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_btnPoisAsiakas.SetWindowPos(NULL, 337, bss - 27, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    m_btnSiirra.SetWindowPos(NULL, 457, bss - 27, 0, 0, SWP_NOSIZE|SWP_NOZORDER);

    bss = bss - trect.bottom - PAGE_GAD_SPACE - 29;
    m_lstAsiakasryhmat.SetWindowPos(NULL, 0, 0, 182, bss, SWP_NOMOVE|SWP_NOZORDER);
    m_lstAsiakkaat.SetWindowPos(NULL, 0, 0, page_width - 195, bss, SWP_NOMOVE|SWP_NOZORDER);
    m_btnEtsi.GetClientRect(&trect);
    m_btnEtsi.SetWindowPos(NULL, page_width - trect.right - 1, 0, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
}

void PpageListat::OnBtnlisAsiakasRyhma() 
{ lisaaAsiakasRyhma(); }
void PpageListat::OnBtnpoisAsiakasRyhma() 
{ poistaAsiakasRyhma(); }
void PpageListat::OnBtnlisAsiakas() 
{ lisaaAsiakas(0); }
void PpageListat::OnBtnpoisAsiakas() 
{ poistaAsiakas(); }
void PpageListat::OnBtnSiirra() 
{ siirraAsiakasRyhmaan(); }
void PpageListat::OnBtnetsi() 
{ etsi(KEY_CTRLF); }
void PpageListat::OnBtnlisaa_1() 
{ 
    if(m_showType == BILLER) lisaaLaskuttaja(0);
    else if(m_showType == WORK) lisaaTyotyyppi(0);
    else if(m_showType == PRODUCT) lisaaTuoteryhma();
}
void PpageListat::OnBtnpoista_1() 
{ 
    if(m_showType == BILLER) poistaLaskuttaja();
    else if(m_showType == WORK) poistaTyotyyppi();
    else if(m_showType == PRODUCT) poistaTuoteryhma();
}
void PpageListat::OnBtnlisaa_2() 
{
    if(m_showType == PRODUCT) lisaaTuote(0);
}
void PpageListat::OnBtnpoista_2() 
{
    if(m_showType == PRODUCT) poistaTuote();
}

void PpageListat::OnDeltaposSpnasiakasryhmat(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int s;
    POSITION pos;
    ItemData_region *pid;
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
                                                     // Hae poistattavan id ja position
    if(!(pos = m_lstAsiakasryhmat.GetFirstSelectedItemPosition())) return;
    //s = m_lstAsiakasryhmat.GetNextSelectedItem(pos);
    //movepos(s, (pNMUpDown->iDelta < 0 ? s - 1 : s + 1), &m_lstAsiakasryhmat);
    pid = (ItemData_region*)m_lstAsiakasryhmat.GetItemData((s = m_lstAsiakasryhmat.GetNextSelectedItem(pos)));
    deltapos("Region", pid->id, "", "", REGION_POSITION, 1, pNMUpDown->iDelta, s, &m_lstAsiakasryhmat);

    *pResult = 0;
}

void PpageListat::OnDeltaposSpnasiakkaat(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int s;
    POSITION pos;
    ItemData_workplace *pid;
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
    if(!(pos = m_lstAsiakkaat.GetFirstSelectedItemPosition())) return;
    pid = (ItemData_workplace*)m_lstAsiakkaat.GetItemData((s = m_lstAsiakkaat.GetNextSelectedItem(pos)));
    deltapos("WorkPlace", pid->id, pid->Region_id, WORKPLACE_REGION_ID, WORKPLACE_POSITION, 1, pNMUpDown->iDelta, s, &m_lstAsiakkaat);

    *pResult = 0;
}

void PpageListat::OnDeltaposSpn_1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int s;
    POSITION pos;
    void *pid;
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

    if(m_showType == BILLER)
	{
      if(!(pos = m_lstLaskuttajat.GetFirstSelectedItemPosition())) return;
      pid = (void*)m_lstLaskuttajat.GetItemData((s = m_lstLaskuttajat.GetNextSelectedItem(pos)));
      deltapos("Biller", ((ItemData_biller*)pid)->id, "", "", BILLER_POSITION, 2, pNMUpDown->iDelta, s, &m_lstLaskuttajat);
	}
    else if(m_showType == WORK)
	{
      if(!(pos = m_lstTyotyypit.GetFirstSelectedItemPosition())) return;
      pid = (void*)m_lstTyotyypit.GetItemData((s = m_lstTyotyypit.GetNextSelectedItem(pos)));
      deltapos("WorkType", ((ItemData_type*)pid)->id, "", "", WORKTYPE_POSITION_WORK, 1, pNMUpDown->iDelta, s, &m_lstTyotyypit);
	}
    else if(m_showType == PRODUCT)
	{
      if(!(pos = m_lstTuoteryhmat.GetFirstSelectedItemPosition())) return;
      pid = (void*)m_lstTuoteryhmat.GetItemData((s = m_lstTuoteryhmat.GetNextSelectedItem(pos)));
      deltapos("ProductGroup", ((ItemData_productgroup*)pid)->id, "", "", PRODUCTGROUP_POSITION, 1, pNMUpDown->iDelta, s, &m_lstTuoteryhmat);
	}

	*pResult = 0;
}

void PpageListat::OnDeltaposSpn_2(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int s;
    POSITION pos;
    void *pid;
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

    if(m_showType == PRODUCT)
	{
      if(!(pos = m_lstTuotteet.GetFirstSelectedItemPosition())) return;
      pid = (void*)m_lstTuotteet.GetItemData((s = m_lstTuotteet.GetNextSelectedItem(pos)));
      deltapos("WorkType", ((ItemData_type*)pid)->id, ((ItemData_type*)pid)->ProductGroup_id, WORKTYPE_PRODUCTGROUP_ID, WORKTYPE_POSITION_PRODUCT, 1, pNMUpDown->iDelta, s, &m_lstTuotteet);
	}

    *pResult = 0;
}

void PpageListat::OnItemchangedLstasiakasryhmat(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int r;
    CString cs;
    POSITION pos;
    static BOOL b = FALSE;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

    if(!m_updRegions) return;                        // estetään turhaa viestien kierrättämistä!!!
    if(b) return;                                    // estetään myös viestiem hallitsematon kierto (stack overflow -vaara)
    b = TRUE;

    if((pos = m_lstAsiakasryhmat.GetFirstSelectedItemPosition()))
	{
      r = m_lstAsiakasryhmat.GetNextSelectedItem(pos); // Päivitä asiakaslista
      cs = m_lstAsiakasryhmat.GetItemText(r, 0);
      if(this->IsWindowVisible()) paivitaAsiakkaat(cs);
	}

    b = FALSE;
}

void PpageListat::OnItemchangedLsttuoteryhmat(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int r;
    CString cs;
    POSITION pos;
    static BOOL b = FALSE;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

    if(!m_updProductgroups) return;                  // estetään turhaa viestien kierrättämistä!!!
    if(b) return;                                    // estetään myös viestiem hallitsematon kierto (stack overflow -vaara)
    b = TRUE;

    if((pos = m_lstTuoteryhmat.GetFirstSelectedItemPosition()))
	{
      r = m_lstTuoteryhmat.GetNextSelectedItem(pos); // Päivitä tuotteet
      cs = m_lstTuoteryhmat.GetItemText(r, 0);
      if(this->IsWindowVisible()) paivitaTuotteet(cs);
	}

    b = FALSE;
}

void PpageListat::muokkaaAsiakasRyhma(CRect cr, RECT rect, ItemData_region *pid, LVHITTESTINFO hti)
{ // Asiakasryhmän nimeä muokataan
	DbSqlite db;
	CString cs, id;
	vector <CString> vect;
	IpeDlgEdit ipeDlgEdit;

	cs = m_lstAsiakasryhmat.GetItemText(hti.iItem, hti.iSubItem);    // CEdit muokkaukseen
	ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
	ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
	ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
	ipeDlgEdit.m_Ipe.h = 24;
	ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
	ipeDlgEdit.DoModal();
	if(!ipeDlgEdit.m_Ipe.isEdited()) return;

	cs = ipeDlgEdit.m_Ipe.getString();
	if((vect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "Name", "=", cs)).size() > 0)
	{
		cs.Format(Props::i().lang("PPAGELISTAT_23"), cs);
		MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return;
	}

	if(db.paivitaYleinen_id("Region", "Name", cs, "", "", pid->id, TRUE) == RETURN_OK)
	{
		m_lstAsiakasryhmat.SetItemText(0, 0, cs);
		paivitaAsiakasryhmat(cs, TRUE);

		((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_ASIAKASRYHMAT);
	}
}

void PpageListat::muokkaaAsiakas(CRect cr, RECT rect, ItemData_workplace *pid, LVHITTESTINFO hti)
{ // Asiakkaan nimen, asiakasnumeron tai ex_datan muokkaus
	int r;
	DbSqlite db;
	CString cs, cs2;
	vector <CString> vect;
	IpeDlgEdit ipeDlgEdit;                           // Edit
	IpeDlgComboBox Ipedlgcombo;                      // Drop List

	// Muokkaa koko riviä   // // // // // // // // // // // // // // // // // // // // // //
	if(hti.iSubItem == 0)
		lisaaAsiakas(1);
    else if(hti.iSubItem != 3)
	{
		cs = m_lstAsiakkaat.GetItemText(hti.iItem, hti.iSubItem);
		ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
		ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
		ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
		ipeDlgEdit.m_Ipe.h = 24;
		ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
		ipeDlgEdit.DoModal();
		if(!ipeDlgEdit.m_Ipe.isEdited()) return;

		cs = ipeDlgEdit.m_Ipe.getString();
		if(hti.iSubItem == 1)		cs2 = WORKPLACE_NAME;
		else if(hti.iSubItem == 2)	cs2 = WORKPLACE_ADDRESS;
		else if(hti.iSubItem == 4)	cs2 = WORKPLACE_NOTE;
		else if(hti.iSubItem == 5)	cs2 = WORKPLACE_SHORTNOTE;
		else if(hti.iSubItem == 6)	cs2 = WORKPLACE_INFO;
		else if(hti.iSubItem == 7)	cs2 = WORKPLACE_CUSTOMERNUMBER;

		r = db.paivitaWorkPlace(pid, 1, cs2, cs);
		if(r == RETURN_OK)
		{
			if(hti.iSubItem == 1) pid->Name = cs;
			else if(hti.iSubItem == 2) pid->Address = cs;
			else if(hti.iSubItem == 4) pid->Note = cs;
			else if(hti.iSubItem == 5) pid->Shortnote = cs;
			else if(hti.iSubItem == 6) pid->Info = cs;
			else if(hti.iSubItem == 7) pid->CustomerNumber = cs;
			m_lstAsiakkaat.SetItemText(hti.iItem, hti.iSubItem, cs);

			((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_ASIAKKAAT);
		}
		else if(r == RETURN_EXISTS)
		{
			cs.Format(Props::i().lang("PPAGELISTAT_24"), cs);
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		}
	}
    else
	{
		vect = db.haeTaulusta("Biller", "Name, id", 2, "Name", 1, "", "Name", "<>", DFLT_BILLER);
		Ipedlgcombo.m_Ipe.x = rect.left + cr.left + 2;
		Ipedlgcombo.m_Ipe.y = rect.top + cr.top;
		Ipedlgcombo.m_Ipe.w = cr.right - cr.left + 2;
		Ipedlgcombo.m_Ipe.h = 24;
		Ipedlgcombo.m_Ipe.init(m_lstAsiakkaat.GetItemText(hti.iItem, hti.iSubItem), NULL, &vect, 2, "", TRUE);
		Ipedlgcombo.DoModal();
		if(!Ipedlgcombo.m_Ipe.isEdited()) return;

		cs.Format("%d", Ipedlgcombo.m_Ipe.getItemData());// hae tiedot
		if(db.paivitaWorkPlace(pid, 1, WORKPLACE_BILLER_ID, cs) == RETURN_OK)
		{
			pid->Biller_id = cs;

			vect = db.haeTaulusta("Biller", "Name", 1, "", 1, "", "id", "=", cs);
			if(vect.size() > 0) m_lstAsiakkaat.SetItemText(hti.iItem, hti.iSubItem, vect[0]);

			((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_ASIAKKAAT);
		}
	}
}

void PpageListat::muokkaaLaskuttaja(CRect cr, RECT rect, ItemData_biller *pid, LVHITTESTINFO hti)
{
	int r;
	DbSqlite db;
	CString cs, cs2;
	vector <CString> vect;
	IpeDlgEdit ipeDlgEdit;                           // Edit

	// Muokkaa koko riviä   // // // // // // // // // // // // // // // // // // // // // //
	if(hti.iSubItem == 0)
		lisaaLaskuttaja(1);
	// Muokkaa yksittäisiä rivejä // // // // // // // // // // // // // // // // // // // //
	else
	{
		cs = m_lstLaskuttajat.GetItemText(hti.iItem, hti.iSubItem);
		ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
		ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
		ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
		ipeDlgEdit.m_Ipe.h = 24;
		ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
		ipeDlgEdit.DoModal();
		if(!ipeDlgEdit.m_Ipe.isEdited()) return;

		cs = ipeDlgEdit.m_Ipe.getString();
		if(hti.iSubItem == 1)		cs2 = BILLER_NAME;
		else if(hti.iSubItem == 2)	cs2 = BILLER_EMAIL;

		if(hti.iSubItem == 1 && cs == DFLT_BILLER)
		{
			cs.Format(Props::i().lang("PPAGELISTAT_25"), DFLT_BILLER);
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
			return;
		}

		r = db.paivitaBiller(pid, 1, cs2, cs);
		if(r == RETURN_OK)
		{
			if(hti.iSubItem == 1) { pid->Name = cs; paivitaAsiakkaat(""); }
			else if(hti.iSubItem == 2) pid->Email = cs;
			m_lstLaskuttajat.SetItemText(hti.iItem, hti.iSubItem, cs);

			((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_LASKUTTAJAT);
		}
		else if(r == RETURN_EXISTS)
		{
			cs.Format(Props::i().lang("PPAGELISTAT_26"), cs);
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		}
	}
}

void PpageListat::muokkaaTyotyyppi(CRect cr, RECT rect, ItemData_type *pid, LVHITTESTINFO hti)
{
	int r;
	DbSqlite db;
	CString cs, cs2;
	vector <CString> vect;
	IpeDlgEdit ipeDlgEdit;                           // Edit

	// Muokkaa koko riviä   // // // // // // // // // // // // // // // // // // // // // //
	if(hti.iSubItem == 0)
		lisaaTyotyyppi(1);
	// Muokkaa yksittäisiä sarakkeita
	else
	{
		cs = m_lstTyotyypit.GetItemText(hti.iItem, hti.iSubItem);
		ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
		ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
		ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
		ipeDlgEdit.m_Ipe.h = 24;
		ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
		ipeDlgEdit.DoModal();
		if(!ipeDlgEdit.m_Ipe.isEdited()) return;

		cs = ipeDlgEdit.m_Ipe.getString();
		if(hti.iSubItem == 1)		cs2 = WORKTYPE_NAME;
		else if(hti.iSubItem == 2)	cs2 = WORKTYPE_PRODUCTNUMBER;

		r = db.paivitaWorkType(pid, 1, cs2, cs);
		if(r == RETURN_OK)
		{
			if(hti.iSubItem == 1) pid->Name = cs;
			else if(hti.iSubItem == 2) pid->ProductNumber = cs;
			m_lstTyotyypit.SetItemText(hti.iItem, hti.iSubItem, cs);

			((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TYOTYYPIT);
		}
		else if(r == RETURN_EXISTS)
		{
			cs.Format(Props::i().lang("PPAGELISTAT_27"), cs);
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		}
	}
}

void PpageListat::muokkaaTuoteryhma(CRect cr, RECT rect, ItemData_productgroup *pid, LVHITTESTINFO hti)
{
	CString cs;
	DbSqlite db;
	vector <CString> vect;
	IpeDlgEdit ipeDlgEdit;                           // Edit

	cs = m_lstTuoteryhmat.GetItemText(hti.iItem, hti.iSubItem);
	ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
	ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
	ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
	ipeDlgEdit.m_Ipe.h = 24;
	ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
	ipeDlgEdit.DoModal();
	if(!ipeDlgEdit.m_Ipe.isEdited()) return;

	cs = ipeDlgEdit.m_Ipe.getString();
	if(cs != "")
	{
		if((vect = db.haeTaulusta("ProductGroup", "Name", 1, "", 1, "", "Name", "=", cs)).size() > 0)
		{
			cs.Format(Props::i().lang("PPAGELISTAT_28"), cs);
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
			return;
		}
	}

	if(db.paivitaYleinen_id("ProductGroup", PRODUCTGROUP_NAME, cs, "", "", pid->id, FALSE) == RETURN_OK)
	{
		pid->Name = cs;
		m_lstTuoteryhmat.SetItemText(hti.iItem, hti.iSubItem, cs);

		((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TUOTERYHMAT);
	}
}

void PpageListat::muokkaaTuotteet(CRect cr, RECT rect, ItemData_type *pid, LVHITTESTINFO hti)
{
	int r;
	DbSqlite db;
	CString cs, cs2;
	vector <CString> vect;
	IpeDlgEdit ipeDlgEdit;                           // Edit
	IpeDlgComboBox2 Ipedlgcombo2;                    // List - voi kirjoittaa

	// Muokkaa koko riviä   // // // // // // // // // // // // // // // // // // // // // //
	if(hti.iSubItem == 0)
		lisaaTuote(1);
	else if(hti.iSubItem == 3)                       // Unit - CComboBox (Drop List)
	{
		if((vect = db.haeTaulusta("Units", "*", 1, "", 0)).size() == 0) return;
		Ipedlgcombo2.m_Ipe.x = rect.left + cr.left + 2;
		Ipedlgcombo2.m_Ipe.y = rect.top + cr.top;
		Ipedlgcombo2.m_Ipe.w = cr.right - cr.left + 2;
		Ipedlgcombo2.m_Ipe.h = 24;
		Ipedlgcombo2.m_Ipe.init(m_lstTuotteet.GetItemText(hti.iItem, hti.iSubItem), NULL, &vect, 1, "", FALSE);
		Ipedlgcombo2.DoModal();
		if(!Ipedlgcombo2.m_Ipe.isEdited()) return;

		cs = Ipedlgcombo2.m_Ipe.getString();
		db.lisaaUnit(cs);

		if(db.paivitaWorkType(pid, 1, WORKTYPE_UNIT, cs) == RETURN_OK)
		{
			pid->Unit = cs;
			m_lstTuotteet.SetItemText(hti.iItem, hti.iSubItem, cs);

			((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TUOTTEET);
		}
	}
	else
	{
		cs = m_lstTuotteet.GetItemText(hti.iItem, hti.iSubItem);
		ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
		ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
		ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
		ipeDlgEdit.m_Ipe.h = 24;
		ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
		ipeDlgEdit.DoModal();
		if(!ipeDlgEdit.m_Ipe.isEdited()) return;

		cs = ipeDlgEdit.m_Ipe.getString();
		if(hti.iSubItem == 1)		cs2 = WORKTYPE_NAME;
		else if(hti.iSubItem == 2)	cs2 = WORKTYPE_PRODUCTNUMBER;
		else if(hti.iSubItem == 4) { cs2 = WORKTYPE_PURCHASEPRICE; cs = db.fixFloat(cs, FALSE); }
		else if(hti.iSubItem == 5) { cs2 = WORKTYPE_SELLPRICE; cs = db.fixFloat(cs, FALSE); }
		else if(hti.iSubItem == 6) { cs2 = WORKTYPE_ALV; cs = db.fixFloat(cs, FALSE); }

		r = db.paivitaWorkType(pid, 1, cs2, cs);
		if(r == RETURN_OK)
		{
			if(hti.iSubItem == 1) pid->Name = cs;
			else if(hti.iSubItem == 2) pid->ProductNumber = cs;
			else if(hti.iSubItem == 4) pid->PurchasePrice = cs;
			else if(hti.iSubItem == 5) pid->SellPrice = cs;
			else if(hti.iSubItem == 6) pid->Alv = cs;
			m_lstTuotteet.SetItemText(hti.iItem, hti.iSubItem, cs);

			((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TUOTTEET);
		}
		else if(r == RETURN_EXISTS)
		{
			cs.Format(Props::i().lang("PPAGELISTAT_29"), cs);
			MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
			return;
		}
	}
}

void PpageListat::valitseKaikki()
{
    int i, s;

    s = m_lstAsiakkaat.GetItemCount();
    for(i=0; i<s; i++) m_lstAsiakkaat.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    m_lstAsiakkaat.SetFocus();
    if(s > 0) m_lstAsiakkaat.SetSelectionMark(0);
}

void PpageListat::lisaa()
{
    CWnd *pCWnd;

    pCWnd = GetFocus();
    if(pCWnd == (CWnd*)&m_lstAsiakasryhmat) lisaaAsiakasRyhma();
    else if(pCWnd == (CWnd*)&m_lstAsiakkaat) lisaaAsiakas(0);
    else if(pCWnd == (CWnd*)&m_lstLaskuttajat) lisaaLaskuttaja(0);
    else if(pCWnd == (CWnd*)&m_lstTyotyypit) lisaaTyotyyppi(0);
    else if(pCWnd == (CWnd*)&m_lstTyotyypit) lisaaTuoteryhma();
    else if(pCWnd == (CWnd*)&m_lstTyotyypit) lisaaTuote(0);
}

void PpageListat::poista()
{
    CWnd *pCWnd;

    pCWnd = GetFocus();
    if(pCWnd == (CWnd*)&m_lstAsiakasryhmat) poistaAsiakasRyhma();
    else if(pCWnd == (CWnd*)&m_lstAsiakkaat) poistaAsiakas();
    else if(pCWnd == (CWnd*)&m_lstLaskuttajat) poistaLaskuttaja();
    else if(pCWnd == (CWnd*)&m_lstTyotyypit) poistaTyotyyppi();
	else if(pCWnd == (CWnd*)&m_lstTuoteryhmat) poistaTuoteryhma();
	else if(pCWnd == (CWnd*)&m_lstTuotteet) poistaTuote();
}

void PpageListat::lisaaAsiakasRyhma()
{ // Lisätään uusi asiakasryhmä ja siihen yksi asiakas - ryhmä/nimi GetLocalTime()-funktiolla
    DbSqlite db;
    CString name, cs;
    vector <CString> vect;

    if((vect = db.haeTaulusta("Region", "max(id)", 1, "", 0)).size() == 0) return;
    name.Format(Props::i().lang("PPAGELISTAT_30"), atoi(vect[0]) + 1);
    if(db.lisaaRegion(name, &cs) != RETURN_OK) return;
    paivitaAsiakasryhmat(name, TRUE);
    paivitaAsiakkaat("");
    naytaEdit(&m_lstAsiakasryhmat);

    ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_ASIAKASRYHMAT);
}

void PpageListat::lisaaAsiakas(int mode)
{ // Lisää uusi asiakas
    int r;
    DbSqlite db;
    POSITION pos;
	DlgUusiAsiakas d;
    ItemData_workplace *pid;

    // Asiakas lisätään valittuun asiakasryhmään => hae asiakasryhmä ensin
	if(!(pos = m_lstAsiakasryhmat.GetFirstSelectedItemPosition())) return;
	r = m_lstAsiakasryhmat.GetNextSelectedItem(pos);
	d.m_region_name = m_lstAsiakasryhmat.GetItemText(r, 0);

	pos = m_lstAsiakkaat.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		r = m_lstAsiakkaat.GetNextSelectedItem(pos);
		if(!(pid = (ItemData_workplace*)m_lstAsiakkaat.GetItemData(r))) return;
	}
	d.m_pid = (mode == 0 ? NULL : pid);					// 0=uusi tapahtuma, 1=muokkaa entistä
	d.m_mode = mode;
	d.DoModal();										// Näytä muokkausdialogi, kutsuu OnOK:lla lisaaAsiakas(DlgUusiAsiakas *pd)
}

int PpageListat::lisaaAsiakas(DlgUusiAsiakas *pd)
{
    int r;
    DbSqlite db;
    CString biller_id;
    vector <CString> r_vect;
    vector <CString> b_vect;

	if(pd->m_mode == 0)									// Lisäystila
	{
		if((r_vect = db.haeTaulusta("Region", "id", 1, "", 1, "", "Name", "=", pd->m_region_name)).size() == 0) return RETURN_OK;
		if((b_vect = db.haeTaulusta("Biller", "id", 1, "", 1, "", "Name", "=", pd->m_biller_name)).size() == 0) return RETURN_OK;
		r = db.lisaaWorkPlace(pd->m_name, r_vect[0], pd->m_customernumber, pd->m_address, pd->m_note, pd->m_shortnote, pd->m_info, b_vect[0], NULL, WP_JUSTADD);
	}
	else												// Muokkaustila
	{
		db.lisaaBiller(pd->m_biller_name, "", &biller_id, B_NOUPDATE);
		r = db.paivitaWorkPlace(pd->m_pid, 7,	WORKPLACE_NAME,				pd->m_name,
												WORKPLACE_CUSTOMERNUMBER,	pd->m_customernumber,
												WORKPLACE_ADDRESS,			pd->m_address,
												WORKPLACE_NOTE,				pd->m_note,
												WORKPLACE_SHORTNOTE,		pd->m_shortnote,
												WORKPLACE_INFO,				pd->m_info,
												WORKPLACE_BILLER_ID,		biller_id);
	}

	if(r == RETURN_EXISTS)
	{
		MessageBox(Props::i().lang("PPAGELISTAT_31"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return r;
	}

	paivitaAsiakkaat(pd->m_name);

	((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, pd->m_sync);
	if(pd->m_sync|SYNC_LASKUTTAJAT) paivitaLaskuttajat("");

	return RETURN_OK;
}

void PpageListat::poistaAsiakasRyhma()
{
    BOOL b;
    CString region, id, cs, position;
    int i, s;
    DbSqlite db;
    POSITION pos;
    ItemData_workplace id_c;
    vector <CString> vect;
    vector <ItemData_workplace> id_vect;
                                                     // Haetaan poistettavan asiakasryhmän nimi -> Region.id
    if(!(pos = m_lstAsiakasryhmat.GetFirstSelectedItemPosition())) return;
    region = m_lstAsiakasryhmat.GetItemText(m_lstAsiakasryhmat.GetNextSelectedItem(pos), 0);
    if((vect = db.haeTaulusta("Region", "id, position", 2, "", 1, "", "Name", "=", region)).size() == 0) return;
    id = vect[0];
	position = vect[1];
                                                     // Haetaan kaikki asiakkaat jotka kuuluvat poistettavaan ryhmään
    s = (vect = db.haeTaulusta("WorkPlace", "id", 1, "", 1, "", "Region_id", "=", id)).size();
    for(i=0; i<s; i++)                               // Muodostetaan saaduista id:eistä asiakas-ItemDatat
	{ id_c.id = vect[i]; id_vect.push_back(id_c); }

    b = FALSE;                                       // !:! Tarkistetaan onko tehty töitä poistettavan asiakasryhmän kohteisiin (asiakkaille)
    s = id_vect.size();
    for(i=0; i<s; i++)
	{
      if((db.haeTaulusta("WorkUnit", "WorkPlace_id", 1, "", 1, "", "WorkPlace_id", "=", id_vect[i].id)).size() > 0)
	  { id_vect[i].kasitelty = RETURN_EXISTS; b = TRUE; }
      else
        id_vect[i].kasitelty = RETURN_NONE;
	}

    if(b)                                            // !:! Jos on, varoitetaan käyttäjää ja kysytään lisätoimenpiteistä
	{
      if(MessageBox(Props::i().lang("PPAGELISTAT_32"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO) == IDNO) return;
	}
    else                                             // !:! Muutoin kysytään vain varmistus
	{
      cs.Format(Props::i().lang("PPAGELISTAT_33"), region);
      if(MessageBox(cs, Props::e().m_app_title, MB_ICONQUESTION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO) == IDNO) return;
	}

    // Valittu poisto (IDYES), joten poistetaan asiakkaat WorkPlace-taulusta...
    GetParent()->EnableWindow(FALSE);                    // :-: Voi viedä jonkin aikaa, estä nappuloiden painelut
    for(i=0; i<s; i++)
	{
      if(id_vect[i].kasitelty == RETURN_EXISTS)      // Myös WorkUnit-taulun rivien poisto hyväksytty
        db.poistaYleinen("WorkUnit", "WorkPlace_id", id_vect[i].id, TRUE, "");

      db.poistaYleinen("WorkPlace", "id", id_vect[i].id, TRUE, "");  // Poista WorkPlace-taulusta
	}
    // Poista itse asiakasryhmä myös, järjestä positiot (1...n)
    db.poistaYleinen("Region", "id", id, TRUE, "");
    db.jarjestaPosition_fast("Region", REGION_POSITION, position, FALSE, "", "");

    GetParent()->EnableWindow(TRUE);                     // :-: OK, käsitelty

    paivitaAsiakasryhmat("", TRUE);                      // Poistot tehty, päivitä listat
    paivitaAsiakkaat("");

    ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_ASIAKASRYHMAT | SYNC_ASIAKKAAT);
}

void PpageListat::poistaAsiakas()
{ // Poistetaan valitut asiakkaat (ja asiakkaalle tehdyt työt, jos käyttäjä niin valitsee)
    BOOL b;
    CString cs;
    int i, s;
    DbSqlite db;
    POSITION pos;
    vector <ItemData_workplace*> pid_vect;

    pos = m_lstAsiakkaat.GetFirstSelectedItemPosition(); // Otetaan poistettavat asiakkaat vektoriin
    while(pos)     
    {
      i = m_lstAsiakkaat.GetNextSelectedItem(pos);
      if(m_lstAsiakkaat.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
        pid_vect.push_back((ItemData_workplace*) m_lstAsiakkaat.GetItemData(i));
	}

    if((s = pid_vect.size()) == 0) return;           // Pois jos ei valintoja

    b = FALSE;                                       // !:! Tarkistetaan onko tehty töitä poistettaviin kohteisiin
    for(i=0; i<s; i++)
	{
      if((db.haeTaulusta("WorkUnit", "WorkPlace_id", 1, "", 1, "", "WorkPlace_id", "=", pid_vect[i]->id)).size() > 0)
	  { pid_vect[i]->kasitelty = RETURN_EXISTS; b = TRUE; }
      else pid_vect[i]->kasitelty = RETURN_NONE;
	}

    if(b)                                            // !:! Jos on, varoitetaan käyttäjää ja kysytään lisätoimenpiteistä
	{
      cs = s > 1 ? Props::i().lang("PPAGELISTAT_34") : Props::i().lang("PPAGELISTAT_35");
      if(MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO) == IDNO) return;
	}
    else                                             // !:! Muutoin kysytään vain varmistus
      if(MessageBox(s > 1 ? Props::i().lang("PPAGELISTAT_36") : Props::i().lang("PPAGELISTAT_37"), Props::e().m_app_title, MB_ICONQUESTION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO) == IDNO) return;

    // Valittu poisto (IDYES), joten poistetaan asiakkaat WorkPlace-taulusta
    GetParent()->EnableWindow(FALSE);                    // :-: Voi viedä jonkin aikaa, estä nappuloiden painelut
    for(i=0; i<s; i++)
	{
      if(pid_vect[i]->kasitelty == RETURN_EXISTS)    // Myös WorkUnit-taulun rivien poisto hyväksytty
        db.poistaYleinen("WorkUnit", "WorkPlace_id", pid_vect[i]->id, TRUE, "");

      db.poistaYleinen("WorkPlace", "id", pid_vect[i]->id, TRUE, "");  // Poista WorkPlace-taulusta
	}
    GetParent()->EnableWindow(TRUE);                 // :-: OK, käsitelty

    // Järjestetään positiot, tarvitaan Region_id (pid:t vielä voimassa)
    db.jarjestaPosition("WorkPlace", "Region_id", pid_vect[0]->Region_id, "position", TRUE);

	                                                 // Poistetaan poistetut asiakkaat listasta (pid:t ei enää voimassa)
    while((pos = m_lstAsiakkaat.GetFirstSelectedItemPosition()))
	{
      i = m_lstAsiakkaat.GetNextSelectedItem(pos);
      m_lstAsiakkaat.DeleteItem(i);
	}

    // Päivitetään listat. Jos asiakkaita jäi listaan, näytä saman asiakasryhmän tiedot
    if((pos = m_lstAsiakasryhmat.GetFirstSelectedItemPosition()))
      cs = m_lstAsiakasryhmat.GetItemText(m_lstAsiakasryhmat.GetNextSelectedItem(pos), 0);
    else
      cs = "";
    m_lstAsiakkaat.GetItemCount() == 0 ? paivitaAsiakkaat("") : paivitaAsiakkaat(cs);

    ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_ASIAKKAAT);
}

void PpageListat::siirraAsiakasRyhmaan() 
{ // Siirrä valitut asiakkaat toiseen ryhmään
    int i;
    POSITION pos;
    DlgSiirraAsiakkaat dlg;
    vector <ItemData_workplace*> pid_vect;

    pos = m_lstAsiakkaat.GetFirstSelectedItemPosition();
    while(pos)                                       // Otetaan siirrettävät asiakkaat vektoriin
    {
      i = m_lstAsiakkaat.GetNextSelectedItem(pos);
      if(m_lstAsiakkaat.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
        pid_vect.push_back((ItemData_workplace*) m_lstAsiakkaat.GetItemData(i));
	}

    if((pos = m_lstAsiakasryhmat.GetFirstSelectedItemPosition()))    // Välitetään lähde region -> ei näytetä kohteissa
      dlg.m_region = m_lstAsiakasryhmat.GetItemText(m_lstAsiakasryhmat.GetNextSelectedItem(pos), 0);
    else
      dlg.m_region = "";

    dlg.m_asiakkaat = pid_vect;
    dlg.DoModal();

    paivitaAsiakasryhmat(dlg.m_region, TRUE);        // Aseta kohderyhmä näytetyksi
    paivitaAsiakkaat("");
    ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_ASIAKASRYHMAT | SYNC_ASIAKKAAT);
}

void PpageListat::lisaaLaskuttaja(int mode)
{
    int r;
    DbSqlite db;
    POSITION pos;
	DlgUusiLaskuttaja d;
    ItemData_biller *pid;

	pos = m_lstLaskuttajat.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		r = m_lstLaskuttajat.GetNextSelectedItem(pos);
		if(!(pid = (ItemData_biller*)m_lstLaskuttajat.GetItemData(r))) return;
	}
	d.m_pid = (mode == 0 ? NULL : pid);					// 0=uusi tapahtuma, 1=muokkaa entistä
	d.m_mode = mode;
	d.DoModal();										// Näytä muokkausdialogi, kutsuu OnOK:lla lisaaLaskuttaja(DlgUusiLaskuttaja *pd)
}

int PpageListat::lisaaLaskuttaja(DlgUusiLaskuttaja *pd)
{
    int r;
    DbSqlite db;

	if(pd->m_mode == 0)									// Lisäystila
		r = db.lisaaBiller(pd->m_name, pd->m_email, NULL, B_JUSTADD);
	else												// Muokkaustila
		r = db.paivitaBiller(pd->m_pid, 2,	BILLER_NAME,	pd->m_name,
											BILLER_EMAIL,	pd->m_email);

	if(r == RETURN_EXISTS)
	{
		MessageBox(Props::i().lang("PPAGELISTAT_38"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return r;
	}

	paivitaLaskuttajat(pd->m_name);

	if(pd->m_sync|SYNC_LASKUTTAJAT) paivitaAsiakkaat("");

	return RETURN_OK;
}

void PpageListat::poistaLaskuttaja()
{
    int s = 0;
    DbSqlite db;
    POSITION pos;
    CString cs, cs2, err;
    ItemData_biller *pid;
    vector <CString> vect;
    BOOL bt[3] = { FALSE, FALSE, FALSE };

    if((pos = m_lstLaskuttajat.GetFirstSelectedItemPosition()))      // Haetaan laskuttajan id
      if(!(pid = (ItemData_biller*)m_lstLaskuttajat.GetItemData(m_lstLaskuttajat.GetNextSelectedItem(pos)))) return;

    // Tutkitaan onko WorkUnit, TravelUnit tai WorkPlace tauluissa viitattu poistettavaan laskuttajaan
    if(db.haeTaulusta("WorkUnit", "Biller_id", 1, "", 1, "", "Biller_id", "=", pid->id).size() > 0) { bt[0] = TRUE; s++; }
    if(db.haeTaulusta("TravelUnit", "Biller_id", 1, "", 1, "", "Biller_id", "=", pid->id).size() > 0) { bt[1] = TRUE; s++; }
    if(db.haeTaulusta("WorkPlace", "Biller_id", 1, "", 1, "", "Biller_id", "=", pid->id).size() > 0) { bt[2] = TRUE; s++; }

    if(s > 0)                                        // On, kysy ohjeita
	{
      cs.Format("\r\n%s%s%s\r\n", bt[0] == TRUE ? Props::i().lang("PPAGELISTAT_39") : "", bt[1] == TRUE ? Props::i().lang("PPAGELISTAT_40") : "", bt[2] == TRUE ? Props::i().lang("PPAGELISTAT_41") : "");
      cs2.Format(Props::i().lang("PPAGELISTAT_42"), DFLT_BILLER);
      err.Format(Props::i().lang("PPAGELISTAT_43"), s > 1 ? Props::i().lang("PPAGELISTAT_44") : Props::i().lang("PPAGELISTAT_45"), cs, cs2);
	}
    else                                             // Ei, kysy silti poistetaanko
      err.Format(Props::i().lang("PPAGELISTAT_46"), pid->Name);
    if(MessageBox(err, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_YESNO) == IDNO) return;

    // Poistetaan laskuttaja, muutetaan osoittanaan DFLT_BILLER-laskutajaan
    if(db.poistaYleinen("Biller", "id", pid->id, TRUE, "") == RETURN_OK)
	{
      vect = db.haeTaulusta("Biller", "id", 1, "", 1, "", "Name", "=", DFLT_BILLER);
      if(bt[0]) db.paivitaYleinen("WorkUnit", "Biller_id", pid->id, vect[0], FALSE);   //
      if(bt[1]) db.paivitaYleinen("TravelUnit", "Biller_id", pid->id, vect[0], FALSE); //
      if(bt[2]) db.paivitaYleinen("WorkPlace", "Biller_id", pid->id, vect[0], FALSE);  //

      paivitaAsiakkaat("");                          // Päivitä listat
      paivitaLaskuttajat("");

	  ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_LASKUTTAJAT);
	}
}

void PpageListat::lisaaTyotyyppi(int mode)
{
    int r;
    DbSqlite db;
    POSITION pos;
	DlgUusiTyotyyppi d;
    ItemData_type *pid;

	pos = m_lstTyotyypit.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		r = m_lstTyotyypit.GetNextSelectedItem(pos);
		if(!(pid = (ItemData_type*)m_lstTyotyypit.GetItemData(r))) return;
	}
	d.m_pid = (mode == 0 ? NULL : pid);					// 0=uusi tapahtuma, 1=muokkaa entistä
	d.m_mode = mode;
	d.DoModal();										// Näytä muokkausdialogi, kutsuu OnOK:lla lisaaTyotyyppi(DlgUusiTyotyyppi *pd)
}

int  PpageListat::lisaaTyotyyppi(DlgUusiTyotyyppi *pd)
{
    int r;
    DbSqlite db;

	if(pd->m_mode == 0)									// Lisäystila
		r = db.lisaaWorkType(pd->m_name, pd->m_productnumber, WORK, "", "", "", "", "", WORKTYPE_POSITION_WORK, NULL, WT_JUSTADD);
	else												// Muokkaustila
		r = db.paivitaWorkType(pd->m_pid, 2,	WORKTYPE_NAME,			pd->m_name,
												WORKTYPE_PRODUCTNUMBER,	pd->m_productnumber);

	if(r == RETURN_EXISTS)
	{
		MessageBox(Props::i().lang("PPAGELISTAT_47"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return r;
	}

	paivitaTyotyypit(pd->m_name);

	((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, pd->m_sync);

	return RETURN_OK;
}

void PpageListat::poistaTyotyyppi()
{
    int i, s = 0;
    DbSqlite db;
    POSITION pos;
    CString cs, cs2, err, name, id, position;
    ItemData_type *pid;
    vector <CString> vect;

    if((pos = m_lstTyotyypit.GetFirstSelectedItemPosition()))      // Haetaan työtyypin/tuotteen id ja nimi
	{
      i = m_lstTyotyypit.GetNextSelectedItem(pos);
      if(!(pid = (ItemData_type*)m_lstTyotyypit.GetItemData(i))) return;
	  name = pid->Name;//m_lstTyotyypit.GetItemText(i, 0);
	}

    // Tutkitaan onko WorkUnit taulussa viitattu poistettavaan työtyyppiin
    if(db.haeTaulusta("WorkUnit", "WorkType_id", 1, "", 1, "", "WorkType_id", "=", pid->id).size() > 0) s++;

    if(s > 0)                                        // On, ilmoitetaan
	{ err.Format(Props::i().lang("PPAGELISTAT_48"), name); s = MB_OK; }
    else                                             // Ei, kysy silti poistetaanko
	{ err.Format(Props::i().lang("PPAGELISTAT_49"), name); s = MB_YESNO; }
    if(MessageBox(err, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|s) == IDNO) return;
    if(s == MB_OK) return;

    // Poistetaan tyyppi, järjestetään positiot (1...n)
    if(db.poistaYleinen("WorkType", "id", pid->id, TRUE, "") == RETURN_OK)
	{
      db.jarjestaPosition_fast("WorkType", WORKTYPE_POSITION_WORK, pid->position, TRUE, "", "");
      paivitaTyotyypit("");

	  ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TYOTYYPIT);
	}
}

void PpageListat::lisaaTuoteryhma()
{
    DbSqlite db;
    CString name, cs;
    vector <CString> vect;

    if((vect = db.haeTaulusta("ProductGroup", "max(id)", 1, "", 0)).size() == 0) return;
    name.Format(Props::i().lang("PPAGELISTAT_50"), atoi(vect[0]) + 1);
    if(db.lisaaProductGroup(name, &cs) != RETURN_OK) return;
    paivitaTuoteryhmat(name, TRUE);
    paivitaTuotteet("");
    naytaEdit(&m_lstTuoteryhmat);

	((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TUOTERYHMAT);
}

void PpageListat::poistaTuoteryhma()
{
    int i, l, s = 0;
    DbSqlite db;
    POSITION pos;
    CString cs, cs2, err, name, id, position;
    ItemData_productgroup *pid;
    vector <CString> vect;

    if((pos = m_lstTuoteryhmat.GetFirstSelectedItemPosition()))      // Haetaan tuoteryhmän itemdata ja nimi
	{
      i = m_lstTuoteryhmat.GetNextSelectedItem(pos);
      if(!(pid = (ItemData_productgroup*)m_lstTuoteryhmat.GetItemData(i))) return;
      name = m_lstTuoteryhmat.GetItemText(i, 0);
	}

    // Tutkitaan onko WorkUnit taulussa viitattu poistettavan tuoteryhmän tuotteisiin
    l = (vect = db.haeTaulusta("WorkType", "id", 1, "", 1, "", "ProductGroup_id", "=", pid->id)).size();
    for(i=0; i<l; i++)
    { if(db.haeTaulusta("WorkUnit", "WorkType_id", 1, "", 1, "", "WorkType_id", "=", vect[i]).size() > 0) s++; }

    if(s > 0)                                        // On, ilmoitetaan
	{ err.Format(Props::i().lang("PPAGELISTAT_51"), name); s = MB_OK; }
    else                                             // Ei, kysy silti poistetaanko
	{ err.Format(Props::i().lang("PPAGELISTAT_52"), name); s = MB_YESNO; }
    if(MessageBox(err, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|s) == IDNO) return;
    if(s == MB_OK) return;

    // Poistetaan tyyppi, järjestetään positiot (1...n)
    if(db.poistaYleinen("ProductGroup", "id", pid->id, TRUE, "") == RETURN_OK)
	{
      db.jarjestaPosition_fast("ProductGroup", PRODUCTGROUP_POSITION, pid->position, TRUE, "", "");
      paivitaTuoteryhmat("", TRUE);
      paivitaTuotteet("");

	  ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TUOTERYHMAT | SYNC_TUOTTEET);
	}
}

void PpageListat::lisaaTuote(int mode)
{
    int r;
    DbSqlite db;
    POSITION pos;
	DlgUusiTuote d;
    ItemData_type *pid;

    // Asiakas lisätään valittuun tuoteryhmään => hae asiakasryhmä ensin
	if(!(pos = m_lstTuoteryhmat.GetFirstSelectedItemPosition())) return;
	r = m_lstTuoteryhmat.GetNextSelectedItem(pos);
	d.m_productgroup_name = m_lstTuoteryhmat.GetItemText(r, 0);

	pos = m_lstTuotteet.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		r = m_lstTuotteet.GetNextSelectedItem(pos);
		if(!(pid = (ItemData_type*)m_lstTuotteet.GetItemData(r))) return;
	}
	d.m_pid = (mode == 0 ? NULL : pid);					// 0=uusi tapahtuma, 1=muokkaa entistä
	d.m_mode = mode;
	d.DoModal();										// Näytä muokkausdialogi, kutsuu OnOK:lla lisaaTuote(DlgUusiTuote *pd)
}

int PpageListat::lisaaTuote(DlgUusiTuote *pd)
{
    int r;
    DbSqlite db;
    vector <CString> pc_vect;

	if(pd->m_mode == 0)									// Lisäystila
	{
		db.lisaaUnit(pd->m_unit);
		if((pc_vect = db.haeTaulusta("ProductGroup", "id", 1, "", 1, "", "Name", "=", pd->m_productgroup_name)).size() == 0) return RETURN_OK;
		r = db.lisaaWorkType(pd->m_name, pd->m_productnumber, PRODUCT, pd->m_unit, pd->m_purchaseprice, pd->m_sellprice, pd->m_alv, pc_vect[0], WORKTYPE_POSITION_PRODUCT, NULL, WT_JUSTADD);
	}
	else												// Muokkaustila
	{
		db.lisaaUnit(pd->m_unit);
		r = db.paivitaWorkType(pd->m_pid, 6,	WORKTYPE_NAME,			pd->m_name,
												WORKTYPE_PRODUCTNUMBER,	pd->m_productnumber,
												WORKTYPE_UNIT,			pd->m_unit,
												WORKTYPE_PURCHASEPRICE,	pd->m_purchaseprice,
												WORKTYPE_SELLPRICE,		pd->m_sellprice,
												WORKTYPE_ALV,			pd->m_alv);
	}

	if(r == RETURN_EXISTS)
	{
		MessageBox(Props::i().lang("PPAGELISTAT_53"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return r;
	}

	paivitaTuotteet(pd->m_name);

	((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, pd->m_sync);

	return RETURN_OK;
}

void PpageListat::poistaTuote()
{
    int i, s = 0;
    DbSqlite db;
    POSITION pos;
    CString cs, cs2, err, name, id, position;
    ItemData_type *pid;
    vector <CString> vect;

    if((pos = m_lstTuotteet.GetFirstSelectedItemPosition()))      // Haetaan työtyypin/tuotteen id ja nimi
	{
      i = m_lstTuotteet.GetNextSelectedItem(pos);
      if(!(pid = (ItemData_type*)m_lstTuotteet.GetItemData(i))) return;
	  name = pid->Name;//m_lstTuotteet.GetItemText(i, 0);
	}

    // Tutkitaan onko WorkUnit taulussa viitattu poistettavaan tuotteeseen
    if(db.haeTaulusta("WorkUnit", "WorkType_id", 1, "", 1, "", "WorkType_id", "=", pid->id).size() > 0) s++;
    if(s > 0)                                        // On, ilmoitetaan
	{ err.Format(Props::i().lang("PPAGELISTAT_54"), name); s = MB_OK; }
    else                                             // Ei, kysy silti poistetaanko
	{ err.Format(Props::i().lang("PPAGELISTAT_55"), name); s = MB_YESNO; }
    if(MessageBox(err, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|s) == IDNO) return;
    if(s == MB_OK) return;

    // Poistetaan tyyppi, järjestetään positiot (1...n)
    if(db.poistaYleinen("WorkType", "id", pid->id, TRUE, "") == RETURN_OK)
	{
      db.jarjestaPosition_fast("WorkType", WORKTYPE_POSITION_PRODUCT, pid->position, TRUE, WORKTYPE_PRODUCTGROUP_ID, pid->ProductGroup_id);
      paivitaTuotteet("");

	  ((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_LISTAT, SYNC_TUOTTEET);
	}
}

void PpageListat::paivitaTila()
{
	paivitaLaskuttajat("");
	paivitaTyotyypit("");
    paivitaTuoteryhmat("", TRUE);
    paivitaTuotteet("");
}

void PpageListat::paivitaAsiakasryhmat(CString region, BOOL antiloop)
{
    CString cs, bname;
    DbSqlite db;
    int i, f, s;
    LVFINDINFO lvfi;
    ItemData_region *pid_r;
    vector <CString> vect;

    if(antiloop) m_updRegions = FALSE;               // Estetään viestien kierto

    m_lstAsiakasryhmat.DeleteAllItems();             // Asiakasryhmät listaan jos päivitys sallittu
    if((s = (vect = db.haeTaulusta("Region", "Name, id, position", 3, "position", 0)).size()) > 0)
	{
      for(i=0; i<s; i+=3)
	  {
        pid_r = new ItemData_region;
        pid_r->id = vect[i + 1];
        pid_r->Name = vect[i];
        pid_r->position = vect[i + 2];
        f = m_lstAsiakasryhmat.InsertItem(LVIF_TEXT, i / 2, vect[i], 0, 0, 0, 0);
        if(f != -1) m_lstAsiakasryhmat.SetItemData(f, (DWORD)pid_r);
	  }
	}

    if(region != "")                                 // : valitaan, jos on annettu, region
	{ lvfi.flags = LVFI_STRING; lvfi.psz = region; f = m_lstAsiakasryhmat.FindItem(&lvfi, -1); }
    else f = 0;                                      // : muutoin valitaan ensimmäinen listasta
    if(f != -1)                                      // : asetetaan valinta
	{ m_lstAsiakasryhmat.SetItemState(f, LVIS_SELECTED, LVIS_SELECTED); m_lstAsiakasryhmat.SetSelectionMark(f); m_lstAsiakasryhmat.EnsureVisible(f, FALSE); }

    if(antiloop) m_updRegions = TRUE;
}

void PpageListat::paivitaAsiakkaat(CString workplace)
{
    CString cs, bname;
    DbSqlite db;
    int i, f, s, t;
    LVFINDINFO lvfi;
    POSITION pos;
    ItemData_region *pid_r;
    ItemData_workplace *pid;
    vector <CString> vect;
    vector <CString> b_vect;
    vector <CString> vect_t;

    m_lstAsiakkaat.DeleteAllItems();                 // Asiakkaat listaan valitun regionin mukaan, pois jos ei saada regioneita

    if((pos = m_lstAsiakasryhmat.GetFirstSelectedItemPosition()))
      pid_r = (ItemData_region*)m_lstAsiakasryhmat.GetItemData(m_lstAsiakasryhmat.GetNextSelectedItem(pos));
    else return;                                     // Haetaan valitun asiakasryhmän ItemData, pois jos ei valintoja

    if((s = (vect = db.haeTaulusta("WorkPlace", "Name, Address, Biller_id, Note, Shortnote, Info, CustomerNumber, position, id", WORKPLACE_COLS, "position", 1, "", "Region_id", "=", pid_r->id)).size()) > 0)
	{
      for(i=0; i<s; i+=WORKPLACE_COLS)
	  {
        t = m_lstAsiakkaat.GetItemCount(); 
        f = m_lstAsiakkaat.InsertItem(LVIF_TEXT|LVIF_IMAGE, t, "", 0, 0, 2, 0);    
		m_lstAsiakkaat.SetItem(f, 1, LVIF_TEXT, vect[i], 0, 0, 0, 0);        // Name
        m_lstAsiakkaat.SetItem(f, 2, LVIF_TEXT, vect[i + 1], 0, 0, 0, 0);    // Address
                                                                             // Biller.Name
        b_vect = db.haeTaulusta("Biller", "Name", 1, "", 1, "", "id", "=", vect[i + 2]);
        if(b_vect.size() > 0) bname = b_vect[0]; else bname = "";
        m_lstAsiakkaat.SetItem(f, 3, LVIF_TEXT, bname, 0, 0, 0, 0);
        m_lstAsiakkaat.SetItem(f, 4, LVIF_TEXT, vect[i + 3], 0, 0, 0, 0);    // Note
        m_lstAsiakkaat.SetItem(f, 5, LVIF_TEXT, vect[i + 4], 0, 0, 0, 0);    // Shortnote
        m_lstAsiakkaat.SetItem(f, 6, LVIF_TEXT, vect[i + 5], 0, 0, 0, 0);    // Info
        m_lstAsiakkaat.SetItem(f, 7, LVIF_TEXT, vect[i + 6], 0, 0, 0, 0);    // Customer number

        pid = new ItemData_workplace;
        pid->Region_id = pid_r->id;
        pid->Name = vect[i];
        pid->Address= vect[i + 1];
        pid->Biller_id = vect[i + 2];
        pid->Note = vect[i + 3];
        pid->Shortnote= vect[i + 4];
        pid->Info = vect[i + 5];
        pid->CustomerNumber = vect[i + 6];
        pid->position = vect[i + 7];
        pid->id = vect[i + 8];
        m_lstAsiakkaat.SetItemData(f, (DWORD)pid);
	  }
	}

    if(workplace != "")                              // : valitaan, jos on annettu, workplace, muutoin valitaan listan ensimmäinen
	{ lvfi.flags = LVFI_STRING; lvfi.psz = workplace; f = m_lstAsiakkaat.FindItem(&lvfi, -1); }
    else f = 0;                                      // : muutoin valitaan ensimmäinen listasta
    if(f != -1)                                      // : asetetaan valinta
	{ m_lstAsiakkaat.SetItemState(f, LVIS_SELECTED, LVIS_SELECTED); m_lstAsiakkaat.SetSelectionMark(f); m_lstAsiakkaat.EnsureVisible(f, FALSE); }
}

void PpageListat::paivitaLaskuttajat(CString name)
{
    CString cs;
    DbSqlite db;
    int i, f, s, t;
    LVFINDINFO lvfi;
    ItemData_biller *pid;
    vector <CString> vect;
    vector <CString> vect_t;

    m_lstLaskuttajat.DeleteAllItems();
    vect = db.haeTaulusta("Biller", "Name, Email, id, position", 4, "position", 1, "", "Name", "<>", DFLT_BILLER);
    s = vect.size();
    for(i=0; i<s; i+=4)
	{
      t = m_lstLaskuttajat.GetItemCount(); 
      f = m_lstLaskuttajat.InsertItem(LVIF_TEXT|LVIF_IMAGE, t, "", 0, 0, 2, 0);
      m_lstLaskuttajat.SetItem(f, 1, LVIF_TEXT, vect[i], 0, 0, 0, 0);      // Name
      m_lstLaskuttajat.SetItem(f, 2, LVIF_TEXT, vect[i + 1], 0, 0, 0, 0);  // Email

      pid = new ItemData_biller;
      pid->Name= vect[i];
      pid->Email = vect[i + 1];
      pid->id = vect[i + 2];
	  pid->position = vect[i + 3];
      m_lstLaskuttajat.SetItemData(f, (DWORD)pid);
	}

    if(name != "")                              // : valitaan, jos on annettu, name, muutoin valitaan listan ensimmäinen
	{ lvfi.flags = LVFI_STRING; lvfi.psz = name; f = m_lstLaskuttajat.FindItem(&lvfi, -1); }
    else f = 0;                                      // : muutoin valitaan ensimmäinen listasta
    if(f != -1)                                      // : asetetaan valinta
	{ m_lstLaskuttajat.SetItemState(f, LVIS_SELECTED, LVIS_SELECTED); m_lstLaskuttajat.SetSelectionMark(f); m_lstLaskuttajat.EnsureVisible(f, FALSE); }
}

void PpageListat::paivitaTyotyypit(CString name)
{
    CString cs;
    DbSqlite db;
    int i, f, s, t;
    LVFINDINFO lvfi;
    ItemData_type *pid;
    vector <CString> vect;
	vector <CString> vectr;

    m_lstTyotyypit.DeleteAllItems();
    vect = db.haeTaulusta("WorkType", "Name, ProductNumber, position_work, id", 4, WORKTYPE_POSITION_WORK, 1, "", "Type", "=", WORK);
    s = vect.size();
    for(i=0; i<s; i+=4)
	{
      t = m_lstTyotyypit.GetItemCount();

      f = m_lstTyotyypit.InsertItem(LVIF_TEXT|LVIF_IMAGE, t, "", 0, 0, 3, 0);  
	  m_lstTyotyypit.SetItem(f, 1, LVIF_TEXT, vect[i], 0, 0, 0, 0);      // Name
	  m_lstTyotyypit.SetItem(f, 2, LVIF_TEXT, vect[i + 1], 0, 0, 0, 0);  // ProductNumber

      pid = new ItemData_type;
      pid->Name= vect[i + 0];
      pid->ProductNumber = vect[i + 1];
      pid->position = vect[i + 2];
      pid->id = vect[i + 3];
      pid->Type = WORK;

      m_lstTyotyypit.SetItemData(f, (DWORD)pid);
	}

    if(name != "")                              // : valitaan, jos on annettu, name, muutoin valitaan listan ensimmäinen
	{ lvfi.flags = LVFI_STRING; lvfi.psz = name; f = m_lstTyotyypit.FindItem(&lvfi, -1); }
    else f = 0;                                      // : muutoin valitaan ensimmäinen listasta
    if(f != -1)                                      // : asetetaan valinta
	{ m_lstTyotyypit.SetItemState(f, LVIS_SELECTED, LVIS_SELECTED); m_lstTyotyypit.SetSelectionMark(f); m_lstTyotyypit.EnsureVisible(f, FALSE); }
}

void PpageListat::paivitaTuoteryhmat(CString productgroup, BOOL antiloop)
{
    CString cs, bname;
    DbSqlite db;
    int i, f, s;
    LVFINDINFO lvfi;
    ItemData_productgroup *pid_p;
    vector <CString> vect;

    if(antiloop) m_updProductgroups = FALSE;               // Estetään viestien kierto

    m_lstTuoteryhmat.DeleteAllItems();               // Tuoteryhmät listaan jos päivitys sallittu
    if((s = (vect = db.haeTaulusta("ProductGroup", "Name, id, position", 3, "position", 0)).size()) > 0)
	{
      for(i=0; i<s; i+=3)
	  {
        pid_p = new ItemData_productgroup;
        pid_p->Name = vect[i];
        pid_p->id = vect[i + 1];
        pid_p->position = vect[i + 2];
        f = m_lstTuoteryhmat.InsertItem(LVIF_TEXT, i / 2, vect[i], 0, 0, 0, 0);
        if(f != -1) m_lstTuoteryhmat.SetItemData(f, (DWORD)pid_p);
	  }
	}

    if(productgroup != "")                           // : valitaan, jos on annettu, productgroup
	{ lvfi.flags = LVFI_STRING; lvfi.psz = productgroup; f = m_lstTuoteryhmat.FindItem(&lvfi, -1); }
    else f = 0;                                      // : muutoin valitaan ensimmäinen listasta
    if(f != -1)                                      // : asetetaan valinta
	{ m_lstTuoteryhmat.SetItemState(f, LVIS_SELECTED, LVIS_SELECTED); m_lstTuoteryhmat.SetSelectionMark(f); m_lstAsiakasryhmat.EnsureVisible(f, FALSE); }

    if(antiloop) m_updProductgroups = TRUE;
}

void PpageListat::paivitaTuotteet(CString name)
{
    DbSqlite db;
    POSITION pos;
    int i, f, s, t;
    LVFINDINFO lvfi;
    CString cs, bname;
    ItemData_type *pid;
    vector <CString> vect;
    vector <CString> b_vect;
    vector <CString> vect_t;
    ItemData_productgroup *pid_p;

    m_lstTuotteet.DeleteAllItems();                  // Tuotteet listaan valitun tuoteryhmän mukaan, pois jos ei saada tuoteryhmiä

    if((pos = m_lstTuoteryhmat.GetFirstSelectedItemPosition()))
      pid_p = (ItemData_productgroup*)m_lstTuoteryhmat.GetItemData(m_lstTuoteryhmat.GetNextSelectedItem(pos));
    else return;                                     // Haetaan valitun tuoteryhmän ItemData

    if((s = (vect = db.haeTaulusta("WorkType", "Name, ProductNumber, ProductGroup_id, Unit, PurchasePrice, SellPrice, Alv, id, position_product", WORKTYPE_COLS - 2, WORKTYPE_POSITION_PRODUCT, 2, "", "ProductGroup_id", "=", pid_p->id, "AND", "Type", "=", PRODUCT)).size()) > 0)
	{
      for(i=0; i<s; i+=(WORKTYPE_COLS - 2))
	  {
        t = m_lstTuotteet.GetItemCount();
        f = m_lstTuotteet.InsertItem(LVIF_TEXT|LVIF_IMAGE, t, "", 0, 0, 5, 0);
        m_lstTuotteet.SetItem(f, 1, LVIF_TEXT, vect[i], 0, 0, 0, 0);							// Name
        m_lstTuotteet.SetItem(f, 2, LVIF_TEXT, vect[i + 1], 0, 0, 0, 0);						// ProductNumber
        m_lstTuotteet.SetItem(f, 3, LVIF_TEXT, vect[i + 3], 0, 0, 0, 0);						// Unit
        m_lstTuotteet.SetItem(f, 4, LVIF_TEXT, db.fixFloat(vect[i + 4], FALSE), 0, 0, 0, 0);	// PurchasePrice
        m_lstTuotteet.SetItem(f, 5, LVIF_TEXT, db.fixFloat(vect[i + 5], FALSE), 0, 0, 0, 0);	// SellPrice
        m_lstTuotteet.SetItem(f, 6, LVIF_TEXT, db.fixFloat(vect[i + 6], FALSE), 0, 0, 0, 0);	// Alv

        pid = new ItemData_type;
        pid->Name = vect[i];
        pid->ProductNumber = vect[i + 1];
        pid->ProductGroup_id = vect[i + 2];
        pid->Unit= vect[i + 3];
        pid->PurchasePrice = vect[i + 4];
        pid->SellPrice = vect[i + 5];
        pid->Alv = vect[i + 6];
        pid->id = vect[i + 7];
        pid->position = vect[i + 8];
		pid->Type = PRODUCT;
        m_lstTuotteet.SetItemData(f, (DWORD)pid);
	  }
	}

    if(name != "")                                   // : valitaan, jos on annettu, name, muutoin valitaan listan ensimmäinen
	{ lvfi.flags = LVFI_STRING; lvfi.psz = name; f = m_lstTuotteet.FindItem(&lvfi, -1); }
    else f = 0;                                      // : muutoin valitaan ensimmäinen listasta
    if(f != -1)                                      // : asetetaan valinta
	{ m_lstTuotteet.SetItemState(f, LVIS_SELECTED, LVIS_SELECTED); m_lstTuotteet.SetSelectionMark(f); m_lstAsiakkaat.EnsureVisible(f, FALSE); }
}

void PpageListat::naytaEdit(ListctrlRaportit *m_plst)
{ // Näytä CEdit nimen muokkaukselle
    int s;
    POINT point;
    POSITION pos;
    LPARAM lparam;

    if((pos = m_plst->GetFirstSelectedItemPosition()))
	{
      s = m_plst->GetNextSelectedItem(pos);
      m_plst->SetSelectionMark(s);
      m_plst->GetItemPosition(s, &point);
      lparam = MAKELONG(point.x, point.y);           // wLow (xPos), wHigh (yPos)
      m_plst->PostMessage(WM_LBUTTONDBLCLK, 0, lparam);
	}
}

void PpageListat::deltapos(CString table, CString id_srce, CString group_id, CString group_field, CString pos_field, int top_position, int direction, int old_list_pos, ListctrlRaportit *pLst)
{
    int new_list_pos;
    DWORD dw_o, dw_n;
    DbSqlite db;
    vector <CString> vect;
    CString pos_srce, pos_dest, id_dest, cs;

	if(pLst->GetItemCount() < 2) return;             // Täytyy olla vähintään kaksi itemiä

    if((vect = db.haeTaulusta(table, pos_field, 1, "", 1, "", "id", "=", id_srce)).size() == 0) return;
    pos_srce = vect[0];                              // Hae siirrettävän position kentän arvo

	if(direction == -1)                      // YLÖSPÄIN LISTALLA
	{
      if(atoi(pos_srce) == top_position) return;         // pois, valmiiksi ylimpänä listassa

      pos_dest.Format("%d", atoi(pos_srce) - 1);         // hae yhtä ylempänä listalla olevan id yhtä pienemmällä positionilla
      if(group_id == "")
	  { if((vect = db.haeTaulusta(table, "id", 1, "", 1, "", pos_field, "=", pos_dest)).size() == 0) return; }
      else
	  { if((vect = db.haeTaulusta(table, "id", 1, "", 2, "", pos_field, "=", pos_dest, "AND", group_field, "=", group_id)).size() == 0) return; }
      id_dest = vect[0];
      new_list_pos = VK_UP;
	}
    else                                             // ALASPÄIN LISTALLA
	{
      if(group_id == "")
	  { if((vect = db.haeTaulusta(table, "max(" + pos_field + ")", 1, "", 0)).size() == 0) return; }
      else
	  { if((vect = db.haeTaulusta(table, "max(" + pos_field + ")", 1, "", 1, "", group_field, "=", group_id)).size() == 0) return; }

      if(atoi(vect[0]) == atoi(pos_srce)) return;        // pois, valmiiksi alimpana listassa

      pos_dest.Format("%d", atoi(pos_srce) + 1);         // hae yhtä alempana listalla olevan id yhtä suuremmalla positionilla
      if(group_id == "")
	  { if((vect = db.haeTaulusta(table, "id", 1, "", 1, "", pos_field, "=", pos_dest)).size() == 0) return; }
      else
	  { if((vect = db.haeTaulusta(table, "id", 1, "", 2, "", pos_field, "=", pos_dest, "AND", group_field, "=", group_id)).size() == 0) return; }
      id_dest = vect[0];
      new_list_pos = VK_DOWN;
	}
                                                     // vaihda positionit tietokannassa
    db.paivitaYleinen_id(table, pos_field, pos_dest, "", "", id_srce, FALSE);
    db.paivitaYleinen_id(table, pos_field, pos_srce, "", "", id_dest, FALSE);

    m_updRegions = FALSE;                                // Estä listojen päivitykset
    m_updProductgroups = FALSE;

	new_list_pos = (new_list_pos == VK_UP ? old_list_pos - 1 : old_list_pos + 1); // Indeksi seuraavaan listan alkioon (ylös tai alaspäin)

	int lp, lh = pLst->GetHeaderCtrl()->GetItemCount();  // Vaihdetaan listan tekstit (koko rivi!!!)
	for(lp=0; lp<lh; lp++)
	{
	    pos_srce = pLst->GetItemText(old_list_pos, lp);
		pos_dest = pLst->GetItemText(new_list_pos, lp);
	    pLst->SetItemText(old_list_pos, lp, pos_dest);
		pLst->SetItemText(new_list_pos, lp, pos_srce);
	}

    dw_o = pLst->GetItemData(old_list_pos);              // Vaihdetaan listan itemdatat ja itedatoissa positionit
    dw_n = pLst->GetItemData(new_list_pos);
	cs = ((Item*)dw_o)->position;                        // :: vaihda positionit luokissa
    ((Item*)dw_o)->position = ((Item*)dw_n)->position;
    ((Item*)dw_n)->position = cs;
    pLst->SetItemData(old_list_pos, dw_n);               // :: vaihda itemdatat
    pLst->SetItemData(new_list_pos, dw_o);

    pLst->SetItemState(old_list_pos, 0, LVIS_SELECTED);  // Vaihda valinnat
    pLst->SetItemState(new_list_pos, LVIS_SELECTED, LVIS_SELECTED);
    pLst->SetSelectionMark(new_list_pos);
    pLst->EnsureVisible(new_list_pos, FALSE);

    m_updRegions = TRUE;                                 // Salli päivitykset taas
    m_updProductgroups = TRUE;
}

void PpageListat::movepos(int srce, int dest, ListctrlRaportit *pLst)
{
    Item *pid;
    DbSqlite db;
	LVITEM lvitem;
    vector <CString> vect;
    CString position, table, pos_field;
    int i, ic , item, max_item, top, bottom;

    if(srce == dest)                                        // ei siirtoa
      return;
	else if(srce == pLst->GetItemCount() - 1 && dest == -1) // Listan viimeistä ei pysty siirtämään viimeiseksi
      return;
	else if(pLst->GetItemCount() <= 1)                      // Listan ainota itemiä ei voi siirrellä
      return;

	GetParent()->EnableWindow(FALSE);                       // Siirto vie aikansa, näytä tiimalasi ja estä painelut
    BeginWaitCursor();

    // SIIRTO LISTALLA ////////////////////////////////////////////////////////////////////////
    ic = pLst->GetHeaderCtrl()->GetItemCount();

    if(dest == -1)                                       // siirto alimmaiseksi listaan?
      dest = pLst->GetItemCount();

    pLst->m_allowDeleteItemData = FALSE;                 // Tilapäisesti estä item dataan asetetun Item-instanssin muistin vapauttaminen (muuten pLst->DeleteItem(...) vapauttaisi sen)

    DWORD item_data = pLst->GetItemData(srce);           // item data
	ZeroMemory(&lvitem, sizeof(LVITEM));                 // kuvan indeksi
	lvitem.mask = LVIF_IMAGE;
	lvitem.iItem = srce;
	lvitem.iSubItem = 0;
	pLst->GetItem(&lvitem);
    for(i=0; i<ic; i++)                                  // ja stringit talteen lähteestä
      vect.push_back(pLst->GetItemText(srce, i));

    if((dest - srce) == 1)                               // vaihda vierekkäiset (erikoistapaus ylhäältä alaspäin siirto)
      pLst->DeleteItem(srce);
	else												 // poista lähde listalta (normaalissa tapauksessa)
      pLst->DeleteItem(srce);

	item = pLst->InsertItem(dest, vect[0], lvitem.iImage); // "siirrä" eli luo uusi itemi kohteen paikalle
    for(i=1; i<ic; i++)                                  // loput tekstit ja item data uuteen itemiin
		pLst->SetItem(item, i, LVIF_TEXT, vect[i], 0, 0, 0, 0);
    pLst->SetItemData(item, item_data);


	pLst->m_allowDeleteItemData = TRUE;                  // Sallitaan taas Item-instanssin muistin vapauttaminen

    // TIETOKANNAN TAULU JA JÄRJESTYSLUVUN KENTTÄ /////////////////////////////////////////////
    if(pLst->m_omistaja == O_ASIAKASRYHMA)
	{ table = "Region"; pos_field = REGION_POSITION; }
    else if(pLst->m_omistaja == O_ASIAKAS)
	{ table = "WorkPlace"; pos_field = WORKPLACE_POSITION; }
    else if(pLst->m_omistaja == O_LASKUTTAJA)
	{ table = "Biller"; pos_field = BILLER_POSITION; }
    else if(pLst->m_omistaja == O_TYOTYYPPI)
	{ table = "WorkType"; pos_field = WORKTYPE_POSITION_WORK; }
    else if(pLst->m_omistaja == O_TUOTERYHMA)
	{ table = "ProductGroup"; pos_field = PRODUCTGROUP_POSITION; }
    else if(pLst->m_omistaja == O_TUOTE)
	{ table = "WorkType"; pos_field = WORKTYPE_POSITION_PRODUCT; }

    // KORJATAAN JÄRJESTYSLUKU - VÄLILTÄ YLIMMÄSTÄ ITEMISTÄ ALIMPAAN //////////////////////////
	max_item = min(max(srce, dest), pLst->GetItemCount() - 1); // varmista, että ei mene listan ohi alin kohta
    for(i=min(srce, dest); i<=max_item; i++)
	{
      position.Format("%d", i+1);                        // uusi järjestysluku listalla

	  pid = (Item*)pLst->GetItemData(i);                 // Järjestysluvun muutos item dataan
      pid->position = position;
                                                         // ja tietokantaan (huom! id yksilöivänä)
      db.paivitaYleinen_id(table, pos_field, position, "", "", pid->id, FALSE);
	}

	// ASETA LOPUKSI VALITUKSI, PALAUTA KURSORI JA SALLI PAINELUT /////////////////////////////
    LVFINDINFO lvfi;
	lvfi.flags = LVFI_STRING; lvfi.psz = vect[1];
    item = pLst->FindItem(&lvfi, -1);
	pLst->SetSelectionMark(item);
    pLst->SetItemState(item, (LVIS_SELECTED | LVIS_FOCUSED), (LVIS_SELECTED | LVIS_FOCUSED));

	GetParent()->EnableWindow(TRUE);
    EndWaitCursor();
}

void PpageListat::email()
{
    DlgSMTP dlg;

    dlg.m_mode = MODE_EMAIL_LISTAT;
    dlg.DoModal();
}

void PpageListat::etsi(int key)
{
    int s, f;
    DlgEtsi *pdlg;
    LVFINDINFO lvfi;

    pdlg = &Props::e().m_dlgEtsi;

    if(pdlg->m_vect.size() == 0 || key == KEY_CTRLF) // Uusi haku
	{ if(pdlg->DoModal() != IDOK) return; }
    else                                             // Hae seuraava
	{ if(++pdlg->m_pos == pdlg->m_count) pdlg->m_pos = 0; }

    s = pdlg->m_pos * 4;
    if(s > pdlg->m_vect.size() || s < 0) return;                       // Varmista, että ei osoiteta olemattomaan alkioon vektorissa

    // Valitaan asiakasryhmä ja etsitty asiakas
    lvfi.flags = LVFI_STRING; lvfi.psz = pdlg->m_vect[s + 3];
    if((f = m_lstAsiakasryhmat.FindItem(&lvfi, -1)) != -1)
	{
      m_lstAsiakasryhmat.SetSelectionMark(f);
      m_lstAsiakasryhmat.SetItemState(f, LVIS_SELECTED, LVIS_SELECTED);// Valitaan etsityn asiakkaan asiakasryhmä
      m_lstAsiakasryhmat.EnsureVisible(f, FALSE);
      paivitaAsiakkaat(pdlg->m_vect[s + 1]);                           // Asiakasryhymän asiakkaat listaan ja valitse etsitty asiakas
	}
}

// - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // -
// ON_UPDATE_COMMAND_UI // - // - // - // - // - // - // - // - // - // - // - // - // - // - // -
LRESULT PpageListat::OnKickIdle(WPARAM wparam, LPARAM lparam)
{
	UpdateDialogControls(this, FALSE);
	return 0L;
}

void PpageListat::OnUpdatePoistaValittuAsiakasRyhma(CCmdUI* pCmdUI)
{
    if(m_lstAsiakasryhmat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnUpdatePoistaValitutAsiakkaat(CCmdUI* pCmdUI)
{
    if(m_lstAsiakkaat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnUpdateSiirraValitutAsiakkaat(CCmdUI* pCmdUI)
{
    if(m_lstAsiakkaat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnUpdatePoistaValittuLaskuttaja(CCmdUI* pCmdUI)
{
    if(m_lstLaskuttajat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnUpdatePoistaValittuTyotyyppi(CCmdUI* pCmdUI)
{
    if(m_lstTyotyypit.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnUpdateSpinAsiakasryhmat(CCmdUI* pCmdUI)
{
    if(m_lstAsiakasryhmat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnUpdateSpinAsiakkaat(CCmdUI* pCmdUI)
{
    if(m_lstAsiakkaat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnUpdateSpin_1(CCmdUI* pCmdUI)
{
    if(m_showType == BILLER)
	{
      if(m_lstLaskuttajat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
      else pCmdUI->Enable(TRUE);
	}
    else if(m_showType == WORK)
	{
      if(m_lstTyotyypit.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
      else pCmdUI->Enable(TRUE);
	}
    else if(m_showType == PRODUCT)
	{}
}

void PpageListat::OnUpdateSpin_2(CCmdUI* pCmdUI)
{
    if(m_lstTuotteet.GetSelectedCount() == 0 && m_showType == PRODUCT) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageListat::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
    setView();
	*pResult = 0;
}
void PpageListat::setView()
{
    int sel = m_tabL.GetCurSel();

	if(sel == 0)             // Näytä laskuttajat
	{
       m_showType = BILLER;
	
       m_lstLaskuttajat.ShowWindow(TRUE);  // Enable windows
	   m_lstTyotyypit.ShowWindow(FALSE);   // Disable windows
	   m_lstTuoteryhmat.ShowWindow(FALSE);
	   m_lstTuotteet.ShowWindow(FALSE);
	   m_btnLisaa_2.ShowWindow(FALSE);
	   m_btnPoista_2.ShowWindow(FALSE);
       m_spn_2.ShowWindow(FALSE);
	}
	else if(sel == 1)        // Näytä työtyypit
	{
       m_showType = WORK;

       m_lstTyotyypit.ShowWindow(TRUE);    // Enable windows
	   m_lstLaskuttajat.ShowWindow(FALSE); // Disable windows
	   m_lstTuoteryhmat.ShowWindow(FALSE);
	   m_lstTuotteet.ShowWindow(FALSE);
	   m_btnLisaa_2.ShowWindow(FALSE);
	   m_btnPoista_2.ShowWindow(FALSE);
       m_spn_2.ShowWindow(FALSE);
	}
	else if(sel == 2)        // Näytä tuoteryhmät ja tuotteet
	{
       m_showType = PRODUCT;

	   m_lstLaskuttajat.ShowWindow(FALSE); // Disable windows
       m_lstTyotyypit.ShowWindow(FALSE);   
	   m_lstTuoteryhmat.ShowWindow(TRUE);  // Enable windows
	   m_lstTuotteet.ShowWindow(TRUE);
	   m_btnLisaa_2.ShowWindow(TRUE);
	   m_btnPoista_2.ShowWindow(TRUE);
       m_spn_2.ShowWindow(TRUE);
	}
}

int PpageListat::importListat()
{
    DlgImport dlg;
    int ret = IDCANCEL;

    if(Props::i().get(OPTIONS_LASKUTUSOHJELMA) == LAS_NONE)
      MessageBox(Props::i().lang("PPAGELISTAT_56"), Props::e().m_app_title, MB_ICONINFORMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
    else
      ret = dlg.DoModal();

    return ret;
}

CMenu *PpageListat::createMenu()
{
	CMenu fileMenu;
	VERIFY(fileMenu.CreatePopupMenu());
	fileMenu.AppendMenu(MF_STRING, IDM_AVAA_LISTAT, Props::i().lang("LISTAT_MENU_1"));
	fileMenu.AppendMenu(MF_STRING, IDM_TALLETA_LISTAT, Props::i().lang("LISTAT_MENU_2"));
	fileMenu.AppendMenu(MF_SEPARATOR);
	fileMenu.AppendMenu(MF_STRING, IDM_TUO_LASKUTUSOHJELMASTA, Props::i().lang("LISTAT_MENU_3"));
	fileMenu.AppendMenu(MF_SEPARATOR);
	fileMenu.AppendMenu(MF_STRING, IDM_EMAIL, Props::i().lang("LISTAT_MENU_4"));
	fileMenu.AppendMenu(MF_SEPARATOR);
	fileMenu.AppendMenu(MF_STRING, ID_APP_EXIT, Props::i().lang("COMMON_MENU_4"));

	CMenu settMenu;
	VERIFY(settMenu.CreatePopupMenu());
	settMenu.AppendMenu(MF_STRING, IDM_ASETUKSET, Props::i().lang("COMMON_MENU_5"));
	settMenu.AppendMenu(MF_SEPARATOR);
	settMenu.AppendMenu(MF_STRING, IDM_VAIHDA_TIETOKANTA, Props::i().lang("COMMON_MENU_6"));
	settMenu.AppendMenu(MF_STRING, IDM_LUO_UUSI_TIETOKANTA, Props::i().lang("COMMON_MENU_7"));
	settMenu.AppendMenu(MF_SEPARATOR);
	settMenu.AppendMenu(MF_STRING, IDM_VARMUUSKOPIOI_TIETOKANTA, Props::i().lang("COMMON_MENU_8"));
	settMenu.AppendMenu(MF_STRING, IDM_SIIVOA_TIETOKANTA, Props::i().lang("COMMON_MENU_9"));

	CMenu infoMenu;
	VERIFY(infoMenu.CreatePopupMenu());
	infoMenu.AppendMenu(MF_STRING, IDM_ABOUT, Props::i().lang("COMMON_MENU_10"));

	CMenu *pNewMenu = new CMenu();
	pNewMenu->CreateMenu();
	pNewMenu->AppendMenu(MF_POPUP, (UINT_PTR)fileMenu.m_hMenu, Props::i().lang("COMMON_MENU_1"));
	pNewMenu->AppendMenu(MF_POPUP, (UINT_PTR)settMenu.m_hMenu, Props::i().lang("COMMON_MENU_2"));
	pNewMenu->AppendMenu(MF_POPUP, (UINT_PTR)infoMenu.m_hMenu, Props::i().lang("COMMON_MENU_3"));

	return pNewMenu;
}