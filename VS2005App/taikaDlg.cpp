// taikaDlg.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "taikaDlg.h"
#include "Props.h"
#include "DlgVarmuuskopioi.h"
#include "DlgSiivoaTietokanta.h"
#include "DlgAsetukset.h"
#include "DlgLuoUusiTietokanta.h"
#include "DlgAbout.h"
#include "StringHelper_luokka.h"

#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaikaDlg dialog

CTaikaDlg::CTaikaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaikaDlg::IDD, pParent), m_pMenu(NULL)
{
	//{{AFX_DATA_INIT(CTaikaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaikaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaikaDlg)
	DDX_Control(pDX, IDC_TABMAIN, m_tabMain);
	DDX_Control(pDX, IDC_SHEET_PLACEHOLDER, m_picPlaceHolder);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTaikaDlg, CDialog)
	//{{AFX_MSG_MAP(CTaikaDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_AVAA_RAPORTTI, OnAvaaRaportti)
	ON_COMMAND(IDM_TALLETA_RAPORTTI, OnTalletaRaportti)
	ON_COMMAND(IDM_VARMUUSKOPIOI_TIETOKANTA, OnVarmuuskopioiTietokanta)
	ON_COMMAND(IDM_VAIHDA_TIETOKANTA, OnVaihdaTietokanta)
	ON_COMMAND(IDM_TALLETA_LISTAT, OnTalletaListat)
	ON_COMMAND(IDM_AVAA_LISTAT, OnAvaaListat)
	ON_COMMAND(IDM_AVAA_RAPORTTI_TM, OnAvaaRaporttiTm)
	ON_COMMAND(IDM_TALLETA_RAPORTTI_TM, OnTalletaRaporttiTm)
	ON_COMMAND(IDM_SIIVOA_TIETOKANTA, OnSiivoaTietokanta)
	ON_COMMAND(IDM_EMAIL, OnEmail)
	ON_COMMAND(IDK_VALITSEKAIKKI, OnValitsekaikki)
	ON_COMMAND(IDK_AVAA, OnAvaa)
	ON_COMMAND(IDK_TALLETA, OnTalleta)
	ON_COMMAND(IDK_ETSI, OnEtsi)
	ON_COMMAND(IDK_ETSI_F3, OnEtsiF3)
	ON_COMMAND(IDK_UUSI, OnUusi)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABMAIN, OnSelchangeTabmain)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_COMMAND(IDM_ASETUKSET, OnAsetukset)
	ON_COMMAND(IDM_LUO_UUSI_TIETOKANTA, OnLuoUusiTietokanta)
	ON_COMMAND(IDK_IMPORT, OnImport)
	ON_COMMAND(IDM_TUO_LASKUTUSOHJELMASTA, OnTuoLaskutusohjelmasta)
	ON_COMMAND(IDK_POISTA_X, OnPoista)
	ON_COMMAND(IDK_PAIVITA_V5, OnPaivitaV5)
	ON_COMMAND(IDK_EMAIL, OnEmail)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
    ON_WM_INITMENUPOPUP()
    ON_MESSAGE(WM_USER_NEW_REPORT, OnMsgUusiRaportti)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaikaDlg message handlers
LRESULT CTaikaDlg::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lparam)
{
    return 0L;
}

