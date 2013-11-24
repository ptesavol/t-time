// DlgImport.cpp : implementation file
//

#include "stdafx.h"
#include "taika.h"
#include "DlgImport.h"
#include "Props.h"
#include "Paivays.h"
#include "AccountingProgramWrapper.h"
#include "AccountingException.h"
#include "BdeException.h"
#include "DlgErittely.h"
#include "DbSqlite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgImport dialog


DlgImport::DlgImport(CWnd* pParent /*=NULL*/)
	: CDialog(DlgImport::IDD, pParent), m_pCImageList(NULL), m_update(FALSE)
{
	//{{AFX_DATA_INIT(DlgImport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgImport)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STCINFO, m_stcInfo);
	DDX_Control(pDX, IDC_CMBTILA, m_cmbTila);
	DDX_Control(pDX, IDC_STCYRITYS, m_stcYritys);
	DDX_Control(pDX, IDC_LSTONE, m_lstOne);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgImport, CDialog)
	//{{AFX_MSG_MAP(DlgImport)
	ON_CBN_SELCHANGE(IDC_CMBTILA, OnSelchangeCmbtila)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_USER_SELECTALL, OnMsgValitseKaikki)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgImport message handlers
BOOL DlgImport::OnInitDialog() 
{
    HBITMAP hbm;
    CBitmap cBmA;
    CBitmap cBmD;

	CDialog::OnInitDialog();

	SetWindowText(Props::i().lang("DLGIMPORT_C1"));
	m_btnOK.SetWindowText(Props::i().lang("DLGIMPORT_C2"));
	m_btnCancel.SetWindowText(Props::i().lang("DLGIMPORT_C3"));

	ListView_SetExtendedListViewStyleEx(m_lstOne.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

    if((m_pCImageList = new CImageList()))
	{
      m_pCImageList->Create(16, 16, ILC_MASK|ILC_COLOR32, 2, 2);
      hbm = (HBITMAP)LoadImage(Props::e().m_hInstance, MAKEINTRESOURCE(IDB_BMPUNCHECKED), IMAGE_BITMAP, 16, 16, LR_LOADMAP3DCOLORS|LR_LOADTRANSPARENT);
      cBmA.Attach(hbm);
      hbm = (HBITMAP)LoadImage(Props::e().m_hInstance, MAKEINTRESOURCE(IDB_BMPCHECKED), IMAGE_BITMAP, 16, 16, LR_LOADMAP3DCOLORS|LR_LOADTRANSPARENT);
      cBmD.Attach(hbm);
      m_pCImageList->Add(&cBmA, RGB(255,0,0));
      m_pCImageList->Add(&cBmD, RGB(255,0,0));

      m_lstOne.GetHeaderCtrl()->SetImageList(m_pCImageList/*, LVSIL_SMALL*/);
	}

    m_stcYritys.SetWindowText(CString(Props::i().lang("DLGIMPORT_1")) + Props::i().get(OPTIONS_LASKUTUSOHJELMA_KOKO_POLKU).c_str());

    m_cmbTila.AddString(Props::i().lang("DLGIMPORT_2")); m_cmbTila.AddString(Props::i().lang("DLGIMPORT_3")); m_cmbTila.AddString(Props::i().lang("DLGIMPORT_4"));
    m_cmbTila.SetCurSel(0);
    OnSelchangeCmbtila();

    return TRUE;
}

void DlgImport::OnDestroy() 
{
    CDialog::OnDestroy();

    if(m_pCImageList) delete m_pCImageList;
}

void DlgImport::OnSelchangeCmbtila() 
{
    int s = m_cmbTila.GetCurSel();

    if(s == 0)
	{
      m_stcInfo.SetWindowText(Props::i().lang("DLGIMPORT_5"));
      haeAsiakkaat();
	}
    else if(s == 1)
	{
      m_stcInfo.SetWindowText(Props::i().lang("DLGIMPORT_6"));
      haeTyotyypit();
	}
    else if(s == 2)
	{
      m_stcInfo.SetWindowText(Props::i().lang("DLGIMPORT_7"));
      haeTuotteet();
	}
}

void DlgImport::haeAsiakkaat()
{
    RECT rect;
    HDITEM hdi;
    int i, j, t, sel;
    DWORD color = WHITE;
    vector<string> vect_p, vect_g;
    CString ryhma;

	CDialog::OnInitDialog();

    m_lstOne.DeleteAllItems();
    while(m_lstOne.DeleteColumn(0));

    m_lstOne.GetClientRect(&rect);                       // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstOne.InsertColumn(0, Props::i().lang("DLGIMPORT_8"), LVCFMT_LEFT, rect.right * 0.20, -1);
    m_lstOne.InsertColumn(1, Props::i().lang("DLGIMPORT_9"), LVCFMT_LEFT, rect.right * 0.20, -1);
    m_lstOne.InsertColumn(2, Props::i().lang("DLGIMPORT_10"), LVCFMT_LEFT, rect.right * 0.20, -1);
    m_lstOne.InsertColumn(3, Props::i().lang("DLGIMPORT_11"), LVCFMT_LEFT, rect.right * 0.20, -1);
    m_lstOne.InsertColumn(4, Props::i().lang("DLGIMPORT_12"), LVCFMT_LEFT, rect.right * 0.20, -1);

    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_10");
    m_lstOne.GetHeaderCtrl()->SetItem(2, &hdi);
    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_11");
    m_lstOne.GetHeaderCtrl()->SetItem(3, &hdi);
    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_12");
    m_lstOne.GetHeaderCtrl()->SetItem(4, &hdi);

    AccountingProgramWrapper::open();
    vect_g = AccountingProgramWrapper::ap->getCustomerGroups();
    vect_p = AccountingProgramWrapper::ap->getCustomers();
	AccountingProgramWrapper::close();

	for(i=0; i<vect_g.size(); i+=2)
	{
      ryhma = vect_g[i + 1].c_str();

      for(j=0; j<vect_p.size(); j+=5)
	  {
        if(vect_p[j] != vect_g[i]) continue;

        t = m_lstOne.GetItemCount();
        sel = m_lstOne.InsertItem(LVIF_TEXT, t, ryhma, 0, 0, 0, 0);             // ASRYHMAT.Nimi
        m_lstOne.SetItem(sel, 1, LVIF_TEXT, vect_p[j + 1].c_str(), 0, 0, 0, 0); // TOI_AS.Nimi
        m_lstOne.SetItem(sel, 2, LVIF_TEXT, vect_p[j + 2].c_str(), 0, 0, 0, 0); // TOI_AS.KatuOs
        m_lstOne.SetItem(sel, 3, LVIF_TEXT, vect_p[j + 3].c_str(), 0, 0, 0, 0); // TOI_AS.AsNro
        m_lstOne.SetItem(sel, 4, LVIF_TEXT, vect_p[j + 4].c_str(), 0, 0, 0, 0); // TOI_AS.Lisatietoja

        m_lstOne.SetItemData(t, color);
		ryhma = "";
	  }
	}
}

void DlgImport::haeTyotyypit()
{
	BOOL bvg;
    RECT rect;
    HDITEM hdi;
    int i, j, t, sel;
    vector<string> vect_p, vect_g;
    CString ryhma;

	CDialog::OnInitDialog();

    m_lstOne.DeleteAllItems();
    while(m_lstOne.DeleteColumn(0));

    m_lstOne.GetClientRect(&rect);                       // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstOne.InsertColumn(0, Props::i().lang("DLGIMPORT_13"), LVCFMT_LEFT, rect.right * 0.30, -1);
    m_lstOne.InsertColumn(1, Props::i().lang("DLGIMPORT_14"), LVCFMT_LEFT, rect.right * 0.30, -1);
    m_lstOne.InsertColumn(2, Props::i().lang("DLGIMPORT_15"), LVCFMT_LEFT, rect.right * 0.20, -1);

    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_15");
    m_lstOne.GetHeaderCtrl()->SetItem(2, &hdi);

	AccountingProgramWrapper::open();
	bvg = AccountingProgramWrapper::ap->isVatGroup();								// 14.8.2010, J.V.
    vect_g = AccountingProgramWrapper::ap->getProductGroups();
    vect_p = AccountingProgramWrapper::ap->getProducts(bvg);
	AccountingProgramWrapper::close();
	vect_g.push_back("");															// 14.8.2010, J.V. ryhm‰ttˆm‰t tuotteet
	vect_g.push_back((LPCSTR)Props::i().lang("DLGIMPORT_16"));

	for(i=0; i<vect_g.size(); i+=2)
	{
      ryhma = vect_g[i + 1].c_str();

      for(j=0; j<vect_p.size(); j+=7)
	  {
        if(vect_p[j] != vect_g[i]) continue;

        t = m_lstOne.GetItemCount();
        sel = m_lstOne.InsertItem(LVIF_TEXT, t, ryhma, 0, 0, 0, 0);                  // TUOTERYHMAT.Nimi
        m_lstOne.SetItem(sel, 1, LVIF_TEXT, vect_p[j + 1].c_str(), 0, 0, 0, 0);      // TUOTTEET.Nimi
        m_lstOne.SetItem(sel, 2, LVIF_TEXT, vect_p[j + 2].c_str(), 0, 0, 0, 0);      // TUOTTEET.TuoteNimi

        m_lstOne.SetItemData(t, WHITE);
        ryhma = "";
	  }
	}
}

void DlgImport::haeTuotteet()
{
	BOOL bvg;
    RECT rect;
    HDITEM hdi;
	Alv *pAlv = NULL;
    int i, j, t, sel;
    DWORD color = WHITE;
    vector<string> vect_p, vect_g;
    CString ryhma;

	CDialog::OnInitDialog();

    m_lstOne.DeleteAllItems();
    while(m_lstOne.DeleteColumn(0));

    m_lstOne.GetClientRect(&rect);                       // Sarakkeiden nimet ja oletus koot prosentteina suhteessa leveyteen
    m_lstOne.InsertColumn(0, Props::i().lang("DLGIMPORT_13"), LVCFMT_LEFT, rect.right * 0.16, -1);
    m_lstOne.InsertColumn(1, Props::i().lang("DLGIMPORT_14"), LVCFMT_LEFT, rect.right * 0.16, -1);
    m_lstOne.InsertColumn(2, Props::i().lang("DLGIMPORT_15"), LVCFMT_LEFT, rect.right * 0.13, -1);
    m_lstOne.InsertColumn(3, Props::i().lang("DLGIMPORT_17"), LVCFMT_LEFT, rect.right * 0.12, -1);
    m_lstOne.InsertColumn(4, Props::i().lang("DLGIMPORT_18"), LVCFMT_LEFT, rect.right * 0.12, -1);
    m_lstOne.InsertColumn(5, Props::i().lang("DLGIMPORT_19"), LVCFMT_LEFT, rect.right * 0.18, -1);
    m_lstOne.InsertColumn(6, Props::i().lang("DLGIMPORT_20"), LVCFMT_LEFT, rect.right * 0.10, -1);

    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_15");
    m_lstOne.GetHeaderCtrl()->SetItem(2, &hdi);
    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText =(LPSTR)(LPCSTR) Props::i().lang("DLGIMPORT_17");
    m_lstOne.GetHeaderCtrl()->SetItem(3, &hdi);
    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_18");
    m_lstOne.GetHeaderCtrl()->SetItem(4, &hdi);
    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_19");
    m_lstOne.GetHeaderCtrl()->SetItem(5, &hdi);
    hdi.mask = HDI_IMAGE|HDI_FORMAT; hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT; hdi.iImage = 1; hdi.pszText = (LPSTR)(LPCSTR)Props::i().lang("DLGIMPORT_20");
    m_lstOne.GetHeaderCtrl()->SetItem(6, &hdi);

	AccountingProgramWrapper::open();
	bvg = AccountingProgramWrapper::ap->getAlvVect(pAlv);							// 14.8.2010, J.V.
    vect_g = AccountingProgramWrapper::ap->getProductGroups();
    vect_p = AccountingProgramWrapper::ap->getProducts(bvg);
	AccountingProgramWrapper::close();
	vect_g.push_back("");															// 14.8.2010, J.V. ryhm‰ttˆm‰t tuotteet
	vect_g.push_back((LPCSTR)Props::i().lang("DLGIMPORT_16"));

	for(i=0; i<vect_g.size(); i+=2)
	{
      ryhma = vect_g[i + 1].c_str();

      for(j=0; j<vect_p.size(); j+=7)
	  {
        if(vect_p[j] != vect_g[i]) continue;

        t = m_lstOne.GetItemCount();
        sel = m_lstOne.InsertItem(LVIF_TEXT, t, ryhma, 0, 0, 0, 0);								// TUOTERYHMAT.Nimi
        m_lstOne.SetItem(sel, 1, LVIF_TEXT, vect_p[j + 1].c_str(), 0, 0, 0, 0);					// TUOTTEET.TuoteNimi
        m_lstOne.SetItem(sel, 2, LVIF_TEXT, vect_p[j + 2].c_str(), 0, 0, 0, 0);					// TUOTTEET.Tuotetunnus
        m_lstOne.SetItem(sel, 3, LVIF_TEXT, vect_p[j + 3].c_str(), 0, 0, 0, 0);					// TUOTTEET.Yksikkˆ
        m_lstOne.SetItem(sel, 4, LVIF_TEXT, vect_p[j + 4].c_str(), 0, 0, 0, 0);					// TUOTTEET.VoHinta
        m_lstOne.SetItem(sel, 5, LVIF_TEXT, vect_p[j + 5].c_str(), 0, 0, 0, 0);					// TUOTTEET.AHinta
        m_lstOne.SetItem(sel, 6, LVIF_TEXT, haeAlv(pAlv, vect_p[j + 6], bvg), 0, 0, 0, 0);	// Alv.AlvPro -> Alv.AlvKanta|Alv.AlvRyhmaID

        m_lstOne.SetItemData(t, color);
		ryhma = "";
	  }
	}

	if(pAlv) delete [] pAlv;
}

CString DlgImport::haeAlv(Alv *pAlv, string alvID, BOOL bvg)
{
	int ai, sd;
	Paivays paivays;
	COleDateTime codt;
	CString alvPro("");

	if(!bvg)
	{
		for(int a=0; a<pAlv[0].size; a++) {
			if(pAlv[a].N == alvID.c_str()) { alvPro.Format("%d", pAlv[a].AlvPro); break; } }
	}
	else
	{
		ai = atoi(alvID.c_str());
		codt = COleDateTime::GetCurrentTime();
		sd = paivays.makeDate(codt.GetYear(), codt.GetMonth(), codt.GetDay());
		if((ai = pAlv[0].findAlvProIndex(pAlv, ai, sd)) != -1)
			alvPro.Format("%d", pAlv[ai].AlvPro);
	}

	return alvPro;
}

void DlgImport::OnOK() 
{
    BOOL bret = FALSE;
    int s = m_cmbTila.GetCurSel();

    if(s == 0) bret = tuoAsiakkaat();
    else if(s == 1) bret = tuoTyotyypit();
    else if(s == 2) bret = tuoTuotteet();

	m_update = bret;
}

BOOL DlgImport::tuoAsiakkaat()
{
    BOOL ret = TRUE;
    HDITEM hdi;
    DbSqlite db;
    vector<CString> vect;
    BOOL chk2, chk3, chk4;
    CString ryhma(""), name, address, custno, info, bid, rid;

    // Ssarakkeiden tila muistiin
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(2, &hdi); chk2 = hdi.iImage;
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(3, &hdi); chk3 = hdi.iImage;
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(4, &hdi); chk4 = hdi.iImage;

	// kysell‰‰n korvaamisesta
	Props::e().m_yanc_wt = Props::e().m_yanc_wp = Props::e().m_yanc_b = 0;

    try
	{
      if(m_lstOne.GetSelectedCount() == 0) throw(ERR_IMPORT_AS_0);					// onko valittu mit‰‰n?

      m_btnCancel.EnableWindow(FALSE);												// est‰ nappulat
      m_btnOK.EnableWindow(FALSE);
      m_cmbTila.EnableWindow(FALSE);

      m_stcInfo.SetWindowText(Props::i().lang("DLGIMPORT_21"));

      // Haetaan Oletuslaskuttajan (DFLT_BILLER) id
      if((vect = db.haeTaulusta("Biller", "id", 1, "", 1, "", "Name", "=", DFLT_BILLER)).size() == 0) throw(ERR_IMPORT_AS_1);
      bid = vect[0];

      int c = m_lstOne.GetItemCount();
      for(int i=0; i<c; i++)
	  {
        name.Format(Props::i().lang("DLGIMPORT_22"), i+1, c);
        m_stcInfo.SetWindowText(name);

        if(m_lstOne.GetItemText(i, 0) != "") ryhma = m_lstOne.GetItemText(i, 0); // P‰ivit‰ ryhm‰nime‰ tarvittaessa

        if(m_lstOne.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)             // Vain valitut rivit k‰sitell‰‰n
		{
          name = m_lstOne.GetItemText(i, 1);                                     // Tiedot
		  address = m_lstOne.GetItemText(i, 2);
          custno = m_lstOne.GetItemText(i, 3);
          info = m_lstOne.GetItemText(i, 4);

	      if(db.lisaaRegion(ryhma, &rid) != RETURN_OK) throw(ERR_IMPORT_AS_2);   // Lis‰‰ asiakasryhm‰ (jos ei ole jo olemassa), palauttaa id:n

          // P‰ivitt‰v‰ vai lis‰‰v‰, riippuu siit‰ onko jo tietokannassa ennest‰‰n
          db.lisaaWorkPlace(name, rid, chk3 ? custno : "", chk2 ? address : "", "", "", chk4 ? info : "", bid, NULL, WP_UPDATE);
          /*vect = db.haeTaulusta("WorkPlace", "id", 1, "", 2, "", "Name", "=", name, "AND", "Region_id", "=", rid);

          if(vect.size() == 0)                                                   // Ei lˆytynyt entist‰ lis‰t‰‰n uusi
			  db.lisaaWorkPlace(name, rid, chk3 ? custno : "", chk2 ? address : "", "", "", chk4 ? info : "", bid, NULL, WP_NOUPDATE);
          else
		  {
            if(chk2) { if(db.paivitaYleinen_id("WorkPlace", WORKPLACE_ADDRESS, address, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_AS_3); }
            if(chk3) { if(db.paivitaYleinen_id("WorkPlace", WORKPLACE_CUSTOMERNUMBER, custno, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_AS_3); }
            if(chk4) { if(db.paivitaYleinen_id("WorkPlace", WORKPLACE_INFO, info, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_AS_3); }
		  }*/
		}
	  }

      m_stcInfo.SetWindowText(Props::i().lang("DLGIMPORT_23"));
	}
    catch(int err)
	{
      if(err == ERR_IMPORT_AS_0)
	  {
	    MessageBox(Props::i().lang("DLGIMPORT_24"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
        ret = FALSE;
	  }
      else
	  {
        name.Format(Props::i().lang("DLGIMPORT_25"), err);
        m_stcInfo.SetWindowText(name);
	  }
	}

    m_btnCancel.EnableWindow(TRUE);                                              // salli nappulat
    m_btnOK.EnableWindow(TRUE);
    m_cmbTila.EnableWindow(TRUE);

    return ret;
}

BOOL DlgImport::tuoTyotyypit()
{
    BOOL ret = TRUE;
    BOOL chk2;
    HDITEM hdi;
    DbSqlite db;
    vector<CString> vect;
    CString name, tuotekoodi;

    // Ssarakkeiden tila muistiin
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(2, &hdi); chk2 = hdi.iImage;

	// kysell‰‰n korvaamisesta
	Props::e().m_yanc_wt = Props::e().m_yanc_wp = Props::e().m_yanc_b = 0;

    try
	{
      if(m_lstOne.GetSelectedCount() == 0) throw(ERR_IMPORT_TT_0);               // onko valittu mit‰‰n?

      m_btnCancel.EnableWindow(FALSE);                                           // est‰ nappulat
      m_btnOK.EnableWindow(FALSE);
      m_cmbTila.EnableWindow(FALSE);

      int c = m_lstOne.GetItemCount();
      for(int i=0; i<c; i++)
	  {
        name.Format(Props::i().lang("DLGIMPORT_26"), i+1, c);
        m_stcInfo.SetWindowText(name);

        if(m_lstOne.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)             // Vain valitut rivit k‰sitell‰‰n
		{
          name = m_lstOne.GetItemText(i, 1);                                     // Tiedot
		  tuotekoodi = m_lstOne.GetItemText(i, 2);

          // P‰ivitt‰v‰ vai lis‰‰v‰, riippuu siit‰ onko jo tietokannassa ennest‰‰n
          db.lisaaWorkType(name, chk2 ? tuotekoodi : "", WORK, "", "", "", "", "", WORKTYPE_POSITION_WORK, &name, WT_UPDATE);
          /*vect = db.haeTaulusta("WorkType", "id", 1, "", 2, "", "Name", "=", name, "AND", "Type", "=", WORK);

          if(vect.size() == 0)                                                   // Ei lˆytynyt entist‰ lis‰t‰‰n uusi
            db.lisaaWorkType(name, chk2 ? tuotekoodi : "", WORK, "", "", "", "", "", WORKTYPE_POSITION_WORK, &name, WT_NOUPDATE);
          else
            if(chk2) { if(db.paivitaYleinen_id("WorkType", WORKTYPE_PRODUCTNUMBER, tuotekoodi, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_TT_3); }*/
		}
	  }

      m_stcInfo.SetWindowText(Props::i().lang("DLGIMPORT_27"));
	}
    catch(int err)
	{
      if(err == ERR_IMPORT_TT_0)
	  {
	    MessageBox(Props::i().lang("DLGIMPORT_24"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
        ret = FALSE;
	  }
      else
	  {
        name.Format(Props::i().lang("DLGIMPORT_25"), err);
        m_stcInfo.SetWindowText(name);
	  }
	}

    m_btnCancel.EnableWindow(TRUE);                                              // salli nappulat
    m_btnOK.EnableWindow(TRUE);
    m_cmbTila.EnableWindow(TRUE);

    return ret;
}

BOOL DlgImport::tuoTuotteet()
{
    BOOL ret = TRUE;
    HDITEM hdi;
    DbSqlite db;
    vector<CString> vect;
    BOOL chk2, chk3, chk4, chk5, chk6;
    CString ryhma(""), name, tuotekoodi, yksikko, ostohinta, myyntihinta, alv, pgid;

    // Ssarakkeiden tila muistiin
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(2, &hdi); chk2 = hdi.iImage;
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(3, &hdi); chk3 = hdi.iImage;
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(4, &hdi); chk4 = hdi.iImage;
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(5, &hdi); chk5 = hdi.iImage;
    hdi.mask = HDI_IMAGE; m_lstOne.GetHeaderCtrl()->GetItem(6, &hdi); chk6 = hdi.iImage;

	// kysell‰‰n korvaamisesta
	Props::e().m_yanc_wt = Props::e().m_yanc_wp = Props::e().m_yanc_b = 0;

    try
	{
      if(m_lstOne.GetSelectedCount() == 0) throw(ERR_IMPORT_TU_0);               // onko valittu mit‰‰n?

      m_btnCancel.EnableWindow(FALSE);                                           // est‰ nappulat
      m_btnOK.EnableWindow(FALSE);
      m_cmbTila.EnableWindow(FALSE);

      int c = m_lstOne.GetItemCount();
      for(int i=0; i<c; i++)
	  {
        name.Format(Props::i().lang("DLGIMPORT_28"), i+1, c);
        m_stcInfo.SetWindowText(name);

        if(m_lstOne.GetItemText(i, 0) != "") ryhma = m_lstOne.GetItemText(i, 0); // P‰ivit‰ ryhm‰nime‰ tarvittaessa

        if(m_lstOne.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)             // Vain valitut rivit k‰sitell‰‰n
		{
          name = m_lstOne.GetItemText(i, 1);                                     // Tiedot
		  tuotekoodi = m_lstOne.GetItemText(i, 2);
          yksikko = m_lstOne.GetItemText(i, 3);
          ostohinta = m_lstOne.GetItemText(i, 4);
          myyntihinta = m_lstOne.GetItemText(i, 5);
          alv = m_lstOne.GetItemText(i, 6);

	      if(db.lisaaProductGroup(ryhma, &pgid) != RETURN_OK) throw(ERR_IMPORT_TU_2);          // Lis‰‰ tuoteryhm‰ (jos ei ole jo olemassa), palauttaa id:n

          // P‰ivitt‰v‰ vai lis‰‰v‰, riippuu siit‰ onko jo tietokannassa ennest‰‰n
          db.lisaaWorkType(name, chk2 ? tuotekoodi : "", PRODUCT, chk3 ? yksikko : "", chk4 ? ostohinta : "", chk5 ? myyntihinta : "", chk6 ? alv : "", pgid, WORKTYPE_POSITION_PRODUCT, &name, WT_UPDATE);
          /*vect = db.haeTaulusta("WorkType", "id", 1, "", 2, "", "Name", "=", name, "AND", "ProductGroup_id", "=", pgid);

          if(vect.size() == 0)                                                   // Ei lˆytynyt entist‰ lis‰t‰‰n uusi
            db.lisaaWorkType(name, chk2 ? tuotekoodi : "", PRODUCT, chk3 ? yksikko : "", chk4 ? ostohinta : "", chk5 ? myyntihinta : "", chk6 ? alv : "", pgid, WORKTYPE_POSITION_PRODUCT, &name, WT_NOUPDATE);
          else
		  {
            if(chk2) { if(db.paivitaYleinen_id("WorkType", WORKTYPE_PRODUCTNUMBER, tuotekoodi, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_TU_3); }
            if(chk3) { if(db.paivitaYleinen_id("WorkType", WORKTYPE_UNIT, yksikko, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_TU_3); }
            if(chk4) { if(db.paivitaYleinen_id("WorkType", WORKTYPE_PURCHASEPRICE, ostohinta, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_TU_3); }
            if(chk5) { if(db.paivitaYleinen_id("WorkType", WORKTYPE_SELLPRICE, myyntihinta, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_TU_3); }
            if(chk6) { if(db.paivitaYleinen_id("WorkType", WORKTYPE_ALV, alv, "", "", vect[0], FALSE) != RETURN_OK) throw(ERR_IMPORT_TU_3); }
		  }*/
		}
	  }

      m_stcInfo.SetWindowText(Props::i().lang("DLGIMPORT_29"));
	}
    catch(int err)
	{
      if(err == ERR_IMPORT_TU_0)
	  {
	    MessageBox(Props::i().lang("DLGIMPORT_24"), Props::e().m_app_title, MB_ICONEXCLAMATION|MB_TASKMODAL|MB_TOPMOST|MB_OK);
        ret = FALSE;
	  }
      else
	  {
        name.Format(Props::i().lang("DLGIMPORT_25"), err);
        m_stcInfo.SetWindowText(name);
	  }
	}

    m_btnCancel.EnableWindow(TRUE);                                              // salli nappulat
    m_btnOK.EnableWindow(TRUE);
    m_cmbTila.EnableWindow(TRUE);

    return ret;
}

void DlgImport::OnCancel() 
{
    if(m_update) EndDialog(IDOK);
    else EndDialog(IDCANCEL);
}

LRESULT DlgImport::OnMsgValitseKaikki(WPARAM wparam, LPARAM lparam)
{
    int i, s;

    s = m_lstOne.GetItemCount();
    for(i=0; i<s; i++) m_lstOne.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    m_lstOne.SetFocus();
    if(s > 0) m_lstOne.SetSelectionMark(0);

    return 0;
}
