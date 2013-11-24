// PpageTyomatkat.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "PpageTyomatkat.h"
#include "Paivays.h"
#include "Props.h"
#include "taikaDlg.h"
#include "IpeDlgEdit.h"
#include "IpeDlgComboBox2.h"
#include "afxpriv.h"
#include "StringHelper_luokka.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PpageTyomatkat property page

//IMPLEMENT_DYNCREATE(PpageTyomatkat, CDialog)

PpageTyomatkat::PpageTyomatkat() //: CPropertyPage(PpageTyomatkat::IDD)
{
	//{{AFX_DATA_INIT(PpageTyomatkat)
	//}}AFX_DATA_INIT
}

PpageTyomatkat::~PpageTyomatkat()
{
}

void PpageTyomatkat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PpageTyomatkat)
	DDX_Control(pDX, IDC_STCSEP4, m_stcSep4);
	DDX_Control(pDX, IDC_STCSEP3, m_stcSep3);
	DDX_Control(pDX, IDC_STCSEP2, m_stcSep2);
	DDX_Control(pDX, IDC_STCSEP1, m_stcSep1);
	DDX_Control(pDX, IDC_STCVALITUT, m_stcValitut);
	DDX_Control(pDX, IDC_STCYHTEENSA, m_stcYhteensa);
	DDX_Control(pDX, IDC_EDTKMKERROIN, m_edtkmKerroin);
	DDX_Control(pDX, IDC_BTNPOISTAVALITUT, m_btnPoistaValitut);
	DDX_Control(pDX, IDC_BTNLISAAUUSI, m_bntLisaaUusi);
	DDX_Control(pDX, IDC_BTNERITTELY, m_btnErittely);
	DDX_Control(pDX, IDC_LSTTYONTEKIJAT, m_lstTyontekijat);
	DDX_Control(pDX, IDC_LSTTYOMATKAT, m_lstTyomatkat);
	DDX_Control(pDX, IDC_DTPPAATTYEN, m_dtpPaattyen);
	DDX_Control(pDX, IDC_DTPALKAEN, m_dtpAlkaen);
	DDX_Control(pDX, IDC_CHKTYONTEKIJAT, m_chkTyontekijat);
	DDX_Control(pDX, IDC_BTNPAATTYEN, m_btnPaattyen);
	DDX_Control(pDX, IDC_BTNALKAEN, m_btnAlkaen);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PpageTyomatkat, CDialog)
	//{{AFX_MSG_MAP(PpageTyomatkat)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTPALKAEN, OnDatetimechangeDtpalkaen)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTPPAATTYEN, OnDatetimechangeDtppaattyen)
	ON_LBN_SELCHANGE(IDC_LSTTYONTEKIJAT, OnSelchangeLsttyontekijat)
	ON_BN_CLICKED(IDC_CHKTYONTEKIJAT, OnChktyontekijat)
	ON_BN_CLICKED(IDC_BTNALKAEN, OnBtnalkaen)
	ON_BN_CLICKED(IDC_BTNPAATTYEN, OnBtnpaattyen)
	ON_BN_CLICKED(IDC_BTNLISAAUUSI, OnBtnlisaauusi)
	ON_BN_CLICKED(IDC_BTNPOISTAVALITUT, OnBtnpoistavalitut)
	ON_BN_CLICKED(IDC_BTNERITTELY, OnBtnerittely)
	ON_EN_CHANGE(IDC_EDTKMKERROIN, OnChangeEdtkmkerroin)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTTYOMATKAT, OnItemchangedLsttyomatkat)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_KICKIDLE, OnKickIdle)              // ON_UPDATE_COMMAND_UI
	ON_UPDATE_COMMAND_UI(IDC_BTNPOISTAVALITUT, OnUpdatePoistaValitut)
	ON_UPDATE_COMMAND_UI(IDC_BTNPOISTAVALITUT, OnUpdateErittely)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PpageTyomatkat message handlers