BOOL CTaikaDlg::OnInitDialog()
{
    int ret;
    RECT trect, crect;
    TCITEM tci;
    CString cs;
    DbSqlite db;
    Parse parse;
    CRect rcSheet;
	string use_db;

	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Päällimmäisin dialogi - aluksi raportit
    m_mainShowMode = SHOW_RAPORTIT;

    // Kansiot - luo kansiot, jos niitä ei löydy
    luoKansiot(Props::e().m_app_path);

    // Asetukset - luo perusasetukset, jos ei löydy
    if(Props::i().get(OPTIONS_AIKAJARJESTYS_R) == "")
	{
      use_db = Props::e().m_app_path + DEFAULT_DB_NAME;
      Props::i().set(OPTIONS_DB_PATH, use_db);
      Props::i().set(OPTIONS_DB_NAME, DEFAULT_DB_NAME);
      Props::i().set(OPTIONS_AUTOPARSE, "TRUE");
      Props::i().set(OPTIONS_LASKUTUSOHJELMA, LAS_NONE);
      Props::i().set(OPTIONS_LASKUTUSOHJELMA_POLKU, "c:\\");
      Props::i().set(OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU, "");
      Props::i().set(OPTIONS_KAYNTIKERTAVELOITUS, C_TRUE);
      Props::i().set(OPTIONS_HINNAT, HINNAT_LASKOHJ);
      Props::i().set(OPTIONS_LASKUTUSTILA, LTILA_LASKUTTAMATTOMAT);
	  Props::i().set(OPTIONS_LASKUNMAKSUAIKA, "30");
	  Props::i().set(OPTIONS_YHDISTATAPAHTUMAT, C_TRUE);
      Props::i().set(OPTIONS_OPENPATH, (LPCSTR)Props::e().m_app_path);
      Props::i().set(OPTIONS_SAVEPATH, (LPCSTR)Props::e().m_app_path);
      Props::i().set(OPTIONS_AJAT, StringHelper::itoa(TIME_MINUTES, 10));
      Props::i().set(OPTIONS_ALKAEN_R, DATE_VANHIN_TYO);
      Props::i().set(OPTIONS_PAATTYEN_R, DATE_UUSIN_TYO);
      Props::i().set(OPTIONS_ALKAEN_VIIMEISIN_R, "1.1.2008");
      Props::i().set(OPTIONS_PAATTYEN_VIIMEISIN_R, "1.1.2008");
      Props::i().set(OPTIONS_ALKAEN_T, DATE_VANHIN_TYO);
      Props::i().set(OPTIONS_PAATTYEN_T, DATE_UUSIN_TYO);
      Props::i().set(OPTIONS_ALKAEN_VIIMEISIN_T, "1.1.2008");
      Props::i().set(OPTIONS_PAATTYEN_VIIMEISIN_T, "1.1.2008");
      Props::i().set(OPTIONS_AIKAJARJESTYS_R, DESCENT_S);
      Props::i().set(OPTIONS_AIKAJARJESTYS_T, DESCENT_S);
      Props::i().set(OPTIONS_KMKERROIN, "0.43");
      use_db = Props::e().m_app_path + "varmuuskopiot\\";
      Props::i().set(OPTIONS_DB_BACKUP_PATH, use_db);
      Props::i().set(OPTIONS_EM_RECIPIENTS, "");
      Props::i().set(OPTIONS_EM_FROM, "");
      Props::i().set(OPTIONS_EM_SMTP_SERVER, "");
      Props::i().set(OPTIONS_EM_SMTP_PORT, "25");
      Props::i().set(OPTIONS_PRNT_ASNIMI, PRNT_ASNIMINRO);
      Props::i().set(OPTIONS_PRNT_ASALOITUSPVM, PRNT_PVM_AIKA);
      Props::i().set(OPTIONS_PRNT_ASLOPETUSPVM, PRNT_PVM_AIKA);
      Props::i().set(OPTIONS_PRNT_ASTYOAIKA, PRNT_TYOAIKA_MIN);
      Props::i().set(OPTIONS_PRNT_ASTYOTYYPIT, PRNT_TYOTYYPIT);
      Props::i().set(OPTIONS_PRNT_TTALOITUSPVM, PRNT_PVM_AIKA);
      Props::i().set(OPTIONS_PRNT_TTLOPETUSPVM, PRNT_PVM_AIKA);
      Props::i().set(OPTIONS_PRNT_TTTYOAIKA, PRNT_TYOAIKA_MIN);
      Props::i().set(OPTIONS_PRNT_TTTYOTYYPIT, PRNT_TYOTYYPIT);
      Props::i().set(OPTIONS_PRNT_TMPAIVAYKSET, PRNT_PVM_AIKA_MOLEMMAT);
      Props::i().set(OPTIONS_PRNT_TMMATKA, PRNT_MATKAT_TARKOITUS);
      Props::i().set(OPTIONS_PRNT_TMLUKEMAT, PRNT_LUKEMAT);
      Props::i().set(OPTIONS_PRNT_TMYKSAJOA, PRNT_YKSAJOA);
      Props::i().set(OPTIONS_PRNT_TMTYOAJOA, PRNT_TYOAJOA);
      Props::i().set(OPTIONS_PRNT_SIVUTUS, C_TRUE);
      Props::i().set(OPTIONS_PRNT_YLATUNNISTE_TEXT, "");
      Props::i().set(OPTIONS_PRNT_ALATUNNISTE_TEXT, "");
      Props::i().set(OPTIONS_PRNT_YLATUNNISTE, C_TRUE);
      Props::i().set(OPTIONS_PRNT_ALATUNNISTE, C_TRUE);
      Props::i().set(OPTIONS_PRNT_YLAPAIVAYS, C_TRUE);
      Props::i().set(OPTIONS_PRNT_FONTINKOKO, FONTSIZE_8);
      Props::i().set(OPTIONS_PRNT_FONTINNIMI, "Arial");
      Props::i().set(OPTIONS_PRNT_YHTEENVETO, C_TRUE);
      Props::i().set(OPTIONS_PRNT_KMKORVAUS, C_TRUE);
	  Props::i().set(OPTIONS_PRNT_YHDISTATAPAHTUMAT, C_TRUE);
      Props::i().set(OPTIONS_EM_SMTP_USE_AUTH, C_FALSE);
      Props::i().set(OPTIONS_EM_SMTP_RMBR_UN, C_FALSE);
      Props::i().set(OPTIONS_EM_SMTP_USERNAME, "");
      Props::i().set(OPTIONS_LSTHEADER_RATA, "");
      Props::i().set(OPTIONS_LSTHEADER_RAMY, "");
      Props::i().set(OPTIONS_LSTHEADER_LIAR, "");
      Props::i().set(OPTIONS_LSTHEADER_LIAS, "");
      Props::i().set(OPTIONS_LSTHEADER_LILA, "");
      Props::i().set(OPTIONS_LSTHEADER_LITT, "");
      Props::i().set(OPTIONS_LSTHEADER_LITR, "");
      Props::i().set(OPTIONS_LSTHEADER_LITU, "");
      Props::i().set(OPTIONS_LSTHEADER_TYTY, "");
	}

    // Otetaan tietokannan polku asetuksista, Tarkistetaan tietokanta (luodaan, jos ei ole olemassa)
    Props::e().m_db_path = Props::i().get(OPTIONS_DB_PATH).c_str();
    if((ret = db.check()) != RETURN_OK)
      Props::e().m_db_path = "";   // Virheen sattuessa, ei tietokantaa!!! //EndDialog(IDCANCEL);

    // Tarkistetaan onko saapuneet kansiossa uusia raportteja
    if(ret == RETURN_OK) parse.parseSaapuneet(PARSE_SAAPUNEET);

    // Dialogin otsikko resurssista ja tietokannan nimi asetuksista
    usedDB();

    // Menu paikoilleen (aluksi IDR_RAPORTIT_MENU, asetetaan eri dilogeissa vastaamaan paremmin niiden toimintoja)
	m_pMenu = pageRaportit.createMenu();
    this->SetMenu(m_pMenu);
    AfxGetMainWnd()->DrawMenuBar();

	// Koko ruutu
	ShowWindow(SW_MAXIMIZE);

	// Alustetaan tab-kontolli
    GetClientRect(&crect);
    m_tabMain.SetWindowPos(NULL, 0, 0, crect.right, crect.bottom, SWP_NOMOVE|SWP_NOZORDER);

	tci.mask = TCIF_IMAGE|TCIF_TEXT; tci.iImage = 0; tci.pszText = (LPSTR)(LPCSTR)Props::i().lang("TAIKADLG_1");
    m_tabMain.InsertItem(0, &tci);
    tci.mask = TCIF_IMAGE|TCIF_TEXT; tci.iImage = 0; tci.pszText = (LPSTR)(LPCSTR)Props::i().lang("TAIKADLG_2");
    m_tabMain.InsertItem(1, &tci);
    tci.mask = TCIF_IMAGE|TCIF_TEXT; tci.iImage = 0; tci.pszText = (LPSTR)(LPCSTR)Props::i().lang("TAIKADLG_3");
    m_tabMain.InsertItem(2, &tci);

    // Placeholder ylänurkkaan
    m_tabMain.GetItemRect(0, &trect);                    // tabin headerin koko
    m_tabMain.GetClientRect(&crect);                     // tabin koko
    m_picPlaceHolder.SetWindowPos(NULL, PAGE_LEFT, PAGE_TOP + trect.bottom, crect.right - PAGE_LEFT - PAGE_RIGHT, crect.bottom - trect.bottom - PAGE_TOP - PAGE_BOTTOM, SWP_NOZORDER);

    // Luo dialogit
    pageRaportit.CRHCreateGenericChildDialog(this, IDC_SHEET_PLACEHOLDER, 0, NULL);
    pageListat.CRHCreateGenericChildDialog(this, IDC_SHEET_PLACEHOLDER, 0, NULL);
    pageTyomatkat.CRHCreateGenericChildDialog(this, IDC_SHEET_PLACEHOLDER, 0, NULL);

    // Ja uudestaan menu - dialogien luonti voi sotkea näytettävän menun
	if(m_pMenu) m_pMenu->DestroyMenu();
	m_pMenu = pageRaportit.createMenu();
    this->SetMenu(m_pMenu);
    AfxGetMainWnd()->DrawMenuBar();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTaikaDlg::OnClose() 
{
    CDialog::OnClose();
}

void CTaikaDlg::OnDestroy() 
{
    CDialog::OnDestroy();

    if(m_pMenu)
		m_pMenu->DestroyMenu();                            // Tuhoa menu
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTaikaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CTaikaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CTaikaDlg::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN)  // Estetään RETURNIN painaminen dialogissa (dialogi ei sulkeudu vahingossa)
	{
      if(pMsg->wParam == VK_RETURN) return TRUE;
	}

    SendMessageToDescendants(WM_KICKIDLE, 0, 0, FALSE, FALSE);

	return CDialog::PreTranslateMessage(pMsg);
}

