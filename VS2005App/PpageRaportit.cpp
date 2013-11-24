// PpageRaportit.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "Paivays.h"
#include "taikaDlg.h"
#include "PpageRaportit.h"
#include "IpeDlgEdit.h"
#include "IpeDlgComboBox.h"
#include "IpeDlgComboBox2.h"
#include "Props.h"
#include "afxpriv.h"
#include "DlgSMTP.h"
#include "DlgEtsi.h"
#include "DlgInfo.h"
#include "StringHelper_luokka.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PpageRaportit property page
//IMPLEMENT_DYNCREATE(PpageRaportit, CPropertyPage)

PpageRaportit::PpageRaportit() //: GenericChildDialogDialog(PpageRaportit::IDD)
{
	//{{AFX_DATA_INIT(PpageRaportit)
	//}}AFX_DATA_INIT
}

PpageRaportit::~PpageRaportit()
{
}

void PpageRaportit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PpageRaportit)
	DDX_Control(pDX, IDC_STCREPORT, m_stcReport);
	DDX_Control(pDX, IDC_STCSEP5, m_stcSep5);
	DDX_Control(pDX, IDC_STCSEP4, m_stcSep4);
	DDX_Control(pDX, IDC_STCSEP3, m_stcSep3);
	DDX_Control(pDX, IDC_STCSEP2, m_stcSep2);
	DDX_Control(pDX, IDC_STCSEP1, m_stcSep1);
	DDX_Control(pDX, IDC_BTNYHTMORE, m_btnYhtMore);
	DDX_Control(pDX, IDC_BTNVALMORE, m_btnValMore);
	DDX_Control(pDX, IDC_STCVALITUT, m_stcValitut);
	DDX_Control(pDX, IDC_BTNETSI, m_btnEtsi);
	DDX_Control(pDX, IDC_BTNLASKUTA, m_btnLaskuta);
	DDX_Control(pDX, IDC_BTNPAATTYEN, m_btnPaattyen);
	DDX_Control(pDX, IDC_BTNALKAEN, m_btnAlkaen);
	DDX_Control(pDX, IDC_STCAJAT, m_stcAjat);
	DDX_Control(pDX, IDC_CMBAIKA, m_cmbAika);
	DDX_Control(pDX, IDC_BTNERITTELY, m_btnErittely);
	DDX_Control(pDX, IDC_BTNPOISTAVALITUT, m_btnPoistaValitut);
	DDX_Control(pDX, IDC_BTNLISAAUUSI, m_btnLisaaUusi);
	DDX_Control(pDX, IDC_CHKTYOTYYPIT, m_chkTyotyypit);
	DDX_Control(pDX, IDC_CHKTYONTEKIJAT, m_chkTyontekijat);
	DDX_Control(pDX, IDC_CHKASIAKKAAT, m_chkAsiakkaat);
	DDX_Control(pDX, IDC_CHKASIAKASRYHMAT, m_chkAsiakasryhmat);
	DDX_Control(pDX, IDC_LSTTYOTYYPPI, m_lstTyotyypit);
	DDX_Control(pDX, IDC_LSTTYONTEKIJA, m_lstTyontekijat);
	DDX_Control(pDX, IDC_LSTASIAKASRYHMA, m_lstAsiakasryhmat);
	DDX_Control(pDX, IDC_LSTASIAKAS, m_lstAsiakkaat);
	DDX_Control(pDX, IDC_LSTTYOAJAT, m_lstTyoajat);
	DDX_Control(pDX, IDC_LSTMYYNNIT, m_lstMyynnit);
	DDX_Control(pDX, IDC_DTPPAATTYEN, m_dtpPaattyen);
	DDX_Control(pDX, IDC_DTPALKAEN, m_dtpAlkaen);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PpageRaportit, CDialog)
	//{{AFX_MSG_MAP(PpageRaportit)
	ON_LBN_SELCHANGE(IDC_LSTASIAKAS, OnSelchangeLstasiakas)
	ON_BN_CLICKED(IDC_CHKTYOTYYPIT, OnChktyotyypit)
	ON_BN_CLICKED(IDC_CHKASIAKASRYHMAT, OnChkasiakasryhmat)
	ON_BN_CLICKED(IDC_CHKASIAKKAAT, OnChkasiakkaat)
	ON_BN_CLICKED(IDC_CHKTYONTEKIJAT, OnChktyontekijat)
	ON_LBN_SELCHANGE(IDC_LSTASIAKASRYHMA, OnSelchangeLstasiakasryhma)
	ON_LBN_SELCHANGE(IDC_LSTTYOTYYPPI, OnSelchangeLsttyotyyppi)
	ON_LBN_SELCHANGE(IDC_LSTTYONTEKIJA, OnSelchangeLsttyontekija)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTPALKAEN, OnDatetimechangeDtpalkaen)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTPPAATTYEN, OnDatetimechangeDtppaattyen)
	ON_BN_CLICKED(IDC_RDLASKUTUS1, OnRdlaskutus)
	ON_BN_CLICKED(IDC_BTNLISAAUUSI, OnBtnlisaauusi)
	ON_BN_CLICKED(IDC_BTNPOISTAVALITUT, OnBtnpoistavalitut)
	ON_BN_CLICKED(IDC_BTNERITTELY, OnBtnerittely)
	ON_CBN_SELCHANGE(IDC_CMBAIKA, OnSelchangeCmbaika)
	ON_BN_CLICKED(IDC_BTNALKAEN, OnBtnalkaen)
	ON_BN_CLICKED(IDC_BTNPAATTYEN, OnBtnpaattyen)
	ON_BN_CLICKED(IDC_BTNLASKUTA, OnBtnlaskuta)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTNETSI, OnBtnetsi)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTTYOAJAT, OnItemchangedLstraportti)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTMYYNNIT, OnItemchangedLstraportti)
	ON_BN_CLICKED(IDC_RDLASKUTUS2, OnRdlaskutus)
	ON_BN_CLICKED(IDC_RDLASKUTUS3, OnRdlaskutus)
	ON_BN_CLICKED(IDC_BTNVALMORE, OnBtnvalmore)
	ON_BN_CLICKED(IDC_BTNYHTMORE, OnBtnyhtmore)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_KICKIDLE, OnKickIdle)              // ON_UPDATE_COMMAND_UI
	ON_UPDATE_COMMAND_UI(IDC_BTNPOISTAVALITUT, OnUpdatePoistaValitut)
	ON_UPDATE_COMMAND_UI(IDC_BTNLASKUTA, OnUpdateLaskuta)
    ON_UPDATE_COMMAND_UI(IDC_BTNERITTELY, OnUpdateErittely)
    ON_UPDATE_COMMAND_UI(IDC_BTNVALMORE, OnUpdateValInfo)
    ON_UPDATE_COMMAND_UI(IDC_BTNYHTMORE, OnUpdateYhtInfo)
	ON_BN_CLICKED(IDC_RDNAYTA1, &PpageRaportit::OnRadnayta)
	ON_BN_CLICKED(IDC_RDNAYTA2, &PpageRaportit::OnRadnayta)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PpageRaportit message handlers
BOOL PpageRaportit::OnInitDialog() 
{
    HDITEM hdi;
    CString cs;
    CRect rcList;
    DbSqlite db;
    Paivays paivays;
	COleDateTime codt;
    vector<CString> vect;
    vector<int> ivect;

	CDialog::OnInitDialog();

	SetDlgItemText(IDC_CHKASIAKASRYHMAT, Props::i().lang("PPAGERAPORTIT_C1"));
	SetDlgItemText(IDC_CHKASIAKKAAT, Props::i().lang("PPAGERAPORTIT_C2"));
	SetDlgItemText(IDC_CHKTYOTYYPIT, Props::i().lang("PPAGERAPORTIT_C3"));
	SetDlgItemText(IDC_CHKTYONTEKIJAT, Props::i().lang("PPAGERAPORTIT_C4"));
	SetDlgItemText(IDC_STATIC1, Props::i().lang("PPAGERAPORTIT_C5"));
	SetDlgItemText(IDC_STATIC2, Props::i().lang("PPAGERAPORTIT_C6"));
	SetDlgItemText(IDC_STATIC3, Props::i().lang("PPAGERAPORTIT_C7"));
	SetDlgItemText(IDC_STATIC4, Props::i().lang("PPAGERAPORTIT_C8"));
	SetDlgItemText(IDC_STATIC5, Props::i().lang("PPAGERAPORTIT_C9"));
	SetDlgItemText(IDC_RDLASKUTUS1, Props::i().lang("PPAGERAPORTIT_C10"));
	SetDlgItemText(IDC_RDLASKUTUS2, Props::i().lang("PPAGERAPORTIT_C11"));
	SetDlgItemText(IDC_RDLASKUTUS3, Props::i().lang("PPAGERAPORTIT_C12"));
	SetDlgItemText(IDC_RDNAYTA1, Props::i().lang("PPAGERAPORTIT_C13"));
	SetDlgItemText(IDC_RDNAYTA2, Props::i().lang("PPAGERAPORTIT_C14"));
	SetDlgItemText(IDC_BTNLISAAUUSI, Props::i().lang("PPAGERAPORTIT_C15"));
	SetDlgItemText(IDC_BTNPOISTAVALITUT, Props::i().lang("PPAGERAPORTIT_C16"));
	SetDlgItemText(IDC_BTNLASKUTA, Props::i().lang("PPAGERAPORTIT_C17"));
	SetDlgItemText(IDC_BTNERITTELY, Props::i().lang("PPAGERAPORTIT_C18"));
	SetDlgItemText(IDC_STCSEP4, Props::i().lang("PPAGERAPORTIT_C19"));
	SetDlgItemText(IDC_STCSEP5, Props::i().lang("PPAGERAPORTIT_C20"));

	m_cmbAika.AddString(Props::i().lang("DEFINES_3"));
	m_cmbAika.AddString(Props::i().lang("DEFINES_4"));
	m_cmbAika.AddString(Props::i().lang("DEFINES_5"));

    // Nappuloiden bitmapit
    m_bmpEtsi.LoadBitmap(IDB_BMPBINOCULAR);                          //
    m_bmpInfo.LoadBitmap(IDB_BMPINFO);
    m_bmpCalendar.LoadBitmap(IDB_BMPCALENDAR);
    m_btnEtsi.SetBitmap(m_bmpEtsi);                                  //
    m_btnValMore.SetBitmap(m_bmpInfo);
    m_btnYhtMore.SetBitmap(m_bmpInfo);
    m_btnAlkaen.SetBitmap(m_bmpCalendar);
    m_btnPaattyen.SetBitmap(m_bmpCalendar);

    // Alustetaan näytön tilat
    m_nayta = ID_WORKUNIT;                           // näytä työajat aluksi
    CheckRadioButton(IDC_RDNAYTA1, IDC_RDNAYTA2, IDC_RDNAYTA1);
    m_stcReport.SetWindowText(Props::i().lang("PPAGERAPORTIT_1"));
    m_chkTyotyypit.SetWindowText(Props::i().lang("PPAGERAPORTIT_2"));

    // Alustetaan Tyoajat CListCtrl
	m_lstTyoajat.m_omistaja = O_TYOAJAT;
	m_lstTyoajat.m_props = OPTIONS_LSTHEADER_RATA;
	ListView_SetExtendedListViewStyleEx(m_lstTyoajat.GetSafeHwnd(), // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_SHOWSELALWAYS/*|LVS_EX_SUBITEMIMAGES*/ , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_SHOWSELALWAYS/*|LVS_EX_SUBITEMIMAGES*/);

	vector<string> vec = StringHelper::split(Props::i().get((LPCSTR)m_lstTyoajat.m_props), ';');
    if(vec.size() < 8)
	{
      m_lstTyoajat.GetClientRect(&rcList);                              // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
	  rcList.right -= 18;
      m_lstTyoajat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstTyoajat.InsertColumn(1, Props::i().lang("PPAGERAPORTIT_3"), LVCFMT_LEFT, rcList.right * 0.25, -1);
      m_lstTyoajat.InsertColumn(2, Props::i().lang("PPAGERAPORTIT_4"), LVCFMT_LEFT, rcList.right * 0.15, -1);
      m_lstTyoajat.InsertColumn(3, Props::i().lang("PPAGERAPORTIT_5"), LVCFMT_LEFT, rcList.right * 0.15, -1);
      m_lstTyoajat.InsertColumn(4, Props::i().lang("PPAGERAPORTIT_6"), LVCFMT_LEFT, rcList.right * 0.13, -1);
      m_lstTyoajat.InsertColumn(5, Props::i().lang("PPAGERAPORTIT_7"), LVCFMT_LEFT, rcList.right * 0.13, -1);
      m_lstTyoajat.InsertColumn(6, Props::i().lang("PPAGERAPORTIT_8"), LVCFMT_LEFT, rcList.right * 0.10, -1);
      m_lstTyoajat.InsertColumn(7, Props::i().lang("PPAGERAPORTIT_9"), LVCFMT_LEFT, rcList.right * 0.095, -1);
	}
    else
	{
      m_lstTyoajat.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstTyoajat.InsertColumn(1, Props::i().lang("PPAGERAPORTIT_3"), LVCFMT_LEFT, StringHelper::parseInt(vec[1]), -1);
      m_lstTyoajat.InsertColumn(2, Props::i().lang("PPAGERAPORTIT_4"), LVCFMT_LEFT, StringHelper::parseInt(vec[2]), -1);
      m_lstTyoajat.InsertColumn(3, Props::i().lang("PPAGERAPORTIT_5"), LVCFMT_LEFT, StringHelper::parseInt(vec[3]), -1);
      m_lstTyoajat.InsertColumn(4, Props::i().lang("PPAGERAPORTIT_6"), LVCFMT_LEFT, StringHelper::parseInt(vec[4]), -1);
      m_lstTyoajat.InsertColumn(5, Props::i().lang("PPAGERAPORTIT_7"), LVCFMT_LEFT, StringHelper::parseInt(vec[5]), -1);
      m_lstTyoajat.InsertColumn(6, Props::i().lang("PPAGERAPORTIT_8"), LVCFMT_LEFT, StringHelper::parseInt(vec[6]), -1);
      m_lstTyoajat.InsertColumn(7, Props::i().lang("PPAGERAPORTIT_9"), LVCFMT_LEFT, StringHelper::parseInt(vec[7]), -1);
	}

    // Alustetaan Myynnit CListCtrl
    m_lstMyynnit.m_omistaja = O_MYYNNIT;
	m_lstMyynnit.m_props = OPTIONS_LSTHEADER_RAMY;
	ListView_SetExtendedListViewStyleEx(m_lstMyynnit.GetSafeHwnd(), // Valitsee koko rivin kerralla ja näytä ruudukko
		    LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_SHOWSELALWAYS/*|LVS_EX_SUBITEMIMAGES*/ , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_SHOWSELALWAYS/*|LVS_EX_SUBITEMIMAGES*/);

	vec = StringHelper::split(Props::i().get((LPCSTR)m_lstMyynnit.m_props), ';');
    if(vec.size() < 11)
	{
      m_lstMyynnit.GetClientRect(&rcList);                             // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
	  rcList.right -= 18;
      m_lstMyynnit.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstMyynnit.InsertColumn(1, Props::i().lang("PPAGERAPORTIT_3"), LVCFMT_LEFT, rcList.right * 0.25, -1);
      m_lstMyynnit.InsertColumn(2, Props::i().lang("PPAGERAPORTIT_4"), LVCFMT_LEFT, rcList.right * 0.15, -1);
      m_lstMyynnit.InsertColumn(3, Props::i().lang("PPAGERAPORTIT_5"), LVCFMT_LEFT, rcList.right * 0.15, -1);
      m_lstMyynnit.InsertColumn(4, Props::i().lang("PPAGERAPORTIT_6"), LVCFMT_LEFT, rcList.right * 0.13, -1);
      m_lstMyynnit.InsertColumn(5, Props::i().lang("PPAGERAPORTIT_7"), LVCFMT_LEFT, rcList.right * 0.13, -1);
      m_lstMyynnit.InsertColumn(6, Props::i().lang("PPAGERAPORTIT_8"), LVCFMT_LEFT, rcList.right * 0.10, -1);
      m_lstMyynnit.InsertColumn(7, Props::i().lang("PPAGERAPORTIT_9"), LVCFMT_LEFT, rcList.right * 0.095, -1);
      m_lstMyynnit.InsertColumn(8, Props::i().lang("PPAGERAPORTIT_10"), LVCFMT_LEFT, rcList.right * 0.12, -1);
      m_lstMyynnit.InsertColumn(9, Props::i().lang("PPAGERAPORTIT_11"), LVCFMT_LEFT, rcList.right * 0.12, -1);
      m_lstMyynnit.InsertColumn(10, Props::i().lang("PPAGERAPORTIT_12"), LVCFMT_LEFT, rcList.right * 0.10, -1);
	}
    else
	{
      m_lstMyynnit.InsertColumn(0, "", LVCFMT_LEFT, 18, -1);
      m_lstMyynnit.InsertColumn(1, Props::i().lang("PPAGERAPORTIT_3"), LVCFMT_LEFT, StringHelper::parseInt(vec[1]), -1);
      m_lstMyynnit.InsertColumn(2, Props::i().lang("PPAGERAPORTIT_4"), LVCFMT_LEFT, StringHelper::parseInt(vec[2]), -1);
      m_lstMyynnit.InsertColumn(3, Props::i().lang("PPAGERAPORTIT_5"), LVCFMT_LEFT, StringHelper::parseInt(vec[3]), -1);
      m_lstMyynnit.InsertColumn(4, Props::i().lang("PPAGERAPORTIT_6"), LVCFMT_LEFT, StringHelper::parseInt(vec[4]), -1);
      m_lstMyynnit.InsertColumn(5, Props::i().lang("PPAGERAPORTIT_7"), LVCFMT_LEFT, StringHelper::parseInt(vec[5]), -1);
      m_lstMyynnit.InsertColumn(6, Props::i().lang("PPAGERAPORTIT_8"), LVCFMT_LEFT, StringHelper::parseInt(vec[6]), -1);
      m_lstMyynnit.InsertColumn(7, Props::i().lang("PPAGERAPORTIT_9"), LVCFMT_LEFT, StringHelper::parseInt(vec[7]), -1);
      m_lstMyynnit.InsertColumn(8, Props::i().lang("PPAGERAPORTIT_10"), LVCFMT_LEFT, StringHelper::parseInt(vec[8]), -1);
      m_lstMyynnit.InsertColumn(9, Props::i().lang("PPAGERAPORTIT_11"), LVCFMT_LEFT, StringHelper::parseInt(vec[9]), -1);
      m_lstMyynnit.InsertColumn(10, Props::i().lang("PPAGERAPORTIT_12"), LVCFMT_LEFT, StringHelper::parseInt(vec[10]), -1);
	}

	// jos listan päälle tulee muita kontrolleja, tämä estää niitä jäämästä alle tai, että niiden päälle piirretään
	m_lstTyoajat.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);
	m_lstMyynnit.ModifyStyle(0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 0);

	m_lstTyoajat.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	m_lstMyynnit.SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

	// CImageList listoihin ja niiden headereihin
	m_lstTyoajat.SetImageList(Props::e().m_pCImageList, LVSIL_SMALL);
	m_lstMyynnit.SetImageList(Props::e().m_pCImageList, LVSIL_SMALL);
	m_lstTyoajat.GetHeaderCtrl()->SetImageList(Props::e().m_pCImageList/*, LVSIL_SMALL*/);
	m_lstMyynnit.GetHeaderCtrl()->SetImageList(Props::e().m_pCImageList/*, LVSIL_SMALL*/);

    hdi.mask = HDI_IMAGE|HDI_FORMAT;
    hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT;
	hdi.iImage = (Props::i().get(OPTIONS_AIKAJARJESTYS_R) == ASCENT_S ? 6 : 7);
    hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGERAPORTIT_13");
    m_lstTyoajat.GetHeaderCtrl()->SetItem(4, &hdi);

    hdi.mask = HDI_IMAGE|HDI_FORMAT;
    hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT;
	hdi.iImage = (Props::i().get(OPTIONS_AIKAJARJESTYS_R) == ASCENT_S ? 6 : 7);
    hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGERAPORTIT_13");
    m_lstMyynnit.GetHeaderCtrl()->SetItem(4, &hdi);

	// Työajat oletuksena näytöllä
	m_plstRaportit = &m_lstTyoajat;

    m_laskutus = ALLREPORTS;                         // laskutuksen tila
    CheckRadioButton(IDC_RDLASKUTUS1, IDC_RDLASKUTUS3, IDC_RDLASKUTUS3);

	m_ajat = StringHelper::parseInt(Props::i().get(OPTIONS_AJAT).c_str());
    if(m_ajat == TIME_MINUTES) m_cmbAika.SetCurSel(0);
    else if(m_ajat == TIME_HOURS) m_cmbAika.SetCurSel(1);
    else if(m_ajat == TIME_CALLS) m_cmbAika.SetCurSel(2);

    paivitaTyotyyppi("", NULL, FALSE);               // Työtyypit valituiksi
    m_lstTyotyypit.SelItemRange(TRUE, 0, m_lstTyotyypit.GetCount());
    m_chkTyotyypit.SetCheck(1);

    OnSetActive();                                   // Päivitä kaikki kontrollit alustavasti

    m_haku = TRUE;                                   // Voi hakea
    uusiHaku(NULL);                                  // Hae asetetuilla tiedoilla

    return TRUE;
}