BOOL PpageTyomatkat::OnInitDialog() 
{
    HDITEM hdi;
    CString cs;
    HBITMAP hbm;
    CBitmap cBmA;
    CBitmap cBmD;
    CRect rcList;

    CDialog::OnInitDialog();

	SetDlgItemText(IDC_CHKTYONTEKIJAT, Props::i().lang("PPAGETYOMATKAT_C1"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("PPAGETYOMATKAT_C2"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("PPAGETYOMATKAT_C3"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("PPAGETYOMATKAT_C4"));
	SetDlgItemText(IDC_STATIC4, Props::i().lang("PPAGETYOMATKAT_C5"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("PPAGETYOMATKAT_C6"));
	SetDlgItemText(IDC_STATIC6, Props::i().lang("PPAGETYOMATKAT_C7"));
	SetDlgItemText(IDC_BTNLISAAUUSI, Props::i().lang("PPAGETYOMATKAT_C8"));
	SetDlgItemText(IDC_BTNPOISTAVALITUT, Props::i().lang("PPAGETYOMATKAT_C9"));
	SetDlgItemText(IDC_BTNERITTELY, Props::i().lang("PPAGETYOMATKAT_C10"));
	SetDlgItemText(IDC_STCSEP1, Props::i().lang("PPAGETYOMATKAT_C11"));
	SetDlgItemText(IDC_STCSEP2, Props::i().lang("PPAGETYOMATKAT_C12"));

    m_bmpCalendar.LoadBitmap(IDB_BMPCALENDAR);       // Bitmapit nappuloihin
    m_btnAlkaen.SetBitmap(m_bmpCalendar);
    m_btnPaattyen.SetBitmap(m_bmpCalendar);

    // Alustetaan Raportti CListCtrl
    m_lstTyomatkat.m_omistaja = O_TRAVEL;
	m_lstTyomatkat.m_props = OPTIONS_LSTHEADER_TYTY;
	ListView_SetExtendedListViewStyleEx(m_lstTyomatkat.GetSafeHwnd(),  // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    vector<string> vec = StringHelper::split(Props::i().get((LPCSTR)m_lstTyomatkat.m_props), ';');
    if(vec.size() < 9)
	{
      m_lstTyomatkat.GetClientRect(&rcList);                             // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
	  rcList.right -= 18;
      m_lstTyomatkat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstTyomatkat.InsertColumn(1, Props::i().lang("PPAGETYOMATKAT_1"), LVCFMT_LEFT, rcList.right * 0.121, -1);
      m_lstTyomatkat.InsertColumn(2, Props::i().lang("PPAGETYOMATKAT_2"), LVCFMT_LEFT, rcList.right * 0.09, -1);
      m_lstTyomatkat.InsertColumn(3, Props::i().lang("PPAGETYOMATKAT_3"), LVCFMT_LEFT, rcList.right * 0.09, -1);
      m_lstTyomatkat.InsertColumn(4, Props::i().lang("PPAGETYOMATKAT_4"), LVCFMT_LEFT, rcList.right * 0.09, -1);
      m_lstTyomatkat.InsertColumn(5, Props::i().lang("PPAGETYOMATKAT_5"), LVCFMT_LEFT, rcList.right * 0.121, -1);
      m_lstTyomatkat.InsertColumn(6, Props::i().lang("PPAGETYOMATKAT_6"), LVCFMT_LEFT, rcList.right * 0.111, -1);
      m_lstTyomatkat.InsertColumn(7, Props::i().lang("PPAGETYOMATKAT_7"), LVCFMT_LEFT, rcList.right * 0.111, -1);
      m_lstTyomatkat.InsertColumn(8, Props::i().lang("PPAGETYOMATKAT_8"), LVCFMT_LEFT, rcList.right * 0.111, -1);
      m_lstTyomatkat.InsertColumn(9, Props::i().lang("PPAGETYOMATKAT_9"), LVCFMT_LEFT, rcList.right * 0.125, -1);
	}
    else
	{
      m_lstTyomatkat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstTyomatkat.InsertColumn(1, Props::i().lang("PPAGETYOMATKAT_1"), LVCFMT_LEFT, StringHelper::parseInt(vec[1]), -1);
      m_lstTyomatkat.InsertColumn(2, Props::i().lang("PPAGETYOMATKAT_2"), LVCFMT_LEFT, StringHelper::parseInt(vec[2]), -1);
      m_lstTyomatkat.InsertColumn(3, Props::i().lang("PPAGETYOMATKAT_3"), LVCFMT_LEFT, StringHelper::parseInt(vec[3]), -1);
      m_lstTyomatkat.InsertColumn(4, Props::i().lang("PPAGETYOMATKAT_4"), LVCFMT_LEFT, StringHelper::parseInt(vec[4]), -1);
      m_lstTyomatkat.InsertColumn(5, Props::i().lang("PPAGETYOMATKAT_5"), LVCFMT_LEFT, StringHelper::parseInt(vec[5]), -1);
      m_lstTyomatkat.InsertColumn(6, Props::i().lang("PPAGETYOMATKAT_6"), LVCFMT_LEFT, StringHelper::parseInt(vec[6]), -1);
      m_lstTyomatkat.InsertColumn(7, Props::i().lang("PPAGETYOMATKAT_7"), LVCFMT_LEFT, StringHelper::parseInt(vec[7]), -1);
      m_lstTyomatkat.InsertColumn(8, Props::i().lang("PPAGETYOMATKAT_8"), LVCFMT_LEFT, StringHelper::parseInt(vec[8]), -1);
      m_lstTyomatkat.InsertColumn(9, Props::i().lang("PPAGETYOMATKAT_9"), LVCFMT_LEFT, StringHelper::parseInt(vec[9]), -1);
	}

	// jos listan päälle tulee muita kontrolleja, tämä estää niitä jäämästä alle tai, että niiden päälle piirretään
	m_lstTyomatkat.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);

	m_lstTyomatkat.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	// Aasetetaan CImageList listaan
	m_lstTyomatkat.SetImageList(Props::e().m_pCImageList, LVSIL_SMALL);
	m_lstTyomatkat.GetHeaderCtrl()->SetImageList(Props::e().m_pCImageList/*, LVSIL_SMALL*/);

    hdi.mask = HDI_IMAGE|HDI_FORMAT;                   // Aseta kuva työmatkalistan otsikkoon 'Aloituspäivä'
    hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT;
    cs = Props::i().get(OPTIONS_AIKAJARJESTYS_T).c_str();
	hdi.iImage = (cs == ASCENT_S ? 6 : 7);
    hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGETYOMATKAT_10");
    m_lstTyomatkat.GetHeaderCtrl()->SetItem(5, &hdi);

	// kilometrikorvauskerroin
    cs = Props::i().get(OPTIONS_KMKERROIN).c_str();
    m_edtkmKerroin.SetWindowText(cs);

	// asetukset kohdilleen kontrolleihin
    paivitaTyontekijat("", NULL, FALSE);
    paivitaPaivays(0, "", NULL, FALSE);
    m_lstTyontekijat.SetSel(0, TRUE); m_lstTyontekijat.SetCaretIndex(0, TRUE);
    uusiHaku(NULL);

    OnSetActive();                                   // Päivitä kaikki kontrollit alustavasti

    return TRUE;
}

void PpageTyomatkat::OnDestroy() 
{
	CDialog::OnDestroy();
}

BOOL PpageTyomatkat::OnSetActive() 
{
    static BOOL firsDraw = TRUE;

	// Aseta menu CTaikaDlg:iin
    CMenu *pMenu = ((CTaikaDlg*)GetParent())->m_pMenu;		// tuhoa edellinen
	if(pMenu) pMenu->DestroyMenu();
	pMenu = createMenu();									// luo uusi
	((CTaikaDlg*)GetParent())->m_pMenu = pMenu;
    AfxGetMainWnd()->SetMenu(pMenu);						// aseta uusi käyttöön
    AfxGetMainWnd()->DrawMenuBar();

    if(firsDraw)
	{
      windowSize();                                  // Asettele kontrollit

      paivitaTyontekijat("", NULL, FALSE);             // Päivitetään näyttö
      paivitaPaivays(0, "", NULL, FALSE);
      uusiHaku(NULL);

	  firsDraw = FALSE;
	}

	if(Props::e().m_sync_tyomatkat != 0)
	{
      if((Props::e().m_sync_tyomatkat & SYNC_TYONTEKIJAT)) paivitaTyontekijat("", NULL, FALSE);
	  uusiHaku(NULL);

	  Props::e().m_sync_tyomatkat = 0;
	}

    return TRUE;//CDialog::OnSetActive();
}

void PpageTyomatkat::windowSize()
{
    static int xoffs[9] = { 0, 101, 106, 11, 106, 11, 36, 138, 51 };
    static int yoffs[9] = { 0, 0, 2, 0, 2, 4, 0, 4, 0 };
    RECT trect, crect;
    int curpos, bs, byp, page_width, page_height; // button size, button y-position

    if(m_bntLisaaUusi.GetSafeHwnd() == 0) return;
    if(m_btnPoistaValitut.GetSafeHwnd() == 0) return;
    if(m_stcSep3.GetSafeHwnd() == 0) return;
    if(m_btnErittely.GetSafeHwnd() == 0) return;
    if(m_stcSep1.GetSafeHwnd() == 0) return;
    if(m_stcValitut.GetSafeHwnd() == 0) return;
    if(m_stcSep2.GetSafeHwnd() == 0) return;
    if(m_stcYhteensa.GetSafeHwnd() == 0) return;
    if(m_lstTyomatkat.GetSafeHwnd() == 0) return;

    m_bntLisaaUusi.GetClientRect(&trect);                            // nappulan koko
    bs = trect.bottom;
    ((CTaikaDlg*)GetParent())->m_tabMain.GetItemRect(0, &trect);     // tabin headerin koko
    ((CTaikaDlg*)GetParent())->m_tabMain.GetClientRect(&crect);      // tabin koko

    page_width = crect.right - PAGE_LEFT - PAGE_RIGHT;               // sivun koko: w = tabin w - marginaalit, h = tabin h - tabin h - marginaalit
    page_height = crect.bottom - trect.bottom - PAGE_TOP - PAGE_BOTTOM;

    this->SetWindowPos(NULL, 0, 0, page_width, page_height, SWP_NOMOVE|SWP_NOZORDER); // muuta dialogin koko

    byp = page_height - bs - 1;                                      // nappuloiden etäisyys sivun yläreunasta

    curpos = 0 + xoffs[0];                                           // lähdetään siirtämän nappuloita
    m_bntLisaaUusi.SetWindowPos(NULL, curpos, byp + yoffs[0], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[1];
    m_btnPoistaValitut.SetWindowPos(NULL, curpos, byp + yoffs[1], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[2];
    m_stcSep3.SetWindowPos(NULL, curpos, byp + yoffs[2], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[3];
    m_btnErittely.SetWindowPos(NULL, curpos, byp + yoffs[3], 0, 0, SWP_NOSIZE|SWP_NOZORDER);

    curpos += xoffs[4];
    m_stcSep4.SetWindowPos(NULL, curpos, byp + yoffs[4], 0, 0, SWP_NOSIZE|SWP_NOZORDER);

    curpos += xoffs[5];
    m_stcSep1.SetWindowPos(NULL, curpos, byp + yoffs[5], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[6];
    m_stcValitut.SetWindowPos(NULL, curpos, byp + yoffs[6], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[7];
    m_stcSep2.SetWindowPos(NULL, curpos, byp + yoffs[7], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[8];
    m_stcYhteensa.SetWindowPos(NULL, curpos, byp + yoffs[8], 0, 0, SWP_NOSIZE|SWP_NOZORDER);

	byp = page_height - 264 - bs - PAGE_GAD_SPACE;
    m_lstTyomatkat.SetWindowPos(NULL, 0, 0, page_width - 1, byp, SWP_NOMOVE|SWP_NOZORDER);
}

void PpageTyomatkat::OnDatetimechangeDtpalkaen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    COleDateTime odt;

    m_dtpAlkaen.GetTime(odt);                        // Hae asetettu aika ja talleta asetuksiin
    Props::i().set(OPTIONS_ALKAEN_VIIMEISIN_T, (LPCSTR)odt.Format(LOCALE_NOUSEROVERRIDE, LOCALE_SYSTEM_DEFAULT));
    uusiHaku(NULL);

    *pResult = 0;
}

void PpageTyomatkat::OnDatetimechangeDtppaattyen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    COleDateTime odt;

    m_dtpPaattyen.GetTime(odt);                      // Hae asetettu aika ja talleta asetuksiin
    Props::i().set(OPTIONS_PAATTYEN_VIIMEISIN_T, (LPCSTR)odt.Format(LOCALE_NOUSEROVERRIDE, LOCALE_SYSTEM_DEFAULT));
    uusiHaku(NULL);

    *pResult = 0;
}

void PpageTyomatkat::OnSelchangeLsttyontekijat() 
{
	uusiHaku(NULL);                       // haetaan työmatkat
                                          // Checkbox päälle, jos kaikki valittu
    if(m_lstTyontekijat.GetCount() == m_lstTyontekijat.GetSelCount()) m_chkTyontekijat.SetCheck(1);
    else m_chkTyontekijat.SetCheck(0);
}

void PpageTyomatkat::OnChktyontekijat() 
{
    if(m_chkTyontekijat.GetCheck())        // Kaikki valituiksi
      m_lstTyontekijat.SelItemRange(TRUE, 0, m_lstTyontekijat.GetCount());
    else                                   // tai kaikki valitsemattomiksi
      m_lstTyontekijat.SelItemRange(FALSE, 0, m_lstTyontekijat.GetCount());

	uusiHaku(NULL);                       // haetaan työmatkat
}

void PpageTyomatkat::OnBtnalkaen() 
{
    RECT rect;
    CString cs;
    CMenu menu, *pPopup;

    cs = Props::i().get(OPTIONS_ALKAEN_T).c_str();

    VERIFY(menu.LoadMenu(IDR_ALKAEN));                               // Tee menu
    pPopup = menu.GetSubMenu(0);

    if(cs == DATE_VIIMEKSI_ASETETTU)                                 // Enabloi sopiva menu item
      pPopup->CheckMenuItem(IDM_PU_VIIMEKSI_ASETETTU, MF_BYCOMMAND|MF_CHECKED);
    else if(cs == DATE_NYKYINEN_PVM)
      pPopup->CheckMenuItem(IDM_PU_NYKYINEN_PVM, MF_BYCOMMAND|MF_CHECKED);
    else if(cs == DATE_NYKYINEN_M1)
      pPopup->CheckMenuItem(IDM_PU_NYKYINEN_M1, MF_BYCOMMAND|MF_CHECKED);
    else if(cs == DATE_NYKYINEN_M2)
      pPopup->CheckMenuItem(IDM_PU_NYKYINEN_M2, MF_BYCOMMAND|MF_CHECKED);
    else if(cs == DATE_NYKYINEN_M3)
      pPopup->CheckMenuItem(IDM_PU_NYKYINEN_M3, MF_BYCOMMAND|MF_CHECKED);
    else  //(DATE_VANHIN_TYO)
      pPopup->CheckMenuItem(IDM_PU_VANHIN_TYO, MF_BYCOMMAND|MF_CHECKED);

    m_btnAlkaen.GetWindowRect(&rect);                                // Näytä popup menu
    int r = pPopup->TrackPopupMenu(TPM_RETURNCMD|TPM_RIGHTALIGN|TPM_RIGHTBUTTON, rect.left, rect.top, this);

    if(r == 0) return;
    if(r == IDM_PU_VIIMEKSI_ASETETTU) cs = DATE_VIIMEKSI_ASETETTU;   // Ota asetus talteen
    else if(r == IDM_PU_VANHIN_TYO) cs = DATE_VANHIN_TYO;
    else if(r == IDM_PU_NYKYINEN_PVM) cs = DATE_NYKYINEN_PVM;
    else if(r == IDM_PU_NYKYINEN_M1) cs = DATE_NYKYINEN_M1;
    else if(r == IDM_PU_NYKYINEN_M2) cs = DATE_NYKYINEN_M2;
    else if(r == IDM_PU_NYKYINEN_M3) cs = DATE_NYKYINEN_M3;
    Props::i().set(OPTIONS_ALKAEN_T, (LPCSTR)cs);

    paivitaPaivays(0, "", NULL, TRUE);                               // Päivitä ohjaimet
}

void PpageTyomatkat::OnBtnpaattyen() 
{
    RECT rect;
    CString cs;
    CMenu menu, *pPopup;

    cs = Props::i().get(OPTIONS_PAATTYEN_T).c_str();

    VERIFY(menu.LoadMenu(IDR_PAATTYEN));                               // Tee menu
    pPopup = menu.GetSubMenu(0);

    if(cs == DATE_VIIMEKSI_ASETETTU)                                 // Enabloi sopiva menu item
      pPopup->CheckMenuItem(IDM_PU_VIIMEKSI_ASETETTU, MF_BYCOMMAND|MF_CHECKED);
    else if(cs == DATE_NYKYINEN_PVM)
      pPopup->CheckMenuItem(IDM_PU_NYKYINEN_PVM, MF_BYCOMMAND|MF_CHECKED);
    else  //(DATE_UUSIN_TYO)
      pPopup->CheckMenuItem(IDM_PU_UUSIN_TYO, MF_BYCOMMAND|MF_CHECKED);

    m_btnAlkaen.GetWindowRect(&rect);                                // Näytä popup menu
    int r = pPopup->TrackPopupMenu(TPM_RETURNCMD|TPM_RIGHTALIGN|TPM_RIGHTBUTTON, rect.left, rect.top, this);

    if(r == 0) return;
    if(r == IDM_PU_VIIMEKSI_ASETETTU) cs = DATE_VIIMEKSI_ASETETTU;   // Ota asetus talteen
    else if(r == IDM_PU_UUSIN_TYO) cs = DATE_UUSIN_TYO;
    else if(r == IDM_PU_NYKYINEN_PVM) cs = DATE_NYKYINEN_PVM;
    Props::i().set(OPTIONS_PAATTYEN_T, (LPCSTR)cs);

    paivitaPaivays(0, "", NULL, TRUE);                               // Päivitä ohjaimet
}

void PpageTyomatkat::OnChangeEdtkmkerroin() 
{
    CString cs;

    m_edtkmKerroin.GetWindowText(cs);                // Talleta uusi kilometrikorvauskerroin
    Props::i().set(OPTIONS_KMKERROIN, (LPCSTR)cs);

    uusiHaku(NULL);
}

void PpageTyomatkat::OnBtnlisaauusi() 
{ lisaaUusi(0); }

void PpageTyomatkat::OnBtnpoistavalitut() 
{ poistaValitut(); }

void PpageTyomatkat::OnBtnerittely() 
{ 
    int flags;
    RECT rect;
    CString cs;
    CMenu menu, *pPopup;

    VERIFY(menu.LoadMenu(IDR_ERITTELY_TM));                          // Tee menu
    pPopup = menu.GetSubMenu(0);

	pPopup->ModifyMenu(IDM_NAYTETYT_TYOMATKAT, MF_BYCOMMAND|MF_STRING, IDM_NAYTETYT_TYOMATKAT, Props::i().lang("IDR_ERITTELY_TM_1"));
	pPopup->ModifyMenu(IDM_VALITUT_TYOMATKAT, MF_BYCOMMAND|MF_STRING, IDM_VALITUT_TYOMATKAT, Props::i().lang("IDR_ERITTELY_TM_2"));
	pPopup->ModifyMenu(IDM_VALITUN_TYOMATKAT, MF_BYCOMMAND|MF_STRING, IDM_VALITUN_TYOMATKAT, Props::i().lang("IDR_ERITTELY_TM_3"));

    if(m_lstTyomatkat.GetItemCount() > 0) flags = MF_ENABLED;        // Enabloi sopivat menu itemit
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_NAYTETYT_TYOMATKAT, MF_BYCOMMAND|flags);

    if(m_lstTyomatkat.GetSelectedCount() > 0) flags = MF_ENABLED;    //
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_VALITUT_TYOMATKAT, MF_BYCOMMAND|flags);

    if(m_lstTyontekijat.GetSelCount() > 0) flags = MF_ENABLED;       //
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_VALITUN_TYOMATKAT, MF_BYCOMMAND|flags);

    m_btnErittely.GetWindowRect(&rect);                              // Näytä popup menu
    int r = pPopup->TrackPopupMenu(TPM_RETURNCMD|TPM_BOTTOMALIGN|TPM_RIGHTBUTTON, rect.left, rect.top, this);

    if(r == 0) return;
    else if(r == IDM_NAYTETYT_TYOMATKAT) eritteletNaytetytTyomatkat();
    else if(r == IDM_VALITUT_TYOMATKAT) eritteleValitutTyomatkat();
    else if(r == IDM_VALITUN_TYOMATKAT) eritteleValittujenTyomatkat();
}

void PpageTyomatkat::paivitaPaivays(int type, CString date, ItemData_travel *pid, BOOL haku)
{
    int i;
    CString cs;
    Paivays paivays;
    COleDateTime d1, d2;
    vector <int> ivect;

    if(date != "")                                   // Aloitus- tai lopetuspäivä annettu, aseta haun alkaen/päättyen uusiksi
	{
      i = atoi(date);
      if(type == UPDATE_START)
	  {
        m_dtpAlkaen.GetTime(d1);
        d2.SetDate(i>>10, (i>>5)&0x1F, i&0x1F);
        if(d2 < d1) d1 = d2;
        m_dtpAlkaen.SetTime(d1);
	  }
      if(type == UPDATE_END)
	  {
        m_dtpPaattyen.GetTime(d1);
        d2.SetDate(i>>10, (i>>5)&0x1F, i&0x1F);
        if(d2 > d1) d1 = d2;
        m_dtpPaattyen.SetTime(d1);
	  }
	}
    else                                             // Asetuksista
	{
      cs = Props::i().get(OPTIONS_ALKAEN_T).c_str(); // ALKAEN / - / - / - / - / - / - / - / - / - 
      if(cs == DATE_VIIMEKSI_ASETETTU)
	  {
        cs = Props::i().get(OPTIONS_ALKAEN_VIIMEISIN_T).c_str();
        if(cs != "") d1.ParseDateTime(cs, LOCALE_NOUSEROVERRIDE , LOCALE_SYSTEM_DEFAULT);
        else d1.GetCurrentTime();
	  }
      else if(cs == DATE_NYKYINEN_PVM)
	    d1 = d1.GetCurrentTime();
      else if(cs == DATE_NYKYINEN_M1)
	  { d1 = d1.GetCurrentTime(); d1.m_dt -= 365; }  // Karkausvuosia ei huomioida :)
      else if(cs == DATE_NYKYINEN_M2)
	  { d1 = d1.GetCurrentTime(); d1.m_dt -= 730; }
      else if(cs == DATE_NYKYINEN_M3)
	  { d1 = d1.GetCurrentTime(); d1.m_dt -= 1095; }
      else //(DATE_VANHIN_TYO)
	  {
        if((i = (ivect = paivays.jarjestaPaivat("TravelUnit", "StartDate", ASCENT)).size()) > 0)
          d1.SetDate(ivect[0]>>10, (ivect[0]>>5)&0x1F, ivect[0]&0x1F);
        else
          d1 = d1.GetCurrentTime();
	  }
      m_dtpAlkaen.SetTime(d1);

      cs = Props::i().get(OPTIONS_PAATTYEN_T).c_str(); // PÄÄTTYEN / - / - / - / - / - / - / - / - / - 
      if(cs == DATE_VIIMEKSI_ASETETTU)
	  {
        cs = Props::i().get(OPTIONS_PAATTYEN_VIIMEISIN_T).c_str();
        if(cs != "") d1.ParseDateTime(cs, LOCALE_NOUSEROVERRIDE , LOCALE_SYSTEM_DEFAULT);
        else d1.GetCurrentTime();
	  }
      else if(cs == DATE_NYKYINEN_PVM)
	    d1 = d1.GetCurrentTime();
      else //(DATE_UUSIN_TYO)
	  {
        if((i = (ivect = paivays.jarjestaPaivat("TravelUnit", "StartDate", ASCENT)).size()) > 0)
          d1.SetDate(ivect[i - 1]>>10, (ivect[i - 1]>>5)&0x1F, ivect[i - 1]&0x1F);
        else
          d1 = d1.GetCurrentTime();
	  }
      m_dtpPaattyen.SetTime(d1);
	}

    if(haku) uusiHaku(pid);
}

void PpageTyomatkat::paivitaTyontekijat(CString tyontekija, ItemData_travel *pid, BOOL haku)
{
    CString cs;
    DbSqlite db;
    int i, f, s;
    vector <CString> vect, vect_t;

    // LISÄTÄÄN TIETOKANTAAN LISÄTYT TYÖNTEKIJÄT LISTAANSA JA POISTETAAN TIETOKANNASTA POISTETUT TYÖNTEKIJÄT LISTASTA
    s = m_lstTyontekijat.GetCount();               // Valitut työntekijät muistiin
    for(i=0; i<s; i++)
	{ if(m_lstTyontekijat.GetSel(i) > 0) { m_lstTyontekijat.GetText(i, cs); vect_t.push_back(cs); } }
    m_lstTyontekijat.ResetContent();               // Tyhjennetään lista

    s = (vect = db.haeTaulusta("Worker", "DISTINCT Name, id", 2, "Name", 0)).size();
    for(i=0; i<s; i+=2)                            // työntekijät listaansa
	{
      f = m_lstTyontekijat.AddString(vect[i]);
      if(f != LB_ERR && f != LB_ERRSPACE)            // ItemDataan työntekijän id!!!
        m_lstTyontekijat.SetItemData(f, atoi(vect[i + 1]));
	}

    s = vect_t.size();                             // Merkitään valituiksi talteen otettujen nimien perusteella
    for(i=0; i<s; i++)
	{ if((f = m_lstTyontekijat.FindStringExact(-1, vect_t[i])) != LB_ERR) m_lstTyontekijat.SetSel(f, TRUE); }

                                                   // Yritetään valita ja scrollata näkyville annettu työntekijänimi
    f = m_lstTyontekijat.FindStringExact(-1, tyontekija);
    if(f != LB_ERR) { m_lstTyontekijat.SetSel(f, TRUE); m_lstTyontekijat.SetCaretIndex(f, TRUE); }

    if(haku) uusiHaku(pid);
}

void PpageTyomatkat::uusiHaku(ItemData_travel *old_pid)
{
    DbSqlite db;
    float kilo;
    Paivays paivays;
    int i, j, t, sel;
    COleDateTime codt;
    vector <int> ivect;
    vector <CString> vect;
    ItemData_travel *pid;
    CString cs, sd, ed, oid;
    vector <CString> tyontekijat;
    vector <CString> tapahtumat;

    if(old_pid) oid = old_pid->id;                   // Talteen, koska m_lstTyomatkat.DeleteAllItems(); tuhoaa ItemDatat

    if((j = m_lstTyontekijat.GetCount()) != LB_ERR)  // Haetaan valitut Worker.id:t vektoriin
	{
      for(i=0; i<j; i++)
	  {
        if(m_lstTyontekijat.GetSel(i) > 0)
		{
          sd.Format("%d", m_lstTyontekijat.GetItemData(i));           // Worker.id
          tyontekijat.push_back(sd);
		}
	  }
	}

    m_dtpAlkaen.GetTime(codt);                       // Aloitus ja lopetus päivät
    i = paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay());
    m_dtpPaattyen.GetTime(codt);
    j = paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay());
    if(i > j)                                        // varmista että  pienempi päiväys on ensin
	{ t = i; i = j; j = t; }
    sd.Format("%d", i);
    ed.Format("%d", j);

    if((cs = Props::i().get(OPTIONS_AIKAJARJESTYS_T).c_str()) == "") cs = DESCENT_S;  // ORDER BY ...

    tapahtumat = db.suodataTravelUnit(tyontekijat, sd, ed, cs);

    kilo = 0;                                        // Lasketaan kilometrimäärät samalla
    m_lstTyomatkat.DeleteAllItems();
    for(i=0, j=tapahtumat.size(); i<j; i += 15)      // Lisätään työntekijöiden työmatkat
	{
      pid = new ItemData_travel;                     // tunnistetiedot jokaiselle listan riville (helppo muokata yms.)
      pid->id = tapahtumat[i];
      pid->StartMeter = tapahtumat[i + 1];
      pid->EndMeter = tapahtumat[i + 2];
      pid->StartDate = tapahtumat[i + 3];
      pid->StartTime = tapahtumat[i + 4];
      pid->EndDate = tapahtumat[i + 5];
      pid->EndTime = tapahtumat[i + 6];
      pid->StartPlace = tapahtumat[i + 7];
      pid->EndPlace = tapahtumat[i + 8];
      pid->Purpose = tapahtumat[i + 9];
      pid->Private = tapahtumat[i + 10];
      pid->Worker_id = tapahtumat[i + 11];
      pid->ReportName = tapahtumat[i + 12];
      pid->ReportDate = tapahtumat[i + 13];
      pid->Biller_id = tapahtumat[i + 14];

      vect = db.haeTaulusta("Worker", "Name", 1, "", 1, "", "id", "=", pid->Worker_id);

      t = m_lstTyomatkat.GetItemCount();                                     
      sel = m_lstTyomatkat.InsertItem(LVIF_TEXT|LVIF_IMAGE, t, "", 0, 0, 4, 0);
      m_lstTyomatkat.SetItem(sel, 1, LVIF_TEXT, vect[0], 0, 0, 0, 0);								// Worker.Name
	  m_lstTyomatkat.SetItem(sel, 2, LVIF_TEXT, db.fixFloat(pid->StartMeter, TRUE), 0, 0, 0, 0);	// StartMeter
      m_lstTyomatkat.SetItem(sel, 3, LVIF_TEXT, db.fixFloat(pid->EndMeter, TRUE), 0, 0, 0, 0);		// EndMeter
      m_lstTyomatkat.SetItem(sel, 4, LVIF_TEXT, db.fixFloat(pid->Private, TRUE), 0, 0, 0, 0);		// Private
      ivect = paivays.date2int(pid->StartDate);														// StartDate, StartTime
      sd.Format("%d%s%d%s%d", ivect[0], DATE_SEP, ivect[1], DATE_SEP, ivect[2]);
      sd += DATETIME_IB + paivays.time2string(pid->StartTime);
      m_lstTyomatkat.SetItem(sel, 5, LVIF_TEXT, sd, 0, 0, 0, 0);
      ivect = paivays.date2int(pid->EndDate);														// EndDate, EndTime
      sd.Format("%d%s%d%s%d", ivect[0], DATE_SEP, ivect[1], DATE_SEP, ivect[2]);
      sd += DATETIME_IB + paivays.time2string(pid->EndTime);
      m_lstTyomatkat.SetItem(sel, 6, LVIF_TEXT, sd, 0, 0, 0, 0);
      m_lstTyomatkat.SetItem(sel, 7, LVIF_TEXT, pid->StartPlace, 0, 0, 0, 0);						// StartPlace
      m_lstTyomatkat.SetItem(sel, 8, LVIF_TEXT, pid->EndPlace, 0, 0, 0, 0);							// EndPlace
      m_lstTyomatkat.SetItem(sel, 9, LVIF_TEXT, pid->Purpose, 0, 0, 0, 0);							// Purpose
      m_lstTyomatkat.SetItemData(sel, (DWORD)pid);													// talletetaan struktuuri

      kilo += fabs(atof(pid->EndMeter) - atof(pid->StartMeter));             // : työajoa yhteensä
	}

    if(oid)                                          // Yritetään valita rivi jolla on old_pid:n tiedot
	{
      for(i=0, j = m_lstTyomatkat.GetItemCount(); i<j; i++) {
        pid = (ItemData_travel*)m_lstTyomatkat.GetItemData(i);
        if(oid == pid->id) break; }

      if(i != j) {
        m_lstTyomatkat.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
        m_lstTyomatkat.SetSelectionMark(i);
        m_lstTyomatkat.EnsureVisible(i, FALSE); }
	}

    if(j == 0) sd = "";                              // Näytetään kokonais km, yksityis km ja eurot
    else sd.Format(Props::i().lang("PPAGETYOMATKAT_17"), kilo, kilo * atof(Props::i().get(OPTIONS_KMKERROIN).c_str()));
    m_stcYhteensa.SetWindowText(sd);
}

void PpageTyomatkat::valitseKaikki()
{
    int i, s;

    s = m_lstTyomatkat.GetItemCount();
    for(i=0; i<s; i++) m_lstTyomatkat.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    m_lstTyomatkat.SetFocus();
    if(s > 0) m_lstTyomatkat.SetSelectionMark(0);
}

void PpageTyomatkat::lisaaUusi(int mode)
{
    int r;
    DlgUusiTyomatka d;
    ItemData_travel *pid;

	POSITION pos = m_lstTyomatkat.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		r = m_lstTyomatkat.GetNextSelectedItem(pos);
		if(!(pid = (ItemData_travel*)m_lstTyomatkat.GetItemData(r))) return;
	}
	d.m_pid = (mode == 0 ? NULL : pid);				// 0=uusi tapahtuma, 1=muokkaa entistä
	d.m_mode = mode;
	d.DoModal();									// Näytä muokkausdialogi, kutsuu OnOK:lla lisaaUusi(DlgUusiTyomatka *pd)
}

int PpageTyomatkat::lisaaUusi(DlgUusiTyomatka *pd)
{
	int r;
    DbSqlite db;
	Paivays paivays;
    ItemData_travel *pid, spid;
	CString worker_id, biller_id;
    vector <CString> vect, wo_vect, b_vect;

	if(pd->m_mode == 0)								// Lisäystila
	{
		vect.clear();									// Lisätään uusi TravelUnit
		vect.push_back(pd->m_startmeter);				// StartMeter
		vect.push_back(pd->m_endmeter);					// EndMeter
		vect.push_back(pd->m_starttime);				// StartTime
		vect.push_back(pd->m_endtime);					// EndTime
		vect.push_back(pd->m_private);					// Private
		vect.push_back(ID_TRAVELUNIT);					// type - TYPE_TRAVELUNIT (id: 3)
		vect.push_back(pd->m_startplace);				// StartPlace
		vect.push_back(pd->m_endplace);					// EndPlace
		vect.push_back(pd->m_purpose);					// Purpose
		r = db.lisaaTravelUnit(&vect, pd->m_worker_name, NOREPORTNAME, paivays.date2string(pd->m_StartDate), pd->m_biller_name);
		if(vect.size() == 0) return r;

		pid = &spid;									// ItemData* uudelle CListCtrl:n riville
		pid->id = vect[0];								// PALUUARVONA SAATU ID!!!
		pid->ReportName = NOREPORTNAME;
		pid->ReportDate = pd->m_StartDate;
	}
	else											// Muokkaustila
	{
		db.lisaaWorker(pd->m_worker_name, &worker_id);
		db.lisaaBiller(pd->m_biller_name, "", &biller_id, B_NOUPDATE);
		r = db.paivitaTravelUnit(pd->m_pid, 12,	TRAVELUNIT_STARTMETER,		pd->m_startmeter,
													TRAVELUNIT_ENDMETER,	pd->m_endmeter,
													TRAVELUNIT_STARTDATE,	pd->m_StartDate,
													TRAVELUNIT_STARTTIME,	pd->m_StartTime,
													TRAVELUNIT_ENDDATE,		pd->m_EndDate,
													TRAVELUNIT_ENDTIME,		pd->m_EndTime,
													TRAVELUNIT_STARTPLACE,	pd->m_startplace,
													TRAVELUNIT_ENDPLACE,	pd->m_endplace,
													TRAVELUNIT_PURPOSE,		pd->m_purpose,
													TRAVELUNIT_PRIVATE,		pd->m_private,
													TRAVELUNIT_WORKER_ID,	worker_id,
													TRAVELUNIT_BILLER_ID,	biller_id);

		pid = pd->m_pid;								// ItemData_travel*!!!
	}

	if(r == RETURN_EXISTS)
	{
		MessageBox(Props::i().lang("PPAGETYOMATKAT_11"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return r;
	}

	// hae uusien kohteiden id:t - fail quietly
	if((wo_vect = db.haeTaulusta("Worker", "id", 1, "", 1, "", "Name", "=", pd->m_worker_name)).size() == 0) return RETURN_OK;
	if((b_vect = db.haeTaulusta("Biller", "id", 1, "", 1, "", "Name", "=", pd->m_biller_name)).size() == 0) return RETURN_OK;

	pid->StartMeter = pd->m_startmeter;
	pid->EndMeter = pd->m_endmeter;
	pid->Private = pd->m_private;
	pid->StartDate = pd->m_StartDate;
	pid->StartTime = pd->m_StartTime;
	pid->EndDate = pd->m_EndDate;
	pid->EndTime = pd->m_EndTime;
	pid->StartPlace = pd->m_startplace;
	pid->EndPlace = pd->m_endplace;
	pid->Purpose = pd->m_purpose;
	pid->Worker_id = wo_vect[0];
	pid->Biller_id = b_vect[0];

	paivitaPaivays(0, "", pid, FALSE);											// Päivitä näyttö
	paivitaTyontekijat(pd->m_worker_name, pid, FALSE);
	uusiHaku(pid);
	m_lstTyomatkat.SetItem(r, 0, LVIF_STATE, 0, 0, LVIS_SELECTED, LVIS_SELECTED, 0);
	m_lstTyomatkat.SetSelectionMark(r);
	m_lstTyomatkat.EnsureVisible(r, FALSE);

	// Synkronoidaan eri näyttöjen listat tarvittaessa
	((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_TYOMATKAT, pd->m_sync);

	return RETURN_OK;
}

void PpageTyomatkat::poistaValitut()
{
    int i;
    DbSqlite db;
    POSITION pos;
    vector <CString> vect;

    if(m_lstTyomatkat.GetItemCount() == 0) return;
    if(m_lstTyomatkat.GetSelectedCount() == 0) return;

    if(MessageBox(Props::i().lang("PPAGETYOMATKAT_12"), Props::e().m_app_title, MB_YESNO|MB_ICONQUESTION) == IDNO)
      return;

    while((pos = m_lstTyomatkat.GetFirstSelectedItemPosition()))      // Käydään valitut läpi
    {
      i = m_lstTyomatkat.GetNextSelectedItem(pos);
      if(m_lstTyomatkat.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) // Poista tietokannasta
        db.poistaYleinen("TravelUnit", TRAVELUNIT_ID, ((ItemData_travel*)m_lstTyomatkat.GetItemData(i))->id, TRUE, "");    // TODO: talletetaan ensin _poistetut kansioon?
      m_lstTyomatkat.DeleteItem(i);                                      // Poista listasta
	}

    paivitaPaivays(0, "", NULL, FALSE);
    paivitaTyontekijat("", NULL, TRUE);
}

void PpageTyomatkat::muokkaaTyomatka(CRect cr, RECT rect, ItemData_travel *pid, LVHITTESTINFO hti)
{
	int r;
	CSize csize;
	DbSqlite db;
	Paivays paivays;
	COleDateTime codt;
	CString cs, cs2, apu;
	vector <CString> vect;
	pair <CString, CString> pari;
	pair <CString, CString> pari_s;
	pair <CString, CString> pari_e;
	IpeDlgEdit ipeDlgEdit;                           // Edit
	IpeDlgComboBox2 Ipedlgcombo2;                    // Dropdown (voi kirjoittaa tekstiä)

	// Muokkaa koko riviä   // // // // // // // // // // // // // // // // // // // // // //
	if(hti.iSubItem == 0)
		lisaaUusi(1);
	// Worker_id - CComboBox (Dropdown) // // // // // // // // // // // // // // // // // //
	else if(hti.iSubItem == 1)
	{
		if((vect = db.haeTaulusta("Worker", "Name", 1, "Name", 0)).size() == 0) return;
		Ipedlgcombo2.m_Ipe.x = rect.left + cr.left + 2;
		Ipedlgcombo2.m_Ipe.y = rect.top + cr.top;
		Ipedlgcombo2.m_Ipe.w = cr.right - cr.left + 2;
		Ipedlgcombo2.m_Ipe.h = 24;
		Ipedlgcombo2.m_Ipe.init(m_lstTyomatkat.GetItemText(hti.iItem, hti.iSubItem), NULL, &vect, 1, "", FALSE);
		Ipedlgcombo2.DoModal();
		if(!Ipedlgcombo2.m_Ipe.isEdited()) return;

		cs = Ipedlgcombo2.m_Ipe.getString();				// hae tiedot
		db.escape_c(&cs);									// escapointi
		db.lisaaWorker(cs, &cs2);							// lisää uusi Worker.Name tarvittaessa, cs2:ssa joka tapauksessa palauttaa Worker_id:n
		if(db.paivitaTravelUnit(pid, 1, TRAVELUNIT_WORKER_ID, cs2) == RETURN_OK)
		{
			pid->Worker_id = cs2;
			paivitaTyontekijat(cs, pid, TRUE);				// Päivitä suodattimet
		}
	}
	// StartDate, StartTime, EndDate, EndTime - CDateTimeCtrl // // // // // // // // // // //
	else if(hti.iSubItem == 5 || hti.iSubItem == 6)
	{
		cs = m_lstTyomatkat.GetItemText(hti.iItem, hti.iSubItem);      // (day.month.year, hour:minute) -> day.month.year.hour.minute) formaattiin Tokenizeria varten
		cs.Replace(DATETIME_IB, " ");
		ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
		ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
		ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
		ipeDlgEdit.m_Ipe.h = 24;
		ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
		ipeDlgEdit.DoModal();
		if(!ipeDlgEdit.m_Ipe.isEdited()) return;

		cs = ipeDlgEdit.m_Ipe.getString();
		if((pari = paivays.str2pair(cs)).first == "") return;
		if(hti.iSubItem == 5)
		{
			pari_s.first = pari.first; pari_s.second = pari.second;
			pari_e.first = pid->EndDate; pari_e.second = pid->EndTime;
		}
		else if(hti.iSubItem == 6)
		{
			pari_s.first = pid->StartDate; pari_s.second = pid->StartTime;
			pari_e.first = pari.first; pari_e.second = pari.second;
		}
		paivays.makeTimesLogical(pari_s, pari_e);

		if(db.paivitaTravelUnit(pid, 4, TRAVELUNIT_STARTDATE, pari_s.first, TRAVELUNIT_STARTTIME, pari_s.second, TRAVELUNIT_ENDDATE, pari_e.first, TRAVELUNIT_ENDTIME, pari_e.second) != RETURN_OK) return;
		pid->StartDate = pari_s.first; pid->StartTime = pari_s.second;
		pid->EndDate = pari_e.first; pid->EndTime = pari_e.second;
		paivitaPaivays(UPDATE_START, pid->StartDate, pid, FALSE);
		paivitaPaivays(UPDATE_END, pid->StartDate, pid, TRUE);
	}
	// StartMeter, EndMeter, Private, StartPlace, EndPlace, Purpose // // // // // // // // //
	else if(hti.iSubItem == 2 || hti.iSubItem == 3 || hti.iSubItem == 4 || hti.iSubItem == 7 || hti.iSubItem == 8 || hti.iSubItem == 9)
	{
		cs = m_lstTyomatkat.GetItemText(hti.iItem, hti.iSubItem);
		ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
		ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
		ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
		ipeDlgEdit.m_Ipe.h = 24;
		ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
		ipeDlgEdit.DoModal();
		if(!ipeDlgEdit.m_Ipe.isEdited()) return;

		cs = ipeDlgEdit.m_Ipe.getString();
		if(hti.iSubItem == 2)		{ cs2 = TRAVELUNIT_STARTMETER; cs = db.fixFloat(cs, TRUE); }
		else if(hti.iSubItem == 3)	{ cs2 = TRAVELUNIT_ENDMETER; cs = db.fixFloat(cs, TRUE); }
		else if(hti.iSubItem == 4)	{ cs2 = TRAVELUNIT_PRIVATE; cs = db.fixFloat(cs, TRUE); }
		else if(hti.iSubItem == 7)	cs2 = TRAVELUNIT_STARTPLACE;
		else if(hti.iSubItem == 8)	cs2 = TRAVELUNIT_ENDPLACE;
		else if(hti.iSubItem == 9)	cs2 = TRAVELUNIT_PURPOSE;

		db.escape_c(&cs);
		if(hti.iSubItem > 3)
			r = db.paivitaTravelUnit(pid, 1, cs2, cs);
		else
		{
			// Varmista mittarilukemien loogisuus, eli pienempi aloituslukemana
			if(cs2 == TRAVELUNIT_STARTMETER) cs2 = pid->EndMeter;
			else if(cs2 == TRAVELUNIT_ENDMETER) { cs2 = cs; cs = pid->StartMeter; }
			if(atof(cs) > atof(cs2)) { apu = cs; cs = cs2; cs2 = apu; }
			r = db.paivitaTravelUnit(pid, 2, TRAVELUNIT_STARTMETER, cs, TRAVELUNIT_ENDMETER, cs2);
		}

		if(r == RETURN_OK)
		{
			if(hti.iSubItem <= 3) { pid->StartMeter = cs; pid->EndMeter = cs2; }
			else if(hti.iSubItem == 4) pid->Private = cs;
			else if(hti.iSubItem == 7) pid->StartPlace = cs;
			else if(hti.iSubItem == 8) pid->EndPlace = cs;
			else if(hti.iSubItem == 9) pid->Purpose = cs;

			if(hti.iSubItem >= 4)
				m_lstTyomatkat.SetItemText(hti.iItem, hti.iSubItem, cs);
			else															// Matka muuttui, päivitä laskurit
			{
				laskeMatkat();
				m_lstTyomatkat.SetItemText(hti.iItem, 2, cs);
				m_lstTyomatkat.SetItemText(hti.iItem, 3, cs2);
			}
		}
	}
}

void PpageTyomatkat::columnHit(int iItem, int iSubItem)
{
    HDITEM hdi;
    CString cs;

    if(iSubItem == 5)                                // Muutetaan aloitusajan mukaan nousevaksi tai laskevaksi järjestykseksi
	{
      cs = Props::i().get(OPTIONS_AIKAJARJESTYS_T).c_str();
      if(cs == DESCENT_S) { cs = ASCENT_S; hdi.iImage = 6; }   // toggle
      else { cs = DESCENT_S; hdi.iImage = 7; }
      Props::i().set(OPTIONS_AIKAJARJESTYS_T, (LPCSTR)cs);     // talleta uusi asetus

      hdi.mask = HDI_IMAGE|HDI_FORMAT;                   // Vaihda kuva työmatkalistan otsikkoon 'Aloituspäivä'
      hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT;
      hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGETYOMATKAT_10");
      m_lstTyomatkat.GetHeaderCtrl()->SetItem(5, &hdi);

      uusiHaku(NULL);                                    // hae uudestaan
	}
}

void PpageTyomatkat::eritteletNaytetytTyomatkat()
{
    if(!haeItemDataList(&m_DlgErittely.m_tyomatkat, MODE_KAIKKINAYTETYT)) return;
    m_DlgErittely.m_mode = MODE_TYOMATKAT;
    m_DlgErittely.DoModal();
	vapautaItemDataList(&m_DlgErittely.m_tyomatkat, MODE_KAIKKINAYTETYT);
}

void PpageTyomatkat::eritteleValitutTyomatkat()
{
    if(!haeItemDataList(&m_DlgErittely.m_tyomatkat, MODE_VALITUT)) return;
    m_DlgErittely.m_mode = MODE_TYOMATKAT;
    m_DlgErittely.DoModal();
	vapautaItemDataList(&m_DlgErittely.m_tyomatkat, MODE_VALITUT);
}

void PpageTyomatkat::eritteleValittujenTyomatkat()
{
    if(!haeItemDataList(&m_DlgErittely.m_tyomatkat, MODE_TYONTEKIJOIDENTIEDOT)) return;
    m_DlgErittely.m_mode = MODE_TYOMATKAT;
    m_DlgErittely.DoModal();
	vapautaItemDataList(&m_DlgErittely.m_tyomatkat, MODE_TYONTEKIJOIDENTIEDOT);
}

BOOL PpageTyomatkat::haeItemDataList(vector <ItemData_travel*> *pvect, int mode)
{
    DbSqlite db;
    int i, j, s, c;
    CString cs, order;
    ItemData_travel *pid;
    vector <CString> vect;

    // Otetaan työntekijät ajan suhteen nousevassa järjestyksessä (pienin->suurin aloituspäivä)
    if((order = Props::i().get(OPTIONS_AIKAJARJESTYS_T).c_str()) == "") order = ASCENT_S;

    try
	{
      pvect->clear();                                // Tyhjennä vanhat tiedot pois

      if(mode == MODE_VALITUT)                       // Otetaan valitut työntekijät raporttilistasta
	  {
        if((s = m_lstTyomatkat.GetItemCount()) == 0) throw(ERR_REPE);
        if(order == ASCENT_S)
		{
          for(i=0; i<s; i++) {
            if(m_lstTyomatkat.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
              pvect->push_back((ItemData_travel*)m_lstTyomatkat.GetItemData(i)); }
		}
        else
		{
          for(i=s-1; i>-1; i--) {
            if(m_lstTyomatkat.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
              pvect->push_back((ItemData_travel*)m_lstTyomatkat.GetItemData(i)); }
		}
	  }
      else if(mode == MODE_KAIKKINAYTETYT)           // Otetaan kaikki työntekijät (näytetyt) raporttilistasta
	  {
        if((s = m_lstTyomatkat.GetItemCount()) == 0) throw(ERR_REPE);
        if(order == ASCENT_S) {
          for(i=0; i<s; i++)
            pvect->push_back((ItemData_travel*)m_lstTyomatkat.GetItemData(i)); }
        else {
          for(i=s-1; i>-1; i--)
            pvect->push_back((ItemData_travel*)m_lstTyomatkat.GetItemData(i)); }
	  }
      else if(mode == MODE_TYONTEKIJOIDENTIEDOT)     // Otetaan tiettyjen työntekijöiden kaikki tiedot
	  {
        if(m_lstTyontekijat.GetSelCount() < 1) throw(ERR_SELATLEASTONE);

        s = m_lstTyontekijat.GetCount();
        for(i=0; i<s; i++)
		{
          j = m_lstTyontekijat.GetSel(i);            // vain valitut työntekijät
          if(j == 0 || j == LB_ERR) continue;

          cs.Format("%d", m_lstTyontekijat.GetItemData(i));// ItemDatassa säilytetty id hakuehdoksi
          if((c = (vect = db.haeTaulusta("TravelUnit", "*", TRAVELUNIT_COLS, "StartDate", 1, "", "Worker_id", "=", cs)).size()) == 0)
            continue;

          for(j=0; j<c; j+=TRAVELUNIT_COLS)
		  {
            pid = new ItemData_travel;
            pid->id = vect[j];
            pid->StartMeter = vect[j + 1];
            pid->EndMeter = vect[j + 2];
            pid->StartDate = vect[j + 3];
            pid->StartTime = vect[j + 4];
            pid->EndDate = vect[j + 5];
            pid->EndTime = vect[j + 6];
            pid->StartPlace = vect[j + 7];
            pid->EndPlace = vect[j + 8];
            pid->Purpose = vect[j + 9];
            pid->Private = vect[j + 10];
            pid->Worker_id = vect[j + 11];
            pid->ReportName = vect[j + 12];
            pid->ReportDate = vect[j + 13];
            pid->Biller_id = vect[j + 14];
            pvect->push_back(pid);
		  }  
		}

        if(pvect->size() == 0) throw(ERR_NOWUNITS);  // Ei tietoja
	  }
      else if(mode == MODE_TYONTEKIJANTIEDOT)        // Otetaan tietyn työntekijän kaikki tiedot
	  {
        if(m_lstTyontekijat.GetSelCount() > 1) throw(ERR_SELONE);

        i = m_lstTyontekijat.GetCurSel();                // vain valittu työntekijä
        cs.Format("%d", m_lstTyontekijat.GetItemData(i));// ItemDatassa säilytetty id hakuehdoksi
        if((c = (vect = db.haeTaulusta("TravelUnit", "*", TRAVELUNIT_COLS, "StartDate", 1, "", "Worker_id", "=", cs)).size()) == 0) throw(ERR_NOWUNITS);

        for(j=0; j<c; j+=TRAVELUNIT_COLS)
		{
          pid = new ItemData_travel;
          pid->id = vect[j];
          pid->StartMeter = vect[j + 1];
          pid->EndMeter = vect[j + 2];
          pid->StartDate = vect[j + 3];
          pid->StartTime = vect[j + 4];
          pid->EndDate = vect[j + 5];
          pid->EndTime = vect[j + 6];
          pid->StartPlace = vect[j + 7];
          pid->EndPlace = vect[j + 8];
          pid->Purpose = vect[j + 9];
          pid->Private = vect[j + 10];
          pid->Worker_id = vect[j + 11];
          pid->ReportName = vect[j + 12];
          pid->ReportDate = vect[j + 13];
          pid->Biller_id = vect[j + 14];
          pvect->push_back(pid);
		}

        if(pvect->size() == 0) throw(ERR_NOWUNITS);  // Ei tietoja
	  }
	}
    catch(int err)
	{
      if(err == ERR_SELATLEASTONE) cs = Props::i().lang("PPAGETYOMATKAT_13");
      if(err == ERR_SELONE) cs = Props::i().lang("PPAGETYOMATKAT_14");
	  else if(err == ERR_REPE) cs = Props::i().lang("PPAGETYOMATKAT_15");
      else if(err == ERR_NOWUNITS) cs = Props::i().lang("PPAGETYOMATKAT_16");

      if(err != 0) MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return FALSE;
	}

    return TRUE;
}

void PpageTyomatkat::vapautaItemDataList(vector <ItemData_travel*> *pvect, int mode)
{
    if(mode == MODE_VALITUT) pvect->clear();
    else if(mode == MODE_KAIKKINAYTETYT) pvect->clear(); 
    else if(mode == MODE_TYONTEKIJOIDENTIEDOT || mode == MODE_TYONTEKIJANTIEDOT)
	{
      int i, s = pvect->size();                      // vapauta muisti
      for(i=0; i<s; i++) delete pvect->at(i);
      pvect->clear(); 
	}
}

// - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // -
// ON_UPDATE_COMMAND_UI // - // - // - // - // - // - // - // - // - // - // - // - // - // - // -
LRESULT PpageTyomatkat::OnKickIdle(WPARAM wparam, LPARAM lparam)
{
	UpdateDialogControls(this, FALSE);
	return 0L;
}

void PpageTyomatkat::OnUpdatePoistaValitut(CCmdUI* pCmdUI)
{
    if(m_lstTyomatkat.GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageTyomatkat::OnUpdateErittely(CCmdUI* pCmdUI)
{
    if(m_lstTyomatkat.GetSelectedCount() > 0 ||
       m_lstTyomatkat.GetItemCount() > 0 ||
       m_lstTyontekijat.GetSelCount() > 0) pCmdUI->Enable(TRUE);
    else pCmdUI->Enable(FALSE);
}

void PpageTyomatkat::OnItemchangedLsttyomatkat(NMHDR* pNMHDR, LRESULT* pResult) 
{ // Näytä valittujen kilometrit ja eurot
    int s;
    CString cs;
    POSITION pos;
    float kilo, cnv;
    ItemData_travel *pid;
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    kilo = 0.0f;
    pos = m_lstTyomatkat.GetFirstSelectedItemPosition();                 // Käydään valitut läpi
    while(pos)
    {
      s = m_lstTyomatkat.GetNextSelectedItem(pos);
      if(m_lstTyomatkat.GetItemState(s, LVIS_SELECTED) == LVIS_SELECTED) // Lasketaan valittujen kilometrit yhteen
	  {
        if((pid = (ItemData_travel*)m_lstTyomatkat.GetItemData(s))) 
		{
          cnv = atof(pid->EndMeter) - atof(pid->StartMeter);
          if(cnv < 0.0f) kilo -= cnv; else kilo += cnv;
		}
	  }
	}

    if(kilo > 0.0f)
      cs.Format(Props::i().lang("PPAGETYOMATKAT_17"), kilo, kilo * atof(Props::i().get(OPTIONS_KMKERROIN).c_str()));
    m_stcValitut.SetWindowText(cs);
	
    *pResult = 0;
}

void PpageTyomatkat::laskeMatkat()
{
    int i, s;
    float cnv;
    CString cs;
    float yht, val;
    ItemData_travel *pid;

    yht = val = 0.0f;
    s = m_lstTyomatkat.GetItemCount();
    for(i=0; i<s; i++)
	{
      if(!(pid = (ItemData_travel*)m_lstTyomatkat.GetItemData(i))) continue;    // seuraava, jos jostain syystä pointteri on nolla

      cnv = fabs(atof(pid->EndMeter) - atof(pid->StartMeter));
      if(m_lstTyomatkat.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) // lasketaan valitut yhteen
        val += cnv;
      yht += cnv;                                                        // lasketaan kaikki yhteen
	}

    if(yht == 0) cs = "";                            // Asetetaan kokonaiskm/eurot näkyville
    else cs.Format(Props::i().lang("PPAGETYOMATKAT_17"), yht, yht * atof(Props::i().get(OPTIONS_KMKERROIN).c_str()));
    m_stcYhteensa.SetWindowText(cs);

    if(val == 0) cs = "";                            // Asetetaan valittujen km:t/eurot näkyville
    else cs.Format(Props::i().lang("PPAGETYOMATKAT_17"), val, val * atof(Props::i().get(OPTIONS_KMKERROIN).c_str()));
    m_stcValitut.SetWindowText(cs);    
}

CMenu *PpageTyomatkat::createMenu()
{
	CMenu fileMenu;
	VERIFY(fileMenu.CreatePopupMenu());
	fileMenu.AppendMenu(MF_STRING, IDM_AVAA_RAPORTTI_TM, Props::i().lang("TYOMATKAT_MENU_1"));
	fileMenu.AppendMenu(MF_STRING, IDM_TALLETA_RAPORTTI_TM, Props::i().lang("TYOMATKAT_MENU_2"));
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