void CTaikaDlg::OnOK()
{}

void CTaikaDlg::OnCancel()
{
    CDialog::OnCancel();
}

void CTaikaDlg::OnSize(UINT nType, int cx, int cy) 
{
    BOOL resize = FALSE;
    RECT crect, trect;
    int page_width, page_height;

    // Varmista, että ikkunat on luotu
    if(this->GetSafeHwnd() == 0) return;
	if(m_tabMain.GetSafeHwnd() == 0) return;
	if(m_picPlaceHolder.GetSafeHwnd() == 0) return;

	CDialog::OnSize(nType, cx, cy);

    // tab-control ruudun kokoiseksi
    GetClientRect(&crect);
    m_tabMain.SetWindowPos(NULL, 0, 0, crect.right, crect.bottom, SWP_NOMOVE|SWP_NOZORDER);

    // placeholder tabin kokoiseksi
    m_tabMain.GetItemRect(0, &trect);                    // tabin headerin koko
    m_tabMain.GetClientRect(&crect);                     // tabin koko
    page_width = crect.right - PAGE_LEFT - PAGE_RIGHT;   // sivun koko: w = tabin w - marginaalit, h = tabin h - tabin h - marginaalit
    page_height = crect.bottom - trect.bottom - PAGE_TOP - PAGE_BOTTOM;

    m_picPlaceHolder.SetWindowPos(NULL, 0, 0, page_width, page_height, SWP_NOMOVE|SWP_NOZORDER);

    // Muuta lapsidialogien koot
    if(pageRaportit.GetSafeHwnd() != NULL)
      pageRaportit.windowSize();
    if(pageListat.GetSafeHwnd() != NULL)
      pageListat.windowSize();
    if(pageTyomatkat.GetSafeHwnd() != NULL)
      pageTyomatkat.windowSize();
}