void PpageRaportit::OnDestroy() 
{
    CDialog::OnDestroy();
}

BOOL PpageRaportit::OnSetActive() 
{
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

      paivitaTyontekijat("", NULL, FALSE);           // Päivitetään näyttö
      paivitaTyotyyppi("", NULL, FALSE);
      paivitaPaivays(0, "", NULL, FALSE);
      paivitaAARListat("", NULL, FALSE);
	  uusiHaku(NULL);

	  firstDraw = FALSE;
	}

	if(Props::e().m_sync_raportit != 0)
	{
      if((Props::e().m_sync_raportit & SYNC_ASIAKASRYHMAT) || (Props::e().m_sync_raportit & SYNC_ASIAKKAAT)) paivitaAARListat("", NULL, FALSE);
      if((Props::e().m_sync_raportit & SYNC_TYOTYYPIT)) paivitaTyotyyppi("", NULL, FALSE);
      if((Props::e().m_sync_raportit & SYNC_TYONTEKIJAT)) paivitaTyontekijat("", NULL, FALSE);
      uusiHaku(NULL);

	  Props::e().m_sync_raportit = 0;
	}

    return TRUE;//CPropertyPage::OnSetActive();
}

void PpageRaportit::windowSize()
{
    static int xoffs[14] = { 0, 101, 103, 9, 103, 9, 103, 9, 88, 36, 104, 19, 51, 104 };
    static int yoffs[14] = { 0, 0, 2, 0, 2, 0, 2, 0, 3, 0, 0, 3, 0, 0 };
    RECT trect, crect;
    int curpos, bs, byp, page_width, page_height; // button size, button y-position

    if(m_btnLisaaUusi.GetSafeHwnd() == 0) return;
    if(m_btnPoistaValitut.GetSafeHwnd() == 0) return;
    if(m_stcSep1.GetSafeHwnd() == 0) return;
    if(m_btnLaskuta.GetSafeHwnd() == 0) return;
    if(m_stcSep2.GetSafeHwnd() == 0) return;
    if(m_btnErittely.GetSafeHwnd() == 0) return;
    if(m_stcSep3.GetSafeHwnd() == 0) return;
    if(m_cmbAika.GetSafeHwnd() == 0) return;
    if(m_stcSep4.GetSafeHwnd() == 0) return;
    if(m_stcValitut.GetSafeHwnd() == 0) return;
    if(m_btnValMore.GetSafeHwnd() == 0) return;
    if(m_stcSep5.GetSafeHwnd() == 0) return;
    if(m_stcAjat.GetSafeHwnd() == 0) return;
    if(m_btnYhtMore.GetSafeHwnd() == 0) return;
    if(m_lstTyoajat.GetSafeHwnd() == 0) return;
    if(m_lstMyynnit.GetSafeHwnd() == 0) return;

    m_btnLisaaUusi.GetClientRect(&trect);                            // nappulan koko
    bs = trect.bottom;
    ((CTaikaDlg*)GetParent())->m_tabMain.GetItemRect(0, &trect);     // tabin headerin koko
    ((CTaikaDlg*)GetParent())->m_tabMain.GetClientRect(&crect);      // tabin koko

    page_width = crect.right - PAGE_LEFT - PAGE_RIGHT;               // sivun koko: w = tabin w - marginaalit, h = tabin h - tabin h - marginaalit
    page_height = crect.bottom - trect.bottom - PAGE_TOP - PAGE_BOTTOM;

    this->SetWindowPos(NULL, 0, 0, page_width, page_height, SWP_NOMOVE|SWP_NOZORDER); // muuta dialogin koko

    byp = page_height - bs - 1;                                      // nappuloiden etäisyys sivun yläreunasta

    curpos = 0 + xoffs[0];                                           // lähdetään siirtämän nappuloita
    m_btnLisaaUusi.SetWindowPos(NULL, curpos, byp + yoffs[0], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[1];
    m_btnPoistaValitut.SetWindowPos(NULL, curpos, byp + yoffs[1], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[2];
    m_stcSep1.SetWindowPos(NULL, curpos, byp + yoffs[2], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[3];
    m_btnLaskuta.SetWindowPos(NULL, curpos, byp + yoffs[3], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[4];
    m_stcSep2.SetWindowPos(NULL, curpos, byp + yoffs[4], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[5];
    m_btnErittely.SetWindowPos(NULL, curpos, byp + yoffs[5], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[6];
    m_stcSep3.SetWindowPos(NULL, curpos, byp + yoffs[6], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[7];
    m_cmbAika.SetWindowPos(NULL, curpos, byp + yoffs[7], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[8];
    m_stcSep4.SetWindowPos(NULL, curpos, byp + yoffs[8], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[9];
    m_stcValitut.SetWindowPos(NULL, curpos, byp + yoffs[9], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[10];
    m_btnValMore.SetWindowPos(NULL, curpos, byp + yoffs[10], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[11];
    m_stcSep5.SetWindowPos(NULL, curpos, byp + yoffs[11], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[12];
    m_stcAjat.SetWindowPos(NULL, curpos, byp + yoffs[12], 0, 0, SWP_NOSIZE|SWP_NOZORDER);
    curpos += xoffs[13];
    m_btnYhtMore.SetWindowPos(NULL, curpos, byp + yoffs[13], 0, 0, SWP_NOSIZE|SWP_NOZORDER);

	byp = page_height - 284 - bs - PAGE_GAD_SPACE;
	m_lstTyoajat.SetWindowPos(NULL, 0, 0, page_width - 1, byp, SWP_NOMOVE|SWP_NOZORDER);
    m_lstMyynnit.SetWindowPos(NULL, 0, 0, page_width - 1, byp, SWP_NOMOVE|SWP_NOZORDER);
}

void PpageRaportit::uusiHaku(ItemData *old_pid)
{
    DbSqlite db;
    ItemData *pid;
    float time, cnv;
    Paivays paivays;
    COleDateTime codt;
    vector <int> ivect;
    vector <CString> vect;
    vector <CString> wt_vect;
    vector <CString> wo_vect;
    vector <CString> asiakkaat;
    vector <CString> tyotyypit;
    vector <CString> tapahtumat;
    vector <CString> tyontekijat;
    CString sd, ed, cs, pid_id;
    int s, e, t, i, j, sel/*, nayta*/;

    if(!m_haku) return;                              // Haku estetty toistaiseksi

    if(old_pid)              // Haun lopuksi yritetään scrollata näkyville rivi jolla on nämä tiedot.
	  pid_id = old_pid->id;  // Tiedot on otettava ylös muistiin, koska old_pid tuhoutuu poistettaessa listasta itemit.

    m_plstRaportit->DeleteAllItems();                // Tyhjennetään vanhat tapahtumat pois -> käyttäjä näkee heti, että jotain tapahtuu

    if((e = m_lstAsiakkaat.GetCount()) != LB_ERR)    // Haetaan valitut WorkPlace.id:t vektoriin
	{
      for(s=0; s<e; s++)
	  {
        if(m_lstAsiakkaat.GetSel(s) > 0)
		{
          sd.Format("%d", m_lstAsiakkaat.GetItemData(s));            // WorkPlace.id
          asiakkaat.push_back(sd);
          m_lstAsiakkaat.GetText(s, ed);                             // WorkPlace.Name
          asiakkaat.push_back(ed);
          vect = db.haeTaulusta("WorkPlace", "CustomerNumber, Region_id", 2, "", 1, "", "id", "=", sd);
          asiakkaat.push_back(vect[0]);                              // WorkPlace.CustomerNumber
          asiakkaat.push_back(vect[1]);                              // WorkPlace.Region_id
		}
	  }
	}

    if((e = m_lstTyotyypit.GetCount()) != LB_ERR)    // Haetaan valitut työtyyppien id:t vektoriin
	{
      for(s=0; s<e; s++)
	  {
        if(m_lstTyotyypit.GetSel(s) > 0)
		{
          sd.Format("%d", m_lstTyotyypit.GetItemData(s));
          tyotyypit.push_back(sd);
		}
	  }
	}

    if((e = m_lstTyontekijat.GetCount()) != LB_ERR)  // Haetaan valitut työntekijöiden nimet vektoriin
	{
      for(s=0; s<e; s++)
	  {
        if(m_lstTyontekijat.GetSel(s) > 0)
		{
          sd.Format("%d", m_lstTyontekijat.GetItemData(s));
          tyontekijat.push_back(sd);
		}
	  }
	}

    m_dtpAlkaen.GetTime(codt);                       // Aloitus ja lopetus päivät
    s = paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay());
    m_dtpPaattyen.GetTime(codt);
    e = paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay());
    if(s > e)                                        // varmista että  pienempi päiväys on ensin
	{ t = s; s = e; e = t; }
    sd.Format("%d", s);
    ed.Format("%d", e);

    if((cs = Props::i().get(OPTIONS_AIKAJARJESTYS_R).c_str()) == "") cs = ASCENT_S; // ORDER BY ...

    // Suodatetaan WorkUnit-taulusta annettujen tietojen mukaiset rivit
	tapahtumat = db.suodataWorkUnit(asiakkaat, tyotyypit, tyontekijat, sd, ed, m_laskutus, m_nayta, cs);

    //nayta = 0;
    time = 0;                                        // lasketaan samalla kokonaisaika (vain _UNIT_MIN_-yksiköt)
    for(i=0, j=asiakkaat.size(); i<j; i += 4)        // Lisätään asiakkaiden tiedot asiakasryhmittäin
	{
      vect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", asiakkaat[i + 3]);

      for(e=0, s=tapahtumat.size(); e<s; e += WORKUNIT_COLS)
	  {
        if(asiakkaat[i] == tapahtumat[e + 2])            // tapahtumat-lista ei ole kohteiden mukaisessa järjestyksessä välttämättä, asiakkaat lista on -> asiakkaat listan mukaan
		{
          /*if(nayta == 0)                                 // #1. Työaikojen/Myyntien peräkkäin näyttö, eli hypätään yli työtyypit joita ei käsitellä (ks. kohta #2)
		  {
            if(m_nayta == TM_BOTH && tapahtumat[e + 17] == ID_SALESUNIT) continue;
            if(m_nayta == MT_BOTH && tapahtumat[e + 17] == ID_WORKUNIT) continue;
		  }
          else if(nayta == 1)
		  {
            if(m_nayta == TM_BOTH && tapahtumat[e + 17] == ID_WORKUNIT) continue;
            if(m_nayta == MT_BOTH && tapahtumat[e + 17] == ID_SALESUNIT) continue;
		  }*/

          pid = new ItemData;                            // tunnistetiedot jokaiselle listan riville (helppo muokata yms.)
          pid->id = tapahtumat[e];
          pid->Worker_id = tapahtumat[e + 1];
          pid->WorkPlace_id = tapahtumat[e + 2];
          pid->WorkType_id = tapahtumat[e + 3];
          pid->StartDate = tapahtumat[e + 4];
          pid->StartTime = tapahtumat[e + 5];
          pid->EndDate = tapahtumat[e + 6];
          pid->EndTime = tapahtumat[e + 7];
          pid->Unit = tapahtumat[e + 8];
          pid->UnitValue = tapahtumat[e + 9];
          pid->Charged = tapahtumat[e + 10];
          pid->UnitPrice = tapahtumat[e + 11];
          pid->TotalPrice = tapahtumat[e + 12];
          pid->Alv = tapahtumat[e + 13];
          pid->ReportName = tapahtumat[e + 14];
          pid->ReportDate = tapahtumat[e + 15];
          pid->Biller_id = tapahtumat[e + 16];
          pid->Type = tapahtumat[e + 17];

          wt_vect = db.haeTaulusta("WorkType", "Name, ProductNumber", 2, "", 1, "", "id", "=", pid->WorkType_id);
          wo_vect = db.haeTaulusta("Worker", "Name", 1, "", 1, "", "id", "=", pid->Worker_id);

          t = m_plstRaportit->GetItemCount();                                      
          sel = m_plstRaportit->InsertItem(LVIF_TEXT|LVIF_STATE, t, "", 0, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
          sd = vect[0] + SEPARATOR + asiakkaat[i + 1] + SEPARATOR + asiakkaat[i + 2];	// Region - Name - CustomerNumber
          m_plstRaportit->SetItem(sel, 1, LVIF_TEXT, sd, 0, 0, 0, 0);
          sd = wt_vect[0] + SEPARATOR + wt_vect[1];                              // WorkType.Name - ProductNumber
          m_plstRaportit->SetItem(sel, 2, LVIF_TEXT, sd, 0, 0, 0, 0);
          m_plstRaportit->SetItem(sel, 3, LVIF_TEXT, wo_vect[0], 0, 0, 0, 0);    // WorkerName
          ivect = paivays.date2int(pid->StartDate);                              // StartDate, StartTime
          sd.Format("%d%s%d%s%d", ivect[0], DATE_SEP, ivect[1], DATE_SEP, ivect[2]);
          sd += DATETIME_IB + paivays.time2string(pid->StartTime);
          m_plstRaportit->SetItem(sel, 4, LVIF_TEXT, sd, 0, 0, 0, 0);
          ivect = paivays.date2int(pid->EndDate);                                // EndDate, EndTime
          sd.Format("%d%s%d%s%d", ivect[0], DATE_SEP, ivect[1], DATE_SEP, ivect[2]);
          sd += DATETIME_IB + paivays.time2string(pid->EndTime);
          m_plstRaportit->SetItem(sel, 5, LVIF_TEXT, sd, 0, 0, 0, 0);
          if(pid->Unit == _UNIT_MIN_)                                            // UnitValue, Unit - tunteina/minuutteina, ajat käsitellään erityistapauksena (työaikaohjelma :-))
		  {
			cnv = atof(pid->UnitValue);
            if(m_ajat == TIME_MINUTES || m_ajat == TIME_HOURS) time += cnv;		 // ajat
            else time++;                                                         // käyntikerrat

			if(m_ajat == TIME_MINUTES)
			{ sd.Format("%.0f", cnv); ed = _UNIT_MIN_; }
            else if(m_ajat == TIME_HOURS)                                             // muunnetaan tunneiksi tarvittaessa
			{ sd.Format("%.2f", cnv / 60.0f); ed = _UNIT_HOUR_; }
            else if(m_ajat == TIME_CALLS)
			{ sd = "1"; ed = Props::i().lang("_UNIT_CALL_"); }
		  }
		  else
		  {
			sd = db.fixFloat(pid->UnitValue, TRUE);
			ed = pid->Unit;
		  }
          m_plstRaportit->SetItem(sel, 6, LVIF_TEXT, sd, 0, 0, 0, 0);  
          m_plstRaportit->SetItem(sel, 7, LVIF_TEXT, ed, 0, 0, 0, 0);
          if(pid->Type == ID_SALESUNIT)
		  {
	          m_plstRaportit->SetItem(sel, 8, LVIF_TEXT, db.fixFloat(pid->UnitPrice, TRUE), 0, 0, 0, 0);	// UnitPrice
		      m_plstRaportit->SetItem(sel, 9, LVIF_TEXT, db.fixFloat(pid->TotalPrice, TRUE), 0, 0, 0, 0);	// TotalPrice
			  m_plstRaportit->SetItem(sel, 10, LVIF_TEXT, db.fixFloat(pid->Alv, TRUE), 0, 0, 0, 0);		// Alv
		  }
          m_plstRaportit->SetItemData(sel, (DWORD)pid);							// talletetaan struktuuri
          if(pid->Type == ID_WORKUNIT)											// Aseta ikoni tyypin mukaan
			m_plstRaportit->SetItem(sel, 0, LVIF_IMAGE, 0, 0, 0, 0, 0);
          else if(pid->Type == ID_SALESUNIT)
            m_plstRaportit->SetItem(sel, 0, LVIF_IMAGE, 0, 1, 0, 0, 0);
		}
	  }

      /*// #2. Koska ID_WORKUNIT- ja ID_SALESUNIT-tapahtumat näytetään peräkkäin (ei sekaisin) täytyy %%_BOTH-tiloissa listat käydä läpi kahdesti!!!
      if(m_nayta == TM_BOTH && (i + 4) == j && nayta == 0) { i = -4; nayta = 1; }
      if(m_nayta == MT_BOTH && (i + 4) == j && nayta == 0) { i = -4; nayta = 1; }*/
	}

    if(j == 0 || m_nayta == ID_SALESUNIT) sd = "";   // Asetetaan kokonaisaika näkyville
    else 
	{
      if(m_ajat == TIME_MINUTES)
        sd.Format("%.0f %s", time, time == 1 ? Props::i().lang("PPAGERAPORTIT_14") : Props::i().lang("PPAGERAPORTIT_15"));
      else if(m_ajat == TIME_HOURS)
        sd.Format("%.2f %s", time / 60.0f, Props::i().lang("PPAGERAPORTIT_16"));
      else if(m_ajat == TIME_CALLS)
        sd.Format("%.0f %s", time, time == 1 ? Props::i().lang("PPAGERAPORTIT_17") : Props::i().lang("PPAGERAPORTIT_18"));
	}
    m_stcAjat.SetWindowText(sd);

    if(old_pid)                                      // Yritetään valita rivi jolla on annetun old_pid:n tiedot
	{
      for(t=0, s = m_plstRaportit->GetItemCount(); t<s; t++)
	  {
        pid = (ItemData*)m_plstRaportit->GetItemData(t);
        if(pid_id == pid->id) break;
	  }

      if(t != s)
	  {
        m_plstRaportit->EnsureVisible(t, FALSE);
        m_plstRaportit->SetItemState(t, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
        //m_plstRaportit->SetSelectionMark(t);
	  }
	}
}

void PpageRaportit::OnChkasiakasryhmat() 
{
    if(m_chkAsiakasryhmat.GetCheck())        // Kaikki valituiksi
      m_lstAsiakasryhmat.SelItemRange(TRUE, 0, m_lstAsiakasryhmat.GetCount());
    else                                     // ja kaikki valitsemattomiksi
      m_lstAsiakasryhmat.SelItemRange(FALSE, 0, m_lstAsiakasryhmat.GetCount());

	OnSelchangeLstasiakasryhma(TRUE, TRUE);  // haetaan asiakkaat
}

void PpageRaportit::OnChkasiakkaat() 
{
    if(m_chkAsiakkaat.GetCheck())        // Kaikki valituiksi
      m_lstAsiakkaat.SelItemRange(TRUE, 0, m_lstAsiakkaat.GetCount());
    else                                   // ja kaikki valitsemattomiksi
      m_lstAsiakkaat.SelItemRange(FALSE, 0, m_lstAsiakkaat.GetCount());

	uusiHaku(NULL);
}

void PpageRaportit::OnChktyotyypit() 
{
    if(m_chkTyotyypit.GetCheck())        // Kaikki valituiksi
      m_lstTyotyypit.SelItemRange(TRUE, 0, m_lstTyotyypit.GetCount());
    else                                   // ja kaikki valitsemattomiksi
      m_lstTyotyypit.SelItemRange(FALSE, 0, m_lstTyotyypit.GetCount());

	uusiHaku(NULL);
}

void PpageRaportit::OnChktyontekijat() 
{
    if(m_chkTyontekijat.GetCheck())        // Kaikki valituiksi
      m_lstTyontekijat.SelItemRange(TRUE, 0, m_lstTyontekijat.GetCount());
    else                                   // ja kaikki valitsemattomiksi
      m_lstTyontekijat.SelItemRange(FALSE, 0, m_lstTyontekijat.GetCount());

	uusiHaku(NULL);
}

void PpageRaportit::OnSelchangeLstasiakasryhma() 
{
    m_chkAsiakasryhmat.SetCheck(0);
    OnSelchangeLstasiakasryhma(TRUE, TRUE);
}
void PpageRaportit::OnSelchangeLstasiakasryhma(BOOL sel, BOOL haku)
{
    int e, s, c, l, i;
    CString cs;
    DbSqlite db;
    vector <CString> vect;

    m_lstAsiakkaat.ResetContent();                   // Tutkitaan mitkä on valittu Asiakasryhmälistassa ja sen perusteella valitaan Asiakkaat-listaan nimet
    if((e = m_lstAsiakasryhmat.GetCount()) != LB_ERR)
	{
      for(s=0; s<e; s++)
	  {
        if(m_lstAsiakasryhmat.GetSel(s) > 0)
		{
          cs.Format("%d", m_lstAsiakasryhmat.GetItemData(s));

          vect = db.haeTaulusta("WorkPlace", "Name, id", 2, "position", 1, "", "Region_id", "=", cs);
          for(c=0, l=vect.size(); c < l; c+=2)
		  {
            i = m_lstAsiakkaat.AddString(vect[c]);
            if(sel) m_lstAsiakkaat.SetSel(i, TRUE);
            if(i != LB_ERR && i != LB_ERRSPACE)          // ItemDataan kohteen id!!!
              m_lstAsiakkaat.SetItemData(i, atoi(vect[c + 1]));
		  }
		}
	  }
	}
                                                         // Asiakasryhmä-Checkbox valituksi, jos kaikki valittu
    if(m_lstAsiakasryhmat.GetCount() == m_lstAsiakasryhmat.GetSelCount())
      m_chkAsiakasryhmat.SetCheck(1);
    else
      m_chkAsiakasryhmat.SetCheck(0);

    if(m_lstAsiakasryhmat.GetSelCount() > 0 && sel)      // Asiakkaista-Checkbox valituksi, jos yksikin valittu ryhmästä ja asiakkaat on valittu
      m_chkAsiakkaat.SetCheck(1);
    else
      m_chkAsiakkaat.SetCheck(0);

	if(haku) uusiHaku(NULL);
}

void PpageRaportit::OnSelchangeLstasiakas() 
{                                                        // Checkbox valituksi, jos kaikki valittu
    if(m_lstAsiakkaat.GetCount() == m_lstAsiakkaat.GetSelCount())
      m_chkAsiakkaat.SetCheck(1);
    else
      m_chkAsiakkaat.SetCheck(0);

	uusiHaku(NULL);
}

void PpageRaportit::OnSelchangeLsttyotyyppi() 
{
    uusiHaku(NULL);

    // Checkbox päälle, jos kaikki valittu
    if(m_lstTyotyypit.GetCount() == m_lstTyotyypit.GetSelCount()) m_chkTyotyypit.SetCheck(1);
    else m_chkTyotyypit.SetCheck(0);
}

void PpageRaportit::OnSelchangeLsttyontekija() 
{
    uusiHaku(NULL);

    // Checkbox päälle, jos kaikki valittu
    if(m_lstTyontekijat.GetCount() == m_lstTyontekijat.GetSelCount()) m_chkTyontekijat.SetCheck(1);
    else m_chkTyontekijat.SetCheck(0);
}

void PpageRaportit::OnItemchangedLstraportti(NMHDR* pNMHDR, LRESULT* pResult) 
{ // Näytä valittujen työajat minutteina, tunteina tai käyntikertoina
    int s;
    CString cs;
    float time;
    POSITION pos;
    ItemData *pid;
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    time = 0.0f;
    pos = m_plstRaportit->GetFirstSelectedItemPosition();                  // Käydään valitut läpi
    while(pos)
    {
      s = m_plstRaportit->GetNextSelectedItem(pos);
      if(m_plstRaportit->GetItemState(s, LVIS_SELECTED) == LVIS_SELECTED)  // Lasketaan valittujen työajat yhteen
	  {
        if(!(pid = (ItemData*)m_plstRaportit->GetItemData(s))) continue;
        if(pid->Type == ID_WORKUNIT) 
		{ // Ajat vs. käyntikerrat
          if(m_ajat == TIME_MINUTES || m_ajat == TIME_HOURS) time += atof(pid->UnitValue);
          else time++;
		}
	  }
	}

    if(time > 0.0f)
	{
      if(m_ajat == TIME_MINUTES)
        cs.Format("%.0f %s", time, time == 1 ? Props::i().lang("PPAGERAPORTIT_14") : Props::i().lang("PPAGERAPORTIT_15"));
      else if(m_ajat == TIME_HOURS)
        cs.Format("%.2f %s", time / 60.0f, Props::i().lang("PPAGERAPORTIT_16"));
      else if(m_ajat == TIME_CALLS)
        cs.Format("%.0f %s", time, time == 1 ? Props::i().lang("PPAGERAPORTIT_17") : Props::i().lang("PPAGERAPORTIT_18"));
	}
    m_stcValitut.SetWindowText(cs);

    *pResult = 0;
}

void PpageRaportit::OnSelchangeCmbaika() 
{
    int s;

    if((s = m_cmbAika.GetCurSel()) == CB_ERR) return;

    if(s == 0) m_ajat = TIME_MINUTES;                // Ajan näyttötapa muuttui -> talleta asetuksiin, päivitä laskuri
    else if(s == 1) m_ajat = TIME_HOURS;
    else if(s == 2) m_ajat = TIME_CALLS;

	Props::i().set(OPTIONS_AJAT, StringHelper::itoa(m_ajat, 10));

    uusiHaku(NULL);                                  // Päivitä näyttö
}

void PpageRaportit::OnDatetimechangeDtpalkaen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    COleDateTime odt;

    m_dtpAlkaen.GetTime(odt);                        // Hae asetettu aika ja talleta asetuksiin
    Props::i().set(OPTIONS_ALKAEN_VIIMEISIN_R, (LPCSTR)odt.Format(LOCALE_NOUSEROVERRIDE, LOCALE_SYSTEM_DEFAULT));
    uusiHaku(NULL);

    *pResult = 0;
}

void PpageRaportit::OnDatetimechangeDtppaattyen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    COleDateTime odt;

    m_dtpPaattyen.GetTime(odt);                      // Hae asetettu aika ja talleta asetuksiin
    Props::i().set(OPTIONS_PAATTYEN_VIIMEISIN_R, (LPCSTR)odt.Format(LOCALE_NOUSEROVERRIDE, LOCALE_SYSTEM_DEFAULT));
    uusiHaku(NULL);

    *pResult = 0;
}

void PpageRaportit::OnBtnetsi() 
{ etsi(KEY_CTRLF); }

void PpageRaportit::OnBtnalkaen() 
{
    RECT rect;
    CString cs;
    CMenu menu, *pPopup;

    cs = Props::i().get(OPTIONS_ALKAEN_R).c_str();

    VERIFY(menu.LoadMenu(IDR_ALKAEN));                               // Tee menu
    pPopup = menu.GetSubMenu(0);

	pPopup->ModifyMenu(IDM_PU_VIIMEKSI_ASETETTU, MF_BYCOMMAND|MF_STRING, IDM_PU_VIIMEKSI_ASETETTU, Props::i().lang("IDR_ALKAEN_1"));
	pPopup->ModifyMenu(IDM_PU_VANHIN_TYO, MF_BYCOMMAND|MF_STRING, IDM_PU_VANHIN_TYO, Props::i().lang("IDR_ALKAEN_2"));
	pPopup->ModifyMenu(IDM_PU_NYKYINEN_PVM, MF_BYCOMMAND|MF_STRING, IDM_PU_NYKYINEN_PVM, Props::i().lang("IDR_ALKAEN_3"));
	pPopup->ModifyMenu(IDM_PU_NYKYINEN_M1, MF_BYCOMMAND|MF_STRING, IDM_PU_NYKYINEN_M1, Props::i().lang("IDR_ALKAEN_4"));
	pPopup->ModifyMenu(IDM_PU_NYKYINEN_M2, MF_BYCOMMAND|MF_STRING, IDM_PU_NYKYINEN_M2, Props::i().lang("IDR_ALKAEN_5"));
	pPopup->ModifyMenu(IDM_PU_NYKYINEN_M3, MF_BYCOMMAND|MF_STRING, IDM_PU_NYKYINEN_M3, Props::i().lang("IDR_ALKAEN_6"));

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
    Props::i().set(OPTIONS_ALKAEN_R, (LPCSTR)cs);

    paivitaPaivays(0, "", NULL, TRUE);                               // Päivitä ohjaimet
}

void PpageRaportit::OnBtnpaattyen() 
{
    RECT rect;
    CString cs;
    CMenu menu, *pPopup;

    cs = Props::i().get(OPTIONS_PAATTYEN_R).c_str();

    VERIFY(menu.LoadMenu(IDR_PAATTYEN));                               // Tee menu
    pPopup = menu.GetSubMenu(0);

	pPopup->ModifyMenu(IDM_PU_VIIMEKSI_ASETETTU, MF_BYCOMMAND|MF_STRING, IDM_PU_VIIMEKSI_ASETETTU, Props::i().lang("IDR_PAATTYEN_1"));
	pPopup->ModifyMenu(IDM_PU_UUSIN_TYO, MF_BYCOMMAND|MF_STRING, IDM_PU_UUSIN_TYO, Props::i().lang("IDR_PAATTYEN_2"));
	pPopup->ModifyMenu(IDM_PU_NYKYINEN_PVM, MF_BYCOMMAND|MF_STRING, IDM_PU_NYKYINEN_PVM, Props::i().lang("IDR_PAATTYEN_3"));

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
    Props::i().set(OPTIONS_PAATTYEN_R, (LPCSTR)cs);

    paivitaPaivays(0, "", NULL, TRUE);                               // Päivitä ohjaimet
}

void PpageRaportit::OnRdlaskutus() 
{
    int s = GetCheckedRadioButton(IDC_RDLASKUTUS1, IDC_RDLASKUTUS3);

    if(s == IDC_RDLASKUTUS1) m_laskutus = CHARGED;
    else if(s == IDC_RDLASKUTUS2) m_laskutus = UNCHARGED;
    else if(s == IDC_RDLASKUTUS3) m_laskutus = ALLREPORTS;

    CheckRadioButton(IDC_RDLASKUTUS1, IDC_RDLASKUTUS3, s);

	uusiHaku(NULL);
}

void PpageRaportit::OnBtnlisaauusi() 
{ lisaaTapahtuma(0); }

void PpageRaportit::OnBtnpoistavalitut() 
{ poistaItems(); }

void PpageRaportit::OnBtnlaskuta() 
{
    int flags;
    RECT rect;
    CString cs;
    CMenu menu, *pPopup;

    VERIFY(menu.LoadMenu(IDR_LASKUTA));                              // Tee menu
    pPopup = menu.GetSubMenu(0);

	pPopup->ModifyMenu(IDM_NAYTETYT, MF_BYCOMMAND|MF_STRING, IDM_NAYTETYT, Props::i().lang("IDR_LASKUTA_1"));
	pPopup->ModifyMenu(IDM_VALITUT, MF_BYCOMMAND|MF_STRING, IDM_VALITUT, Props::i().lang("IDR_LASKUTA_2"));
	pPopup->ModifyMenu(IDM_ASIAKKAAT, MF_BYCOMMAND|MF_STRING, IDM_ASIAKKAAT, Props::i().lang("IDR_LASKUTA_3"));

    if(m_plstRaportit->GetItemCount() > 0) flags = MF_ENABLED;       // Enabloi sopivat menu itemit
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_NAYTETYT, MF_BYCOMMAND|flags);
    if(m_plstRaportit->GetSelectedCount() > 0) flags = MF_ENABLED;   //
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_VALITUT, MF_BYCOMMAND|flags);
    if(m_lstAsiakkaat.GetSelCount() > 0) flags = MF_ENABLED;         //
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_ASIAKKAAT, MF_BYCOMMAND|flags);

    m_btnLaskuta.GetWindowRect(&rect);                               // Näytä popup menu
    int r = pPopup->TrackPopupMenu(TPM_RETURNCMD|TPM_BOTTOMALIGN|TPM_RIGHTBUTTON, rect.left, rect.top, this);

    if(r == 0) return;
    if(r == IDM_NAYTETYT) laskutaKaikkiNaytetyt();
    else if(r == IDM_VALITUT) laskutaValitut();
    else if(r == IDM_ASIAKKAAT) laskutaAsiakas();
}

void PpageRaportit::OnBtnerittely() 
{
    int flags;
    RECT rect;
    CString cs;
    CMenu menu, *pPopup;

    VERIFY(menu.LoadMenu(IDR_ERITTELY));                             // Tee menu
    pPopup = menu.GetSubMenu(0);

	pPopup->ModifyMenu(IDM_NAYTETYT_TYOT, MF_BYCOMMAND|MF_STRING, IDM_NAYTETYT_TYOT, Props::i().lang("IDR_ERITTELY_1"));
	pPopup->ModifyMenu(IDM_VALITUT_TYOT, MF_BYCOMMAND|MF_STRING, IDM_VALITUT_TYOT, Props::i().lang("IDR_ERITTELY_2"));
	pPopup->ModifyMenu(IDM_VALITUT_ASIAKAS_TYOT, MF_BYCOMMAND|MF_STRING, IDM_VALITUT_ASIAKAS_TYOT, Props::i().lang("IDR_ERITTELY_3"));
	pPopup->ModifyMenu(IDM_NAYTETYT_TYOAJAT, MF_BYCOMMAND|MF_STRING, IDM_NAYTETYT_TYOAJAT, Props::i().lang("IDR_ERITTELY_4"));
	pPopup->ModifyMenu(IDM_VALITUT_TYOAJAT, MF_BYCOMMAND|MF_STRING, IDM_VALITUT_TYOAJAT, Props::i().lang("IDR_ERITTELY_5"));
	pPopup->ModifyMenu(IDM_VALITUT_TYONTEKIJA_TYOAJAT, MF_BYCOMMAND|MF_STRING, IDM_VALITUT_TYONTEKIJA_TYOAJAT, Props::i().lang("IDR_ERITTELY_6"));

    if(m_plstRaportit->GetItemCount() > 0) flags = MF_ENABLED;       // Enabloi sopivat menu itemit
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_NAYTETYT_TYOT, MF_BYCOMMAND|flags);
    pPopup->EnableMenuItem(IDM_NAYTETYT_TYOAJAT, MF_BYCOMMAND|flags);

    if(m_plstRaportit->GetSelectedCount() > 0) flags = MF_ENABLED;   //
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_VALITUT_TYOT, MF_BYCOMMAND|flags);
    pPopup->EnableMenuItem(IDM_VALITUT_TYOAJAT, MF_BYCOMMAND|flags);

    if(m_lstAsiakkaat.GetSelCount() > 0) flags = MF_ENABLED;         //
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_VALITUT_ASIAKAS_TYOT, MF_BYCOMMAND|flags);
    if(m_lstTyontekijat.GetSelCount() > 0) flags = MF_ENABLED;       //
    else flags = MF_GRAYED|MF_DISABLED;
    pPopup->EnableMenuItem(IDM_VALITUT_TYONTEKIJA_TYOAJAT, MF_BYCOMMAND|flags);

    m_btnErittely.GetWindowRect(&rect);                              // Näytä popup menu
    int r = pPopup->TrackPopupMenu(TPM_RETURNCMD|TPM_BOTTOMALIGN|TPM_RIGHTBUTTON, rect.left, rect.top, this);

    if(r == 0) return;
    if(r == IDM_NAYTETYT_TYOT) eritteleNaytetytTyot();
    else if(r == IDM_VALITUT_TYOT) eritteleValitutTyot();
    else if(r == IDM_VALITUT_ASIAKAS_TYOT) eritteleValitutAsiakasTyot();
    else if(r == IDM_NAYTETYT_TYOAJAT) eritteleNaytetytTyoajat();
    else if(r == IDM_VALITUT_TYOAJAT) eritteleValitutTyoajat();
    else if(r == IDM_VALITUT_TYONTEKIJA_TYOAJAT) eritteleValitutTyontekijaTyoajat();
}

void PpageRaportit::OnBtnvalmore() 
{
    RECT rect;
    DlgInfo dlg;

    m_btnValMore.GetWindowRect(&rect);
    dlg.m_dlgXPos = rect.left + (rect.right - rect.left);
    dlg.m_dlgYPos = rect.top;
    dlg.m_mode = MODE_VALITUT;
    dlg.m_time_mode = m_ajat;
    dlg.m_pCListCtrl = (CListCtrl*)m_plstRaportit;
    dlg.m_caption = Props::i().lang("PPAGERAPORTIT_19");

    dlg.DoModal();
}

void PpageRaportit::OnBtnyhtmore() 
{
    RECT rect;
    DlgInfo dlg;

    m_btnYhtMore.GetWindowRect(&rect);
    dlg.m_dlgXPos = rect.left + (rect.right - rect.left);
    dlg.m_dlgYPos = rect.top;
    dlg.m_mode = MODE_KAIKKINAYTETYT;
    dlg.m_time_mode = m_ajat;
    dlg.m_pCListCtrl = (CListCtrl*)m_plstRaportit;
    dlg.m_caption = Props::i().lang("PPAGERAPORTIT_20");

    dlg.DoModal();
}

void PpageRaportit::paivitaAARListat(CString workplace_id, ItemData *pid, BOOL haku)
{
    DbSqlite db;
    int i, f, s;
    CString region, name, asiakas, asiakasryhma;
    vector <CString> rvect;
	vector <DWORD> avect, rvect_t;

    if(workplace_id != "")                           // Haetaan asiakkaan nimi ja ryhmä id:n perusteella
	{
      if((rvect = db.haeTaulusta("WorkPlace", "Name, Region_id", 2, "", 1, "", "id", "=", workplace_id)).size() > 0)
	  {
        asiakas = rvect[0];
        if((rvect = db.haeTaulusta("Region", "Name", 1, "", 1, "", "id", "=", rvect[1])).size() > 0)
	      asiakasryhma = rvect[0];
	  }
	}

    // LISÄTÄÄN TIETOKANTAAN LISÄTYT ASIAKASRYHMÄT/ASIAKKAAT LISTOIHINSA JA POISTETAAN TIETOKANNASTA POISTETUT ASIAKASRYHMÄT/ASIAKKAAT LISTOISTAAN
    m_haku = FALSE;                                  // Estetään haku toistaiseksi (uusiHaku()-funktio)

    rvect_t.clear();                                 // Valitut asiakasryhmät muistiin
    for(i=0, s = m_lstAsiakasryhmat.GetCount(); i<s; i++)
	{ if(m_lstAsiakasryhmat.GetSel(i) > 0) rvect_t.push_back(m_lstAsiakasryhmat.GetItemData(i)); }
    avect.clear();                                   // Valitut asiakkaat muistiin
    for(i=0, s = m_lstAsiakkaat.GetCount(); i<s; i++)
	{ if(m_lstAsiakkaat.GetSel(i) > 0) avect.push_back(m_lstAsiakkaat.GetItemData(i)); }
    m_lstAsiakasryhmat.ResetContent();               // Tyhjennetään listat
    m_lstAsiakkaat.ResetContent();
	                                                 // Asiakasryhmät asiakasryhmälistaan tietokannasta
    s = (rvect = db.haeTaulusta("Region", "Name, id", 2, "position", 0)).size();
    for(i=0; i<s; i+=2)
	{
      f = m_lstAsiakasryhmat.AddString(rvect[i]);
      if(f != LB_ERR && f != LB_ERRSPACE)              // ItemDataan regionin id!!!
        m_lstAsiakasryhmat.SetItemData(f, atoi(rvect[i + 1]));
	}
    for(i=0, s = rvect_t.size(); i<s; i++)           // Merkitään valituiksi talteen otettujen nimien perusteella
	  palautaValitut(rvect_t[i], &m_lstAsiakasryhmat);
    if((f = m_lstAsiakasryhmat.FindStringExact(-1, asiakasryhma)) != LB_ERR)
      m_lstAsiakasryhmat.SetSel(f, TRUE);            // +++ annettu asiakasryhmä valituksi
    if(m_lstAsiakasryhmat.GetSelCount() == 0)        // +++ jos ei valittuja, valitse ensimmäinen ar-listasta
      m_lstAsiakasryhmat.SetSel(0, TRUE);

    OnSelchangeLstasiakasryhma(FALSE, TRUE);         // Lisätään asiakkaat asiakaslistaan (valittujen asiakasryhmien perusteella)
    for(i=0, s = avect.size(); i<s; i++)             // Yritetään valita ne asiakkaat jotka oli valittuna ennen tyhjennystä
	  palautaValitut(avect[i], &m_lstAsiakkaat);
    if((f = m_lstAsiakkaat.FindStringExact(-1, asiakas)) != LB_ERR)
      m_lstAsiakkaat.SetSel(f, TRUE);                // +++ annettu asiakas valituksi

    m_haku = TRUE;                                   // mahdollista haku
    if(haku) uusiHaku(pid);
}

void PpageRaportit::paivitaTyontekijat(CString tyontekija, ItemData *pid, BOOL haku)
{
    CString cs;
    DbSqlite db;
    int i, f, s;
    vector <CString> vect;
	vector <DWORD> rvect_t;

    for(i=0, s = m_lstTyontekijat.GetCount(); i<s; i++) // Valitut työntekijät muistiin
    { if(m_lstTyontekijat.GetSel(i) > 0) rvect_t.push_back(m_lstTyontekijat.GetItemData(i)); }

    m_lstTyontekijat.ResetContent();               // Tyhjennetään lista

    s = (vect = db.haeTaulusta("Worker", "DISTINCT Name, id", 2, "Name", 0)).size();
    for(i=0; i<s; i+=2)                            // työntekijät listaansa
	{
      f = m_lstTyontekijat.AddString(vect[i]);
      if(f != LB_ERR && f != LB_ERRSPACE)            // ItemDataan työtyypin id!!!
        m_lstTyontekijat.SetItemData(f, atoi(vect[i + 1]));
	}

    for(i=0, s = rvect_t.size(); i<s; i++)         // Merkitään valituiksi talteen otettujen nimien perusteella
      palautaValitut(rvect_t[i], &m_lstTyontekijat);

                                                   // Yritetään valita ja scrollata näkyville annettu työntekijänimi
    f = m_lstTyontekijat.FindStringExact(-1, tyontekija);
    if(f != LB_ERR) { m_lstTyontekijat.SetSel(f, TRUE); m_lstTyontekijat.SetCaretIndex(f, TRUE); }

                                                     // Checkbox oikeaan tilaan
    if(m_lstTyontekijat.GetSelCount() == m_lstTyontekijat.GetCount()) m_chkTyontekijat.SetCheck(1);
    else m_chkTyontekijat.SetCheck(0);

    if(haku) uusiHaku(pid);
}

void PpageRaportit::paivitaTyotyyppi(CString tyotyyppi, ItemData *pid, BOOL haku)
{
    CString cs;
    DbSqlite db;
    int i, f, s;
    vector <CString> vect;
	vector <DWORD> rvect_t;

    for(i=0, s = m_lstTyotyypit.GetCount(); i<s; i++) // Valitut työtyypit muistiin
	{ if(m_lstTyotyypit.GetSel(i) > 0) rvect_t.push_back(m_lstTyotyypit.GetItemData(i)); }

    m_lstTyotyypit.ResetContent();                   // Tyhjennetään lista

    if(m_nayta == ID_WORKUNIT)                       // Hae kaikki työtyypit tai tuotteet
      s = (vect = db.haeTaulusta("WorkType", "Name, id", 2, WORKTYPE_POSITION_WORK, 1, "", "Type", "=", WORK)).size();
    else
      s = (vect = db.haeTaulusta("WorkType", "Name, id", 2, WORKTYPE_POSITION_PRODUCT, 1, "", "Type", "=", PRODUCT)).size();

    for(i=0; i<s; i+=2)                              // lisää haetut työtyypit/tuotteet listaansa
	{
      f = m_lstTyotyypit.AddString(vect[i]);
      if(f != LB_ERR && f != LB_ERRSPACE)                // ItemDataan työtyypin/tuotteen id!!!
        m_lstTyotyypit.SetItemData(f, atoi(vect[i + 1]));
	}

    for(i=0, s = rvect_t.size(); i<s; i++)           // Merkitään valituiksi talteen otettujen nimien perusteella
      palautaValitut(rvect_t[i], &m_lstTyotyypit);

                                                     // Yritetään valita ja scrollata näkyville annettu työtyypin nimi
    f = m_lstTyotyypit.FindStringExact(-1, tyotyyppi);
    if(f != LB_ERR) { m_lstTyotyypit.SetSel(f, TRUE); m_lstTyotyypit.SetCaretIndex(f, TRUE); }

                                                     // Checkbox oikeaan tilaan
    if(m_lstTyotyypit.GetSelCount() == m_lstTyotyypit.GetCount()) m_chkTyotyypit.SetCheck(1);
    else m_chkTyotyypit.SetCheck(0);

    if(haku) uusiHaku(pid);
}

void PpageRaportit::paivitaPaivays(int type, CString date, ItemData *pid, BOOL haku)
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
        if(d2 < d1) d1 = d2;                             // annettu päivä pienenmpi kuin nykyinen, päivitä alkaen
        m_dtpAlkaen.SetTime(d1);
	  }
      if(type == UPDATE_END)
	  {
        m_dtpPaattyen.GetTime(d1);
        d2.SetDate(i>>10, (i>>5)&0x1F, i&0x1F);
        if(d2 > d1) d1 = d2;                             // annettu päivä suurempi kuin nykyinen, päivitä ppäättyen
        m_dtpPaattyen.SetTime(d1);
	  }
	}
    else                                             // Asetuksista
	{
      cs = Props::i().get(OPTIONS_ALKAEN_R).c_str();   // ALKAEN / - / - / - / - / - / - / - / - / - 
      if(cs == DATE_VIIMEKSI_ASETETTU)
	  {
        cs = Props::i().get(OPTIONS_ALKAEN_VIIMEISIN_R).c_str();
        if(cs != "") d1.ParseDateTime(cs, LOCALE_NOUSEROVERRIDE , LOCALE_SYSTEM_DEFAULT);
        else d1 = d1.GetCurrentTime();
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
        if((i = (ivect = paivays.jarjestaPaivat("WorkUnit", "StartDate", ASCENT)).size()) > 0)
          d1.SetDate(ivect[0]>>10, (ivect[0]>>5)&0x1F, ivect[0]&0x1F);
        else
          d1 = d1.GetCurrentTime();
	  }
      m_dtpAlkaen.SetTime(d1);

      cs = Props::i().get(OPTIONS_PAATTYEN_R).c_str(); // PÄÄTTYEN / - / - / - / - / - / - / - / - / - 
      if(cs == DATE_VIIMEKSI_ASETETTU)
	  {
        cs = Props::i().get(OPTIONS_PAATTYEN_VIIMEISIN_R).c_str();
        if(cs != "") d1.ParseDateTime(cs, LOCALE_NOUSEROVERRIDE , LOCALE_SYSTEM_DEFAULT);
        else d1 = d1.GetCurrentTime();
	  }
      else if(cs == DATE_NYKYINEN_PVM)
	    d1 = d1.GetCurrentTime();
      else //(DATE_UUSIN_TYO)
	  {
        if((i = (ivect = paivays.jarjestaPaivat("WorkUnit", "StartDate", ASCENT)).size()) > 0)
          d1.SetDate(ivect[i - 1]>>10, (ivect[i - 1]>>5)&0x1F, ivect[i - 1]&0x1F);
        else
          d1 = d1.GetCurrentTime();
	  }
      m_dtpPaattyen.SetTime(d1);
	}

    if(haku) uusiHaku(pid);
}

void PpageRaportit::palautaValitut(DWORD id, CListBox *pCListBox)
{
	CString cs;

	for(int i=0; i<pCListBox->GetCount(); i++)
	{
		if(pCListBox->GetItemData(i) == id) pCListBox->SetSel(i, TRUE);
	}
}

void PpageRaportit::muokkaaTapahtuma(CRect cr, RECT rect, ItemData *pid, LVHITTESTINFO hti)
{
    float fval;
    CSize csize;
    DbSqlite db;
    int i, j, s, r;
    Paivays paivays;
    CString cs, cs2, cs3;
	int tabbedOut = 0;
    vector <int> ivect;
    vector <CString> r_vect;
    vector <CString> wp_vect;
    vector <CString> vect;
    vector <CString> vect2;
    pair <CString, CString> pari;
    pair <CString, CString> pari_s;
    pair <CString, CString> pari_e;
    IpeDlgEdit ipeDlgEdit;                           // Edit
    IpeDlgComboBox Ipedlgcombo;                      // Drop List
    IpeDlgComboBox2 Ipedlgcombo2;                    // Dropdown (voi kirjoittaa tekstiä)

    // NÄYTETÄÄN EDITOINTIIN SOPIVIN KONTROLLI
	try
	{
		// Muokkaa koko riviä   // // // // // // // // // // // // // // // // // // // // // //
		if(hti.iSubItem == 0)
			lisaaTapahtuma(1);
		// WorkPlace_id - CComboBox (Dropdown) // // // // // // // // // // // // // // // // //
	    else if(hti.iSubItem == 1)
		{
			if((s = (r_vect = db.haeTaulusta("Region", "id, Name", 2, "position", 0)).size()) == 0) throw(ERR_REPORTS_0);
			for(i=0; i<s; i+=2)                            // Alueittain asiakkaat vektoriin
			{
				if((r = (wp_vect = db.haeTaulusta("WorkPlace", "Region_id, Name, CustomerNumber, id", 4, "position", 1, "", "Region_id", "=", r_vect[i])).size()) == 0) continue;
				for(j=0; j<r; j++)
				{ 
					if(j % 4 == 0) wp_vect[j] = r_vect[i + 1];     // Joka neljänteen vektoriin muutetaan WorkPlace.Region_id:n tilalle Region.Name
					vect.push_back(wp_vect[j]);
				}
			}

			Ipedlgcombo.m_Ipe.x = rect.left + cr.left + 2;
			Ipedlgcombo.m_Ipe.y = rect.top + cr.top;
			Ipedlgcombo.m_Ipe.w = cr.right - cr.left + 2;
			Ipedlgcombo.m_Ipe.h = 24;
			Ipedlgcombo.m_Ipe.init(m_plstRaportit->GetItemText(hti.iItem, hti.iSubItem), NULL, &vect, 4, SEPARATOR, TRUE);
			Ipedlgcombo.DoModal();
			if(!Ipedlgcombo.m_Ipe.isEdited()) throw(ERR_REPORTS_0);               // muokattu? -> päivitä lista ja tietokanta

			cs.Format("%d", Ipedlgcombo.m_Ipe.getItemData());	// hae tiedot
			if((r = db.paivitaWorkUnit(pid, 1, WORKUNIT_WORKPLACE_ID, cs)) == RETURN_OK)
			{
				pid->WorkPlace_id = cs;
				paivitaAARListat(cs, pid, TRUE);
			}

			tabbedOut = Ipedlgcombo.m_Ipe.getTabbedOut();
		}
		// WorkType_id - CComboBox (Drop List) // // // // // // // // // // // // // // // // //
		else if(hti.iSubItem == 2)
		{
			if((vect = db.haeTaulusta("WorkType", "Name, ProductNumber, id", 3, CString(WORKTYPE_POSITION_PRODUCT) + ", " + CString(WORKTYPE_POSITION_WORK), 0)).size() == 0) throw(ERR_REPORTS_0);
			Ipedlgcombo.m_Ipe.x = rect.left + cr.left + 2;
			Ipedlgcombo.m_Ipe.y = rect.top + cr.top;
			Ipedlgcombo.m_Ipe.w = cr.right - cr.left + 2;
			Ipedlgcombo.m_Ipe.h = 24;
			Ipedlgcombo.m_Ipe.init(m_plstRaportit->GetItemText(hti.iItem, hti.iSubItem), NULL, &vect, 3, SEPARATOR, TRUE);
			Ipedlgcombo.DoModal();                             // näytetään InPlaceEdit-kontrolli
			if(!Ipedlgcombo.m_Ipe.isEdited()) throw(ERR_REPORTS_0);

			cs.Format("%d", Ipedlgcombo.m_Ipe.getItemData());// Hae tiedot
			if((r = db.paivitaWorkUnit(pid, 1, WORKUNIT_WORKTYPE_ID, cs)) == RETURN_OK)
			{
				pid->WorkType_id = cs;
				if((vect = db.haeTaulusta("WorkType", "Name", 1, "", 1, "", "id", "=", cs)).size() > 0)
				{
					int f = m_lstTyotyypit.FindStringExact(-1, vect[0]);
					if(f != LB_ERR) { m_lstTyotyypit.SetSel(f, TRUE); m_lstTyotyypit.SetCaretIndex(f, TRUE); }
					uusiHaku(pid);
				}
				else
					paivitaTyotyyppi("", pid, TRUE);
			}

			tabbedOut = Ipedlgcombo.m_Ipe.getTabbedOut();
		}
		// Worker_id - CComboBox (Drop List) // // // // // // // // // // // // // // // // // //
		else if(hti.iSubItem == 3)
		{
			if((vect = db.haeTaulusta("Worker", "DISTINCT Name", 1, "", 0)).size() == 0) throw(ERR_REPORTS_0);

			Ipedlgcombo2.m_Ipe.x = rect.left + cr.left + 2;
			Ipedlgcombo2.m_Ipe.y = rect.top + cr.top;
			Ipedlgcombo2.m_Ipe.w = cr.right - cr.left + 2;
			Ipedlgcombo2.m_Ipe.h = 24;
			Ipedlgcombo2.m_Ipe.init(m_plstRaportit->GetItemText(hti.iItem, hti.iSubItem), NULL, &vect, 1, "", FALSE);
			Ipedlgcombo2.DoModal();
			if(!Ipedlgcombo2.m_Ipe.isEdited()) throw(ERR_REPORTS_0);

			cs = Ipedlgcombo2.m_Ipe.getString();
			db.escape_c(&cs);
			db.lisaaWorker(cs, &cs2);													// lisää uusi Worker.Name jos ei löydy

			onkoTyontekijaListassa(cs, cs2);											// lisätään ListBoxiin tarvittaessa
			if((r = db.paivitaWorkUnit(pid, 1, WORKUNIT_WORKER_ID, cs2)) == RETURN_OK)	// päivitä Worker_id
			{
				pid->Worker_id = cs2;				// Päivitä suodattimet
				uusiHaku(pid);
				//paivitaTyontekijat(cs, pid, TRUE);			
			}

			tabbedOut = Ipedlgcombo2.m_Ipe.getTabbedOut();
		}
		// Unit - CComboBox (Drop List) // // // // // // // // // // // // // // // // // // // //
		else if(hti.iSubItem == 7)
		{
			if(pid->Type == ID_WORKUNIT || pid->Type == ID_WORKSESSION) throw(ERR_REPORTS_1);
			if((vect = db.haeTaulusta("Units", "*", 1, "", 0)).size() == 0) throw(ERR_REPORTS_0);

			Ipedlgcombo2.m_Ipe.x = rect.left + cr.left + 2;
			Ipedlgcombo2.m_Ipe.y = rect.top + cr.top;
			Ipedlgcombo2.m_Ipe.w = cr.right - cr.left + 2;
			Ipedlgcombo2.m_Ipe.h = 24;
			Ipedlgcombo2.m_Ipe.init(m_plstRaportit->GetItemText(hti.iItem, hti.iSubItem), NULL, &vect, 1, "", FALSE);
			Ipedlgcombo2.DoModal();
			if(!Ipedlgcombo2.m_Ipe.isEdited()) throw(ERR_REPORTS_0);

			cs = Ipedlgcombo2.m_Ipe.getString();

			if(pid->Type == ID_SALESUNIT && (cs == _UNIT_MIN_ || cs == _UNIT_HOUR_)) throw(ERR_REPORTS_2);

			db.escape_c(&cs);
			db.lisaaUnit(cs);                                        // : lisää uusi Units.Unit jos ei löydy
			if(cs == _UNIT_HOUR_) cs = _UNIT_MIN_;                   // : pakotetaan tunnit minuuteiksi
			if((r = db.paivitaWorkUnit(pid, 1, WORKUNIT_UNIT, cs)) == RETURN_OK)
			{ pid->Unit = cs; uusiHaku(pid); }						 // Yksiköt vaikuttaa laskuun -> päivitä

			tabbedOut = Ipedlgcombo2.m_Ipe.getTabbedOut();
		}
		// StartDate/StartTime EndDate/EndTime - CDateTimeCtrl // // // // // // // // // // // //
		else if(hti.iSubItem == 4 || hti.iSubItem == 5)
		{
			cs = m_plstRaportit->GetItemText(hti.iItem, hti.iSubItem); // (day.month.year, hour:minute) -> day.month.year.hour.minute) formaattiin Tokenizeria varten
			cs.Replace(DATETIME_IB, " ");
			ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
			ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
			ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
			ipeDlgEdit.m_Ipe.h = 24;
			ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
			ipeDlgEdit.DoModal();
			if(!ipeDlgEdit.m_Ipe.isEdited()) throw(ERR_REPORTS_0);

			cs = ipeDlgEdit.m_Ipe.getString();
			if((pari = paivays.str2pair(cs)).first == "") throw(ERR_REPORTS_0);
			if(hti.iSubItem == 4)
			{
				pari_s.first = pari.first; pari_s.second = pari.second;
				pari_e.first = pid->EndDate; pari_e.second = pid->EndTime;
			}
			else if(hti.iSubItem == 5)
			{
				pari_s.first = pid->StartDate; pari_s.second = pid->StartTime;
				pari_e.first = pari.first; pari_e.second = pari.second;
			}
			paivays.makeTimesLogical(pari_s, pari_e);

			if(pid->Type == ID_WORKUNIT)                   // Asetetaan uusi työaika minuutteina (lasketusta aikaerosta)
				cs.Format("%d", paivays.caclTimeDiff(pari_s, pari_e));
			else
				cs = pid->UnitValue;                       // SALESUNIT annetaan olla sellaisenaan

			if(db.paivitaWorkUnit(pid, 5, WORKUNIT_STARTDATE, pari_s.first, WORKUNIT_STARTTIME, pari_s.second, WORKUNIT_ENDDATE, pari_e.first, WORKUNIT_ENDTIME, pari_e.second, WORKUNIT_UNITVALUE, cs) == RETURN_OK)
			{
				pid->StartDate = pari_s.first; pid->StartTime = pari_s.second;
				pid->EndDate = pari_e.first; pid->EndTime = pari_e.second;

				paivitaPaivays(UPDATE_START, pid->StartDate, pid, FALSE);
				paivitaPaivays(UPDATE_END, pid->StartDate, pid, FALSE);
				uusiHaku(pid);
			}

			tabbedOut = ipeDlgEdit.m_Ipe.getTabbedOut();
		}
		// UnitValue, UnitPrice, TotalPrice, Alv - CEdit // // // // // // // // // // // // // //
		else if(hti.iSubItem == 6 || hti.iSubItem == 8 || hti.iSubItem == 9 || hti.iSubItem == 10)
		{
			if(m_ajat == TIME_CALLS && pid->Type == ID_WORKUNIT && hti.iSubItem == 6) throw(ERR_REPORTS_4);

			cs = m_plstRaportit->GetItemText(hti.iItem, hti.iSubItem);
			ipeDlgEdit.m_Ipe.x = rect.left + cr.left + 2;
			ipeDlgEdit.m_Ipe.y = rect.top + cr.top;
			ipeDlgEdit.m_Ipe.w = cr.right - cr.left + 2;
			ipeDlgEdit.m_Ipe.h = 24;
			ipeDlgEdit.m_Ipe.init(cs, NULL, NULL, 0, "", FALSE);
			ipeDlgEdit.DoModal();
			if(!ipeDlgEdit.m_Ipe.isEdited()) throw(ERR_REPORTS_0);

			cs = db.fixFloat(ipeDlgEdit.m_Ipe.getString(), TRUE);
			if(hti.iSubItem == 6)		cs2 = WORKUNIT_UNITVALUE;
			else if(hti.iSubItem == 8)	cs2 = WORKUNIT_UNITPRICE;
			else if(hti.iSubItem == 9)	cs2 = WORKUNIT_TOTALPRICE;
			else if(hti.iSubItem == 10)	cs2 = WORKUNIT_ALV;

			fval = atof(cs);
			if(pid->Unit == _UNIT_MIN_ && hti.iSubItem == 6)
			{ // Ajat annetaan tilan mukaan joko minuutteina tai tunteina.
				if(m_ajat == TIME_MINUTES) cs.Format("%.0f", fval);					// annettu aika täysiksi minuuteiksi
				else if(m_ajat == TIME_HOURS) cs.Format("%.0f", fval * 60.0f);		// annetaan tunteina, mutta ajat on aina tietokannassa täysinä minuutteina
				pari_e = paivays.calcEndTime(cs, pid->StartDate, pid->StartTime);	// laske minuuteista uusi lopetusaika
				r = db.paivitaWorkUnit(pid, 3, cs2, cs, WORKUNIT_ENDDATE, pari_e.first, WORKUNIT_ENDTIME, pari_e.second); // päivitä kanta
			}
			else if(pid->Unit != _UNIT_MIN_ && hti.iSubItem == 6)
			{
				cs3.Format("%.2f", fval * atof(pid->UnitPrice));
				r = db.paivitaWorkUnit(pid, 2, cs2, cs, WORKUNIT_TOTALPRICE, cs3);
			}
			else if(hti.iSubItem == 8)
			{
				cs3.Format("%.2f", fval * atof(pid->UnitValue));
				r = db.paivitaWorkUnit(pid, 2, cs2, cs, WORKUNIT_TOTALPRICE, cs3);
			}
			else
				r = db.paivitaWorkUnit(pid, 1, cs2, cs);							// kannan päivitys, jos ei muuteta työaikaa

			if(r == RETURN_OK)
			{
				if(hti.iSubItem == 6) pid->UnitValue = cs;
				else if(hti.iSubItem == 8) pid->UnitPrice = cs;
				else if(hti.iSubItem == 9) pid->TotalPrice = cs;
				else if(hti.iSubItem == 10) pid->Alv = cs;

				if(hti.iSubItem == 6 && pid->Unit == _UNIT_MIN_)                   
				{
					pid->EndDate = pari_e.first; pid->EndTime = pari_e.second;

					laskeAjat();													// päivitä laskurit
					cs2 = paivays.date2string(pid->EndDate) + DATETIME_IB + paivays.time2string(pid->EndTime);
					m_plstRaportit->SetItemText(hti.iItem, 5, cs2);					// päivitä lopetusaika raportti-listaan

					if(m_ajat == TIME_HOURS) cs.Format("%.2f",  atof(cs) / 60.0f);	// minuutit tunneiksi (raportti-listan päivitys alla)
				}
				if(hti.iSubItem == 6 && pid->Unit != _UNIT_MIN_)                   
				{
					fval = fval * atof(pid->UnitPrice);
					cs2.Format("%.2f",  fval);
					m_plstRaportit->SetItemText(hti.iItem, 9, cs2);					// päivitä 'Veroton hinta yhteensä' raportti-listaan

					pid->TotalPrice = cs2;
				}
				if(hti.iSubItem == 8)
				{
					fval = fval * atof(pid->UnitValue);
					cs2.Format("%.2f",  fval);
					m_plstRaportit->SetItemText(hti.iItem, 9, cs2);					// päivitä 'Veroton hinta yhteensä' raportti-listaan

					pid->TotalPrice = cs2;
				}

				m_plstRaportit->SetItemText(hti.iItem, hti.iSubItem, cs);			// Päivitetään raportit-listan muokatun itemin teksti
			}

			tabbedOut = ipeDlgEdit.m_Ipe.getTabbedOut();
		}
	}
	catch(int err)
	{
		if(err == ERR_REPORTS_1)
			MessageBox(Props::i().lang("PPAGERAPORTIT_21"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		else if(err == ERR_REPORTS_2)
			MessageBox(Props::i().lang("PPAGERAPORTIT_22"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		else if(err == ERR_REPORTS_4)
			MessageBox(Props::i().lang("PPAGERAPORTIT_23"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
	}

	// Tabilla siirtyy samalla rivillä seuraavaan sarakkeeseen
	if(tabbedOut != 0)
		m_plstRaportit->PostMessage(WM_USER_TABBEDOUT, ((hti.iItem << 8) & 0xFFFFFF00) + hti.iSubItem, tabbedOut);
}

void PpageRaportit::columnHit(int iItem, int iSubItem)
{
    CString cs;
    HDITEM hdi;

    if(iSubItem == 4)                                // Muutetaan aloitusajan mukaan nousevaksi tai laskevaksi järjestykseksi
	{
      cs = Props::i().get(OPTIONS_AIKAJARJESTYS_R).c_str();
      if(cs == DESCENT_S) { cs = ASCENT_S; hdi.iImage = 6; }   // toggle
      else { cs = DESCENT_S; hdi.iImage = 7; }
      Props::i().set(OPTIONS_AIKAJARJESTYS_R, (LPCSTR)cs);     // talleta uusi asetus

      hdi.mask = HDI_IMAGE|HDI_FORMAT;                   // Vaihda kuva raporttilistan otsikkoon 'Aloituspäivä'
      hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT;
      hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("PPAGERAPORTIT_13");
      m_plstRaportit->GetHeaderCtrl()->SetItem(4, &hdi);

      uusiHaku(NULL);                                    // hae uudestaan
	}
}

void PpageRaportit::lisaaTapahtuma(int mode)
{
    int i;
    DlgUusiRaportti d;
    ItemData *pid = NULL;

	POSITION pos = m_plstRaportit->GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		i = m_plstRaportit->GetNextSelectedItem(pos);
		if(!(pid = (ItemData*)m_plstRaportit->GetItemData(i))) return;
	}
	d.m_pid = (mode == 0 ? NULL : pid);				// 0=uusi tapahtuma, 1=muokkaa entistä
	d.m_mode = mode;
    d.m_tyyppi = m_nayta;
    d.DoModal();									// Näytä muokkausdialogi, kutsuu OnOK:lla lisaaTapahtuma(DlgUusiRaportti *pd)
	m_plstRaportit->SetFocus();
}

int PpageRaportit::lisaaTapahtuma(DlgUusiRaportti *pd)
{
    int r;
    DbSqlite db;
	CString biller_id, region_id, worker_id, workplace_id;
    Paivays paivays;
    vector <int> ivect;
    vector <CString> vect;
    vector <CString> wp_vect;
    vector <CString> wt_vect;
    vector <CString> wo_vect;
    vector <CString> b_vect;
    vector <CString> r_vect;
    ItemData *pid = NULL, spid;

	if(pd->m_mode == 0)								// Lisäystila
	{
		vect.clear();									// Lisätään uusi WorkUnit
		vect.push_back(pd->m_workplace_name);			// WorkPlaceName
		vect.push_back(pd->m_worktype_name);			// WorkTypeName
		vect.push_back(pd->m_starttime);				// StartTime
		if(m_nayta == ID_WORKUNIT)
		{
			vect.push_back(pd->m_endtime);				// EndTime
			vect.push_back(pd->m_unitvalue);			// UnitValue
			vect.push_back(m_nayta);					// Type
	        vect.push_back(pd->m_region_name);			// Region
		    vect.push_back(pd->m_alv);					// Alv
			r = db.lisaaWorkUnit(&vect, pd->m_worker_name, NOREPORTNAME, paivays.date2string(pd->m_StartDate), pd->m_biller_name, _UNIT_MIN_, _UNSET_, _UNSET_);
		}
		else if(m_nayta == ID_SALESUNIT)
		{
			vect.push_back(pd->m_unit);					// Unit
			vect.push_back(pd->m_unitvalue);			// UnitValue
			vect.push_back(m_nayta);					// Type
			vect.push_back(pd->m_unitprice);			// UnitPrice
			vect.push_back(pd->m_totalprice);			// TotalPrice
			vect.push_back(_UNSET_);					// ProductNumber
			vect.push_back(pd->m_alv);					// Alv
			vect.push_back(pd->m_region_name);			// Region
			r = db.lisaaSalesUnit(&vect, pd->m_worker_name, NOREPORTNAME, paivays.date2string(pd->m_StartDate), pd->m_biller_name);
		}
		if(vect.size() == 0) return r;

		pid = &spid;									// ItemData* uudelle CListCtrl:n riville
		pid->id = vect[0];								// PALUUARVONA SAATU ID!!!
		pid->ReportName = NOREPORTNAME;
		pid->ReportDate = pd->m_StartDate;
	}
	else											// Muokkaustila
	{
		if(m_nayta == ID_SALESUNIT) db.lisaaUnit(pd->m_unit);
		db.lisaaWorker(pd->m_worker_name, &worker_id);
		db.lisaaBiller(pd->m_biller_name, "", &biller_id, B_NOUPDATE);
		db.lisaaRegion(pd->m_region_name, &region_id);
		db.lisaaWorkPlace(pd->m_workplace_name, region_id, _UNSET_, "", "", "", "", biller_id, &workplace_id, WP_NOUPDATE);
		vect = db.haeTaulusta("WorkType", "id", 1, "", 2, "", "Name", "=", pd->m_worktype_name, "AND", "Type", "=", (m_nayta == ID_WORKUNIT ? WORK : PRODUCT));

		if(m_nayta == ID_WORKUNIT)
			r = db.paivitaWorkUnit(pd->m_pid, 10,	WORKUNIT_WORKER_ID,		worker_id,
													WORKUNIT_WORKPLACE_ID,	workplace_id,
													WORKUNIT_WORKTYPE_ID,	vect[0],
													WORKUNIT_STARTDATE,		pd->m_StartDate,
													WORKUNIT_STARTTIME,		pd->m_StartTime,
													WORKUNIT_ENDDATE,		pd->m_EndDate,
													WORKUNIT_ENDTIME,		pd->m_EndTime,
													WORKUNIT_UNITVALUE,		pd->m_unitvalue,
													WORKUNIT_CHARGED,		pd->m_charged,
													WORKUNIT_BILLER_ID,		biller_id);
		else
			r = db.paivitaWorkUnit(pd->m_pid, 14,	WORKUNIT_WORKER_ID,		worker_id, 
													WORKUNIT_WORKPLACE_ID,	workplace_id,
													WORKUNIT_WORKTYPE_ID,	vect[0],
													WORKUNIT_STARTDATE,		pd->m_StartDate,
													WORKUNIT_STARTTIME,		pd->m_StartTime,
													WORKUNIT_ENDDATE,		pd->m_EndDate,
													WORKUNIT_ENDTIME,		pd->m_EndTime,
													WORKUNIT_UNIT,			pd->m_unit,
													WORKUNIT_UNITVALUE,		pd->m_unitvalue,
													WORKUNIT_CHARGED,		pd->m_charged,
													WORKUNIT_UNITPRICE,		pd->m_unitprice,
													WORKUNIT_TOTALPRICE,	pd->m_totalprice,
													WORKUNIT_ALV,			pd->m_alv,
													WORKUNIT_BILLER_ID,		biller_id);

		pid = pd->m_pid;								// ItemData*!!!
	}

	if(r == RETURN_EXISTS)							// Ei samoja!!!
	{
		MessageBox(Props::i().lang("PPAGERAPORTIT_24"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
		return r;
	}

	// hae uusien kohteiden id:t - fail quietly
	if((r_vect = db.haeTaulusta("Region", "id", 1, "", 1, "", "Name", "=", pd->m_region_name)).size() == 0) return RETURN_OK;
	if((wp_vect = db.haeTaulusta("WorkPlace", "id, CustomerNumber", 2, "", 2, "", "Name", "=", pd->m_workplace_name, "AND", "Region_id", "=", r_vect[0])).size() == 0) return RETURN_OK;
	if((wt_vect = db.haeTaulusta("WorkType", "id, ProductNumber", 2, "", 1, "", "Name", "=", pd->m_worktype_name)).size() == 0) return RETURN_OK;
	if((wo_vect = db.haeTaulusta("Worker", "id", 1, "", 1, "", "Name", "=", pd->m_worker_name)).size() == 0) return RETURN_OK;
	if((b_vect = db.haeTaulusta("Biller", "id", 1, "", 1, "", "Name", "=", pd->m_biller_name)).size() == 0) return RETURN_OK;

	pid->Worker_id = wo_vect[0];
	pid->WorkPlace_id = wp_vect[0];
	pid->WorkType_id = wt_vect[0];
	pid->StartDate = pd->m_StartDate;
	pid->StartTime = pd->m_StartTime;
	pid->EndDate = pd->m_EndDate;
	pid->EndTime = pd->m_EndTime;
	pid->Unit = pd->m_unit;
	pid->UnitValue = pd->m_unitvalue;
	pid->Charged = pd->m_charged;
	pid->UnitPrice = pd->m_unitprice;
	pid->TotalPrice = pd->m_totalprice;
	pid->Alv = pd->m_alv;
	pid->Biller_id = b_vect[0];
	pid->Type = m_nayta;

	// Muokataan suodattimet vastaamaan uutta tilannetta, valitse ja scrollaa näkyville uusi
	paivitaAARListat(pid->WorkPlace_id, pid, FALSE);
	paivitaTyontekijat(pd->m_worker_name, pid, FALSE);
	paivitaTyotyyppi(pd->m_worktype_name, pid, FALSE);
	paivitaPaivays(0, "", pid, TRUE);

	// Synkronoidaan eri näyttöjen listat tarvittaessa
	((CTaikaDlg*)GetParent())->syncListat(SYNC_FROM_RAPORTIT, pd->m_sync);

	return RETURN_OK;
}

void PpageRaportit::poistaItems()
{ // Poistetaan valitut itemit ClistCtrl-kontollista (m_lstTyoajat tai m_lstMyynnit) ja tietokannasta
    int i = -1;
    DbSqlite db;
    POSITION pos;
    vector <CString> vect;

    if(m_plstRaportit->GetItemCount() == 0) return;
    if(m_plstRaportit->GetSelectedCount() == 0) return;

    if(MessageBox(Props::i().lang("PPAGERAPORTIT_25"), Props::e().m_app_title, MB_YESNO|MB_ICONQUESTION) == IDNO)
      return;

    while((pos = m_plstRaportit->GetFirstSelectedItemPosition()))      // Käydään valitut läpi
    {
      i = m_plstRaportit->GetNextSelectedItem(pos);

      if(m_plstRaportit->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)  // Poista tietokannasta
        db.poistaYleinen("WorkUnit", WORKUNIT_ID, ((ItemData*)m_plstRaportit->GetItemData(i))->id, TRUE, "");    // TODO: talletetaan ensin _poistetut kansioon?

      m_plstRaportit->DeleteItem(i);                                       // Poista listasta
	}

	if(m_plstRaportit->GetItemCount() > 0)
	{
		i = max(i - 1, 0);
        m_plstRaportit->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
        m_plstRaportit->EnsureVisible(i, FALSE);
	}
	m_plstRaportit->SetFocus();
}

void PpageRaportit::valitseKaikki()
{
    int i,s;

    s = m_plstRaportit->GetItemCount();
    for(i=0; i<s; i++) m_plstRaportit->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    m_plstRaportit->SetFocus();
    if(s > 0) m_plstRaportit->SetSelectionMark(0);
}

void PpageRaportit::laskutaKaikkiNaytetyt()
{
    if(!haeItemDataList(&m_DlgLaskutus.m_tapahtumat, MODE_KAIKKINAYTETYT)) return;  // Laskutetaan kaikki asiakkaat raporttilistasta
	m_DlgLaskutus.m_nayta = m_nayta;
    m_DlgLaskutus.DoModal();
	laskutettu(MODE_KAIKKINAYTETYT);
}

void PpageRaportit::laskutaValitut()
{ 
    if(!haeItemDataList(&m_DlgLaskutus.m_tapahtumat, MODE_VALITUT)) return;         // Laskutetaan kaikki valitut asiakkaat raporttilistasta
	m_DlgLaskutus.m_nayta = m_nayta;
    m_DlgLaskutus.DoModal();
	laskutettu(MODE_VALITUT);
}

void PpageRaportit::laskutaAsiakas()
{ 
    if(!haeItemDataList(&m_DlgLaskutus.m_tapahtumat, MODE_ASIAKAANTIEDOT)) return;  // Laskutetaan kaikki valitut asiakkaat asiakkaat-listasta
	m_DlgLaskutus.m_nayta = m_nayta;
    m_DlgLaskutus.DoModal();
	laskutettu(MODE_ASIAKAANTIEDOT);
}

void PpageRaportit::laskutettu(int mode)
{
	int i, s;
	CString cs;
	POSITION pos;
	CStringList wpid;

	vapautaItemDataLists(&m_DlgLaskutus.m_tapahtumat, &m_DlgLaskutus.m_tapahtumat_laskutukseen, mode);

	pos = m_plstRaportit->GetFirstSelectedItemPosition();   // Talleta valittujen WorkUnit.id
	while(pos)
    {
      s = m_plstRaportit->GetNextSelectedItem(pos);
      if(m_plstRaportit->GetItemState(s, LVIS_SELECTED) == LVIS_SELECTED)
		  wpid.AddTail(((ItemData*)m_plstRaportit->GetItemData(s))->id);
	}

    paivitaAARListat("", NULL, TRUE);//uusiHaku(NULL);

	for(i=0; i<m_plstRaportit->GetItemCount(); i++)			// Palauta valitut
	{
		cs = ((ItemData*)m_plstRaportit->GetItemData(i))->id;

		if((pos = wpid.Find(cs, 0)) != NULL)
		{
			m_plstRaportit->SetItem(i, 0, LVIF_STATE, 0, 0, LVIS_SELECTED, LVIS_SELECTED, 0);
			m_plstRaportit->EnsureVisible(i, FALSE);

			wpid.RemoveAt(pos);
		}
	}

}

void PpageRaportit::eritteleNaytetytTyot()
{
    if(!haeItemDataList(&m_DlgErittely.m_tapahtumat, MODE_KAIKKINAYTETYT)) return;  // Eritellään kaikki asiakkaat raporttilistasta
    m_DlgErittely.m_mode = MODE_ASIAKKAAT;
	m_DlgErittely.m_nayta = m_nayta;
    m_DlgErittely.DoModal();
	vapautaItemDataLists(&m_DlgErittely.m_tapahtumat, &m_DlgErittely.m_tapahtumat_tulostukseen, MODE_KAIKKINAYTETYT);
}

void PpageRaportit::eritteleValitutTyot()
{
    if(!haeItemDataList(&m_DlgErittely.m_tapahtumat, MODE_VALITUT)) return;         // Eritellään kaikki valitut asiakkaat raporttilistasta
    m_DlgErittely.m_mode = MODE_ASIAKKAAT;
	m_DlgErittely.m_nayta = m_nayta;
    m_DlgErittely.DoModal();
	vapautaItemDataLists(&m_DlgErittely.m_tapahtumat, &m_DlgErittely.m_tapahtumat_tulostukseen, MODE_VALITUT);
}

void PpageRaportit::eritteleValitutAsiakasTyot()
{
    if(!haeItemDataList(&m_DlgErittely.m_tapahtumat, MODE_ASIAKAANTIEDOT)) return;  // Eritellään kaikki valitut asiakkaat asiakkaat-listasta
    m_DlgErittely.m_mode = MODE_ASIAKKAAT;
	m_DlgErittely.m_nayta = m_nayta;
    m_DlgErittely.DoModal();
	vapautaItemDataLists(&m_DlgErittely.m_tapahtumat, &m_DlgErittely.m_tapahtumat_tulostukseen, MODE_ASIAKAANTIEDOT);
}

void PpageRaportit::eritteleNaytetytTyoajat()
{
    if(!haeItemDataList(&m_DlgErittely.m_tapahtumat, MODE_KAIKKINAYTETYT)) return;  // Eritellään kaikki asiakkaat raporttilistasta
    m_DlgErittely.m_mode = MODE_TYOAJAT;
	m_DlgErittely.m_nayta = m_nayta;
    m_DlgErittely.DoModal();
	vapautaItemDataLists(&m_DlgErittely.m_tapahtumat, &m_DlgErittely.m_tapahtumat_tulostukseen, MODE_KAIKKINAYTETYT);
}

void PpageRaportit::eritteleValitutTyoajat()
{
    if(!haeItemDataList(&m_DlgErittely.m_tapahtumat, MODE_VALITUT)) return;         // Eritellään kaikki valitut asiakkaat raporttilistasta
    m_DlgErittely.m_mode = MODE_TYOAJAT;
	m_DlgErittely.m_nayta = m_nayta;
    m_DlgErittely.DoModal();
	vapautaItemDataLists(&m_DlgErittely.m_tapahtumat, &m_DlgErittely.m_tapahtumat_tulostukseen, MODE_VALITUT);
}

void PpageRaportit::eritteleValitutTyontekijaTyoajat()
{
    if(!haeItemDataList(&m_DlgErittely.m_tapahtumat, MODE_ASIAKAANTIEDOT_TT)) return;  // Eritellään kaikki valitut asiakkaat asiakkaat-listasta työntekijöittäin
    m_DlgErittely.m_mode = MODE_TYOAJAT;
	m_DlgErittely.m_nayta = m_nayta;
    m_DlgErittely.DoModal();
	vapautaItemDataLists(&m_DlgErittely.m_tapahtumat, &m_DlgErittely.m_tapahtumat_tulostukseen, MODE_ASIAKAANTIEDOT_TT);
}

BOOL PpageRaportit::haeItemDataList(vector <ItemData*> *pvect, int mode)
{ // Hakee asiakkaalle/-ille tai työntekijälle/-öille tehdyt/tekemät työt
    DbSqlite db;
    ItemData *pid;
    int i, j, s, c;
    CString cs, order;
    vector <CString> vect;

    // Otetaan asiakkaat ajan suhteen nousevassa järjestyksessä (pienin->suurin aloituspäivä)
    if((order = Props::i().get(OPTIONS_AIKAJARJESTYS_R).c_str()) == "") order = ASCENT_S;

    try
	{
      pvect->clear();                                // Tyhjennä vanhat tiedot pois

      if(mode == MODE_VALITUT)                       // Otetaan valitut tapahtumat asiakkaille raporttilistasta
	  {
        if((s = m_plstRaportit->GetItemCount()) == 0) throw(ERR_REPE);
        if(order == ASCENT_S)
		{
          for(i=0; i<s; i++) {
            if(m_plstRaportit->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
              pvect->push_back((ItemData*)m_plstRaportit->GetItemData(i)); }
		}
        else
		{
          for(i=s-1; i>-1; i--) {
            if(m_plstRaportit->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
              pvect->push_back((ItemData*)m_plstRaportit->GetItemData(i)); }
		}
	  }
      else if(mode == MODE_KAIKKINAYTETYT)           // Otetaan kaikki tapahtumat asiakkaalle (näytetyt) raporttilistasta
	  {
        if((s = m_plstRaportit->GetItemCount()) == 0) throw(ERR_REPE);
        if(order == ASCENT_S) {
          for(i=0; i<s; i++)
            pvect->push_back((ItemData*)m_plstRaportit->GetItemData(i)); }
        else {
          for(i=s-1; i>-1; i--)
            pvect->push_back((ItemData*)m_plstRaportit->GetItemData(i)); }
	  }
      else if(mode == MODE_ASIAKAANTIEDOT)           // Otetaan tietyn asiakkaille kaikki tapahtumat
	  {
        if(m_lstAsiakkaat.GetSelCount() < 1) throw(ERR_SELATLEASTONE);

        s = m_lstAsiakkaat.GetCount();
        for(i=0; i<s; i++)
		{
          j = m_lstAsiakkaat.GetSel(i);              // vain valitut tapahtumat asiakkaille
          if(j == 0 || j == LB_ERR) continue;

          cs.Format("%d", m_lstAsiakkaat.GetItemData(i));// ItemDatassa säilytetty id hakuehdoksi - hae tehdyt työt
          if((c = (vect = db.haeTaulusta("WorkUnit", "*", WORKUNIT_COLS, "StartDate", 1, "", "WorkPlace_id", "=", cs)).size()) == 0) 
            continue;

          for(j=0; j<c; j+=WORKUNIT_COLS)
		  {
            pid = new ItemData;
            pid->id = vect[j];
            pid->Worker_id = vect[j + 1];
            pid->WorkPlace_id = vect[j + 2];
            pid->WorkType_id = vect[j + 3];
            pid->StartDate = vect[j + 4];
            pid->StartTime = vect[j + 5];
            pid->EndDate = vect[j + 6];
            pid->EndTime = vect[j + 7];
            pid->Unit = vect[j + 8];
            pid->UnitValue = vect[j + 9];
            pid->Charged = vect[j + 10];
            pid->UnitPrice = vect[j + 11];
            pid->TotalPrice = vect[j + 12];
            pid->Alv = vect[j + 13];
            pid->ReportName = vect[j + 14];
            pid->ReportDate = vect[j + 15];
            pid->Biller_id = vect[j + 16];
            pid->Type = vect[j + 17];
            pvect->push_back(pid);
		  }
		}

        if(pvect->size() == 0) throw(ERR_NOWUNITS);  // Ei tietoja
	  }
      else if(mode == MODE_ASIAKAANTIEDOT_TT)        // Otetaan tiettyjen työntekijöiden tekemät työt
	  {
        if(m_lstTyontekijat.GetSelCount() < 1) throw(ERR_SELATLEASTONE);

        s = m_lstTyontekijat.GetCount();
        for(i=0; i<s; i++)
		{
          j = m_lstTyontekijat.GetSel(i);            // vain valitut työntekijät
          if(j == 0 || j == LB_ERR) continue;

          cs.Format("%d", m_lstTyontekijat.GetItemData(i));// ItemDatassa säilytetty id hakuehdoksi - 
          if((c = (vect = db.haeTaulusta("WorkUnit", "*", WORKUNIT_COLS, "WorkPlace_id, StartDate", 1, "", "Worker_id", "=", cs)).size()) == 0)
            continue;

          for(j=0; j<c; j+=WORKUNIT_COLS)
		  {
            pid = new ItemData;
            pid->id = vect[j];
            pid->Worker_id = vect[j + 1];
            pid->WorkPlace_id = vect[j + 2];
            pid->WorkType_id = vect[j + 3];
            pid->StartDate = vect[j + 4];
            pid->StartTime = vect[j + 5];
            pid->EndDate = vect[j + 6];
            pid->EndTime = vect[j + 7];
            pid->Unit = vect[j + 8];
            pid->UnitValue = vect[j + 9];
            pid->Charged = vect[j + 10];
            pid->UnitPrice = vect[j + 11];
            pid->TotalPrice = vect[j + 12];
            pid->Alv = vect[j + 13];
            pid->ReportName = vect[j + 14];
            pid->ReportDate = vect[j + 15];
            pid->Biller_id = vect[j + 16];
            pid->Type = vect[j + 17];
            pvect->push_back(pid);
		  }  
		}

        if(pvect->size() == 0) throw(ERR_NOWUNITS);  // Ei tietoja
	  }
	}
    catch(int err)
	{
      if(err == ERR_SELATLEASTONE) cs.Format(Props::i().lang("PPAGERAPORTIT_26"), ASIAKKAAT);
	  else if(err == ERR_REPE) cs.Format(Props::i().lang("PPAGERAPORTIT_27"), TYOTKOHTEISSA);
      else if(err == ERR_NOWUNITS) cs = Props::i().lang("PPAGERAPORTIT_28");

      MessageBox(cs, Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
      return FALSE;
	}

    return TRUE;
}

void PpageRaportit::vapautaItemDataLists(vector <ItemData*> *pvect, vector <ItemData*> *pvectT, int mode)
{
    int i, s;

    if(mode == MODE_VALITUT) pvect->clear();
    else if(mode == MODE_KAIKKINAYTETYT) pvect->clear(); 
    else if(mode == MODE_ASIAKAANTIEDOT || mode == MODE_ASIAKAANTIEDOT_TT)
	{
      s = pvect->size();                      // vapauta muisti
      for(i=0; i<s; i++) delete pvect->at(i);
      pvect->clear(); 
	}

    if(pvectT != NULL)
	{
      s = pvectT->size();                       // vapauta muisti
      for(i=0; i<s; i++) delete pvectT->at(i);
      pvectT->clear();
	}
}

int PpageRaportit::getMode()
{ // palauttaa tilat joissa voidaan operoida tapahtumilla
    int mode = 0;

    if(m_plstRaportit->GetFirstSelectedItemPosition()) mode = MODE_VALITUT;
    if(m_plstRaportit->GetItemCount() > 0) mode += MODE_KAIKKINAYTETYT;
    if(m_lstAsiakkaat.GetSelCount() > 0) mode += MODE_ASIAKAANTIEDOT;

    return mode;
}

/*void PpageRaportit::email()
{
    DlgSMTP dlg;

    dlg.m_mode = MODE_EMAIL_RAPORTIT;
    dlg.DoModal();
}*/

void PpageRaportit::etsi(int key)
{
    int s, f;
    DlgEtsi *pdlg;

    pdlg = &Props::e().m_dlgEtsi;

    if(pdlg->m_vect.size() == 0 || key == KEY_CTRLF) // Uusi haku
	{ if(pdlg->DoModal() != IDOK) return; }
    else                                             // Hae seuraava
	{ if(++pdlg->m_pos == pdlg->m_count) pdlg->m_pos = 0; }

    s = pdlg->m_pos * 4;
    if(s > pdlg->m_vect.size() || s < 0) return;                               // Varmista, että ei osoiteta olemattomaan alkioon vektorissa

    // Valitaan asiakasryhmä ja etsitty asiakas
    if((f = m_lstAsiakasryhmat.FindStringExact(-1, pdlg->m_vect[s + 3])) != LB_ERR)
	{
      m_lstAsiakasryhmat.SelItemRange(FALSE, 0, m_lstAsiakasryhmat.GetCount());// Entiset valinnat pois
      m_lstAsiakasryhmat.SetSel(f, TRUE);                                      // Etsityn asiakkaan asiakasryhmä valituksi
      OnSelchangeLstasiakasryhma(FALSE, FALSE);                                // Hae valitun asiakasryhmän kaikki asiakkaat (ei valittuina)
      if((f = m_lstAsiakkaat.FindString(-1, pdlg->m_vect[s + 1])) != LB_ERR)   // Valitse etsitty asiakas
	  {
        m_lstAsiakkaat.SetSel(f, TRUE);
        uusiHaku(NULL);                                                        // Näytetään etsityn asiakkaan tiedot
	  }
	}
}

void PpageRaportit::laskeAjat()
{ // lasketaan yhteensä ja valitut ajat raportit-listasta
    int i, s;
    float cnv;
    CString cs;
    ItemData *pid;
    float yht, val;

    yht = val = 0.0f;
    s = m_plstRaportit->GetItemCount();
    for(i=0; i<s; i++)
	{
      if(!(pid = (ItemData*)m_plstRaportit->GetItemData(i))) continue;   // seuraava, jos jostain syystä pointteri on nolla
      if(pid->Type != ID_WORKUNIT) continue;                             // huomioidaan vain työajat

      cnv = atof(pid->UnitValue);
      if(m_plstRaportit->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)// lasketaan valitut yhteen
        val += cnv;
      yht += cnv;                                                        // lasketaan kaikki yhteen
	}

    if(yht == 0) cs = "";                            // Asetetaan kokonaisaika näkyville
    else
	{
      if(m_ajat == TIME_MINUTES) cs.Format("%.0f %s", yht, yht == 1 ? Props::i().lang("PPAGERAPORTIT_14") : Props::i().lang("PPAGERAPORTIT_15"));
      else if(m_ajat == TIME_HOURS) cs.Format("%.2f %s", yht / 60.0f, Props::i().lang("PPAGERAPORTIT_16"));
      //else if(m_ajat == TIME_CALLS) cs.Format("%.0f %s", yht, yht == 1 ? Props::i().lang("PPAGERAPORTIT_17") : Props::i().lang("PPAGERAPORTIT_18"));
	}
    m_stcAjat.SetWindowText(cs);

    if(val == 0) cs = "";                            // Asetetaan valittujen ajat näkyville
    else
	{
      if(m_ajat == TIME_MINUTES) cs.Format("%.0f %s", val, val == 1 ? Props::i().lang("PPAGERAPORTIT_14") : Props::i().lang("PPAGERAPORTIT_15"));
      else if(m_ajat == TIME_HOURS) cs.Format("%.2f %s", val / 60.0f, Props::i().lang("PPAGERAPORTIT_16"));
      //else if(m_ajat == TIME_CALLS) cs.Format("%.0f %s", val, val == 1 ? Props::i().lang("PPAGERAPORTIT_17") : Props::i().lang("PPAGERAPORTIT_18"));
	}
    m_stcValitut.SetWindowText(cs);
}

void PpageRaportit::onkoTyontekijaListassa(CString nimi, CString wid) // 31.8.2009, onko työntekijän id listassa (raportissa työntekijä muutettu, tarkistetaan luotiinko konaan uusi vai valittiinko vanha)
{ // Lisää listaan, jos ei löydy id:tä. Muussa tapauksessa valitse listan kohta, josta löytyi.
	int i,
		icount = (m_lstTyontekijat.GetCount() == LB_ERR ? -1 : m_lstTyontekijat.GetCount()), 
		id = atoi(wid);

	for(i=0; i<icount; i++)						// etsitään
	{ if(m_lstTyontekijat.GetItemData(i) == id) break; }

	if(i == icount)								// lisätään, jos ei löydy
	{
		i = m_lstTyontekijat.AddString(nimi);
		m_lstTyontekijat.SetItemData(i, id);
		m_lstTyontekijat.SetSel(i, TRUE);
	}
	else										// valitaan, jos löytyy
		m_lstTyontekijat.SetSel(i, TRUE);
}

// - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // -
// ON_UPDATE_COMMAND_UI // - // - // - // - // - // - // - // - // - // - // - // - // - // - // -
// - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // -
LRESULT PpageRaportit::OnKickIdle(WPARAM wparam, LPARAM lparam)
{
	UpdateDialogControls(this, FALSE);
	return 0L;
}

void PpageRaportit::OnUpdatePoistaValitut(CCmdUI* pCmdUI)
{
    if(m_plstRaportit->GetSelectedCount() == 0) pCmdUI->Enable(FALSE);
    else pCmdUI->Enable(TRUE);
}

void PpageRaportit::OnUpdateLaskuta(CCmdUI* pCmdUI)
{
    int ic_r, sc_r, sc_a;

    ic_r = m_plstRaportit->GetItemCount();
    sc_r = m_plstRaportit->GetSelectedCount();
    sc_a = m_lstAsiakkaat.GetSelCount();

    if(ic_r > 0 || sc_r > 0 || sc_a > 0) pCmdUI->Enable(TRUE);
    else pCmdUI->Enable(FALSE);
}

void PpageRaportit::OnUpdateErittely(CCmdUI* pCmdUI)
{
    int ic_r, sc_r, sc_a;

    ic_r = m_plstRaportit->GetItemCount();
    sc_r = m_plstRaportit->GetSelectedCount();
    sc_a = m_lstAsiakkaat.GetSelCount();

    if(ic_r > 0 || sc_r > 0 || sc_a > 0) pCmdUI->Enable(TRUE);
    else pCmdUI->Enable(FALSE);
}

void PpageRaportit::OnUpdateValInfo(CCmdUI* pCmdUI)
{
    if(m_plstRaportit->GetSelectedCount() > 0) pCmdUI->Enable(TRUE);
    else pCmdUI->Enable(FALSE);
}

void PpageRaportit::OnUpdateYhtInfo(CCmdUI* pCmdUI)
{
    if(m_plstRaportit->GetItemCount() > 0) pCmdUI->Enable(TRUE);
    else pCmdUI->Enable(FALSE);
}

void PpageRaportit::OnRadnayta()
{
    int s = GetCheckedRadioButton(IDC_RDNAYTA1, IDC_RDNAYTA2);

    CheckRadioButton(IDC_RDNAYTA1, IDC_RDNAYTA2, s);

    if(s == IDC_RDNAYTA1)
	{
      m_nayta = ID_WORKUNIT;

	  m_lstTyoajat.ShowWindow(SW_SHOW);
	  m_lstMyynnit.ShowWindow(SW_HIDE);
	  m_plstRaportit = &m_lstTyoajat;
      m_cmbAika.EnableWindow(TRUE);
      m_stcReport.SetWindowText(Props::i().lang("PPAGERAPORTIT_1")); 
      m_chkTyotyypit.SetWindowText(Props::i().lang("PPAGERAPORTIT_2"));
      paivitaTyotyyppi("", NULL, FALSE);
	}
    else if(s == IDC_RDNAYTA2)
	{
      m_nayta = ID_SALESUNIT;

	  m_lstMyynnit.ShowWindow(SW_SHOW);
	  m_lstTyoajat.ShowWindow(SW_HIDE);
	  m_plstRaportit = &m_lstMyynnit;
      m_cmbAika.EnableWindow(FALSE);
      m_stcReport.SetWindowText(Props::i().lang("PPAGERAPORTIT_29"));
      m_chkTyotyypit.SetWindowText(Props::i().lang("PPAGERAPORTIT_30"));
      paivitaTyotyyppi("", NULL, FALSE);
	}
    /*else if(s == 2) m_nayta = TM_BOTH;
    else if(s == 3) m_nayta = MT_BOTH;*/

    uusiHaku(NULL);
}

CMenu *PpageRaportit::createMenu()
{
	CMenu fileMenu;
	VERIFY(fileMenu.CreatePopupMenu());
	fileMenu.AppendMenu(MF_STRING, IDM_AVAA_RAPORTTI, Props::i().lang("RAPORTIT_MENU_1"));
	fileMenu.AppendMenu(MF_STRING, IDM_TALLETA_RAPORTTI, Props::i().lang("RAPORTIT_MENU_2"));
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