void CTaikaDlg::OnSizing(UINT nSide, LPRECT lpRect)
{
    if(lpRect->right - lpRect->left < 890) lpRect->right = lpRect->left + 890;
    if(lpRect->bottom - lpRect->top < 500) lpRect->bottom = lpRect->top + 500;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  // // //
// Komentojen käsittelijät
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  // // //
void CTaikaDlg::OnSelchangeTabmain(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int sel = m_tabMain.GetCurSel();

    if(sel == 0 && m_mainShowMode != SHOW_RAPORTIT)
	{
      m_mainShowMode = SHOW_RAPORTIT;
      pageRaportit.ShowWindow(SW_SHOW);
	  pageListat.ShowWindow(SW_HIDE);
      pageTyomatkat.ShowWindow(SW_HIDE);

      pageRaportit.OnSetActive();
	}
    else if(sel == 1)
	{
      m_mainShowMode = SHOW_LISTAT;
      pageRaportit.ShowWindow(SW_HIDE);
	  pageListat.ShowWindow(SW_SHOW);
      pageTyomatkat.ShowWindow(SW_HIDE);

      pageListat.OnSetActive();
	}
    else if(sel == 2)
	{
      m_mainShowMode = SHOW_TYOMATKAT;
      pageRaportit.ShowWindow(SW_HIDE);
	  pageListat.ShowWindow(SW_HIDE);
      pageTyomatkat.ShowWindow(SW_SHOW);

      pageTyomatkat.OnSetActive();
	}

	*pResult = 0;
}

LRESULT CTaikaDlg::OnMsgUusiRaportti(WPARAM wparam, LPARAM lparam)
{
    //int s;
    Parse parse;

    this->BringWindowToTop();

    parse.parseSaapuneet(PARSE_ADD_FILE);   // Parsitaan saapuneet lista ja päivitetään näytöt

    if(wparam == PARAM_TTI || wparam == PARAM_TTA)
      paivitaNaytot(TRUE, TRUE, FALSE, SYNC_ALL);

    return 0;
}

void CTaikaDlg::luoKansiot(CString app_path)
{ // Luo kansiot jos niitä ei löydy
    WIN32_FIND_DATA fd;
    HANDLE hfile = NULL;
    CString dirpath, cs;

    dirpath = app_path + "saapuneet\\";
    if((hfile = FindFirstFile(dirpath, &fd)) != INVALID_HANDLE_VALUE) FindClose(hfile);
    else { if(GetLastError() == ERROR_PATH_NOT_FOUND) CreateDirectory(dirpath, NULL); }
    dirpath = app_path + "raportit\\";
    if((hfile = FindFirstFile(dirpath, &fd)) != INVALID_HANDLE_VALUE) FindClose(hfile);
    else { if(GetLastError() == ERROR_PATH_NOT_FOUND) CreateDirectory(dirpath, NULL); }
    dirpath = app_path + "varmuuskopiot\\";
    if((hfile = FindFirstFile(dirpath, &fd)) != INVALID_HANDLE_VALUE) FindClose(hfile);
    else { if(GetLastError() == ERROR_PATH_NOT_FOUND) CreateDirectory(dirpath, NULL); }
}

/////////////////////////////////////////////////////////////////////////////
// Menun itemien disablointi/enablointi logiikka
void CTaikaDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible())
      setRaporttiMenu(nIndex);
    if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible())
      setListatMenu(nIndex);
}

void CTaikaDlg::setRaporttiMenu(UINT nIndex)
{
    int flags;
    CMenu *pMenu = this->GetMenu();

    if(nIndex == 0)                                  // Tiedosto-menu
	{
      // IDM_TALLETA_RAPORTTI
      if(pageRaportit.m_lstAsiakkaat.GetSelCount() > 0 || pageRaportit.m_plstRaportit->GetItemCount() > 0) flags = MF_ENABLED;
      else flags = MF_DISABLED|MF_GRAYED;
      pMenu->EnableMenuItem(IDM_TALLETA_RAPORTTI, flags);
	}
}

void CTaikaDlg::setListatMenu(UINT nIndex)
{}

/////////////////////////////////////////////////////////////////////////////
// IDM_RAPORTIT_MENU - Menu itemien viestit
void CTaikaDlg::OnAvaaRaportti() 
{
    //int s;
    Parse parse;

    if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible())    // Avaa .tti-tiedosto
	{ if(!parse.avaaTTI(this->GetSafeHwnd())) return; }

	paivitaNaytot(TRUE, TRUE, FALSE, SYNC_ALL);
}

void CTaikaDlg::OnTalletaRaportti()
{
    Parse parse;

    if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible())    // Talleta valitut ID_WORKUNIT/ID_SALESUNIT-tiedostoon (.tta)
	{ parse.talletaTTI(this->GetSafeHwnd(), pageRaportit.getMode()); }
}

void CTaikaDlg::OnEmail() 
{
    Parse parse;

    //if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) pageRaportit.email();
    if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) pageListat.email();
}

void CTaikaDlg::OnAbout()
{
	CDlgAbout dlga;
	dlga.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// IDM_LISTAT_MENU - Menu itemien viestit
void CTaikaDlg::OnAvaaListat() 
{
    Parse parse;

    if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible())        // Avaa .tta-tiedosto
	{ if(!parse.avaaTTA(this->GetSafeHwnd())) return; }

    paivitaNaytot(FALSE, FALSE, FALSE, SYNC_ALL);
}

void CTaikaDlg::OnTalletaListat() 
{
    Parse parse;

    if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible())        // Talleta listat
	{ parse.talletaTTA(this->GetSafeHwnd(), "", 0, 0, 0, 0, MODE_SAVE); }
}

void CTaikaDlg::OnTuoLaskutusohjelmasta() 
{
    OnImport();
}

/////////////////////////////////////////////////////////////////////////////
// IDM_TYOMATKAT_MENU - Menu itemien viestit
void CTaikaDlg::OnAvaaRaporttiTm() 
{
    //int s;
    Parse parse;

    if(m_mainShowMode == SHOW_TYOMATKAT && pageTyomatkat.IsWindowVisible())  // Avaa .tti-tiedosto
	{ if(!parse.avaaTTI(this->GetSafeHwnd())) return; }

	paivitaNaytot(TRUE, TRUE, FALSE, SYNC_ALL);
}

void CTaikaDlg::OnTalletaRaporttiTm() 
{
    Parse parse;
    vector <ItemData_travel*> id_vect;

    // Haetaan GetSaveFileName()-funktiossa valitun tilan mukaan vektoriin talletettavat tiedot
	if(m_mainShowMode != SHOW_TYOMATKAT || !pageTyomatkat.IsWindowVisible()) return;
    pageTyomatkat.haeItemDataList(&id_vect, MODE_TYONTEKIJANTIEDOT);
    if(id_vect.size() > 0)
	{
      parse.talletaTTI_tyomatkat(this->GetSafeHwnd(), id_vect);              // Talletetaan
      pageTyomatkat.vapautaItemDataList(&id_vect, MODE_TYONTEKIJANTIEDOT);   // Vapautetaan muisti
	}
}

/////////////////////////////////////////////////////////////////////////////
// IDM_RAPORTIT_MENU, IDM_LISTAT_MENU, IDM_ASETUKSET - Menu itemien yhteiset viestit
void CTaikaDlg::OnVarmuuskopioiTietokanta() 
{
    DlgVarmuuskopioi dlg;

    if(dlg.DoModal() == IDOK)
      paivitaNaytot(TRUE, TRUE, FALSE, SYNC_ALL);
}

void CTaikaDlg::OnVaihdaTietokanta() 
{
	DWORD e;
	CString file;
	char buf[128] = {0};
    OPENFILENAME ofn;
    DlgParseInfo dlg;
    char *lpstrFile = NULL, strFileTitle[MAX_PATH];

    try
	{
      file = Props::i().get(OPTIONS_DB_PATH).c_str();

      if(!(lpstrFile = new char[MAX_PATH * 100])) throw(0);          // Tarpeeksi tilaa useammalle tiedostonimelle

      ofn.lStructSize = sizeof(OPENFILENAME);
      ofn.hwndOwner = this->GetSafeHwnd();
      ofn.lpstrFilter = Props::i().langs("TAIKADLG_4", buf, 128);
      ofn.lpstrTitle = Props::i().lang("TAIKADLG_5");
      ofn.lpstrInitialDir = file;
      ofn.lpstrCustomFilter = NULL; ofn.nFilterIndex = 1;
      *lpstrFile = NULL; ofn.lpstrFile = lpstrFile; ofn.nMaxFile = MAX_PATH * 100;
      ofn.lpstrFileTitle = strFileTitle; ofn.nMaxFileTitle = MAX_PATH;
      ofn.Flags = OFN_EXPLORER|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_PATHMUSTEXIST;
      ofn.lpstrDefExt = NULL; ofn.lCustData = NULL;
      if(!GetOpenFileName(&ofn)) throw(0);
      Props::i().set(OPTIONS_DB_PATH, ofn.lpstrFile);     // talleta, mahdollisesti uusi, polku asetuksiin
      Props::i().set(OPTIONS_DB_NAME, (char*)(ofn.lpstrFile + ofn.nFileOffset));
      Props::e().m_db_path = ofn.lpstrFile;

      paivitaNaytot(TRUE, TRUE, TRUE, SYNC_ALL);
	}
    catch(...)
	{
      if((e = CommDlgExtendedError()) != ERROR_SUCCESS)
      {
        file.Format(Props::i().lang("TAIKADLG_6"), e);
        MessageBox(file, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	  }
	}

    if(lpstrFile) delete [] lpstrFile;
}

void CTaikaDlg::OnAsetukset() 
{
    CDlgAsetukset dlg;

    dlg.DoModal();	
}

void CTaikaDlg::OnLuoUusiTietokanta() 
{
    CDlgLuoUusiTietokanta dlg;

    if(dlg.DoModal() == IDOK)
      paivitaNaytot(TRUE, TRUE, TRUE, SYNC_ALL);
}

void CTaikaDlg::OnSiivoaTietokanta() 
{
    DlgSiivoaTietokanta dlg;

    if(dlg.DoModal() == IDOK)
      paivitaNaytot(TRUE, TRUE, FALSE, SYNC_ALL);
}

// Accelerator-näppäimet (kaasutusnäppäimet)
void CTaikaDlg::OnValitsekaikki() 
{
    if(GetForegroundWindow() != this)
      GetForegroundWindow()->PostMessage(WM_USER_SELECTALL);
    else
	{
      if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) pageRaportit.valitseKaikki();
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) pageListat.valitseKaikki();
      if(m_mainShowMode == SHOW_TYOMATKAT && pageTyomatkat.IsWindowVisible()) pageTyomatkat.valitseKaikki();
	}
}

void CTaikaDlg::OnAvaa() 
{
    if(GetForegroundWindow() == this)
	{
      if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) OnAvaaRaportti();
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) OnAvaaListat();
      if(m_mainShowMode == SHOW_TYOMATKAT && pageTyomatkat.IsWindowVisible()) OnAvaaRaporttiTm();
	}
}

void CTaikaDlg::OnTalleta() 
{
    if(GetForegroundWindow() == this)
	{
      if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) OnTalletaRaportti();
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) OnTalletaListat();
      if(m_mainShowMode == SHOW_TYOMATKAT && pageTyomatkat.IsWindowVisible()) OnTalletaRaporttiTm();
	}
}

void CTaikaDlg::OnEtsi() 
{
    if(GetForegroundWindow() == this)
	{
      if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) pageRaportit.etsi(KEY_CTRLF);
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) pageListat.etsi(KEY_CTRLF);
	}
}

void CTaikaDlg::OnEtsiF3()
{
    if(GetForegroundWindow() == this)
	{
      if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) pageRaportit.etsi(KEY_F3);
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) pageListat.etsi(KEY_F3);
	}
}

void CTaikaDlg::OnPoista()
{ poista(); }
BOOL CTaikaDlg::poista()
{
    if(GetForegroundWindow() == this)
	{
      if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) pageRaportit.poistaItems();
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) pageListat.poista();
      if(m_mainShowMode == SHOW_TYOMATKAT && pageTyomatkat.IsWindowVisible()) pageTyomatkat.poistaValitut();

	  return TRUE;
	}

	return FALSE;
}
void CTaikaDlg::OnUusi() 
{
    if(GetForegroundWindow() == this)
	{
      if(m_mainShowMode == SHOW_RAPORTIT && pageRaportit.IsWindowVisible()) pageRaportit.lisaaTapahtuma(0);
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible()) pageListat.lisaa();
      if(m_mainShowMode == SHOW_TYOMATKAT && pageTyomatkat.IsWindowVisible()) pageTyomatkat.lisaaUusi(0);
	}
}

void CTaikaDlg::OnImport() 
{
    if(GetForegroundWindow() == this)
	{
      if(m_mainShowMode == SHOW_LISTAT && pageListat.IsWindowVisible())
	  { if(pageListat.importListat() == IDOK) paivitaNaytot(TRUE, FALSE, FALSE, SYNC_ALL); }
	}
}

void CTaikaDlg::OnPaivitaV5() 
{
    if(GetForegroundWindow() == this)
      paivitaNaytot(TRUE, TRUE, TRUE, SYNC_ALL);
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  // // //
// Yhteiset funktiot
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  // // //
void CTaikaDlg::paivitaNaytot(BOOL date, BOOL select, BOOL database, int type)
{ // Keskitetty näyttöjen päivitys
    if(m_mainShowMode == SHOW_RAPORTIT)
	{
      pageRaportit.paivitaAARListat("", NULL, FALSE);
      pageRaportit.paivitaTyontekijat("", NULL, FALSE);
      pageRaportit.paivitaTyotyyppi("", NULL, FALSE);
      pageRaportit.paivitaPaivays(0, "", NULL, FALSE);
      if(date) pageRaportit.paivitaPaivays(0, "", NULL, FALSE);
      if(select) pageRaportit.uusiHaku(NULL);

      syncListat(SYNC_FROM_RAPORTIT, type);
	}
      
	if(m_mainShowMode == SHOW_LISTAT)
	{
      pageListat.paivitaAsiakasryhmat("", TRUE);
      pageListat.paivitaAsiakkaat("");
      pageListat.paivitaTila();

      syncListat(SYNC_FROM_LISTAT, type);
	}
      
	if(m_mainShowMode == SHOW_TYOMATKAT)
	{
      pageTyomatkat.paivitaTyontekijat("", NULL, FALSE);
      pageTyomatkat.paivitaPaivays(0, "", NULL, FALSE);
      if(date) pageTyomatkat.paivitaPaivays(0, "", NULL, FALSE);
      if(select) pageTyomatkat.uusiHaku(NULL);

      syncListat(SYNC_FROM_TYOMATKAT, type);
	}

    if(database) usedDB();
}

void CTaikaDlg::syncListat(int from, int type)
{  // Listojen muutokset heijastuu kaikkien eri näyttöjen listoihin -> välitä tieto päivityksestä näytöille
    if(from != SYNC_FROM_RAPORTIT)
      Props::e().m_sync_raportit |= type;

    if(from != SYNC_FROM_LISTAT)
      Props::e().m_sync_listat |= type;

    if(from != SYNC_FROM_TYOMATKAT)
      Props::e().m_sync_tyomatkat |= type;

    // Etsi-toiminnon vanhat osumat poistetaan, jos asiakkaat muuttuneet
	if((type&SYNC_ASIAKKAAT) || (type&SYNC_ASIAKASRYHMAT))
      Props::e().m_dlgEtsi.clear();
}

void CTaikaDlg::usedDB()
{
    CString cs;

    cs = Props::i().lang("APPNAME") + CString(" - ") + Props::i().get(OPTIONS_DB_NAME).c_str();
    this->SetWindowText(cs);
}